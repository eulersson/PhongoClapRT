#include <iostream>
#include <stdlib.h>

#include "Sphere.h"



int main(int argc, char *argv[])
{
  Ray r1(ngl::Vec3(0,0,0),ngl::Vec3(0,0,1));
  geo::Sphere s1(ngl::Vec3(0,0,10),1);

  std::cout << s1.getIntersection(r1) << std::endl;



  return 0;
}
