// This file contains utility functions for communication between the summoner and the daemon,
// as well as checking whether the daemon is currently running.

#include <fcntl.h>
#include <unistd.h>

#include "vars.h" // Contains the named pipe's path and the buffer size

// Used to check whether the daemon is currently running (returns 0 in that case)
int is_haunted() {
    // Simply check whether the pipe currently exists
    return access(SPELL_PATH, F_OK);
}

// Used to read data from the communication pipe into the buffer
void receive(char* buffer) {
    // Open the pipe in read-only mode
    int fd = open(SPELL_PATH, O_RDONLY);

    // read [BUFFER_SIZE] bytes into the buffer argument.
    read(fd, buffer, BUFFER_SIZE);

    // Close the pipe
    close(fd);
}

// Used to write data into the communication pipe
void send(char* data) {
    // Open the pipe in write-only mode
    int fd = open(SPELL_PATH, O_WRONLY);

    // write [BUFFER_SIZE] bytes of the data into the pipe
    write(fd, data, BUFFER_SIZE);

    // Close the pipe
    close(fd);
}
