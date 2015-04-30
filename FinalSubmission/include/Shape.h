#ifndef _SHAPE_H_
#define _SHAPE_H_

/// @file Scene.h
/// @author Ramon Blanquer
/// @brief This hold all the objects and lights that the parser interpred and later pushed into th escene

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include "Material.h"
#include "Ray.h"


namespace geo {
//----------------------------------------------------------------------------------------------------------------------
/// @class Shape
/// @brief Semi abstract class with virtual methods that holds all the calls for getting intersections, getting normals,
/// also for specifying the properties of the material that will be hold by the Material member of this class
/// @author Ramon Blanquer
//----------------------------------------------------------------------------------------------------------------------
class Shape
{
public:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Default constructor.
  //--------------------------------------------------------------------------------------------------------------------
  Shape() {}
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Frees any memory grabbed from the heap.
  //--------------------------------------------------------------------------------------------------------------------
  ~Shape() {delete m_material;}
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Returs colour of a Shape object
  /// @returns Colour of the Shape object
  //--------------------------------------------------------------------------------------------------------------------
  virtual ngl::Colour getColour() = 0;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Returns colour depending on intersection point
  /// @return Colour of a Shape object
  //--------------------------------------------------------------------------------------------------------------------
  virtual ngl::Colour getColour(ngl::Vec3 &_isect) = 0;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Passing a ray it will calculate the intersection in the derived class, this is purely abstract method
  /// @returns Variable (mathematically speaking) **'t'** in equation `R = O + t * d`.
  //--------------------------------------------------------------------------------------------------------------------
  virtual float getIntersection(geo::Ray& _ray) = 0;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Returns the normal at a given point
  /// @returns Normal
  //--------------------------------------------------------------------------------------------------------------------
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p) = 0;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Sets parameters related to refraction, this will be given to the Material class.
  /// @param[in] _ior          Index of refraction.
  /// @param[in] _transparency Amount of refraction of the object.
  /// @param[in] _ diffuse_intensity This is calculated automatically, but it is the complementary of transparency,
  /// I could say this is the 'opacity'.
  //--------------------------------------------------------------------------------------------------------------------
  void hasRefraction(float _ior, float _transparency, float _diffuse_intensity)
  {
    m_material->setRefraction(_ior,_transparency, _diffuse_intensity);
  }
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Sets reflection attributes.
  /// @param[in] _refl_intensity    How reflective the material is.
  /// @param[in] _diffuse_intensity How non-reflective the material is.
  //--------------------------------------------------------------------------------------------------------------------
  void hasReflection(float _refl_intensity, float _diffuse_intensity)
  {
    m_material->setReflection(_refl_intensity, _diffuse_intensity);
  }
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Returns the material attached to a shape object. This is useful for querying or changing private interface,
  /// that's why it is not const.
  /// @returns The object associated with a Shape instance.
  //--------------------------------------------------------------------------------------------------------------------
  Material* getMaterial() {return m_material;}
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Derived classes will be Spheres or Planes, I will store the type of geometry in this attribute.
  /// @returns Whether it is a sphere or a plane, this will be expanded to other geometry in the future.
  //--------------------------------------------------------------------------------------------------------------------
  char getType() {return m_type;}

protected:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Type of geometric object it is.
  //--------------------------------------------------------------------------------------------------------------------
  char m_type;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Colour of the shape.
  //--------------------------------------------------------------------------------------------------------------------
  ngl::Colour m_colour;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Material attached to the Shape object.
  //--------------------------------------------------------------------------------------------------------------------
  Material* m_material;
};
}

#endif
