// This file contains utility functions for communication between the summoner and the daemon,
// as well as checking whether the daemon is currently running.

// cf. utils.c for implementation

#ifndef DAEMON_UTILS_H
#define DAEMON_UTILS_H

int is_haunted();
void receive(char* buffer);
void send(char* data);

#endif //DAEMON_UTILS_H
