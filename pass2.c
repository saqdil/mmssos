#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot open %s\n", filename);
        return;
    }
    printf("\nContents of %s:\n", filename);
    char ch;
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);
    fclose(fp);
}

void passTwo() {
    char label[10], opcode[10], operand[10], code[10], mnemonic[3];
    int loc;
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("pass2intermediate.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("pass2symtab.txt", "r");
    fp4 = fopen("output.txt", "w");

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening files\n");
        return;
    }

    char temp[50];
    char progName[20] = "";
    fgets(temp, sizeof(temp), fp1);
    sscanf(temp, "%s %s %s", progName, opcode, operand);

    int startAddr = 0;
    if (strcmp(opcode, "START") == 0) {
        startAddr = (int)strtol(operand, NULL, 16);
    }

    // Prepare to collect text record object codes in-memory
    char textBuf[8192] = "";
    int textBytes = 0; // length in bytes of object codes
    int textStart = 0;
    int firstCode = 1;

    // read first actual instruction line after header
    if (fscanf(fp1, "%X %s %s %s", &loc, label, opcode, operand) != 4) {
        // nothing to process
        fprintf(fp4, "H^%s^%06X^%06X\n", progName, startAddr, 0);
        fprintf(fp4, "E^%06X\n", startAddr);
        fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4);
        printf("\nPass 2 completed. Output written to output.txt\n");
        displayFile("output.txt");
        return;
    }

    textStart = loc;

    while (strcmp(opcode, "END") != 0) {
        int found = 0;
        rewind(fp2);
        // check optab for opcode
        while (fscanf(fp2, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                char symLabel[10];
                int symLoc;
                rewind(fp3);
                int symFound = 0;
                while (fscanf(fp3, "%s %X", symLabel, &symLoc) != EOF) {
                    if (strcmp(operand, symLabel) == 0) {
                        symFound = 1;
                        break;
                    }
                }
                char obj[32];
                if (symFound) sprintf(obj, "%s%04X", mnemonic, symLoc);
                else sprintf(obj, "%s0000", mnemonic);

                if (firstCode) {
                    strcat(textBuf, obj);
                    firstCode = 0;
                } else {
                    strcat(textBuf, "^");
                    strcat(textBuf, obj);
                }
                textBytes += 3; // machine instruction typically 3 bytes
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                int val = atoi(operand);
                char obj[16];
                sprintf(obj, "%06X", val);
                if (firstCode) { strcat(textBuf, obj); firstCode = 0; }
                else { strcat(textBuf, "^"); strcat(textBuf, obj); }
                textBytes += 3;
            }
            else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    // convert characters to hex bytes
                    char obj[256] = "";
                    int count = 0;
                    for (int i = 2; operand[i] != '\''; i++) {
                        char tmp[4];
                        sprintf(tmp, "%02X", (unsigned char)operand[i]);
                        strcat(obj, tmp);
                        count++;
                    }
                    if (firstCode) { strcat(textBuf, obj); firstCode = 0; }
                    else { strcat(textBuf, "^"); strcat(textBuf, obj); }
                    textBytes += count;
                } else if (operand[0] == 'X') {
                    char *hexstr = operand + 2; // e.g., X'F1'
                    // hexstr may include trailing quote - remove it
                    char tmphex[256];
                    strncpy(tmphex, hexstr, sizeof(tmphex)-1);
                    tmphex[sizeof(tmphex)-1] = '\0';
                    // remove trailing quote if present
                    char *q = strchr(tmphex, '\'');
                    if (q) *q = '\0';
                    if (firstCode) { strcat(textBuf, tmphex); firstCode = 0; }
                    else { strcat(textBuf, "^"); strcat(textBuf, tmphex); }
                    textBytes += strlen(tmphex) / 2;
                }
            }
        }

        if (fscanf(fp1, "%X %s %s %s", &loc, label, opcode, operand) != 4) break;
    }

    // at this point 'loc' holds the address of the END line; program length = loc - startAddr
    int programLength = loc - startAddr;

    // write header with program length (use program name from START line)
    fprintf(fp4, "H^%s^%06X^%06X\n", progName, startAddr, programLength);

    // write text record if we have any object codes
    if (textBytes > 0) {
        fprintf(fp4, "T^%06X^%02X^%s\n", textStart, textBytes, textBuf);
    }

    // write end record - use execution start address (startAddr)
    fprintf(fp4, "E^%06X\n", startAddr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    printf("\nPass 2 completed. Output written to output.txt\n");
    
    displayFile("output.txt");
}

int main() {
    passTwo();
    return 0;
}

