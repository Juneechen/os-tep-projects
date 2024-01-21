#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *infile;
    int32_t count;
    int ch;

    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) { // for each file
        infile = fopen(argv[i], "r");
        if (infile == NULL) { // file cannot be opened
            printf("wunzip: cannot open file\n");
            return 1;
        }

        // use fread for reading binary data
        while (fread(&count, sizeof(int32_t), 1, infile) == 1) {
            // fread(&ch, sizeof(char), 1, infile);
            ch = fgetc(infile);
            for (int i = 0; i < count; i++) {
                // printf("%c", ch);
                fputc(ch, stdout);
            }
        }

        fclose(infile);
    }
}