#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "vars.h"

void date() {
    if (access(SPELL_PATH, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    int incantations = open(SPELL_PATH, O_WRONLY);
    write(incantations, "date", BUFFER_SIZE);
    close(incantations);

    int curses = open(SPELL_PATH, O_RDONLY);
    char output[BUFFER_SIZE];
    read(curses, output, BUFFER_SIZE);
    close(curses);
    printf("The current date in hell is the %s\n", output);
}

void duration() {
    if (access(SPELL_PATH, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    int incantations = open(SPELL_PATH, O_WRONLY);
    write(incantations, "duration", BUFFER_SIZE);
    close(incantations);

    int curses = open(SPELL_PATH, O_RDONLY);
    char output[BUFFER_SIZE];
    read(curses, output, BUFFER_SIZE);
    close(curses);
    printf("The demon has been haunting you for %s\n", output);
}

void help() {
    printf("Usage: summoner [option]\n");
    printf("Options: \n");
    printf("\t--date\t\tDisplay the date\n");
    printf("\t--duration\tShows how long the demon has been haunting you\n");
    printf("\t--help\t\tDisplay the summoner's manual\n");
    printf("\t--reset\t\tReset the demon's counter\n");
    printf("\t--restart\tBanish the current demon and summon a new demon\n");
    printf("\t--start\t\tSummon a demon\n");
    printf("\t--status\tDisplay the status of the demon (alive/dead)\n");
    printf("\t--stop\t\tBanish the demon\n");
}

void reset() {
    if (access(SPELL_PATH, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    int incantations = open(SPELL_PATH, O_WRONLY);
    write(incantations, "reset", BUFFER_SIZE);
    printf("The demon has been reset\n");
}

int start() {
    if (access(SPELL_PATH, F_OK) == 0) {
        printf("A demon is already haunting you!\nUse 'summoner --stop' to banish it to the shadow realm\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
//    if (pid < 0) exit(EXIT_FAILURE);
//    if (pid > 0) exit(EXIT_SUCCESS);
//    if (setsid() < 0) exit(EXIT_FAILURE);
//    pid = fork();
//    if (pid < 0) exit(EXIT_FAILURE);
//    if (pid > 0) exit(EXIT_SUCCESS);
    switch(pid) {
        case -1:
            printf("Couldn't summon a demon!\n");
            exit(EXIT_FAILURE);
        case 0:
            setsid();
            execl("./demon", "demon", NULL);
        default:
            if (mkfifo(SPELL_PATH, 0644) != 0) {
                perror("Couldn't talk to demon!");
                exit(EXIT_FAILURE);
            }
            printf("A demon has been summoned!\n");
            exit(EXIT_SUCCESS);
    }
}

void status() {
    if (access(SPELL_PATH, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
    } else {
        printf("A demon is haunting you!\nUse 'summoner --stop' to banish it to the shadow realms\n");
    }
    exit(EXIT_SUCCESS);
}

void stop() {
    if (access(SPELL_PATH, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    int incantations = open(SPELL_PATH, O_WRONLY);
    write(incantations, "stop", BUFFER_SIZE);
    printf("The demon has been banished\n");
}
