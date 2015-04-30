//----------------------------------------------------------------------------------------------------------------------
/// @file Scene.cpp
/// @brief Definitions for Scene class
//----------------------------------------------------------------------------------------------------------------------

#include "Scene.h"

Scene::Scene() {}
Scene::Scene(std::string _n) : m_fileName(_n) {}
Scene::~Scene() {}

void Scene::addObject(geo::Shape *_object)
{
  m_objects.push_back(dynamic_cast<geo::Shape*>(_object));
}

void Scene::addLight(Light *_light)
{
  m_lights.push_back(dynamic_cast<Light*>(_light));
}
