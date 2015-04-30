#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <ngl/Vec3.h>
#include <ngl/Colour.h>

/// @file Light.h
/// @author Ramon Blanquer
/// @brief A class for the lights in the scene. There is no sepparate `.cpp` file due to its simplicity.

// LIGHT - Base Class
//----------------------------------------------------------------------------------------------------------------------
/// @class Light
/// @brief This is a base class that will be used as template when creating concretes types of light.
/// @author Ramon Blanquer
/// @todo Implement `Kd`, `Ka` and `Ks` on the sphere
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
  /// @brief Destructor for the Light objects.
  //------------------------------------------------------------------------------------------------------------------
  ~Light() {}

  // Allow Renderer to access the protected interface
  friend class Renderer;

protected:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Light's position vector.
  //--------------------------------------------------------------------------------------------------------------------
  ngl::Vec3   m_pos;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief *Diffuse* colour emmited by the light.
  //--------------------------------------------------------------------------------------------------------------------
  ngl::Colour m_diff_col;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief *Specular* colour emmited by the light.
  //--------------------------------------------------------------------------------------------------------------------
  ngl::Colour m_spec_col;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief *Diffuse* contribution **intensity**. It will multiply the diffuse colour when doing the Phong calculations
  //--------------------------------------------------------------------------------------------------------------------
  float m_diff_int;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief *Specular* contribution **intensity**. Will multiply the specular colour when doing the Phong calculations
  //--------------------------------------------------------------------------------------------------------------------
  float m_spec_int;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Controlls the *falloff* of the light. Higher values will accentuate the decay.
  //--------------------------------------------------------------------------------------------------------------------
  float m_falloff;
};

/* POINT LIGHT */
//------------------------------------------------------------------------------------------------------------------
/// @brief Point light constructor.
/// @param[in] _pos      Light's position.
/// @param[in] _diff_col Diffuse colour emitted by the light.
/// @param[in] _spec_col Specular colour emmited by the light.
/// @param[in] _diff_int Sets the intensity of the diffuse colour emission.
/// @param[in] _spec_int Sets the intensity of the specular emission.
/// @param[in] _falloff  Controlls how the light decays.
//------------------------------------------------------------------------------------------------------------------
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

/* POINT LIGHT */
//------------------------------------------------------------------------------------------------------------------
/// @brief Spotlight constructor.
/// @param[in] _pos      Light's position.
/// @param[in] _diff_col Diffuse colour emitted by the light.
/// @param[in] _spec_col Specular colour emmited by the light.
/// @param[in] _diff_int Sets the intensity of the diffuse colour emission.
/// @param[in] _spec_int Sets the intensity of the specular emission.
/// @param[in] _falloff  Controlls how the light decays.
/// @param[in] _angle    The cone angle in which light is emitted.
/// @param[in] _dir      Direction or aiming vector of the spotlight.
//------------------------------------------------------------------------------------------------------------------
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
                ngl::Vec3 _dir) : Light(_pos, _diff_col,
                                        _spec_col,
                                        _diff_int,
                                        _spec_int,
                                        _falloff),
                                  m_angle(_angle), m_dir(_dir) {}
~SpotLight() {}
private:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief The cone angle in which light is emitted.
  //--------------------------------------------------------------------------------------------------------------------
  float m_angle;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Direction or aiming vector of the spotlight.
  //--------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_dir;
};

#endif // Light.h
