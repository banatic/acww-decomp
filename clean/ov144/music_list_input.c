/* The music list of overlay 144 (music_list.h): the cursor's moves with the d-pad, the places
 * under the touch, the commands (choose a row, play or stop, store, take out, close), the
 * pointer that shows the cursor and the two ways of input (buttons and touch). */
#include "music_list.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/current_pockets.h"
#include "main/group_params.h"
#include "main/house_record.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/room_objects.h"

/* Not 0 in some scenes (autoload_2/sound_scene.h, kind 10); then the room's objects are synced
 * again when the song played stops. */
extern u8 data_020e54a8;

/* The panel's button that closes the scene. */
#define MUSIC_LIST_PANEL_CLOSE 6

/* The pointer's places: x for the rows, x and y of the three buttons, and the default. */
#define MUSIC_LIST_ROW_POINTER_X 0x48
#define MUSIC_LIST_BUTTON_POINTER_X 0x26
#define MUSIC_LIST_PLAY_POINTER_Y 0x2a
#define MUSIC_LIST_TAKE_POINTER_Y 0x7d
#define MUSIC_LIST_STORE_POINTER_Y 0x65

/* The sounds. */
#define MUSIC_LIST_SOUND_CHOOSE 0x29
#define MUSIC_LIST_SOUND_PLAY 0x55
#define MUSIC_LIST_SOUND_STOP 0x56
#define MUSIC_LIST_SOUND_STORE 0x57
#define MUSIC_LIST_SOUND_TAKE_OUT 0x58

/* The error messages (of "obj_etc_error"): the pockets are full, the song plays elsewhere. */
#define MUSIC_LIST_ERROR_POCKETS_FULL 0x10
#define MUSIC_LIST_ERROR_PLAYED_ELSEWHERE 0x20

/* The frames before the close, and before the taken out song leaves the list. */
#define MUSIC_LIST_CLOSE_DELAY 5
#define MUSIC_LIST_TAKE_OUT_DELAY 10

static MenuScene *music_list_scene(MusicList *self)
{
    return &self->base;
}

