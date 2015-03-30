#include <cmath>
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
    m_center = ngl::Vec3(1,1,1);
    m_radius = 2.0f;
    m_type = 's';
    m_colour = ngl::Colour(1,1,1,1);
  }

  Sphere::~Sphere() {}

  Sphere::Sphere(ngl::Vec3 _center, float _radius, ngl::Colour _colour)
  {
      m_center = _center;
      m_radius = _radius;
      m_colour = _colour;
      m_type = 's';
  }

  // setters
  void Sphere::setRadius(float _radius)       {m_radius = _radius;}
  void Sphere::setCenter(ngl::Vec3 _center)   {m_center = _center;}

  // getters
  float Sphere::getRadius() const          {return m_radius;}
  ngl::Vec3 Sphere::getCenter() const      {return m_center;}

  float Sphere::getIntersection(Ray& ray)
  {
    // from Wikipedia: http://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

    ngl::Vec3 diff;
    diff = ray.getOrigin() - this->getCenter();

    float a = 1;
    float b = 2 * diff.dot(ray.getDirection());
    float c =   pow(ray.getOrigin().m_x - this->getCenter().m_x,2)
              + pow(ray.getOrigin().m_y - this->getCenter().m_y,2)
              + pow(ray.getOrigin().m_z - this->getCenter().m_z,2)
              - (this->getRadius()*this->getRadius());
    //float c = diff.dot(diff) - pow(this->getRadius(),2);

    float discriminant = b * b - 4 * c;

    if (discriminant < 0) {return -1;}
    else if (discriminant == 0) {return - 0.5 * b;}
    else {return - 0.5 * (b - sqrt(discriminant));}

  }

  ngl::Vec3 Sphere::getNormalAt(ngl::Vec3 _p)
  {
    ngl::Vec3 normal;
    normal = _p - m_center;
    normal.normalize();
    return normal;
  }
}


