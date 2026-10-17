/* The "my designs" scene of overlay 121 (my_designs.h): its destructors, its flags, the
 * buttons' blinking, the d-pad's cursor and the pointer, the popup, the pen, the sub states,
 * the states, the draw and the constructor. */
#include "my_designs.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/design_info.h"
#include "main/design_sets.h"
#include "main/display_layers.h"
#include "main/name_texts.h"
#include "main/oam_buffer.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/session.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_string.h"
#include "main/tile_convert.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(MyDesigns, wipe_y) == 0x94, "base");
static_assert(offsetof(MyDesigns, flags) == 0xa2 && offsetof(MyDesigns, grab_dy) == 0xaa, "places");
static_assert(offsetof(MyDesigns, where) == 0xac && offsetof(MyDesigns, wear_kind) == 0xb7, "bytes");
static_assert(offsetof(MyDesigns, backdrop_palette) == 0xb8 && offsetof(MyDesigns, popup) == 0x2d8, "backdrop");
static_assert(offsetof(MyDesigns, pointer) == 0x3a8 && offsetof(MyDesigns, error) == 0x40c, "pointer");
static_assert(offsetof(MyDesigns, choice) == 0x528 && offsetof(MyDesigns, entries) == 0x910, "choice");
static_assert(offsetof(MyDesigns, tasks) == 0x91c && offsetof(MyDesigns, screen) == 0x98c, "tasks");
static_assert(offsetof(MyDesigns, order) == 0x118c && sizeof(MyDesigns) == 0x1194, "size (func_ov121_0229c19c)");

/* The pen and the buttons (autoload_2/input.c). */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern PadState data_021fbe40;
extern Heap *data_021fbe94;
extern u8 data_020e54a8; /* in a room */
extern NetSession *data_020ccf94;

#define MY_DESIGNS_PAD_A 0x0001
#define MY_DESIGNS_PAD_B 0x0002
#define MY_DESIGNS_PAD_SELECT 0x0004
#define MY_DESIGNS_PAD_R 0x0100
#define MY_DESIGNS_PAD_L 0x0200
#define MY_DESIGNS_PAD_X 0x0400
#define MY_DESIGNS_PAD_Y 0x0800

/* The tabs of overlay 90's bar this scene asks for (ov090/menu_tabs.h). */
#define MY_DESIGNS_TAB_POCKETS 0
#define MY_DESIGNS_TAB_SELF 1
#define MY_DESIGNS_TAB_4 4
#define MY_DESIGNS_TAB_5 5
#define MY_DESIGNS_TAB_CLOSE 7
#define MY_DESIGNS_TAB_NONE (-1)

/* The buttons' palettes on their screen. */
#define MY_DESIGNS_PALETTE_NORMAL 2
#define MY_DESIGNS_PALETTE_LIT 6
#define MY_DESIGNS_PALETTE_DISABLED 7

/* Sound effects (SoundSys_PlaySe). */
#define MY_DESIGNS_SE_TOUCH 0x0c
#define MY_DESIGNS_SE_PICK_UP 0x0d
#define MY_DESIGNS_SE_PUT_DOWN 0x0e
#define MY_DESIGNS_SE_ROW 0x50

/* The layers: the buttons' screen on the sub screen's background 3, the designs' OBJs. */
#define MY_DESIGNS_LAYER LAYER_SUB_BG3
#define MY_DESIGNS_WIPE_MARGIN 0x30

/* The scene's vtable, and the profile's places of each design and button (by place, x and
 * y), the cursor's design under each tab, and the buttons' cells on their screen (by button
 * - 9, column and row). */
extern const u8 data_ov121_0229c3a8[];
extern const u8 data_ov121_0229c248[];
extern const u8 data_ov121_0229c238[];
extern const u8 data_ov121_0229c210[];
extern const u16 data_ov121_0229c218[];
extern const u16 data_ov121_0229c228[];
/* The designs' OBJ (its tile set for each design before it is drawn) and the target's mark. */
extern OamEntry data_ov121_0229c2c0;
extern const OamEntry data_ov121_0229c380[];
/* The files. */
extern const char data_ov121_0229c408[]; /* "menu/desi/b_myd_obj.bch" */
extern const char data_ov121_0229c420[]; /* "menu/desi/b_myd_obj.bpl" */
extern const char data_ov121_0229c438[]; /* "menu/desi/b_myd_bg.bpl" */
extern const char data_ov121_0229c450[]; /* "menu/desi/b_myd_bg.bch" */
extern const char data_ov121_0229c468[]; /* "menu/desi/b_myd_a_bg.bsc" */

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables (the
 * symbol table names the sub states' second part, from sub state 0x10, data_ov121_0229c548)
 * and their constants. */
extern u32 data_ov121_0229c4a0; /* the sub states' guard */
extern u32 data_ov121_0229c4a4; /* the states' guard */
extern MemberPointer data_ov121_0229c4a8[MY_DESIGNS_STATES];
extern MemberPointer data_ov121_0229c4c8[MY_DESIGNS_SUB_STATES];
extern const MemberPointer data_ov121_0229c2a0, data_ov121_0229c2a8, data_ov121_0229c2b0, data_ov121_0229c2c8,
    data_ov121_0229c2d0, data_ov121_0229c2d8, data_ov121_0229c2e0, data_ov121_0229c2e8, data_ov121_0229c2f0,
    data_ov121_0229c2f8, data_ov121_0229c308, data_ov121_0229c310, data_ov121_0229c318, data_ov121_0229c320,
    data_ov121_0229c328, data_ov121_0229c330, data_ov121_0229c338, data_ov121_0229c340, data_ov121_0229c348,
    data_ov121_0229c350, data_ov121_0229c358, data_ov121_0229c360, data_ov121_0229c368, data_ov121_0229c370,
    data_ov121_0229c378;

static MenuScene *scene(MyDesigns *self)
{
    return &self->base;
}

static PagedChoice *choice(MyDesigns *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static CellLayerSprite *pointer_cells(MyDesigns *self)
{
    return (CellLayerSprite *) (void *) &self->pointer;
}

static MenuTabs *parent_tabs(MyDesigns *self)
{
    return (MenuTabs *) (void *) Process_GetParent((Process *) (void *) self);
}

/* An object updated or drawn through its class (vtable slot `slot`). */
static void call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

static int pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

static int distance(int a, int b)
{
    int d = a - b;
    return d < 0 ? -d : d;
}

/* func_ov121_022999a0 (vtable slot 0x40) and func_ov121_022999ec (slot 0x44): the members'
 * destructors, last member first, then the base's. The layer tasks have none. */
static void destroy_members(MyDesigns *self)
{
    self->base.vtable = data_ov121_0229c3a8;
    PagedChoice_Destroy(choice(self));
    ErrorMessage_Destruct(&self->error);
    Glider0_Destroy(&self->pointer);
    Popup_Destroy(&self->popup);
    MenuScene_DestroyBase(scene(self));
}

/* func_ov121_022999a0 */
MyDesigns *MyDesigns_Destroy(MyDesigns *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov121_022999a0, MyDesigns_Destroy)

/* func_ov121_022999ec */
MyDesigns *MyDesigns_Delete(MyDesigns *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov121_022999ec, MyDesigns_Delete)

/* func_ov121_02299a3c */
void MyDesigns_ClearFlags(MyDesigns *self, unsigned short mask)
{
    self->flags &= (u16) ~mask;
}
CLEAN_AS(func_ov121_02299a3c, MyDesigns_ClearFlags)

/* func_ov121_02299a4c */
void MyDesigns_SetFlags(MyDesigns *self, unsigned short mask)
{
    self->flags |= mask;
}
CLEAN_AS(func_ov121_02299a4c, MyDesigns_SetFlags)

/* func_ov121_02299a5c: 1 when any of `mask` is set. */
int MyDesigns_TestFlags(MyDesigns *self, int mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov121_02299a5c, MyDesigns_TestFlags)

/* func_ov121_02299c10 (each frame): a blinking button counts down, lit every fifth frame from
 * the second and normal two frames later; at 0 it stops, normal. */
void MyDesigns_StepBlink(MyDesigns *self)
{
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_BLINKING) == 0) {
        return;
    }
    if (self->blink_count != 0) {
        self->blink_count--;
        switch (self->blink_count % 5) {
            case 0:
                MyDesigns_SetButtonPalette(self, self->blink_button, MY_DESIGNS_PALETTE_NORMAL);
                break;
            case 3:
                MyDesigns_SetButtonPalette(self, self->blink_button, MY_DESIGNS_PALETTE_LIT);
                break;
        }
    } else {
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_BLINKING);
        MyDesigns_SetButtonPalette(self, self->blink_button, MY_DESIGNS_PALETTE_NORMAL);
    }
}
CLEAN_AS(func_ov121_02299c10, MyDesigns_StepBlink)

/* func_ov121_02299c88: `button` blinks for 15 frames; one blinking before is made normal.
 * REQUIRES: `button` is 9-15 when it is blinked (MyDesigns_SetButtonPalette). */
void MyDesigns_StartBlink(MyDesigns *self, unsigned char button)
{
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_BLINKING) != 0) {
        MyDesigns_SetButtonPalette(self, self->blink_button, MY_DESIGNS_PALETTE_NORMAL);
    }
    self->blink_button = button;
    self->blink_count = 15;
    MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_BLINKING);
}
CLEAN_AS(func_ov121_02299c88, MyDesigns_StartBlink)

