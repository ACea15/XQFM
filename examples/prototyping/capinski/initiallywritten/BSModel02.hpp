#pragma once

#include "Matrix.hpp"
typedef vector<Vector> SamplePath;

class BSModel {
public:
  Vector S0, sigma;
  Matrix C;
  double r;

  BSModel(Vector S0_, double r_, Matrix C_);
  void GenerateSamplePath(double T, int m, SamplePath &S);
};
