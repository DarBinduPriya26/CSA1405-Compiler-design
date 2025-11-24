#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input;
int i = 0, top = 0, l;
char lasthandle[6], stack[50];

char handles[][5] = {")E(", "E*E", "E+E", "i", "E^E"};

char prec[9][9] =
{
    /*          +    -    *    /    ^    i    (    )    $  */
    /* + */   { '>', '>', '<', '<', '<', '<', '<', '>', '>' },
    /* - */   { '>', '>', '<', '<', '<', '<', '<', '>', '>' },
    /* * */   { '>', '>', '>', '>', '<', '<', '<', '>', '>' },
    /* / */   { '>', '>', '>', '>', '<', '<', '<', '>', '>' },
    /* ^ */   { '>', '>', '>', '>', '<', '<', '<', '>', '>' },
    /* i */   { '>', '>', '>', '>', '>', 'e', 'e', '>', '>' },
    /* ( */   { '<', '<', '<', '<', '<', '<', '<', '>', 'e' },
    /* ) */   { '>', '>', '>', '>', '>', 'e', 'e', '>', '>' },
    /* $ */   { '<', '<', '<', '<', '<', '<', '<', '<', '>' }
};

int getindex(char c)
{
    switch (c)
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        case 'i': return 5;
        case '(': return 6;
        case ')': return 7;
        case '$': return 8;
    }
    return -1;
}

int shift()
{
    stack[++top] = input[i++];
    stack[top + 1] = '\0';
    return 1;
}

int reduce()
{
    int h, t, len, found;

    for (h = 0; h < 5; h++)
    {
        len = strlen(handles[h]);

        if (top + 1 >= len)
        {
            found = 1;

            for (t = 0; t < len; t++)
            {
                if (stack[top - t] != handles[h][t])
                {
                    found = 0;
                    break;
                }
            }

            if (found)
            {
                strcpy(lasthandle, handles[h]);

                stack[top - len + 1] = 'E';
                top = top - len + 1;
                stack[top + 1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

void dispstack()
{
    for (int j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

void dispinput()
{
    for (int j = i; j < l; j++)
        printf("%c", input[j]);
}

int main()
{
    input = (char *)malloc(50 * sizeof(char));

    printf("Enter the string: ");
    scanf("%s", input);

    strcat(input, "$");
    l = strlen(input);

    strcpy(stack, "$");
    top = 0;

    printf("\nSTACK\tINPUT\tACTION");

    while (i < l)
    {
        shift();
        printf("\n");
        dispstack();
        printf("\t");
        dispinput();
        printf("\tShift");

        while (prec[getindex(stack[top])][getindex(input[i])] == '>')
        {
            if (!reduce())
                break;

            printf("\n");
            dispstack();
            printf("\t");
            dispinput();
            printf("\tReduced: E->%s", lasthandle);
        }
    }

    if (strcmp(stack, "$E$") == 0)
        printf("\nAccepted\n");
    else
        printf("\nNot Accepted\n");

    return 0;
}
