#include "func.h"

double f(const gsl_vector* v, void* params) { //Rosenbrock basic function
  double x[5];
  x[0] = gsl_vector_get(v, 0);
  x[1] = gsl_vector_get(v, 1);
  x[2] = gsl_vector_get(v, 2);
  x[3] = gsl_vector_get(v, 3);
  x[4] = gsl_vector_get(v, 4);

  double* p = (double*)params; 
  
  double rosenbrock;
  rosenbrock = 0;

  for (int t = 1; t <= 10; t++) {
    rosenbrock += pow(p[t-1] - (x[0] * exp(-x[1]*t) +x[2] *t*t + x[3]*t + x[4]), 2);
  } 
  return rosenbrock;
}


