#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATTERN_LENGTH 256
#define MAX_FILE_NAME_LENGTH 256

int main() {
    char directory_name[MAX_FILE_NAME_LENGTH];
    char pattern[MAX_PATTERN_LENGTH];
    int count = 0; // number of files containing at least one occurrence of pattern
    int occurrence = 0; // total number of occurrences

    printf("Enter directory name: ");
    scanf("%s", directory_name);

    printf("Enter pattern: ");
    scanf("%s", pattern);

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(directory_name)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_name[0] == '.') {
            continue; // skip current and parent directories
        }

        char file_name[MAX_FILE_NAME_LENGTH];
        sprintf(file_name, "%s/%s", directory_name, ent->d_name);

        struct stat file_stat;
        if (stat(file_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISREG(file_stat.st_mode) && strstr(ent->d_name, ".txt") != NULL) {
            FILE *file;
            if ((file = fopen(file_name, "r")) == NULL) {
                perror("fopen");
                continue;
            }

            char line[1024];
            int file_occurrence = 0;
            while (fgets(line, sizeof(line), file) != NULL) {
                if (strstr(line, pattern) != NULL) {
                    occurrence++;
                    file_occurrence++;
                }
            }

            if (file_occurrence > 0) {
                count++;
                printf("%s: %d occurrence(s)\n", file_name, file_occurrence);
            }

            fclose(file);
        }
    }

    closedir(dir);

    printf("Total occurrences: %d\n", occurrence);
    printf("Number of files containing pattern: %d\n", count);

    return 0;
}
