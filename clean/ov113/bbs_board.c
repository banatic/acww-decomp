/* The bulletin board scene of overlay 113 (bbs_board.h): its destructors, the cursor and its
 * moves, the actions, a post's display, the states and sub states and the vtable's slots. */
#include "bbs_board.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/bbs.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/letter_view.h"
#include "main/oam_buffer.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_base.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(BbsBoard, wipe_y) == 0x94, "wipe_y");
static_assert(offsetof(BbsBoard, flags) == 0x98 && offsetof(BbsBoard, post) == 0x9a, "flags");
static_assert(offsetof(BbsBoard, cursor) == 0x9b && offsetof(BbsBoard, tabs_x) == 0x9e, "bytes");
static_assert(offsetof(BbsBoard, screen) == 0xa0 && offsetof(BbsBoard, line_chars) == 0x8a0, "screen");
static_assert(offsetof(BbsBoard, chars_task) == 0x26a0 && offsetof(BbsBoard, screen_task) == 0x26c4, "tasks");
static_assert(sizeof(LayerTask) == 0x24 && sizeof(TextLabel) == 0x6c, "members");
static_assert(offsetof(BbsBoard, labels) == 0x26e8 && offsetof(BbsBoard, lines) == 0x2898, "labels");
static_assert(offsetof(BbsBoard, cursor_sprite) == 0x2b20, "cursor sprite");
static_assert(sizeof(BbsBoard) == 0x2b84, "size (func_ov113_0229aae4)");

/* The scene's vtable. */
extern const u8 data_ov113_0229ac00[];

/* The town's bulletin board (main/bbs.h). */
extern Bbs data_021eed68;

/* The keys (autoload_2/input.h), the pen (ov002/menu_scene.c) and the touch's place (main's
 * bytes, as ov099's pockets_view.c reads them). */
extern PadState data_021fbe40;
#define BBS_BOARD_PAD_A 0x001
#define BBS_BOARD_PAD_B 0x002
#define BBS_BOARD_PAD_R 0x100
#define BBS_BOARD_PAD_L 0x200
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* The scene heap. */
extern Heap *data_021fbe94;

/* The background's files. */
extern const char data_ov113_0229ad18[]; /* "menu/bbs/b_bbs.bpl" */
extern const char data_ov113_0229ad2c[]; /* "menu/bbs/b_bbs.bsc" */
extern const char data_ov113_0229ad40[]; /* "menu/bbs/b_bbs.bch" */

/* The cells: the right arrow (4 OBJs), the left arrow (4 OBJs), then the tab of each of the
 * 15 posts (one OBJ each, 8 pixels apart). */
extern const OamEntry data_ov113_0229ac60[];
extern const OamEntry data_ov113_0229ac80[];
#define BBS_BOARD_FIRST_TAB_OBJ 8 /* the tabs' OBJs follow the arrows' in data_ov113_0229ac60 */

/* The text labels' constructor and destructor, handed to __cxa_vec_ctor and __cxa_vec_cleanup
 * (so the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);

/* The SDK's brightness and blend setting (main/display_shadow.c calls it too). */
extern void G2x_SetBlendBrightnessExt_(u32 reg, u32 planes, u32 second_planes, u32 ev, u32 second_ev, u32 brightness);
#define BBS_BOARD_REG_BLDCNT 0x04000050u

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov113_0229ad60; /* the states' guard */
extern u32 data_ov113_0229ad64; /* the sub states' guard */
extern MemberPointer data_ov113_0229ad68[BBS_BOARD_SUB_STATES];
extern MemberPointer data_ov113_0229ad90[BBS_BOARD_STATES];
extern const MemberPointer data_ov113_0229ab80; /* BbsBoard_Open */
extern const MemberPointer data_ov113_0229ab90; /* BbsBoard_WaitGlide */
extern const MemberPointer data_ov113_0229ab98; /* BbsBoard_UpdateKeys */
extern const MemberPointer data_ov113_0229aba0; /* BbsBoard_ShowFirstPost */
extern const MemberPointer data_ov113_0229aba8; /* BbsBoard_WipeIn */
extern const MemberPointer data_ov113_0229abb0; /* BbsBoard_WaitPress */
extern const MemberPointer data_ov113_0229abb8; /* BbsBoard_TurnIn */
extern const MemberPointer data_ov113_0229abc0; /* BbsBoard_TurnShow */
extern const MemberPointer data_ov113_0229abc8; /* BbsBoard_TurnOut */
extern const MemberPointer data_ov113_0229abd0; /* BbsBoard_StartTurn */
extern const MemberPointer data_ov113_0229abd8; /* BbsBoard_WipeOut */
extern const MemberPointer data_ov113_0229abe0; /* BbsBoard_StartWipeOut */
extern const MemberPointer data_ov113_0229abe8; /* BbsBoard_UpdateTouch */
extern const MemberPointer data_ov113_0229abf0; /* BbsBoard_WaitRelease */

/* The sounds. */
#define BBS_BOARD_SE_WRITE 0x29     /* the write button */
#define BBS_BOARD_SE_QUIT 0x12      /* the quit button */
#define BBS_BOARD_SE_TAB 0x0b       /* the cursor moves between tabs */
#define BBS_BOARD_SE_TURN_ENDS 0x3c /* the page turns to the oldest or the newest post */
#define BBS_BOARD_SE_TURN 0x39      /* the page turns otherwise */

/* The full-width digits '0'-'9' are 0xff10-0xff19. */
#define BBS_BOARD_DIGIT_0 0xff10

static MenuScene *bbs_scene(BbsBoard *self)
{
    return &self->base;
}

static Process *bbs_parent(BbsBoard *self)
{
    return Process_GetParent((Process *) (void *) self);
}

