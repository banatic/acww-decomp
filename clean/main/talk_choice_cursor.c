/* The cursor of a talk's choice window (talk_choice_cursor.h). */
#include "talk_choice_cursor.h"

#include "autoload_2/input.h" /* PadState */
#include "clean.h"
#include "label_box.h"
#include "menu_input.h"
#include "sound.h" /* SoundSys_PlaySe */
#include "talk_answers.h"
#include "text_draw.h"

static_assert(offsetof(TalkChoiceCursor, answers) == 0x20, "talk choice cursor");
static_assert(sizeof(TalkChoiceCursor) == 0x30, "talk choice cursor");

/* The pad's buttons. */
#define TALK_CHOICE_CURSOR_PAD_A 0x0001
#define TALK_CHOICE_CURSOR_PAD_B 0x0002
#define TALK_CHOICE_CURSOR_PAD_UP 0x0040
#define TALK_CHOICE_CURSOR_PAD_DOWN 0x0080

/* A held direction moves the cursor again after this many frames, then every few frames. */
#define TALK_CHOICE_CURSOR_REPEAT_FIRST 9
#define TALK_CHOICE_CURSOR_REPEAT_NEXT 3

/* The sounds: the cursor moved, the cancelling answer picked, and the answers' own. */
#define TALK_CHOICE_CURSOR_SE_MOVE 0x0b
#define TALK_CHOICE_CURSOR_SE_CANCEL 0x2a
#define TALK_CHOICE_CURSOR_SE_ANSWER 0x29
#define TALK_CHOICE_CURSOR_SE_ANSWER_1 0x3a
#define TALK_CHOICE_CURSOR_SE_ANSWER_2 0x6a
#define TALK_CHOICE_CURSOR_SE_ANSWER_3 0x6c

/* The labels: in VRAM from the first tile of their row, 13 tiles wide and 2 high, layer 1, on
 * the main screen, in colour (row + 1) on background 0xe, underlined. */
#define TALK_CHOICE_CURSOR_LABEL_CELLS 0xd
#define TALK_CHOICE_CURSOR_LABEL_ROWS 2
#define TALK_CHOICE_CURSOR_LABEL_LAYER 1
#define TALK_CHOICE_CURSOR_LABEL_BACKGROUND 0xe

extern PadState data_021fbe40;

/* An answer, its text and its sound kind (talk_answers.h). */
extern TalkAnswer *func_020ab550(TalkAnswers *answers, int index);
extern TextBase *func_020ab798(TalkAnswer *answer);
extern u32 func_020ab780(TalkAnswer *answer);
/* The pick cleared, and all the answers cleared. */
extern void func_020ab58c(TalkAnswers *answers);
extern void func_020ab558(TalkAnswers *answers);
/* The first VRAM tile of label `row` of `rows`. */
extern int func_020ac318(int row, int rows);
/* The message window's row at (x, y), or -1. */
extern int func_020ac148(void *window, int x, int y);

/* func_020aaee8: the sound of the answer under the cursor. */
void TalkChoiceCursor_PlayAnswerSound(TalkChoiceCursor *cursor)
{
    u32 kind = func_020ab780(func_020ab550(cursor->answers, cursor->position));
    int sound = TALK_CHOICE_CURSOR_SE_ANSWER;
    if (kind == TALK_ANSWER_SOUND_1) {
        sound = TALK_CHOICE_CURSOR_SE_ANSWER_1;
    } else if (kind == TALK_ANSWER_SOUND_2) {
        sound = TALK_CHOICE_CURSOR_SE_ANSWER_2;
    } else if (kind == TALK_ANSWER_SOUND_3) {
        sound = TALK_CHOICE_CURSOR_SE_ANSWER_3;
    }
    SoundSys_PlaySe(sound);
}
CLEAN_AS(func_020aaee8, TalkChoiceCursor_PlayAnswerSound)

/* func_020aaf20 (with the buttons): 1 when an answer is picked, the one under the cursor.
 * After B the cancelling answer is picked when its frames run out; else A picks the answer
 * under the cursor; B (when there is a cancelling answer) puts the cursor on it, holding the
 * controls until it is picked; else up and down move the cursor: at once when first pressed,
 * then while held after 9 frames and every 3, the controls held meanwhile.
 * QUIRK: the pad is read directly, not through menu_input.h, so a control held with the
 * touch screen does not hide the buttons here. */
