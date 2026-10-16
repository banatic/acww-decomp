/* The overlays loaded on request (overlay_groups.c loads and releases them one at a time):
 * twelve slots at data_021c80f4, each with the overlay's number, how many requests hold it,
 * and the memory it takes. A request for an overlay already loaded only counts one more; an
 * overlay is unloaded when the last request lets it go, or when a new one needs its memory and
 * no request holds it. */
#ifndef CLEAN_MAIN_OVERLAY_SLOTS_H
#define CLEAN_MAIN_OVERLAY_SLOTS_H

#include "types.h"

#define OVERLAY_SLOTS_COUNT 12
/* The overlay number of an empty slot. */
#define OVERLAY_SLOTS_EMPTY 0xff

typedef struct OverlaySlot {
    u8 overlay; /* OVERLAY_SLOTS_EMPTY when empty */
    u8 holds;   /* the requests that hold it */
    u8 unk_02;  /* always 0 */
    u32 start;  /* its first address */
    u32 size;   /* its code and data, then its bss */
} OverlaySlot;

/* What FS_LoadOverlayInfo fills in (NitroSDK's FSOverlayInfo, with room to spare). */
typedef struct OverlaySlotsInfo {
    u32 id;
    u32 ram_address;
    u32 ram_size;
    u32 bss_size;
    u8 rest[0x1c];
} OverlaySlotsInfo;

void OverlaySlots_Clear(void);
void OverlaySlots_Release(u8 overlay);
void OverlaySlots_Load(u8 overlay);
void OverlaySlots_Empty(OverlaySlot *slot);
void OverlaySlots_Fill(OverlaySlot *slot, int overlay);
void OverlaySlots_Unload(int overlay);
void OverlaySlots_LoadOverlay(int overlay);
void OverlaySlots_ReadInfo(OverlaySlotsInfo *info, int overlay);

#endif
