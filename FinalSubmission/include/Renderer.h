#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Film.h>

class Renderer
{
  public:
    Renderer(Film &film);
    ~Renderer();
  private:
    Film *m_film;
    int m_width;
    int m_height;
};

#endif // Renderer.h
