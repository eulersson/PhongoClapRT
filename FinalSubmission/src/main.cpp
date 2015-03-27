#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ngl/Vec3.h>

#include "Scene.h"
#include "Film.h"
#include "Shape.h"
#include "Sphere.h"
#include "Renderer.h"

int main(int argc, char *argv[])
{
  // initialise scene
  Scene scene;

  // create some geometry and push it into the scene
  geo::Shape* sphere = new geo::Sphere(ngl::Vec3(3,3,3),float(3.44));

  scene.addObject(sphere);

  // initialise film
  Film myFilm(100,100);

  // initialise renderer
  Renderer renderer(myFilm);

  std::cout << scene.getInfo() << std::endl;

  // associate film with the renderer



// TESTING AREA






  return 0;
}
