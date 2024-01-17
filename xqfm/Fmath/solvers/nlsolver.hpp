#pragma once
#include <codi.hpp>
using Real = codi::RealForward;

template <typename Function>
Real SolveByBisect(Function *Fct, double Tgt, double LEnd, double REnd,
                     double Acc) {
  double left = LEnd, right = REnd, mid = (left + right) / 2;
  Real y_left = Fct->Value(left) - Tgt;
  Real y_mid = Fct->Value(mid) - Tgt;
  while (mid - left > Acc) {
    if ((y_left > 0 && y_mid > 0) || (y_left < 0 && y_mid < 0)) {
      left = mid;
      y_left = y_mid;
    } else
      right = mid;
    mid = (left + right) / 2;
    y_mid = Fct->Value(mid) - Tgt;
  }
  return mid;
}

template <typename Function>
Real SolveByNR(Function *Fct, double Tgt, Real Guess, double Acc) {
  Real x_prev = Guess;
  //x_prev.setGradient(1.0);
  Real x_next = x_prev - (Fct->Value(x_prev, true) - Tgt) / Fct->GetDeriv();
  //Real try1=Fct->Value(x_next+1);
  while (x_next - x_prev > Acc || x_prev - x_next > Acc) {
    //Real try2=Fct->Value(x_prev+1);
    x_prev = x_next;
    x_prev.setGradient(1.0);
    Real try3=Fct->Value(x_prev+1, true);
    Real fctvalue = Fct->Value(x_prev, true);
    Real fctderv = Fct->GetDeriv();
    x_next = x_prev - (fctvalue - Tgt) / fctderv;
    //x_prev.setGradient(0.0);
  }
  return x_next;
}