/* func_ov121_02299ccc: the cursor moved by `keys` (KeyRepeat_Has*): left and right first, then,
 * unless that move wrapped (or went diagonally from 11 to 15), up and down. `carrying` (a
 * design carried) lets the cursor reach the buttons from the designs and wrap between the
 * bottom row and the backdrop's button. The wrap flags are cleared first. 1 when the cursor
 * changed place. */
int MyDesigns_MoveCursor(MyDesigns *self, int keys, int carrying)
{
    u8 before = self->cursor;
    MyDesigns_ClearFlags(self, MY_DESIGNS_FLAGS_WRAPPED);
    if (MyDesigns_MoveCursorAcross(self, keys, carrying) == 0) {
        MyDesigns_MoveCursorVertically(self, keys, carrying);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov121_02299ccc, MyDesigns_MoveCursor)

/* func_ov121_02299d10: up and down.
 *
 * - Up: from the backdrop's button to design 0; from the top designs to the buttons below them
 *   (12-15) when carrying, else to the tab under the pointer; from the bottom designs to the
 *   top ones; from 9-11 to the tabs unless carrying; from 12-15 to the row above (12 to 9, 13
 *   to 10, 14 and 15 to 11; one further left when right is held too, so 12 goes to 8).
 * - Down: from the top designs to the bottom ones; from a tab to its design
 *   (MyDesigns_TabDownToDesigns); from 12-15 to the top designs; from 9-11 to the row below (9
 *   to 12, ...; one further when left is held too). */
void MyDesigns_MoveCursorVertically(MyDesigns *self, int keys, int carrying)
{
    if (KeyRepeat_HasUp(keys) != 0) {
        u8 place = self->cursor;
        if (place == MY_DESIGNS_BUTTON_BACKDROP) {
            self->cursor = MY_DESIGNS_DESIGN_FIRST;
            return;
        }
        if (place <= 3) {
            if (carrying != 0) {
                self->cursor += MY_DESIGNS_BUTTON_HEAD;
            } else {
                MyDesigns_UpToTabs(self);
            }
            return;
        }
        if (MyDesigns_ShiftCursor2(self, 4, MY_DESIGNS_DESIGN_LAST, 0) != 0) {
            return;
        }
        place = self->cursor;
        if (place >= MY_DESIGNS_BUTTON_FURNITURE && place <= MY_DESIGNS_BUTTON_WALLPAPER) {
            if (carrying == 0) {
                MyDesigns_UpToTabs(self);
            }
            return;
        }
        if (place < MY_DESIGNS_BUTTON_HEAD || place > MY_DESIGNS_BUTTON_GROUND) {
            return;
        }
        if (KeyRepeat_HasRight(keys) != 0) {
            self->cursor -= 1;
        }
        self->cursor -= 3;
        if (self->cursor > MY_DESIGNS_BUTTON_WALLPAPER) {
            self->cursor = MY_DESIGNS_BUTTON_WALLPAPER;
        }
        return;
    }

    if (KeyRepeat_HasDown(keys) == 0) {
        return;
    }
    if (MyDesigns_ShiftCursor(self, 0, 3, 4) != 0) {
        return;
    }
    int tab = MyDesigns_CursorTab(self);
    if (tab != -1) {
        MyDesigns_TabDownToDesigns(self, tab);
        return;
    }
    if (MyDesigns_ShiftCursor(self, MY_DESIGNS_BUTTON_HEAD, MY_DESIGNS_BUTTON_GROUND, 0) != 0) {
        return;
    }
    u8 place = self->cursor;
    if (place < MY_DESIGNS_BUTTON_FURNITURE || place > MY_DESIGNS_BUTTON_WALLPAPER) {
        return;
    }
    if (KeyRepeat_HasLeft(keys) != 0) {
        self->cursor += 1;
    }
    self->cursor += 3;
}
CLEAN_AS(func_ov121_02299d10, MyDesigns_MoveCursorVertically)

/* func_ov121_02299e34: from tab `tab` down to its design (data_ov121_0229c210), the pointer
 * turning to set A.
 * REQUIRES: `tab` is 0-7. */
void MyDesigns_TabDownToDesigns(MyDesigns *self, int tab)
{
    self->cursor = data_ov121_0229c210[tab];
    Glider_TurnToSetA(&self->pointer);
}
CLEAN_AS(func_ov121_02299e34, MyDesigns_TabDownToDesigns)

/* func_ov121_02299e54: up to the tab under the pointer, the pointer turning to set C. */
void MyDesigns_UpToTabs(MyDesigns *self)
{
    self->cursor = (u8) (MenuTabs_TabAtX(Glider_ScreenX(&self->pointer)) + MY_DESIGNS_TAB_FIRST);
    Glider_TurnToSetC(&self->pointer);
}
CLEAN_AS(func_ov121_02299e54, MyDesigns_UpToTabs)

/* func_ov121_02299e80: left and right. Within each row of designs and buttons the cursor wraps
 * around (MY_DESIGNS_FLAG_WRAPPED_LEFT or _RIGHT); the tabs do not wrap. The backdrop's button
 * goes left to design 7 (a wrap) and right to design 4; when carrying, design 4 goes left to it
 * and design 7 right to it (a wrap). Right with down from 11 goes to 15 at once (answers 1).
 * Else the answer is whether this move wrapped. */
int MyDesigns_MoveCursorAcross(MyDesigns *self, int keys, int carrying)
{
    if (KeyRepeat_HasLeft(keys) != 0) {
        if (self->cursor == MY_DESIGNS_BUTTON_BACKDROP) {
            self->cursor = MY_DESIGNS_DESIGN_LAST;
            MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_WRAPPED_LEFT);
        } else if (self->cursor == 4 && carrying != 0) {
            self->cursor = MY_DESIGNS_BUTTON_BACKDROP;
        } else if (MyDesigns_StepCursorLeft(self, 0, 3) == 0 &&
                   MyDesigns_StepCursorLeft(self, 4, MY_DESIGNS_DESIGN_LAST) == 0 &&
                   MyDesigns_StepCursorLeft(self, MY_DESIGNS_BUTTON_FURNITURE, MY_DESIGNS_BUTTON_WALLPAPER) == 0 &&
                   MyDesigns_StepCursorLeft(self, MY_DESIGNS_BUTTON_HEAD, MY_DESIGNS_BUTTON_GROUND) == 0) {
            u8 place = self->cursor;
            if (place > MY_DESIGNS_TAB_FIRST && place <= MY_DESIGNS_TAB_LAST) {
                self->cursor--;
            }
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (self->cursor == MY_DESIGNS_BUTTON_BACKDROP) {
            self->cursor = 4;
        } else if (self->cursor == MY_DESIGNS_DESIGN_LAST && carrying != 0) {
            self->cursor = MY_DESIGNS_BUTTON_BACKDROP;
            MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_WRAPPED_RIGHT);
        } else if (self->cursor == MY_DESIGNS_BUTTON_WALLPAPER && KeyRepeat_HasDown(keys) != 0) {
            self->cursor = MY_DESIGNS_BUTTON_GROUND;
            return 1;
        } else if (MyDesigns_StepCursorRight(self, 0, 3) == 0 &&
                   MyDesigns_StepCursorRight(self, 4, MY_DESIGNS_DESIGN_LAST) == 0 &&
                   MyDesigns_StepCursorRight(self, MY_DESIGNS_BUTTON_FURNITURE, MY_DESIGNS_BUTTON_WALLPAPER) == 0 &&
                   MyDesigns_StepCursorRight(self, MY_DESIGNS_BUTTON_HEAD, MY_DESIGNS_BUTTON_GROUND) == 0) {
            u8 place = self->cursor;
            if (place >= MY_DESIGNS_TAB_FIRST && place < MY_DESIGNS_TAB_LAST) {
                self->cursor++;
            }
        }
    }
    return MyDesigns_TestFlags(self, MY_DESIGNS_FLAGS_WRAPPED);
}
CLEAN_AS(func_ov121_02299e80, MyDesigns_MoveCursorAcross)

/* func_ov121_02299fc8: the tab (0-7) the cursor is on, or -1. */
int MyDesigns_CursorTab(MyDesigns *self)
{
    u8 place = self->cursor;
    if (place >= MY_DESIGNS_TAB_FIRST && place <= MY_DESIGNS_TAB_LAST) {
        return place - MY_DESIGNS_TAB_FIRST;
    }
    return -1;
}
CLEAN_AS(func_ov121_02299fc8, MyDesigns_CursorTab)

/* The cursor in `first`-`last` moved to the same place from `to`; whether it was in them. */
static int shift_cursor(MyDesigns *self, unsigned int first, unsigned int last, int to)
{
    unsigned int place = self->cursor;
    if (place >= first && place <= last) {
        self->cursor = (u8) (self->cursor + (to - (int) first));
        return 1;
    }
    return 0;
}

/* func_ov121_02299fe0 (shift_cursor) */
int MyDesigns_ShiftCursor(MyDesigns *self, unsigned int first, unsigned int last, int to)
{
    return shift_cursor(self, first, last, to);
}
CLEAN_AS(func_ov121_02299fe0, MyDesigns_ShiftCursor)

/* func_ov121_0229a00c: the same as func_ov121_02299fe0 (shift_cursor). */
int MyDesigns_ShiftCursor2(MyDesigns *self, unsigned int first, unsigned int last, int to)
{
    return shift_cursor(self, first, last, to);
}
CLEAN_AS(func_ov121_0229a00c, MyDesigns_ShiftCursor2)

/* func_ov121_0229a038: in the row `first`-`last`, the cursor one place left, from the first to
 * the last (MY_DESIGNS_FLAG_WRAPPED_LEFT); whether it was in the row. */
