#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

/// @file Light.h
/// @author Ramon Blanquer
/// @brief A class for the lights in the scene

// LIGHT - Base Class
//----------------------------------------------------------------------------------------------------------------------
/// @class Light
/// @brief This is a base class that will be used as template when creating concretes types of light.
/// @author Ramon Blanquer
/// @todo Implement Kd, Ka and Ks on the sphere
//----------------------------------------------------------------------------------------------------------------------
class Light
{
public:
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Light constructor.
  /// @param[in] _pos      Light's position.
  /// @param[in] _diff_col Diffuse colour emitted by the light.
  /// @param[in] _spec_col Specular colour emmited by the light.
  /// @param[in] _diff_int Sets the intensity of the diffuse colour emission.
  /// @param[in] _spec_int Sets the intensity of the specular emission.
  /// @param[in] _falloff  Controlls how the light decays.
  //------------------------------------------------------------------------------------------------------------------
  Light(ngl::Vec3 _pos,
        ngl::Colour _diff_col,
        ngl::Colour _spec_col,
              float _diff_int,
              float _spec_int,
              float _falloff) : m_pos(_pos), m_diff_col(_diff_col), m_spec_col(_spec_col),
                                m_diff_int(_diff_int), m_spec_int(_spec_int), m_falloff(_falloff) {}
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Destructor for the Light class.
  //------------------------------------------------------------------------------------------------------------------
  ~Light() {}

  // Allow Renderer to access the protected interface
  friend class Renderer;

protected:
  ngl::Vec3   m_pos;
  ngl::Colour m_diff_col;
  ngl::Colour m_spec_col;
        float m_diff_int;
        float m_spec_int;
        float m_falloff;
};

/* POINT LIGHT */
class PointLight : public Light
{
public:
  PointLight(ngl::Vec3 _pos,
             ngl::Colour _diff_col,
             ngl::Colour _spec_col,
                   float _diff_int,
                   float _spec_int,
                   float _falloff) : Light(_pos, _diff_col, _spec_col, _diff_int, _spec_int, _falloff) {}
  ~PointLight() {}
};

/* SPOTLIGHT */
class SpotLight : public Light
{
public:
SpotLight(ngl::Vec3 _pos,
          ngl::Colour _diff_col,
          ngl::Colour _spec_col,
                float _diff_int,
                float _spec_int,
                float _falloff,
                float _angle,
                ngl::Vec3 _dir) : Light(_pos, _diff_col, _spec_col, _diff_int, _spec_int, _falloff)
         {
           m_angle = _angle;
           m_dir = _dir;
         }
~SpotLight() {}
private:
  float m_angle;
  ngl::Vec3 m_dir;
};

#endif // Light.h
