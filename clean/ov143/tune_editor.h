/* The scene of overlay 143 (vtable 0x0229b1c0, include/cpp/ov143/Obj_ov143_0229b1c0.h;
 * constructor TuneEditor_New, 0x11c0 bytes): a menu scene (ov002/menu_scene.h) where the town
 * tune is written, as the evidence says:
 *
 * - overlay 92's dispatcher opens it as overlay group 0x25 for GroupParams' mode 0x3f, with
 *   the music volume's slot 1 at index 2 (ov092/menu_dispatch.c); its files are under
 *   "menu/melody/";
 * - it edits the town tune unpacked a step to a byte (data_021cfbbc, main/town_tune.h): 16
 *   steps in two rows of eight, each drawn as its note's OBJs raised by the note's height
 *   (TuneEditor_StepPlace, TuneEditor_DrawSteps). A step's note is changed by dragging it up
 *   or down or by up and down with A held, and played as it changes (TownTune_PlaySeqD3);
 * - the play button plays the tune (TownTune_Play), lighting the step playing; the erase
 *   button asks (panel layout 13, message 0x8d) and on yes sets every step to note 15;
 * - the panel's button 1 keeps the tune (packed into the save, used at once and, when linked,
 *   sent to the others) and tells main so (GroupParams_SetC4C(1)); button 2 leaves it as it was
 *   (GroupParams_SetC4C(0)).
 *
 * A note (0-15) has a height (0-15, TuneEditor_HeightOfNote): notes 0-12 are heights 2-14,
 * note 13 height 15, note 14 height 1 and note 15 height 0. */
#ifndef CLEAN_OV143_TUNE_EDITOR_H
#define CLEAN_OV143_TUNE_EDITOR_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

#define TUNE_EDITOR_STEPS 16
#define TUNE_EDITOR_ROW_STEPS 8
#define TUNE_EDITOR_LABELS 16

/* The note every step gets when the tune is erased, and the highest height. */
#define TUNE_EDITOR_NOTE_ERASED 15
#define TUNE_EDITOR_HEIGHT_TOP 15

/* The places of the cursor (`cursor`). */
enum TuneEditorPlace {
    TUNE_EDITOR_STEP_FIRST = 0, /* 0-7: the top row of steps, 8-15 the bottom row */
    TUNE_EDITOR_STEP_LAST = 15,
    TUNE_EDITOR_ERASE = 0x10,  /* the erase button */
    TUNE_EDITOR_PLAY = 0x11,   /* the play button */
    TUNE_EDITOR_KEEP = 0x12,   /* the panel's button 1: the tune is kept */
    TUNE_EDITOR_LEAVE = 0x13,  /* the panel's button 2: the tune is left as it was */
    TUNE_EDITOR_YES = 0x14,    /* the panel's button 3 while erasing: erase */
    TUNE_EDITOR_NO = 0x15,     /* the panel's button 4 while erasing: do not */
    TUNE_EDITOR_NOWHERE = 0x16 /* TuneEditor_TouchedPlace: no place touched */
};

/* In `flags`. */
enum TuneEditorFlag {
    TUNE_EDITOR_FLAG_DRAWN = 0x01,        /* the scene is drawn (TuneEditor_Draw) */
    TUNE_EDITOR_FLAG_PLAYING = 0x02,      /* the tune plays: the lit step is the one playing */
    TUNE_EDITOR_FLAG_SCREEN_DIRTY = 0x04, /* `screen` is queued for layer 4 at the frame's end */
    TUNE_EDITOR_FLAG_PLAY_PENDING = 0x08  /* the tune has not started playing yet */
};

/* The states, run from the table of TuneEditor_RunState (MenuScene_SetState). */
enum TuneEditorState {
    TUNE_EDITOR_STATE_START_SETUP = 0,    /* TuneEditor_StartSetup */
    TUNE_EDITOR_STATE_WIPE_IN = 1,        /* TuneEditor_WipeIn */
    TUNE_EDITOR_STATE_START_WIPE_OUT = 2, /* TuneEditor_StartWipeOut */
    TUNE_EDITOR_STATE_WIPE_OUT = 3,       /* TuneEditor_WipeOut */
    TUNE_EDITOR_STATE_TO_ERASE = 4,       /* TuneEditor_FadeToErase */
    TUNE_EDITOR_STATE_ERASE_IN = 5,       /* TuneEditor_FadeInErase */
    TUNE_EDITOR_STATE_FROM_ERASE = 6,     /* TuneEditor_FadeFromErase */
    TUNE_EDITOR_STATE_EDIT_IN = 7,        /* TuneEditor_FadeInEdit */
    TUNE_EDITOR_STATES = 8
};

