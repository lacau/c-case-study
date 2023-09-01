#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("002", O_WRONLY | O_CREAT, 0644);
    if(fd <0) {
        printf("Error number: %d\n", errno);
        perror("002");
        exit(1);
    }
    
    write(fd, "hello", 11);
    close(fd);
}