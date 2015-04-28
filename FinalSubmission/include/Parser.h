#ifndef _PARSER_H_
#define _PARSER_H_

#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <ngl/Vec3.h>
#include <ngl/Colour.h>

#include "Light.h"
#include "Shape.h"
#include "Plane.h"
#include "Sphere.h"


class Parser
{

public:

  Parser(    std::string &_image_name,
             std::string &_text_file,
             int &_width,
             int &_height,
             float &_camPosX,
             float &_camPosY,
             float &_camPosZ,
             float &_lookAtX,
             float &_lookAtY,
             float &_lookAtZ,
             int &_max_depth,
             int &_anti_aliasing,
             std::vector<Light*> &_scene_lights,
             std::vector<geo::Shape*> &_scene_objects)
  {

      typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
      boost::char_separator<char> quote{"\""};

      std::string text;
      std::ifstream sceneFile(_text_file);

      sceneFile.seekg(0, std::ios::end);
      text.reserve(sceneFile.tellg());
      sceneFile.seekg(0, std::ios::beg);

      text.assign((std::istreambuf_iterator<char>(sceneFile)),
                  std::istreambuf_iterator<char>());

      tokenizer tok{text,quote};
      tokenizer::iterator it = tok.begin();
      std::string tmp;

      std::cout << "Parsing filename...\n";
      ++it;
      _image_name = *it;
      std::cout << "OK! Filename: " << _image_name << std::endl;
      ++it; ++it;
      std::cout << "Parsing file dimensions...\n";
      tmp = *it;
      _width = atoi(tmp.c_str()); // WIDTH
      ++it; ++it;
      tmp = *it;
      _height = atoi(tmp.c_str()); // HEIGHT
      std::cout << "OK! " << _width << "x" << _height << " image specified.\n";
      ++it; ++it;
      std::cout << "Parsing camera...\n";
      tmp = *it;
      _camPosX = atof(tmp.c_str()); // camPosX
      ++it; ++it;
      tmp = *it;
      _camPosY = atof(tmp.c_str()); // camPosY
      ++it; ++it;
      tmp = *it;
      _camPosZ = atof(tmp.c_str()); // camPosZ
      ++it; ++it;
      tmp = *it;
      _lookAtX = atof(tmp.c_str()); // lookAtX
      ++it; ++it;
      tmp = *it;
      _lookAtY = atof(tmp.c_str()); // lookAtY
      ++it; ++it;
      tmp = *it;
      _lookAtZ = atof(tmp.c_str()); // lookAtZ
      std::cout << "OK! Camera parsed with pos["<<_camPosX <<","<<_camPosY<<","<<_camPosZ<<"] and lookup["<<_lookAtX<<","<<_lookAtY<<","<<_lookAtZ<<"]\n";
      ++it; ++it;
      tmp = *it;
      _max_depth = atoi(tmp.c_str()); // max_depth
      ++it; ++it;  tmp = *it;
      _anti_aliasing = atoi(tmp.c_str()); // anti_aliasing
      ++it; ++it;

      std::cout << "Parsing lights...\n";
      parseLights(text, _scene_lights);

      std::cout << "Parsing objects...\n";
      parseObjects(text, _scene_objects);


  }
  ~Parser() {}

  void parseObjects(std::string& _text, std::vector<geo::Shape*> &_scene_objects)
  {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> dollar{"$"};
    tokenizer tok{_text,dollar};
    tokenizer::iterator it = tok.begin();
    it++;

    std::string tmp;
    tmp = *it;





    while(it != tok.end())
    {
      tmp = *it;
      if (tmp.at(0) == '}') break;
      if (tmp.at(0) == 'P')
      {
        // parse plane
        parsePlane(tmp,_scene_objects);
      }
      else if (tmp.at(0) == 'S')
      {
        // parse sphere
        parseSphere(tmp,_scene_objects);
      }
      ++it;
    }








  }

  void parseLights(std::string& _text, std::vector<Light*> &_scene_lights)
  {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> plus{"+"};
    tokenizer tok{_text,plus};
    tokenizer::iterator it = tok.begin();
    ++it;

    std::string tmp;

    while(it != tok.end())
    {
      tmp = *it;
      if (tmp.at(0) == '}') break;
      parseSingleLight(tmp, _scene_lights);
      ++it;
    }
  }

