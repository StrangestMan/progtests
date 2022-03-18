#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    fp = fopen("test", "r");

    int bufferIndex = 0;
    int bufferSize = 2;
    char **buffer = calloc(2, sizeof(char*));
    if(buffer == NULL) {
        fprintf(stderr, "Calloc call for buffer's first dimension broke\n");
        return 1;
    }

    for(int i = 0; i < 2; i++) {
        buffer[i] = calloc(bufferSize, sizeof(char));
        if(buffer[i] == NULL) {
            fprintf(stderr, "Initalizing calloc call for buffer %d broke\n", i);
            return 1;
        }
    }

    char *sbuffer = calloc(1, sizeof(char));
    if(sbuffer == NULL) {
        fprintf(stderr, "Calloc call for sbuffer broke\n");
        return 1;
    }

    for(char c = getc(fp); c != EOF; c = fgetc(fp)) {
        switch(c) {
            default:
                *sbuffer = c;
                strcat(buffer[bufferIndex], sbuffer);
                bufferSize++;
                buffer[bufferIndex] = realloc(buffer[bufferIndex], bufferSize * sizeof(char));
                if(buffer[bufferIndex] == NULL) {
                    fprintf(stderr, "Realloc call for buffer %d resizing broke\n", bufferIndex);
                    return 1;
                }

            break;
            case(';'):
                bufferSize = 2;
                bufferIndex++;
            break;
        }
    }

    for(int i = 0; i < 2; i++) {
        printf("Buffer %d: %s\n", i, buffer[i]);
    }

    free(buffer);
    free(sbuffer);

    return 0;
}