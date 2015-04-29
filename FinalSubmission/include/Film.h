#ifndef _FILM_H_
#define _FILM_H_

/// @file Film.h
/// @author Ramon Blanquer
/// @brief All the operations regarding to file output and file input belong to this class. It abstracts the idea of a
/// film as the camera sensor chip which collects the incoming light and prints it into digital format.

#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include <fstream>
#include <vector>

//----------------------------------------------------------------------------------------------------------------------
/// @brief Pixel data structure that will be used by the Film class
// ---------------------------------------------------------------------------------------------------------------------
typedef struct Pixel
{
  float r;
  float g;
  float b;
}
Pixel;

//----------------------------------------------------------------------------------------------------------------------
/// @class Film
/// @brief Holds all the operations regarding to input/output of colour information
/// @author Ramon Blanquer
//----------------------------------------------------------------------------------------------------------------------
class Film
{
public:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Film constructor these will be set as default
  /// @param[in] _w Width of the Film/Image
  /// @param[in] _h Height of the Film/Image
  // -------------------------------------------------------------------------------------------------------------------
  Film(int _w, int _h);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Destructor for the Film.
  //--------------------------------------------------------------------------------------------------------------------
  ~Film();
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Will create a pixel and push it to the pixel vector
  //--------------------------------------------------------------------------------------------------------------------
  void writePixel(ngl::Colour _colour);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Iterates over the pixel vector and writes into a file using basic output stream methods
  //--------------------------------------------------------------------------------------------------------------------
  void writeFile();

  // give renderer permissions to access m_width and m_height with no need of getters
  friend class Renderer;

private:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Width of the Film's image
  //--------------------------------------------------------------------------------------------------------------------
  int m_width;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Height of the Film's image
  //--------------------------------------------------------------------------------------------------------------------
  int m_height;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Vector of pixels. The index of the pixel corresponds to this equation: i = height * y + x
  //-------------------------------------------------------------------------------------------------------------------
  std::vector<Pixel> m_pixels;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief File output stream, in charge of writing the pixels into a file
  //--------------------------------------------------------------------------------------------------------------------
  std::ofstream m_file;
};


#endif // Film.h
