#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t summoned = time(NULL);
    int status = 1;

    char* incantation_path = "/tmp/daemon.incantation.txt";
    FILE* incantation_stream = fopen(incantation_path, "r");

    char* curse_path = "/tmp/daemon.curse.txt";
    if(mkfifo(curse_path, 0644) != 0) {
        perror("A demon is already summoned!\nUse 'summoner --stop' to banish it to the shadow realm\n");
        exit(1);
    }

    while (status) {
        char incantation[50];
        fscanf(incantation_stream, "%s", incantation);
        if (!strcmp(incantation, "--stop")) {
            status = 0;
        } else if (!strcmp(incantation, "--date")) {
            printf("bite");
            time_t now;
            time(&now);
            struct tm *local = localtime(&now);
            int day = local->tm_mday;
            int month = local->tm_mon;
            int year = local->tm_year;
            FILE* curse_stream = fopen(curse_path, "w");
            fprintf(curse_stream, "%d %d %d", day, month, year);
            unlink("curse_path");
        } else if (!strcmp(incantation, "--reset")) {
            summoned = time(NULL);
        }
    }
    remove(incantation_path);
    remove(curse_path);
    exit(0);
}