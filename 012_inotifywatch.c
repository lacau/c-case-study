#include <linux/limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>

// Buffer big enough to hold 100 events from one read 
#define BUFSIZE (100 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main() {
    FILE *fconfig;
    FILE *fout;
    char watchname[PATH_MAX];
    struct stat sb;
    int notifyfd, watchfd;
    char eventbuf[BUFSIZE];
    int n;
    char *p;
    struct inotify_event *event;

    // Names of watched files, indexed by watch descriptor
    char watchednames[100][NAME_MAX+1];

    notifyfd = inotify_init();

    // open configuration file
    if((fconfig = fopen("monitor.conf", "r")) == NULL) {
        printf("unable to open config file\n");
        exit(1);
    }

    // Read all watched file names from config file
    while(fgets(watchname, PATH_MAX, fconfig) != NULL) {
        // fgets retain newline char, so get rid of it
        int lastindex = strlen(watchname) -1;
        if(watchname[lastindex] == '\n')
            watchname[lastindex] = '\0';

        if(stat(watchname, &sb) < 0) {
            printf("Cannot stat %s, ignored\n", watchname);
            continue;
        }

        // Is a regular file
        if(S_ISREG(sb.st_mode)) {
            // Add to watch list
            if((watchfd = inotify_add_watch(notifyfd, watchname, IN_MODIFY | IN_DELETE_SELF)) < 0) {
                printf("error adding watch for %s\n", watchname);
            } else {
                printf("added %s to watch list on descriptor %d\n", watchname, watchfd);
                strcpy(watchednames[watchfd], watchname);
            }
        } else {
            printf("%s is not a regular file, ignored\n", watchname);
        }
    }

    fout = fopen("monitor.out", "a");

    while(1) {
        // read will block until event occurs
        n = read(notifyfd, eventbuf, BUFSIZE);

        // loop over events. this is a little tricky because event records are not fixed length

        for(p = eventbuf; p < eventbuf + n;) {
            event = (struct inotify_event *) p;
            p += sizeof(struct inotify_event) + event->len;

            if(event->mask & IN_MODIFY)
                fprintf(fout, "%s was modified\n", watchednames[event->wd]);
            if(event->mask & IN_DELETE_SELF)
                fprintf(fout, "%s was deleted\n", watchednames[event->wd]);

            fflush(fout);
        }
    }
}