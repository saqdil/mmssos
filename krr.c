#include<stdio.h>
#define max 200
int start[max],end[max],count=0,gid[max];
struct process{
    int at,bt,ct,tat,wt,done,id,rt;
};

int main(){
    int n,tq,completed=0,time=0;
    printf("enter the number of elements\n");
    scanf("%d",&n);
    printf("enter the time quantum\n");
    scanf("%d",&tq);
    struct process p[n];
    for(int i=0;i<n;i++){
        printf("enter P%d at and bt\n",i);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].rt=p[i].bt;
        p[i].done=0;
        p[i].id=i;
    }
    
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                struct process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    
    int queue[200],rear=0,front=0,visited[n];
    for(int i=0;i<n;i++){
        visited[i]=0;
    }
    
    queue[rear++]=0;
    visited[0]=1;
    time=p[0].at;
    printf("| ");
    while(completed<n){
                int idx=queue[front++];
        if(p[idx].rt>0){
     
            int exec=p[idx].rt>tq?tq:p[idx].rt;
            printf("P%d |",idx);
            start[count]=time;
            gid[count]=idx;
            time+=exec;
            end[count]=time;
            count++;
            p[idx].rt-=exec;
            
            for(int i=0;i<n;i++){
                if(p[i].at<=time&&!visited[i]){
                    queue[rear++]=i;
                    visited[i]=1;
                }
            }
            
            if(p[idx].rt>0){
                queue[rear++]=idx;
            }
            
            if(p[idx].rt==0&&!p[idx].done){
                p[idx].ct=time;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt=p[idx].tat-p[idx].bt;
                p[idx].done=1;
                completed++;
            }
            
            if(front==rear&&completed<n){
                for(int i=0;i<n;i++){
                    if(p[i].at>time){
                        start[count]=time;
                        printf("idle |");
                        time=p[i].at;
                        end[count]=time;
                        gid[count]=-1;
                        count++;
                    }
                    queue[rear++]=i;
                    visited[i]=1;
                    break;
                }
                
            }
            
            
        
    }
    
    
}
  printf("\n");
  printf("%d",start[0]);
  for(int i=0;i<count;i++){
      printf("  %d",end[i]);
  }
printf("id\tat\tbt\tct\ttat\twt\t\n");
for(int i=0;i<n;i++){
    printf("P%d\t%d\t%d\t%d\t%d\t%d\t\n",i,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
}
return 0;
}