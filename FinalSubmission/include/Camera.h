#ifndef NGLSCENE_H__
#define NGLSCENE_H__

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>

class Camera
{
public:
  Camera() : m_pos(ngl::Vec3(0,0,0)), m_dir(ngl::Vec3(0,0,1)), m_up(ngl::Vec3(0,1,0)), m_right(ngl::Vec3(1,0,0)) {}
  Camera(ngl::Vec3 _pos, ngl::Vec3 _dir, ngl::Vec3 _right, ngl::Vec3 _up);
  ~Camera() {}
  void transform(ngl::Mat4 _trasform);
  ngl::Vec3 getPosition() {return m_pos;}
  ngl::Vec3 getDirection() {return m_dir;}

  // allow access to camera from Renderer
  friend class Renderer;

private:
  ngl::Vec3 m_pos;
  ngl::Vec3 m_dir;
  ngl::Vec3 m_up;
  ngl::Vec3 m_right;

};

#endif // Camera.h
