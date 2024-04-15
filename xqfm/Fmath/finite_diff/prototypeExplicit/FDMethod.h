#ifndef FDMethod_h
#define FDMethod_h
#include <vector>
#include "ParabPDE.h"

using namespace std;
typedef vector<xdouble> Vector;

class FDMethod
{
   public:
      ParabPDE* PtrPDE;
      int imax, jmax;
      xdouble dx, dt;

      vector<Vector> V;

      FDMethod(ParabPDE* PtrPDE_, int imax_, int jmax_);

      xdouble t(xdouble i){return dt*i;}
      xdouble x(int j){return PtrPDE->xl+dx*j;}

      xdouble a(xdouble i,int j){return PtrPDE->a(t(i),x(j));}
      xdouble b(xdouble i,int j){return PtrPDE->b(t(i),x(j));}
      xdouble c(xdouble i,int j){return PtrPDE->c(t(i),x(j));}
      xdouble d(xdouble i,int j){return PtrPDE->d(t(i),x(j));}

      xdouble f (int j){return PtrPDE->f(x(j));}
      xdouble fu(int i){return PtrPDE->fu(t(i));}
      xdouble fl(int i){return PtrPDE->fl(t(i));}

      xdouble v(xdouble t,xdouble x);
};

#endif
