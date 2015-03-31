#include "Camera.h"

Camera::Camera(ngl::Vec3 _pos, ngl::Vec3 _dir, ngl::Vec3 _right, ngl::Vec3 _down)
{
  m_pos = _pos;
  m_dir = _dir;
  m_right = _right;
  m_down = _down;
}
