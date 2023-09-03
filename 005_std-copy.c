#include <stdio.h>
#define BSIZE 16384

int main() {
    FILE *fin, *fout;
    char buf[BSIZE];
    int count;
    char source[] = "005_source";
    char target[] = "005_target";

    fin = fopen(source, "r");
    fout = fopen(target, "w");

    while((count = fread(buf, 1, BSIZE, fin)) > 0)
        fwrite(buf, 1, count, fout);

    fclose(fin);
    fclose(fout);
}