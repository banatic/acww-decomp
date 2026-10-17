/* The town tune editor of overlay 143 (tune_editor.h): keeping or leaving the tune, the sub
 * states, the graphics, the frame's start and end, the states, the draw and the vtable's
 * slots. */
#include "tune_editor.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/town_tune.h"
#include "main/villager_town.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

/* The scene's vtable. */
extern const u8 data_ov143_0229b1c0[];

/* The labels' constructor and destructor, handed to __cxa_vec_ctor. */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The tune in the save's state block and unpacked a step to a byte (main/town_tune.c); the
 * step the second player plays, -1 for none. */
extern TownTunePacked data_021f3b68;
extern u8 data_021cfbbc[TUNE_EDITOR_STEPS];
extern s32 data_020df2a0;

/* The town's villagers (main/villager_town.h). */
extern u8 data_021e5a2c[];

/* The session (main/session.h). */
extern NetSession *data_020ccf94;

/* The pad, and the pen (autoload_2/input.c): down, and gone down or up this frame; where. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */
#define TUNE_EDITOR_PAD_A 0x0001
#define TUNE_EDITOR_PAD_B 0x0002
#define TUNE_EDITOR_PAD_START 0x0008

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The files under "menu/melody/". */
extern const char data_ov143_0229b220[]; /* "obj.bch" */
extern const char data_ov143_0229b234[]; /* "obj2.bch" */
extern const char data_ov143_0229b24c[]; /* "obj.bpl" */
extern const char data_ov143_0229b260[]; /* "bg0.bch" */
extern const char data_ov143_0229b274[]; /* "bg.bpl" */
extern const char data_ov143_0229b288[]; /* "a_bg.bsc" */
extern const char data_ov143_0229b2a0[]; /* "b_bg.bsc" */

/* The title's OBJs, and the OBJ lists of note 15 and of the playing notes 6-13 and 15: the
 * latter's third OBJ shows the tile 4 past the former's. */
extern const OamEntry data_ov143_0229afc0[];
extern const OamEntry data_ov143_0229b028[];
extern OamEntry data_ov143_0229b040[];

/* The sounds: the panel's buttons, the tune erased. */
#define TUNE_EDITOR_SOUND_BUTTON 0x2a
#define TUNE_EDITOR_SOUND_ERASED 0x5a

/* The tune sent to the others when linked: a message of kind 0x0c with the 16 steps, ended for
 * handler 0x16 as kind 4. */
#define TUNE_EDITOR_MESSAGE_TUNE 0x0c
#define TUNE_EDITOR_SEND_HANDLER 0x16
#define TUNE_EDITOR_SEND_KIND 4

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes. */
#define TUNE_EDITOR_PARENT_CLOSE 0x44

static MenuScene *tune_scene(TuneEditor *self)
{
    return &self->base;
}

static MenuDispatch *tune_parent(TuneEditor *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

static CellLayerSprite *tune_sprite_cells(TuneEditor *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* func_ov143_0229a16c: whether the scene may be deleted: unless the tune was kept while linked,
 * at once; else once the session has reached the sequence the tune was sent at. */
int TuneEditor_CanEnd(TuneEditor *self)
{
    if (!GroupParams_C4CIs1()) {
        return 1;
    }
    if (Session_IsLinked(data_020ccf94)) {
        if (!Session_HasReachedSequence(self->sequence)) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov143_0229a16c, TuneEditor_CanEnd)

/* func_ov143_0229a1a4: when linked, the tune sent to the others and the session's frame
 * sequence kept. */
void TuneEditor_SendTune(TuneEditor *self)
{
    u8 message[1 + TUNE_EDITOR_STEPS];
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    message[0] = TUNE_EDITOR_MESSAGE_TUNE;
    MI_CpuCopy8(self->steps, message + 1, TUNE_EDITOR_STEPS);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, message, sizeof(message));
    Session_EndMessage(session, TUNE_EDITOR_SEND_HANDLER, TUNE_EDITOR_SEND_KIND);
    self->sequence = Session_GetFrameSequence(session);
}
CLEAN_AS(func_ov143_0229a1a4, TuneEditor_SendTune)

/* func_ov143_0229a200: the tune left as it was: main told 0, the panel's button 2 pressed, and
 * after the press the wipe out (state 2). */
void TuneEditor_Leave(TuneEditor *self)
{
    GroupParams_SetC4C(0);
    ButtonPanel_Select(&self->panel, 2);
    MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_PANEL_PRESS);
}
CLEAN_AS(func_ov143_0229a200, TuneEditor_Leave)

/* func_ov143_0229a230: the tune kept: main told 1, the panel's button 1 pressed, and after the
 * press the wipe out (state 2); the tune packed into the save, used, no villager marked, and
 * sent to the others when linked. */
void TuneEditor_Keep(TuneEditor *self)
{
    GroupParams_SetC4C(1);
    ButtonPanel_Select(&self->panel, 1);
    MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_PANEL_PRESS);
    TownTune_Pack(&data_021f3b68, self->steps);
    TownTune_UseTune();
    VillagerTown_ClearMark((VillagerTown *) (void *) data_021e5a2c);
    TuneEditor_SendTune(self);
}
CLEAN_AS(func_ov143_0229a230, TuneEditor_Keep)

