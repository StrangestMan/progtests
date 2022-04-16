#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdint.h>

off_t getFilesize(const char *);

int main() {
    // Filename and size
    const char *FILENAME = "split.test";
    off_t filesize = getFilesize(FILENAME);
    
    // Open the file for reading
    FILE *fp;
    fp = fopen(FILENAME, "r");
    
    // Put the whole file into a buffer
    char *filebuf = NULL;
    filebuf = calloc(filesize, sizeof(char));
    fread(filebuf, sizeof(char), filesize, fp);

    // Need to learn more about this
    /*
    for(char c; *filebuf; filebuf++) {
        c = *filebuf;
        printf("%c", c);
    }
    */

    // Create a buffer to store everything
    int bufIndex = 0;
    int bufSize = 1;
    char **buf = calloc(bufSize, sizeof(char*));

    // Use strtok() to split the massive string into smaller ones
    for(char *tokenHolder = strtok(filebuf, "\n"); tokenHolder != NULL; tokenHolder = strtok(NULL, "\n")) {
        buf[bufIndex] = calloc(strlen(tokenHolder) + 1, sizeof(char));
        strcpy(buf[bufIndex], tokenHolder);

        bufIndex++;
        bufSize++;

        buf = reallocarray(buf, bufSize, sizeof(char*));
    }

    for(int i = 0; i < bufSize; i++) {
        printf("%s ", buf[i]);
    }

    // Why the hell did setting filebuf to null fix the segfault?
    filebuf = NULL;
    free(filebuf);

    return 0;
}

// Get the filesize without opening the file
off_t getFilesize(const char *filename) {
    off_t filesize = 0;
    struct stat fileinfo;

    stat(filename, &fileinfo);
    filesize = fileinfo.st_size + 1; // +1 to account for the EOF
    
    return filesize;
}