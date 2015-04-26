#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
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

  ngl::Colour white(1,1,1,1);
  ngl::Colour black(0,0,0,1);
  ngl::Colour red(1,0,0,1);
  ngl::Colour green(0,1,0,1);
  ngl::Colour blue(0,0,1,1);
  ngl::Colour light_blue(0.347,0.89,0.78,1);

  PointLight* light1 = new PointLight(ngl::Vec3(1,5,2),light_blue,light_blue,1,1,1);
  myScene.addLight(light1);

  PointLight* light2 = new PointLight(ngl::Vec3(-1,0.4,0),white,white,0.5,0.5,1);
  myScene.addLight(light2);

  PointLight* light3 = new PointLight(ngl::Vec3(-1.5,1,10),red,red,1,1,1);
  myScene.addLight(light3);

  //create some geometry and push it into the scene

  // FLOOR PLANE
  geo::Shape* plane1 = new geo::Plane(-1.0f,ngl::Vec3(0,1,0),ngl::Colour(0,0,0,1), ngl::Colour(1,1,1,1));
  plane1->getMaterial()->m_spec_hardness = 4.0f;
  myScene.addObject(plane1);
  // FRONT PLANE
  //geo::Shape* plane2 = new geo::Plane(-8.0f,ngl::Vec3(0,0,-1),ngl::Colour(1,1,1,1)*0.5);
  //myScene.addObject(plane2);
  // LEFT PLANE
  //geo::Shape* plane3 = new geo::Plane(-2.0f,ngl::Vec3(1,0,0),ngl::Colour(0.403,0.770,0.760,1));
  //myScene.addObject(plane3);
  // RIGHT PLANE
  //geo::Shape* plane4 = new geo::Plane(-2.0f,ngl::Vec3(-1,0,0),ngl::Colour(1,0.56,0,1));
  //myScene.addObject(plane4);
  // TOP PLANE
  //geo::Shape* plane5 = new geo::Plane(-2.0f,ngl::Vec3(0,-1,0),ngl::Colour(1,1,1,1));
  //myScene.addObject(plane5);
  // BACK PLANE
  //geo::Shape* plane6 = new geo::Plane(-2.0f,ngl::Vec3(0,0,1),ngl::Colour(0.5f,0,0,1));
  //myScene.addObject(plane6);

  geo::Shape* sphere1 = new geo::Sphere(ngl::Vec3(0,0,2),float(0.8f), ngl::Colour(1,0,1,1));
  sphere1->getMaterial()->m_spec_hardness = 5.0f;
  //sphere1->hasRefraction(1.2, 0.9f, 0.1f);
  myScene.addObject(sphere1);

  geo::Shape* sphere2 = new geo::Sphere(ngl::Vec3(-1,1.2,2),float(0.6f), ngl::Colour(0.1,0.4,0.95,1));
  sphere2->hasReflection(0.7f, 0.3f);
  myScene.addObject(sphere2);

  geo::Shape* sphere3 = new geo::Sphere(ngl::Vec3(0.9,0.15,2.4),float(0.3f), ngl::Colour(0,1,0,1));
  sphere3->getMaterial()->m_spec_hardness = 100.0f;
  myScene.addObject(sphere3);

  geo::Shape* sphere4 = new geo::Sphere(ngl::Vec3(-0.9,0.15,0.8),float(0.3f), ngl::Colour(1,0,0,1));
  sphere4->hasRefraction(1.2f, 1.0f, 0.0f);
  myScene.addObject(sphere4);

  geo::Shape* sphere5 = new geo::Sphere(ngl::Vec3(0.5,0.15,0.2),float(0.2f), ngl::Colour(0,0.8,1,1));
  sphere5->getMaterial()->m_spec_hardness = 40.0f;
  myScene.addObject(sphere5);

  // initialise film
  Film myFilm(1000,1000);

  ngl::Vec3 O (0,0,0);
  ngl::Vec3 X (1,0,0);
  ngl::Vec3 Y (0,1,0);
  ngl::Vec3 Z (0,0,1);

  ngl::Vec3 campos(0,1,-2);
  ngl::Vec3 lookat(0,0,6);
  ngl::Vec3 diff_btw = campos - lookat;
  diff_btw.normalize();
  ngl::Vec3 camdir = -diff_btw;
  ngl::Vec3 camright = Y.cross(camdir);
  ngl::Vec3 camdown = camright.cross(camdir);


  // initialise camera
  Camera myCamera(campos,camdir,camright,camdown);



  // initialise renderer and bind film and camera to it
  Renderer renderer(myScene, myFilm, myCamera, 4, 16);

  // start the rendering process
  renderer.render();

  // display the image


  return 0;
}
