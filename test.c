
#include <stdio.h>
int main() {
int i = 99;
int *p = &i;
p++;
printf("%d %p %p %d\n", i, &i, ++p, *p);
}
