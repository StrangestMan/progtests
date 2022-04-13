#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char str[] = "this/is/a/file/path.test";
    char *token = strtok(str, "/");
    
    
    
    return 0;
}