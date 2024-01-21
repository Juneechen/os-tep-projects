#include <stdio.h>  
// #include <stdlib.h>
// #include <string.h>

void runLenEncode(FILE *input, FILE *output, int *prev, int32_t *count) {
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (*prev == EOF) {
            *prev = ch;
            *count = 1;
        } else if (*prev == ch) {
            (*count)++;
        } else {
            fwrite(count, sizeof(int32_t), 1, output);
            fputc(*prev, output);
            *prev = ch;
            *count = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    FILE *output = stdout;
    int prev = EOF;
    int32_t count = 0;

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) { // for each file
        fp = fopen(argv[i], "r");
        if (fp == NULL) { // file cannot be opened
            printf("wzip: cannot open file\n");
            return 1;
        }

        runLenEncode(fp, output, &prev, &count);

        fclose(fp);
    }

    fwrite(&count, sizeof(int32_t), 1, output);
    fputc(prev, output);

    return 0;
}