/* func_ov143_0229a284: the erase question goes on by touch or the keys, as state flag 2
 * says. */
void TuneEditor_ResumeErase(TuneEditor *self)
{
    if (StateFlags_IsClear2()) {
        TuneEditor_ResumeEraseByTouch(self);
    } else {
        TuneEditor_ResumeEraseByKeys(self);
    }
}
CLEAN_AS(func_ov143_0229a284, TuneEditor_ResumeErase)

/* func_ov143_0229a2a4: the erase question by the keys: the cursor on "no", its sprite shown,
 * the key repeat reset (sub state 8). */
void TuneEditor_ResumeEraseByKeys(TuneEditor *self)
{
    self->cursor = TUNE_EDITOR_NO;
    TuneEditor_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(tune_scene(self));
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_ERASE_KEYS);
}
CLEAN_AS(func_ov143_0229a2a4, TuneEditor_ResumeEraseByKeys)

/* func_ov143_0229a2c8: the erase question by touch: the cursor sprite hidden (sub state 7). */
void TuneEditor_ResumeEraseByTouch(TuneEditor *self)
{
    TuneEditor_HideCursorSprite(self);
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_ERASE_TOUCH);
}
CLEAN_AS(func_ov143_0229a2c8, TuneEditor_ResumeEraseByTouch)

/* func_ov143_0229a2e0: the tune's editing goes on by touch or the keys, as state flag 2
 * says. */
void TuneEditor_Resume(TuneEditor *self)
{
    if (StateFlags_IsClear2()) {
        TuneEditor_ResumeByTouch(self);
    } else {
        TuneEditor_ResumeByKeys(self);
    }
}
CLEAN_AS(func_ov143_0229a2e0, TuneEditor_Resume)

/* func_ov143_0229a300: by the keys: the cursor sprite shown at the cursor, the key repeat
 * reset (sub state 2). */
void TuneEditor_ResumeByKeys(TuneEditor *self)
{
    TuneEditor_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(tune_scene(self));
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_KEYS);
}
CLEAN_AS(func_ov143_0229a300, TuneEditor_ResumeByKeys)

/* func_ov143_0229a31c: by touch: the cursor sprite hidden (sub state 0). */
void TuneEditor_ResumeByTouch(TuneEditor *self)
{
    TuneEditor_HideCursorSprite(self);
    MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_TOUCH);
}
CLEAN_AS(func_ov143_0229a31c, TuneEditor_ResumeByTouch)

/* func_ov143_0229a334 (sub state 10): while the tune plays its step is lit (and the playback
 * is no longer pending); when no step plays once it has started, the playback is over. */
void TuneEditor_FollowPlayback(TuneEditor *self)
{
    int step = data_020df2a0;
    if (step == -1 || step >= TUNE_EDITOR_STEPS) {
        if (TuneEditor_TestFlags(self, TUNE_EDITOR_FLAG_PLAY_PENDING)) {
            return;
        }
        TuneEditor_StopPlayback(self);
    } else {
        TuneEditor_ClearFlags(self, TUNE_EDITOR_FLAG_PLAY_PENDING);
        self->lit_step = (s16) step;
    }
}
CLEAN_AS(func_ov143_0229a334, TuneEditor_FollowPlayback)

