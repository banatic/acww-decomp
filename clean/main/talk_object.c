/* A talk (talk_object.h). */
#include "talk_object.h"

#include <string.h>

#include "clean.h"
#include "mail_particles.h"
#include "menu_input.h"
#include "message_reader.h"
#include "number_text.h"
#include "ov004/member_pointer.h"
#include "player_options.h"
#include "text_base.h"
#include "autoload_2/approach.h"

static_assert(offsetof(TalkObject, window) == 0x001c, "talk window");
static_assert(offsetof(TalkObject, shake_angle) == 0x00a0, "talk shake");
static_assert(offsetof(TalkObject, choice_windows) == 0x00b4, "talk choice windows");
static_assert(offsetof(TalkObject, answers) == 0x031c, "talk answers");
static_assert(offsetof(TalkObject, name_box) == 0x0680, "talk name box");
static_assert(offsetof(TalkObject, page) == 0x0684, "talk page");
static_assert(offsetof(TalkObject, walker) == 0x13b8, "talk walker");
static_assert(offsetof(TalkObject, run) == 0x149c, "talk run");
static_assert(offsetof(TalkObject, receiver) == 0x14a8, "talk receiver");
static_assert(offsetof(TalkObject, parts) == 0x14b8, "talk parts");
static_assert(offsetof(TalkObject, values) == 0x18ac, "talk values");
static_assert(offsetof(TalkObject, value_kinds) == 0x1a1c, "talk value kinds");
static_assert(offsetof(TalkObject, voice) == 0x1a2c, "talk voice");
static_assert(offsetof(TalkObject, particles) == 0x1a58, "talk particles");
static_assert(offsetof(TalkObject, year) == 0x1a64, "talk year");
static_assert(offsetof(TalkObject, second) == 0x1a70, "talk second");
static_assert(offsetof(TalkObject, year_text) == 0x1a78, "talk year text");
static_assert(offsetof(TalkObject, second_text) == 0x1c30, "talk second text");
static_assert(offsetof(TalkObject, town_name) == 0x1c8c, "talk town name");
static_assert(offsetof(TalkObject, other_player) == 0x1d2c, "talk other player");
static_assert(offsetof(TalkObject, impression) == 0x1da8, "talk impression");
static_assert(offsetof(TalkObject, memory) == 0x1e4c, "talk memory");
static_assert(offsetof(TalkObject, message) == 0x1e77, "talk message");
static_assert(offsetof(TalkObject, go_on) == 0x1e92, "talk go on");
static_assert(offsetof(TalkObject, quiet) == 0x1e9a, "talk quiet");
static_assert(sizeof(TalkObject) == 0x1e9c, "talk");

/* The talks (TALK_OBJECT_COUNT of them), or NULL. */
extern TalkObject *data_021cda88;

/* "No message" in TalkObject.message. */
extern u8 data_021f43f8;

/* The name plate's palettes (the top 4 bits of a screen entry): without a villager, for a
 * speaker of style 1, for the others. */
extern u16 data_020ccf50;
extern u16 data_020ccf54;
extern u16 data_020ccf58;
/* The year's text before its two digits. */
extern const char data_020cce80[];

/* The table of the states' steps (a function-local static of the game, filled on the first
 * call): the guard, the table, and the constants it is filled from (Base_02068144::func_020670f8,
 * func_02066f2c, func_02066dc4, func_02066cd4, func_02066be0, func_02066bd0). */
extern u32 data_021cda5c;
extern MemberPointer data_021cdb14[6];
extern const MemberPointer data_020deea4, data_020de804, data_020de814, data_020de9e4, data_020de82c, data_020de83c;

extern const s16 FX_SinCosTable_[];
extern s32 FX_MulFunc(s32 a, s32 b);
extern void *G2_GetBG2ScrPtr(void);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The runtime's new[] and delete[] of an array with a header of `prefix` bytes. */
extern void *func_02138e38(int count, int size, int prefix, void (*construct)(void *), void (*destruct)(void *));
extern void func_02138c00(void *array, unsigned int size, unsigned int prefix, void (*destruct)(void *));

