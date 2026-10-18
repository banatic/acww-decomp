/* The town map's scene (town_map.h): its construction and teardown, its states and sub states,
 * the key cursor and its pointer, and its draw. */
#include "town_map.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/dual_cell_sprite.h"
#include "main/layer_load_task.h"
#include "main/message_reader.h"
#include "main/oam_buffer.h"
#include "main/player_actor_ops.h"
#include "main/rom_file.h"
#include "main/scene_place.h"
#include "main/scene_tables.h"
#include "main/screen_map.h"
#include "main/text_base.h"
#include "main/text_label.h"
#include "main/town_name.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(TownMap, wipe_y) == 0x94, "wipe");
static_assert(offsetof(TownMap, flags) == 0x9c && offsetof(TownMap, first_row) == 0xa3, "bytes");
static_assert(offsetof(TownMap, cursor) == 0xab && offsetof(TownMap, blink_frame) == 0xaf, "bytes");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(TownMap, map_task) == 0xd4, "tasks");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(TownMap, labels) == 0xf8, "labels");
static_assert(offsetof(TownMap, knob) == 0x674 && offsetof(TownMap, pointer) == 0x6bc, "sprites");
static_assert(offsetof(TownMap, map_screen) == 0x720 && offsetof(TownMap, list_template) == 0x1f20, "screens");
static_assert(offsetof(TownMap, people) == 0x2720 && offsetof(TownMap, places) == 0x272d, "lists");
static_assert(sizeof(TownMapMark) == 3 && offsetof(TownMap, marks) == 0x2743, "marks");
static_assert(sizeof(TownMapMarker) == 6 && sizeof(TownMap) == 0x2770, "size (func_ov120_0229c45c)");

/* The scene's vtable. */
extern const u8 data_ov120_0229c650[];

/* The phases the scene sets (MenuScene_Update runs phase 1 by the vtable's slot 0x4c, 2 by
 * 0x50, 3 by 0x54, 4 by 0x58 and 5 by 0x5c). */
enum TownMapPhase {
    TOWN_MAP_PHASE_STATES = 1,      /* TownMap_RunState */
    TOWN_MAP_PHASE_INTERACTIVE = 2, /* TownMap_RunInteractive */
    TOWN_MAP_PHASE_DELETE = 5       /* TownMap_RequestDelete */
};

/* The pad and the touch (main's bytes, as ov106's mailbox_scene.c reads them). */
extern PadState data_021fbe40;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

extern Heap *data_021fbe94;      /* the current heap */
extern TownName data_021dc7aa;   /* the town's name */
extern u8 data_020e54a8;         /* set in a room */
extern ScenePlace data_021f69b8; /* the marked place */

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov120_0229c784; /* the states' guard */
extern u32 data_ov120_0229c788; /* the sub states' guard */
extern MemberPointer data_ov120_0229c798[TOWN_MAP_STATES];
extern MemberPointer data_ov120_0229c7d0[TOWN_MAP_SUB_STATES];
extern const MemberPointer data_ov120_0229c520; /* TownMap_SubPress */
extern const MemberPointer data_ov120_0229c528; /* TownMap_StateStartWipeIn */
extern const MemberPointer data_ov120_0229c530; /* TownMap_SubKnobPress */
extern const MemberPointer data_ov120_0229c538; /* TownMap_SubKnobHold */
extern const MemberPointer data_ov120_0229c540; /* TownMap_SubKnobRelease */
extern const MemberPointer data_ov120_0229c548; /* TownMap_StateShowList */
extern const MemberPointer data_ov120_0229c550; /* TownMap_SubRelease */
extern const MemberPointer data_ov120_0229c560; /* TownMap_SubGlide */
extern const MemberPointer data_ov120_0229c568; /* TownMap_SubTouch */
extern const MemberPointer data_ov120_0229c570; /* TownMap_SubOnMap */
extern const MemberPointer data_ov120_0229c578; /* TownMap_SubDrag */
extern const MemberPointer data_ov120_0229c588; /* TownMap_StateWipeOut */
extern const MemberPointer data_ov120_0229c590; /* TownMap_StateStartWipeOut */
extern const MemberPointer data_ov120_0229c598; /* TownMap_StateWipeIn */
extern const MemberPointer data_ov120_0229c5a0; /* TownMap_SubKeys */
extern const MemberPointer data_ov120_0229c5a8; /* TownMap_StateLoadBg */
extern const MemberPointer data_ov120_0229c5b0; /* TownMap_StateLoadMap */

/* The cells of the list's frame and its two tabs. */
extern const OamEntry data_ov120_0229c5b8[]; /* the places' tab */
extern const OamEntry data_ov120_0229c5d8[]; /* the people's tab */
extern const OamEntry data_ov120_0229c5f8[]; /* the frame */

/* The files of "menu/map/". */
extern const char data_ov120_0229c6b0[]; /* b_map_obj.bpl */
extern const char data_ov120_0229c6c8[]; /* b_map_obj_0.bch */
extern const char data_ov120_0229c6e4[]; /* b_map_obj_1.bch */
extern const char data_ov120_0229c700[]; /* b_map_bg.bpl */
extern const char data_ov120_0229c718[]; /* b_map_bg_0.bch */
extern const char data_ov120_0229c730[]; /* b_map_bg_1.bch */
extern const char data_ov120_0229c748[]; /* b_map_a_bg.bsc */
extern const char data_ov120_0229c760[]; /* b_map_b_bg.bsc */

/* Overlay 117's table of places, a static object made once (guard bit 0 of
 * data_ov120_0229c780) and registered with its destructor (the game's function) in the record
 * at data_ov120_0229c78c. */
extern u32 data_ov120_0229c780;
extern u8 data_ov120_0229c78c[];
extern TownMapMarker data_ov120_0229c820[TOWN_MAP_MARKERS];
/* The table's destructor (TownMapMarkers_Destruct, which does nothing) is registered with the
 * C++ runtime, so it is the game's symbol. */
extern void func_ov117_0229a2ec(void *places);
extern void __register_global_object(void *object, void *destruct, void *record);

