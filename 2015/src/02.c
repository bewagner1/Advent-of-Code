/**
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        printf("Usage: ./02.out <path/to/puzzle.txt> <part>\n");
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


    size_t l,w,h;
    size_t total = 0;
    while (fscanf(infile, "%ldx%ldx%ld\n", &l, &w, &h) == 3)
    {
        switch (part)
        {
        case 1:
            total = total + 2*l*w + 2*l*h + 2*w*h;
            total = total + fminl(fminl(l*w, l*h), w*h);
            break;
        
        case 2:
            total = total + l*w*h;
            size_t max_dim = fmaxl(fmaxl(l,w),h);
            if (max_dim == l)      total = total + 2*(w+h);
            else if (max_dim == w) total = total + 2*(l+h);
            else                   total = total + 2*(l+w);
            break;

        default:
            printf("Invalid part: %d\n", part);
            exit(1);
        }
    }
    fclose(infile);

    printf("They should order %ld feet or ribbon\n", total);

    return 0;
}