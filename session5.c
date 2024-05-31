#include <stdio.h>
#include <stdlib.h>

int first() {
    int  i = 99;
    int *pointer_i = &i; // pointer_i is a pointer to i
    // 포인터는 *로 선언한다. &는 주소를 나타낸다.
    printf("i is %d\n", i);
    printf("pointer_i is %p\n", pointer_i); 
    // &i is the address of i
    printf("%p, %p\n", &i, pointer_i); // 두개의 다른 방법으로 포인터를 가져올 수 있다.


    return (0);
}       

int second(){
    int a[5] = {1,2,3,4,5}; // array of integers

    printf("a is %p.\n", a); // a 는 배열의 첫번째 요소의 주소를 가리킨다. 즉, a는 포인터다.
    printf("a[0] is %d.\n", a[0]); // a[0] 는 배열의 첫번째 요소의 값을 가리킨다.
    printf("*a is %d.\n", *a); // *a 는 a가 가리키는 주소의 값을 가리킨다.


}

int fun(int array[]) {
    printf("sizeof(array)/sizeof(int)=%d\n",sizeof(array)/sizeof(int)); 
    // array는 포인터이기 때문에 sizeof(array)는 포인터의 크기를 반환한다.
    // 작동하지 않는다.    
}

int third(){
    int i,a[5] = {1,2,3,4,5};
    for (i = 0; i<sizeof(a)/sizeof(int); i++)
        printf("entry %d = %d\n", i+1, a[i]);
    fun(a);
    
}

//--------------------------------------------------------------

void fun2(int array[], int array_size) {
    int i;
    for(i=0; i<array_size; i++) {
        printf("array[%d]=%d\n", i+1, *array++); // array++는 다음 주소를 가리킨다.
        //a 자체에는 접근할 수 없기 때문에, *a++는 사용할 수 없다. 따라서 포인터를 사용해야 한다.
    }
}

int forth(){
    int a[5] = {2,4,6,8,10};
    fun2(a,5);
    return(0);
}

//--------------------------------------------------------------

/*
void fun( int array[], int array_size) {
    int i;
    for(i=0; i<array_size; i++) {
        printf("array[%d]=%d\n", i+1, *a++); 
        //작동하지않음! array의 주소는 변경할 수 없다. *a++가 오류를 일으킨다.
        // 따라서 포인터를 사용해야 한다.
        // 
    }
}
*/

int fifth(){
    int i,a[5] = {1,2,3,4,5};
    int *pointer_a = a; // 포인터는 변경될 수 있다.

    for (i=0; i<5; i++)
        printf("a[%d]=%d\n", i+1, *pointer_a++); // 포인터를 사용해야 한다.
    // 포인터는 매 루프마다 다음주소, 즉 다음 배열의 요소를 가리킨다.
    // *point_a++는 1을 더하는데, 이는 다음 배열의 요소를 가리키게 된다. 왜? 포인터는 주소를 가리키기 때문이다.
    // ++자체는 integer의 1스텝을 더하는 거기 때문에, 자료형에 따라 자동으로 바로 다음 인덱스를 가리키게 된다. 
}

//--------------------------------------------------------------

int sixth(){
    int i,a[5] = {2,4,6,8,10};
    
    for (i=0; i<5; i++)
        printf("a[%d]=%d\n", i+1, *(a+i)); // a+i는 다음 배열의 요소를 가리킨다.
        // a+i는 다음 배열의 요소를 가리킨다. 따라서 *(a+i)는 다음 배열의 요소를 가리킨다.
}

//--------------------------------------------------------------

void swap(int *a, int *b) {
    int temp = *b;;
    *b = *a;
    *a = temp;
} // a와 b의 포인터를 받아서, a와 b의 값을 바꾼다. 
// 값 자체를 바꾸는 것이 아니라, 주소를 바꾼다.

