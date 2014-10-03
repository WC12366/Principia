﻿#pragma once

#include "testing_utilities/solar_system.hpp"

#include <vector>

#include "geometry/epoch.hpp"
#include "geometry/grassmann.hpp"
#include "geometry/named_quantities.hpp"
#include "geometry/point.hpp"
#include "physics/body.hpp"
#include "physics/n_body_system.hpp"
#include "physics/trajectory.hpp"
#include "quantities/named_quantities.hpp"
#include "quantities/quantities.hpp"
#include "quantities/si.hpp"

using principia::geometry::Displacement;
using principia::geometry::Instant;
using principia::geometry::JulianDate;
using principia::geometry::Point;
using principia::geometry::Vector;
using principia::physics::Body;
using principia::physics::NBodySystem;
using principia::physics::Trajectory;
using principia::quantities::GravitationalParameter;
using principia::quantities::Pow;
using principia::quantities::SIUnit;
using principia::quantities::Time;
using principia::si::Day;
using principia::si::Kilo;
using principia::si::Kilogram;
using principia::si::Metre;
using principia::si::Second;

namespace principia {
namespace testing_utilities {

std::unique_ptr<SolarSystem> SolarSystem::AtСпутникLaunch() {
  // Number of days since the JD epoch. JD2436116.3115 is the time of the launch
  // of Простейший Спутник-1.
  Instant const kСпутникLaunchTime = JulianDate(2436116.3115);

  std::unique_ptr<SolarSystem> solar_system(new SolarSystem);

  // All data is from the Jet Propulsion Laboratory's HORIZONS system.

  // Star.
  Trajectory<ICRFJ2000Ecliptic>* sun_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(*solar_system->massive_bodies_[kSun]));
  sun_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           { 1.138350928138014E+06 * Kilo(Metre),
             6.177753685036716E+05 * Kilo(Metre),
            -3.770941657504326E+04 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-5.067456621846211E-03 * Kilo(Metre) / Second,
             1.259599196445122E-02 * Kilo(Metre) / Second,
             9.778588606052481E-05 * Kilo(Metre) / Second})});

  // Planets.

  // Gas giants.
  Trajectory<ICRFJ2000Ecliptic>* jupiter_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kJupiter]));
  jupiter_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-7.950209667306620E+08 * Kilo(Metre),
            -1.784285526424396E+08 * Kilo(Metre),
             1.853825132237791E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 2.709330231918198E+00 * Kilo(Metre) / Second,
            -1.213073724288562E+01 * Kilo(Metre) / Second,
            -1.088748435062713E-02 * Kilo(Metre) / Second})});
  Trajectory<ICRFJ2000Ecliptic>* saturn_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kSaturn]));
  saturn_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-3.774715321901159E+08 * Kilo(Metre),
            -1.451892263379818E+09 * Kilo(Metre),
             4.040621083792380E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 8.817029873536633E+00 * Kilo(Metre) / Second,
            -2.466058486223613E+00 * Kilo(Metre) / Second,
            -3.068419809533604E-01 * Kilo(Metre) / Second})});
  Trajectory<ICRFJ2000Ecliptic>* neptune_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kNeptune]));
  neptune_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-3.810689792831146E+09 * Kilo(Metre),
            -2.456423858579051E+09 * Kilo(Metre),
             1.383694320077938E+08 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 2.913267720085410E+00 * Kilo(Metre) / Second,
            -4.535247383721019E+00 * Kilo(Metre) / Second,
             2.589759251085161E-02 * Kilo(Metre) / Second})});
  Trajectory<ICRFJ2000Ecliptic>* uranus_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kUranus]));
  uranus_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-1.729995609344851E+09 * Kilo(Metre),
             2.159967050539728E+09 * Kilo(Metre),
             3.048735047038063E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-5.366539669972795E+00 * Kilo(Metre) / Second,
            -4.575802196749351E+00 * Kilo(Metre) / Second,
             5.261322980347850E-02 * Kilo(Metre) / Second})});

  // Telluric planets.
  Trajectory<ICRFJ2000Ecliptic>* earth_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kEarth]));
  earth_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           { 1.475150112055673E+08 * Kilo(Metre),
             3.144435102288270E+07 * Kilo(Metre),
            -3.391764309344300E+04 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-6.635753510543799E+00 * Kilo(Metre) / Second,
             2.904321639216012E+01 * Kilo(Metre) / Second,
             3.125252418990812E-03 * Kilo(Metre) / Second})});
  Trajectory<ICRFJ2000Ecliptic>* venus_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kVenus]));
  venus_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           { 6.084974577091119E+07 * Kilo(Metre),
            -9.037413730207849E+07 * Kilo(Metre),
            -4.719158908401959E+06 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 2.903958257174759E+01 * Kilo(Metre) / Second,
             1.910383147602264E+01 * Kilo(Metre) / Second,
            -1.418780340302349E+00 * Kilo(Metre) / Second})});
  Trajectory<ICRFJ2000Ecliptic>* mars_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(*solar_system->massive_bodies_[kMars]));
  mars_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-2.440047184660406E+08 * Kilo(Metre),
            -2.002994580992744E+07 * Kilo(Metre),
             5.577600092368793E+06 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 2.940381268511949E+00 * Kilo(Metre) / Second,
            -2.206625841382794E+01 * Kilo(Metre) / Second,
            -5.348179460834037E-01 * Kilo(Metre) / Second})});
  Trajectory<ICRFJ2000Ecliptic>* mercury_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kMercury]));
  mercury_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-3.013851560892715E+07 * Kilo(Metre),
             3.823388939456400E+07 * Kilo(Metre),
             5.907240907643730E+06 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-4.731017449071709E+01 * Kilo(Metre) / Second,
            -2.918747853895398E+01 * Kilo(Metre) / Second,
             1.963450229872517E+00 * Kilo(Metre) / Second})});

  // End of planets.

  // Satellite of Jupiter.
  Trajectory<ICRFJ2000Ecliptic>* ganymede_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kGanymede]));
  ganymede_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-7.942681422941415E+08 * Kilo(Metre),
            -1.776681035234876E+08 * Kilo(Metre),
             1.857215495334835E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-5.026319376504355E+00 * Kilo(Metre) / Second,
            -4.481735740234995E+00 * Kilo(Metre) / Second,
             1.326192167761359E-01 * Kilo(Metre) / Second})});

  // Satellite of Saturn.
  Trajectory<ICRFJ2000Ecliptic>* titan_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kTitan]));
  titan_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-3.771930512714775E+08 * Kilo(Metre),
            -1.452931696594699E+09 * Kilo(Metre),
             4.091643033375849E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 1.433381483669744E+01 * Kilo(Metre) / Second,
            -1.422590492527597E+00 * Kilo(Metre) / Second,
            -1.375826555026097E+00 * Kilo(Metre) / Second})});

  // Satellites of Jupiter.
  Trajectory<ICRFJ2000Ecliptic>* callisto_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kCallisto]));
  callisto_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-7.951805452047400E+08 * Kilo(Metre),
            -1.802957437059298E+08 * Kilo(Metre),
             1.847154088070625E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 1.091928199422218E+01 * Kilo(Metre) / Second,
            -1.278098875182818E+01 * Kilo(Metre) / Second,
             5.878649120351949E-02 * Kilo(Metre) / Second})});
  Trajectory<ICRFJ2000Ecliptic>* io_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(*solar_system->massive_bodies_[kIo]));
  io_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-7.946073188298367E+08 * Kilo(Metre),
            -1.783491436977172E+08 * Kilo(Metre),
             1.854699192614355E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-5.049684272040893E-01 * Kilo(Metre) / Second,
             4.916473261567652E+00 * Kilo(Metre) / Second,
             5.469177855959977E-01 * Kilo(Metre) / Second})});

  // Satellite of Earth.
  Trajectory<ICRFJ2000Ecliptic>* moon_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(*solar_system->massive_bodies_[kMoon]));
  moon_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           { 1.478545271460863E+08 * Kilo(Metre),
             3.122566749814625E+07 * Kilo(Metre),
             1.500491219719345E+03 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-6.099833968412930E+00 * Kilo(Metre) / Second,
             2.985006033154299E+01 * Kilo(Metre) / Second,
            -1.952438319420470E-02 * Kilo(Metre) / Second})});

  // Satellite of Jupiter.
  Trajectory<ICRFJ2000Ecliptic>* europa_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kEuropa]));
  europa_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-7.944180333947762E+08 * Kilo(Metre),
            -1.787346439588362E+08 * Kilo(Metre),
             1.853675837527557E+07 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 8.811255547505889E+00 * Kilo(Metre) / Second,
             5.018147960240774E-02 * Kilo(Metre) / Second,
             6.162195631257494E-01 * Kilo(Metre) / Second})});

  // Satellite of Neptune.
  Trajectory<ICRFJ2000Ecliptic>* triton_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kTriton]));
  triton_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-3.810797098554279E+09 * Kilo(Metre),
            -2.456691608348630E+09 * Kilo(Metre),
             1.381629136719314E+08 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-1.047462448797063E+00 * Kilo(Metre) / Second,
            -4.404556713303486E+00 * Kilo(Metre) / Second,
             1.914469843538767E+00 * Kilo(Metre) / Second})});

  // Dwarf planet (scattered disc object).
  Trajectory<ICRFJ2000Ecliptic>* eris_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(*solar_system->massive_bodies_[kEris]));
  eris_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           { 1.317390066862979E+10 * Kilo(Metre),
             2.221403321600002E+09 * Kilo(Metre),
            -5.736076877456254E+09 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           { 4.161883594267296E-01 * Kilo(Metre) / Second,
             1.872714752602233E+00 * Kilo(Metre) / Second,
             1.227093842948539E+00 * Kilo(Metre) / Second})});

  // Dwarf planet (Kuiper belt object).
  Trajectory<ICRFJ2000Ecliptic>* pluto_trajectory(
      new Trajectory<ICRFJ2000Ecliptic>(
          *solar_system->massive_bodies_[kPluto]));
  pluto_trajectory->Append(
      kСпутникLaunchTime,
      {kSolarSystemBarycentre + Displacement<ICRFJ2000Ecliptic>(
           {-4.406985590968750E+09 * Kilo(Metre),
             2.448731153209013E+09 * Kilo(Metre),
             1.012525975599311E+09 * Kilo(Metre)}),
       Velocity<ICRFJ2000Ecliptic>(
           {-1.319871918266467E+00 * Kilo(Metre) / Second,
            -5.172112237151897E+00 * Kilo(Metre) / Second,
             9.407707128142039E-01 * Kilo(Metre) / Second})});

  // End of celestial bodies.

  solar_system->trajectories_.emplace_back(sun_trajectory);
  solar_system->trajectories_.emplace_back(jupiter_trajectory);
  solar_system->trajectories_.emplace_back(saturn_trajectory);
  solar_system->trajectories_.emplace_back(neptune_trajectory);
  solar_system->trajectories_.emplace_back(uranus_trajectory);
  solar_system->trajectories_.emplace_back(earth_trajectory);
  solar_system->trajectories_.emplace_back(venus_trajectory);
  solar_system->trajectories_.emplace_back(mars_trajectory);
  solar_system->trajectories_.emplace_back(mercury_trajectory);
  solar_system->trajectories_.emplace_back(ganymede_trajectory);
  solar_system->trajectories_.emplace_back(titan_trajectory);
  solar_system->trajectories_.emplace_back(callisto_trajectory);
  solar_system->trajectories_.emplace_back(io_trajectory);
  solar_system->trajectories_.emplace_back(moon_trajectory);
  solar_system->trajectories_.emplace_back(europa_trajectory);
  solar_system->trajectories_.emplace_back(triton_trajectory);
  solar_system->trajectories_.emplace_back(eris_trajectory);
  solar_system->trajectories_.emplace_back(pluto_trajectory);

  return std::move(solar_system);
}

