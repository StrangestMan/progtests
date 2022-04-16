#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Create an empty string w/ a space of 4096
    char *buffer = calloc(4096, sizeof(*buffer));

    // Make sure the memory was properly allocated
    if(buffer == NULL) {
        fprintf(stderr, "That calloc call is brokey\n");
        return 1;
    }

    // Put some text in the string
    strcpy(buffer, "\nThis is some cool text\n");

    // Char for testing
    char c;

    // This is what I was interested in, the *buffer in the while loop
    while(*buffer) {
        //fputc(*((int *)buffer), stdout);
        c = *buffer;
        printf("%c", c);
        buffer++;
    }

    buffer--;

    while(*buffer) {
        fputc(*((int *)buffer), stdout);
        buffer--;
    }
    
    // Free the buffer (This fails for some reason - munmap_chunk(): Invalid pointer)
    //free(buffer);

    return 0;
}