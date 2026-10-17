/* An item shown in the room as a room object (room_preview.h). */
#include "room_preview.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/item_code.h"
#include "main/item_form.h"
#include "main/item_texture.h"
#include "main/wallpaper_file.h"
#include "room_objects.h"
#include "room_placement.h"

static_assert(offsetof(RoomPreview, items) == 0x08, "preview items");
static_assert(offsetof(RoomPreview, current) == 0x0c, "preview current");
static_assert(offsetof(RoomPreview, number) == 0x10, "preview number");
static_assert(offsetof(RoomPreview, wallpaper_files) == 0x14, "preview wallpaper files");
static_assert(offsetof(RoomPreview, carpet_files) == 0x1c, "preview carpet files");
static_assert(sizeof(RoomPreview) == 0x24, "preview");

#define ROOM_PREVIEW_WALLPAPER_FIRST 0x1100
#define ROOM_PREVIEW_WALLPAPER_LAST 0x1143
#define ROOM_PREVIEW_CARPET_FIRST 0x1144
#define ROOM_PREVIEW_CARPET_LAST 0x1187
/* The room objects the items are shown as. */
#define ROOM_PREVIEW_WALL_OBJECT 0x4a64
#define ROOM_PREVIEW_FLOOR_OBJECT 0x4a60
#define ROOM_PREVIEW_PILE_OBJECT 0x4a68 /* plus 4 for each item of the piles */
#define ROOM_PREVIEW_WALLPAPER_FILE_SIZE 0x10c4
#define ROOM_PREVIEW_CARPET_FILE_SIZE 0x20c4

extern RoomPreview data_ov004_022596b0;
extern Heap *data_021fbe94; /* the current heap */

/* The item codes' constructor and destructor handed to __cxa_vec_ctor and __cxa_vec_cleanup:
 * the game's (RoomInterior_ConstructCode and TrivialObject_DestructItemCode in Clean). */
extern void func_02034ce0(void *code);
extern void func_020051b0(void *code);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_ov004_0223d03c */
RoomPreview *RoomPreview_Get(void)
{
    return &data_ov004_022596b0;
}
CLEAN_AS(func_ov004_0223d03c, RoomPreview_Get)

/* func_ov004_0223d044: the carpet texture file of the slot shown. */
u8 *RoomPreview_CarpetFile(RoomPreview *preview)
{
    return preview->carpet_files[preview->current & 1];
}
CLEAN_AS(func_ov004_0223d044, RoomPreview_CarpetFile)

/* func_ov004_0223d054: the wallpaper file of the slot shown. */
u8 *RoomPreview_WallpaperFile(RoomPreview *preview)
{
    return preview->wallpaper_files[preview->current & 1];
}
CLEAN_AS(func_ov004_0223d054, RoomPreview_WallpaperFile)

/* func_ov004_0223d064: both objects are deleted and the slots emptied. */
void RoomPreview_Clear(RoomPreview *preview)
{
    for (unsigned int i = 0; i < ROOM_PREVIEW_SLOTS; i++) {
        if (preview->objects[i] != NULL) {
            Process_RequestDelete(preview->objects[i]);
        }
    }
    RoomPreview_Reset(preview);
}
CLEAN_AS(func_ov004_0223d064, RoomPreview_Clear)

/* Whether two items are the same: by their variants' item for an item with variants. */
static int same_item(ItemCode *item, ItemCode *other)
{
    if (ItemCode_HasVariant(item) != 0) {
        int variant = ItemCode_VariantItem(item);
        return variant == ItemCode_VariantItem(other);
    }
    return *item == *other;
}

static int in_range(unsigned int code, unsigned int first, unsigned int last)
{
    return code >= first && code <= last;
}

/* func_ov004_0223d08c: shows `item` unless the slot shown has it already: the room object it
 * is shown as (see room_preview.h; a wallpaper's or carpet's number is noted, -1 when the item
 * itself is out of the range its placed form is in) goes in the other slot, near the player,
 * once that slot is free; the object shown is deleted in any case. 1 when the new one was
 * made, which then is the slot shown.
 * QUIRK: the slot shown loses its object even when the new one cannot be placed. */
