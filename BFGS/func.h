#ifndef _FUNC_H_
#define _FUNC_H_

#include <math.h>
#include <gsl/gsl_multimin.h>
double f(const gsl_vector *v, void* params);
void df(const gsl_vector* v, void* params, gsl_vector* grad);
void fdf(const gsl_vector* v, void* params, double* f0, gsl_vector *df0);
#endif //_FUNC_H_