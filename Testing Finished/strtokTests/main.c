#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is to determine why strtok() is giving me weirdness off-by-1 errors on the size of a buffer

int main() {
    const char *SAMPLE_TEXT = "This is some sample-text;It should split on semicolons;Maybe newlines too";
    char *nc_sample = calloc(strlen(SAMPLE_TEXT) + 1, sizeof(char));
    strcpy(nc_sample, SAMPLE_TEXT);
    
    int bufferSize = 1;
    int bufferIndex = 0;
    char **buffer = NULL;
    buffer = calloc(bufferSize, sizeof(char*));

    /*
    for(char *holder = strtok(nc_sample, ";"); holder != NULL; holder = strtok(NULL, ";")) {
        buffer[bufferIndex] = calloc(strlen(holder) + 1, sizeof(char));
        strcpy(buffer[bufferIndex], holder);

        bufferIndex++;
        bufferSize++;
        buffer = reallocarray(buffer, bufferSize, sizeof(char*));
    }

    printf("bufferSize: %d, bufferIndex: %d\n", bufferSize, bufferIndex);
    for(int i = 0; i < 3; i++) {
        printf("%s\n", buffer[i]);
    }
    */

    // Goddamn off-by-one errors. bufferSize is the literal size, but not the range of the index. If the bufferSize is 4, the bufferIndex is 3, and the array spans
    //  indexes 0-2. There has to be some way to avoid allocating an extra pointer or increase the bufferIndex/Size
    //      I could always just decrement the values and reallocate the buffer to the proper size, but that's a hack solution I'd rather avoid


    // Cool. Didn't expect that weird if statement syntax to work
    for(char *holder = strtok(nc_sample, ";"); holder != NULL;) {
        buffer[bufferIndex] = calloc(strlen(holder) + 1, sizeof(char));
        strcpy(buffer[bufferIndex], holder);

        if((holder = strtok(NULL, ";")) != NULL) {
            bufferIndex++;
            bufferSize++;
            buffer = reallocarray(buffer, bufferSize, sizeof(char*));
        }
    }

    for(int i = 0; i < bufferSize; i++) {
        printf("%s\n", buffer[i]);
    }

    return 0;
}