int MyDesigns_StepCursorLeft(MyDesigns *self, unsigned int first, unsigned int last)
{
    unsigned int place = self->cursor;
    if (place < first || place > last) {
        return 0;
    }
    if (place == first) {
        self->cursor = (u8) last;
        MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_WRAPPED_LEFT);
    } else {
        self->cursor--;
    }
    return 1;
}
CLEAN_AS(func_ov121_0229a038, MyDesigns_StepCursorLeft)

/* func_ov121_0229a074: in the row `first`-`last`, the cursor one place right, from the last to
 * the first (MY_DESIGNS_FLAG_WRAPPED_RIGHT); whether it was in the row. */
int MyDesigns_StepCursorRight(MyDesigns *self, unsigned int first, unsigned int last)
{
    unsigned int place = self->cursor;
    if (place < first || place > last) {
        return 0;
    }
    if (place == last) {
        MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_WRAPPED_RIGHT);
        self->cursor = (u8) first;
    } else {
        self->cursor++;
    }
    return 1;
}
CLEAN_AS(func_ov121_0229a074, MyDesigns_StepCursorRight)

/* func_ov121_0229a0b4: the carried design drawn at the pointer's frame, 3 pixels left of it and
 * 9 below. */
void MyDesigns_HeldAtPointer(MyDesigns *self)
{
    self->held_x = (s16) (Glider_FrameX(&self->pointer) - 3);
    self->held_y = (s16) (Glider_FrameY(&self->pointer) + 9);
}
CLEAN_AS(func_ov121_0229a0b4, MyDesigns_HeldAtPointer)

/* func_ov121_0229a0e0 (B with a design carried): the pointer's put-down turn, the design to go
 * back (MY_DESIGNS_FLAG_PUT_BACK), MY_DESIGNS_SUB_PUT_DOWN. */
void MyDesigns_BeginPutBack(MyDesigns *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_TURN_A + 1);
    MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_PUT_BACK);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_PUT_DOWN);
}
CLEAN_AS(func_ov121_0229a0e0, MyDesigns_BeginPutBack)

/* func_ov121_0229a108 (A with a design carried): the pointer's put-down turn, on the cursor,
 * MY_DESIGNS_SUB_PUT_DOWN. */
void MyDesigns_BeginPutDown(MyDesigns *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_TURN_A + 1);
    MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_PUT_BACK);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_PUT_DOWN);
}
CLEAN_AS(func_ov121_0229a108, MyDesigns_BeginPutDown)

/* func_ov121_0229a130 (A on a design): the pointer's pick-up turn, MY_DESIGNS_SUB_PICK_UP. */
void MyDesigns_BeginPickUp(MyDesigns *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_TURN_A);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_PICK_UP);
}
CLEAN_AS(func_ov121_0229a130, MyDesigns_BeginPickUp)

/* func_ov121_0229a150: the pointer's third of its set, MY_DESIGNS_SUB_TAB_RELEASE. */
void MyDesigns_BeginTabRelease(MyDesigns *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_TAB_RELEASE);
}
CLEAN_AS(func_ov121_0229a150, MyDesigns_BeginTabRelease)

/* func_ov121_0229a170 (A on a tab): the pointer's second of its set, MY_DESIGNS_SUB_TAB_PRESS. */
void MyDesigns_BeginTabPress(MyDesigns *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_TAB_PRESS);
}
CLEAN_AS(func_ov121_0229a170, MyDesigns_BeginTabPress)

/* func_ov121_0229a190: the pointer's first of its set, and the pointer updated through its
 * class (vtable slot 3). */
void MyDesigns_PointerFirstOfSet(MyDesigns *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    call_slot(&self->pointer, 3);
}
CLEAN_AS(func_ov121_0229a190, MyDesigns_PointerFirstOfSet)

/* func_ov121_0229a1b0: the pointer put at the cursor's place, in set A. */
void MyDesigns_PlacePointerAtCursor(MyDesigns *self)
{
    int x = MyDesigns_PointerX(self);
    int y = MyDesigns_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov121_0229a1b0, MyDesigns_PlacePointerAtCursor)

/* func_ov121_0229a1e4: the choice's first row chosen, the pointer put at its text, in set B. */
void MyDesigns_PointAtFirstRow(MyDesigns *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(choice(self));
    int y = PagedChoice_RowY(choice(self), self->choice_row);
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov121_0229a1e4, MyDesigns_PointAtFirstRow)

/* func_ov121_0229a230 (B in the choice): the cancel row (the last one) picked, its action
 * MY_DESIGNS_ACTION_CANCEL, the pointer put at it at the end of animation 8,
 * MY_DESIGNS_SUB_CHOICE_PICKED. */
void MyDesigns_CancelChoice(MyDesigns *self)
{
    self->action = MY_DESIGNS_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(choice(self), 1);
    int x = PagedChoice_TextX(choice(self));
    Glider_PlaceAt(&self->pointer, x, PagedChoice_RowY(choice(self), self->choice_row));
    CellLayerSprite_SetAnimAtEnd(pointer_cells(self), 8);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_PICKED);
}
CLEAN_AS(func_ov121_0229a230, MyDesigns_CancelChoice)

/* func_ov121_0229a294: the pointer moves to the chosen row's text in two steps; this sub state
 * comes back once it stops (MY_DESIGNS_SUB_POINTER_GLIDE). */
void MyDesigns_GlideToChoiceRow(MyDesigns *self)
{
    int x = PagedChoice_TextX(choice(self));
    int y = PagedChoice_RowY(choice(self), self->choice_row);
    Glider_MoveTo(&self->pointer, x, y, 2);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov121_0229a294, MyDesigns_GlideToChoiceRow)

/* func_ov121_0229a2e4: the pointer to the cursor: put there at once with
 * MY_DESIGNS_FLAG_POINTER_JUMP (cleared), else eased there in three steps with a cue, this sub
 * state coming back once it stops (MY_DESIGNS_SUB_POINTER_GLIDE). */
void MyDesigns_GlidePointer(MyDesigns *self)
{
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_POINTER_JUMP) != 0) {
        int x = MyDesigns_PointerX(self);
        int y = MyDesigns_PointerY(self);
        Glider_PlaceAt(&self->pointer, x, y);
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_POINTER_JUMP);
    } else {
        int x = MyDesigns_PointerX(self);
        int y = MyDesigns_PointerY(self);
        Glider_EaseTo(&self->pointer, x, y, 3, 1);
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_POINTER_GLIDE);
    }
}
CLEAN_AS(func_ov121_0229a2e4, MyDesigns_GlidePointer)

/* func_ov121_0229a358: the pointer without an animation, updated through its class (vtable
 * slot 3). */
void MyDesigns_ResetPointer(MyDesigns *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    call_slot(&self->pointer, 3);
}
CLEAN_AS(func_ov121_0229a358, MyDesigns_ResetPointer)

/* func_ov121_0229a37c: the pointer's y for the cursor: the place's, 11 pixels up except on the
 * tabs. */
int MyDesigns_PointerY(MyDesigns *self)
{
    int y = MyDesigns_PlaceY(self, self->cursor);
    if (MyDesigns_CursorTab(self) == -1) {
        y -= 11;
    }
    return y;
}
CLEAN_AS(func_ov121_0229a37c, MyDesigns_PointerY)

/* func_ov121_0229a3a8: the pointer's x for the cursor: the place's, a screen further right after
 * a wrap to the right (further left after one to the left) so that it glides around, 11 pixels
 * right except on the tabs. */
int MyDesigns_PointerX(MyDesigns *self)
{
    int x = MyDesigns_PlaceX(self, self->cursor);
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    if (MyDesigns_CursorTab(self) == -1) {
        x += 0xb;
    }
    return x;
}
CLEAN_AS(func_ov121_0229a3a8, MyDesigns_PointerX)

/* func_ov121_0229a3fc: the pointer put at the cursor in set C on a tab, else set A; then its
 * first of the set, updated. */
void MyDesigns_ShowPointerAtCursor(MyDesigns *self)
{
    int x = MyDesigns_PointerX(self);
    int y = MyDesigns_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
    if (MyDesigns_CursorTab(self) != -1) {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_C);
    } else {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    }
    MyDesigns_PointerFirstOfSet(self);
}
CLEAN_AS(func_ov121_0229a3fc, MyDesigns_ShowPointerAtCursor)

/* func_ov121_0229a450: on a design, the popup is to name it (`hover`, queued); elsewhere no
 * popup is queued. */
void MyDesigns_QueuePopupAtCursor(MyDesigns *self)
{
    u8 place = self->cursor;
    if (place <= MY_DESIGNS_DESIGN_LAST) {
        self->hover = place;
        Popup_Queue(&self->popup);
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov121_0229a450, MyDesigns_QueuePopupAtCursor)

/* func_ov121_0229a480 (when the popup is to show its text): the popup placed above the design at
 * `hover` (10 pixels higher in the d-pad's mode) and given the design's title. */
void MyDesigns_SetPopupText(MyDesigns *self)
{
    NameWideText title;
    SlidingWindowText line;

    int y = MyDesigns_PlaceY(self, self->hover) - 0x84;
    if (StateFlags_Test2()) {
        y -= 0xa;
    }
    int x = MyDesigns_PlaceX(self, self->hover);
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x - 0x78, y);

    NameWideText_Construct(&title);
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    unsigned int design = (unsigned int) PlayerDesigns_InOrder(designs, self->hover);
    unsigned int info = Design_Info(design);
    DesignInfo_TitleToWide((char *) (uintptr_t) info, (DesignTitleWide *) (void *) &title);
    SlidingWindowText_Construct(&line);
    TextString_WideToBytes((TextObject *) (void *) &line, (TextObject *) (void *) &title);
    SlidingWindow_SetText((SlidingWindow *) (void *) &self->popup, (struct TextObject *) (void *) &line);
    SlidingWindowText_Destruct(&line);
    NameWideText_Destruct(&title);
}
CLEAN_AS(func_ov121_0229a480, MyDesigns_SetPopupText)

