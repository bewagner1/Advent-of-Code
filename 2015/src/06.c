/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void solve(FILE* infile, int part);
void turn_on1(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y);
void turn_off1(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y);
void toggle1(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y);
void turn_on2(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y);
void turn_off2(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y);
void toggle2(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y);


int main(int argc, char* argv[])
{

    if (argc != 3)
    {
        printf("Usage: ./06.out <path/to/puzzle.txt> <part>\n");
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

    solve(infile, part);

    return 0;
}


void solve(FILE* infile, int part)
{
    u_int32_t* lights = malloc(sizeof(u_int8_t) * 1e6);
    for (int i=0; i<1e6; i++) lights[i] = 0;

    u_int32_t low_x, low_y, high_x, high_y;
    char word1[8], word2[8];

    while (fscanf(infile, "%7s", word1) == 1)
    {
        if (strcmp(word1, "toggle") == 0)
        {
            fscanf(infile, "%d,%d through %d,%d", &low_x, &low_y, &high_x, &high_y);
            if (part == 1) toggle1(lights, low_x, low_y, high_x, high_y);
            else toggle2(lights, low_x, low_y, high_x, high_y);
        }
        else
        { 
            fscanf(infile, "%7s %d,%d through %d,%d", word2, &low_x, &low_y, &high_x, &high_y);
            if (strstr(word2, "on")) 
            {
                if (part == 1) turn_on1(lights, low_x, low_y, high_x, high_y);
                else turn_on2(lights, low_x, low_y, high_x, high_y);
            }
            else if (strstr(word2, "off"))
            {
                if (part == 1) turn_off1(lights, low_x, low_y, high_x, high_y);
                else turn_off2(lights, low_x, low_y, high_x, high_y);
            }
        }
    }
    fclose(infile);

    if (part == 1)
    {
        u_int32_t n_lights_on = 0;
        for (int i=0; i<1e6; i++) 
        {
            if (lights[i]) n_lights_on++;
        }
        free(lights);

        printf("%u lights are lit\n", n_lights_on);
    }
    else
    {
        u_int64_t total_brightness = 0;
        for (int i=0; i<1e6; i++) total_brightness = total_brightness + lights[i];
        free(lights);

        printf("The total brightness is %lld\n", total_brightness);
    }
}


void turn_on1(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y)
{
    for (int i=low_x; i<=high_x; i++)
    {
        for (int j=low_y; j<=high_y; j++)
        {
            lights[i*1000 + j] = 1;
        }
    }
}


void turn_off1(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y)
{
    for (int i=low_x; i<=high_x; i++)
    {
        for (int j=low_y; j<=high_y; j++)
        {
            lights[i*1000 + j] = 0;
        }
    }
}


void toggle1(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y)
{
    for (int i=low_x; i<=high_x; i++)
    {
        for (int j=low_y; j<=high_y; j++)
        {
            if (lights[i*1000 + j] == 0) lights[i*1000 + j] = 1;
            else if (lights[i*1000 + j] == 1) lights[i*1000 + j] = 0;
        }
    }
}


void turn_on2(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y)
{
    for (int i=low_x; i<=high_x; i++)
    {
        for (int j=low_y; j<=high_y; j++)
        {
            lights[i*1000 + j]++;
        }
    }
}


void turn_off2(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y)
{
    for (int i=low_x; i<=high_x; i++)
    {
        for (int j=low_y; j<=high_y; j++)
        {
            if (lights[i*1000 + j] > 0) lights[i*1000 + j]--;
        }
    }
}


void toggle2(u_int32_t* lights, u_int32_t low_x, u_int32_t low_y, u_int32_t high_x, u_int32_t high_y)
{
    for (int i=low_x; i<=high_x; i++)
    {
        for (int j=low_y; j<=high_y; j++)
        {
            lights[i*1000 + j]++;
            lights[i*1000 + j]++;
        }
    }
}