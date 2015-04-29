#ifndef _SCENE_H_
#define _SCENE_H_

#include <fstream>
#include <string>
#include <vector>

#include "Shape.h"
#include "Light.h"


class Scene
{
public:
  Scene() : m_fileName(std::string("Hello")) {}
  Scene(std::string _n) : m_fileName(_n) {}
  ~Scene();
  void addObject(geo::Shape *_object);
  void addLight(Light  *_light);
  float getInfo();

  // give access to Renderer class to the private interface
  friend class Renderer;

private:
  std::string m_fileName;
  std::vector<geo::Shape*> m_objects;
  std::vector<Light*> m_lights;

};

#endif // Scene.h
