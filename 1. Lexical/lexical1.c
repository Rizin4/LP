#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 35
FILE *input, *output;
int line_no = 1, token_no = 0;

// Function to check if the given identifier is a keyword
int isKeyword(char *identifier)
{
    char keyword[MAX_LENGTH][MAX_LENGTH] = {"auto", "break", "case", "char", "const", "continue", "default",
                                            "do", "double", "else", "enum", "extern", "float", "for", "goto",
                                            "if", "int", "long", "register", "return", "short", "signed",
                                            "sizeof", "static", "struct", "switch", "typedef", "union",
                                            "unsigned", "void", "volatile", "while"};
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        if (strcmp(identifier, keyword[i]) == 0)
        {
            return 1; // Return 1 if it is a keyword
        }
    }
    return 0; // Return 0 if it is not a keyword
}

// Function to print a token and its corresponding lexeme
void printToken(char *token, char *lexeme)
{
    fprintf(output, "%-10d\t %-10d\t\t %-20s\t\t %-20s\n", line_no, token_no, token, lexeme);
}

int main()
{
    char ch, str[MAX_LENGTH];
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    fprintf(output, "%-10s\t %-10s\t\t %-20s\t\t %-20s\n", "Line no.", "Token no.", "Token", "Lexeme");
    
    // Loop through the characters in the input file
    while ((ch = fgetc(input)) != EOF)
    {
        // Check for preprocessor directives
        if (ch == '#')
        {
            str[0] = ch;
            int i = 1;
            do
            {
                ch = fgetc(input);
                str[i] = ch;
                i++;
            } while (ch != '>');
            str[i] = '\0';
            printToken("Preprocessor directive", str);
            token_no++;
        }
        // Check for arguments enclosed in double quotes
        else if (ch == '"')
        {
            str[0] = ch;
            int i = 1;
            do
            {
                ch = fgetc(input);
                str[i] = ch;
                i++;
            } while (ch != '"');
            str[i] = '\0';
            printToken("Argument", str);
            token_no++;
        }
        // Check for operators
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
        {
            str[0] = ch;
            str[1] = '\0';
            printToken("Operator", str);
            token_no++;
        }
        // Check for separators
        else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '?' ||
                 ch == '@' || ch == '!' ||
                 ch == '%' || ch == ',' || ch == '&')
        {
            str[0] = ch;
            str[1] = '\0';
            printToken("Separator", str);
            token_no++;
        }
        // Check for numbers
        else if (isdigit(ch))
        {
            int s = 0;
            do
            {
                str[s] = ch;
                s++;
            } while (isdigit(ch = fgetc(input)));
            str[s] = '\0';
            printToken("Number", str);
            token_no++;
            fseek(input, -1, SEEK_CUR);
        }
        // Check for identifiers and keywords
        else if (isalpha(ch) || ch == '_')
        {
            int i = 0;
            do
            {
                str[i] = ch;
                i++;
                ch = fgetc(input);
            } while (isalnum(ch) || ch == '_');
            str[i] = '\0';
            // Check if the identifier is a keyword or not
            if (isKeyword(str))
            {
                printToken("Keyword", str);
            }
            else
            {
                printToken("Identifier", str);
            }
            token_no++;
            fseek(input, -1, SEEK_CUR);
        }
        // Check for newline characters to track line numbers
        else if (ch == '\n')
        {
            line_no++;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