/* The constructor and destructor of a message part and of a talk, handed to the game as they
 * are. */
extern void *func_020a8228(void *part);
extern void *func_020a8210(void *part);
extern void *func_02068644(void *talk);
extern void *func_020684b0(void *talk);

/* The state asked for entered (talk_flow.h). */
extern void func_02067108(TalkObject *talk);
/* The speaker's name: its label box freed, and made again. */
extern void func_020675c0(TalkObject *talk);
extern void func_020675e0(TalkObject *talk);
/* The message window: constructed, destroyed, run, drawn, placed; its spinner started and
 * stopped. */
extern void *func_02069128(void *window);
extern void *func_02069100(void *window);
extern void func_020690ec(void *window);
extern void func_020690d8(void *window);
extern void func_02068d44(void *window, s32 x, s32 y);
extern void func_02068c24(void *window, int sound);
extern void func_02068c10(void *window);
/* The part at 0xb14: constructed and destroyed. */
extern void *func_0206d688(void *part);
extern void *func_0206d670(void *part);

/* The receiver's vtable slot 0x68: the villager talked to, or NULL. */
#define TALK_OBJECT_SLOT_VILLAGER 0x68

/* The touch screen's box that goes on with or hurries the message. */
#define TALK_OBJECT_TOUCH_LEFT 8
#define TALK_OBJECT_TOUCH_RIGHT 0xf8
#define TALK_OBJECT_TOUCH_TOP 0x70
#define TALK_OBJECT_TOUCH_BOTTOM 0xc0

/* The name plate on BG2 of the main screen (32 entries a row): rows 13 to 16, columns 3 to
 * 14; its entries' palette bits. */
#define TALK_OBJECT_PLATE_TOP 13
#define TALK_OBJECT_PLATE_BOTTOM 16
#define TALK_OBJECT_PLATE_LEFT 3
#define TALK_OBJECT_PLATE_RIGHT 14
#define TALK_OBJECT_SCREEN_WIDTH 32
#define TALK_OBJECT_PALETTE_BITS 0xf000

/* The speaker's style whose name plate takes data_020ccf54. */
#define TALK_OBJECT_STYLE_1 1

typedef int TalkObjectSlot(void *receiver);

static s16 talk_object_cos(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2 + 1];
}

static s16 talk_object_sin(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2];
}

/* func_02067c74: each frame of a shake while the talk writes or waits: the window swings
 * about its place, a quarter turn a frame, by an amplitude that falls to 0; otherwise (or once
 * the amplitude is 0) the shake ends and the window is back in its place.
 * QUIRK: the amplitude falls by a step even in another state, where the shake then ends. */
void TalkObject_Shake(TalkObject *talk)
{
    if (talk->shake_amplitude == 0) {
        return;
    }
    int shown = talk->state == TALK_OBJECT_WRITING || talk->state == TALK_OBJECT_WAITING;
    int ended = Approach_S32((int *) &talk->shake_amplitude, 0, talk->shake_fall) != 0;
    if (shown && !ended) {
        talk->shake_angle = (u16) (talk->shake_angle + 0x4000);
        s32 x = FX_MulFunc(talk->shake_amplitude, talk->shake_scale_x);
        s32 y = FX_MulFunc(talk->shake_amplitude, talk->shake_scale_y);
        u16 angle = talk->shake_angle;
        x = FX_MulFunc(talk_object_cos((u16) (angle + 0x2000)), x);
        y = FX_MulFunc(talk_object_sin((u16) (angle * 2 - 0x4000)), y);
        func_02068d44(talk->window, -(x >> 12), talk->window_offset + (y >> 12));
    } else {
        talk->shake_angle = 0;
        talk->shake_amplitude = 0;
        talk->shake_fall = 0;
        talk->shake_scale_x = 0;
        talk->shake_scale_y = 0;
        func_02068d44(talk->window, 0, talk->window_offset);
    }
}
CLEAN_AS(func_02067c74, TalkObject_Shake)

