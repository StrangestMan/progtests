#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *src;
    char *dest;
    int srcLength;
    int destLength;

    int index;
} confLine;

void initConfLine(confLine *);

int main() {
    // Open the test file
    FILE *fp;
    fp = fopen("lines.test", "r");

    int confSize = 1;
    int confIndex = 0;
    confLine *config = calloc(confSize, sizeof(confLine));

    int buffIndex = 0;
    int DEF_BUFFSIZE = 2;
    int buffSize = DEF_BUFFSIZE;
    char **buffer = calloc(2, sizeof(char*));
    for(int i = 0; i < 2; i++) {
        buffer[i] = calloc(DEF_BUFFSIZE, sizeof(char));
    }
    char *sbuffer = calloc(1, sizeof(char));

    for(char c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        switch(c) {
            default:
                *sbuffer = c;
                strcat(buffer[buffIndex], sbuffer);
                buffSize++;
                buffer[buffIndex]  = reallocarray(buffer[buffIndex], buffSize, sizeof(char));
            break;
            case(';'):
                buffIndex++;
                buffSize = DEF_BUFFSIZE;
            break;
            case('\n'):
                initConfLine(&config[confIndex]);

                config[confIndex].srcLength = strlen(buffer[0]) + 1;
                config[confIndex].destLength = strlen(buffer[1]) + 1;

                config[confIndex].src = reallocarray(config[confIndex].src, config[confIndex].srcLength, sizeof(char));
                config[confIndex].dest = reallocarray(config[confIndex].dest, config[confIndex].destLength, sizeof(char));

                strcpy(config[confIndex].src, buffer[0]);
                strcpy(config[confIndex].dest, buffer[1]);

                buffIndex = 0;
                buffSize = DEF_BUFFSIZE;
                for(int i = 0; i < 2; i++) {
                    buffer[i] = realloc(buffer[i], buffSize * sizeof(char));
                    strcpy(buffer[i], "");
                }

                confSize++;
                confIndex++;
                config = reallocarray(config, confSize, sizeof(confLine));

            break;
        }
    }

    printf("%s ; %s\n%s ; %s\n", config[0].src, config[0].dest, config[1].src, config[1].dest);
    // HEEEEEEEEEEEEEEEEEEEELLLLLLLLLLLLLLLL YYYYYYYYYYYYYEEEEEEEEEEEEEEAAAAAAAAAAAAAAHHHHHHHHH
    // I didn't believe this would ever work

    return 0;
}

// Initalizes the variables in a given confLine object
void initConfLine(confLine *obj) {
    obj->srcLength = 2;
    obj->destLength = 2;

    obj->src = calloc(obj->srcLength, sizeof(char));
    obj->dest = calloc(obj->destLength, sizeof(char));

    obj->index = 0;
}