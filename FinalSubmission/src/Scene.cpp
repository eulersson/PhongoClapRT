#include "Scene.h"


Scene::~Scene()
{

}

void Scene::addObject(Shape &_object)
{
  m_objects.push_back(_object);
}

void Scene::addLight(Light &_light)
{
  m_lights.push_back(_light);
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
