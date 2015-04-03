#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <ngl/Colour.h>
#include <cmath>
#include "Ray.h"

class Material
{
public:
  Material(ngl::Colour _c) : m_colour1(_c), m_isChecker(false) {}
  Material(ngl::Colour _c1, ngl::Colour _c2 ) : m_colour1(_c1), m_colour2(_c2), m_isChecker(true) {}
  ngl::Colour objColour(ngl::Vec3 &_isect)
  {
    if(m_isChecker)
    {
      int index = (int)(floor(_isect.m_z)) % 2;
      if ((bool)index == 0)
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

friend class Renderer;

private:
ngl::Colour m_colour1;
ngl::Colour m_colour2; // for checker boards
bool m_isChecker;

};


#endif // Material.h
