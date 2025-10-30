#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BITMASK 1000   // enough to hold expanded binary for large bitmasks

char bit[MAX_BITMASK];     // stores binary expansion of bitmask

// Convert hex string (bitmask) to binary string (4 bits per hex)
void convert(char hex[]) {
    strcpy(bit, "");
    for (int i = 0; hex[i] != '\0'; i++) {
        switch (hex[i]) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': case 'a': strcat(bit, "1010"); break;
            case 'B': case 'b': strcat(bit, "1011"); break;
            case 'C': case 'c': strcat(bit, "1100"); break;
            case 'D': case 'd': strcat(bit, "1101"); break;
            case 'E': case 'e': strcat(bit, "1110"); break;
            case 'F': case 'f': strcat(bit, "1111"); break;
        }
    }
}

int main() {
    FILE *fp_in, *fp_out;
    char record[10];
    int start_addr;

    printf("Enter the actual starting address (hex): ");
    scanf("%x", &start_addr);

    fp_in = fopen("input.txt", "r");
    if (!fp_in) {
        printf("Error: input.txt not found!\n");
        return 1;
    }

    fp_out = fopen("output.txt", "w");
    fprintf(fp_out, "----------------------------\n");
    fprintf(fp_out, "ADDRESS\t\tCONTENT\n");
    fprintf(fp_out, "----------------------------\n");

    while (fscanf(fp_in, "%s", record) != EOF) {
        if (strcmp(record, "E") == 0) {
            break;  // End record → stop processing
        }

        else if (strcmp(record, "H") == 0) {
            char progname[10], progaddr[10], length[10];
            fscanf(fp_in, "%s %s %s", progname, progaddr, length);
        }

        else if (strcmp(record, "T") == 0) {
            int text_addr, tlen;
            char bitmask_hex[50];

            fscanf(fp_in, "%x %x %s", &text_addr, &tlen, bitmask_hex);
            text_addr += start_addr;

            convert(bitmask_hex);
            int bit_len = strlen(bit);

            for (int i = 0; i < bit_len; i++) {
                int opcode, addr;

                // Stop if we reach EOF
                if (fscanf(fp_in, "%x %x", &opcode, &addr) != 2)
                    break;

                int actual_addr = (bit[i] == '1') ? addr + start_addr : addr;
                fprintf(fp_out, "%04X\t\t%02X%04X\n", text_addr, opcode, actual_addr);
                text_addr += 3;
            }
        }
        else {
            // Skip unknown records
            continue;
        }
    }

    fprintf(fp_out, "----------------------------\n");
    fclose(fp_in);
    fclose(fp_out);

    printf("\nRelocation complete! Output written to output.txt\n");

    // Display output file
    fp_out = fopen("output.txt", "r");
    char ch;
    while ((ch = fgetc(fp_out)) != EOF) putchar(ch);
    fclose(fp_out);

    return 0;
}
