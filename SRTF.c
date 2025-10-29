#include <stdio.h>
#define MAX 1000

struct Process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int start_time;
    int response_time;
};
void generate_table(struct Process p[],int n){
    float total_tat = 0,total_wt = 0,total_rt = 0;
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        p[i].tat = p[i].ct-p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].response_time = p[i].start_time-p[i].at;

        total_tat +=p[i].tat;
        total_wt+=p[i].wt;
        total_rt+=p[i].response_time;

         printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].start_time, p[i].ct,
               p[i].tat, p[i].wt, p[i].response_time);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);
}
void SRTF(struct Process p[],int n){
    printf("\n\n========SRTF(Premptive SJF)============\n\n");

    int completed = 0,time=0;
    int shortest =-1,min_remaining;
    int done[MAX]={0};
    for(int i=0;i<n;i++){
        p[i].rt = p[i].bt;
        p[i].start_time = -1;
    }
    while(completed<n){
      shortest=-1;
      min_remaining = 999999;
        //step 1:find the process with the smallest remaining time
    for(int i=0;i<n;i++){
        if(p[i].at<=time && done[i]==0){
          if(p[i].rt<min_remaining && p[i].rt>0){
            min_remaining = p[i].rt;
            shortest = i;
          }
        }
    }
    //step 2: if no process is ready , increase time
    if(shortest == -1){
        time++;
        continue;
    }
    //step 3: if first time excecuting , record start_time
    if(p[shortest].start_time==-1){
        p[shortest].start_time = time;
    }
    //step 4: excecute 1 unit of time
    p[shortest].rt--;
    time++;

    //step 5: if process finishes
    if(p[shortest].rt==0){
        p[shortest].ct = time;
        done[shortest]= 1;
        completed++;
    }
    }
    generate_table(p,n);
}
int main(){
    int n;
    struct Process p[MAX];
    printf("Enter number of total processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        printf("Enter arrival time of p%d",i+1);
        scanf("%d",&p[i].at);
         printf("Enter Burst time of p%d",i+1);
         scanf("%d",&p[i].bt);

    }
    SRTF(p,n);
    return 0;
}