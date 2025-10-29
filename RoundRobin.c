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
};
void generate_table(struct Process p[],int n){
    float total_tat = 0,total_wt = 0,total_rt = 0;
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        p[i].tat = p[i].ct-p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
   
        total_tat +=p[i].tat;
        total_wt+=p[i].wt;
        

         printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].start_time, p[i].ct,
               p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);
}
 void roundRobin(struct Process p[],int n,int tq){
    int time = 0,completed = 0;
    float total_tat = 0,total_wt = 0;

    //initialize remaining time and start time
    for(int i=0;i<n;i++){
        p[i].rt = p[i].bt;
        p[i].start_time = -1;
    }
    printf("\n=== ROUND ROBIN SCHEDULING ===\n");

    while(completed<n){
        int idle = 1; //assume cpu idle

        for(int i=0;i<n;i++){
            if(p[i].at<=time && p[i].rt>0){
                idle = 0;//found a ready process

                if(p[i].start_time==-1)
                p[i].start_time = time;

                if(p[i].rt<=tq){
                    time+=p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    completed++;
                }else{
                    p[i].rt-=tq;
                    time+=tq;
                }
            }
        }
        if(idle){
            time++;
        }
    }
    generate_table(p,n);
 }
int main(){
    struct Process p[MAX];
    int n,tq;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        printf("Enter arrival time of P%d: ", i+1);
        scanf("%d", &p[i].at);
        printf("Enter burst time of P%d: ", i+1);
        scanf("%d", &p[i].bt);
    }
    printf("Enter time quantum: ");
    scanf("%d",&tq);
    
    roundRobin(p,n,tq);
}