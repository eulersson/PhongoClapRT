#ifndef _RENDERER_H_
#define _RENDERER_H_

/// @file Renderer.h
/// @author Ramon Blanquer
/// @brief This class is the heart of my raytracer. It is the core, where all the camera rays are calculated and sent
/// to the raytrace algorithm which takes them as primary and handles the recursion. It is also responsible for shading
/// taking into account all the reflection colours refraction colours and diffuse that have been stacked. I used and
/// adapted the Phong model and did some tweaks to it to make things look nicer.

#include "Film.h"
#include "Camera.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <ngl/Vec3.h>

//----------------------------------------------------------------------------------------------------------------------
/// @class Renderer
/// @brief Core of my program, central unit that manages all the other classes almost.
/// @author Ramon Blanquer
//----------------------------------------------------------------------------------------------------------------------
class Renderer
{
public:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor for the renderer class
  /// @param[in] _scene         Scene which will contain all the lights, objects, etc...
  /// @param[in] _film          Film structure to query the width, height and other attributes from.
  /// @param[in] _camera        Camera used to fire the primary and secondary rays.
  /// @param[in] _max_depth     Maximum depth of recursion.
  /// @param[in] _anti_aliasing Amount of antialiasing.
  /// @param[in] _image_name    The image filename.
  //--------------------------------------------------------------------------------------------------------------------
  Renderer(Scene &_scence, Film &_film, Camera &_camera, int _max_depth, int _anti_aliasing, std::string _image_name);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Destructor, frees any possible memory from the heap
  //--------------------------------------------------------------------------------------------------------------------
  ~Renderer();
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Implements a loading bar. This algorithm is taken from another person
  /// @param[in] x Current value (in my case the current pixel expressed as y*height + x)
  /// @param[in] n Total number of elements (in my case width/height)
  /// @param[in] r Number of times for the bar to be refreshed
  /// @param[in] w Width in characters of the loading bar
  //--------------------------------------------------------------------------------------------------------------------
  static inline void loadBar(int x, int n, int r, int w);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Will trigger the class and start doing all the calculations
  //--------------------------------------------------------------------------------------------------------------------
  void render();
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Given an intersections vector will return the closest to the camera, the one that it will read colour from
  /// @param[in] _intersections Vector with all the 't' parameters from the ray equation R = O + t * d, aka intersection
  /// @returns Object index that has the smallest intersection value
  //--------------------------------------------------------------------------------------------------------------------
  int getIndexClosest(std::vector<double> _intersections);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Will fire rays from a position, then iterate over the lights, and if any object is inbetweet will return
  /// true as value, that means that this particular point has to be shadowed.
  /// @param[in] _from (in world space) where to fire the ray from
  /// @param[in] _avoid Will make sure that there is no self-shadowing, the shadowing effect is thus sold by the shading
  /// model. This is the index of the object which has to be ignored when finding the shadowing objects.
  /// @returns Whether the point is obscured or not by another object.
  /// @todo Work harder on this, shadows should layer up, not just be absolute true or false.
  //--------------------------------------------------------------------------------------------------------------------
  bool raycast(ngl::Vec3 _from, int _avoid);
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Probably the most important algorithm of this class. This method is recursive. It will fire a ray from the
  /// given position in the first parameter aiming towards the direction specified in the second one. If it hits a
  /// reflective or refractive material the new reflection/transimission ray will be calculated and this method will be
  /// called again. The limiter will be the depth argument.
  /// @param[in] _from      Position where to fire the ray from
  /// @param[in] _direction Aim vector that defines the directions in which we want to fire the ray
  /// @param[in] _avoid     Index of the object we want to avoid. By index I mean the position in the m_scene_objects vector
  /// @returns The radiance colour of the ray fired
  //--------------------------------------------------------------------------------------------------------------------
  ngl::Colour trace(ngl::Vec3 _from, ngl::Vec3 _direction, int _depth);

private:
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Name of the filename that will be written.
  //--------------------------------------------------------------------------------------------------------------------
  std::string m_image_name;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Associated film.
  //--------------------------------------------------------------------------------------------------------------------
  Film *m_film;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Associated scene.
  //--------------------------------------------------------------------------------------------------------------------
  Scene *m_scene;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Associated camera.
  //--------------------------------------------------------------------------------------------------------------------
  Camera *m_camera;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief default background colour.
  //--------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_bg_colour;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Width of the image.
  //--------------------------------------------------------------------------------------------------------------------
  int m_width;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Height of the image.
  //--------------------------------------------------------------------------------------------------------------------
  int m_height;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Antialiasing amount.
  //--------------------------------------------------------------------------------------------------------------------
  int m_anti_aliasing;
  //--------------------------------------------------------------------------------------------------------------------
  /// @brief Maximum number of ray stack frames.
  //--------------------------------------------------------------------------------------------------------------------
  int m_max_depth;
};

#endif // Renderer.h
