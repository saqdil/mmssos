DATA SEGMENT
    MSG1 DB 10,13,'ENTER THE NUMBER OF ELEMENTS:$'
    MSG2 DB 10,13,'ENTER THE ELEMENTS: $'
    MSG3 DB 10,13,'ENTER THE SEARCH ELEMENT: $'
    MSG4 DB 10,13,'NOT FOUND$'
    MSG5 DB 10,13,'FOUND$'
    
    ARR DW 50 DUP(0) 
    LENGTH DB ?

    INPUT_BUFFER DB 10, ?, 10 DUP(0)
    NEWLINE DB 10, 13, '$'   
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE DS:DATA
    START:
        MOV AX,DATA
        MOV DS,AX

        LEA DX,MSG1
        MOV AH,09H
        INT 21H
        
        CALL READ_NUMBER 
        MOV LENGTH,AL   
        MOV CL,AL       
        SUB CH,CH       
        
        LEA SI,ARR  

        LEA DX,MSG2 
        MOV AH,09H
        INT 21H
        
    READ_LOOP:  
        CALL READ_NUMBER 
        MOV [SI],AX  
        ADD SI,2      
        LOOP READ_LOOP   

        LEA SI,ARR    
        
        LEA DX,MSG3
        MOV AH,09H
        INT 21H
        
        CALL READ_NUMBER 
        MOV BX,AX      
        
        MOV CL,LENGTH   
        SUB CH,CH       
        
    SEARCH_LOOP:    
        MOV AX,[SI]  
        CMP AX,BX   
        JE FOUND
        ADD SI,2       
        LOOP SEARCH_LOOP 
        
    NOTFOUND:
        LEA DX,MSG4
        MOV AH,09H
        INT 21H
        JMP EXIT
        
    FOUND:
        LEA DX,MSG5
        MOV AH,09H
        INT 21H
        
    EXIT:
        MOV AH,4CH
        INT 21H

READ_NUMBER PROC
    PUSH CX
    PUSH BX
    PUSH DX
    PUSH SI

    LEA DX, INPUT_BUFFER
    MOV AH, 0AH   
    INT 21H

    LEA DX, NEWLINE
    MOV AH, 09H
    INT 21H
    
    LEA SI, INPUT_BUFFER + 2  
    MOV CL, [INPUT_BUFFER + 1] 
    SUB CH,CH                 
    
    MOV AX, 0                
    MOV BX, 10               

    JCXZ DONE_CONVERT         
    
CONVERT_LOOP:
    MOV DX, 0          
    MOV DL, [SI]           
    SUB DL, 30H               
    
    PUSH DX               

    MUL BX                    
    
    POP DX                  
    ADD AX, DX              
    
    INC SI                 
    DEC CX                   
    JNZ CONVERT_LOOP          
    
DONE_CONVERT:
    POP SI
    POP DX
    POP BX
    POP CX
    RET
READ_NUMBER ENDP
        
CODE ENDS
END START