static CellLayerSprite *bbs_cursor_cells(BbsBoard *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void bbs_update_cursor_sprite(BbsBoard *self)
{
    const u32 *vtable = (const u32 *) self->cursor_sprite.vtable;
    ((void (*)(Glider *))(uintptr_t) vtable[3])(&self->cursor_sprite);
}

/* The scene's sound: the menu sounds of main (main/sound.h). */
static void bbs_play(int sound)
{
    SoundSys_PlaySe(sound);
}

/* func_ov113_022995a0 (vtable slot 0x40) */
BbsBoard *BbsBoard_Destroy(BbsBoard *self)
{
    self->base.vtable = data_ov113_0229ac00;
    Glider1_Destroy(&self->cursor_sprite);
    __cxa_vec_cleanup(self->lines, BBS_BOARD_LINES, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    __cxa_vec_cleanup(self->labels, BBS_BOARD_DATE_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    MenuScene_DestroyBase(bbs_scene(self));
    return self;
}
CLEAN_AS(func_ov113_022995a0, BbsBoard_Destroy)

/* func_ov113_022995f0 (vtable slot 0x44) */
BbsBoard *BbsBoard_Delete(BbsBoard *self)
{
    self->base.vtable = data_ov113_0229ac00;
    Glider1_Destroy(&self->cursor_sprite);
    __cxa_vec_cleanup(self->lines, BBS_BOARD_LINES, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    __cxa_vec_cleanup(self->labels, BBS_BOARD_DATE_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    MenuScene_DestroyBase(bbs_scene(self));
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov113_022995f0, BbsBoard_Delete)

/* The cursor moves from a post's tab up or down: to the right arrow or the write button when
 * right is held, or when the cursor sprite is on the right half and left is not held; else to
 * the left arrow or the newest button. */
static int bbs_from_tab_goes_right(BbsBoard *self, u32 keys)
{
    return KeyRepeat_HasRight((int) keys) != 0 ||
           (Glider_FrameX(&self->cursor_sprite) > 0x80 && KeyRepeat_HasLeft((int) keys) == 0);
}

/* func_ov113_02299644: the cursor moved by the d-pad's repeated `keys`; whether it moved.
 *
 * - Among the buttons, left and right go round the four (past either end, the sprite's next
 *   place is 256 pixels to that side, BbsBoard_CursorX); up goes to the tab under the sprite.
 * - From the left arrow, down goes to the first tab and left or right to the right arrow (left
 *   wrapping); from the right arrow, down goes to the last tab and left or right to the left
 *   arrow (right wrapping).
 * - Among the tabs, up goes to an arrow and down to a button (bbs_from_tab_goes_right); left and
 *   right step a tab (with sound 0x0b, the sprite put there at once), past the ends to the
 *   arrows.
 * The keys are tested in the order left, right, up for the buttons, down, left, right for the
 * arrows and up, down, left, right for the tabs, the first held one taken. */
int BbsBoard_MoveCursor(BbsBoard *self, u32 keys)
{
    unsigned int was = self->cursor;
    int ikeys = (int) keys;

    if (was <= BBS_BOARD_CURSOR_QUIT) {
        if (KeyRepeat_HasLeft(ikeys) != 0) {
            if (self->cursor != 0) {
                self->cursor--;
            } else {
                self->cursor = BBS_BOARD_CURSOR_QUIT;
                BbsBoard_SetFlags(self, BBS_BOARD_FLAG_WRAP_LEFT);
            }
        } else if (KeyRepeat_HasRight(ikeys) != 0) {
            if (self->cursor < BBS_BOARD_CURSOR_QUIT) {
                self->cursor++;
            } else {
                self->cursor = BBS_BOARD_CURSOR_OLDEST;
                BbsBoard_SetFlags(self, BBS_BOARD_FLAG_WRAP_RIGHT);
            }
        } else if (KeyRepeat_HasUp(ikeys) != 0) {
            int first_x = self->tabs_x + 0x44;
            int dx = Glider_FrameX(&self->cursor_sprite) - first_x;
            if (dx < 0) {
                dx = 0;
            }
            int tab = dx / 8;
            if (tab >= self->posts) {
                /* QUIRK: with no post, tab -1 makes the cursor the left arrow */
                tab = self->posts - 1;
            }
            self->cursor = (u8) (tab + BBS_BOARD_CURSOR_TAB);
        }
    } else if (was == BBS_BOARD_CURSOR_OLDER) {
        if (KeyRepeat_HasDown(ikeys) != 0) {
            self->cursor = BBS_BOARD_CURSOR_TAB;
        } else if (KeyRepeat_HasLeft(ikeys) != 0) {
            self->cursor = BBS_BOARD_CURSOR_NEWER;
            BbsBoard_SetFlags(self, BBS_BOARD_FLAG_WRAP_LEFT);
        } else if (KeyRepeat_HasRight(ikeys) != 0) {
            self->cursor = BBS_BOARD_CURSOR_NEWER;
        }
    } else if (was == BBS_BOARD_CURSOR_NEWER) {
        if (KeyRepeat_HasDown(ikeys) != 0) {
            self->cursor = (u8) (self->posts + BBS_BOARD_CURSOR_TAB - 1);
        } else if (KeyRepeat_HasLeft(ikeys) != 0) {
            self->cursor = BBS_BOARD_CURSOR_OLDER;
        } else if (KeyRepeat_HasRight(ikeys) != 0) {
            self->cursor = BBS_BOARD_CURSOR_OLDER;
            BbsBoard_SetFlags(self, BBS_BOARD_FLAG_WRAP_RIGHT);
        }
    } else if (was <= BBS_BOARD_CURSOR_LAST_TAB) {
        if (KeyRepeat_HasUp(ikeys) != 0) {
            self->cursor = bbs_from_tab_goes_right(self, keys) ? BBS_BOARD_CURSOR_NEWER : BBS_BOARD_CURSOR_OLDER;
        } else if (KeyRepeat_HasDown(ikeys) != 0) {
            self->cursor = bbs_from_tab_goes_right(self, keys) ? BBS_BOARD_CURSOR_WRITE : BBS_BOARD_CURSOR_NEWEST;
        } else if (KeyRepeat_HasLeft(ikeys) != 0) {
            if (self->cursor > BBS_BOARD_CURSOR_TAB) {
                self->cursor--;
                BbsBoard_SetFlags(self, BBS_BOARD_FLAG_SNAP);
                bbs_play(BBS_BOARD_SE_TAB);
            } else {
                self->cursor = BBS_BOARD_CURSOR_OLDER;
            }
        } else if (KeyRepeat_HasRight(ikeys) != 0) {
            if (self->cursor + 1 < self->posts + BBS_BOARD_CURSOR_TAB) {
                self->cursor++;
                BbsBoard_SetFlags(self, BBS_BOARD_FLAG_SNAP);
                bbs_play(BBS_BOARD_SE_TAB);
            } else {
                self->cursor = BBS_BOARD_CURSOR_NEWER;
            }
        }
    }
    return self->cursor != was;
}
CLEAN_AS(func_ov113_02299644, BbsBoard_MoveCursor)

/* func_ov113_022998ac: the cursor sprite shows the first of its set, then is updated. */
void BbsBoard_ShowCursorFirstOfSet(BbsBoard *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    bbs_update_cursor_sprite(self);
}
CLEAN_AS(func_ov113_022998ac, BbsBoard_ShowCursorFirstOfSet)

/* func_ov113_022998cc: a press that did nothing: the cursor sprite shows the third of its set
 * and the scene waits for it (sub state 4). */
void BbsBoard_CancelPress(BbsBoard *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(bbs_scene(self), BBS_BOARD_SUB_RELEASE);
}
CLEAN_AS(func_ov113_022998cc, BbsBoard_CancelPress)

/* func_ov113_022998ec: A pressed: the cursor sprite shows the second of its set and the scene
 * waits for it (sub state 3). */
void BbsBoard_Press(BbsBoard *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(bbs_scene(self), BBS_BOARD_SUB_PRESS);
}
CLEAN_AS(func_ov113_022998ec, BbsBoard_Press)

/* func_ov113_0229990c: the cursor moved: with BBS_BOARD_FLAG_SNAP the sprite is put at the
 * cursor's place (and the flag cleared); else it eases there in 4 steps (cue 1) while the scene
 * waits in sub state 2, coming back to the current sub state. */
void BbsBoard_CursorMoved(BbsBoard *self)
{
    if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_SNAP) != 0) {
        int x = BbsBoard_CursorX(self);
        int y = BbsBoard_CursorY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_SNAP);
    } else {
        int x = BbsBoard_CursorX(self);
        int y = BbsBoard_CursorY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 4, 1);
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(bbs_scene(self), BBS_BOARD_SUB_GLIDE);
    }
}
CLEAN_AS(func_ov113_0229990c, BbsBoard_CursorMoved)

/* func_ov113_02299980: the cursor sprite hidden (animation 0), then updated. */
void BbsBoard_HideCursor(BbsBoard *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    bbs_update_cursor_sprite(self);
}
CLEAN_AS(func_ov113_02299980, BbsBoard_HideCursor)

/* func_ov113_022999a4: the cursor sprite's y: the buttons' row, the arrows', the tabs'. */
u8 BbsBoard_CursorY(BbsBoard *self)
{
    u8 cursor = self->cursor;
    if (cursor <= BBS_BOARD_CURSOR_QUIT) {
        return 0xaa;
    }
    if (cursor <= BBS_BOARD_CURSOR_OLDER) {
        return 0x56;
    }
    if (cursor <= BBS_BOARD_CURSOR_LAST_TAB) {
        return 0x98;
    }
    return 0x60;
}
CLEAN_AS(func_ov113_022999a4, BbsBoard_CursorY)

/* func_ov113_022999c4: the cursor sprite's x (BbsBoard_CursorBaseX), 256 pixels to the left or
 * right after a wrap (BBS_BOARD_FLAG_WRAP_LEFT, then _RIGHT); both flags cleared. */
int BbsBoard_CursorX(BbsBoard *self)
{
    int x = BbsBoard_CursorBaseX(self);
    if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_WRAP_LEFT) != 0) {
        x -= 0x100;
    } else if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_WRAP_RIGHT) != 0) {
        x += 0x100;
    }
    BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_WRAP_LEFT | BBS_BOARD_FLAG_WRAP_RIGHT);
    return x;
}
CLEAN_AS(func_ov113_022999c4, BbsBoard_CursorX)

