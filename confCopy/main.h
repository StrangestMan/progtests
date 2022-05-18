#ifndef __mainh_051320221531__
#define __mainh_051320221531__

// Define a 64 bit number for potential filesize
typedef unsigned long long int uint64;
typedef long long int int64;

// struct to hold info about source and destination files
typedef struct {
    char *srcpath;      // Path to the source file
    int srcLength;      // Length of the string that holds the path to src

    char *destpath;     // Path to the destination file
    int destLength;     // Length of the string that holds the path to dest
} linefiles;

// Returns the filesize of the file specified by PATH
uint64 getFileSize(const char *PATH);
// Returns the contents of the file specified by PATH as a string FILESIZE + 1 characters long
char * configToBuffer(const char *PATH, const int FILESIZE);

// Populates a linefiles array with the contents of the file pointed to by PATH
linefiles * readConfig(const char *PATH, uint64 *size);

// Copies files from SRC to DEST
int copyFiles(const char *SRC, const char *DEST);

#endif