#ifndef BSModel01_h
#define BSModel01_h

#include <vector>
#include <cstdlib>
#include <ctime>
#include "../../../Common/coditype.hpp"

using namespace std;

typedef vector<xdouble> SamplePath;

class BSModel
{
   public:
      xdouble S0, r, sigma;
      BSModel(xdouble S0_, xdouble r_, xdouble sigma_)
         {S0 = S0_; r = r_; sigma = sigma_;
                            srand(time(NULL));}
      void GenerateSamplePath(xdouble T,int m,SamplePath& S);
};

#endif