/* func_ov113_02299a08: the x of the cursor's place: the buttons 48 pixels apart from 0x47, the
 * left arrow at 0x10, the right one at 0xf0, the tabs 8 pixels apart from tabs_x + 0x48. */
int BbsBoard_CursorBaseX(BbsBoard *self)
{
    u8 cursor = self->cursor;
    if (cursor <= BBS_BOARD_CURSOR_QUIT) {
        return 0x30 * cursor + 0x47;
    }
    if (cursor == BBS_BOARD_CURSOR_OLDER) {
        return 0x10;
    }
    if (cursor == BBS_BOARD_CURSOR_NEWER) {
        return 0xf0;
    }
    if (cursor <= BBS_BOARD_CURSOR_LAST_TAB) {
        return self->tabs_x + 0x48 + (cursor - BBS_BOARD_CURSOR_TAB) * 8;
    }
    return 0x80;
}
CLEAN_AS(func_ov113_02299a08, BbsBoard_CursorBaseX)

/* func_ov113_02299a44: the cursor sprite put at the cursor's place, animation 1, shown. */
void BbsBoard_PlaceCursor(BbsBoard *self)
{
    int x = BbsBoard_CursorX(self);
    int y = BbsBoard_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    BbsBoard_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov113_02299a44, BbsBoard_PlaceCursor)

/* func_ov113_02299a80: the number of posts, and the tabs' x that centres their row. */
void BbsBoard_CountPosts(BbsBoard *self)
{
    self->posts = Bbs_CountTownPosts();
    self->tabs_x = (u8) ((BBS_POSTS - self->posts) * 4);
}
CLEAN_AS(func_ov113_02299a80, BbsBoard_CountPosts)

/* The page turns to the post now in `post` (state 5, the states' phase). */
static int bbs_turn(BbsBoard *self)
{
    self->base.state = BBS_BOARD_STATE_TURN;
    MenuScene_SetPhase(bbs_scene(self), BBS_BOARD_PHASE_STATES);
    return 1;
}

/* func_ov113_02299aa4: the action of the cursor's place, the posts counted first; whether
 * something happens.
 *
 * - WRITE (with sound 0x29) and QUIT: the button lit, the scene closes (state 3); the dispatch
 *   is told mode 1 (with its sound) or mode 0x43 without, then sound 0x12.
 * - NEWER, OLDER, OLDEST and NEWEST: when there is such another post, it becomes the one shown,
 *   the button or arrow lit, and the page turns (state 5).
 * - A tab: another post's becomes the one shown, BBS_BOARD_FLAG_FORWARD saying whether it is a
 *   later one, and the page turns.
 * The state is written directly, not through MenuScene_SetState. */
int BbsBoard_RunAction(BbsBoard *self)
{
    BbsBoard_CountPosts(self);
    unsigned int cursor = self->cursor;
    switch (cursor) {
        case BBS_BOARD_CURSOR_WRITE:
        case BBS_BOARD_CURSOR_QUIT:
            if (cursor == BBS_BOARD_CURSOR_WRITE) {
                bbs_play(BBS_BOARD_SE_WRITE);
            }
            BbsBoard_LightCursor(self, 1);
            self->base.state = BBS_BOARD_STATE_CLOSE;
            MenuScene_SetPhase(bbs_scene(self), BBS_BOARD_PHASE_STATES);
            if (self->cursor == BBS_BOARD_CURSOR_QUIT) {
                MenuDispatch_SetMode((MenuDispatch *) (void *) bbs_parent(self), MENU_DISPATCH_MODE_END, 0);
                bbs_play(BBS_BOARD_SE_QUIT);
            } else {
                MenuDispatch_SetMode((MenuDispatch *) (void *) bbs_parent(self), BBS_BOARD_MODE_WRITE, 1);
            }
            return 1;
        case BBS_BOARD_CURSOR_NEWER:
            if (self->posts > self->post + 1) {
                self->post++;
                BbsBoard_LightCursor(self, 1);
                return bbs_turn(self);
            }
            break;
        case BBS_BOARD_CURSOR_OLDER:
            if (self->post != 0) {
                self->post--;
                BbsBoard_LightCursor(self, 1);
                return bbs_turn(self);
            }
            break;
        case BBS_BOARD_CURSOR_NEWEST:
            if (self->post != self->posts - 1) {
                self->post = (u8) (self->posts - 1);
                BbsBoard_LightCursor(self, 1);
                return bbs_turn(self);
            }
            break;
        case BBS_BOARD_CURSOR_OLDEST:
            if (self->post != 0) {
                self->post = 0;
                BbsBoard_LightCursor(self, 1);
                return bbs_turn(self);
            }
            break;
        default:
            break;
    }
    if (cursor >= BBS_BOARD_CURSOR_TAB && cursor <= BBS_BOARD_CURSOR_LAST_TAB) {
        unsigned int post = (u8) (cursor - BBS_BOARD_CURSOR_TAB);
        unsigned int shown = self->post;
        if (post == shown) {
            return 0;
        }
        if (shown < post) {
            BbsBoard_SetFlags(self, BBS_BOARD_FLAG_FORWARD);
        } else {
            BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_FORWARD);
        }
        self->post = (u8) post;
        return bbs_turn(self);
    }
    return 0;
}
CLEAN_AS(func_ov113_02299aa4, BbsBoard_RunAction)

