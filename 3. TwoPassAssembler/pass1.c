#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global variables
char opcode[20], operand[20], label[20], t1[20], t2[20], t3[20];
int locctr, start, len, s = -1, i, j = 0, flag, size = 0, opd;
FILE *input, *optab, *symtab, *output, *length;

// Symbol Table structure
struct SYMTAB
{
    char label[20];
    int addr;
} ST[30];

// Opcode Table structure
struct OPTAB
{
    char opcode[20], hexcode[20];
} OT[30];

// Function to read Opcode Table from file
void read_OPTAB()
{
    int o = 0;
    while (fscanf(optab, "%s%s", OT[o].opcode, OT[o].hexcode) != EOF && o < 30)
    {
        o++;
    }
}

// Function to read a line from the input file
void read_Line()
{
    strcpy(t1, "");
    strcpy(t2, "");
    strcpy(t3, "");
    if (fscanf(input, "%s", t1) != EOF)
    {
        if (fgetc(input) != '\n')
        {
            if (fscanf(input, "%s", t2) != EOF)
            {
                if (fgetc(input) != '\n')
                {
                    fscanf(input, "%s", t3);
                }
            }
        }
    }
    if (strcmp(t1, "") != 0 && strcmp(t2, "") != 0 && strcmp(t3, "") != 0)
    {
        strcpy(label, t1);
        strcpy(opcode, t2);
        strcpy(operand, t3);
    }
    else if (strcmp(t1, "") != 0 && strcmp(t2, "") != 0 && strcmp(t3, "") == 0)
    {
        strcpy(label, "");
        strcpy(opcode, t1);
        strcpy(operand, t2);
    }
    else if (strcmp(t1, "") != 0 && strcmp(t2, "") == 0 && strcmp(t3, "") == 0)
    {
        strcpy(label, "");
        strcpy(opcode, t1);
        strcpy(operand, "");
    }
}

// Main function
int main()
{
    // File pointers for input, opcode table, symbol table, intermediate code, and length
    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "w");
    output = fopen("output1.txt", "w");
    length = fopen("length.txt", "w");
    
    // Read Opcode Table
    read_OPTAB();

    // Read the first line of the input file
    if (fscanf(input, "%s %s %x", label, opcode, &opd) != EOF && strcmp(opcode, "START") == 0)
    {
        start = opd;
        locctr = start;
        fprintf(output, "\t%s\t%s\t%x\n", label, opcode, opd);
        printf("----------------------INTERMEDIATE CODE----------------------------------\n");
        printf("\t%s\t%s\t%x\n", label, opcode, opd);
        read_Line();
    }
    else
    {
        locctr = 0;
    }

    // Process the input file until END is encountered
    while (strcmp(opcode, "END") != 0)
    {
        fprintf(output, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        printf("%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        
        // Handle labels and update Symbol Table
        if (strcmp(label, "") != 0)
        {
            for (i = 0; i <= s; i++)
            {
                if (strcmp(ST[i].label, label) == 0)
                {
                    printf("Error: Duplicate label '%s'\n", label);
                    exit(1);
                }
            }
            s++;
            strcpy(ST[s].label, label);
            ST[s].addr = locctr;
        }
        
        // Check if the opcode is present in the Opcode Table
        flag = 0;
        for (i = 0; i <= 30; i++)
        {
            if (strcmp(opcode, OT[i].opcode) == 0)
            {
                locctr += 0x3;
                size += 3;
                flag = 1;
                break;
            }
        }
        
        // If opcode is not in Opcode Table, handle special cases
        if (flag == 0)
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                locctr += 0x3;
                size += 3;
            }
            else if (strcmp(opcode, "RESW") == 0)
            {
                locctr += (0x3 * (atoi(operand)));
            }
            else if (strcmp(opcode, "RESB") == 0)
                locctr += (atoi(operand));
            else if (strcmp(opcode, "BYTE") == 0)
            {
                len = strlen(operand);
                if (operand[0] == 'C' || operand[0] == 'c')
                    len = len - 2;
                else
                    len = (len - 2) / 2;
                locctr += len;
                size += len;
            }
        }
        
        // Read the next line
        read_Line();
    }
    
    // Print the last line
    fprintf(output, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    printf("%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    printf("The length of program:%x", locctr - start);
    
    // Print the Symbol Table
    printf("\n ----------------------SYMBOL TAB----------------------------------\n");
    for (i = 0; i <= s; i++)
    {
        fprintf(symtab, "%s\t%x", ST[i].label, ST[i].addr);
        printf("%s\t%x", ST[i].label, ST[i].addr);
        if (i != s)
            fprintf(symtab, "\n");
        printf("\n");
    }
    
    // Print the length to the length file
    fprintf(length, "%x\n%x", locctr - start, size);
    
    // Close file pointers
    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(output);
    fclose(length);
    
    // Return 0 to indicate successful execution
    printf("");
    return 0;
}
