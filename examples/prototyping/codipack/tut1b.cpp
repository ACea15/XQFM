#include <cmath>
#include <iostream>
#include <codi.hpp>
 
using Real = codi::RealForward;


Real func1(const Real x) {
  return x * x * x * x;
}

Real func2(const Real x) {
  return x * 2;
}


int main(int nargs, char** args) {
  Real x = 4.0;
  x.setGradient(0.5);
  
  Real y = func1(x);
  Real x2 = std::pow(y,0.5);
  y = x2;
  Real y2 = func2(y);
 
  std::cout << "y = " << y << std::endl;
  std::cout << "y2 = " << y2 << std::endl;
  std::cout << "yp = " << y.getGradient() << std::endl;
  std::cout << "y2p = " << y2.getGradient() << std::endl;
 
  return 0;
}