/* The members' constructors and destructors handed to __cxa_vec_ctor and __cxa_vec_cleanup
 * (the game's symbols): a label's (TextLabel_Construct, TextLabel_Destruct) and a mark's. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);
extern void func_ov120_0229a420(void *mark);
extern void func_ov120_0229a424(void *mark);

#define TOWN_MAP_LABEL_CONSTRUCT ((void (*)(void *))(uintptr_t) func_02070c08)
#define TOWN_MAP_LABEL_DESTRUCT ((void (*)(void *))(uintptr_t) func_02070be8)

/* The list's bar and rows. */
#define TOWN_MAP_SCREEN_BYTES 0x800
#define TOWN_MAP_LIST_Y 0x50 /* sub BG3 is scrolled so that the list's top is here */
#define TOWN_MAP_MAP_CHARS_BYTES 0x2000

/* The wipes: on window 2 over layers 10 (sub BG1 and BG3), margin 0x30. */
#define TOWN_MAP_WIPE_LAYERS 10
#define TOWN_MAP_WIPE_MARGIN 0x30

/* The menu message of the title ("... the town's name") and the kinds of the marks drawn apart. */
#define TOWN_MAP_TITLE_MESSAGE 0xa9
#define TOWN_MAP_KIND_PLAYER 0x0a
#define TOWN_MAP_KIND_MAP_CURSOR 0x0b
#define TOWN_MAP_PALETTE_PICKED 8

static MenuScene *town_map_scene(TownMap *self)
{
    return &self->base;
}

static DualCellSprite *town_map_knob_cells(TownMap *self)
{
    return (DualCellSprite *) (void *) &self->knob;
}

static CellLayerSprite *town_map_pointer_cells(TownMap *self)
{
    return (CellLayerSprite *) (void *) &self->pointer;
}

static MenuDispatch *town_map_parent(TownMap *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* A virtual function of a member's class without arguments: slot 2 draws, slot 3 animates. */
static void town_map_call_slot(void *object, int slot)
{
    void (*const *vtable)(void *) = *(void (*const *const *)(void *)) object;
    vtable[slot](object);
}

#define TOWN_MAP_SLOT_DRAW 2
#define TOWN_MAP_SLOT_ANIMATE 3

static int town_map_is_row(int cursor)
{
    return cursor >= TOWN_MAP_CURSOR_ROW_FIRST && cursor <= TOWN_MAP_CURSOR_ROW_LAST;
}

/* The pen touched the screen this frame. */
static int town_map_touch_began(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The members' destructors, last member first, then the base's.
 * QUIRK: the two layer tasks are not destructed. */
static void town_map_destroy_members(TownMap *self)
{
    self->base.vtable = data_ov120_0229c650;
    __cxa_vec_cleanup(self->marks, TOWN_MAP_MARKS, sizeof(TownMapMark), func_ov120_0229a420);
    __cxa_vec_cleanup(self->extra_marks, TOWN_MAP_EXTRA_MARKS, sizeof(TownMapMark), func_ov120_0229a420);
    Glider0_Destroy(&self->pointer);
    PushButton_Destroy(&self->knob);
    __cxa_vec_cleanup(self->labels, TOWN_MAP_LABELS, sizeof(TextLabel), TOWN_MAP_LABEL_DESTRUCT);
    MenuScene_DestroyBase(town_map_scene(self));
}

/* func_ov120_0229a340 (vtable slot 0x40) */
TownMap *TownMap_Destroy(TownMap *self)
{
    town_map_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov120_0229a340, TownMap_Destroy)

/* func_ov120_0229a3ac (vtable slot 0x44): the deleting destructor. */
TownMap *TownMap_Delete(TownMap *self)
{
    town_map_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov120_0229a3ac, TownMap_Delete)

/* func_ov120_0229a420: a mark's destructor: nothing. */
void TownMap_MarkDestruct(void *mark)
{
    (void) mark;
}
CLEAN_AS(func_ov120_0229a420, TownMap_MarkDestruct)

/* func_ov120_0229a424: a mark's constructor: nothing. */
void TownMap_MarkConstruct(void *mark)
{
    (void) mark;
}
CLEAN_AS(func_ov120_0229a424, TownMap_MarkConstruct)

/* func_ov120_0229a428 */
void TownMap_ClearFlags(TownMap *self, unsigned short mask)
{
    self->flags = (u16) (self->flags & ~mask);
}
CLEAN_AS(func_ov120_0229a428, TownMap_ClearFlags)

/* func_ov120_0229a438 */
void TownMap_SetFlags(TownMap *self, unsigned short mask)
{
    self->flags = (u16) (self->flags | mask);
}
CLEAN_AS(func_ov120_0229a438, TownMap_SetFlags)

/* func_ov120_0229a448: whether any of `mask` is set, as 0 or 1. */
int TownMap_TestFlags(TownMap *self, unsigned short mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov120_0229a448, TownMap_TestFlags)

/* func_ov120_0229a4bc: A on the cursor: on the map the mark under it picked; on the knob the
 * knob pressed (1); on the other list's tab that list shown with nothing picked (2); on a row the
 * row picked. 0 otherwise. */
int TownMap_Pick(TownMap *self)
{
    int cursor;

    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_ON_MAP) != 0) {
        TownMap_Select(self, (unsigned char) (self->map_mark + TOWN_MAP_TARGET_MARK_FIRST));
        return 0;
    }
    cursor = self->cursor;
    if (cursor == TOWN_MAP_CURSOR_KNOB) {
        MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_KNOB_PRESS);
        DualCellSprite_SetState(town_map_knob_cells(self), DUAL_CELL_SPRITE_PLAY_A);
        TownMap_SetFlags(self, TOWN_MAP_FLAG_KNOB_HELD);
        return 1;
    }
    if (cursor == TOWN_MAP_CURSOR_PEOPLE_TAB) {
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES) != 0) {
            TownMap_Select(self, TOWN_MAP_TARGET_NONE);
            TownMap_ShowPeople(self);
            return 2;
        }
        return 0;
    }
    if (cursor == TOWN_MAP_CURSOR_PLACES_TAB) {
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES) == 0) {
            TownMap_Select(self, TOWN_MAP_TARGET_NONE);
            TownMap_ShowPlaces(self);
            return 2;
        }
        return 0;
    }
    if (town_map_is_row(cursor)) {
        TownMap_Select(self,
                       (unsigned char) (self->first_row + cursor + (TOWN_MAP_TARGET_ROW_FIRST - TOWN_MAP_CURSOR_ROW_FIRST)));
    }
    return 0;
}
CLEAN_AS(func_ov120_0229a4bc, TownMap_Pick)

