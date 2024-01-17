#ifndef PathDepOption04_h
#define PathDepOption04_h
#include <codi.hpp>
 
using Real = codi::RealForward;

#include "BSModel01.h"

class PathDepOption
{
   public:
  Real Price,PricingError; 
  double T;
      int m;
      virtual Real Payoff(SamplePath& S)=0;
      Real PriceByMC(BSModel Model, long N);
      double PriceByVarRedMC
             (BSModel Model, long N, PathDepOption& CVOption);
      virtual double PriceByBSFormula
                     (BSModel Model){return 0.0;}
};

class DifferenceOfOptions: public PathDepOption
{
   public:
      PathDepOption* Ptr1;
      PathDepOption* Ptr2;
      DifferenceOfOptions(double T_, int m_,
                          PathDepOption* Ptr1_,
                          PathDepOption* Ptr2_)
         {T=T_; m=m_; Ptr1=Ptr1_; Ptr2=Ptr2_;}
      Real Payoff(SamplePath& S)
         {return Ptr1->Payoff(S)-Ptr2->Payoff(S);}
};

class ArthmAsianCall: public PathDepOption
{
   public:
      double K;
      ArthmAsianCall(double T_, double K_, int m_)
            {T=T_; K=K_; m=m_;}
      Real Payoff(SamplePath& S);
};

#endif
