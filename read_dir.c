#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILE_NAME 256

int main() {
    DIR *dir;
    struct dirent *dptr;
    char path[256];
    char buffer[MAX_FILES][MAX_FILE_NAME];
    int file_count = 0;

    printf("Enter Dir Name to be Opened: ");
    scanf("%255s", path);

    dir = opendir(path);

    if (dir != NULL) {
        while ((dptr = readdir(dir)) != NULL) {
            strcpy(buffer[file_count], dptr->d_name);
            file_count++;
        }

        closedir(dir);

        printf("Files in the directory:\n");

        for (int i = 0; i < file_count; i++) {
            printf("%s\n", buffer[i]);
        }
    } else {
        perror("Error opening directory");
    }

    return 0;
}