static CellLayerSprite *music_list_pointer_cells(MusicList *self)
{
    /* The pointer's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->pointer;
}

/* An object's virtual function at `slot` of its vtable, called with nothing more. */
static void music_list_call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* The cursor goes to the knob when the list scrolls, else to the panel's close button. */
static u8 music_list_right_place(MusicList *self)
{
    return self->scroll_max > 0 ? MUSIC_LIST_PLACE_KNOB : MUSIC_LIST_PLACE_CLOSE;
}

/* func_ov144_022996d4: the cursor moved by the repeated d-pad keys `keys`; whether it moved (or
 * the list's scroll target did).
 *
 * On a row: left goes to the button by the pointer's height, right to the knob (or the close
 * button); up moves a row up, and on the top row scrolls a row (keeping the cursor) when the
 * list is above its top; reaching the top row lines the list up on rows. Down moves a row down
 * as far as the last song when the list does not scroll; else to the eighth row, then the list
 * is lined up on rows or scrolled a row down as far as it goes.
 * Then, on the other places (also when a key just took the cursor there): the close button goes
 * left to the place by the pointer's height and up to the knob (when the list scrolls); the knob
 * down to the close button and left as the close button does; the play button down to the store
 * button, the take out button up to it, the store button up to play and down to take out; each
 * of the three goes right to the row by the pointer's height (else the knob or the close
 * button). */
int MusicList_MoveCursor(MusicList *self, int keys)
{
    u8 before = self->cursor;

    if (keys == 0) {
        return 0;
    }

    if (before <= MUSIC_LIST_PLACE_LAST_ROW) {
        if (KeyRepeat_HasLeft(keys)) {
            MusicList_ButtonAtPointer(self);
        } else if (KeyRepeat_HasRight(keys)) {
            self->cursor = music_list_right_place(self);
        } else if (KeyRepeat_HasUp(keys)) {
            if (self->cursor != 0) {
                self->cursor--;
                if (self->cursor == 0) {
                    int off_row = self->scroll_target & 0xf;
                    if (off_row != 0) {
                        self->scroll_target -= off_row;
                    }
                }
            } else if (self->scroll_target >= MUSIC_LIST_ROW_HEIGHT) {
                self->scroll_target -= MUSIC_LIST_ROW_HEIGHT;
                return 1;
            }
        } else if (KeyRepeat_HasDown(keys)) {
            if (self->scroll_max == 0) {
                if (self->cursor < self->count - 1) {
                    self->cursor++;
                }
            } else if (self->cursor < MUSIC_LIST_ROWS_SHOWN - 1) {
                self->cursor++;
            } else {
                int target = self->scroll_target;
                int off_row = target & 0xf;
                if (off_row != 0) {
                    self->scroll_target += MUSIC_LIST_ROW_HEIGHT - off_row;
                    return 1;
                }
                if (target <= self->scroll_max - MUSIC_LIST_ROW_HEIGHT) {
                    self->scroll_target += MUSIC_LIST_ROW_HEIGHT;
                    return 1;
                }
            }
        }
    }

    switch (self->cursor) {
        case MUSIC_LIST_PLACE_CLOSE:
            if (KeyRepeat_HasLeft(keys)) {
                MusicList_LeaveToLeft(self);
            } else if (KeyRepeat_HasUp(keys)) {
                if (self->scroll_max > 0) {
                    self->cursor = MUSIC_LIST_PLACE_KNOB;
                }
            }
            break;
        case MUSIC_LIST_PLACE_KNOB:
            if (KeyRepeat_HasDown(keys)) {
                self->cursor = MUSIC_LIST_PLACE_CLOSE;
            } else if (KeyRepeat_HasLeft(keys)) {
                MusicList_LeaveToLeft(self);
            }
            break;
        case MUSIC_LIST_PLACE_PLAY:
            if (KeyRepeat_HasDown(keys)) {
                self->cursor = MUSIC_LIST_PLACE_STORE;
            } else if (KeyRepeat_HasRight(keys)) {
                MusicList_LeaveToRight(self);
            }
            break;
        case MUSIC_LIST_PLACE_TAKE:
            if (KeyRepeat_HasUp(keys)) {
                self->cursor = MUSIC_LIST_PLACE_STORE;
            } else if (KeyRepeat_HasRight(keys)) {
                MusicList_LeaveToRight(self);
            }
            break;
        case MUSIC_LIST_PLACE_STORE:
            if (KeyRepeat_HasUp(keys)) {
                self->cursor = MUSIC_LIST_PLACE_PLAY;
            } else if (KeyRepeat_HasDown(keys)) {
                self->cursor = MUSIC_LIST_PLACE_TAKE;
            } else if (KeyRepeat_HasRight(keys)) {
                MusicList_LeaveToRight(self);
            }
            break;
        default:
            break;
    }

    return before != self->cursor;
}
CLEAN_AS(func_ov144_022996d4, MusicList_MoveCursor)

/* func_ov144_02299924: from the close button or the knob to the row at the pointer's height,
 * else (no songs) to the button there. */
void MusicList_LeaveToLeft(MusicList *self)
{
    if (MusicList_RowAtPointer(self) == 0) {
        MusicList_ButtonAtPointer(self);
    }
}
CLEAN_AS(func_ov144_02299924, MusicList_LeaveToLeft)

/* func_ov144_0229993c: from a button to the row at the pointer's height, else (no songs) to the
 * knob or the close button. */
void MusicList_LeaveToRight(MusicList *self)
{
    if (MusicList_RowAtPointer(self) == 0) {
        self->cursor = music_list_right_place(self);
    }
}
CLEAN_AS(func_ov144_0229993c, MusicList_LeaveToRight)

/* func_ov144_02299968: the cursor to the row at the pointer's height (y within 0x20-0x9f), among
 * the first nine rows and the songs; with the list between rows, the top row lines it up upward
 * and the bottom one (the cursor a row above it) downward. 0 when there are no songs, else 1. */
int MusicList_RowAtPointer(MusicList *self)
{
    int rows = self->count;
    if (rows == 0) {
        return 0;
    }
    if (rows > MUSIC_LIST_ROWS) {
        rows = MUSIC_LIST_ROWS;
    }

    int y = Glider_ScreenY(&self->pointer);
    if (y < 0x20) {
        y = 0x20;
    }
    if (y >= 0xa0) {
        y = 0x9f;
    }

    int off_row = self->scroll_target & 0xf;
    int row = (y - (0x20 - off_row)) >> 4;
    if (row >= rows) {
        row = rows - 1;
    }
    self->cursor = (u8) row;

    if (off_row != 0) {
        if (row == 0) {
            self->scroll_target -= off_row;
        } else if (row == rows - 1) {
            self->cursor = (u8) (self->cursor - 1);
            self->scroll_target += MUSIC_LIST_ROW_HEIGHT - (self->scroll_target & 0xf);
        }
    }
    return 1;
}
CLEAN_AS(func_ov144_02299968, MusicList_RowAtPointer)

/* func_ov144_02299a00: the cursor to the button at the pointer's height: play above y 76, store
 * above 116, else take out. */
void MusicList_ButtonAtPointer(MusicList *self)
{
    int y = Glider_ScreenY(&self->pointer);
    if (y < 76) {
        self->cursor = MUSIC_LIST_PLACE_PLAY;
    } else if (y < 116) {
        self->cursor = MUSIC_LIST_PLACE_STORE;
    } else {
        self->cursor = MUSIC_LIST_PLACE_TAKE;
    }
}
CLEAN_AS(func_ov144_02299a00, MusicList_ButtonAtPointer)

/* func_ov144_02299a30: the place under the touch at (x, y): the panel's close button, the play
 * (x 0x10-0x30, y 0x20-0x40), take out (y 0x78-0x88) and store (y 0x60-0x70) buttons, or a row on
 * the screen (x 0x40-0xc0, y 0x18-0x97) that holds a song; else MUSIC_LIST_PLACE_NONE.
 * QUIRK: the row is counted from the scroll's target, not from the scroll shown. */
int MusicList_HitTest(MusicList *self, int x, int y)
{
    if (ButtonPanel_IsTouched(&self->panel, MUSIC_LIST_PANEL_CLOSE) != 0) {
        return MUSIC_LIST_PLACE_CLOSE;
    }
    if (x >= 0x10 && x <= 0x30 && y >= 0x20 && y <= 0x40) {
        return MUSIC_LIST_PLACE_PLAY;
    }
    if (x >= 0x10 && x <= 0x30 && y >= 0x78 && y <= 0x88) {
        return MUSIC_LIST_PLACE_TAKE;
    }
    if (x >= 0x10 && x <= 0x30 && y >= 0x60 && y <= 0x70) {
        return MUSIC_LIST_PLACE_STORE;
    }
    if (x >= 0x40 && x <= 0xc0 && y >= 0x18 && y < 0x98) {
        int row = (y - (0x18 - (self->scroll_target & 0xf))) >> 4;
        if (row < self->count) {
            return (u8) row;
        }
    }
    return MUSIC_LIST_PLACE_NONE;
}
CLEAN_AS(func_ov144_02299a30, MusicList_HitTest)

/* func_ov144_02299ac4: a place's command. A row on the screen is chosen (sound 0x29 when the
 * choice changed; answers 0). The close button closes the scene, the knob is pressed (sub state
 * 4, the d-pad moves it) and the buttons play or stop, take out or store; 1 for these, the play
 * and take out buttons answering whether they did anything. 0 for other places. */
int MusicList_Command(MusicList *self, unsigned int command)
{
    if (command <= MUSIC_LIST_PLACE_LAST_ROW) {
        if (MusicList_Select(self, (int) command + self->first_row)) {
            SoundSys_PlaySe(MUSIC_LIST_SOUND_CHOOSE);
        }
        return 0;
    }
    switch (command) {
        case MUSIC_LIST_PLACE_CLOSE:
            MusicList_CloseByPanel(self);
            return 1;
        case MUSIC_LIST_PLACE_PLAY:
            return MusicList_PlayOrStop(self);
        case MUSIC_LIST_PLACE_TAKE:
            return MusicList_TakeOut(self);
        case MUSIC_LIST_PLACE_STORE:
            MusicList_StartStore(self);
            return 1;
        case MUSIC_LIST_PLACE_KNOB:
            PushButton_Press(&self->knob_button);
            PushButton_PressCue(&self->knob_button);
            MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_KNOB_KEYS);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov144_02299ac4, MusicList_Command)

/* func_ov144_0229a0a4: the third animation of the pointer's set, the sub state kept and sub
 * state 8 waiting for it to end. */
void MusicList_StartPointerAnim(MusicList *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_POINTER_ANIM);
}
CLEAN_AS(func_ov144_0229a0a4, MusicList_StartPointerAnim)

