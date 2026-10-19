/* A talk (talk_object.h). */
#include "talk_object.h"

#include <string.h>

#include "clean.h"
#include "bmg_file.h"
#include "c_library.h"
#include "calendar.h"
#include "clock.h"
#include "player_record.h"
#include "player_records.h"
#include "session_villager.h"
#include "sound.h"
#include "state_block.h"
#include "talk_flow.h"
#include "text_draw.h"
#include "villager_catchphrase.h"
#include "villager_impression.h"
#include "villager_memories.h"
#include "villager_memory_entry.h"
#include "villager_names.h"
#include "villager_status.h"
#include "talk_box.h"
#include "mail_particles.h"
#include "menu_input.h"
#include "message_reader.h"
#include "number_text.h"
#include "ov004/member_pointer.h"
#include "player_options.h"
#include "text_base.h"
#include "autoload_2/approach.h"
#include "talk_message_file.h"
#include "talk_pick_scan.h"

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
        TalkBox_SetPlace(&talk->window, -(x >> 12), talk->window_offset + (y >> 12));
    } else {
        talk->shake_angle = 0;
        talk->shake_amplitude = 0;
        talk->shake_fall = 0;
        talk->shake_scale_x = 0;
        talk->shake_scale_y = 0;
        TalkBox_SetPlace(&talk->window, 0, talk->window_offset);
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
    TalkObject_FreeNameBox(talk);
    TalkObject_MakeNameBox(talk);
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
    TalkBox_Draw(&talk->window);
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
    TalkFlow_EnterNext(talk);
    TalkObject_Shake(talk);
    TalkBox_Update(&talk->window);
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
    TalkReceiver_SetTalk(receiver, talk);
}
CLEAN_AS(func_02068340, TalkObject_AttachReceiver)

/* func_02068358 */
void TalkObject_StopSpinner(TalkObject *talk)
{
    TalkBox_StopSpinner(&talk->window);
}
CLEAN_AS(func_02068358, TalkObject_StopSpinner)