/* func_ov113_02299c44: the cursor's place lit (`lit`) or not: a button's cells (6 wide from
 * column 4, rows 0x14-0x16) in palette 14 or 13, the screen queued again; the right arrow by
 * BBS_BOARD_FLAG_NEWER_LIT and anything else by BBS_BOARD_FLAG_OLDER_LIT.
 * QUIRK: a tab counts as the left arrow (the turn's end unlights the cursor on a tab too). */
void BbsBoard_LightCursor(BbsBoard *self, int lit)
{
    u8 cursor = self->cursor;
    if (cursor <= BBS_BOARD_CURSOR_QUIT) {
        int left = cursor * 6 + 4;
        ScreenMap_SetPalette(self->screen, left, 0x14, left + 5, 0x16, lit ? 0xe : 0xd);
        BbsBoard_SetFlags(self, BBS_BOARD_FLAG_SCREEN_DIRTY);
    } else if (cursor == BBS_BOARD_CURSOR_NEWER) {
        if (lit) {
            BbsBoard_SetFlags(self, BBS_BOARD_FLAG_NEWER_LIT);
        } else {
            BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_NEWER_LIT);
        }
    } else {
        if (lit) {
            BbsBoard_SetFlags(self, BBS_BOARD_FLAG_OLDER_LIT);
        } else {
            BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_OLDER_LIT);
        }
    }
}
CLEAN_AS(func_ov113_02299c44, BbsBoard_LightCursor)

/* func_ov113_02299cd0: the cursor put at the place touched; whether one was. The arrows are at
 * y 0x54-0x70 (x up to 0x18 the left, from 0xe8 the right), the buttons at y 0xa4-0xb4 (48
 * pixels each from x 0x20), the tabs at y 0x92-0x9e (8 pixels each from tabs_x + 0x44). */
