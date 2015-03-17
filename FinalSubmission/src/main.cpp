#include <iostream>
#include <stdlib.h>

#include "Sphere.h"



int main(int argc, char *argv[])
{
  geo::Sphere s1;
  s1.setRadius(3.0);
  std::cout << s1.getRadius() << std::endl;
  return 0;
}
