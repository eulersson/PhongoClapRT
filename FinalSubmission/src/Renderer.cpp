#include <iostream>
#include <vector>
#include "Renderer.h"
#include "Ray.h"
#include <ngl/Vec3.h>

Renderer::Renderer(Scene &_scene, Film &_film, Camera &_camera)
{
  m_scene = &_scene;
  m_film = &_film;
  m_camera = &_camera;
  m_width = m_film->m_width;
  m_height = m_film->m_height;
  m_bg_colour = ngl::Vec3(0,0,0);
}

Renderer::~Renderer()
{

}

int Renderer::winningObjectIndex(std::vector<double> _interxs)
{
  int index_min_val;
  if(_interxs.size() == 0) {return -1;}
  else if(_interxs.size() == 1)
  {
    if(_interxs.at(0) > 0) {return 0;}
    else {return -1;}
  }
  else
  {
    double max = 0;
    for (unsigned int i = 0; i < _interxs.size(); i++)
    {
      if(max < _interxs.at(i)) {max = _interxs.at(i);}
    }
    if (max > 0)
    {
      for (unsigned int i = 0; i < _interxs.size(); i++)
      {
        if(_interxs.at(i) > 0 && _interxs.at(i) <= max)
        {
          max = _interxs.at(i);
          index_min_val = i;
        }
      }
      return index_min_val;
    }
    else {return -1;}
  }

}

/*ngl::Colour Renderer::getColourAt(ngl::Vec3 _interx_pos, ngl::Vec3 _interx_dir, int iowo)
{
  // define colour of winning object

  // define normal of winning object


}*/

void Renderer::render()
{
  for(int y = 0; y < m_film->m_height; y++)
  {
    for(int x = 0; x < m_film->m_width; x++)
    {
      std::vector<double> intersections;

      float x_amount = (x+0.5)/(float)m_film->m_width;
      float y_amount = ((m_film->m_height - y) + 0.5)/(float)m_film->getHeight();

      ngl::Vec3 cam_ray_dir = m_camera->m_dir + (m_camera->m_right * (x_amount - 0.5) + (m_camera->m_up * (y_amount - 0.5)));
      cam_ray_dir.normalize();

      geo::Ray cam_ray(m_camera->m_pos, cam_ray_dir);

      for(unsigned int i = 0; i < m_scene->m_objects.size(); i++)
      {
        intersections.push_back( m_scene->m_objects.at(i)->getIntersection(cam_ray));
      }

      int index_of_winning_object = winningObjectIndex(intersections);

      if(index_of_winning_object == -1)
      {
        // write black pixel
        m_film->writePixel(ngl::Colour(0,0,0,1));
      }
      else
      {
        // get colour of intersection
        /*ngl::Vec3 _interx_pos = cam_ray.getOrigin() + cam_ray.getDirection() * intersections.at(index_of_winning_object);
        ngl::Vec3 _interx_dir_ = cam_ray.getDirection();
        ngl::Colour intersection_colour = getColourAt(_interx_pos, _interx_dir_, index_of_winning_object);*/



        // write it into the pixel in the film
        m_film->writePixel(ngl::Colour(1,0,0,1));
      }
    }
  }

  // output image
  m_film->writeFile();
}
