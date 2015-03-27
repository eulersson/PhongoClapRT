#include "Film.h"

Film::Film(int _w, int _h)
{
  m_width = _w;
  m_height = _h;
  m_aspectRatio = (float)m_width/(float)m_height;
  file.open("your_image.ppm", std::ios::out | std::ios::binary);
  file << "P6\n" << m_width << " " << m_height << "\n255\n";

  for(unsigned i = 0; i < m_width * m_height; ++i)
  {
    file << (unsigned char)50 <<
            (unsigned char)0 <<
            (unsigned char)0;
  }

  file.close();
}

Film::~Film()
{
  // Deallocate all the pixel memory
}

void Film::writePixel(ngl::Vec3 _colour)
{
  file << (unsigned char)_colour[0] <<
          (unsigned char)_colour[1] <<
          (unsigned char)_colour[2];
}
