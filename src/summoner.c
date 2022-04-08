// This file contains the main execution function for the summoner.
// This is the program the user will be interacting with. It handles
// reading and validating the user's input and executing the correct
// function if needed.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spells.h" // Contains the different functions associated with the defined options

int main(int argc, char** argv) {
    // First, we check whether there is one and only one argument
    // If that isn't the case, we exit the program
    if (argc < 2) {
        printf("Too few arguments\nEnter 'summoner --help' to get help\n");
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        printf("Too many arguments\nEnter 'summoner --help' to get help\n");
        exit(EXIT_FAILURE);
    }

    // We then compare the second argument (the option) to the list of defined options to try and find a match
    // If we find one, we inform the user of what we are about to do and run the appropriate function
    // If no match is found, we display an error message
    if (!strcmp(argv[1], "--date")) {
        printf("Getting the date...\n");
        date();

    } else if (!strcmp(argv[1], "--duration")) {
        printf("Getting the duration...\n");
        duration();

    } else if (!strcmp(argv[1], "--help")) {
        help();

    } else if (!strcmp(argv[1], "--reset")) {
        printf("Resetting the demon...\n");
        reset();

    // If the restart option is identified, we simply stop the current daemon and start it again.
    } else if (!strcmp(argv[1], "--restart")) {
        printf("Restarting the demon...\n");
        stop();
        start();

    } else if (!strcmp(argv[1], "--summon")) {
        printf("Summoning demon...\n");
        start();

    } else if (!strcmp(argv[1], "--status")) {
        status();

    } else if (!strcmp(argv[1], "--banish")) {
        printf("Stopping the demon...\n");
        stop();

    // If the option doesn't match any of the defined option, we inform the user that the option doesn't exist and exit the program
    } else {
        printf("Unknown spell: %s\nEnter 'summoner --help' to display the summoner's manual\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Once everything is finished, we exit the program
    exit(EXIT_SUCCESS);
}