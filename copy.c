#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 800

int main() {
    char source_file[256], dest_file[256];
    char buffer[BUFFER_SIZE];
    int fd_source, fd_dest;
    ssize_t bytes_read;

    printf("Enter source file name: ");
    scanf("%s", source_file);

    printf("Enter destination file name: ");
    scanf("%s", dest_file);

    fd_source = open(source_file, O_RDONLY);
    if (fd_source < 0) {
        perror("Error opening source file");
        return 1;
    }

    fd_dest = open(dest_file, O_WRONLY | O_CREAT, 0644); // Corrected permissions
    if (fd_dest < 0) {
        perror("Error opening destination file");
        close(fd_source); // Close source file if destination open fails
        return 1;
    }

    while ((bytes_read = read(fd_source, buffer, BUFFER_SIZE)) > 0) {
        if (write(fd_dest, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(fd_source);
            close(fd_dest);
            return 1;
        }
    }
    if (bytes_read < 0) { // Check for read errors
        perror("Error reading source file");
        close(fd_source);
        close(fd_dest);
        return 1;
    }


    close(fd_source);
    close(fd_dest);

    printf("File copied successfully!\n");
    return 0;
}
