#include <stdio.h>
#include <string.h>

int main() {
    char string[50];
    int flag = 0;   // 0 = still reading a's, 1 = b's started
    int count = 0;

    printf("The grammar is: S->aS, S->Sb, S->ab\n");
    printf("Enter the string to be checked:\n");
    scanf("%s", string);

    // string must start with 'a'
    if (string[0] != 'a') {
        printf("String not accepted\n");
        return 0;
    }

    for (count = 1; string[count] != '\0'; count++) {

        // Once b starts, no more a is allowed
        if (string[count] == 'b') {
            flag = 1;    // b-phase
        }
        else if (string[count] == 'a') {
            if (flag == 1) {
                printf("The string does not belong to the specified grammar\n");
                return 0;
            }
        }
        else {
            printf("Invalid character in string\n");
            return 0;
        }
    }

    // If no b appeared, string cannot be "all a's"
    if (flag == 0) {
        printf("String not accepted\n");
    }
    else {
        printf("String accepted\n");
    }

    return 0;
}
