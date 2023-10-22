#pragma once
#include "PayOff2.hpp"
double SimpleMonteCarlo2(const PayOff &thePayOff, double Expiry, double Spot,
                         double Vol, double r, unsigned long NumberOfPaths);
