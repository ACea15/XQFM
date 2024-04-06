#include "BinModel.hpp"
#include <codi.hpp>
using Real = codi::RealForward;

class Option
{
   private:
      int N; //steps to expiry

   public:
      void SetN(int N_){N=N_;}
      int GetN(){return N;}
  //virtual double Payoff(double z)=0;
};

class EurOption: public virtual Option
{
   public:
      //pricing European option
      Real PriceByCRR(BinModel Model);
};

class Call: public EurOption
{
   private:
      Real K; //strike price

   public:
      void SetK(double K_){K=K_;}
      int GetInputData();
      Real PriceByCRR(BinModel Model);
      Real Payoff(Real z);
};
