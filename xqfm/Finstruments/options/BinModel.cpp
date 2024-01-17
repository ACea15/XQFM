
#include "BinModel.hpp"

double BinModel::RiskNeutProb()
  {return (rate-down)/(up-down);}

      //computing the stock price at node n,i
Real BinModel::S(int n, int i)
{return S0*std::pow(1+up,i)*std::pow(1+down,n-i);}

//inputting, displaying and checking model data
int BinModel::GetInputData()
{   //entering data
  std::cout << "Enter S0: "; std::cin >> S0;
  std::cout << "Enter U:  "; std::cin >> up;
  std::cout << "Enter D:  "; std::cin >> down;
  std::cout << "Enter R:  "; std::cin >> rate;
  std::cout << std::endl;

   //making sure that 0<S0, -1<D<U, -1<R
   if (S0<=0.0 || up<=-1.0 || down<=-1.0 || up<=down
                                     || rate<=-1.0)
   {
      std::cout << "Illegal data ranges" << std::endl;
      std::cout << "Terminating program" << std::endl;
      return 1;
   }

  //checking for arbitrage
   if (rate>=up || rate<=down)
   {
      std::cout << "Arbitrage exists" << std::endl;
      std::cout << "Terminating program" << std::endl;
      return 1;
   }

   std::cout << "Input data checked" << std::endl;
   std::cout << "There is no arbitrage" << std::endl << std::endl;

   return 0;
}	

double BinModel::GetR()
{return rate;}