int BbsBoard_TouchCursor(BbsBoard *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;

    if (y >= 0x54 && y <= 0x70) {
        if (x <= 0x18) {
            self->cursor = BBS_BOARD_CURSOR_OLDER;
            return 1;
        }
        if (x >= 0xe8) {
            self->cursor = BBS_BOARD_CURSOR_NEWER;
            return 1;
        }
        return 0;
    }
    if (y >= 0xa4 && y <= 0xb4) {
        if (x < 0x20 || x >= 0xe0) {
            return 0;
        }
        self->cursor = (u8) ((x - 0x20) / 0x30);
        return 1;
    }
    if (y >= 0x92 && y <= 0x9e) {
        int first_x = self->tabs_x + 0x44;
        if (x < first_x) {
            return 0;
        }
        unsigned int tab = (u8) ((x - first_x) >> 3);
        if (tab >= self->posts) {
            return 0;
        }
        self->cursor = (u8) (tab + BBS_BOARD_CURSOR_TAB);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov113_02299cd0, BbsBoard_TouchCursor)

/* func_ov113_02299d84 */
void BbsBoard_ClearFlags(BbsBoard *self, u16 flags)
{
    self->flags &= (u16) ~flags;
}
CLEAN_AS(func_ov113_02299d84, BbsBoard_ClearFlags)

/* func_ov113_02299d94 */
void BbsBoard_SetFlags(BbsBoard *self, u16 flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov113_02299d94, BbsBoard_SetFlags)

/* func_ov113_02299da4: whether any of `flags` is set. */
int BbsBoard_TestFlags(BbsBoard *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov113_02299da4, BbsBoard_TestFlags)

/* func_ov113_02299db8: label `label` opened in a box of style 2 at (x, y) with colours 15 and
 * 10, and shown (centred when `center`). The last parameter is handed on unused. */
void BbsBoard_OpenLabel(BbsBoard *self, int label, int x, int y, int center, int unused)
{
    TextLabel *text = &self->labels[label];
    TextLabel_OpenStyledBox(text, 2, x, y, 15, 10, unused);
    TextLabel_Show(text, center, 0);
}
CLEAN_AS(func_ov113_02299db8, BbsBoard_OpenLabel)

/* func_ov113_02299df0: nothing. */
void BbsBoard_Nothing(BbsBoard *self)
{
    (void) self;
}
CLEAN_AS(func_ov113_02299df0, BbsBoard_Nothing)

/* func_ov113_02299df4: post `post` shown: its date, its number, its text and its read mark. */
void BbsBoard_ShowPost(BbsBoard *self, int post)
{
    BbsBoard_ShowDate(self, post);
    BbsBoard_ShowNumber(self, post);
    BbsBoard_ShowText(self, post);
    BbsBoard_ShowReadMark(self, post);
}
CLEAN_AS(func_ov113_02299df4, BbsBoard_ShowPost)

/* func_ov113_02299e20: the screen's palettes for post `post`: the mark at cells (0x10-0x12,
 * 0-3) in palette 8 when the current player has read the post, else 10, and the band at (6-0x19,
 * 5-6) in palette 10 for a post whose text came as such (BbsPost_IsText), else 8; the screen
 * queued again, and the post marked read by the current player. */
void BbsBoard_ShowReadMark(BbsBoard *self, int post)
{
    BbsPost *shown = Bbs_GetPost(&data_021eed68, post);
    int player = PlayerRecords_CurrentNumber();
    int read = BbsPost_IsRead(shown, player);
    ScreenMap_SetPalette(self->screen, 0x10, 0, 0x12, 3, read ? 8 : 10);
    int text = BbsPost_IsText(shown);
    ScreenMap_SetPalette(self->screen, 6, 5, 0x19, 6, text ? 10 : 8);
    BbsBoard_SetFlags(self, BBS_BOARD_FLAG_SCREEN_DIRTY);
    BbsPost_MarkRead(shown, player);
}
CLEAN_AS(func_ov113_02299e20, BbsBoard_ShowReadMark)

/* func_ov113_02299e98: the post's number (post + 1, one or two full-width digits) in its label,
 * opened at (0x11a, 2) and centred. */
void BbsBoard_ShowNumber(BbsBoard *self, int post)
{
    u16 digits[3] = {0, 0, 0};
    int number = post + 1;
    if (number >= 10) {
        digits[0] = (u16) (number / 10 + BBS_BOARD_DIGIT_0);
        digits[1] = (u16) (number % 10 + BBS_BOARD_DIGIT_0);
        digits[2] = 0;
    } else {
        /* the game leaves the third character as it was on the stack; the text ends before */
        digits[0] = (u16) (post + BBS_BOARD_DIGIT_0 + 1);
        digits[1] = 0;
    }
    TextLabel_SetFromWide(&self->labels[BBS_BOARD_LABEL_NUMBER], digits, (void *) (uintptr_t) 3);
    BbsBoard_OpenLabel(self, BBS_BOARD_LABEL_NUMBER, 0x11a, 2, 1, 0);
}
CLEAN_AS(func_ov113_02299e98, BbsBoard_ShowNumber)

/* func_ov113_02299f10: the post's date: "20" and the year's two digits at (0x111, 4), the
 * month's and the day's two digits at (0x116, 4), not centred. Each part is read twice, once
 * for each digit. */
void BbsBoard_ShowDate(BbsBoard *self, int post)
{
    BbsPost *shown = Bbs_GetPost(&data_021eed68, post);
    u16 digits[5];

    digits[0] = BBS_BOARD_DIGIT_0 + 2;
    digits[1] = BBS_BOARD_DIGIT_0;
    digits[2] = (u16) (BbsPost_GetYear(shown) / 10 + BBS_BOARD_DIGIT_0);
    digits[3] = (u16) (BbsPost_GetYear(shown) % 10 + BBS_BOARD_DIGIT_0);
    digits[4] = 0;
    TextLabel_SetFromWide(&self->labels[BBS_BOARD_LABEL_YEAR], digits, (void *) (uintptr_t) 5);
    BbsBoard_OpenLabel(self, BBS_BOARD_LABEL_YEAR, 0x111, 4, 0, 1);

    digits[0] = (u16) (BbsPost_GetMonth(shown) / 10 + BBS_BOARD_DIGIT_0);
    digits[1] = (u16) (BbsPost_GetMonth(shown) % 10 + BBS_BOARD_DIGIT_0);
    digits[2] = (u16) (BbsPost_GetDay(shown) / 10 + BBS_BOARD_DIGIT_0);
    digits[3] = (u16) (BbsPost_GetDay(shown) % 10 + BBS_BOARD_DIGIT_0);
    TextLabel_SetFromWide(&self->labels[BBS_BOARD_LABEL_DAY], digits, (void *) (uintptr_t) 5);
    BbsBoard_OpenLabel(self, BBS_BOARD_LABEL_DAY, 0x116, 4, 0, 1);
}
CLEAN_AS(func_ov113_02299f10, BbsBoard_ShowDate)

/* func_ov113_0229a004: the post's text broken into its six lines (96 characters, up to 16 a
 * line, 0xa0 pixels wide), each line's label cleared and set from its characters (when it has
 * any), then each drawn into its characters (a box at 0x14, 0xe, colour 0xd) and shown; the
 * characters queued for BG 2 (0x11-0x100). The text is looked up again for each line. */
void BbsBoard_ShowText(BbsBoard *self, int post)
{
    BbsPost *shown = Bbs_GetPost(&data_021eed68, post);
    s32 starts[BBS_BOARD_LINES + 1];
    s32 end_line;

    LetterView_BreakLines(BbsPost_Text(shown), starts, &end_line, BBS_POST_LENGTH, BBS_LINE_LENGTH, 0xa0, BBS_BOARD_LINES);
    for (int i = 0; i < BBS_BOARD_LINES; i++) {
        u32 length = (u32) starts[i + 1] - (u32) starts[i];
        TextLabel *line = &self->lines[i];
        TextBase_Clear(line);
        if (length != 0) {
            const u16 *text = BbsPost_Text(shown);
            TextLabel_SetFromWideConverted(line, text + (u32) starts[i], (int) length, 0, 0);
        }
    }
    for (int i = 0; i < BBS_BOARD_LINES; i++) {
        TextLabel *line = &self->lines[i];
        TextLabel_OpenBox(line, (int) (uintptr_t) self->line_chars[i], 0x14, 0xe, 0xd);
        TextLabel_Show(line, 0, 0);
    }
    LayerTask_QueueChars(&self->chars_task, (int) (uintptr_t) self->line_chars, BBS_BOARD_LAYER, 0x11, 0x11, 0x100);
}
CLEAN_AS(func_ov113_0229a004, BbsBoard_ShowText)

/* func_ov113_0229a0ec: the keys take over: the cursor placed, the key repeat reset, sub state 1. */
void BbsBoard_StartKeys(BbsBoard *self)
{
    BbsBoard_PlaceCursor(self);
    MenuScene_ResetKeyRepeat(bbs_scene(self));
    MenuScene_SetSubState(bbs_scene(self), BBS_BOARD_SUB_KEYS);
}
CLEAN_AS(func_ov113_0229a0ec, BbsBoard_StartKeys)

/* func_ov113_0229a108: the pen takes over: the cursor hidden, sub state 0. */
void BbsBoard_StartTouch(BbsBoard *self)
{
    BbsBoard_HideCursor(self);
    MenuScene_SetSubState(bbs_scene(self), BBS_BOARD_SUB_TOUCH);
}
CLEAN_AS(func_ov113_0229a108, BbsBoard_StartTouch)

/* func_ov113_0229a120 (sub state 4): once the cursor sprite's animation is done, it shows the
 * first of its set again and the keys go on (sub state 1). */
void BbsBoard_WaitRelease(BbsBoard *self)
{
    if (CellLayerSprite_IsDone(bbs_cursor_cells(self))) {
        BbsBoard_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(bbs_scene(self), BBS_BOARD_SUB_KEYS);
    }
}
CLEAN_AS(func_ov113_0229a120, BbsBoard_WaitRelease)

/* func_ov113_0229a148 (sub state 3): once the cursor sprite's animation is done, the action of
 * its place: done, the cursor is hidden for WRITE and QUIT, else shows the third of its set (the
 * page turns); not done, the press is cancelled. */
void BbsBoard_WaitPress(BbsBoard *self)
{
    if (CellLayerSprite_IsDone(bbs_cursor_cells(self)) == 0) {
        return;
    }
    if (BbsBoard_RunAction(self) != 0) {
        if (self->cursor == BBS_BOARD_CURSOR_WRITE || self->cursor == BBS_BOARD_CURSOR_QUIT) {
            BbsBoard_HideCursor(self);
        } else {
            Glider_ShowThirdOfSet(&self->cursor_sprite);
        }
    } else {
        BbsBoard_CancelPress(self);
    }
}
CLEAN_AS(func_ov113_0229a148, BbsBoard_WaitPress)

/* func_ov113_0229a194 (sub state 2): once the cursor sprite stops gliding, back to the sub state
 * it glided from. */
void BbsBoard_WaitGlide(BbsBoard *self)
{
    if (!Glider_IsMoving(&self->cursor_sprite)) {
        MenuScene_SetSubState(bbs_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov113_0229a194, BbsBoard_WaitGlide)

/* func_ov113_0229a1b8 (sub state 1): a touch hands over to the pen; else the d-pad moves the
 * cursor; else A presses its place, B quits (the cursor hidden first), L and R turn to the
 * post before and the next (the cursor hidden when the page turns). */
void BbsBoard_UpdateKeys(BbsBoard *self)
{
    if (MenuScene_TakeTouch(bbs_scene(self)) != 0) {
        BbsBoard_StartTouch(self);
        return;
    }
    if (BbsBoard_MoveCursor(self, MenuScene_LatchRepeatedKeys(bbs_scene(self))) != 0) {
        BbsBoard_CursorMoved(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & BBS_BOARD_PAD_A) {
        BbsBoard_Press(self);
        return;
    }
    if (pressed & BBS_BOARD_PAD_B) {
        self->cursor = BBS_BOARD_CURSOR_QUIT;
        BbsBoard_HideCursor(self);
        BbsBoard_RunAction(self);
        return;
    }
    if (pressed & BBS_BOARD_PAD_L) {
        self->cursor = BBS_BOARD_CURSOR_OLDER;
        if (BbsBoard_RunAction(self) != 0) {
            BbsBoard_HideCursor(self);
        }
        return;
    }
    if (pressed & BBS_BOARD_PAD_R) {
        self->cursor = BBS_BOARD_CURSOR_NEWER;
        if (BbsBoard_RunAction(self) != 0) {
            BbsBoard_HideCursor(self);
        }
    }
}
CLEAN_AS(func_ov113_0229a1b8, BbsBoard_UpdateKeys)

/* func_ov113_0229a274 (sub state 0): a button hands over to the keys (with command 0x3b,
 * MenuScene_TakeButtons); else a touch this frame picks the place touched and runs its action. */
void BbsBoard_UpdateTouch(BbsBoard *self)
{
    if (MenuScene_TakeButtons(bbs_scene(self), 1)) {
        BbsBoard_StartKeys(self);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        if (BbsBoard_TouchCursor(self)) {
            BbsBoard_RunAction(self);
        }
    }
}
CLEAN_AS(func_ov113_0229a274, BbsBoard_UpdateTouch)

/* func_ov113_0229a2c4: the background loaded on BG 2: palettes 8-14, the screen read into
 * `screen` and loaded, characters 16-319. */
void BbsBoard_LoadLayers(BbsBoard *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov113_0229ad18, heap, BBS_BOARD_LAYER, 8, 8, 14);
    RomFile_Read(data_ov113_0229ad2c, self->screen, BBS_BOARD_SCREEN_SIZE);
    DisplayLayer_LoadScreen(self->screen, BBS_BOARD_LAYER, BBS_BOARD_SCREEN_SIZE, 0);
    DisplayLayer_LoadCharsFromFile(data_ov113_0229ad40, heap, BBS_BOARD_LAYER, 16, 16, 319);
}
CLEAN_AS(func_ov113_0229a2c4, BbsBoard_LoadLayers)

/* func_ov113_0229a32c: the main engine in BG mode 0, BG 2 at priority 1 with its control 0. */
void BbsBoard_SetUpLayers(void)
{
    DisplayShadow_SetMainBgMode(0);
    DisplayLayer_SetPriority(BBS_BOARD_LAYER, 1);
    DisplayLayer_SetBgControl(BBS_BOARD_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov113_0229a32c, BbsBoard_SetUpLayers)

/* func_ov113_0229a350: a changed screen queued for BG 2 (the flag cleared once it is). */
void BbsBoard_QueueScreen(BbsBoard *self)
{
    if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_SCREEN_DIRTY)) {
        if (LayerTask_QueueScreen(&self->screen_task, (int) (uintptr_t) self->screen, BBS_BOARD_LAYER, BBS_BOARD_SCREEN_SIZE,
                                  0)) {
            BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_SCREEN_DIRTY);
        }
    }
}
CLEAN_AS(func_ov113_0229a350, BbsBoard_QueueScreen)

/* func_ov113_0229a390: a frame's end. */
void BbsBoard_EndFrame(BbsBoard *self)
{
    BbsBoard_QueueScreen(self);
}
CLEAN_AS(func_ov113_0229a390, BbsBoard_EndFrame)

/* func_ov113_0229a398: a frame's start: the cursor sprite updated and the boxes the labels
 * drew through last frame freed. */
void BbsBoard_BeginFrameBody(BbsBoard *self)
{
    bbs_update_cursor_sprite(self);
    for (int i = 0; i < BBS_BOARD_DATE_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
    for (int i = 0; i < BBS_BOARD_LINES; i++) {
        TextLabel_CloseBox(&self->lines[i]);
    }
}
CLEAN_AS(func_ov113_0229a398, BbsBoard_BeginFrameBody)

/* func_ov113_0229a3fc: a frame's start in the interactive phase. */
void BbsBoard_BeginFrame(BbsBoard *self)
{
    BbsBoard_BeginFrameBody(self);
}
CLEAN_AS(func_ov113_0229a3fc, BbsBoard_BeginFrame)

/* func_ov113_0229a404: the scene closes: both layer tasks ended and the labels' boxes freed. */
void BbsBoard_Teardown(BbsBoard *self)
{
    LayerTask_End(&self->chars_task);
    LayerTask_End(&self->screen_task);
    for (int i = 0; i < BBS_BOARD_DATE_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
    for (int i = 0; i < BBS_BOARD_LINES; i++) {
        TextLabel_CloseBox(&self->lines[i]);
    }
}
CLEAN_AS(func_ov113_0229a404, BbsBoard_Teardown)

/* func_ov113_0229a474: the scene's own state at its start: no flags, the cursor on QUIT, the
 * posts counted and the newest one shown. */
void BbsBoard_Setup(BbsBoard *self)
{
    self->wipe_y = 0;
    self->flags = 0;
    self->cursor = BBS_BOARD_CURSOR_QUIT;
    BbsBoard_CountPosts(self);
    self->post = (u8) (self->posts - 1);
}
CLEAN_AS(func_ov113_0229a474, BbsBoard_Setup)

/* func_ov113_0229a4a4 (state 8): the new page wipes in; when done, the interactive phase, the
 * cursor's place unlit, then the pen (when state flag 2 is clear) or the keys take over (the
 * key repeat reset, the turn's flag cleared, the cursor placed). The layer follows the wipe.
 * QUIRK: BBS_BOARD_FLAG_TURNING stays set when the pen takes over; the wipe's offset is 0 by
 * then. */
void BbsBoard_TurnIn(BbsBoard *self)
{
    if (MenuScene_StepWipeBack(bbs_scene(self), 1) != 0) {
        MenuScene_SetPhase(bbs_scene(self), BBS_BOARD_PHASE_INTERACTIVE);
        BbsBoard_LightCursor(self, 0);
        if (StateFlags_IsClear2()) {
            BbsBoard_StartTouch(self);
        } else {
            MenuScene_ResetKeyRepeat(bbs_scene(self));
            MenuScene_SetSubState(bbs_scene(self), BBS_BOARD_SUB_KEYS);
            BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_TURNING);
            BbsBoard_PlaceCursor(self);
        }
    }
    MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
}
CLEAN_AS(func_ov113_0229a4a4, BbsBoard_TurnIn)

/* For a tab: the wipe's direction `earlier` when the post picked is before the one shown
 * (BBS_BOARD_FLAG_FORWARD clear), else `later`. */
static int bbs_tab_direction(BbsBoard *self, int earlier, int later)
{
    return BbsBoard_TestFlags(self, BBS_BOARD_FLAG_FORWARD) == 0 ? earlier : later;
}

/* func_ov113_0229a504 (state 7): the button picked unlit (NEWEST, OLDEST), the new page starts
 * to wipe in on window 0 from the side the turn goes to (3 for NEWEST and NEWER, 2 for OLDEST
 * and OLDER; for a tab 3 when it is later, else 2), BG 2 shown and following the wipe (state 8),
 * and the post shown. */
void BbsBoard_TurnShow(BbsBoard *self)
{
    int direction;
    switch (self->cursor) {
        case BBS_BOARD_CURSOR_NEWEST:
            BbsBoard_LightCursor(self, 0);
            direction = 3;
            break;
        case BBS_BOARD_CURSOR_NEWER:
            direction = 3;
            break;
        case BBS_BOARD_CURSOR_OLDEST:
            BbsBoard_LightCursor(self, 0);
            direction = 2;
            break;
        case BBS_BOARD_CURSOR_OLDER:
            direction = 2;
            break;
        default:
            direction = bbs_tab_direction(self, 2, 3);
            break;
    }
    MenuScene_StartWipeCoveredOnWindow0(bbs_scene(self), 8, 6, direction, BBS_BOARD_WIPE_MARGIN);
    DisplayLayer_Show(BBS_BOARD_LAYER);
    MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
    MenuScene_SetState(bbs_scene(self), BBS_BOARD_STATE_TURN_IN);
    BbsBoard_ShowPost(self, self->post);
}
CLEAN_AS(func_ov113_0229a504, BbsBoard_TurnShow)

/* func_ov113_0229a590 (state 6): the old page wipes out; when done, BG 2 hidden (state 7), else
 * the layer follows the wipe. */
void BbsBoard_TurnOut(BbsBoard *self)
{
    if (MenuScene_StepWipe(bbs_scene(self), 1)) {
        DisplayLayer_Hide(BBS_BOARD_LAYER);
        MenuScene_SetState(bbs_scene(self), BBS_BOARD_STATE_TURN_SHOW);
    } else {
        MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
    }
}
CLEAN_AS(func_ov113_0229a590, BbsBoard_TurnOut)

/* func_ov113_0229a5c0 (state 5): the page turns: the tabs follow the wipe, sound 0x3c for
 * OLDEST and NEWEST (else 0x39), and the old page starts to wipe out on window 0 towards the
 * side opposite the one the new page comes from (state 6). */
void BbsBoard_StartTurn(BbsBoard *self)
{
    int direction;
    BbsBoard_SetFlags(self, BBS_BOARD_FLAG_TURNING);
    switch (self->cursor) {
        case BBS_BOARD_CURSOR_NEWEST:
        case BBS_BOARD_CURSOR_NEWER:
            direction = 2;
            break;
        case BBS_BOARD_CURSOR_OLDEST:
        case BBS_BOARD_CURSOR_OLDER:
            direction = 3;
            break;
        default:
            direction = bbs_tab_direction(self, 3, 2);
            break;
    }
    switch (self->cursor) {
        case BBS_BOARD_CURSOR_OLDEST:
        case BBS_BOARD_CURSOR_NEWEST:
            bbs_play(BBS_BOARD_SE_TURN_ENDS);
            break;
        default:
            bbs_play(BBS_BOARD_SE_TURN);
            break;
    }
    MenuScene_StartWipeOnWindow0(bbs_scene(self), 8, 0, direction, BBS_BOARD_WIPE_MARGIN);
    MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
    MenuScene_SetState(bbs_scene(self), BBS_BOARD_STATE_TURN_OUT);
}
CLEAN_AS(func_ov113_0229a5c0, BbsBoard_StartTurn)

/* func_ov113_0229a658 (state 4): the scene wipes out; when done, BG 2 hidden and its scroll
 * reset, the scene asks to be deleted (phase 5) and is no longer drawn. Else the layer and the
 * OBJs follow the wipe. */
void BbsBoard_WipeOut(BbsBoard *self)
{
    if (MenuScene_StepWipe(bbs_scene(self), 1)) {
        DisplayLayer_Hide(BBS_BOARD_LAYER);
        DisplayLayer_SetScroll(BBS_BOARD_LAYER, 0, 0);
        MenuScene_SetPhase(bbs_scene(self), BBS_BOARD_PHASE_DELETE);
        BbsBoard_ClearFlags(self, BBS_BOARD_FLAG_DRAWN);
    } else {
        MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
        self->wipe_y = MenuScene_WipeOffsetY(bbs_scene(self));
    }
}
CLEAN_AS(func_ov113_0229a658, BbsBoard_WipeOut)

/* func_ov113_0229a6a4 (state 3): the scene starts to wipe out on window 0 (state 4). */
void BbsBoard_StartWipeOut(BbsBoard *self)
{
    MenuScene_StartWipeOnWindow0(bbs_scene(self), 8, 0, 0, BBS_BOARD_WIPE_MARGIN);
    MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
    MenuScene_SetState(bbs_scene(self), BBS_BOARD_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov113_0229a6a4, BbsBoard_StartWipeOut)

/* func_ov113_0229a6d4 (state 2): the scene wipes in; when done, the interactive phase with the
 * pen (state flag 2 clear) or the keys. The layer and the OBJs follow the wipe. */
void BbsBoard_WipeIn(BbsBoard *self)
{
    if (MenuScene_StepWipeBack(bbs_scene(self), 1)) {
        MenuScene_SetPhase(bbs_scene(self), BBS_BOARD_PHASE_INTERACTIVE);
        if (StateFlags_IsClear2()) {
            BbsBoard_StartTouch(self);
        } else {
            BbsBoard_StartKeys(self);
        }
    }
    MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(bbs_scene(self));
}
CLEAN_AS(func_ov113_0229a6d4, BbsBoard_WipeIn)

/* func_ov113_0229a71c (state 1): state 2 next, the post shown, the OBJs placed with the wipe
 * and drawn. */
void BbsBoard_ShowFirstPost(BbsBoard *self)
{
    MenuScene_SetState(bbs_scene(self), BBS_BOARD_STATE_WIPE_IN);
    BbsBoard_ShowPost(self, self->post);
    self->wipe_y = MenuScene_WipeOffsetY(bbs_scene(self));
    BbsBoard_SetFlags(self, BBS_BOARD_FLAG_DRAWN);
}
CLEAN_AS(func_ov113_0229a71c, BbsBoard_ShowFirstPost)

/* func_ov113_0229a74c (state 0): the layers set up and loaded, the scene starts to wipe in on
 * window 0, BG 2 shown and following the wipe (state 1). */
void BbsBoard_Open(BbsBoard *self)
{
    BbsBoard_SetUpLayers();
    BbsBoard_LoadLayers(self);
    MenuScene_StartWipeCoveredOnWindow0(bbs_scene(self), 8, 6, 0, BBS_BOARD_WIPE_MARGIN);
    DisplayLayer_Show(BBS_BOARD_LAYER);
    MenuScene_ScrollWipe(bbs_scene(self), BBS_BOARD_LAYER, 0, 0);
    MenuScene_SetState(bbs_scene(self), BBS_BOARD_STATE_SHOW_FIRST);
    BbsBoard_Nothing(self);
}
CLEAN_AS(func_ov113_0229a74c, BbsBoard_Open)

/* func_ov113_0229a794 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int BbsBoard_RequestDelete(BbsBoard *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov113_0229a794, BbsBoard_RequestDelete)

/* func_ov113_0229a7a4 (vtable slot 0x58, phase 4): nothing. */
int BbsBoard_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov113_0229a7a4, BbsBoard_Phase4)

/* func_ov113_0229a7a8 (vtable slot 0x54, phase 3): nothing. */
int BbsBoard_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov113_0229a7a8, BbsBoard_Phase3)

/* func_ov113_0229a7ac (vtable slot 0x50, phase 2): a frame of the scene in use. The menu close's
 * delay is counted first; when the menu is asked to close with the pen or the keys in use, QUIT
 * is picked with the cursor hidden. Else the frame's start, the sub state (BbsBoardSubState,
 * through the table of member functions, filled once from its constants) and the frame's end.
 * Answers 1.
 * REQUIRES: the sub state is below 5; the game reads past the table for others. */
int BbsBoard_RunInteractive(BbsBoard *self)
{
    static const MemberPointer *const sub_states[BBS_BOARD_SUB_STATES] = {
        &data_ov113_0229abe8, &data_ov113_0229ab98, &data_ov113_0229ab90, &data_ov113_0229abb0, &data_ov113_0229abf0,
    };
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        u8 sub_state = self->base.sub_state;
        if (sub_state == BBS_BOARD_SUB_TOUCH || sub_state == BBS_BOARD_SUB_KEYS) {
            self->cursor = BBS_BOARD_CURSOR_QUIT;
            BbsBoard_HideCursor(self);
            BbsBoard_RunAction(self);
            return 1;
        }
    }
    BbsBoard_BeginFrame(self);
    MemberTable_InitOnce(&data_ov113_0229ad64, data_ov113_0229ad68, sub_states, BBS_BOARD_SUB_STATES);
    MemberPointer_CallVoid(&data_ov113_0229ad68[self->base.sub_state], self);
    BbsBoard_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov113_0229a7ac, BbsBoard_RunInteractive)

