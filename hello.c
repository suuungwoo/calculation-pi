#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  int i;
  int count = 0;
  int max = 1000000;
  double x, y, pi;

  srand(time(NULL));

  for (i = 0; i < max; i++)
  {
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    if (x * x + y * y < 1)
      count++;
  }

  pi = (double)count / max * 4;
  printf("%f\n", pi);

  return 0;
}
