#ifndef _RAY_H_
#define _RAY_H_

/// @file Ray.h
/// @author Ramon Blanquer
/// @brief This class handles the implementation of ray: an object with an origin and a direction.

#include <ngl/Vec3.h>
//----------------------------------------------------------------------------------------------------------------------
/// @class Ray
/// @brief Class that holds the definition of a ray. A ray consists of those points on a line starting at an origin O
/// proceeding indefinitely towards an explicit direction. Always going in one direction only along the line.
/// @author Ramon Blanquer
//----------------------------------------------------------------------------------------------------------------------
namespace geo
{
class Ray
{
public:
  //------------------------------------------------------------------------------------------------------------------
  /// @brief First ray ctor, this takes an origin and a direction and passes them directly to the class members.
  /// @param[in] _origin Starting point of the ray
  /// @param[in] _direction Vector in which the points lay on the line.
  //------------------------------------------------------------------------------------------------------------------
  Ray(ngl::Vec3 _origin, ngl::Vec3 _direction);
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Second ray ctor, this takes two points and creates the direction from them and takes the first as origin.
  /// @param[in] _A Starting point of the ray
  /// @param[in] _B Another point which will be used to construct a vector which will act as direction for the ray.
  /// @param[in] _p This parameter discrimines between the previous ctor because they both accept two vectors as
  ///               inputs and this cannot be overloaded.
  //------------------------------------------------------------------------------------------------------------------
  Ray(ngl::Vec3 _A, ngl::Vec3 _B, bool _p);
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Simple destructor. Frees memory.
  //------------------------------------------------------------------------------------------------------------------
  ~Ray();

  // setters
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Setter method for the origin.
  /// @param[in] _origin Sets the origin class member.
  //------------------------------------------------------------------------------------------------------------------
  void setOrigin(ngl::Vec3 _origin);
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Setter method for the direction.
  /// @param[in] _direction Sets the direction class member.
  //------------------------------------------------------------------------------------------------------------------
  void setDirection(ngl::Vec3 _direction);

  // getters
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Getter method for the origin.
  /// @returns The origin of the ray.
  //------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 getOrigin();
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Getter method for the direction.
  /// @returns The direction of the ray.
  //------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 getDirection();

private:
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Ray's origin class member
  //------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_origin;
  //------------------------------------------------------------------------------------------------------------------
  /// @brief Ray's direction class member
  //------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_direction;

};
}







#endif
