/* Per-scene facts of main: four tables of a byte for each of the 52 scenes, whether any player
 * is in one of the scenes 0x0c-0x0e and 0x2e-0x2f, and main's entry record.
 *
 * The entry record (data_021f69d0) holds where the next scene is entered: its first byte is
 * the scene being gone to (0x3f for none, func_020b6454 sets it), byte 1 says the scene's own
 * point is used, then a position and an angle (scene_setup.h). */
#ifndef CLEAN_MAIN_SCENE_TABLES_H
#define CLEAN_MAIN_SCENE_TABLES_H

#include "types.h"

#define SCENE_TABLES_SCENES 52

int SceneTables_NoPlayerInClosedScene(void);
unsigned char SceneTables_Value20e8(unsigned int scene);
unsigned char SceneTables_HeapCount(unsigned int scene);
unsigned char SceneTables_FirstCount(unsigned int scene);
unsigned char SceneTables_SecondCount(unsigned int scene);
int SceneTables_EntryRecord(void);

#endif
