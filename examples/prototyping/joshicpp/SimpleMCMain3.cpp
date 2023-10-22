#include "PayOff2.hpp"
#include "SimpleMC2.hpp"
#include <iostream>

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

int main()
{
  double Expiry, Strike, Spot, Vol, r;
  unsigned long NumberOfPaths;
  std::string ExpiryName("Expiry"), StrikeName("Strike"),
    SpotName("Spot"), VolName("Volatility"), ratesName("Rates"),
    PathsName("NumPaths");
  input1(ExpiryName, Expiry);
  input1(StrikeName, Strike);
  input1(SpotName, Spot);
  input1(VolName, Vol);
  input1(ratesName, r);
  input1(PathsName, NumberOfPaths);
  PayOffCall callPayOff(Strike);
  PayOffPut putPayOff(Strike);  
  double resultCall = SimpleMonteCarlo2(callPayOff, Expiry, Spot, Vol, r, NumberOfPaths);
  double resultPut = SimpleMonteCarlo2(putPayOff, Expiry, Spot, Vol, r, NumberOfPaths);
  std::cout << "the prices are: " << resultCall
	    << " for the call and " << resultPut << " for the put\n";
  return 0;
}
