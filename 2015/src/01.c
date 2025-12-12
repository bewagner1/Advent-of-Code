/**
 * 
 */


#include <stdio.h>
#include <stdlib.h>


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

    int floor = 0;
    size_t pos = 0;
    char c;
    while ((c = fgetc(infile)) != EOF)
    {
        pos++;
        switch (c)
        {
        case '(':
            floor++;
            break;
        
        case ')':
            floor--;
            if (part == 2 && floor == -1)
            {
                printf("The posistion of the character that first causes Santa to enter the basement is %ld\n", pos);
                return 0;
            }
            break;

        
        default:
            printf("Infvalid character encountered: %c\n", c);
            exit(1);
        }
    }

    printf("The instructions take Santa to floor %d\n", floor);

    return 0;
}