  void parseSingleLight(std::string &_text_light, std::vector<Light*> &_scene_lights)
  {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> space{" "};
    tokenizer tok{_text_light,space};
    tokenizer::iterator it = tok.begin();
    std::string tmp;
    std::string light_name;

    ngl::Vec3 position;
    ngl::Colour diffuse_col;
    ngl::Colour specular_col;
    float diff_int;
    float spec_int;
    float falloff;
    light_name = *it;
    it++;it++;
    tmp = *it;
    position.m_x = atof(tmp.c_str());
    it++;
    tmp = *it;
    position.m_y = atof(tmp.c_str());
    it++;
    tmp = *it;
    position.m_z = atof(tmp.c_str());
    it++;it++;it++;
    tmp = *it;

    diffuse_col.m_r = atof(tmp.c_str()); it++;
    tmp = *it; diffuse_col.m_g = atof(tmp.c_str()); it++;
    tmp = *it; diffuse_col.m_b = atof(tmp.c_str()); it++;it++;it++;
    tmp = *it; specular_col.m_r = atof(tmp.c_str()); it++;
    tmp = *it; specular_col.m_g = atof(tmp.c_str()); it++;
    tmp = *it; specular_col.m_b = atof(tmp.c_str()); it++;it++;

    tmp = *it;
    diff_int = atof(tmp.c_str());
    it++;


    tmp = *it;
    spec_int = atof(tmp.c_str());
    it++;


    tmp = *it;
    falloff = atof(tmp.c_str());



    PointLight* light = new PointLight(position, diffuse_col, specular_col, diff_int, spec_int, falloff);
    _scene_lights.push_back(light);
    std::cout << "OK! Light with name " << light_name << " has been parsed.\n";
  }

  void parsePlane(std::string& _text, std::vector<geo::Shape*> &_scene_objects)
  {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> space{" "};
    tokenizer tok{_text,space};
    tokenizer::iterator it = tok.begin();
    ++it;

    std::string tmp;

    float nX, nY, nZ;
    float distance;

    std::string plane_name = *it; it++;

    tmp = *it; distance = atof(tmp.c_str());
    it++;it++;
    tmp = *it; nX = atof(tmp.c_str()); it++;
    tmp = *it; nY = atof(tmp.c_str()); it++;
    tmp = *it; nZ = atof(tmp.c_str()); it++;it++;
    tmp = *it;
    if (tmp == "@checker")
    {
      float col1_r, col1_g, col1_b, col2_r, col2_g, col2_b;
      it++;it++;
      tmp = *it; col1_r = atof(tmp.c_str());it++;
      tmp = *it; col1_g = atof(tmp.c_str());it++;
      tmp = *it; col1_b = atof(tmp.c_str());it++; it++; it++;
      tmp = *it; col2_r = atof(tmp.c_str());it++;
      tmp = *it; col2_g = atof(tmp.c_str());it++;
      tmp = *it; col2_b = atof(tmp.c_str());it++; it++;
      tmp = *it;
      if (tmp == "@specularHardness")
      {
        it++;
        float specularHardness;
        tmp = *it; specularHardness = atof(tmp.c_str());
        geo::Shape* plane = new geo::Plane(distance,ngl::Vec3(nX,nY,nZ),ngl::Colour(col1_r,col1_g,col1_b,1), ngl::Colour(col2_r,col2_g,col2_b,1));
        plane->getMaterial()->m_spec_hardness = specularHardness;
        _scene_objects.push_back(plane);
        std::cout << "OK! Plane " << plane_name << " has been parsed successfully.\n";
      }
      else
      {

        geo::Shape* plane = new geo::Plane(distance,ngl::Vec3(nX,nY,nZ),ngl::Colour(col1_r,col1_g,col1_b,1), ngl::Colour(col2_r,col2_g,col2_b,1));
        _scene_objects.push_back(plane);
        std::cout << "OK! Plane " << plane_name << " has been parsed successfully.\n";

      }


      //std::cout << "DEBUGGING --> " << *it << std::endl;


    }
    else
    {
      float col_r, col_g, col_b;
      it++;
      tmp = *it;
      col_r = atof(tmp.c_str()); it++;
      tmp = *it; col_g = atof(tmp.c_str()); it++;
      tmp = *it; col_b = atof(tmp.c_str()); it++; it++;
      tmp = *it;
      if(tmp == "@specularHardness")
      {
        it++;
        float specularHardness;
        tmp = *it; specularHardness = atof(tmp.c_str());
        geo::Shape* plane = new geo::Plane(distance,ngl::Vec3(nX,nY,nZ),ngl::Colour(col_r,col_g,col_b,1));
        plane->getMaterial()->m_spec_hardness = specularHardness;
        _scene_objects.push_back(plane);
        std::cout << "OK! Plane " << plane_name << " has been parsed successfully.\n";

      }
      else
      {
        geo::Shape* plane = new geo::Plane(distance,ngl::Vec3(nX,nY,nZ),ngl::Colour(col_r,col_g,col_b,1));
        _scene_objects.push_back(plane);
        std::cout << "OK! Plane " << plane_name << " has been parsed successfully.\n";

      }
    }
  }

