#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <ngl/Vec3.h>

/// @file Light.h
/// @author Ramon Blanquer
/// @brief A class for the lights in the scene

// LIGHT - Base Class
//----------------------------------------------------------------------------------------------------------------------
/// @class Light
/// @brief This is an abstract class that will be used as template when creating concretes types of light.
/// @author Ramon Blanquer
/// @todo Implement Kd, Ka and Ks on the sphere
//----------------------------------------------------------------------------------------------------------------------
class Light
{
public:
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Light constructor.
  /// @param[in] _pos                   Light's position.
  /// @param[in] _diffuse_contribution  DiffuseThe radius in scene units of the sphere object.
  /// @param[in] _colour The colour of the Sphere
  //------------------------------------------------------------------------------------------------------------------
  Light(ngl::Vec3 _pos, float _diffuse_contribution, float _specular_contribution);
  ~Light() {}
  ngl::Vec3 getPosition() {return m_pos;}
  float getSpecularContribution() {return m_specular_contribution;}
  float getDiffuseContribution() {return m_diffuse_contribution;}
protected:
  ngl::Vec3 m_pos;
  float m_intensity;
  float m_diffuse_contribution;
  float m_specular_contribution;
};

/* POINT LIGHT */
class PointLight : public Light
{
public:
  PointLight(ngl::Vec3 _pos, float _diffuse_contribution, float _specular_contribution);
  ~PointLight() {}
};

/* SPOTLIGHT */
class SpotLight : public Light
{
public:
  SpotLight(ngl::Vec3 _pos, float _diffuse_contribution, float _specular_contribution, float _angle, ngl::Vec3 _dir);
  ~SpotLight() {}
private:
  float m_angle;
  ngl::Vec3 m_dir;
};

#endif // Light.h
