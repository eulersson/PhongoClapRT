#include <cmath>
#include "Vec.h"


namespace geo
{
Vec::Vec(Point _A, Point _B)
{
  m_x = (_B.x - _A.x);
  m_y = (_B.y - _A.y);
  m_z = (_B.z - _A.z);
}
Vec::Vec(Ray _r, float _t)
{

}
}
