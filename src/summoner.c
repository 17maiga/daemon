#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int start(char* incantation_path) {
    printf("Summoning demon...\n");
    if(mkfifo(incantation_path, 0644) != 0) {
        perror("A demon is already summoned!\nUse 'summoner --stop' to banish it to the shadow realm\n");
        exit(1);
    }
    pid_t pid = fork();
    FILE* incantation_stream;
    switch(pid) {
        case -1:
            printf("Couldn't summon a demon");
            exit(-1);
        case 0:
            execl("./demon", "demon", NULL);
        default:
            exit(0);
    }
}

int stop(char* incantation_path) {
    printf("Banishing demon...\n");
    if (access(incantation_path, F_OK) == 0) {
        FILE* incantation_stream = fopen(incantation_path, "w");
        fprintf(incantation_stream, "--stop");
        unlink(incantation_path);
        exit(0);
    } else {
        printf("No demon to banish!\nSummon a demon with 'summoner --start'\n");
        exit(-1);
    }
}

void help(){
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

int date(char* incantation_path, char* curse_path) {

    if (access(incantation_path, F_OK)) {
        printf("No demon to banish!\nSummon a demon with 'summoner --start'\n");
        exit(-1);
    }
    printf("1\n");
    FILE* incantation_stream = fopen(incantation_path, "w");
    fprintf(incantation_stream, "--date");
    unlink(incantation_path);

    while (access(curse_path, F_OK)) {

    }
    FILE* curse_stream = fopen(curse_path, "r");
    int day, month, year;
    fscanf(curse_stream, "%d %d %d", &day, &month, &year);
    printf("The demon indicates we're the %d/%d/%d\n", day, month, year);
    exit(0);

}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Too few spells at once!\nEnter 'summoner --help' to display the summoner's manual\n");
        return -1;
    } else if (argc > 2) {
        printf("Too many spells at once!\nEnter 'summoner --help' to display the summoner's manual\n");
        return -1;
    } else {
        char* incantation_path = "/tmp/daemon.incantation.txt";
        char* curse_path = "/tmp/daemon.curse.txt";

        if (!strcmp(argv[1], "--start")) {
            start(incantation_path);
        } else if (!strcmp(argv[1], "--help")) {
            help();
        } else if (!strcmp(argv[1], "--stop")) {
            stop(incantation_path);
        } else if (!strcmp(argv[1], "--date")) {
            date(incantation_path, curse_path);
        } else {
            printf("Unknown spell: %s\nEnter 'summoner --help' to display the summoner's manual\n", argv[1]);
            return -1;
        }
    }
}
