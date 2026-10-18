/* The windows a talk opens for its choices (talk_windows.h). */
#include "talk_windows.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "game_variables.h" /* GameVariables_Tweak */
#include "ov004/member_pointer.h"
#include "sound.h" /* SoundSys_PlaySe */
#include "mes_bg.h"
#include "mes_choice_window.h"
#include "mes_slider_window.h"
#include "talk_choice_cursor.h"
#include "talk_slider.h"

static_assert(sizeof(TalkWindow) == 0x08, "talk window");
static_assert(offsetof(TalkSliderWindow, slider) == 0x154, "talk slider window");
static_assert(offsetof(TalkSliderWindow, decided) == 0x198, "talk slider window");
static_assert(sizeof(TalkSliderWindow) == 0x19c, "talk slider window");
static_assert(offsetof(TalkChoiceWindow, list) == 0x84, "talk choice window");
static_assert(offsetof(TalkChoiceWindow, decided) == 0xc0, "talk choice window");
static_assert(sizeof(TalkChoiceWindow) == 0xc4, "talk choice window");
static_assert(offsetof(TalkWindows, slider) == 0xc8, "talk windows");
static_assert(offsetof(TalkWindows, closed_now) == 0x264, "talk windows");

/* The classes' vtables. */
extern const u32 data_020e408c[]; /* the base class */
extern const u32 data_020e404c[]; /* the slider window */
extern const u32 data_020e406c[]; /* the choice window */

/* The windows' vtable slots called here (TalkWindow), and their message windows' (the slots of
 * main's sprite classes: 2 the frame, 3 drawing). */
#define TALK_WINDOW_SLOT_UPDATE 2
#define TALK_WINDOW_SLOT_DRAW 3
#define TALK_WINDOW_SLOT_IS_CLOSED 4
#define TALK_WINDOW_SLOT_DECIDED 5
#define TALK_WINDOW_MESSAGE_SLOT_UPDATE 2
#define TALK_WINDOW_MESSAGE_SLOT_DRAW 3

/* The adjustments (GameVariables_Tweak, always 0) of the slides in and out. */
#define TALK_WINDOW_TWEAK_OPENING 100
#define TALK_WINDOW_TWEAK_CLOSING 101

/* The sounds of a window opening and closing. */
#define TALK_WINDOW_SE_OPEN 0x13
#define TALK_WINDOW_SE_CLOSE 0x14

/* The message window's animation state in which the slider window closes. */
#define TALK_SLIDER_WINDOW_ANIM_DONE 0xb

/* The windows' state tables: the guards and tables the game fills on the first frame, and the
 * member-pointer constants they are filled from. */
extern u32 data_021f45ac;
extern MemberPointer data_021f45d0[4];
extern const MemberPointer data_020e3f6c, data_020e3f74, data_020e3edc, data_020e3ef4;
extern u32 data_021f45a4;
extern MemberPointer data_021f45f0[4];
extern const MemberPointer data_020e3f3c, data_020e3f34, data_020e3f24, data_020e3f2c;

typedef void TalkWindowCall(void *object);
typedef int TalkWindowQuery(void *object);

/* The address in vtable slot `slot` of an object whose first word is its vtable. */
static uintptr_t talk_window_slot(const void *object, int slot)
{
    return (uintptr_t) (*(const u32 *const *) object)[slot];
}

static void talk_window_call(void *object, int slot)
{
    ((TalkWindowCall *) talk_window_slot(object, slot))(object);
}

static int talk_window_query(void *object, int slot)
{
    return ((TalkWindowQuery *) talk_window_slot(object, slot))(object);
}

/* ---- The pair */

/* func_020a9ce0: the window shown drawn (slot 3). */
void TalkWindows_Draw(TalkWindows *windows)
{
    if (windows->current != NULL) {
        talk_window_call(windows->current, TALK_WINDOW_SLOT_DRAW);
    }
}
CLEAN_AS(func_020a9ce0, TalkWindows_Draw)

