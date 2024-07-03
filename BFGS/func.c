#include "func.h"

//Function x[0]^2 (test) 
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



void df(const gsl_vector* v, void* params, gsl_vector* grad) {
    double x[5];
    x[0] = gsl_vector_get(v, 0);
    x[1] = gsl_vector_get(v, 1);
    x[2] = gsl_vector_get(v, 2);
    x[3] = gsl_vector_get(v, 3);
    x[4] = gsl_vector_get(v, 4);

    double* p = (double*) params;

    for (int i = 0; i < 5; ++i) {
        double dv = 0.0;
        for (int t = 1; t <= 10; ++t) {
            // Model calculation at time t
            double exp_term = exp(-x[1] * t);
            double model = x[0] * exp_term + x[2] * pow(t, 2) + x[3] * t + x[4];
            double diff = p[t-1] - model;

            // Determine the derivative based on the current parameter
            switch (i) {
                case 0:
                    dv += 2 * diff * (-exp_term);
                    break;
                case 1:
                    dv += 2 * diff * (x[0] * t * exp_term);
                    break;
                case 2:
                    dv += 2 * diff * (-pow(t, 2));
                    break;
                case 3:
                    dv += 2 * diff * (-t);
                    break;
                case 4:
                    dv += 2 * diff * (-1);
                    break;
            }
        }
        // Set the computed gradient component
        gsl_vector_set(grad, i, dv);
    }
}

void fdf(const gsl_vector* v, void* params, double* f0, gsl_vector *df0){
  *f0 = f(v, params);
  df(v, params, df0);
}


#if 0
void fdf(const gsl_vector* v, void* params, double* f0, gsl_vector *df0){
  *f0 = f(v, params);
  df(v, params, df0);
}
#endif