/* func_ov143_0229a374 (sub state 9): while the panel's button selected is pressed the cursor
 * sprite (when shown) follows it, 6 left of the button and down by the press's frame; at the
 * press's end the sprite is hidden and the states run again (phase 1). */
void TuneEditor_FollowPanelPress(TuneEditor *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel)) {
        if (CellLayerSprite_AnimNumber(tune_sprite_cells(self)) == 0) {
            return;
        }
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, frame + (x - 6), frame + y);
    } else {
        TuneEditor_HideCursorSprite(self);
        MenuScene_SetPhase(tune_scene(self), TUNE_EDITOR_PHASE_STATES);
    }
}
CLEAN_AS(func_ov143_0229a374, TuneEditor_FollowPanelPress)

/* func_ov143_0229a3e0: "no" to erasing: the question left, with the sound and the panel's
 * button 4 pressed. */
void TuneEditor_EraseNo(TuneEditor *self)
{
    TuneEditor_LeaveErase(self);
    SoundSys_PlaySe(TUNE_EDITOR_SOUND_BUTTON);
    ButtonPanel_Select(&self->panel, 4);
}
CLEAN_AS(func_ov143_0229a3e0, TuneEditor_EraseNo)

/* func_ov143_0229a404: "yes" to erasing: the question left with the panel's button 3 pressed
 * and the sound, and every step set to note 15. */
void TuneEditor_EraseYes(TuneEditor *self)
{
    TuneEditor_LeaveErase(self);
    ButtonPanel_Select(&self->panel, 3);
    SoundSys_PlaySe(TUNE_EDITOR_SOUND_ERASED);
    for (int i = 0; i < TUNE_EDITOR_STEPS; i++) {
        self->steps[i] = TUNE_EDITOR_NOTE_ERASED;
    }
}
CLEAN_AS(func_ov143_0229a404, TuneEditor_EraseYes)

/* func_ov143_0229a438 (sub state 8): the erase question by the keys. A touch goes on by touch;
 * left and right (repeated) put the cursor on "yes" and "no" and ease the sprite there; else A
 * presses the cursor, B says no and Start yes. */
void TuneEditor_EraseByKeys(TuneEditor *self)
{
    if (MenuScene_TakeTouch(tune_scene(self))) {
        TuneEditor_ResumeEraseByTouch(self);
        return;
    }
    u8 before = self->cursor;
    MenuScene_LatchRepeatedKeys(tune_scene(self));
    if (MenuScene_RepeatedLeft(tune_scene(self))) {
        self->cursor = TUNE_EDITOR_YES;
    } else if (MenuScene_RepeatedRight(tune_scene(self))) {
        self->cursor = TUNE_EDITOR_NO;
    }
    if (before != self->cursor) {
        TuneEditor_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & TUNE_EDITOR_PAD_A) {
        TuneEditor_PressA(self);
        return;
    }
    if (pressed & TUNE_EDITOR_PAD_B) {
        TuneEditor_HideCursorSprite(self);
        TuneEditor_EraseNo(self);
        return;
    }
    if (pressed & TUNE_EDITOR_PAD_START) {
        TuneEditor_HideCursorSprite(self);
        TuneEditor_EraseYes(self);
    }
}
CLEAN_AS(func_ov143_0229a438, TuneEditor_EraseByKeys)

/* func_ov143_0229a4e0 (sub state 7): the erase question by touch. A button goes on by the
 * keys; the pen going down on the panel's button 3 says yes, on button 4 no. */
void TuneEditor_EraseByTouch(TuneEditor *self)
{
    if (MenuScene_TakeButtons(tune_scene(self), 1)) {
        TuneEditor_ResumeEraseByKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, 3)) {
        TuneEditor_EraseYes(self);
    } else if (ButtonPanel_IsTouched(&self->panel, 4)) {
        TuneEditor_EraseNo(self);
    }
}
CLEAN_AS(func_ov143_0229a4e0, TuneEditor_EraseByTouch)

/* func_ov143_0229a54c (sub state 6): once the press's animation ends the sprite is shown again
 * and the sub state it was in comes back. */
void TuneEditor_WaitPress(TuneEditor *self)
{
    if (!CellLayerSprite_IsDone(tune_sprite_cells(self))) {
        return;
    }
    TuneEditor_ShowCursorSprite(self);
    MenuScene_SetSubState(tune_scene(self), self->return_sub_state);
}
CLEAN_AS(func_ov143_0229a54c, TuneEditor_WaitPress)

