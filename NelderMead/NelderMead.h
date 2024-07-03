#ifndef _NELDERMEAD_H_
#define _NELDERMEAD_H_

#include <gsl/gsl_errno.h>
#include <gsl/gsl_multimin.h>
#include <stdio.h>
#include "func.h"
int NelderMead(double *data);

#endif //_NELDERMEAD_H_