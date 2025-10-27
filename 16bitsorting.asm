data segment
    MSG1 DB 0Dh,0Ah ,'Enter the Array:$'
    MSG2 DB 0Dh,0Ah,'Sorted Array: $'
    MSG3 DB 0Dh,0Ah,'Before Sorting:$'   
    MSG4 DB 0Dh,0Ah,'Enter the length of Array:$'
    ARRAY DB 50 DUP(0)
    LEN DB 1 DUP(?)   
    SPACE DB ' $'
data ends

code segment
    ASSUME CS:code, DS:data
    
    START:
        MOV AX,data
        MOV DS,AX 
        LEA DX,MSG4
        MOV AH,09H
        INT 21H 
        MOV AH,01H
        INT 21H 
        SUB AL,'0'
        LEA DI,LEN 
        MOV [DI],AL 
        MOV CL,[DI] 
        MOV CH,0
        mov SI,0    
        LEA DX,MSG1
        MOV AH,09H
        INT 21H
    READ_LOOP:   
        MOV AH,01H
        INT 21H
        SUB AL,'0'
        mov ARRAY[SI],AL   
        INC SI
        LOOP READ_LOOP
        
        MOV CL,[DI] 
        MOV SI,0 
        LEA DX,MSG3
        MOV AH,09H
        INT 21H
    PRINT_INITIAL:  
        MOV AL,ARRAY[SI]     
        ADD AL,'0'
        MOV DL,AL
        MOV AH,02H
        INT 21H
        LEA DX,SPACE
        MOV AH,09H
        INT 21H
        INC SI
        LOOP PRINT_INITIAL
        
        MOV CL,[DI]  
        DEC CL
        
         
        
        
    OUTER_LOOP:
        mov CH,CL
        MOV SI,0
    INNER_LOOP:
        MOV AL,ARRAY[SI]
        CMP AL,ARRAY[SI+1]
        JBE SKIP_SWAP
        XCHG AL,ARRAY[SI+1]
        MOV ARRAY[SI],AL
    SKIP_SWAP:
        INC SI
        DEC CH
        JNZ INNER_LOOP
        DEC CL
        JNZ OUTER_LOOP
        
        LEA DX,MSG2
        MOV AH,09H
        INT 21H
        
        MOV CL,[LEN]
        MOV SI,0
    PRINT_LOOP:
        MOV AL, ARRAY[SI]
        ADD AL, '0'          
        MOV DL, AL
        MOV AH, 02h
        INT 21h
    
        LEA DX,SPACE        
        MOV AH, 09h
        INT 21h
    
        INC SI
        LOOP PRINT_LOOP
    
        HLT  
CODE ENDS
END START