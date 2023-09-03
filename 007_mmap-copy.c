#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char *src, *dst;
    int fin, fout;
    size_t size;
    char src_file_name[] = "007_src";
    char dst_file_name[] = "007_dst";

    fin = open(src_file_name, O_RDONLY);
    if(fin < 0) {
        perror(src_file_name);
        exit(1);
    }

    size = lseek(fin, 0, SEEK_END);
    src = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fin, 0);
    if(src == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    fout = open(dst_file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fout < 0) {
        perror(dst_file_name);
        exit(1);
    }

    if(ftruncate(fout, size) == -1) {
        perror("truncate");
        exit(1);
    }

    dst = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fout, 0);
    if(dst == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    memcpy(dst, src, size);
    if(msync(dst, size, MS_SYNC) == -1) {
        perror("msync");
        exit(1);
    }

    exit(0);
}