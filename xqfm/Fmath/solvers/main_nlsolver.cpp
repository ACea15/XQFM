#include "nlsolver.hpp"
#include <iostream>
using namespace std;
#include <codi.hpp>
using Real = codi::RealForward;

class F1 {
public:
  Real Value(Real x, bool compute_derivative=false) {
    Real y = x * x - 2;
    cout << "function: " << y << endl;    
    if (compute_derivative) {
      Real yprime = y.getGradient();
      cout << "Derivative: " << yprime << endl;
      SetDeriv(yprime);
	}
    return y;
  }
  Real GetDeriv() { return deriv; }
  void SetDeriv(Real yprime) { deriv = yprime; }

private:
  Real deriv;
} MyF1;

int main() {
  double Acc = 0.001;
  double LEnd = 1.0, REnd = 2.0;
  double Tgt = 0.0;
  cout << "Root of F1 by bisect: " << SolveByBisect(&MyF1, Tgt, LEnd, REnd, Acc)
       << endl;

  Real Guess = 0.5;
  Guess.setGradient(1.0);
  Real sol_nr = SolveByNR(&MyF1, Tgt, Guess, Acc);
  cout << "Root of F1 by Newton-Raphson: " << sol_nr
       << endl;
  return 0;
}
