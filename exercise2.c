#include <stdio.h>
#include <limits.h>


//-------------------- Lecture 2 --------------------
int type_casting()
{
    int i=i, j=4, k=3;
    printf("i/j=%d\n",i/j);
    printf("i/k=%d\n", i/k); // integer를 연산하면, 답 또한 integer로 나온다. 

    float res = (float)i/k; // float로 형변환을 해주면, 정수형으로 나오는 것을 방지할 수 있다.
    printf ("i / k = %f\n", res ); // %f는 float형을 출력할 때 사용하는 포맷이다.
    res = i / ( float ) k; // (float)i는 i를 float로 미리 변환해 결과를 float로 출력한다.
    printf ("i / k = %f\n", res ); // 형변환을 안하면, 예를들어 3/4는 0.75가 나와야 하지만, 0이 나온다.

    res = ( float ) (i / k); // i/k를 먼저 계산하고, 그 결과를 float로 변환한다.
    printf ("i / k = %f\n", res ); // 이는 결국 integer로 계산된 결과를 나중에 float로 바꾸는거라 역시 그냥 2다.
}

int testing_forloop(){
    int i;
    for (i=0; i<10; i++){
        printf("i=%d\n",i);
    }
    printf("i=%d\n",i);
    // for문이 끝나고 나면, i는 10이 된다.
    // for문에서 선언된 변수는 for문이 끝나도 유효하다.
    // 이는 for문이 끝나도 i가 유효하다는 것을 의미한다.
}

int testing_whileloop(){

    // Single statement
    int i=0;
    while (i<10){
        printf("i=%d\n",i);
        i++;
    }
    printf("i=%d\n",i);
    // while문이 끝나고 나면, i는 10이 된다.
    // while문에서 선언된 변수는 while문이 끝나도 유효하다.
    // 이는 while문이 끝나도 i가 유효하다는 것을 의미한다.

    // Block of statement
    int j=0;
    while (j<10){
        printf("j=%d\n",j);
        j++;
    }
    return (0);
}

int another_whileloop()
{
    int c;
    c= getchar();
    while(c!=EOF){ // EOF는 End Of File의 약자로, 파일의 끝을 나타내는 값이다.
        putchar(c); // getchar()로 입력받은 값을 출력한다.
        c = getchar(); //    다음 문자를 입력받는다.
    }
    
    return (0);
}


int testing_dowhileloop()
{
    int i=0;
    do{
        printf("i=%d\n",i);
        i++;
    }while(i<10);
    printf("i=%d\n",i);
    // do-while문은 while문과 다르게, 먼저 한번 실행하고 조건을 검사한다.
    // 따라서, i=10이 되어도 한번은 실행된다.
}

int pointers(){
    // initialize a variable i
    int i = 99;
    // set pointer to variable i 
    int *pointer_i = &i;

    // i and *pointer_i refer to value
    printf("i is %d, *pointer_i is %d\n", i, *pointer_i);
    // &i and pointer_i refer to address
    printf("%p, %p\n", &i, pointer_i);
}

int testing_array(){

    int a[10]; // 배열의 크기를 10으로 선언한다.
    // 배열의 크기는 변경할 수 없다.
    // 배열의 크기를 변경하려면, 새로운 배열을 만들어야 한다.

    a[0]=1;

    printf("a[0]=%d\n",a[0]);
    return (0);
}

//---------------------- Exercise 2 ----------------------

// 2.1.1 Integer data type ranges

int minmax()
{
    // Write a program to get the minimum and maximum values for signed and unsigned char, short, int and long data types on your system
    // Hint: Use the limits.h header file

    printf("Minimum value of signed char: %d\n", SCHAR_MIN); 
    // SCHAR_MIN은 signed char의 최소값을 나타낸다.
    printf("Maximum value of signed char: %d\n", SCHAR_MAX);
    printf("Minimum value of unsigned char: %d\n", 0);
    printf("Maximum value of unsigned char: %d\n", UCHAR_MAX);

    printf("Minimum value of signed short: %d\n", SHRT_MIN); 
    // SHRT_MIN은 signed short의 최소값을 나타낸다.
    printf("Maximum value of signed short: %d\n", SHRT_MAX);
    printf("Minimum value of unsigned short: %d\n", 0);
    printf("Maximum value of unsigned short: %d\n", USHRT_MAX);

    printf("Minimum value of signed int: %d\n", INT_MIN); 
    printf("Maximum value of signed int: %d\n", INT_MAX);
    printf("Minimum value of unsigned int: %d\n", 0);
    printf("Maximum value of unsigned int: %u\n", UINT_MAX);

    printf("Minimum value of signed long: %ld\n", LONG_MIN);
    printf("Maximum value of signed long: %ld\n", LONG_MAX);
    printf("Minimum value of unsigned long: %d\n", 0);
    printf("Maximum value of unsigned long: %lu\n", ULONG_MAX);

}