SolarSystem::SolarSystem() {
  // All data is from the Jet Propulsion Laboratory's HORIZONS system unless
  // otherwise specified.

  // Star.
  Body* sun(
      new Body(1.3271244004193938E+11 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));

  // Planets.

  // Gas giants.
  Body* jupiter(new Body(126686511 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));
  Body* saturn(new Body(37931207.8 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));
  Body* neptune(new Body(6835107 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));
  Body* uranus(new Body(5793966 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));

  // Telluric planets.
  Body* earth(new Body(398600.440 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));
  Body* venus(new Body(324858.63 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));
  Body* mars(new Body(42828.3 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));
  Body* mercury(new Body(22032.09 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));

  // End of planets.

  // Satellite of Jupiter.
  Body* ganymede(new Body(1482E20 * Kilogram));

  // Satellite of Saturn.
  Body* titan(new Body(8978.13 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));

  // Satellites of Jupiter.
  Body* callisto(new Body(1076E20 * Kilogram));
  Body* io(new Body(893.3E20 * Kilogram));

  // Satellite of Earth.
  Body* moon(new Body(4902.798 * Pow<3>(Kilo(Metre)) / Pow<2>(Second)));

  // Satellite of Jupiter.
  Body* europa(new Body(479.7E20 * Kilogram));

  // Satellite of Neptune.
  Body* triton(new Body(214.7E20 * Kilogram));

  // Dwarf planet (scattered disc object).
  // Mass from Brown, Michael E.; Schaller, Emily L. (15 June 2007).
  // "The Mass of Dwarf Planet Eris", in Science, through Wikipedia.
  Body* eris(new Body(1.67E22 * Kilogram));

  // Dwarf planet (Kuiper belt object).
  Body* pluto(new Body(1.307E22 * Kilogram));

  // End of celestial bodies.

  massive_bodies_.emplace_back(sun);
  massive_bodies_.emplace_back(jupiter);
  massive_bodies_.emplace_back(saturn);
  massive_bodies_.emplace_back(neptune);
  massive_bodies_.emplace_back(uranus);
  massive_bodies_.emplace_back(earth);
  massive_bodies_.emplace_back(venus);
  massive_bodies_.emplace_back(mars);
  massive_bodies_.emplace_back(mercury);
  massive_bodies_.emplace_back(ganymede);
  massive_bodies_.emplace_back(titan);
  massive_bodies_.emplace_back(callisto);
  massive_bodies_.emplace_back(io);
  massive_bodies_.emplace_back(moon);
  massive_bodies_.emplace_back(europa);
  massive_bodies_.emplace_back(triton);
  massive_bodies_.emplace_back(eris);
  massive_bodies_.emplace_back(pluto);
}