/* func_ov120_0229a584: the cursor moved by the latched keys: on the rows up and down (up from
 * the first to the places' tab, down to the last in view or of the list), right to the knob when
 * it is shown; from the knob up to the people's tab, left back to the row at the knob's height;
 * on the tabs down to the first row, left to the places' tab, right to the people's tab or from
 * there to the knob. Returns whether it moved. */
int TownMap_MoveCursor(TownMap *self, u32 keys)
{
    int was = self->cursor;

    if (town_map_is_row(was)) {
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLABLE) != 0 && KeyRepeat_HasRight((int) keys) != 0) {
            self->cursor = TOWN_MAP_CURSOR_KNOB;
        } else if (KeyRepeat_HasUp((int) keys) != 0) {
            if (self->cursor > TOWN_MAP_CURSOR_ROW_FIRST) {
                self->cursor--;
            } else {
                self->cursor = TOWN_MAP_CURSOR_PLACES_TAB;
            }
        } else if (KeyRepeat_HasDown((int) keys) != 0) {
            int last = (int) TownMap_RowCount(self) - 1;
            int cursor = self->cursor;
            if (cursor < TOWN_MAP_CURSOR_ROW_LAST && cursor < last + TOWN_MAP_CURSOR_ROW_FIRST) {
                self->cursor++;
            }
        }
    } else if (was == TOWN_MAP_CURSOR_KNOB) {
        if (KeyRepeat_HasUp((int) keys) != 0) {
            self->cursor = TOWN_MAP_CURSOR_PEOPLE_TAB;
        } else if (KeyRepeat_HasLeft((int) keys) != 0) {
            int y = PushButton_FaceY(&self->knob);
            if (y < 0x50) {
                y = 0x50;
            }
            if (y >= 0xb0) {
                y = 0xaf;
            }
            self->cursor = (u8) (((y - 0x50) >> 4) + TOWN_MAP_CURSOR_ROW_FIRST);
        }
    } else if (was <= TOWN_MAP_CURSOR_PLACES_TAB) {
        if (KeyRepeat_HasDown((int) keys) != 0) {
            self->cursor = TOWN_MAP_CURSOR_ROW_FIRST;
        } else if (KeyRepeat_HasLeft((int) keys) != 0) {
            self->cursor = TOWN_MAP_CURSOR_PLACES_TAB;
        } else if (KeyRepeat_HasRight((int) keys) != 0) {
            if (self->cursor == TOWN_MAP_CURSOR_PEOPLE_TAB && TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLABLE) != 0) {
                self->cursor = TOWN_MAP_CURSOR_KNOB;
            } else {
                self->cursor = TOWN_MAP_CURSOR_PEOPLE_TAB;
            }
        }
    }
    return was != self->cursor;
}
CLEAN_AS(func_ov120_0229a584, TownMap_MoveCursor)

/* func_ov120_0229a6d0: the pointer shows the first of its set of animations (at rest). */
void TownMap_ShowPointer(TownMap *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    town_map_call_slot(&self->pointer, TOWN_MAP_SLOT_ANIMATE);
}
CLEAN_AS(func_ov120_0229a6d0, TownMap_ShowPointer)

/* func_ov120_0229a6f0: the pointer's release played (TOWN_MAP_SUB_RELEASE). */
void TownMap_ReleasePointer(TownMap *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_RELEASE);
}
CLEAN_AS(func_ov120_0229a6f0, TownMap_ReleasePointer)

/* func_ov120_0229a710: the pointer's press played (TOWN_MAP_SUB_PRESS). */
void TownMap_PressPointer(TownMap *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_PRESS);
}
CLEAN_AS(func_ov120_0229a710, TownMap_PressPointer)

/* func_ov120_0229a730: the pointer to the cursor: put there at once with
 * TOWN_MAP_FLAG_PLACE_POINTER (which is then cleared), else eased there in 3 steps while the sub
 * state waits (TOWN_MAP_SUB_GLIDE, back to this one after). */
void TownMap_GlideToCursor(TownMap *self)
{
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACE_POINTER)) {
        int x = TownMap_CursorX(self);
        int y = TownMap_CursorY(self);
        Glider_PlaceAt(&self->pointer, x, y);
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_PLACE_POINTER);
    } else {
        int x = TownMap_CursorX(self);
        int y = TownMap_CursorY(self);
        Glider_EaseTo(&self->pointer, x, y, 3, 1);
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_GLIDE);
    }
}
CLEAN_AS(func_ov120_0229a730, TownMap_GlideToCursor)

/* func_ov120_0229a7a8: the pointer hidden (animation 0). */
void TownMap_HidePointer(TownMap *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    town_map_call_slot(&self->pointer, TOWN_MAP_SLOT_ANIMATE);
}
CLEAN_AS(func_ov120_0229a7a8, TownMap_HidePointer)

/* func_ov120_0229a7cc: the cursor's y (TownMapCursor; on the map `map_y`). */
int TownMap_CursorY(TownMap *self)
{
    int cursor;

    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_ON_MAP)) {
        return self->map_y;
    }
    cursor = self->cursor;
    if (town_map_is_row(cursor)) {
        return 0x58 + ((cursor - TOWN_MAP_CURSOR_ROW_FIRST) << 4);
    }
    if (cursor <= TOWN_MAP_CURSOR_PLACES_TAB) {
        return 0x40;
    }
    if (cursor == TOWN_MAP_CURSOR_KNOB) {
        return PushButton_FaceY(&self->knob);
    }
    return 0x60;
}
CLEAN_AS(func_ov120_0229a7cc, TownMap_CursorY)

/* func_ov120_0229a81c: the cursor's x (TownMapCursor; on the map `map_x`). */
int TownMap_CursorX(TownMap *self)
{
    int cursor;

    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_ON_MAP) != 0) {
        return self->map_x;
    }
    cursor = self->cursor;
    if (town_map_is_row(cursor)) {
        return 0xa0;
    }
    if (cursor == TOWN_MAP_CURSOR_PEOPLE_TAB) {
        return 0xd8;
    }
    if (cursor == TOWN_MAP_CURSOR_PLACES_TAB) {
        return 0xbc;
    }
    if (cursor == TOWN_MAP_CURSOR_KNOB) {
        return PushButton_FaceX(&self->knob);
    }
    return 0x80;
}
CLEAN_AS(func_ov120_0229a81c, TownMap_CursorX)

/* func_ov120_0229a870: the cursor taken up: off the knob when it is not shown, the pointer put
 * at it and shown, the list scrolled to a whole row when the cursor is on one. */
