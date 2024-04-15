#ifndef ExplicitMethod_h
#define ExplicitMethod_h

#include "FDMethod.h"

class ExplicitMethod: public FDMethod
{
   public:
      ExplicitMethod(ParabPDE* PtrPDE_, int imax_, int jmax_)
         : FDMethod(PtrPDE_, imax_, jmax_) {}

      xdouble A(int i, int j)
             {return dt*(b(i,j)/2.0-a(i,j)/dx)/dx;}
      xdouble B(int i, int j)
             {return 1.0-dt*c(i,j)+2.0*dt*a(i,j)/(dx*dx);}
      xdouble C(int i, int j)
             {return -dt*(b(i,j)/2.0+a(i,j)/dx)/dx;}
      xdouble D(int i, int j)
             {return -dt*d(i,j);}

      void SolvePDE();
};

#endif
