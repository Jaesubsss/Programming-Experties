# Intro C++

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
- **static II**: 클래스 내에서 정적 멤버로 사용될 경우, 클래스에 대한 멤버이며 객체에 속하지 않는다.
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
    // 지역 정적 변수
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

    // 함수 호출하여 값들을 더합니다.
    result = sum(a, b);
    cout << "Total value is : " << result;

    // 매개변수에 기본값이 있는 함수를 호출합니다.
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

* C++에서는 `rand()` 함수를 사용하여 랜덤한 정수를 생성할 수 있습니다. 그러나 이 함수는 유사 난수를 생성한다.
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