/* Loading, ending and checking the library overlay slot (library_overlay.h). */
#include "library_overlay.h"

#include <stdint.h>

#include "clean.h"

static_assert(offsetof(LibraryOverlaySlot, loading) == 0x04, "loading");
static_assert(offsetof(LibraryOverlaySlot, info) == 0x08, "info");

extern LibraryOverlaySlot data_021d11c4;
extern char SDK_OVERLAY_ov065_ID;
extern char SDK_OVERLAY_ov066_ID;
extern char SDK_OVERLAY_ov067_ID;
extern void OS_Terminate(void);
extern void func_0204fa5c(void *info, int overlay); /* FS_LoadOverlayInfo of the main processor */
extern int FS_LoadOverlayImage(void *info);
extern void FS_StartOverlay(void *info);
extern void FS_EndOverlay(void *info);

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

/* func_02077b70: loads `overlay` (the address of its SDK_OVERLAY_ symbol) into the slot and
 * starts it; marked as loading meanwhile. Always 0. */
int LibraryOverlay_Load(LibraryOverlaySlot *slot, int overlay)
{
    slot->loading = 1;
    slot->overlay = overlay;
    func_0204fa5c(slot->info, overlay);
    FS_LoadOverlayImage(slot->info);
    FS_StartOverlay(slot->info);
    slot->loading = 0;
    return 0;
}
CLEAN_AS(func_02077b70, LibraryOverlay_Load)

/* func_02077b9c: ends the overlay in the slot and empties the slot. */
void LibraryOverlay_End(LibraryOverlaySlot *slot)
{
    FS_EndOverlay(slot->info);
    slot->overlay = -1;
}
CLEAN_AS(func_02077b9c, LibraryOverlay_End)

/* func_02077bb4: the slot's destructor, registered when the game starts; it does nothing. */
void LibraryOverlay_Destroy(LibraryOverlaySlot *slot)
{
    (void) slot;
}
CLEAN_AS(func_02077bb4, LibraryOverlay_Destroy)