/* func_ov121_0229a53c (when the menu is asked to close during the choice): the cancel action,
 * the pointer back at the cursor, the choice asked to close, MY_DESIGNS_SUB_CHOICE_CLOSING. */
void MyDesigns_CloseChoiceOnRequest(MyDesigns *self)
{
    self->action = MY_DESIGNS_ACTION_CANCEL;
    MyDesigns_PlacePointerAtCursor(self);
    PagedChoice_RequestClose(choice(self), 0);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov121_0229a53c, MyDesigns_CloseChoiceOnRequest)

/* func_ov121_0229a568: the choice's rows (`entries`) shown, the choice placed 0x18 pixels left
 * of the target and 0x10 below it and opening, MY_DESIGNS_SUB_CHOICE_OPENING. */
void MyDesigns_OpenChoice(MyDesigns *self)
{
    PagedChoice_ShowEntries(choice(self), &self->entries, 0);
    int x = MyDesigns_PlaceX(self, self->target) - 0x18;
    int y = MyDesigns_PlaceY(self, self->target) + 0x10;
    PagedChoice_Place(choice(self), x, y);
    PagedChoice_RequestOpen(choice(self), 0);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_OPENING);
}
CLEAN_AS(func_ov121_0229a568, MyDesigns_OpenChoice)

/* func_ov121_0229ad40: the carried design drawn where the pen is, kept as far from it as it was
 * when touched. */
void MyDesigns_HeldAtPen(MyDesigns *self)
{
    self->held_x = (s16) (self->grab_dx + data_021f6c58);
    self->held_y = (s16) (self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov121_0229ad40, MyDesigns_HeldAtPen)

/* func_ov121_0229ad68: whether the pen has moved more than 16 pixels from where it touched, on
 * either axis. */
int MyDesigns_PenMoved(void)
{
    return distance(data_021f6c60, data_021f6c58) > 0x10 || distance(data_021f6c5c, data_021f6c54) > 0x10;
}
CLEAN_AS(func_ov121_0229ad68, MyDesigns_PenMoved)

/* The bit of place `place` in `disabled`, as the ARM's shift by a register makes it: the
 * shift is the low byte of `place`, and 32 or more shifts the bit out. */
static u32 place_bit(int place)
{
    unsigned int shift = (unsigned int) place & 0xff;
    return shift < 32 ? 1u << shift : 0;
}

/* func_ov121_0229adac: whether place `place` cannot be used (the game passes places, 0-0x18). */
int MyDesigns_IsDisabled(MyDesigns *self, int place)
{
    return (self->disabled & place_bit(place)) != 0;
}
CLEAN_AS(func_ov121_0229adac, MyDesigns_IsDisabled)

/* func_ov121_0229adc0: place `place` cannot be used (the game passes buttons, 9-15). */
void MyDesigns_Disable(MyDesigns *self, int place)
{
    self->disabled |= place_bit(place);
}
CLEAN_AS(func_ov121_0229adc0, MyDesigns_Disable)

/* func_ov121_0229add4: the design or button (0-15) under the carried design, the pen moved by
 * the grab offset; MY_DESIGNS_NO_PLACE for none or one that cannot be used.
 * QUIRK: the point is taken to 8 bits (MyDesigns_PlaceNear's parameters). */
int MyDesigns_PlaceUnderHeld(MyDesigns *self)
{
    int x = data_021f6c58 + self->grab_dx;
    int y = data_021f6c54 + self->grab_dy;
    int place = MyDesigns_PlaceNear(self, (u8) x, (u8) y, MY_DESIGNS_BUTTON_GROUND);
    if (MyDesigns_IsDisabled(self, place) != 0) {
        place = MY_DESIGNS_NO_PLACE;
    }
    return place;
}
CLEAN_AS(func_ov121_0229add4, MyDesigns_PlaceUnderHeld)

/* func_ov121_0229ae18: the design (0-7) under the pen, or MY_DESIGNS_NO_PLACE; for a design,
 * the grab offset is its place less the pen's. */
int MyDesigns_DesignUnderPen(MyDesigns *self)
{
    u8 x = data_021f6c58;
    u8 y = data_021f6c54;
    int place = MyDesigns_PlaceNear(self, x, y, MY_DESIGNS_DESIGN_LAST);
    if (place != MY_DESIGNS_NO_PLACE) {
        self->grab_dx = (s16) (MyDesigns_PlaceX(self, (unsigned int) place) - x);
        self->grab_dy = (s16) (MyDesigns_PlaceY(self, (unsigned int) place) - y);
    }
    return place;
}
CLEAN_AS(func_ov121_0229ae18, MyDesigns_DesignUnderPen)

/* func_ov121_0229ae68: the first of the places 0-`last` less than 16 pixels from (x, y) on both
 * axes (its x checked first), else MY_DESIGNS_NO_PLACE.
 * REQUIRES: `last` is below 0x18 (the game passes 7 and 15). */
int MyDesigns_PlaceNear(MyDesigns *self, unsigned char x, unsigned char y, unsigned int last)
{
    for (unsigned int place = 0; place <= last; place++) {
        int place_x = MyDesigns_PlaceX(self, place);
        if (place_x > x - 0x10 && place_x < x + 0x10) {
            int place_y = MyDesigns_PlaceY(self, place);
            if (place_y > y - 0x10 && place_y < y + 0x10) {
                return (int) place;
            }
        }
    }
    return MY_DESIGNS_NO_PLACE;
}
CLEAN_AS(func_ov121_0229ae68, MyDesigns_PlaceNear)

/* func_ov121_0229aec4: button `place` lit (MY_DESIGNS_NO_PLACE: none), the one lit before made
 * normal; nothing when it is lit already.
 * QUIRK: `highlighted` keeps the low byte of `place`. */
void MyDesigns_Highlight(MyDesigns *self, int place)
{
    u8 before = self->highlighted;
    if (place == before) {
        return;
    }
    if (before != MY_DESIGNS_NO_PLACE) {
        MyDesigns_SetButtonPalette(self, before, MY_DESIGNS_PALETTE_NORMAL);
    }
    self->highlighted = (u8) place;
    if (self->highlighted != MY_DESIGNS_NO_PLACE) {
        MyDesigns_SetButtonPalette(self, self->highlighted, MY_DESIGNS_PALETTE_LIT);
    }
}
CLEAN_AS(func_ov121_0229aec4, MyDesigns_Highlight)

/* func_ov121_0229af00: the 4 by 4 cells of `button` on the buttons' screen in `palette`, the
 * screen to be queued again.
 * REQUIRES: `button` is 9-15 (the tables have seven). */
void MyDesigns_SetButtonPalette(MyDesigns *self, int button, int palette)
{
    int index = button - MY_DESIGNS_BUTTON_FURNITURE;
    int column = data_ov121_0229c218[index];
    int row = data_ov121_0229c228[index];
    ScreenMap_SetPalette(self->screen, column, row, column + 3, row + 3, (u32) palette);
    MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov121_0229af00, MyDesigns_SetButtonPalette)

/* func_ov121_0229af40: the y of place `place`: 8 for the tabs, else the table's.
 * REQUIRES: `place` is 0-0x17. */
int MyDesigns_PlaceY(MyDesigns *self, unsigned int place)
{
    (void) self;
    if (place >= MY_DESIGNS_TAB_FIRST && place <= MY_DESIGNS_TAB_LAST) {
        return 8;
    }
    return data_ov121_0229c238[place];
}
CLEAN_AS(func_ov121_0229af40, MyDesigns_PlaceY)

/* func_ov121_0229af58: the x of place `place`: the tab bar's for the tabs, else the table's.
 * REQUIRES: `place` is 0-0x17. */
int MyDesigns_PlaceX(MyDesigns *self, unsigned int place)
{
    (void) self;
    if (place >= MY_DESIGNS_TAB_FIRST && place <= MY_DESIGNS_TAB_LAST) {
        return MenuTabs_TabX((int) (place - MY_DESIGNS_TAB_FIRST));
    }
    return data_ov121_0229c248[place];
}
CLEAN_AS(func_ov121_0229af58, MyDesigns_PlaceX)

/* func_ov121_0229af7c: error message `message` opened (with `flag`), MY_DESIGNS_SUB_ERROR, the
 * pointer without an animation. */
void MyDesigns_ShowError(MyDesigns *self, char message, int flag)
{
    u8 number = (u8) message;
    ErrorMessage_Open(&self->error, &number, flag, 0);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_ERROR);
    MyDesigns_ResetPointer(self);
}
CLEAN_AS(func_ov121_0229af7c, MyDesigns_ShowError)

/* func_ov121_0229afb8: back to the idle sub state of the mode in use: the pen's while state
 * flag 2 is clear, else the d-pad's. */
unsigned char *MyDesigns_BackToIdle(MyDesigns *self)
{
    if (StateFlags_IsClear2()) {
        return MyDesigns_EnterTouchIdle(self);
    }
    return MyDesigns_EnterKeysIdle(self);
}
CLEAN_AS(func_ov121_0229afb8, MyDesigns_BackToIdle)

