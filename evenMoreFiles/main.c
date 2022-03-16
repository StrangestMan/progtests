#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char ***threed = calloc(1, sizeof(char**));
    int curIndex = 0;
    int numLines = 1;

    char **buffer = calloc(2, sizeof(char*));
    for(int i = 0; i < 2; i++) {
        buffer[i] = calloc(4096, sizeof(char));
    }
    int bufferIndex = 0;

    FILE *fp;
    fp = fopen("test", "r");

    char c;
    char *stupidBuffer = &c;
    int loop = 1;
    while(loop) {
        c = fgetc(fp);
        *stupidBuffer = c;

        switch(c) {
            case(';'):
                bufferIndex++;
            break;
            case('\n'):
                threed[curIndex] = calloc(2, sizeof(char*));
                for(int i = 0; i < 2; i++) {
                    threed[curIndex][i] = calloc(strlen(buffer[i]) + 1, sizeof(char));
                    strcpy(threed[curIndex][i], buffer[i]);
                }

                // Something is wrong with THIS bit of code. Everything else works fine
                bufferIndex = 0;
                curIndex++;
                numLines++;

                for(int i = 0; i < 2; i++) {
                    strcpy(buffer[i], "");
                }

                threed = realloc(threed, numLines * sizeof(char**));

            break;
            case(EOF):
                loop = 0;
            break;
            default:
                strcat(buffer[bufferIndex], stupidBuffer);
            break;
        }
    }

    fclose(fp);
    free(buffer);

    printf("String from threed: %s\n", threed[0][1]);

    return 0;
}