#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    DIR *d;
    struct dirent *info;
    struct stat sb;
    long total = 0;

    d = opendir(".");

    while((info = readdir(d)) != NULL) {
        stat(info->d_name, &sb);
        total += sb.st_size;
    }

    closedir(d);

    printf("total size: %ld\n", total);
}