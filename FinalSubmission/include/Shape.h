#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Ray.h"
#include "Material.h"
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

namespace geo {
class Shape
{
public:
  virtual ngl::Colour getColour() = 0;
  virtual ngl::Colour getColour(ngl::Vec3 &_isect) = 0;

  // virtual functions
  virtual float getIntersection(geo::Ray& _ray) = 0;
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p) = 0;
  Material getMaterial() {return m_material;}
protected:
  char m_type;
  ngl::Colour m_colour;
  Material m_material;
};
}
#endif