/* func_02068364 */
void TalkObject_StartSpinner(TalkObject *talk, int sound)
{
    TalkBox_StartSpinner(&talk->window, sound);
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
    return MessageReader_LoadMessage(&talk->parts[index], (unsigned char *) (uintptr_t) message,
                                     (const char *) (uintptr_t) name);
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
    TalkObject_FreeNameBox(talk);
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
    TalkMessageFile_Destruct((TalkMessageFile *) (void *) talk->unk_b14);
    TalkPage_Destruct(&talk->page);
    TalkAnswers_Destruct(&talk->answers);
    TalkWindows_Destruct(&talk->choice_windows);
    TalkBox_Destruct(&talk->window);
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
    TalkBox_Construct(&talk->window);
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
    TalkMessageFile_Construct((TalkMessageFile *) (void *) talk->unk_b14);
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

/* The first and the second part of a message file's name ("fu", "bo", ..., "obj", then "ai",
 * "tsu", ..., "q17"), each followed by '_' in the name: lists of strings ending with NULL. */
extern const char *const data_020ccec4[];
extern const char *const data_020ccee8[];
/* A message file's path, built by TalkObject_MessagePath: its buffer, and its formats with
 * both parts ("%s/%s/%s/%s_.bmg"), with the first only ("%s/%s/Other/%s_.bmg") and with none
 * ("%s/Other/%s_.bmg"). */
extern char data_021cdb74[];
extern const char data_020df094[];
extern const char data_020df0a8[];
extern const char data_020df0bc[];
/* The sound effects of a message by its entry's byte 9 (0 or 1; 0 for none). */
extern const u16 data_020cce84[];
/* The change of the villager's fondness for the player by a message's entry's byte 5. */
extern const s8 data_020ccea0[];
/* The state block: the town's name at its 0x02. */
extern StateBlock data_021dc7a8;

/* The receiver's vtable slots the talk calls here: the folder of the message files, what
 * begins with a message (0x10), what follows its end (0x14), the player's answer (0x18). */
#define TALK_OBJECT_SLOT_FOLDER 0x0c
#define TALK_OBJECT_SLOT_BEGUN 0x10
#define TALK_OBJECT_SLOT_ENDED 0x14
#define TALK_OBJECT_SLOT_ANSWER 0x18

/* The talk's message file (BmgFile) and its text buffer's slot (the derived class's slot 2). */
#define TALK_OBJECT_FILE_SLOT_BUFFER 0x08

/* A message's sounds (data_020cce84's entries). */
#define TALK_OBJECT_MESSAGE_SOUNDS 2

/* The speaker's name box: its first VRAM tile and its size in tiles, its screens, background
 * and text colours. */
#define TALK_OBJECT_NAME_TILE 0x89
#define TALK_OBJECT_NAME_CELLS 8
#define TALK_OBJECT_NAME_ROWS 2
#define TALK_OBJECT_NAME_SCREENS 2
#define TALK_OBJECT_NAME_BACKGROUND 0x0e
#define TALK_OBJECT_NAME_COLOUR 2

/* The kind a cleared value gets (TalkObject.value_kinds). */
#define TALK_OBJECT_VALUE_CLEARED 7

/* The size of the walker TalkObject_RunAnswerText builds on its stack. */
#define TALK_OBJECT_ANSWER_WALKER_SIZE 0x44

/* The receiver's vtable entry at `slot`. */
static u32 talk_object_receiver_slot(const TalkReceiver *receiver, int slot)
{
    const u8 *vtable = (const u8 *) receiver->base.vtable;
    return *(const u32 *) (const void *) (vtable + slot);
}

/* The villager talked to (the receiver's slot 0x68), or NULL. */
static u8 *talk_object_villager(TalkObject *talk)
{
    typedef u8 *TalkObjectVillager(TalkReceiver * receiver);
    TalkReceiver *receiver = talk->receiver;
    return ((TalkObjectVillager *) (uintptr_t) talk_object_receiver_slot(receiver, TALK_OBJECT_SLOT_VILLAGER))(receiver);
}

/* The receiver's slot `slot` told `value`. */
static void talk_object_tell(TalkObject *talk, int slot, int value)
{
    typedef void TalkObjectTell(TalkReceiver * receiver, int value);
    TalkReceiver *receiver = talk->receiver;
    ((TalkObjectTell *) (uintptr_t) talk_object_receiver_slot(receiver, slot))(receiver, value);
}

/* The characters of a text (its vtable's slot 3). */
static const char *talk_object_chars(void *text)
{
    typedef const char *TalkObjectChars(void *text);
    const TextVtable *vtable = *(const TextVtable *const *) text;
    return ((TalkObjectChars *) (uintptr_t) vtable->buffer)(text);
}

/* The talk's message file. */
static BmgFile *talk_object_file(TalkObject *talk)
{
    return (BmgFile *) (void *) talk->unk_b14;
}

/* This system's player. */
static DesignCreator *talk_object_player(void)
{
    return PlayerRecord_Player(PlayerRecords_Current());
}

/* func_020671fc: the receiver's message loaded and begun; the date and time noted. */
void TalkObject_StartMessage(TalkObject *talk)
{
    TalkObject_LoadMessage(talk);
    TalkObject_BeginMessage(talk);
    TalkObject_NoteTime(talk);
}
CLEAN_AS(func_020671fc, TalkObject_StartMessage)

/* func_02067218: the message the talk was given handed to the receiver (its number, and its
 * file when it has one) and the talk's cleared; then as TalkObject_StartMessage.
 * REQUIRES: the talk has a receiver. */
void TalkObject_StartGivenMessage(TalkObject *talk)
{
    talk->receiver->base.message = talk->message;
    if (talk->name[0] != 0) {
        MessageReceiver_SetName(&talk->receiver->base, talk->name);
    }
    TalkObject_SetMessage(talk, &data_021f43f8, NULL);
    TalkObject_LoadMessage(talk);
    TalkObject_BeginMessage(talk);
    TalkObject_NoteTime(talk);
}
CLEAN_AS(func_02067218, TalkObject_StartGivenMessage)

/* func_0206726c: the receiver's message read from its file into the talk's message file (the
 * text buffer cleared first; nothing read when the file does not open), and the message's
 * INF1 entry kept at 0x14ac. */
void TalkObject_LoadMessage(TalkObject *talk)
{
    BmgFile *file = talk_object_file(talk);
    TalkMessageFile_Clear((TalkMessageFile *) file);
    const char *path = TalkObject_MessagePath(talk, NULL, NULL);
    if (BmgFile_Open(file, path)) {
        BmgFile_LoadMessage(file, &talk->receiver->base.message);
    }
    Block020a8248_Copy(&talk->unk_14ac, BmgFile_Entry(file));
    BmgFile_Close(file);
}
CLEAN_AS(func_0206726c, TalkObject_LoadMessage)

/* The entry of `parts` that `name` begins with, followed by '_', or NULL. */
static const char *talk_object_find_part(const char *const *parts, const char *name)
{
    const char *part;
    while ((part = *parts) != NULL) {
        size_t length = strlen(part);
        if (strncmp(name, part, length) == 0 && name[length] == '_') {
            break;
        }
        parts++;
    }
    return part;
}

/* func_020672cc: the second part `name` begins with (data_020ccee8), or NULL. */
const char *TalkObject_FileSubfolder(TalkObject *talk, const char *name)
{
    (void) talk;
    return talk_object_find_part(data_020ccee8, name);
}
CLEAN_AS(func_020672cc, TalkObject_FileSubfolder)

/* func_02067308: the first part `name` begins with (data_020ccec4), or NULL. */
const char *TalkObject_FileFolder(TalkObject *talk, const char *name)
{
    (void) talk;
    return talk_object_find_part(data_020ccec4, name);
}
CLEAN_AS(func_02067308, TalkObject_FileFolder)

/* func_02067344: the path of the message file `name` (the receiver's file when NULL) under
 * `folder` (the receiver's folder, its slot 0x0c, when NULL): the name's first and second
 * parts are its folders, the rest of it the file's name ("Other" for a missing second part,
 * and the whole name in "Other" without a first part). Written to data_021cdb74, and returned.
 * REQUIRES: the talk has a receiver when either is NULL. */
char *TalkObject_MessagePath(TalkObject *talk, const char *name, const char *folder)
{
    typedef const char *TalkObjectFolder(TalkReceiver * receiver);

    if (folder == NULL) {
        TalkReceiver *receiver = talk->receiver;
        folder = ((TalkObjectFolder *) (uintptr_t) talk_object_receiver_slot(receiver, TALK_OBJECT_SLOT_FOLDER))(receiver);
    }
    if (name == NULL) {
        name = talk->receiver->base.name;
    }
    const char *first = TalkObject_FileFolder(talk, name);
    if (first == NULL) {
        CLib_SPrintf(data_021cdb74, data_020df0bc, folder, name);
        return data_021cdb74;
    }
    const char *rest = name + strlen(first) + 1;
    const char *second = TalkObject_FileSubfolder(talk, rest);
    if (second != NULL) {
        CLib_SPrintf(data_021cdb74, data_020df094, folder, first, second, rest + strlen(second) + 1);
    } else {
        CLib_SPrintf(data_021cdb74, data_020df0a8, folder, first, rest);
    }
    return data_021cdb74;
}
CLEAN_AS(func_02067344, TalkObject_MessagePath)

/* func_020673e0: the text of the answer picked walked by a walker of the talk's tags (so its
 * tags act on the talk). */
void TalkObject_RunAnswerText(TalkObject *talk)
{
    u32 walker[TALK_OBJECT_ANSWER_WALKER_SIZE / sizeof(u32)];
    u8 *text = TalkAnswers_PickedText(&talk->answers);
    TalkPickScan_Construct((TalkPickScan *) walker, talk);
    TalkPickScan_Run((TalkPickScan *) walker, talk_object_chars(text));
    TalkPickScan_Destruct((TalkPickScan *) walker);
}
CLEAN_AS(func_020673e0, TalkObject_RunAnswerText)

/* func_0206741c: the message begins: the receiver to be told of its beginning and its end,
 * no answer to tell; the page centred for the kinds of message that are (the entry's kind),
 * the walker's speed and the voice's muting by the kind; the message that follows (the
 * entry's byte 8) set, of no file; the receiver told the beginning, the message's sound
 * played, and the walk started over the file's text. */
void TalkObject_BeginMessage(TalkObject *talk)
{
    typedef int TalkObjectBuffer(BmgFile * file);

    talk->unk_1e95 = 1;
    talk->unk_1e94 = 1;
    talk->unk_1e96 = 0;
    TalkPage_SetCentred(&talk->page, Block020a8248_FlagOfKind(&talk->unk_14ac) == 1);
    int speed = (int) (uintptr_t) Block020a8248_ValueOfKind(&talk->unk_14ac);
    TalkTags_SetSpeed(&talk->walker, speed);
    talk->voice.unk_1c = speed == 1;

    u8 next = 0;
    Block020a8248_GetByte08(&next, &talk->unk_14ac);
    TalkObject_SetMessage(talk, &next, NULL);
    TalkObject_TellMessageBegun(talk);
    TalkObject_PlayMessageSound(talk);

    MessageWalkRun_Reset(&talk->run);
    BmgFile *file = talk_object_file(talk);
    const u8 *vtable = (const u8 *) file->vtable;
    u32 buffer = *(const u32 *) (const void *) (vtable + TALK_OBJECT_FILE_SLOT_BUFFER);
    MessageWalkRun_Start(&talk->run, ((TalkObjectBuffer *) (uintptr_t) buffer)(file));
}
CLEAN_AS(func_0206741c, TalkObject_BeginMessage)

/* func_020674d8: the sound of the message (its entry's byte 9), when it has one. */
void TalkObject_PlayMessageSound(TalkObject *talk)
{
    int sound = Block020a8248_Byte09(&talk->unk_14ac);
    if (sound < TALK_OBJECT_MESSAGE_SOUNDS && data_020cce84[sound] != 0) {
        SoundSys_PlaySe(data_020cce84[sound]);
    }
}
CLEAN_AS(func_020674d8, TalkObject_PlayMessageSound)

/* func_02067504: the receiver told the answer picked (its record's byte 7, slot 0x18), once
 * after a choice. */
void TalkObject_TellAnswer(TalkObject *talk)
{
    if (talk->unk_1e96 == 0) {
        return;
    }
    int answer = Block020a8248_Byte07(TalkAnswers_PickedRecord(&talk->answers));
    talk_object_tell(talk, TALK_OBJECT_SLOT_ANSWER, answer);
    talk->unk_1e96 = 0;
}
CLEAN_AS(func_02067504, TalkObject_TellAnswer)

/* func_02067540: the message's end, once: the villager's fondness for the player changed by
 * the entry's byte 5, and the receiver told the entry's byte 7 (slot 0x14). */
void TalkObject_TellMessageEnded(TalkObject *talk)
{
    if (talk->unk_1e95 == 0) {
        return;
    }
    TalkObject_ChangeFondness(talk, Block020a8248_Byte05(&talk->unk_14ac));
    talk_object_tell(talk, TALK_OBJECT_SLOT_ENDED, Block020a8248_Byte07(&talk->unk_14ac));
    talk->unk_1e95 = 0;
}
CLEAN_AS(func_02067540, TalkObject_TellMessageEnded)

/* func_02067588: the message's beginning, once: the receiver told the entry's byte 6 (slot
 * 0x10). */
void TalkObject_TellMessageBegun(TalkObject *talk)
{
    if (talk->unk_1e94 == 0) {
        return;
    }
    talk_object_tell(talk, TALK_OBJECT_SLOT_BEGUN, Block020a8248_Byte06(&talk->unk_14ac));
    talk->unk_1e94 = 0;
}
CLEAN_AS(func_02067588, TalkObject_TellMessageBegun)

/* func_020675c0: the speaker's name box freed. */
void TalkObject_FreeNameBox(TalkObject *talk)
{
    if (talk->name_box != NULL) {
        LabelBox_Free(talk->name_box);
        talk->name_box = NULL;
    }
}
CLEAN_AS(func_020675c0, TalkObject_FreeNameBox)

/* func_020675e0: the speaker's name box made in VRAM (when there is room) with the speaker's
 * name, centred and drawn. */
void TalkObject_MakeNameBox(TalkObject *talk)
{
    talk->name_box = LabelBox_NewInVram(TALK_OBJECT_NAME_TILE, TALK_OBJECT_NAME_CELLS, TALK_OBJECT_NAME_ROWS);
    if (talk->name_box == NULL) {
        return;
    }
    talk->name_box->base.screens = TALK_OBJECT_NAME_SCREENS;
    talk->name_box->base.background = TALK_OBJECT_NAME_BACKGROUND;
    TalkReceiverName *speaker = TalkReceiver_SpeakerName(talk->receiver);
    talk->name_box->base.text = talk_object_chars(speaker);
    TextDraw_Center(&talk->name_box->base);
    talk->name_box->base.color = TALK_OBJECT_NAME_COLOUR;
    TextDraw_RequestDraw(&talk->name_box->base);
}
CLEAN_AS(func_020675e0, TalkObject_MakeNameBox)

/* func_02067648: the villager talked to changes its fondness for this system's player by
 * data_020ccea0[change] (nothing for 0, without a villager, or when it does not remember the
 * player), and the link is told the new fondness.
 * REQUIRES: change indexes data_020ccea0 (0 to 32). */
void TalkObject_ChangeFondness(TalkObject *talk, int change)
{
    if (change == 0) {
        return;
    }
    u8 *villager = talk_object_villager(talk);
    u8 *records = PlayerRecords_Current();
    if (villager == NULL) {
        return;
    }
    int entry = VillagerMemory_IndexOf(villager, PlayerRecord_Player(records));
    VillagerMemory *memory = VillagerMemory_At(villager, entry);
    if (memory == NULL) {
        return;
    }
    VillagerMemoryEntry_ChangeFondness(memory, data_020ccea0[change]);
    SessionVillager_SendEntryByte6C(villager, entry, VillagerMemoryEntry_Fondness(memory));
}
CLEAN_AS(func_02067648, TalkObject_ChangeFondness)

/* func_020676ac: the talk's countdown (word 0x10) run a frame: 1 when it reached 0 now. */
int TalkObject_AutoAdvanceDue(TalkObject *talk)
{
    if (talk->unk_10 <= 0) {
        return 0;
    }
    talk->unk_10--;
    return talk->unk_10 == 0;
}
CLEAN_AS(func_020676ac, TalkObject_AutoAdvanceDue)

/* func_020676c4: the talk goes on by itself, while waiting, after `frames` frames. */
void TalkObject_SetAutoAdvance(TalkObject *talk, int frames)
{
    talk->unk_10 = frames;
}
CLEAN_AS(func_020676c4, TalkObject_SetAutoAdvance)

/* func_020676c8: the countdown off. */
void TalkObject_ClearAutoAdvance(TalkObject *talk)
{
    talk->unk_10 = 0;
}
CLEAN_AS(func_020676c8, TalkObject_ClearAutoAdvance)

/* The texts loaded from the villager talked to (or about) for a message's tags: each loader
 * clears its text and, with a villager, loads it; 1 when it did. Each is cleared again for the
 * next message (TalkFlow_NextMessage). */

/* func_020676d0: what the villager remembers of this system's player; 1 when it does. */
int TalkObject_LoadMemory(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->memory);
    if (villager == NULL) {
        return 0;
    }
    return VillagerMemory_GetText3E(villager, &talk->memory, talk_object_player()) != 0;
}
CLEAN_AS(func_020676d0, TalkObject_LoadMemory)

