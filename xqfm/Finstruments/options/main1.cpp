#include "BinModel.hpp"
#include "BinOptions.hpp"
#include <iostream>
#include <codi.hpp>
using Real = codi::RealReverse;
using Tape = typename Real::Tape;

using namespace std;

int main()
{
   BinModel Model;

   if (Model.GetInputData()==1) return 1;

   Call Option;
   Option.GetInputData();
   Real price = Option.PriceByCRR(Model);
   cout << "price:" << price
        << endl << endl;
   Real d_price = price.getGradient();
   cout << "price der:" << d_price
        << endl << endl;   
   return 0;
}
