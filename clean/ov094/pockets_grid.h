/* Overlay 094's grid object (vtable data_ov094_0229bf90, 0xa60 bytes), the first of the
 * objects the pockets scenes keep (at 0x358 of ov096's PocketsScreen, 0xcc of ov099's
 * PocketsView, 0x2fc of ov105's LetterStorage). It draws the scenes' places as OBJs on the sub
 * screen (one OBJ of data_ov094_0229bfb0 per place, PocketsGrid_PlaceObj) and the item the
 * cursor holds (the OBJ data_ov094_0229bf70), whose pick-up is animated
 * (PocketsGrid_StepPickUp): frames of an animation (the object at 0x184) copied into the held
 * OBJ's characters, and a scale from 1/10 to full size.
 *
 * Three sets of 64 bits hold, per place: whether it holds something (`filled`, drawn), whether
 * it has a mark (`marked`, OBJ data_ov094_0229bfa8) and whether it is shown dimmed (`dimmed`,
 * palette 14). A filled place is drawn with OBJ data_ov094_0229bf98 round it; the place the
 * cursor lifts (`lifted`) is raised by an offset (data_ov094_0229bc58 by `lift`, which counts
 * down: 5, 3, then 2 pixels), with data_ov094_0229bfa0 (the tile of data_ov094_0229bf98, 2
 * pixels lower, palette 1) under it. */
#ifndef CLEAN_OV094_POCKETS_GRID_H
#define CLEAN_OV094_POCKETS_GRID_H

#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "ov002/popup.h"
#include "types.h"

#define POCKETS_GRID_TASKS 3
#define POCKETS_GRID_NO_PLACE 0x23
#define POCKETS_GRID_FULL_SIZE 10 /* `held_size`, in tenths */

/* A set of 64 bits (two words, bit n in word n / 32). */
typedef struct PocketsBits {
    u32 words[2];
} PocketsBits;

typedef struct PocketsGrid {
    u32 vtable;                              /* 0x000: data_ov094_0229bf90 */
    u8 held_chars[3][0x80];                  /* 0x004: characters copied for the held OBJ, one per task */
    u8 animation[0x808];                     /* 0x184: the pick-up's frames (func_ov094_0229b0d4, func_ov094_0229b048) */
    LayerTaskPair tasks[POCKETS_GRID_TASKS]; /* 0x98c */
    u32 unk_a34;                             /* 0xa34 */
    PocketsBits filled;                      /* 0xa38 */
    PocketsBits marked;                      /* 0xa40 */
    PocketsBits dimmed;                      /* 0xa48 */
    s32 priority;                            /* 0xa50: the OBJs' priority */
    u16 held_item;                           /* 0xa54 */
    u8 lifted;                               /* 0xa56: the place lifted, POCKETS_GRID_NO_PLACE for none */
    u8 lift;                                 /* 0xa57: an index into the lift's offsets, counting down */
    u8 tasks_used;                           /* 0xa58: this frame's tasks */
    u8 held_size;                            /* 0xa59: the held OBJ's size in tenths, 0 hidden */
    u8 pickup_step;                          /* 0xa5a */
    u8 pickup_variant;                       /* 0xa5b: 0 for an item of state 1, else 1 */
    u8 held_lowered;                         /* 0xa5c: data_ov094_0229bfa0 is drawn under the held item */
    u8 pad_a5d[3];
} PocketsGrid;

int PocketsBits_Test(PocketsBits *bits, int bit);
void PocketsBits_Clear(PocketsBits *bits, int bit);
void PocketsBits_Set(PocketsBits *bits, int bit);
void PocketsBits_ClearAll(PocketsBits *bits);
u8 PocketsGrid_PickUpSize(PocketsGrid *grid);
int PocketsGrid_StepPickUp(PocketsGrid *grid);
void PocketsGrid_EndPickUp(PocketsGrid *grid);
void PocketsGrid_StartPickUp(PocketsGrid *grid, u16 item, int state);
int PocketsGrid_NextTask(PocketsGrid *grid);
void PocketsGrid_EndTasks(PocketsGrid *grid);
int PocketsGrid_SizeScale(unsigned int size);
OamEntry *PocketsGrid_PlaceObj(int unused, int place);
void PocketsGrid_DrawPlace(PocketsGrid *grid, const OamEntry *obj, int place, int x, int y);
int PocketsGrid_DrawLowered(PocketsGrid *grid, int x, int y);
void PocketsGrid_DrawSurround(PocketsGrid *grid, int x, int y, int palette);
int PocketsGrid_DrawMark(PocketsGrid *grid, int x, int y);

