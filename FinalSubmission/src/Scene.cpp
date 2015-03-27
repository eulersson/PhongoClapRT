#include "Scene.h"


Scene::~Scene()
{
  // Iterate over vectors and delete all the dynamically allocated objects
}

Scene::addObject(const Shape *_object)
{
  m_objects.push_back(object);
}

Scene::addLight(const Light *_light)
{
  m_objects.push_back(light);
}

/*
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

*/
