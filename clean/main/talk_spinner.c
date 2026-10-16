/* The spinning sprite of the talks (talk_spinner.h). */
#include "talk_spinner.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "display_shadow.h" /* DisplayShadow_EnableMainWindows, ... */
#include "oam_buffer.h"     /* OamBuffer_DrawCell */
#include "sound.h"          /* SoundSys_StartOnHandle38, SoundSys_StopSound */

#include "ov004/member_pointer.h" /* MemberPointer */

static_assert(offsetof(TalkSpinner, state) == 0x0c && offsetof(TalkSpinner, angle) == 0x10, "TalkSpinner");
static_assert(offsetof(TalkSpinner, requested) == 0x13 && offsetof(TalkSpinner, sound) == 0x1c, "TalkSpinner");
static_assert(offsetof(TalkSpinner, sound_on) == 0x20 && sizeof(TalkSpinner) == 0x24, "TalkSpinner");

/* The spinner's vtable. */
extern const u32 data_020e23e4[];

/* Its sounds, and the animations its two cells are the first frames of (0 and 2). */
extern const u16 data_020d0bac[];
extern const CellAnimData data_020d71cc[];
#define TALK_SPINNER_ANIM_WHEEL 0
#define TALK_SPINNER_ANIM_HUB 2

/* What the spinner's angle grows by each frame: one fifteenth of a turn. */
#define TALK_SPINNER_ANGLE_STEP 0x1111

/* Its sound stopped at once (no fade). */
#define TALK_SPINNER_SOUND_FADE 1

/* The main screen's OBJ window, with the OBJs inside it. */
#define TALK_SPINNER_PLANE_OBJ 0x10
#define TALK_SPINNER_WINDOW_OBJ 0x04

#define TALK_SPINNER_FX_ONE 0x1000
#define TALK_SPINNER_OBJ_MODE_WINDOW 2

/* The spinner's vtable slots: draw and update. */
#define TALK_SPINNER_SLOT_DRAW 2
#define TALK_SPINNER_SLOT_UPDATE 3

/* func_0208fb24: the sound stopped, if it was started. */
void TalkSpinner_StopSound(TalkSpinner *spinner)
{
    if (spinner->sound_on != 0) {
        spinner->sound_on = 0;
        SoundSys_StopSound(data_020d0bac[spinner->sound], TALK_SPINNER_SOUND_FADE);
    }
}
CLEAN_AS(func_0208fb24, TalkSpinner_StopSound)

/* func_0208fb54: the sound started on handle 0x38. */
void TalkSpinner_StartSound(TalkSpinner *spinner)
{
    u16 number = data_020d0bac[(int) spinner->sound];
    spinner->sound_on = 1;
    SoundSys_StartOnHandle38(number);
}
CLEAN_AS(func_0208fb54, TalkSpinner_StartSound)

/* func_0208fb70 (state 1): once the start is withdrawn, the sound stopped, the OBJ window
 * disabled when it was used, and idle again. */
void TalkSpinner_StepSpinning(TalkSpinner *spinner)
{
    if (spinner->requested != 0) {
        return;
    }
    TalkSpinner_StopSound(spinner);
    if (spinner->window != 0) {
        DisplayShadow_DisableMainWindows(TALK_SPINNER_WINDOW_OBJ);
    }
    TalkSpinner_SetIdle(spinner);
}
CLEAN_AS(func_0208fb70, TalkSpinner_StepSpinning)

/* func_0208fb98: spinning, with its sound; when `window` is set the main screen's OBJ window
 * enabled with the OBJs inside it. */
void TalkSpinner_Begin(TalkSpinner *spinner)
{
    spinner->state = TALK_SPINNER_SPINNING;
    TalkSpinner_StartSound(spinner);
    if (spinner->window != 0) {
        DisplayShadow_SetMainObjWindowPlanes(TALK_SPINNER_PLANE_OBJ);
        DisplayShadow_EnableMainWindows(TALK_SPINNER_WINDOW_OBJ);
    }
}
CLEAN_AS(func_0208fb98, TalkSpinner_Begin)

/* func_0208fbbc (state 0): once a start is requested, spinning. */
void TalkSpinner_StepIdle(TalkSpinner *spinner)
{
    if (spinner->requested != 0) {
        TalkSpinner_Begin(spinner);
    }
}
CLEAN_AS(func_0208fbbc, TalkSpinner_StepIdle)

/* func_0208fbd0 */
void TalkSpinner_SetIdle(TalkSpinner *spinner)
{
    spinner->state = TALK_SPINNER_IDLE;
}
CLEAN_AS(func_0208fbd0, TalkSpinner_SetIdle)

/* func_0208fbd8 */
void TalkSpinner_SetOffset(TalkSpinner *spinner, int x, int y)
{
    spinner->offset_x = x;
    spinner->offset_y = y;
}
CLEAN_AS(func_0208fbd8, TalkSpinner_SetOffset)

/* func_0208fbe0: the spinner's vtable slot 2 (its draw) called; its result passed on. */
int TalkSpinner_CallDraw(TalkSpinner *spinner)
{
    return ((int (*)(TalkSpinner *))(uintptr_t) spinner->base.vtable[TALK_SPINNER_SLOT_DRAW])(spinner);
}
CLEAN_AS(func_0208fbe0, TalkSpinner_CallDraw)

/* func_0208fbf0: the spinner's vtable slot 3 (its update) called; its result passed on. */
int TalkSpinner_CallUpdate(TalkSpinner *spinner)
{
    return ((int (*)(TalkSpinner *))(uintptr_t) spinner->base.vtable[TALK_SPINNER_SLOT_UPDATE])(spinner);
}
CLEAN_AS(func_0208fbf0, TalkSpinner_CallUpdate)