/* func_020a9cf8: 1 when the window shown has just had a choice taken (slot 5). */
int TalkWindows_Decided(TalkWindows *windows)
{
    if (windows->current == NULL) {
        return 0;
    }
    return talk_window_query(windows->current, TALK_WINDOW_SLOT_DECIDED);
}
CLEAN_AS(func_020a9cf8, TalkWindows_Decided)

/* func_020a9d14: 1 when no window is shown. */
int TalkWindows_NoneShown(TalkWindows *windows)
{
    return windows->current == NULL;
}
CLEAN_AS(func_020a9d14, TalkWindows_NoneShown)

/* func_020a9d24: the window shown asked to open. */
void TalkWindows_Open(TalkWindows *windows)
{
    if (windows->current != NULL) {
        TalkWindow_RequestOpen(windows->current);
    }
}
CLEAN_AS(func_020a9d24, TalkWindows_Open)

/* func_020a9d38: the window shown runs its frame (slot 2); once it says it is closed (slot 4)
 * it is no longer shown, and `closed_now` says so for this frame. */
void TalkWindows_Update(TalkWindows *windows)
{
    if (windows->current == NULL) {
        windows->closed_now = 0;
        return;
    }
    talk_window_call(windows->current, TALK_WINDOW_SLOT_UPDATE);
    if (talk_window_query(windows->current, TALK_WINDOW_SLOT_IS_CLOSED)) {
        windows->current = NULL;
        windows->closed_now = 1;
    }
}
CLEAN_AS(func_020a9d38, TalkWindows_Update)

/* func_020a9d70: the destructor: the two windows destroyed, the slider window first. */
TalkWindows *TalkWindows_Destruct(TalkWindows *windows)
{
    TalkSliderWindow_Destruct(&windows->slider);
    TalkChoiceWindow_Destruct(&windows->choice);
    return windows;
}
CLEAN_AS(func_020a9d70, TalkWindows_Destruct)

/* func_020a9d88: the constructor: both windows built, none shown. */
TalkWindows *TalkWindows_Construct(TalkWindows *windows)
{
    windows->current = NULL;
    TalkChoiceWindow_Construct(&windows->choice);
    TalkSliderWindow_Construct(&windows->slider);
    windows->closed_now = 0;
    return windows;
}
CLEAN_AS(func_020a9d88, TalkWindows_Construct)

/* func_020a9db0: the slider window handed `choices` and shown. */
void TalkWindows_ShowSlider(TalkWindows *windows, void *choices)
{
    TalkSliderWindow_SetChoices(&windows->slider, choices);
    windows->current = &windows->slider.base;
}
CLEAN_AS(func_020a9db0, TalkWindows_ShowSlider)

/* func_020a9dc8: the choice window handed `choices` and shown. */
void TalkWindows_ShowChoices(TalkWindows *windows, void *choices)
{
    TalkChoiceWindow_SetChoices(&windows->choice, choices);
    windows->current = &windows->choice.base;
}
CLEAN_AS(func_020a9dc8, TalkWindows_ShowChoices)

/* ---- The slider window */

/* func_020a9ddc: the message window as wide as the slider says, with the slider's frame. */
void TalkSliderWindow_LayOut(TalkSliderWindow *self)
{
    MesBg_SetColumns((MesBg *) (void *) self->window, TalkSlider_LabelCells(&self->slider));
    MesBg_ShapeFiveLines((MesBg *) (void *) self->window);
}
CLEAN_AS(func_020a9ddc, TalkSliderWindow_LayOut)

/* func_020a9e04 (closing): the message window slides on out; at the end the slider is reset
 * and the window closed.
 * QUIRK: unlike the opening, the slide out leaves out the 4 pixels down the opening ends at,
 * so the message window jumps up 4 pixels as it starts to close. */
