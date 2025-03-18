#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]){
     if (argc != 3) {
        write(STDERR_FILENO, "Usage: ./copy <source> <destination>\n", 37);
        return 1;
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    int srcFd = open(argv[1], O_RDONLY);
    if (srcFd < 0) {
        write(STDERR_FILENO, "Error opening source file\n", 26);
        return 1;
    }

    int destFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd < 0) {
        write(STDERR_FILENO, "Error opening destination file\n", 31);
        close(srcFd);
        return 1;
    }
    
    while ((bytesRead = read(srcFd, buffer, BUFFER_SIZE)) > 0) {
        write(destFd, buffer, bytesRead);
    }

    close(srcFd);
    close(destFd);

    write(STDOUT_FILENO, "File copied successfully!\n", 26);
    return 0;
}