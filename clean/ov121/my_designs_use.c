/* What the "my designs" scene (my_designs.h) does with a design put down on a button: the order
 * of the designs, the choice of how to use it, and the uses: the clothes, head item or held item
 * worn, the room's carpet or wallpaper, the menu backdrop, furniture of the room and a pattern
 * on the ground. */
#include "my_designs.h"

#include <stdint.h>

#include "clean.h"
#include "main/camera_control.h"
#include "main/current_pockets.h"
#include "main/design_sets.h"
#include "main/menu_backdrop.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/room_interior.h"
#include "main/scene_kinds.h"
#include "main/session.h"
#include "main/sound.h"
#include "main/tile_requests.h"
#include "main/town_objects.h"
#include "ov004/room_objects.h"
#include "ov004/room_placement.h"
#include "ov004/room_shell.h"

extern NetSession *data_020ccf94;

/* The choices' rows (ChoiceEntries, 11 bytes each): 0 carpet, 1 wallpaper, 3 clothes or
 * furniture, 4 head item or furniture (2 and 5 are not used by this overlay). */
extern const u8 data_ov121_0229c258[][sizeof(ChoiceEntries)];
/* The ground pattern items' first by player number: 0xa7 + 8 * player. */
extern const u16 data_ov121_0229c2b8[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* An item code of no item. */
#define MY_DESIGNS_NO_ITEM 0xfff1

/* The design items: a design worn as clothes, head item or held item is the item of its place
 * (the first of each kind for a place past 7). The game's other clothes, the shirts, are
 * 0x11a8-0x12a7. */
#define MY_DESIGNS_SHIRT_FIRST 0x11a8
#define MY_DESIGNS_SHIRT_LAST 0x12a7
#define MY_DESIGNS_CLOTHES_ITEM 0x12a8
#define MY_DESIGNS_HEAD_ITEM 0x1429
#define MY_DESIGNS_HELD_ITEM 0x13a0
/* The carpets and wallpapers of designs; the others go back to the pockets when replaced. */
#define MY_DESIGNS_ROOM_DESIGN_FIRST 0x1188
#define MY_DESIGNS_ROOM_DESIGN_LAST 0x11a7

/* The error messages (MyDesigns_ShowError). */
#define MY_DESIGNS_ERROR_NO_SPACE 3     /* no space for it (ROOM_PLACEMENT_NO_SPACE, or the ground) */
#define MY_DESIGNS_ERROR_POCKETS_FULL 4 /* what it replaces has no free slot to go to */
#define MY_DESIGNS_ERROR_NOT_PLACED 5   /* the furniture could not be made or the room is full */
#define MY_DESIGNS_ERROR_VISITORS 9     /* more than one player is here */
#define MY_DESIGNS_ERROR_CARPET 0x17    /* the carpet may not be changed (MyDesigns_MayChangeRoom) */
#define MY_DESIGNS_ERROR_WALLPAPER 0x18 /* the wallpaper may not be changed */

/* Sound effects (SoundSys_PlaySe). */
#define MY_DESIGNS_SE_REFUSED 0x73
#define MY_DESIGNS_SE_BACKDROP 0x6b
#define MY_DESIGNS_SE_SWAP 0x0e
#define MY_DESIGNS_SE_ROW 0x50

static MenuScene *use_scene(MyDesigns *self)
{
    return &self->base;
}

static int in_range(unsigned int value, unsigned int first, unsigned int last)
{
    return value >= first && value <= last;
}

/* The design item of `kind` for the design at place `design`. */
static u16 design_item(unsigned int first, unsigned int design)
{
    return (u16) (design < MY_DESIGNS_COUNT ? design + first : first);
}

static void refuse(MyDesigns *self, char message)
{
    MyDesigns_ShowError(self, message, 0);
    SoundSys_PlaySe(MY_DESIGNS_SE_REFUSED);
}

/* func_ov121_02299a70: whether the room's carpet and wallpaper may be changed: not as a linked
 * guest (only the session's slot 0 may) and with at most one player here. */
int MyDesigns_MayChangeRoom(void)
{
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) != 0) {
        return session->local_slot == 0 && (unsigned int) TownObjects_VisitorsHere() <= 1;
    }
    return (unsigned int) TownObjects_VisitorsHere() <= 1;
}
CLEAN_AS(func_ov121_02299a70, MyDesigns_MayChangeRoom)

