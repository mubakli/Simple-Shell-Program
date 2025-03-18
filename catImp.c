#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main (int argc, char *argv[]){
    if( argc != 2 ){
        write(STDERR_FILENO, "Usage: ./cat <filename>\n", 25);
        return 1;
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    int fd = open (argv[1], O_RDONLY);
    
    if (fd < 0) {
        write(STDERR_FILENO, "Error opening file\n", 19);
        return 1;
    }

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    close(fd);
    return 0;
}