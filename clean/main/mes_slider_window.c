/* The message window of the talk's slider window: its states (mes_slider_window.h). */
#include "mes_slider_window.h"

#include "autoload_2/heap.h"   /* Heap_OperatorDeleteB */
#include "cell_layer_sprite.h" /* CellLayerSprite_IsDone, CellLayerSprite_SetAnim */
#include "clean.h"
#include "label_sprite.h"
#include "message_reader.h" /* MessageReader_LoadMenuMessage */
#include "ov004/member_pointer.h"
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
    MesSliderWindow_SetMarkerAnim(self, MES_SLIDER_WINDOW_MARKER_9);
    LabelSprite_SetState((LabelSprite *) (void *) self->button, MES_SLIDER_WINDOW_BUTTON_SHOWN);
}
CLEAN_AS(func_020ab9c8, MesSliderWindow_Enter10)

/* func_020ab9ec (step of state 9): on to state 10 once the button's animation ended. */
void MesSliderWindow_Step9(MesSliderWindow *self)
{
    if (LabelSprite_IsDone((LabelSprite *) (void *) self->button) != 0) {
        MesSliderWindow_Enter10(self);
    }
}
CLEAN_AS(func_020ab9ec, MesSliderWindow_Step9)

/* func_020aba08 (step of state 8): done once the button's animation ended. */
void MesSliderWindow_StepPressing(MesSliderWindow *self)
{
    if (LabelSprite_IsDone((LabelSprite *) (void *) self->button) != 0) {
        MesSliderWindow_EnterDone(self);
    }
}
CLEAN_AS(func_020aba08, MesSliderWindow_StepPressing)

/* func_020aba24: state 8: the button pressed. */
void MesSliderWindow_EnterPressing(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_PRESSING;
    LabelSprite_SetState((LabelSprite *) (void *) self->button, MES_SLIDER_WINDOW_BUTTON_PRESSED);
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
    MesSliderWindow_SetMarkerAnim(self, MES_SLIDER_WINDOW_MARKER_PRESS);
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
    LabelSprite_SetState((LabelSprite *) (void *) self->button, MES_SLIDER_WINDOW_BUTTON_SHOWN);
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
    MesSliderWindow_SetMarkerAnim(self, MES_SLIDER_WINDOW_MARKER_RELEASE);
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
    MesSliderWindow_SetMarkerAnim(self, MES_SLIDER_WINDOW_MARKER_GRAB);
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
    MesSliderWindow_SetMarkerAnim(self, MES_SLIDER_WINDOW_MARKER_BESIDE_SLIDER);
    MesBgSlider_ShowStill(&self->slider);
    LabelSprite_SetState((LabelSprite *) (void *) self->button, MES_SLIDER_WINDOW_BUTTON_SHOWN);
}
CLEAN_AS(func_020abbf8, MesSliderWindow_EnterSlider)

/* func_020abc3c (step of state 0): nothing. */
void MesSliderWindow_StepHidden(void) {}
CLEAN_AS(func_020abc3c, MesSliderWindow_StepHidden)

/* ---- The requests, the places read by the talk's slider, the frame and the drawing */

/* The class's vtable. */
extern const u8 data_020e3fe4[];

/* The state table of the frame: the guard and table the game fills on the first frame, and the
 * member-pointer constants they are filled from (the Step functions above, by state). */
extern u32 data_021f45b0;
extern MemberPointer data_021f4610[12];
extern const MemberPointer data_020e3f84, data_020e3ee4, data_020e3f8c, data_020e3eec, data_020e3f14, data_020e3f1c,
    data_020e3f7c, data_020e3f04, data_020e3f44, data_020e3f4c, data_020e3f0c, data_020e3f64;

/* The button's label: message 0x12 of the menu messages. */
#define MES_SLIDER_WINDOW_BUTTON_TEXT 0x12

/* Where the marker goes beside the slider (from the indicator's movement and the knob) and
 * beside the button (from the button's movement), and where the button is. */
#define MES_SLIDER_WINDOW_MARKER_SLIDER_X 0x10
#define MES_SLIDER_WINDOW_MARKER_SLIDER_Y 7
#define MES_SLIDER_WINDOW_MARKER_BUTTON_X 0x46
#define MES_SLIDER_WINDOW_MARKER_BUTTON_Y 0x4c
#define MES_SLIDER_WINDOW_BUTTON_X 0x3c
#define MES_SLIDER_WINDOW_BUTTON_Y 0x44

