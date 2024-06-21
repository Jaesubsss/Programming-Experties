#include <stdio.h>



int main (int argc,char * argv[]) {

    int a = 10; // 정수형 변수 a 선언 및 초기화
    int *p = &a; // 포인터 p 선언 및 초기화, a의 주소를 저장    

    printf("%i %i %i\n",a, p, &a);

    return(0);

}

 