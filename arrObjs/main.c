#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **lines;

    int index;
    int *lengths;
} confLine;

int main() {
    // Open the test file
    FILE *fp;
    fp = fopen("lines.test", "r");

    // Initalize the config array
    int confSize = 1;
    int confIndex = 0;
    confLine *config = calloc(confSize, sizeof(confLine));
    
    // Create a buffer for storing each line
    char **buffer = calloc(2, sizeof(char*));
    for(int i = 0; i < 2; i++) {
        buffer[i] = calloc(2, sizeof(char));
    }
    int buffIndex = 0;
    int buffSize = 2;

    char *sbuffer = calloc(1, sizeof(char));
    for(char c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        switch(c) {
            default:
                *sbuffer = c;
                strcat(buffer[buffIndex], sbuffer);
                buffSize++;
                buffer[buffIndex] = reallocarray(buffer[buffIndex], buffSize, sizeof(char));
            break;
            case(';'):
                buffIndex++;
                buffSize = 2;
            break;
            case('\n'):

            break;
        }
    }

    printf("%s\n%s\n", buffer[0], buffer[1]);

    return 0;
}