  void parseSphere(std::string& _text, std::vector<geo::Shape*> &_scene_objects)
  {
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> space{" "};
    tokenizer tok{_text,space};
    tokenizer::iterator it = tok.begin();
    ++it;

    std::string tmp;

    float posX, posY, posZ;
    float colX, colY, colZ;
    float radius;


    std::string sphere_name = *it;
    it++;it++;


    tmp = *it; posX = atof(tmp.c_str()); it++;
    tmp = *it; posY = atof(tmp.c_str()); it++;
    tmp = *it; posZ = atof(tmp.c_str()); it++;it++;

    tmp = *it; radius = atof(tmp.c_str()); it++;it++;
    tmp = *it; colX = atof(tmp.c_str()); it++;
    tmp = *it; colY = atof(tmp.c_str()); it++;
    tmp = *it; colZ = atof(tmp.c_str()); it++;it++;

    tmp = *it;
    if(tmp == "@specularHardness") {
      it++;

      tmp = *it;
      float specularHardness = atof(tmp.c_str());
      geo::Shape* sphere = new geo::Sphere(ngl::Vec3(posX,posY,posZ),radius, ngl::Colour(colX,colY,colZ,1));
      sphere->getMaterial()->m_spec_hardness = specularHardness;
      _scene_objects.push_back(sphere);
      std::cout << "OK! Sphere " << sphere_name << " has been parsed successfully.\n";

    }
    else if(tmp == "@reflective") {
      it++;
      tmp = *it;
      float reflection_ratio = atof(tmp.c_str()) / 100.0f;

      geo::Shape* sphere = new geo::Sphere(ngl::Vec3(posX,posY,posZ),radius, ngl::Colour(colX,colY,colZ,1));
      sphere->hasReflection(reflection_ratio, 1.0f-reflection_ratio);
      _scene_objects.push_back(sphere);
      std::cout << "OK! Sphere " << sphere_name << " has been parsed successfully.\n";
    }
    else if(tmp == "@refractive") {
      it++;
      tmp = *it;
      float ior = atof(tmp.c_str());
      it++;
      tmp = *it;
      float refraction_ratio = atof(tmp.c_str()) / 100.0f;

      geo::Shape* sphere = new geo::Sphere(ngl::Vec3(posX,posY,posZ),radius, ngl::Colour(colX,colY,colZ,1));
      sphere->hasRefraction(ior, refraction_ratio, 1.0f-refraction_ratio);
      _scene_objects.push_back(sphere);
      std::cout << "OK! Sphere " << sphere_name << " has been parsed successfully.\n";
    }
    else {
      geo::Shape* sphere = new geo::Sphere(ngl::Vec3(posX,posY,posZ),radius, ngl::Colour(colX,colY,colZ,1));
      _scene_objects.push_back(sphere);
    }


    //geo::Shape* sphere1 = new geo::Sphere(ngl::Vec3(0,0,2),float(0.8f), ngl::Colour(1,0,1,1));


  }

};

#endif
