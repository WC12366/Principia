#pragma once

#include "Geometry/Grassmann.hpp"
#include "Geometry/Sign.hpp"

namespace principia {
namespace geometry {

template<typename FromFrame, typename ToFrame>
class LinearMap {
 public:
  LinearMap() = default;
  virtual ~LinearMap() = default;

  virtual Sign Determinant() const = 0;

// The following is the contract that must be implemented by subclasses.
// Apologies for the commented-out code, but we cannot write this in real C++
// for a variety of reasons.
//
//  virtual LinearMap<ToFrame, FromFrame> Inverse() const = 0;
//
//  template<typename Scalar>
//  virtual Vector<Scalar, ToFrame> operator()(
//      Vector<Scalar, FromFrame> const& vector) const = 0;
//
//  template<typename Scalar>
//  virtual Bivector<Scalar, ToFrame> operator()(
//      Bivector<Scalar, FromFrame> const& bivector) const = 0;
//
//  template<typename Scalar>
//  virtual Trivector<Scalar, ToFrame> operator()(
//      Trivector<Scalar, FromFrame> const& trivector) const = 0;
//
//protected:
//  template<typename Scalar>
//  virtual R3Element<Scalar> operator()(
//      R3Element<Scalar> const& r3_element) const = 0;
};

}  // namespace geometry
}  // namespace principia
