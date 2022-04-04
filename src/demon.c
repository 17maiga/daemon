#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

char* incantation_path = "/tmp/daemon.incantation.txt";
char* curse_path = "/tmp/daemon.curse.txt";

int main() {
    time_t summoned = time(NULL);
    struct timeval last_spell_time;
    gettimeofday(&last_spell_time, NULL);
    int status = 1;
    FILE* incantation_stream = fopen(incantation_path, "r");

    while (status) {
        char input[50];
        struct timeval spell_time;
        fscanf(incantation_stream, "%ld %ld %s", &spell_time.tv_sec, &spell_time.tv_usec, input);

        if (spell_time.tv_sec != last_spell_time.tv_sec || spell_time.tv_usec != last_spell_time.tv_usec) {
            last_spell_time = spell_time;

            if (!strcmp(input, "date")) {
                FILE* curse_stream = fopen(curse_path, "w");
                fprintf(curse_stream, "%ld", time(NULL));
                fclose(curse_stream);

            } else if (!strcmp(input, "duration")) {
                FILE* curse_stream = fopen(curse_path, "w");
                fprintf(curse_stream, "%ld", time(NULL) - summoned);
                fclose(curse_stream);

            } else if (!strcmp(input, "reset")) {
                summoned = time(NULL);

            } else if (!strcmp(input, "stop")) {
                fclose(incantation_stream);
                unlink(incantation_path);
                unlink(curse_path);
                status = 0;
            }
        }
        rewind(incantation_stream);
    }
    exit(0);
};