/* func_ov143_0229a570 (sub state 5): once the A press's animation ends the place under the
 * cursor acts; when it is no place, the keys go on (sub state 2) after a press of the
 * sprite. */
void TuneEditor_ActOnPress(TuneEditor *self)
{
    if (CellLayerSprite_IsDone(tune_sprite_cells(self))) {
        if (!TuneEditor_Act(self, self->cursor)) {
            MenuScene_SetSubState(tune_scene(self), TUNE_EDITOR_SUB_KEYS);
            TuneEditor_PressCursor(self);
        }
    }
}
CLEAN_AS(func_ov143_0229a570, TuneEditor_ActOnPress)

/* Obj_ov143_0229b1c0::func_ov143_0229a5a4 (sub state 4): once the cursor sprite stops, the sub
 * state it was in comes back and runs at once. */
void TuneEditor_WaitCursorSprite(TuneEditor *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(tune_scene(self), self->return_sub_state);
        TuneEditor_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov143_0229b1c019func_ov143_0229a5a4Ev, TuneEditor_WaitCursorSprite)

/* func_ov143_0229a5cc (sub state 3): while A is held, up and down (repeated) raise and lower
 * the note of the step under the cursor by a height (within 0-15): the new note sounds and the
 * sprite follows it. When A is let go the keys go on, after a press of the sprite.
 * REQUIRES: the cursor is on a step (0-15). */
