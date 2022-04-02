#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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

int start(char* incantation_path) {
    pid_t pid = fork();
    int incantation_int;
    switch(pid) {
        case -1:
            printf("Error");
            exit(-1);
        case 0:
            execl("./demon", "demon", NULL);
        default:
            if (mkfifo(incantation_path, 0666) != 0) {
                printf("Couldn't talk to demon!\n");
                exit(1);
            }
            exit(0);
    }
}

void test(char* incantation_path, char* curse_path) {
    int incantation_int = open(incantation_path, O_WRONLY);
    FILE* incantation_stream = fdopen(incantation_int, "w");
    fprintf(incantation_stream, "--test");
    unlink(incantation_path);

    int curse_int = open(curse_path, O_RDONLY);
    FILE* curse_stream = fdopen(curse_int, "r");
    char output[50];
    fscanf(curse_stream, "%s", output);
    puts(output);
    unlink(curse_path);
}

void stop(char* incantation_path) {
    int incantation_int = open(incantation_path, O_WRONLY);
    FILE* incantation_stream = fdopen(incantation_int, "w");
    fprintf(incantation_stream, "--stop");
    unlink(incantation_path);
}


int main(int argc, char** argv) {
    char* incantation_path = "/tmp/daemon.incantation.txt";
    char* curse_path = "/tmp/daemon.incantation.txt";

    if (argc < 2) {
        printf("Too few arguments\nEnter 'summoner --help' to get help\n");
        exit(-1);
    } else if (argc > 2) {
        printf("Too many arguments\nEnter 'summoner --help' to get help\n");
        exit(-1);
    }

    if (!strcmp(argv[1], "--start")) {
        printf("Summoning demon...\n");
        start(incantation_path);
    } else if (!strcmp(argv[1], "--test")) {
        printf("Getting the test...\n");
        test(incantation_path, curse_path);
    } else if (!strcmp(argv[1], "--stop")) {
        printf("Stopping the demon...\n");
        stop(incantation_path);
    } else if (!strcmp(argv[1], "--help")) {
        help();
    } else {
        printf("Unknown spell: %s\nEnter 'summoner --help' to display the summoner's manual\n", argv[1]);
        return -1;
    }
}