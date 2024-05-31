#include <stdio.h>

void print_int(int i);

int main()
{
  int a[10] = {1,2,3,4,5,6,7,8,9,10};
  int i = 7;
  int *p = &i;
  p = a;
  printf("1: %d\n", *p);
  print_int(7);
  printf("3: %p\n", a);
  return(0);
}

void print_int(int i)
{
  i = 5;
  printf("2: %d\n", i);
}