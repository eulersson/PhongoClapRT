#ifndef _PARSER_H_
#define _PARSER_H_

/// @file Parser.h
/// @author Ramon Blanquer
/// @brief Parses a text file that user passes as an argument when executing the program
/// @todo I CANNOT MOVE THE DEFINITIONS TO A CPP FILE! IT COMPLAINTS ABOUT MULTIPLE DECLARATIONS, try to do it!

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

  Parser(std::string &_image_name,
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

    text.assign((std::istreambuf_iterator<char>(sceneFile)), std::istreambuf_iterator<char>());

    tokenizer tok{text,quote};
    tokenizer::iterator it = tok.begin();
    std::string tmp;

    std::cout << "Parsing filename...\n"; ++it;

    _image_name = *it;

    std::cout << "OK! Filename: " << _image_name << std::endl; ++it; ++it;
    std::cout << "Parsing file dimensions...\n";

    tmp = *it; _width = atoi(tmp.c_str()); ++it; ++it; // WIDTH
    tmp = *it; _height = atoi(tmp.c_str()); // HEIGHT

    std::cout << "OK! " << _width << "x" << _height << " image specified.\n";

    std::cout << "Parsing camera...\n"; ++it; ++it;
    tmp = *it; _camPosX = atof(tmp.c_str()); ++it; ++it; // camPosX
    tmp = *it; _camPosY = atof(tmp.c_str()); ++it; ++it; // camPosY
    tmp = *it; _camPosZ = atof(tmp.c_str()); ++it; ++it; // camPosZ
    tmp = *it; _lookAtX = atof(tmp.c_str()); ++it; ++it; // lookAtX
    tmp = *it; _lookAtY = atof(tmp.c_str()); ++it; ++it; // lookAtY
    tmp = *it; _lookAtZ = atof(tmp.c_str()); // lookAtZ

    std::cout << "OK! Camera parsed with pos["<<_camPosX <<","<<_camPosY<<","<<_camPosZ<<"] and lookup["<<_lookAtX<<","<<_lookAtY<<","<<_lookAtZ<<"]\n"; ++it; ++it;

    tmp = *it; _max_depth = atoi(tmp.c_str()); ++it; ++it; // max_depth
    tmp = *it; _anti_aliasing = atoi(tmp.c_str()); ++it; ++it; // anti_aliasing

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
    ngl::Colour diffuse_col, specular_col;
    float diff_int, spec_int, falloff;

    light_name = *it; it++;it++;

    tmp = *it; position.m_x = atof(tmp.c_str()); it++;              // light x position
    tmp = *it; position.m_y = atof(tmp.c_str()); it++;              // light y position
    tmp = *it; position.m_z = atof(tmp.c_str()); it++;it++;it++;    // light z position
    tmp = *it; diffuse_col.m_r = atof(tmp.c_str()); it++;           // light r diffuse value
    tmp = *it; diffuse_col.m_g = atof(tmp.c_str()); it++;           // light g diffuse value
    tmp = *it; diffuse_col.m_b = atof(tmp.c_str()); it++;it++;it++; // light b diffuse value
    tmp = *it; specular_col.m_r = atof(tmp.c_str()); it++;          // light r specular value
    tmp = *it; specular_col.m_g = atof(tmp.c_str()); it++;          // light g specular value
    tmp = *it; specular_col.m_b = atof(tmp.c_str()); it++;it++;     // light b specular value
    tmp = *it; diff_int = atof(tmp.c_str()); it++;                  // light diffuse intensity
    tmp = *it; spec_int = atof(tmp.c_str()); it++;                  // light specular intensity
    tmp = *it; falloff = atof(tmp.c_str());                         // light falloff

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

    tmp = *it; distance = atof(tmp.c_str()); it++;it++; // distance
    tmp = *it; nX = atof(tmp.c_str()); it++;            // normal x component
    tmp = *it; nY = atof(tmp.c_str()); it++;            // normal y component
    tmp = *it; nZ = atof(tmp.c_str()); it++;it++;       // normal z component
    tmp = *it;
    if (tmp == "@checker")
    {
      float col1_r, col1_g, col1_b, col2_r, col2_g, col2_b; it++;it++;

      tmp = *it; col1_r = atof(tmp.c_str());it++;             // colour1 r
      tmp = *it; col1_g = atof(tmp.c_str());it++;             // colour1 g
      tmp = *it; col1_b = atof(tmp.c_str());it++; it++; it++; // colour1 b
      tmp = *it; col2_r = atof(tmp.c_str());it++;             // colour2 r
      tmp = *it; col2_g = atof(tmp.c_str());it++;             // colour2 g
      tmp = *it; col2_b = atof(tmp.c_str());it++; it++;       // colour2 b
      tmp = *it;

      if (tmp == "@specularHardness")
      {
        it++;
        float specularHardness;
        tmp = *it; specularHardness = atof(tmp.c_str()); // specular hardness

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
    }
    else
    {
      float col_r, col_g, col_b;
      it++;
      tmp = *it; col_r = atof(tmp.c_str()); it++;        // colour1 r
      tmp = *it; col_g = atof(tmp.c_str()); it++;        // colour1 g
      tmp = *it; col_b = atof(tmp.c_str()); it++; it++;  // colour1 b
      tmp = *it;

      if(tmp == "@specularHardness")
      {
        it++;
        float specularHardness;
        tmp = *it; specularHardness = atof(tmp.c_str()); // specular hardness

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

    tmp = *it; posX = atof(tmp.c_str()); it++;        // sphere center x
    tmp = *it; posY = atof(tmp.c_str()); it++;        // sphere center y
    tmp = *it; posZ = atof(tmp.c_str()); it++;it++;   // sphere center z
    tmp = *it; radius = atof(tmp.c_str()); it++;it++; // sphere radius
    tmp = *it; colX = atof(tmp.c_str()); it++;        // sphere colour r
    tmp = *it; colY = atof(tmp.c_str()); it++;        // sphere colour g
    tmp = *it; colZ = atof(tmp.c_str()); it++;it++;   // sphere colour b
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
      tmp = *it; float reflection_ratio = atof(tmp.c_str()) / 100.0f; // reflection amount

      geo::Shape* sphere = new geo::Sphere(ngl::Vec3(posX,posY,posZ),radius, ngl::Colour(colX,colY,colZ,1));
      sphere->hasReflection(reflection_ratio, 1.0f-reflection_ratio);
      _scene_objects.push_back(sphere);

      std::cout << "OK! Sphere " << sphere_name << " has been parsed successfully.\n";
    }
    else if(tmp == "@refractive") {
      it++;
      tmp = *it; float ior = atof(tmp.c_str()); it++;                 // index of refraction
      tmp = *it; float refraction_ratio = atof(tmp.c_str()) / 100.0f; // refraction amount

      geo::Shape* sphere = new geo::Sphere(ngl::Vec3(posX,posY,posZ),radius, ngl::Colour(colX,colY,colZ,1));
      sphere->hasRefraction(ior, refraction_ratio, 1.0f-refraction_ratio);
      _scene_objects.push_back(sphere);

      std::cout << "OK! Sphere " << sphere_name << " has been parsed successfully.\n";
    }
    else {
      geo::Shape* sphere = new geo::Sphere(ngl::Vec3(posX,posY,posZ),radius, ngl::Colour(colX,colY,colZ,1));
      _scene_objects.push_back(sphere);
    }
  }
};

#endif