void TuneEditor_AdjustStep(TuneEditor *self)
{
    if ((data_021fbe40.held & TUNE_EDITOR_PAD_A) == 0) {
        TuneEditor_Resume(self);
        TuneEditor_PressCursor(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(tune_scene(self));
    if (keys == 0) {
        return;
    }
    u8 step = self->cursor;
    u8 height = TuneEditor_HeightOfNote(self, self->steps[step]);
    u8 before = height;
    if (KeyRepeat_HasUp(keys)) {
        if (height < TUNE_EDITOR_HEIGHT_TOP) {
            height++;
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (height != 0) {
            height--;
        }
    }
    if (height != before) {
        self->steps[step] = TuneEditor_NoteOfHeight(self, height);
        TownTune_PlaySeqD3(self->steps[step]);
        int x = TuneEditor_CursorSpriteX(self);
        int y = TuneEditor_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
    }
}
CLEAN_AS(func_ov143_0229a5cc, TuneEditor_AdjustStep)

/* func_ov143_0229a67c (sub state 2): the tune by the keys. A touch goes on by touch; a d-pad
 * move eases the sprite to the new place; A presses the cursor, B leaves the tune as it was
 * and Start keeps it. */
void TuneEditor_BrowseByKeys(TuneEditor *self)
{
    if (MenuScene_TakeTouch(tune_scene(self))) {
        TuneEditor_ResumeByTouch(self);
        return;
    }
    if (TuneEditor_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(tune_scene(self)))) {
        TuneEditor_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & TUNE_EDITOR_PAD_A) {
        TuneEditor_PressA(self);
        return;
    }
    if (pressed & TUNE_EDITOR_PAD_B) {
        TuneEditor_HideCursorSprite(self);
        TuneEditor_Leave(self);
        return;
    }
    if (pressed & TUNE_EDITOR_PAD_START) {
        TuneEditor_HideCursorSprite(self);
        TuneEditor_Keep(self);
    }
}
CLEAN_AS(func_ov143_0229a67c, TuneEditor_BrowseByKeys)

/* The ROM's signed division (_s32_div_f) by a constant that is neither 0 nor -1: C's. */
static int tune_div(int numerator, int divisor)
{
    return numerator / divisor;
}

/* func_ov143_0229a6f8 (sub state 1): while the pen is down the step's height follows it: the
 * height when the drag started plus a height for each 3 lines the pen went up (within 0-15);
 * a new note sounds and is set. When the pen is up the editing goes on.
 * REQUIRES: the cursor is on a step (0-15). */
void TuneEditor_DragStep(TuneEditor *self)
{
    if (data_021fbdd8 == 0) {
        TuneEditor_Resume(self);
        return;
    }
    int height = self->drag_height + tune_div(self->drag_y - data_021f6c54, 3);
    if (height < 0) {
        height = 0;
    } else if (height > TUNE_EDITOR_HEIGHT_TOP) {
        height = TUNE_EDITOR_HEIGHT_TOP;
    }
    u8 step = self->cursor;
    u8 before = self->steps[step];
    u8 note = TuneEditor_NoteOfHeight(self, (u8) height);
    if (before == note) {
        return;
    }
    TownTune_PlaySeqD3(note);
    self->steps[step] = note;
}
CLEAN_AS(func_ov143_0229a6f8, TuneEditor_DragStep)

/* func_ov143_0229a76c (sub state 0): the tune by touch. A button goes on by the keys. When the
 * pen goes down on a step or the erase or play button it acts; else on the panel's button 1
 * the tune is kept, on button 2 left as it was. */
void TuneEditor_BrowseByTouch(TuneEditor *self)
{
    if (MenuScene_TakeButtons(tune_scene(self), 1)) {
        TuneEditor_ResumeByKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    int place = TuneEditor_TouchedPlace(self, data_021f6c58, data_021f6c54);
    if (place != TUNE_EDITOR_NOWHERE) {
        TuneEditor_Act(self, (unsigned int) place);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, 1)) {
        TuneEditor_Keep(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, 2)) {
        TuneEditor_Leave(self);
    }
}
CLEAN_AS(func_ov143_0229a76c, TuneEditor_BrowseByTouch)

/* func_ov143_0229a7fc: the panel's text colours, the notes' OBJ characters (0xc0-0xff and
 * 0x140-0x1bf) and OBJ palettes 4-13 loaded. */
void TuneEditor_LoadPanelGraphics(TuneEditor *self)
{
    ButtonPanel_LoadTextColors(&self->panel);
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov143_0229b220, heap, 8, 0xc0, 0xc0, 0xff);
    DisplayLayer_LoadCharsFromFile(data_ov143_0229b234, heap, 8, 0x140, 0x140, 0x1bf);
    DisplayLayer_LoadPalettesFromFile(data_ov143_0229b24c, heap, 8, 4, 4, 0xd);
}
CLEAN_AS(func_ov143_0229a7fc, TuneEditor_LoadPanelGraphics)

/* func_ov143_0229a868: layer 6's characters, palettes and screen loaded; layer 4's screen read
 * into `screen` and loaded. */
void TuneEditor_LoadGraphics(TuneEditor *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov143_0229b260, heap, 6, 0x11, 0x11, 0x9c);
    DisplayLayer_LoadPalettesFromFile(data_ov143_0229b274, heap, 6, 1, 1, 6);
    DisplayLayer_LoadScreenFromFile(data_ov143_0229b288, heap, 6);
    RomFile_Read(data_ov143_0229b2a0, self->screen, sizeof(self->screen));
    DisplayLayer_LoadScreen(self->screen, 4, sizeof(self->screen), 0);
}
CLEAN_AS(func_ov143_0229a868, TuneEditor_LoadGraphics)

/* func_ov143_0229a8dc: the sub screen's BG mode 0, layers 6 and 4 at priority 2 with a plain
 * control. */
void TuneEditor_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 2);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
}
CLEAN_AS(func_ov143_0229a8dc, TuneEditor_SetUpLayers)

/* func_ov143_0229a914: the end of a frame: the screen queued when it changed. */
void TuneEditor_EndFrame(TuneEditor *self)
{
    TuneEditor_QueueScreen(self);
}
CLEAN_AS(func_ov143_0229a914, TuneEditor_EndFrame)

/* func_ov143_0229a91c: the start of a frame: the screen's task ended, the labels' boxes and the
 * panel's texts closed. */
void TuneEditor_BeginFrame(TuneEditor *self)
{
    LayerTask_End(&self->screen_task);
    TuneEditor_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov143_0229a91c, TuneEditor_BeginFrame)

/* func_ov143_0229a944: the end of an interactive frame. */
void TuneEditor_EndInteractiveFrame(TuneEditor *self)
{
    TuneEditor_EndFrame(self);
}
CLEAN_AS(func_ov143_0229a944, TuneEditor_EndInteractiveFrame)

/* func_ov143_0229a94c: the start of an interactive frame, then the cursor sprite's update
 * through its class (vtable slot 3). */
