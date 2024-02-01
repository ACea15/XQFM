#include <iostream>
#include <cmath>
#include <codi.hpp>

using namespace std;

template <typename DoubleType>
class BinModel
{
private:
  DoubleType S0;
  DoubleType U;
  DoubleType D;
  DoubleType R;

public:
  //computing risk-neutral probability
  DoubleType RiskNeutProb()
  {
    return (R-D)/(U-D);
  }
	
  //computing the stock price at node n,i
  DoubleType S(int n, int i)
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
	
  void GetInputData(const DoubleType& S0_, const DoubleType &U_, const DoubleType& D_, const DoubleType& R_)
  {
    S0 = S0_;
    U = U_;
    D = D_;
    R = R_;
    // S0.setGradient(0.0);
    U.setGradient(1.0);
    D.setGradient(1.0);
    // R.setGradient(0.0);
  }

  DoubleType GetR()
  {
    return R;
  }

};

template <typename DoubleType>
int GetInputData(int& N, DoubleType& K)
{
   cout << "Enter steps to expiry N: "; cin >> N;
   cout << "Enter strike price K:    "; cin >> K;
   cout << endl;
   return 0;
}

template <typename DoubleType>
DoubleType PriceByCRR(BinModel<DoubleType> Model, int N, DoubleType K,
               DoubleType (*Payoff)(DoubleType z, DoubleType K))
{
   DoubleType q=Model.RiskNeutProb();
   DoubleType Price[N+1];
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

template <typename DoubleType>
DoubleType CallPayoff(DoubleType z, DoubleType K)
{
   if (z>K) return z-K;
   return 0.0;
}

template <typename DoubleType>
DoubleType PutPayoff(DoubleType z, DoubleType K)
{
   if (z<K) return K-z;
   return 0.0;
}



int main()
{

   using Real = codi::RealForward;

   BinModel<Real> Model;

   //if (Model.GetInputData()==1) return 1;
   Real S0=1, U=0.2, D=0, R=0.03;
   Model.GetInputData(S0, U, D, R);
   Real K;   //strike price
   //U.setGradient(1.0);
   int N;      //steps to expiry
   cout << "Enter call option data:" << endl;
   GetInputData(N,K);
   Real callPrice = PriceByCRR(Model,N,K,CallPayoff);
   cout << "European call option price = "
        << callPrice
        << endl << endl;
   cout << "##########################" << endl;
   cout << "European call option derivative = "
        << callPrice.getGradient()
        << endl << endl;
   
   cout << "##########################" << endl;
   cout << "Enter put option data:" << endl;
   GetInputData(N,K);
   U.setGradient(1.0);
   Real putPrice = PriceByCRR(Model,N,K,CallPayoff);;   
   cout << "European put option price =  "
        << putPrice
        << endl << endl;
   cout << "##########################" << endl;
   cout << "European put option derivative = "
        << putPrice.getGradient()
        << endl << endl;

   return 0;
}
