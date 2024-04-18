#include <stdio.h>
#include <math.h>

#define A 2

int multiplier(){
    int a,b,c, res;
    printf("Enter three integers: ");
    scanf("%d", &a);
    scanf("%d",&b);
    scanf("%d",&c);
    res = a*b*c;
    return res;
}

int squred()
{
    int a;
    printf("Enter an integer: ");
    scanf("%d",&a);
    return a*a;
}

int tilinterrupt()
{
    int ipt;
    printf("give your integer input: ");
    while (ipt<ipt+1){
        scanf("%d",&ipt);
        printf("your number is %d", ipt);
    }
}

int swapping(){
    int a,b,c;
    printf("Enter a first integer: ");
    scanf("%d",&a);
    printf("Enter a second integer: ");
    scanf("%d",&b);
    printf("SWAPPING!\n TADA!\n");
    c = a;
    a = b;
    b = c;
    printf("your numbers are swapped: now %d and %d", a,b);
}

int swappingwo(){
    int a,b;
    printf("Enter a first integer: ");
    scanf("%d",&a);
    printf("Enter a second integer: ");
    scanf("%d",&b);
    printf("SWAPPING!\n TADA!\n");
    a = a^b;
    b = a^b;
    a = a^b;
    printf("your numbers are swapped: now %d and %d", a,b);
}

int main(void)
{
    swappingwo();
    return 0;
}
