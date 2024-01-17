#include <codi.hpp>
#include <iostream>
 
int main(int nargs, char** args) {
  codi::RealForward x = 4.0;
  x.setGradient(1.0);
 
  codi::RealForward y = x * x;
 
  std::cout << "f(4.0) = " << y << std::endl;
  std::cout << "df/dx(4.0) = " << y.getGradient() << std::endl;
 
  return 0;
}