void TalkSliderWindow_StepClosing(TalkSliderWindow *self)
{
    self->decided = 0;
    self->offset_x += GameVariables_Tweak(TALK_WINDOW_TWEAK_CLOSING, 3) + 11;
    self->offset_y += GameVariables_Tweak(TALK_WINDOW_TWEAK_CLOSING, 4) - 11;
    self->frames_left--;
    int done = self->frames_left <= 0;
    MesBg_SetScroll((MesBg *) (void *) self->window, self->offset_x, self->offset_y);
    if (done) {
        TalkSlider_Close(&self->slider);
        TalkSliderWindow_EnterClosed(self);
    }
}
CLEAN_AS(func_020a9e04, TalkSliderWindow_StepClosing)

/* func_020a9e8c: closing, a choice having been taken: the slide out starts, with its sound. */
void TalkSliderWindow_StartClosing(TalkSliderWindow *self)
{
    self->state = TALK_WINDOW_CLOSING;
    self->decided = 1;
    self->frames_left = GameVariables_Tweak(TALK_WINDOW_TWEAK_CLOSING, 2) + 2;
    SoundSys_PlaySe(TALK_WINDOW_SE_CLOSE);
}
CLEAN_AS(func_020a9e8c, TalkSliderWindow_StartClosing)

/* func_020a9ebc (open): the slider's frame, shown in the message window; once a choice is
 * taken the window closes when the message window's animation is at its end (else the
 * animation is told to end); until then the message window's marks follow the slider's focus
 * and input. */
void TalkSliderWindow_StepOpen(TalkSliderWindow *self)
{
    void *slider = &self->slider;
    unsigned char *window = self->window;

    TalkSlider_Update(slider);
    MesSliderWindow_SetButtons((MesSliderWindow *) (void *) window, TalkSlider_TouchOrStart(slider) == 0, 1);
    MesSliderWindow_SetLevel((MesSliderWindow *) (void *) window, TalkSlider_Level(slider));
    int choice = TalkSlider_Picked(slider);
    int anim = MesSliderWindow_State((MesSliderWindow *) (void *) window);
    if (choice >= 0) {
        if (anim == TALK_SLIDER_WINDOW_ANIM_DONE) {
            MesSliderWindow_Dismiss((MesSliderWindow *) (void *) window);
            TalkSlider_Hide(slider);
            TalkSliderWindow_StartClosing(self);
        } else {
            MesSliderWindow_Choose((MesSliderWindow *) (void *) window);
        }
    } else if (TalkSlider_KnobFocused(slider)) {
        if (MesSliderWindow_OnButton((MesSliderWindow *) (void *) window)) {
            MesSliderWindow_RequestFocusSlider((MesSliderWindow *) (void *) window);
        } else if (TalkSlider_KnobHeld(slider)) {
            MesSliderWindow_Grab((MesSliderWindow *) (void *) window);
        } else {
            MesSliderWindow_Release((MesSliderWindow *) (void *) window);
        }
    } else if (TalkSlider_OkFocused(slider) && MesSliderWindow_OnSlider((MesSliderWindow *) (void *) window)) {
        MesSliderWindow_RequestFocusButton((MesSliderWindow *) (void *) window);
    }
}
CLEAN_AS(func_020a9ebc, TalkSliderWindow_StepOpen)

/* func_020a9fa4: open. */
void TalkSliderWindow_EnterOpen(TalkSliderWindow *self)
{
    self->state = TALK_WINDOW_OPEN;
}
CLEAN_AS(func_020a9fa4, TalkSliderWindow_EnterOpen)

/* func_020a9fac (opening): the message window slides on in, faster for the first frames; at
 * the end it is in place (4 pixels down), shows its input mode and the window is open. */