/* func_ov144_0229a0c8: the second animation of the pointer's set (a press), sub state 7. */
void MusicList_StartPointerPress(MusicList *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_POINTER_PRESS);
}
CLEAN_AS(func_ov144_0229a0c8, MusicList_StartPointerPress)

/* func_ov144_0229a0e0: the first animation of the pointer's set, then its update (slot 3). */
void MusicList_ShowPointer(MusicList *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    music_list_call_slot(&self->pointer, 3);
}
CLEAN_AS(func_ov144_0229a0e0, MusicList_ShowPointer)

/* func_ov144_0229a0fc: the pointer eased to (x, y) in 3 steps (cue 1), the sub state kept and
 * sub state 6 waiting for the move. */
void MusicList_GlidePointerTo(MusicList *self, int x, int y)
{
    Glider_EaseTo(&self->pointer, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_POINTER_MOVE);
}
CLEAN_AS(func_ov144_0229a0fc, MusicList_GlidePointerTo)

/* func_ov144_0229a12c: the pointer turned to its set B on a row or the close button, else to its
 * set A, and eased to the cursor's place. */
void MusicList_MovePointer(MusicList *self)
{
    u8 cursor = self->cursor;
    if (cursor == MUSIC_LIST_PLACE_CLOSE || cursor <= MUSIC_LIST_PLACE_LAST_ROW) {
        Glider_TurnToSetB(&self->pointer);
    } else {
        Glider_TurnToSetA(&self->pointer);
    }
    int x = MusicList_PointerX(self);
    int y = MusicList_PointerY(self);
    MusicList_GlidePointerTo(self, x, y);
}
CLEAN_AS(func_ov144_0229a12c, MusicList_MovePointer)

