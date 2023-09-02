#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct record {
    int id;
    char name[80];
};

int main() {
    int fd, size = sizeof(struct record);
    struct record info;
    char filename[] = "004_datafile";

    fd = open(filename, O_RDWR);
    read(fd, &info, size);
    close(fd);

    fd = open(filename, O_RDWR);
    read(fd, &info, size);

    info.id = 99;
    lseek(fd, -size, SEEK_CUR);
    write(fd, &info, size);

    close(fd);
}