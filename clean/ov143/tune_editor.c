/* The town tune editor of overlay 143 (tune_editor.h): its destructors, its flags, the steps'
 * places and drawing, the labels, the cursor and its sprite. */
#include "tune_editor.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/display_shadow.h"
#include "main/oam_buffer.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/town_tune.h"
#include "ov002/key_repeat.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(TuneEditor, wipe_y) == 0x94, "wipe");
static_assert(offsetof(TuneEditor, flags) == 0x98 && offsetof(TuneEditor, lit_step) == 0x9a, "flags");
static_assert(offsetof(TuneEditor, sequence) == 0x9c && offsetof(TuneEditor, labels_used) == 0x9f, "sequence");
static_assert(offsetof(TuneEditor, steps) == 0xa0 && offsetof(TuneEditor, cursor) == 0xa4, "steps");
static_assert(offsetof(TuneEditor, drag_y) == 0xa8 && offsetof(TuneEditor, cursor_sprite) == 0xac, "drag");
static_assert(sizeof(Glider) == 0x64 && offsetof(TuneEditor, panel) == 0x110, "panel");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(TuneEditor, labels) == 0x2dc, "labels");
static_assert(offsetof(TuneEditor, screen) == 0x99c && offsetof(TuneEditor, screen_task) == 0x119c, "screen");
static_assert(sizeof(TuneEditor) == 0x11c0, "size (func_ov143_0229ae84)");

/* The scene's vtable. */
extern const u8 data_ov143_0229b1c0[];

/* The labels' destructor, handed to __cxa_vec_cleanup. */
extern void func_02070be8(void *label);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* Each note's OBJs (three: two lit in palette 13 when the step is picked, then the rest), the
 * heights of the notes and the notes of the heights. */
extern const OamEntry *const data_ov143_0229b178[TUNE_EDITOR_STEPS];
extern const u8 data_ov143_0229afb0[TUNE_EDITOR_STEPS];
extern const u8 data_ov143_0229afd0[TUNE_EDITOR_STEPS];

/* The frame drawn on the lit step; the OBJ drawn for a playing rest; the OBJs drawn for a
 * playing note: notes 0-5 and 14, and the others. */
extern const OamEntry data_ov143_0229af90[];
extern const OamEntry data_ov143_0229af08[];
extern const OamEntry data_ov143_0229b038[];
extern OamEntry data_ov143_0229b050[]; /* written by TuneEditor_Setup, through data_ov143_0229b040 */

/* The title's OBJs (its label's characters start at the first one's tile). */
extern const OamEntry data_ov143_0229afc0[];

/* The labels' messages: seven note names (0xc3-0xc9) in turn for the notes 0-12, starting
 * from 0xc7 for note 0, then notes 13 and 14 and the title. */
#define TUNE_EDITOR_MESSAGE_NAME_FIRST 0xc3
#define TUNE_EDITOR_MESSAGE_NAME_LAST 0xc9
#define TUNE_EDITOR_MESSAGE_NOTE_0 0xc7
#define TUNE_EDITOR_MESSAGE_NOTE_13 0xca
#define TUNE_EDITOR_MESSAGE_NOTE_14 0xcb
#define TUNE_EDITOR_MESSAGE_TITLE 0x8d
#define TUNE_EDITOR_PITCHED_NOTES 13

/* The sounds: the erase button and its "no", the play delay passed to TownTune_Play. */
#define TUNE_EDITOR_SOUND_BUTTON 0x2a
#define TUNE_EDITOR_PLAY_NUMBER 400

/* The cursor sprite's animations (glide.h): hidden, and at a place. */
#define TUNE_EDITOR_ANIM_HIDDEN 0
#define TUNE_EDITOR_ANIM_CURSOR 1