/* func_ov144_0229a17c: the pointer's animation 0 (hidden), then its update (slot 3). */
void MusicList_HidePointer(MusicList *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    music_list_call_slot(&self->pointer, 3);
}
CLEAN_AS(func_ov144_0229a17c, MusicList_HidePointer)

/* func_ov144_0229a198: the pointer's y for the cursor: a row's 0x20 + 16 per row less the list's
 * offset from a row (of the scroll's target), the close button's and the knob's face's, the three
 * buttons'; 0x60 for others. */
int MusicList_PointerY(MusicList *self)
{
    u8 cursor = self->cursor;
    if (cursor <= MUSIC_LIST_PLACE_LAST_ROW) {
        return (int) (((u32) cursor << 4) + 0x20 - ((u32) self->scroll_target & 0xf));
    }
    switch (cursor) {
        case MUSIC_LIST_PLACE_CLOSE:
            return ButtonPanel_ButtonY(&self->panel, MUSIC_LIST_PANEL_CLOSE);
        case MUSIC_LIST_PLACE_PLAY:
            return MUSIC_LIST_PLAY_POINTER_Y;
        case MUSIC_LIST_PLACE_TAKE:
            return MUSIC_LIST_TAKE_POINTER_Y;
        case MUSIC_LIST_PLACE_STORE:
            return MUSIC_LIST_STORE_POINTER_Y;
        case MUSIC_LIST_PLACE_KNOB:
            return PushButton_FaceY(&self->knob_button);
        default:
            return 0x60;
    }
}
CLEAN_AS(func_ov144_0229a198, MusicList_PointerY)

/* func_ov144_0229a208: the pointer's x for the cursor: 0x48 on a row, the close button's and the
 * knob's face's, 0x26 on the three buttons; 0x80 for others. */
