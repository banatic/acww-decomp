/* The overlays loaded on request (overlay_slots.h). */
#include "overlay_slots.h"

#include "clean.h"
#include "main/game_halt.h"
#include "rom_file.h"

static_assert(sizeof(OverlaySlot) == 12, "OverlaySlot size");
static_assert(offsetof(OverlaySlot, start) == 4, "OverlaySlot start");
static_assert(sizeof(OverlaySlotsInfo) == 0x2c, "OverlaySlotsInfo size");

extern OverlaySlot data_021c80f4[OVERLAY_SLOTS_COUNT];

/* NitroSDK's FSFileID. */
typedef struct OverlaySlotsFileId {
    void *archive;
    u32 file_id;
} OverlaySlotsFileId;

extern int FS_LoadOverlayInfo(OverlaySlotsInfo *info, int target, int overlay);
/* the ROM's FSFileID result is 8 bytes: it comes back through the address in r0 */
extern void FS_GetOverlayFileID(OverlaySlotsFileId *result, const void *info);

/* func_0204f8bc: every slot empty. */
void OverlaySlots_Clear(void)
{
    for (u32 i = 0; i < OVERLAY_SLOTS_COUNT; i++) {
        OverlaySlot *slot = &data_021c80f4[i];
        slot->overlay = OVERLAY_SLOTS_EMPTY;
        slot->holds = 0;
        slot->unk_02 = 0;
        slot->start = 0;
        slot->size = 0;
    }
}
CLEAN_AS(func_0204f8bc, OverlaySlots_Clear)

/* func_0204f8ec: lets a request for `overlay` go; the overlay is unloaded when no request
 * holds it any more. Stops the game when the overlay is not loaded.
 * QUIRK: every slot of the overlay counts one request less (there is only ever one); the last
 * of them is the one checked. */
void OverlaySlots_Release(u8 overlay)
{
    OverlaySlot *found = NULL;

    for (u32 i = 0; i < OVERLAY_SLOTS_COUNT; i++) {
        OverlaySlot *slot = &data_021c80f4[i];
        if (slot->overlay == overlay) {
            found = slot;
            if (slot->holds != 0) {
                slot->holds--;
            }
        }
    }
    if (found == NULL) {
        GameHalt_Terminate();
        return; /* not reached: OS_Terminate does not return */
    }
    if (found->holds == 0) {
        OverlaySlots_Empty(found);
    }
}
CLEAN_AS(func_0204f8ec, OverlaySlots_Release)

/* func_0204f934: a request for `overlay`. When it is loaded, it counts one request more;
 * otherwise each loaded overlay whose memory overlaps it is unloaded (the game stops when a
 * request still holds one), and it is loaded into the first empty slot, or the first slot
 * freed so.
 * QUIRK: the overlay's file is looked up (FS_GetOverlayFileID) and the answer not used.
 * QUIRK: with no empty slot and no overlap the overlay is not loaded and nothing says so. */
void OverlaySlots_Load(u8 overlay)
{
    OverlaySlot *free_slot = NULL;
    OverlaySlotsInfo info;

    for (u32 i = 0; i < OVERLAY_SLOTS_COUNT; i++) {
        OverlaySlot *slot = &data_021c80f4[i];
        if (slot->overlay == overlay) {
            slot->holds++;
            return;
        }
        if (slot->overlay == OVERLAY_SLOTS_EMPTY && free_slot == NULL) {
            free_slot = slot;
        }
    }
    OverlaySlots_ReadInfo(&info, overlay);
    OverlaySlotsFileId file;
    FS_GetOverlayFileID(&file, &info);

    u32 start = info.ram_address;
    u32 end = info.ram_size + info.bss_size + start;
    for (u32 i = 0; i < OVERLAY_SLOTS_COUNT; i++) {
        OverlaySlot *slot = &data_021c80f4[i];
        if (slot->overlay == overlay || slot->overlay == OVERLAY_SLOTS_EMPTY) {
            continue;
        }
        if (slot->start + slot->size <= start || end <= slot->start) {
            continue;
        }
        if (slot->holds == 0) {
            OverlaySlots_Empty(slot);
            if (free_slot == NULL) {
                free_slot = slot;
            }
        } else {
            GameHalt_Terminate();
        }
    }
    if (free_slot != NULL) {
        OverlaySlots_Fill(free_slot, overlay);
    }
}
CLEAN_AS(func_0204f934, OverlaySlots_Load)

/* func_0204f9ec: unloads the slot's overlay and empties the slot.
 * QUIRK: the overlay's information is read after it is unloaded, and not used. */
void OverlaySlots_Empty(OverlaySlot *slot)
{
    OverlaySlotsInfo info;
    u8 overlay = slot->overlay;

    OverlaySlots_Unload(overlay);
    OverlaySlots_ReadInfo(&info, overlay);
    slot->overlay = OVERLAY_SLOTS_EMPTY;
    slot->holds = 0;
    slot->unk_02 = 0;
    slot->start = 0;
    slot->size = 0;
}
CLEAN_AS(func_0204f9ec, OverlaySlots_Empty)

/* func_0204fa18: loads `overlay` and gives it the slot, held by one request. */
void OverlaySlots_Fill(OverlaySlot *slot, int overlay)
{
    OverlaySlotsInfo info;

    OverlaySlots_ReadInfo(&info, overlay);
    OverlaySlots_LoadOverlay(overlay);
    slot->overlay = (u8) overlay;
    slot->holds = 1;
    slot->unk_02 = 0;
    slot->start = info.ram_address;
    slot->size = info.ram_size + info.bss_size;
}
CLEAN_AS(func_0204fa18, OverlaySlots_Fill)

/* func_0204fa4c */
void OverlaySlots_Unload(int overlay)
{
    RomFile_UnloadOverlay(overlay);
}
CLEAN_AS(func_0204fa4c, OverlaySlots_Unload)

/* func_0204fa54 */
void OverlaySlots_LoadOverlay(int overlay)
{
    RomFile_LoadOverlay(overlay);
}
CLEAN_AS(func_0204fa54, OverlaySlots_LoadOverlay)

/* func_0204fa5c: the information of an overlay of the main processor. */
void OverlaySlots_ReadInfo(OverlaySlotsInfo *info, int overlay)
{
    FS_LoadOverlayInfo(info, 0, overlay);
}
CLEAN_AS(func_0204fa5c, OverlaySlots_ReadInfo)
