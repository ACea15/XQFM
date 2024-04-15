#ifndef ParabPDE_h
#define ParabPDE_h
#include "../../../Common/coditype.hpp"

class ParabPDE
{
   public:
      xdouble T,xl,xu;

      virtual xdouble a(xdouble t, xdouble x)=0;
      virtual xdouble b(xdouble t, xdouble x)=0;
      virtual xdouble c(xdouble t, xdouble x)=0;
      virtual xdouble d(xdouble t, xdouble x)=0;

      virtual xdouble f(xdouble x)=0;
      virtual xdouble fu(xdouble t)=0;
      virtual xdouble fl(xdouble t)=0;
};

#endif
