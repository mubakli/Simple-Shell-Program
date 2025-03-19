#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 64

// Function to tokenize user input
char **tokenize_input(char *input) {
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    char *token;
    int pos = 0;

    if (!tokens) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " \t\r\n"); // Split by spaces/tabs/newlines
    while (token != NULL) {
        tokens[pos] = token;
        pos++;

        if (pos >= MAX_TOKENS) {
            fprintf(stderr, "Too many arguments\n");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " \t\r\n");
    }
    tokens[pos] = NULL; // Null-terminate the array
    return tokens;
}

// Function to execute a command using fork() and execvp()
void execute_command(char **args) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 
        // Child process executes the command
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
        }
        exit(EXIT_FAILURE);
    } else {
        // Parent process waits for child to finish
        waitpid(pid, NULL, 0);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char **args;

    while (1) {
        printf("mini-shell> ");
        if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
            perror("fgets failed");
            exit(EXIT_FAILURE);
        }

        // Exit condition
        if (strncmp(input, "exit", 4) == 0) {
            printf("Exiting shell...\n");
            break;
        }

        args = tokenize_input(input);
        if (args[0] != NULL) {  // Execute only if a command is entered
            execute_command(args);
        }

        free(args); // Free allocated memory
    }

    return 0;
}
