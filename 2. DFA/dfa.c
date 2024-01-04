#include <stdio.h>
#include <string.h>

int dfa = 0;
void state0(char c)
{
    if (c == '1')
        dfa = 1;
    else if (c == '0')
        dfa = 3;
    else
        dfa = -1;
}
void state1(char c)
{
    if (c == '0')
        dfa = 2;
    else if (c == '1')
        dfa = 0;
    else
        dfa = -1;
}
void state2(char c)
{
    if (c == '1')
        dfa = 3;
    else if (c == '0')
        dfa = 1;
    else
        dfa = -1;
}
void state3(char c)
{
    if (c == '0')
        dfa = 0;
    else if (c == '1')
        dfa = 2;
    else
        dfa = -1;
}
int isAccepted(char str[])
{
    int i, len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (dfa == 0)
            state0(str[i]);
        else if (dfa == 1)
            state1(str[i]);
        else if (dfa == 2)
            state2(str[i]);
        else if (dfa == 3)
            state3(str[i]);
        else
            return 0;
    }
    if (dfa == 0)
        return 1;
    else
        return 0;
}
int main()
{
    char str[1000];
    printf("enter string:");
    scanf("%s", str);
    if (isAccepted(str))
        printf("accepted");
    else
        printf("not accepted");
    return 0;
}