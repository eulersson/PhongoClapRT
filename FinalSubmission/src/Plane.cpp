#include <ngl/Vec3.h>

#include "Plane.h"
#include "Ray.h"

namespace geo
{
Plane::Plane(float _distance, ngl::Vec3 _n, ngl::Colour _c)
{
  m_distance = _distance;
  m_colour = _c;
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

}
