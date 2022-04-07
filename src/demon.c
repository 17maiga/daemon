#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "vars.h"

int main() {
    time_t summoned = time(NULL);
    int status = 1;
    int incantations = open(INCANTATION_PATH, O_RDONLY);
    char buffer[BUFFER_SIZE];

    while (status) {

        if (read(incantations, buffer, BUFFER_SIZE) != 0) {
            if (!strcmp(buffer, "date")) {
                int curses = open(CURSE_PATH, O_WRONLY);
                time_t t = time(NULL);
                struct tm date = *localtime(&t);
                char output[BUFFER_SIZE];
                sprintf(output, "%d-%d-%d", date.tm_mday, date.tm_mon +1, date.tm_year + 1900);
                write(curses, output, BUFFER_SIZE);
                close(curses);

            } else if (!strcmp(buffer, "duration")) {
                int curses = open(CURSE_PATH, O_WRONLY);
                char output[BUFFER_SIZE];
                sprintf(output, "%ld", time(NULL) - summoned);
                write(curses, output, BUFFER_SIZE);
                close(curses);

            } else if (!strcmp(buffer, "reset")) {
                summoned = time(NULL);

            } else if (!strcmp(buffer, "stop")) {
                close(incantations);
                unlink(INCANTATION_PATH);
                unlink(CURSE_PATH);
                status = 0;
            }
        } else {

        }
    }
    exit(0);
}