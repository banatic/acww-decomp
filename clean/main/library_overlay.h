/* The slot (data_021d11c4) that holds one of the library overlays 65-67 while it runs: the
 * number of the overlay in it (-1 for none) and whether it is being loaded (func_02077b70
 * loads one, func_02077b9c ends it). The code that needs a library first checks that the slot
 * holds it, and stops the game (OS_Terminate) when it does not. */
#ifndef CLEAN_MAIN_LIBRARY_OVERLAY_H
#define CLEAN_MAIN_LIBRARY_OVERLAY_H

#include "types.h"

typedef struct LibraryOverlaySlot {
    int overlay; /* -1 for none */
    u8 loading;
} LibraryOverlaySlot;

unsigned int LibraryOverlay_RequireAny(void);
void LibraryOverlay_Require67(void);
void LibraryOverlay_Require66(void);
void LibraryOverlay_Require65(void);

#endif
