#include<stdio.h>
#include<stdlib.h>

typedef struct a{
    int id;
    struct a *prev, *next;
}Node;  //for an item of linkedlist

typedef struct 
{
    Node *head, *tail;
}List;

void push(List *list, int id){

    Node *t = (Node *) malloc(sizeof(Node));
    t->id = id;
    t->prev = t->next = 0;
    if(list->head == 0) // for first item or if the list is empty
    {
        list->head = list->tail = t;
    }
    else{
        list->tail->next = t;
        t->prev = list->tail;
        list->tail = t;

    }
    printf("%d has been  added @%d\n",t->id, t);

}

int pop(List *list){

    if(list->tail == 0){
        printf("\nStack Underflow");
        return -1;
    }
    int t = list->tail->id;
    list->tail = list->tail->prev;
    return t;
}

int main(){
    //linkedlist

    List *stack = (List *) malloc(sizeof(List));
    stack->head = stack->tail = 0;
    push(stack, 5);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);

    printf("\nPopped %d", pop(stack));
    printf("\nPopped %d", pop(stack));
    printf("\nPopped %d", pop(stack));
    printf("\nPopped %d", pop(stack));
    printf("\nPopped %d", pop(stack));
    printf("\nPopped %d", pop(stack));
    
    return 0;
}