// #include "SimpleMC2.hpp"
#include <iostream>
#include <string>

void print1(std::string name, double& var)
{
  std::cout << "\n Enter " << name << "\n";
  std::cin >> var;
}
  
int main()
{
  double Expiry, Strike, Spot, Vol, r;
  unsigned long NumberOfPaths;
  std::string ExpiryName ("Expiry");
  print1(ExpiryName, Expiry);
  //std::cout << "Expiry: " << Expiry << std::endl;
  return 0;
}
  
  
  