/* func_02067d7c: the player hurries the message: the touch screen's box or B held (not a
 * press that only switched the input). */
int TalkObject_HurryPressed(TalkObject *talk)
{
    if (talk->silent != 0 || TalkObject_SwitchInputPressed(talk) != 0) {
        return 0;
    }
    if (MenuInput_TouchPressedIn(TALK_OBJECT_TOUCH_LEFT, TALK_OBJECT_TOUCH_RIGHT, TALK_OBJECT_TOUCH_TOP,
                                 TALK_OBJECT_TOUCH_BOTTOM) != 0) {
        return 1;
    }
    return MenuInput_BHeld() != 0;
}
CLEAN_AS(func_02067d7c, TalkObject_HurryPressed)

/* func_02067dbc: the player goes on: the touch screen's box, A or B pressed (not a press that
 * only switched the input). */
int TalkObject_AdvancePressed(TalkObject *talk)
{
    if (talk->silent != 0 || TalkObject_SwitchInputPressed(talk) != 0) {
        return 0;
    }
    if (MenuInput_TouchPressedIn(TALK_OBJECT_TOUCH_LEFT, TALK_OBJECT_TOUCH_RIGHT, TALK_OBJECT_TOUCH_TOP,
                                 TALK_OBJECT_TOUCH_BOTTOM) != 0) {
        return 1;
    }
    if (MenuInput_APressed() != 0) {
        return 1;
    }
    return MenuInput_BPressed() != 0;
}
CLEAN_AS(func_02067dbc, TalkObject_AdvancePressed)

/* func_02067e04: a press that switches the input: a button while the touch screen is used, or
 * the touch screen while the buttons are; the input switched, and 1. */
