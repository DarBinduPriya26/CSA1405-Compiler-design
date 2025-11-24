#include <stdio.h>
#include <string.h>

int main()
{
    int n, i, j;
    char a[50][50];

    printf("Enter the number of intermediate codes: ");
    scanf("%d", &n);
    getchar();   // to clear newline from buffer

    for (i = 0; i < n; i++)
    {
        printf("Enter the 3-address code %d: ", i + 1);
        fgets(a[i], 50, stdin);   // read the entire line
    }

    printf("\nThe generated code is:\n");

    for (i = 0; i < n; i++)
    {
        // Format : X = Y + Z
        // index : 0   1 2 3 4 5 6
        // example: a = b + c

        char result = a[i][0];   // left side variable
        char op1    = a[i][4];   // first operand
        char oper   = a[i][6];   // operator
        char op2    = a[i][8];   // second operand

        printf("\n mov %c, R%d", op1, i);

        if (oper == '+')
            printf("\n add %c, R%d", op2, i);
        else if (oper == '-')
            printf("\n sub %c, R%d", op2, i);
        else if (oper == '*')
            printf("\n mul %c, R%d", op2, i);
        else if (oper == '/')
            printf("\n div %c, R%d", op2, i);

        printf("\n mov R%d, %c\n", i, result);
    }

    return 0;
}
