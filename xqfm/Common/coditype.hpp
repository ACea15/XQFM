#include "codi.hpp"

#ifdef USE_CODIFORWARD
using xdouble = codi::RealForward;
#elif USE_CODIREVERSE
using xdouble = codi::RealReverse;
#else  // primal / direct / no AD
using xdouble = double;
#endif
