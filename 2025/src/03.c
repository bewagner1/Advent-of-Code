/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


long power_on(char* bank, int len, int part);
int find_digit(char* bank, int len, int place);


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./03.out <path/to/puzzle.txt> <part>\n");
        printf("       <path/to/puzzle>: path from cwd to puzzle\n");
        printf("       <part>: 1 or 2\n");
        exit(1);
    }

    FILE* infile = NULL;
    infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        printf("Error: unable to read source file: %s\n", argv[1]);
        exit(1);
    }

    int part = atoi(argv[2]);
    if (!(part == 1 || part == 2))
    {
        printf("Invalid part: %d\n", part);
        exit(1);
    }

    long joltage = 0;
    char *bank = NULL;
    size_t linecap = 0;
    while (getline(&bank, &linecap, infile) > 0)
    {
        joltage = joltage + power_on(bank, strlen(bank), part);
    }
    fclose(infile);

    printf("The total output joltage is: %ld\n", joltage);
    return 0;
}


long power_on(char* bank, int len, int part)
{
    long total = 0;
    int bidx = 0;
    int val;
    if (bank[len-1] != '\n') len++;
    switch (part)
    {
    case 1:
        for (int p=1; p>=0; p--)
        {
            bidx = bidx + find_digit(&bank[bidx], len-bidx-1, p);
            val = bank[bidx] - '0';
            total = 10 * total + val;
            bidx++;
        }
        return total;
    
    case 2:
        for (int p=11; p>=0; p--)
        {
            bidx = bidx + find_digit(&bank[bidx], len-bidx-1, p);
            val = bank[bidx] - '0';
            total = 10 * total + val;
            bidx++;
        }
        return total;
        break;
    
    default:
        printf("Invalid part number encounted: %d\n", part);
        exit(1);
    }

    printf("Error: Power not switched on!\n");
    exit(1);
}


int find_digit(char* bank, int len, int place)
{
    int digit;
    for (int i=9; i>0; i--)
    {
        for (int bidx=0; bidx<(len-place); bidx++)
        {
            digit = bank[bidx] - '0';
            if (digit == i) return bidx;
        }
    }

    printf("Error: No valid digit found!\n");
    exit(1);
}