/* func_02067718 */
void TalkObject_ClearMemory(TalkObject *talk)
{
    TextBase_Clear(&talk->memory);
}
CLEAN_AS(func_02067718, TalkObject_ClearMemory)

/* func_02067728: the villager's praise word for this system's player. */
int TalkObject_LoadPraise(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->praise);
    if (villager == NULL) {
        return 0;
    }
    VillagerMemory_GetText2A(villager, &talk->praise, talk_object_player());
    return 1;
}
CLEAN_AS(func_02067728, TalkObject_LoadPraise)

/* func_0206776c */
void TalkObject_ClearPraise(TalkObject *talk)
{
    TextBase_Clear(&talk->praise);
}
CLEAN_AS(func_0206776c, TalkObject_ClearPraise)

/* func_0206777c: the nickname the villager gives this system's player. */
int TalkObject_LoadNickname(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->nickname);
    if (villager == NULL) {
        return 0;
    }
    VillagerMemory_NameFor(villager, &talk->nickname, talk_object_player());
    return 1;
}
CLEAN_AS(func_0206777c, TalkObject_LoadNickname)

/* func_020677c0 */
void TalkObject_ClearNickname(TalkObject *talk)
{
    TextBase_Clear(&talk->nickname);
}
CLEAN_AS(func_020677c0, TalkObject_ClearNickname)

