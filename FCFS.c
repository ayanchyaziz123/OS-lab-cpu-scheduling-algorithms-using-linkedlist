#include<stdio.h>
#include<stdlib.h>
#define P_NORMAL 10
#define P_HIGH 1

int PID = 1, CLOCK = 0, TotalWaitingTime = 0;
int TotalProcessExecuted = 0;

typedef struct a
{
    int pid, priority;
    char processName;
    int burstTime, arrivalTime, waitingTime, turnArTime;
    struct a *next, *prev;
}PCB;

typedef struct{
    PCB *head, *tail;

} Queue;

void printQueue(Queue *q){
    PCB *pn= q->head;
    printf("PID\t ProcessName\t CPUBurst\t ArrivalTime\t WaitingTime\t  NodeLocation\n");
    while(pn!=0){
        printf("%3d %8c  %15d    %15d    %15d     @%15d\n", 
        pn->pid, pn->processName, pn->burstTime, pn->arrivalTime, pn->waitingTime, pn);
        pn = pn->next;
    }

}

void insertProcess(Queue *q, int burst, int priority, char pName){

    PCB *newProcess = (PCB *)malloc(sizeof(PCB));
    newProcess->next = newProcess->prev = 0; //Link Reset
    //set values
    newProcess->pid = PID++;
    newProcess->arrivalTime = CLOCK;
    newProcess->burstTime = burst;
    newProcess->priority = priority;
    newProcess->processName = pName;

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
        printf("\n Waiting Time for process->%d is %d",r.pid, r.waitingTime);
        printf("\nAfter Completion, CLOCK->%d", CLOCK);
        TotalProcessExecuted++;

        printf("\n_____________________________________________\n");

    }
}

int main()
{
    Queue *readyQ = (Queue *) malloc(sizeof(Queue));
    readyQ->head = readyQ->tail = 0; 
    insertProcess(readyQ, 10, P_NORMAL,'A');
    insertProcess(readyQ, 5, P_NORMAL, 'B');
    insertProcess(readyQ, 20, P_NORMAL, 'C');

    printQueue(readyQ);
    //deQueue(readyQ);
   // printQueue(readyQ);
   executeProcess(readyQ);
   printf("\nAverage Waiting time = %f",(float) (TotalWaitingTime/TotalProcessExecuted));
    return 0;
}