void TalkSliderWindow_StepOpening(TalkSliderWindow *self)
{
    if (self->frames_left > GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 3) + 2) {
        self->offset_x += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 6) - 6;
        self->offset_y += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 7) + 6;
    } else {
        self->offset_x += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 8) + 2;
        self->offset_y += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 9) - 2;
    }
    self->frames_left--;
    int done = self->frames_left <= 0;
    if (done) {
        self->offset_x = 0;
        self->offset_y = 0;
    }
    MesBg_SetScroll((MesBg *) (void *) self->window, self->offset_x, self->offset_y + 4);
    if (done) {
        MesSliderWindow_Open((MesSliderWindow *) (void *) self->window);
        MesSliderWindow_SetButtons((MesSliderWindow *) (void *) self->window, TalkSlider_TouchOrStart(&self->slider) == 0, 0);
        TalkSlider_Show(&self->slider);
        TalkSliderWindow_EnterOpen(self);
    }
}
CLEAN_AS(func_020a9fac, TalkSliderWindow_StepOpening)

/* func_020aa09c: opening: the slider reset, the message window loaded, laid out, uploaded and
 * shown at the start of its slide in, with the opening sound. */
void TalkSliderWindow_StartOpening(TalkSliderWindow *self)
{
    self->state = TALK_WINDOW_OPENING;
    MesBg_Load((MesBg *) (void *) self->window);
    TalkSlider_Start(&self->slider);
    TalkSliderWindow_LayOut(self);
    MesBg_SetBgControl((MesBg *) (void *) self->window);
    MesBg_UploadScreen((MesBg *) (void *) self->window);
    MesBg_Show((MesBg *) (void *) self->window);
    MesBg_FreeScreen((MesBg *) (void *) self->window);
    self->frames_left = GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 2) + 3;
    self->offset_x = GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 4) + 5;
    self->offset_y = GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 5) - 5;
    MesBg_SetScroll((MesBg *) (void *) self->window, self->offset_x, self->offset_y + 4);
    MesBg_ResetLineColours((MesBg *) (void *) self->window);
    SoundSys_PlaySe(TALK_WINDOW_SE_OPEN);
}
CLEAN_AS(func_020aa09c, TalkSliderWindow_StartOpening)

/* func_020aa13c (closed): opening once asked to. */
void TalkSliderWindow_StepClosed(TalkSliderWindow *self)
{
    if (self->base.open_requested != 0) {
        self->base.open_requested = 0;
        TalkSliderWindow_StartOpening(self);
    }
}
CLEAN_AS(func_020aa13c, TalkSliderWindow_StepClosed)

/* func_020aa154: closed, its message window hidden. */
void TalkSliderWindow_EnterClosed(TalkSliderWindow *self)
{
    self->state = TALK_WINDOW_CLOSED;
    MesBg_Hide((MesBg *) (void *) self->window);
}
CLEAN_AS(func_020aa154, TalkSliderWindow_EnterClosed)

/* func_020aa164 (slot 5) */
u8 TalkSliderWindow_Decided(TalkSliderWindow *self)
{
    return self->decided;
}
CLEAN_AS(func_020aa164, TalkSliderWindow_Decided)

/* func_020aa170 (slot 4) */
int TalkSliderWindow_IsClosed(TalkSliderWindow *self)
{
    return self->state == TALK_WINDOW_CLOSED;
}
CLEAN_AS(func_020aa170, TalkSliderWindow_IsClosed)

/* func_020aa180 (slot 3): the message window drawn and its colours uploaded. */
void TalkSliderWindow_Draw(TalkSliderWindow *self)
{
    talk_window_call(self->window, TALK_WINDOW_MESSAGE_SLOT_DRAW);
    MesBg_UploadColours((MesBg *) (void *) self->window);
}
CLEAN_AS(func_020aa180, TalkSliderWindow_Draw)

/* func_020aa19c (slot 2): the state's step, through the game's table (filled on the first
 * call), then the message window's frame.
 * REQUIRES: the state is 0-3 (the ROM indexes its table unchecked). */