void TuneEditor_BeginInteractiveFrame(TuneEditor *self)
{
    TuneEditor_BeginFrame(self);
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->cursor_sprite.vtable;
    vtable[3](&self->cursor_sprite);
}
CLEAN_AS(func_ov143_0229a94c, TuneEditor_BeginInteractiveFrame)

/* func_ov143_0229a964: the members torn down, as at a frame's start. */
void TuneEditor_Teardown(TuneEditor *self)
{
    LayerTask_End(&self->screen_task);
    TuneEditor_CloseLabels(self);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov143_0229a964, TuneEditor_Teardown)

/* func_ov143_0229a98c: the scene's own fields set up: no flag, the tune unpacked from the save
 * into the steps, the playing notes' second OBJ list pointed 4 tiles past note 15's, no step
 * lit and the cursor on the first step. */
void TuneEditor_Setup(TuneEditor *self)
{
    self->flags = 0;
    self->steps = data_021cfbbc;
    TownTune_Unpack(&data_021f3b68, self->steps);
    u16 tile = (u16) ((data_ov143_0229b028[2].attr2 & 0x3ff) + 4);
    data_ov143_0229b040[2].attr2 = (u16) ((data_ov143_0229b040[2].attr2 & 0xfc00) | (tile & 0x3ff));
    self->lit_step = -1;
    self->cursor = TUNE_EDITOR_STEP_FIRST;
}
CLEAN_AS(func_ov143_0229a98c, TuneEditor_Setup)

/* func_ov143_0229a9f4 (state 7): the fade back to the tune stepped (both screens); at its end
 * the editing goes on (phase 2). */
void TuneEditor_FadeInEdit(TuneEditor *self)
{
    if (MenuScene_StepWipeBack(tune_scene(self), -1)) {
        TuneEditor_Resume(self);
        MenuScene_SetPhase(tune_scene(self), TUNE_EDITOR_PHASE_INTERACTIVE);
    }
}
CLEAN_AS(func_ov143_0229a9f4, TuneEditor_FadeInEdit)

/* func_ov143_0229aa18 (state 6): the fade out of the erase question stepped (both screens); at
 * its end the panel back in layout 3 and the fade in started (state 7). */
void TuneEditor_FadeFromErase(TuneEditor *self)
{
    if (MenuScene_StepWipe(tune_scene(self), -1)) {
        MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_EDIT_IN);
        MenuScene_StartWipeCovered(tune_scene(self), 0, 0);
        ButtonPanel_SetLayout3(&self->panel);
    }
}
CLEAN_AS(func_ov143_0229aa18, TuneEditor_FadeFromErase)

/* func_ov143_0229aa4c (state 5): the fade in of the erase question stepped (both screens); at
 * its end the question goes on (phase 2). */
void TuneEditor_FadeInErase(TuneEditor *self)
{
    if (MenuScene_StepWipeBack(tune_scene(self), -1)) {
        TuneEditor_ResumeErase(self);
        MenuScene_SetPhase(tune_scene(self), TUNE_EDITOR_PHASE_INTERACTIVE);
    }
}
CLEAN_AS(func_ov143_0229aa4c, TuneEditor_FadeInErase)

/* func_ov143_0229aa70 (state 4): the fade out of the tune stepped (both screens); at its end
 * the panel in layout 13 with the question (message 0x8d), the fade in started (state 5) and
 * the screen dimmed. */
void TuneEditor_FadeToErase(TuneEditor *self)
{
    if (MenuScene_StepWipe(tune_scene(self), -1)) {
        MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_ERASE_IN);
        MenuScene_StartWipeCovered(tune_scene(self), 0, 0);
        ButtonPanel_SetLayout13(&self->panel, 0x8d);
        TuneEditor_Dim(self);
    }
}
CLEAN_AS(func_ov143_0229aa70, TuneEditor_FadeToErase)

