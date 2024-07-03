#include "main.h"

int main() {
  int status;
  double x_min;
  printf("Enter initial guess: ");
  scanf("%lf", &x_min);
  status = newton(x_min);
  printf("status: %d\n", status);
}
