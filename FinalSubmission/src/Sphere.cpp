#include <cmath>
#include <ngl/Vec3.h>
#include <ngl/Colour.h>
#include "Shape.h"
#include "Sphere.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file Sphere.cpp
/// @brief implementation files for Sphere class
//----------------------------------------------------------------------------------------------------------------------
namespace geo
{
  float Sphere::getIntersection(Ray& ray)
  {
    float ray_origin_x = ray.getOrigin().m_x;
    float ray_origin_y = ray.getOrigin().m_y;
    float ray_origin_z = ray.getOrigin().m_z;

    float ray_direction_x = ray.getDirection().m_x;
    float ray_direction_y = ray.getDirection().m_y;
    float ray_direction_z = ray.getDirection().m_z;

    float sphere_center_x = this->getCenter().m_x;
    float sphere_center_y = this->getCenter().m_y;
    float sphere_center_z = this->getCenter().m_z;

    //float a = 1;
    float b = (2*(ray_origin_x - sphere_center_x)*ray_direction_x)
            + (2*(ray_origin_y - sphere_center_y)*ray_direction_y)
            + (2*(ray_origin_z - sphere_center_z)*ray_direction_z);
    float c = pow(ray_origin_x - sphere_center_x, 2)
            + pow(ray_origin_y - sphere_center_y, 2)
            + pow(ray_origin_z - sphere_center_z, 2)
            - (this->getRadius()*this->getRadius());
    float discriminant = b*b - 4*c;

    if(discriminant > 0)
    {
      //ray intersects sphere

      // first root
      float root_1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;

      if (root_1 > 0)
      {
        return root_1;
      }

      else
      {
        // second root is the smallest positive root
        float root_2 = ((sqrt(discriminant)-b)/2) - 0.000001;
        return root_2;
      }
    }
    else
    {
      return -1;
    }






    /*
    // from Wikipedia: http://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

    ngl::Vec3 diff;
    diff = ray.getOrigin() - this->getCenter();

    //float a = 1;
    float b = 2 * diff.dot(ray.getDirection());
    float c =   pow(ray.getOrigin().m_x - this->getCenter().m_x,2)
              + pow(ray.getOrigin().m_y - this->getCenter().m_y,2)
              + pow(ray.getOrigin().m_z - this->getCenter().m_z,2)
              - (this->getRadius()*this->getRadius());
    //float c = diff.dot(diff) - pow(this->getRadius(),2);

    float discriminant = b * b - 4 * c;

    if (discriminant < 0) {return -1;}
    else if (discriminant == 0) {return - 0.5 * b;}
    else {return - 0.5 * (b - sqrt(discriminant));}*/

  }

  ngl::Vec3 Sphere::getNormalAt(ngl::Vec3 _p)
  {
    ngl::Vec3 normal;
    normal = _p - m_center;
    normal.normalize();
    return normal;
  }
}


