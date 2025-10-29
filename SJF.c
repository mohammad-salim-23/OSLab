#include<stdio.h>
#define MAX 1000
struct Process{
    int pid;
    int at;//arrival time
    int bt;//brust time
    int start_time ;//start time
    int ct;//completion time
    int wt;//waiting time
    int tat;//turn around time
};
void generate_table(struct Process p[],int n){
    float total_wt = 0,total_tat = 0;
    int i;
    printf("\n PID\tAT\t\tBT\tST\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        p[i].tat = p[i].ct-p[i].at;
        p[i].wt = p[i].tat-p[i].bt;
        total_tat+=p[i].tat;
        total_wt+=p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].start_time,p[i].ct,p[i].tat,p[i].wt);
    }
}
void SJF(struct Process p[],int n){
    printf("\n\n========SJF===========\n\n");
    int i,time,j;
    int completed = 0;// to track the number of processes completed
    time = 0;
    int done[MAX] = {0}; //keeps track of which process is done, like a to do list
    while(completed<n){
        int current_process = -1;
        int current_min_burst = 999999;

        for(i=0;i<n;i++){
            if(done[i]==0){
                if(p[i].at<=time && p[i].bt<current_min_burst){
                    current_process=i;
                    current_min_burst=p[i].bt;
                }
            }
        }
        if(current_process==-1){
            time++;
            continue;//wait until a process arrives
        }

        p[current_process].start_time = time;
        time = time+p[current_process].bt;
        p[current_process].ct = time;
        done[current_process] = 1;
        completed++;
    }
    generate_table(p,n);
}
int main(){
    int i,n;
    struct Process p[MAX],c[MAX];
    printf("ENter Number of total Process :");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        p[i].pid = i+1;

        printf("Enter arrival time of process P%d : ",i+1);
        scanf("%d",&p[i].at);

        printf("Enter brust time of Process p%d :",i+1);
        scanf("%d",&p[i].bt);
    }
    SJF(c,n);
}