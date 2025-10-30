#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SYMBOL {
    char label[10];
    int addr;
} SYMTAB[50];

struct OPCODE {
    char mnemonic[10];
    char hexcode[10];
} OPTAB[50];

int main() {
    FILE *fp_intermediate, *fp_optab, *fp_symtab, *fp_obj, *fp_len;
    int locctr, start_addr, prog_len;
    int sym_count = 0, op_count = 0;
    char label[20], opcode[20], operand[20];
    char text_record[80], current_obj_code[20];
    int text_record_len = 0, text_record_start_addr = 0;

    // --- 1. LOAD OPTAB INTO MEMORY ---
    fp_optab = fopen("optab.txt", "r");
    while (fscanf(fp_optab, "%s %s", OPTAB[op_count].mnemonic, OPTAB[op_count].hexcode) == 2) {
        op_count++;
    }
    fclose(fp_optab);

    // --- 2. LOAD SYMTAB INTO MEMORY ---
    fp_symtab = fopen("symtab.txt", "r");
    while (fscanf(fp_symtab, "%s %x", SYMTAB[sym_count].label, &SYMTAB[sym_count].addr) == 2) { //
        sym_count++;
    }
    fclose(fp_symtab);

    // --- 3. READ PROGRAM LENGTH ---
    fp_len = fopen("length.txt", "r"); //
    fscanf(fp_len, "%x", &prog_len);
    fclose(fp_len);

    // --- 4. OPEN FILES ---
    fp_intermediate = fopen("intermediate.txt", "r");
    fp_obj = fopen("objcode.txt", "w");

    // --- 5. READ FIRST LINE (START line) ---
    fscanf(fp_intermediate, "\t%s\t%s\t%s", label, opcode, operand);
    start_addr = (int)strtol(operand, NULL, 16);

    fprintf(fp_obj, "H^%-6s^%06X^%06X\n", label, start_addr, prog_len);

    // --- 6. READ NEXT LINE (first instruction) ---
    fscanf(fp_intermediate, "%x\t%s\t%s\t%s", &locctr, label, opcode, operand);
    text_record_start_addr = locctr;
    strcpy(text_record, "");

    // --- 7. PROCESS EACH LINE UNTIL "END" ---
    while (strcmp(opcode, "END") != 0) {
        char machine_opcode[10] = "";
        char operand_addr[10] = "0000";

        // Search opcode in OPTAB
        for (int i = 0; i < op_count; i++) {
            if (strcmp(opcode, OPTAB[i].mnemonic) == 0) {
                strcpy(machine_opcode, OPTAB[i].hexcode);
                break;
            }
        }

        // Search operand in SYMTAB
        if (strcmp(operand, "-") != 0) {
            for (int i = 0; i < sym_count; i++) {
                if (strcmp(operand, SYMTAB[i].label) == 0) {
                    sprintf(operand_addr, "%04X", SYMTAB[i].addr); //first use of sprintf
                    break;
                }
            }
        }

        // --- Generate Object Code ---
        strcpy(current_obj_code, "");
        if (strcmp(machine_opcode, "") != 0) {
            strcat(current_obj_code, machine_opcode);
            strcat(current_obj_code, operand_addr);
        }
        else if (strcmp(opcode, "WORD") == 0) {
            sprintf(current_obj_code, "%06X", atoi(operand)); //second use of sprintf
        }
        else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') { // Character constant
                for (int i = 2; i < strlen(operand) - 1; i++) {
                    char hex_char[3];
                    sprintf(hex_char, "%02X", operand[i]); //third use of sprintf
                    strcat(current_obj_code, hex_char);
                }
            }
            else if (operand[0] == 'X') { // Hex constant
                for (int i = 2; i < strlen(operand) - 1; i++) {
                    char hex_char[2] = {operand[i], '\0'};
                    strcat(current_obj_code, hex_char);
                }
            }
        }

        // --- Check Text Record Length or Reserved Areas ---
        if ((strlen(text_record) + strlen(current_obj_code) + 1) > 60 ||
            strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {

            if (text_record_len > 0) {
                fprintf(fp_obj, "T^%06X^%02X%s\n",text_record_start_addr, text_record_len, text_record);
            }

            strcpy(text_record, "");
            text_record_len = 0;
        }

        // --- Add Object Code to Text Record ---
        if (strcmp(opcode, "RESW") != 0 && strcmp(opcode, "RESB") != 0 && strcmp(current_obj_code, "") != 0) {
            if (text_record_len == 0) {
                text_record_start_addr = locctr;
            }
            strcat(text_record, "^");
            strcat(text_record, current_obj_code);
            text_record_len += (strlen(current_obj_code) / 2);
        }

        // --- Read Next Line ---
        fscanf(fp_intermediate, "%x\t%s\t%s\t%s", &locctr, label, opcode, operand);
    }

    // --- 8. WRITE FINAL TEXT RECORD ---
    if (text_record_len > 0) {
        fprintf(fp_obj, "T^%06X^%02X%s\n", text_record_start_addr, text_record_len, text_record);
    }

    // --- 9. END RECORD ---
    fprintf(fp_obj, "E^%06X\n", start_addr);

    fclose(fp_intermediate);
    fclose(fp_obj);

    printf("\n✅ Pass 2 complete. Object code generated in objcode.txt\n");
    return 0;
}