int TalkChoiceCursor_StepButtons(TalkChoiceCursor *cursor)
{
    int cancel = TalkAnswers_Cancel(cursor->answers);

    if (cursor->cancel_frames > 0) {
        cursor->cancel_frames--;
        if (cursor->cancel_frames <= 0) {
            MenuInput_Release();
            return 1;
        }
    }

    u16 pressed = data_021fbe40.pressed;
    if (pressed & TALK_CHOICE_CURSOR_PAD_A) {
        if (cancel >= 0 && cancel == cursor->position) {
            SoundSys_PlaySe(TALK_CHOICE_CURSOR_SE_CANCEL);
        } else {
            TalkChoiceCursor_PlayAnswerSound(cursor);
        }
        MenuInput_Release();
        return 1;
    }
    if (cancel >= 0 && (pressed & TALK_CHOICE_CURSOR_PAD_B)) {
        SoundSys_PlaySe(TALK_CHOICE_CURSOR_SE_CANCEL);
        cursor->position = TalkAnswers_Cancel(cursor->answers);
        cursor->cancel_frames = 1;
        MenuInput_Hold();
        return 0;
    }

    u16 held = data_021fbe40.held;
    int up_held = (held & TALK_CHOICE_CURSOR_PAD_UP) != 0;
    int down_held = (held & TALK_CHOICE_CURSOR_PAD_DOWN) != 0;
    int up_pressed = (pressed & TALK_CHOICE_CURSOR_PAD_UP) != 0;
    int down_pressed = (pressed & TALK_CHOICE_CURSOR_PAD_DOWN) != 0;
    int last = (int) TalkAnswers_Count(cursor->answers) - 1;
    int before = cursor->position;
    int move = 0;
    int direction = cursor->direction;

    if (direction == 0 && (up_held || down_held) && (up_pressed || down_pressed)) {
        move = 1;
        MenuInput_Hold();
        cursor->repeat_frames = TALK_CHOICE_CURSOR_REPEAT_FIRST;
        cursor->direction = up_held ? -1 : 1;
    } else if ((direction > 0 && down_held) || (direction < 0 && up_held)) {
        if (cursor->repeat_frames > 0) {
            cursor->repeat_frames--;
            if (cursor->repeat_frames <= 0) {
                move = 1;
                cursor->repeat_frames = TALK_CHOICE_CURSOR_REPEAT_NEXT;
            }
        }
    } else {
        if (direction != 0) {
            MenuInput_Release();
        }
        cursor->direction = 0;
        cursor->repeat_frames = 0;
    }

    if (move) {
        cursor->position += cursor->direction;
    }
    if (cursor->position < 0) {
        cursor->position = last;
    } else if (cursor->position > last) {
        cursor->position = 0;
    }
    if (before != cursor->position) {
        SoundSys_PlaySe(TALK_CHOICE_CURSOR_SE_MOVE);
    }
    return 0;
}
CLEAN_AS(func_020aaf20, TalkChoiceCursor_StepButtons)

/* func_020ab0a4 (with the touch screen): 1 when an answer's row is touched; the cursor is put
 * on it and its sound played (the cancel sound for the cancelling answer). */
int TalkChoiceCursor_StepTouch(TalkChoiceCursor *cursor)
{
    int x;
    int y;
    if (!MenuInput_TouchPressedAt(&x, &y)) {
        return 0;
    }
    int row = func_020ac148(cursor->window, x, y);
    if (row < 0) {
        return 0;
    }
    cursor->position = row;
    int cancel = TalkAnswers_Cancel(cursor->answers);
    if (cancel >= 0 && cancel == row) {
        SoundSys_PlaySe(TALK_CHOICE_CURSOR_SE_CANCEL);
    } else {
        TalkChoiceCursor_PlayAnswerSound(cursor);
    }
    return 1;
}
CLEAN_AS(func_020ab0a4, TalkChoiceCursor_StepTouch)

/* func_020ab0f4: 1 when the input not in use was pressed (a button while the touch screen is
 * in use, a touch while the buttons are), which is then the one used. */