void TalkSliderWindow_Update(TalkSliderWindow *self)
{
    static const MemberPointer *const constants[4] = {
        &data_020e3f6c, /* TalkSliderWindow_StepClosed */
        &data_020e3f74, /* TalkSliderWindow_StepOpening */
        &data_020e3edc, /* TalkSliderWindow_StepOpen */
        &data_020e3ef4, /* TalkSliderWindow_StepClosing */
    };
    MemberTable_InitOnce(&data_021f45ac, data_021f45d0, constants, 4);
    MemberPointer_CallVoid(&data_021f45d0[self->state], self);
    talk_window_call(self->window, TALK_WINDOW_MESSAGE_SLOT_UPDATE);
}
CLEAN_AS(func_020aa19c, TalkSliderWindow_Update)

/* func_020aa228 (slot 1): destroyed (as TalkSliderWindow_Destruct) and freed. */
TalkSliderWindow *TalkSliderWindow_Delete(TalkSliderWindow *self)
{
    self->base.vtable = data_020e404c;
    TalkSlider_Destruct(&self->slider);
    MesSliderWindow_Destruct((MesSliderWindow *) (void *) self->window);
    TalkWindow_BaseDestruct(&self->base);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020aa228, TalkSliderWindow_Delete)

/* func_020aa25c (slot 0): the destructor: the slider, the message window, then the base. */
TalkSliderWindow *TalkSliderWindow_Destruct(TalkSliderWindow *self)
{
    self->base.vtable = data_020e404c;
    TalkSlider_Destruct(&self->slider);
    MesSliderWindow_Destruct((MesSliderWindow *) (void *) self->window);
    TalkWindow_BaseDestruct(&self->base);
    return self;
}
CLEAN_AS(func_020aa25c, TalkSliderWindow_Destruct)

/* func_020aa28c: the constructor: closed, its slider working on its message window. */
TalkSliderWindow *TalkSliderWindow_Construct(TalkSliderWindow *self)
{
    TalkWindow_Construct(&self->base);
    self->base.vtable = data_020e404c;
    self->state = TALK_WINDOW_CLOSED;
    MesSliderWindow_Construct((MesSliderWindow *) (void *) self->window);
    TalkSlider_Construct(&self->slider, self->window);
    self->offset_x = 0;
    self->offset_y = 0;
    self->frames_left = 0;
    self->decided = 0;
    return self;
}
CLEAN_AS(func_020aa28c, TalkSliderWindow_Construct)

/* func_020aa2e4: the slider handed `choices`. */
void TalkSliderWindow_SetChoices(TalkSliderWindow *self, void *choices)
{
    TalkSlider_SetChoices(&self->slider, choices);
}
CLEAN_AS(func_020aa2e4, TalkSliderWindow_SetChoices)

/* ---- The choice window */

/* func_020aa2f4: the message window as wide as the choices say, with the frame of their
 * layout (none for another layout). */