/* Obj_ov113_0229ac00::func_ov113_0229a880 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (BbsBoardState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 9; the game reads past the table for others. */
int BbsBoard_RunState(BbsBoard *self)
{
    static const MemberPointer *const states[BBS_BOARD_STATES] = {
        &data_ov113_0229ab80, &data_ov113_0229aba0, &data_ov113_0229aba8, &data_ov113_0229abe0, &data_ov113_0229abd8,
        &data_ov113_0229abd0, &data_ov113_0229abc8, &data_ov113_0229abc0, &data_ov113_0229abb8,
    };
    MemberTable_InitOnce(&data_ov113_0229ad60, data_ov113_0229ad90, states, BBS_BOARD_STATES);
    BbsBoard_BeginFrameBody(self);
    MemberPointer_CallVoid(&data_ov113_0229ad90[self->base.state], self);
    BbsBoard_QueueScreen(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov113_0229ac0019func_ov113_0229a880Ev, BbsBoard_RunState)

/* func_ov113_0229a958 (vtable slot 0x24): the scene's OBJs, while drawn: the cursor sprite (with
 * state flag 2), the two arrows at the wipe's y (in palette 11 when lit, the right one first;
 * else 10) and the posts' tabs, following the wipe's x while the page turns. Answers 1. */
int BbsBoard_Draw(BbsBoard *self)
{
    if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_DRAWN) == 0) {
        return 1;
    }
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    int y = self->wipe_y + 0x60;
    int newer_palette = 0xa;
    int older_palette = 0xa;
    if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_NEWER_LIT) != 0) {
        newer_palette = 0xb;
    } else if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_OLDER_LIT) != 0) {
        older_palette = 0xb;
    }
    OamBuffer_DrawCell(0, data_ov113_0229ac60, 0x80, y, newer_palette, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    OamBuffer_DrawCell(0, data_ov113_0229ac80, 0x80, y, older_palette, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    int x = 0x80 + self->tabs_x;
    if (BbsBoard_TestFlags(self, BBS_BOARD_FLAG_TURNING) != 0) {
        x += MenuScene_WipeOffsetX(bbs_scene(self));
    }
    BbsBoard_DrawTabs(self, x, y);
    return 1;
}
CLEAN_AS(func_ov113_0229a958, BbsBoard_Draw)

/* func_ov113_0229aa34: the tab of each post at (x, y) on the main engine, the shown post's in
 * palette 11, the others' in 10. */
void BbsBoard_DrawTabs(BbsBoard *self, int x, int y)
{
    const OamEntry *tabs = data_ov113_0229ac60 + BBS_BOARD_FIRST_TAB_OBJ;
    for (u8 i = 0; i < self->posts; i++) {
        int palette = i == self->post ? 11 : 10;
        OamBuffer_DrawObjAffine(0, &tabs[i], x, y, palette, 1, NULL);
    }
}
CLEAN_AS(func_ov113_0229aa34, BbsBoard_DrawTabs)

/* func_ov113_0229aa8c (vtable slot 0x0c): the scene closes: the dispatch told and the members
 * torn down. Answers 1. */
int BbsBoard_Close(BbsBoard *self)
{
    MenuDispatch_ChildClosed((MenuDispatch *) (void *) bbs_parent(self));
    BbsBoard_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov113_0229aa8c, BbsBoard_Close)

/* func_ov113_0229aaa8 (vtable slot 0x00): the scene starts: the main engine's blending set
 * (BLDCNT: all planes over the backdrop, both weights 16, brightness 0), its own state, state 0
 * in the states' phase. Answers 1. */
int BbsBoard_Start(BbsBoard *self)
{
    G2x_SetBlendBrightnessExt_(BBS_BOARD_REG_BLDCNT, 0x1f, 0x20, 0x10, 0x10, 0);
    BbsBoard_Setup(self);
    MenuScene_SetState(bbs_scene(self), BBS_BOARD_STATE_OPEN);
    MenuScene_SetPhase(bbs_scene(self), BBS_BOARD_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov113_0229aaa8, BbsBoard_Start)

/* func_ov113_0229aae4 (named by the profile at 0x0229ab88): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the labels by __cxa_vec_ctor. */
BbsBoard *BbsBoard_New(void)
{
    BbsBoard *self = MenuScene_Alloc(sizeof(BbsBoard));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov113_0229ac00;
    LayerTask_Construct(&self->chars_task);
    LayerTask_Construct(&self->screen_task);
    __cxa_vec_ctor(self->labels, BBS_BOARD_DATE_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    __cxa_vec_ctor(self->lines, BBS_BOARD_LINES, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    Glider1_Construct(&self->cursor_sprite);
    return self;
}
CLEAN_AS(func_ov113_0229aae4, BbsBoard_New)
