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
  Plane() : m_distance(5.0f),
            m_n(ngl::Vec3(1,1,1)) {m_colour = ngl::Colour(1,0,0); m_type='p';}
  Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c);
  virtual float getIntersection(geo::Ray &_ray);
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p) {return m_n;}

private:
  float m_distance;
  ngl::Vec3 m_n;


};
}
#endif // Plane.h