/* func_ov121_0229afd8: the d-pad's idle: nothing picked or named, the pointer at the cursor,
 * the key repeat reset, the popup queued for the cursor, MY_DESIGNS_SUB_KEYS. */
unsigned char *MyDesigns_EnterKeysIdle(MyDesigns *self)
{
    self->picked = MY_DESIGNS_NO_PLACE;
    self->hover = MY_DESIGNS_NO_PLACE;
    MyDesigns_ShowPointerAtCursor(self);
    MenuScene_ResetKeyRepeat(scene(self));
    MyDesigns_QueuePopupAtCursor(self);
    return MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_KEYS);
}
CLEAN_AS(func_ov121_0229afd8, MyDesigns_EnterKeysIdle)

/* func_ov121_0229b008: the pen's idle: the pointer without an animation, MY_DESIGNS_SUB_TOUCH. */
unsigned char *MyDesigns_EnterTouchIdle(MyDesigns *self)
{
    MyDesigns_ResetPointer(self);
    return MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_TOUCH);
}
CLEAN_AS(func_ov121_0229b008, MyDesigns_EnterTouchIdle)

/* func_ov121_0229b078 (MY_DESIGNS_SUB_ERROR): once the error message is done, back to idle.
 * Answers 0 while it is up, else the address of the sub state (MyDesigns_BackToIdle's). */
int MyDesigns_WaitError(MyDesigns *self)
{
    int done = ErrorMessage_Update(&self->error, 1);
    if (done != 0) {
        return (int) (uintptr_t) MyDesigns_BackToIdle(self);
    }
    return done;
}
CLEAN_AS(func_ov121_0229b078, MyDesigns_WaitError)

/* func_ov121_0229b0e4 (MY_DESIGNS_SUB_CHOICE_CLOSING): once the choice is closed, the action of
 * the row picked. */
void MyDesigns_WaitChoiceClosed(MyDesigns *self)
{
    if (PagedChoice_IsIdle(choice(self)) != 0) {
        MyDesigns_RunChoiceAction(self);
    }
}
CLEAN_AS(func_ov121_0229b0e4, MyDesigns_WaitChoiceClosed)

/* func_ov121_0229b104 (MY_DESIGNS_SUB_CHOICE_PICKED): once the picked row has been shown, the
 * choice asked to close, the pointer put back at the cursor when it has an animation,
 * MY_DESIGNS_SUB_CHOICE_CLOSING. */
void MyDesigns_ChoicePicked(MyDesigns *self)
{
    if (PagedChoice_CountDown(choice(self)) == 0) {
        return;
    }
    PagedChoice_RequestClose(choice(self), 0);
    if (CellLayerSprite_AnimNumber(pointer_cells(self)) != 0) {
        MyDesigns_PlacePointerAtCursor(self);
    }
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov121_0229b104, MyDesigns_ChoicePicked)

/* func_ov121_0229b148 (MY_DESIGNS_SUB_CHOICE_OPENING): once the choice is shown, its rows by the
 * d-pad (the pointer at the first one) while state flag 2 is set, else by the pen. */
void MyDesigns_WaitChoiceOpen(MyDesigns *self)
{
    if (PagedChoice_IsShown(choice(self)) == 0) {
        return;
    }
    if (StateFlags_Test2()) {
        MyDesigns_PointAtFirstRow(self);
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_KEYS);
    } else {
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_TOUCH);
    }
}
CLEAN_AS(func_ov121_0229b148, MyDesigns_WaitChoiceOpen)

/* The row `row` picked: its action kept, a sound for the room's carpet and wallpaper rows,
 * none at all for the furniture row (the choice's own sound off), MY_DESIGNS_SUB_CHOICE_PICKED. */
static void pick_row(MyDesigns *self, int row)
{
    int sound = 1;
    self->action = MyDesigns_RowAction(self, (unsigned int) row);
    switch (self->action) {
        case MY_DESIGNS_ACTION_CARPET_0:
        case MY_DESIGNS_ACTION_CARPET_1:
        case MY_DESIGNS_ACTION_WALLPAPER_0:
        case MY_DESIGNS_ACTION_WALLPAPER_1:
            SoundSys_PlaySe(MY_DESIGNS_SE_ROW);
            break;
        case MY_DESIGNS_ACTION_FURNITURE:
            sound = 0;
            break;
        default:
            break;
    }
    PagedChoice_PickRowWithSound(choice(self), row, sound);
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_PICKED);
}

/* func_ov121_0229b184 (MY_DESIGNS_SUB_CHOICE_KEY_PRESS): the choice closes when the menu is asked
 * to; else once the pointer's press is over, the chosen row is picked. */
void MyDesigns_ChoiceKeyPress(MyDesigns *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MyDesigns_CloseChoiceOnRequest(self);
        return;
    }
    if (CellLayerSprite_IsDone(pointer_cells(self)) != 0) {
        pick_row(self, self->choice_row);
    }
}
CLEAN_AS(func_ov121_0229b184, MyDesigns_ChoiceKeyPress)

/* func_ov121_0229b214 (MY_DESIGNS_SUB_CHOICE_KEYS): the choice by the d-pad. It closes when the
 * menu is asked to; the pen takes over (MY_DESIGNS_SUB_CHOICE_TOUCH); the d-pad moves the
 * chosen row (the pointer glides to it); A presses it (MY_DESIGNS_SUB_CHOICE_KEY_PRESS), B
 * cancels. */
void MyDesigns_RunChoiceKeys(MyDesigns *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MyDesigns_CloseChoiceOnRequest(self);
        return;
    }
    if (MenuScene_TakeTouch(scene(self)) != 0) {
        MyDesigns_ResetPointer(self);
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_TOUCH);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(scene(self));
    if (PagedChoice_MoveCursor(choice(self), keys, &self->choice_row, 0) != 0) {
        MyDesigns_GlideToChoiceRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & MY_DESIGNS_PAD_A) {
        Glider_ShowSecondOfSet(&self->pointer);
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_KEY_PRESS);
        return;
    }
    if (pressed & MY_DESIGNS_PAD_B) {
        MyDesigns_CancelChoice(self);
    }
}
CLEAN_AS(func_ov121_0229b214, MyDesigns_RunChoiceKeys)

/* func_ov121_0229b2a4 (MY_DESIGNS_SUB_PUT_DOWN): once the pointer's put-down turn has reached its
 * frame 3, the design is no longer carried: put back (MY_DESIGNS_FLAG_PUT_BACK, with its sound)
 * or put down on the cursor (MyDesigns_UseOnTarget); then the d-pad again unless the use goes
 * on.
 * QUIRK: MY_DESIGNS_FLAG_CARRYING is cleared twice when put down. */
void MyDesigns_PutDown(MyDesigns *self)
{
    if (Glider_IsTurnSettled(&self->pointer) != 0) {
        return;
    }
    MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_CARRYING);
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_PUT_BACK) != 0) {
        MyDesigns_QueuePopupAtCursor(self);
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_KEYS);
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_PUT_BACK);
        SoundSys_PlaySe(MY_DESIGNS_SE_PUT_DOWN);
    } else {
        self->target = self->cursor;
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_CARRYING);
        if (MyDesigns_UseOnTarget(self) == 0) {
            MyDesigns_QueuePopupAtCursor(self);
            MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_KEYS);
        }
    }
}
CLEAN_AS(func_ov121_0229b2a4, MyDesigns_PutDown)

/* func_ov121_0229b31c (MY_DESIGNS_SUB_PICKED_UP): once the pointer's animation is done, the
 * cursor carries the design (MY_DESIGNS_SUB_KEYS_CARRY). */
void MyDesigns_PickedUp(MyDesigns *self)
{
    if (CellLayerSprite_IsDone(pointer_cells(self)) != 0) {
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_KEYS_CARRY);
    }
}
CLEAN_AS(func_ov121_0229b31c, MyDesigns_PickedUp)

/* func_ov121_0229b340 (MY_DESIGNS_SUB_PICK_UP): once the pointer's pick-up turn has gone far
 * enough, the design at the cursor is carried, with its sound (MY_DESIGNS_SUB_PICKED_UP). */
void MyDesigns_PickUp(MyDesigns *self)
{
    if (Glider_IsTurnSettled(&self->pointer) != 0) {
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_PICKED_UP);
        self->picked = self->cursor;
        MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_CARRYING);
        SoundSys_PlaySe(MY_DESIGNS_SE_PICK_UP);
    }
}
CLEAN_AS(func_ov121_0229b340, MyDesigns_PickUp)

/* func_ov121_0229b37c (MY_DESIGNS_SUB_TAB_RELEASE): once the pointer's animation is done, its
 * first of the set again and the d-pad (MY_DESIGNS_SUB_KEYS). */
void MyDesigns_TabReleased(MyDesigns *self)
{
    if (CellLayerSprite_IsDone(pointer_cells(self)) != 0) {
        MyDesigns_PointerFirstOfSet(self);
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_KEYS);
    }
}
CLEAN_AS(func_ov121_0229b37c, MyDesigns_TabReleased)

/* func_ov121_0229b3a4 (MY_DESIGNS_SUB_TAB_PRESS): once the pointer's press is over, the menu
 * switches to the cursor's tab; when it does not (this tab), the release plays. */
void MyDesigns_TabPressed(MyDesigns *self)
{
    if (CellLayerSprite_IsDone(pointer_cells(self)) == 0) {
        return;
    }
    int tab = MyDesigns_CursorTab(self);
    if (tab == -1 || MyDesigns_SwitchTab(self, tab) == 0) {
        MyDesigns_BeginTabRelease(self);
    }
}
CLEAN_AS(func_ov121_0229b3a4, MyDesigns_TabPressed)

