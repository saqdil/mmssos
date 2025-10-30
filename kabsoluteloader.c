#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    char name[20],type;
    int start,header,text,addr,length;
    FILE *f1,*f2;
    f1=fopen("input.txt","r");
    f2=fopen("output.txt","w");
    if(f1==NULL||f2==NULL){
        printf("error opening the file");
        return 1;
    }
    while(fscanf(f1," %c",&type)!=EOF){
        if(type=='H'){
            fscanf(f1,"%s%x%x",name,&header,&length);
        }
        else if(type=='T'){
            fscanf(f1,"%x%x",&text,&length);
            
            for(int i=0;i<length;i++){
                fscanf(f1,"%02X",&addr);
                fprintf(f2,"%06X\t\t%02X\n",text,addr);
                 text+=1;
            }
        }
       else if(type=='E'){
        break;
       }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}