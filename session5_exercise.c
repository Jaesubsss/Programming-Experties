#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/*
Exercise 5.1.1 Calculating class average
1. Write a program having a function to ask an instructor for the number of students that took part in an exam.
2. Add a function collecting the grades one by one.
3. Add a function calculating the class average.
4. Add a function printing out the class avereg.
5. Put every function in a different file. Compile and link using make.
*/

// 5.5.1
// 1. 
int ask_st_num()
{   
    int num_students;
    printf("Enter the number of students: ");
    scanf("%d", &num_students);
    return num_students;
}

// 2. 
int* grade(int num_students)
{
    int i;
    int *grades;
    grades = (int *)malloc(num_students * sizeof(int));

    for (i = 0; i < num_students; i++)
    {
        printf("Enter the grade of students %d: ", i + 1);
        scanf("%d", &grades[i]);
    }
    return grades;
}

// 3.

int calc_class_average(int *grades, int num_students)
{
    int i;
    int sum = 0;
    for (i = 0; i < num_students; i++)
    {
        sum += grades[i];
    }
    return sum;
}

// 4.
int print_class_average(int sum, int num_students)
{
    int averge = sum / num_students;
    printf("The class average is %d\n", averge);
}

// 5. 

int class_average()
{
    int num_students;
    int *grades;
    int sum;

    num_students = ask_st_num();
    grades = grade(num_students);
    sum = calc_class_average(grades, num_students);
    print_class_average(sum, num_students);
    free(grades);
    return 0;
}

// --------------------------------------------------------------

/*
Exercise 5.1.2 Student list
1. Write a program collecting students names, surnames and marks in arrays.
2. Add a function to print those to stdout in somehow tabular form.
3. Add the average mark to the bottom of that tabular output.
*/
// 1. 

typedef struct {
    char name[50];
    char surname[50];
    int mark;
} Student;

Student* student_list(int num_students)
{
    int i;
    Student *students; // *student는 Student 구조체를 가리키는 포인터이다.
    students = (Student *)malloc(num_students * sizeof(Student)); // Student 구조체 배열을 만들기 위해 Student *로 선언
    
    for (i = 0; i < num_students; i++)
    {
        printf("Enter the name of students %d: ", i + 1);
        scanf("%s", students[i].name);
        printf("Enter the surname of student %d: ", i + 1);
        scanf("%s", students[i].surname);
        printf("Enter the mark of student %d: ", i + 1);
        scanf("%d", &students[i].mark); // 구조체 배열의 mark에 값을 넣어준다. &는 주소값을 넣어준다.
    }
    return students;
}

// 2. 

void print_student_list(Student *students, int num_students)
{
    int i;
    printf("Name\tSurname\tMark\n");
    for (i = 0; i < num_students; i++)
    {
        printf("%s\t%s\t%d\n", students[i].name, students[i].surname, students[i].mark);
    }
}

// 3. 

int calc_class_mark(Student *students, int num_students)
{
    int i;
    int sum = 0;
    for (i = 0; i < num_students; i++)
    {
        sum += students[i].mark;
    }
    return sum/num_students;
}

void student_list_main()
{
    int num_students;
    Student *students;

    num_students = ask_st_num();
    students = student_list(num_students);
    print_student_list(students, num_students);
    printf("The class average is %d\n", calc_class_mark(students, num_students));
    free(students);
}

// --------------------------------------------------------------

/*
Exercise 5.2.1 Linked lists
1. Write a program to successivly fill up a linked list with student names, surnames and
grades (via user input).
2. Print out in tabular form. Including the average mark.
3. How could you sort the list?
4. List three or more examples where linked lists are used
*/

// 1. 
struct students {
    char name[50];
    char surname[50];
    int mark;
    struct students* next;
};

typedef struct students students; // typedef를 사용하여 struct students를 students라는 별칭으로 정의했습니다.

students* add_student(students* new_student); // 새로운 학생 노드를 생성하고 초기화하는 함수입니다.
void print_table(students* head); // 연결 리스트의 학생 정보를 출력하고 평균 점수를 계산하는 함수입니다.

// 2. 

students* linkedlist() { // linkedlist 함수는 새로운 학생 노드를 생성하여 리스트에 추가합니다.
    students *new_student, *current, *head = NULL; // head는 리스트의 첫 번째 노드를 가리킵니다.
                                                // current는 현재 노드를 가리키는 포인터로, 새로 추가된 노드를 리스트 끝에 연결하기 위해 사용됩니다.

    int add = 1;
    while (add == 1) {
        new_student = (students*) malloc(sizeof(students));
        if (head == NULL) {
            head = add_student(new_student);
            current = head;
        } else {
            current->next = add_student(new_student);
            current = current->next;
        }
        printf("Type 1 to add another entry: ");
        scanf("%d", &add);
    }

    return head; // 리스트의 헤드를 반환
}

students* add_student(students* new_student) {
    printf("Enter the name of the student: ");
    scanf("%s", new_student->name);
    printf("Enter the surname of the student: ");
    scanf("%s", new_student->surname);
    printf("Enter the grade of the student: ");
    scanf("%d", &new_student->mark);
    new_student->next = NULL; // 새 노드의 next 포인터를 NULL로 초기화하여 리스트의 끝을 나타냅니다.

    return new_student;
}

void print_table(students* head) {
    students* current = head;
    float sum_of_marks = 0;
    int number_of_marks = 0;

    printf("Name\tSurname\tMark\n");
    while (current != NULL) {
        sum_of_marks += current->mark;
        number_of_marks++;
        printf("%s\t%s\t%d\n", current->name, current->surname, current->mark);
        current = current->next;
    }
    if (number_of_marks > 0) {
        printf("The class average is %.2f\n", sum_of_marks / number_of_marks);
    } else {
        printf("No students in the list.\n");
    }
}

//--------------------------------------------------------------

// Define the structure of a tree node
struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int value) {
    struct TreeNode *newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* createTree() {
    struct TreeNode *root = createNode(2);
    root->left = createNode(9);
    root->right = createNode(3);
    root->left->left = createNode(7);
    root->left->right = createNode(4);
    root->right->right = createNode(99);
    return root;
}

int calculateSize(struct TreeNode *root) {
    if (root == NULL) return 0;
    return 1 + calculateSize(root->left) + calculateSize(root->right);
}

// 트리에서 최소값을 찾는 함수
int findMin(struct TreeNode *root) {
    if (root == NULL) return INT_MAX;
    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);
    return (root->value < leftMin) ? (root->value < rightMin ? root->value : rightMin) : (leftMin < rightMin ? leftMin : rightMin);
}

// 트리에서 최대값을 찾는 함수
int findMax(struct TreeNode *root) {
    if (root == NULL) return INT_MIN;
    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);
    return (root->value > leftMax) ? (root->value > rightMax ? root->value : rightMax) : (leftMax > rightMax ? leftMax : rightMax);
}

// 트리를 출력하는 함수 (확인용)
void printTree(struct TreeNode* root, int space) {
    if (root == NULL) return;

    space += 5;
    printTree(root->right, space);
    printf("\n");
    for (int i = 5; i < space; i++) printf(" ");
    printf("%d\n", root->value);
    printTree(root->left, space);
}

int main() {
    struct TreeNode *root = createTree();
    printTree(root, 0);
    printf("트리의 크기: %d\n", calculateSize(root));
    printf("트리의 최소값: %d\n", findMin(root));
    printf("트리의 최대값: %d\n", findMax(root));
    return 0;
}


