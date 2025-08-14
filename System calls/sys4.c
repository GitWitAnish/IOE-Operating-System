// Write a program using the I/O system calls of UNIX operating system (open,read, write, etc)

#include <stdio.h>
#include <fcntl.h>      // For open(), creat()
#include <unistd.h>     // For read(), write(), close()
#include <sys/stat.h>   // For stat()

int main(int argc, char *argv[]) {
    int fd_in, fd_out;
    char buffer[100];
    ssize_t n;
    struct stat file_info;

    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0) {
        perror("Error opening input file");
        return 1;
    }

    // Create output file with read/write permissions
    fd_out = creat(argv[2], 0644);
    if (fd_out < 0) {
        perror("Error creating output file");
        close(fd_in);
        return 1;
    }

    // Read from input file and write to output file
    while ((n = read(fd_in, buffer, sizeof(buffer))) > 0) {
        if (write(fd_out, buffer, n) != n) {
            perror("Error writing to output file");
            close(fd_in);
            close(fd_out);
            return 1;
        }
    }

    // Display file size using stat
    if (stat(argv[1], &file_info) == 0) {
        printf("Input file size: %ld bytes\n", file_info.st_size);
    }

    // Close files
    close(fd_in);
    close(fd_out);

    printf("File copied successfully!\n");
    return 0;
}


// ./lab4 input.txt output.txt
