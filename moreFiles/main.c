#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    fp = fopen("test", "r");

    char **buffer = calloc(2, sizeof(char*));
    for(int i = 0; i < 2; i++) {
        buffer[i] = calloc(4096, sizeof(char));
    }
    int bufferIndex = 0;

    char c;                                        // This is infuriatingly dumb, and I shouldn't need to use this hackey solution, but C has forced my hand
    char *dummyBuffer = calloc(1, sizeof(char *)); // This is dumb, but also the only way to free the pointer after use

    int loop = 0;
    while(loop == 0) {
        c = fgetc(fp);
        *dummyBuffer = c;

        switch(c) {
            case(';'):
                bufferIndex++;
            break;
            case(EOF):
                loop = 1;
            break;
            default:
                strcat(buffer[bufferIndex], dummyBuffer);
            break;
        }
    }

    free(dummyBuffer);
    fclose(fp);

    for(int i = 0; i < 2; i++) {
        printf("String %d: %s\n", i, buffer[i]);
    }

    free(buffer);

    return 0;
}