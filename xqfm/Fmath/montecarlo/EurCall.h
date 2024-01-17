#ifndef EurCall_h
#define EurCall_h
#include <codi.hpp>
 
using Real = codi::RealForward;


class EurCall
{
   public:
      double T, K;
      EurCall(double T_, double K_){T=T_; K=K_;}
      Real d_plus(Real S0, Real sigma, Real r);
      Real d_minus(Real S0, Real sigma, Real r);
      Real PriceByBSFormula(Real S0,
         Real sigma, Real r);
      Real VegaByBSFormula(Real S0,
         Real sigma, Real r);
};

#endif
