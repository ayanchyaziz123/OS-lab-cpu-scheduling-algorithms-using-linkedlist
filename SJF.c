#include<stdio.h>
#include<stdlib.h>
#define P_NORMAL 10
#define P_HIGH 1

int PID = 1, CLOCK = 0, TotalWaitingTime = 0;
int TotalProcessExecuted = 0;

typedef struct a
{
    int pid, priority;
    int burstTime, arrivalTime, waitingTime, turnArTime;
    struct a *next, *prev;
}PCB;

typedef struct{
    PCB *head, *tail;


} Queue;

void sortList(Queue *q) {  
    PCB *current = NULL; 
    PCB *index = NULL;
    int temp;  
    if(q->head == NULL) {  
        return;  
    }  
    else {  

        for(current = q->head; current->next != NULL; current = current->next) {  

            for(index = current->next; index != NULL; index = index->next) {   
                if(current->burstTime > index->burstTime) {  
            
                    temp = current->burstTime;  
                    current->burstTime = index->burstTime;  
                    index->burstTime = temp;  
                }  
            }  
        }  
    }  
}  




void printQueue(Queue *q){
    PCB *pn= q->head;
    printf("PID\t CPUBurst\t ArrivalTime\t WaitingTime\t  NodeLocation\n");
    while(pn!=0){
        printf("%3d    %8d    %15d    %15d     @%15d\n", 
        pn->pid, pn->burstTime, pn->arrivalTime, pn->waitingTime, pn);
        pn = pn->next;
    }

}
void insertProcess(Queue *q, int burst, int priority){

    PCB *newProcess = (PCB *)malloc(sizeof(PCB));
    newProcess->next = newProcess->prev = 0; //Link Reset
    //set values
    newProcess->pid = PID++;
    newProcess->arrivalTime = CLOCK;
    newProcess->burstTime = burst;
    newProcess->priority = priority;

    newProcess->waitingTime=-1;
    newProcess->turnArTime=-1;

    if(q->head==0){
        q->head= q->tail = newProcess;
    }
    else{
        q->tail->next = newProcess;
        newProcess->prev = q->tail;
        q->tail = newProcess;
    }
   




}


PCB deQueue(Queue *list){
    PCB t;
    t.pid=0;
    if(list->head == 0){
        printf("\n Queue is Empty \n");
        return t;
    }
    t = *list->head;
    list->head = list->head->next;

    return t;


}

void executeProcess(Queue *rq){
    while(!rq->head == 0){// cpu execution
        PCB r = deQueue(rq);
        printf("\n\nProcess %d is being Processed",r.pid); 
        r.waitingTime= CLOCK- r.arrivalTime;
        TotalWaitingTime+= r.waitingTime;
        CLOCK+=r.burstTime;
        printf("\n Waiting Time for process-%d is %d",r.pid, r.waitingTime);
        printf("\nAfter Completion, CLOCK->%d", CLOCK);
        TotalProcessExecuted++;

    }
}

int main()
{
    Queue *readyQ = (Queue *) malloc(sizeof(Queue));
    readyQ->head = readyQ->tail = 0;
    insertProcess(readyQ, 10, P_NORMAL);
    insertProcess(readyQ, 5, P_NORMAL);
    insertProcess(readyQ, 20, P_NORMAL);
    insertProcess(readyQ, 4, P_NORMAL);
    printQueue(readyQ);
    printf("\n");
    sortList(readyQ);
    printQueue(readyQ);
    //deQueue(readyQ);
   // printQueue(readyQ);
    

   executeProcess(readyQ);
   printf("\nAverage Waiting time = %f",(float) (TotalWaitingTime/TotalProcessExecuted));



    return 0;
}