/* func_ov121_02299aac: whether the player is done changing: the held item by state 0x3f, the
 * others by the early part of state 7. */
int MyDesigns_IsChangeDone(MyDesigns *self, int kind)
{
    (void) self;
    if (kind == MY_DESIGNS_WEAR_HELD) {
        return PlayerActorOps_InState3F() == 0;
    }
    return PlayerActorOps_EarlyInState7() == 0;
}
CLEAN_AS(func_ov121_02299aac, MyDesigns_IsChangeDone)

/* func_ov121_02299ad8: the player asked to change into `item` (its low 16 bits) of `kind`; 1
 * when the player took the request, 0 also for an unknown kind. */
int MyDesigns_RequestChange(MyDesigns *self, int kind, int item)
{
    (void) self;
    u16 code = (u16) item;
    switch (kind) {
        case MY_DESIGNS_WEAR_CLOTHES:
            return PlayerActorOps_RequestState7Kind0Next5(&code) != 0;
        case MY_DESIGNS_WEAR_HEAD:
            return PlayerActorOps_RequestState7Kind2Next5(&code) != 0;
        case MY_DESIGNS_WEAR_HELD:
            return PlayerActorOps_RequestState3F(&code) != 0;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov121_02299ad8, MyDesigns_RequestChange)

/* func_ov121_02299b20: `item` put on as the current player's clothes or head item, and what was
 * worn before given back for the pockets: clothes only when they were a shirt, a head item
 * unless it was a design's (0x1429-0x1430); MY_DESIGNS_NO_ITEM for nothing.
 * QUIRK: for the held item nothing is set; the one held is answered unless it was a design's
 * (0x13a0-0x13a7). For an unknown kind the answer is MyDesigns_WornItem's. */
unsigned short MyDesigns_SwapWornItem(MyDesigns *self, int kind, unsigned short item)
{
    u16 worn = MyDesigns_WornItem(self, kind);
    u8 *record = PlayerRecords_Current();
    u16 code = item;
    switch (kind) {
        case MY_DESIGNS_WEAR_CLOTHES:
            PlayerRecord_SetClothes(record, &code);
            if (!in_range(worn, MY_DESIGNS_SHIRT_FIRST, MY_DESIGNS_SHIRT_LAST)) {
                worn = MY_DESIGNS_NO_ITEM;
            }
            break;
        case MY_DESIGNS_WEAR_HEAD:
            PlayerRecord_SetHeadItem(record, &code);
            if (in_range(worn, MY_DESIGNS_HEAD_ITEM, MY_DESIGNS_HEAD_ITEM + MY_DESIGNS_COUNT - 1)) {
                worn = MY_DESIGNS_NO_ITEM;
            }
            break;
        case MY_DESIGNS_WEAR_HELD:
            if (in_range(worn, MY_DESIGNS_HELD_ITEM, MY_DESIGNS_HELD_ITEM + MY_DESIGNS_COUNT - 1)) {
                worn = MY_DESIGNS_NO_ITEM;
            }
            break;
        default:
            break;
    }
    return worn;
}
CLEAN_AS(func_ov121_02299b20, MyDesigns_SwapWornItem)

/* func_ov121_02299bd4: the current player's clothes, head item or held item;
 * MY_DESIGNS_NO_ITEM for another kind. */
unsigned short MyDesigns_WornItem(MyDesigns *self, int kind)
{
    (void) self;
    u8 *record = PlayerRecords_Current();
    switch (kind) {
        case MY_DESIGNS_WEAR_CLOTHES:
            return *PlayerRecord_Clothes(record);
        case MY_DESIGNS_WEAR_HEAD:
            return *PlayerRecord_HeadItem(record);
        case MY_DESIGNS_WEAR_HELD:
            return *PlayerRecord_HeldItem(record);
        default:
            return MY_DESIGNS_NO_ITEM;
    }
}
CLEAN_AS(func_ov121_02299bd4, MyDesigns_WornItem)

/* func_ov121_0229a50c: the camera's view put back when one was kept (CameraControl_SaveView);
 * what CameraControl_RestoreView answers, else 0. */
int MyDesigns_RestoreCamera(MyDesigns *self)
{
    (void) self;
    int saved = CameraControl_IsViewSaved();
    if (saved != 0) {
        return CameraControl_RestoreView();
    }
    return saved;
}
CLEAN_AS(func_ov121_0229a50c, MyDesigns_RestoreCamera)

/* func_ov121_0229a524: the camera's view kept, unless one is kept already. */
void MyDesigns_SaveCamera(MyDesigns *self)
{
    (void) self;
    if (CameraControl_IsViewSaved() == 0) {
        CameraControl_SaveView();
    }
}
CLEAN_AS(func_ov121_0229a524, MyDesigns_SaveCamera)

/* func_ov121_0229a5c8: the action of the row picked (MyDesignsAction); the cancel row and any
 * other value go back to the idle sub state. */
void MyDesigns_RunChoiceAction(MyDesigns *self)
{
    switch (self->action) {
        case MY_DESIGNS_ACTION_CARPET_0:
            MyDesigns_UseAsCarpet(self, 0);
            break;
        case MY_DESIGNS_ACTION_CARPET_1:
            MyDesigns_UseAsCarpet(self, 1);
            break;
        case MY_DESIGNS_ACTION_WALLPAPER_0:
            MyDesigns_UseAsWallpaper(self, 0);
            break;
        case MY_DESIGNS_ACTION_WALLPAPER_1:
            MyDesigns_UseAsWallpaper(self, 1);
            break;
        case MY_DESIGNS_ACTION_BACKDROP:
            MyDesigns_UseAsBackdrop(self);
            break;
        case MY_DESIGNS_ACTION_CLOTHES:
            MyDesigns_WearPicked(self, MY_DESIGNS_WEAR_CLOTHES);
            break;
        case MY_DESIGNS_ACTION_FURNITURE:
            MyDesigns_PlaceFurniture(self);
            break;
        case MY_DESIGNS_ACTION_HEAD:
            MyDesigns_WearPicked(self, MY_DESIGNS_WEAR_HEAD);
            break;
        default:
            MyDesigns_BackToIdle(self);
            break;
    }
}
CLEAN_AS(func_ov121_0229a5c8, MyDesigns_RunChoiceAction)

/* func_ov121_0229a63c (MY_DESIGNS_BUTTON_GROUND): the picked design put on the ground in front of
 * the player as the player's ground pattern item (`item`), asked of the session's slot; the
 * answer is waited for (MY_DESIGNS_SUB_DROP_WAIT), or MY_DESIGNS_ERROR_NO_SPACE when it may not
 * ask.
 * REQUIRES: the current player's number is 0-3 (the table has four). */
void MyDesigns_DropOnGround(MyDesigns *self)
{
    int player = PlayerRecord_Number(PlayerRecords_Current());
    self->item = (u16) (data_ov121_0229c2b8[player] + MyDesigns_DesignAt(self, self->picked));
    self->drop_request = TileRequests_AskDrop(data_020ccf94->local_slot, self->item);
    if (self->drop_request == -1) {
        refuse(self, MY_DESIGNS_ERROR_NO_SPACE);
    } else {
        MenuScene_SetSubState(use_scene(self), MY_DESIGNS_SUB_DROP_WAIT);
    }
}
CLEAN_AS(func_ov121_0229a63c, MyDesigns_DropOnGround)

/* func_ov121_0229a6b4: the picked design made a piece of furniture of the series of the target's
 * button (9: 0x3f24, 12: 0x4224, 13: 0x3d84, 14: 0x3ea4) and put down near the player; then the
 * camera's view back, the button blinks and the scene goes back to idle. Refused with more than
 * one player here, when the furniture cannot be made or the room is full, or when there is no
 * space for it; another target goes back to idle at once. */
void MyDesigns_PlaceFurniture(MyDesigns *self)
{
    u32 placement;
    int result;

    if ((unsigned int) TownObjects_VisitorsHere() > 1) {
        refuse(self, MY_DESIGNS_ERROR_VISITORS);
        return;
    }
    switch (self->target) {
        case MY_DESIGNS_BUTTON_CLOTHES:
            result = RoomPlacement_PlaceSeries3D84(&placement, (u8) MyDesigns_DesignAt(self, self->picked), 1);
            break;
        case MY_DESIGNS_BUTTON_HEAD:
            result = RoomPlacement_PlaceSeries4224(&placement, (u8) MyDesigns_DesignAt(self, self->picked), 1);
            break;
        case MY_DESIGNS_BUTTON_FURNITURE:
            result = RoomPlacement_PlaceSeries3F24(&placement, (u8) MyDesigns_DesignAt(self, self->picked), 1);
            break;
        case MY_DESIGNS_BUTTON_HELD:
            result = RoomPlacement_PlaceSeries3EA4(&placement, (u8) MyDesigns_DesignAt(self, self->picked), 1);
            break;
        default:
            MyDesigns_BackToIdle(self);
            return;
    }
    switch (result) {
        case ROOM_PLACEMENT_NOT_FURNITURE:
        case ROOM_PLACEMENT_ROOM_FULL:
            refuse(self, MY_DESIGNS_ERROR_NOT_PLACED);
            break;
        case ROOM_PLACEMENT_NO_SPACE:
            refuse(self, MY_DESIGNS_ERROR_NO_SPACE);
            break;
        default:
            MyDesigns_RestoreCamera(self);
            RoomObjects_Spawn(placement);
            MyDesigns_BackToIdle(self);
            MyDesigns_StartBlink(self, self->target);
            break;
    }
}
CLEAN_AS(func_ov121_0229a6b4, MyDesigns_PlaceFurniture)

/* The design item that `kind` is worn as, for the picked design. */
static u16 worn_design_item(MyDesigns *self, int kind)
{
    unsigned int design = (unsigned int) MyDesigns_DesignAt(self, self->picked);
    switch (kind) {
        case MY_DESIGNS_WEAR_CLOTHES:
            return design_item(MY_DESIGNS_CLOTHES_ITEM, design);
        case MY_DESIGNS_WEAR_HEAD:
            return design_item(MY_DESIGNS_HEAD_ITEM, design);
        default:
            return design_item(MY_DESIGNS_HELD_ITEM, design);
    }
}

/* func_ov121_0229a7c8: the picked design worn as `kind`: what is worn now goes to the pockets
 * first unless it is a design's item of that kind (MY_DESIGNS_ERROR_POCKETS_FULL when it has
 * no free slot); the camera's view kept, the new item set (MyDesigns_SwapWornItem, its answer
 * not used) and the player asked to change (MY_DESIGNS_SUB_CHANGE_REQUEST); the target's
 * button blinks. For an unknown kind the item kept in `item` is set again. */
void MyDesigns_WearPicked(MyDesigns *self, u8 kind)
{
    self->wear_kind = kind;
    u16 worn = MyDesigns_WornItem(self, self->wear_kind);
    switch (self->wear_kind) {
        case MY_DESIGNS_WEAR_CLOTHES:
            if (in_range(worn, MY_DESIGNS_CLOTHES_ITEM, MY_DESIGNS_CLOTHES_ITEM + MY_DESIGNS_COUNT - 1)) {
                worn = MY_DESIGNS_NO_ITEM;
            }
            break;
        case MY_DESIGNS_WEAR_HEAD:
            if (in_range(worn, MY_DESIGNS_HEAD_ITEM, MY_DESIGNS_HEAD_ITEM + MY_DESIGNS_COUNT - 1)) {
                worn = MY_DESIGNS_NO_ITEM;
            }
            break;
        case MY_DESIGNS_WEAR_HELD:
            if (in_range(worn, MY_DESIGNS_HELD_ITEM, MY_DESIGNS_HELD_ITEM + MY_DESIGNS_COUNT - 1)) {
                worn = MY_DESIGNS_NO_ITEM;
            }
            break;
        default:
            break;
    }
    if (worn != MY_DESIGNS_NO_ITEM) {
        if (CurrentPockets_FreeSlot() == -1) {
            MyDesigns_ShowError(self, MY_DESIGNS_ERROR_POCKETS_FULL, 1);
            return;
        }
        CurrentPockets_Give(&worn, 0);
    }
    MyDesigns_SaveCamera(self);
    if (self->wear_kind <= MY_DESIGNS_WEAR_HELD) {
        self->item = worn_design_item(self, self->wear_kind);
    }
    MyDesigns_SwapWornItem(self, self->wear_kind, self->item);
    MenuScene_SetSubState(use_scene(self), MY_DESIGNS_SUB_CHANGE_REQUEST);
    MyDesigns_StartBlink(self, self->target);
}
CLEAN_AS(func_ov121_0229a7c8, MyDesigns_WearPicked)

/* The room's carpet or wallpaper replaced by the picked design: refused when it may not be
 * changed, or when the one there is not a design's and the pockets have no free slot for it
 * (the free slot is looked for first in any case). Then the camera's view back, the design set
 * in `option`, the one there before given to the pockets unless it was a design's, back to
 * idle and the target's button blinks. */
static void use_on_room(MyDesigns *self, int option, int wallpaper)
{
    if (MyDesigns_MayChangeRoom() == 0) {
        MyDesigns_ShowError(self, wallpaper ? MY_DESIGNS_ERROR_WALLPAPER : MY_DESIGNS_ERROR_CARPET, 1);
        return;
    }
    if (!wallpaper) {
        PlayerRecords_Current();
    }
    int free_slot = CurrentPockets_FreeSlot();
    u16 there = wallpaper ? *RoomShell_WallpaperCode2() : *RoomShell_CarpetCode2();
    int a_design = in_range(there, MY_DESIGNS_ROOM_DESIGN_FIRST, MY_DESIGNS_ROOM_DESIGN_LAST);
    if (!a_design && free_slot == -1) {
        MyDesigns_ShowError(self, MY_DESIGNS_ERROR_POCKETS_FULL, 1);
        return;
    }
    MyDesigns_RestoreCamera(self);
    if (wallpaper) {
        RoomInterior_SetWallpaperDesign(MyDesigns_DesignAt(self, self->picked), option, 1, 1);
    } else {
        RoomInterior_SetCarpetDesign(MyDesigns_DesignAt(self, self->picked), option, 1, 1);
    }
    if (!a_design) {
        CurrentPockets_Give(&there, 0);
    }
    MyDesigns_BackToIdle(self);
    MyDesigns_StartBlink(self, self->target);
}

/* func_ov121_0229a940 (actions 2 and 3): the picked design as the room's wallpaper, in
 * `option` (use_on_room). */
void MyDesigns_UseAsWallpaper(MyDesigns *self, int option)
{
    use_on_room(self, option, 1);
}
CLEAN_AS(func_ov121_0229a940, MyDesigns_UseAsWallpaper)

/* func_ov121_0229a9f8 (actions 0 and 1): the picked design as the room's carpet, in `option`
 * (use_on_room).
 * QUIRK: it asks for the current player's record and does not use it. */
void MyDesigns_UseAsCarpet(MyDesigns *self, int option)
{
    use_on_room(self, option, 0);
}
CLEAN_AS(func_ov121_0229a9f8, MyDesigns_UseAsCarpet)

/* func_ov121_0229aab4 (MY_DESIGNS_BUTTON_BACKDROP, action 4): the picked design's clothes item
 * put behind the menus (MenuBackdrop_QueueDesign, through the second layer task and the scene's
 * buffers); a shirt there before goes to the pockets (MY_DESIGNS_ERROR_POCKETS_FULL when they
 * have no free slot, looked for first in any case). Then back to idle, with its sound. */
void MyDesigns_UseAsBackdrop(MyDesigns *self)
{
    u8 *record = PlayerRecords_Current();
    int free_slot = CurrentPockets_FreeSlot();
    u16 there = *PlayerRecord_Item2410(record);
    int a_shirt = in_range(there, MY_DESIGNS_SHIRT_FIRST, MY_DESIGNS_SHIRT_LAST);
    if (a_shirt && free_slot == -1) {
        MyDesigns_ShowError(self, MY_DESIGNS_ERROR_POCKETS_FULL, 1);
        return;
    }
    MyDesigns_RestoreCamera(self);
    u16 item = design_item(MY_DESIGNS_CLOTHES_ITEM, (unsigned int) MyDesigns_DesignAt(self, self->picked));
    MenuBackdrop_QueueDesign(&item, &self->tasks[1], self->backdrop_chars, self->backdrop_palette);
    if (a_shirt) {
        CurrentPockets_Give(&there, 0);
    }
    MyDesigns_BackToIdle(self);
    SoundSys_PlaySe(MY_DESIGNS_SE_BACKDROP);
}
CLEAN_AS(func_ov121_0229aab4, MyDesigns_UseAsBackdrop)

/* func_ov121_0229ab80: the action of the choice's row `row`.
 * REQUIRES: `row` is a row of the choice (0-4); the game reads past them for others. */
unsigned char MyDesigns_RowAction(MyDesigns *self, unsigned int row)
{
    return self->entries.values[row];
}
CLEAN_AS(func_ov121_0229ab80, MyDesigns_RowAction)

/* func_ov121_0229ab8c: the choice's rows set to those of `choice` (data_ov121_0229c258). */
void MyDesigns_SetChoice(MyDesigns *self, int choice)
{
    MI_CpuCopy8(data_ov121_0229c258[choice], &self->entries, sizeof(ChoiceEntries));
}
CLEAN_AS(func_ov121_0229ab8c, MyDesigns_SetChoice)

/* func_ov121_0229abac: the current player's design shown at place `place` (its DesignOrder). */
int MyDesigns_DesignAt(MyDesigns *self, int place)
{
    (void) self;
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    return DesignOrder_Get((unsigned char *) (uintptr_t) (u32) PlayerDesigns_Order(designs), place);
}
CLEAN_AS(func_ov121_0229abac, MyDesigns_DesignAt)

/* func_ov121_0229abc8: places `a` and `b` swap their designs, in the player's order and in the
 * scene's copy of it; nothing for the same place. */
void MyDesigns_SwapPlaces(MyDesigns *self, int a, int b)
{
    if (a == b) {
        return;
    }
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    DesignOrder_Swap((unsigned char *) (uintptr_t) (u32) PlayerDesigns_Order(designs), a, b);
    u8 kept = self->order[a];
    self->order[a] = self->order[b];
    self->order[b] = kept;
}
CLEAN_AS(func_ov121_0229abc8, MyDesigns_SwapPlaces)

/* The choice `choice` opened over the target when the room may be changed, else the error. */
static void open_room_choice(MyDesigns *self, int choice, char locked)
{
    if (MyDesigns_MayChangeRoom() != 0) {
        MyDesigns_SetChoice(self, choice);
    } else {
        MyDesigns_ShowError(self, locked, 1);
        return;
    }
    MyDesigns_OpenChoice(self);
}

/* func_ov121_0229ac00: the picked design put down on `target`: on a design the two swap places
 * (0, the caller goes on); on a button its use (1), by `where` for the buttons 12-14 (in the
 * player's own room a choice, or furniture for 14). 0 for MY_DESIGNS_BUTTON_HELD in
 * MY_DESIGNS_ROOM and for any other place. */
int MyDesigns_UseOnTarget(MyDesigns *self)
{
    if (self->target <= MY_DESIGNS_DESIGN_LAST) {
        SoundSys_PlaySe(MY_DESIGNS_SE_SWAP);
        MyDesigns_SwapPlaces(self, self->target, self->picked);
        return 0;
    }
    switch (self->target) {
        case MY_DESIGNS_BUTTON_BACKDROP:
            MyDesigns_UseAsBackdrop(self);
            return 1;
        case MY_DESIGNS_BUTTON_CARPET:
            open_room_choice(self, 0, MY_DESIGNS_ERROR_CARPET);
            return 1;
        case MY_DESIGNS_BUTTON_WALLPAPER:
            open_room_choice(self, 1, MY_DESIGNS_ERROR_WALLPAPER);
            return 1;
        case MY_DESIGNS_BUTTON_CLOTHES:
            switch (self->where) {
                case MY_DESIGNS_OUTSIDE:
                case MY_DESIGNS_ROOM:
                    MyDesigns_WearPicked(self, MY_DESIGNS_WEAR_CLOTHES);
                    break;
                case MY_DESIGNS_OWN_ROOM:
                    MyDesigns_SetChoice(self, 3);
                    MyDesigns_OpenChoice(self);
                    break;
            }
            return 1;
        case MY_DESIGNS_BUTTON_HEAD:
            switch (self->where) {
                case MY_DESIGNS_OUTSIDE:
                case MY_DESIGNS_ROOM:
                    MyDesigns_WearPicked(self, MY_DESIGNS_WEAR_HEAD);
                    break;
                case MY_DESIGNS_OWN_ROOM:
                    MyDesigns_SetChoice(self, 4);
                    MyDesigns_OpenChoice(self);
                    break;
            }
            return 1;
        case MY_DESIGNS_BUTTON_HELD:
            switch (self->where) {
                case MY_DESIGNS_OUTSIDE:
                    MyDesigns_WearPicked(self, MY_DESIGNS_WEAR_HELD);
                    return 1;
                case MY_DESIGNS_OWN_ROOM:
                    MyDesigns_PlaceFurniture(self);
                    return 1;
                default:
                    return 0;
            }
        case MY_DESIGNS_BUTTON_FURNITURE:
            MyDesigns_PlaceFurniture(self);
            return 1;
        case MY_DESIGNS_BUTTON_GROUND:
            MyDesigns_DropOnGround(self);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov121_0229ac00, MyDesigns_UseOnTarget)

/* func_ov121_0229b020 (MY_DESIGNS_SUB_DROP_WAIT): the ground's answer to `drop_request`: once
 * it worked, the camera's view back, the target's button blinks and back to idle; refused, the
 * error MY_DESIGNS_ERROR_NO_SPACE. Either way the request is let go. */
void MyDesigns_WaitDrop(MyDesigns *self)
{
    switch (TileRequests_Carry(self->drop_request)) {
        case 1:
            MyDesigns_RestoreCamera(self);
            MyDesigns_StartBlink(self, self->target);
            MyDesigns_BackToIdle(self);
            break;
        case 2:
            refuse(self, MY_DESIGNS_ERROR_NO_SPACE);
            break;
        default:
            return;
    }
    TileRequests_Release(self->drop_request);
    self->drop_request = -1;
}
CLEAN_AS(func_ov121_0229b020, MyDesigns_WaitDrop)

/* func_ov121_0229b09c (MY_DESIGNS_SUB_CHANGE_WAIT): back to idle once the player has changed. */
void MyDesigns_WaitChange(MyDesigns *self)
{
    if (MyDesigns_IsChangeDone(self, self->wear_kind) != 0) {
        MyDesigns_BackToIdle(self);
    }
}
CLEAN_AS(func_ov121_0229b09c, MyDesigns_WaitChange)

/* func_ov121_0229b0bc (MY_DESIGNS_SUB_CHANGE_REQUEST): the player asked to change into `item`;
 * once taken, MY_DESIGNS_SUB_CHANGE_WAIT. Answers 0 while not taken, else the address of the
 * sub state (MenuScene_SetSubState's). */
int MyDesigns_WaitChangeRequest(MyDesigns *self)
{
    int taken = MyDesigns_RequestChange(self, self->wear_kind, self->item);
    if (taken != 0) {
        return (int) (uintptr_t) MenuScene_SetSubState(use_scene(self), MY_DESIGNS_SUB_CHANGE_WAIT);
    }
    return taken;
}
CLEAN_AS(func_ov121_0229b0bc, MyDesigns_WaitChangeRequest)

/* func_ov121_0229ba2c: whether the player is in a house's room and not as a linked guest. */
int MyDesigns_InOwnRoom(void *self)
{
    (void) self;
    if (SceneKinds_CurrentIsHouseRoom() == 0) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) != 0 && session->local_slot != 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov121_0229ba2c, MyDesigns_InOwnRoom)
