#include <stdio.h>
#include <string.h>

char arr[18][3] = {
    {'E', '+', 'F'}, {'E', '*', 'F'}, {'E', '(', 'F'}, {'E', ')', 'F'}, {'E', 'i', 'F'}, {'E', '$', 'F'},
    {'F', '+', 'F'}, {'F', '*', 'F'}, {'F', '(', 'F'}, {'F', ')', 'F'}, {'F', 'i', 'F'}, {'F', '$', 'F'},
    {'T', '+', 'F'}, {'T', '*', 'F'}, {'T', '(', 'F'}, {'T', ')', 'F'}, {'T', 'i', 'F'}, {'T', '$', 'F'}
};

char prod[6] = "EETTF";

char res[6][3] = {
    {'E', '+', 'T'},
    {'T', '\0', '\0'},
    {'T', '*', 'F'},
    {'F', '\0', '\0'},
    {'(', 'E', ')'},
    {'i', '\0', '\0'}
};

char stack[50][2];
int top = -1;

void install(char pro, char re)
{
    for (int i = 0; i < 18; i++)
    {
        if (arr[i][0] == pro && arr[i][1] == re)
        {
            arr[i][2] = 'T';   // mark precedence
        }
    }

    top++;
    stack[top][0] = pro;
    stack[top][1] = re;
}

int main()
{
    int i, j;
    char pro, re, pri = ' ';

    // STEP 1: INITIAL install from grammar rules
    for (i = 0; i < 6; i++)
    {
        for (j = 2; j >= 0; j--)
        {
            char c = res[i][j];

            // Terminal symbols
            if (c == '+' || c == '*' || c == '(' || c == ')' || c == 'i' || c == '$')
            {
                install(prod[i], c);
                break;
            }

            // Nonterminals followed by a terminal
            if ((c == 'E' || c == 'T' || c == 'F') && j > 0)
            {
                char prev = res[i][j - 1];

                if (prev == '+' || prev == '*' || prev == '(' || prev == ')' || prev == 'i' || prev == '$')
                {
                    install(prod[i], prev);
                    break;
                }
            }
        }
    }

    // STEP 2: CLOSURE — install implied precedence
    while (top >= 0)
    {
        pro = stack[top][0];
        re = stack[top][1];
        top--;

        for (i = 0; i < 6; i++)
        {
            if (res[i][0] == pro && prod[i] != pro)
            {
                install(prod[i], re);
            }
        }
    }

    // STEP 3: PRINT OPERATOR PRECEDENCE TABLE
    printf("\nOPERATOR PRECEDENCE TABLE:\n");
    for (i = 0; i < 18; i++)
    {
        printf("\n\t");
        for (j = 0; j < 3; j++)
        {
            printf("%c\t", arr[i][j]);
        }
    }

    // STEP 4: PRINT PRODUCTIONS
    printf("\n\nGrammar Representation:\n");
    for (i = 0; i < 18; i++)
    {
        if (pri != arr[i][0])
        {
            pri = arr[i][0];
            printf("\n\t%c -> ", pri);
        }

        if (arr[i][2] == 'T')
        {
            printf("%c ", arr[i][1]);
        }
    }

    printf("\n");
    return 0;
}
