#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <ngl/Vec3.h>


class Light
{
public:
  Light(ngl::Vec3 _pos, float _intensity)
  {
    m_pos = _pos;
    m_intensity = _intensity;
  }
  ~Light() {}
protected:
  ngl::Vec3 m_pos;
  float m_intensity;
};

class PointLight : public Light
{
public:
  PointLight(ngl::Vec3 _pos, float _intensity) : Light(_pos, _intensity) {}
};

class SpotLight : public Light
{
public:
  SpotLight(ngl::Vec3 _pos, float _intensity, float _angle, ngl::Vec3 _dir) : Light(_pos, _intensity)
  {
    m_angle = _angle;
    m_dir = _dir;

  }
private:
  float m_angle;
  ngl::Vec3 m_dir;
};

#endif // Light.h