int TalkChoiceCursor_SwitchInput(TalkChoiceCursor *cursor)
{
    (void) cursor;
    if (MenuInput_UsesTouch()) {
        if (MenuInput_AnyPressed()) {
            MenuInput_UseButtons();
            return 1;
        }
    } else if (MenuInput_UsesButtons()) {
        if (MenuInput_TouchPressed()) {
            MenuInput_UseTouch();
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020ab0f4, TalkChoiceCursor_SwitchInput)

/* func_020ab130: the labels freed. */
void TalkChoiceCursor_FreeLabels(TalkChoiceCursor *cursor)
{
    for (unsigned int i = 0; i < TALK_CHOICE_CURSOR_LABELS; i++) {
        if (cursor->labels[i] != NULL) {
            LabelBox_Free(cursor->labels[i]);
            cursor->labels[i] = NULL;
        }
    }
}
CLEAN_AS(func_020ab130, TalkChoiceCursor_FreeLabels)

/* func_020ab158: the labels asked to clear. */
void TalkChoiceCursor_ClearLabels(TalkChoiceCursor *cursor)
{
    for (unsigned int i = 0; i < TALK_CHOICE_CURSOR_LABELS; i++) {
        if (cursor->labels[i] != NULL) {
            TextDraw_RequestClear(&cursor->labels[i]->base, 0);
        }
    }
}
CLEAN_AS(func_020ab158, TalkChoiceCursor_ClearLabels)

/* func_020ab17c: the labels asked to draw. */
void TalkChoiceCursor_DrawLabels(TalkChoiceCursor *cursor)
{
    for (unsigned int i = 0; i < TALK_CHOICE_CURSOR_LABELS; i++) {
        if (cursor->labels[i] != NULL) {
            TextDraw_RequestDraw(&cursor->labels[i]->base);
        }
    }
}
CLEAN_AS(func_020ab17c, TalkChoiceCursor_DrawLabels)

/* func_020ab1a0: a label for each answer, showing its text (vtable slot 3 of the text, its
 * characters), cleared at once; a label that cannot be allocated is left out.
 * REQUIRES: at most five answers (the labels are five). */
void TalkChoiceCursor_MakeLabels(TalkChoiceCursor *cursor)
{
    unsigned int count = TalkAnswers_Count(cursor->answers);
    for (unsigned int i = 0; i < count; i++) {
        TalkAnswer *answer = func_020ab550(cursor->answers, (int) i);
        int first_tile = func_020ac318((int) i, (int) count);
        TextBase *text = func_020ab798(answer);
        LabelBox *label = LabelBox_NewInVram(first_tile, TALK_CHOICE_CURSOR_LABEL_CELLS, TALK_CHOICE_CURSOR_LABEL_ROWS);
        if (label == NULL) {
            continue;
        }
        TextDrawBox *box = &label->base;
        box->layer = TALK_CHOICE_CURSOR_LABEL_LAYER;
        box->text = ((const char *(*) (TextBase *) )(uintptr_t) text->vtable->buffer)(text);
        box->screens = TEXT_DRAW_TO_MAIN;
        box->background = TALK_CHOICE_CURSOR_LABEL_BACKGROUND;
        box->color = (u8) (i + 1);
        box->underline = 1;
        box->update_mode = TEXT_DRAW_AT_ONCE;
        TextDraw_RequestClear(box, 0);
        box->update_mode = TEXT_DRAW_GROUP_0;
        cursor->labels[i] = label;
    }
}
CLEAN_AS(func_020ab1a0, TalkChoiceCursor_MakeLabels)

/* func_020ab230: no direction held. */
void TalkChoiceCursor_StopRepeat(TalkChoiceCursor *cursor)
{
    cursor->repeat_frames = 0;
    cursor->direction = 0;
}
CLEAN_AS(func_020ab230, TalkChoiceCursor_StopRepeat)

/* func_020ab238: the widest of the answers' labels, in tiles. */
void TalkChoiceCursor_MeasureLabels(TalkChoiceCursor *cursor)
{
    unsigned int count = TalkAnswers_Count(cursor->answers);
    unsigned int widest = 0;
    for (unsigned int i = 0; i < count; i++) {
        if (cursor->labels[i] != NULL) {
            unsigned int cells = TextDraw_WidthInCells(&cursor->labels[i]->base);
            if (cells > widest) {
                widest = cells;
            }
        }
    }
    cursor->label_cells = widest;
}
CLEAN_AS(func_020ab238, TalkChoiceCursor_MeasureLabels)

/* func_020ab270 */
int TalkChoiceCursor_UsesTouch(TalkChoiceCursor *cursor)
{
    (void) cursor;
    return MenuInput_UsesTouch();
}
CLEAN_AS(func_020ab270, TalkChoiceCursor_UsesTouch)

/* func_020ab278 (each frame): while there are answers and none is picked, the input switched
 * (the held direction dropped), or else the step of the input in use, which may pick the
 * answer under the cursor. */
void TalkChoiceCursor_Update(TalkChoiceCursor *cursor)
{
    if (cursor->answers == NULL || (int) TalkAnswers_Picked(cursor->answers) >= 0) {
        return;
    }
    if (TalkChoiceCursor_SwitchInput(cursor)) {
        TalkChoiceCursor_StopRepeat(cursor);
        return;
    }
    int picked = 0;
    if (MenuInput_UsesTouch()) {
        picked = TalkChoiceCursor_StepTouch(cursor);
    } else if (MenuInput_UsesButtons()) {
        picked = TalkChoiceCursor_StepButtons(cursor);
    }
    if (picked) {
        TalkAnswers_Pick(cursor->answers, cursor->position);
    }
}
CLEAN_AS(func_020ab278, TalkChoiceCursor_Update)

/* func_020ab2e0: the labels freed and the answers cleared and let go. */
void TalkChoiceCursor_Close(TalkChoiceCursor *cursor)
{
    TalkChoiceCursor_FreeLabels(cursor);
    func_020ab558(cursor->answers);
    cursor->label_cells = 0;
    cursor->answers = NULL;
}
CLEAN_AS(func_020ab2e0, TalkChoiceCursor_Close)

/* func_020ab2fc */
void TalkChoiceCursor_Hide(TalkChoiceCursor *cursor)
{
    TalkChoiceCursor_ClearLabels(cursor);
}
CLEAN_AS(func_020ab2fc, TalkChoiceCursor_Hide)

/* func_020ab304 */
void TalkChoiceCursor_Show(TalkChoiceCursor *cursor)
{
    TalkChoiceCursor_DrawLabels(cursor);
}
CLEAN_AS(func_020ab304, TalkChoiceCursor_Show)

/* func_020ab30c: as the window opens: no answer picked, the labels made, the cursor on the
 * first answer, and the labels measured. */
void TalkChoiceCursor_Start(TalkChoiceCursor *cursor)
{
    func_020ab58c(cursor->answers);
    TalkChoiceCursor_MakeLabels(cursor);
    cursor->position = 0;
    cursor->cancel_frames = 0;
    TalkChoiceCursor_StopRepeat(cursor);
    TalkChoiceCursor_MeasureLabels(cursor);
}
CLEAN_AS(func_020ab30c, TalkChoiceCursor_Start)

/* func_020ab334 */
int TalkChoiceCursor_LabelCells(TalkChoiceCursor *cursor)
{
    return (int) cursor->label_cells;
}
CLEAN_AS(func_020ab334, TalkChoiceCursor_LabelCells)

/* func_020ab338: the answer picked, or -1. */
int TalkChoiceCursor_Picked(TalkChoiceCursor *cursor)
{
    return (int) TalkAnswers_Picked(cursor->answers);
}
CLEAN_AS(func_020ab338, TalkChoiceCursor_Picked)

/* func_020ab344 */
int TalkChoiceCursor_Position(TalkChoiceCursor *cursor)
{
    return cursor->position;
}
CLEAN_AS(func_020ab344, TalkChoiceCursor_Position)

/* func_020ab348: how many answers (the window's layout). */
unsigned int TalkChoiceCursor_Count(TalkChoiceCursor *cursor)
{
    return TalkAnswers_Count(cursor->answers);
}
CLEAN_AS(func_020ab348, TalkChoiceCursor_Count)

/* func_020ab354: the answers to show.
 * QUIRK: their count is read and not used. */
void TalkChoiceCursor_SetAnswers(TalkChoiceCursor *cursor, struct TalkAnswers *answers)
{
    TalkAnswers_Count(answers);
    cursor->answers = answers;
}
CLEAN_AS(func_020ab354, TalkChoiceCursor_SetAnswers)

/* func_020ab36c: the destructor: the labels freed. */
TalkChoiceCursor *TalkChoiceCursor_Destruct(TalkChoiceCursor *cursor)
{
    TalkChoiceCursor_FreeLabels(cursor);
    return cursor;
}
CLEAN_AS(func_020ab36c, TalkChoiceCursor_Destruct)

/* func_020ab37c: the constructor, for the choice window's message window. */
void TalkChoiceCursor_Construct(TalkChoiceCursor *cursor, void *window)
{
    cursor->position = 0;
    cursor->window = window;
    cursor->label_cells = 0;
    cursor->answers = NULL;
    cursor->cancel_frames = 0;
    cursor->repeat_frames = 0;
    cursor->direction = 0;
    for (unsigned int i = 0; i < TALK_CHOICE_CURSOR_LABELS; i++) {
        cursor->labels[i] = NULL;
    }
}
CLEAN_AS(func_020ab37c, TalkChoiceCursor_Construct)
