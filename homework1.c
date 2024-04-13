#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Exercise 2.2.4 Multiple choice

int mc()
{
    int random_number;
    int a,res,ans,ipt;
    srand(time(NULL));
    random_number = rand() % 3 + 1; // generate random integer between 1-3
    printf("give an integer: ");
    scanf("%d", &a);

    if (random_number == 1){
        printf("What is the value of a given integer multiplied by 3?:\n");
        res = a*3;
        ans=1;
    }
    else if (random_number == 2){
        printf("What is the value of a given integer multiplied by 10?\n");
        res = a*10;
        ans=2;
    }
    else if(random_number == 3){
        printf("What is the value of a given integer squared?\n");
        res = a*a;
        ans=3;
    }

    printf("1. %d\n2. %d\n3. %d\n", a*3,a*10,a*a);

    // task 2
/*
    do{
        printf("give your answer: \n");
        scanf("%d",&ipt);

        if (ipt == ans){
            printf("that's right!");
            return 0; // return and terminate the program if the answer is correct
        } else{
            printf("that's wrong.\n");
            printf("the right answer is %d.",ans);
            printf("try again.\n");
        }
    } while (1);  // iterate, until correct answer is given
*/
    printf("give your answer: \n");
    scanf("%d",&ipt);

    if (ipt == ans){
        printf("that's right!\n");
        return 1; // return and terminate the program if the answer is correct
    } else{
        printf("that's wrong.\n");
        printf("the right answer is %d.\n",ans);
        return 0;
    }
}

int main(void)
{
    int count;
    for (int i = 1; i <=3; i++){
        count += mc();
    }
    printf("Total number of correct answers: %d\n", count);
    return 0;
}