/* Obj_ov121_0229c3a8::func_ov121_0229b3e0 (MY_DESIGNS_SUB_POINTER_GLIDE): once the pointer stops,
 * `return_sub_state` again, run at once. */
void MyDesigns_WaitPointer(MyDesigns *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(scene(self), self->return_sub_state);
        MyDesigns_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov121_0229c3a819func_ov121_0229b3e0Ev, MyDesigns_WaitPointer)

/* func_ov121_0229b40c (MY_DESIGNS_SUB_KEYS_CARRY): the d-pad's cursor carries a design. When the
 * menu is asked to close it is let go and the menu closes; the d-pad moves the cursor (the
 * pointer glides to it); A puts the design down on a place that can be used, B puts it back
 * (both are looked at). */
void MyDesigns_RunKeysCarry(MyDesigns *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_CARRYING);
        MyDesigns_SwitchTab(self, MY_DESIGNS_TAB_CLOSE);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(scene(self));
    if (MyDesigns_MoveCursor(self, keys, 1) != 0) {
        MyDesigns_GlidePointer(self);
        return;
    }
    if ((data_021fbe40.pressed & MY_DESIGNS_PAD_A) && MyDesigns_IsDisabled(self, self->cursor) == 0) {
        MyDesigns_BeginPutDown(self);
    }
    if (data_021fbe40.pressed & MY_DESIGNS_PAD_B) {
        MyDesigns_BeginPutBack(self);
    }
}
CLEAN_AS(func_ov121_0229b40c, MyDesigns_RunKeysCarry)

/* func_ov121_0229b484 (MY_DESIGNS_SUB_KEYS): the d-pad's cursor. The pen takes over (the popup
 * hidden); the d-pad moves the cursor (the popup queued for it, the pointer gliding); A presses
 * a tab or picks up a design (the popup hidden); R and L switch to the next and previous tab,
 * B closes the menu; else a queued popup is shown.
 * QUIRK: A on a button only hides the popup, then R, L and B are looked at. */
void MyDesigns_RunKeys(MyDesigns *self)
{
    if (MenuScene_TakeTouch(scene(self)) != 0) {
        MyDesigns_EnterTouchIdle(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (MyDesigns_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(scene(self)), 0) != 0) {
        MyDesigns_QueuePopupAtCursor(self);
        MyDesigns_GlidePointer(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (data_021fbe40.pressed & MY_DESIGNS_PAD_A) {
        Popup_Hide(&self->popup, 1);
        if (MyDesigns_CursorTab(self) != -1) {
            MyDesigns_BeginTabPress(self);
            return;
        }
        if (self->cursor <= MY_DESIGNS_DESIGN_LAST) {
            MyDesigns_BeginPickUp(self);
            return;
        }
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & MY_DESIGNS_PAD_R) {
        MyDesigns_SwitchTab(self, MenuTabs_NextTab(MY_DESIGNS_TAB_SELF));
    } else if (pressed & MY_DESIGNS_PAD_L) {
        MyDesigns_SwitchTab(self, MenuTabs_PreviousTab(MY_DESIGNS_TAB_SELF));
    } else if (pressed & MY_DESIGNS_PAD_B) {
        MyDesigns_SwitchTab(self, MY_DESIGNS_TAB_CLOSE);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov121_0229b484, MyDesigns_RunKeys)

/* func_ov121_0229b574 (MY_DESIGNS_SUB_CHOICE_TOUCH): the choice by the pen. It closes when the
 * menu is asked to; the buttons take over (the pointer at the first row, the cursor on the
 * target, MY_DESIGNS_SUB_CHOICE_KEYS); a touch picks the row under the pen (or the last). */
void MyDesigns_RunChoiceTouch(MyDesigns *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MyDesigns_CloseChoiceOnRequest(self);
        return;
    }
    if (MenuScene_TakeButtons(scene(self), 1) != 0) {
        MyDesigns_PointAtFirstRow(self);
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_CHOICE_KEYS);
        self->cursor = self->target;
        return;
    }
    if (pen_pressed()) {
        int row = PagedChoice_RowAtOrLast(choice(self), data_021f6c58, data_021f6c54);
        if (row < 0) {
            return;
        }
        pick_row(self, row);
    }
}
CLEAN_AS(func_ov121_0229b574, MyDesigns_RunChoiceTouch)

/* func_ov121_0229b64c (MY_DESIGNS_SUB_DRAG): the pen carries a design. When the menu is asked to
 * close it is let go (MY_DESIGNS_SUB_TOUCH); when the pen lifts it is put down on the target
 * (back to MY_DESIGNS_SUB_TOUCH unless the use goes on); else the target is the place under it:
 * a button is lit, and the target's mark is drawn on a button, a design or the backdrop's
 * button. */
void MyDesigns_RunDrag(MyDesigns *self)
{
    MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_TARGET_SHOWN);
    if (StateFlags_MenuCloseAsked()) {
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_CARRYING);
        MyDesigns_Highlight(self, MY_DESIGNS_NO_PLACE);
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_TOUCH);
        return;
    }
    if (data_021fbdd8 == 0) {
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_CARRYING);
        MyDesigns_Highlight(self, MY_DESIGNS_NO_PLACE);
        if (MyDesigns_UseOnTarget(self) == 0) {
            MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_TOUCH);
        }
        return;
    }
    self->target = (u8) MyDesigns_PlaceUnderHeld(self);
    if (self->target >= MY_DESIGNS_BUTTON_FURNITURE && self->target <= MY_DESIGNS_BUTTON_GROUND) {
        MyDesigns_Highlight(self, self->target);
        MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_TARGET_SHOWN);
    } else {
        if (self->target <= MY_DESIGNS_BUTTON_BACKDROP) {
            MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_TARGET_SHOWN);
        }
        MyDesigns_Highlight(self, MY_DESIGNS_NO_PLACE);
    }
}
CLEAN_AS(func_ov121_0229b64c, MyDesigns_RunDrag)

/* func_ov121_0229b6f0 (MY_DESIGNS_SUB_TOUCH_HOLD): the pen on a design. When it lifts, back to
 * MY_DESIGNS_SUB_TOUCH with the popup up for 60 frames; when it moves, the design is carried
 * (MY_DESIGNS_SUB_DRAG, the popup hidden, with its sound); else a queued popup is shown. */
void MyDesigns_RunTouchHold(MyDesigns *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_TOUCH);
        Popup_SetTimer(&self->popup, 0x3c);
        return;
    }
    if (MyDesigns_PenMoved() != 0) {
        self->picked = self->hover;
        MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_CARRYING);
        self->target = MY_DESIGNS_NO_PLACE;
        MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_DRAG);
        Popup_Hide(&self->popup, 1);
        SoundSys_PlaySe(MY_DESIGNS_SE_PICK_UP);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov121_0229b6f0, MyDesigns_RunTouchHold)

/* func_ov121_0229b764 (MY_DESIGNS_SUB_TOUCH): the pen's idle. The buttons take over (the d-pad's
 * idle); a touch on a design holds it (MY_DESIGNS_SUB_TOUCH_HOLD), the popup queued to name it,
 * with its sound. */
void MyDesigns_RunTouch(MyDesigns *self)
{
    if (MenuScene_TakeButtons(scene(self), 1) != 0) {
        MyDesigns_EnterKeysIdle(self);
        return;
    }
    if (!pen_pressed()) {
        return;
    }
    int place = MyDesigns_DesignUnderPen(self);
    if (place == MY_DESIGNS_NO_PLACE) {
        return;
    }
    MenuScene_SetSubState(scene(self), MY_DESIGNS_SUB_TOUCH_HOLD);
    self->hover = (u8) place;
    Popup_Queue(&self->popup);
    SoundSys_PlaySe(MY_DESIGNS_SE_TOUCH);
}
CLEAN_AS(func_ov121_0229b764, MyDesigns_RunTouch)

extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

/* func_ov121_0229b7d4: the designs' OBJs on the sub screen: the characters of
 * "menu/desi/b_myd_obj.bch", then the pixels of the player's designs in the order of their
 * places, design n of that order as 4 by 4 tiles at 0xc0 + 4 * n, and their palettes, design
 * n's as palette 4 + n, with the file "menu/desi/b_myd_obj.bpl" after them; both built in
 * blocks from the back of main's heap. */
void MyDesigns_LoadDesignObjs(MyDesigns *self)
{
    (void) self;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov121_0229c408, heap, LAYER_SUB_OBJ, 0x140, 0x140, 0x17f);

    u32 *sheet = Heap_AllocBack(heap, 0x1000);
    PlayerDesigns *designs = PlayerRecord_Designs(PlayerRecords_Current());
    for (u8 i = 0; i < MY_DESIGNS_COUNT; i++) {
        Design *design = (Design *) (uintptr_t) (u32) PlayerDesigns_InOrder(designs, i);
        TileConvert_BitmapToSheet(Design_Pixels(design), sheet, i * 4, 4, 4);
    }
    DisplayLayer_LoadChars((u32) (uintptr_t) sheet, LAYER_SUB_OBJ, 0xc0, 0xc0, 0x13f);
    Heap_Free(heap, sheet);

    u16 *palettes = Heap_AllocBack(heap, 0x120);
    for (u8 i = 0; i < MY_DESIGNS_COUNT; i++) {
        unsigned int design = (unsigned int) PlayerDesigns_InOrder(designs, i);
        DesignInfo *info = (DesignInfo *) (uintptr_t) Design_Info(design);
        const void *colours = (const void *) (uintptr_t) (u32) DesignInfo_PaletteColours(info);
        MIi_CpuCopy16(colours, palettes + i * 0x10, 0x20);
    }
    RomFile_Read(data_ov121_0229c420, palettes + MY_DESIGNS_COUNT * 0x10, 0x20);
    DisplayLayer_LoadPalettes((u8 *) palettes, LAYER_SUB_OBJ, 4, 4, 0xc);
    Heap_Free(heap, palettes);
}
CLEAN_AS(func_ov121_0229b7d4, MyDesigns_LoadDesignObjs)

