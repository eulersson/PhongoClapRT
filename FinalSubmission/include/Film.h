#ifndef _FILM_H_
#define _FILM_H_

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <fstream>
#include <vector>

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
  void writePixel(ngl::Colour _colour);
  void writeFile();
  int getWidth() {return m_width;}
  int getHeight() {return m_height;}

  // give renderer permissions to access m_width and m_height without need of getters
  friend class Renderer;

private:
  int m_width;
  int m_height;
  float m_aspectRatio;
  std::vector<Pixel> m_pixels;
  std::ofstream file;
};


#endif // Film.h