/* func_020677d0: the villager's impression (of no record). */
int TalkObject_LoadImpression(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->impression);
    if (villager == NULL) {
        return 0;
    }
    VillagerImpression_LoadText(villager, (int) (uintptr_t) &talk->impression, NULL);
    return 1;
}
CLEAN_AS(func_020677d0, TalkObject_LoadImpression)

/* func_0206780c */
void TalkObject_ClearImpression(TalkObject *talk)
{
    TextBase_Clear(&talk->impression);
}
CLEAN_AS(func_0206780c, TalkObject_ClearImpression)

/* func_0206781c: the villager's boom; 1 when it has one. */
int TalkObject_LoadBoom(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->boom);
    if (villager == NULL) {
        return 0;
    }
    return VillagerStatus_LoadModeText(villager, &talk->boom) != 0;
}
CLEAN_AS(func_0206781c, TalkObject_LoadBoom)

/* func_0206785c */
void TalkObject_ClearBoom(TalkObject *talk)
{
    TextBase_Clear(&talk->boom);
}
CLEAN_AS(func_0206785c, TalkObject_ClearBoom)

/* func_0206786c: another resident's player name, loaded once until cleared (byte 0x1e75);
 * without one, another villager's name (then `other_colour` set), and 0 without a villager
 * either.
 * QUIRK: once tried, it answers 1 until cleared, even when nothing was loaded. */
