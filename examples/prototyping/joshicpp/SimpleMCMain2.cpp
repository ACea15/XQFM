// #include "SimpleMC2.hpp"
#include "SimpleMC.hpp"
#include <iostream>
#include <string>

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

  return 0;
}
  
  
  
