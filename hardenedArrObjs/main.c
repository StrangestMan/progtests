#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *src;
    char *dest;
    int srcLength;
    int destLength;
} confLine;

void initConfLine(confLine *);

int main() {
    // Open the test file
    FILE *fp;
    fp = fopen("lines.test", "r");
    if(fp == NULL) {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    // Create the config array
    int confSize = 1;
    int confIndex = 0;
    confLine *config = calloc(confSize, sizeof(confLine));
    if(config == NULL) {
        fprintf(stderr, "Could not initalize config array\n");
        return 1;
    }

    // Create a 2d buffer for reading the file
    int buffIndex = 0;
    int DEF_BUFFSIZE = 2;
    int buffSize = DEF_BUFFSIZE;
    char **buffer = calloc(2, sizeof(char*));
    if(buffer == NULL) {
        fprintf(stderr, "Could not allocate first dimension of buffer\n");
        return 1;
    }
    for(int i = 0; i < 2; i++) {
        buffer[i] = calloc(DEF_BUFFSIZE, sizeof(char));
        if(buffer[i] == NULL) {
            fprintf(stderr, "Could not initalize buffer[%d]\n", i);
            return 1;
        }
    }
    // sbuffer, short for stupid buffer, used to do string operations on the buffer
    char *sbuffer = calloc(1, sizeof(char));
    if(sbuffer == NULL) {
        fprintf(stderr, "Could not allocate space for sbuffer");
        return 1;
    }

    int readFile = 0;
    // I love the flexibility of for loops
    for(char c = fgetc(fp); readFile == 0; c = fgetc(fp)) {
        if(c == ';') {
            // Increase the buffer index to use the next buffer, if doing so wouldn't cause a crash
            if(buffIndex + 1 < 2) {
                buffIndex++;
                buffSize = DEF_BUFFSIZE;
            } else {
                fprintf(stderr, "Too many semicolons in string. Skipping to next line...\n");

                // Skip to the next newline
                for(char a = fgetc(fp); a != '\n'; a = fgetc(fp));
                // Scoot back 1 character to set up next object
                if(fseek(fp, -1 * sizeof(char), SEEK_CUR) == -1) {
                    fprintf(stderr, "fseek call broke");
                    return 1;
                }
            }
        } else if(c == '\n' || c == EOF) {
            // Initalize the current confLine object
            initConfLine(&config[confIndex]);
            if(config == NULL) {
                fprintf(stderr, "Couldn't initalize confLine, array destroyed\n");
                return 1;
            }

            // Set the lengths of each string for later copying
            config[confIndex].srcLength = strlen(buffer[0]) + 1;
            config[confIndex].destLength = strlen(buffer[1]) + 1;

            // Reallocate both arrays to fit the buffer
            config[confIndex].src = reallocarray(config[confIndex].src, config[confIndex].srcLength, sizeof(char));
            if(config[confIndex].src == NULL) {
                fprintf(stderr, "Could not reallocate config[%d].src\n", confIndex);
                return 1;
            }
            config[confIndex].dest = reallocarray(config[confIndex].dest, config[confIndex].destLength, sizeof(char));
            if(config[confIndex].dest == NULL) {
                fprintf(stderr, "Could not reallocate config[%d].dest\n", confIndex);
                return 1;
            }

            // Copy the buffer into the object
            strcpy(config[confIndex].src, buffer[0]);
            strcpy(config[confIndex].dest, buffer[1]);

            // Reset the buffer for the next iteration
            buffIndex = 0;
            buffSize = DEF_BUFFSIZE;
            for(int i = 0; i < 2; i++) {
                strcpy(buffer[i], "");
                buffer[i] = realloc(buffer[i], buffSize * sizeof(char));
                if(buffer[i] == NULL) {
                    fprintf(stderr, "Could not reset buffer[%d] size\n", i);
                    return 1;
                }
            }

            // Increase the size of the config array
            if(c != EOF) {
                confSize++;
                confIndex++;
                config = reallocarray(config, confSize, sizeof(confLine));
                if(config == NULL) {
                    fprintf(stderr, "Could not expand config array\n");
                    return 1;
                }
            }
        } else {
            // Copy the current character into the current buffer
            *sbuffer = c;
            strcat(buffer[buffIndex], sbuffer);
            
            // Reallocate the buffer to be 1 character larger
            buffSize++;
            buffer[buffIndex]  = reallocarray(buffer[buffIndex], buffSize, sizeof(char));
            if(buffer[buffIndex] == NULL) {
                fprintf(stderr, "Could not resize buffer[%d]\n", buffIndex);
                return 1;
            }
        }

        if(c == EOF) {
            readFile++;
        }
    }

    // The final 2 strings aren't properly coppied in becuase the switch doesn't copy on EOF. I need to fix that
    for(int i = 0; i < confSize; i++) {
        printf("%s ; %s\n", config[i].src, config[i].dest);
    }

    // Free stuff that isn't being used anymore
    free(buffer);
    free(sbuffer);
    if(fclose(fp) == EOF) {
        fprintf(stderr, "Error closing file\n");
        return 1;
    }

    return 0;
}

// Initalizes the variables in a given confLine object
void initConfLine(confLine *obj) {
    obj->srcLength = 2;
    obj->destLength = 2;

    obj->src = calloc(obj->srcLength, sizeof(char));
    if(obj->src == NULL) {
        fprintf(stderr, "Could not initalize src in confLine obj\n");
        obj = NULL;
        return;
    }

    obj->dest = calloc(obj->destLength, sizeof(char));
    if(obj->dest == NULL) {
        fprintf(stderr, "Could not initalize dest in confLine obj\n");
        obj = NULL;
        return;
    }
}