void TownMap_EnterCursor(TownMap *self)
{
    int x;
    int y;

    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLABLE) == 0 && self->cursor == TOWN_MAP_CURSOR_KNOB) {
        self->cursor = TOWN_MAP_CURSOR_PEOPLE_TAB;
    }
    x = TownMap_CursorX(self);
    y = TownMap_CursorY(self);
    Glider_PlaceAt(&self->pointer, x, y);
    if (town_map_is_row(self->cursor)) {
        TownMap_SetScrollTarget(self, (unsigned short) (self->scroll & ~0xf));
    }
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    TownMap_ShowPointer(self);
}
CLEAN_AS(func_ov120_0229a870, TownMap_EnterCursor)

/* func_ov120_0229b604: on to the keys: the knob at rest, the cursor taken up, the usual key
 * repeat; TOWN_MAP_SUB_ON_MAP with the cursor on the map, else TOWN_MAP_SUB_KEYS. */
void TownMap_EnterKeys(TownMap *self)
{
    DualCellSprite_SetState(town_map_knob_cells(self), DUAL_CELL_SPRITE_STILL);
    TownMap_EnterCursor(self);
    MenuScene_ResetKeyRepeat(town_map_scene(self));
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_ON_MAP) != 0) {
        MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_ON_MAP);
    } else {
        MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_KEYS);
    }
}
CLEAN_AS(func_ov120_0229b604, TownMap_EnterKeys)

/* func_ov120_0229b64c: on to the pen: the pointer hidden (TOWN_MAP_SUB_TOUCH). */
void TownMap_EnterTouch(TownMap *self)
{
    TownMap_HidePointer(self);
    MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_TOUCH);
}
CLEAN_AS(func_ov120_0229b64c, TownMap_EnterTouch)

/* func_ov120_0229b664 (sub state 9): A, X, B or a touch closes the scene. */
void TownMap_SubOnMap(TownMap *self)
{
    u16 pressed = data_021fbe40.pressed;

    if ((pressed & (TOWN_MAP_KEY_A | TOWN_MAP_KEY_X | TOWN_MAP_KEY_B)) != 0 || town_map_touch_began()) {
        TownMap_RequestClose(self);
    }
}
CLEAN_AS(func_ov120_0229b664, TownMap_SubOnMap)

/* func_ov120_0229b6b8 (sub state 8): once the knob has come back up, the pointer's release. */
void TownMap_SubKnobRelease(TownMap *self)
{
    if (DualCellSprite_IsDone(town_map_knob_cells(self))) {
        TownMap_ReleasePointer(self);
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_KNOB_HELD);
    }
}
CLEAN_AS(func_ov120_0229b6b8, TownMap_SubKnobRelease)

/* func_ov120_0229b6e4 (sub state 7): while A is held, up and down scroll the list; when it is
 * let go, the knob comes back up (TOWN_MAP_SUB_KNOB_RELEASE). */
void TownMap_SubKnobHold(TownMap *self)
{
    if ((data_021fbe40.held & TOWN_MAP_KEY_A) == 0) {
        DualCellSprite_SetState(town_map_knob_cells(self), DUAL_CELL_SPRITE_PLAY_B);
        MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_KNOB_RELEASE);
    } else {
        TownMap_ScrollByKeys(self);
    }
}
CLEAN_AS(func_ov120_0229b6e4, TownMap_SubKnobHold)

/* func_ov120_0229b71c (sub state 6): once the knob is down, TOWN_MAP_SUB_KNOB_HOLD. */
void TownMap_SubKnobPress(TownMap *self)
{
    if (DualCellSprite_IsDone(town_map_knob_cells(self)) != 0) {
        MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_KNOB_HOLD);
    }
}
CLEAN_AS(func_ov120_0229b71c, TownMap_SubKnobPress)

/* func_ov120_0229b740 (sub state 5): once the pointer's release has played, the pointer at
 * rest and back to the keys' sub state. */
void TownMap_SubRelease(TownMap *self)
{
    if (CellLayerSprite_IsDone(town_map_pointer_cells(self))) {
        TownMap_ShowPointer(self);
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_ON_MAP)) {
            MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_ON_MAP);
        } else {
            MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_KEYS);
        }
    }
}
CLEAN_AS(func_ov120_0229b740, TownMap_SubRelease)

/* func_ov120_0229b784 (sub state 4): once the pointer's press has played, the pick
 * (TownMap_Pick); then the release, unless the knob was pressed, with the list at its top after
 * a switch. */
void TownMap_SubPress(TownMap *self)
{
    if (CellLayerSprite_IsDone(town_map_pointer_cells(self)) != 0) {
        int result = TownMap_Pick(self);
        if (result == 1) {
            return;
        }
        if (result == 2) {
            TownMap_SetScroll(self, 0);
            self->first_row = 0xff;
            TownMap_ReleasePointer(self);
            return;
        }
        TownMap_ReleasePointer(self);
    }
}
CLEAN_AS(func_ov120_0229b784, TownMap_SubPress)

/* func_ov120_0229b7cc (sub state 3): once the pointer has stopped, back to the sub state it
 * left, which runs at once. */
void TownMap_SubGlide(TownMap *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(town_map_scene(self), self->return_sub_state);
        TownMap_RunSubState(self);
    }
}
CLEAN_AS(func_ov120_0229b7cc, TownMap_SubGlide)

/* func_ov120_0229b7f8 (sub state 2): the keys. A touch goes on to the pen; a move of the cursor
 * glides the pointer to it (the list scrolled to a whole row first); A presses; Y puts the
 * cursor on the map, at the mark of the row it was on, with nothing picked. */
void TownMap_SubKeys(TownMap *self)
{
    u16 pressed;

    if (MenuScene_TakeTouch(town_map_scene(self)) != 0) {
        TownMap_EnterTouch(self);
        return;
    }
    if (TownMap_MoveCursor(self, MenuScene_LatchRepeatedKeys(town_map_scene(self))) != 0) {
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLABLE) != 0 && town_map_is_row(self->cursor)) {
            TownMap_SetScrollTarget(self, (unsigned short) (self->scroll & ~0xf));
        }
        TownMap_GlideToCursor(self);
        return;
    }
    pressed = data_021fbe40.pressed;
    if (pressed & TOWN_MAP_KEY_A) {
        TownMap_PressPointer(self);
        return;
    }
    if (!(pressed & TOWN_MAP_KEY_Y)) {
        return;
    }
    TownMap_Select(self, TOWN_MAP_TARGET_NONE);
    TownMap_HighlightRow(self, TOWN_MAP_NONE);
    if (town_map_is_row(self->cursor)) {
        TownMap_MapCursorFromRow(self);
    }
    self->map_mark = TownMap_FindMarkAt(self, self->map_x, self->map_y);
    TownMap_SetFlags(self, TOWN_MAP_FLAG_ON_MAP);
    MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_ON_MAP);
    TownMap_GlideToCursor(self);
}
CLEAN_AS(func_ov120_0229b7f8, TownMap_SubKeys)

