#include <stdio.h>
#include <string.h>

int main()
{
    char gram[20], part1[20], part2[20], modifiedGram[20], newGram[20];
    int i, j = 0, k = 0, pos = 0;

    printf("Enter Production : S->");
    gets(gram);  // (unsafe but kept as in your code)

    // Split into two parts at '|'
    for(i = 0; gram[i] != '|'; i++, j++)
        part1[j] = gram[i];
    part1[j] = '\0';

    for(j = ++i, i = 0; gram[j] != '\0'; j++, i++)
        part2[i] = gram[j];
    part2[i] = '\0';

    // Find common prefix
    for(i = 0; i < strlen(part1) && i < strlen(part2); i++)
    {
        if(part1[i] == part2[i])
        {
            modifiedGram[k++] = part1[i];
            pos = i + 1;
        }
        else
            break;
    }

    // Form new productions
    int l = 0;
    for(i = pos; part1[i] != '\0'; i++)
        newGram[l++] = part1[i];

    newGram[l++] = '|';

    for(i = pos; part2[i] != '\0'; i++)
        newGram[l++] = part2[i];

    modifiedGram[k] = 'X';
    modifiedGram[++k] = '\0';
    newGram[l] = '\0';

    // Output
    printf("\nS->%s", modifiedGram);
    printf("\nX->%s\n", newGram);

    return 0;
}
