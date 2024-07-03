#include "NelderMead.h"

int NelderMead(double *data) {
  // Function and derivative:  
  gsl_multimin_function F;
  F.n = 5; //dimension (number of variables) 
  F.f = &f; //function to optimize
  F.params = data; //parameters of the function to optimitze

  double points[5] = {1,0,-1,1,0};
  // Set starting point:
  gsl_vector *x;
  x = gsl_vector_alloc(5);
  gsl_vector_set(x, 0, points[0]);
  gsl_vector_set(x, 1, points[1]);
  gsl_vector_set(x, 2, points[2]);
  gsl_vector_set(x, 3, points[3]);
  gsl_vector_set(x, 4, points[4]);


  // Set initial step sizes (only Nelder-Mead; construction of initial simplex):
  gsl_vector *ss;
  ss = gsl_vector_alloc(5);  // ss = stepSizes
  gsl_vector_set(ss, 0, 1);  // x[0]+ss[0] (second point)
  gsl_vector_set(ss, 1, 1);  // x[1]+ss[1] (third point)
  gsl_vector_set(ss, 2, 1);  // x[2]+ss[2] (fourth point)
  gsl_vector_set(ss, 3, 1);  // x[3]+ss[3] (fifth point)
  gsl_vector_set(ss, 4, 1);  // x[4]+ss[4] (sixth point)


  //initialize minimizer:
  const gsl_multimin_fminimizer_type* T;
  T = gsl_multimin_fminimizer_nmsimplex;
  gsl_multimin_fminimizer* s = NULL;
  s = gsl_multimin_fminimizer_alloc(T, F.n);
  gsl_multimin_fminimizer_set(s, &F, x, ss);
  
  // Iterations control:
  int status;
  int iter = 0;
  int max_iter = 1000;
  double size;
  double tol = 0.0001;
  printf("using %s method\n", gsl_multimin_fminimizer_name(s));
  
  do {
    iter++;
    status = gsl_multimin_fminimizer_iterate(s);

    if(status)
      break;

    size = gsl_multimin_fminimizer_size(s);
    status = gsl_multimin_test_size(size, tol);  //("tol" is the radius of simplex from centroid)
    if(status == GSL_SUCCESS)   // =0 (the simplex size is smaller than the tolerance)
      printf("Converged at iteration: %d\n", iter);
    printf("x= (%10.7f, %10.7f, %10.7f, %10.7f, %10.7f). Objective= %10.7f\n",
           gsl_vector_get(s->x, 0), gsl_vector_get(s->x, 1), gsl_vector_get(s->x, 2), gsl_vector_get(s->x,3), gsl_vector_get(s->x, 4),s->fval);
  } while(status == GSL_CONTINUE && iter < max_iter);  
  if(status == GSL_CONTINUE)  // =-2 (the simplex size is still bigger than the tolerance)
    printf("Maximum iterations reached.\n");

  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free(s);
  return status;
}

/*
### Definition of the types "gsl_multimin_function" and "gsl_multimin_function_fdf":
See manual GSL, chapter "Multidimensional Minimization".
The first for algorithms without derivatives.
The second for algorithms with derivatives, where we have to provide pointers
to both the function and the gradient.
*/