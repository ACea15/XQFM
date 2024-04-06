#include <cmath>
#include <iostream>
#include <codi.hpp>
 
using Real = codi::RealReverse;


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
  using Tape = typename Real::Tape;
  
  Real x = 3.0;
  Tape& tape = Real::getTape();
  tape.setActive();        // Step 1: Start recording
 
  tape.registerInput(x);   // Step 2: Register inputs
  Real y = func1(x);     // Step 3: Call function
  tape.registerOutput(y);  // Step 4: Register outputs
 
  tape.setPassive();       // Step 5: Stop recording
  y.setGradient(1.0);      // Step 6: Set seeding
  tape.evaluate();         // Step 7: Perform reverse evaluation
   
  tape.registerOutput(y);  // Step 4: Register outputs
  tape.setPassive();       // Step 5: Stop recording
  y.setGradient(1.0);      // Step 6: Set seeding
  tape.evaluate();         // Step 7: Perform reverse evaluation
  std::cout << "y = " << y << std::endl;
  std::cout << "yp = " << x.getGradient() << std::endl;
  

  tape.setActive();        // Step 1: Start recording
  tape.registerInput(x);   // Step 2: Register inputs
  Real y1 = func1(x);        // Step 3: Call function
  Real x2 = std::pow(y1,0.5);
  //y = x2;
  Real y2 = func2(x2);
  tape.registerOutput(y2);  // Step 4: Register outputs
  tape.setPassive();       // Step 5: Stop recording
  y2.setGradient(1.0);      // Step 6: Set seeding
  tape.evaluate();         // Step 7: Perform reverse evaluation
  std::cout << "y2 = " << y2 << std::endl;
  std::cout << "y2p = " << x.getGradient() << std::endl;
  
  tape.setActive();        // Step 1: Start recording
  tape.registerInput(x);   // Step 2: Register inputs
  Real y3 = func3(x);
  tape.registerOutput(y3);  // Step 4: Register outputs
  tape.setPassive();       // Step 5: Stop recording
  y3.setGradient(1.0);      // Step 6: Set seeding
  tape.evaluate();         // Step 7: Perform reverse evaluation

  std::cout << "y3 = " << y3 << std::endl;
  std::cout << "y3p = " << x.getGradient() << std::endl;
  return 0;
}
