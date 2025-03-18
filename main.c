#include<stdio.h>
#include<fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main (void){

    char fileName[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;


    write(STDOUT_FILENO, "Enter file name: ", 17);
    bytesRead = read(STDIN_FILENO, fileName, BUFFER_SIZE);
    if(bytesRead < 0 ){
        write(STDERR_FILENO, "Error reading input \n", 21);
        return 1;
    }

    int fd = open(fileName, O_WRONLY | O_CREAT, 0644);
    if( fd < 0 ){
        write(STDERR_FILENO, "Error opening file \n", 20);
        return 1; 
    }

    write(STDOUT_FILENO, "Enter text to save: ", 20);
    bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    if(bytesRead <= 0 ){
        write(STDERR_FILENO, "Error reading input \n", 21);
        close(fd);
        return 1;
    }

    write(fd, buffer, bytesRead);

    close(fd);

    write(STDOUT_FILENO, "File saved successfully!\n", 25);

    write(STDOUT_FILENO, buffer, bytesRead);


    return 0;
}