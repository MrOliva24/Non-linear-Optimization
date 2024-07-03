#include "func.h"

double f(double x, void* params) {
  (void)(params); /* avoid unused parameter warning */
  //return cos(x) + sin(x);
  return 4*cos(x) + 2*sin(5*x+1);
}

double df(double x, void* params) {
  (void)(params); /* avoid unused parameter warning */
  //return -sin(x) + cos(x);
  return -4*sin(x) + 10*cos(5*x+1);
}

double ddf(double x, void* params) {
  (void)(params); /* avoid unused parameter warning */
  //return -cos(x) - sin(x);
  return -4*cos(x) - 50*sin(5*x+1);
}

// (exercise) Change function to f(x) = 4*cos(x) + 2*sin(5*x+1)