/* The sub states, run from the table of TuneEditor_RunSubState (MenuScene_SetSubState). */
enum TuneEditorSubState {
    TUNE_EDITOR_SUB_TOUCH = 0,       /* TuneEditor_BrowseByTouch */
    TUNE_EDITOR_SUB_DRAG = 1,        /* TuneEditor_DragStep */
    TUNE_EDITOR_SUB_KEYS = 2,        /* TuneEditor_BrowseByKeys */
    TUNE_EDITOR_SUB_ADJUST = 3,      /* TuneEditor_AdjustStep */
    TUNE_EDITOR_SUB_SPRITE_MOVE = 4, /* TuneEditor_WaitCursorSprite */
    TUNE_EDITOR_SUB_A_PRESS = 5,     /* TuneEditor_ActOnPress */
    TUNE_EDITOR_SUB_PRESS = 6,       /* TuneEditor_WaitPress */
    TUNE_EDITOR_SUB_ERASE_TOUCH = 7, /* TuneEditor_EraseByTouch */
    TUNE_EDITOR_SUB_ERASE_KEYS = 8,  /* TuneEditor_EraseByKeys */
    TUNE_EDITOR_SUB_PANEL_PRESS = 9, /* TuneEditor_FollowPanelPress */
    TUNE_EDITOR_SUB_PLAYING = 10,    /* TuneEditor_FollowPlayback */
    TUNE_EDITOR_SUB_STATES = 11
};

/* The phases set (MenuScene_SetPhase): 0 waits (vtable slot 0x48), 1 runs the states (slot
 * 0x4c), 2 the sub states (slot 0x50) and 5 deletes the scene (slot 0x5c). */
#define TUNE_EDITOR_PHASE_WAIT 0
#define TUNE_EDITOR_PHASE_STATES 1
#define TUNE_EDITOR_PHASE_INTERACTIVE 2
#define TUNE_EDITOR_PHASE_DELETE 5

typedef struct TuneEditor {
    MenuScene base;                       /* 0x000 */
    s32 wipe_y;                           /* 0x094: MenuScene_WipeOffsetY's */
    u16 flags;                            /* 0x098: TuneEditorFlag */
    s16 lit_step;                         /* 0x09a: the step drawn lit, -1 for none */
    s16 sequence;                         /* 0x09c: the session's frame sequence when the tune was
                                         * sent */
    u8 return_sub_state;                  /* 0x09e: the sub state to go back to once the sprite
                                         * stops or the press ends */
    u8 labels_used;                       /* 0x09f: the labels handed out (TuneEditor_NextLabel) */
    u8 *steps;                            /* 0x0a0: the tune, a note to a step (data_021cfbbc) */
    u8 cursor;                            /* 0x0a4: TuneEditorPlace */
    u8 drag_height;                       /* 0x0a5: the step's height when the drag started */
    u8 pad_0a6[2];                        /* 0x0a6 */
    s32 drag_y;                           /* 0x0a8: the pen's y when the drag started */
    Glider cursor_sprite;                 /* 0x0ac: a Glider0 */
    ButtonPanel panel;                    /* 0x110 */
    TextLabel labels[TUNE_EDITOR_LABELS]; /* 0x2dc: the notes' labels and the title's */
    u16 screen[0x400];                    /* 0x99c: layer 4's screen */
    LayerTask screen_task;                /* 0x119c: `screen` to layer 4 */
} TuneEditor;

