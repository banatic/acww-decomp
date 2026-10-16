/* The message window of the talk's slider window: its states (mes_slider_window.h). */
#include "mes_slider_window.h"

#include "cell_layer_sprite.h" /* CellLayerSprite_IsDone, CellLayerSprite_SetAnim */
#include "clean.h"
#include "sound.h" /* SoundSys_PlaySe */

static_assert(offsetof(MesSliderWindow, marker) == 0x20, "mes slider window");
static_assert(offsetof(MesSliderWindow, button) == 0x6c, "mes slider window");
static_assert(offsetof(MesSliderWindow, slider) == 0xe4, "mes slider window");
static_assert(offsetof(MesSliderWindow, state) == 0x13c, "mes slider window");
static_assert(offsetof(MesSliderWindow, buttons) == 0x145, "mes slider window");
static_assert(sizeof(MesSliderWindow) == 0x148, "mes slider window");

/* The marker's animations (cell layer sprite numbers). */
#define MES_SLIDER_WINDOW_MARKER_BESIDE_SLIDER 1
#define MES_SLIDER_WINDOW_MARKER_GRAB 2
#define MES_SLIDER_WINDOW_MARKER_RELEASE 3
#define MES_SLIDER_WINDOW_MARKER_BESIDE_BUTTON 7
#define MES_SLIDER_WINDOW_MARKER_PRESS 8
#define MES_SLIDER_WINDOW_MARKER_9 9

/* The button's animations. */
#define MES_SLIDER_WINDOW_BUTTON_SHOWN 1
#define MES_SLIDER_WINDOW_BUTTON_PRESSED 2

/* The sounds played. */
#define MES_SLIDER_WINDOW_SE_CHOSEN 0x27
#define MES_SLIDER_WINDOW_SE_GRAB 0x33

/* The marker's animation started (its cell layer sprite's SetAnim). */
extern void func_020abc6c(MesSliderWindow *self, int anim);
/* main's button sprite: whether its animation ended, an animation started. */
extern int func_0208f098(void *button);
extern void func_0208f0c4(void *button, int anim);

static int mes_slider_window_marker_done(MesSliderWindow *self)
{
    return CellLayerSprite_IsDone((CellLayerSprite *) &self->marker);
}

/* func_020ab988 (step of state 11): the choice flag dropped. */
void MesSliderWindow_StepDone(MesSliderWindow *self)
{
    self->chosen = 0;
}
CLEAN_AS(func_020ab988, MesSliderWindow_StepDone)

/* func_020ab994: done (state 11). */
void MesSliderWindow_EnterDone(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_DONE;
    self->chosen = 0;
}
CLEAN_AS(func_020ab994, MesSliderWindow_EnterDone)

/* func_020ab9ac (step of state 10): done once the marker's animation ended. */
void MesSliderWindow_Step10(MesSliderWindow *self)
{
    if (mes_slider_window_marker_done(self)) {
        MesSliderWindow_EnterDone(self);
    }
}
CLEAN_AS(func_020ab9ac, MesSliderWindow_Step10)

/* func_020ab9c8: state 10: the marker's animation 9, the button shown. */
void MesSliderWindow_Enter10(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_STATE_10;
    func_020abc6c(self, MES_SLIDER_WINDOW_MARKER_9);
    func_0208f0c4(self->button, MES_SLIDER_WINDOW_BUTTON_SHOWN);
}
CLEAN_AS(func_020ab9c8, MesSliderWindow_Enter10)

/* func_020ab9ec (step of state 9): on to state 10 once the button's animation ended. */
void MesSliderWindow_Step9(MesSliderWindow *self)
{
    if (func_0208f098(self->button) != 0) {
        MesSliderWindow_Enter10(self);
    }
}
CLEAN_AS(func_020ab9ec, MesSliderWindow_Step9)

/* func_020aba08 (step of state 8): done once the button's animation ended. */
void MesSliderWindow_StepPressing(MesSliderWindow *self)
{
    if (func_0208f098(self->button) != 0) {
        MesSliderWindow_EnterDone(self);
    }
}
CLEAN_AS(func_020aba08, MesSliderWindow_StepPressing)

/* func_020aba24: state 8: the button pressed. */
void MesSliderWindow_EnterPressing(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_PRESSING;
    func_0208f0c4(self->button, MES_SLIDER_WINDOW_BUTTON_PRESSED);
}
CLEAN_AS(func_020aba24, MesSliderWindow_EnterPressing)

/* func_020aba3c (step of state 7): once the marker's animation ended, the choice's sound and
 * the button pressed. */
void MesSliderWindow_StepChosen(MesSliderWindow *self)
{
    if (mes_slider_window_marker_done(self)) {
        SoundSys_PlaySe(MES_SLIDER_WINDOW_SE_CHOSEN);
        MesSliderWindow_EnterPressing(self);
    }
}
CLEAN_AS(func_020aba3c, MesSliderWindow_StepChosen)

/* func_020aba5c: state 7: the marker placed at the window's left (following its vertical
 * scroll) and its press animation started. */
void MesSliderWindow_EnterChosen(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_CHOSEN;
    self->marker.vtable->set_place(&self->marker, 0, -self->bg.scroll_y);
    func_020abc6c(self, MES_SLIDER_WINDOW_MARKER_PRESS);
}
CLEAN_AS(func_020aba5c, MesSliderWindow_EnterChosen)