/* func_ov121_0229b8c0: the buttons' layer: "menu/desi/b_myd_bg.bpl" and ".bch" loaded, the
 * screen "menu/desi/b_myd_a_bg.bsc" read into `screen`, the buttons that cannot be used drawn
 * in their palette, the screen to be queued. */
void MyDesigns_LoadButtons(MyDesigns *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov121_0229c438, heap, MY_DESIGNS_LAYER, 1, 1, 7);
    DisplayLayer_LoadCharsFromFile(data_ov121_0229c450, heap, MY_DESIGNS_LAYER, 0x10, 0x10, 0xc5);
    RomFile_Read(data_ov121_0229c468, self->screen, sizeof(self->screen));
    for (u8 button = MY_DESIGNS_BUTTON_FURNITURE; button <= MY_DESIGNS_BUTTON_GROUND; button++) {
        if (MyDesigns_IsDisabled(self, button) != 0) {
            MyDesigns_SetButtonPalette(self, button, MY_DESIGNS_PALETTE_DISABLED);
        }
    }
    MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov121_0229b8c0, MyDesigns_LoadButtons)

/* func_ov121_0229b948: the buttons' layer at priority 2, in BG control 0. */
void MyDesigns_SetUpLayer(void)
{
    DisplayLayer_SetPriority(MY_DESIGNS_LAYER, 2);
    DisplayLayer_SetBgControl(MY_DESIGNS_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov121_0229b948, MyDesigns_SetUpLayer)

/* func_ov121_0229b968 (each frame, after the states or the sub state): the blinking stepped, a
 * changed buttons' screen queued (until the queue takes it), the popup updated (its text set when
 * it asks) and the choice updated. */
void MyDesigns_Update(MyDesigns *self)
{
    MyDesigns_StepBlink(self);
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_SCREEN_DIRTY) != 0 &&
        LayerTask_QueueScreen(&self->tasks[0].first, (int) (uintptr_t) self->screen, MY_DESIGNS_LAYER, sizeof(self->screen),
                              0) != 0) {
        MyDesigns_ClearFlags(self, MY_DESIGNS_FLAG_SCREEN_DIRTY);
    }
    if (Popup_Update(&self->popup) != 0) {
        MyDesigns_SetPopupText(self);
    }
    PagedChoice_Update(choice(self));
}
CLEAN_AS(func_ov121_0229b968, MyDesigns_Update)

/* func_ov121_0229b9d4: nothing (called before the states and the sub states). */
void MyDesigns_Nothing(void *self)
{
    (void) self;
}
CLEAN_AS(func_ov121_0229b9d4, MyDesigns_Nothing)

/* func_ov121_0229b9d8: MyDesigns_Update. */
void MyDesigns_UpdateAfterSubState(MyDesigns *self)
{
    MyDesigns_Update(self);
}
CLEAN_AS(func_ov121_0229b9d8, MyDesigns_UpdateAfterSubState)

/* func_ov121_0229b9e0: MyDesigns_Nothing, then the pointer updated through its class (vtable
 * slot 3). */
void MyDesigns_UpdatePointerFirst(MyDesigns *self)
{
    MyDesigns_Nothing(self);
    call_slot(&self->pointer, 3);
}
CLEAN_AS(func_ov121_0229b9e0, MyDesigns_UpdatePointerFirst)

/* func_ov121_0229b9fc: what the members hold let go: the choice dismissed, both layer tasks
 * ended. */
void MyDesigns_Release(MyDesigns *self)
{
    PagedChoice_Dismiss(choice(self));
    LayerTask_End(&self->tasks[0].first);
    LayerTask_End(&self->tasks[1].first);
}
CLEAN_AS(func_ov121_0229b9fc, MyDesigns_Release)

/* func_ov121_0229ba60: the setup: the designs in their places, no flags, the buttons that cannot
 * be used where the player is (MyDesignsWhere), the choice on the sub screen's background 0
 * (priority 1), no button lit and the cursor on design 0. */
void MyDesigns_Setup(MyDesigns *self)
{
    for (u8 i = 0; i < MY_DESIGNS_COUNT; i++) {
        self->order[i] = i;
    }
    self->flags = 0;
    self->disabled = 0;
    if (data_020e54a8 == 0) {
        self->where = MY_DESIGNS_OUTSIDE;
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_FURNITURE);
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_CARPET);
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_WALLPAPER);
        NetSession *session = data_020ccf94;
        if (Session_IsLinked(session) != 0 && session->local_slot != 0) {
            MyDesigns_Disable(self, MY_DESIGNS_BUTTON_GROUND);
        }
    } else if (MyDesigns_InOwnRoom(self) != 0) {
        self->where = MY_DESIGNS_OWN_ROOM;
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_GROUND);
    } else {
        self->where = MY_DESIGNS_ROOM;
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_FURNITURE);
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_CARPET);
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_WALLPAPER);
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_HELD);
        MyDesigns_Disable(self, MY_DESIGNS_BUTTON_GROUND);
    }
    PagedChoice_Init(choice(self), LAYER_SUB_BG0, 1, NULL);
    self->highlighted = MY_DESIGNS_NO_PLACE;
    self->cursor = MY_DESIGNS_DESIGN_FIRST;
}
CLEAN_AS(func_ov121_0229ba60, MyDesigns_Setup)

/* The buttons' layer follows the wipe, whose y is kept for the designs. */
static void follow_wipe(MyDesigns *self)
{
    MenuScene_ScrollWipe(scene(self), MY_DESIGNS_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(scene(self));
}

/* func_ov121_0229bb54 (MY_DESIGNS_STATE_WIPE_OUT): the scene wipes out; when done, the buttons'
 * layer hidden and its scroll reset, phase 5. */
void MyDesigns_WipeOut(MyDesigns *self)
{
    if (MenuScene_StepWipe(scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(MY_DESIGNS_LAYER);
        MenuScene_SetPhase(scene(self), MY_DESIGNS_PHASE_DELETE);
    } else {
        follow_wipe(self);
    }
}
CLEAN_AS(func_ov121_0229bb54, MyDesigns_WipeOut)

/* func_ov121_0229bb90 (MY_DESIGNS_STATE_LEAVE): the pointer without an animation, the scene
 * starts to wipe out on window 2 (state 3). */
void MyDesigns_StartWipeOut(MyDesigns *self)
{
    MyDesigns_ResetPointer(self);
    MenuScene_StartWipeOnWindow2(scene(self), 8, 0, 0, MY_DESIGNS_WIPE_MARGIN);
    MenuScene_SetState(scene(self), MY_DESIGNS_STATE_WIPE_OUT);
    follow_wipe(self);
}
CLEAN_AS(func_ov121_0229bb90, MyDesigns_StartWipeOut)

/* func_ov121_0229bbd0 (MY_DESIGNS_STATE_WIPE_IN): the scene wipes in; when done, phase 2 and the
 * idle sub state. */
void MyDesigns_WipeIn(MyDesigns *self)
{
    if (MenuScene_StepWipeBack(scene(self), 0) != 0) {
        MenuScene_SetPhase(scene(self), MY_DESIGNS_PHASE_INTERACTIVE);
        MyDesigns_BackToIdle(self);
    }
    follow_wipe(self);
}
CLEAN_AS(func_ov121_0229bbd0, MyDesigns_WipeIn)

/* func_ov121_0229bc08 (MY_DESIGNS_STATE_START): the buttons' layer set up and loaded, the
 * designs' OBJs and the choice's graphics loaded, the layer shown and wiping in on window 2
 * (state 1); the scene is drawn from now on. */
void MyDesigns_StartWipeIn(MyDesigns *self)
{
    MyDesigns_SetUpLayer();
    MyDesigns_LoadButtons(self);
    MyDesigns_LoadDesignObjs(self);
    PagedChoice_LoadChoiceGraphics(choice(self));
    MenuScene_StartWipeCoveredOnWindow2(scene(self), 8, 0, 0, MY_DESIGNS_WIPE_MARGIN);
    DisplayLayer_Show(MY_DESIGNS_LAYER);
    MenuScene_SetState(scene(self), MY_DESIGNS_STATE_WIPE_IN);
    MyDesigns_SetFlags(self, MY_DESIGNS_FLAG_SHOWN);
    follow_wipe(self);
}
CLEAN_AS(func_ov121_0229bc08, MyDesigns_StartWipeIn)

/* func_ov121_0229bc70: the menu switches to `tab` (MY_DESIGNS_TAB_CLOSE closes it): the parent
 * told, the scene wipes out (state 2) after phase 1, the popup hidden, and but for closing the
 * camera's view put back. Whether it switched: not for no tab or this one.
 * QUIRK: the parent is asked for before the tab is checked, and gets the tab's low byte. */
int MyDesigns_SwitchTab(MyDesigns *self, int tab)
{
    MenuTabs *parent = parent_tabs(self);
    if (tab == MY_DESIGNS_TAB_NONE || tab == MY_DESIGNS_TAB_SELF) {
        return 0;
    }
    MenuTabs_SelectTab(parent, (u8) tab);
    self->base.state = MY_DESIGNS_STATE_LEAVE;
    MenuScene_SetPhase(scene(self), MY_DESIGNS_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    if (tab != MY_DESIGNS_TAB_CLOSE) {
        MyDesigns_RestoreCamera(self);
    }
    return 1;
}
CLEAN_AS(func_ov121_0229bc70, MyDesigns_SwitchTab)

/* func_ov121_0229bcc8: the menu close's delay counted. When main asked the menu to close in a
 * sub state that may be left (the idles, the pen on a design, A on a tab), it closes. In the two
 * idles another tab may be asked for: by the pen on the tab bar while state flag 2 is clear,
 * else Y for the pockets, X for tab 5 and SELECT for tab 4. Whether the menu switched. */
int MyDesigns_CloseOrSwitchOnRequest(MyDesigns *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        switch (self->base.sub_state) {
            case MY_DESIGNS_SUB_TOUCH:
            case MY_DESIGNS_SUB_TOUCH_HOLD:
            case MY_DESIGNS_SUB_KEYS:
            case MY_DESIGNS_SUB_TAB_PRESS:
            case MY_DESIGNS_SUB_TAB_RELEASE:
                return MyDesigns_SwitchTab(self, MY_DESIGNS_TAB_CLOSE);
            default:
                break;
        }
    }
    if (self->base.sub_state != MY_DESIGNS_SUB_TOUCH && self->base.sub_state != MY_DESIGNS_SUB_KEYS) {
        return 0;
    }
    int tab = MY_DESIGNS_TAB_NONE;
    if (StateFlags_IsClear2()) {
        tab = MenuTabs_TabAtTouch();
    } else {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & MY_DESIGNS_PAD_Y) {
            tab = MY_DESIGNS_TAB_POCKETS;
        } else if (pressed & MY_DESIGNS_PAD_X) {
            tab = MY_DESIGNS_TAB_5;
        } else if (pressed & MY_DESIGNS_PAD_SELECT) {
            tab = MY_DESIGNS_TAB_4;
        }
    }
    return MyDesigns_SwitchTab(self, tab);
}
CLEAN_AS(func_ov121_0229bcc8, MyDesigns_CloseOrSwitchOnRequest)

/* func_ov121_0229bd7c (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int MyDesigns_End(MyDesigns *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov121_0229bd7c, MyDesigns_End)

/* func_ov121_0229bd8c (vtable slot 0x58, phase 4): nothing. */
int MyDesigns_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov121_0229bd8c, MyDesigns_Phase4)

