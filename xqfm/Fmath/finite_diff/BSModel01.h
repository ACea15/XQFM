#ifndef BSModel01_h
#define BSModel01_h

#include <vector>
#include <cstdlib>
#include <ctime>
#include <codi.hpp>
 
using Real = codi::RealForward;

using namespace std;

typedef vector<Real> SamplePath;

class BSModel
{
   public:
      Real S0, r, sigma;
      BSModel(Real S0_, Real r_, Real sigma_)
         {S0 = S0_; r = r_; sigma = sigma_;
                            srand(time(NULL));}
      void GenerateSamplePath(double T,int m,SamplePath& S);
};

#endif
