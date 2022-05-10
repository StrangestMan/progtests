#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdbool.h>

bool isFile(const char *);
bool isFolder(const char *);

int main() {
    const char *PATH1 = "folder";
    const char *PATH2 = "folder/file";

    printf("(1 = true, 0 = false)\nPath 1: File - %d, Folder - %d\nPath 2: File - %d, Folder - %d\n", isFile(PATH1), isFolder(PATH1), isFile(PATH2), isFolder(PATH2));

}

bool isFile(const char *PATH) {
    struct stat info;
    stat(PATH, &info);
    bool result = S_ISREG(info.st_mode);
    return result;
}

bool isFolder(const char *PATH) {
    struct stat info;
    stat(PATH, &info);
    bool result = S_ISDIR(info.st_mode);
    return result;
}