int MusicList_PointerX(MusicList *self)
{
    u8 cursor = self->cursor;
    if (cursor <= MUSIC_LIST_PLACE_LAST_ROW) {
        return MUSIC_LIST_ROW_POINTER_X;
    }
    switch (cursor) {
        case MUSIC_LIST_PLACE_CLOSE:
            return ButtonPanel_ButtonX(&self->panel, MUSIC_LIST_PANEL_CLOSE);
        case MUSIC_LIST_PLACE_PLAY:
        case MUSIC_LIST_PLACE_TAKE:
        case MUSIC_LIST_PLACE_STORE:
            return MUSIC_LIST_BUTTON_POINTER_X;
        case MUSIC_LIST_PLACE_KNOB:
            return PushButton_FaceX(&self->knob_button);
        default:
            return 0x80;
    }
}
CLEAN_AS(func_ov144_0229a208, MusicList_PointerX)

/* func_ov144_0229a264: the pointer put at the cursor's place at once, in its set A, shown. */
void MusicList_PlacePointer(MusicList *self)
{
    int x = MusicList_PointerX(self);
    int y = MusicList_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    MusicList_ShowPointer(self);
}
CLEAN_AS(func_ov144_0229a264, MusicList_PlacePointer)

/* func_ov144_0229a588: error `message` of "obj_etc_error" shown (sub state 12 waits for it), the
 * pointer's OBJ window cleared. */
void MusicList_ShowError(MusicList *self, char message)
{
    char number = message;
    ErrorMessage_Open(&self->error, (const u8 *) &number, 1, 0);
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_ERROR);
    CellLayerSprite_ClearWindow(music_list_pointer_cells(self));
}
CLEAN_AS(func_ov144_0229a588, MusicList_ShowError)

/* func_ov144_0229a5bc: the store button pressed: the scene closes into the store screen
 * (MUSIC_LIST_FLAG_STORE) after a delay of 5 frames (sub state 11), the button lit, state 2,
 * sound 0x57. */
void MusicList_StartStore(MusicList *self)
{
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_STORE);
    MusicList_SetStorePalette(self, 8);
    self->delay = MUSIC_LIST_CLOSE_DELAY;
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_CLOSE_DELAY);
    MenuScene_SetState(music_list_scene(self), MUSIC_LIST_STATE_CLOSE);
    SoundSys_PlaySe(MUSIC_LIST_SOUND_STORE);
}
CLEAN_AS(func_ov144_0229a5bc, MusicList_StartStore)

/* func_ov144_0229a5f4: the take out button pressed. Nothing with no row chosen (0). An error
 * when the chosen song plays elsewhere (0x20) or the pockets are full (0x10). Else the song goes
 * into the first free pocket (the song played stopped when it is this one), out of the house's
 * collection, the list shows its row and, after 10 frames (sub state 10), lets it go; the button
 * lit, sound 0x58. 1 except with no row chosen. */
int MusicList_TakeOut(MusicList *self)
{
    if (self->selected == MUSIC_LIST_NO_ROW) {
        return 0;
    }
    u16 song = self->songs[self->selected];
    if (HouseRecord_CurrentSongPlayedElsewhere(&song) != 0) {
        MusicList_ShowError(self, MUSIC_LIST_ERROR_PLAYED_ELSEWHERE);
        return 1;
    }
    int slot = CurrentPockets_FreeSlot();
    if (slot == -1) {
        MusicList_ShowError(self, MUSIC_LIST_ERROR_POCKETS_FULL);
        return 1;
    }
    CurrentPockets_Set(&song, 0, slot);
    if (self->selected == self->playing) {
        if (data_020e54a8 != 0) {
            RoomObjects_SyncKind3AOn();
        }
        self->playing = MUSIC_LIST_NO_ROW;
    }
    HouseRecord_RemoveSong(self->songs[self->selected]);
    MusicList_ScrollToRow(self, self->selected);
    self->delay = MUSIC_LIST_TAKE_OUT_DELAY;
    MusicList_SetTakePalette(self, 8);
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_TAKE_OUT);
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_TAKEN_OUT);
    SoundSys_PlaySe(MUSIC_LIST_SOUND_TAKE_OUT);
    return 1;
}
CLEAN_AS(func_ov144_0229a5f4, MusicList_TakeOut)

/* func_ov144_0229a6c8: the song played stops: the room's objects synced again when
 * data_020e54a8 is set, the list shows its row, no row plays, the rows and buttons redrawn, the
 * input again, sound 0x56. */