TuneEditor *TuneEditor_Destroy(TuneEditor *self);
TuneEditor *TuneEditor_Delete(TuneEditor *self);
void TuneEditor_ClearFlags(TuneEditor *self, u16 flags);
void TuneEditor_SetFlags(TuneEditor *self, u16 flags);
int TuneEditor_TestFlags(TuneEditor *self, u16 flags);
void TuneEditor_Undim(TuneEditor *self);
void TuneEditor_Dim(TuneEditor *self);
void TuneEditor_StepPlace(TuneEditor *self, int *place, int step);
void TuneEditor_OpenLabels(TuneEditor *self);
void TuneEditor_OpenNoteLabel(TuneEditor *self, int message, int note);
u8 TuneEditor_NoteOfHeight(TuneEditor *self, int height);
u8 TuneEditor_HeightOfNote(TuneEditor *self, int note);
void TuneEditor_DrawSteps(TuneEditor *self, int x, int y);
void TuneEditor_DrawLitStep(TuneEditor *self, int step, int x, int y);
void TuneEditor_DrawStep(TuneEditor *self, int note, int x, int y);
void TuneEditor_DrawPickedStep(TuneEditor *self, int note, int x, int y);
void TuneEditor_DrawPlayingStep(TuneEditor *self, unsigned int note, int x, int y);
void TuneEditor_CloseLabels(TuneEditor *self);
TextLabel *TuneEditor_NextLabel(TuneEditor *self);
void TuneEditor_LeaveErase(TuneEditor *self);
void TuneEditor_AskErase(TuneEditor *self);
void TuneEditor_StopPlayback(TuneEditor *self);
void TuneEditor_StartPlayback(TuneEditor *self);
void TuneEditor_SetErasePalette(TuneEditor *self, int palette);
void TuneEditor_SetPlayPalette(TuneEditor *self, int palette);
void TuneEditor_QueueScreen(TuneEditor *self);
int TuneEditor_MoveCursor(TuneEditor *self, int keys);
int TuneEditor_Act(TuneEditor *self, unsigned int place);
int TuneEditor_TouchedPlace(TuneEditor *self, int x, int y);
void TuneEditor_PressCursor(TuneEditor *self);
void TuneEditor_PressA(TuneEditor *self);
void TuneEditor_ShowCursorSprite(TuneEditor *self);
void TuneEditor_EaseTo(TuneEditor *self, int x, int y);
void TuneEditor_GlideToCursor(TuneEditor *self);
void TuneEditor_HideCursorSprite(TuneEditor *self);
int TuneEditor_CursorSpriteY(TuneEditor *self);
int TuneEditor_CursorSpriteX(TuneEditor *self);
void TuneEditor_ShowCursorAtCursor(TuneEditor *self);
int TuneEditor_CanEnd(TuneEditor *self);
void TuneEditor_SendTune(TuneEditor *self);
void TuneEditor_Leave(TuneEditor *self);
void TuneEditor_Keep(TuneEditor *self);
void TuneEditor_ResumeErase(TuneEditor *self);
void TuneEditor_ResumeEraseByKeys(TuneEditor *self);
void TuneEditor_ResumeEraseByTouch(TuneEditor *self);
void TuneEditor_Resume(TuneEditor *self);
void TuneEditor_ResumeByKeys(TuneEditor *self);
void TuneEditor_ResumeByTouch(TuneEditor *self);
void TuneEditor_FollowPlayback(TuneEditor *self);
void TuneEditor_FollowPanelPress(TuneEditor *self);
void TuneEditor_EraseNo(TuneEditor *self);
void TuneEditor_EraseYes(TuneEditor *self);
void TuneEditor_EraseByKeys(TuneEditor *self);
void TuneEditor_EraseByTouch(TuneEditor *self);
void TuneEditor_WaitPress(TuneEditor *self);
void TuneEditor_ActOnPress(TuneEditor *self);
void TuneEditor_WaitCursorSprite(TuneEditor *self);
void TuneEditor_AdjustStep(TuneEditor *self);
void TuneEditor_BrowseByKeys(TuneEditor *self);
void TuneEditor_DragStep(TuneEditor *self);
void TuneEditor_BrowseByTouch(TuneEditor *self);
void TuneEditor_LoadPanelGraphics(TuneEditor *self);
void TuneEditor_LoadGraphics(TuneEditor *self);
void TuneEditor_SetUpLayers(void);
void TuneEditor_EndFrame(TuneEditor *self);
void TuneEditor_BeginFrame(TuneEditor *self);
void TuneEditor_EndInteractiveFrame(TuneEditor *self);
void TuneEditor_BeginInteractiveFrame(TuneEditor *self);
void TuneEditor_Teardown(TuneEditor *self);
void TuneEditor_Setup(TuneEditor *self);
void TuneEditor_FadeInEdit(TuneEditor *self);
void TuneEditor_FadeFromErase(TuneEditor *self);
void TuneEditor_FadeInErase(TuneEditor *self);
void TuneEditor_FadeToErase(TuneEditor *self);
void TuneEditor_ScrollWithWipe(TuneEditor *self);
void TuneEditor_WipeOut(TuneEditor *self);
void TuneEditor_StartWipeOut(TuneEditor *self);
void TuneEditor_WipeIn(TuneEditor *self);
void TuneEditor_StartSetup(TuneEditor *self);
int TuneEditor_End(TuneEditor *self);
int TuneEditor_Phase4Idle(void);
int TuneEditor_Phase3Idle(void);
int TuneEditor_RunInteractive(TuneEditor *self);
void TuneEditor_RunSubState(TuneEditor *self);
int TuneEditor_RunState(TuneEditor *self);
int TuneEditor_Draw(TuneEditor *self);
int TuneEditor_Close(TuneEditor *self);
int TuneEditor_Start(TuneEditor *self);
TuneEditor *TuneEditor_New(void);

#endif
