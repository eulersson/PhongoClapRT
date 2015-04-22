#ifndef _PLANE_H_
#define _PLANE_H_

#include "Shape.h"
#include "Ray.h"
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

namespace geo
{
class Plane : public Shape
{
public:

  Plane() : m_distance(5.0f), m_n(ngl::Vec3(1,1,1))
  {
    m_colour = ngl::Colour(1,0,0);
    m_type='p';
    Material mat(ngl::Colour(1,1,1,1), ngl::Colour(0,0,0,1));
    m_material = mat;
  }

  Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c);

  Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c1, ngl::Colour _c2);

  virtual float getIntersection(geo::Ray &_ray);

  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p) {return m_n;}

  virtual ngl::Colour getColour()
  {
      return m_material.objColour();
  }

  virtual ngl::Colour getColour(ngl::Vec3 &_isect)
  {
    if (m_material.m_isChecker)
    {
      return m_material.objColour(_isect);
    }
    else
    {
      return m_material.objColour();
    }
  }


private:
  float m_distance;
  ngl::Vec3 m_n;


};
}
#endif // Plane.h
