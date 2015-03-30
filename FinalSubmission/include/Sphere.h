#ifndef _SPHERE_H__
#define _SPHERE_H__

/// @file Sphere.h
/// @author Ramon Blanquer
/// @brief A class for implicit sphere definitions

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include "Shape.h"
#include "Ray.h"

namespace geo
{
//----------------------------------------------------------------------------------------------------------------------
/// @class Sphere
/// @brief Class that hold an implicit definition of a sphere through center and radius parameters. It also implements
/// a method for finding intersections.
/// @author Ramon Blanquer
/// @todo Implement colour on the sphere
//----------------------------------------------------------------------------------------------------------------------
class Sphere : public Shape
{
public:

  //------------------------------------------------------------------------------------------------------------------
  /// @brief Sphere ctor, by default it will instanciate a 1 unit radius sphere in the origin (0,0,0).
  // -----------------------------------------------------------------------------------------------------------------
  Sphere();
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Sphere ctor using a radius and a center.
  /// @param[in] _center The position in where the sphere is positioned.
  /// @param[in] _radius The radius in scene units of the sphere object.
  /// @param[in] _colour The colour of the Sphere
  //------------------------------------------------------------------------------------------------------------------
   Sphere(ngl::Vec3 _center, float _radius, ngl::Colour _colour);
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Destructor so that all memory is freed.
  //------------------------------------------------------------------------------------------------------------------
  ~Sphere();
  //------------------------------------------------------------------------------------------------------------------
  // setters
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Setter for the radius.
  /// @param[in] _center The radius of the sphere.
  //------------------------------------------------------------------------------------------------------------------
  void setRadius(float _radius);
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Setter for the center.
  /// @param[in] _center Center of the sphere.
  //------------------------------------------------------------------------------------------------------------------
  void setCenter(ngl::Vec3 _center);
  //------------------------------------------------------------------------------------------------------------------
  // getters
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Returns radius of a sphere.
  /// @returns The radius of a sphere.
  //------------------------------------------------------------------------------------------------------------------
  virtual float getRadius() const;
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Returns center of a sphere.
  /// @returns The center of a sphere.
  //------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 getCenter() const;
  //------------------------------------------------------------------------------------------------------------------
  // other methods
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Calculates the intersection of the passed ray with the sphere according to the parametric form of a ray:
  /// R(t) = P + t * (Q - P)
  /// @param[in] _ray
  /// @returns The distance from the origin of the ray where it intersects the sphere.
  //------------------------------------------------------------------------------------------------------------------
  virtual float getIntersection(geo::Ray& _ray);
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Calculates what the normal is at a given point of a sphere. It doesn't check whether it is on the surface
  /// or not because that point will be passed through an intersection which we are sure about.
  /// @param[in] _p The position in the surface of the spehere where we calculate the normal.
  /// @return The normal of the sphere at a given point.
  //------------------------------------------------------------------------------------------------------------------
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p);

private:
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Center of the sphere, in world space coordinates.
  //------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_center;
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Radius of the sphere.
  //------------------------------------------------------------------------------------------------------------------
  double m_radius;
};
}

#endif // Sphere
