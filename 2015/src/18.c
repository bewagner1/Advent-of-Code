/**
 * 
 */


#include <stdio.h>
#include <stdlib.h>

int bounds_check(int row, int col, size_t dim);
char get_next_state(int row, int col, char* grid, size_t dim);
void update1(char* grid, char* change_grid, size_t dim);
void update2(char* grid, char* change_grid, size_t dim);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./18.out <path/to/puzzle.txt> <part>\n");
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

    const size_t dims = 100;
    char* grid = malloc(sizeof(char) * dims * dims);
    char* change_grid = malloc(sizeof(char) * dims * dims);

    char tok;
    size_t idx = 0;
    while ((tok = fgetc(infile)) != EOF)
    {
        if (tok == '\n') continue;
        grid[idx] = tok;
        idx++;
    }
    fclose(infile);

    if (part == 2)
    {
        grid[0] = '#';
        grid[dims-1] = '#';
        grid[dims*(dims-1)] = '#';
        grid[dims*dims-1] = '#';
    }


    for (int i=0; i<100; i++)
    {
        for (int r=0; r<dims; r++)
        {
            for (int c=0; c<dims; c++)
            {
                change_grid[dims * r + c] = get_next_state(r, c, grid, dims);
            }
        }
        if (part == 1) update1(grid, change_grid, dims);
        else update2(grid, change_grid, dims);
    }
    free(change_grid);

    size_t n_on = 0;
    for (int r=0; r<dims; r++)
    {
        for (int c=0; c<dims; c++)
        {
            if (grid[dims * r + c] == '#') n_on++;
        }
    }
    free(grid);
    printf("%zu\n", n_on);


    return 0;
}


int bounds_check(int row, int col, size_t dim)
{
    if (row < 0 || row >= dim) return 0;
    if (col < 0 || col >= dim) return 0;
    return 1;
}


char get_next_state(int row, int col, char* grid, size_t dim)
{
    char curr = grid[dim * row + col];
    u_int8_t n_on = 0;
    for (int r=row-1; r<=row+1; r++)
    {
        for (int c=col-1; c<=col+1; c++)
        {
            if (!bounds_check(r, c, dim) || (r == row && c == col)) continue;
            if (grid[r * dim + c] == '#') n_on++;
        }
    }
    switch (curr)
    {
        case '#':
            if (n_on == 2 || n_on == 3) return '#';
            return '.';

        case '.':
            if (n_on == 3) return '#';
            return '.';
        
        default:
            printf("Invalid state encountered: %c\n", curr);
            exit(1);
    }
}


void update1(char* grid, char* change_grid, size_t dim)
{
    for (size_t r=0; r<dim; r++)
    {
        for (size_t c=0; c<dim; c++)
        {
            grid[dim * r + c] = change_grid[dim * r + c];
        }
    }
}


void update2(char* grid, char* change_grid, size_t dim)
{
    for (size_t r=0; r<dim; r++)
    {
        for (size_t c=0; c<dim; c++)
        {
            if (r == 0 && c == 0) grid[dim * r + c] = '#';
            else if (r == 0 && c == dim-1) grid[dim * r + c] = '#';
            else if (r == dim-1 && c == 0) grid[dim * r + c] = '#';
            else if (r == dim-1 && c == dim-1) grid[dim * r + c] = '#';
            else grid[dim * r + c] = change_grid[dim * r + c];
        }
    }
}