/* func_ov120_0229b8d0 (sub state 1): the knob follows the pen; when the pen is up the knob
 * comes back up and the scene goes back to the pen (after a last move). */
void TownMap_SubDrag(TownMap *self)
{
    if (!data_021fbdd8) {
        DualCellSprite_SetState(town_map_knob_cells(self), DUAL_CELL_SPRITE_PLAY_B);
        TownMap_EnterTouch(self);
    }
    TownMap_ScrollByDrag(self);
}
CLEAN_AS(func_ov120_0229b8d0, TownMap_SubDrag)

/* func_ov120_0229b900 (sub state 0): the pen. A button goes on to the keys; a touch switches the
 * list on a tab, takes the knob (TOWN_MAP_SUB_DRAG) or picks a mark or a row. */
void TownMap_SubTouch(TownMap *self)
{
    if (MenuScene_TakeButtons(town_map_scene(self), 1) != 0) {
        TownMap_EnterKeys(self);
        return;
    }
    if (!town_map_touch_began()) {
        return;
    }
    if (TownMap_TouchTabs(self) != 0) {
        return;
    }
    if (TownMap_TouchKnob(self) != 0) {
        DualCellSprite_SetState(town_map_knob_cells(self), DUAL_CELL_SPRITE_PLAY_A);
        MenuScene_SetSubState(town_map_scene(self), TOWN_MAP_SUB_DRAG);
    } else if (TownMap_TouchMap(self) == 0) {
        TownMap_TouchList(self);
    }
}
CLEAN_AS(func_ov120_0229b900, TownMap_SubTouch)

/* func_ov120_0229b97c: the OBJs' palettes 6-14 and characters 0xc0-0xff and 0x180-0x1ff of the
 * sub screen from their files. */
void TownMap_LoadObjFiles(void)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadPalettesFromFile(data_ov120_0229c6b0, heap, LAYER_SUB_OBJ, 6, 6, 14);
    DisplayLayer_LoadCharsFromFile(data_ov120_0229c6c8, heap, LAYER_SUB_OBJ, 0xc0, 0xc0, 0xff);
    DisplayLayer_LoadCharsFromFile(data_ov120_0229c6e4, heap, LAYER_SUB_OBJ, 0x180, 0x180, 0x1ff);
}
CLEAN_AS(func_ov120_0229b97c, TownMap_LoadObjFiles)

/* func_ov120_0229b9dc: the town's map drawn by overlay 117 into 0x2000 bytes from the current
 * heap, loaded as sub BG1's characters 0x60-0x15f, and its places taken as the marks. Overlay
 * 117's table of places is made the first time (and registered for its destructor), then unset
 * each time before the drawing.
 * QUIRK: the block from the heap is not checked for NULL. */
void TownMap_LoadMap(TownMap *self)
{
    Heap *heap = data_021fbe94;
    void *chars = Heap_AllocBack(heap, TOWN_MAP_MAP_CHARS_BYTES);

    if (!(data_ov120_0229c780 & 1)) {
        TownMapMarkers_Construct(data_ov120_0229c820);
        __register_global_object(data_ov120_0229c820, (void *) (uintptr_t) func_ov117_0229a2ec, data_ov120_0229c78c);
        data_ov120_0229c780 |= 1;
    }
    TownMapMarkers_Clear(data_ov120_0229c820);
    TownMapImage_Build((int) (uintptr_t) chars, (int) (uintptr_t) data_ov120_0229c820);
    DisplayLayer_LoadChars((u32) (uintptr_t) chars, LAYER_SUB_BG1, 0x60, 0x60, 0x15f);
    TownMap_ReadMarks(self, data_ov120_0229c820);
    Heap_Free(heap, chars);
}
CLEAN_AS(func_ov120_0229b9dc, TownMap_LoadMap)

/* func_ov120_0229ba68: the backgrounds' palettes 1-15 and characters 0x11-0x5f and 0x230-0x25f
 * of sub BG1 from their files; sub BG1's screen read and loaded; the list's template read, with
 * the rows' two lines plain. */
void TownMap_LoadBg(TownMap *self)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadPalettesFromFile(data_ov120_0229c700, heap, LAYER_SUB_BG1, 1, 1, 0xf);
    DisplayLayer_LoadCharsFromFile(data_ov120_0229c718, heap, LAYER_SUB_BG1, 0x11, 0x11, 0x5f);
    DisplayLayer_LoadCharsFromFile(data_ov120_0229c730, heap, LAYER_SUB_BG1, 0x230, 0x230, 0x25f);
    RomFile_Read(data_ov120_0229c748, self->map_screen, TOWN_MAP_SCREEN_BYTES);
    DisplayLayer_LoadScreen(self->map_screen, LAYER_SUB_BG1, TOWN_MAP_SCREEN_BYTES, 0);
    RomFile_Read(data_ov120_0229c760, self->list_template, TOWN_MAP_SCREEN_BYTES);
    ScreenMap_SetPalette(self->list_template, 0x13, 0, 0x1c, 1, 4);
}
CLEAN_AS(func_ov120_0229ba68, TownMap_LoadBg)

/* func_ov120_0229bb18: sub BG1 and BG3 at priority 2 with the plain background control. */
void TownMap_SetUpLayers(void)
{
    DisplayLayer_SetPriority(LAYER_SUB_BG1, 2);
    DisplayLayer_SetPriority(LAYER_SUB_BG3, 2);
    DisplayLayer_SetBgControl(LAYER_SUB_BG1, 0, 0, 0);
    DisplayLayer_SetBgControl(LAYER_SUB_BG3, 0, 0, 0);
}
CLEAN_AS(func_ov120_0229bb18, TownMap_SetUpLayers)

/* func_ov120_0229bb4c */
void TownMap_EndFrame(TownMap *self)
{
    TownMap_UpdateScreens(self);
}
CLEAN_AS(func_ov120_0229bb4c, TownMap_EndFrame)