void TalkChoiceWindow_LayOut(TalkChoiceWindow *self)
{
    unsigned int layout = TalkChoiceCursor_Count((TalkChoiceCursor *) (void *) self->list);
    MesBg_SetColumns((MesBg *) (void *) self->window, TalkChoiceCursor_LabelCells((TalkChoiceCursor *) (void *) self->list));
    switch (layout) {
        case 1:
            MesBg_ShapeOneLine((MesBg *) (void *) self->window);
            break;
        case 2:
            MesBg_ShapeTwoLines((MesBg *) (void *) self->window);
            break;
        case 3:
            MesBg_ShapeThreeLines((MesBg *) (void *) self->window);
            break;
        case 4:
            MesBg_ShapeFourLines((MesBg *) (void *) self->window);
            break;
        case 5:
            MesBg_ShapeFiveLines((MesBg *) (void *) self->window);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020aa2f4, TalkChoiceWindow_LayOut)

/* func_020aa360 (closing): the message window slides on out; at the end the cursor is reset,
 * the message window hidden and the window closed. */
void TalkChoiceWindow_StepClosing(TalkChoiceWindow *self)
{
    self->offset_x += GameVariables_Tweak(TALK_WINDOW_TWEAK_CLOSING, 3) + 0x11;
    self->offset_y += GameVariables_Tweak(TALK_WINDOW_TWEAK_CLOSING, 4) - 0x11;
    self->frames_left--;
    int done = self->frames_left <= 0;
    MesBg_SetScroll((MesBg *) (void *) self->window, self->offset_x, self->offset_y);
    self->decided = 0;
    if (done) {
        TalkChoiceCursor_Close((TalkChoiceCursor *) (void *) self->list);
        MesBg_Hide((MesBg *) (void *) self->window);
        TalkChoiceWindow_EnterClosed(self);
    }
}
CLEAN_AS(func_020aa360, TalkChoiceWindow_StepClosing)

/* func_020aa3f4: closing, a choice having been taken: the slide out starts, with its sound. */
void TalkChoiceWindow_StartClosing(TalkChoiceWindow *self)
{
    self->state = TALK_WINDOW_CLOSING;
    self->decided = 1;
    self->frames_left = GameVariables_Tweak(TALK_WINDOW_TWEAK_CLOSING, 2) + 2;
    SoundSys_PlaySe(TALK_WINDOW_SE_CLOSE);
}
CLEAN_AS(func_020aa3f4, TalkChoiceWindow_StartClosing)

/* func_020aa420 (open): the cursor's frame, shown in the message window; once a choice is
 * taken, the message window's marker animates it, and when its animation ends the window
 * closes. */
void TalkChoiceWindow_StepOpen(TalkChoiceWindow *self)
{
    unsigned char *window = self->window;

    TalkChoiceCursor_Update((TalkChoiceCursor *) (void *) self->list);
    MesChoiceWindow_SetButtons((MesChoiceWindow *) (void *) window,
                               TalkChoiceCursor_UsesTouch((TalkChoiceCursor *) (void *) self->list) == 0, 1);
    MesChoiceWindow_SetCursor((MesChoiceWindow *) (void *) window,
                              TalkChoiceCursor_Position((TalkChoiceCursor *) (void *) self->list));
    int choice = TalkChoiceCursor_Picked((TalkChoiceCursor *) (void *) self->list);
    if (choice < 0) {
        return;
    }
    if (MesChoiceWindow_MarkerBeside((MesChoiceWindow *) (void *) window)) {
        MesChoiceWindow_PressMarker((MesChoiceWindow *) (void *) window);
        MesChoiceWindow_ResetFlash((MesChoiceWindow *) (void *) window);
        return;
    }
    if (MesChoiceWindow_PressDone((MesChoiceWindow *) (void *) window) &&
        MesChoiceWindow_FlashChoice((MesChoiceWindow *) (void *) window, choice)) {
        MesChoiceWindow_HideMarker((MesChoiceWindow *) (void *) window);
        TalkChoiceCursor_Hide((TalkChoiceCursor *) (void *) self->list);
        TalkChoiceWindow_StartClosing(self);
    }
}
CLEAN_AS(func_020aa420, TalkChoiceWindow_StepOpen)

/* func_020aa4c0: open, the message window showing the input mode. */
void TalkChoiceWindow_EnterOpen(TalkChoiceWindow *self)
{
    self->state = TALK_WINDOW_OPEN;
    MesChoiceWindow_Open((MesChoiceWindow *) (void *) self->window);
    MesChoiceWindow_SetButtons((MesChoiceWindow *) (void *) self->window,
                               TalkChoiceCursor_UsesTouch((TalkChoiceCursor *) (void *) self->list) == 0, 0);
}
CLEAN_AS(func_020aa4c0, TalkChoiceWindow_EnterOpen)

/* func_020aa4f4 (opening): the message window slides on in, faster for the first frames; at
 * the end it is in place and the window open. */
void TalkChoiceWindow_StepOpening(TalkChoiceWindow *self)
{
    if (self->frames_left > GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 3) + 2) {
        self->offset_x += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 6) - 6;
        self->offset_y += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 7) + 6;
    } else {
        self->offset_x += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 8) + 1;
        self->offset_y += GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 9) - 1;
    }
    self->frames_left--;
    int done = self->frames_left <= 0;
    if (done) {
        self->offset_x = 0;
        self->offset_y = 0;
    }
    MesBg_SetScroll((MesBg *) (void *) self->window, self->offset_x, self->offset_y);
    if (done) {
        TalkChoiceCursor_Show((TalkChoiceCursor *) (void *) self->list);
        TalkChoiceWindow_EnterOpen(self);
    }
}
CLEAN_AS(func_020aa4f4, TalkChoiceWindow_StepOpening)

