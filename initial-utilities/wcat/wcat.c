#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    // char ch;
    char buffer[1000];

    if (argc < 2)
    {
        // printf("Usage: wcat <filename>\n"); 
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1;
        }

        // while ((ch = fgetc(fp)) != EOF)
        // {
        //     printf("%c", ch);
        // }
        
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        
        // if (feof(fp))
        // {
        //     printf("End of file reached.\n");
        // }
        // else
        // {
        //     printf("Something went wrong.\n");
        // }

        fclose(fp);
    }

    return 0;
}

