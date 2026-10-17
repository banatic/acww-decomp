/* The scene of overlay 91 (overlay group 12, which GroupParams_OpenGroup12 opens with a letter;
 * vtable 0x02299530, include/cpp/ov091/Obj_ov091_02299530.h; constructor LetterReader_New, 0x498
 * bytes): a menu scene (ov002/menu_scene.h) that shows the letter at GroupParams_Pointer with
 * main's letter view (main/letter_view.h) on layers 0 and 2 of the main screen, wiped in and out
 * on window 0, with a label button (message 0x65) at the lower right that ends it.
 *
 * The button is pressed by touch (sub state 0) or, once a button of the pad was pressed, by A
 * or B with a cursor sprite (a Glider1, ov002/glide.h) pointing at it (sub state 1); the pen
 * and the pad switch between the two. */
#ifndef CLEAN_OV091_LETTER_READER_H
#define CLEAN_OV091_LETTER_READER_H

#include "main/letter_view.h"
#include "ov002/glide.h"
#include "ov002/label_button.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* The states (MenuScene.state), run by LetterReader_RunState. */
enum LetterReaderState {
    LETTER_READER_STATE_SHOW = 0,     /* LetterReader_ShowLetter */
    LETTER_READER_STATE_WIPE_IN = 1,  /* LetterReader_WipeIn */
    LETTER_READER_STATE_PRESS = 2,    /* LetterReader_WaitCursorPress */
    LETTER_READER_STATE_BUTTON = 3,   /* LetterReader_WaitButton */
    LETTER_READER_STATE_CLOSE = 4,    /* LetterReader_StartWipeOut */
    LETTER_READER_STATE_WIPE_OUT = 5, /* LetterReader_WipeOut */
    LETTER_READER_STATES = 6
};

/* The sub states (MenuScene.sub_state), run by LetterReader_RunInteractive. */
enum LetterReaderSubState {
    LETTER_READER_SUB_TOUCH = 0, /* LetterReader_TouchInput */
    LETTER_READER_SUB_PAD = 1,   /* LetterReader_PadInput */
    LETTER_READER_SUB_STATES = 2
};

/* The phases the scene sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase 1 by
 * the vtable's slot 0x4c, 2 by 0x50 and 5 by 0x5c). */
enum LetterReaderPhase {
    LETTER_READER_PHASE_STATES = 1,      /* LetterReader_RunState */
    LETTER_READER_PHASE_INTERACTIVE = 2, /* LetterReader_RunInteractive */
    LETTER_READER_PHASE_DELETE = 5       /* LetterReader_RequestDelete */
};

typedef struct LetterReader {
    MenuScene base;     /* 0x00 */
    LetterView view;    /* 0x94 */
    LabelButton button; /* 0x3bc: a LabelButton1 */
    Glider cursor;      /* 0x434: a Glider1 */
} LetterReader;

LetterReader *LetterReader_Destroy(LetterReader *self);
LetterReader *LetterReader_Delete(LetterReader *self);
void LetterReader_UsePad(LetterReader *self);
void LetterReader_UseTouch(LetterReader *self);
void LetterReader_PadInput(LetterReader *self);
void LetterReader_TouchInput(LetterReader *self);
void LetterReader_EndFrame(void);
void LetterReader_BeginFrame(void);
void LetterReader_ReleaseView(LetterReader *self);
void LetterReader_Init(LetterReader *self);
void LetterReader_WipeOut(LetterReader *self);
void LetterReader_StartWipeOut(LetterReader *self);
void LetterReader_WaitButton(LetterReader *self);
void LetterReader_WaitCursorPress(LetterReader *self);
void LetterReader_WipeIn(LetterReader *self);
void LetterReader_ShowLetter(LetterReader *self);
int LetterReader_RequestDelete(LetterReader *self);
int LetterReader_Phase4(void);
int LetterReader_Phase3(void);
int LetterReader_RunInteractive(LetterReader *self);
int LetterReader_RunState(LetterReader *self);
int LetterReader_Draw(LetterReader *self);
int LetterReader_End(LetterReader *self);
int LetterReader_Start(LetterReader *self);
LetterReader *LetterReader_New(void);

#endif
