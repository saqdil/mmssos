#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char bit[100];
void convert(char *hexa){
    int len=strlen(hexa);
    strcpy(bit,"");
    for(int i=0;i<len;i++){
      switch(hexa[i]){
        case '0':
            strcat(bit,"0000");
            break;
        case '1':
               strcat(bit,"0001");
               break;
     case '2':
            strcat(bit,"0010");
            break;
    case '3':
           strcat(bit,"0011");
            break;
    case '4':
          strcat(bit,"0100");
            break;
    case '5':
           strcat(bit,"0101");
            break;
    case '6':
           strcat(bit,"0110");
            break;
         case '7':
           strcat(bit,"0111");
            break;
      case '8':
            strcat(bit,"1000");
            break;
      case '9':
            strcat(bit,"1001");
            break;
      case 'A':
            strcat(bit,"1010");
            break;
     case 'B':
            strcat(bit,"1011");
            break;
     case 'C':
            strcat(bit,"1100");
            break;
    
     case 'D':
            strcat(bit,"1101");
            break;
     case 'E':
            strcat(bit,"1110");
            break;
     case 'F':
            strcat(bit,"1111");
            break;
    
      }
    }
}

int main(){
    char hexa[20],type,name[20];
    int header,text,actual,addr,length,start,opcode;
    FILE *f1,*f2;
    f1=fopen("input.txt","r");
    f2=fopen("output.txt","w");
    if(f1==NULL||f2==NULL){
        printf("error opening the file");
        return 1;
    }
    printf("enter the starting address");
    scanf("%x",&start);
  while(fscanf(f1," %c",&type)!=EOF){
    if(type=='H'){
        fscanf(f1,"%s%x%x",name,&header,&length);
    }
    else if(type=='T'){
        fscanf(f1,"%x%x%s",&text,&length,hexa);
        convert(hexa);
        int count=length/3;
        for(int i=0;i<count;i++){
            fscanf(f1,"%x%x",&opcode,&addr);
            if(bit[i]=='0'){
                actual=addr;
            }
            else{
                actual=addr+start;
            }
             fprintf(f2,"%06X\t%02X%04X\n",text+start,opcode,actual);
            text+=3;
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