/* func_0208fc00: called by the talk's destructor before the spinner's; does nothing. */
void TalkSpinner_Finish(TalkSpinner *spinner)
{
    (void) spinner;
}
CLEAN_AS(func_0208fc00, TalkSpinner_Finish)

/* func_0208fc04: called by the talk's constructor: idle. */
void TalkSpinner_Init(TalkSpinner *spinner)
{
    TalkSpinner_SetIdle(spinner);
}
CLEAN_AS(func_0208fc04, TalkSpinner_Init)

/* The member function table of TalkSpinner_Update (a function-local static of the game): its
 * guard, the table, and the constants it is filled from. */
extern u32 data_021d3624;
extern MemberPointer data_021d3634[2];
extern const MemberPointer data_020e23b4, data_020e23d4;

/* func_0208fc0c (vtable slot 3): the angle turned on (whatever the state), then the state's
 * step, through the game's table (filled on the first call).
 * REQUIRES: the state is 0 or 1 (the ROM indexes its table unchecked). */
void TalkSpinner_Update(TalkSpinner *spinner)
{
    static const MemberPointer *const constants[2] = {
        &data_020e23b4, /* TalkSpinner_StepIdle */
        &data_020e23d4, /* TalkSpinner_StepSpinning */
    };
    MemberTable_InitOnce(&data_021d3624, data_021d3634, constants, 2);
    spinner->angle = (u16) (spinner->angle + TALK_SPINNER_ANGLE_STEP);
    MemberPointer_CallVoid(&data_021d3634[spinner->state], spinner);
}
CLEAN_AS(func_0208fc0c, TalkSpinner_Update)

/* func_0208fc7c (vtable slot 2): while spinning, the two cells drawn on the main screen at the
 * place plus the offset, the first turned by the angle; when `window` is set, both again as
 * OBJ window. */
void TalkSpinner_Draw(TalkSpinner *spinner)
{
    if (spinner->state == TALK_SPINNER_IDLE) {
        return;
    }
    int x = spinner->offset_x + ScreenSprite_X(&spinner->base);
    int y = spinner->offset_y + ScreenSprite_Y(&spinner->base);
    const OamEntry *wheel = data_020d71cc[TALK_SPINNER_ANIM_WHEEL].frames[0].cell;
    const OamEntry *hub = data_020d71cc[TALK_SPINNER_ANIM_HUB].frames[0].cell;
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, wheel, x, y, -1, -1, TALK_SPINNER_FX_ONE, TALK_SPINNER_FX_ONE, spinner->angle,
                       -1, 0, 0);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, hub, x, y, -1, -1, TALK_SPINNER_FX_ONE, TALK_SPINNER_FX_ONE, 0, -1, 0, 0);
    if (spinner->window != 0) {
        OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, wheel, x, y, -1, -1, TALK_SPINNER_FX_ONE, TALK_SPINNER_FX_ONE,
                           spinner->angle, TALK_SPINNER_OBJ_MODE_WINDOW, 0, 0);
        OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, hub, x, y, -1, -1, TALK_SPINNER_FX_ONE, TALK_SPINNER_FX_ONE, 0,
                           TALK_SPINNER_OBJ_MODE_WINDOW, 0, 0);
    }
}
CLEAN_AS(func_0208fc7c, TalkSpinner_Draw)

static void talk_spinner_destruct(TalkSpinner *spinner)
{
    spinner->base.vtable = data_020e23e4;
    TalkSpinner_StopSound(spinner);
    ScreenSprite_DestructBase(&spinner->base);
}

/* func_0208fd44 (vtable slot 1): its sound stopped, destructed and freed. */
TalkSpinner *TalkSpinner_Delete(TalkSpinner *spinner)
{
    talk_spinner_destruct(spinner);
    Heap_OperatorDeleteB(spinner);
    return spinner;
}
CLEAN_AS(func_0208fd44, TalkSpinner_Delete)

/* func_0208fd68 (vtable slot 0): the destructor: its sound stopped. */
TalkSpinner *TalkSpinner_Destruct(TalkSpinner *spinner)
{
    talk_spinner_destruct(spinner);
    return spinner;
}
CLEAN_AS(func_0208fd68, TalkSpinner_Destruct)

/* func_0208fd88: the constructor: idle, nothing requested, no sound, no offset. */
TalkSpinner *TalkSpinner_Construct(TalkSpinner *spinner)
{
    ScreenSprite_Construct(&spinner->base);
    spinner->base.vtable = data_020e23e4;
    spinner->state = TALK_SPINNER_IDLE;
    spinner->angle = 0;
    spinner->window = 0;
    spinner->requested = 0;
    spinner->offset_x = 0;
    spinner->offset_y = 0;
    spinner->sound = 0;
    spinner->sound_on = 0;
    return spinner;
}
CLEAN_AS(func_0208fd88, TalkSpinner_Construct)

/* func_0208fdb8: the start withdrawn (the spinner stops at its next update). */
void TalkSpinner_Stop(TalkSpinner *spinner)
{
    spinner->requested = 0;
}
CLEAN_AS(func_0208fdb8, TalkSpinner_Stop)

/* func_0208fdc0: a start requested, with sound `sound` of data_020d0bac (it starts spinning at
 * its next update). */
void TalkSpinner_Start(TalkSpinner *spinner, int sound)
{
    spinner->requested = 1;
    spinner->sound = (u32) sound;
}
CLEAN_AS(func_0208fdc0, TalkSpinner_Start)
