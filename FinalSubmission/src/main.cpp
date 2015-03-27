#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ngl/Vec3.h>

#include "Scene.h"
#include "Film.h"
#include "Sphere.h"
#include "Renderer.h"

int main(int argc, char *argv[])
{
  // initialise scene
  Scene scene;

  // create some geometry and push it into the scene
  geo::Sphere sphere(ngl::Vec3(0,0,-10),3);

  scene.addObject(sphere);


  // initialise film
  Film myFilm(100,100);

  // initialise renderer
  Renderer renderer(myFilm);

  // associate film with the renderer



// TESTING AREA






  return 0;
}
