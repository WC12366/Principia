﻿
#include "ksp_plugin/plugin.hpp"

#include <cmath>
#include <map>
#include <memory>

#include "geometry/permutation.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "quantities/si.hpp"
#include "testing_utilities/almost_equals.hpp"
#include "testing_utilities/numerics.hpp"
#include "testing_utilities/solar_system.hpp"

using principia::geometry::Bivector;
using principia::geometry::Permutation;
using principia::quantities::Abs;
using principia::quantities::Sqrt;
using principia::si::Radian;
using principia::si::AstronomicalUnit;
using principia::testing_utilities::AlmostEquals;
using principia::testing_utilities::ICRFJ2000Ecliptic;
using principia::testing_utilities::AbsoluteError;
using principia::testing_utilities::SolarSystem;
using testing::Eq;
using testing::Lt;

namespace principia {
namespace ksp_plugin {

class PluginTest : public testing::Test {
 protected:
  PluginTest()
      : looking_glass_(Permutation<ICRFJ2000Ecliptic, AliceSun>::XZY),
        solar_system_(SolarSystem::AtСпутникLaunch()),
        bodies_(solar_system_->massive_bodies()),
        initial_time_(solar_system_->trajectories().front()->last_time()),
        sun_gravitational_parameter_(
            bodies_[SolarSystem::kSun]->gravitational_parameter()),
        planetarium_rotation_(1 * Radian) {
    plugin_ = std::make_unique<Plugin>(initial_time_,
                                       SolarSystem::kSun,
                                       sun_gravitational_parameter_,
                                       planetarium_rotation_);
  }

  void InsertAllSolarSystemBodies() {
  for (std::size_t index = SolarSystem::kSun + 1;
       index < bodies_.size();
       ++index) {
    Index const parent_index = SolarSystem::parent(index);
    Displacement<AliceSun> const from_parent_position = looking_glass_(
        solar_system_->trajectories()[index]->last_position() -
        solar_system_->trajectories()[parent_index]->last_position());
    Velocity<AliceSun> const from_parent_velocity = looking_glass_(
        solar_system_->trajectories()[index]->last_velocity() -
        solar_system_->trajectories()[parent_index]->last_velocity());
    plugin_->InsertCelestial(index,
                             bodies_[index]->gravitational_parameter(),
                             parent_index,
                             from_parent_position,
                             from_parent_velocity);
  }
  }

  Permutation<ICRFJ2000Ecliptic, AliceSun> looking_glass_;
  std::unique_ptr<SolarSystem> solar_system_;
  SolarSystem::Bodies bodies_;
  Instant initial_time_;
  GravitationalParameter sun_gravitational_parameter_;
  Angle planetarium_rotation_;

  std::unique_ptr<Plugin> plugin_;
};

TEST_F(PluginTest, Initialisation) {
  InsertAllSolarSystemBodies();
  plugin_->EndInitialisation();
  for (std::size_t index = SolarSystem::kSun + 1;
       index < bodies_.size();
       ++index) {
    Index const parent_index = SolarSystem::parent(index);
    EXPECT_THAT(solar_system_->trajectories()[index]->last_position() -
                solar_system_->trajectories()[parent_index]->last_position(),
                AlmostEquals(looking_glass_.Inverse()(
                    plugin_->CelestialDisplacementFromParent(index)),
                    250000));
    EXPECT_THAT(solar_system_->trajectories()[index]->last_velocity() -
                solar_system_->trajectories()[parent_index]->last_velocity(),
                AlmostEquals(looking_glass_.Inverse()(
                    plugin_->CelestialParentRelativeVelocity(index)),
                    1000));
  }
}

TEST_F(PluginTest, VesselInsertion) {
  GUID const guid = "Test Satellite";
  InsertAllSolarSystemBodies();
  plugin_->EndInitialisation();
  bool const inserted = plugin_->InsertOrKeepVessel(guid,
                                                    SolarSystem::kEarth);
  EXPECT_TRUE(inserted);
  Displacement<AliceSun> const displacement({3111.0 * Kilo(Metre),
                                             4400.0 * Kilo(Metre),
                                             3810.0 * Kilo(Metre)});
  auto const tangent = displacement * Bivector<double, AliceSun>({1, 2, 3});
  Vector<double, AliceSun> unit_tangent = tangent / tangent.Norm();
  EXPECT_THAT(InnerProduct(unit_tangent, displacement / displacement.Norm()),
              Eq(0));
  // This yields a circular orbit.
  Velocity<AliceSun> const velocity =
      Sqrt(bodies_[SolarSystem::kEarth]->gravitational_parameter() /
               displacement.Norm()) * unit_tangent;
  plugin_->SetVesselStateOffset(guid, displacement, velocity);
  EXPECT_THAT(
      AbsoluteError(plugin_->VesselDisplacementFromParent(guid), displacement),
      Lt(DBL_EPSILON * AstronomicalUnit));
  EXPECT_THAT(plugin_->VesselParentRelativeVelocity(guid),
              AlmostEquals(velocity));
}

}  // namespace ksp_plugin
}  // namespace principia
