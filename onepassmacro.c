#include<stdio.h>
#include<stdlib.h>
#include<string.h>
  int main(){
    char arg[20],opnd[20],opnd1[20],arg1[20],mne[20],mne1[20],name[20],la[20],pos1[20],pos2[20];
    int i,len,pos;

    FILE *f1,*f2,*f3,*f4,*f5;
    f1=fopen("input.txt","r");
    f2=fopen("namtab.txt","w+");
    f3=fopen("deftab.txt","w+");
    f4=fopen("argtab.txt","w+");
    f5=fopen("output.txt","w");
    if(f1==NULL||f2==NULL||f3==NULL||f4==NULL||f5==NULL){
      printf("erroe opening the file");
      return 1;

    }
    fscanf(f1,"%s%s%s",la,mne,opnd);
    while(strcmp(mne,"END")!=0){
      if(strcmp(mne,"MACRO")==0){
        pos=1;
        fprintf(f2,"%s\n",la);
        fprintf(f3,"%s\t%s\n",la,opnd);
          fscanf(f1,"%s%s%s",la,mne,opnd);
          while(strcmp(mne,"MEND")!=0){
            if(opnd[0]=='&'){
              sprintf(pos1,"%d",pos);
              strcpy(pos2,"?");
              strcat(pos2,pos1);
              strcpy(opnd,pos2);
              pos++;
            }
            fprintf(f3,"%s\t%s\n",mne,opnd);
            fscanf(f1,"%s%s%s",la,mne,opnd);
          }
          fprintf(f3,"%s\n",mne);
      }

      else{

        int macro_found=0;
        rewind(f2);
        while(fscanf(f2,"%s",name)!=EOF){
          if(strcmp(mne,name)==0){
            macro_found=1;
            break;
          }
        }
        if(macro_found==1){
          
          len=strlen(opnd);
          for(int i=0;i<len;i++){
            if(opnd[i]!=','){
                fprintf(f4,"%c",opnd[i]);
            }
            else{
              fprintf(f4,"\n");
            }
          }
          fprintf(f4,"\n");
          rewind(f4);
          rewind(f3);

          while(fscanf(f3,"%s%s",mne1,opnd1)!=EOF){
               if(strcmp(mne1,name)==0){
                fprintf(f5,".\t%s\t%s\n",mne,opnd);
                break;
               }
          }
          while(fscanf(f3,"%s%s",mne1,opnd1)!=EOF){
            if(strcmp(mne1,"MEND")==0){
              break;
            }
            if(opnd1[0]=='?'){
              fscanf(f4,"%s",arg1);
              fprintf(f5,"-\t%s\t%s\n",mne1,arg1);
            }
            else{
              fprintf(f5,"-\t%s\t%s\n",mne1,opnd1);
            }
          }
        }
        else{
          fprintf(f5,"%s\t%s\t%s\n",la,mne,opnd);
        }
      }
       fscanf(f1,"%s%s%s",la,mne,opnd);
    }
    fprintf(f5,"%s\t%s\t%s\n",la,mne,opnd);
    fclose(f1);
      fclose(f2);
        fclose(f3);
          fclose(f4);
            fclose(f5);
            return 0;
  }
