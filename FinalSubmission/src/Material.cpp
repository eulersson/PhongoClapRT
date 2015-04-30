/// @file Material.cpp
/// @brief Definitions for the Material class.

#include "Material.h"
#include <ngl/Colour.h>

Material::Material() {}

Material::Material(ngl::Colour _c)
{
  m_colour1 = _c;
  m_isChecker = false;
}

Material::Material(ngl::Colour _c1, ngl::Colour _c2 )
{
  m_colour1 = _c1;
  m_colour2 = _c2;
  m_isChecker = true;
}

bool Material::isReflective()
{
  return m_isReflective;
}

bool Material::isRefractive()
{
  return m_isRefractive;
}

void Material::setHardness(float _highlight_size)
{
  m_spec_hardness = _highlight_size;
}

void Material::setReflection(float _refl_intensity, float _diffuse_intensity)
{
  m_isReflective = true;
  m_refl_intensity = _refl_intensity;
  m_diffuse_intensity = _diffuse_intensity;
}

void Material::setRefraction(float _ior, float _transparency, float _diffuse_intensity)
{
  m_isRefractive = true;
  m_ior = _ior;
  m_transparency = _transparency;
  m_diffuse_intensity = _diffuse_intensity;
}

float Material::getReflIntensity()
{
  return m_refl_intensity;
}

float Material::getIOR()
{
  return m_ior;
}

float Material::getTransparency()
{
  return m_transparency;
}

float Material::getDiffuseIntensity()
{
  return m_diffuse_intensity;
}

ngl::Colour Material::objColour()
{
  return m_colour1;
}

ngl::Colour Material::objColour(ngl::Vec3 &_isect)
{
  /* This will floor the z and x position of a plane and for each integer value modulus operation will be performed
   * after that, depending on whether the remainder is 0 or 1 we apply one colour or another.*/

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