int PocketsGrid_IsEmpty(PocketsGrid *grid, int place);
void PocketsGrid_DrawHeld(PocketsGrid *grid, int x, int y);
void PocketsGrid_DrawSideMarks(PocketsGrid *grid, int x, int y);
void PocketsGrid_DrawBox(PocketsGrid *grid, int x, int y);
void PocketsGrid_DrawPocketsRightOf(PocketsGrid *grid, int x, int y, int left);
void PocketsGrid_DrawPockets(PocketsGrid *grid, int x, int y);
void PocketsGrid_DimPlace(PocketsGrid *grid, int place);
void PocketsGrid_DimPlaces(PocketsGrid *grid, u8 first, u8 last);
int PocketsGrid_IsDimmed(PocketsGrid *grid, int place);
void PocketsGrid_SetObjChars(PocketsGrid *grid, OamEntry *obj, const u8 *chars, int palette);
void PocketsGrid_SetObjIcon(PocketsGrid *grid, OamEntry *obj, u16 item, int state);
void PocketsGrid_SetHeldIcon(PocketsGrid *grid, int item, int state);
void PocketsGrid_RefreshPlace(PocketsGrid *grid, unsigned int place);
void PocketsGrid_SetItem(PocketsGrid *grid, int place, int item, int state);
void PocketsGrid_EmptyPlace(PocketsGrid *grid, int place);
u8 PocketsGrid_ItemState(PocketsGrid *grid, int place);
u16 PocketsGrid_Item(PocketsGrid *grid, int place);
void PocketsGrid_MarkPlace(PocketsGrid *grid, int place);
void PocketsGrid_ClearMarks(PocketsGrid *grid);
void PocketsGrid_Lift(PocketsGrid *grid, int place);
void PocketsGrid_Unlift(PocketsGrid *grid);
int PocketsGrid_LiftOffset(PocketsGrid *grid);
int PocketsGrid_IsLifted(PocketsGrid *grid, u8 place);
int PocketsGrid_PlaceY(PocketsGrid *grid, int place);
int PocketsGrid_PlaceX(PocketsGrid *grid, int place);
void PocketsGrid_ShowItemText(PocketsGrid *grid, Popup *popup, int place);
void PocketsGrid_SetPopupText(PocketsGrid *grid, Popup *popup, u16 *item, int state);
int PocketsGrid_IconOf(PocketsGrid *grid, u16 *item, int state);
void PocketsGrid_SetBox(PocketsGrid *grid, u16 *box);
void PocketsGrid_LoadPockets(PocketsGrid *grid);
void PocketsGrid_LoadPlace(PocketsGrid *grid, int place, u16 *item, int state);
int PocketsGrid_TouchOnPlace(PocketsGrid *grid, int x, int y, int place);
u8 PocketsGrid_PlaceInside(PocketsGrid *grid, int min_x, int min_y, int max_x, int max_y, u8 first, u8 last);
int PocketsGrid_TouchOnBells(PocketsGrid *grid, int x, int y);
int PocketsGrid_BoxPlaceAtTouch(PocketsGrid *grid, int x, int y);
int PocketsGrid_PocketPlaceAtTouch(PocketsGrid *grid, int x, int y);
void PocketsGrid_Teardown(PocketsGrid *grid);
void PocketsGrid_BeginFrame(PocketsGrid *grid);
void PocketsGrid_Init(PocketsGrid *grid, int priority);
PocketsGrid *PocketsGrid_DestructDelete(PocketsGrid *grid);
PocketsGrid *PocketsGrid_Destruct(PocketsGrid *grid);
PocketsGrid *PocketsGrid_Construct(PocketsGrid *grid);

#endif