/* func_ov143_0229aaac: layers 6 and 4 scrolled with the wipe, and the wipe's y kept. */
void TuneEditor_ScrollWithWipe(TuneEditor *self)
{
    MenuScene_ScrollWipe(tune_scene(self), 6, 0, 0);
    MenuScene_ScrollWipe(tune_scene(self), 4, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(tune_scene(self));
}
CLEAN_AS(func_ov143_0229aaac, TuneEditor_ScrollWithWipe)

/* func_ov143_0229aad8 (state 3): the wipe out stepped; at its end layers 6 and 4 hidden and the
 * scene deleted (phase 5); before, the layers follow it. */
void TuneEditor_WipeOut(TuneEditor *self)
{
    if (MenuScene_StepWipe(tune_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        MenuScene_SetPhase(tune_scene(self), TUNE_EDITOR_PHASE_DELETE);
    } else {
        TuneEditor_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov143_0229aad8, TuneEditor_WipeOut)

/* func_ov143_0229ab08 (state 2): the parent told the menu closes, the wipe out started on
 * window 2 (layers 2 and 8, margin 0x18) with the layers following it; state 3. */
void TuneEditor_StartWipeOut(TuneEditor *self)
{
    MenuDispatch_SetMode(tune_parent(self), TUNE_EDITOR_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(tune_scene(self), 0xa, 0, 0, 0x18);
    TuneEditor_ScrollWithWipe(self);
    MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov143_0229ab08, TuneEditor_StartWipeOut)

/* func_ov143_0229ab40 (state 1): the wipe in stepped; at its end the scene goes interactive
 * (phase 2). The layers follow the wipe. */
void TuneEditor_WipeIn(TuneEditor *self)
{
    if (MenuScene_StepWipeBack(tune_scene(self), 0)) {
        MenuScene_SetPhase(tune_scene(self), TUNE_EDITOR_PHASE_INTERACTIVE);
        TuneEditor_Resume(self);
    }
    TuneEditor_ScrollWithWipe(self);
}
CLEAN_AS(func_ov143_0229ab40, TuneEditor_WipeIn)

/* func_ov143_0229ab68 (state 0): the layers set up, the graphics loaded, the labels opened, the
 * wipe in started covered on window 2 (layers 2 and 8, 4 frames, margin 0x18), layers 6 and 4
 * shown and following it, the scene drawn, the panel in layout 3; state 1. */
void TuneEditor_StartSetup(TuneEditor *self)
{
    TuneEditor_SetUpLayers();
    TuneEditor_LoadGraphics(self);
    TuneEditor_LoadPanelGraphics(self);
    TuneEditor_OpenLabels(self);
    MenuScene_StartWipeCoveredOnWindow2(tune_scene(self), 0xa, 4, 0, 0x18);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    TuneEditor_ScrollWithWipe(self);
    TuneEditor_SetFlags(self, TUNE_EDITOR_FLAG_DRAWN);
    ButtonPanel_SetLayout3(&self->panel);
    MenuScene_SetState(tune_scene(self), TUNE_EDITOR_STATE_WIPE_IN);
}
CLEAN_AS(func_ov143_0229ab68, TuneEditor_StartSetup)

/* func_ov143_0229abcc (vtable slot 0x5c, phase 5): the scene asks to be deleted once it may
 * (TuneEditor_CanEnd). Answers 1. */
int TuneEditor_End(TuneEditor *self)
{
    if (TuneEditor_CanEnd(self)) {
        Process_RequestDelete((Process *) (void *) self);
    }
    return 1;
}
CLEAN_AS(func_ov143_0229abcc, TuneEditor_End)

/* func_ov143_0229abec (vtable slot 0x58, phase 4): nothing. */
int TuneEditor_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov143_0229abec, TuneEditor_Phase4Idle)

/* func_ov143_0229abf0 (vtable slot 0x54, phase 3): nothing. */
int TuneEditor_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov143_0229abf0, TuneEditor_Phase3Idle)

/* Obj_ov143_0229b1c0::func_ov143_0229abf4 (vtable slot 0x50, phase 2): a frame of the editor in
 * use: its start, its sub state and its end. Answers 1. */
int TuneEditor_RunInteractive(TuneEditor *self)
{
    TuneEditor_BeginInteractiveFrame(self);
    TuneEditor_RunSubState(self);
    TuneEditor_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov143_0229b1c019func_ov143_0229abf4Ev, TuneEditor_RunInteractive)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov143_0229b2c0; /* the states' guard */
extern u32 data_ov143_0229b2c4; /* the sub states' guard */
extern MemberPointer data_ov143_0229b2c8[TUNE_EDITOR_STATES];
extern MemberPointer data_ov143_0229b308[TUNE_EDITOR_SUB_STATES];
extern const MemberPointer data_ov143_0229af00, data_ov143_0229af10, data_ov143_0229af18, data_ov143_0229af20,
    data_ov143_0229af28, data_ov143_0229af30, data_ov143_0229af38, data_ov143_0229af40, data_ov143_0229af48,
    data_ov143_0229af50, data_ov143_0229af60, data_ov143_0229af68, data_ov143_0229af70, data_ov143_0229af78,
    data_ov143_0229af80, data_ov143_0229af88, data_ov143_0229af98, data_ov143_0229afa0, data_ov143_0229afa8;

/* Obj_ov143_0229b1c0::func_ov143_0229ac10: the sub state's function (TuneEditorSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 11; the game reads past the table for others. */
void TuneEditor_RunSubState(TuneEditor *self)
{
    static const MemberPointer *const sub_states[TUNE_EDITOR_SUB_STATES] = {
        &data_ov143_0229af98, &data_ov143_0229af80, &data_ov143_0229af18, &data_ov143_0229af10,
        &data_ov143_0229af48, &data_ov143_0229af40, &data_ov143_0229af28, &data_ov143_0229af20,
        &data_ov143_0229af78, &data_ov143_0229af38, &data_ov143_0229af50,
    };
    MemberTable_InitOnce(&data_ov143_0229b2c4, data_ov143_0229b308, sub_states, TUNE_EDITOR_SUB_STATES);
    MemberPointer_CallVoid(&data_ov143_0229b308[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov143_0229b1c019func_ov143_0229ac10Ev, TuneEditor_RunSubState)

/* Obj_ov143_0229b1c0::func_ov143_0229acf8 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (TuneEditorState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 8; the game reads past the table for others. */
int TuneEditor_RunState(TuneEditor *self)
{
    static const MemberPointer *const states[TUNE_EDITOR_STATES] = {
        &data_ov143_0229af88, &data_ov143_0229af00, &data_ov143_0229afa8, &data_ov143_0229afa0,
        &data_ov143_0229af60, &data_ov143_0229af68, &data_ov143_0229af70, &data_ov143_0229af30,
    };
    MemberTable_InitOnce(&data_ov143_0229b2c0, data_ov143_0229b2c8, states, TUNE_EDITOR_STATES);
    TuneEditor_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov143_0229b2c8[self->base.state], self);
    TuneEditor_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov143_0229b1c019func_ov143_0229acf8Ev, TuneEditor_RunState)

/* func_ov143_0229adc4 (vtable slot 0x24): the scene's draw: the cursor sprite (with the keys in
 * use), then, while the scene is drawn (else answers 0), the panel with the wipe, the title and
 * the steps at the wipe's y kept plus 0x60. Answers 1. */
int TuneEditor_Draw(TuneEditor *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (TuneEditor_TestFlags(self, TUNE_EDITOR_FLAG_DRAWN) == 0) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(tune_scene(self)));
    int y = self->wipe_y + 0x60;
    OamBuffer_DrawCell(1, data_ov143_0229afc0, 0x80, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    TuneEditor_DrawSteps(self, 0x80, y);
    return 1;
}
CLEAN_AS(func_ov143_0229adc4, TuneEditor_Draw)

/* func_ov143_0229ae48 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int TuneEditor_Close(TuneEditor *self)
{
    MenuDispatch_ChildClosed(tune_parent(self));
    TuneEditor_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov143_0229ae48, TuneEditor_Close)

/* func_ov143_0229ae64 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int TuneEditor_Start(TuneEditor *self)
{
    TuneEditor_Setup(self);
    self->base.state = TUNE_EDITOR_STATE_START_SETUP;
    MenuScene_SetPhase(tune_scene(self), TUNE_EDITOR_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov143_0229ae64, TuneEditor_Start)

/* func_ov143_0229ae84 (named by the profile at 0x0229af58): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
TuneEditor *TuneEditor_New(void)
{
    TuneEditor *self = MenuScene_Alloc(sizeof(TuneEditor));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov143_0229b1c0;
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    __cxa_vec_ctor(self->labels, TUNE_EDITOR_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    LayerTask_Construct(&self->screen_task);
    return self;
}
CLEAN_AS(func_ov143_0229ae84, TuneEditor_New)
