#include <stdio.h>

int main() {
    // Keywords and Identifiers
    int num1;
    char str[50];  // Assuming a maximum string length of 49 characters
    float floatVar;

    // User input using a single scanf
    printf("Enter an integer, a string, and a floating-point number: ");
    scanf("%d %s %f", &num1, str, &floatVar);

    // Invalid Token
    int invalidToken123 = 42abc;  // Invalid token

    // Operators
    int result = num1 + 20 * floatVar;

    // String
    printf("String example: %s\n", str);

    
    /*
        This is a multi-line comment.
        It spans multiple lines.
    */

    // This is a single-line comment.

    // Separator
    for (int i = 0; i < 5; i++) {
        printf("Iteration %d\n", i);
    }

    return 0;
}
