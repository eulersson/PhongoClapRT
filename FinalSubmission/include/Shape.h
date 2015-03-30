#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Ray.h"
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

namespace geo {
class Shape
{
public:
  ngl::Colour getColour() {return m_colour;}

  // virtual functions
  virtual float getIntersection(geo::Ray& _ray) = 0;
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p) = 0;
protected:
  char m_type;
  ngl::Colour m_colour;
};
}
#endif
