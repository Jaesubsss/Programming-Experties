- [C - Boring part](#c---boring-part)
  - [Basic](#basic)
    - [return 0 vs return 1](#return-0-vs-return-1)
    - [printf();](#printf)
    - [scanf();](#scanf)
  - [Data types and control constructs](#data-types-and-control-constructs)
    - [Size of data type](#size-of-data-type)
    - [형변환](#형변환)
    - [반복문](#반복문)
    - [String](#string)
    - [Pointer](#pointer)
  - [Function](#function)
    - [local vs global](#local-vs-global)
      - [local](#local)
      - [global](#global)
    - [static vs automatic](#static-vs-automatic)
  - [Array and Pointers](#array-and-pointers)
    - [Array](#array)
      - [Multidimensional arrays](#multidimensional-arrays)
      - [Pointers](#pointers)
  - [Pointers, Trees, Linked Lists](#pointers-trees-linked-lists)
      - [Pointer arithmetics](#pointer-arithmetics)
      - [melloc()](#melloc)
      - [struct name{}](#struct-name)
      - [typedef](#typedef)
- [Lecture 1](#lecture-1)
  - [Identifier](#identifier)
  - [Basic data types](#basic-data-types)
    - [local and global](#local-and-global)
    - [const](#const)
  - [Operator](#operator)
  - [Data Container](#data-container)
  - [Storage classes](#storage-classes)
  - [Templates](#templates)
  - [Calling function](#calling-function)
  - [Math functions](#math-functions)
  - [random number](#random-number)
- [Lecture 2](#lecture-2)
  - [Inline function](#inline-function)
  - [Recursion vs Iteration](#recursion-vs-iteration)
  - [Pointers and References](#pointers-and-references)
    - [how to return more than one value/item?](#how-to-return-more-than-one-valueitem)
    - [Call by](#call-by)
      - [Pointer and Reference?](#pointer-and-reference)
  - [Const keyword](#const-keyword)
  - [Function overloading](#function-overloading)
  - [Polymorphic functions with templates](#polymorphic-functions-with-templates)
  - [Lambda Functions](#lambda-functions)
  - [Container](#container)
    - [Array](#array-1)
    - [Which container?](#which-container)
      - [Vector](#vector)
      - [map](#map)
  - [Structure and Classes](#structure-and-classes)
    - [Struct](#struct)
    - [Class](#class)
      - [Getter, Setter](#getter-setter)
    - [Constructor](#constructor)
      - [Initialization list](#initialization-list)
- [Lecture 3](#lecture-3)
  - [Memorization](#memorization)
  - [Destructor](#destructor)
  - [Static members](#static-members)
  - [Const member function](#const-member-function)
  - [C++ std::string](#c-stdstring)
  - [Input, Output and File](#input-output-and-file)
    - [Opening a file](#opening-a-file)
      - [Openmode](#openmode)
    - [Stringstream](#stringstream)
    - [Filesystem](#filesystem)
      - [Preprocessor](#preprocessor)
    - [Traversing a directory](#traversing-a-directory)
    - [Get home directory](#get-home-directory)
    - [Formatted Output](#formatted-output)
- [Lecture 4](#lecture-4)
  - [Inheritance](#inheritance)
    - [Base Class Constructor](#base-class-constructor)
    - [Composition](#composition)
    - [Multiple Inharitance](#multiple-inharitance)
    - [Abstract Class](#abstract-class)
    - [Mixin](#mixin)
    - [Virtual Functions](#virtual-functions)
      - [Using Pointer and Reference](#using-pointer-and-reference)
      - [Using Template and Auto](#using-template-and-auto)
  - [Stylistic rules](#stylistic-rules)
  - [Regex](#regex)
    - [regex functions](#regex-functions)
    - [Command Line Options](#command-line-options)
      - [argc](#argc)
      - [argv](#argv)
      - [argparse](#argparse)
      - [Popl - Program Options Parser Library](#popl---program-options-parser-library)
      - [flags.h](#flagsh)
      - [Structopt](#structopt)
- [Lecture 5](#lecture-5)
  - [Friends Function](#friends-function)
  - [Copy Constructor](#copy-constructor)
  - [This pointer](#this-pointer)
  - [Operator overloading](#operator-overloading)
  - [Namespace](#namespace)
    - [Nested namespace](#nested-namespace)
  - [Function Template](#function-template)
  - [Class Template](#class-template)
  - [Standard Template Library (STL)](#standard-template-library-stl)
    - [Set vs Vector vs Map](#set-vs-vector-vs-map)
    - [Pair and Tuple](#pair-and-tuple)
- [Lecture 6](#lecture-6)
  - [Exception](#exception)
    - [Dynamic memory](#dynamic-memory)
    - [Smart Pointer](#smart-pointer)

# C - Boring part

## Basic

### return 0 vs return 1

C와 C++에서 return 0과 return 1은 함수가 종료될 때 반환하는 값에 차이를 두는 구문이다. 특히, 메인 함수(main 함수)에서 주로 사용되며, 그 값은 프로그램의 종료 상태를 나타낸다.

1. return 0

   * 성공적인 종료를 의미한다.
   * 대부분의 운영 체제는 0을 성공적인 프로그램 실행을 나타내는 값으로 해석한다.
   * 따라서 return 0;을 하면 프로그램이 정상적으로 종료되었음을 의미한다.

2. return 1 (또는 다른 비 0 값)

   * 오류 또는 비정상적인 종료를 의미한다.
   * 비 0 값을 반환하면, 일반적으로 프로그램이 오류가 발생했거나 비정상적으로 종료되었음을 나타낸다.
   * 관례적으로 1은 일반적인 오류를 나타내는 경우가 많지만, 1 외에도 다양한 값이 상황에 맞게 사용될 수 있다. 예를 들어, 특정 오류에 대해 다른 값을 반환할 수 있다.

### printf();

`print`로 대표적으로 사용되는 녀석인데, 사용이 좀 독특하다. 출력할 문자열 내에 형식 지정자를 끼워넣고, 문자열 외부에서 그 형식 지정자에 들어갈 변수를 순서대로 넣어준다. 

```c
int a = 10;
float b = 3.14;
char c = 'A';

printf("정수: %d, 실수: %f, 문자: %c\n", a, b, c);
// 출력: 정수: 10, 실수: 3.140000, 문자: A
```
형식 지정자는 다음과 같다.

* `%d`: 정수형(`int`)
* `%f`: 실수형(`float, double`)
* `%c`: 문자형(`char`)
* `%s`: 문자열(`char *`)
* `%x`, `%X`: 16진수 출력
* `%o`: 8진수 출력
* `%%`: % 문자 출력

### scanf();

뭔가 입력을 받을 때 사용되는 함수로써, 일반적인 사용법은 `printf()`와 같다. 

```c
int a;
float b;
char c;

scanf("%d %f %c", &a, &b, &c);
```
형식지정자에 따라, 상응하는 데이터형에 따른 입력을 받는다. 


## Data types and control constructs

### Size of data type

|Type|Bytes| Minimum range|
|:-|:-:|:-|
|char|1| [-128, +127]|
|unsigned char| 1| [0, 255]
|short |2| [-32,768, +32,767]|
|unsigned short |2| |[0, 65,535]|
|int |2 |[-32,768, +32,767]|
|unsigned int |2 |[0, 65,535]|
|long |4 |[-2,147,483,647, +2,147,483,647]|
|unsigned long |4 |[0, 4,294,967,295]|
|long long |8 |[-9,223,372,036,854,775,808, +9,223,372,036,854,775,807]|
|unsigned long long |8 |[0, 18,446,744,073,709,551,615]|

long long > long > int > short > char

### 형변환

어떤 데이터의 형을 변환하고싶다면 앞에 `(data type)`를 사용하면 된다.

```c
float res = ( float ) i / k;
```

### 반복문

for loop의 형태가 꽤나 헷갈린다.

```c
for (i =0; i <=10; i=i +1){}
```
이런 형태이다.

while의 형태는 별로 다르지 않다. 

```c
while (조건문) {}
```

do while loop도 자주 쓰이니 알아두자.

```c
int j = 0;
do {
    printf("j=%d\n", j++);
} while (j < 10);
```

### String

String은 Character의 배열이다. 이 경우, 배열의 마지막엔 항상 문장의 끝을 의미하는 "널 문자" `'\0'`이 들어가야 한다.


```c
#include <stdio.h>

int main() {
    char a[23] = {'P', 'o', 't', 't', 's', 'd', 'a', 'm', '\0'};
    
    printf("%s\n", a);    // 1. 문자열 전체 출력
    printf("%c\n", a[0]); // 2. 첫 번째 문자 출력
    printf("%d\n", a[0]); // 3. 첫 번째 문자의 ASCII 값 출력, 80
    printf("%d\n", a[7]); // 4. 7번째 문자의 ASCII 값 (널 문자) 출력, 0

    return 0;
}
```
`%d`는 정수형을 의미하는 형식 지정자로써, 이것으로 호출하면 아스키값을 출력한다. 


### Pointer

매우 중요한 개념이고, 매우 헷갈리는 개념이다. 

포인터는 메모리 주소를 저장하는 변수이다. 일반 변수는 값을 저장하지만, 포인터는 **값이 저장된 메모리 주소**를 저장한다. 

포인터는 다음과 같이 선언될 수 있다.

```c
int i = 99;
int *pointer_i = &i;
```
이때, `*pointer_i`는 포인터로써 선언이 되는데, 이 주소값을 주소연산자 `&`를 통해, `i`의 주소를 포인터에 할당해 주는 것이다. 

포인터를 이용해 값을 참조할 수 있다.

```c
printf("i is %d, *pointer_i is %d\n", i, *pointer_i);
```
이때 `i`는 변수 i의 값을 가져와 99를 출력한다.

`*pointer_i`는 해당 변수가 가리키는 주소에 있는 값을 가져와 출력한다. 따라서, 똑같이 99를 출력한다. 

자! 이제 여기서 중요한 포인트이다. `*`연산자가 붙으면 그 주소의 값을 참조하는건데, 얘가 없으면 어떻게 될까?

```c
printf("%p, %p\n", &i, pointer_i);
```
먼저, `&i`는 주소연산자 `&`를 통해, 변수 i의 주소를 가져온다.

그리고, `pointer_i`는 변수 i의 주소를 저장한 포인터이므로, 변수 i가 저장된 주소를 가져온다. 

따라서, 두 값은 동일한 메모리 주소를 출력한다. (예: `0x7ffee6a09a8c`)

## Function

C 언어에서 함수는 다음과 같은 세 가지 구성 요소로 이루어져 있다:

* 반환형 (Return Type): 함수가 반환하는 값의 데이터 타입.
* 함수 이름 (Function Name): 함수를 호출할 때 사용하는 이름.
* 매개변수 (Parameters): 함수가 입력받는 데이터(인자).
* 함수 본체 (Function Body): 함수가 수행할 작업을 정의하는 코드.

```c
반환형 함수이름(매개변수 목록) {
    // 함수 본체 (실제 코드 실행 부분)
    return 반환값;  // 반환형이 void인 경우에는 return을 생략할 수 있음
}
```
```c
#include <stdio.h>

// 함수 선언 (프로토타입)
int add(int a, int b);

// main 함수 (프로그램의 시작점)
int main() {
    int result = add(5, 3);  // add 함수 호출
    printf("Result: %d\n", result);
    return 0;
}

// 함수 정의
int add(int a, int b) {
    return a + b;  // a와 b를 더한 값을 반환
}
```

### local vs global

#### local

local variable은 코드블록 내부에서 선언된 변수이다. 이 변수는 변수가 선언된 블록 내에서만 접근이 가능하다.

로컬은 또한 선언된 함수가 호출될 때 생성되고, 함수가 종료되면 메모리에서 사라진다. 

그러나, 이 로컬 변수는 자동으로 초기화 되지 않으므로, 반드시 명시적으로 초기화해야한다. 그렇지 않은 경우 garbage value가 들어갈 수 있다.

```c
#include <stdio.h>

void myFunction() {
    int localVar = 10;  // 지역 변수
    printf("localVar: %d\n", localVar);  // 지역 변수를 사용할 수 있음
}

int main() {
    myFunction();  // 함수 호출
    // printf("%d", localVar);  // 오류! localVar는 myFunction() 내부에서만 접근 가능
    return 0;
}
```

#### global

global variable은 모든 함수 외부에서 선언된 변수이다. 선언된 지점에서 프로그램 전체에서 접근할 수 있으며, 모두 공유되는 변수이다. 

이는 프로그램이 시작될 때 생성되고, 프로그램이 종료될 때 까지 유지된다. 

글로벌은 자동으로 초기화되며, 기본적으로 0으로 초기화된다.

```c
#include <stdio.h>

int globalVar = 100;  // 전역 변수

void myFunction() {
    printf("globalVar in myFunction: %d\n", globalVar);  // 전역 변수 사용 가능
}

int main() {
    printf("globalVar in main: %d\n", globalVar);  // 전역 변수 사용 가능
    myFunction();  // 함수 호출
    return 0;
}
```

### static vs automatic

`static` 키워드는 변수가 선언된 위치와 관계없이 변수의 생명 주기를 프로그램의 전체 실행 시간으로 확장시킨다. 즉, `static` 변수는 한 번 초기화되면 프로그램이 종료될 때까지 메모리에서 유지된다.

`local static` 변수는 함수 내부에서 선언되어도 그 유효 범위는 해당 함수 내에만 한정된다. 하지만 해당 함수가 여러 번 호출되어도 초기화는 단 한 번만 이루어진다.

`global static` 변수는 파일 내에서만 유효하며, 다른 파일에서 접근할 수 없다. 이를 통해 외부에서 접근할 수 없도록 파일 범위의 은닉성을 제공한다.

`automatic` 은 디폴트 값이며, 기본적으로 local 변수이다. 함수나 블록이 호출되거나 실행될 때 자동으로 생성되고, 종료될 때 소멸된다.

## Array and Pointers

### Array

모두 같은 데이터타입을 공유하는 storage locations의 모임이다. 

```c
int main(){
    int a[10];
    a[0] = 1;
    printf("%d\n", a[0]);
    return(0);
}
```
요러면 1이 나오겠죠? 처음에 `a[10]`은 크기를 명시한 것이다. array는 처음 선언할 때 크기를 같이 선언해주어야 하고, 이는 변경될 수 없다. 

```c
#include <stdio.h>

int main() {
    int points[31], count;

    // 1. 점수 입력
    for(count = 0; count < 31; count++) {
        printf("Enter smiley points for May %d: ", count + 1);
        scanf("%d", &points[count]);
    }

    // 2. 점수 출력
    for(count = 0; count < 31; count++) {
        printf("Smiley points for May %d: %d\n", count + 1, points[count]);
    }

    return 0;
}
```

이때, 중요한 부분이 `scanf("%d", &points[count]);` 이부분이다. 

`&points[count]`는 `points` array에서 `count`번째 요소의 주소를 가리킨다. 즉, 입력된 point는 저부분에 저장이 되는 것이다. 

또한 출력부분에서 `points[count]`는 `count`번째에 저장된 요소를 출력하라는 것이다. 

#### Multidimensional arrays

```c
int main(){
    int table[2][5] = {1,2,3,4,5,6,7,8,9,10};
    printf("%d\n", table [1][2]); // 8
    return(0);
}
```
요롷게 표를 만들 수 있따.

#### Pointers

```c
typename variablename = value ;
typename * pointername ;
pointername = & variablename ;
```

- `*`: indirection operator
- `&`: address of

변수의 값에는 어떻게 접근할까? 

변수의 이름을 직접 호출하여, 값에 직접적으로 접근할 수 있다. 

또는, `*pointername`를 통해 간접적으로 변수에 접근할 수 있다.

포인터를 선언할 때 중요한 점은 `*`의 위치이다. 보통같으면 딱히 문제가 없는데, 한번에 여러개를 선언할때는 구분이 필요하다.

```c
int *p, i;
int* p1, p2;
```

여기서보면, `i`는 일반 변수이다. 그러나, `p1`과 `p2`는 모두 포인터이다. 

array의 사이즈를 보려면, 다음과 같이 사용할 수 있다.

```c
printf("Size of int:%zu\n",sizeof(int));
```

포인터를 통해 어떤 배열을 가리킬 수 있다. 

```c
#include <stdio.h>
#define MAX 13

int a[MAX] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};  // 크기가 13인 배열 초기화
int *pointer_a, count;  // 정수형 포인터와 반복 제어 변수 선언

int main() {
    pointer_a = a;  // 포인터가 배열 a의 첫 번째 요소를 가리키도록 설정

    printf("Index\tValue\tAddress\n");  // 헤더 출력

    // 배열 요소와 그 주소를 출력하는 for 루프
    for(count = 0; count < MAX; count++) {
        printf("%d\t%d\t%p\n", count, *pointer_a++, pointer_a);
    }

    return 0;
}
```

`pointer_a`: 정수형 포인터로, 배열 a의 첫 번째 요소를 가리키는 데 사용된다.

배열 `a`의 이름은 배열의 첫 번째 요소의 주소를 가리키므로, `pointer_a`에 배열 `a`의 시작 주소가 할당된다.
따라서, `pointer_a`는 배열의 첫 번째 요소를 가리키게 된다.

```c
printf("%d\t%d\t%p\n", count, *pointer_a++, pointer_a);
```
여기에서, `*pointer_a++`는 `pointer_a`가 가리키는 값을 출력한다. 이 표현식은 후위 증가 연산자`(++)`를 사용하여 먼저 현재 주소가 가리키는 값을 출력하고, 그 후 포인터를 다음 요소로 이동시킨다. 즉, 출력 후 `pointer_a`가 다음 배열 요소로 이동한다.

`pointer_a`: 배열의 현재 주소를 출력한다. 포인터가 증가되었기 때문에, 다음 요소의 주소가 출력된다.

```
Index   Value   Address
0       1       0x7ffeed5bc020
1       2       0x7ffeed5bc024
2       3       0x7ffeed5bc028
3       4       0x7ffeed5bc02c
4       5       0x7ffeed5bc030
5       6       0x7ffeed5bc034
...
12      13      0x7ffeed5bc04c
```

`pointer_a++`는 4바이트씩 증가한다. 이는 int형이 4바이트를 차지하기 때문에, 다음 메모리 주소는 4바이트 뒤로 이동하게 된다. 즉, 메모리 주소 간의 차이는 `sizeof(int)`(4바이트)입니다.

`%p`는 메모리 주소를 출력하는데 사용되며, 각 배열 요소의 주소는 4바이트씩 증가한다.



## Pointers, Trees, Linked Lists

```c
void fun(int array[]);
int main() {
    int i, a[5] = {1, 2, 3, 4, 5};
    for(i = 0; i < sizeof(a)/sizeof(int); i++) {
        printf("Entry %d is %d.\n", i+1, a[i]);
    }
    fun(a);
    return 0;
}
void fun(int array[]) {
    printf("sizeof(array)/sizeof(int)=%d\n", sizeof(array)/sizeof(int));
}
```
for문: `sizeof(a)/sizeof(int)`는 배열 a의 요소 개수를 구하는데 사용된다. 여기서 `sizeof(a)`는 배열의 전체 크기를 바이트 단위로 나타내고, `sizeof(int)`는 배열의 각 요소의 크기를 나타낸다. 이 결과를 통해 배열의 길이를 구할 수 있다.

따라서 `sizeof(array)/sizeof(int)`는 항상 8/4 = 2를 반환하게 된다.

#### Pointer arithmetics

```c
int main() {
    int i, a[5] = {2, 4, 6, 8, 10};
for(i = 0; i < 5; i++) {
    printf("a[%d]=%d\n", i, *(a+i));
}
return(0);
}
```
`*(a+i)`는  배열의 포인터를 사용하여 인덱스 i에 해당하는 값을 출력한다.

  * `a`는 배열의 시작 주소를 나타내는 포인터이다.
  * `*(a+i)`는 포인터 산술을 이용하여 배열의 i번째 요소에 접근한다. 여기서 `a + i`는 배열의 `i`번째 요소의 주소를 나타내며, `*` 연산자는 그 주소에 있는 값을 가져온다.
  
배열 a의 주소는 변경되지 않으며, 포인터 산술을 통해 각 요소에 접근하는 방식이 동작한다.


```
a[0]=2
a[1]=4
a[2]=6
a[3]=8
a[4]=10
```

#### melloc()

`melloc`함수는 동적 메모리 할당을 가능하게한다. `stdlib.h` 헤더파일에 포함되어있다.
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *string; // 문자열을 가리키는 포인터를 선언
    string = (char*) malloc(96); // 96바이트의 메모리를 동적으로 할당. 
                                 // 이는 95개의 문자와 문자열 끝에 오는 null 문자(\0)를 포함하기 위한 메모리 공간

    int count;
    char *p = string;
    for(count = 32; count < 126; count++) {
        *p++ = count;
    }
    *p++ = '\0';

    puts(string);
    printf("%s\n", string);
    free(string); // 할당된 메모리 해제

    return(0);
}
```
`(char*)`는 `malloc()`의 반환값을 `char` 포인터로 형변환한다. 

#### struct name{}

struct는 C와 C++에서 구조체를 정의하기 위한 키워드다. 구조체는 서로 다른 데이터 타입을 하나의 복합 데이터 타입으로 묶을 수 있는 방법을 제공한다. struct를 사용하면 여러 변수를 하나의 이름 아래 그룹화하여 관리할 수 있다.

선언은 다음과 같이 한다.
```c
struct name {
    char first[20];
    char last[20];
    int age;
};
```

이렇게 구조체를 선언해 놓으면, 아래와 같이 자료형처럼 사용할 수 있다.

```c
struct name person1 = {"John", "Doe", 30};
```

또한, `person.last`와 같은 방법으로 해당 변수에 접근할 수 있다. 

```c
struct student{
    char name[23];
    int age;
}

typedef struct student student;
```
요런식으로 원래 `struct student`를 사용해서 선언해야 했던 저 구조체를 `student`하나만으로 선언할 수 있다. 

#### typedef

typedef는 C와 C++에서 데이터 타입에 새로운 이름을 부여하는 데 사용되는 키워드다. 이를 통해 기존 데이터 타입을 더 읽기 쉽거나 편리하게 사용하기 위한 별칭(alias)을 정의할 수 있다.

# Lecture 1

c++같은 좆같은 언어를 왜 쓰는가? c++은 저수준 언어이기 때문에, 메모리에 직접적인 액세스가 가능하고 강력한 하드웨어 제어능력이 있다. 파이썬같은건 대충 휘뚜루 마뚜루 쓰기엔 좋은데, 대규모 및 고성능 애플리케이션에선 조금 짜친다. c++은 이런 대규모 데이터를 다루기에 좋은데, 마침 bioinformatic이 아주 대규모 데이터를 다루네? 따라서 c++사용은 거의 필수라고 할 수 있다.

또한 C++은 다양한 플랫폼과 운영체제에서 베이직으로 사용되어 이식성이 뛰어나다. 라이브러리도 많고, 시스템 프로그래밍에도 적합하다.

파이썬과 R에서도 c++을 사용할 수 있다. 예를들어, `ctypes` 모듈은 외부 공유 라이브러리를 사용하여 c함수를 호출할 수 있다. 파이썬에서 기본적으로 제공된다. 또한 `SWIG`는 c/c++코드와 스크립팅 언어간의 인터페이스를 생성하여, c/c++ 코드를 파이썬에 통합할 수 있도록 한다. 

파이썬에서 C API extension을 사용한걸 보자.

```cpp
#include <Python.h>
extern int myfunc (int x, const char * s1);
static PyObject *wrapped_myfunc(PyObject *self,
    PyObject *args) {
  const char *s1;
  int ival;
  if (!PyArg_ParseTuple(args, "is", &ival, &s1))
    return NULL;
  ival = myfunc(x, s1);
  return Py_BuildValue("i", ival);
}
```
C코드 컴파일러가 따로 필요하며, 복잡하다. 

ctypes 예시를 보자.

```python
import ctypes
mydll = ctypes.CDLL("./mydll.dll")
myfunc = mydll.myfunc
myfunc.argtypes = [ctypes.c_int, ctypes.c_char_p]
myfunc.restype = ctypes.c_int
print mydll.myfunc(22, "This is a test.")
```
쉽쥬?

마찬가지로 R에서도 c/c++ 환경을 사용할 수 있다. `Rcpp`라는 패키지를 사용한다. 

```r
library("Rcpp")
cppFunction("
    Rcpp::NumericVector nfun(
    Rcpp::NumericVector a,
    Rcpp::NumericVector b) {

    Rcpp::NumericVector xa(a);
    Rcpp::NumericVector xb(b);
    int n_xa = xa.size(), n_xb = xb.size();
    Rcpp::NumericVector xab(n_xa + n_xb - 1);
    for (int i = 0; i < n_xa; i++) {
        for (int j = 0; j < n_xb; j++) {
            xab[i + j] += xa[i] * xb[j];
        }
    }
    return xab;
}
")
```

이런식으로, R과 python에서 미리 만들어놓은 것들을 C를 이용해 바꿔서 더 빠르게 만들거나, 더 큰 데이터셋에 사용할 수 있도록 바꿀 수 있다. 

C++은 C의 업그레이드 버젼으로, C에서 사용한것들을 모두 사용할 수 있고, OOP나 regex와 같은 더 많은 기능들이 들어가있다. c는 버리고  c++을 쓰도록 하자. 그래도 C++을 할려면 c도 결국 할줄 알아야한다.. 

추가된 기능에 대해 예시를 보도록 하자.
```c
#include <stdio.h>
int main() {
    printf("Hello C World !\n");
    return(0);
}
```
C에서는 항상 저렇게 `printf()`를 사용해줬어야 했다.

그러나, C++에서는!

```cpp
#include <iostream>
int main() {
    std::cout << "Hello C++ World!\n";
    return(0);
}
```
요로코롬 신기한 기능이 생겼다. 근데 뭐 사실 다른언어에서 다 print 쓰는데 굳이 저걸 써야하나 싶기도 하고..

## Identifier

중요한! 식별자부터 알아보도록 하자.  변수, 함수, 클래스, 모듈 또는 다른 사용자 정의 항목을 식별하는 데 사용되는 이름이다. 식별자는 대문자 A부터 Z, 소문자 a부터 z, 또는 밑줄(_)로 시작하며 이어서 문자, 밑줄 및 숫자(0부터 9)가 올 수 있다. C++에서는 @, $, %와 같은 구두점 문자를 식별자 내에서 허용하지 않는다. 또한 C++은 대소문자를 구분한다. `myVariable`
`my_function`
`_myClass`
`MyModule`
`variable123` 등은 유효한 이름으로 식별된다. 당연히, 키워드는 identifier로 사용될 수 없다.

주석은 `/**/`와 `//`로 사용할 수 있다.

## Basic data types

C 언어의 유형과 동일하지만 몇 가지 추가 유형이 있다.

- **bool** (부울): 참/거짓을 나타내는 부울 값으로 사용된다.
- **wchar_t (UTF-16)**: 넓은 문자(wide character)를 나타내며 주로 UTF-16 문자열을 다룰 때 사용된다.
- C++에는 **std::string**이라는 정교한 문자열 유형이 있다. strncpy, strcmp 등과 같은 함수를 사용할 필요 없이 간단한 할당 및 비교 연산자를 사용할 수 있다.
- **enum**: C++에서는 열거형을 정의하는 데 사용되며, 연속된 정수 상수의 집합을 정의한다.
- **const** VARIABLES: 상수를 정의하는 데 사용되며, 값이 변경되지 않아야 하는 변수에 사용된다.


enumeration의 예시를 보자.

```cpp
int main() {
    enum { kreuz, pik, karo, herz, dummy=7 };
    int karte = karo;
    std::cout << "Wert von Pik ist: " << pik << "\n";
    std::cout << "Wert der Karte: " << karte << "\n";
    karte=dummy;
    std::cout << "Wert der Karte: " << karte << "\n";
    return(0);
}
```
```
Wert von Pik ist: 1
Wert der Karte: 2
Wert der Karte: 7
```
요로코롬 나타나게 된다. 

### local and global 

local 쓰고싶으면 그냥 함수 안에 쓰면 되고, global을 쓰고싶으면 그냥 함수 밖에 선언하면 된다. 

```cpp
#include <iostream>
using namespace std;

// 전역 변수 선언
int globalVar = 10;

void func() {
    // 전역 변수 globalVar를 출력
    cout << "전역 변수 globalVar의 값: " << globalVar << endl;
}

int main() {
    // 전역 변수 globalVar를 출력
    cout << "전역 변수 globalVar의 값: " << globalVar << endl;
    
    // func 함수 호출
    func();
    
    return 0;
}
```
### const

또한, 상수를 정의할때 `#define`나 `const`를 사용할 수 있다. 상수는 대문자로 정의하는게 국룰이다. 근데, 예전에는 `#define`을 사용하여 상수를 적용했지만, 이게 somehow 혼동을 일으키거나 오류를 발생시킬 수 있기 때문에, 일단 냅두지만 `const`를 사용하는게 권장된다. 

```cpp
// #define을 사용한 상수 정의 (지양하는 방법)
#define MAX_VALUE 100

// const 키워드를 사용한 상수 정의
const int MAX_VALUE = 100;
```
## Operator

operator는 C와 유사하다. 논리 연산자는 && (and)와 || (or)를 사용하며, 할당 연산자로는 =, +=, -=, *=, /= 등이 있다. 그러나, **비트 연산자**가 있는데, &, |, ^를 사용할 수 있따. 

또한, c++에서 추가된것들이 있다.

* **auto**: auto 키워드는 변수의 자료형을 자동으로 추측하도록 한다. 예를 들어, `auto x = 1;`은 x가 정수로 추측된다.

* **sizeof**: sizeof 연산자는 데이터 형식 또는 변수의 크기를 반환한다. 예를 들어, `sizeof(int)`는 정수의 크기를 반환한다.

* **condition ? x : y**: 조건 연산자는 조건식의 결과에 따라 두 개의 값 중 하나를 선택한다. 조건이 참이면 x를 반환하고, 거짓이면 y를 반환한다.

* **. (dot) and -> arrow**: `.` 연산자는 객체나 구조체의 멤버에 접근할 때 사용된다. `->` 연산자는 포인터가 가리키는 객체나 구조체의 멤버에 접근할 때 사용된다.

* **cast like int(3.4)**: 캐스트 연산자를 사용하여 데이터 형식을 변환할 수 있다. 예를 들어, `int(3.4)`는 실수 3.4를 정수로 변환한다.

* **& pointer**: `&` 연산자는 변수의 주소를 반환한다. 이는 포인터 변수를 초기화하거나 함수에 참조 매개변수를 전달할 때 유용하다.

* **`*` pointer**: `*` 연산자는 포인터 변수를 나타냅니다. 이는 포인터가 가리키는 변수의 값을 역참조할 때 사용된다.

## Data Container

c++에는 신기하고 다양한 컨테이너들이 있다.

- std::string
- std::map (Python의 dictionary, R의 list와 유사)
- std::array (크기가 고정된 배열)
- std::vector (배열과 유사하지만 크기를 조절할 수 있음)
- std::set (map과 유사하지만 값이 없음)

뭐 이상한것들이 많은데, 대충 map과 vector만 쓰면 웬만한건 다 할 수 있다. map에 대한 몇가지 기본적인 메서드들을 알아보자.

- `begin()` - 맵의 첫 번째 요소에 대한 반복자를 반환한다.
- `end()` - 맵의 마지막 요소 다음의 이론적 요소에 대한 반복자를 반환한다.
- `size()` - 맵에 포함된 요소의 수를 반환한다.
- `empty()` - 맵이 비어 있는지 여부를 반환한다.
- `insert(keyvalue, mapvalue)` - 새로운 요소를 맵에 추가한다.
- `erase(const g)`- 맵에서 키 값 "g"를 제거한다.
- `clear()` - 맵에서 모든 요소를 제거한다.

써보도록 하자.

```cpp
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>

int main() {
    std::string hw = "Hello World!\n";
    std::cout << hw;
    std::cout << "Length of String: " << hw.length() << std::endl;

    std::vector<int> v = {7, 5, 16, 8};
    std::cout << "element at 0: " << v.at(0) << std::endl;
    v[0]++;
    std::cout << "element at 0: " << v[0] << std::endl;
    std::cout << "length of vector: " << v.size() << std::endl;

    // 새로운 요소 추가 (배열에는 사용할 수 없음)
    v.push_back(20);
    std::cout << "last element: " << v.at(v.size() - 1) << std::endl;

    std::map<std::string, char> aaa = { {"Leu", 'L'} };
    // std::map에 데이터 삽입
    aaa.insert(std::make_pair("Cys", 'C'));
    aaa.insert(std::make_pair("Asp", 'D'));
    // 자동 쌍(pair) 생성
    aaa.insert({ "Ala", 'A' });
    // 더 간단한 삽입
    aaa["Asn"] = 'N';
    aaa["His"] = 'H';
    std::cout << "map size: " << aaa.size() << std::endl;
    std::cout << "Proline? " << aaa.count("Pro") << std::endl;
    aaa["Pro"] = 'P';
    std::cout << "Proline? " << aaa.count("Pro") << std::endl;

    return 0;
}
```
```
Hello World!
Length of String: 13
element at 0: 7
element at 0: 8
length: of vector: 4
last element: 20
map size: 6
Proline? 0
Proline? 1
```

## Storage classes

Storage classes는 C++에서 변수나 함수가 메모리 내에서 어떻게 저장되고 접근되는지를 제어하는 데 사용된다. 다양한 저장 클래스는 변수 또는 함수의 범위(scope), 수명(lifetime), 초기화 및 접근 가능성(accessibility)을 결정한다.

여러 가지 저장 클래스가 있지만 일반적으로 다음과 같이 분류된다:

- **auto**: C++11 이후 자동 형식 추론을 지원한다. 변수 선언 시 자료형을 명시하지 않고, 초기화된 값의 자료형을 기반으로 자동으로 결정한다.
- **register**: 레지스터 변수로 선언되며, 빠른 접근을 위해 레지스터에 저장되지만, 현대의 컴파일러는 레지스터 관리를 자동으로 수행하므로 거의 사용되지 않는다.
- **static I**: 함수 내에서 지역 변수로 사용할 경우, 함수 호출 이후에도 값이 유지된다. 또한 전역 변수로 선언될 경우, 다른 파일에서도 접근 가능하다.
- **static II**: 클래스 내에서 static 멤버로 사용될 경우, 클래스에 대한 멤버이며 객체에 속하지 않는다.
- **extern**: 다른 파일에 선언된 전역 변수를 현재 파일에서 사용할 때 사용된다.
- **mutable**: 클래스 객체의 멤버 변수를 변경 가능하게 만듭니다. 이는 const 멤버 함수 내에서도 해당 멤버 변수의 값을 변경할 수 있도록 한다.

```cpp
#include <iostream>

// Function declaration
void func(void);

// Global variable
static int count = 10;

// 자동 형식 추론을 사용한 변수 선언
auto x = 4;

// 초기화 없이 선언할 수 없음
// 예시: auto x;

int main() {
    // count 값을 감소시키면서 반복
    while(count--) { // 두 번 감소!!
        func();
    }

    std::cout << "And x is " << x << std::endl;

    return 0;
}

// Function definition
void func( void ) {
    // 지역 static 변수
    static int i = 5;
    i++;
    std::cout << "i is " << i ;
    std::cout << " and count is " << count << std::endl;
}
```

```
i is 6 and count is 9
i is 7 and count is 8
i is 8 and count is 7
i is 9 and count is 6
i is 10 and count is 5
i is 11 and count is 4
i is 12 and count is 3
i is 13 and count is 2
i is 14 and count is 1
i is 15 and count is 0
And x is 4
```

## Templates

템플릿(templates)은 C++에서 코드를 일반화하여 여러 자료형에 대해 동작할 수 있도록 하는 강력한 기능이다. 템플릿을 사용하면 클래스나 함수를 작성할 때 특정 자료형에 종속되지 않고, 여러 자료형에 대해 일반적으로 동작하도록 할 수 있다.

일반적으로 두가지 유형이 있다.:

1. Class Templates

    클래스 템플릿은 클래스를 정의할 때 사용되는 템플릿이다. 클래스 템플릿을 사용하면 특정 자료형에 대한 클래스를 생성할 때마다 클래스의 정의를 다시 작성할 필요가 없다. 대신, 템플릿을 사용하여 클래스를 정의하고, 특정 자료형에 대해 인스턴스화할 때 자료형을 지정한다.

    ```cpp
    template<typename T>
    class Stack {
    private:
        T arr[100];
        int top;
    public:
        Stack() : top(-1) {}
        void push(T val) { arr[++top] = val; }
        T pop() { return arr[top--]; }
        T peek() { return arr[top]; }
        bool isEmpty() { return top == -1; }
    };
    ```
    템플릿을 이용하여 제네릭한 스택 클래스를 정의하는 예시이다. 

2. Function Templates

    함수 템플릿은 함수를 정의할 때 사용되는 템플릿이다. 함수 템플릿을 사용하면 특정 자료형에 대해 동일한 동작을 수행하는 함수를 여러 자료형에 대해 재사용할 수 있다.

    ```cpp
    template<typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }
    ```
    다음은 템플릿을 사용하여 두 값을 교환하는 함수를 정의하는 예시이다.

템플릿은 매우 유연하며 강력한 기능이지만, 사용법을 잘못하면 코드를 이해하거나 디버그하기 어려울 수 있다. 또한 템플릿을 사용할 때 특정 자료형에 대한 오버로딩된 함수가 생성될 수 있으므로 컴파일된 코드의 크기가 커질 수 있다.

## Calling function

함수 호출 방식에는 세 가지가 있다:

1. **값에 의한 호출(Call by Value)**:
   - 기본적으로 사용되는 방식이다.
   - 호출할 때마다 매개변수로 전달되는 값의 **복사본**이 함수로 전달된다.
   - 함수 내에서 매개변수의 값이 변경되더라도 호출된 곳의 변수에는 **영향을 주지 않는다**.

2. **포인터에 의한 호출(Call by Pointer)**:
   - 매개변수로 변수의 주소를 전달한다.
   - 함수 내에서 매개변수를 통해 **변수의 값을 변경할 수 있다**.
   - 함수가 호출될 때마다 변수의 주소가 전달되므로 함수 **호출 시간이 더 오래 걸릴 수 있다**.

1. **참조에 의한 호출(Call by Reference)**:
   - C++에서만 사용할 수 있는 방식이다.
   - 매개변수로 **변수의 참조(레퍼런스)를 전달**한다.
   - 함수 내에서 매개변수를 통해 **변수의 값을 변경할 수 있다**.
   - **값에 의한 호출과 달리 함수 호출 시간이 더 짧다**.
   - 포인터에 의한 호출과 달리 **주소 연산자(`&`)를 사용할 필요가 없으므로 코드가 더 간결**해진다.

2. **기본 값이 있는 함수 인수(Default Arguments)**:
   - C++에서만 사용할 수 있는 기능이다.
   - 함수의 매개변수에 기본 값을 할당할 수 있다. 함수 호출 시 해당 매개변수에 값을 전달하지 않으면 기본 값이 사용된다.
   - 이를 통해 함수를 호출할 때 필요한 매개변수의 수를 줄일 수 있다.

이러한 함수 호출 방식은 각각의 상황에 따라 적합한 방법을 선택하여 사용해야 한다. 함수 호출 시에는 함수가 수행해야 할 작업과 매개변수로 전달되는 값의 변화 여부 등을 고려하여 적절한 호출 방식을 선택해야 한다.

```cpp
#include <iostream>
using namespace std;

// 함수 선언
int sum(int a, int b = 20) {
    int result;
    result = a + b;
    return result;
}

int main() {
    // 지역 변수 선언
    int a = 100;
    int b = 200;
    int result;

    // 함수 호출하여 값들을 더한다.
    result = sum(a, b);
    cout << "Total value is : " << result;

    // 매개변수에 기본값이 있는 함수를 호출한다.
    result = sum(a);
    cout << " - Total value is : " << result << endl;

    return 0;
}
```
* `int sum(int a, int b = 20)`: 함수 sum은 매개변수 a와 b를 받는다. b의 기본값은 20으로 지정되어 있다.
* `result = sum(a, b);`: 함수 sum을 호출하여 a와 b를 인수로 전달한다. 이 때, b에 명시적으로 값이 전달되므로 기본값이 사용되지 않는다.
* `result = sum(a);`: 함수 sum을 호출하여 a만을 인수로 전달한다. 이 때, b의 기본값인 20이 사용된다.

## Math functions 

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main () {
    // number definition:
    short s = 10;
    int i = -1000;
    long l = 100000;
    float f = 230.47;
    double d = 200.374;
    // mathematical operations;
    cout << "d is: " << d << endl;
    cout << "sin(d) :" << sin(d) << endl;
    cout << "sin(f) :" << sin(f) << endl;
    cout << "abs(i) :" << abs(i) << endl;
    cout << "floor(d) :" << floor(d) << endl;
    cout << "sqrt(f) :" << sqrt(f) << endl;
    cout << "pow( d, 2) :" << pow(d, 2) << endl;
    return 0;
}
```
```
d is: 200.374
sin(d) :-0.634939
sin(f) :-0.906
abs(i) :1000
floor(d) :200
sqrt(f) :15.1812
pow( d, 2) :40149.7
```

## random number

* C++에서는 `rand()` 함수를 사용하여 랜덤한 정수를 생성할 수 있다. 그러나 이 함수는 유사 난수를 생성한다.
* 유사 난수를 생성하기 위해서는 먼저 `srand()` 함수를 호출하여 시드(seed) 값을 설정해야 한다.
* 시드 값은 랜덤 순서를 결정하는 초기 값으로, 동일한 시드 값이 주어지면 항상 동일한 랜덤 순서가 생성된다.
* 일반적으로 시드 값으로 현재 시간을 사용하여 매번 다른 랜덤 순서를 생성할 수 있다.

```cpp
#include <iostream>
#include <cstdlib> // rand, srand 함수를 사용하기 위한 헤더
#include <ctime>   // 현재 시간을 얻기 위한 헤더

int main() {
    // 현재 시간을 시드 값으로 사용
    srand(time(0));

    // 0부터 RAND_MAX(32767) 사이의 랜덤 정수 생성
    int randomNumber = rand();

    std::cout << "Random number: " << randomNumber << std::endl;

    return 0;
}
```

# Lecture 2

## Inline function

인라인 함수는 성능 최적화를 위해 사용되는 함수의 한 형태로, 함수 호출의 오버헤드를 줄이고자 하는 목적이다. 함수 호출의 오버헤드를 줄이기 위해 컴파일러에게 함수 호출 대신 함수의 코드 본문을 호출 위치에 직접 복사하도록 요청한다. 

어떤 식이냐면, 함수를 호출하는 대신, 함수 본문을 호출 위치에 직접 삽입한다. 이는 특히 함수 호출이 빈번히 이루어지는 경우 성능을 향상할 수 있다. 즉, 빨라진다는 의미인데, 진짜 속도가 문제일 경우에만 사용이 권장된다. 함수를 호출할때 제어의 이동, 즉 점프가 발생하게 되는데, 이걸 줄여준다.

그러나, 이를 사용하게 되면 동일한 코드가 여러 위치에 복사되므로, 코드블럭의 크기가 증가할 수 있다. 따라서 매우 짧거나 간단한 함수들이 inline function 사용에 적합하다. 

이 inline 함수는 컴파일러에게 "야 대충 여기다가 꽂아넣으면 좋지않을까?"하고 제안하는것과 마찬가지이다. 컴파일러가 판단하기에 적합하지 않으면, 사용하지 않을 수 있다. `#define`을 사용하는 매크로 보다는 인라인 함수를 사용하는게 더 권장된다. 

```cpp
inline int add(int a, int b) {
    return a + b;
}
```
이런식으로 선언할 수 있으며, 본문에서 `add`함수를 사용할 경우 함수 본문이 호출된다. 

## Recursion vs Iteration

Recursive function은 좀 간지나 보이지만, 비효율적인 경우가 많다. 함수 동작에 메모라이징과 캐싱이 사용되기 때문이다. 그에 비해 반복문은 대부분 좀 짜쳐보이지만 더 효율적인 경우가 많다. 

## Pointers and References

C++에서 포인터와 참조는 메모리 관리와 효율적인 데이터 처리를 위한 중요한 도구이다. C++에서 함수가 하나 이상의 값을 반환해야 하는 경우, 포인터와 참조를 사용하여 이를 해결할 수 있다. 이들은 함수 호출, 데이터 구조 처리, 메모리 직접 접근 등에 사용된다. 

### how to return more than one value/item?

함수 인자를 reference를 사용해서 전달하는 경우, 함수 내부에서 값을 변경할 수 있다. 이는 파이썬같은곳에서 함수 내부의 변수가 local로 취급되어 변수를 반환하지 않을 시 변경되지 않는것과는 다르다. 

```cpp
void getValues(int &a, int &b) {
    a = 10;
    b = 20;
}
```
이 경우, a와 b의 값이 실제로 변하게 된다. 이는 파이썬에서 처럼, 함수 실행시 값을 복사해오는게 아니라, reference를 통해 직접 값이 저장된 메모리에 접근이 가능하기 때문이다. 

이를 통해, 여러 값을 한번에 처리할 수 있다. 이는 즉 여러값을 한번에 반환하는것과 다르지 않은 결과를 가져온다. 

또한, 그저 변수가 아닌 데이터구조에 여러 변수를 욱여넣은 후 반환함으로써 여러 값을 한번에 반환할수도 있다. 

```cpp
std::pair<int, int> getValues() {
    return std::make_pair(10, 20);
}

int main() {
    std::pair<int, int> values = getValues();
    std::cout << "First: " << values.first << ", Second: " << values.second << std::endl;
    return 0;
}
```

### Call by

포인터 혹은 레퍼런스를 이용하여 함수를 호출할 수 있다. 보통은 value를 사용하여 함수를 호출한다. 이 경우, 함수 인자로 전달된 변수의 값을 복사하여 함수 내부로 전달하고, 함수 내부에서 인자의 값을 변경해도 원래의 변수에는 영향을 미치지 않는다. 이는 일반적으로 파이썬같은데서 사용되는 원리와 같다. 

```cpp
void foo(int a) {
    a = 5; // 원래의 변수에는 영향 없음
}
```

그러나, 레퍼런스나 포인터로 함수를 호출하는 경우, 함수 인자로 전달된 변수 자체를 참조하여 함수 내부로 전달한다. 따라서, 함수 내부에서 인자의 값을 변경하면 원래의 변수에도 영향을 미치게 된다. 

아래는 포인터를 사용한 예이다.
```cpp
void foo(int *a) {
    *a = 5; // 원래의 변수에 영향을 미침
}

int main() {
    int x = 10;
    foo(&x);
    std::cout << x << std::endl; // 5 출력
    return 0;
}
```

아래는 레퍼런스를 사용한 예시이다. 포인터 사용과는 달리 이는 C++에서만 가능하다. 

```cpp
void foo(int &a) {
    a = 5; // 원래의 변수에 영향을 미침
}

int main() {
    int x = 10;
    foo(x);
    std::cout << x << std::endl; // 5 출력
    return 0;
}
```

레퍼런스를 사용한 함수 호출이 가지는 장점이 무엇일까? 왜하는걸까? 이는 입력 변수를 변경할 필요가 있을때 유용할 수 있다. 그런데 이걸 자주쓰면 예상치 못한 부작용을 낳을 수 있으니 조심하자. 

또한! 가장 중요한것. 큰 함수를 호출할때 큰 데이터 구조를 입력으로 사용한다면, 그리고 이걸 변수로 호출한다면, 이 큰 데이터구조가 모조리 복사되는 경우가 발생하는데 이는 비효율적이다. 이때 call by reference를 사용하면 데이터 스트럭쳐를 다 복사하지 않아도 개별 값에 접근하므로 성능이 향상된다. 

```cpp
void processLargeData(const std::vector<int> &data) {
    // 데이터 구조를 복사하지 않고 처리
}
```

#### Pointer and Reference?

이쯤에서 pointer와 reference에 대해 다시한번 짚고 넘어가자. 포인터는 변수의 메모리 주소를 저장하는 변수이다. 

```cpp
int a = 10;
int *p = &a; // 'p'는 'a'의 주소를 가리키는 포인터
```
이는 포인터의 선언과 초기화이다. 

cpp에서는 reference operator `*`와, address operator `&`가 사용된다. 

```cpp
int value = *p; // 'value'는 'a'의 값을 가짐 (10)
```
즉, *p는 a의 주소값을 가지고 있는데, a의 위치에 직접 접근해서 a의 값을 가지고온다. `*p`가 포인터이기 때문에, `p`를 호출하면 a의 주소값이 나올것이다. 즉, 직접 출력을 해보면 `&a==p`이고, `a==*p`이 나온다. 줜내 헷갈리쥬? 

또한, 

- **x가 만약 point이면, `*x`는 x의 주소값이다.**
- **x가 일반 변수이면, `&x`는 x의 주소값이다.**

**reference variable**이라는것도 존재하는데, 대충 아무 변수나 선언한뒤, 이 변수의 레퍼런스, 즉 주소값을 가리키는 변수를 선언하면 언제 어디서든 이 변수에 접근할 수 있다. 

```cpp
int a = 10;
int &ref = a;

std::cout << ref << std::endl; // 참조 ref가 가리키는 변수의 값 출력 (10)
ref = 20; // 참조 ref가 가리키는 변수의 값을 20으로 변경
std::cout << a << std::endl; // a의 값 출력 (20)
```

이 레퍼런스는 한번 initialized 되면 다른 변수를 참조할 수 없다.

```cpp
#include <iostream>

int main () {
    int x = 6;
    int y = 7;
    int &rx = x; // rx는 x를 참조
    std::cout << "x=" << x << " rx=" << rx << " y=" << y << std::endl;
    rx = y; // x의 값을 y의 값으로 변경
    std::cout << "x=" << x << " rx=" << rx << " y=" << y << std::endl;
    return 0;
}
```
```
x=6 rx=6 y=7
x=7 rx=7 y=7
```

여기선 rx만 바꿧는데, x가 따라서 바뀌었다. 이 관계는 바꿀 수 없다. 한번 rx와 x를 묶어놓으면, rx=y 이런걸 해도 안바뀐단 얘기다. 

포인터는 C에서부터 도입된 것으로, 낡았다. C++에서도 포인터를 사용할 수 있긴 하지만, 웬만하면 reference만 사용하자. 또한, 작은 데이터를 다룰땐 굳이 불필요하니 큰 데이터를 사용할때만 사용하자. 

## Const keyword

C++에서 함수 인자를 `const` 키워드로 선언하면, 해당 인자의 값이 함수 내부에서 변경되지 않음을 보장할 수 있다. 상수로 선언하는것이다. 얘는 못바꿔용! 튜플같다. 이는 특히 큰 데이터 구조를 참조로 전달할 때 유용하다. 

위에서 말햇듯, 레퍼런스와 포인터를 이용해 함수를 호출하는 것은 효율적이다. 그러나, 이것이 변수를 막 바꾸는 등 원치않는 부작용을 초래할 수 있기 때문에 조심해야한다고 했다. 이 때, 이 부작용을 막기위해 사용할 수 있는것이 바로 `const`이다. 

```cpp
void foo(const int &x) {
    x = 6; // 컴파일 에러: const 참조는 값을 변경할 수 없다.
}
```

`const`의 참조를 사용하여 큰 데이터를 처리하는 예시를 살펴보자.

```cpp
#include <iostream>
#include <vector>

void printVector(const std::vector<int> &vec) {
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> myVec = {1, 2, 3, 4, 5};
    printVector(myVec); // vec는 const 참조로 전달됨
    return 0;
}
```

일단 큰 데이터를 처리할때, 참조를 이용해서 값을 직접 가져와놓고, 받을때 아예 const로 선언해서 혹시모를 불상사를 방지하는 것이다. 어차피 값만 가져오고 함수 내부에서 복사에서 쓰면 되잖아? 모든 데이터스트럭쳐를 싹 긁어오는것보다 훨씬 효율적이다. 또, 누가 실수로 혹은 고의로 내 코드를 족쳐놓는 것도 방지할 수 있다. 

따라서, 내가 만약 reference를 이용해서 큰 데이터의 값을 받는다면, 반드시 const를 함께 사용하자. 

## Function overloading

함수 오버로딩은 동일한 이름을 가진 여러 함수를 생성할 수 있는 기능을 의미한다. 각 함수는 다른 매개변수 목록을 가지며, 함수 호출 시 전달된 인자의 유형과 개수에 따라 적절한 함수가 실행된다. 이는 함수 호출이 문맥에 따라 다른 작업을 수행할 수 있도록 한다. 

간단히 말해서, 똑같은 이름의 함수를 여러개를 선언해 놓은뒤 사용하는 것이다. 가끔 parameter의 자료형때문에 오류가 발생하는 경우가 있는데, 이렇게 미리 오버로딩을 해놓으면 알아서 맞는걸 골라다 쓴다. 

```cpp
#include <iostream>

// 정수 두 개를 더하는 함수
int add(int a, int b) {
    return a + b;
}

// 실수 두 개를 더하는 함수
double add(double a, double b) {
    return a + b;
}

// 정수 세 개를 더하는 함수
int add(int a, int b, int c) {
    return a + b + c;
}

int main() {
    std::cout << "add(3, 4) = " << add(3, 4) << std::endl;           // 정수형 add 호출
    std::cout << "add(3.5, 2.7) = " << add(3.5, 2.7) << std::endl;   // 실수형 add 호출
    std::cout << "add(1, 2, 3) = " << add(1, 2, 3) << std::endl;     // 정수형 add(세 개) 호출
    return 0;
}

```
사실 이건 C에서나 하는 방법이지, C++에선 그냥 `auto` 쓰면 된다.

## Polymorphic functions with templates

여러 개의 타입 매개변수를 사용하는 템플릿 함수도 정의할 수 있다. 

```cpp
#include <iostream>

// 다중 타입 템플릿 함수 정의
template <typename T1, typename T2>
auto multiply(T1 a, T2 b) -> decltype(a * b) {
    return a * b;
}

int main() {
    std::cout << "multiply(3, 4.5) = " << multiply(3, 4.5) << std::endl;  // int와 double 타입의 multiply 호출
    std::cout << "multiply(2.5, 2) = " << multiply(2.5, 2) << std::endl;  // double과 int 타입의 multiply 호출
    return 0;
}
```
대충 넘어가자. 나는 템플릿이 싫다.


## Lambda Functions

람다 함수는 익명 함수로, C++11부터 도입되었다. 파이썬에서도 람다함수를 찾아볼 수 있고, R에선 주로 `apply`함수가 이 역할을 한다.  람다 함수는 주로 간결한 일회성 함수를 작성할 때 사용되며, 코드의 가독성을 높이고 함수 객체를 쉽게 정의할 수 있게 한다. 

예를 들어, 함수에 어떤 다른 함수를 써야하는데, 짧고 간단한데다가 한번밖에 안쓸 함수다. 이럴경우 간단히 람다함수를 이용할 수 있다.  

람다함수는 다음과 같은 형식을 가진다.

```
[캡처](매개변수) -> 반환형 { 함수 본문 }
```
`[]`를 이용해 선언한다. 저 브라켓 내부에는 변수가 들어갈 수 있는데, 외부 변수에 접근하기 위해 캡처를 사용한다. 

```cpp
#include <iostream>

int main() {
    int x = 10;
    int y = 20;

    // 값에 의한 캡처
    auto addX = [x](int a) -> int {
        return a + x; // x는 값으로 캡처됨
    };

    // 참조에 의한 캡처
    auto addY = [&y](int a) -> int {
        return a + y; // y는 참조로 캡처됨
    };

    std::cout << "addX(5) = " << addX(5) << std::endl; // addX(5) = 15 출력
    std::cout << "addY(5) = " << addY(5) << std::endl; // addY(5) = 25 출력

    y = 30;
    std::cout << "addY(5) = " << addY(5) << std::endl; // addY(5) = 35 출력

    return 0;
}
```

캡처할 변수가 없는 경우 그냥 빈 `[]`만 사용해도 되며, 모든 외부변수를 값으로 캡쳐하려면 `=`를 넣고, 모든 외부 변수를 참조로 캡쳐하려면 `&`를 넣는다. 물론 `[=,&a]`와 같이 섞어쓰는것도 가능하다. 

```cpp
#include <iostream>

int main() {
    int a = 1, b = 2, c = 3;

    // 모든 변수를 값으로 캡처
    auto lambda1 = [=]() {
        return a + b + c;
    };

    // 모든 변수를 참조로 캡처
    auto lambda2 = [&]() {
        a = 4;
        return a + b + c;
    };

    std::cout << "lambda1() = " << lambda1() << std::endl; // lambda1() = 6 출력
    std::cout << "lambda2() = " << lambda2() << std::endl; // lambda2() = 9 출력

    return 0;
}
```

람다 함수는 표준 라이브러리와 함께 사용할 때 매우 유용하다. 특히, std::sort와 같은 알고리즘 함수에서 사용자 정의 비교 함수를 제공할 때 유용하다.


```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {5, 2, 8, 3, 1};

    // 람다 함수를 사용하여 벡터를 오름차순으로 정렬
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        return a < b;
    });

    // 정렬된 벡터 출력
    for (int n : vec) {
        std::cout << n << " ";
    }
    std::cout << std::endl; // 1 2 3 5 8 출력

    return 0;
}
```

## Container

### Array

배열은 C와 C++에서 기본적으로 제공되는 데이터 구조로, 동일한 타입의 데이터를 정해진 크기만큼 연속적으로 저장할 수 있는 구조이다. 사용 전에 미리 크기를 지정해야하고, 동일한 구조만 넣을 수 있기 때문에 제한이 많다.

```c
#include <iostream>

int main () {
    // 5행 2열의 배열 선언 및 초기화
    int a[5][2] = { {0,0}, {1,2}, {2,4} };
    
    // 각 배열 요소의 값을 출력
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << "a[" << i << "][" << j << "]: ";
            std::cout << a[i][j] << std::endl;
        }
    }
    return 0;
}
```
C에서는 딱히 다른 선택지가 없어서 배열을 자주 사용해야한다. 그러나 C++에선 `vector`를 이용해 배열의 거의 모든 기능을 구현할 수 있으므로, 배열의 사용은 딱히 추천되지 않는다. 

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> matrix = {
        {0, 0},
        {1, 2},
        {2, 4}
    };

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << "matrix[" << i << "][" << j << "]: " << matrix[i][j] << std::endl;
        }
    }

    return 0;
}
```

배열을 함수로 전달할수도 있는데, 이는 C에서와 C++에서 방법이 다르다.  C에서는 배열을 함수 인자로 전달할 때 배열의 크기도 함께 전달해야 하며, C++에서는 표준 라이브러리의 `std::vector`를 사용하여 더 안전하고 유연하게 배열을 처리할 수 있다. 

C스타일은 다음과 같다.

```c
#include <iostream>
using namespace std;

// C 스타일 배열과 크기를 전달받는 함수
double getAverage(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return static_cast<double>(sum) / size;
}

```
C 표준을 따르기 때문에 기존 C 코드와 호환성이 높다. 그러나 배열 크기를 별도로 관리해야 하며, 포인터로 배열을 다루기 때문에 안전성이 떨어질 수 있다.

c++스타일은 다음과 같다.
```cpp
#include <vector>
using namespace std;

// C++ 스타일의 벡터를 전달받는 함수
double getAverage(vector<int> arr) {
    double average = 0;
    for (auto i : arr) {
        average += i;
    }
    return average / arr.size();
}
```
### Which container?

C++ 표준 라이브러리는 다양한 데이터를 효율적으로 관리하고 처리하기 위해 여러 컨테이너를 제공한다. 

#### Vector
`std::vector`는 동적 배열로, 크기가 자동으로 조정되는 배열이다.

* 빠른 인덱스 접근 (O(1))
* 요소 삽입 및 삭제 (끝에서: O(1), 중간에서: O(n))
* 연속된 메모리 블록 사용

주로,
* 크기가 가변적인 배열이 필요할 때
* 인덱스를 통해 자주 접근해야 할 때
* 메모리 사용을 최적화하고 싶을 때

사용한다. 

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6); // 요소 추가
    for (int v : vec) {
        std::cout << v << " ";
    }
    return 0;
}
```

#### map

`std::map`은 키-값 쌍을 저장하는 정렬된 연관 컨테이너이다.


* 키를 기준으로 정렬됨
* 키를 통해 빠르게 요소를 검색 (O(log n))
* 중복 키를 허용하지 않음

주로, 

* 키-값 쌍을 저장하고 정렬된 순서로 유지해야 할 때
* 빠른 검색이 필요할 때

사용한다.

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> map;
    map[1] = "one";
    map[2] = "two";
    map[3] = "three";

    for (const auto &pair : map) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    return 0;
}
```

C++은 여러 데이터 컨테이너를 제공하지만, 웬만하면 이 벡터와 맵으로 모두 표현이 가능하다. 더 쓴다면 뭐 리스트가 있겠다. 다른거 쓸필 요 없다. 

또 벡터를 두개 겹쳐놓으면 매트릭스가 되기 때문에, 매트릭스도 뭐 r이나 매트랩에서 많이 써서 익숙하니 이걸 써도 된겠다. 

## Structure and Classes

### Struct

Struct는 서로 다른 종류의 데이터 항목을 결합하여 사용자 정의 데이터 타입을 만드는 것이다. C++에서 구조체는 기본적으로 모든 멤버 변수가 public으로 선언되며, 메서드가 포함되지 않는 경우가 많다. 이는 C++ 클래스와 유사하지만, 접근 제어에 차이가 있다. 

예시를 보자.

```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct Books { // struct 정의
    char title[50]; // 변수와 크기 선언
    char author[50];
    char subject[100];
    int book_id;
};

int main() {
    // struct 키워드는 선택 사항
    Books Book1; // Books 타입의 Book1 선언
    Books Book2; // Books 타입의 Book2 선언

    // Book1 정보 설정
    strcpy(Book1.title, "Learn C++ Programming"); // 내부 값에 변수 할당
    strcpy(Book1.author, "Chand Miyan");
    strcpy(Book1.subject, "C++ Programming");
    Book1.book_id = 6495407;

    // Book2 정보 설정
    strcpy(Book2.title, "Telecom Billing");
    strcpy(Book2.author, "Yakit Singha");
    strcpy(Book2.subject, "Telecom");
    Book2.book_id = 6495700;

    // Book1 정보 출력
    cout << "Book 1 title : " << Book1.title << endl;
    cout << "Book 1 author : " << Book1.author << endl;
    cout << "Book 1 subject : " << Book1.subject << endl;
    cout << "Book 1 id : " << Book1.book_id << endl;

    // Book2 정보 출력
    cout << "Book 2 title : " << Book2.title << endl;
    cout << "Book 2 author : " << Book2.author << endl;
    cout << "Book 2 subject : " << Book2.subject << endl;
    cout << "Book 2 id : " << Book2.book_id << endl;

    printBook(Book1);
    printBook(Book2);

    return 0;
}

void printBook(Books book) {
    cout << "Book title : " << book.title << endl;
    cout << "Book author : " << book.author << endl;
    cout << "Book subject : " << book.subject << endl;
    cout << "Book id : " << book.book_id << endl;
}
```

struct와 class의 기본적인 차이는 접근 제어이다.

struct는 기본적으로 `public`으로 제어되고, 클래스는 기본적으로 `private`로 제어된다. 이에 따라 둘의 사용 목적도 갈리게 된다. 

struct는 주로 데이터의 집합, 데이터 구조로 사용되는데 반해, class는 데이터와 해당 데이터를 처리하는 메서드를 함께 묶는다. 따라서 클래스는 상속, 다형성 등 객체 지향 프로그래밍의 모든 기능을 지원한다. 

### Class

클래스는 객체의 형태를 지정하기 위해 사용되며, 데이터 표현과 데이터를 조작하기 위한 메서드를 하나의 깔끔한 패키지로 결합한다. 클래스 내의 데이터와 함수는 클래스의 멤버라고 한다. 클래스는 객체 지향 프로그래밍의 핵심 개념으로, 데이터와 기능을 캡슐화하고 재사용성을 높이는 데 기여한다.

클래스 멤버는 접근 지정자에 따라 접근할 수 있는 범위가 달라진다.

C++에서는 `public`, `protected`, `private` 세 가지 접근 지정자를 사용할 수 있다.

클래스는 보통 `class`키워드로 선언되며, 클래스로 만들어진 인스턴스를 object라고 한다. 

두가지 예시를 보도록 하자. 

```cpp
#include <iostream>
#include <string>

class Books {
public:
    std::string title;
    std::string author;
    std::string subject;
    int book_id;

    // 멤버 함수 선언
    void printBookInfo();
};

// 멤버 함수 정의
void Books::printBookInfo() {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Subject: " << subject << std::endl;
    std::cout << "Book ID: " << book_id << std::endl;
}

int main() {
    Books Book1; // Books 클래스의 Book1 객체 생성
    Books Book2; // Books 클래스의 Book2 객체 생성

    // Book1 정보 설정
    Book1.title = "Learn C++ Programming";
    Book1.author = "Chand Miyan";
    Book1.subject = "C++ Programming";
    Book1.book_id = 6495407;

    // Book2 정보 설정
    Book2.title = "Telecom Billing";
    Book2.author = "Yakit Singha";
    Book2.subject = "Telecom";
    Book2.book_id = 6495700;

    // Book 정보 출력
    Book1.printBookInfo();
    Book2.printBookInfo();

    return 0;
}
```

class 내에 선언된 함수나 변수에 접근하기 위해선 `.`를 사용한다. 

다른 형식의 예시를 보자. 

```cpp
#include <iostream>
#include <string>
using namespace std;

class Books {
public:
    string title = "";
    string author = "";
    string subject = "";
    int book_id = 0;

    void printBook() {
        cout << "Book title : " << title << endl;
        cout << "Book author : " << author << endl;
        cout << "Book subject : " << subject << endl;
        cout << "Book id : " << book_id << endl;
    }
};

int main() {
    Books Book1; // Book1 객체 생성
    Books Book2; // Book2 객체 생성

    // Book1 정보 설정
    Book1.title = "Learn C++ Programming";
    Book1.author = "Chand Miyan";
    Book1.subject = "C++ Programming";
    Book1.book_id = 6495407;

    // Book2 정보 설정
    Book2.title = "Telecom Billing";
    Book2.author = "Yakit Singha";
    Book2.subject = "Telecom";
    Book2.book_id = 6495700;

    cout << "Class Example 2 ...\n";
    Book1.printBook();
    Book2.printBook();

    return 0;
}
```

난 이게 더 좋은듯? 

---

클래스에 함수를 추가하려면 어떻게해야할까? 클래스의 멤버 함수는 클래스 정의 내에 프로토타입이나 정의를 가지고 있는 함수이다. 이러한 멤버 함수는 클래스의 객체에 대해 작동하며, 해당 객체의 모든 멤버에 접근할 수 있다.

ㅇ가보자.

```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    // 속성
    string name;
    int age;

    // 생성자
    Animal(string n, int a) : name(n), age(a) {}

    // 멤버 함수
    void makeSound() {
        cout << name << " is making a sound!" << endl;
    }

    void printInfo() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    void birthday() {
        age++;
        cout << "Happy Birthday, " << name << "! You are now " << age << " years old." << endl;
    }
};

int main() {
    // Animal 객체 생성
    Animal animal1("Dog", 5);
    Animal animal2("Cat", 3);

    // 객체의 정보 출력
    animal1.printInfo();
    animal2.printInfo();

    // 객체의 행동 호출
    animal1.makeSound();
    animal2.makeSound();

    // 생일 함수 호출
    animal1.birthday();
    animal2.birthday();

    // 다시 객체의 정보 출력
    animal1.printInfo();
    animal2.printInfo();

    return 0;
}
```
어렵지 않다. 

#### Getter, Setter

C++에서 `public` 변수는 일반적으로 권장되지 않는다. 대신, 모든 변수를 `private` 또는 `protected`로 선언하고, 해당 변수에 접근하거나 수정할 수 있는 getter 및 setter 함수를 제공하는 것이 좋은 방법이다. 

* **Getter 함수**: 클래스 멤버 변수의 값을 반환한다.
* **Setter 함수**: 클래스 멤버 변수의 값을 설정한다.

이 둘을 추가하면 다음과 같은 형태가 된다.

```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    // Setter 함수
    void setAge(int age) {
        if (age >= 0) {
            itsAge = age;
        } else {
            cout << "Invalid age!" << endl;
        }
    }

    // Getter 함수
    int getAge() const {
        return itsAge;
    }

    // Getter 및 Setter 함수 추가
    void setName(const string &name) {
        itsName = name;
    }

    string getName() const {
        return itsName;
    }

    void setSpecies(const string &species) {
        itsSpecies = species;
    }

    string getSpecies() const {
        return itsSpecies;
    }

protected:
    int itsAge = 0;
    string itsName;
    string itsSpecies;
};

int main() {
    Animal animal1;

    // Setter 함수를 사용하여 속성 설정
    animal1.setAge(5);
    animal1.setName("Buddy");
    animal1.setSpecies("Dog");

    // Getter 함수를 사용하여 속성 출력
    cout << "Animal Info:" << endl;
    cout << "Name: " << animal1.getName() << endl;
    cout << "Species: " << animal1.getSpecies() << endl;
    cout << "Age: " << animal1.getAge() << endl;

    return 0;
}
```

### Constructor

Constructor는 클래스의 특별한 멤버 함수로, 클래스의 새 객체가 생성될 때마다 실행된다. Constructor는 클래스와 정확히 같은 이름을 가지며, 반환형이 없으며, 멤버 변수의 초기 값을 설정하는 데 매우 유용하다.

* **클래스와 동일한 이름**: 생성자는 클래스와 동일한 이름을 가져야 한다.
* **반환형이 없음**: 생성자는 반환형이 없으며, void조차도 사용하지 않다.
* **자동 호출**: 객체가 생성될 때 자동으로 호출된다.

다음과 같은 종류가 있다:

* **Default Constructor**: 매개변수가 없는 생성자.
* **Parameterized Constructor**: 매개변수를 받아 멤버 변수를 초기화하는 생성자.
* **Copy Constructor**: 다른 객체를 사용하여 새 객체를 초기화하는 생성자.

이 constructor는 클래스 외부에서도 정의할 수 있다. 이는 클래스의 인터페이스와 구현을 분리할 수 있게 한다.

```cpp
#include <iostream>
using namespace std;

// 클래스 정의 (인터페이스)
class Animal {
public:
    // 생성자 선언
    Animal(int age);
    Animal();
    
    // 멤버 함수 선언
    int getAge();
    
protected:
    int itsAge;
};

// 멤버 함수 정의 (구현)
int Animal::getAge() {
    return itsAge;
}

// 기본 생성자 정의
Animal::Animal() {
    cout << "simple animal creation ..." << endl;
    itsAge = 0;
}

// 매개변수가 있는 생성자 정의
Animal::Animal(int age) {
    cout << "complex animal creation ..." << endl;
    itsAge = age;
}

int main() {
    // 기본 생성자를 사용한 객체 생성
    Animal animal1;
    cout << "Animal1 age: " << animal1.getAge() << endl;

    // 매개변수가 있는 생성자를 사용한 객체 생성
    Animal animal2(5);
    cout << "Animal2 age: " << animal2.getAge() << endl;

    return 0;
}
```

#### Initialization list

초기화 리스트는 C++에서 클래스 멤버 변수를 초기화하는 데 사용되는 특별한 구문이다. 초기화 리스트는 생성자의 본문이 실행되기 전에 멤버 변수의 초기화를 수행한다. 이를 통해 멤버 변수의 초기화와 할당을 분리하지 않고 한 번에 처리할 수 있다. 

초기화 리스트는 콜론(:) 다음에 초기화할 멤버 변수와 그 초기값을 나열하는 방식으로 작성된다. 

이 초기화 리스트 없이 생성자를 정의하면 다음과 같은 형태이다.

```cpp
class Animal {
public:
    // 생성자 1
    Animal(int age) { itsAge = age; }
protected:
    int itsAge = 0;
};
```

초기화 리스트를 사용하면?

```cpp
class Animal {
public:
    // 생성자 1
    Animal(int age) : itsAge(age) { }
protected:
    int itsAge = 0;
};
```
멤버 변수 여러개를 넣을수도 있다.

```cpp
class ClassName {
public:
    ClassName(매개변수 목록) : 멤버변수1(초기값1), 멤버변수2(초기값2), ... {
        // 생성자 본문
    }
};

```

이 초기화 리스트를 사용하면 여러 장점이 있다. 예를 들어, 초기화 리스트를 사용하면 멤버 변수가 객체 생성 시점에 바로 초기화된다. 이는 불필요한 기본 초기화와 재할당을 방지할 수 있어 더 효율적이다. 또한 초기화 리스트는 객체 생성 시점에 멤버 변수를 초기화하므로 불필요한 기본 초기화와 재할당을 방지할 수 있다. 

이 초기화 리스트를 사용해야하는 상황이 두가지가 있다. 

1. 상수 데이터 멤버 초기화 (Initialization of non-static const data members)

상수 데이터 멤버는 객체가 생성된 후에는 값을 변경할 수 없기 때문에 초기화 리스트를 사용하여 생성 시에만 값을 설정할 수 있다. 

```cpp
#include <iostream>
using namespace std;

class Test {
public:
    // const 멤버 변수 't' 초기화
    Test(int x) : t(x) { }

    void print() const {
        cout << "t: " << t << endl;
    }

private:
    const int t; // const 멤버 변수
};

int main() {
    Test obj(10);
    obj.print();
    return 0;
}
```

2. 참조 멤버 초기화 (Initialization of reference members)

참조 멤버는 선언 시 반드시 초기화되어야 하며, 이후에는 다른 객체를 참조하도록 변경할 수 없다. 따라서 참조 멤버도 초기화 리스트를 사용하여 초기화해야 한다.


```cpp
#include <iostream>
using namespace std;

class Test {
public:
    // 참조 멤버 변수 'ref' 초기화
    Test(int &x) : ref(x) { }

    void print() const {
        cout << "ref: " << ref << endl;
    }

private:
    int &ref; // 참조 멤버 변수
};

int main() {
    int a = 20;
    Test obj(a);
    obj.print();
    return 0;
}
```

# Lecture 3

## Memorization

Memorization은 컴퓨터 프로그램에서 계산의 결과를 캐시에 저장하여 동일한 계산을 반복하지 않도록 하는 방법이다. 주로 재귀함수의 성능을 최적화하기 위해서 사용되며, 특히 다이나믹 프로그래밍에서 중요하게 사용된다. 특히, 피보나치에서 큰 성능 향상을 보인다. 이를 c++에서 적용하려면, 계산된 값을 저장할 array나 map을 사용해야한다. 

예시로써 피보나치를 구현해보도록 하자.

```cpp
#include <iostream>
#include <vector>

std::vector<int> memo;

int fib(int n) {
    if (n <= 1) {
        return n;
    }
    // 이미 계산된 값이 있으면 바로 반환
    if (memo[n] != -1) {
        return memo[n];
    }
    // 계산된 값을 memo 배열에 저장
    memo[n] = fib(n - 1) + fib(n - 2);
    return memo[n];
}

int main() {
    int n = 10;
    // memo 배열을 -1로 초기화 (아직 계산되지 않은 상태)
    memo.assign(n + 1, -1);
    std::cout << "Fibonacci of " << n << " is " << fib(n) << std::endl;
    return 0;
}
```

여기서는 벡터를 이용해 array를 구현했고, 매 계산 후 값을 글로벌 변수 memo에 저장한 뒤, 매 재귀 호출마다 memo에 값이 있는지 확인하고 있으면 그걸 들고온다. 

이런 메모라이제이션은 간단한 함수에서는 효과가 두드러지지 않을 수 있지만, 곱셈이나 덧셈이 큰숫자로 가게되면 계산 비용이 증가하게 되므로 메모라이제이션이 큰 효과를 나타낼 수 있다. 

## Destructor

이전 강의에서 Constructor에 대해 알아보았다. 그와 반대되는 개념인 Destructor는, **클래스의 특수한 멤버 함수**로써, 객체가 범위를 벗어날때나 `delete` expression이 그 클래스의 객체에 대한 **포인터**에 적용될 때 실행된다. **Destructor는 클래스와 동일한 이름을 가지며,** 앞에 `~`가 붙는다. **Destructor는 값을 반환할 수 없으며 매개변수를 가질 수도 없다.** 얘는 프로그램이 종료되기 전에 파일을 닫거나 메모리를해제하는 등 자원을 해제하는데 사용된다. 따라서 이는 자원 관리를 자동화하고 메모리 누수를 방지하는 중요한 역할을 한다.

예시를 통해 사용법을 알아보자.

```cpp
#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "Constructor called!" << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called!" << std::endl;
    }
};

int main() {
    MyClass obj; // Constructor called!
    // 객체가 범위를 벗어나면 Destructor가 호출된다.
    return 0;    // Destructor called!
}
```
여기서 객체가 범위를 벗어난다는 얘기는, 이 경우 `main`함수가 종료될 때 객체가 범위를 벗어나게 된다. 이때 destructor가 호출된다. destructor의 역할을 더 자세히 정리해보자.

* 동적 메모리 해제: 객체가 동적으로 할당된 메모리를 해제할 때 Destructor를 사용한다.
* 파일 닫기: 파일 입출력 작업이 끝난 후 파일을 닫을 때 Destructor를 사용한다.
* 네트워크 연결 종료: 네트워크 연결을 종료할 때 Destructor를 사용한다.
* 기타 자원 해제: 기타 시스템 자원을 해제할 때 Destructor를 사용한다.

동적 메모리를 해제하는 예시도 한번 살펴보자.

```cpp
#include <iostream>

class MyClass {
private:
    int* data;
public:
    MyClass(int size) {
        data = new int[size]; // new는 새로운 동적 메모리를 할당하는데 사용된다. 
        std::cout << "Memory allocated!" << std::endl;
    }

    ~MyClass() {
        delete[] data; // array를 할당했기 때문에, delete[]를 사용
        std::cout << "Memory deallocated!" << std::endl;
    }
};

int main() {
    MyClass obj(10); // Memory allocated!
    // 객체가 범위를 벗어나면 소멸자가 호출된다.
    return 0;       // Memory deallocated!
}
```

## Static members

클래스의 멤버를 `static`으로 선언하게 되면, 그 클래스의 객체가 몇개 만들어지든 간에 `static member`는 **단 하나의 복사본**만 존재하게 된다. **이 static member는 모든 객체에 의해 공유된다**. 다른 초기화가 없으면, 첫번째 객체가 생성될 때 모든 static data는 0으로 초기화된다. 

**static member는 반드시 클래스 내부에서 선언되어야 하며, 클래스 밖에서 초기화 되어야 한다.** 클래스 내부에서 초기화 될 수 없으며, 클래스 외부에서 초기화할땐 범위 지정 연산자 `::`를 사용하여 다시 선언함으로써 초기화할 수 있다. 

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    // 생성자 1 선언
    Animal(int age);
    // 생성자 2 선언
    Animal();
    // 소멸자 선언
    ~Animal();
    // 멤버 함수 선언
    int getAge();
    // static 멤버 변수
    static int animalCount;
    // static 상수 멤버 변수
    const static int MAXANIMALS = 10;
    // static member function, static vars에만 접근이 가능하다. 
    static int getAnimalCount () {
        return animalCount ;
    }
protected:
    int itsAge = 0;
};

// static 변수는 클래스 외부에서 초기화
int Animal::animalCount = 0;

// 멤버 함수 정의
int Animal::getAge() {
    return itsAge;
}

// 기본 생성자 정의, 클래스 외부에서 정의하는중이기 때문에, Animal::를 통해 내부에 접근
Animal::Animal() {
    animalCount += 1;
    cout << "simple animal creation ..." << endl;
}

// 매개변수가 있는 생성자 정의
Animal::Animal(int age) {
    animalCount += 1;
    cout << "complex animal creation ..." << endl;
    itsAge = age;
}

// 소멸자 정의
Animal::~Animal() {
    cout << "destroy an animal (painless!)" << endl;
    animalCount -= 1;

void func () { // 외부 함수에서 static member function에 접근
    Animal animal ;
    cout << "inside func we have " << Animal::getAnimalCount() << " animals " << endl;
}

int main () {
    Animal animal; // 객체 생성
    cout <<"Animal 1's age: " <<animal.getAge() << endl;
    Animal animal2(12); // 매개변수와 함께 객체 생성
    cout <<"Animal 2's age: " <<animal2.getAge() << endl;
    func();
    cout << "inside main we have " << Animal::getAnimalCount() << " animals " << endl;
}

}
```
```
simple animal creation ...
Animal 1's age: 0
complex animal creation ...
Animal 2's age: 12
simple animal creation ...
inside func we have 3 animals
destroy an animal (painless!)
inside main we have 2 animals
destroy an animal (painless!)
destroy an animal (painless!)
```

어떤 클래스 멤버 함수를 `static`으로 선언하게 되면, **해당 함수는 클래스의 특정 객체와 독립적으로 작동한다.** static 멤버 함수는 클래스의 객체가 존재하지 않더라도 호출할 수 있으며, static function은 클래스 이름과 `::`를 사용하여 접근한다. 예를 들어, `ClassName::staticFunction()`와 같은 형태이다. static member function은 static data member, 다른 static 멤버 함수 및 클래스 외부의 다른 함수에만 접근할 수 있다. 예를 들어, `ClassName::staticVar`와 같은 static 변수에만 접근이 가능하다.

## Const member function

이미, 변경되지 않는 변수를 생성할 때 `const`키워드를 사용한 적이 있다. 클래스 내의 멤버 함수에서도 `const`를 사용할 수 있다. **클래스 메서드를 `const`로 선언하면, 해당 메서드가 클래스의 어떤 멤버 변수 값도 변경하지 않을 것을 보장한다.** 클래스 메서드를 const로 선언하려면, 매개변수를 둘러싸는 괄호 뒤에 `const` 키워드를 넣고 메서드 선언을 끝내는 세미콜론 앞에 위치시키면 된다.

위에서 봤던 animal 클래스의 예시에 이를 추가해보자.

```cpp
class Animal {
public:
    Animal(int age);      
    Animal();             
    ~Animal();            
    int getAge() const;   // Const 멤버 함수로 선언된 나이를 반환하는 함수, 뒤에 const를 붙여준다. 
    void setAge(int age); // 나이를 설정하는 함수, 그냥 멤버함수임.
    static int animalCount; 
protected:
    int itsAge = 0;       // 동물의 나이를 저장하는 변수
};

int Animal::animalCount = 0;

int Animal::getAge() const { // const를 같이 집어넣어준다.
    return itsAge;
}

// setAge() 함수의 구현
void Animal::setAge(int age) {
    itsAge = age;
}

Animal::Animal() {
    animalCount += 1;
    cout << "simple animal creation ..." << endl;
}

Animal::Animal(int age) {
    animalCount += 1;
    cout << "complex animal creation ..." << endl;
    itsAge = age;
}

Animal::~Animal() {
    cout << "destroy an animal (painless!)" << endl;
    animalCount -= 1;
}
int main() {
    Animal animal;   // 기본 생성자를 사용하여 Animal 객체 생성
    cout <<"Animal 1's age: " << animal.getAge() << endl;  // 객체의 나이 출력

    animal.setAge(animal.getAge() + 1);  // 나이를 1살 증가시킴
    cout <<"Animal 1's age: " << animal.getAge() << endl;  // 증가된 나이 출력

    cout << "inside main we have " << Animal::animalCount << " animals " << endl;  // 전체 동물 수 출력

    return 0;
}
```
```
simple animal creation ...
Animal 1's age: 0
Animal 1's age: 1
inside main we have 1 animals 
destroy an animal (painless!)
```
이 예시에선 딱히 잘 안보이긴 하는데, 왜냐면 const 함수인 `getAge`함수가 어차피 아무것도 안바꾸기 때문이다. 암튼, 이런식으로 사용할 수 있다. 

## C++ std::string

`std::string`은  C++ 표준 라이브러리에서 제공하는 문자열 처리를 위한 클래스이다. 문자를 처리하는 다양한 기능을 제공한다. 

* **동적 크기 조정**: `std::string`은 문자열의 길이를 동적으로 조정할 수 있다. 필요에 따라 문자열의 길이를 늘리거나 줄일 수 있으며, 메모리 관리를 자동으로 처리한다.

* **문자열 저장**: `std::string`은 문자들의 시퀀스를 저장하는 데 사용된다. 이 클래스를 사용하면 문자열의 추가, 제거, 검색 등의 작업을 쉽게 수행할 수 있다.

* **유틸리티 함수**: `std::string`은 다양한 유틸리티 함수를 제공하여 문자열 처리를 간편하게 만듭니다. 예를 들어, 길이 반환, 문자 찾기, 부분 문자열 추출, 문자열 합치기 등이 가능하다.

* **문자열 비교**: `std::string` 객체들은 문자열을 비교하는 다양한 방법을 제공한다. ==, !=, <, <=, >, >= 연산자들을 사용하여 문자열 간 비교가 가능하다.

* **STL과의 통합**: `std::string`은 C++ 표준 라이브러리(STL)의 일부이며, 다른 STL 컨테이너와 함께 사용할 수 있다. 예를 들어, 벡터(vector), 리스트(list) 등의 컨테이너에 `std::string`을 요소로 저장할 수 있다.

* **간편한 초기화**: `std::string` 객체는 다양한 방법으로 초기화할 수 있다. 문자열 리터럴을 직접 할당하거나, 다른 `std::string` 객체나 C 스타일 문자열로부터 초기화할 수 있다.

`std::string`과 `std::vector`를 사용하여 문자열 처리와 검색을 수행하는 예시를 보도록 하자.

```cpp
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string::size_type n;  // 문자열의 인덱스를 저장할 변수
    std::string const s = "t PEX Homework";  // 상수 문자열 s
    std::vector<std::string> items = {  // 문자열을 저장하는 벡터 items
        "t PEX-Homework",
        "t PEX-Quiz",
        "p PEX-Homework"
    };
    std::vector<std::string> choices = {"t", "p", "d"};  // 선택지를 저장하는 벡터 choices

    // choices 벡터의 각 선택지에 대해 items 벡터를 순회
    for (auto c : choices) { // choices 내 각 벡터의 선택지를 순회
        for (auto item : items) {
            // item에서 선택지 c가 처음부터 시작하는 위치를 찾음
            n = item.find(c);
            if (n == 0) {
                // 선택지 c가 item의 첫 부분과 일치할 경우 출력
                std::cout << c << "-item: " << item << std::endl;
            }
        }
    }

    return 0;
}
```
```
t-item: t PEX-Homework
t-item: t PEX-Quiz
p-item: p PEX-Homework
```

이 방법을 사용하려면, `#include <string>`와 `#include <vector>`가 필요하다. `std::string::size_type`은 문자열의 인덱스를 저장하는 데이터 타입이다. 아주 쓸모가 많다. 

## Input, Output and File

Input과 output에 사용되는 여러 함수들을 보자. 이에는 보통 `fstream`과 `iostream` 헤더파일이 필요하다. 

iostream이란, 터미널과 interacting하는 것을 의미한다.

* `std::cout`: 터미널(표준 출력)에 출력을 작성하는 데 사용된다. 일반적으로 사용자에게 정보를 표시하는 데에 쓰이다.
    ```cpp
    std::cout << "안녕, 세상!" << std::endl;
    ```
* `std::cin`: 터미널(표준 입력)로부터 입력을 읽어오는 데 사용된다. 사용자가 입력한 데이터를 받기 위해 사용된다.
    ```cpp
    int number;
    std::cout << "숫자를 입력하세요: ";
    std::cin >> number;
    ```    

* `std::cerr`: 오류 메시지를 즉시 오류 채널(표준 오류)에 쓰기 위해 사용된다. std::cout과 달리, std::cerr로 쓰인 메시지는 버퍼링되지 않고 즉시 표시된다.
    ```cpp
    std::cerr << "오류: 파일을 찾을 수 없다!" << std::endl;
    ```
* `std::clog`: 오류 메시지를 오류 채널에 쓰지만, `std::cerr`와 달리 출력은 버퍼링된다. 이는 출력이 버퍼가 플러시되거나 프로그램이 종료될 때까지 지연될 수 있음을 의미한다.
    ```cpp
    std::clog << "경고: 메모리가 부족합니다!" << std::endl;
    ```


fstream은 파일에 대한 스트림 작업을 의미한다. C++의 `fstream` 라이브러리는 파일 입력 및 출력 작업을 다루는 클래스를 제공한다.

* `ofstream`: 출력 파일 스트림을 나타내며, 파일에 데이터를 쓰기 위해 사용된다. 새 파일을 생성하거나 기존 파일을 덮어쓸 때 주로 사용된다.
    ```cpp
    #include <fstream>

    std::ofstream outfile("output.txt"); // 쓰기 위해 파일 생성/열기
    if (outfile.is_open()) {
        outfile << "이 내용이 파일에 쓰여집니다.\n";
        outfile.close();
    }
    ```
* `ifstream`: 입력 파일 스트림을 나타내며, 파일에서 데이터를 읽기 위해 사용된다. 파일의 내용을 읽어야 할 때 사용된다.
    ```cpp
    #include <fstream>

    std::ifstream infile("input.txt"); // 읽기 위해 파일 열기
    std::string line;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::cout << line << std::endl; // 각 줄을 콘솔에 출력
        }
        infile.close();
    }
    ```
###  Opening a file

파일을 열기 위해서는 `<fstream>`를 포함해야하며, `std::ifstream`과 `std::ofstream`클래스를 사용하여 파일의 입출력을 처리한다.

```cpp
#include <fstream>

std::ofstream ofs; // 출력 파일 스트림 객체
std::ifstream ifs; // 입력 파일 스트림 객체

// 파일 열기
ifs.open("input.txt", std::ios::in); // 입력 파일 "input.txt"을 읽기 모드로 열기
ofs.open("output.txt", std::ios::out); // 출력 파일 "output.txt"을 쓰기 모드로 열기

// 파일 닫기
ifs.close(); // 입력 파일 닫기
ofs.close(); // 출력 파일 닫기
```

#### Openmode

`ios::openmode`는 파일을 열 때 사용할 여러 모드를 지정하는 열거형이다. 각각의 모드는 파일을 어떻게 열 것인지 결정한다. 

* `ios::app`: 파일의 끝에 데이터를 추가하는 모드이다. 이미 존재하는 파일에 쓸 때 유용하다.
```cpp
ofs.open("log.txt", std::ios::app); // log.txt 파일을 추가 모드로 열기
```

* `ios::ate`: 파일을 출력용으로 열고 파일의 끝으로 커서를 이동시키는 모드이다. 즉, 파일의 마지막 위치에서 시작하여 데이터를 쓸 수 있다.
```cpp
ofs.open("data.txt", std::ios::out | std::ios::ate); // data.txt 파일을 출력 및 끝에서 시작 모드로 열기
```
* `ios::in`: 파일을 읽기 모드로 연다.
```cpp
ifs.open("input.txt", std::ios::in); // input.txt 파일을 읽기 모드로 열기
```
* `ios::out`: 파일을 쓰기 모드로 연다. 파일이 이미 존재할 경우, 이 모드는 기존 파일의 내용을 지우고 새로 씁니다.
```cpp
ofs.open("output.txt", std::ios::out); // output.txt 파일을 쓰기 모드로 열기 (기존 내용 삭제됨)
```
* `ios::trunc`: 파일을 열기 전에 파일의 내용을 모두 삭제합니다. 주로 ios::out 모드와 함께 사용됩니다.
```cpp
ofs.open("data.txt", std::ios::out | std::ios::trunc); // data.txt 파일을 쓰기 및 내용 초기화 모드로 열기
```

아래는 사용 예시이다.

```cpp
#include <fstream>
#include <iostream>

int main() {
    // 파일 쓰기 예시
    std::ofstream outfile("output.txt", std::ios::out | std::ios::app);
    if (outfile.is_open()) {
        outfile << "Hello, ";
        outfile << "World!" << std::endl;
        outfile.close();
    } else {
        std::cerr << "파일을 열 수 없습니다!" << std::endl;
    }

    // 파일 읽기 예시
    std::ifstream infile("input.txt", std::ios::in);
    std::string line;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::cout << line << std::endl;
        }
        infile.close();
    } else {
        std::cerr << "파일을 열 수 없습니다!" << std::endl;
    }

    return 0;
}
```
`std::ios::out | std::ios::app`는 파일을 열 때 사용하는 모드 플래그이다. 이것은 OR 연산자를 사용, 두가지 플래그를 결합하여 파일을 열 때 동작을 지정한다. 

이를 통해, 파일을 쓰기 모드로 열되, 파일의 끝에 데이터를 추가할 수 있는 상태로 연다.

### Stringstream

스트림이라는 단어가 계속 나온다. 스트림이란 뭘까? 스트림(stream)은 데이터가 흐르는 통로라고 생각할 수 있다. C++에서 스트림은 입출력을 쉽게 다루기 위한 추상화된 개념이다. 주로 데이터를 읽어오거나 출력하는 작업에서 사용되며, 파일, 터미널, 메모리 등 다양한 소스와 대상으로 데이터를 전송할 수 있다. `<<`나 `>>` 또한 스트림 연산자이다. 

스트림은 내부적으로 버퍼를 사용하여 데이터를 일시적으로 저장하고, 효율적인 입출력을 위해 데이터를 묶어서 처리한다. 이 버퍼링은 입출력의 성능을 향상시키고, 프로그램의 실행 속도를 개선하는데 중요한 역할을 한다. 

`std::stringstream`은 문자열을 스트림으로 다룰 수 있게 해준다. 이는 `<sstream>` 헤더파일에서 제공된다. `std::stringstream` 객체는 문자열을 스트림처럼 다룰 수 있어서, 문자열에서 데이터를 읽어오거나 데이터를 문자열로 변환하는 데 쓰인다. 주로 입력 문자열을 파싱하거나, 다양한 형식의 데이터를 문자열로 만드는 작업에 활용된다.

```cpp
#include <iostream>
#include <sstream> // stringstream을 사용하기 위한 헤더 파일

int main() {
    std::string S = "Hello C++ World!";
    std::stringstream X(S); // 문자열 S를 stringstream X 객체에 연결

    std::string T; //  각 단어를 저장할 변수 T를 준비
    while (std::getline(X, T, ' ')) { // X에서 공백(' ')을 기준으로 문자열을 읽어 T에 저장
        std::cout << T << std::endl; // 각 단어를 출력
    }

    return 0;
}
```
```
Hello
C++
World!
```

### Filesystem

C++17에서 도입된 Filesystem 라이브러리는 Boost 라이브러리에서 가져온 핵심 부분들을 포함한다. 이 라이브러리는 파일 및 디렉터리 경로와 관련된 작업을 수행하며, 다음과 같은 주요 구성 요소들이 있다.

* **path object**: 파일 또는 디렉터리의 경로를 나타내는 객체이다.
* **directory_entry**: 디렉터리의 각 항목(파일 또는 하위 디렉터리)에 대한 정보를 제공하는 객체이다.
* **directory iterators**: 디렉터리 내의 파일 및 디렉터리를 반복적으로 탐색할 수 있는 반복자이다.
* **supportive functions**: 경로에 관한 정보, 파일 조작(복사, 이동, 생성 등), 파일 속성, 시간, 크기 등 다양한 작업을 수행할 수 있는 보조 함수들을 포함합니다.

예시 코드를 보자.

이 코드는 이전 버전의 컴파일러에 대한 호환성을 고려하여, 사용 가능한 파일시스템 지원에 따라 <filesystem> 또는 <experimental/filesystem> 헤더를 포함하고 있다.

```cpp
#include <iostream>
#include <version>

// 이전 버전의 컴파일러에서 파일시스템 라이브러리 지원 확인
#ifdef __cpp_lib_filesystem
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #error "no filesystem support ='("
#endif

int main() {
    std::cout << "current_path:\n" << fs::current_path() << "\nExists Makefile?: " << fs::exists("../Makefile") << std::endl;
    return 0;
}
```

* `current_path()`: `fs::current_path()` 함수는 현재 작업 디렉터리의 경로를 반환한다.

* `exists()`: `fs::exists("../Makefile")` 함수는 지정된 경로의 파일이나 디렉터리가 존재하는지 여부를 검사한다.

#### Preprocessor

위에서 나온 코드중에 처음보는 이상한것들이 있다. 이들은 preprocessor라는 것으로, 컴파일 이전 단계에서 실행되며 코드의 특정 부분을 컴파일 전에 처리하는데 사용된다. 차근차근 살펴보자. 

`#ifdef`은 "if defined"의 약자로, 지정된 심볼이 정의되어있는지 여부를 확인한다. 이 뒤에 따라온 `__cpp_lib_filesystem`은 C++ 표준 라이브러리에 파일시스템 지원이 포함되어 있는지 여부를 확인하는 매크로이다.  C++17부터 표준 라이브러리에 파일시스템이 포함되었으므로, 이 매크로는 C++17 이상에서는 정의된다. 나머지 `#elif`와 `else` 또한 기존과 동일한 역할을 수행한다. preprocessor의 경우, `#endif`를 통해 조건문을 종료해주어야 한다. 

`#error`는 뭘까? **preprocessor가 처리를 하다가 이 지시문을 만나면 컴파일을 중단하고 오류메세지를 출력한다.**

`namespace fs = std::filesystem;`는 파일시스템 라이브러리를 사용하기 위해 적절한 네임스페이스를 정의한다. C++17 이상에서는 `std::filesystem`를 사용하고, 그 이전 버전에서는 `std::experimental::filesystem`를 사용한다.

### Traversing a directory

Traversing a directory란 파일 시스템에서 특정 디렉터리 안에 있는 파일과 디렉터리들을 순차적으로 접근하고 조사하는 과정을 말한다. 이 과정은 주어진 디렉터리 안의 모든 파일과 하위 디렉터리를 찾고, 각각에 대해 필요한 작업을 수행하는 것을 포함한다. 위에서 언급한 `Filesystem` 라이브러리를 사용하여 제어가 가능하다. 

예시를 보자.

```cpp
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void DisplayDirTree(const fs::path& pathToShow, int level) {
    if (fs::exists(pathToShow) && fs::is_directory(pathToShow)) { // 1
        auto lead = std::string(level * 3, ' '); // 들여쓰기 공백 계산
        for (const auto& entry : fs::directory_iterator(pathToShow)) { // 2
            auto filename = entry.path().filename(); // 항목의 파일명 획득
            if (fs::is_directory(entry.status())) { // 3
                std::cout << lead << "[+] " << filename << "\n"; // 디렉터리인 경우 [+] 표시
                DisplayDirTree(entry, level + 1); // 재귀적으로 하위 디렉터리 순회
                std::cout << "\n";
            } else if (fs::is_regular_file(entry.status())) { // 4
                std::cout << lead << " " << filename << "\n"; // 파일인 경우 출력
            } else { // 5
                std::cout << lead << " [?]" << filename << "\n"; // 기타 상황 처리
            }
        }
    }
}

int main() {
    std::cout << "Directory test:\n";
    DisplayDirTree("test", 0); // "test" 디렉터리 순회
    return 0;
}
```

1. `fs::exists(pathToShow) && fs::is_directory(pathToShow)`는, 먼저 시작 디렉터리가 존재하는지 확인하고, 원하는 디렉토리인지 확인한다. 
2. `fs::directory_iterator(pathToShow)`를 이용하여 디렉토리 내의 각 항목을 반복적으로 처리한다. `const auto&`는 `entry`가 `fs::directory_entry` 객체에 대한 const 참조임을 나타낸다. 이는 `entry`를 통해 디렉터리 항목의 내용을 읽고 수정하지 않음을 보장한다. 
3. `fs::is_directory(entry.status())`를 사용하여 디렉터리인지 확인하고, 디렉터리라면 [+]를 추가하여 출력한다.
4. `fs::is_regular_file(entry.status())`를 사용하여 일반 파일인지 확인하고, 일반 파일이라면 파일명을 출력한다.
5. 기타 상황에서는 [?]를 추가하여 처리한다.

예를 들어, 만약 다음과 같은 구조가 있다면,
```
test/
├── dir1/
│   ├── file1.txt
│   └── file2.txt
├── dir2/
│   ├── subdir/
│   │   └── file3.txt
│   └── file4.txt
└── file5.txt
```
다음과 같이 출력한다.

```
Directory test:
[+] dir1
   file1.txt
   file2.txt

[+] dir2
   file4.txt

   [+] subdir
      file3.txt

file5.txt
```

### Get home directory

홈 디렉토리를 반환하는 함수의 예시를 한번 보자.

```cpp
#include <iostream>   // 표준 입력 및 출력을 위한 헤더 파일
#include <cstdlib>    // C 표준 라이브러리의 일부로, getenv 함수를 사용하기 위한 헤더 파일
#include <string>     // 문자열 관리를 위한 표준 라이브러리

namespace pex {
    std::string get_home_directory() {
        // get home directory Unix
        const char* homeDir = getenv("HOME");  // Unix 시스템에서 환경 변수 HOME을 통해 홈 디렉터리 경로 가져오기
        // Get home directory on Windows (untested)
        const char* userProfile = getenv("USERPROFILE");  // Windows 시스템에서 환경 변수 USERPROFILE을 통해 홈 디렉터리 경로 가져오기
        
        std::string result = "";  // 결과를 저장할 빈 문자열 초기화
        
        if (homeDir != nullptr) {
            result = homeDir;  // 환경 변수 HOME이 존재하면 그 값을 result에 할당
        } else if (userProfile != nullptr) {
            result = userProfile;  // 환경 변수 USERPROFILE이 존재하면 그 값을 result에 할당
        }
        
        return result;  // 홈 디렉터리 경로 반환
    }
}

int main() {
    std::cout << "PEX Home: " << pex::get_home_directory() << std::endl;  // PEX Home: 와 함께 홈 디렉터리 경로 출력
    return 0;  // 프로그램 정상 종료
}
```

### Formatted Output

Formatted Output은 프로그래밍에서 특정 형식에 맞추어 데이터를 문자열로 변환하여 화면에 출력하는 과정을 말한다. C++에서는 여러 가지 방법으로 포맷팅된 출력을 구현할 수 있다. 

1. **`std::cout`을 이용한 포맷팅**
     - C++의 기본 출력 스트림인 `std::cout`을 사용하여 데이터를 화면에 출력할 수 있다.
     - `std::setw`, `std::setprecision`, `std::fixed` 등의 맨니퓰레이터(manipulator) 함수들을 이용하여 출력 포맷을 지정할 수 있다.
       ```cpp
       #include <iostream>
       #include <iomanip>

       int main() {
           double number = 3.141592653589793;
           std::cout << std::setprecision(4) << std::fixed << number << "\n";
           return 0;
       }
       ```

2. **C 스타일의 `printf` 함수**
    ```cpp
    #include <cstdio>

    int main() {
        int number = 42;
        printf("The answer is %d.\n", number);
        return 0;
    }
    ```

3.  **현대적인 방법: `fmt` 라이브러리**
      - C++11 이상에서는 `fmt` 라이브러리를 사용하여 더욱 간편하고 강력한 포맷팅 기능을 제공받을 수 있다.
      - Python의 포맷 문자열과 유사한 형태로 포맷팅을 지원하며, 타입에 맞추어 자동으로 변환한다.
        ```cpp
        #include <string>
        #include <fmt/core.h>

        int main() {
            int number = 42;
            std::string s = fmt::format("The answer is {}.\n", number);
            fmt::print(s);
            return 0;
        }
        ```

      - `{}`를 사용하여 변수를 삽입하고,` fmt::format` 함수를 통해 포맷 문자열을 생성한다.
      - `fmt::print` 함수를 사용하여 포맷 문자열을 출력한다.

4. **C++20에서의 표준 포맷팅**

    - C++20에서는 std::format 함수가 추가되어, 포맷 문자열의 표준 기능이 제공된다. 파이썬의 f-string과 유사한 형태.
  
        ```cpp
        #include <format>

        int main() {
            int number = 42;
            std::string s = std::format("The answer is {}.\n", number);
            std::cout << s;
            return 0;
        }
        ```
    - `std::format` 함수를 사용하여 포맷 문자열을 생성하고, `std::cout`을 통해 출력한다.

# Lecture 4

## Inheritance

C++ 또한 객체지향 프로그래밍을 지원한다. 따라서 inheritance를 사용할 수 있다. 

Base Class와 Derived Class로 나뉘게 되는데, 아래 예시를 통해 알아보자. 

```cpp
class A {
    public:
        int x;
    protected:
        int y;
    private:
        int z;
    };
class B : public A {
// x is public
// y is protected
// z is not accessible
};
class C : protected A {
// x is protected
// y is protected
// z is not accessible
};
class D : private A {
// 'private' is default
// for classes
// x is private
// y is private
// z is not accessible
};

```

```cpp
DerivedClass : public BaseClass {
// derived class has the same interface as the
// BaseClass, it can implement more methods.
};
DerivedClass : protected BaseClass {
// class inheriting from DerivedClass has access to
// all protected/public (now protected) methods of BaseClass
// objects created from derived class have no!
// access to methods and properties in BaseClass
};
DerivedClass : private BaseClass {
// class inheriting from DerivedClass has access to
// all protected/public (now private) methods of BaseClass
// object created from derived class have no!
// access to methods and properties in BaseClass
};

```

C++에서는 Base Class를 public, protected 또는 private로 선언함으로써 이게 어떻게 inherited 될 것인지 컨트롤 할 수 있다. 

Derived Class의 객체는 Base 클래스의 public으로 선언된 모든것들에 접근이 가능하다. 만약 베이스 클래스에서 protected로 선언된 것들이 있다면, derived class의 객체는 일단 접근이 가능하다. 사용은 가능하단 뜻이다. 그러나, 외부 코드나 베이스 클래스의 보호된 멤버에는 직접 접근할 수 없다. 즉, derived 클래스의 객체는 그 객체가 속한 클래스 내에서만 베이스 클래스의 protected member를 사용할 수 있다.

private 멤버의 경우, 애초에 상속이 불가능하며, 클래스 외부에서 접근할 수 없다. 

Animal 클래스의 더 자세한 예시를 보자. 

```cpp
#include <iostream>
class Animal {
public:
    void run() { std::cout << "Run, run, run!\n"; }
    void eat() { std::cout << "Eating generic food!\n"; }
};

class Cat : public Animal {
public:
    void meow() {
        std::cout << "Meow, meow!\n";
    }
};
// we have run automatically as we used: public Animal
// 자동으로 부모클래스의 run과 eat 함수를 가진다. 
// 새로운 함수를 추가할 수 있다.

// private inheritance is the default
// which is different to Python where public is the default
class Dog : private Animal {
public:
    void wuff() {
        std::cout << "Wuff, wuff!\n";
    }
// Animal 클래스를 private로 상속받았기 때문에, 외부에서 run, eat 함수를 호출할 수 없다.
// we must reimplement run and call Animal::run()
// by the Dog::run() method
    void run() {
        Animal::run(); // Animal 클래스의 run() 메서드 호출
        // 외부에서 접근이 불가하기 때문에, 이렇게 클래스 내부에서 재 구현 하여 사용해야한다.
    }
};


int main() {
    Cat mike = Cat();
    Dog fido = Dog();

    mike.run();   // Cat 클래스에서 상속받은 run() 메서드 호출
    mike.eat();   // Animal 클래스에서 상속받은 eat() 메서드 호출
    mike.meow();  // Cat 클래스의 meow() 메서드 호출

    fido.run();   // Dog 클래스에서 재구현한 run() 메서드 호출
    // fido.eat(); // 컴파일 오류: private 상속으로 인해 eat() 메서드 접근 불가
    fido.wuff();  // Dog 클래스의 wuff() 메서드 호출
}
```

### Base Class Constructor

```cpp
#include <iostream>
#include <string>

class Animal {
protected:
    std::string name;

public:
    Animal(std::string name) { // constructor
        this->name = name;
    }

    void run() {
        std::cout << this->name << " runs! ";
    }
};

class Cat : public Animal {
public:
    Cat(std::string name) : Animal(name) { } // 부모클래스의 생성자를 불러온다. super.와 비슷하다고 생각하면 될 듯

    void meow() {
        std::cout << this->name << " says meow!\n";
    }
};

int main(int argc, char *argv[]) {
    Cat micky("Micky");

    micky.run();   // "Micky runs! " 출력
    micky.meow();  // "Micky says meow!" 출력
}

```

### Composition

그렇지. Inheritance가 나왔으면 Composition도 있어야겠지? 

Part-of 관계를 가진다. inheritance는 is-a 관계였고. 

객체들간의 강한 소유 관계가 필요할 때 사용한다. 또한, 기본 베이스 클래스에서 다는 필요없고 일부 메서드만 필요한 경우 상속보다는 composition을 통해 필요한 것만 빼올 수 있다. 그냥 import하면 안되나..? 

암튼, 베이스 클래스의 일부 메서드를 외부에 감추고자 할 때나, 여러 구성요소로 메서드를 위임하고자 할때 사용할 수 있다.

파이썬에서의 예시를 보자. 

```python
class Tail:
    def wag(self):
        print('Wag, wag!')
    class Dog:
        def __init__(self,name,breed):
        self.tail=Tail() # component
        self.name=name
        self.breed=breed
        self.confidence=0
    def chase(self,thing):
        print(self.name,' chases ',thing)
        print('Wuff! Wuff!', end=' ')
        self.tail.wag()
        self.confidence=self.confidence+1
    def getConfidence(self):
        if self.confidence > 3:
            return('confidence of '+ self.name+' is good!')
        else:
            return('confidence of '+ self.name+' is ok!')

fido=Dog('Fido','Australian Shepherd')
for cat in ['Susi','Kathi', 'Moritz']:
    fido.chase('cat '+cat)
print(fido.getConfidence())
fido.chase('Student Martin')
print(fido.getConfidence())
print(fido.tail.wag()) # bad style
```
파이썬에선 대충 요런식으로 썻었다. 

C++에서도 사용 방법은 동일하다. 

```cpp
#include <iostream>
#include <string>
class Tail {
public:
    void wag () { std::cout << "Wag, wag!" << std::endl; }
};
class Dog {
public:
    Dog(std::string name, std::string breed);
    int getConfidence () const { return(confidence); }
    void chase (std::string thing);
protected:
    int confidence = 0;
    std::string itsName ;
    std::string itsBreed;
    Tail itsTail;
};
Dog::Dog(std::string name, std::string breed) { // constructor
    itsName = name;
    itsBreed=breed;
    itsTail = Tail(); // composition, dog 클래스의 멤버로 tail 클래스를 가져온다
                    // 명백한 has-a relationship
}
void Dog::chase (std::string thing) {
    std::cout << itsName << " chases "<<thing<< "!"<<std::endl;
    itsTail.wag();
    confidence += 1;
}
int main () {
    Dog fido("Fido PEX XXII","Australian Shepherd");
    fido.chase("Kathi PEX XXII");
    std::cout<<"Fido confidence: "<<fido.getConfidence()<<std::endl;}
```

### Multiple Inharitance

하나의 클래스가 여러개의 다른 클래스로부터 상속을 받을 수 있다. 파이썬에서도 가능했고 했지만, c++에서는 지양되는 방식중 하나이다. 왜냐면 다이아몬드 문제를 일으킬 수 있기 때문이다. 

만약 두개의 클래스 a,b 를 상속받을때, 이 둘 모두 하나의 동일한 클래스 c로부터 상속받는 중이라면, c클래스의 멤버가 중복될 수 있다. 이러면 충돌이 일어난다.

따라서, 이를 해결하기위해 C++에서는 virtual inheritance를 지원한다.

Multiple inheritance를 사용하여 Mixin을 사용할수도 있지만, Multiple inheritance 자체를 사용하는건 되도록이면 지양하자. 

그래도 예시는 보고 가야지?
```cpp
#include <iostream>
using namespace std;
class Bird {
public:
    void fly () {
    cout << "I believe I can fly ..." << endl;
    }
    void beat () { // can't have eat in Bird and Horse
    cout << "Mhmm, dendrobena ..." << endl; // ?
    }
    };
class Horse {
public:
    void run () {
    cout << "Run, run, run, ..." << endl;
    }
    void heat () { // can't have eat in Bird and Horse
    cout << "Mhmm, apples ..." << endl;
    }
};
class Pegasus : public Bird, public Horse {
public:
    void whoami () {
    cout << "Pegasus" << endl;
    }
};
int main () {
    Pegasus pegi;
    pegi.fly();
    pegi.run();
    pegi.beat(); // can't have eat in Bird and Horse
    pegi.heat(); // can't have eat in Bird and Horse
    pegi.whoami();
}
```

### Abstract Class

Abstract class는 위에서 언급한 가상함수를 사용하는 예이다. abstract class는 인터페이스를 정의하게 되는데, 자식 클래스에서 구현될 메서드들의 집합을 먼저 선언하고, 이들 메서드는 인터페이스를 따르는 모든 객체에 대해 동일한 방식으로 호출될 수 있다. 

abstract class는 하나 이상의 pure virtual function를 포함하는데, `virtual` 키워드와 함께 `= 0`으로 정의되는 함수이다. 이 함수는 abstract class 내에서 구현되지 않으며, 파생 자식 클래스에서 반드시 override되어야 한다. 또한, 자식 클래스는 반드시 이것을 정의하고 넘어가야 한다. 이는 프로그램의 일관성을 유지시키며, 템플릿 역할을 수행할 수 있다. 

abstract class는 pure virtual function 외에도 일반적인 멤버 함수나 데이터 멤버를 포함할 수 있다. 이들은 기본적인 동작을 제공하거나, 파생 클래스에서 공통적으로 사용할 수 있는 기능을 제공한다. 

```cpp
#include <iostream>

// 추상 클래스 Animal 정의
class Animal {
public:
    // 순수 가상 함수 pure virtual function
    virtual void sound() const = 0;  // 동물의 소리를 출력하는 함수
    virtual void eat() = 0;          // 동물이 먹이를 먹는 함수
    
    // 일반 멤버 함수
    void sleep() {
        std::cout << "Animal is sleeping" << std::endl;
    }
};

// 추상 클래스 Animal을 상속받는 파생 클래스 Dog 정의
class Dog : public Animal {
public:
    // 순수 가상 함수를 오버라이드하여 구현
    void sound() const override {
        std::cout << "Woof!" << std::endl;
    }
    void eat() override {
        std::cout << "Dog is eating bones" << std::endl;
    }
};

int main() {
    // Animal은 추상 클래스이므로 직접 객체를 생성할 수 없음
    // Animal animal; // 컴파일 오류: 추상 클래스의 객체 생성 불가

    Dog dog;
    dog.sound();  // Dog 클래스에서 구현한 sound 함수 호출
    dog.eat();    // Dog 클래스에서 구현한 eat 함수 호출
    dog.sleep();  // Animal 클래스에서 상속받은 sleep 함수 호출

    return 0;
}
```

### Mixin

C++에는 딱히 mixin이라는 기능이 없다. 하지만 multiple inheritance를 사용해서 mixin기능을 흉내낼 수 있다. 

Mixin 클래스의 경우, 일반적으로 인스턴스화되면 안된다. multiple inheritance를 사용하기 때문에 인스턴스화가 될 수 있지만, 하면 안된다. 


Mixin 클래스는 다른 클래스에서 필요한 기능을 제공하기 위해 포함될 수 있다. 

예시를 보자!

```cpp
#include <iostream>
#include <string>

class Person {
private:
    float km = 0;
public:
    void eat() { std::cout << "I am eating every day ...!\n"; }
    void run(float km) {
        this->km = this->km + km;
        std::cout << "running " << getKm() << "km!" << std::endl;
    }
    int getKm() { return static_cast<int>(this->km); }
};

class Cat {
public:
    void eat() { std::cout << "I am eating mice! \n"; }
};

class SingerMixin { // Mixin, 메서드가 하나 정의되어있다. 
protected:
    std::string song = "Lala, lalalaaaa!\n";
public:
    void sing(int n = 1) {
        for (int i = 0; i < n; i++) {
            std::cout << song;
        }
    }
};

class SingingPerson : public Person, public SingerMixin { }; // mixin 사용

class SingingCat : public Cat, public SingerMixin { // mixin을 다중상속 받는다. 
public:
    SingingCat() { song = "Meow - I love Lasagne!\n"; }
};

int main() {
    SingingPerson bob;
    bob.eat();
    bob.sing();
    bob.run(2.5);
    std::cout << "Bob ran " << bob.getKm() << "km!" << std::endl;

    SingingCat garfield;
    garfield.eat();
    garfield.sing(5); // mixin으로 받은 함수를 사용할 수 있다. 

    return 0;
}
```


### Virtual Functions

코드의 polymorphism을 구현하는 주요 매커니즘 중 하나이다. 이를 사용하면 상속관계에서 동일한 메서드의 이름을 사용하면서 각각의 클래스에 맞는 특정 동작을 구현할 수 있다. 

`virtual` 키워드를 통해 정의될 수 있으며, 파생 클래스에서는 이걸 오버라이딩해서 사용한다. 오버라이딩 할때는 함수 뒤에 `override`라는 키워드를 포함해야하며, **함수의 이름, 매개변수 형식, 반환 유형 또한 동일해야한다.** 

```cpp
#include <iostream>

class Animal {
public:
    void eat() {
        std::cout << "I'm eating generic food. ";
    }
};

class Cat : public Animal {
public:
    void eat() { 
        std::cout << "I'm eating a rat. "; 
    }
};

// Function which gets an object as argument!!
void gomensa(Animal& xyz) { 
    xyz.eat(); 
}

int main () {
    Animal ani = Animal();
    Cat cat = Cat();
    
    ani.eat(); // Outputs: "I'm eating generic food."
    cat.eat(); // Outputs: "I'm eating a rat."
    
    std::cout << std::endl << "But in the mensa: " << std::endl;
    gomensa(ani);
    gomensa(cat); // Now it outputs: "I'm eating a rat."
    
    return 0;
}

```

가상함수를 이용하여 다음의 문제를 해결하는 과정을 살펴보도록 하자.

```cpp
#include <iostream>

class Animal {
public:
    void eat() {
        std::cout << "I'm eating generic food. ";
    }
};

class Cat : public Animal {
public:
    void eat() {
        std::cout << "I'm eating a rat. ";
    }
};
void gomensa(Animal xyz) { 
    xyz.eat(); 
}

// we add another func for cats' but that is tedious ...
void gomensa(Cat xyz) { 
    xyz.eat(); 
}
int main() {
    auto ani = Animal(); // or Animal animal = Animal();
    auto cat = Cat();
    
    ani.eat();
    cat.eat();
    
    std::cout << "Now in the mensa: " << std::endl;
    
    gomensa(ani);
    gomensa(cat);
}
```

이 코드에는 문제가 있다. 딱히 문제가 없어 보이지만, 출력을 해보면 알 수 있다. 
```
I'm eating generic food. I'm eating a rat. Now in the mensa:
I'm eating generic food. I'm eating a rat.
```
우리는 먼저 `Animal`과 `Cat`클래스의 객체를 하나씩 생성한다. 두 클래스에서는 모두 각각 `eat()`이라는 이름의 함수가 정의되어 있다. Cat의 eat은 Animal로부터 상속받은 것이다. 

우리의 main 함수에서, 우리는 `ani.eat()`과 `cat.eat()`에서 우리가 기대했던대로 각각의 클래스에서 정의된 함수가 잘 작동하는것을 볼 수 있다.

또한, 클래스의 외부에서, 각각 Cat을 받았을때와 Animal을 받았을때 따로따로 각각의 클래스 멤버 함수를 호출하는 함수를 정의했다. 이후 main 함수에서 우리가 `gomensa(ani)`와 `gomensa(cat)`을 호출했을 때, 위 두 함수와 같은 기능을 하길 기대할 수 있다. 

그러나 이것을 하려면 모든 객체의 클래스에 대해 클래스 외부에서 각각 해당하는 클래스 만큼의 추가적인 함수를 정의해야한다는 문제가 있다. 사실 이런게 한두개면 상관이 없는데, 한 대여섯개를 넘어가는 순간 매우 귀찮고 비효율 적인 작업이 될 것이다. 이것을 **virtual function**를 이용한 **dynamic binding**으로 해결할 수 있다. 

첫번째 과정을 보자.

#### Using Pointer and Reference

```cpp
#include <iostream>

class Animal {
public:
    virtual void eat() {
        std::cout << "I'm eating generic food. ";
    }
};

class Cat : public Animal {
public:
    void eat() override {
        std::cout << "I'm eating a rat. ";
    }
};
void gomensa(Animal *xyz) {
    xyz->eat();
}

int main() {
    auto *ani = new Animal();  // Animal 객체의 포인터 생성
    auto *cat = new Cat();     // Cat 객체의 포인터 생성
    auto cat2 = Cat();         // Cat 객체 생성 (포인터 아님)
    
    ani->eat();   // "I'm eating generic food. "
    cat->eat();   // "I'm eating a rat. "
    cat2.eat();   // "I'm eating a rat. "
    
    std::cout << std::endl << "Now: " << std::endl;
    
    gomensa(ani);      // "I'm eating generic food. "
    gomensa(cat);      // "I'm eating a rat. "
    gomensa(&cat2);    // "I'm eating a rat. " (주소를 전달)
}

```
```
I'm eating generic food. I'm eating a rat. I'm eating a rat.
Now:
I'm eating generic food. I'm eating a rat. I'm eating a rat.
```

이 예시에서, 우리는 `gomensa()`함수를 단 하나만 정의했다. 그리고, 이 함수의 파라미터에 우리는 `Animal *xyz`, 즉 포인터를 사용했다. 이 경우, `gomensa`함수는 `Animal`타입의 포인터를 매개변수로 받아, 해당 객체의 `eat()`함수를 호출한다. 포인터를 사용함으로써, 객체의 실제 타입에 따라 올바른 가상함수가 호출된다.

레퍼런스를 사용해서도 구현이 가능하다.

```cpp
void gomensa(Animal& xyz) { // 참조자로 변경
    xyz.eat();
}
```

#### Using Template and Auto

위의 형태를 Template 혹은 Auto로도 사용할 수 있다. 

```cpp
#include <iostream>

class Animal {
public:
    void eat() {
        std::cout << "I'm eating generic food. ";
    }
};

class Cat : public Animal {
public:
    void eat() {
        std::cout << "I'm eating a rat. ";
    }
};
template <typename T>
void gomensa(T xyz) {
    xyz.eat();
}
int main() {
    auto ani = Animal();
    auto cat = Cat();

    ani.eat();    // "I'm eating generic food. "
    cat.eat();    // "I'm eating a rat. "

    std::cout << std::endl << "Now: " << std::endl;

    gomensa(ani); // "I'm eating generic food. "
    gomensa(cat); // "I'm eating a rat. "

    return 0;
}
```
`gomensa(ani)`는 `Animal`객체를 전달하여 템플릿 함수가 `Animal`타입으로 인스턴스화 된다. `gomensa<Animal>(ani)`와 동일하게 동작하며, 제네릭 푸드를 출려한다.

마찬가지로, `gomensa(cat)`은 `Cat`을 전달하여 템플릿 함수가 `Cat`타입으로 인스턴스화 된다. `gomensa<Cat>(cat)`으로 작동한다. 

```cpp
#include <iostream>
class Animal {
public:
    void eat() {
        std::cout << "I'm eating generic food. " ;
    }
};

class Cat : public Animal {
public:
    void eat() { std::cout << "I'm eating a rat. "; }
};

void gomensa(auto xyz) { xyz.eat(); } // 객체의 클래스에 해당하는 함수를 불러오고, 객체를 자동 인식

int main () {
    auto ani = Animal();
    auto cat = Cat();
    ani.eat();
    cat.eat();
    std::cout << std::endl <<"Now: " << std::endl;
    gomensa(ani);
    gomensa(cat);
}
```
당연히? auto도 잘 작동한다. auto가 그리고 제일 간단하다. auto 쓰자 그냥. 

## Stylistic rules

스타일리스틱 룰은 일관성있고 가독성 높은 코드를 작성하기 위한 지침이다. 

1. 클래스를 여러개 만들고 싶으면, 클래스 마다 별도의 파일을 작성한다. 또한, 클래스의 이름과 파일 이름을 일치시킨다. 
2. 소스파일과 헤더파일의 확장자를 다르게 사용한다. 소스파일의 경우 `.cpp`, `.cxx`, `.cc`가 될 것이고, 헤더파일은 `.h`, `.hpp`, `.hxx`가 될 것이다.
3. 클래스의 이름은 대문자로 시작한다.
4. 객체의 이름은 소문자로 시작한다. 예) `Animal fido("Fido")`
5. 긴 이름은 CamelCase 또는 Under_Scores를 사용한다.
6. 모든 상수는 대문자로 작성한다. 예) `const int MAX_SPEED = 100;`
7. `#define`의 사용을 피하고, 웬만하면 `const`를 사용한다.
8. 네임스페이스를 잘 사용하자.
9. multiple inheritance의 사용을 피한다.
10. 파일 시작 부분에 라이선스와 작성자 정보를 추가한다.

## Regex

교수님이 사랑해 마지않는, Regex와 CLA의 시간이 돌아왔다. 

C++에서 Regex를 사용하기 위해선, `<regex>`헤더파일이 필요하다. 
```cpp
#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char **argv) {
    regex rxFullname("[A-Z][a-z]+ [A-Z][a-z]+");
    string name;
    
    cout << "Enter your full name: " << flush;
    getline(cin, name);  // 전체 입력 줄을 읽습니다.

    //string name = "Detlef Groth";
    //cout << "Enter you full name: " << flush;
    //cin >> name;
    // cin은 공백을 기준으로 입력을 분리하기 때문에 전체 이름을 제대로 읽지 못한다.
    // getline을 사용하여 전체 입력 줄을 읽는 것이 권장된다. 
    
    if (!regex_match(name, rxFullname)) {
        cout << "\nError: Name not entered correctly, your name is '" << name << "'??" << endl;
    } else {
        cout << "Great, you entered the name correctly as: " << name << endl;
    }
    
    return 0;
}
```

자 그러면 다시한번 Regex의 syntax에 대해 차근차근 알아보도록 하자.

- `[]`: 문자 클래스를 나타내며, 대괄호 안에있는 문자 중하나와 일치 하는지를 검사한다. 예를들어 `[abc]`는 a, b, c 중 하나와 일치하는지 검사한다.
- `.`: 어떤 문자 하나와 일치하는지를 찾는다. `a.`는 `ab`, `ac`등이 될 수 있다.
- `?`: 직전의 패턴이 없는지 본다.
- `*`: 직전의 패턴이 있을 수 있다. 0회 이상.. 
- `+`: 직전의 패턴이 1회 이상 반복된다. 
- `|`: OR 연산을 나타내며, 왼쪽 또는 오른쪽의 패턴 중 하나와 일치하는지 검사한다.
- `{}`:반복 횟수를 지정한다. `{n}`은 정확히 n번 반복을 나타내고, `{m,n}`은 최소 m번에서 최대 n번 반복을 나타낸다.
- `()`: 그룹을 지정한다. 그룹화된 패턴은 후속작업에서 참조할 수 있다. 
- `\s` 공백, `\t` 탭, `\n` 줄바꿈, `\w` 단어 문자 (소문자, 대문자, 숫자, 밑줄을 포함)


Unix/Linux 환경에서 Regex의 이용은 필수이다. 이게없으면 돌아가질 않는다. 

Regex는 보통 `grep`명령어와 자주 함께 쓰이는데, 기본 형식은 다음과 같다.

```bash
grep [options] pattern [filename(s)]
```
여기에 이제 `-E` 옵션을 붙이면 Regex를 사용할 수 있다.

```bash
grep -E "regex" filename(s)
```
이 명령어는 "regex"라는 단어가 포함된 모든 라인을 출력한다. 

`egrep`은 `grep -E`의 축약형으로, 위에 말한 기능을 수행한다. 

아래 사용 예시를 보자. 

1. **“A”**: standard IUPAC one-letter codes
   - `"A"`는 특정한 IUPAC 아미노산 코드를 나타내며, 여기서는 Alanine (알라닌)을 나타냅니다.

2. **“.”**: position where any aa is accepted
   - `"."`은 어떤 아미노산이든 허용되는 위치를 나타냅니다. 즉, 어떤 한 문자에 대응됩니다.

3. **“[ALT]”**: ambiguity any of Ala or Leu or Thr
   - `"[ALT]"`는 Ala (Alanine), Leu (Leucine), Thr (Threonine) 중 하나에 대응됩니다. 즉, 이 위치에서는 이 세 가지 아미노산 중 하나가 올 수 있습니다.

4. **“[^AL]”**: negative ambiguity any aa but not! Ala or Leu.
   - `"[^AL]"`은 Ala (Alanine) 또는 Leu (Leucine)이 아닌 다른 아미노산을 나타냅니다. 즉, 이 위치에서는 Ala와 Leu를 제외한 다른 아미노산이 올 수 있습니다.

5. **“.{2,4}”**: repetition. two to four amino acids of any type
   - `".{2,4}"`는 어떤 아미노산이든 2개에서 4개까지의 문자열에 대응됩니다. 즉, 2개 이상 4개 이하의 아미노산이 올 수 있습니다.

6. **“L{3}”**: exactly three Leu
   - `"L{3}"`은 정확히 세 번의 Leucine (Leu)을 나타냅니다. 따라서 "LLL"과 같은 패턴에 매칭됩니다.

7. **“L{2,4}”**: two to four Leu, why not :)
   - `"L{2,4}"`는 Leucine (Leu)가 2개에서 4개까지 나타날 수 있는 패턴을 나타냅니다. 따라서 "LL", "LLL", "LLLL"과 같은 패턴에 매칭됩니다.

8. **“+”**: one or more, X+ == X{1,}
   - `"+"`는 바로 앞의 패턴이 한 번 이상 반복됨을 나타냅니다. 즉, "X+"는 "X"가 한 번 이상 나오는 패턴을 의미합니다.

9. **“*”**: zero or more, X* == X{0,}
   - `"*"`는 바로 앞의 패턴이 0회 이상 반복됨을 나타냅니다. 즉, "X*"는 "X"가 0회 이상 나오는 패턴을 의미합니다.

10. **“?”**: zero or one, X? == X{0,1}
    - `"?"`는 바로 앞의 패턴이 0회 또는 1회 나오는지를 나타냅니다. 즉, "X?"는 "X"가 0회 또는 1회 나오는 패턴을 의미합니다.

11. **“^M”**: N terminal Met
    - `"^M"`은 문자열의 시작 부분에 있는 Met (Methionine)을 나타냅니다. 즉, 문자열이 "M"으로 시작하는지를 검사합니다.

12. **“A$”**: C terminal Ala
    - `"A$"`은 문자열의 끝 부분에 있는 Ala (Alanine)을 나타냅니다. 즉, 문자열이 "A"로 끝나는지를 검사합니다.


### regex functions

Regex를 사용하는데 유용한 functions들이 있다. 이 형태는 파이썬과 비슷하지만 조금 다르므로 자세히 알아보자. 

1. **`std::regex_match`**
   - **설명**: 문자열 전체가 정규 표현식과 일치하는지 여부를 확인합니다.
   - **기본 형태**: 
   - **사용 예시**:
     ```cpp
     std::string str = "Hello World";
     std::regex reg("Hello");
     if (std::regex_match(str, reg)) {
         std::cout << "Match found!\n";
     }
     ```

2. **`std::regex_search`**
   - **설명**: 문자열에서 정규 표현식과 일치하는 부분을 찾습니다.
   - **기본 형태**: `regex_search(string, pattern,flag(s))`
   - **사용 예시**:
     ```cpp
     std::string str = "abc def ghi";
     std::regex reg("\\b\\w{3}\\b");  // 정규 표현식: 세 글자로 이루어진 단어
     if (std::regex_search(str, reg)) {
         std::cout << "Pattern found!\n";
     }
     ```

3. **`std::regex_replace`**
   - **설명**: 문자열에서 정규 표현식과 일치하는 부분을 다른 문자열로 치환합니다.
   - **기본 형태**: `regex_replace(string, pattern, replace)`
   - **사용 예시**:
     ```cpp
     std::string str = "apple orange banana";
     std::regex reg("\\b(\\w+)\\b");  // 각 단어를 캡처하는 정규 표현식
     std::string result = std::regex_replace(str, reg, "fruit");
     std::cout << result << "\n";  // 출력: "fruit fruit fruit"
     ```

4. **`std::regex_iterator`**
   - **설명**: 문자열에서 정규 표현식과 일치하는 모든 부분을 반복적으로 가져오는 반복자를 생성합니다.
   - **사용 예시**:
     ```cpp
     std::string str = "cat dog bird";
     std::regex reg("\\b\\w+\\b");  // 각 단어를 캡처하는 정규 표현식
     std::sregex_iterator iter(str.begin(), str.end(), reg);
     std::sregex_iterator end;
     while (iter != end) {
         std::cout << iter->str() << "\n";
         ++iter;
     }
     ```

5. **`std::regex_constants::match_flag_type`**
   - **설명**: `std::regex_match`와 `std::regex_search` 함수의 매치 동작을 제어하기 위한 상수 타입이다.
   - **사용 예시**:
     ```cpp
     std::string str = "Hello World";
     std::regex reg("hello", std::regex_constants::icase);  // 대소문자 구분 없이 검색
     if (std::regex_search(str, reg)) {
         std::cout << "Match found!\n";
     }
     ```

6. **`std::smatch`**
   - **설명**: `std::regex_match` 또는 `std::regex_search`에서 매치된 결과를 저장하는 클래스이다.
   - **사용 예시**:
     ```cpp
     std::string str = "John: 555-1234";
     std::regex reg("(\\w+): (\\d+-\\d+)");
     std::smatch match;
     if (std::regex_search(str, match, reg)) {
         std::cout << "Name: " << match[1] << ", Phone: " << match[2] << "\n";
     }
     ```


또한, `grep`함수는 c++에 없지만 정의할 수 있다. 

```cpp
#include <iostream>
#include <vector>
#include <regex>
#include <string>
namespace pex {
    // a C++ grep which works like the R grep
std::vector<int> grep (std::string pattern, std::string str, const std::regex::flag_type & flag = std::regex::basic) {
    std::regex rx;
    rx =std::regex(pattern,flag);
    std::vector<int> index_matches; // results saved here
    for(auto it = std::sregex_iterator(str.begin(), str.end(), rx);
        it != std::sregex_iterator(); ++it) {
            index_matches.push_back(it->position());
    }
    return(index_matches);
}
std::vector<int> grep (std::string pattern, std::vector<std::string> vstring, const std::regex::flag_type & flag = std::regex::basic) {
    std::regex rx;
    rx =std::regex(pattern,flag);
    std::vector<int> index_matches = {}; // results saved here
    int i = 0;
    for (auto el : vstring) {
        if (std::regex_search(el,rx)) {
            index_matches.push_back(i);
        }
        i=i+1;
    }
    return(index_matches);
}
} // END OF NAMESPACE

int main (int argc, char ** argv) {
    std::vector<int> res = pex::grep("[Hh][ea]", "Hello and hallo world!");
    for (auto r : res)
        std::cout << r << std::endl;
    for (auto i : pex::grep("H[ea]",{"Hello","World!", "Hallo","Welt!","by","hallo"})) {
        std::cout << i << std::endl;
    }
    for (auto i : pex::grep("H[ea]",{"Hello","World!", "Hallo","Welt!","by","hallo"}, std::regex::icase)) {
        std::cout << i << std::endl;
    }
}
```

### Command Line Options

커멘드라인 옵션은 소스 코드를 변경하지 않고도 애플리케이션을 동적으로 제어할 수 있는 방법이다. 사용자는 명령 줄에서 직접 인수를 전달하여 애플리케이션의 동작을 조정할 수 있다.

간단하게 정의를 먼저 짚고 넘어가도록 하자.

1. **Sub-command**: 얘는 애플리케이션이 수행할 다양한 작업이나 동작을 지정하는데 사용된다. 예를들어 Git에서 사용하는 `git clone`, `git commit`, `git pull`등이 subcommand가 될 수 있다. 일반적으로 애플리케이션 이름 다음에 위치하며, 주요 작업을 결정한다.
2. **Options**: 주 명령어나 서브 커맨드의 동작을 수정한다. 플래그 또는 값을 요구하는 매개변수 형태가 있다.
   1. **Flags**: 존재 여부에 따라 True 혹은 False를 나타내는 옵션이다. 일반적으로 `-`뒤에 글자나 단어로 표시된다.
   2. **Parameters**: 값을 요구하는 옵션으로, 일반적으로 `--` 혹은 `=`로 표시된다.
    ```bash
    app commit --message="버그 수정"
    app pull --rebase
    ```
3. **Positional Arguments**: `-`나 `--`없이 지정되는 변수로, 일반적으로 필수이며, 파일이름, 경로, 또는 데이터 등을 나타낸다. 보통 특정 순서나 지정된 위치가 이미 존재한다. 
    ```cpp
    app process file.txt
    ```
예시:

```bash
app process --verbose --output=results.txt input_data.txt
```

아래는 C++에서 CLA를 이용한 애플리케이션의 구현 예시이다. 
```cpp
static const char HELP[] =
R"(Example application, Max Musterman, University of Potsdam
Usage:
{0} (-h | --help)
{0} (-v | --verbose)
{0} --round 2 number
Options:
-h --help Show this screen.
--round n Rounding digits [default: 2]
)";

static const char USAGE[] =
R"(Usage: {0} [-h,--help -v,--verbose] --round n number
)";
void usage(std::string appname, bool help = false) {
    if (help) {
        fmt::print(HELP, appname);
    } else {
        fmt::print(USAGE, appname);
    }
}
int main(int argc, char *argv[]) {
    std::string appname = argv[0];
    std::regex isnumber("^[+-]?([0-9]*[.])?[0-9]+$");
    float square = 0; // 위치 인수: 숫자의 제곱
    bool square_set = false; // 위치 인수가 지정되었는지 여부
    int round = 2; // 옵션: 반올림 자릿수, 기본값 2
    bool help = false; // 도움말 플래그
    bool verbose = false; // 자세한 출력 플래그

    // 명령줄 인자가 없는 경우 사용법 출력
    if (argc == 1) {
        usage(appname);
    } else if (argc == 2 && std::regex_match(argv[1], isnumber)) {
        // 인자가 하나이고 숫자인 경우, 제곱할 수를 설정
        square = std::stof(argv[1]);
        square_set = true;
    } else {
        // 인자를 반복하여 처리
        for (int i = 1; i < argc; i++) {
            std::string carg(argv[i]);
            if ("-h" == carg || "--help" == carg) {
                help = true; // 도움말 플래그 설정
            } else if ("-v" == carg || "--verbose" == carg) {
                verbose = true; // 자세한 출력 플래그 설정
            } else if (carg == "--round" || carg == "-r") {
                // --round 옵션 처리
                if (argc > i + 1 && std::regex_match(argv[i + 1], isnumber)) {
                    round = std::stoi(argv[i + 1]);
                    i = i + 1; // 다음 인자로 이동
                }
            } else if (std::regex_match(carg, isnumber)) {
                // 숫자인 경우, 제곱할 수 설정
                square = std::stof(carg);
                square_set = true;
            }
        }
    }

    // 도움말 출력
    if (help) {
        usage(appname, true);
    } else if (square_set) {
        // 제곱 값 계산 및 출력
        if (verbose) {
            std::cout << "Let's be verbose!\n";
        }
        std::cout << "square of: " << square << " is " <<
            std::fixed << std::setprecision(round) <<
            square * square << std::endl;
    }

    return 0;
}
```
```
./app 4.5
square of: 4.5 is 20.25

./app --round 3 2.7
square of: 2.7 is 7.290

./app -v --round 1 3.14159
Let's be verbose!
square of: 3.14159 is 9.9
```

#### argc

Argument count라고 하며, C++에서 argv나 argh등과 함께 명령줄 인수를 처리하는데 사용되는 변수들이다. 이들은 `main`함수의 매개변수로 전달된다.

`argc`는 integer 타입의 변수로, 프로그램에 전달된 argument의 개수를 나타낸다. 
```bash
./program arg1 arg2 arg3
```
요로코롬 프로그램이 실행되었다면, `argc`는 3이 된다. 

#### argv

Argument vector이며, `char *argv[]` 또는 `char **argv[]`의 형태로, 프로그램에 전달된 각 인수를 포함하는 문자열 배열이다.

`argv[0]`은 보통 프로그램의 이름을 가리키고, `argv[1]`, `argv[2]`등은 각각 첫번째, 두번째 사용자가 입력한 argument를 가리킨다. 

```cpp
#include <iostream>

int main(int argc, char* argv[]) {
    // argc는 전달된 인수의 개수를 나타낸다.
    std::cout << "Number of arguments: " << argc << std::endl;

    // argv[0]는 항상 실행 파일의 이름을 가진다.
    std::cout << "Program name: " << argv[0] << std::endl;

    // 인수가 있는 경우, 각 인수를 출력한다.
    if (argc > 1) {
        std::cout << "Arguments:" << std::endl;
        for (int i = 1; i < argc; ++i) {
            std::cout << "  " << i << ": " << argv[i] << std::endl;
        }
    } else {
        std::cout << "No arguments provided." << std::endl;
    }

    return 0;
}
```
#### argparse

C++에는 Python의 argparse와 비슷한 명령줄 인수 파싱을 지원하는 라이브러리가 없지만, 몇 가지 대안이 있다. Boost.Program_options 라이브러리를 사용하여 명령줄 인수를 처리하는 것이 흔히 사용되는 방법이다. 
그런데 참 시발 교수님은 비슷한걸 또 찾아내셨다. 표준 라이브러리 `unility`에 argparse를 제공하는 뭔가가 있나보다.

다음은 사용 예시이다.

```cpp
#include <utility>
#include "include/argparse.hpp"

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("argparse");
    // 프로그램 이름을 "argparse"로 설정한 argparse 객체를 생성합니다.
    program.add_argument("number")
        .help("display the square of a given number")
        .action([](const std::string& value) {
            return std::stof(value); });
    program.add_argument("-r", "--round")
        .help("the rounding digits").default_value(2)
        .action([](const std::string& value) {
            return std::stoi(value); });
    program.add_argument("-v", "--verbose")
        .help("set verbose on")
        .default_value(false)
        .implicit_value(true);
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    auto input = program.get<float>("number");
    auto round = program.get<int>("--round");
    auto verbose = program.get<bool>("--verbose");

    if (verbose) { std::cout << "verbose is on\n"; }
    std::cout << "square of: " << input << " is " <<
        std::fixed << std::setprecision(round) <<
        input*input << std::endl;

    return 0;
}
```

이걸 왜하는거임?


#### Popl - Program Options Parser Library

popl은 C++ 프로그램의 명령줄 인수를 처리하기 위한 라이브러리이다. 이 라이브러리는 명령줄 인수를 파싱하고, 각 인수의 값을 쉽게 접근하고 사용할 수 있는 기능을 제공합니다. 주로 사용되는 기능은 다음과 같습니다:

+ 옵션 정의: popl을 사용하여 명령줄 옵션을 정의하고 설명을 추가할 수 있습니다. 예를 들어, 옵션의 이름, 단축 이름, 설명 등을 설정할 수 있습니다.

+ 인수 파싱: 프로그램이 시작될 때 주어진 명령줄 인수를 파싱하여 각 옵션과 위치 인수의 값을 추출합니다.

+ 옵션 및 위치 인수 접근: 파싱된 인수를 통해 각 옵션의 값을 가져올 수 있습니다. 이를 통해 프로그램 내에서 인수에 따라 다른 동작을 정의할 수 있습니다.

+ 자동 생성된 도움말: popl은 정의된 옵션들을 바탕으로 자동으로 도움말 메시지를 생성할 수 있습니다. 이를 통해 사용자에게 프로그램의 사용법을 쉽게 설명할 수 있습니다.

+ 예외 처리: 잘못된 인수나 옵션을 처리할 때 발생하는 예외를 처리할 수 있는 기능을 제공합니다.

```cpp
#include <iostream>
#include <iomanip>
#include "include/popl.hpp"
#include <regex>

using namespace std;
using namespace popl;

int main(int argc, const char * argv[]) {
    // OptionParser 객체 생성 및 프로그램 설명 설정
    OptionParser app("poplex application\nUsage: poplex [options] number\nOptions");

    // 스위치 옵션 추가: -h 또는 --help
    auto help = app.add<Switch>("h", "help", "produce help message");

    // 스위치 옵션 추가: -v 또는 --verbose
    auto verbose = app.add<Switch>("v", "verbose", "set verbose on");

    // 값 옵션 추가: -r 또는 --round, 기본값은 2
    auto round = app.add<Value<int>>("r", "round", "rounding digits", 2);

    // 명령줄 인수 파싱
    app.parse(argc, argv);

    // print auto-generated help message
    // 도움말 옵션(-h 또는 --help)이 설정된 경우 출력
    if (help->is_set()) {
        cout << app << "\n";
        return 0;
    } else if (verbose->is_set()) {
        cout << "verbose is on\n";
    }

    // show unknown options
    // 알 수 없는 옵션 (정의되지 않은 옵션) 출력
    for (const auto& unknown_option : app.unknown_options()) {
        cout << "Error: unknown option: " << unknown_option << "\n";
        return 0;
    }

    // positionals
    // 위치 인수 처리
    float number = 0;
    for (const auto& arg : app.non_option_args()) {
        if (std::regex_match(arg, std::regex("[-+.0-9]+"))) {
            number = std::stof(arg);
            cout << "square of: " << number << " is " <<
                    std::fixed <<
                    std::setprecision(round->value()) <<
                    number * number << std::endl;
        } else {
            cout << "Error: " << arg << " is not a number!\n";
        }
    }

    // 만약 number가 0이면 도움말 출력
    if (number == 0) {
        cout << app.help();
    }

    return 0;
}
```
#### flags.h

```cpp
#include <iostream>
#include <iomanip>
#include "include/flags.h"

int main(int argc, char** argv) {
    // args 객체 생성
    const flags::args args(argc, argv);

    // round 옵션 가져오기: long 옵션 이름 "round", 기본값 0
    auto round = args.get<int>("round", 0);

    // round 옵션이 0이면 short 옵션 이름 "r"을 확인하여 기본값 2 설정
    if (round == 0) {
        round = args.get<int>("r", 2);
    }

    // help 옵션 가져오기: long 옵션 이름 "help" 또는 short 옵션 이름 "h", 기본값 false
    const auto help = args.get<bool>("help", false) || args.get<bool>("h", false);

    // position 인수 가져오기: 인덱스 0, 기본값 0
    const auto square = args.get<float>(0, 0);

    // round 값 출력
    std::cout << round << std::endl;

    // 도움말 옵션이 설정된 경우 출력
    if (help) {
        std::cout << "Help!\n";
    } else if (square == 0) {
        // square 값이 0인 경우 사용법 출력
        std::cout << "Usage: app number\n";
    } else {
        // square 값이 있는 경우 제곱 결과 출력
        std::cout << "square of: " << square << " is " <<
                std::fixed <<
                std::setprecision(round) <<
                square * square << std::endl;
    }

    return 0;
}
```


#### Structopt

structopt은 C++ 프로그램에서 명령줄 인수를 처리하기 위한 간단하고 강력한 라이브러리이다. 주요 특징과 사용 방법을 설명드리겠습니다.

- 간편한 정의: 구조체(struct)를 사용하여 옵션들을 정의하고, 이를 통해 명령줄 인수를 파싱합니다.

- 유연성: 옵션은 위치 인수, 플래그, 매개변수 등으로 정의할 수 있습니다.

- 자동 도움말 생성: 정의된 옵션들을 기반으로 자동으로 도움말 메시지를 생성하여 사용자에게 제공합니다.

- 예외 처리: 잘못된 인수나 옵션을 처리하기 위한 예외 처리 기능을 제공합니다.

- 모던 C++ 지원: C++17 이상의 모던한 C++ 기능을 활용하여 작성되었습니다

```cpp
#include <iostream>
#include <iomanip>
#include "include/structopt.hpp"

struct Options {
    float number = 0;                   // positional parameter
    std::optional<bool> verbose = false;// optional flag
    std::optional<int> round = 2;       // optional parameter
};

STRUCTOPT(Options, number, verbose, round);

int main(int argc, char *argv[]) {
    try {
        auto app = structopt::app("Squaring application", "0.0.1");
        auto options = app.parse<Options>(argc, argv);

        if (options.number == 0) {
            app.help(); // 인수가 주어지지 않았을 때 도움말 출력
        } else {
            if (options.verbose.value_or(false)) {
                std::cout << "verbose is on\n";
            }
            std::cout << "square of: " << options.number << " is " <<
                         std::fixed << std::setprecision(options.round.value_or(2)) <<
                         options.number * options.number << std::endl;
        }
    } catch (structopt::exception& e) {
        std::cout << e.what() << "\n";
        std::cout << e.help(); // 예외 발생 시 도움말 출력
    }

    return 0;
}
```

# Lecture 5

## Friends Function

위에서 봤듯이, private로 선언된 함수나 protected로 선언된 함수 및 변수는 접근하기가 어려웠다. 이때 사용할 수 있는것이 바로 프렌드 함수이다. 클래스의 프렌드 함수는 클래스의 범위 외부에 정의되지만 클래스의 모든 porivate 및 protected 멤버에 접근할 수 있는 권한을 가진다. **프렌드 함수의 프로토타입은 클래스 정의에 나타나지만, 프렌드는 멤버함수가 아니다.** 프렌드는 함수, 함수 템플릿, 멤버 함수, 클래스 또는 클래스 템플릿일 수 있다.

다시 말해, 프렌드 함수는 클래스 외부에 정의되지만, 클래스 정의 부분에서 함수의 원형, 즉 프로토 타입을 선언하여 프렌드로 지정해야 한다. 또한, 선언할 때 `friend` 키워드를 사용하여 명시해주어야 한다. 

```cpp
#include <iostream>
using namespace std;

class Box {
private:
    double width; // private 멤버 변수로 박스의 너비를 저장

public:
    // printWidth 함수를 프렌드로 선언하여 이 함수가 private 멤버에 접근할 수 있게 함
    friend void printWidth(Box box);

    // 멤버 함수로 width 변수의 값을 설정하는 함수
    void setWidth(double wid) { 
        width = wid; 
    }
};

// 주의: printWidth()는 일반 함수이며, 어떤 클래스의 멤버 함수가 아님
void printWidth(Box box) {
    /* printWidth()는 Box 클래스의 프렌드이므로,
       이 클래스의 어떤 멤버에도 직접 접근할 수 있음 */
    cout << "Width of box : " << box.width << endl;
}

// 프로그램의 메인 함수
int main() {
    Box box; // Box 클래스의 인스턴스 생성

    // 멤버 함수를 사용하여 박스의 너비를 설정
    box.setWidth(10.0);

    // 프렌드 함수를 사용하여 박스의 너비를 출력
    printWidth(box);

    return 0;
}
```

프렌드 함수를 사용할 때 주의해야할 점이 있다.

- 프렌드 함수는 제한된 목적으로만 사용해야 한다. 프렌드 함수는 내부 함수에 접근할 수 있어 강력하지만, 이는 잘못 사용하면 encapsulation을 저해할 수 있기 때문에 꼭 필요한 경우에만 사용하는 것이 좋다.
- 너무 많은 함수나 외부 클래스가 protected 또는 private 데이터를 가진 클래스의 프렌드로 선언되는 것은 바람직 하지 않다. 이는 데이터를 보호하는 본래 목적을 훼손할 수 있다. 
- 프렌드 관계는 상호적이지 않다. 클래스 A가 클래스 B의 프렌드더라도, 클래스 B가 자동으로 클래스의 A의 프렌드가 되거나 하진 않는다. 
- 프렌드 관계는 상속되지 않는다.
- 자바에는 프렌드 함수가 없다. 


## Copy Constructor

카피 생성자는 c++에서 동일한 클래스의 다른 객체를 사용하여 새로운 객체를 초기화하는 특별한 멤버함수이다. 원형은 다음과 같다.

```cpp
ClassName(const ClassName &old_obj);
```

copy constructor를 정의하지 않더라도, c++컴파일러는 각 클래스에 대해 default copy constructor를 생성한다. 이 기본 카피 생성자는 객체 간의 멤더 단위 복사를 수행한다. 

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char *s;
    int size;

public:
    String(const char *str = NULL); // 생성자
    ~String() { delete [] s; } // 소멸자
    String(const String &oldstr); // 복사 생성자
    void print() { cout << s << endl; }
    void change(const char *);
};

// 생성자: 문자열을 받아서 객체를 초기화
String::String(const char *str) {
    size = strlen(str);
    s = new char[size + 1]; // 새로운 메모리 할당
    strcpy(s, str);
}

// 문자열을 변경하는 함수
void String::change(const char *str) {
    delete [] s;
    size = strlen(str);
    s = new char[size + 1];
    strcpy(s, str);
}

// 복사 생성자: 다른 String 객체를 사용하여 새로운 객체를 초기화
String::String(const String &oldstr) {
    size = oldstr.size;
    s = new char[size + 1];
    strcpy(s, oldstr.s);
}

int main() {
    String str1("GeeksQuiz"); // String 객체 str1 생성
    String str2 = str1; // 복사 생성자 호출, str1을 사용하여 str2 초기화
    str1.print(); // str1 출력: "GeeksQuiz"
    str2.print(); // str2 출력: "GeeksQuiz"

    str2.change("GeeksforGeeks"); // str2의 문자열을 변경
    str1.print(); // str1 출력: "GeeksQuiz"
    str2.print(); // str2 출력: "GeeksforGeeks"

    return 0;
}
```

기본으로 자동으로 생성되는 디폴트 copy 콘스트럭터는 `shallow copy`를 수행한다. 즉, 객체의 모든 멤버 변수를 그대로 복사한다. 만약 객체가 포인터나 동적 할당된 메모리를 포함하고 있다면, shallow copy는 이런 자원을 공유하게 되어 예기치 않은 동작을 유발할 수 있다.

이런 경우를 대비하여, `deep copy`를 수행하는 카피 컨스트럭터를 정의할 수 있다. deep copy는 객체의 멤버가 가리키는 메모리도 새로 할당하여 복사한다. 

위의 코드는 복사 생성자를 두개 넣어서 deep copy를 수행하는데, 위의, 클래스 내의 복사 생성자를 제거할 경우 shallow copy가 쓰이게 되어 위에 말한 문제가 생길 수 있다. 조심하자. 

## This pointer

`this` 포인터는 C++에서 모든 객체가 자신의 주소에 접근할 수 있게 하는 중요한 포인터이다. `this` 포인터는 모든 멤버 함수의 암시적 매개변수이다. 따라서, 멤버 함수 내부에서 `this`를 사용하여 호출 객체를 참조할 수 있다. 프렌드 함수는 클래스의 멤버 함수가 아니기 때문에 `this` 포인터를 가지지 않는다. 

```cpp
#include <iostream>
using namespace std;

class Box {
public:
    // 생성자 정의
    Box(double l = 2.0, double b = 2.0, double h = 2.0) {
        cout << "Constructor called." << endl;
        length = l;
        breadth = b;
        height = h;
    }
    
    // 부피를 계산하는 멤버 함수
    double Volume() {
        return length * breadth * height;
    }
    
    // Box 객체를 비교하는 멤버 함수
    int compare(Box box) {
        return this->Volume() > box.Volume();
        // this를 통해 호출 객체의 부피와, 매개변수로 전달된 객체의 부피를 비교한다. 
        // this -> Volume()은 호출 객체의 부피를 참조한다. 
    }

    // `this` 포인터를 사용하지 않고 Box 객체를 비교하는 멤버 함수
    int compare2(Box box) {
        return Volume() > box.Volume();
    }

private:
    double length;  // 박스의 길이
    double breadth; // 박스의 너비
    double height;  // 박스의 높이
};

int main(void) {
    Box Box1(3.3, 1.2, 1.5); // Box1 선언 및 초기화
    Box Box2(8.5, 6.0, 2.0); // Box2 선언 및 초기화

    // Box1과 Box2를 비교하여 결과 출력
    if (Box1.compare(Box2)) {
        cout << "Box2 is smaller than Box1" << endl;
    } else {
        cout << "Box2 is equal to or larger than Box1" << endl;
    }

    // compare 함수와 compare2 함수의 결과를 출력
    cout << "compare: " << Box1.compare(Box2) << " compare2: " << Box1.compare2(Box2) << endl;
    return 0;
}
```

언제 `this`를 사용해아할까? 

보통 로컬 변수의 이름이 member의 이름과 같을때 `this -> x = x`처럼 사용하고, 호출 객체에 참조를 리턴해야할 때 `*this`처럼 사용한다. 

## Operator overloading

오퍼레이터 오버로딩은 C++에서 사용자가 정의한 타입에 대해 내장 연산자를 재정의할 수 있는 기능이다. 이를 통해 사용자 정의 타입에 대해서도 산술 연산, 비교 연산 등을 사용할 수 있다. 

```cpp
#include <iostream>
using namespace std;

class Box {
public:
    double getVolume(void) {
        return length * breadth * height;
    }
    void setLength(double len) {
        length = len;
    }
    void setBreadth(double bre) {
        breadth = bre;
    }
    void setHeight(double hei) {
        height = hei;
    }

    // + 연산자 오버로딩: 두 Box 객체를 더한 결과를 반환
    Box operator+(const Box& b) {
        Box box;
        box.length = this->length + b.length;
        box.breadth = this->breadth + b.breadth;
        box.height = this->height + b.height;
        return box;
    }

private:
    double length;  // 상자의 길이
    double breadth; // 상자의 너비
    double height;  // 상자의 높이
};

int main() {
    Box Box1; // Box1 객체 생성
    Box Box2; // Box2 객체 생성
    Box Box3; // Box3 객체 생성

    // Box1 사양 설정
    Box1.setLength(6.0);
    Box1.setBreadth(7.0);
    Box1.setHeight(5.0);

    // Box2 사양 설정
    Box2.setLength(12.0);
    Box2.setBreadth(13.0);
    Box2.setHeight(10.0);

    // Box1의 부피 계산 및 출력
    double volume = Box1.getVolume();
    cout << "Volume of Box1: " << volume << endl;

    // Box2의 부피 계산 및 출력
    volume = Box2.getVolume();
    cout << "Volume of Box2: " << volume << endl;

    // 두 상자를 더하여 Box3에 할당
    Box3 = Box1 + Box2;

    // Box3의 부피 계산 및 출력
    volume = Box3.getVolume();
    cout << "Volume of Box3: " << volume << endl;

    return 0;
}
```
요렇게, 그냥 원하는 연산자를 `operator`키워드와 붙여서 쓰면 된다. 만약 `+`를 오버로딩 하고싶으면 뭐 예를들어 `int operator+`, 다른거라면 뭐 `bool operator==`등이 있겠다. 

연산자를 오버로딩 하는 경우는 실제로는 매우 드물다. 대부분의 연산자는 해당 연산의 직관적인 의미를 유지하며 사용된다. 무분별한 오버로딩은 혼란을 초래할 수 있다. 

## Namespace

네임스페이스(namespace)는 C++에서 식별자를 논리적으로 그룹화하여 충돌을 방지하고 코드를 구조화하는 데 사용되는 메커니즘이다. 네임스페이스는 전역 범위에서 정의되며, 다음과 같은 이점을 제공한다. 

* **식별자 충돌 방지**: 다양한 소스에서 사용되는 식별자들을 네임스페이스 내에서 격리함으로써 충돌을 방지한다.
* **코드 구조화**: 관련된 함수, 변수, 클래스 등을 하나의 네임스페이스에 묶어 코드를 더 쉽게 관리할 수 있다.
* **가독성 및 유지보수성**: 코드의 구조가 명확해지고, 코드의 의도가 명백해지므로 가독성이 향상되고 유지보수가 용이해진다.

```cpp
#include <iostream>
using namespace std;

// first name space
namespace first_space {
    void func() {
        cout << "Inside first_space" << endl;
    }
}

// second name space
namespace second_space {
    void func() {
        cout << "Inside second_space" << endl;
    }
}

int main() {
    // Calls function from first name space.
    first_space::func();

    // Calls function from second name space.
    second_space::func();

    return 0;
}
```

요렇게 네임스페이스 안에 함수를 가두면, 네임스페이스를 명시하고 그 다음 함수를 호출해야 하기 때문에, 함수들의 이름이 같더라도 각각 다른 함수를 호출할 수 있다. 

이런 네임스페이스는 `using namespace std;`와 같은 코드를 통해 네임스페이스 전체를 가져올 수 있고, 네임스페이스 명시를 생략하여 사용할 수 있다. 그러나 이와같은 방법은 식별자 충돌을 초래할 수 있으므로 주의해야한다. 

### Nested namespace

네임스페이스 안에 네임스페이스를 중첩하여 사용할 수 있다. 

```cpp
#include <iostream>
using namespace std;

// 첫 번째 네임스페이스
namespace first_space {
    void func() {
        cout << "Inside first_space" << endl;
    }

    // 첫 번째 네임스페이스 안에 중첩된 두 번째 네임스페이스
    namespace second_space {
        void func() {
            cout << "Inside second_space" << endl;
        }
    }
}

using namespace first_space::second_space;

int main () {
    // 두 번째 네임스페이스에 있는 함수 호출
    func();

    return 0;
}
```
복잡한 코드의 구조를 효과적으로 관리할 수 있는 방법이다. 정리충 애들이 좋아할 것 같은 방법임.

**정리**

* **코드 구조화 및 정리**: 네임스페이스를 사용하면 코드를 더욱 체계적으로 구조화할 수 있습니다. 관련된 변수, 함수, 클래스를 함께 그룹화하여 관리할 수 있습니다.

* **이름 충돌 회피**: 서로 다른 네임스페이스에 동일한 이름을 사용하여 이름 충돌을 피할 수 있습니다. 이는 큰 프로젝트에서 특히 중요합니다.

* **관련 기능 집중**: 네임스페이스를 사용하면 관련된 기능을 하나의 네임스페이스 안에 집중시킬 수 있습니다. 예를 들어, 파일 시스템 관련 기능은 std::filesystem 네임스페이스 안에 모을 수 있습니다.

* **여러 파일에서 네임스페이스 확장**: 네임스페이스는 여러 파일에 걸쳐 확장할 수 있으며, 이는 코드의 재사용성과 유지보수성을 높이는 데 도움을 줍니다.

* **현재 스코프에 네임스페이스 가져오기**: using 키워드를 사용하여 특정 네임스페이스의 범위를 현재 스코프로 가져올 수 있습니다. 이는 코드를 간결하게 만들고 타이핑을 줄이는 데 도움을 줍니다.

* **네임스페이스 별칭**: 네임스페이스의 긴 이름을 짧게 줄여서 사용할 수 있습니다. 이는 코드를 읽기 쉽게 만들어주며, 복잡한 구조의 네임스페이스를 간단하게 다룰 수 있습니다.

* **대규모 프로젝트에서의 권장**: 작은 프로젝트보다는 대규모 프로젝트에서 네임스페이스 사용이 권장됩니다. 코드의 구조화와 관리가 더욱 중요해지기 때문이다.

* **함수 선언과 정의**: 네임스페이스 안에서 함수를 선언하고 외부에서 정의할 수 있습니다. 이는 네임스페이스 안에서의 인터페이스 분리와 구현의 분리를 가능하게 합니다.

* **네임스페이스의 파일 구조**: 네임스페이스가 여러 파일로 구성되어 있는 경우, 해당 네임스페이스와 동일한 이름의 폴더 안에 네임스페이스 파일들을 위치시키는 것이 일반적이다.

* **C++ 네임스페이스의 편리함**: C++의 네임스페이스는 R과 같은 다른 언어의 네임스페이스보다 훨씬 편리합니다. 예를 들어, 모든 함수의 자동 import가 없으며, 네임스페이스의 생성과 중첩이 더 간단합니다.


## Function Template

템플릿은 C++에서 제공하는 기능으로, 여러 데이터 타입에 대해 동작할 수 있는 함수나 클래스를 정의할 수 있게한다. 지금까지 변수에 대한 템플릿은 알아봤는데, 템플릿은 사실 함수나 클래스에도 사용이 가능하다.

```cpp
template <typename T>
T Max(T const& a, T const& b) {
    return a < b ? b : a;
}
```

요래 사용이 가능하다. 

## Class Template

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// 템플릿 클래스 Stack 정의
template <class T>
class Stack {
private:
    vector<T> elems; // 요소들을 저장하는 벡터
public:
    void push(T const &elem); // 요소를 스택에 추가하는 함수
    T pop(); // 스택에서 요소를 제거하고 반환하는 함수
    T top() const; // 스택의 맨 위 요소를 반환하는 함수
    bool empty() const; // 스택이 비어있는지 여부를 반환하는 함수
};

// push 함수 정의: 요소를 스택에 추가
template <class T>
void Stack<T>::push(T const& elem) {
    elems.push_back(elem); // 벡터에 요소 추가
}

// pop 함수 정의: 스택에서 요소를 제거하고 반환
template <class T>
T Stack<T>::pop() {
    if (elems.empty()) // 스택이 비어있는 경우 예외 처리
        throw out_of_range("Stack<T>::pop(): empty stack");
    T elem = top(); // 맨 위 요소를 얻어옴
    elems.pop_back(); // 벡터에서 마지막 요소 제거
    return elem; // 제거한 요소 반환
}

// top 함수 정의: 스택의 맨 위 요소 반환
template <class T>
T Stack<T>::top() const {
    if (elems.empty()) // 스택이 비어있는 경우 예외 처리
        throw out_of_range("Stack<>::top(): empty stack");
    return elems.back(); // 벡터의 마지막 요소 반환
}

// empty 함수 정의: 스택이 비어있는지 여부 반환
template <class T>
bool Stack<T>::empty() const {
    return elems.empty(); // 벡터의 empty() 함수 호출하여 결과 반환
}

int main() {
    try {
        Stack<int> intStack; // 정수형 스택 생성
        Stack<string> stringStack; // 문자열 스택 생성

        // 정수형 스택 조작
        intStack.push(7);
        intStack.push(9);
        cout << "Top of intStack: " << intStack.top() << endl;

        // 문자열 스택 조작
        stringStack.push("Hello");
        stringStack.push("World!");
        cout << "Top of stringStack: " << stringStack.top() << endl;
        cout << "Popped element from stringStack: " << stringStack.pop() << endl;

        // 스택이 비어있는 경우
        stringStack.pop(); // 두 번 pop() 호출하여 스택 비우기
        stringStack.pop(); 

    } catch (exception const& ex) {
        cout << "Exception: " << ex.what() << endl; // 예외 처리
        return -1;
    }

    return 0;
}
```

아 근데 나는 진짜 템플릿은 알다가도 모르겠다. 

## Standard Template Library (STL)

STL(Standard Template Library)은 C++ 프로그래밍 언어를 위한 표준 라이브러리이다. 이 라이브러리는 C++ 표준에 포함되어 있으며, 다음 네 가지 주요 구성 요소를 제공한다. 

* 알고리즘 (Algorithms):

  * STL은 다양한 알고리즘을 제공합니다. 예를 들어, 정렬(sorting), 검색(searching), 변형(transforming) 등의 알고리즘을 포함합니다. 이 알고리즘들은 일반적으로 사용되는 작업들을 구현하여 제공하며, 데이터 처리를 간편하게 할 수 있습니다.
* 컨테이너 (Containers):

  * 컨테이너는 데이터를 저장하고 관리하는 객체들을 말합니다. STL은 다양한 종류의 컨테이너를 제공하는데, 배열(array), 리스트(list), 벡터(vector), 맵(map), 세트(set) 등이 있습니다. 각 컨테이너는 특정 데이터 구조를 구현하여 데이터를 효율적으로 저장하고 접근할 수 있게 합니다.

  * `std::vector`: 동적 배열을 제공하며, 원소의 끝에 삽입 및 삭제가 빠르게 가능합니다.
  * `std::deque`: 덱(Deque)은 double-ended queue의 약어로, 양 끝에서 원소의 추가와 제거가 O(1) 시간에 가능한 자료구조이다.
  * `std::list`: 이중 연결 리스트를 구현한 자료구조로, 임의 위치에서의 원소 삽입과 삭제가 O(1) 시간에 가능합니다.
  * `std::set`: 균형 이진 검색 트리로 구현된 자료구조로, 중복을 허용하지 않고 원소를 정렬된 상태로 유지합니다.
  * `std::map`: 키와 값을 한 쌍으로 저장하는 자료구조로, 키를 기준으로 정렬되어 있으며 중복을 허용하지 않습니다.
  * `std::unordered_set`: 해시 테이블을 사용하여 구현된 자료구조로, 원소의 삽입, 삭제, 검색 등이 상수 시간에 이루어집니다.
  * `std::unordered_map`: 해시 테이블을 사용하여 구현된 맵으로, 키를 기준으로 중복 없이 값을 저장하며 상수 시간에 삽입, 삭제, 검색이 가능합니다.
  * 
* 함수 (Functions):

  * STL은 함수 객체(function objects)와 함수 포인터(function pointers)를 포함한 다양한 함수를 제공합니다. 이러한 함수들은 알고리즘과 컨테이너에서 사용될 수 있으며, 일반 함수 또는 람다 표현식(lambda expressions)으로 구현될 수 있습니다. 
  * 대표적으로 `std::sort`, `std::find`, `std::transform`등이 있다. 
* 이터레이터 (Iterators):

  * 이터레이터는 컨테이너의 요소를 순회(traverse)하고 접근(access)하기 위한 인터페이스를 제공합니다. STL에서 제공하는 이터레이터들은 포인터와 유사하게 동작하며, 컨테이너의 요소에 접근하여 작업을 수행할 수 있습니다.


### Set vs Vector vs Map

* **std::set**:

  * `std::set`은 정렬된 유일한 값을 갖는 컨테이너이다. 중복된 값이 삽입되지 않으며, 항목들이 자동으로 정렬됩니다.
  * 여러 항목을 한 번에 삽입할 때 `std::set`이 더 빠릅니다.
  * 항목이 정렬된 순서로 유지되어야 할 경우에 사용됩니다.
  * 성능이 매우 중요한 경우에 사용될 수 있습니다.
* **std::vector**:

  * `std::vector`는 동적 배열을 나타내며, 요소를 순차적으로 저장합니다. 크기가 동적으로 조절되며, 중간 삽입 및 삭제가 비효율적일 수 있습니다.
  * 자료를 순차적으로 접근해야 할 때 유용하며, 순서가 중요한 경우에도 사용될 수 있습니다.
  * 많은 경우에서 기본적으로 사용되는 컨테이너이다.
* **std::map**:

  * `std::map`은 key-value 쌍으로 데이터를 저장하는 연관 컨테이너이다. key는 유일해야 하며, 자동으로 정렬됩니다.
  * 데이터를 검색할 때 효율적이며, key에 따라 자동으로 정렬되어야 할 경우에 사용됩니다.
  * `std::multimap`은 하나의 key에 여러 개의 값이 매핑될 수 있습니다. 이는 `std::map`에 `std::vector`를 값으로 사용하여 구현할 수 있습니다.
* 추가 설명:

  * `std::array`는 정적 배열로 크기가 고정되어 있으며, `std::vector`보다 메모리 관리나 크기 조정 면에서 제약이 있습니다.
  * `std::multimap`은 `std::map`에 `std::vector`를 값으로 사용하여 다수의 값들을 한 key에 연결할 수 있습니다. 이는 반복문에서 더 쉽게 처리할 수 있습니다.
  * 일반적으로, 대부분의 상황에서는 `std::vector`와 `std::map`을 사용하는 것이 권장됩니다. 이 두 컨테이너는 유연성과 성능 면에서 매우 우수합니다.

### Pair and Tuple 

새로 생긴 애들인가보다. 

* **std::tuple**:

  * `std::tuple`은 C++ 표준 라이브러리에서 제공하는 클래스로, 다양한 타입의 여러 값을 하나의 단위로 저장할 수 있습니다.
  * 예를 들어, `std::tuple<int, std::string, double>`은 정수, 문자열, 실수 세 가지 타입의 값을 저장할 수 있는 구조체이다.
  * `std::make_tuple` 함수를 사용하여 tuple을 생성할 수 있습니다. 이 함수는 전달된 값들로부터 tuple을 만들어 반환합니다.
* **std::pair**:

  * `std::pair`는 두 개의 값, 동일한 타입 또는 다른 타입의 두 값을 저장할 수 있는 클래스이다.
  * 예를 들어, `std::pair<int, std::string>`은 정수와 문자열 한 쌍을 저장할 수 있습니다.
  * `std::make_pair` 함수를 사용하여 pair를 생성할 수 있습니다. 이 함수는 두 개의 값으로부터 pair를 만들어 반환합니다.


# Lecture 6

## Exception

C++에서 **예외 처리(Exception Handling)**는 프로그램 실행 중에 발생할 수 있는 오류나 예외적인 상황을 처리하는 메커니즘입니다. 예외 처리는 프로그램의 흐름을 제어하면서도 예기치 못한 오류를 처리하고, 프로그램이 갑작스럽게 종료되지 않도록 돕습니다.

C++에서는 예외 처리를 위해 `try`, `catch`, `throw` 키워드를 사용합니다.

기본 개념
* `throw`: 예외를 던질 때 사용됩니다. 프로그램에서 특정 조건이 발생하면 `throw` 키워드를 통해 예외를 발생시킬 수 있습니다. 예외가 발생하면 프로그램의 제어가 즉시 `throw` 구문으로부터 멀어지고, 이를 처리할 수 있는 적절한 `catch` 블록을 찾습니다.

* `try`: 예외가 발생할 수 있는 코드 블록을 감싸는 데 사용됩니다. try 블록 내에서 발생한 예외는 `catch` 블록에서 처리됩니다.

* `catch`: 예외를 처리하는 코드 블록입니다. `catch` 블록은 `throw`된 예외 객체를 받아 적절히 처리할 수 있습니다. 하나의 try 블록에 대해 여러 개의 `catch` 블록이 있을 수 있으며, 각 `catch` 블록은 서로 다른 타입의 예외를 처리합니다.

다음은 기본적인 예외 처리 구조입니다.

```c
#include <iostream>

int main() {
    try {
        // 예외가 발생할 수 있는 코드
        throw 20;  // int 타입 예외 발생
    }
    catch (int e) {
        // 예외 처리
        std::cout << "Caught an exception: " << e << std::endl;
    }

    return 0;
}
```
위 코드에서 `throw 20;`은 정수 예외를 발생시키고, `catch (int e)` 블록에서 이를 받아 처리합니다. 예외가 발생하면 `try` 블록 내의 나머지 코드는 실행되지 않고, 해당 예외 타입을 처리할 수 있는 `catch` 블록으로 제어가 넘어갑니다.

### Dynamic memory

스택과 힙(Stack and Heap):
C++ 프로그램에서 메모리는 두 부분으로 나뉩니다:

* 스택: 함수 내에서 선언된 변수들은 스택 메모리를 사용합니다.
* 힙: 프로그램의 사용되지 않은 메모리 공간으로, 프로그램이 실행될 때 동적으로 메모리를 할당하는 데 사용됩니다.

많은 경우, 변수에 특정 정보를 저장하기 위해 얼마나 많은 메모리가 필요한지 미리 알 수 없으며, 필요한 메모리 크기는 런타임에 결정됩니다.

1. 스택 메모리

   * **스택(stack)**은 프로그램이 실행될 때, 특히 함수 호출 시 메모리를 자동으로 관리하는 영역입니다. 로컬 변수나 함수 매개변수는 스택에 저장됩니다.
   * LIFO(Last In First Out) 방식으로 관리되며, 함수가 종료되면 스택 메모리에 할당된 변수가 자동으로 해제됩니다.
   * 장점은 할당과 해제가 매우 빠르지만, 메모리 크기가 제한적입니다.

2. 힙 메모리

   * **힙(heap)**은 동적 메모리 할당이 이루어지는 공간으로, 프로그램이 실행되는 동안 개발자가 직접 할당(new)하고 해제(delete)할 수 있습니다.
   * 스택과 달리 힙 메모리는 런타임에 크기를 결정할 수 있어, 프로그램의 유연성을 제공합니다.
   * 그러나 힙 메모리는 개발자가 직접 메모리 해제를 관리해야 하며, 이를 관리하지 않으면 **메모리 누수(memory leak)**가 발생할 수 있습니다.

3. 동적 메모리의 필요성

   * 프로그램이 실행되는 동안 어떤 데이터를 처리할지 미리 알 수 없는 경우, 특히 대규모 데이터나 다양한 크기의 데이터를 처리할 때 동적 메모리가 유용합니다.
   * 예를 들어, 사용자가 입력하는 데이터의 양에 따라 메모리를 할당하거나, 프로그램이 수행 중에 생성되는 객체의 수를 조정할 수 있습니다.


단일 객체 할당

```c
int* ptr = new int;  // 정수형 메모리 동적 할당
*ptr = 10;
delete ptr;  // 메모리 해제
```

배열 할당
```c
int* arr = new int[5];  // 정수형 배열 동적 할당
for (int i = 0; i < 5; ++i) {
    arr[i] = i + 1;  // 배열 초기화
}
delete[] arr;  // 배열 메모리 해제
```

동적 메모리를 사용하면 메모리 해제를 반드시 신경 써야 합니다. 만약 동적으로 할당한 메모리를 해제하지 않으면, 메모리 누수가 발생하여 프로그램 성능이 저하되거나 충돌할 수 있습니다. 이를 방지하기 위해, C++11부터는 스마트 포인터(std::unique_ptr, std::shared_ptr)가 도입되어 메모리 관리를 자동화합니다.

### Smart Pointer


**스마트 포인터(Smart Pointer)**는 C++에서 메모리 관리를 자동화하는 데 사용되는 객체입니다. 스마트 포인터는 동적 할당된 메모리의 수명을 자동으로 관리하며, 메모리 누수(memory leak)를 방지할 수 있도록 설계되었습니다. 스마트 포인터는 RAII(Resource Acquisition Is Initialization) 원칙을 따르며, 포인터가 더 이상 필요하지 않을 때 자동으로 메모리를 해제합니다.

C++에서 가장 널리 사용되는 스마트 포인터들은 `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`입니다. 이들은 모두 **표준 라이브러리 헤더 <memory>**에 정의되어 있습니다.

1. `std::unique_ptr`
   * 소유권이 유일한 스마트 포인터입니다.
   * 하나의 객체에 대해 단 하나의 `std::unique_ptr`만 소유권을 가질 수 있습니다. 즉, 복사 불가이며, 이동만 가능합니다.
   * 메모리 해제는 포인터가 범위를 벗어나거나 명시적으로 해제될 때 이루어집니다.

```c
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass created" << std::endl; }
    ~MyClass() { std::cout << "MyClass destroyed" << std::endl; }
};

int main() {
    std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();  // 객체 생성 및 관리 시작
    // std::unique_ptr<MyClass> ptr2 = ptr1;  // 복사는 불가능 (컴파일 에러)
    
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);  // 이동은 가능
    // ptr1은 더 이상 객체에 대한 소유권을 가지지 않음
}
```

`std::move`를 통해 소유권을 다른 `unique_ptr`로 이전할 수 있습니다. 리소스의 단일 소유권이 명확할 때 사용됩니다. 예를 들어, 객체를 함수로 전달할 때 소유권을 넘겨줄 필요가 있을 때 유용합니다.

1. `std::shared_ptr`
   * 참조 횟수 기반으로 메모리를 관리하는 스마트 포인터입니다.
   * 여러 개의 `std::shared_ptr`가 같은 객체를 참조할 수 있으며, **참조 카운트(reference count)**가 관리됩니다.
   * 마지막 `std::shared_ptr`가 범위를 벗어나거나 해제되면 객체가 삭제됩니다.

```c
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass created" << std::endl; }
    ~MyClass() { std::cout << "MyClass destroyed" << std::endl; }
};

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();  // 객체 생성 및 참조 시작
    {
        std::shared_ptr<MyClass> ptr2 = ptr1;  // 참조 카운트 증가
        std::cout << "Reference count: " << ptr1.use_count() << std::endl;  // 2
    }  // ptr2가 범위를 벗어나면서 참조 카운트 감소
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;  // 1
}  // ptr1이 범위를 벗어나면서 객체 소멸
```

`shared_ptr`는 참조 카운트를 내부적으로 관리합니다. 복사할 때마다 참조 카운트가 증가하고, 각 shared_ptr가 소멸될 때 참조 카운트가 감소합니다. 참조 카운트가 0이 되면 객체가 삭제됩니다. 여러 곳에서 객체를 공유하고, 소유권을 명확하게 정의하지 않고 싶을 때 유용합니다.


스마트 포인터 요약

* 함수 인자에서는 (const) 참조를 선호하세요!
* vector나 map 같은 컨테이너를 선호하세요!
* 성능 문제가 발생할 때만 스마트 포인터를 사용하세요.
* new와 delete 대신 스마트 포인터를 사용하세요.
* 외부의 원시 포인터를 다루거나 직접 컨테이너를 생성할 때만 new와 delete를 사용하세요.
* 참고 링크: https://www.modernescpp.com/index.php/c-core-guidelines-rules-to-smart-pointers
* R.20: 소유권을 표현할 때 unique_ptr 또는 shared_ptr을 사용하세요.
* R.21: 소유권 공유가 필요하지 않다면 shared_ptr보다 unique_ptr을 선호하세요.
* R.22: shared_ptr을 만들 때는 make_shared()를 사용하세요.
* R.23: unique_ptr을 만들 때는 make_unique()를 사용하세요.
* 스니펫을 만드세요.