int TalkObject_LoadOtherPlayer(TalkObject *talk)
{
    int loaded = 1;
    if (talk->unk_1e75 != 0) {
        return loaded;
    }
    u8 *records = PlayerRecords_Current();
    TextBase_Clear(&talk->other_player);
    if (PlayerRecord_OtherPlayerName(records, (struct PlayerRecordName *) (void *) &talk->other_player) == 0) {
        u8 *villager = talk_object_villager(talk);
        if (villager != NULL) {
            VillagerNames_FormatOther(villager, (char *) (void *) &talk->other_player);
            talk->other_colour = 1;
        } else {
            loaded = 0;
        }
    }
    talk->unk_1e75 = 1;
    return loaded;
}
CLEAN_AS(func_0206786c, TalkObject_LoadOtherPlayer)

/* func_020678d4: the other resident's name cleared, to load again. */
void TalkObject_ClearOtherPlayer(TalkObject *talk)
{
    talk->unk_1e75 = 0;
    talk->other_colour = 0;
    TextBase_Clear(&talk->other_player);
}
CLEAN_AS(func_020678d4, TalkObject_ClearOtherPlayer)

/* func_020678f8: another villager's name, picked once until cleared (byte 0x1e74); 0 without
 * a villager talked to.
 * QUIRK: once tried, it answers 1 until cleared, even when nothing was loaded. */
