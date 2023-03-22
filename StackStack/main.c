#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MSIZE 20

struct Node {
    float data;
    struct Node* next;
};

struct StackFloat{
    int size;
    float stack[MSIZE];
};

//exercise 1.1
int isfull(struct StackFloat *ptr);
int isempty(struct StackFloat *ptr);
void top(struct StackFloat *ptr);
float pop(struct StackFloat *ptr);
int push(struct StackFloat *ptr, float a);
//exercise 1.2
int priority(char oper);
int operat(char ch);
char *infixToPost(char *infix);
//exercise 1.3
float countPost(char *postfix);
//exercise 2.1
void pushNode(struct Node** fNode, float val);
float popNode(struct Node** fNode);
void printList(struct Node* node);
//exercise Palindrom
void isPalindrom(char *palindrom);

int main(){
    //////////////////////////////////////////////////////////
    char pal[] = "301038";
    isPalindrom(pal);
    //////////////////////////////////////////////////////////
    char infix[MSIZE];
    printf("Enter an infix expression: ");
    gets(infix);
    char *postfix = infixToPost(infix);
    printf("Postfix expression: %s\n", postfix);
    //////////////////////////////////////////////////////////
    if(postfix!="Invalid Expression") {
        printf("Result:%f\n", countPost(postfix));
    }
    //////////////////////////////////////////////////////////
    return 0;
}

//exercise 1.1.
int isfull(struct StackFloat *ptr){
    if(ptr->size==MSIZE){
        printf("stack is full\n");
        return 1;
    }
    return 0;
}

int isempty(struct StackFloat *ptr){
    if(ptr->size==0){
        printf("stack is empty\n");
        return 1;
    }
    return 0;
}

void top(struct StackFloat *ptr){
    if(isempty(ptr) == 0){
        printf("\n|%d|\n", ptr -> size);
        printf("%f\n", ptr -> stack[ptr -> size - 1]);
    }
}

float pop(struct StackFloat *ptr){
    if(isempty(ptr)==0){
        ptr -> size = (ptr -> size - 1);
        return ptr -> stack[ptr -> size];
    }
    return -1;
}

int push(struct StackFloat *ptr, float a){
    if(isfull(ptr)==0){
        ptr -> size = (ptr -> size + 1);
        (ptr -> stack[ptr -> size - 1]) = a;
        return 1;
    }
    return 0;
}

//exercise 1.2.
int priority(char oper){
    switch(oper){
        case '*':
        case '/':
            return 1;
        case '+':
        case '-':
            return 2;
        default:
            return -1;
    }
}

int operat(char ch){
    switch(ch){
        case '+':
            return '+';
        case '-':
            return '-';
        case '*':
            return '*';
        case '/':
            return '/';
        default:
            return 0;
    }
}

char *infixToPost(char *infix){
    int i,j;
    int len = strlen(infix);
    char *postfix = (char *)malloc(sizeof(char)*(len+2));
    struct StackFloat opstack = {0};

    for (i = 0, j = 0; i < len; i++) {
        if (infix[i] == ' ')
            continue;
        if(operat(infix[i]) && infix[i+1]!=' '){
            postfix[j++] = infix[i];
            postfix[j++] = infix[++i];
        }else if (isdigit(infix[i]) || infix[i]=='.') {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&opstack, infix[i]);
        } else if (infix[i] == ')') {
            while (opstack.size > 0 && opstack.stack[opstack.size - 1] != '(') {
                postfix[j++] = ' ';
                postfix[j++] = pop(&opstack);
            }
            if (opstack.size > 0 && opstack.stack[opstack.size - 1] != '(')
                return "Invalid Expression";
            else
                opstack.size--;
        } else if (operat(infix[i]) && infix[i+1]== ' ') {
            while (opstack.size > 0 && priority(opstack.stack[opstack.size - 1]) >= priority(infix[i])) {
                postfix[j++] = ' ';
                postfix[j++] = pop(&opstack);
            }
            postfix[j++] = ' ';
            push(&opstack, infix[i]);
        }
    }

    while (opstack.size > 0){
        if (opstack.stack[opstack.size - 1]=='('){
            return "Invalid Expression";
        }
        postfix[j++] = ' ';
        postfix[j++] = opstack.stack[(opstack.size--) - 1];
    }
    postfix[j] = '\0';
    return postfix;
}

//exercise 1.3.
float countPost(char *postfix){
    int i;
    float conv, tempa, tempb;
    int j=0;
    int len = strlen(postfix);
    char space[2] = {' '};
    char *extract;
    char postfixx[len][len];
    struct StackFloat cstack = {0};

    extract = strtok(postfix, space);
    while(extract != NULL){
        strcpy(postfixx[j], extract);
        extract = strtok(NULL, space);
        j++;
    }

    for(i=0; i<j; i++) {
        if (atof(postfixx[i])!=0) {
            conv = atof(postfixx[i]);
            push(&cstack, conv);
        } else {
            tempa = pop(&cstack);
            tempb = pop(&cstack);
            //if(tempa == -1 || tempb == -1){
            //    printf("Wrong expression returning -1\n");
            //    return -1;
            //}
            if (postfixx[i][0] == '+')
                push(&cstack, tempb + tempa);
            else if (postfixx[i][0] == '-')
                push(&cstack, tempb - tempa);
            else if (postfixx[i][0] == '*')
                push(&cstack, tempb * tempa);
            else if (postfixx[i][0] == '/')
                push(&cstack, tempb / tempa);
        }
    }
    if(cstack.size != 1){
        printf("Wrong expression returning -1\n");
        return -1;
    }
    return pop(&cstack);
}

//exercise 2.1
void pushNode(struct Node** fNode, float val) {
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *fNode;
    newnode->data = val;
    newnode->next = NULL;
    if(*fNode == NULL){
        *fNode = newnode;
        return;
    }
    while(last -> next != NULL){
        last = last->next;
    }
    last->next = newnode;
}

float popNode(struct Node** fNode){
    float val;
    struct Node* temp = NULL;
    if(*fNode == NULL){
        printf("\nLinked list is empty, returning -1");
        return -1;
    }
    temp = (*fNode)->next;
    val = (*fNode)->data;
    *fNode = temp;
    return val;
}

void printList(struct Node* node){
    while (node != NULL) {
        printf(" %f ", node->data);
        node = node->next;
    }
}

//exercise Palindrom
void isPalindrom(char *palindrom){
    int j = 0;
    struct Node* palin = NULL;
    struct StackFloat palind = {0};
    int length = strlen(palindrom);
    for(int i=0; i< length; i++){
        push(&palind,palindrom[i]);
        pushNode(&palin, palindrom[i]);
    }
    for(int i=0; i< length; i++){
        if(pop(&palind) != popNode(&palin)){
            printf("not a palindrom\n");
            break;
        }
        else j++;
    }
    if(j == length){
        printf("it is a palindrom\n");
    }
}