/* func_ov120_0229bb54: the start of an interactive frame: the labels let go, the knob and the
 * pointer animated (their classes' slot 3). */
void TownMap_BeginInteractive(TownMap *self)
{
    TownMap_BeginFrame(self);
    town_map_call_slot(&self->knob, TOWN_MAP_SLOT_ANIMATE);
    town_map_call_slot(&self->pointer, TOWN_MAP_SLOT_ANIMATE);
}
CLEAN_AS(func_ov120_0229bb54, TownMap_BeginInteractive)

/* func_ov120_0229bb80: the end of a frame: the scroll stepped (sub BG3 scrolled with it, the
 * shown list made again when its top row changed), the blink stepped, the shown list made
 * again when asked, and the screens asked for queued (each flag kept until its queueing
 * succeeds). */
void TownMap_UpdateScreens(TownMap *self)
{
    if (TownMap_IsScrolling(self) != 0) {
        TownMap_StepScroll(self);
        DisplayLayer_SetScroll(LAYER_SUB_BG3, 0, (int) self->scroll - TOWN_MAP_LIST_Y);
        if (self->first_row != self->scroll >> 4) {
            TownMap_SetFlags(self, TOWN_MAP_FLAG_LIST_DIRTY);
        }
    }
    TownMap_StepBlink(self);
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_LIST_DIRTY) != 0) {
        TownMap_MakeShownList(self);
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_LIST_DIRTY);
    }
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_MAP_UPLOAD) != 0) {
        if (LayerTask_QueueScreen(&self->map_task, (int) (uintptr_t) self->map_screen, LAYER_SUB_BG1, TOWN_MAP_SCREEN_BYTES,
                                  0) != 0) {
            TownMap_ClearFlags(self, TOWN_MAP_FLAG_MAP_UPLOAD);
        }
    }
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_LIST_UPLOAD) != 0) {
        if (LayerTask_QueueScreen(&self->list_task, (int) (uintptr_t) self->list_shown, LAYER_SUB_BG3, TOWN_MAP_SCREEN_BYTES,
                                  0) != 0) {
            TownMap_ClearFlags(self, TOWN_MAP_FLAG_LIST_UPLOAD);
        }
    }
}
CLEAN_AS(func_ov120_0229bb80, TownMap_UpdateScreens)

/* func_ov120_0229bc4c: the start of a frame: the labels let go (taken again as drawn). */
void TownMap_BeginFrame(TownMap *self)
{
    TownMap_ReleaseLabels(self);
}
CLEAN_AS(func_ov120_0229bc4c, TownMap_BeginFrame)

/* func_ov120_0229bc54: the labels let go and both layer tasks ended. */
void TownMap_Teardown(TownMap *self)
{
    TownMap_ReleaseLabels(self);
    LayerTask_End(&self->list_task);
    LayerTask_End(&self->map_task);
}
CLEAN_AS(func_ov120_0229bc54, TownMap_Teardown)

/* func_ov120_0229bc74: the scene's values set up: the list at its top, nothing picked, the
 * map cursor at the map's centre, the lists built, the player's mark at the player's place
 * (outdoors the place of PlayerActorOps_StartPosition(4); in a room the marked place's), the
 * knob at rest. The mark is 8 pixels left of and 13 below the place's whole x and z. */
void TownMap_Setup(TownMap *self)
{
    Vec3 at;

    self->label_count = 0;
    self->flags = 0;
    self->scroll = 0;
    self->scroll_target = 0;
    self->knob_pos = 0;
    self->wipe_y = 0;
    self->blink_timer = 0;
    self->cursor = TOWN_MAP_CURSOR_PEOPLE_TAB;
    self->map_x = 0x58;
    self->map_y = 0x70;
    self->map_mark = TOWN_MAP_NONE;
    TownMap_Select(self, TOWN_MAP_TARGET_NONE);
    TownMap_BuildLists(self);
    if (data_020e54a8 == 0) {
        at = *PlayerActorOps_StartPosition(4);
    } else {
        SceneTables_EntryRecord();
        at = *(const Vec3 *) ScenePlace_Position(&data_021f69b8);
    }
    /* the whole x and z, rounded (fx32, arithmetic shift) */
    self->player_x = (u8) (((at.x + 0x800) >> 12) - 8);
    self->player_y = (u8) (((at.z + 0x800) >> 12) + 0xd);
    DualCellSprite_SetState(town_map_knob_cells(self), DUAL_CELL_SPRITE_STILL);
}
CLEAN_AS(func_ov120_0229bc74, TownMap_Setup)

/* Both layers scrolled with the wipe (sub BG3 at the list's scroll) and its offset kept. */
static void town_map_follow_wipe(TownMap *self)
{
    MenuScene_ScrollWipe(town_map_scene(self), LAYER_SUB_BG1, 0, 0);
    MenuScene_ScrollWipe(town_map_scene(self), LAYER_SUB_BG3, 0, TOWN_MAP_LIST_Y - self->scroll);
    self->wipe_y = MenuScene_WipeOffsetY(town_map_scene(self));
}

/* func_ov120_0229bd4c (state 6): the wipe out; at its end both layers hidden, the OBJs no more
 * drawn and the scene deleted (phase 5). */
void TownMap_StateWipeOut(TownMap *self)
{
    if (MenuScene_StepWipe(town_map_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG1);
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG3);
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_DRAWN);
        MenuScene_SetPhase(town_map_scene(self), TOWN_MAP_PHASE_DELETE);
    } else {
        town_map_follow_wipe(self);
    }
}
CLEAN_AS(func_ov120_0229bd4c, TownMap_StateWipeOut)

/* func_ov120_0229bdac (state 5): the pointer hidden and the wipe out started. */
void TownMap_StateStartWipeOut(TownMap *self)
{
    TownMap_HidePointer(self);
    MenuScene_StartWipeOnWindow2(town_map_scene(self), TOWN_MAP_WIPE_LAYERS, 0, 0, TOWN_MAP_WIPE_MARGIN);
    MenuScene_ScrollWipe(town_map_scene(self), LAYER_SUB_BG1, 0, 0);
    MenuScene_ScrollWipe(town_map_scene(self), LAYER_SUB_BG3, 0, TOWN_MAP_LIST_Y - self->scroll);
    MenuScene_SetState(town_map_scene(self), TOWN_MAP_STATE_WIPE_OUT);
    self->wipe_y = MenuScene_WipeOffsetY(town_map_scene(self));
}
CLEAN_AS(func_ov120_0229bdac, TownMap_StateStartWipeOut)