static MenuScene *tune_scene(TuneEditor *self)
{
    return &self->base;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void tune_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void tune_destroy_members(TuneEditor *self)
{
    self->base.vtable = data_ov143_0229b1c0;
    __cxa_vec_cleanup(self->labels, TUNE_EDITOR_LABELS, sizeof(TextLabel), func_02070be8);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(tune_scene(self));
}

/* func_ov143_022995a0 (vtable slot 0x40) */
TuneEditor *TuneEditor_Destroy(TuneEditor *self)
{
    tune_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov143_022995a0, TuneEditor_Destroy)

/* func_ov143_022995e4 (vtable slot 0x44) */
TuneEditor *TuneEditor_Delete(TuneEditor *self)
{
    tune_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov143_022995e4, TuneEditor_Delete)

/* func_ov143_02299630 */
void TuneEditor_ClearFlags(TuneEditor *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov143_02299630, TuneEditor_ClearFlags)

/* func_ov143_02299640 */
void TuneEditor_SetFlags(TuneEditor *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov143_02299640, TuneEditor_SetFlags)

/* func_ov143_02299650 */
int TuneEditor_TestFlags(TuneEditor *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov143_02299650, TuneEditor_TestFlags)

/* func_ov143_02299664: the sub screen's OBJ window brightness ended and the panel's flag 2
 * cleared. */
void TuneEditor_Undim(TuneEditor *self)
{
    DisplayShadow_EndSubObjWindowBrightness();
    ButtonPanel_ClearFlag2(&self->panel);
}
CLEAN_AS(func_ov143_02299664, TuneEditor_Undim)

/* func_ov143_02299680: the sub screen dimmed outside the OBJ window (brightness -6) and the
 * panel's flag 2 set. */
void TuneEditor_Dim(TuneEditor *self)
{
    DisplayShadow_BeginSubObjWindowBrightness();
    DisplayShadow_SetSubBrightness((u8) -6);
    ButtonPanel_SetFlag2(&self->panel);
}
CLEAN_AS(func_ov143_02299680, TuneEditor_Dim)

/* func_ov143_022996a4: the place of step `step` (x, then y): 24 pixels a step, the bottom row
 * 16 to the right and 56 lower; raised 2 lines a height of its note.
 * REQUIRES: the step's note is below 16 (TuneEditor_HeightOfNote). */
void TuneEditor_StepPlace(TuneEditor *self, int *place, int step)
{
    int height = TuneEditor_HeightOfNote(self, self->steps[step]);
    int x = 26;
    int y = 63;
    if (step < TUNE_EDITOR_ROW_STEPS) {
        x += 24 * step;
        y -= 2 * height;
    } else {
        x += 24 * (step - TUNE_EDITOR_ROW_STEPS) + 16;
        y += 56 - 2 * height;
    }
    place[0] = x;
    place[1] = y;
}
CLEAN_AS(func_ov143_022996a4, TuneEditor_StepPlace)

/* func_ov143_022996ec: the labels opened: notes 0-12 with the note names in turn, notes 13 and
 * 14, then the title's (message 0x8d, style 8 at the title's OBJ tile, colour 8). */
void TuneEditor_OpenLabels(TuneEditor *self)
{
    u8 message = TUNE_EDITOR_MESSAGE_NOTE_0;
    for (int note = 0; note < TUNE_EDITOR_PITCHED_NOTES; note++) {
        TuneEditor_OpenNoteLabel(self, message, note);
        message++;
        if (message > TUNE_EDITOR_MESSAGE_NAME_LAST) {
            message = TUNE_EDITOR_MESSAGE_NAME_FIRST;
        }
    }
    TuneEditor_OpenNoteLabel(self, TUNE_EDITOR_MESSAGE_NOTE_13, 13);
    TuneEditor_OpenNoteLabel(self, TUNE_EDITOR_MESSAGE_NOTE_14, 14);

    TextLabel *label = TuneEditor_NextLabel(self);
    TextLabel_LoadMenuMessage(label, (char) TUNE_EDITOR_MESSAGE_TITLE);
    TextLabel_OpenStyledBox2(label, 8, data_ov143_0229afc0[0].attr2 & 0x3ff, 8, 15, 0, 0);
    TextLabel_Show(label, 1, 0);
}
CLEAN_AS(func_ov143_022996ec, TuneEditor_OpenLabels)

/* func_ov143_02299768: the next label opened with menu message `message` into the characters
 * of note `note`'s first OBJ (style 8, colour 3). */
void TuneEditor_OpenNoteLabel(TuneEditor *self, int message, int note)
{
    const OamEntry *objs = data_ov143_0229b178[note];
    TextLabel *label = TuneEditor_NextLabel(self);
    TextLabel_LoadMenuMessage(label, (char) message);
    TextLabel_OpenStyledBox2(label, 8, objs[0].attr2 & 0x3ff, 3, 15, 0, 0);
    TextLabel_Show(label, 1, 0);
}
CLEAN_AS(func_ov143_02299768, TuneEditor_OpenNoteLabel)

/* func_ov143_022997b0: the note of a height.
 * REQUIRES: height is below 16; the game reads a copy of the table on its stack. */
u8 TuneEditor_NoteOfHeight(TuneEditor *self, int height)
{
    (void) self;
    return data_ov143_0229afd0[height];
}
CLEAN_AS(func_ov143_022997b0, TuneEditor_NoteOfHeight)

/* func_ov143_022997d8: the height of a note.
 * REQUIRES: note is below 16; the game reads a copy of the table on its stack. */
u8 TuneEditor_HeightOfNote(TuneEditor *self, int note)
{
    (void) self;
    return data_ov143_0229afb0[note];
}
CLEAN_AS(func_ov143_022997d8, TuneEditor_HeightOfNote)

/* func_ov143_02299800: the 16 steps drawn from (x, y), 24 pixels apart; the bottom row 16 to
 * the right and 0x38 lower. The lit step is drawn lit. */
void TuneEditor_DrawSteps(TuneEditor *self, int x, int y)
{
    int step = 0;
    int step_x = x;
    for (; step < TUNE_EDITOR_ROW_STEPS; step++) {
        if (step == self->lit_step) {
            TuneEditor_DrawLitStep(self, step, step_x, y);
        } else {
            TuneEditor_DrawStep(self, self->steps[step], step_x, y);
        }
        step_x += 24;
    }
    step_x = x + 16;
    for (; step < TUNE_EDITOR_STEPS; step++) {
        if (step == self->lit_step) {
            TuneEditor_DrawLitStep(self, step, step_x, y + 0x38);
        } else {
            TuneEditor_DrawStep(self, self->steps[step], step_x, y + 0x38);
        }
        step_x += 24;
    }
}
CLEAN_AS(func_ov143_02299800, TuneEditor_DrawSteps)

/* func_ov143_02299880: step `step` drawn lit (as playing while the tune plays, else as picked),
 * then the frame over it. */
void TuneEditor_DrawLitStep(TuneEditor *self, int step, int x, int y)
{
    if (TuneEditor_TestFlags(self, TUNE_EDITOR_FLAG_PLAYING)) {
        TuneEditor_DrawPlayingStep(self, self->steps[step], x, y);
    } else {
        TuneEditor_DrawPickedStep(self, self->steps[step], x, y);
    }
    OamBuffer_DrawObjAffine(1, data_ov143_0229af90, x, y, -1, -1, NULL);
}
CLEAN_AS(func_ov143_02299880, TuneEditor_DrawLitStep)

/* func_ov143_022998dc: a step of note `note` drawn at (x, y), raised by its height.
 * REQUIRES: note is below 16. */
void TuneEditor_DrawStep(TuneEditor *self, int note, int x, int y)
{
    int top = y - 2 * TuneEditor_HeightOfNote(self, note);
    OamBuffer_DrawCell(1, data_ov143_0229b178[note], x, top, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov143_022998dc, TuneEditor_DrawStep)

/* func_ov143_02299924: a picked step of note `note`: its first two OBJs in palette 13, then
 * the rest of its cell.
 * REQUIRES: note is below 16. */
void TuneEditor_DrawPickedStep(TuneEditor *self, int note, int x, int y)
{
    const OamEntry *objs = data_ov143_0229b178[note];
    int top = y - 2 * TuneEditor_HeightOfNote(self, note);
    OamBuffer_DrawObjAffine(1, &objs[0], x, top, 13, 2, NULL);
    OamBuffer_DrawObjAffine(1, &objs[1], x, top, 13, 2, NULL);
    OamBuffer_DrawCell(1, &objs[2], x, top, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov143_02299924, TuneEditor_DrawPickedStep)

/* func_ov143_022999a4: a playing step of note `note`: for note 15 (a rest) its OBJ rotated,
 * 0x5c left and 0x18 up; else the playing OBJs (one set for notes 0-5 and 14, another for the
 * rest) in the palette of the note's third OBJ.
 * REQUIRES: note is below 16. */
void TuneEditor_DrawPlayingStep(TuneEditor *self, unsigned int note, int x, int y)
{
    const OamEntry *objs = data_ov143_0229b178[note];
    int top = y - 2 * TuneEditor_HeightOfNote(self, (int) note);
    if (note == 15) {
        OamBuffer_DrawObjRotated(1, data_ov143_0229af08, x - 0x5c, top - 0x18, -1, 2, 0x1000, 0xeaab, 0);
        return;
    }
    int palette = objs[2].attr2 >> 12;
    const OamEntry *playing = (note < 6 || note == 14) ? data_ov143_0229b038 : data_ov143_0229b050;
    OamBuffer_DrawCell(1, playing, x, top, palette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov143_022999a4, TuneEditor_DrawPlayingStep)

/* func_ov143_02299a38: no label handed out, and the 16 labels' boxes closed. */
void TuneEditor_CloseLabels(TuneEditor *self)
{
    self->labels_used = 0;
    for (int i = 0; i < TUNE_EDITOR_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov143_02299a38, TuneEditor_CloseLabels)

/* func_ov143_02299a64: the next label not handed out.
 * QUIRK: once all 16 are, the last one is handed out again. */
TextLabel *TuneEditor_NextLabel(TuneEditor *self)
{
    if (self->labels_used >= TUNE_EDITOR_LABELS) {
        return &self->labels[TUNE_EDITOR_LABELS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov143_02299a64, TuneEditor_NextLabel)

/* func_ov143_02299a9c: the erase question left: the cursor back on the erase button, the panel
 * press followed (sub state 9) and then the fade back to the tune (state 6); the erase button
 * as drawn and the screen no longer dimmed. */
void TuneEditor_LeaveErase(TuneEditor *self)
{
    self->cursor = TUNE_EDITOR_ERASE;
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_PANEL_PRESS);
    MenuScene_StartWipe(tune_scene(self), 0, 0);
    MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_FROM_ERASE);
    TuneEditor_SetErasePalette(self, 5);
    TuneEditor_Undim(self);
}
CLEAN_AS(func_ov143_02299a9c, TuneEditor_LeaveErase)

/* func_ov143_02299ad4: the erase button pressed: drawn pressed, the cursor sprite hidden, and
 * the fade to the erase question (state 4, phase 1). */
void TuneEditor_AskErase(TuneEditor *self)
{
    TuneEditor_SetErasePalette(self, 6);
    TuneEditor_HideCursorSprite(self);
    MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_TO_ERASE);
    MenuScene_SetPhase(tune_scene(self), TUNE_EDITOR_PHASE_STATES);
    MenuScene_StartWipe(tune_scene(self), 0, 0);
}
CLEAN_AS(func_ov143_02299ad4, TuneEditor_AskErase)

/* func_ov143_02299b04: the playback over: no step lit, the scene goes on and the play button is
 * drawn as before. */
void TuneEditor_StopPlayback(TuneEditor *self)
{
    TuneEditor_ClearFlags(self, TUNE_EDITOR_FLAG_PLAYING);
    self->lit_step = -1;
    TuneEditor_Resume(self);
    TuneEditor_SetPlayPalette(self, 3);
}
CLEAN_AS(func_ov143_02299b04, TuneEditor_StopPlayback)

/* func_ov143_02299b2c: the play button pressed: the tune played, no step lit until it starts,
 * the playback followed (sub state 10), the play button lit and the cursor sprite hidden. */
void TuneEditor_StartPlayback(TuneEditor *self)
{
    TownTune_Play(TUNE_EDITOR_PLAY_NUMBER);
    self->lit_step = -1;
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_PLAYING);
    TuneEditor_SetFlags(self, TUNE_EDITOR_FLAG_PLAYING);
    TuneEditor_SetFlags(self, TUNE_EDITOR_FLAG_PLAY_PENDING);
    TuneEditor_SetPlayPalette(self, 4);
    TuneEditor_HideCursorSprite(self);
}
CLEAN_AS(func_ov143_02299b2c, TuneEditor_StartPlayback)

/* func_ov143_02299b70: the erase button's part of the screen set to `palette` (queued). */
void TuneEditor_SetErasePalette(TuneEditor *self, int palette)
{
    TuneEditor_SetFlags(self, TUNE_EDITOR_FLAG_SCREEN_DIRTY);
    ScreenMap_SetPalette(self->screen, 0, 0x11, 9, 0x17, (u32) palette);
}
CLEAN_AS(func_ov143_02299b70, TuneEditor_SetErasePalette)

/* func_ov143_02299ba0: the play button's part of the screen set to `palette` (queued). */
void TuneEditor_SetPlayPalette(TuneEditor *self, int palette)
{
    TuneEditor_SetFlags(self, TUNE_EDITOR_FLAG_SCREEN_DIRTY);
    ScreenMap_SetPalette(self->screen, 0xc, 0x12, 0x15, 0x16, (u32) palette);
}
CLEAN_AS(func_ov143_02299ba0, TuneEditor_SetPlayPalette)

/* func_ov143_02299bd0: `screen` queued for layer 4 when it changed (cleared once queued). */
void TuneEditor_QueueScreen(TuneEditor *self)
{
    if (TuneEditor_TestFlags(self, TUNE_EDITOR_FLAG_SCREEN_DIRTY)) {
        if (LayerTask_QueueScreen(&self->screen_task, (int) (uintptr_t) self->screen, 4, sizeof(self->screen), 0)) {
            TuneEditor_ClearFlags(self, TUNE_EDITOR_FLAG_SCREEN_DIRTY);
        }
    }
}
CLEAN_AS(func_ov143_02299bd0, TuneEditor_QueueScreen)

/* func_ov143_02299c14: the cursor moved by the d-pad keys `keys` (none: nothing); whether it
 * moved. On the top row down goes to the step below and left and right step (right from the
 * last step goes on to the bottom row's first). On the bottom row down goes to the erase
 * button (from its first two steps), the play button (the next four) or the panel's button 1,
 * up to the step above, left and right step (left from the first step goes back to the top
 * row's last). The buttons below lead to each other and up to the steps above them. */
int TuneEditor_MoveCursor(TuneEditor *self, int keys)
{
    if (keys == 0) {
        return 0;
    }
    u8 before = self->cursor;
    if (before < TUNE_EDITOR_ROW_STEPS) {
        if (KeyRepeat_HasDown(keys)) {
            self->cursor += TUNE_EDITOR_ROW_STEPS;
        } else if (KeyRepeat_HasLeft(keys)) {
            if (self->cursor != 0) {
                self->cursor--;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            self->cursor++;
        }
    } else if (before <= TUNE_EDITOR_STEP_LAST) {
        if (KeyRepeat_HasDown(keys)) {
            int column = self->cursor - TUNE_EDITOR_ROW_STEPS;
            if (column < 2) {
                self->cursor = TUNE_EDITOR_ERASE;
            } else if (column < 6) {
                self->cursor = TUNE_EDITOR_PLAY;
            } else {
                self->cursor = TUNE_EDITOR_KEEP;
            }
        } else if (KeyRepeat_HasUp(keys)) {
            self->cursor -= TUNE_EDITOR_ROW_STEPS;
        } else if (KeyRepeat_HasLeft(keys)) {
            self->cursor--;
        } else if (KeyRepeat_HasRight(keys)) {
            if (self->cursor < TUNE_EDITOR_STEP_LAST) {
                self->cursor++;
            }
        }
    } else {
        switch (before) {
            case TUNE_EDITOR_ERASE:
                if (KeyRepeat_HasUp(keys)) {
                    self->cursor = 8;
                } else if (KeyRepeat_HasRight(keys)) {
                    self->cursor = TUNE_EDITOR_PLAY;
                }
                break;
            case TUNE_EDITOR_PLAY:
                if (KeyRepeat_HasUp(keys)) {
                    self->cursor = 0xb;
                } else if (KeyRepeat_HasRight(keys)) {
                    self->cursor = TUNE_EDITOR_KEEP;
                } else if (KeyRepeat_HasLeft(keys)) {
                    self->cursor = TUNE_EDITOR_ERASE;
                }
                break;
            case TUNE_EDITOR_KEEP:
                if (KeyRepeat_HasUp(keys)) {
                    self->cursor = 0xe;
                } else if (KeyRepeat_HasDown(keys)) {
                    self->cursor = TUNE_EDITOR_LEAVE;
                } else if (KeyRepeat_HasLeft(keys)) {
                    self->cursor = TUNE_EDITOR_PLAY;
                }
                break;
            case TUNE_EDITOR_LEAVE:
                if (KeyRepeat_HasUp(keys)) {
                    self->cursor = TUNE_EDITOR_KEEP;
                } else if (KeyRepeat_HasLeft(keys)) {
                    self->cursor = TUNE_EDITOR_PLAY;
                }
                break;
            default:
                break;
        }
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov143_02299c14, TuneEditor_MoveCursor)

/* The pen's y (autoload_2/input.c). */
extern u8 data_021f6c54;

/* func_ov143_02299e18: place `place` acts; whether it is a place. A step is lit and gets the
 * cursor: by touch its drag starts at the pen's y (sub state 1), by the keys its note is
 * adjusted (sub state 3); either way its note sounds. The buttons: erase asks (with the
 * sound), play plays, the panel's buttons keep, leave, erase or do not. */
int TuneEditor_Act(TuneEditor *self, unsigned int place)
{
    if (place <= TUNE_EDITOR_STEP_LAST) {
        self->lit_step = (s16) place;
        self->cursor = (u8) place;
        if (StateFlags_IsClear2()) {
            self->drag_y = data_021f6c54;
            self->drag_height = TuneEditor_HeightOfNote(self, self->steps[place]);
            MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_DRAG);
        } else {
            MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_ADJUST);
        }
        TownTune_PlaySeqD3(self->steps[place]);
        return 1;
    }
    switch (place) {
        case TUNE_EDITOR_ERASE:
            TuneEditor_AskErase(self);
            SoundSys_PlaySe(TUNE_EDITOR_SOUND_BUTTON);
            return 1;
        case TUNE_EDITOR_PLAY:
            TuneEditor_StartPlayback(self);
            return 1;
        case TUNE_EDITOR_KEEP:
            TuneEditor_Keep(self);
            return 1;
        case TUNE_EDITOR_LEAVE:
            TuneEditor_Leave(self);
            return 1;
        case TUNE_EDITOR_YES:
            TuneEditor_EraseYes(self);
            return 1;
        case TUNE_EDITOR_NO:
            TuneEditor_EraseNo(self);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov143_02299e18, TuneEditor_Act)

/* func_ov143_02299ed8: the place at (x, y): the first step whose 20 x 18 box holds it, else the
 * erase or the play button, else TUNE_EDITOR_NOWHERE. */
int TuneEditor_TouchedPlace(TuneEditor *self, int x, int y)
{
    for (int step = 0; step < TUNE_EDITOR_STEPS; step++) {
        int place[2];
        TuneEditor_StepPlace(self, place, step);
        if (place[0] <= x && x < place[0] + 0x14 && place[1] <= y && y < place[1] + 0x12) {
            return step;
        }
    }
    if (x >= 0 && x < 0x38 && y >= 0x90 && y < 0xac) {
        return TUNE_EDITOR_ERASE;
    }
    if (x >= 0x60 && x < 0xb0 && y >= 0x90 && y < 0xb8) {
        return TUNE_EDITOR_PLAY;
    }
    return TUNE_EDITOR_NOWHERE;
}
CLEAN_AS(func_ov143_02299ed8, TuneEditor_TouchedPlace)

/* func_ov143_02299f48: the cursor sprite pressed (the third of its set) until its animation
 * ends (sub state 6), then back to the sub state it was in. */
void TuneEditor_PressCursor(TuneEditor *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_PRESS);
}
CLEAN_AS(func_ov143_02299f48, TuneEditor_PressCursor)

/* func_ov143_02299f6c: A pressed: the cursor sprite shows the second of its set and the place
 * under the cursor acts once its animation ends (sub state 5). */
void TuneEditor_PressA(TuneEditor *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_A_PRESS);
}
CLEAN_AS(func_ov143_02299f6c, TuneEditor_PressA)

/* func_ov143_02299f84: the cursor sprite shown (the first of its set) and updated. */
void TuneEditor_ShowCursorSprite(TuneEditor *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    tune_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov143_02299f84, TuneEditor_ShowCursorSprite)

/* func_ov143_02299fa0: the cursor sprite eased to (x, y) in 3 steps with a cue, while the scene
 * waits for it (sub state 4) to go back to the sub state it was in. */
void TuneEditor_EaseTo(TuneEditor *self, int x, int y)
{
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov143_02299fa0, TuneEditor_EaseTo)

/* func_ov143_02299fd0: the cursor sprite turned (to set B at the panel's buttons 1 and 2, else
 * to set A) and eased to the cursor's place. */
void TuneEditor_GlideToCursor(TuneEditor *self)
{
    if (self->cursor == TUNE_EDITOR_KEEP || self->cursor == TUNE_EDITOR_LEAVE) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = TuneEditor_CursorSpriteX(self);
    int y = TuneEditor_CursorSpriteY(self);
    TuneEditor_EaseTo(self, x, y);
}
CLEAN_AS(func_ov143_02299fd0, TuneEditor_GlideToCursor)

/* func_ov143_0229a014: the cursor sprite hidden (animation 0) and updated. */
void TuneEditor_HideCursorSprite(TuneEditor *self)
{
    Glider_SetAnim(&self->cursor_sprite, TUNE_EDITOR_ANIM_HIDDEN);
    tune_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov143_0229a014, TuneEditor_HideCursorSprite)

/* func_ov143_0229a030: the cursor sprite's y at the cursor: 3 below a step's place, 0xa0 at
 * the erase and play buttons, the panel's button's y, else 0x60. */
int TuneEditor_CursorSpriteY(TuneEditor *self)
{
    u8 cursor = self->cursor;
    if (cursor <= TUNE_EDITOR_STEP_LAST) {
        int place[2];
        TuneEditor_StepPlace(self, place, cursor);
        return place[1] + 3;
    }
    switch (cursor) {
        case TUNE_EDITOR_ERASE:
        case TUNE_EDITOR_PLAY:
            return 0xa0;
        case TUNE_EDITOR_KEEP:
            return ButtonPanel_ButtonY(&self->panel, 1);
        case TUNE_EDITOR_LEAVE:
            return ButtonPanel_ButtonY(&self->panel, 2);
        case TUNE_EDITOR_YES:
            return ButtonPanel_ButtonY(&self->panel, 3);
        case TUNE_EDITOR_NO:
            return ButtonPanel_ButtonY(&self->panel, 4);
        default:
            return 0x60;
    }
}
CLEAN_AS(func_ov143_0229a030, TuneEditor_CursorSpriteY)

/* func_ov143_0229a0b0: the cursor sprite's x at the cursor: 10 right of a step's place, set
 * places at the erase and play buttons, the panel's button's x (6 left of it for buttons 1 and
 * 2), else 0x80. */
int TuneEditor_CursorSpriteX(TuneEditor *self)
{
    u8 cursor = self->cursor;
    if (cursor <= TUNE_EDITOR_STEP_LAST) {
        int place[2];
        TuneEditor_StepPlace(self, place, cursor);
        return place[0] + 0xa;
    }
    switch (cursor) {
        case TUNE_EDITOR_ERASE:
            return 0x2e;
        case TUNE_EDITOR_PLAY:
            return 0x94;
        case TUNE_EDITOR_KEEP:
            return ButtonPanel_ButtonX(&self->panel, 1) - 6;
        case TUNE_EDITOR_LEAVE:
            return ButtonPanel_ButtonX(&self->panel, 2) - 6;
        case TUNE_EDITOR_YES:
            return ButtonPanel_ButtonX(&self->panel, 3);
        case TUNE_EDITOR_NO:
            return ButtonPanel_ButtonX(&self->panel, 4);
        default:
            return 0x80;
    }
}
CLEAN_AS(func_ov143_0229a0b0, TuneEditor_CursorSpriteX)

/* func_ov143_0229a134: the cursor sprite put at the cursor's place, in its animation, shown. */
void TuneEditor_ShowCursorAtCursor(TuneEditor *self)
{
    int x = TuneEditor_CursorSpriteX(self);
    int y = TuneEditor_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, TUNE_EDITOR_ANIM_CURSOR);
    TuneEditor_ShowCursorSprite(self);
}
CLEAN_AS(func_ov143_0229a134, TuneEditor_ShowCursorAtCursor)
