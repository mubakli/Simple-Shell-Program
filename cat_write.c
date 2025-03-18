#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main (int argc, char *argv[]){
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: ./cat_write <filename>\n", 30);
        return 1;
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        write(STDERR_FILENO, "Error opening file\n", 19);
        return 1;
    }

    while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        write(fd, buffer, bytesRead);
    }

    close(fd);


    return 0;
}