/* func_ov120_0229be00 (state 4): the wipe in; at its end the cursor on the map 4 pixels right
 * of and above the players' house (in a byte, held at its edges), and on to the keys (phase 2). */
void TownMap_StateWipeIn(TownMap *self)
{
    if (MenuScene_StepWipeBack(town_map_scene(self), 0)) {
        const TownMapMark *house;

        MenuScene_SetPhase(town_map_scene(self), TOWN_MAP_PHASE_INTERACTIVE);
        self->map_mark = TOWN_MAP_MARK_PLAYERS_HOUSE;
        house = &self->marks[self->map_mark];
        self->map_x = house->x;
        self->map_y = house->y;
        if (self->map_y > 4) {
            self->map_y -= 4;
        } else {
            self->map_y = 0;
        }
        if (self->map_x < 0xfc) {
            self->map_x += 4;
        } else {
            self->map_x = 0xff;
        }
        TownMap_SetFlags(self, TOWN_MAP_FLAG_ON_MAP);
        TownMap_EnterKeys(self);
    }
    town_map_follow_wipe(self);
}
CLEAN_AS(func_ov120_0229be00, TownMap_StateWipeIn)

/* func_ov120_0229bedc (state 3): the OBJs' files loaded; the title (menu message 0xa9 with the
 * town's name as its part 0) in a label of its own; the wipe in started with both layers shown;
 * the OBJs drawn from now. */
void TownMap_StateStartWipeIn(TownMap *self)
{
    TownNameText name;
    TextLabel *title;

    TownMap_LoadObjFiles();
    TownNameText_Construct(&name);
    TownName_ToText(&data_021dc7aa, (TextBase *) (void *) &name);
    MessageReader_SetPart(0, (int) (uintptr_t) &name);
    title = TownMap_TakeLabel(self);
    TextLabel_OpenStyledBox2(title, 8, 0x1ab, 0x12, 0xf, 0, 0);
    TextLabel_LoadMenuMessage((int) (uintptr_t) title, (char) TOWN_MAP_TITLE_MESSAGE);
    TextLabel_Show(title, 1, 0);
    TownNameText_Destruct(&name);

    MenuScene_StartWipeCoveredOnWindow2(town_map_scene(self), TOWN_MAP_WIPE_LAYERS, 0, 0, TOWN_MAP_WIPE_MARGIN);
    DisplayLayer_Show(LAYER_SUB_BG1);
    MenuScene_ScrollWipe(town_map_scene(self), LAYER_SUB_BG1, 0, 0);
    DisplayLayer_Show(LAYER_SUB_BG3);
    MenuScene_ScrollWipe(town_map_scene(self), LAYER_SUB_BG3, 0, TOWN_MAP_LIST_Y - self->scroll);
    TownMap_SetFlags(self, TOWN_MAP_FLAG_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(town_map_scene(self));
    MenuScene_SetState(town_map_scene(self), TOWN_MAP_STATE_WIPE_IN);
}
CLEAN_AS(func_ov120_0229bedc, TownMap_StateStartWipeIn)

/* func_ov120_0229bf98 (state 2): the people's list shown and made for sub BG3. */
void TownMap_StateShowList(TownMap *self)
{
    TownMap_ShowPeople(self);
    TownMap_MakeShownList(self);
    MenuScene_SetState(town_map_scene(self), TOWN_MAP_STATE_START_WIPE);
}
CLEAN_AS(func_ov120_0229bf98, TownMap_StateShowList)

/* func_ov120_0229bfb4 (state 1): the map loaded. The source gives it three more parameters, not
 * read (it is called as a member function of the scene alone). */
void TownMap_StateLoadMap(TownMap *self, int unused_op, u32 unused_0, u32 unused_1)
{
    (void) unused_op;
    (void) unused_0;
    (void) unused_1;
    TownMap_LoadMap(self);
    MenuScene_SetState(town_map_scene(self), TOWN_MAP_STATE_SHOW_LIST);
}
CLEAN_AS(func_ov120_0229bfb4, TownMap_StateLoadMap)

/* func_ov120_0229bfcc (state 0): the layers set up and the backgrounds loaded. */
void TownMap_StateLoadBg(TownMap *self)
{
    TownMap_SetUpLayers();
    TownMap_LoadBg(self);
    MenuScene_SetState(town_map_scene(self), TOWN_MAP_STATE_LOAD_MAP);
}
CLEAN_AS(func_ov120_0229bfcc, TownMap_StateLoadBg)

/* func_ov120_0229bfe8: the parent told the screen closes (with the backdrop and sound), and the
 * wipe out started (state 5, phase 1). Answers 1. */
int TownMap_RequestClose(TownMap *self)
{
    MenuDispatch_SetMode(town_map_parent(self), MENU_DISPATCH_MODE_CLOSE, 1);
    self->base.state = TOWN_MAP_STATE_CLOSE;
    MenuScene_SetPhase(town_map_scene(self), TOWN_MAP_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov120_0229bfe8, TownMap_RequestClose)

/* func_ov120_0229c010 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int TownMap_RequestDelete(TownMap *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov120_0229c010, TownMap_RequestDelete)

/* func_ov120_0229c020 (vtable slot 0x58, phase 4): nothing. */
int TownMap_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov120_0229c020, TownMap_Phase4)

/* func_ov120_0229c024 (vtable slot 0x54, phase 3): nothing. */
int TownMap_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov120_0229c024, TownMap_Phase3)

/* func_ov120_0229c028 (vtable slot 0x50, phase 2): an interactive frame: its start, the sub
 * state, its end. Answers 1. */
int TownMap_RunInteractive(TownMap *self)
{
    TownMap_BeginInteractive(self);
    TownMap_RunSubState(self);
    TownMap_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov120_0229c028, TownMap_RunInteractive)

/* func_ov120_0229c044: the sub state (TownMapSubState) run through its table of member
 * functions, filled once from its constants.
 * REQUIRES: the sub state is below 10; the game reads past the table for others. */
void TownMap_RunSubState(TownMap *self)
{
    static const MemberPointer *const sub_states[TOWN_MAP_SUB_STATES] = {
        &data_ov120_0229c568, &data_ov120_0229c578, &data_ov120_0229c5a0, &data_ov120_0229c560, &data_ov120_0229c520,
        &data_ov120_0229c550, &data_ov120_0229c530, &data_ov120_0229c538, &data_ov120_0229c540, &data_ov120_0229c570,
    };
    MemberTable_InitOnce(&data_ov120_0229c788, data_ov120_0229c7d0, sub_states, TOWN_MAP_SUB_STATES);
    MemberPointer_CallVoid(&data_ov120_0229c7d0[self->base.sub_state], self);
}
CLEAN_AS(func_ov120_0229c044, TownMap_RunSubState)

