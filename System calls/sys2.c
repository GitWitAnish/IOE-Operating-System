// To write a program for implementing Directory management using the following system calls of UNIX operating system: opendir, readdir.


#include <stdio.h>      // For printf(), perror()
#include <stdlib.h>     // For exit(), EXIT_FAILURE
#include <dirent.h>     // For DIR, struct dirent, opendir(), readdir(), closedir()

int main(int argc, char *argv[]) {
    DIR *folder;                // Pointer to the directory
    struct dirent *entry;       // Pointer to each directory entry
    int count = 0;              // Counter for total items in directory

    // Step 1: Check if user provided a directory name as command-line argument
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1; // Exit with error code
    }

    // Step 2: Try to open the directory
    folder = opendir(argv[1]); // argv[1] = directory name given by user
    if (!folder) {             // If folder is NULL, opendir failed
        perror("Could not open directory"); // Print error reason
        return 1; // Exit with error code
    }

    // Step 3: Read and display directory contents
    printf("\nItems in directory:\n");
    while ((entry = readdir(folder)) != NULL) {  // Read next file/folder in directory
        printf("%s\n", entry->d_name);           // Print the name
        count++;                                 // Increase count
    }

    // Step 4: Close the directory
    closedir(folder);

    // Step 5: Print total number of items found
    printf("\nTotal items: %d\n", count);

    return 0; // Successful program end
}




// run it with:
// ./sys2 Demo