#include "BinOptions.hpp"
#include <vector>


Real Call::PriceByCRR(BinModel Model)
{
   Real q=Model.RiskNeutProb();
   int N=GetN();
   std::vector<Real> Price(N+1);
   for (int i=0; i<=N; i++)
   {
      Price[i]=Payoff(Model.S(N,i));
   }
   for (int n=N-1; n>=0; n--)
   {
      for (int i=0; i<=n; i++)
      {
         Price[i]=(q*Price[i+1]+(1-q)*Price[i])
            /(1+Model.GetR());
      }
   }
   return Price[0];
}

Real Call::Payoff(Real z)
{
   if (z>K) return z-K;
   Real x = 0.0;
   return x;
}

int Call::GetInputData()
{
   std::cout << "Enter call option data:" << std::endl;
   int N;
   std::cout << "Enter steps to expiry N: "; std::cin >> N;
   SetN(N);
   std::cout << "Enter strike price K:    "; std::cin >> K;
   std::cout << std::endl;
   return 0;
}
