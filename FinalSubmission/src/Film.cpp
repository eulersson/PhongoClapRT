//----------------------------------------------------------------------------------------------------------------------
/// @file Film.cpp
/// @brief Implementation files for Film class
//----------------------------------------------------------------------------------------------------------------------

#include "Film.h"
#include <ngl/Colour.h>

Film::Film(int _w, int _h)
{
  m_width = _w;
  m_height = _h;
}

Film::~Film()
{
  // Deallocate all the pixel memory
}

void Film::writePixel(ngl::Colour _colour)
{
  Pixel curr;
  curr.r = _colour.m_r;
  curr.g = _colour.m_g;
  curr.b = _colour.m_b;
  m_pixels.push_back(curr);
}

void Film::writeFile()
{
  m_file.open("image.ppm", std::ios::out | std::ios::binary);
  m_file << "P6\n" << m_width << " " << m_height << "\n255\n";

  for(unsigned int i = 0; i < m_pixels.size(); ++i)
  {
    m_file << (unsigned char) (m_pixels.at(i).r * 255)  <<
            (unsigned char) (m_pixels.at(i).g * 255) <<
            (unsigned char) (m_pixels.at(i).b * 255);
  }

  m_file.close();

}
