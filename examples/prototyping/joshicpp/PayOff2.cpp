#include "PayOff2.hpp"
#include <algorithm>

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_){}
double PayOffCall::operator ()(double Spot) const {
  return std::max(Spot-Strike,0.0)  ;
}
PayOffCall::PayOffPut(double Strike_) : Strike(Strike_){}
PayOffCall::PayOffCall(double Strike_) : Strike(Strike_){}
double PayOffPut::operator ()(double Spot) const {
  return std::max(Strike-Spot,0.0);
}
