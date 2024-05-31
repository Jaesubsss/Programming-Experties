#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int linked_list()
{
    struct student
    {
        char name[50];
        struct student *next;

    };

    typedef struct student student;

    student *new, *current, *head=NULL;

    // Adding first element
    new = (student*)malloc(sizeof(student));
    strcpy(new->name, "John");
    new -> next = NULL;
    head = new;

    // adding additional element to the end

    current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    new = (student*)malloc(sizeof(student));
    strcpy(new->name, "Jane");
    new->next = NULL;
    current->next = new;

    // point out elements

    current = head;
    while (current != NULL)
    {
        printf("%s\n", current->name);
        current = current->next;
    }

    // free memory
    while ( head != NULL)
    {
        current = head;
        head = head->next;
        free(current);
    }
}

int dynamic_memory()
{
    // allocate memory for an user defined number of array
    int size;
    scanf("%d", &size);

    int *a = (int*)malloc(size * sizeof(int));
    if (a == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    free(a);
}

int text_file_opening()
{
    FILE *fp;
    char filename[50] = "test.txt";

    if ( (fp = fopen(filename, "r")) == NULL)
    {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    int i;
    for (i=0; i < 51; i++)
    {
        fprintf(fp, "%d\t%lf\n", i, exp(i));
    }
    fclose(fp);
}

int text_file_opening2()
{
    FILE *fp;
    char filename[50] = "test.txt";

    if ( (fp = fopen(filename, "r")) == NULL)
    {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    double i1, i2, i3;
    fscanf(fp, "%f %f %f", &i1, &i2, &i3); // fscanf는 파일에서 데이터를 읽어 변수에 저장합니다.
    fclose(fp);
}

int text_file_opening3()
{
    FILE *fp;
    char filename[50] = "file-to-write.txt";

    if ( (fp = fopen(filename, "w")) == NULL)
    {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    int i;
    for (i=0; i < 51; i++)
    {
        fprintf(fp, "%d\t%lf\n", i, exp(i));
    }
    fclose(fp);
}

int main()
{
    linked_list();
    return 0;
}