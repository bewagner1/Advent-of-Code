/**
 * 
 */

#include <stdio.h>
#include <stdlib.h>


int triple(char* s, const int len);
int doubledouble(char* s, const int len);
int letters(char* s, const int len);
int valid(char* s, const int len);
void increment(char* s, const int len);


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

    fseek(infile, 0, SEEK_END);
    long fsize = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    char* password = malloc(fsize+1);
    size_t bytes_read = fread(password, 1, fsize, infile);
    fclose(infile);
    password[bytes_read] = '\0';

    if (bytes_read > 0 && password[bytes_read - 1] == '\n') {
        password[bytes_read - 1] = '\0';
        bytes_read--;
    }
    const int length = bytes_read;
    
    if (valid(password, length)) increment(password, length);
    while (!valid(password, length)) increment(password, length);

    if (part == 2)
    {
        increment(password, length);
        while (!valid(password, length)) increment(password, length);
    }

    printf("Santa's new password should be %s\n", password);
    free(password);

    return 0;
}


int triple(char* s, const int len)
{
    for (int i=0; i<len-2; i++)
    {
        if (s[i] == s[i+1]-1 && s[i] == s[i+2]-2) return 1;
    }
    return 0;
}


int doubledouble(char* s, const int len)
{
    for (int i=0; i<len-3; i++)
    {
        if (s[i] != s[i+1]) continue;
        for (int j=i+2; j<len-1; j++)
        {
            if (s[j] == s[j+1]) return 1;
        }
    }
    return 0;
}


int letters(char* s, const int len)
{
    for (int i=0; i<len; i++)
    {
        if (s[i] == 'i' || s[i] == 'o' || s[i] == 'l') return 0;
    }
    return 1;
}


int valid(char* s, const int len)
{
    int ret = triple(s, len) && doubledouble(s, len);
    return ret && letters(s, len);
}


void increment(char* s, const int len)
{
    for (int i=len-1; i>=0; i--)
    {
        if (s[i] != 'z')
        {
            s[i] = s[i] + 1;
            return;
        }
        s[i] = 'a';
    }

    return;
}