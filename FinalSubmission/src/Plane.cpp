/// @file Plane.cpp
/// @brief Implementation files for Plane class.

#include <ngl/Vec3.h>
#include "Plane.h"
#include "Ray.h"
#include "Material.h"

namespace geo
{
Plane::Plane() : m_distance(5.0f), m_n(ngl::Vec3(1,1,1))
{
  m_colour = ngl::Colour(1,0,0);
  m_type='p';
  Material* mat = new Material(ngl::Colour(1,1,1,1), ngl::Colour(0,0,0,1));
  m_material = mat;
}

Plane::Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c)
{
  m_distance = _distance;
  m_colour = _c;
  m_type='p';

  Material* mat = new Material(_c);
  m_material = mat;

  if(_n.length() > 1.01 || _n.length() < 0.99)
  {
    _n.normalize();
    m_n = _n;
  }
  else
  {
    m_n = _n;
  }
}

Plane::Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c1, ngl::Colour _c2)
{
  m_distance = _distance;
  m_colour = _c1;
  m_type='p';

  Material* mat = new Material(_c1, _c2);
  m_material = mat;

  if(_n.length() > 1.01 || _n.length() < 0.99)
  {
    _n.normalize();
    m_n = _n;
  }
  else
  {
    m_n = _n;
  }
}

float Plane::getIntersection(geo::Ray &_ray)
{
  ngl::Vec3 ray_dir = _ray.getDirection();

  float a = ray_dir.dot(m_n);

  if(a == 0)
  {
    // ray is paralel
    return -1;
  }
  else
  {
    double b = m_n.dot(_ray.getOrigin() + (-(m_distance*m_n)));
    return -1*b/a;
  }
}

ngl::Vec3 Plane::getNormalAt(ngl::Vec3 _p)
{
  return m_n;
}

ngl::Colour Plane::getColour()
{
  return m_material->objColour();
}

ngl::Colour Plane::getColour(ngl::Vec3 &_isect)
{
  if (m_material->m_isChecker)
  {
    return m_material->objColour(_isect);
  }
  else
  {
    return m_material->objColour();
  }
}
}
