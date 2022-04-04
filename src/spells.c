#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "spells.h"

char* incantation_path = "/tmp/daemon.incantation.txt";
char* curse_path = "/tmp/daemon.curse.txt";

void date() {
    if (access(incantation_path, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    FILE* incantation_stream = fopen(incantation_path, "w");
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(incantation_stream, "%ld %ld %s", tv.tv_sec, tv.tv_usec, "date");
    fclose(incantation_stream);

    FILE* curse_stream = fopen(curse_path, "r");
    long output;
    fscanf(curse_stream, "%ld", &output);
    fclose(curse_stream);
    printf("%lds have passed since January 1st, 1970\n", output);
}
void duration() {
    if (access(incantation_path, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    FILE* incantation_stream = fopen(incantation_path, "w");
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(incantation_stream, "%ld %ld %s", tv.tv_sec, tv.tv_usec, "duration");
    fclose(incantation_stream);

    FILE* curse_stream = fopen(curse_path, "r");
    long output;
    fscanf(curse_stream, "%ld", &output);
    fclose(curse_stream);
    printf("The demon has been haunting you for %lds\n", output);
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
    if (access(incantation_path, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    FILE* incantation_stream = fopen(incantation_path, "w");
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(incantation_stream, "%ld %ld %s", tv.tv_sec, tv.tv_usec, "reset");
    fclose(incantation_stream);
    printf("The demon has been reset\n");
}
int start() {
    pid_t pid = fork();
    switch(pid) {
        case -1:
            printf("Couldn't summon a demon!\n");
            exit(-1);
        case 0:
            execl("./demon", "demon", NULL);
        default:
            if (mkfifo(incantation_path, 0666) != 0) {
                perror("Couldn't talk to demon!");
                exit(1);
            }
            if (mkfifo(curse_path, 0666) != 0) {
                perror("The demon can't talk to you!");
                exit(1);
            }
            printf("A demon has been summoned!\n");
            exit(0);
    }
}
void status() {
    if (access(incantation_path, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
    } else {
        printf("A demon is haunting you!\nUse 'summoner --stop' to banish it to the shadow realms\n");
    }
    exit(0);
}
void stop() {
    if (access(incantation_path, F_OK)) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(0);
    }
    FILE* incantation_stream = fopen(incantation_path, "w");
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(incantation_stream, "%ld %ld %s", tv.tv_sec, tv.tv_usec, "stop");
    fclose(incantation_stream);
    printf("The demon has been banished\n");
}
