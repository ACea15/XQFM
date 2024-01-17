#include <iostream>
#include "PathDepOption04.h"
#include "GmtrAsianCall.h"
#include <codi.hpp>
 
using Real = codi::RealForward;

using namespace std;

int main()
{
   Real S0=100.0, r=0.03, sigma=0.2;
   S0.setGradient(1.);

   BSModel Model(S0,r,sigma);

   double T =1.0/12.0, K=100.0;
   int m=30;

   ArthmAsianCall Option(T,K,m);
   //GmtrAsianCall  CVOption(T,K,m);

   long N=30000;
   //Option.PriceByVarRedMC(Model,N,CVOption);
   //cout << "Arithmetic call price = " << Option.Price << endl
   //     << "Error = " << Option.PricingError << endl;

   Option.PriceByMC(Model,N);
   cout << "Price by direct MC = " << Option.Price << endl
        << "MC Error = " << Option.PricingError << endl;

   return 0;
}
