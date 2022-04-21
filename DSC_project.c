/*   DSC project infix-postfix-prefix converter 

    Project by :- 

    Aditya Prakash            20070123092
    Shrey Choudhary           20070123093
    Tanishq Katre             20070123119
    Hemant Jaiswal            20070123090

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30

//---------------------------------------------Stack Declaration-------------------------------------------

char stack[MAX_SIZE] = "";
int top = -1;

void push(char arr[], int *top, char val){
    if(*top == MAX_SIZE -1){
        printf("\n%s\n","Stack Overflow");
        return;
    }
    *top = *top + 1;
    arr[*top] = val;
}

char pop(char arr[], int *top){
    char temp;
    temp = arr[*top];
    *top = *top -1;
    return temp;
}

void peek(char arr[], int *top){
    printf("\n%c\n",arr[*top]);
}

void list(char arr[], int *top){
    for(int i =0; i<= *top; i++){
        printf("%c",arr[i]);
    }
}


//---------------------------------------------Utils-------------------------------------------------
int isOperator(char val){
    switch(val){
        case '(':
        case ')':
        case '+':
        case '-':
        case '/':
        case '*':
        case '^':
            return 0;
    }
    return 1;
}

int precedence(char ch){
    switch(ch){
        case '(':
        case ')':
            return 0;
            break;
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
        case '^':
            return 3;
            break; 
    }
}



//---------------------------------------------Logic Declaration-------------------------------------------

char *inf_post(char stack[], int *top, char str[])
{
    
    char *temp = (char *)malloc(sizeof(char)*MAX_SIZE);
    int j = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if(isOperator(str[i]) != 0){

            temp[j] = str[i];
            j++;
            //printf("%c",str[i]);
        }
        
        else{
            if(*top == -1){
                push(stack,top,str[i]);
            }
            else{
                while(precedence(stack[*top]) >= precedence(str[i])){
                    temp[j] = pop(stack,top);
                    j++;
                    //printf("%c", pop(stack,top));
                }
                push(stack,top,str[i]);
            }
            
        }

    }
    //list(stack,top);
    while(*top >= 0) {
        temp[j] = pop(stack,top);
        j++;
    }
    temp[j] = '\0';

    //printf("\n%s",temp);
    return temp;
}


char *inf_pre(char stack[], int *top, char exp[]){
    char *rev_ptr = strrev(exp);
    char result[MAX_SIZE] = "";
    int j = 0;
    for(int i = 0; i < strlen(rev_ptr); i++){
        if(isOperator(rev_ptr[i]) != 0){
            result[j] = rev_ptr[i];
            j++;
        }
        else{
            while(*top >= 0 && precedence(stack[*top]) >= precedence(rev_ptr[i])){
                result[j] = stack[*top];
                j++;
                pop(stack,top);
            }
            push(stack,top,rev_ptr[i]);
        }
    }
    while(*top >= 0){
        result[j] = pop(stack, top);
        j++;
    }
    result[j] = '\0';

    rev_ptr = strrev(result);
    return rev_ptr;
}



//--------------------------------------------------Menu------------------------------------------------


void displayMenu(char exp[], int *flag)
{

    int optionChoice;
    char *result;

    printf("\n\n**************Main Menu***************\n\n\n");

    printf("Choose one of the following operations: \n\n");
    printf("1. Convert from Infix to Postfix\n");
    printf("2. Convert from Infix to Prefix\n");
    printf("3. Exit the Program\n");

    printf("\nEnter your choice: ");
    scanf("%d", &optionChoice);

    switch (optionChoice)
    {

    case 1:
        printf("%s", "\nYour PostFix Expression is: ");
        char *postfix = inf_post(stack, &top, exp);
        printf("%s", postfix);
        break;

    case 2:
        printf("%s", "\nYour PreFix Expression is: ");
        char *prefix = inf_pre(stack, &top, exp);
        printf("%s", prefix);

        break;


    case 3:
        *flag = 1;
        break;

    default:
        printf("Invalid Input\n");
        break;
    }
}

//---------------------------------------------Driver Code------------------------------------------------

int main()
{
    char str[MAX_SIZE];
    int flag = 0;



    printf("\n\n**************Expression***************\n\n");

    printf("Enter your expression: ");
    scanf("%s", str);

    while(flag != 1){
        displayMenu(str, &flag);
    }
    
    return 0;
}