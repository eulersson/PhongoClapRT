

#include "Light.h"

/* BASE LIGHT */
Light::Light(ngl::Vec3 _pos, float _diffuse_contribution, float _specular_contribution)
{
  m_pos = _pos;
  m_specular_contribution = _specular_contribution;
  m_diffuse_contribution = _diffuse_contribution;
}

/* POINT LIGHT */
PointLight::PointLight(ngl::Vec3 _pos, float _diffuse_contribution, float _specular_contribution) : Light(_pos, _diffuse_contribution, _specular_contribution) {}


/* SPOTLIGHT */
SpotLight::SpotLight(ngl::Vec3 _pos, float _diffuse_contribution, float _specular_contribution, float _angle, ngl::Vec3 _dir) : Light(_pos, _diffuse_contribution, _specular_contribution)
{
  m_angle = _angle;
  m_dir = _dir;
}
