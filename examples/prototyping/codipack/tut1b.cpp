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

Real func3(const Real x) {
  Real f1 = func1(x);
  Real f2 = func2(x);
  return f1 / (f2 * f2);
}


int main(int nargs, char** args) {
  Real x = 3.0;
  x.setGradient(1.);
  
  Real y = func1(x);
  Real x2 = std::pow(y,0.5);
  //y = x2;
  Real y2 = func2(x2);
  Real y3 = func3(x);
  std::cout << "y = " << y << std::endl;
  std::cout << "yp = " << y.getGradient() << std::endl;
  std::cout << "y2 = " << y2 << std::endl;
  std::cout << "y2p = " << y2.getGradient() << std::endl;
  std::cout << "y3 = " << y3 << std::endl;
  std::cout << "y3p = " << y3.getGradient() << std::endl;
  return 0;
}