/* func_020aba8c (step of state 6): on to state 7 once a choice was taken. */
void MesSliderWindow_StepButton(MesSliderWindow *self)
{
    if (self->chosen != 0) {
        MesSliderWindow_EnterChosen(self);
    }
}
CLEAN_AS(func_020aba8c, MesSliderWindow_StepButton)

/* func_020abaa8: state 6: the marker placed at the window's left and shown beside the button,
 * the slider still, the button shown. */
void MesSliderWindow_EnterButton(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_BUTTON;
    self->marker.vtable->set_place(&self->marker, 0, -self->bg.scroll_y);
    CellLayerSprite_SetAnim((CellLayerSprite *) &self->marker, MES_SLIDER_WINDOW_MARKER_BESIDE_BUTTON);
    MesBgSlider_ShowStill(&self->slider);
    func_0208f0c4(self->button, MES_SLIDER_WINDOW_BUTTON_SHOWN);
}
CLEAN_AS(func_020abaa8, MesSliderWindow_EnterButton)

/* func_020abaec (step of state 5): back to state 1 once the marker's animation ended. */
void MesSliderWindow_StepReleasing(MesSliderWindow *self)
{
    if (mes_slider_window_marker_done(self)) {
        MesSliderWindow_EnterSlider(self);
    }
}
CLEAN_AS(func_020abaec, MesSliderWindow_StepReleasing)

/* func_020abb08: state 5: the slider still, the marker's release animation. */
void MesSliderWindow_EnterReleasing(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_RELEASING;
    MesBgSlider_ShowStill(&self->slider);
    func_020abc6c(self, MES_SLIDER_WINDOW_MARKER_RELEASE);
}
CLEAN_AS(func_020abb08, MesSliderWindow_EnterReleasing)

/* func_020abb2c (step of state 4): on to state 5 once the slider's indicator ended. */
void MesSliderWindow_StepLettingGo(MesSliderWindow *self)
{
    if (MesBgSlider_IndicatorDone(&self->slider)) {
        MesSliderWindow_EnterReleasing(self);
    }
}
CLEAN_AS(func_020abb2c, MesSliderWindow_StepLettingGo)

/* func_020abb48: state 4: the slider's indicator played back (its state 3). */
void MesSliderWindow_EnterLettingGo(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_LETTING_GO;
    MesBgSlider_PlayIndicatorB(&self->slider);
}
CLEAN_AS(func_020abb48, MesSliderWindow_EnterLettingGo)

/* func_020abb5c (step of state 3): on to state 4 once the slider is let go. */
void MesSliderWindow_StepHeld(MesSliderWindow *self)
{
    if (self->grabbed == 0) {
        MesSliderWindow_EnterLettingGo(self);
    }
}
CLEAN_AS(func_020abb5c, MesSliderWindow_StepHeld)

/* func_020abb78: state 3: the slider's indicator played (its state 2). */
void MesSliderWindow_EnterHeld(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_HELD;
    MesBgSlider_PlayIndicatorA(&self->slider);
}
CLEAN_AS(func_020abb78, MesSliderWindow_EnterHeld)

/* func_020abb8c (step of state 2): once the marker's animation ended, the grab's sound (when
 * the input shown is the buttons) and on to state 3. */
void MesSliderWindow_StepGrabbing(MesSliderWindow *self)
{
    if (mes_slider_window_marker_done(self)) {
        if (self->buttons != 0) {
            SoundSys_PlaySe(MES_SLIDER_WINDOW_SE_GRAB);
        }
        MesSliderWindow_EnterHeld(self);
    }
}
CLEAN_AS(func_020abb8c, MesSliderWindow_StepGrabbing)

/* func_020abbb8: state 2: the marker's grab animation. */
void MesSliderWindow_EnterGrabbing(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_GRABBING;
    func_020abc6c(self, MES_SLIDER_WINDOW_MARKER_GRAB);
}
CLEAN_AS(func_020abbb8, MesSliderWindow_EnterGrabbing)

/* func_020abbcc (step of state 1): grabbing the slider comes first, then a choice taken. */
void MesSliderWindow_StepSlider(MesSliderWindow *self)
{
    if (self->grabbed != 0) {
        MesSliderWindow_EnterGrabbing(self);
    } else if (self->chosen != 0) {
        MesSliderWindow_EnterChosen(self);
    }
}
CLEAN_AS(func_020abbcc, MesSliderWindow_StepSlider)

/* func_020abbf8: state 1: the marker placed at the window's scroll and shown beside the
 * slider, the slider still, the button shown. */
void MesSliderWindow_EnterSlider(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_SLIDER;
    self->marker.vtable->set_place(&self->marker, -self->bg.scroll_x, -self->bg.scroll_y);
    func_020abc6c(self, MES_SLIDER_WINDOW_MARKER_BESIDE_SLIDER);
    MesBgSlider_ShowStill(&self->slider);
    func_0208f0c4(self->button, MES_SLIDER_WINDOW_BUTTON_SHOWN);
}
CLEAN_AS(func_020abbf8, MesSliderWindow_EnterSlider)

/* func_020abc3c (step of state 0): nothing. */
void MesSliderWindow_StepHidden(void) {}
CLEAN_AS(func_020abc3c, MesSliderWindow_StepHidden)
