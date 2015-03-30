#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ngl/Vec3.h>

#include "Scene.h"
#include "Film.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Renderer.h"

int main(int argc, char *argv[])
{
  // initialise scene
  Scene myScene;

  // create some geometry and push it into the scene
  geo::Shape* plane1 = new geo::Plane(10.0f,ngl::Vec3(0,1,-0.2),ngl::Colour(1,0,0,1));
  myScene.addObject(plane1);

  geo::Shape* sphere1 = new geo::Sphere(ngl::Vec3(0,2,8),float(1.2), ngl::Colour(1,1,0,1));
  myScene.addObject(sphere1);

  geo::Shape* sphere2 = new geo::Sphere(ngl::Vec3(0,0,3),float(0.8), ngl::Colour(0,1,0,1));
  myScene.addObject(sphere2);


  /*
  geo::Shape* sphere1 = new geo::Sphere(ngl::Vec3(0,2,8),float(1.2), ngl::Colour(1,0,0,1));
  geo::Shape* sphere2 = new geo::Sphere(ngl::Vec3(0,0,3),float(0.8), ngl::Colour(0,1,0,1));


  myScene.addObject(sphere1);
  myScene.addObject(sphere2);*/

  // initialise film
  Film myFilm(400,400);

  // initialise camera
  Camera myCamera;

  // initialise renderer and bind film and camera to it
  Renderer renderer(myScene, myFilm, myCamera);

  // start the rendering process
  renderer.render();

  // display the image


  return 0;
}
