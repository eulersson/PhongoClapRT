#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <ngl/Colour.h>
#include <cmath>
#include "Ray.h"
#include "Shape.h"

class Material
{
public:
  Material() {}

  Material(ngl::Colour _c) : m_colour1(_c), m_isChecker(false) {}

  Material(ngl::Colour _c1, ngl::Colour _c2 ) : m_colour1(_c1), m_colour2(_c2)
  {
    m_isChecker = true;
  }

  ngl::Colour objColour() {return m_colour1;}

  ngl::Colour objColour(ngl::Vec3 &_isect)
  {
    if(m_isChecker)
    {
      int index_x = (int)(floor(_isect.m_x)) % 2;
      int index_z = (int)(floor(_isect.m_z)) % 2;
      if (((bool)index_x && (bool)index_z) || ((bool)index_x == 0 && (bool)index_z == 0))
      {
        return m_colour1;
      }
      else
      {
        return m_colour2;
      }
    }
    else
    {
      return m_colour1;
    }
  }
  ngl::Colour m_colour1;
  ngl::Colour m_colour2;
  bool m_isChecker;

};


#endif // Material.h