/* func_020aa5d0: opening: the cursor reset, the message window loaded, laid out, uploaded and
 * shown at the start of its slide in.
 * QUIRK: no sound, where the slider window plays one (the talk plays it itself). */
void TalkChoiceWindow_StartOpening(TalkChoiceWindow *self)
{
    self->state = TALK_WINDOW_OPENING;
    MesBg_Load((MesBg *) (void *) self->window);
    TalkChoiceCursor_Start((TalkChoiceCursor *) (void *) self->list);
    TalkChoiceWindow_LayOut(self);
    MesBg_SetBgControl((MesBg *) (void *) self->window);
    MesBg_UploadScreen((MesBg *) (void *) self->window);
    MesBg_Show((MesBg *) (void *) self->window);
    MesBg_FreeScreen((MesBg *) (void *) self->window);
    self->frames_left = GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 2) + 3;
    self->offset_x = GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 4) + 5;
    self->offset_y = GameVariables_Tweak(TALK_WINDOW_TWEAK_OPENING, 5) - 5;
    MesBg_SetScroll((MesBg *) (void *) self->window, self->offset_x, self->offset_y);
    MesBg_ResetLineColours((MesBg *) (void *) self->window);
}
CLEAN_AS(func_020aa5d0, TalkChoiceWindow_StartOpening)

/* func_020aa660 (closed): opening once asked to. */
void TalkChoiceWindow_StepClosed(TalkChoiceWindow *self)
{
    if (self->base.open_requested != 0) {
        self->base.open_requested = 0;
        TalkChoiceWindow_StartOpening(self);
    }
}
CLEAN_AS(func_020aa660, TalkChoiceWindow_StepClosed)

/* func_020aa678: closed (the closing hid the message window). */
void TalkChoiceWindow_EnterClosed(TalkChoiceWindow *self)
{
    self->state = TALK_WINDOW_CLOSED;
}
CLEAN_AS(func_020aa678, TalkChoiceWindow_EnterClosed)

/* func_020aa680 (slot 5) */
u8 TalkChoiceWindow_Decided(TalkChoiceWindow *self)
{
    return self->decided;
}
CLEAN_AS(func_020aa680, TalkChoiceWindow_Decided)

/* func_020aa688 (slot 4) */
int TalkChoiceWindow_IsClosed(TalkChoiceWindow *self)
{
    return self->state == TALK_WINDOW_CLOSED;
}
CLEAN_AS(func_020aa688, TalkChoiceWindow_IsClosed)

/* func_020aa698 (slot 3): the message window drawn and its colours uploaded. */
void TalkChoiceWindow_Draw(TalkChoiceWindow *self)
{
    talk_window_call(self->window, TALK_WINDOW_MESSAGE_SLOT_DRAW);
    MesBg_UploadColours((MesBg *) (void *) self->window);
}
CLEAN_AS(func_020aa698, TalkChoiceWindow_Draw)

/* func_020aa6b4 (slot 2): the state's step, through the game's table (filled on the first
 * call), then the message window's frame.
 * REQUIRES: the state is 0-3 (the ROM indexes its table unchecked). */
