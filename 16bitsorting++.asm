DATA SEGMENT
    MSG1 DB 10,13,"ENTER THE NUMBER OF ELEMENTS $"
    MSG2 DB 10,13,"ENTER THE ELEMENTS: $"
    MSG3 DB 10,13, "SORTED ARRAY: $"
    SPACE DB " $"
    
    ARR DB 50 DUP(0) 
    LENGTH DB ?
DATA ENDS

CODE SEGMENT
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
        
        MOV CL,LENGTH
        DEC CL
        
        OUTER:
            MOV CH,CL
            LEA SI,ARR
        INNER:
                MOV AL,[SI]
                CMP AL,[SI+1]
                JBE SKIP
                XCHG AL,[SI+1]
                MOV [SI],AL
         SKIP:
            INC SI
            DEC CH
            JNZ INNER
            
            DEC CL
            JNZ OUTER 
            
        LEA DX,MSG3 
        MOV AH,09H
        INT 21H
        
        MOV CL,LENGTH
        LEA SI,ARR
        
        PRINT:
            MOV AL,[SI]
            ADD AL,'0'
            MOV DL,AL
            MOV AH,02H
            INT 21H
            
            LEA DX,SPACE
            MOV AH,09H
            INT 21H
            
            INC SI
            DEC CL
            JNZ PRINT
            
        MOV AH,4CH
        INT 21H
CODE ENDS
END START