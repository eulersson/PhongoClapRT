#ifndef _PLANE_H_
#define _PLANE_H_

/// @file Plane.h
/// @author Ramon Blanquer
/// @brief Implements the interface for creating a plane shape and the methods for finding its intersections

#include "Shape.h"
#include "Ray.h"
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

namespace geo
{
//----------------------------------------------------------------------------------------------------------------------
/// @class Plane
/// @brief Inherits from shape. Implements functionability for plane shape and its materials
///  and the ray-plane intersections algorithms.
/// @author Ramon Blanquer
/// @todo Implement new ways to instanciate a plane, ie specifying three points, or one point and a normal
//----------------------------------------------------------------------------------------------------------------------
class Plane : public Shape
{
public:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Default constructor for the plane. If no arguments passed it will be initialised with distance(5) n(1,1,1)
  // -------------------------------------------------------------------------------------------------------------------
  Plane();
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief This constructor reads some arguments and pass them to the private interface
  /// @param[in] _distance  Distance from the origin the plane is located at.
  /// @param[in] _n         Normal of the plane.
  /// @param[in] _c         Plain colour of the plane.
  // -------------------------------------------------------------------------------------------------------------------
  Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief This constructor reads some arguments and pass them to the private interface. For checkerboard planes.
  /// @param[in] _distance  Distance from the origin the plane is located at.
  /// @param[in] _n         Primary colour of the checkerboard.
  /// @param[in] _c1        Secondary colour of the checkerboard.
  // -------------------------------------------------------------------------------------------------------------------
  Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c1, ngl::Colour _c2);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Virtual method that implements the ray-plane intersection
  /// @param[in] _ray Ray that will be used to solve the equation for finding the "t" parameter of the ray that
  /// satisfies that this point is shared by both ray and plane aka intersection point.
  /// @returns The 't' parameter from the R = O + t * d equation form of the line, thus the intersection point.
  // -------------------------------------------------------------------------------------------------------------------
  virtual float getIntersection(geo::Ray &_ray);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Simple getter that returns the normal of the plane
  /// @returns The normal of the plane
  // -------------------------------------------------------------------------------------------------------------------
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Returns the colour for plain objects, in other words for non-checkerboard planes
  /// @return The colour of the plane
  // -------------------------------------------------------------------------------------------------------------------
  virtual ngl::Colour getColour();
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Returns the colour for checker-board planes. This will imply passing an intersection point in world space
  /// so that we can make the right calculations to see whether we must return the colour1 or colour2.
  /// @param[in] _isect Position in world space of the intersecting point.
  /// @return The colour of the plane at the intersection point
  // -------------------------------------------------------------------------------------------------------------------
  virtual ngl::Colour getColour(ngl::Vec3 &_isect);

private:
  // -------------------------------------------------------------------------------------------------------------------
  /// @brief Distance from the origin the plane is located at
  // -------------------------------------------------------------------------------------------------------------------
  float m_distance;
  // -------------------------------------------------------------------------------------------------------------------
  /// @brief Normal of the plane.
  // -------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_n;
};
}
#endif // Plane.h
