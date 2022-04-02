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
    char* curse_path = "/tmp/daemon.curse.txt";
    if(mkfifo(curse_path, 0644) != 0) {
        printf("The demon can't talk!\n");
        remove(incantation_path);
        exit(1);
    }

    while (status) {
        int incantation_int = open(incantation_path, O_RDONLY);
        FILE* incantation_stream = fdopen(incantation_int, "r");
        char input[50];
        fscanf(incantation_stream, "%s", input);
        puts(input);
        unlink(incantation_path);
        if (!strcmp(input, "--help")) {
            int curse_int = open(curse_path, O_WRONLY);
            FILE* curse_stream = fdopen(curse_int, "w");
            fprintf(curse_stream, "ceci est un test\n");
            unlink(curse_path);
        } else if (!strcmp(input, "--stop")) {
            remove(incantation_path);
            remove(curse_path);
            status = 0;
        }
    }

};