#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 128  // Adjust buffer size if needed

void read_and_print() {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while (1) {
        bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (bytesRead <= 0) {
            break;
        }
        buffer[bytesRead] = '\0';  // Null-terminate input
        write(STDOUT_FILENO, buffer, bytesRead);
    }
}

void read_word_by_word() {
    char buffer[BUFFER_SIZE];
    char *saveptr;
    
    while (1) {
        ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (bytesRead <= 0) {
            break;
        }
        buffer[bytesRead] = '\0';  // Null-terminate input

        char *token = strtok_r(buffer, " \n", &saveptr);
        while (token) {
            write(STDOUT_FILENO, token, strlen(token));
            write(STDOUT_FILENO, "\n", 1);
            token = strtok_r(NULL, " \n", &saveptr);
        }
    }
}

void cat_mode() {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while (1) {
        bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (bytesRead <= 0) {
            break;
        }
        buffer[bytesRead] = '\0';
        write(STDOUT_FILENO, buffer, bytesRead);
    }
}

void cat_to_file(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1)) > 0) {
        write(fd, buffer, bytesRead);
    }

    close(fd);
}

int main() {
    char command[BUFFER_SIZE];

    while (1) {
        write(STDOUT_FILENO, "Enter command: ", 15);
        ssize_t bytesRead = read(STDIN_FILENO, command, BUFFER_SIZE - 1);
        // if (bytesRead <= 0) {
        //     break;
        // }
        // command[bytesRead - 1] = '\0';  // Remove newline

        // if (strcmp(command, "exit") == 0) {
        //     break;
        // } else if (strcmp(command, "cat") == 0) {
        //     cat_mode();
        // } else if (strncmp(command, "cat > ", 6) == 0) {
        //     cat_to_file(command + 6);
        // } else {
        //     write(STDOUT_FILENO, "Unknown command\n", 16);
        // }
    }
    return 0;
}
