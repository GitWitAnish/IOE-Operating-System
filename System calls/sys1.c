// Write programs using the following system calls of UNIX operating system: fork, exec, getpid, exit, wait, close, stat.


#include <stdio.h>      // For printf, perror, FILE functions
#include <stdlib.h>     // For exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <unistd.h>     // For fork(), execlp()
#include <sys/wait.h>   // For wait()
#include <errno.h>      // For errno (error codes)
#include <string.h>     // For strerror() (convert error code to message)

// Main function: argc = argument count, argv = argument values
int main(int argc, char *argv[]) {

    // Check if user provided at least 3 arguments: program name, file, command
    if (argc < 3) {
        // Tell user how to run this program
        printf("Usage: %s <file> <command> [args...]\n", argv[0]);
        exit(EXIT_FAILURE); // Exit with error
    }

    // Fork a child process
    pid_t pid = fork();

    // If fork failed (pid < 0), print error and exit
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    // This block runs in the child process
    if (pid == 0) {
        printf("Child process running command: %s\n", argv[2]);

        // Replace child process with the command passed in argv[2...]
        // argv[2] = command, argv[3...] = arguments for that command
        execvp(argv[2], &argv[2]);

        // If execvp returns, it means it failed
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    // This block runs in the parent process
    else {
        printf("Parent process (PID %d) waiting for child to finish...\n", getpid());

        // Wait for the child process to complete
        wait(NULL);

        printf("Child finished. Now reading file: %s\n", argv[1]);

        // Open the file provided as argv[1] in read mode
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        // Read and print file content character-by-character
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }

        // Close the file
        fclose(file);
    }

    return EXIT_SUCCESS; // Program finished successfully
}




// run it with:
// ./sys1 test.txt ls -l
