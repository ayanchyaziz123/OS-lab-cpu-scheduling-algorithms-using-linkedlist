#include<stdio.h>
#include<stdlib.h>

typedef struct a{
    int id;
    struct a *prev, *next;
}Node;

typedef struct{
    Node *head, *tail;
}Store;

void addInHeadNode(Store *store, int id){
    Node *n = (Node *) malloc(sizeof(Node));
    n->prev = n->next = NULL;
    n->id = id;

    if(store->head == NULL){
        store->head = store->tail = n;
    }
    else{
        store->head->prev = n;
        n->next = store->head;
        store->head = n;
    }
    printf("%d succesfully Added @%d\n", id, n);
}
void addInTailNode(Store *store, int id){
    Node *n = (Node *) malloc(sizeof(Node));
    n->prev = n->next = NULL;
    n->id = id;

    if(store->head == NULL){
        store->head = store->tail = n;
    }
    else{
        store->tail->next = n;
        n->prev = store->tail;
        store->tail = n;
    }
    printf("%d succesfully Added @%d\n", id, n);
}
void printList(Store *st){
    Node *n = st->head;
    while (n!=NULL)
    {
        printf("Item = %d ", n->id);
        n = n->next;
    }
    printf("\n");
    

}

void printListReverse(Store *st){
    Node *n = st->tail;
    while (n!=NULL)
    {
        printf("Item = %d ", n->id);
        n = n->prev;
    }
    printf("\n");
    

}
int main()
{
    Store *store =(Store *) malloc(sizeof(Store));
    store->head = store->tail = NULL;
    addInHeadNode(store, 10);
    addInHeadNode(store, 20);
    addInHeadNode(store, 30);
    addInTailNode(store, 1);
    printList(store);
    printListReverse(store);
    return 0;
}