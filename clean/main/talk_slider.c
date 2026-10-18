/* The slider of a talk's slider window (talk_slider.h). */
#include "talk_slider.h"

#include "clean.h"
#include "label_box.h"
#include "menu_input.h"
#include "sound.h" /* SoundSys_PlaySe */
#include "talk_answers.h"
#include "text_draw.h"
#include "mes_bg.h"
#include "mes_slider_window.h"

static_assert(offsetof(TalkSlider, focus) == 0x2c, "talk slider");
static_assert(offsetof(TalkSlider, choices) == 0x34, "talk slider");
static_assert(sizeof(TalkSlider) == 0x38, "talk slider");

/* The OK button on the touch screen: x from 0xb8 to 0x100, y from 0xa0 to 0xb0. */
#define TALK_SLIDER_OK_LEFT 0xb8
#define TALK_SLIDER_OK_RIGHT 0x100
#define TALK_SLIDER_OK_TOP 0xa0
#define TALK_SLIDER_OK_BOTTOM 0xb0

/* Where the knob can be touched: from 5 pixels left of its x to 0x15 right, and 0x10 down from
 * its y. */
#define TALK_SLIDER_KNOB_LEFT 5
#define TALK_SLIDER_KNOB_RIGHT 0x15
#define TALK_SLIDER_KNOB_HEIGHT 0x10

/* The buttons' speed: back to this when neither up nor down is held, else this much faster
 * each frame up to the most. */
#define TALK_SLIDER_SPEED_START 0x28
#define TALK_SLIDER_SPEED_STEP 0x51
#define TALK_SLIDER_SPEED_MAX 0x199

/* The track's notches, every TALK_SLIDER_NOTCH from 0; a move shorter than
 * TALK_SLIDER_SOUND_MOVE plays no sound. */
#define TALK_SLIDER_NOTCH 0x199
#define TALK_SLIDER_NOTCHES 10
#define TALK_SLIDER_SOUND_MOVE 0x51
#define TALK_SLIDER_SE_NOTCH 0x19

