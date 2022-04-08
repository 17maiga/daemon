// This file contains the functions executed by summoner.c when the option
// passed in by the user matches one of the predefined options, except the
// [--start] option

#include <stdio.h>
#include <stdlib.h>

#include "utils.h" // Contains functions used to communicate with the daemon and check if it is running
#include "vars.h" // Contains the named pipe's path and the buffer size

// Used when the [--date] option is matched
// Asks the daemon for the current date
void date() {
    // If there is no daemon currently running, we inform the user and exit the program
    if (is_haunted()) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(EXIT_FAILURE);
    }

    // Send the "date" string to the daemon
    send("date");

    // Declare a string buffer and fill it with the value received from the daemon
    char buffer[BUFFER_SIZE];
    receive(buffer);

    // Display the received value
    printf("The current date in hell is the %s\n", buffer);
}

// Used when the [--duration] option is matched
// Asks the daemon for its execution time
void duration() {
    // If there is no daemon currently running, we inform the user and exit the program
    if (is_haunted()) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(EXIT_FAILURE);
    }

    // Send the "duration" string to the daemon
    send("duration");

    // Declare a string buffer and fill it with the value received from the daemon
    char buffer[BUFFER_SIZE];
    receive(buffer);

    // Display the received value
    printf("The demon has been haunting you for %s\n", buffer);
}

// Used when the [--help] option is matched
// Displays the summoner's help information
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

// Used when the [--reset] option is matched
// Instructs the daemon to reset its execution time counter
void reset() {
    // If there is no daemon currently running, we inform the user and exit the program
    if (is_haunted()) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(EXIT_FAILURE);
    }

    // Send the "reset" string to the daemon
    send("reset");

    // Inform the user that the daemon has been reset
    printf("The demon has been reset\n");
}

// Used when the [--status] option is matched
// Check whether the daemon is currently running and tell the user
void status() {
    if (is_haunted()) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
    } else {
        printf("A demon is haunting you!\nUse 'summoner --stop' to banish it to the shadow realms\n");
    }
}

// Used when the [--status] option is matched
// Instructs the daemon to stop running
void stop() {
    // If there is no daemon currently running, we inform the user and exit the program
    if (is_haunted()) {
        printf("No demon summoned!\nUse 'summoner --start' to summon a demon\n");
        exit(EXIT_FAILURE);
    }

    // Send the "stop" string to the daemon
    send("stop");

    // Inform the user that the daemon has been stopped
    printf("The demon has been banished\n");
}
