/* Usage example: arghandle -a -b -n 400 -t purple */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    int c;
    int aflag = 0;
    int bflag = 0;
    int numoption = 0;
    char txtoption[200] = "default";

    opterr = 0;

    while((c = getopt(argc, argv, "abn:t:")) != EOF) {
        switch(c) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'n':
                numoption = atoi(optarg);
                break;
            case 't':
                strcpy(txtoption, optarg);
                break;
            case '?':
                fprintf(stderr, "invalid option: -%c\n", optopt);
        }
    }

    if(aflag) printf("Option a is set\n");
    if(bflag) printf("Option b is set\n");
    printf("Numeric option values is %d\n", numoption);
    printf("Text    option values is %s\n", txtoption);

    argv += optind;
    argc -= optind;

    while(argc--) {
        printf("arg: %s\n", *argv++);
    }    
}