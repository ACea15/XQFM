#ifndef BSEq_h
#define BSEq_h

#include "ParabPDE.h"
#include "BSModel01.h"
#include "Option.h"

class BSEq: public ParabPDE
{
   public:
      BSModel* PtrModel;
      Option* PtrOption;
      BSEq(BSModel* PtrModel_,Option* PtrOption_);

      xdouble a(xdouble t, xdouble z);
      xdouble b(xdouble t, xdouble z);
      xdouble c(xdouble t, xdouble z);
      xdouble d(xdouble t, xdouble z);

      xdouble f(xdouble z);
      xdouble fl(xdouble t);
      xdouble fu(xdouble t);
};

#endif