/* The sound of the input shown turning to the buttons. */
#define MES_SLIDER_WINDOW_SE_BUTTONS 0x3b

static LabelSprite *mes_slider_window_button(MesSliderWindow *self)
{
    return (LabelSprite *) self->button;
}

/* The vtable of one of main's sprites (the marker, the button or the slider). */
static const MesBgSpriteVtable *mes_slider_window_vtable(void *sprite)
{
    return *(const MesBgSpriteVtable *const *) sprite;
}

/* func_020abc40: state 0: the marker, the slider and the button hidden. */
void MesSliderWindow_EnterHidden(MesSliderWindow *self)
{
    self->state = MES_SLIDER_WINDOW_HIDDEN;
    MesSliderWindow_SetMarkerAnim(self, CELL_LAYER_SPRITE_NONE);
    MesBgSlider_Hide(&self->slider);
    LabelSprite_SetState(mes_slider_window_button(self), LABEL_SPRITE_HIDDEN);
}
CLEAN_AS(func_020abc40, MesSliderWindow_EnterHidden)

/* func_020abc6c: the marker's animation started. */
void MesSliderWindow_SetMarkerAnim(MesSliderWindow *self, int anim)
{
    CellLayerSprite_SetAnim((CellLayerSprite *) &self->marker, anim);
}
CLEAN_AS(func_020abc6c, MesSliderWindow_SetMarkerAnim)

/* func_020abc78: to state 0 on the next frame. */
void MesSliderWindow_RequestHide(MesSliderWindow *self)
{
    self->hide = 1;
}
CLEAN_AS(func_020abc78, MesSliderWindow_RequestHide)

/* func_020abc84: a choice was taken. */
void MesSliderWindow_Choose(MesSliderWindow *self)
{
    self->chosen = 1;
}
CLEAN_AS(func_020abc84, MesSliderWindow_Choose)

/* func_020abc90: to state 6 (the button focused) on the next frame. */
void MesSliderWindow_RequestFocusButton(MesSliderWindow *self)
{
    self->focus_button = 1;
}
CLEAN_AS(func_020abc90, MesSliderWindow_RequestFocusButton)

/* func_020abc9c: the slider let go. */
void MesSliderWindow_Release(MesSliderWindow *self)
{
    self->grabbed = 0;
}
CLEAN_AS(func_020abc9c, MesSliderWindow_Release)

/* func_020abca8: the slider grabbed. */
void MesSliderWindow_Grab(MesSliderWindow *self)
{
    self->grabbed = 1;
}
CLEAN_AS(func_020abca8, MesSliderWindow_Grab)

/* func_020abcb4: to state 1 (the slider focused) on the next frame. */
void MesSliderWindow_RequestFocusSlider(MesSliderWindow *self)
{
    self->focus_slider = 1;
}
CLEAN_AS(func_020abcb4, MesSliderWindow_RequestFocusSlider)

/* func_020abcc0 */
int MesSliderWindow_State(MesSliderWindow *self)
{
    return self->state;
}
CLEAN_AS(func_020abcc0, MesSliderWindow_State)

/* func_020abccc: whether the button has the focus (states 6 to 11). */
int MesSliderWindow_OnButton(MesSliderWindow *self)
{
    return (u32) self->state - MES_SLIDER_WINDOW_BUTTON <= MES_SLIDER_WINDOW_DONE - MES_SLIDER_WINDOW_BUTTON;
}
CLEAN_AS(func_020abccc, MesSliderWindow_OnButton)

/* func_020abce4: whether the slider has the focus (states 1 to 5). */
int MesSliderWindow_OnSlider(MesSliderWindow *self)
{
    return (u32) self->state - MES_SLIDER_WINDOW_SLIDER <= MES_SLIDER_WINDOW_RELEASING - MES_SLIDER_WINDOW_SLIDER;
}
CLEAN_AS(func_020abce4, MesSliderWindow_OnSlider)

/* func_020abcfc: the screen y of the bottom of the slider's track. The sprites are placed
 * relative to the screen's centre and the window's scroll. */
int MesSliderWindow_TrackBottomY(MesSliderWindow *self)
{
    return MesBgSlider_TrackBottom(&self->slider) + SCREEN_SPRITE_CENTER_Y - self->bg.scroll_y;
}
CLEAN_AS(func_020abcfc, MesSliderWindow_TrackBottomY)

