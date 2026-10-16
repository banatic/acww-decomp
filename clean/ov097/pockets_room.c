/* Overlay 097's part of the pockets scene (pockets_room.h). */
#include "pockets_room.h"

#include "clean.h"
#include "main/session.h"
#include "main/sound.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"

/* The item codes of the wallpapers and the carpets (ov004/room_object_022511e0.c,
 * ov004/room_object_02250e5c.c). */
#define ITEM_WALLPAPER_FIRST 0x1100
#define ITEM_WALLPAPER_LAST 0x1143
#define ITEM_CARPET_FIRST 0x1144
#define ITEM_CARPET_LAST 0x1187

/* The actions the choice rows carry (PocketsScreen_RunAction runs 18 and 19 from here) and
 * their rows' texts. */
#define ACTION_WALLPAPER 0x12
#define ACTION_CARPET 0x13
#define ROW_WALLPAPER 0x0b
#define ROW_CARPET 0x0c

/* The error messages (PocketsScreen_ShowError) and the sound of a refusal. */
#define ERROR_3 3
#define ERROR_5 5
#define ERROR_18 0x18
#define ERROR_17 0x17
#define SOUND_ERROR 0x73

extern NetSession *data_020ccf94;

/* Main's: a count that must be at most 1 for a wallpaper or a carpet to be used (also tested by
 * field actor state 0x18, main/field_actor_states.c). */
extern unsigned int func_020b2300(void);
/* Main's: the item code an item becomes (in `out`), and whether func_0204bcdc accepts it. */
extern void func_02061b1c(unsigned short *out, unsigned short *in, int flag);
extern int func_0204bcdc(unsigned short *item);
/* Main's use request of an item for a session slot (pockets_screen.c: PocketsScreen_CheckUseItem),
 * -1 when none could be made. */
extern int func_020435fc(int slot, unsigned short item);
/* Main's: the room's wallpaper (func_02034b80) or carpet (func_02034b04) set to `*item`; the
 * one it replaces comes back. Only when data_020e54a8 is 1; else they answer a word of main's
 * (data_021c5174). */
extern u16 *func_02034b80(u16 *item, int a, int b, int c);
extern u16 *func_02034b04(u16 *item, int a, int b, int c);
/* Overlay 4's: an answer for the converted item (0-2 are refusals, others carry a value in
 * `out` for func_ov004_0223c660). */
extern int func_ov004_0223b540(int *out, unsigned short *item, int flag);
extern int func_ov004_0223c660(int value);

/* func_ov097_022a27c0: a wallpaper or a carpet can be used when func_020b2300 is at most 1,
 * and, in a linked session, only on the console in slot 0. */
int PocketsRoom_CanUse(PocketsScreen *self)
{
    (void) self;
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session)) {
        return session->local_slot == 0 && func_020b2300() <= 1;
    }
    return func_020b2300() <= 1;
}
CLEAN_AS(func_ov097_022a27c0, PocketsRoom_CanUse)

/* The action ends with an error message and the refusal's sound. */
static void refuse(PocketsScreen *self, int message, unsigned int flag)
{
    PocketsScreen_EndAction(self);
    PocketsScreen_ShowError(self, message, 0xff, flag);
    SoundSys_PlaySe(SOUND_ERROR);
}

/* func_ov097_022a27fc: whether `item` can be used (PocketsScreen_CheckUseItem asks this one
 * when data_020e54a8 is set). An item that converts (func_02061b1c) to one func_0204bcdc
 * accepts is asked of overlay 4: answers 0 and 2 refuse with error 3, 1 with error 5 (flag 1);
 * any other hands its value to func_ov004_0223c660 and answers 1. Any other item is asked for
 * by a use request (kept at `unk_c4`): 2 when one was made, else a refusal with error 3.
 * Refusals answer 0. */
int PocketsRoom_CheckUseItem(PocketsScreen *self, u16 item)
{
    u16 original = item;
    u16 converted;
    func_02061b1c(&converted, &original, 0);
    if (func_0204bcdc(&converted) != 0) {
        int value;
        switch (func_ov004_0223b540(&value, &converted, 1)) {
            case 0:
            case 2:
                refuse(self, ERROR_3, 0);
                return 0;
            case 1:
                refuse(self, ERROR_5, 1);
                return 0;
            default:
                func_ov004_0223c660(value);
                return 1;
        }
    }
    self->unk_c4 = func_020435fc(data_020ccf94->local_slot, item);
    if (self->unk_c4 == -1) {
        refuse(self, ERROR_3, 0);
        return 0;
    }
    return 2;
}
CLEAN_AS(func_ov097_022a27fc, PocketsRoom_CheckUseItem)

/* func_ov097_022a28e4: when PocketsRoom_CanUse allows it, a carpet in the grid gets the row
 * of action 19 and a wallpaper the row of action 18. */
void PocketsRoom_AddItemRows(PocketsScreen *self, u16 item)
{
    if (PocketsRoom_CanUse(self) == 0) {
        return;
    }
    if (item >= ITEM_CARPET_FIRST && item <= ITEM_CARPET_LAST) {
        ChoiceEntries_Add(&self->entries, ROW_CARPET, ACTION_CARPET);
    } else if (item >= ITEM_WALLPAPER_FIRST && item <= ITEM_WALLPAPER_LAST) {
        ChoiceEntries_Add(&self->entries, ROW_WALLPAPER, ACTION_WALLPAPER);
    }
}
CLEAN_AS(func_ov097_022a28e4, PocketsRoom_AddItemRows)

/* The picked place's item put up in the room as its carpet or its wallpaper; the place gets
 * the one it replaces when that is of the same kind, else it is emptied. */
static void swap_with_room(PocketsScreen *self, int carpet)
{
    int place = self->slot;
    u16 item = PocketsScreen_PlaceItem(self, place);
    PocketsScreen_RequestSwitchOff(self);
    u16 old = carpet ? *func_02034b04(&item, 0, 1, 1) : *func_02034b80(&item, 0, 1, 1);
    unsigned int first = carpet ? ITEM_CARPET_FIRST : ITEM_WALLPAPER_FIRST;
    unsigned int last = carpet ? ITEM_CARPET_LAST : ITEM_WALLPAPER_LAST;
    if (old >= first && old <= last) {
        PocketsScreen_SetPlaceItem(self, place, old, 0);
    } else {
        PocketsScreen_EmptyPlace(self, place);
    }
    PocketsScreen_EndAction(self);
}

/* func_ov097_022a2954 (action 18): the picked wallpaper put up in the room, the old one put in
 * its place; error 0x18 (flag 1) when PocketsRoom_CanUse no longer allows it. */
void PocketsRoom_ActionWallpaper(PocketsScreen *self)
{
    if (PocketsRoom_CanUse(self) == 0) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, ERROR_18, 0xff, 1);
        return;
    }
    swap_with_room(self, 0);
}
CLEAN_AS(func_ov097_022a2954, PocketsRoom_ActionWallpaper)

/* func_ov097_022a29e4 (action 19): the same for a carpet; error 0x17. */
void PocketsRoom_ActionCarpet(PocketsScreen *self)
{
    if (PocketsRoom_CanUse(self) == 0) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, ERROR_17, 0xff, 1);
        return;
    }
    swap_with_room(self, 1);
}
CLEAN_AS(func_ov097_022a29e4, PocketsRoom_ActionCarpet)
