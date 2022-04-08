// This file contains the main execution loop of the daemon
// as well as its start method (executed when the [--start]
// option is identified by the summoner

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "utils.h" // Contains functions used to communicate with the daemon and check if it is running
#include "vars.h" // Contains the named pipe's path and the buffer size

// The main execution loop of the daemon
// Listens to the communication pipe for instructions and sends back the appropriate response
void run() {
    // Save the start time and initialize the instruction buffer
    time_t summoned = time(NULL);
    char instruction[BUFFER_SIZE];

    // Main loop
    while (1) {
        // Read data from the pipe into the instruction buffer
        receive(instruction);

        // Compare the received data to the list of predefined instructions
        if (!strcmp(instruction, "date")) { // --date
            // Save the current time and generate a tm structure to represent the date from our current time
            time_t t = time(NULL);
            struct tm date = *localtime(&t);

            // Declare our response buffer and print the formatted date into it
            char response[BUFFER_SIZE];
            sprintf(response, "%d-%d-%d", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);

            // Send our response buffer
            send(response);

        } else if (!strcmp(instruction, "duration")) { // --duration
            // Declare our response buffer and print the number of seconds since start into the response buffer
            char response[BUFFER_SIZE];
            sprintf(response, "%ld", time(NULL) - summoned);

            // Send our response buffer
            send(response);

        } else if (!strcmp(instruction, "reset")) { // --reset
            // Set the start time to the current time
            summoned = time(NULL);

            // Send a confirmation message
            send("ok");

        } else if (!strcmp(instruction, "stop")) { // --stop
            // Send a confirmation message
            send("stopping");

            // Delete the communication pipe and exit the main loop
            unlink(SPELL_PATH);
            break;
        }
    }
}

// Used when the [--start] option is identified
// Creates a new process and separates it from the terminal,
// then creates the communication pipe and starts the execution loop
int start() {
    // If there is a daemon currently running, we inform the user and exit the program
    if (!is_haunted()) {
        printf("A demon is already haunting you!\nUse 'summoner --stop' to banish it to the shadow realm\n");
        exit(EXIT_FAILURE);
    }
    // First fork to ensure we are not the process group leader
    pid_t pid = fork();

    // If an error occurred, we exit the program
    if (pid < 0) exit(EXIT_FAILURE);
    // If we are the parent process, we exit the program
    if (pid > 0) exit(EXIT_SUCCESS);

    // At this point, we are the child of the original process
    // Create a new session
    if (setsid() < 0) exit(EXIT_FAILURE);
    // Second fork to ensure we are not the process group leader
    pid = fork();


    // If an error occurred, we exit the program
    if (pid < 0) exit(EXIT_FAILURE);
    // If we are the parent process, we exit the program
    if (pid > 0) exit(EXIT_SUCCESS);

    // At this point, we are the grandchild of the original process
    // Create the communication pipe
    if (mkfifo(SPELL_PATH, 0644)) {
        // If the pipe creation failed, we inform the user and exit the process
        perror("Couldn't talk to demon!");
        exit(EXIT_FAILURE);
    }

    // Start the main execution loop and exit once finished
    run();
    exit(EXIT_SUCCESS);
}
