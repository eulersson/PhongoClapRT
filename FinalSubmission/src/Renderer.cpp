#include <iostream>
#include <vector>
#include <cmath>
#include "Renderer.h"
#include "Ray.h"
#include "Material.h"
#include <ngl/Vec3.h>
#include <ngl/Types.h>

Renderer::Renderer(Scene &_scene, Film &_film, Camera &_camera, int _depth, int _anti_aliasing)
{
  m_scene = &_scene;
  m_film = &_film;
  m_camera = &_camera;
  m_width = m_film->m_width;
  m_height = m_film->m_height;
  m_anti_aliasing = _anti_aliasing;
  m_max_depth = _depth;
  m_bg_colour = ngl::Vec3(0,0,0);
}

Renderer::~Renderer()
{

}

int Renderer::getIndexClosest(std::vector<double> _interxs)
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
  ngl::Colour winning_object_colour = m_scene->m_objects.at(iowo)->getColour(_interx_pos);
  ngl::Vec3   winning_object_normal = m_scene->m_objects.at(iowo)->getNormalAt(_interx_pos);
  bool shadowed = false;

  for(unsigned int i = 0; i < m_scene->m_lights.size(); i++)
  {
    ngl::Vec3 light_direction = m_scene->m_lights.at(i)->getPosition() - _interx_pos;
    float light_distance = light_direction.length();
    light_direction.normalize();

    if(winning_object_normal.dot(light_direction) > 0)
    {
      geo::Ray shadow_ray(_interx_pos, light_direction);

      std::vector<double> shadow_isect;
      for (unsigned int j = 0; j < m_scene->m_objects.size(); j++)
      {
          shadow_isect.push_back(m_scene->m_objects.at(j)->getIntersection(shadow_ray));
      }

      for(unsigned int k = 0; k < shadow_isect.size(); k++)
      {
        if(shadow_isect.at(k) > 0.01 && shadow_isect.at(k) <= light_distance) shadowed = true;
      }
    }
  }

  _interx_dir.normalize();

  ngl::Colour final_col;

  if (shadowed == true)
  {
    final_col = winning_object_colour * -(winning_object_normal.dot(_interx_dir));
    final_col *= 0.5;
  }
  else
  {
    final_col = winning_object_colour * -(winning_object_normal.dot(_interx_dir));
  }
  return final_col;


}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * RAYCASTLGORITHM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool Renderer::raycast(ngl::Vec3 _from)
{
  for(unsigned int i = 0; i < m_scene->m_lights.size(); i++)
  {
    // create vector that will store intersection values for parameter t in the primary ray
    std::vector<double> intersections;

    ngl::Vec3 dir = m_scene->m_lights.at(i)->getPosition() - _from;
    dir.normalize();
    geo::Ray fire_ray(_from, dir);

    // iterate over objects in the scene and find intersections
    for(unsigned int i = 0; i < m_scene->m_objects.size(); i++)
    {
      intersections.push_back( m_scene->m_objects.at(i)->getIntersection(fire_ray));
    }

    // find closest object
    int closest_index = getIndexClosest(intersections);

    // if no intersections are found RETURN black =
    if(closest_index == -1) {return false;}
    else {return true;}
  }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * TRACE ALGORITHM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ngl::Colour Renderer::trace(ngl::Vec3 _from, ngl::Vec3 _direction, int depth)
{
  // create vector that will store intersection values for parameter t in the primary ray
  // a primary ray has a form like R = O + t * D where O is the origin vector, and D direction.
  std::vector<double> intersections;
  geo::Ray cam_ray(_from,_direction);

  // iterate over objects in the scene and find intersections
  for(unsigned int i = 0; i < m_scene->m_objects.size(); i++)
  {
    // each Shape subclass (Sphere, Plane...) has its own method for calculating intersections
    intersections.push_back( m_scene->m_objects.at(i)->getIntersection(cam_ray));
  }

  // find closest object
  int closest_index = getIndexClosest(intersections);

  // if no intersections are found RETURN black =
  if(closest_index == -1) {return ngl::Colour(0,0,0,1);}

  // calculate pHit (position of the new intersection) and nHit (normal at hit point)
  ngl::Vec3 pHit = _from + intersections.at(closest_index) * _direction;
  ngl::Vec3 nHit = m_scene->m_objects.at(closest_index)->getNormalAt(pHit);

  // calculate if we are inside or outside
  bool inside = false;
  if(_direction.dot(nHit) > 0)
  {
    nHit = -nHit;
    inside = true;
  }

 float bias = 0.01;
 // calculate if point is obscured or shadowed
 bool isObscured = raycast(pHit + nHit * bias);

                          // // // // // // // // //
                          //  calculate radiance  //
                          // // // // // // // // //


  // is the object reflective or refractive???
  if ((m_scene->m_objects.at(closest_index)->getMaterial().isReflective() ||
      m_scene->m_objects.at(closest_index)->getMaterial().isRefractive()) &&
      depth < m_max_depth)
  {
    ngl::Colour crfr, crfl;
    // check whether it is REFLECTIVE
    if (m_scene->m_objects.at(closest_index)->getMaterial().isReflective())
    {
      // calculate reflection dir
      float bias = 0.01;
      ngl::Vec3 refl_dir = _direction - nHit * 2 * _direction.dot(nHit);
      refl_dir.normalize();

      // fire ray along reflection direction from hit point
      crfl = trace(pHit + bias*nHit, refl_dir, depth+1);
    }

    // check whether it is REFRACTIVE
    if (m_scene->m_objects.at(closest_index)->getMaterial().isRefractive())
    {
      // calculate refrection dir (transmission ray)
      float ior = m_scene->m_objects.at(closest_index)->getMaterial().getIOR();
      float eta = inside;
      float bias = 0.01;
      float cosi = -nHit.dot(_direction);

      if (eta == true) // we are inside
      {
        eta = ior;
      }
      else // we are outside
      {
        eta = 1 / ior;
      }

      float k = 1 - eta * eta * (1 - cosi * cosi);
      ngl::Vec3 refr_dir = _direction * eta + nHit * (eta * cosi - sqrt(k));
      refr_dir.normalize();
      crfr = trace(pHit - nHit * bias, refr_dir, depth+1);
    }

    ngl::Colour s01 = crfl * m_scene->m_objects.at(closest_index)->getMaterial().getReflIntensity();
    ngl::Colour s02 = crfr * m_scene->m_objects.at(closest_index)->getMaterial().getTransparency();
    ngl::Colour s03 = s01 + s02;
    float cosineFactor = -nHit.dot(cam_ray.getDirection());
    ngl::Colour diffuseColor = m_scene->m_objects.at(closest_index)->getColour(pHit) * cosineFactor * m_scene->m_objects.at(closest_index)->getMaterial().getDiffuseIntensity();

    ngl::Colour surfaceColor = diffuseColor + s03;
    return isObscured ? surfaceColor * 0.8f : surfaceColor;

    // Do PHONG MODEL calculations stuff. By now I keep it VERY VERY simple



  }

  // if it is not REFLECTIVE nor REFRACTIVE
  else
  {
    ngl::Colour surfaceColor = m_scene->m_objects.at(closest_index)->getColour(pHit);
    float cosineFactor = -nHit.dot(cam_ray.getDirection());

    ngl::Colour Ka(0.5,0.5,0,1);
    ngl::Colour Kd = surfaceColor;// * cosineFactor;
    ngl::Colour Ks(1,1,1,1);

    ngl::Colour ambient_contrib = Ka * 0.2;
    ngl::Colour diffuse_contrib(0,0,0,1);
    ngl::Colour specular_contrib(0,0,0,1);

    for(int m = 0; m < m_scene->m_lights.size(); m++)
    {
      ngl::Vec3 L = m_scene->m_lights.at(m)->getPosition() - pHit;
      L.normalize();
      ngl::Vec3 N = nHit;
      ngl::Vec3 R = 2 * (L.dot(N) * N) - L;

      R.normalize();

      if(L.dot(N) > 0)
      {
        diffuse_contrib  += (Kd * L.dot(N) * m_scene->m_lights.at(m)->getDiffuseContribution());
      }
      if(R.dot(-_direction) > 0)
      specular_contrib += (Ks * pow(R.dot(-_direction),10) * m_scene->m_lights.at(m)->getSpecularContribution());
    }

    ngl::Colour outRadiance;
    outRadiance.m_r = 0*ambient_contrib.m_r + 1*diffuse_contrib.m_r + 1*specular_contrib.m_r;
    outRadiance.m_g = 0*ambient_contrib.m_g + 1*diffuse_contrib.m_g + 1*specular_contrib.m_g;
    outRadiance.m_b = 0*ambient_contrib.m_b + 1*diffuse_contrib.m_b + 1*specular_contrib.m_b;
    outRadiance *= cosineFactor;
    outRadiance.m_a = 1;

    outRadiance.clamp(0,1);

    return isObscured ? outRadiance * 0.3f : outRadiance;
  }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Renderer::render()
{
  std::vector<ngl::Colour> colourStack;
  for(int y = 0; y < m_film->m_height; y++)
  {
    for(int x = 0; x < m_film->m_width; x++)
    {
      ngl::Colour finalColour;
      if(m_anti_aliasing)
      {
        for(int aay = 0; aay < m_anti_aliasing; aay++)
        {
          for(int aax = 0; aax < m_anti_aliasing; aax++)
          {
            // calculate the primary ray
            float x_amount = ( (float)x + ((float)aax / (float)m_anti_aliasing) + 0.5f * ((float)aax / (float)m_anti_aliasing) ) / (float)m_film->m_width;
            float y_amount = ( (float)y + ((float)aay / (float)m_anti_aliasing) + 0.5f * ((float)aay / (float)m_anti_aliasing) ) / (float)m_film->m_width;

            ngl::Vec3 cam_ray_dir = m_camera->m_dir + (m_camera->m_right * (x_amount - 0.5) + (m_camera->m_down * (y_amount - 0.5)));
            cam_ray_dir.normalize();

            // fire the ray and store its colour into a variable
            ngl::Colour col = trace(m_camera->m_pos, cam_ray_dir, 0);

            colourStack.push_back(col);
          }
        }
        // AVERAGE COLOURS
        float cRed   = 0.0f;
        float cGreen = 0.0f;
        float cBlue  = 0.0f;

        for(int i = 0; i < m_anti_aliasing; i++)

        {
          cRed    += colourStack.at(i).m_r;
          cGreen  += colourStack.at(i).m_g;
          cBlue   += colourStack.at(i).m_b;
        }

        cRed   /= (float)m_anti_aliasing;
        cGreen /= (float)m_anti_aliasing;
        cBlue  /= (float)m_anti_aliasing;

        finalColour = ngl::Colour(cRed, cGreen, cBlue, 1);

        // FLUSH VECTOR
        colourStack.clear();
      }
      else // there is anti-aliasing
      {
        float x_amount = (x+0.5)/(float)m_film->m_width;
        float y_amount = ((y) + 0.5)/(float)m_film->getHeight();

        ngl::Vec3 cam_ray_dir = m_camera->m_dir + (m_camera->m_right * (x_amount - 0.5) + (m_camera->m_down * (y_amount - 0.5)));
        cam_ray_dir.normalize();

        // fire the ray and store its colour into a variable
        finalColour = trace(m_camera->m_pos, cam_ray_dir, 0);
      }

      // write pixel into the Film object associated to the Render object
      m_film->writePixel(finalColour);

      // write the file into disk afterwards and display it

    }
  }
  m_film->writeFile();
  system("display image.ppm");
}
