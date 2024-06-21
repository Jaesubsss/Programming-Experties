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
    x = 6; // 컴파일 에러: const 참조는 값을 변경할 수 없습니다.
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

* **클래스와 동일한 이름**: 생성자는 클래스와 동일한 이름을 가져야 합니다.
* **반환형이 없음**: 생성자는 반환형이 없으며, void조차도 사용하지 않습니다.
* **자동 호출**: 객체가 생성될 때 자동으로 호출됩니다.

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

이전 강의에서 Constructor에 대해 알아보았다. 