#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat sb;

    char *filetype[] = {
        "unknown", "FIFO", "character device", "unknown", "directory",
        "unknown", "block device", "unknown", "file",
        "unknown", "symlink", "unknown", "socket"
    };

    if(argc != 2) {
        fprintf(stderr, "usage: listfile filename\n");
        exit(1);
    }

    if(stat(argv[1], &sb) < 0) {
        perror(argv[1]);
        exit(2);
    }

    printf("file type: %s\n", filetype[(sb.st_mode >> 12) & 017]);
    printf("persmissions: %c%c%c%c%c%c%c%c%c\n",
        (sb.st_mode & S_IRUSR) ? 'r' : '-',
        (sb.st_mode & S_IWUSR) ? 'w' : '-',
        (sb.st_mode & S_IXUSR) ? 'x' : '-',
        (sb.st_mode & S_IRGRP) ? 'r' : '-',
        (sb.st_mode & S_IWGRP) ? 'w' : '-',
        (sb.st_mode & S_IXGRP) ? 'x' : '-',
        (sb.st_mode & S_IROTH) ? 'r' : '-',
        (sb.st_mode & S_IWOTH) ? 'w' : '-',
        (sb.st_mode & S_IXOTH) ? 'x' : '-'
    );

    printf("last accessed: %s", ctime(&sb.st_atime));
    printf("last modified: %s", ctime(&sb.st_mtime));
    printf("last change: %s", ctime(&sb.st_ctime));
}