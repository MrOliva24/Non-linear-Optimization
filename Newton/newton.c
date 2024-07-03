#include "newton.h"

int newton(double x_min) {
  struct Function {
    double (*f)(double x, void* params);
    double (*df)(double x, void* params);
    double (*ddf)(double x, void* params);
    void* params;
  };
  struct Function F;
  F.f = &f;
  F.df = &df;
  F.ddf = &ddf;
  F.params = NULL;

  // double x_min = 3; /* initial guess */
  // double x_lower = 0.0, x_upper = 6.0; /* initial interval, not used */
  // (exercise) make initial guess an input of the user, collected in
  // function main() and passed as argument to function newton()

  int status = 0;
  int iter = 0;
  int max_iter = 10;
  // double epsabs = 0.001;  /* not used */
  // double epsrel = 0; /* not used */

  
  printf("using Newton method\n");
  printf("%5s %10s \n", "iter", "min");
  printf("%5d %.8f \n", iter, x_min);

  do {
    iter++;
    double x_min_old = x_min;
    x_min = x_min_old - F.df(x_min, F.params) / F.ddf(x_min, F.params);  // could be extracted to a function Newton_iteration();

    // (exercise) compare consecutives values of x_min and raise a flag if difference is < 10^(-12)
    // and in that case print "Converged" and finish the iterations
    if (fabs(x_min - x_min_old) < 1e-12) {
      printf("Converged in iteration %d\n", iter); 
      break;
    }
    // (exercise) compare consecutive function values and raise a flag if difference is < 10^(-12),
    // and in that case also print "Converged" and finish the iterations
    // if(difference small)
    // printf("Converged:\n");
    if (fabs (F.f(x_min, F.params) - F.f(x_min_old, F.params)) < 1e-12) {
      printf("Converged in iteration %d\n", iter); 
      break;
    }
    // (exercise) If the second derivative is negative, stop the iterations,
    // print an informative message and change status to 1
    if (F.ddf(x_min, F.params) < 0) {
      printf("Second derivative is negative\n");
      status = 1;
      break;
    }

    
    // (exercise) add the value of the function at every iteration to this printf
    printf("%5d | %.15f | %.15f \n", iter, x_min, F.f(x_min, F.params));

  } while(iter < max_iter);
  
  // (exercise) if maximum iterations are reached, print an informative message
  // and change status to 2
  if (iter >= max_iter) {
    printf("Maximum iterations reached\n");
    status = 2;
  }

  return status;
}
