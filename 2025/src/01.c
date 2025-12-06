/**
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>


void rotate_dial(char dir, int len, int* curr, int* times_at_zero, int part);


int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        printf("Usage: ./01.out <path/to/puzzle.txt> <part>\n");
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

    int curr = 50;
    int times_at_zero = 0;

    char dir;
    int len;

    while (fscanf(infile, "%c%d\n", &dir, &len) == 2)
    {
        rotate_dial(dir, len, &curr, &times_at_zero, part);
    }
    fclose(infile);

    printf("The dial points at zero %d times\n", times_at_zero);
    return 0;
}


void rotate_dial(char dir, int len, int* curr, int* times_at_zero, int part)
{

    switch (dir)
    {
    case 'L':
        for (int i = 0; i < len; i++)
        {
            *curr = *curr - 1;
            if (part == 2 && *curr == 0) *times_at_zero = *times_at_zero + 1;
            if (*curr < 0) *curr = 99;
        }
        break;
    
    case 'R':
        for (int i = 0; i < len; i++)
        {
            *curr = *curr + 1;
            if (*curr > 99) *curr = 0;
            if (part == 2 && *curr == 0) *times_at_zero = *times_at_zero + 1;
        }
        break;
        
    default:
        printf("Invalid direction encountered: %c\n", dir);
        exit(1);
        break;
    }

    if (part == 1 && *curr == 0)
    {
        *times_at_zero = *times_at_zero + 1;
    }
    return;
}