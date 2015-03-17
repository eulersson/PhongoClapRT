#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include "Shape.h"
#include "Sphere.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file Sphere.cpp
/// @brief implementation files for Sphere class
//----------------------------------------------------------------------------------------------------------------------

namespace geo
{
  Sphere::Sphere()
  {
      m_center = ngl::Vec3(0.0,0.0,0.0);
      m_radius = 1.0;
  }

  Sphere::~Sphere() {}

  Sphere::Sphere(ngl::Vec3 _center, float _radius, ngl::Colour _colour)
  {
      m_center = _center;
      m_radius = _radius;
      m_colour = _colour;
  }

  // setters
  void Sphere::setRadius(float _radius)       {m_radius = _radius;}
  void Sphere::setCenter(ngl::Vec3 _center)   {m_center = _center;}
  void Sphere::setColour(ngl::Colour _colour) {m_colour = _colour;}

  // getters
  float Sphere::getRadius() {return m_radius;}
  ngl::Vec3 Sphere::getCenter() {return m_center;}
  //ngl::Vec3 Sphere::getShapeColour() {return m_colour;}

  float Sphere::getIntersection(Ray const& ray)
  {
    // from Wikipedia: http://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

    return 4.05;

  }

  ngl::Vec3 Sphere::getNormalAt(ngl::Vec3 _p)
  {
    ngl::Vec3 normal;
    normal = _p - m_center;
    normal.normalize();
    return normal;
  }
}


