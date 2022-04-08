// This file contains the functions executed by summoner.c when the option
// passed in by the user matches one of the predefined options, except the
// [--start] option

// cf. spells.c for implementation

#ifndef DAEMON_SPELLS_H
#define DAEMON_SPELLS_H

void date();
void duration();
void help();
void reset();
void status();
void stop();

#endif //DAEMON_SPELLS_H
