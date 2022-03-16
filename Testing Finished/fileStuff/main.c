#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    fp = fopen("test", "r");

    char *buffer = calloc(4096, sizeof(char));
    char *buffer2 = calloc(1, sizeof(char));

    int loop = 0;
    char c;

    while(loop == 0) {
        c = fgetc(fp);
        if(c == EOF) {
            loop = 1;
        } else {
            *buffer2 = c;
            strcat(buffer, buffer2);
        }
    }

    printf("%s\n", buffer);

    fclose(fp);

    return 0;
}