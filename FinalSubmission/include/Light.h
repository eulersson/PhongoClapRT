#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <ngl/Vec3.h>

/* BASE LIGHT */
class Light
{
public:
  Light(ngl::Vec3 _pos, float _intensity);
  ~Light() {}
  ngl::Vec3 getPosition() {return m_pos;}
protected:
  ngl::Vec3 m_pos;
  float m_intensity;
};

/* POINT LIGHT */
class PointLight : public Light
{
public:
  PointLight(ngl::Vec3 _pos, float _intensity);
  ~PointLight() {}
};

/* SPOTLIGHT */
class SpotLight : public Light
{
public:
  SpotLight(ngl::Vec3 _pos, float _intensity, float _angle, ngl::Vec3 _dir);
  ~SpotLight() {}
private:
  float m_angle;
  ngl::Vec3 m_dir;
};

#endif // Light.h
