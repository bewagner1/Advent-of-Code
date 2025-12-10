/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int is_invalid(char* id, int len, int part);


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

    long invalid_sum = 0;
    int len;

    long left, right;
    while (fscanf(infile, "%ld-%ld,", &left, &right) == 2)
    {
        for (long id = left; id <= right; id++)
        {
            len = snprintf(NULL, 0, "%ld", id);
            char *id_s = malloc(len + 1);
            snprintf(id_s, len + 1, "%ld", id);
            id_s[len] = '\0';

            invalid_sum = invalid_sum + is_invalid(id_s, len, part) * id;
            free(id_s);
        }
    }
    fclose(infile);

    printf("The total sum of the invalid IDs is: %ld\n", invalid_sum);

    return 0;
}


int is_invalid(char* id, int len, int part)
{
    switch (part)
    {
    case 1:

        if (len % 2) return 0;
        return strncmp(id, &id[len/2], len/2) == 0;
        break;
    
    case 2:
        ;
        long sub_l;
        int flag;
        long mx = sqrt(atol(id));
        for (long i = 2; i <= mx; i++)
        {
            if (len % i) continue;
            sub_l = len / i;
            flag = 1;
            for (int k = 1; k < i; k++)
            {
                if (strncmp(id, id + k * sub_l, sub_l)) {
                    flag = 0;
                    break;
                }
            }
            if (flag) return 1;
        }

        return 0;

    default:
        printf("Invalid part number encounted: %d\n", part);
        exit(1);
    }
}