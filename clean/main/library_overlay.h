/* The slot (data_021d11c4) that holds one of the library overlays 65-67 (or overlay 68) while
 * it runs: the number of the overlay in it (-1 for none), whether it is being loaded and the
 * overlay's information (LibraryOverlay_Load loads one, LibraryOverlay_End ends it). The code
 * that needs a library first checks that the slot holds it, and stops the game (OS_Terminate)
 * when it does not. The slot is a global object of the game, set to -1 when the game starts;
 * its destructor (LibraryOverlay_Destroy) does nothing. */
#ifndef CLEAN_MAIN_LIBRARY_OVERLAY_H
#define CLEAN_MAIN_LIBRARY_OVERLAY_H

#include "types.h"

typedef struct LibraryOverlaySlot {
    int overlay; /* -1 for none */
    u8 loading;
    u8 unk_05[3];
    u8 info[]; /* 0x08: the overlay's information (FSOverlayInfo) */
} LibraryOverlaySlot;

unsigned int LibraryOverlay_RequireAny(void);
void LibraryOverlay_Require67(void);
void LibraryOverlay_Require66(void);
void LibraryOverlay_Require65(void);
int LibraryOverlay_Load(LibraryOverlaySlot *slot, int overlay);
void LibraryOverlay_End(LibraryOverlaySlot *slot);
void LibraryOverlay_Destroy(LibraryOverlaySlot *slot);
int LibraryOverlay_Switch68(void);
void LibraryOverlay_Switch65(void);
void LibraryOverlay_Switch66(void);

#endif
