#ifndef Option_h
#define Option_h

#include "BSModel01.h"

class Option
{
   public:
      xdouble T, zl, zu;
      virtual xdouble Payoff(xdouble z)=0;
      virtual xdouble UpperBdCond
         (BSModel* PtrModel, xdouble t)=0;
      virtual xdouble LowerBdCond
         (BSModel* PtrModel, xdouble t)=0;
};

class Put: public Option
{
   public:
      xdouble K;
      Put(xdouble K_, xdouble T_, xdouble zl_, xdouble zu_)
         {K=K_; T=T_; zl=zl_; zu=zu_;}
      xdouble Payoff(xdouble z);
      xdouble UpperBdCond(BSModel* PtrModel, xdouble t);
      xdouble LowerBdCond(BSModel* PtrModel, xdouble t);
};

#endif
