#ifndef _FILM_H_
#define _FILM_H_

#include <ngl/Vec3.h>
#include <fstream>

typedef struct Pixel
{
  float r;
  float g;
  float b;
}
Pixel;

class Film
{
public:
  Film(int _w, int _h);
  ~Film();
  void writePixel(ngl::Vec3 _colour);
  int getWidth() {return m_width;}

  // give renderer permissions to access m_width and m_height without need of getters
  friend class Renderer;

private:
  int m_width;
  int m_height;
  float m_aspectRatio;
  Pixel* m_pixels;
  std::ofstream file;
};


#endif // Film.h
