#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include "Material.h"
#include "Ray.h"


namespace geo {
class Shape
{
public:
  virtual ngl::Colour getColour() = 0;
  virtual ngl::Colour getColour(ngl::Vec3 &_isect) = 0;

  // virtual functions
  virtual float getIntersection(geo::Ray& _ray) = 0;
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p) = 0;
  void hasRefraction(float _ior, float _transparency, float _diffuse_intensity)
  {
    m_material->setRefraction(_ior,_transparency, _diffuse_intensity);

  }
  void hasReflection(float _refl_intensity, float _diffuse_intensity)
  {
    m_material->setReflection(_refl_intensity, _diffuse_intensity);
  }
  Material* getMaterial() {return m_material;}
  char getType() {return m_type;}



protected:
  char m_type;
  ngl::Colour m_colour;
  Material* m_material;
};
}

#endif
