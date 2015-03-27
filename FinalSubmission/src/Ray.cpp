#include <ngl/Vec3.h>
#include "Ray.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file Ray.cpp
/// @brief implementation files for Ray class
//----------------------------------------------------------------------------------------------------------------------
namespace geo
{
Ray::Ray(ngl::Vec3 _origin, ngl::Vec3 _direction)
{
  m_origin = _origin;

  // check that it is unit length, if not, normalize
  if (_direction.length() > 1.1 || _direction.length() < 0.9) {_direction.normalize();}
  m_direction = _direction;
}

Ray::Ray(ngl::Vec3 _A, ngl::Vec3 _B, bool _p)
{

  m_origin = _A;

  ngl::Vec3 direction = _B - _A;
  direction.normalize();

  m_direction = direction;
}

Ray::~Ray() {;}

void Ray::setOrigin(ngl::Vec3 _origin) {m_origin = _origin;}

void Ray::setDirection(ngl::Vec3 _direction)
{
  // check that it is unit length, if not, normalize
  if (_direction.length() > 1.1 || _direction.length() < 0.9) {_direction.normalize();}
  m_direction = _direction;
}

ngl::Vec3 Ray::getOrigin() {return m_origin;}

ngl::Vec3 Ray::getDirection() {return m_direction;}
}
