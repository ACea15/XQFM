#include <iostream>
#include <cmath>
using namespace std;


class BinModel
{
private:
  double S0;
  double U;
  double D;
  double R;

public:
  //computing risk-neutral probability
  double RiskNeutProb()
  {
    return (R-D)/(U-D);
  }
	
  //computing the stock price at node n,i
  double S(int n, int i)
  {
    return S0*pow(1+U,i)*pow(1+D,n-i);
  }
	
      //inputting, displaying and checking model data
  int GetInputData()
  {
    //entering data
    cout << "Enter S0: "; cin >> S0;
    cout << "Enter U:  "; cin >> U;
    cout << "Enter D:  "; cin >> D;
    cout << "Enter R:  "; cin >> R;
    cout << endl;
 
    //making sure that 0<S0, -1<D<U, -1<R
    if (S0<=0.0 || U<=-1.0 || D<=-1.0 || U<=D
                                      || R<=-1.0)
    {
       cout << "Illegal data ranges" << endl;
       cout << "Terminating program" << endl;
       return 1;
    }
 
   //checking for arbitrage
    if (R>=U || R<=D)
    {
       cout << "Arbitrage exists" << endl;
       cout << "Terminating program" << endl;
       return 1;
    }
 
    cout << "Input data checked" << endl;
    cout << "There is no arbitrage" << endl << endl;
 
    return 0;
  }
	

  double GetR()
  {
    return R;
  }

};


int GetInputData(int& N, double& K)
{
   cout << "Enter steps to expiry N: "; cin >> N;
   cout << "Enter strike price K:    "; cin >> K;
   cout << endl;
   return 0;
}

double PriceByCRR(BinModel Model, int N, double K,
               double (*Payoff)(double z, double K))
{
   double q=Model.RiskNeutProb();
   double Price[N+1];
   for (int i=0; i<=N; i++)
   {
      Price[i]=Payoff(Model.S(N,i),K);
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

double CallPayoff(double z, double K)
{
   if (z>K) return z-K;
   return 0.0;
}

double PutPayoff(double z, double K)
{
   if (z<K) return K-z;
   return 0.0;
}



int main()
{
   BinModel Model;

   if (Model.GetInputData()==1) return 1;

   double K;   //strike price
   int N;      //steps to expiry

   cout << "Enter call option data:" << endl;
   GetInputData(N,K);
   cout << "European call option price = "
        << PriceByCRR(Model,N,K,CallPayoff)
        << endl << endl;

   cout << "Enter put option data:" << endl;
   GetInputData(N,K);
   cout << "European put option price =  "
        << PriceByCRR(Model,N,K,PutPayoff)
        << endl << endl;

   return 0;
}
