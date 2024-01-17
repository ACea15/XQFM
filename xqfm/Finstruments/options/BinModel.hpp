#pragma once

#include <cmath>
#include <iostream>
#include <codi.hpp>
using Real = codi::RealForward;


class BinModel
{
private:
  Real S0;
  double up;
  double down;
  double rate;

public:
  //computing risk-neutral probability
  double RiskNeutProb();
  int GetInputData();
  //computing the stock price at node n,i
  Real S(int n, int i);
  double GetR();
};
