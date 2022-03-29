#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void help(){
    printf("Usage: invoker [option]\n");
    printf("Options: \n");
    printf("\t--date\t\tDisplay the date\n");
    printf("\t--duration\tShows how long the program has been running\n");
    printf("\t--help\t\tDisplay this information\n");
    printf("\t--reset\t\tReset the demon's counter\n");
    printf("\t--restart\tRestart the demon\n");
    printf("\t--start\t\tLaunch the demon\n");
    printf("\t--status\tDisplay the status of the daemon (alive/dead)\n");
    printf("\t--stop\t\tStop the demon\n");
};

int main(int argc, char** argv) {
    FILE *incantation_stream;
    char *incantation_path="/tmp/daemon.incantation.txt";


    if(mkfifo(incantation_path, 0644) != 0) {
        perror("No demons in the astral plane. Can't invoke any!");
        exit(1);
    }

    if (argc < 2) {
        printf("Too many arguments\nEnter 'invoker --help' to get help\n");
        return -1;
    } else if (argc > 2) {
        printf("Too few arguments\nEnter 'invoker --help' to get help\n");
        return -1;
    } else if (!strcmp(argv[1], "--start")) {
        printf("Invoking demon...\n");
        execl("./demon", "demon", NULL);
    } else if (!strcmp(argv[1], "--help")) {
        help();
    } else {
        printf("Invalid argument: %s\nEnter 'invoker --help' to get help\n", argv[1]);
        return -1;
    }

    pid_t pid = fork();
    switch(pid) {
        case -1:
            printf("Couldn't invoke demon");
            exit(-1);
        case 0:
            execl("./demon", "demon", NULL);
        default:
            incantation_stream = fopen(incantation_path, "w");
            fprintf(incantation_stream, "coucou\n");
            unlink(incantation_path);
            exit(0);
    }
}
