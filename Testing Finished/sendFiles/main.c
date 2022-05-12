#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>

int main() {
    // Variable definitions
    const char *PATHFROM = "folder/file";
    const char *PATHTO = "folder/other_folder/copied_file";
    struct stat info;

    // Get required info on the file to copy
    stat(PATHFROM, &info);

    int fd1 = open(PATHFROM, O_RDONLY); // Open the file to copy in read-only mode
    int fd2 = open(PATHTO, O_WRONLY | O_CREAT | O_TRUNC); // Open the result in write-only mode, and create / overwrite it
    // Sidenote: I don't know exactly why setting the mode in open() doesn't work, but I do know that I am now majorly annoyed because of it
    
    //printf("perms: %o\n", info.st_mode & 0777);
    // Didn't think I'd get working code from Wikipedia, but I've been proven wrong. Apparently it was as easy as and-ing the number for max permissions

    // Send all the contents of file 1 into file 2 from the beginning of the file
    sendfile(fd2, fd1, 0, info.st_size);

    // Chmod the file to the correct permissions
    fchmod(fd2, (info.st_mode & 0777));

    // Close open file descriptors
    close(fd2);
    close(fd1);

    return 0;
}