static int talk_slider_clamp(int value, int low, int high)
{
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

/* func_020aa83c (the step with the OK button focused): unless a choice is taken already, the
 * level handed to the choices when the OK button is touched (touch screen) or pressed (A or
 * START). */
void TalkSlider_PressOk(TalkSlider *slider)
{
    if (slider->choices == NULL) {
        return;
    }
    if ((int) TalkAnswers_Picked(slider->choices) >= 0) {
        return;
    }
    if ((MenuInput_UsesTouch() && TalkSlider_OkTouched(slider)) ||
        (MenuInput_UsesButtons() && TalkSlider_OkPressedWithButtons(slider))) {
        TalkAnswers_PickByLevel(slider->choices, slider->level);
    }
}
CLEAN_AS(func_020aa83c, TalkSlider_PressOk)

/* func_020aa880: the OK button focused. */
void TalkSlider_FocusOk(TalkSlider *slider)
{
    slider->focus = TALK_SLIDER_FOCUS_OK;
}
CLEAN_AS(func_020aa880, TalkSlider_FocusOk)

/* func_020aa888 (the step with the knob focused): while the knob is held and can be moved, it
 * follows the touch (its y, less where it was grabbed, kept on the track) or the buttons (up
 * raises it, down lowers it, by a speed that grows while either is held). Then the notches'
 * sound when the level moved far enough to pass a notch or reach the top.
 * REQUIRES: the track's two ends at different y (the original divides by their distance). */
void TalkSlider_MoveKnob(TalkSlider *slider)
{
    if (slider->held != 0 && MesSliderWindow_GrabSettled(slider->window) != 0) {
        if (MenuInput_UsesTouch()) {
            int x;
            int y;
            if (MenuInput_TouchPosition(&x, &y)) {
                int bottom_y = MesSliderWindow_TrackBottomY(slider->window);
                int top_y = MesSliderWindow_TrackTopY(slider->window);
                int knob_y = y - slider->grab_offset;
                if (knob_y < top_y) {
                    knob_y = top_y;
                } else if (knob_y > bottom_y) {
                    knob_y = bottom_y;
                }
                slider->level = (knob_y - bottom_y) * TALK_SLIDER_LEVEL_MAX / (top_y - bottom_y);
            }
            slider->speed = 0;
        } else if (MenuInput_UsesButtons()) {
            int up = MenuInput_UpHeld();
            int down = MenuInput_DownHeld();
            if (up == 0 && down == 0) {
                slider->speed = TALK_SLIDER_SPEED_START;
            } else {
                slider->speed = talk_slider_clamp(slider->speed + TALK_SLIDER_SPEED_STEP, 0, TALK_SLIDER_SPEED_MAX);
            }
            if (up != 0) {
                slider->level += slider->speed;
            }
            if (down != 0) {
                slider->level -= slider->speed;
            }
            slider->level = talk_slider_clamp(slider->level, 0, TALK_SLIDER_LEVEL_MAX);
        }
    }

    int before = slider->last_level;
    int now = slider->level;
    int moved = now - before;
    if (moved < 0) {
        moved = -moved;
    }
    if (moved >= TALK_SLIDER_SOUND_MOVE) {
        int high = now > before ? now : before;
        int low = now > before ? before : now;
        int passed = 0;
        for (int i = 0; i < TALK_SLIDER_NOTCHES; i++) {
            int notch = i * TALK_SLIDER_NOTCH;
            if (notch >= low && notch < high) {
                passed = 1;
                break;
            }
        }
        if (high == TALK_SLIDER_LEVEL_MAX) {
            passed = 1;
        }
        if (passed) {
            SoundSys_PlaySe(TALK_SLIDER_SE_NOTCH);
        }
    }
    slider->last_level = slider->level;
}
CLEAN_AS(func_020aa888, TalkSlider_MoveKnob)

/* func_020aa9c0: the knob focused. */
void TalkSlider_FocusKnob(TalkSlider *slider)
{
    slider->focus = TALK_SLIDER_FOCUS_KNOB;
}
CLEAN_AS(func_020aa9c0, TalkSlider_FocusKnob)

/* func_020aa9c8: 1 when, with the OK button focused, START (which is noted) or A is pressed. */
int TalkSlider_OkPressedWithButtons(TalkSlider *slider)
{
    if (slider->focus != TALK_SLIDER_FOCUS_OK) {
        return 0;
    }
    if (MenuInput_StartPressed()) {
        slider->confirmed_by_start = 1;
        return 1;
    }
    return MenuInput_APressed() != 0;
}
CLEAN_AS(func_020aa9c8, TalkSlider_OkPressedWithButtons)

/* func_020aa9fc: 1 when the OK button is touched. */
int TalkSlider_OkTouched(TalkSlider *slider)
{
    (void) slider;
    return MenuInput_TouchPressedIn(TALK_SLIDER_OK_LEFT, TALK_SLIDER_OK_RIGHT, TALK_SLIDER_OK_TOP, TALK_SLIDER_OK_BOTTOM) != 0;
}
CLEAN_AS(func_020aa9fc, TalkSlider_OkTouched)

/* func_020aaa20: 1 when A is no longer held (the buttons let the knob go). */
int TalkSlider_ReleasedByButtons(TalkSlider *slider)
{
    (void) slider;
    return MenuInput_AHeld() == 0;
}
CLEAN_AS(func_020aaa20, TalkSlider_ReleasedByButtons)

/* func_020aaa38: 1 when the touch screen is no longer touched. */
int TalkSlider_ReleasedByTouch(TalkSlider *slider)
{
    (void) slider;
    return MenuInput_TouchPosition(NULL, NULL) == 0;
}
CLEAN_AS(func_020aaa38, TalkSlider_ReleasedByTouch)

/* func_020aaa54: 1 when A is pressed with the knob focused. */
int TalkSlider_GrabbedByButtons(TalkSlider *slider)
{
    return slider->focus == TALK_SLIDER_FOCUS_KNOB && MenuInput_APressed() != 0;
}
CLEAN_AS(func_020aaa54, TalkSlider_GrabbedByButtons)

/* func_020aaa74: 1 when the knob is touched; where, from its top, is kept. */
int TalkSlider_GrabbedByTouch(TalkSlider *slider)
{
    int knob_x = MesSliderWindow_TrackX(slider->window);
    int knob_y = MesSliderWindow_KnobY(slider->window);
    if (!MenuInput_TouchPressedIn(knob_x - TALK_SLIDER_KNOB_LEFT, knob_x + TALK_SLIDER_KNOB_RIGHT, knob_y,
                                  knob_y + TALK_SLIDER_KNOB_HEIGHT)) {
        return 0;
    }
    int x;
    int y;
    MenuInput_TouchPressedAt(&x, &y);
    slider->grab_offset = y - knob_y;
    return 1;
}
CLEAN_AS(func_020aaa74, TalkSlider_GrabbedByTouch)

/* ---- The slider's frame, its labels and its life */

/* The labels: the five answers' texts beside the track, in VRAM from the first tile of their
 * row, 13 tiles wide and 2 high, layer 1, on the main screen, in colour (row + 1) on
 * background 0xe. */
#define TALK_SLIDER_LABEL_CELLS 0xd
#define TALK_SLIDER_LABEL_ROWS 2
#define TALK_SLIDER_LABEL_LAYER 1
#define TALK_SLIDER_LABEL_BACKGROUND 0xe

/* The knob starts in the middle of the track. */
#define TALK_SLIDER_LEVEL_START 0x800

/* The sound of the focus moving. */
#define TALK_SLIDER_SE_FOCUS 0x0b

/* func_020aaabc: the knob taken or let go. Held, it is let go when the input in use lets it
 * go (the touch screen untouched, or A released); else it is taken when the input in use
 * grabs it (the knob touched, or A pressed with the knob focused). The menus' controls are
 * held meanwhile. */
void TalkSlider_UpdateHold(TalkSlider *slider)
{
    if (slider->held) {
        int released = 0;
        if (MenuInput_UsesTouch()) {
            released = TalkSlider_ReleasedByTouch(slider);
        } else {
            released = MenuInput_UsesButtons() && TalkSlider_ReleasedByButtons(slider);
        }
        if (released) {
            slider->held = 0;
            MenuInput_Release();
        }
    } else {
        int grabbed = 0;
        if (MenuInput_UsesTouch()) {
            grabbed = TalkSlider_GrabbedByTouch(slider);
        } else {
            grabbed = MenuInput_UsesButtons() && TalkSlider_GrabbedByButtons(slider);
        }
        if (grabbed) {
            slider->held = 1;
            MenuInput_Hold();
        }
    }
}
CLEAN_AS(func_020aaabc, TalkSlider_UpdateHold)

/* func_020aab48: the focus moved. With the touch screen, touching the OK button focuses it,
 * and holding the knob focuses the knob again. With the buttons, down or START with the knob
 * focused and let go focuses the OK button (down with a sound), and up focuses the knob again
 * (with a sound). */
void TalkSlider_UpdateFocus(TalkSlider *slider)
{
    if (MenuInput_UsesTouch()) {
        if (slider->focus == TALK_SLIDER_FOCUS_KNOB) {
            if (TalkSlider_OkTouched(slider)) {
                TalkSlider_FocusOk(slider);
            }
        } else if (slider->focus == TALK_SLIDER_FOCUS_OK) {
            if (slider->held) {
                TalkSlider_FocusKnob(slider);
            }
        }
    } else if (MenuInput_UsesButtons()) {
        if (slider->focus == TALK_SLIDER_FOCUS_KNOB) {
            if (!slider->held) {
                int down = MenuInput_DownPressed();
                int start = MenuInput_StartPressed();
                if (down || start) {
                    if (down) {
                        SoundSys_PlaySe(TALK_SLIDER_SE_FOCUS);
                    }
                    TalkSlider_FocusOk(slider);
                }
            }
        } else if (slider->focus == TALK_SLIDER_FOCUS_OK) {
            if (MenuInput_UpPressed()) {
                SoundSys_PlaySe(TALK_SLIDER_SE_FOCUS);
                TalkSlider_FocusKnob(slider);
            }
        }
    }
}
CLEAN_AS(func_020aab48, TalkSlider_UpdateFocus)

/* func_020aabe0: 1 when the input not in use was pressed (a button while the touch screen is
 * in use, a touch while the buttons are), which is then the one used. */
int TalkSlider_SwitchInput(void)
{
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
CLEAN_AS(func_020aabe0, TalkSlider_SwitchInput)

/* func_020aac1c: the labels freed. */
void TalkSlider_FreeLabels(TalkSlider *slider)
{
    for (unsigned int i = 0; i < TALK_SLIDER_LABELS; i++) {
        if (slider->labels[i] != NULL) {
            LabelBox_Free(slider->labels[i]);
            slider->labels[i] = NULL;
        }
    }
}
CLEAN_AS(func_020aac1c, TalkSlider_FreeLabels)

/* func_020aac44: the labels asked to clear. */
void TalkSlider_ClearLabels(TalkSlider *slider)
{
    for (unsigned int i = 0; i < TALK_SLIDER_LABELS; i++) {
        if (slider->labels[i] != NULL) {
            TextDraw_RequestClear(&slider->labels[i]->base, 0);
        }
    }
}
CLEAN_AS(func_020aac44, TalkSlider_ClearLabels)

/* func_020aac68: the labels asked to draw. */
void TalkSlider_DrawLabels(TalkSlider *slider)
{
    for (unsigned int i = 0; i < TALK_SLIDER_LABELS; i++) {
        if (slider->labels[i] != NULL) {
            TextDraw_RequestDraw(&slider->labels[i]->base);
        }
    }
}
CLEAN_AS(func_020aac68, TalkSlider_DrawLabels)

/* func_020aac8c: a label for each of the five answers, showing its text (vtable slot 3 of the
 * text, its characters), cleared at once; a label that cannot be allocated is left out.
 * QUIRK: always five, whatever the answers' count, at the rows of a list of five. */
void TalkSlider_MakeLabels(TalkSlider *slider)
{
    TalkAnswers *answers = slider->choices;
    for (unsigned int i = 0; i < TALK_SLIDER_LABELS; i++) {
        TalkAnswer *answer = TalkAnswers_Answer(answers, (int) i);
        int first_tile = MesBg_LabelTile((int) i, TALK_SLIDER_LABELS);
        TextBase *text = TalkAnswers_Text(answer);
        LabelBox *label = LabelBox_NewInVram(first_tile, TALK_SLIDER_LABEL_CELLS, TALK_SLIDER_LABEL_ROWS);
        if (label == NULL) {
            continue;
        }
        TextDrawBox *box = &label->base;
        box->layer = TALK_SLIDER_LABEL_LAYER;
        box->text = ((const char *(*) (TextBase *) )(uintptr_t) text->vtable->buffer)(text);
        box->screens = TEXT_DRAW_TO_MAIN;
        box->background = TALK_SLIDER_LABEL_BACKGROUND;
        box->color = (u8) (i + 1);
        box->update_mode = TEXT_DRAW_AT_ONCE;
        TextDraw_RequestClear(box, 0);
        box->update_mode = TEXT_DRAW_GROUP_0;
        slider->labels[i] = label;
    }
}
CLEAN_AS(func_020aac8c, TalkSlider_MakeLabels)

/* func_020aad08: the wider of the bottom and the top labels (the last and the first), in
 * tiles. */
void TalkSlider_MeasureLabels(TalkSlider *slider)
{
    unsigned int widest = 0;
    if (slider->labels[TALK_SLIDER_LABELS - 1] != NULL) {
        unsigned int cells = TextDraw_WidthInCells(&slider->labels[TALK_SLIDER_LABELS - 1]->base);
        if (cells > widest) {
            widest = cells;
        }
    }
    if (slider->labels[0] != NULL) {
        unsigned int cells = TextDraw_WidthInCells(&slider->labels[0]->base);
        if (cells > widest) {
            widest = cells;
        }
    }
    slider->label_cells = widest;
}
CLEAN_AS(func_020aad08, TalkSlider_MeasureLabels)

/* func_020aad3c: 1 while the touch screen is in use or once START pressed the OK button. */
int TalkSlider_TouchOrStart(TalkSlider *slider)
{
    return MenuInput_UsesTouch() || slider->confirmed_by_start != 0;
}
CLEAN_AS(func_020aad3c, TalkSlider_TouchOrStart)

/* func_020aad5c: 1 while the knob is focused and held. */
int TalkSlider_KnobHeld(TalkSlider *slider)
{
    return TalkSlider_KnobFocused(slider) && slider->held != 0;
}
CLEAN_AS(func_020aad5c, TalkSlider_KnobHeld)

/* func_020aad7c */
int TalkSlider_OkFocused(TalkSlider *slider)
{
    return slider->focus == TALK_SLIDER_FOCUS_OK;
}
CLEAN_AS(func_020aad7c, TalkSlider_OkFocused)

/* func_020aad8c */
int TalkSlider_KnobFocused(TalkSlider *slider)
{
    return slider->focus == TALK_SLIDER_FOCUS_KNOB;
}
CLEAN_AS(func_020aad8c, TalkSlider_KnobFocused)

/* The step of each focus (the game's table holds the two member functions). */
static void (*const talk_slider_steps[])(TalkSlider *) = {
    TalkSlider_MoveKnob, /* TALK_SLIDER_FOCUS_KNOB */
    TalkSlider_PressOk,  /* TALK_SLIDER_FOCUS_OK */
};

/* func_020aad9c (each frame): unless the input was switched on this frame, the knob taken or
 * let go, the focus moved, and the focus's step.
 * REQUIRES: the focus is TALK_SLIDER_FOCUS_KNOB or TALK_SLIDER_FOCUS_OK. */
void TalkSlider_Update(TalkSlider *slider)
{
    if (TalkSlider_SwitchInput()) {
        return;
    }
    TalkSlider_UpdateHold(slider);
    TalkSlider_UpdateFocus(slider);
    talk_slider_steps[slider->focus](slider);
}
CLEAN_AS(func_020aad9c, TalkSlider_Update)

/* func_020aae14: the labels freed and the answers cleared and let go. */
void TalkSlider_Close(TalkSlider *slider)
{
    TalkSlider_FreeLabels(slider);
    TalkAnswers_ClearAnswers(slider->choices);
    slider->label_cells = 0;
    slider->choices = NULL;
}
CLEAN_AS(func_020aae14, TalkSlider_Close)

/* func_020aae30 */
void TalkSlider_Hide(TalkSlider *slider)
{
    TalkSlider_ClearLabels(slider);
}
CLEAN_AS(func_020aae30, TalkSlider_Hide)

/* func_020aae38 */
void TalkSlider_Show(TalkSlider *slider)
{
    TalkSlider_DrawLabels(slider);
}
CLEAN_AS(func_020aae38, TalkSlider_Show)

/* func_020aae40: as the window opens: no answer picked, the labels made, the knob still in
 * the middle of the track and focused, the labels measured, START not pressed. */
void TalkSlider_Start(TalkSlider *slider)
{
    TalkAnswers_ClearPick(slider->choices);
    TalkSlider_MakeLabels(slider);
    slider->speed = 0;
    slider->level = TALK_SLIDER_LEVEL_START;
    slider->last_level = TALK_SLIDER_LEVEL_START;
    TalkSlider_FocusKnob(slider);
    TalkSlider_MeasureLabels(slider);
    slider->confirmed_by_start = 0;
}
CLEAN_AS(func_020aae40, TalkSlider_Start)

/* func_020aae78: the answer picked, or -1. */
int TalkSlider_Picked(TalkSlider *slider)
{
    return (int) TalkAnswers_Picked(slider->choices);
}
CLEAN_AS(func_020aae78, TalkSlider_Picked)

/* func_020aae84 */
int TalkSlider_LabelCells(TalkSlider *slider)
{
    return (int) slider->label_cells;
}
CLEAN_AS(func_020aae84, TalkSlider_LabelCells)

/* func_020aae88 */
int TalkSlider_Level(TalkSlider *slider)
{
    return slider->level;
}
CLEAN_AS(func_020aae88, TalkSlider_Level)

/* func_020aae8c: the answers to show.
 * QUIRK: their count is read and not used. */
void TalkSlider_SetChoices(TalkSlider *slider, void *choices)
{
    TalkAnswers_Count(choices);
    slider->choices = choices;
}
CLEAN_AS(func_020aae8c, TalkSlider_SetChoices)

/* func_020aaea4: the destructor: the labels freed. */
TalkSlider *TalkSlider_Destruct(TalkSlider *slider)
{
    TalkSlider_FreeLabels(slider);
    return slider;
}
CLEAN_AS(func_020aaea4, TalkSlider_Destruct)

/* func_020aaeb4: the constructor, for the slider window's message window. */
void TalkSlider_Construct(TalkSlider *slider, void *window)
{
    slider->window = window;
    slider->speed = 0;
    slider->level = TALK_SLIDER_LEVEL_START;
    slider->last_level = TALK_SLIDER_LEVEL_START;
    slider->grab_offset = 0;
    slider->label_cells = 0;
    slider->focus = TALK_SLIDER_FOCUS_KNOB;
    slider->held = 0;
    slider->confirmed_by_start = 0;
    slider->choices = NULL;
    for (unsigned int i = 0; i < TALK_SLIDER_LABELS; i++) {
        slider->labels[i] = NULL;
    }
}
CLEAN_AS(func_020aaeb4, TalkSlider_Construct)
