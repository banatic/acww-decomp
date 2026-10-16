/* Checks of the library overlay slot (library_overlay.h). */
#include "library_overlay.h"

#include <stdint.h>

#include "clean.h"

extern LibraryOverlaySlot data_021d11c4;
extern char SDK_OVERLAY_ov065_ID;
extern char SDK_OVERLAY_ov066_ID;
extern char SDK_OVERLAY_ov067_ID;
extern void OS_Terminate(void);

/* The overlay in the slot; none while one is being loaded. */
static int current_overlay(void)
{
    if (data_021d11c4.loading) {
        return -1;
    }
    return data_021d11c4.overlay;
}

/* The number of an overlay, which the linker gives as the address of its symbol. */
static int overlay_id(const char *symbol)
{
    return (int) (uintptr_t) symbol;
}

/* func_02073044: stops the game unless the slot holds overlay 65, 66 or 67; 1 otherwise. */
unsigned int LibraryOverlay_RequireAny(void)
{
    int overlay = current_overlay();
    if (overlay == overlay_id(&SDK_OVERLAY_ov065_ID) || overlay == overlay_id(&SDK_OVERLAY_ov066_ID) ||
        overlay == overlay_id(&SDK_OVERLAY_ov067_ID)) {
        return 1;
    }
    OS_Terminate();
    return 0; /* not reached: OS_Terminate does not return */
}
CLEAN_AS(func_02073044, LibraryOverlay_RequireAny)

/* func_02073090: stops the game unless the slot holds overlay 67. */
void LibraryOverlay_Require67(void)
{
    if (current_overlay() != overlay_id(&SDK_OVERLAY_ov067_ID)) {
        OS_Terminate();
    }
}
CLEAN_AS(func_02073090, LibraryOverlay_Require67)

/* func_020730c8: stops the game unless the slot holds overlay 66. */
void LibraryOverlay_Require66(void)
{
    if (current_overlay() != overlay_id(&SDK_OVERLAY_ov066_ID)) {
        OS_Terminate();
    }
}
CLEAN_AS(func_020730c8, LibraryOverlay_Require66)

/* func_02073100: stops the game unless the slot holds overlay 65. */
void LibraryOverlay_Require65(void)
{
    if (current_overlay() != overlay_id(&SDK_OVERLAY_ov065_ID)) {
        OS_Terminate();
    }
}
CLEAN_AS(func_02073100, LibraryOverlay_Require65)
