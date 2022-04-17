// File and string handling
#include <stdio.h>
#include <string.h>

// Memory management
#include <stdlib.h>

// Needed to use stat()
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Needed for off_t
#include <stdint.h>


// Get the size of a file specified in FILENAME (const char *)
off_t getFilesize(const char *);

// Return a string that contains the entire file. Needs a FILENAME and FILESIZE (const char *, const int FILESIZE)
char* fileToBuffer(const char *, const int FILESIZE);


int main() {
    const char *FILENAME = "structure.test";
    off_t filesize = 0;
    char *filebuf = NULL;

    // Get the filesize and stick the file into a buffer
    filesize = getFilesize(FILENAME);
    filebuf = fileToBuffer(FILENAME, filesize);

    // Print the buffer to make sure it works
    //printf("%s\n", filebuf);
    
    // Create a buffer to split file into lines
    off_t buffSize = 1;
    off_t buffIndex = 0;
    char **buff = NULL;

    buff = calloc(buffSize, sizeof(char*));

    for(char *token = strtok(filebuf, "\n"); token != NULL; token = strtok(NULL, "\n")) {
        buff[buffIndex] = calloc(strlen(token) + 1, sizeof(char));
        strcpy(buff[buffIndex], token);

        buffSize++;
        buffIndex++;

        buff = reallocarray(buff, buffSize, sizeof(char*));
    }

    // Create a second buffer to split lines into strings

    off_t buff2Size = 1;
    off_t buff2Index = 0;
    char **buff2 = NULL;
    buff2 = calloc(buff2Size, sizeof(char*));

    // I've gotta figure out why buffSize causes a segfault, but buffSize - 1 doesn't. My intuition says either the final index in buffSize doesn't exist, or is NULL
    for(int i = 0; i < buffSize - 1; i++) {
        for(char *token = strtok(buff[i], ";"); token != NULL; token = strtok(NULL, ";")) {
            buff2[buff2Index] = calloc(strlen(token) + 1, sizeof(char));
            strcpy(buff2[buff2Index], token);

            buff2Size++;
            buff2Index++;

            buff2 = reallocarray(buff2, buff2Size, sizeof(char*));
        }
    }

    // Print the fully split buffer to check if it works
    for(int i = 0; i < buff2Size - 1; i++) {
        printf("%s\n", buff2[i]);
    }

    // IDK if this is actually doing anything. It doesn't crash though
    free(filebuf);

    return 0;
}

off_t getFilesize(const char *FILENAME) {
    off_t filesize = 0;
    struct stat fileinfo;

    // Use stat to get the filesize
    stat(FILENAME, &fileinfo);
    filesize = fileinfo.st_size + 1; // +1 to account for the EOF

    return filesize;
}

char* fileToBuffer(const char *FILENAME, const int FILESIZE) {
    FILE *fp;
    char *filebuf = NULL;

    fp = fopen(FILENAME, "r");
    filebuf = calloc(FILESIZE, sizeof(char));

    // Read the whole file into the buffer
    fread(filebuf, sizeof(char), FILESIZE, fp);

    return filebuf;
}