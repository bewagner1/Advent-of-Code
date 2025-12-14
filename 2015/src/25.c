/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>

size_t next_code(size_t code);

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

    size_t row, col;
    if (fscanf(infile, "To continue, please consult the code grid in the manual.  Enter the code at row %zu, column %zu.", &row, &col) != 2)
    {
        printf("Error parsing file\n");
        fclose(infile);
        exit(1);
    }
    fclose(infile);


    size_t code = 20151125;
    size_t n = col + ((row + col - 2) * (row + col - 1)) / 2;
    for (size_t i=1; i<n; i++) code = next_code(code);

    printf("The code is %zu\n", code);

    return 0;
}


size_t next_code(size_t code)
{
    return (code * 252533) % 33554393;
}