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

  PointLight* light1 = new PointLight(ngl::Vec3(0,1,0),1);
  myScene.addLight(light1);

  // create some geometry and push it into the scene
  geo::Shape* plane1 = new geo::Plane(0.0f,ngl::Vec3(0,1,0),ngl::Colour(1,0,0,1));
  myScene.addObject(plane1);

  geo::Shape* sphere1 = new geo::Sphere(ngl::Vec3(0,0.2,0),float(0.1f), ngl::Colour(1,1,0,1));
  myScene.addObject(sphere1);

  //geo::Shape* sphere2 = new geo::Sphere(ngl::Vec3(1.75f,-0.25f,0.0f),float(0.15f), ngl::Colour(0,1,0,1));
  //myScene.addObject(sphere2);


  // initialise film
  Film myFilm(400,400);

  ngl::Vec3 O (0,0,0);
  ngl::Vec3 X (1,0,0);
  ngl::Vec3 Y (0,1,0);
  ngl::Vec3 Z (0,0,1);

  ngl::Vec3 campos(0,0.4,1);
  ngl::Vec3 lookat(0,0,-1);
  ngl::Vec3 diff_btw = campos - lookat;
  diff_btw.normalize();
  ngl::Vec3 camdir = -diff_btw;
  ngl::Vec3 camright = Y.cross(camdir);
  ngl::Vec3 camdown = camright.cross(camdir);


  // initialise camera
  Camera myCamera(campos,camdir,camright,camdown);

  // initialise renderer and bind film and camera to it
  Renderer renderer(myScene, myFilm, myCamera);

  // start the rendering process
  renderer.render();

  // display the image


  return 0;
}
