#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <assert.h>
#include <ngl/Vec3.h>
#include <vector>
#include <boost/tokenizer.hpp>

#include "Scene.h"
#include "Film.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Renderer.h"
#include "Parser.h"



int main(int argc, char *argv[])
{

  // USER DEFINES THESE VARIABLES
  int width         = 0;
  int height        = 0;
  float camPosX     = 0;
  float camPosY     = 0;
  float camPosZ     = 0;
  float lookAtX     = 0;
  float lookAtY     = 0;
  float lookAtZ     = 0;
  int max_depth     = 0;
  int anti_aliasing = 0;

  std::vector<Light*> scene_lights;
  std::vector<geo::Shape*> scene_objects;

  std::string text_file("scene_file.txt");
  std::string image_name("yourImage.ppm");

  Parser scene_parser(image_name,
                      text_file,
                      width,
                      height,
                      camPosX,
                      camPosY,
                      camPosZ,
                      lookAtX,
                      lookAtY,
                      lookAtZ,
                      max_depth,
                      anti_aliasing,
                      scene_lights,
                      scene_objects);

  // ASSERTIONS and EXCEPTION HANDLING
  if(anti_aliasing < 1)
  {
    std::cout << "ERROR: Anti-aliasing should be 1 (no-antialising) or more." << std::endl;
    assert(anti_aliasing > 0);
  }

  // initialise scene
  Scene myScene;


  for(unsigned int i = 0; i < scene_objects.size(); i++)
  {
    myScene.addObject(scene_objects.at(i));
  }

  for(unsigned int i = 0; i < scene_lights.size(); i++)
  {
    myScene.addLight(scene_lights.at(i));
  }



  // initialise film
  Film myFilm(width,height);

  ngl::Vec3 Y (0,1,0);
  ngl::Vec3 campos(camPosX,camPosY,camPosZ);
  ngl::Vec3 lookat(lookAtX,lookAtY,lookAtZ);

  ngl::Vec3 diff_btw = campos - lookat;
  diff_btw.normalize();

  ngl::Vec3 camdir = -diff_btw;
  ngl::Vec3 camright = Y.cross(camdir);
  ngl::Vec3 camdown = camright.cross(camdir);

  // initialise camera
  Camera myCamera(campos,camdir,camright,camdown);


  // initialise renderer and bind film and camera to it
  Renderer renderer(myScene, myFilm, myCamera, max_depth, anti_aliasing);

  // start the rendering process
  renderer.render();

  // display the image


  return 0;
}
