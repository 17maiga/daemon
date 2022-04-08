// This file contains variables used throughout the program

#ifndef DAEMON_VARS_H
#define DAEMON_VARS_H

#define SPELL_PATH "/tmp/daemon.spell" // The path to the fifo used for communication between the daemon and the summoner
#define BUFFER_SIZE 50 // The number of bytes sent from the summoner to the daemon and vice-versa. Increase this value if you ever need to send more bytes.

#endif //DAEMON_VARS_H
