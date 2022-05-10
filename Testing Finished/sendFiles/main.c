#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>

int main() {
    const char *PATHFROM = "folder/file";
    const char *PATHTO = "folder/other_folder/copied_file";
    struct stat info;

    stat(PATHFROM, &info);

    int fd1 = open(PATHFROM, O_RDONLY);
    int fd2 = open(PATHTO, O_WRONLY | O_CREAT | O_TRUNC, info.st_mode & 0777);

    //printf("perms: %o\n", info.st_mode & 0777);
    // Didn't think I'd get working code from Wikipedia, but I've been proven wrong. Apparently it was as easy as and-ing the number for max permissions

    sendfile(fd2, fd1, 0, info.st_size);

    close(fd2);
    close(fd1);

    return 0;
}