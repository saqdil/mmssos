ASSUME DS:DATA, CS:CODE

DATA SEGMENT
    MSG  DB 0AH,0DH,"ENTER FIRST NUMBER: $"
    MSG2 DB 0AH,0DH,"ENTER SECOND NUMBER: $"
    MSG3 DB 0AH,0DH,"DIFFERENCE IS: $"
    MSG4 DB 0AH,0DH,"DIFFERENCE IS: NEGATIVE $"
DATA ENDS

CODE SEGMENT
START:
    
    MOV AX, DATA
    MOV DS, AX
    
     
    LEA DX, MSG
    MOV AH, 09H
    INT 21H
    
    MOV AH, 01H
    INT 21H
    MOV BH, AL
    
    MOV AH, 01H
    INT 21H
    MOV BL, AL
    
     
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H
    
    MOV AH, 01H
    INT 21H
    MOV CH, AL
    
    MOV AH, 01H
    INT 21H
    MOV CL, AL
    
     
    CMP BX, CX
    JE ZERO
    JB NEGATIVE
    
     
    MOV AL, BL
    SUB AL, CL
    AAS
    ADD AL, 30H
    MOV BL, AL
    
    MOV AL, BH
    SBB AL, CH
    AAS
    ADD AL, 30H
    MOV BH, AL
    
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H
    
    MOV DL, BH
    MOV AH, 02H
    INT 21H
    
    MOV DL, BL
    MOV AH, 02H
    INT 21H
    
    JMP EXIT_PROG
    
     
ZERO:
    LEA DX, MSG3
    MOV AH, 09H
    INT 21H
    "
    MOV DL, '0'
    MOV AH, 02H
    INT 21H
    MOV AH, 02H
    INT 21H
    
    JMP EXIT_PROG
    
     
NEGATIVE:
    
    MOV AL, CL
    SUB AL, BL
    AAS
    ADD AL, 30H
    MOV CL, AL
    
    MOV AL, CH
    SBB AL, BH
    AAS
    ADD AL, 30H
    MOV CH, AL
    
    LEA DX, MSG4
    MOV AH, 09H"
    INT 21H
    
    MOV DL, CH
    MOV AH, 02H
    INT 21H
    
    MOV DL, CL
    MOV AH, 02H
    INT 21H
    
     
EXIT_PROG:
    MOV AH, 4CH
    INT 21H
    
CODE ENDS
END START
