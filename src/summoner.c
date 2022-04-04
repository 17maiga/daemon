#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spells.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Too few arguments\nEnter 'summoner --help' to get help\n");
        exit(-1);
    } else if (argc > 2) {
        printf("Too many arguments\nEnter 'summoner --help' to get help\n");
        exit(-1);
    }

    if (!strcmp(argv[1], "--date")) {
        printf("Getting the date...\n");
        date();
        exit(0);

    } else if (!strcmp(argv[1], "--duration")) {
        printf("Getting the duration...\n");
        duration();
        exit(0);

    } else if (!strcmp(argv[1], "--help")) {
        help();
        exit(0);

    } else if (!strcmp(argv[1], "--reset")) {
        printf("Resetting the demon...\n");
        reset();
        exit(0);

    } else if (!strcmp(argv[1], "--restart")) {
        printf("Restarting the demon...\n");
        stop();
        start();

    } else if (!strcmp(argv[1], "--start")) {
        printf("Summoning demon...\n");
        start();

    } else if (!strcmp(argv[1], "--status")) {
        status();

    } else if (!strcmp(argv[1], "--stop")) {
        printf("Stopping the demon...\n");
        stop();
        exit(0);

    } else {
        printf("Unknown incantation: %s\nEnter 'summoner --help' to display the summoner's manual\n", argv[1]);
        return -1;
    }
}