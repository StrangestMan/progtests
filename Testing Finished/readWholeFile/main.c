// Standard headers for I/O
#include <stdio.h>
#include <string.h>

// Memory management
#include <stdlib.h>

// Needed for stat()
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// 64 byte number
#include <stdint.h>

// Thanks to user9258013 for the examples (https://stackoverflow.com/a/54114840)
off_t ansiFilesize(const char *);
off_t posixFilesize(const char *);

int main() {
    const char *FILENAME = "bigfile.test";
    // Despite the name, bigfile really only needs to have a lot of characters

    printf("File size (ansi): %ld\n", ansiFilesize(FILENAME));
    printf("File size (posix): %ld\n", posixFilesize(FILENAME));

    off_t filesize = posixFilesize(FILENAME);
    char *filebuf = calloc(filesize + 1, sizeof(char));
    
    // This +1 offset is annoying, but works fine

    FILE *fp;
    fp = fopen(FILENAME, "r");

/*    
    // Fgets may be helpful for a different implementation, as it stops at newlines, but for now I need the whole file read into memory
    fgets(filebuf, filesize + 1, fp);
    // filesize contains the number of characters in the file, not including the EOF.
    // Adding the +1 offset makes it read the whole file, but is annoying.
    // This can be fixed by adding 1 to the returned value of posix/ansiFilesize
*/

    // This works though!
    fread(filebuf, sizeof(char), filesize + 1, fp);

    printf("Size of string: %ld; String: %s\n", strlen(filebuf) + 1, filebuf);

    return 0;
}

// This should, supposedly, work on any system
off_t ansiFilesize(const char *filename) {
    FILE *fp;
    off_t filesize = 0;
    
    fp = fopen(filename, "r");

    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);

    fclose(fp);
    return filesize;
}

// So far I like posix more because:
    // The end program will be linux exclusive
    // There's less code
    // Don't have to open the file
off_t posixFilesize(const char *filename) {
    off_t filesize = 0;

    struct stat info;
    stat(filename, &info);
    filesize = info.st_size;

    return filesize;
}