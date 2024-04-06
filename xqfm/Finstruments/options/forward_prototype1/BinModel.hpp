#pragma once

#include <cmath>
#include <iostream>
#include <codi.hpp>
using Real = codi::RealForward;


class BinModel
{
private:
  Real S0;
  Real up;
  Real down;
  Real rate;

public:
  //computing risk-neutral probability
  Real RiskNeutProb();
  int GetInputData();
  //computing the stock price at node n,i
  Real S(int n, int i);
  Real GetR();
};
