#include "BSEq.h"
#include "../../../Common/coditype.hpp"
#include <cmath>

BSEq::BSEq(BSModel* PtrModel_,Option* PtrOption_)
{
   PtrModel=PtrModel_; PtrOption=PtrOption_;
   T =PtrOption->T;
   xl=PtrOption->zl;
   xu=PtrOption->zu;
}

xdouble BSEq::a(xdouble t, xdouble z)
{
   return -0.5*pow(PtrModel->sigma*z,2.0);
}

xdouble BSEq::b(xdouble t, xdouble z)
{
   return -PtrModel->r*z;
}

xdouble BSEq::c(xdouble t, xdouble z)
{
   return PtrModel->r;
}

xdouble BSEq::d(xdouble t, xdouble z)
{
   return 0.0;
}

xdouble BSEq::f(xdouble z)
{
   return PtrOption->Payoff(z);
}

xdouble BSEq::fl(xdouble t)
{
   return PtrOption->LowerBdCond(PtrModel,t);
}

xdouble BSEq::fu(xdouble t)
{
   return PtrOption->UpperBdCond(PtrModel,t);
}
