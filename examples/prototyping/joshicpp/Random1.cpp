#include "Random1.hpp"
#include <cstdlib>
#include <cmath>

double GetOneGaussianBySummation()
{
  double result=0.;
  for (unsigned long j=0; j<12; j++)
    result += std::rand()/static_cast<double>(RAND_MAX);
  result -= 6;
  return result;
}

double GetOneGaussianByBoxMuller()
{
  double result, x, y, sizeSquared;
  do
    {
      x = 2.0*std::rand()/static_cast<double>(RAND_MAX)-1;
      y = 2.0*std::rand()/static_cast<double>(RAND_MAX)-1;
      sizeSquared = x*x + y*y;
    }
  while (sizeSquared >= 1.0);
  result = x*std::sqrt(-2*std::log(sizeSquared)/sizeSquared);
  return result;
}
  
