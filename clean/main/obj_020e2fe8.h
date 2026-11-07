/* The players' reporting process (vtable 0x020e2fe8, 0x50 bytes: a process and nothing more):
 * its constructor and creation; its phases are PlayerReportProcess_* in player_processes.c. */
#ifndef CLEAN_MAIN_OBJ_020E2FE8_H
#define CLEAN_MAIN_OBJ_020E2FE8_H

#include "autoload_2/process.h"

Process *PlayerReportProcess_Construct(Process *self);
void PlayerReportProcess_New(void);

#endif