SolarSystem::Bodies SolarSystem::massive_bodies() {
  return std::move(massive_bodies_);
}

SolarSystem::Bodies SolarSystem::massless_bodies() {
  return std::move(massless_bodies_);
}

physics::NBodySystem<ICRFJ2000Ecliptic>::Trajectories
SolarSystem::trajectories() const {
  physics::NBodySystem<ICRFJ2000Ecliptic>::Trajectories result;
  for (auto const& trajectory : trajectories_) {
    result.push_back(trajectory.get());
  }
  return result;
}

int SolarSystem::parent(int const index) {
  switch (index) {
    case kSun:
      LOG(FATAL) << "The Sun has no parent";
      return kSun;  // Silly compiler is silly.
    case kJupiter:
    case kSaturn:
    case kNeptune:
    case kUranus:
    case kEarth:
    case kVenus:
    case kMars:
    case kMercury:
    case kEris:
    case kPluto:
      return kSun;
    case kGanymede:
    case kCallisto:
    case kIo:
    case kEuropa:
      return kJupiter;
    case kTitan:
      return kSaturn;
    case kMoon:
      return kEarth;
    case kTriton:
      return kNeptune;
    default:
      LOG(FATAL) << "Undefined index";
      return kSun;
  }
}

}  // namespace testing_utilities
}  // namespace principia
