#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Ray.h"
#include <ngl/Vec3.h>

namespace geo {
class Shape
{
public:

  // virtual functions
  virtual float getIntersection(geo::Ray& _ray) = 0;
  virtual float getRadius() const = 0;
  virtual ngl::Vec3 getNormalAt(ngl::Vec3 _p) = 0;
protected:
  char type;
};
}
#endif
