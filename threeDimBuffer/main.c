#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Open file for reading
    FILE *fp;
    fp = fopen("test", "r");


    // Initalize the config buffer /
    int configSize = 2;
    int configIndex = 0;
    char ***config = calloc(configSize, sizeof(char**)); // Initalizing this as a size of 2 just in case
    if(config == NULL) {
        fprintf(stderr, "Init calloc call for the config array broke\n");
        return 1;
    }

    for(int i = 0; i < 2; i++) {
        config[i] = calloc(2, sizeof(char*));
        if(config[i] == NULL) {
            fprintf(stderr, "Init for config's 2nd dimension broke\n");
            return 1;
        }
    }

    // -/

    // Create and initalize buffer for later use /
    int bufferIndex = 0;
    int bufferSize = 2;
    char **buffer = calloc(2, sizeof(char*));
    if(buffer == NULL) {
        fprintf(stderr, "Init calloc call for buffer broke\n");
        return 1;
    }

    // Init the 2nd dimension of the buffer to make it easier to copy things in
    for(int i = 0; i < 2; i++) {
        buffer[i] = calloc(bufferSize, sizeof(char));
        if(buffer[i] == NULL) {
            fprintf(stderr, "Secondary init calloc call for buffer broke\n");
            return 1;
        }
    }

    // sbuffer is basically just a char pointer, but is needed to do str operations
        // I could have used "char *sbuffer = NULL", but then I couldn't call free on it
    char *sbuffer = calloc(1, sizeof(char));
    if(sbuffer == NULL) {
        fprintf(stderr, "Init calloc call for sbuffer broke\n");
        return 1;
    }
    // -/ Done initalizing the buffer

    // Read the file
    for(char c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        switch(c) {
            default:
                *sbuffer = c;
                strcat(buffer[bufferIndex], sbuffer);

                bufferSize++;
                buffer[bufferIndex] = realloc(buffer[bufferIndex], bufferSize * sizeof(char));
                if(buffer[bufferIndex] == NULL) {
                    fprintf(stderr, "Buffer resizing broke\n");
                    return 1;
                }

            break;
            case(';'):
                bufferSize = 2;
                bufferIndex++;
            break;
            case('\n'):
                for(int i = 0; i < 2; i++) {
                    config[configIndex][i] = calloc(strlen(buffer[i]) + 1, sizeof(char));
                    if(config[configIndex][i] == NULL) {
                        fprintf(stderr, "Calloc call for config %d-%d broke\n", configIndex, i);
                        return 1;
                    }

                    strcpy(config[configIndex][i], buffer[i]);

                    configSize++;
                    configIndex++;

                    config = realloc(config, configSize * sizeof(char**));
                    if(config == NULL) {
                        fprintf(stderr, "Config reallocation %d-%d broke\n", configSize, configIndex);
                        return 1;
                    }

                    bufferIndex = 0;
                    bufferSize = 2;

                    for(int i = 0; i < 2; i++) {
                        strcpy(buffer[i], "");
                        buffer[i] = realloc(buffer[i], bufferSize * sizeof(char));
                    }
                }

            break;
        }
    }

    /* NO SEGFAULT BAYBEEEEEEE
    printf("%s\n", buffer[0]);
    printf("%s\n", buffer[1]);
    */

    // anything that isn't [0][0] causes a segfault
    printf("%s\n", config[0][0]);

    return 0;
}