int seventh(){
    int a = 10, b = 20;
    printf("a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("a=%d, b=%d\n", a, b);
}

//--------------------------------------------------------------

int eighth(){
    int i = 23;
    int *p1, **p2; // 더블포인터

    p1 = &i; // p1은 i의 주소를 가리킨다.
    p2 = &p1; // p2는 p1의 주소를 가리킨다.

    printf("i=%d\n", i); // 23
    printf("p1=%d\n", p1); // p1은 i의 주소를 가리킨다. addr1
    printf("*p1=%d\n", *p1); // *p1은 i의 값을 가리킨다. 23
    printf("p2=%d\n", p2); // p2는 p1의 주소를 가리킨다. addr2
    printf("*p2=%d\n", *p2); // *p2는 p1의 값을 가리킨다. addr1
    printf("**p2=%d\n", **p2); // **p2는 i의 값을 가리킨다. 23
}

//--------------------------------------------------------------

int ninth(){
    char *welcome[4] = {"Hello", "World", "C", "Programming"}; // char에 대한 포인터 배열

    int i;
    for (i=0; i<4; i++)
        printf("%s\n", welcome[i]);
    printf("\n");
}

//--------------------------------------------------------------

// malloc() function allows dynamic memory allocation. 
// Looks for free memory and returns address, if found.
// Part of stdlib.h

int tenth(){
    char *string; // allocate memory for a 95 character string
    string = (char *)malloc(96); // malloc() returns a void pointer, so we cast it to a char pointer
    // 말록은 char 포인터를 반환한다. 따라서 void 포인터를 char 포인터로 캐스팅한다.
    // 96바이트의 메모리를 할당한다.
    // char*는 

    int count;
    char *p = string;
    for (count = 32; count < 126; count++)
        *p++ = count; // store ASCII characters in the string
    *p++='\0'; // null-terminate the string

    puts(string); // print the string
    printf("%s\n", string); // print the string
    free(string); // free the memory
}
 
// 이 녀석은 이해가 잘 안되니 더 알아보자. 
// malloc은 메모리를 동적으로 할당하는 함수이다.


//--------------------------------------------------------------


int eleven(){
    int size;
    scanf("%d", &size); // get the size of the array from the user

    int *a;
    a = (int *)malloc(size * sizeof(int)); // 메모리를 할당한다.
    // 왜 메모리를 할당하는가? 사용자가 입력한 사이즈만큼의 배열을 만들기 위해서이다.
    // 그럼 메모리를 할당을 안하면 배열을 못만드나? 할당을 안하면 배열을 만들 수 없다.
    // 말록에 대해서 챗지피티에 더 물어보자.


    free(a); // free the memory 이 함수는 메모리를 해제한다.
    // 반드시는 아니지만 메모리를 해제하는 것이 좋다.
}

int twelve(){
    int size;
    scanf("%d", &size); 

    int *a = (int *)malloc(size * sizeof(int)); // 메모리를 할당한다.
    if (a == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    } // 메모리 할당이 실패하면 NULL을 반환한다.

    free(a);
}

//--------------------------------------------------------------
// Trees and linked list는 포인터를 사용해 구현할 수 있는 데이터 스트럭쳐이다.

int tree(){
    struct sample { // struct는 데이터 스트럭쳐를 정의한다.
        char *name;
        int height;
        int width;
    }; // linked list의 노드를 정의한다.

    struct sample s1; // struct sample의 인스턴스를 생성한다.
    s1.name = "Bacteria 1";
    s1.height = 150;
    s1.width = 180;

    printf("%s: h=%d, w=%d\n", s1.name, s1.height, s1.width);
    return (0);
}

int linkedlist(){
    struct student{
        char name[23];
        struct student *next; // struct 내의 struct로 다음을 가리키는 포인터를 student 내에 정의한다.
    };

    typedef struct student student; // struct student를 student로 정의한다? 왜? 편의성을 위해서이다.

    student *new, *current, *head = NULL; // student 포인터를 선언한다.

    // Adding first element
    new = (student*)malloc(sizeof(student)); // 메모리를 할당한다.
    strcpy(new->name, "John"); // new의 name에 John을 복사한다.
    new->next = NULL; // new의 next를 NULL로 초기화한다. 아직 데이터가 없음. 
    head = new; // head는 new를 가리킨다.

    // Adding additional element to the end

    current = head; // current는 head를 가리킨다.
    while(current -> next != NULL)
    { // current의 next가 NULL이 아닐 때까지 (리스트의 끝까지)
        current = current -> next; // current는 current의 next를 가리킨다.
    }
    new = (student*)malloc(sizeof(student)); // 메모리를 할당한다.
    strcpy(new->name, "Michael"); // new의 name에 Jane을 복사한다.
    new->next = NULL; // new의 next를 NULL로 초기화한다.
    current->next = new; // current의 next는 new를 가리킨다.

    current = head;
    while (current != NULL)
    {
        printf("%s\n", current->name);
        current = current->next;
    } // 리스트의 모든 요소를 출력한다.

    // Free memory
    while(head != NULL)
    {
        current = head;
        head = head->next; // 이전 entry를 해제하면, head는 자동으로 다음 entry를 가리킨다.
        free(current);
    } // 특히, 여기서 말록은 entry마다 메모리를 할당하기 때문에, 완전 mess가 되기 쉽다. 따라서 메모리를 해제하는 것이 중요하다.
}


// --------------------------------------------------------------

struct node 
{
    int value; // 함수 밖에서 정의된 변수는 함수 내에서 사용할 수 있다.
    struct node *left; //node는 자기 자신을 가리키는 포인터를 가진다.
    struct node *right;
};

int binarytree()
{
    struct node* firstNode = (struct node*)malloc(sizeof(struct node)); // 메모리를 할당한다.

    firstNode -> value = 0;
    firstNode -> left = NULL;
    firstNode -> right = NULL;
} // 여기선 free를 사용하지 않는다. 왜? 이것은 단순히 메모리 할당을 보여주기 위한 것이다.

int main(){
    thirteen();
    return (0);
}