#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BSIZE 16384

int main() {
    int fin, fout;
    char buf[BSIZE];
    int count;
    char source[] = "003_source";
    char target[] = "003_target";

    if((fin = open(source, O_RDONLY)) < 0) {
        perror(source);
        exit(1);
    }

    if((fout = open(target, O_WRONLY | O_CREAT, 0644)) < 0) {
        perror(target);
        exit(1);
    }

    while((count = read(fin, buf, BSIZE)) > 0)
        write(fout, buf, count);

    close(fin);
    close(fout);
}