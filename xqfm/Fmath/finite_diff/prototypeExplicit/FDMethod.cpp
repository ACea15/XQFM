#include "FDMethod.h"
#include "../../../Common/coditype.hpp"

FDMethod::FDMethod(ParabPDE* PtrPDE_, int imax_, int jmax_)
{
   PtrPDE=PtrPDE_;
   imax=imax_; jmax=jmax_;
   dx=(PtrPDE->xu - PtrPDE->xl)/jmax;
   dt=PtrPDE->T/imax;
   V.resize(imax+1);
   for (int i=0; i<=imax; i++) V[i].resize(jmax+1);
}

xdouble FDMethod::v(ti, xj)//xdouble t,xdouble x)
{
  // xdouble i = (t/dt);
  // xdouble j = ((x-PtrPDE->xl)/dx);
  // xdouble l1 = (t-FDMethod::t(i))/dt, l0 = 1.0-l1;
  // xdouble w1 = (x-FDMethod::x(j))/dx, w0 = 1.0-w1;
  xdouble l1 = (t-FDMethod::t(ti))/dt, l0 = 1.0-l1;
  xdouble w1 = (x-FDMethod::x(xj))/dx, w0 = 1.0-w1;
  
  return l1*w1*V[i+1][j+1] + l1*w0*V[i+1][j]
    +l0*w1*V[ i ][j+1] + l0*w0*V[ i ][j];
}