/* func_020abd14: the screen y of the top of the slider's track. */
int MesSliderWindow_TrackTopY(MesSliderWindow *self)
{
    return MesBgSlider_TrackTop(&self->slider) + SCREEN_SPRITE_CENTER_Y - self->bg.scroll_y;
}
CLEAN_AS(func_020abd14, MesSliderWindow_TrackTopY)

/* func_020abd2c: the screen y of the slider's knob (wrapping in 32 bits for a level far
 * outside the track). */
int MesSliderWindow_KnobY(MesSliderWindow *self)
{
    int knob = MesBgSlider_KnobY(&self->slider);
    return (int) ((u32) knob + SCREEN_SPRITE_CENTER_Y - (u32) self->bg.scroll_y);
}
CLEAN_AS(func_020abd2c, MesSliderWindow_KnobY)

/* func_020abd44: the screen x of the slider's track. */
int MesSliderWindow_TrackX(MesSliderWindow *self)
{
    return MesBgSlider_TrackX(&self->slider) + SCREEN_SPRITE_CENTER_X - self->bg.scroll_x;
}
CLEAN_AS(func_020abd44, MesSliderWindow_TrackX)

/* func_020abd5c: the slider's level. */
void MesSliderWindow_SetLevel(MesSliderWindow *self, fx32 level)
{
    MesBgSlider_SetLevel(&self->slider, level);
}
CLEAN_AS(func_020abd5c, MesSliderWindow_SetLevel)

/* func_020abd68: whether the input shown is the buttons (else the touch screen); with `sound`,
 * a sound when it turns to the buttons. */
void MesSliderWindow_SetButtons(MesSliderWindow *self, u8 buttons, int sound)
{
    if (sound != 0 && self->buttons == 0 && buttons != 0) {
        SoundSys_PlaySe(MES_SLIDER_WINDOW_SE_BUTTONS);
    }
    self->buttons = buttons;
}
CLEAN_AS(func_020abd68, MesSliderWindow_SetButtons)

/* func_020abd98: whether the slider is held and its indicator's animation ended. */
int MesSliderWindow_GrabSettled(MesSliderWindow *self)
{
    return self->grabbed != 0 && MesBgSlider_IndicatorDone(&self->slider) != 0;
}
CLEAN_AS(func_020abd98, MesSliderWindow_GrabSettled)

/* func_020abdc0: the window done with: hidden on the next frame. */
void MesSliderWindow_Dismiss(MesSliderWindow *self)
{
    MesSliderWindow_RequestHide(self);
}
CLEAN_AS(func_020abdc0, MesSliderWindow_Dismiss)

/* func_020abdc8: the window opened: the marker and the slider placed at its scroll, the button
 * at its left (following its vertical scroll) with its label, the slider at half level, and
 * state 1 on the next frame. */
void MesSliderWindow_Open(MesSliderWindow *self)
{
    int y = -self->bg.scroll_y;
    int x = -self->bg.scroll_x;
    LabelSprite *button = mes_slider_window_button(self);

    self->marker.vtable->set_place(&self->marker, x, y);
    mes_slider_window_vtable(button)->set_place(button, 0, y);
    self->slider.vtable->set_place(&self->slider, x, y);

    LabelSpriteText label;
    LabelSprite_TextConstruct(&label);
    u8 message = MES_SLIDER_WINDOW_BUTTON_TEXT;
    MessageReader_LoadMenuMessage(&label, &message, NULL);
    LabelSprite_SetText(button, (TextBase *) &label);
    MesBgSlider_SetLevel(&self->slider, MES_BG_SLIDER_LEVEL_TOP / 2);
    MesSliderWindow_RequestFocusSlider(self);
    LabelSprite_TextDestruct(&label);
}
CLEAN_AS(func_020abdc8, MesSliderWindow_Open)

/* func_020abe48 (vtable slot 3): drawn: the marker (only while the input shown is the
 * buttons), the button, the slider. */
void MesSliderWindow_Draw(MesSliderWindow *self)
{
    LabelSprite *button = mes_slider_window_button(self);

    if (self->buttons != 0) {
        self->marker.vtable->draw(&self->marker);
    }
    mes_slider_window_vtable(button)->draw(button);
    self->slider.vtable->draw(&self->slider);
}
CLEAN_AS(func_020abe48, MesSliderWindow_Draw)