void MusicList_StopSong(MusicList *self)
{
    if (data_020e54a8 != 0) {
        RoomObjects_SyncKind3AOn();
    }
    MusicList_ScrollToRow(self, self->playing);
    self->playing = MUSIC_LIST_NO_ROW;
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_LIST_DIRTY);
    MusicList_RefreshButtons(self);
    MusicList_StartInput(self);
    SoundSys_PlaySe(MUSIC_LIST_SOUND_STOP);
}
CLEAN_AS(func_ov144_0229a6c8, MusicList_StopSong)

/* func_ov144_0229a71c: the play button pressed. Nothing with no row chosen; while a song plays
 * it stops (0). Else the chosen song is played: the scene closes (not into the store screen)
 * after a delay of 5 frames (sub state 11), the button lit, the list shows its row, main told
 * (GroupParams_SetC4C(1)) and given the song, state 2, sound 0x55 (1). */
int MusicList_PlayOrStop(MusicList *self)
{
    if (self->selected == MUSIC_LIST_NO_ROW) {
        return 0;
    }
    if (self->playing != MUSIC_LIST_NO_ROW) {
        MusicList_StopSong(self);
        return 0;
    }
    MusicList_ClearFlags(self, MUSIC_LIST_FLAG_STORE);
    self->delay = MUSIC_LIST_CLOSE_DELAY;
    MusicList_SetPlayPalette(self, 8);
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_CLOSE_DELAY);
    MusicList_ScrollToRow(self, self->selected);
    GroupParams_SetC4C(1);
    GroupParams_SetItem(self->songs[self->selected]);
    MenuScene_SetState(music_list_scene(self), MUSIC_LIST_STATE_CLOSE);
    SoundSys_PlaySe(MUSIC_LIST_SOUND_PLAY);
    return 1;
}
CLEAN_AS(func_ov144_0229a71c, MusicList_PlayOrStop)

/* func_ov144_0229a798: the scene closes by the panel's button 6: main told nothing changed
 * (GroupParams_SetC4C(0)), the button pressed, state 2, sub state 9 while it plays. */
void MusicList_CloseByPanel(MusicList *self)
{
    GroupParams_SetC4C(0);
    ButtonPanel_Select(&self->panel, MUSIC_LIST_PANEL_CLOSE);
    MenuScene_SetState(music_list_scene(self), MUSIC_LIST_STATE_CLOSE);
    MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_PANEL_PRESS);
}
CLEAN_AS(func_ov144_0229a798, MusicList_CloseByPanel)

/* func_ov144_0229a7c8: the input by the state flags: the touch when flag 2 is clear, else the
 * buttons. Answers what MenuScene_SetSubState answered. */
int MusicList_StartInput(MusicList *self)
{
    if (StateFlags_IsClear2()) {
        return (int) (uintptr_t) MusicList_StartTouch(self);
    }
    return (int) (uintptr_t) MusicList_StartKeys(self);
}
CLEAN_AS(func_ov144_0229a7c8, MusicList_StartInput)

/* func_ov144_0229a7e8: the buttons' input (sub state 3): the cursor on the play button unless a
 * song was just taken out (that flag cleared), the pointer put there, the key repeat reset. */
u8 *MusicList_StartKeys(MusicList *self)
{
    if (MusicList_TestFlags(self, MUSIC_LIST_FLAG_TAKEN_OUT)) {
        MusicList_ClearFlags(self, MUSIC_LIST_FLAG_TAKEN_OUT);
    } else {
        self->cursor = MUSIC_LIST_PLACE_PLAY;
    }
    MusicList_PlacePointer(self);
    MenuScene_ResetKeyRepeat(music_list_scene(self));
    return MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_KEYS);
}
CLEAN_AS(func_ov144_0229a7e8, MusicList_StartKeys)

/* func_ov144_0229a824: the touch's input (sub state 0), the pointer hidden. */
u8 *MusicList_StartTouch(MusicList *self)
{
    MusicList_HidePointer(self);
    return MenuScene_SetSubState(music_list_scene(self), MUSIC_LIST_SUB_TOUCH);
}
CLEAN_AS(func_ov144_0229a824, MusicList_StartTouch)
