#ifndef _PARSER_H_
#define _PARSER_H_

#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>

#include "Light.h"
#include "Shape.h"


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
      ++it;
      _image_name = *it;
      ++it; ++it;
      tmp = *it;
      _width = atoi(tmp.c_str()); // WIDTH
      ++it; ++it;
      tmp = *it;
      _height = atoi(tmp.c_str()); // HEIGHT
      ++it; ++it;
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
      ++it; ++it;
      tmp = *it;
      _max_depth = atoi(tmp.c_str()); // max_depth
      ++it; ++it;  tmp = *it;
      _anti_aliasing = atoi(tmp.c_str()); // anti_aliasing
      ++it; ++it;

      parseLights(text);


  }
  ~Parser() {}

  void parseObjects(){}

  void parseLights(std::string& _text)
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
      parseSingleLight(tmp);
      ++it;


    }

  }

  void parseSingleLight(std::string &_text_light){

    std::cout << _text_light << std::endl;

  }
  void parseSingleObject(){}

};

#endif
