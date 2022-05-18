#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/sendfile.h>
#include <fcntl.h>

#include "main.h"

int main() {
    // Set the umask to exclude non-users from reading, writing, or executing. Then, change the working directory to / (root) (active directory will be specified later)
    //umask(0077);
    //chdir("/");

    linefiles *test;
    uint64 testSize;
    test = readConfig("test.conf", &testSize);

    for(int i = 0; i < testSize; i++) {
        copyFiles(test[i].srcpath, test[i].destpath);
    }

    return 0;
}

uint64 getFileSize(const char *PATH) {
    // Get the info of a file via stat
    struct stat info;
    stat(PATH, &info);
    
    // Return the filesize of the specified file
    return info.st_size;
}

char * configToBuffer(const char *PATH, const int FILESIZE) {
    // Variables needed to read a file into a string
    FILE *fp;
    char *filebuf = NULL;

    // Open the file & allocate memory for it
    fp = fopen(PATH, "r");
    filebuf = calloc(FILESIZE + 1, sizeof(char));

    // Read the whole file into memory
    fread(filebuf, sizeof(char), FILESIZE, fp);

    // Return the file now in a string
    return filebuf;
}

linefiles * readConfig(const char *PATH, uint64 *size) {
    // Read the config file into a buffer
    char *filebuf = configToBuffer(PATH, getFileSize(PATH));

    // Buffer for first pass of organization
    uint64 p1bSize = 1;
    uint64 p1bIndex = 0;
    char **pass1Buf = NULL;

    pass1Buf = calloc(p1bSize, sizeof(char*)); // Initalize the array for later

    // First pass of splitting the config up
    for(char *token = strtok(filebuf, "\n"); token != NULL; ) {
        pass1Buf[p1bIndex] = calloc(strlen(token) + 1, sizeof(char));
        strcpy(pass1Buf[p1bIndex], token);

        if((token = strtok(NULL, "\n")) != NULL) {
            p1bSize++;
            p1bIndex++;
            pass1Buf = reallocarray(pass1Buf, p1bSize, sizeof(char*));
        }
    }

    // Free the file buffer now that it's in memory again
    free(filebuf);

    // Buffer for second pass of organization
    uint64 p2bSize = 1;
    uint64 p2bIndex = 0;
    char **pass2Buf = NULL;

    pass2Buf = calloc(p2bSize, sizeof(char*));

    // Second pass of splitting the config
    for(uint64 i = 0; i < p1bSize; i++) {
        for(char *token = strtok(pass1Buf[i], ";"); token != NULL;) {
            pass2Buf[p2bIndex] = calloc(strlen(token) + 1, sizeof(char));
            strcpy(pass2Buf[p2bIndex], token);

            if((token = strtok(NULL, ";")) != NULL) {
                p2bSize++;
                p2bIndex++;
                pass2Buf = reallocarray(pass2Buf, p2bSize, sizeof(char*));
            }
        }
        if(i < p1bSize - 1) {
            p2bSize++;
            p2bIndex++;
            pass2Buf = reallocarray(pass2Buf, p2bSize, sizeof(char*));
        }
    }

    // Free the buffer used for the first pass
    free(pass1Buf);

    /* ayyyy this is working
    for(uint64 i = 0; i < p2bSize; i++) {
        printf("%s\n", pass2Buf[i]);
    }
    */

    // Populate the linefiles object
    linefiles *fileobj = NULL;
    uint64 foSize = 1;
    uint64 foIndex = 0;

    fileobj = calloc(foSize, sizeof(*fileobj));

    for(uint64 i = 0; i < p2bSize; i += 2) {
        fileobj[foIndex].srcLength = strlen(pass2Buf[i]) + 1;
        fileobj[foIndex].srcpath = calloc(fileobj[foIndex].srcLength, sizeof(char));
        strcpy(fileobj[foIndex].srcpath, pass2Buf[i]);

        fileobj[foIndex].destLength = strlen(pass2Buf[i + 1]) + 1;
        fileobj[foIndex].destpath = calloc(fileobj[foIndex].destLength, sizeof(char));
        strcpy(fileobj[foIndex].destpath, pass2Buf[i + 1]);

        if(i < p2bSize - 1) {
            foSize++;
            foIndex++;
            fileobj = reallocarray(fileobj, foSize, sizeof(linefiles));
        }
    }

    // Return fileobj if everything works
    *size = p1bSize;
    return fileobj;
}

int copyFiles(const char *SRC, const char *DEST) {
    // Get file info on the source
    struct stat info;
    stat(SRC, &info);

    // Open each file and get their descriptors
    int64 srcfd = open(SRC, O_RDONLY);
    int64 destfd = open(DEST, O_WRONLY | O_CREAT | O_TRUNC);

    // Send the contents of SRC to DEST, then copy SRC's file perms to DEST
    sendfile(destfd, srcfd, 0, info.st_size);
    fchmod(destfd, (info.st_mode & 0777));

    // Return 0 if all went well
    return 0;
}