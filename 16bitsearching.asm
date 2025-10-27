DATA SEGMENT
    MSG1 DB 10,13,'ENTER THE NUMBER OF ELEMENTS:$'
    MSG2 DB 10,13,'ENTER THE ELEMENTS: $'
    MSG3 DB 10,13,'ENTER THE SEARCH ELEMENT: $'
    MSG4 DB 10,13,'NOT FOUND$'
    MSG5 DB 10,13,'FOUND$'
    
    ARR DB 50 DUP(0)  
    LENGTH DB ?
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE DS:DATA
    START:
        MOV AX,DATA
        MOV DS,AX
        
        LEA DX,MSG1
        MOV AH,09H
        INT 21H
        
        MOV AH,01H
        INT 21H
        SUB AL,30H
        MOV LENGTH,AL
        MOV CL,LENGTH
        LEA SI,ARR  
        
        LEA DX,MSG2 
        MOV AH,09H
        INT 21H
        
        MOV AH,01H
        
        
    READ: 
        INT 21H
        SUB AL,30H 
        MOV [SI],AL
        INC SI
        DEC CL
        JNZ READ  
        
        LEA SI,ARR  
        
        LEA DX,MSG3
        
        MOV AH,09H
        INT 21H
        
        MOV AH,01H
        INT 21H
        
        SUB AL,30H 
        MOV BL,AL    
        MOV CL,LENGTH
        
    SEARCH:    
        MOV AL,[SI]
        CMP AL,BL
        JE FOUND
        INC SI   
        DEC CL
        JNZ SEARCH
    NOTFOUND:
        LEA DX,MSG4
        MOV AH,09H
        INT 21H
        JMP XX
    FOUND:
        LEA DX,MSG5
        MOV AH,09H
        INT 21H
    XX:
        MOV AH,4CH
        INT 21H
CODE ENDS
END START