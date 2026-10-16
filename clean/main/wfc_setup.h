/* The Wi-Fi Connection library (overlay 65) set up outside the network code: its first start,
 * whose result is kept for one reader, and a run of the program of overlay 1 with the library's
 * memory functions and a 256 KiB work area.
 *
 * The work area of 0x700 bytes and the results 0-3 match the NitroDWC library's DWC_Init; the
 * result 4 kept after it has been read is the game's own. */
#ifndef CLEAN_MAIN_WFC_SETUP_H
#define CLEAN_MAIN_WFC_SETUP_H

#include "types.h"

/* What WfcSetup_TakeInitResult gives once the result has been taken (and before any start). */
#define WFC_SETUP_NO_RESULT 4

void WfcSetup_RunOverlay1(void);
void WfcSetup_Free(int name, void *block, unsigned int size);
void *WfcSetup_Alloc(int name, unsigned int size, int align);
unsigned char WfcSetup_TakeInitResult(void);
int WfcSetup_InitLibrary(void);

#endif
