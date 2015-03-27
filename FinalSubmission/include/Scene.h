#ifndef _SCENE_H_
#define _SCENE_H_

#include <fstream>
#include <string>
#include <vector>

#include "Shape.h"
#include "Light.h"
#include "Streamer.h"

class Scene
{
public:
  Scene() : m_fileName(std::string("Hello")) {}
  Scene(Streamer _s, std::string _n) : m_streamer(_s), m_fileName(_n) {}
  ~Scene();
  void addObject(const Shape* _object);
  void addLight(const Light* _light);
private:
  Streamer m_streamer;
  std::string m_fileName;
  std::vector<Shape*> m_objects;
  std::vector<Light*> m_lights;

};

#endif // Scene.h