/* func_020abe7c (vtable slot 2): the frame: the requests acted on (focus the slider, focus the
 * button, hide, in this order), the state's step, the marker placed beside the slider's knob
 * or the button by the focus, the button placed, and the three sprites updated. */
void MesSliderWindow_Update(MesSliderWindow *self)
{
    static const MemberPointer *const steps[12] = {
        &data_020e3f84, &data_020e3ee4, &data_020e3f8c, &data_020e3eec, &data_020e3f14, &data_020e3f1c,
        &data_020e3f7c, &data_020e3f04, &data_020e3f44, &data_020e3f4c, &data_020e3f0c, &data_020e3f64,
    };
    LabelSprite *button = mes_slider_window_button(self);
    CellLayerSprite *marker = (CellLayerSprite *) &self->marker;

    if (self->focus_slider != 0) {
        self->focus_slider = 0;
        MesSliderWindow_EnterSlider(self);
    }
    if (self->focus_button != 0) {
        self->focus_button = 0;
        MesSliderWindow_EnterButton(self);
    }
    if (self->hide != 0) {
        self->hide = 0;
        MesSliderWindow_EnterHidden(self);
    }

    MemberTable_InitOnce(&data_021f45b0, data_021f4610, steps, 12);
    MemberPointer_CallVoid(&data_021f4610[self->state], self);

    if (MesSliderWindow_OnSlider(self)) {
        int dx;
        int dy;
        MesBgSlider_IndicatorMove(&self->slider, &dx, &dy);
        int knob = MesBgSlider_LevelToY(&self->slider);
        CellLayerSprite_SetOffset(marker, dx + MES_SLIDER_WINDOW_MARKER_SLIDER_X,
                                  (int) ((u32) dy + MES_SLIDER_WINDOW_MARKER_SLIDER_Y + (u32) knob));
    } else if (MesSliderWindow_OnButton(self)) {
        int dx;
        int dy;
        LabelSprite_Travel(button, &dx, &dy);
        CellLayerSprite_SetOffset(marker, dx + MES_SLIDER_WINDOW_MARKER_BUTTON_X, dy + MES_SLIDER_WINDOW_MARKER_BUTTON_Y);
    }
    LabelSprite_SetOffset(button, MES_SLIDER_WINDOW_BUTTON_X, MES_SLIDER_WINDOW_BUTTON_Y);

    self->marker.vtable->update(&self->marker);
    mes_slider_window_vtable(button)->update(button);
    self->slider.vtable->update(&self->slider);
}
CLEAN_AS(func_020abe7c, MesSliderWindow_Update)

/* func_020ac040 (vtable slot 1): destroyed (as MesSliderWindow_Destruct) and freed. */
MesSliderWindow *MesSliderWindow_DestructDelete(MesSliderWindow *self)
{
    self->bg.vtable = data_020e3fe4;
    MesBgSlider_Destruct(&self->slider);
    LabelSprite_Destruct(mes_slider_window_button(self));
    MesBgMarker_Destruct(&self->marker);
    MesBg_DestructBase(&self->bg);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020ac040, MesSliderWindow_DestructDelete)

/* func_020ac078 (vtable slot 0): the destructor: the slider, the button, the marker, then the
 * base. */
MesSliderWindow *MesSliderWindow_Destruct(MesSliderWindow *self)
{
    self->bg.vtable = data_020e3fe4;
    MesBgSlider_Destruct(&self->slider);
    LabelSprite_Destruct(mes_slider_window_button(self));
    MesBgMarker_Destruct(&self->marker);
    MesBg_DestructBase(&self->bg);
    return self;
}
CLEAN_AS(func_020ac078, MesSliderWindow_Destruct)

/* func_020ac0ac: the constructor: hidden, no requests, the input shown the touch screen; the
 * button a main-screen label sprite of kind 0. */
MesSliderWindow *MesSliderWindow_Construct(MesSliderWindow *self)
{
    MesBg_Construct(&self->bg);
    self->bg.vtable = data_020e3fe4;
    MesBgMarker_Construct(&self->marker);
    LabelSprite_Construct(mes_slider_window_button(self), 1, 0);
    MesBgSlider_Construct(&self->slider);
    self->state = MES_SLIDER_WINDOW_HIDDEN;
    self->focus_slider = 0;
    self->grabbed = 0;
    self->focus_button = 0;
    self->chosen = 0;
    self->hide = 0;
    self->buttons = 0;
    return self;
}
CLEAN_AS(func_020ac0ac, MesSliderWindow_Construct)