/* func_ov121_0229bd90 (vtable slot 0x54, phase 3): nothing. */
int MyDesigns_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov121_0229bd90, MyDesigns_Phase3)

/* Obj_ov121_0229c3a8::func_ov121_0229bd94 (vtable slot 0x50, phase 2): a frame of the scene in
 * use, unless the menu closes or switches tabs: the pointer updated, the sub state, then the
 * scene's update. Answers 1. */
int MyDesigns_RunInteractive(MyDesigns *self)
{
    if (MyDesigns_CloseOrSwitchOnRequest(self) != 0) {
        return 1;
    }
    MyDesigns_UpdatePointerFirst(self);
    MyDesigns_RunSubState(self);
    MyDesigns_UpdateAfterSubState(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov121_0229c3a819func_ov121_0229bd94Ev, MyDesigns_RunInteractive)

/* Obj_ov121_0229c3a8::func_ov121_0229bdc0: the sub state's function (MyDesignsSubState) through
 * the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 21; the game reads past the table for others. */
void MyDesigns_RunSubState(MyDesigns *self)
{
    static const MemberPointer *const sub_states[MY_DESIGNS_SUB_STATES] = {
        &data_ov121_0229c370, &data_ov121_0229c368, &data_ov121_0229c360, &data_ov121_0229c358, &data_ov121_0229c350,
        &data_ov121_0229c348, &data_ov121_0229c340, &data_ov121_0229c2d8, &data_ov121_0229c330, &data_ov121_0229c328,
        &data_ov121_0229c320, &data_ov121_0229c318, &data_ov121_0229c310, &data_ov121_0229c308, &data_ov121_0229c2c8,
        &data_ov121_0229c2f8, &data_ov121_0229c2f0, &data_ov121_0229c2e8, &data_ov121_0229c2e0, &data_ov121_0229c2b0,
        &data_ov121_0229c2d0,
    };
    MemberTable_InitOnce(&data_ov121_0229c4a0, data_ov121_0229c4c8, sub_states, MY_DESIGNS_SUB_STATES);
    MemberPointer_CallVoid(&data_ov121_0229c4c8[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov121_0229c3a819func_ov121_0229bdc0Ev, MyDesigns_RunSubState)

/* func_ov121_0229bf38 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (MyDesignsState) through the table of member functions (filled once from its constants),
 * after MyDesigns_Nothing and before the scene's update. Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int MyDesigns_RunState(MyDesigns *self)
{
    static const MemberPointer *const states[MY_DESIGNS_STATES] = {
        &data_ov121_0229c338,
        &data_ov121_0229c2a8,
        &data_ov121_0229c2a0,
        &data_ov121_0229c378,
    };
    MemberTable_InitOnce(&data_ov121_0229c4a4, data_ov121_0229c4a8, states, MY_DESIGNS_STATES);
    MyDesigns_Nothing(self);
    MemberPointer_CallVoid(&data_ov121_0229c4a8[self->base.state], self);
    MyDesigns_Update(self);
    return 1;
}
CLEAN_AS(func_ov121_0229bf38, MyDesigns_RunState)

/* The designs' OBJ set to design `design`'s tiles (0xc0 + 4 * design; the other bits of its
 * third attribute kept). */
static void set_design_tiles(u8 design)
{
    u16 tile = (u16) ((design * 4 + 0xc0) & 0x3ff);
    data_ov121_0229c2c0.attr2 = (u16) ((data_ov121_0229c2c0.attr2 & ~0x3ffu) | tile);
}

/* func_ov121_0229bfcc (vtable slot 0x24): the scene's draw, once it is shown: the popup through
 * its class (slot 2), the pointer while state flag 2 is set, the choice; the carried design at
 * the pointer (state flag 2) or at the pen; the target's mark; then the designs at their places
 * (but the carried one), wipe_y pixels down, each with its tiles and palette 4 + its design.
 * Answers 1. */
int MyDesigns_Draw(MyDesigns *self)
{
    int wipe_y = self->wipe_y;
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_SHOWN) == 0) {
        return 1;
    }
    call_slot(&self->popup, 2);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->pointer);
    }
    PagedChoice_Draw(choice(self));

    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_CARRYING) != 0) {
        if (StateFlags_Test2()) {
            MyDesigns_HeldAtPointer(self);
        } else {
            MyDesigns_HeldAtPen(self);
        }
        u8 design = self->order[self->picked];
        set_design_tiles(design);
        OamBuffer_DrawObjAffine(1, &data_ov121_0229c2c0, self->held_x, self->held_y, self->order[self->picked] + 4, 2, NULL);
    }
    if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_TARGET_SHOWN) != 0) {
        u8 target = self->target;
        int y = wipe_y + MyDesigns_PlaceY(self, target);
        OamBuffer_DrawCell(1, data_ov121_0229c380, MyDesigns_PlaceX(self, target), y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    for (u8 place = 0; place < MY_DESIGNS_COUNT; place++) {
        if (MyDesigns_TestFlags(self, MY_DESIGNS_FLAG_CARRYING) != 0 && place == self->picked) {
            continue;
        }
        set_design_tiles(self->order[place]);
        int palette = self->order[place] + 4;
        int y = wipe_y + MyDesigns_PlaceY(self, place);
        OamBuffer_DrawObjAffine(1, &data_ov121_0229c2c0, MyDesigns_PlaceX(self, place), y, palette, 2, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov121_0229bfcc, MyDesigns_Draw)

/* func_ov121_0229c160 (vtable slot 0x0c): the scene closes: the parent told, then what the
 * members hold let go. Answers 1. */
int MyDesigns_Close(MyDesigns *self)
{
    MenuTabs_ChildClosed(parent_tabs(self));
    MyDesigns_Release(self);
    return 1;
}
CLEAN_AS(func_ov121_0229c160, MyDesigns_Close)

/* func_ov121_0229c17c (vtable slot 0x00): the scene starts: its setup, state 0 and phase 1.
 * Answers 1. */
int MyDesigns_Begin(MyDesigns *self)
{
    MyDesigns_Setup(self);
    MenuScene_SetState(scene(self), MY_DESIGNS_STATE_START);
    MenuScene_SetPhase(scene(self), MY_DESIGNS_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov121_0229c17c, MyDesigns_Begin)

/* func_ov121_0229c19c (named by the profile at 0x0229c300): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the two layer tasks last. */
MyDesigns *MyDesigns_New(void)
{
    MyDesigns *self = MenuScene_Alloc(sizeof(MyDesigns));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov121_0229c3a8;
    Popup_Construct(&self->popup);
    Glider0_Construct(&self->pointer);
    ErrorMessage_Construct(&self->error);
    PagedChoice_Construct(choice(self));
    for (int i = 0; i < 2; i++) {
        LayerTask_ConstructPair(&self->tasks[i]);
    }
    return self;
}
CLEAN_AS(func_ov121_0229c19c, MyDesigns_New)
