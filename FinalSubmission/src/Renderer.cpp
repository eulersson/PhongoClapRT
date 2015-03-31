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

ngl::Colour Renderer::getColourAt(ngl::Vec3 _interx_pos, ngl::Vec3 _interx_dir, int iowo)
{
  ngl::Colour winning_object_colour = m_scene->m_objects.at(iowo)->getColour();
  ngl::Vec3   winning_object_normal = m_scene->m_objects.at(iowo)->getNormalAt(_interx_pos);
  bool shadowed = false;

  for(unsigned int i = 0; i < m_scene->m_lights.size(); i++)
  {
    ngl::Vec3 light_direction = m_scene->m_lights.at(i)->getPosition() - _interx_pos;
    float light_distance = light_direction.length();
    light_direction.normalize();

    geo::Ray shadow_ray(_interx_pos, light_direction);

    std::vector<double> shadow_isect;
    for (unsigned int j = 0; j < m_scene->m_objects.size(); j++)
    {
      if((int)j != iowo)
      {
        shadow_isect.push_back(m_scene->m_objects.at(j)->getIntersection(shadow_ray));
      }
    }

    for(unsigned int k = 0; k < shadow_isect.size(); k++)
    {
      if(shadow_isect.at(k) > 0.01)
      {
        if(shadow_isect.at(k) <= light_distance)
        {
          shadowed = true;
        }
      }
    }
  }

  _interx_dir.normalize();

  ngl::Colour final_col;

  if (shadowed == true)
  {
    final_col = ngl::Colour(0,0,0,1);
  }
  else
  {
    final_col = winning_object_colour * winning_object_normal.dot(_interx_dir);
  }
  return final_col;


}

void Renderer::render()
{
  for(int y = 0; y < m_film->m_height; y++)
  {
    for(int x = 0; x < m_film->m_width; x++)
    {
      std::vector<double> intersections;


      float x_amount = (x+0.5)/(float)m_film->m_width;
      float y_amount = ((y) + 0.5)/(float)m_film->getHeight();

      ngl::Vec3 cam_ray_dir = m_camera->m_dir + (m_camera->m_right * (x_amount - 0.5) + (m_camera->m_down * (y_amount - 0.5)));
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
        ngl::Vec3 _interx_pos = cam_ray.getOrigin() + cam_ray.getDirection() * intersections.at(index_of_winning_object);
        ngl::Vec3 _interx_dir_ = cam_ray.getDirection();
        ngl::Colour intersection_colour = getColourAt(_interx_pos, _interx_dir_, index_of_winning_object);



        // write it into the pixel in the film
        m_film->writePixel(intersection_colour);
      }
    }
  }

  // output image
  m_film->writeFile();

  system("display your_image.ppm");
}
