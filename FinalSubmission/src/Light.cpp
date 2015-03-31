

#include "Light.h"

/* BASE LIGHT */
Light::Light(ngl::Vec3 _pos, float _intensity)
{
  m_pos = _pos;
  m_intensity = _intensity;
}

/* POINT LIGHT */
PointLight::PointLight(ngl::Vec3 _pos, float _intensity) : Light(_pos, _intensity) {}


/* SPOTLIGHT */
SpotLight::SpotLight(ngl::Vec3 _pos, float _intensity, float _angle, ngl::Vec3 _dir) : Light(_pos, _intensity)
{
  m_angle = _angle;
  m_dir = _dir;
}
