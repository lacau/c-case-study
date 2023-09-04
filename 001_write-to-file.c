#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("001", O_WRONLY | O_CREAT, 0644);
    write(fd, "hello", 11);
    close(fd);
}