int TalkObject_SwitchInputPressed(TalkObject *talk)
{
    if (talk->silent != 0) {
        return 0;
    }
    if (MenuInput_UsesTouch() != 0) {
        if (MenuInput_AnyPressed() != 0) {
            MenuInput_UseButtons();
            return 1;
        }
    } else if (MenuInput_UsesButtons() != 0) {
        if (MenuInput_TouchPressed() != 0) {
            MenuInput_UseTouch();
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02067e04, TalkObject_SwitchInputPressed)

/* func_02067e4c */
void TalkObject_ApplyInputMode(TalkObject *talk)
{
    if (talk->silent == 0) {
        MenuInput_ApplyMode();
    }
}
CLEAN_AS(func_02067e4c, TalkObject_ApplyInputMode)

/* func_02067e68 */
void TalkObject_TakeInputMode(TalkObject *talk)
{
    if (talk->silent == 0) {
        MenuInput_TakeMode();
    }
}
CLEAN_AS(func_02067e68, TalkObject_TakeInputMode)

/* func_02067e84: the name plate's palette set by the speaker (no villager talked to, the
 * speaker's style 1, or another), and the speaker's name made again. */
void TalkObject_ColourNamePlate(TalkObject *talk)
{
    TalkReceiver *receiver = talk->receiver;
    const u8 *vtable = *(const u8 *const *) (const void *) receiver;
    u32 function = *(const u32 *) (const void *) (vtable + TALK_OBJECT_SLOT_VILLAGER);
    int no_villager = ((TalkObjectSlot *) (uintptr_t) function)(receiver) == 0;
    int style = TalkReceiver_SpeakerStyle(talk->receiver);
    u16 *screen = G2_GetBG2ScrPtr();
    u16 palette;
    if (no_villager) {
        palette = data_020ccf50;
    } else if (style == TALK_OBJECT_STYLE_1) {
        palette = data_020ccf54;
    } else {
        palette = data_020ccf58;
    }
    for (int y = TALK_OBJECT_PLATE_TOP; y <= TALK_OBJECT_PLATE_BOTTOM; y++) {
        u16 *row = screen + y * TALK_OBJECT_SCREEN_WIDTH;
        for (int x = TALK_OBJECT_PLATE_LEFT; x <= TALK_OBJECT_PLATE_RIGHT; x++) {
            row[x] = (u16) ((row[x] & ~TALK_OBJECT_PALETTE_BITS) | palette);
        }
    }
    func_020675c0(talk);
    func_020675e0(talk);
}
CLEAN_AS(func_02067e84, TalkObject_ColourNamePlate)

/* func_02067f28: a shake of the window asked for (TalkObject_Shake runs it).
 * QUIRK: the amplitude falls by 1.5 times `fall` a frame (rounded down). */
void TalkObject_StartShake(TalkObject *talk, s32 amplitude, s32 fall, s32 scale_x, s32 scale_y)
{
    talk->shake_angle = 0;
    talk->shake_amplitude = amplitude;
    talk->shake_scale_x = scale_x;
    talk->shake_scale_y = scale_y;
    talk->shake_fall = (fall * 3) >> 1;
}
CLEAN_AS(func_02067f28, TalkObject_StartShake)

/* func_02067f74: the second the talk began, as two digits; the text (a MessageText46). */
void *TalkObject_SecondText(TalkObject *talk)
{
    NumberText_Format(&talk->second_text, (int) talk->second, 2, 0, 0, 0);
    return &talk->second_text;
}
CLEAN_AS(func_02067f74, TalkObject_SecondText)

/* func_02067fa4: the minute, as two digits with its unit word (unit 9). */
void *TalkObject_MinuteText(TalkObject *talk)
{
    NumberText_Format(&talk->minute_text, talk->minute, 2, 0, 9, 0);
    return &talk->minute_text;
}
CLEAN_AS(func_02067fa4, TalkObject_MinuteText)

/* func_02067fd4: the hour on a 12-hour clock (12 for 0 and 12). */
void *TalkObject_HourText(TalkObject *talk)
{
    unsigned int hour = talk->hour;
    if (hour >= 12) {
        hour -= 12;
    }
    if (hour == 0) {
        hour = 12;
    }
    NumberText_Format(&talk->hour_text, (int) hour, 2, 0, 0, 0);
    return &talk->hour_text;
}
CLEAN_AS(func_02067fd4, TalkObject_HourText)

/* func_02068010: the weekday's name (a general message); the text (a MessagePart). */
void *TalkObject_WeekdayText(TalkObject *talk)
{
    MessageReader_LoadGeneral(&talk->weekday_text, talk->weekday, 0);
    return &talk->weekday_text;
}
CLEAN_AS(func_02068010, TalkObject_WeekdayText)

/* func_02068034: the day. */
void *TalkObject_DayText(TalkObject *talk)
{
    NumberText_SetTwoDigits(&talk->day_text, talk->day);
    return &talk->day_text;
}
CLEAN_AS(func_02068034, TalkObject_DayText)

/* func_02068058: the month. */
void *TalkObject_MonthText(TalkObject *talk)
{
    NumberText_SetTwoDigitsB(&talk->month_text, talk->month);
    return &talk->month_text;
}
CLEAN_AS(func_02068058, TalkObject_MonthText)

/* func_0206807c: the year: data_020cce80's text, then its two digits. */
void *TalkObject_YearText(TalkObject *talk)
{
    MessagePart digits;
    MessagePart_Construct(&digits);
    NumberText_Format(&digits, talk->year, 2, 6, 0, 0);
    TextBase_SetChars((TextBase *) (void *) &talk->year_text, data_020cce80);
    TextBase_AppendText(&talk->year_text, (TextBase *) (void *) &digits);
    MessagePart_Destruct(&digits);
    return &talk->year_text;
}
CLEAN_AS(func_0206807c, TalkObject_YearText)

/* func_020680d0: the mouth stopped and the characters to voice cleared. */
void TalkObject_ClearVoice(TalkObject *talk)
{
    talk->voiced = 0;
    TalkVoice_Clear(&talk->voice, 1);
}
CLEAN_AS(func_020680d0, TalkObject_ClearVoice)

/* func_020680ec */
void TalkObject_SetVoiced(TalkObject *talk, int voiced)
{
    talk->voiced = voiced ? 1 : 0;
}
CLEAN_AS(func_020680ec, TalkObject_SetVoiced)

/* func_02068104: a character shown, handed to the voice. */
void TalkObject_PushVoiceChar(TalkObject *talk, int character)
{
    TalkVoice_PushChar(&talk->voice, (short) character);
}
CLEAN_AS(func_02068104, TalkObject_PushVoiceChar)

/* func_02068114: 1 when bit 0 of the player's options is clear. */
int TalkObject_OptionFlagOff(void)
{
    return PlayerOptions_FlagInUse() == 0;
}
CLEAN_AS(func_02068114, TalkObject_OptionFlagOff)

/* func_0206812c: the message window and the choice windows drawn. */
void TalkObject_Draw(TalkObject *talk)
{
    func_020690d8(talk->window);
    TalkWindows_Draw(&talk->choice_windows);
}
CLEAN_AS(func_0206812c, TalkObject_Draw)

/* func_02068144: each frame: the state's step, the state asked for entered, the shake, the
 * message window and the choice windows; then the input mode applied while the talk is up. */
void TalkObject_Update(TalkObject *talk)
{
    static const MemberPointer *const constants[6] = {
        &data_020deea4, &data_020de804, &data_020de814, &data_020de9e4, &data_020de82c, &data_020de83c,
    };
    MemberTable_InitOnce(&data_021cda5c, data_021cdb14, constants, 6);
    MemberPointer_CallVoid(&data_021cdb14[talk->state], talk);
    func_02067108(talk);
    TalkObject_Shake(talk);
    func_020690ec(talk->window);
    TalkWindows_Update(&talk->choice_windows);
    if (talk->state != TALK_OBJECT_CLOSED && talk->state != TALK_OBJECT_GONE) {
        TalkObject_ApplyInputMode(talk);
    }
}
CLEAN_AS(func_02068144, TalkObject_Update)

/* func_0206820c: both talks drawn, when they exist. */
void TalkObject_DrawAll(void)
{
    if (data_021cda88 == NULL) {
        return;
    }
    for (int i = 0; i < TALK_OBJECT_COUNT; i++) {
        TalkObject_Draw(&data_021cda88[i]);
    }
}
CLEAN_AS(func_0206820c, TalkObject_DrawAll)

/* func_0206823c: both talks run, when they exist. */
void TalkObject_UpdateAll(void)
{
    if (data_021cda88 == NULL) {
        return;
    }
    for (int i = 0; i < TALK_OBJECT_COUNT; i++) {
        TalkObject_Update(&data_021cda88[i]);
    }
}
CLEAN_AS(func_0206823c, TalkObject_UpdateAll)

/* func_0206826c: the talks destroyed and freed. */
void TalkObject_FreeAll(void)
{
    if (data_021cda88 != NULL) {
        func_02138c00(data_021cda88, sizeof(TalkObject), 8, (void (*)(void *))(uintptr_t) func_020684b0);
        data_021cda88 = NULL;
    }
}
CLEAN_AS(func_0206826c, TalkObject_FreeAll)

/* func_0206829c: the two talks allocated and constructed, each told its place.
 * REQUIRES: the allocation succeeds (the result is not checked). */
void TalkObject_AllocAll(void)
{
    data_021cda88 = func_02138e38(TALK_OBJECT_COUNT, sizeof(TalkObject), 8, (void (*)(void *))(uintptr_t) func_02068644,
                                  (void (*)(void *))(uintptr_t) func_020684b0);
    for (int i = 0; i < TALK_OBJECT_COUNT; i++) {
        data_021cda88[i].index = i;
    }
}
CLEAN_AS(func_0206829c, TalkObject_AllocAll)

/* func_020682e0: talk `index`, or NULL while there are none. */
TalkObject *TalkObject_Get(int index)
{
    if (data_021cda88 == NULL) {
        return NULL;
    }
    return &data_021cda88[index];
}
CLEAN_AS(func_020682e0, TalkObject_Get)

/* func_020682fc */
void TalkObject_SetQuiet(TalkObject *talk)
{
    talk->quiet = 1;
}
CLEAN_AS(func_020682fc, TalkObject_SetQuiet)

/* func_02068308 */
void TalkObject_SetUnk1e99(TalkObject *talk)
{
    talk->unk_1e99 = 1;
}
CLEAN_AS(func_02068308, TalkObject_SetUnk1e99)

/* func_02068314 */
void TalkObject_SetSilent(TalkObject *talk)
{
    talk->silent = 1;
}
CLEAN_AS(func_02068314, TalkObject_SetSilent)

/* func_02068320: the receiver let go of the talk, and the talk of it. */
void TalkObject_DetachReceiver(TalkObject *talk)
{
    if (talk->receiver != NULL) {
        TalkReceiver_DropTalk(talk->receiver);
        talk->receiver = NULL;
    }
}
CLEAN_AS(func_02068320, TalkObject_DetachReceiver)

/* func_02068340: the receiver shown by the talk, and told so. */
void TalkObject_AttachReceiver(TalkObject *talk, TalkReceiver *receiver)
{
    talk->receiver = receiver;
    TalkReceiver_SetTalk(receiver, (struct TalkFlowTalk *) (void *) talk);
}
CLEAN_AS(func_02068340, TalkObject_AttachReceiver)

/* func_02068358 */
void TalkObject_StopSpinner(TalkObject *talk)
{
    func_02068c10(talk->window);
}
CLEAN_AS(func_02068358, TalkObject_StopSpinner)

/* func_02068364 */
void TalkObject_StartSpinner(TalkObject *talk, int sound)
{
    func_02068c24(talk->window, sound);
}
CLEAN_AS(func_02068364, TalkObject_StartSpinner)

/* func_02068370: the speaker says the characters shown (the scenes move its mouth). */
u8 TalkObject_Voiced(TalkObject *talk)
{
    return talk->voiced;
}
CLEAN_AS(func_02068370, TalkObject_Voiced)

/* func_0206837c */
TalkAnswers *TalkObject_Answers(TalkObject *talk)
{
    return &talk->answers;
}
CLEAN_AS(func_0206837c, TalkObject_Answers)

/* func_02068388: the answers offered: once the walk stops (`later`), or now in the choice
 * windows. */
void TalkObject_OpenChoices(TalkObject *talk, int later)
{
    if (later) {
        talk->choices_asked = 1;
    } else {
        TalkWindows_ShowChoices(&talk->choice_windows, &talk->answers);
        TalkWindows_Open(&talk->choice_windows);
    }
}
CLEAN_AS(func_02068388, TalkObject_OpenChoices)

/* func_020683b4: value `index` a message's tags put in: a copy of `text`, and its kind. */
void TalkObject_SetValue(TalkObject *talk, int index, TextBase *text, int kind)
{
    TextBase_Copy((TextBase *) (void *) &talk->values[index], text);
    talk->value_kinds[index] = kind;
}
CLEAN_AS(func_020683b4, TalkObject_SetValue)

/* func_020683e4: part `index` loaded with message `*message` of the file `name`. */
int TalkObject_LoadPart(TalkObject *talk, int index, const u8 *message, unsigned int name)
{
    return MessageReader_LoadMessage((int) (uintptr_t) &talk->parts[index], (unsigned char *) (uintptr_t) message, (int) name);
}
CLEAN_AS(func_020683e4, TalkObject_LoadPart)

/* func_02068404: part `index` a copy of `text`. */
void TalkObject_SetPart(TalkObject *talk, int index, TextBase *text)
{
    TextBase_Copy((TextBase *) (void *) &talk->parts[index], text);
}
CLEAN_AS(func_02068404, TalkObject_SetPart)

/* func_0206841c */
void TalkObject_StopGoingOn(TalkObject *talk)
{
    talk->go_on = 0;
}
CLEAN_AS(func_0206841c, TalkObject_StopGoingOn)

/* func_02068428: the talk asked to go on with its message. */
void TalkObject_GoOn(TalkObject *talk)
{
    talk->go_on = 1;
}
CLEAN_AS(func_02068428, TalkObject_GoOn)

/* func_02068434 */
void TalkObject_Release(TalkObject *talk)
{
    talk->held = 0;
}
CLEAN_AS(func_02068434, TalkObject_Release)

/* func_02068440 */
void TalkObject_Hold(TalkObject *talk)
{
    talk->held = 1;
}
CLEAN_AS(func_02068440, TalkObject_Hold)

/* func_0206844c: the message to show: number `*message` of the file `name` (25 characters at
 * most), or of no file (the name cleared) when `name` is NULL. */
void TalkObject_SetMessage(TalkObject *talk, const u8 *message, const char *name)
{
    talk->message = *message;
    if (name != NULL) {
        strncpy(talk->name, name, TALK_OBJECT_NAME_SIZE - 1);
    } else {
        MI_CpuFill8(talk->name, 0, TALK_OBJECT_NAME_SIZE);
    }
}
CLEAN_AS(func_0206844c, TalkObject_SetMessage)

/* func_02068484: as TalkObject_SetMessage while the talk has no message; 1 when set. */
int TalkObject_SetMessageIfNone(TalkObject *talk, const u8 *message, const char *name)
{
    if (talk->message != data_021f43f8) {
        return 0;
    }
    TalkObject_SetMessage(talk, message, name);
    return 1;
}
CLEAN_AS(func_02068484, TalkObject_SetMessageIfNone)

/* func_020684b0: the destructor: the speaker's name freed, the receiver let go, then the
 * members destroyed in the reverse order of their construction. */
TalkObject *TalkObject_Destruct(TalkObject *talk)
{
    func_020675c0(talk);
    TalkObject_DetachReceiver(talk);
    VillagerMemoryLabel_Destruct(&talk->memory);
    Label22Text_Destruct(&talk->praise);
    PlayerIdText_Destruct(&talk->nickname);
    MessagePart_Destruct(&talk->impression);
    MessagePart_Destruct(&talk->boom);
    PlayerIdText_Destruct(&talk->other_player);
    PlayerIdText_Destruct(&talk->random_npc);
    PlayerIdText_Destruct(&talk->disliked_npc);
    PlayerIdText_Destruct(&talk->liked_npc);
    PlayerIdText_Destruct(&talk->unk_1cac);
    TownNameText_Destruct(&talk->town_name);
    Label10Text_Destruct(&talk->unk_1c70);
    MessageText46_Destruct(&talk->second_text);
    MessageText46_Destruct(&talk->minute_text);
    MessageText46_Destruct(&talk->hour_text);
    MessagePart_Destruct(&talk->weekday_text);
    MessageText46_Destruct(&talk->day_text);
    MessagePart_Destruct(&talk->month_text);
    MessageText46_Destruct(&talk->year_text);
    MailParticles_Destruct(&talk->particles);
    TalkVoice_Destruct(&talk->voice);
    __cxa_vec_cleanup(talk->values, TALK_OBJECT_VALUES, sizeof(MessagePart), (void (*)(void *))(uintptr_t) func_020a8210);
    __cxa_vec_cleanup(talk->parts, TALK_OBJECT_PARTS, sizeof(MessagePart), (void (*)(void *))(uintptr_t) func_020a8210);
    Block020a8248_Destruct(&talk->unk_14ac);
    MessageWalkRun_Destruct(&talk->run);
    TalkTags_Destruct(&talk->walker);
    func_0206d670(talk->unk_b14);
    TalkPage_Destruct(&talk->page);
    TalkAnswers_Destruct(&talk->answers);
    TalkWindows_Destruct(&talk->choice_windows);
    func_02069100(talk->window);
    return talk;
}
CLEAN_AS(func_020684b0, TalkObject_Destruct)

/* func_02068644: the constructor: closed (no state asked for), mode 4, no message, nothing
 * shaken, no receiver; the members constructed in order, the page and the walker on this
 * talk. */
TalkObject *TalkObject_Construct(TalkObject *talk)
{
    talk->index = 0;
    talk->state = TALK_OBJECT_CLOSED;
    talk->next_state = TALK_OBJECT_NO_STATE;
    talk->slide = 0;
    talk->unk_10 = 0;
    talk->mode = 4;
    talk->choices_asked = 0;
    func_02069128(talk->window);
    talk->window_offset = 0;
    talk->shake_angle = 0;
    talk->shake_amplitude = 0;
    talk->shake_fall = 0;
    talk->shake_scale_x = 0;
    talk->shake_scale_y = 0;
    TalkWindows_Construct(&talk->choice_windows);
    TalkAnswers_Construct(&talk->answers);
    talk->name_box = NULL;
    TalkPage_Construct(&talk->page, (u8 *) talk);
    func_0206d688(talk->unk_b14);
    TalkTags_Construct(&talk->walker, (u8 *) talk, &talk->page);
    MessageWalkRun_Construct(&talk->run, &talk->walker.base);
    talk->receiver = NULL;
    Block020a8248_Construct(&talk->unk_14ac);
    __cxa_vec_ctor(talk->parts, TALK_OBJECT_PARTS, sizeof(MessagePart), (void (*)(void *))(uintptr_t) func_020a8228,
                   (void (*)(void *))(uintptr_t) func_020a8210);
    __cxa_vec_ctor(talk->values, TALK_OBJECT_VALUES, sizeof(MessagePart), (void (*)(void *))(uintptr_t) func_020a8228,
                   (void (*)(void *))(uintptr_t) func_020a8210);
    TalkVoice_Construct(&talk->voice, talk);
    MailParticles_Construct(&talk->particles);
    talk->year = 0;
    talk->weekday = 0;
    talk->second = 0;
    talk->part_of_day = 0;
    MessageText46_Construct(&talk->year_text);
    MessagePart_Construct(&talk->month_text);
    MessageText46_Construct(&talk->day_text);
    MessagePart_Construct(&talk->weekday_text);
    MessageText46_Construct(&talk->hour_text);
    MessageText46_Construct(&talk->minute_text);
    MessageText46_Construct(&talk->second_text);
    Label10Text_Construct(&talk->unk_1c70);
    TownNameText_Construct(&talk->town_name);
    PlayerIdText_Construct(&talk->unk_1cac);
    PlayerIdText_Construct(&talk->liked_npc);
    PlayerIdText_Construct(&talk->disliked_npc);
    PlayerIdText_Construct(&talk->random_npc);
    PlayerIdText_Construct(&talk->other_player);
    MessagePart_Construct(&talk->boom);
    MessagePart_Construct(&talk->impression);
    PlayerIdText_Construct(&talk->nickname);
    Label22Text_Construct(&talk->praise);
    VillagerMemoryLabel_Construct(&talk->memory);
    talk->unk_1e74 = 0;
    talk->unk_1e75 = 0;
    talk->other_colour = 0;
    talk->message = data_021f43f8;
    talk->go_on = 0;
    talk->held = 0;
    talk->unk_1e94 = 0;
    talk->unk_1e95 = 0;
    talk->unk_1e96 = 0;
    talk->voiced = 0;
    talk->silent = 0;
    talk->unk_1e99 = 0;
    talk->quiet = 0;
    MI_CpuFill8(talk->name, 0, TALK_OBJECT_NAME_SIZE);
    return talk;
}
CLEAN_AS(func_02068644, TalkObject_Construct)
