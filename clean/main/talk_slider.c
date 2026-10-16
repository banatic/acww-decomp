/* The slider of a talk's slider window (talk_slider.h). */
#include "talk_slider.h"

#include "clean.h"
#include "menu_input.h"
#include "sound.h" /* SoundSys_PlaySe */

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

/* The talk's choices: the one taken (negative while none is), and the one taken from a level
 * (0 to 0x1000). */
extern unsigned int func_020ab504(void *choices);
extern void func_020ab3a8(void *choices, int level);

/* The slider window's message window: whether the knob can be moved, the knob's y at level 0
 * and at the top level, and the knob's place. */
extern int func_020abd98(void *window);
extern int func_020abcfc(void *window);
extern int func_020abd14(void *window);
extern int func_020abd44(void *window);
extern int func_020abd2c(void *window);

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
    if ((int) func_020ab504(slider->choices) >= 0) {
        return;
    }
    if ((MenuInput_UsesTouch() && TalkSlider_OkTouched(slider)) ||
        (MenuInput_UsesButtons() && TalkSlider_OkPressedWithButtons(slider))) {
        func_020ab3a8(slider->choices, slider->level);
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
    if (slider->held != 0 && func_020abd98(slider->window) != 0) {
        if (MenuInput_UsesTouch()) {
            int x;
            int y;
            if (MenuInput_TouchPosition(&x, &y)) {
                int bottom_y = func_020abcfc(slider->window);
                int top_y = func_020abd14(slider->window);
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
    int knob_x = func_020abd44(slider->window);
    int knob_y = func_020abd2c(slider->window);
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