void TalkChoiceWindow_Update(TalkChoiceWindow *self)
{
    static const MemberPointer *const constants[4] = {
        &data_020e3f3c, /* TalkChoiceWindow_StepClosed */
        &data_020e3f34, /* TalkChoiceWindow_StepOpening */
        &data_020e3f24, /* TalkChoiceWindow_StepOpen */
        &data_020e3f2c, /* TalkChoiceWindow_StepClosing */
    };
    MemberTable_InitOnce(&data_021f45a4, data_021f45f0, constants, 4);
    MemberPointer_CallVoid(&data_021f45f0[self->state], self);
    talk_window_call(self->window, TALK_WINDOW_MESSAGE_SLOT_UPDATE);
}
CLEAN_AS(func_020aa6b4, TalkChoiceWindow_Update)

/* func_020aa740 (slot 1): destroyed (as TalkChoiceWindow_Destruct) and freed. */
TalkChoiceWindow *TalkChoiceWindow_Delete(TalkChoiceWindow *self)
{
    self->base.vtable = data_020e406c;
    TalkChoiceCursor_Destruct((TalkChoiceCursor *) (void *) self->list);
    MesChoiceWindow_Destruct((MesChoiceWindow *) (void *) self->window);
    TalkWindow_BaseDestruct(&self->base);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020aa740, TalkChoiceWindow_Delete)

/* func_020aa770 (slot 0): the destructor: the cursor, the message window, then the base. */
TalkChoiceWindow *TalkChoiceWindow_Destruct(TalkChoiceWindow *self)
{
    self->base.vtable = data_020e406c;
    TalkChoiceCursor_Destruct((TalkChoiceCursor *) (void *) self->list);
    MesChoiceWindow_Destruct((MesChoiceWindow *) (void *) self->window);
    TalkWindow_BaseDestruct(&self->base);
    return self;
}
CLEAN_AS(func_020aa770, TalkChoiceWindow_Destruct)

/* func_020aa79c: the constructor: closed, its cursor working on its message window. */
TalkChoiceWindow *TalkChoiceWindow_Construct(TalkChoiceWindow *self)
{
    TalkWindow_Construct(&self->base);
    self->base.vtable = data_020e406c;
    self->state = TALK_WINDOW_CLOSED;
    MesChoiceWindow_Construct((MesChoiceWindow *) (void *) self->window);
    TalkChoiceCursor_Construct((TalkChoiceCursor *) (void *) self->list, self->window);
    self->offset_x = 0;
    self->offset_y = 0;
    self->frames_left = 0;
    self->decided = 0;
    return self;
}
CLEAN_AS(func_020aa79c, TalkChoiceWindow_Construct)

/* func_020aa7e8: the cursor handed `choices`. */
void TalkChoiceWindow_SetChoices(TalkChoiceWindow *self, void *choices)
{
    TalkChoiceCursor_SetAnswers((TalkChoiceCursor *) (void *) self->list, choices);
}
CLEAN_AS(func_020aa7e8, TalkChoiceWindow_SetChoices)

/* ---- The base class */

/* func_020aa7f4: asked to open on its next frame. */
void TalkWindow_RequestOpen(TalkWindow *self)
{
    self->open_requested = 1;
}
CLEAN_AS(func_020aa7f4, TalkWindow_RequestOpen)

/* func_020aa7fc: the destructor the derived classes call: its vtable put back. */
void TalkWindow_BaseDestruct(TalkWindow *self)
{
    self->vtable = data_020e408c;
}
CLEAN_AS(func_020aa7fc, TalkWindow_BaseDestruct)

/* func_020aa808 (slot 1): destroyed and freed. */
TalkWindow *TalkWindow_Delete(TalkWindow *self)
{
    self->vtable = data_020e408c;
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_020aa808, TalkWindow_Delete)

/* func_020aa820 (slot 0): the destructor. */
void TalkWindow_Destruct(TalkWindow *self)
{
    self->vtable = data_020e408c;
}
CLEAN_AS(func_020aa820, TalkWindow_Destruct)

/* func_020aa82c: the constructor: not asked to open. */
void TalkWindow_Construct(TalkWindow *self)
{
    self->vtable = data_020e408c;
    self->open_requested = 0;
}
CLEAN_AS(func_020aa82c, TalkWindow_Construct)
