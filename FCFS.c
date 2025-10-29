#include<stdio.h>
#define MAX 1000
struct Process{
    int pid;
    int at;//arrival time
    int bt ;//brust time
    int start_time;//start time
    int ct;//completion time
    int wt;//waiting time
    int tat ;//turn around time

};
void generate_table(struct Process p[],int n){
   float total_wt = 0,total_tat=0;
   int i;
   printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\n");
   for(i=0;i<n;i++){
    p[i].tat = p[i].ct-p[i].at;
    p[i].wt = p[i].tat-p[i].bt;
    total_tat+=p[i].tat;
    total_wt+=p[i].wt;
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].start_time,
    p[i].ct,p[i].tat,p[i].wt);
   }
    printf("\nAverage Turnaround Time: %.2f", total_tat/n);
    printf("\nAverage Waiting Time   : %.2f\n", total_wt/n);
}
void FCFS(struct Process p[],int n){
    int i,time,j;
    time=0;//start clock
    //now we start the process by their arrival time
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    for(i=0;i<n;i++){
        if(time<p[i].at){
            time = p[i].at;//setting clock to first arrival time of a process
        }
        p[i].start_time = time;//taking the start time of a process
        time = time+p[i].bt;
        p[i].ct = time;//taking completion time as brust finishes
    }
    generate_table(p,n);
}
int main(){
    int i,n;
    struct Process p[MAX];
    printf("Enter Number of total process: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        p[i].pid = i+1;
          printf("Enter Arrival Time of Process P%d : ", i+1);
          scanf("%d",&p[i].at);
          printf("Enter Burst Time of Process P%d : ", i+1);
          scanf("%d",&p[i].bt);
    }
    FCFS(p,n);
    return 0;
}