int getsize()
{
    // Write a program to get the size of the following data types on your system: char, short, int, long, float, double, long double
    // Hint: Use the sizeof operator

    printf("Size of the unsigned char data type: %lu\n", sizeof(char)); 
    // %lu는 unsigned long을 출력할 때 사용하는 포맷이다.
    // sizeof()의 결과는 unsigned long이기 때문에, %lu를 사용한다.
    printf("Size of the signed char data type: %lu\n", sizeof(char));
    
    printf("Size of the unsigned short data type: %lu\n", sizeof(short)); 
    printf("Size of the signed short data type: %lu\n", sizeof(short)); 
    
    printf("Size of the unsigned int data type: %lu\n", sizeof(int));
    printf("Size of the signed int data type: %lu\n", sizeof(int));

    printf("Size of the unsigned long data type: %lu\n", sizeof(long));
    printf("Size of the signed long data type: %lu\n", sizeof(long));
    
    // C 표준에서는 signed char와 unsigned char 모두 최소한 1 바이트(8 비트)여야 한다고 명시하고 있다. 
    // signed와 unsigned는 데이터 타입이 어떤 값을 가질 수 있는지를 결정하지만, 그 크기는 동일합니다. 예를 들어, char는 1바이트, short는 2바이트, int는 4바이트를 차지한다. 
    // unsigned는 음수를 표현할 수 없으므로 그 범위는 0부터 시작하지만, signed는 음수와 양수를 모두 표현할 수 있다. 
    // 따라서 signed와 unsigned의 차이는 값의 범위에 있지, 메모리에서 차지하는 공간에는 없습니다.

}

int cal_max()
{
    // How can you calculate the maximum value once you have the size?
    // Hint: Use the limits.h header file

    printf("Maximum value of unsigned char: %d\n", UCHAR_MAX);
    // 위의 minmax와 기본적으로 같은 내용이다.
}

// 2.1.2 Numerical storage of characters

int letter_to_num()
{
    // Write a program that asks for a letter and gives back its numerical representation
    // Modify the program to print out the letter and its numerical representation.

    char letter;
    printf("Enter a letter: ");
    scanf("%c", &letter); // %c는 char형을 입력받을 때 사용하는 포맷이다.
    printf("The numerical representation of the letter %c is %d\n", letter, letter);

    return (0);

}

// 2.2 Control constructs

// 2.2.1 Printing out numbers

int print_nums()
{
    // Write a program that prints out the numbers from 1 to 100
    // Hint: Use a for loop

    int i;
    for (i=1; i<=100; i++){
        printf("%d, ", i);
        if (i%10==0){
            printf("\n");
        }
    }
    return (0);
}

// 2.2.2 Sum of integers

int sum_nums()
{
    // Write o program asking for integers and summing them up until you enter 0
    int sum=0, enter;
    do{
        printf("now sum is: %d\n", sum);
        printf("Enter an integer: ");
        scanf("%d", &enter);
        sum += enter;
    } while (enter != 0);
    return sum;
}

// 2.2.3 Optimal data type

int optdata()
{
    // Write a program to calculate the optimal data type (in terms of storage efficiency) for a given integer.
    // Hint: Use the limits.h header file

    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    if (num >= CHAR_MIN && num <= CHAR_MAX){
        printf("The optimal data type for %d is char\n", num);
    }
    else if (num >= SHRT_MIN && num <= SHRT_MAX){
        printf("The optimal data type for %d is short\n", num);
    }
    else if (num >= INT_MIN && num <= INT_MAX){
        printf("The optimal data type for %d is int\n", num);
    }
    else if (num >= LONG_MIN && num <= LONG_MAX){
        printf("The optimal data type for %d is long\n", num);
    }
    else{
        printf("The optimal data type for %d is long long\n", num);
    }

}

int main(void)
{

    minmax();
    return 0;
}