int RoomPreview_Show(RoomPreview *preview, ItemCode *item)
{
    ItemCode shown;
    ItemForm_ToPlaced(&shown, item, 1);
    if (in_range(shown, ROOM_PREVIEW_WALLPAPER_FIRST, ROOM_PREVIEW_WALLPAPER_LAST)) {
        preview->number = in_range(*item, ROOM_PREVIEW_WALLPAPER_FIRST, ROOM_PREVIEW_WALLPAPER_LAST)
                              ? (int) *item - ROOM_PREVIEW_WALLPAPER_FIRST
                              : -1;
        shown = ROOM_PREVIEW_WALL_OBJECT;
    } else if (in_range(shown, ROOM_PREVIEW_CARPET_FIRST, ROOM_PREVIEW_CARPET_LAST)) {
        preview->number = in_range(*item, ROOM_PREVIEW_CARPET_FIRST, ROOM_PREVIEW_CARPET_LAST)
                              ? (int) *item - ROOM_PREVIEW_CARPET_FIRST
                              : -1;
        shown = ROOM_PREVIEW_FLOOR_OBJECT;
    } else if (in_range(shown, ITEM_CODE_PILE_FIRST, ITEM_CODE_PILE_LAST)) {
        unsigned int pile = (unsigned int) ItemCode_PileItem(&shown);
        shown = (ItemCode) (pile < ITEM_CODE_PILE_ITEMS ? ROOM_PREVIEW_PILE_OBJECT + pile * 4 : ROOM_PREVIEW_PILE_OBJECT);
    }
    if (same_item(item, &preview->items[preview->current & 1])) {
        return 0;
    }
    unsigned int old = preview->current & 1;
    if (preview->objects[old] != NULL) {
        Process_RequestDelete(preview->objects[old]);
        preview->objects[old] = NULL;
    }
    unsigned int next = (preview->current + 1u) & 1;
    if (preview->objects[next] == NULL) {
        u32 placement;
        if (RoomPlacement_FindNearPlayer(&placement, &shown, ROOM_PLACEMENT_MODE_UNPLACED) == ROOM_PLACEMENT_PLACED) {
            preview->objects[next] = (Process *) (intptr_t) RoomObjects_Spawn(placement);
            preview->items[next] = *item;
            preview->current = (u8) next;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223d08c, RoomPreview_Show)

/* func_ov004_0223d200: at the room's end, the texture files are freed (to the heap current on
 * entry). */
void RoomPreview_FreeFiles(RoomPreview *preview)
{
    Heap *heap = data_021fbe94;
    for (unsigned int i = 0; i < ROOM_PREVIEW_SLOTS; i++) {
        if (preview->wallpaper_files[i] != NULL) {
            Heap_Free(heap, preview->wallpaper_files[i]);
            preview->wallpaper_files[i] = NULL;
        }
        if (preview->carpet_files[i] != NULL) {
            Heap_Free(heap, preview->carpet_files[i]);
            preview->carpet_files[i] = NULL;
        }
    }
}
CLEAN_AS(func_ov004_0223d200, RoomPreview_FreeFiles)

/* func_ov004_0223d248: at the room's start, the texture files missing are allocated from the
 * heap current on entry and constructed (one that could not be allocated stays NULL). */
void RoomPreview_AllocFiles(RoomPreview *preview)
{
    Heap *heap = data_021fbe94;
    for (unsigned int i = 0; i < ROOM_PREVIEW_SLOTS; i++) {
        if (preview->wallpaper_files[i] == NULL) {
            u8 *file = Heap_Alloc(heap, ROOM_PREVIEW_WALLPAPER_FILE_SIZE);
            preview->wallpaper_files[i] = file;
            if (file != NULL) {
                file = WallpaperFile_Construct(file);
            }
            preview->wallpaper_files[i] = file;
        }
        if (preview->carpet_files[i] == NULL) {
            u8 *file = Heap_Alloc(heap, ROOM_PREVIEW_CARPET_FILE_SIZE);
            preview->carpet_files[i] = file;
            if (file != NULL) {
                file = CarpetTexture_Construct(file);
            }
            preview->carpet_files[i] = file;
        }
    }
}
CLEAN_AS(func_ov004_0223d248, RoomPreview_AllocFiles)

/* func_ov004_0223d2ac */
unsigned long RoomPreview_Number(RoomPreview *preview)
{
    return (unsigned long) (u32) preview->number;
}
CLEAN_AS(func_ov004_0223d2ac, RoomPreview_Number)

/* func_ov004_0223d2b0: no objects, no items (0xfff1), slot 0 shown. */
void RoomPreview_Reset(RoomPreview *preview)
{
    for (unsigned int i = 0; i < ROOM_PREVIEW_SLOTS; i++) {
        preview->objects[i] = NULL;
        preview->items[i] = ITEM_CODE_NONE;
    }
    preview->current = 0;
}
CLEAN_AS(func_ov004_0223d2b0, RoomPreview_Reset)

/* func_ov004_0223d2d4: the destructor (run at the overlay's end). */
RoomPreview *RoomPreview_Destruct(RoomPreview *preview)
{
    RoomPreview_Reset(preview);
    __cxa_vec_cleanup(preview->items, ROOM_PREVIEW_SLOTS, sizeof(ItemCode), func_020051b0);
    return preview;
}
CLEAN_AS(func_ov004_0223d2d4, RoomPreview_Destruct)

/* func_ov004_0223d2f8: the constructor (run at the overlay's start): reset, with no texture
 * files. */
RoomPreview *RoomPreview_Construct(RoomPreview *preview)
{
    __cxa_vec_ctor(preview->items, ROOM_PREVIEW_SLOTS, sizeof(ItemCode), func_02034ce0, func_020051b0);
    RoomPreview_Reset(preview);
    for (unsigned int i = 0; i < ROOM_PREVIEW_SLOTS; i++) {
        preview->wallpaper_files[i] = NULL;
        preview->carpet_files[i] = NULL;
    }
    return preview;
}
CLEAN_AS(func_ov004_0223d2f8, RoomPreview_Construct)
