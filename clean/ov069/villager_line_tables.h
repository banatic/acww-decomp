/* Overlay 69: the tables of line members of the villagers' talk scenes (main's
 * villager_talk_scene.h and the villager_talk_*.c files that pick from them). Main's startup
 * loads the overlay as a library (startup.c) and ends it at once: its static initialiser
 * (ov069_static_init.c) fills fifteen tables of C++ pointers to member functions in the
 * overlay's own memory and has them copied into main's (VillagerLineTables_Copy), where they
 * stay once the overlay is gone. Each table is a list of triples (the line, the member at 0x10
 * of an event and the member run at each message, VillagerTalkScene_SetLines). */
#ifndef CLEAN_OV069_VILLAGER_LINE_TABLES_H
#define CLEAN_OV069_VILLAGER_LINE_TABLES_H

#include "ov004/member_pointer.h"
#include "types.h"

/* The fifteen tables. */
#define VILLAGER_LINE_TABLES 15

void VillagerLineTables_Copy(int unused_a, int unused_b);

#endif
