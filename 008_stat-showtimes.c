#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct stat sb;

    stat("008_src", &sb);

    printf("last accessed: %s", ctime(&sb.st_atime));
    printf("last modified: %s", ctime(&sb.st_mtime));
    printf("last change: %s", ctime(&sb.st_ctime));
}