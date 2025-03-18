#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 128 

int main(void){

    char buffer[BUFFER_SIZE];
    char *token, *saveptr;
    ssize_t bytesRead;


    while (1) { // Infinite loop
        bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytesRead < 0) {
            write(STDERR_FILENO, "Error reading input\n", 20);
            return 1;
        }
        buffer[bytesRead] = '\0';
        token = strtok_r(buffer, " ", &saveptr);
        while(token){
            write(STDOUT_FILENO, token, strlen(token));
            write(STDOUT_FILENO, "\n", 1);
            token = strtok_r(NULL, " ", &saveptr);
        }

    }

    return 0;
}