/* func_ov120_0229c11c (vtable slot 0x4c, phase 1): a frame of the states (TownMapState) through
 * their table of member functions (filled once from its constants), between the frame's start
 * and the screens' update. Answers 1.
 * REQUIRES: the state is below 7; the game reads past the table for others. */
int TownMap_RunState(TownMap *self)
{
    static const MemberPointer *const states[TOWN_MAP_STATES] = {
        &data_ov120_0229c5a8, &data_ov120_0229c5b0, &data_ov120_0229c548, &data_ov120_0229c528,
        &data_ov120_0229c598, &data_ov120_0229c590, &data_ov120_0229c588,
    };
    MemberTable_InitOnce(&data_ov120_0229c784, data_ov120_0229c798, states, TOWN_MAP_STATES);
    TownMap_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov120_0229c798[self->base.state], self);
    TownMap_UpdateScreens(self);
    return 1;
}
CLEAN_AS(func_ov120_0229c11c, TownMap_RunState)

/* func_ov120_0229c1d8 (vtable slot 0x24): the scene's draw, while TOWN_MAP_FLAG_DRAWN, all at
 * the wipe's offset: the knob placed on its bar (when shown), the pointer, the list's frame and
 * its two tabs (their palettes by the list shown), the map cursor's mark, the player's mark in 12 of
 * each 16 frames, the extra marks, the marks (the picked one in palette 8 but in the off half of
 * its blink) and the knob (its class's slot 2). Answers 1. */
int TownMap_Draw(TownMap *self)
{
    int y = self->wipe_y + 0x60;
    int people_palette;
    int places_palette;

    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_DRAWN) == 0) {
        return 1;
    }
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLABLE) != 0) {
        DualCellSprite_SetOffset(town_map_knob_cells(self), 0x67, self->wipe_y - 0x12 + self->knob_pos);
    }
    Glider_DrawWrapped(&self->pointer);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, data_ov120_0229c5f8, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES) != 0) {
        people_palette = 0xc;
        places_palette = 0xd;
    } else {
        people_palette = 0xb;
        places_palette = 0xe;
    }
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, data_ov120_0229c5b8, 0x80, y, places_palette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, data_ov120_0229c5d8, 0x80, y, people_palette, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    if (self->map_mark != TOWN_MAP_NONE && self->marks[self->map_mark].kind != TOWN_MAP_KIND_NONE) {
        const TownMapMark *mark = &self->marks[self->map_mark];
        TownMap_DrawMark(self, mark->x, self->wipe_y + mark->y, TOWN_MAP_KIND_MAP_CURSOR, 0, -1);
    }
    self->blink_frame = (self->blink_frame + 1) & 0xf;
    if ((self->blink_frame & 0xc) != 0) {
        TownMap_DrawMark(self, self->player_x, self->wipe_y + self->player_y, TOWN_MAP_KIND_PLAYER, 0, -1);
    }
    for (int i = 0; i < TOWN_MAP_EXTRA_MARKS; i++) {
        const TownMapMark *mark = &self->extra_marks[i];
        int kind = mark->kind;
        if (kind != TOWN_MAP_KIND_NONE) {
            int flip = (kind & 0x80) != 0 ? 1 : 0;
            TownMap_DrawMark(self, mark->x, self->wipe_y + mark->y, kind & 0x7f, flip, -1);
        }
    }
    for (int i = 0; i < TOWN_MAP_MARKS; i++) {
        const TownMapMark *mark = &self->marks[i];
        if (mark->kind != TOWN_MAP_KIND_NONE) {
            int palette;
            if (i == self->picked_mark && TownMap_TestFlags(self, TOWN_MAP_FLAG_BLINK_OFF) == 0) {
                palette = TOWN_MAP_PALETTE_PICKED;
            } else {
                palette = -1;
            }
            TownMap_DrawMark(self, mark->x, self->wipe_y + mark->y, mark->kind, 0, palette);
        }
    }
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLABLE) != 0) {
        town_map_call_slot(&self->knob, TOWN_MAP_SLOT_DRAW);
    }
    return 1;
}
CLEAN_AS(func_ov120_0229c1d8, TownMap_Draw)

/* func_ov120_0229c420 (vtable slot 0x0c): the scene ends: the parent told and the scene torn
 * down. Answers 1. */
int TownMap_End(TownMap *self)
{
    MenuDispatch_ChildClosed(town_map_parent(self));
    TownMap_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov120_0229c420, TownMap_End)

/* func_ov120_0229c43c (vtable slot 0x00): the scene starts: its setup, state 0 and phase 1.
 * Answers 1. */
int TownMap_Start(TownMap *self)
{
    TownMap_Setup(self);
    MenuScene_SetState(town_map_scene(self), TOWN_MAP_STATE_LOAD_BG);
    MenuScene_SetPhase(town_map_scene(self), TOWN_MAP_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov120_0229c43c, TownMap_Start)

/* func_ov120_0229c45c (named by the profile at 0x0229c580): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the labels and the marks by __cxa_vec_ctor. */
TownMap *TownMap_New(void)
{
    TownMap *self = MenuScene_Alloc(sizeof(TownMap));

    if (self != NULL) {
        MenuScene_Construct(&self->base);
        self->base.vtable = data_ov120_0229c650;
        LayerTask_Construct(&self->list_task);
        LayerTask_Construct(&self->map_task);
        __cxa_vec_ctor(self->labels, TOWN_MAP_LABELS, sizeof(TextLabel), TOWN_MAP_LABEL_CONSTRUCT, TOWN_MAP_LABEL_DESTRUCT);
        PushButton_Construct(&self->knob);
        Glider0_Construct(&self->pointer);
        __cxa_vec_ctor(self->extra_marks, TOWN_MAP_EXTRA_MARKS, sizeof(TownMapMark), func_ov120_0229a424, func_ov120_0229a420);
        __cxa_vec_ctor(self->marks, TOWN_MAP_MARKS, sizeof(TownMapMark), func_ov120_0229a424, func_ov120_0229a420);
    }
    return self;
}
CLEAN_AS(func_ov120_0229c45c, TownMap_New)
