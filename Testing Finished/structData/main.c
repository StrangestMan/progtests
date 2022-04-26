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

    // Split the file buffer into smaller lines (by newline)
    for(char *token = strtok(filebuf, "\n"); token != NULL;) {
        buff[buffIndex] = calloc(strlen(token) + 1, sizeof(char));
        strcpy(buff[buffIndex], token);

        if((token = strtok(NULL, "\n")) != NULL) {
            buffSize++;
            buffIndex++;
            buff = reallocarray(buff, buffSize, sizeof(char*));
        }
    }

    for(int i = 0; i < buffSize; i++) {
        printf("%s\n", buff[i]);
    }
    printf("\n");
    printf("Size of buff: %ld, Index: %ld\n\n", buffSize, buffIndex);

    // Create a second buffer to split lines into strings
    off_t buff2Size = 1;
    off_t buff2Index = 0;
    char **buff2 = NULL;
    buff2 = calloc(buff2Size, sizeof(char*));

    // Split each line into smaller strings (by semicolon)
    for(int i = 0; i < buffSize; i++) {
        for(char *token = strtok(buff[i], ";"); token != NULL;) {
            buff2[buff2Index] = calloc(strlen(token) + 1, sizeof(char));
            strcpy(buff2[buff2Index], token);

            if((token = strtok(NULL, ";")) != NULL) {
            buff2Size++;
            buff2Index++;
            buff2 = reallocarray(buff2, buff2Size, sizeof(char*));
            }
        }
        if(i < buffSize - 1) {
            buff2Size++;
            buff2Index++;
            buff2 = reallocarray(buff2, buff2Size, sizeof(char*));
        }
    }

    // The reason this broke for a while is because my code assumes that the current index is empty and needs to be allocated. If the buffer's index didn't increment
    //  then it allocates more memory to the same address (causing a memory leak) and copys the new string into the space (losing the old string's info)

    // Slapping on another if-statement just to allocate the buffer to be slightly larger isn't perfect, but it's better than reallocating strings needlessly
    
    for(int i = 0; i < buff2Size; i++) {
        printf("%s\n", buff2[i]);
    }
    printf("\nSize of buff2: %ld, Index: %ld\n", buff2Size, buff2Index);
    
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