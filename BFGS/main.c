#include "main.h"



int main() {
  const char targetNIU[8] = "1668300";
  FILE *f;
  char line[1024];
  if ((f = fopen("mesures.txt", "r")) == NULL) {printf("Unable to access file mesures.txt\n"); return 1;}
  double data[10];
  char NIU[8];

  
  fgets(line, sizeof(line), f); //Se salta el header
  while (!feof(f)) { 
    fscanf(f,"%s", NIU);
    fscanf(f,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9]);

    if (strcmp(NIU, targetNIU) == 0){
      break;
    }
  }
  fclose(f);

  
  int status;
  status = BFGS(data);
  printf("status: %s\n", gsl_strerror(status));
}
