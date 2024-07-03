#include "main.h"

int main() {
  int status;
  double xmin;
  printf("Enter initial guess: ");
  scanf("%lf", &xmin);
  status = goldenSection(xmin);
  printf("status: %s\n", gsl_strerror(status));
}
