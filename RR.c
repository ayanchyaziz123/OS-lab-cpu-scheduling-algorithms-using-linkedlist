#include<stdio.h>
#include<stdlib.h>
#define P_NORMAL 10
#define P_HIGH 1
#define QUANTUM 5

int PID = 1, CLOCK = 0, TotalWaitingTime = 0;
int TotalProcessExecuted = 0;


typedef struct a
{
    int pid, priority;
    int burstTime, arrivalTime, waitingTime, turnArTime;
    int lastSeen;
    struct a *next, *prev;
}PCB;

typedef struct{
    PCB *head, *tail;


} Queue;

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
    newProcess->lastSeen = -1;

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

void re_addPCB(Queue *q, PCB r){
    PCB *p = (PCB *) malloc(sizeof(PCB));
    p->priority = r.priority;
    p->burstTime = r.burstTime;
    p->arrivalTime = r.arrivalTime;
    p->waitingTime = r.waitingTime;
    p->turnArTime = r.turnArTime;
    p->lastSeen = r.lastSeen;

    p->next = p->prev = 0;
    if(q->head==0){
        q->head = q->tail = p;
    }
    else{
        q->tail->next=p;
        p->prev = q->tail;
        q->tail = p;
    }
    
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

void executeProcessRR(Queue *rq){
    int waiting = 0;
    while(!rq->head == 0){// cpu execution
        PCB r = deQueue(rq);
        printf("\n\nProcess %d is being Processed",r.pid); 

        if(r.lastSeen==-1){
            waiting = CLOCK - r.arrivalTime;
        }
        else{
            waiting = CLOCK - r.lastSeen;
        }
        r.waitingTime= waiting;
        TotalWaitingTime+= waiting;
        if(r.burstTime <= QUANTUM){
            CLOCK+=r.burstTime;
            TotalProcessExecuted++;
            printf("\nProcess Completed #%d\n",r.pid);

        }
        else{
            CLOCK+=QUANTUM;
            r.burstTime = r.burstTime - QUANTUM;
            r.lastSeen = CLOCK;
            re_addPCB(rq, r);

        }
        printf("\n Waiting Time for process-%d is %d",r.pid, r.waitingTime);
        printf("\nAfter time slice completion, CLOCK->%d", CLOCK);
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

    printQueue(readyQ);
    //deQueue(readyQ);
   // printQueue(readyQ);
   executeProcessRR(readyQ);
   printf("\nAverage Waiting time = %f",(float) (TotalWaitingTime/TotalProcessExecuted));
    return 0;
}