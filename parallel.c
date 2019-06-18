#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 10000

int count(double x, double y, double *in, double *out)
{
  double dist;
  double local_in = 0.0, local_out = 0.0;
  int j;
  for (j = 0; j < N; j++)
  {
    dist = x * x + y * y;
    if (dist <= 1)
      local_in++;
    else
      local_out++;
  }
  *in += local_in;
  *out += local_out;
  return 0;
}

int main(void)
{
  double in, out;
  double *p_in, *p_out;
  double x, y, pi;
  int i;

  p_in = &in;
  p_out = &out;
  srand(time(NULL));
#pragma omp parallel
  {
#pragma omp single
    {
      double delta = 0.79;
      while (in / (in + out) > delta || in + out == 0)
      {
        for (i = 0; i < N; i++)
        {
#pragma omp task
          {
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;
            count(x, y, p_in, p_out);
          }
        }
      }
    }
  }
  pi = in / (in + out) * 4;
  printf("%f\n", pi);

  return 0;
}