int TalkObject_LoadRandomNpc(TalkObject *talk)
{
    int loaded = 1;
    if (talk->unk_1e74 != 0) {
        return loaded;
    }
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->random_npc);
    if (villager != NULL) {
        VillagerNames_FormatOther(villager, (char *) (void *) &talk->random_npc);
    } else {
        loaded = 0;
    }
    talk->unk_1e74 = 1;
    return loaded;
}
CLEAN_AS(func_020678f8, TalkObject_LoadRandomNpc)

/* func_02067948: the other villager's name cleared, to pick again. */
void TalkObject_ClearRandomNpc(TalkObject *talk)
{
    talk->unk_1e74 = 0;
    TextBase_Clear(&talk->random_npc);
}
CLEAN_AS(func_02067948, TalkObject_ClearRandomNpc)

/* func_02067964: a villager the one talked to is on bad terms with. */
int TalkObject_LoadDislikedNpc(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->disliked_npc);
    if (villager == NULL) {
        return 0;
    }
    VillagerNames_FormatWorstMatch(villager, (char *) (void *) &talk->disliked_npc);
    return 1;
}
CLEAN_AS(func_02067964, TalkObject_LoadDislikedNpc)

/* func_020679a0 */
void TalkObject_ClearDislikedNpc(TalkObject *talk)
{
    TextBase_Clear(&talk->disliked_npc);
}
CLEAN_AS(func_020679a0, TalkObject_ClearDislikedNpc)

