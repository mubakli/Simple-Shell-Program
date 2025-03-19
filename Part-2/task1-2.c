#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100

// Define a structure to hold a command and its arguments.
struct command {
    char *name;   // command name (e.g., "ls")
    char **args;  // array of arguments (including command name as args[0])
};

// Function: tokenize_input
// Tokenizes the given input string into an array of tokens.
// It returns a pointer to an array of char pointers (tokens) and updates num_tokens.
char **tokenize_input(char *input, int *num_tokens) {
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    
    int i = 0;
    // Tokenize input based on space, newline and tab characters.
    char *token = strtok(input, " \n\t");
    while(token != NULL && i < MAX_TOKENS - 1) {
        tokens[i++] = token;
        token = strtok(NULL, " \n\t");
    }
    tokens[i] = NULL;  // NULL-terminate the array for exec family calls.
    *num_tokens = i;
    return tokens;
}

// Function: execute_command
// Takes a pointer to a struct command and runs the command by forking a child process.
// The child process calls execvp() to run the command.
void execute_command(struct command *cmd) {
    pid_t pid = fork();
    
    if(pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0) { 
        // Child process: execute the command.
        execvp(cmd->name, cmd->args);
        // If execvp returns, an error occurred.
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process: wait for the child to finish.
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    
    // Prompt the user to enter a command.
    printf("Enter command: ");
    if(fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        exit(EXIT_FAILURE);
    }
    
    // Tokenize the input string.
    int num_tokens = 0;
    char **tokens = tokenize_input(input, &num_tokens);
    
    // Check if the user entered any command.
    if(num_tokens == 0) {
        fprintf(stderr, "No command entered.\n");
        free(tokens);
        return 0;
    }
    
    // Prepare the command structure.
    struct command cmd;
    cmd.name = tokens[0];
    cmd.args = tokens;  // tokens is a NULL-terminated array suitable for execvp.
    
    // Execute the command.
    execute_command(&cmd);
    
    // Free the allocated memory for tokens.
    free(tokens);
    
    return 0;
}
