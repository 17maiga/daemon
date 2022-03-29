//
// Created by maiga on 23/03/2022.
//
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main() {
    int status = 1;

    time_t invoked = time(NULL);

    char* incantation_path = "/tmp/daemon.incantation.txt", incantation[50];

    int incantation_file = open(incantation_path, O_RDONLY);
    FILE* incantation_stream = fdopen(incantation_file, "r");
    fscanf(incantation_stream, "%s", incantation);
    printf("%s", incantation);
//    puts(incantation);
//    unlink(incantation_path);
//    return 0;
    /*
    char* curse_path = "/tmp/daemon.curse.txt";
    int curse;
    FILE* curse_stream;
    while (status) {

    }
    */
}