/* func_020679b0: a villager the one talked to is on good terms with. */
int TalkObject_LoadLikedNpc(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->liked_npc);
    if (villager == NULL) {
        return 0;
    }
    VillagerNames_FormatBestMatch(villager, (char *) (void *) &talk->liked_npc);
    return 1;
}
CLEAN_AS(func_020679b0, TalkObject_LoadLikedNpc)

/* func_020679ec */
void TalkObject_ClearLikedNpc(TalkObject *talk)
{
    TextBase_Clear(&talk->liked_npc);
}
CLEAN_AS(func_020679ec, TalkObject_ClearLikedNpc)

/* func_020679fc: this system's player's name; always 1. */
int TalkObject_LoadPlayerName(TalkObject *talk)
{
    u8 *records = PlayerRecords_Current();
    TextBase_Clear(&talk->unk_1cac);
    PlayerId_NameToText(PlayerRecord_Player(records), (TextBase *) (void *) &talk->unk_1cac);
    return 1;
}
CLEAN_AS(func_020679fc, TalkObject_LoadPlayerName)

/* func_02067a2c */
void TalkObject_ClearPlayerName(TalkObject *talk)
{
    TextBase_Clear(&talk->unk_1cac);
}
CLEAN_AS(func_02067a2c, TalkObject_ClearPlayerName)

/* func_02067a3c: the town's name; always 1. */
int TalkObject_LoadTownName(TalkObject *talk)
{
    TextBase_Clear(&talk->town_name);
    TownName_ToText((TownName *) (void *) &data_021dc7a8.town, (TextBase *) (void *) &talk->town_name);
    return 1;
}
CLEAN_AS(func_02067a3c, TalkObject_LoadTownName)

/* func_02067a64 */
void TalkObject_ClearTownName(TalkObject *talk)
{
    TextBase_Clear(&talk->town_name);
}
CLEAN_AS(func_02067a64, TalkObject_ClearTownName)

/* func_02067a74: the villager's catchphrase (with VillagerCatchphrase_ToLabel's third argument
 * 1). */
int TalkObject_LoadCatchphrase(TalkObject *talk)
{
    u8 *villager = talk_object_villager(talk);
    TextBase_Clear(&talk->unk_1c70);
    if (villager == NULL) {
        return 0;
    }
    VillagerCatchphrase_ToLabel(villager, &talk->unk_1c70, 1);
    return 1;
}
CLEAN_AS(func_02067a74, TalkObject_LoadCatchphrase)

/* func_02067ab0 */
void TalkObject_ClearCatchphrase(TalkObject *talk)
{
    TextBase_Clear(&talk->unk_1c70);
}
CLEAN_AS(func_02067ab0, TalkObject_ClearCatchphrase)

/* func_02067ac0: the four values a message's tags put in cleared, of the cleared kind. */
void TalkObject_ClearValues(TalkObject *talk)
{
    for (int i = 0; i < TALK_OBJECT_VALUES; i++) {
        MessagePart_Clear(&talk->values[i]);
        talk->value_kinds[i] = TALK_OBJECT_VALUE_CLEARED;
    }
}
CLEAN_AS(func_02067ac0, TalkObject_ClearValues)

/* func_02067af8: the eleven message parts cleared. */
void TalkObject_ClearParts(TalkObject *talk)
{
    for (int i = 0; i < TALK_OBJECT_PARTS; i++) {
        MessagePart_Clear(&talk->parts[i]);
    }
}
CLEAN_AS(func_02067af8, TalkObject_ClearParts)

/* func_02067c20: the date and time the talk begins noted: the year, the day and month, the
 * minute and hour, the weekday, the second and the part of the day. */
void TalkObject_NoteTime(TalkObject *talk)
{
    talk->year = Clock_Year();
    Clock_GetDayMonth(&talk->day);
    Calendar_Now((Time *) (void *) &talk->minute);
    talk->weekday = Calendar_TodayWeekday();
    talk->second = (u32) Clock_Second();
    talk->part_of_day = Calendar_PartOfDay();
}
CLEAN_AS(func_02067c20, TalkObject_NoteTime)
