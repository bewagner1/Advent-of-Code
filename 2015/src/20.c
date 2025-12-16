/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>


size_t presents1(size_t house);
size_t presents2(size_t house);
size_t presents(size_t house, int part);


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./25.out <path/to/puzzle.txt> <part>\n");
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

    size_t n_presents;
    fscanf(infile, "%zu", &n_presents);
    fclose(infile);

    size_t i = 1;
    while (n_presents > presents(i, part)) i++;
    printf("%zu\n", i);

    return 0;
}


size_t presents1(size_t house)
{
    size_t n = 10;
    for (size_t elf=2; elf<=house; elf++)
    {
        if (house % elf == 0) n = n + 10 * elf;
    }

    return n;
}


size_t presents2(size_t house)
{
    size_t n = 11;
    for (size_t elf=2; elf<=house; elf++)
    {
        if (house % elf == 0 && house / elf <= 50) n = n + 11 * elf;
    }

    return n;
}


size_t presents(size_t house, int part)
{
    if (part == 1) return presents1(house);
    return presents2(house);
}