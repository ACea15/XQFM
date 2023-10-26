#include "PayOff2.hpp"
#include "SimpleMC2.hpp"
#include <iostream>
#include <ostream>

void input1(std::string name, double& var)
{
  std::cout << "\n Enter " << name << "\n";
  std::cin >> var;
}

void input1(std::string name, unsigned long& var)
{
  std::cout << "\n Enter " << name << "\n";
  std::cin >> var;
}

void input1(std::string name, int& var)
{
  std::cout << "\n Enter " << name << "\n";
  std::cin >> var;
}

int main()
{
  double Expiry, Strike, Spot, Vol, r;
  unsigned long NumberOfPaths;
  int optionType;
  std::string ExpiryName("Expiry"), StrikeName("Strike"),
    SpotName("Spot"), VolName("Volatility"), ratesName("Rates"),
    PathsName("NumPaths"), optionTypeName("optionType");
  input1(ExpiryName, Expiry);
  input1(StrikeName, Strike);
  input1(SpotName, Spot);
  input1(VolName, Vol);
  input1(ratesName, r);
  input1(PathsName, NumberOfPaths);
  input1(optionTypeName, optionType);
  // Expiry=1.;
  // Strike=10.;
  // Spot=9.;
  // Vol=0.3;
  // r=0.01;
  // NumberOfPaths=10000;
  // optionType=1;
  PayOff* thePayOffPtr;
  if (optionType==0)
    {
    std::cout<<"call\n";
    thePayOffPtr = new PayOffCall(Strike);
    }
  else
    {
    std::cout<<"put\n";
    thePayOffPtr = new PayOffPut(Strike);
    }
  // PayOffCall callPayOff(Strike);
  // PayOffPut putPayOff(Strike);  
  // double resultCall = SimpleMonteCarlo2(callPayOff, Expiry, Spot, Vol, r, NumberOfPaths);
  // double resultPut = SimpleMonteCarlo2(putPayOff, Expiry, Spot, Vol, r, NumberOfPaths);
  double result = SimpleMonteCarlo2(*thePayOffPtr, Expiry, Spot, Vol, r, NumberOfPaths);
  std::cout << "the prices are: " << result << std::endl;
  delete thePayOffPtr;
  // std::cout << "the prices are: " << resultCall << " for the call and " << resultPut << " for the put\n";
  return 0;
}
