#include "BFGS.h"

int BFGS(double * data) {
  // Function and derivative:  
  gsl_multimin_function_fdf F;
  F.n = 5; //dimension (number of variables) 
  F.f = &f; //function to optimize
  F.df = &df; //gradient of function
  F.fdf = &fdf; //call to function and gradient together. Not recommended.
  F.params = data; //parameters of the function to optimitze
  double tol = 1e-3;
  double ss = 1e-2;
  // Set starting point f1:

  double points[5] = {1,0,-1,1,0}; 

  gsl_vector *x;
  x = gsl_vector_alloc(5);
  gsl_vector_set(x, 0, points[0]);
  gsl_vector_set(x, 1, points[1]);
  gsl_vector_set(x, 2, points[2]);
  gsl_vector_set(x, 3, points[3]);
  gsl_vector_set(x, 4, points[4]);

  
  //initialize minimizer:
  const gsl_multimin_fdfminimizer_type* T;
  T = gsl_multimin_fdfminimizer_vector_bfgs;
  gsl_multimin_fdfminimizer* s = NULL;
  s = gsl_multimin_fdfminimizer_alloc(T, F.n);
  gsl_multimin_fdfminimizer_set(s, &F, x, ss, tol); 
    // where ss is the initial step-size for line search, and 
    // tol is a final tolerance for the line search (see manual)
  
  // Iterations control:
  // ...
  int status, iter = 0, max_iter = 1000;
  double epsabs = 1e-3 ;
  printf("using %s method\n, epsabs = %0.10f, tol = %0.10f\n", gsl_multimin_fdfminimizer_name(s), epsabs, tol);
  
  do {
    iter++;
    status = gsl_multimin_fdfminimizer_iterate(s);
    if (status) {
      break;
    }
    status = gsl_multimin_test_gradient(s->gradient, epsabs); 
    if (status == GSL_SUCCESS){
      printf("Converged! at iteration %d\n", iter);
    }
    printf("x = (%10.7f, %10.7f, %10.7f, %10.7f, %10.7f). Objective = %10.7f\n", 
           gsl_vector_get(s->x, 0), gsl_vector_get(s->x, 1), 
           gsl_vector_get(s->x, 2), gsl_vector_get(s->x, 3), 
           gsl_vector_get(s->x, 4), s->f);
  } while(status == GSL_CONTINUE && iter < max_iter);
  if (status == GSL_CONTINUE) {
    printf("Maximum iterations reached\n");
  }
  gsl_vector_free(x);
  gsl_multimin_fdfminimizer_free(s);
  return status;
}

/*
### Definition of the types "gsl_multimin_function_f" and "gsl_multimin_function_fdf":
See manual: https://www.gnu.org/software/gsl/doc/html/multimin.html
The first for algorithms without derivatives.
The second for algorithms with derivatives, where we have to provide pointers
to both the function and the gradient.
*/

/* 
- Please print epsabs and tol used after the name of the method.
- You can use bfgs or bfgs2. You may print some comment at the end 
  if you have tried other methods (see manual).
  */