#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    fp = fopen("test", "r");

    // Set up buffer
    int bufferSize = 2; // Buffer size of 2 to hold a single char and null character
    char *buffer = calloc(bufferSize, sizeof(char)); // Allocate the buffer's initial size
    char *sbuffer = calloc(1, sizeof(char)); // Create another "buffer" to do string operations

    // This took way too long for me to get right, but it works well
    for(char c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        *sbuffer = c;
        strcat(buffer, sbuffer);
        bufferSize++;
        
        buffer = realloc(buffer, bufferSize * sizeof(char));

    }

    printf("Size of buffer: %ld; Buffer contents: \n%s\n", strlen(buffer) + 1, buffer);

    free(buffer);
    free(sbuffer);

    return 0;
}