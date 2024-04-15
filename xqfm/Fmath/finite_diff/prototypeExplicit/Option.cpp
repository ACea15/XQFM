#include "Option.h"
#include "../../../Common/coditype.hpp"
#include <cmath>

xdouble Put::Payoff(xdouble z)
{
   if (K<z) return 0.0;
   return K-z;
}

xdouble Put::UpperBdCond(BSModel* PtrModel, xdouble t)
{
   return 0.0;
}

xdouble Put::LowerBdCond(BSModel* PtrModel, xdouble t)
{
   return K*exp(-PtrModel->r*(T-t));
}
