// Write a programs to simulate UNIX commands like ls, grep, etc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <file>\n", argv[0]);
        return 1;
    }

    char *word = argv[1];    // Word to search
    char *filename = argv[2]; // File to search in
    char line[256];          // Buffer to store each line

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) { // Read file line by line
        if (strstr(line, word)) {             // Check if word exists in line
            printf("%s", line);               // Print the line
        }
    }

    fclose(file); // Close the file
    return 0;
}


// to run this
// ./sys3 hello test.txt


