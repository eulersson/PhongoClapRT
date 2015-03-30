#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Film.h"
#include "Camera.h"
#include "Scene.h"
#include <ngl/Vec3.h>

class Renderer
{
  public:
    Renderer(Scene &_scence, Film &_film, Camera &_camera);
    ~Renderer();
    void render();
    int winningObjectIndex(std::vector<double>);
    /*ngl::Colour getColourAt(ngl::Vec3 _interx_pos, ngl::Vec3 _interx_dir, int iowo);*/
  private:
    Film *m_film;
    Scene *m_scene;
    Camera *m_camera;
    ngl::Vec3 m_bg_colour;
    int m_width;
    int m_height;
};

#endif // Renderer.h
