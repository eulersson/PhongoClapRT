#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Film.h"
#include "Camera.h"
#include "Scene.h"
#include <vector>
#include <ngl/Vec3.h>

class Renderer
{
  public:
    static inline void loadBar(int x, int n, int r, int w);
    Renderer(Scene &_scence, Film &_film, Camera &_camera, int _max_depth, int _anti_aliasing);
    ~Renderer();
    void render();
    int getIndexClosest(std::vector<double>);
    ngl::Colour getColourAt(ngl::Vec3 _interx_pos, ngl::Vec3 _interx_dir, int iowo);
    bool raycast(ngl::Vec3 _from, int _avoid);
    ngl::Colour trace(ngl::Vec3 _from, ngl::Vec3 _direction, int _depth);
  private:
    Film *m_film;
    Scene *m_scene;
    Camera *m_camera;
    ngl::Vec3 m_bg_colour;
    std::vector<ngl::Colour> m_colour_stack;
    int m_width;
    int m_height;
    int m_anti_aliasing;
    int m_max_depth;
};

#endif // Renderer.h
