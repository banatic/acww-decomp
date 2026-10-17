/* The talk scene of overlay 55's exchange character (xct_exchange_talk.h): its class, its lines
 * and the steps it runs while the exchange goes on. */
#include "xct_exchange_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "clean.h"
#include "main/library_overlay.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/scene_base.h"
#include "main/session_link.h"
#include "main/sound.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "xct_exchange.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(XctExchangeTalk, owner) == 0xb0 && offsetof(XctExchangeTalk, step) == 0xb4, "XctExchangeTalk");
static_assert(sizeof(XctExchangeTalk) == 0xb8, "XctExchangeTalk");
static_assert(sizeof(XctExchangeTalkStep) == 12, "a step's function");
static_assert(sizeof(XctExchangeTalkStart) == 8, "what a talk starts with");

/* The vtable of its class. */
extern const u8 data_ov055_02260f44[];
/* Its message file: a pointer to "sp_etc_sequence1". */
extern const char *const data_ov055_02260e60;
/* Its steps (the members filled at start-up by __sinit_ov055_02260db4). */
extern XctExchangeTalkStep data_ov055_02260f0c[XCT_EXCHANGE_TALK_STEPS];
/* The buttons, and the pen: it came down this frame when both bytes are set. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The vtable slot of the scene that resets it (SceneBase_Reset). */
#define XCT_EXCHANGE_TALK_SLOT_RESET 0x08

/* Its lines (the receiver's message). */
#define XCT_EXCHANGE_TALK_LINE_SAVE_FAILED 0x36
#define XCT_EXCHANGE_TALK_LINE_FIRST 0x38
#define XCT_EXCHANGE_TALK_LINE_START 0x39
#define XCT_EXCHANGE_TALK_LINE_STOP 0x3a
#define XCT_EXCHANGE_TALK_LINE_RESTORE 0x3b
#define XCT_EXCHANGE_TALK_LINE_RECEIVED 0x3c

/* The answer to line 0x3a that ends the session's exchange. */
#define XCT_EXCHANGE_TALK_ANSWER_END 1

/* The sound played when the lid is open again after the exchange. */
#define XCT_EXCHANGE_TALK_SOUND 0x69

/* The A button (PadState.pressed). */
#define XCT_EXCHANGE_TALK_BUTTON_A 1

/* The ARM7's word of the buttons it reads (X, Y, ...); bit 15 is set while the lid is closed. */
#define XCT_EXCHANGE_TALK_BUTTONS (*(const volatile u16 *) 0x027fffa8)
#define XCT_EXCHANGE_TALK_LID_CLOSED 0x8000u

static int xct_exchange_talk_lid_closed(void)
{
    /* HW: the ARM7 keeps this word up to date. */
    return (XCT_EXCHANGE_TALK_BUTTONS & XCT_EXCHANGE_TALK_LID_CLOSED) != 0;
}

static TalkObject *xct_exchange_talk_object(XctExchangeTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* The line shown. */
static u8 xct_exchange_talk_shown(const XctExchangeTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The talk shows `line` of "sp_etc_sequence1". */
static void xct_exchange_talk_say(XctExchangeTalk *talk, int line)
{
    u8 message = (u8) line;
    TalkObject_SetMessage(xct_exchange_talk_object(talk), &message, data_ov055_02260e60);
}

/* ---- The class */

/* func_ov055_02260a20 (vtable slot 0x04): the destructor of the scene class it derives from,
 * then the scene freed. */
XctExchangeTalk *XctExchangeTalk_DestructDelete(XctExchangeTalk *talk)
{
    talk->base.vtable = data_ov055_02260f44;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov055_02260a20, XctExchangeTalk_DestructDelete)

/* func_ov055_02260a40 (vtable slot 0x00): the destructor of the scene class it derives from. */
XctExchangeTalk *XctExchangeTalk_Destruct(XctExchangeTalk *talk)
{
    talk->base.vtable = data_ov055_02260f44;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov055_02260a40, XctExchangeTalk_Destruct)

/* func_ov055_02260a58: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
XctExchangeTalk *XctExchangeTalk_Construct(XctExchangeTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->base.vtable = data_ov055_02260f44;
    return talk;
}
CLEAN_AS(func_ov055_02260a58, XctExchangeTalk_Construct)

/* func_ov055_02260a04: the scene reset (its vtable slot 0x08) and given its owner. */
void XctExchangeTalk_Begin(XctExchangeTalk *talk, XctExchange *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + XCT_EXCHANGE_TALK_SLOT_RESET);
    ((void (*)(XctExchangeTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov055_02260a04, XctExchangeTalk_Begin)

/* func_ov055_02260870 */
void XctExchangeTalk_SetStep(XctExchangeTalk *talk, u32 step)
{
    talk->step = step;
}
CLEAN_AS(func_ov055_02260870, XctExchangeTalk_SetStep)

/* func_ov055_022608c8 (vtable slot 0x80, before each step of the scene): its step's function,
 * when the step runs before the scene's steps and has one.
 * REQUIRES: the step is 0 to 3 (the table is not bounded). */
void XctExchangeTalk_RunStep(XctExchangeTalk *talk)
{
    const XctExchangeTalkStep *step = &data_ov055_02260f0c[talk->step];
    if (step->before_step == 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
}
CLEAN_AS(func_ov055_022608c8, XctExchangeTalk_RunStep)

/* func_ov055_02260878 (vtable slot 0x84, a command of the scene ended): its step's function,
 * when the step is not one run before the scene's steps and has one; then step 0. Every step
 * with a function runs before the scene's steps, so this does nothing.
 * REQUIRES: the step is 0 to 3 (the table is not bounded). */
void XctExchangeTalk_OnCommandEnded(XctExchangeTalk *talk)
{
    const XctExchangeTalkStep *step = &data_ov055_02260f0c[talk->step];
    if (step->before_step != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
    XctExchangeTalk_SetStep(talk, XCT_EXCHANGE_TALK_STEP_NONE);
}
CLEAN_AS(func_ov055_02260878, XctExchangeTalk_OnCommandEnded)

/* ---- Its lines */

/* func_ov055_022609f4 (vtable slot 0x78): every talk starts with line 0x38; the line. */
int XctExchangeTalk_Line(XctExchangeTalk *talk, XctExchangeTalkStart *out)
{
    (void) talk;
    out->name = data_ov055_02260e60;
    out->message = XCT_EXCHANGE_TALK_LINE_FIRST;
    return XCT_EXCHANGE_TALK_LINE_FIRST;
}
CLEAN_AS(func_ov055_022609f4, XctExchangeTalk_Line)

/* func_ov055_0226090c (vtable slot 0x18, the player answered): the second choice to line 0x3a
 * ends the session's exchange. */
void XctExchangeTalk_OnAnswer(XctExchangeTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked(TalkObject_Answers(xct_exchange_talk_object(talk)));
    if (xct_exchange_talk_shown(talk) == XCT_EXCHANGE_TALK_LINE_STOP && answer == XCT_EXCHANGE_TALK_ANSWER_END) {
        Session_EndExchange();
    }
}
CLEAN_AS(func_ov055_0226090c, XctExchangeTalk_OnAnswer)

/* func_ov055_02260930 (vtable slot 0x14, a line ended):
 * - after line 0x39, unless the library runs already: when a save of the exchange block failed,
 *   line 0x36 and nothing more; else the session's exchange starts, the received packet is
 *   cleared and the library set up to send the owner's packet and receive into the other,
 *   and started. Then the library is started, the talk held and step 1 taken;
 * - after line 0x3c, what came is put in place; after line 0x3b, the town's own block.
 * QUIRK: a fresh exchange is started twice (Exchange_Start right after Exchange_Init, then
 * again with the one that follows every case). */
void XctExchangeTalk_OnLineEnd(XctExchangeTalk *talk)
{
    TalkObject *object = xct_exchange_talk_object(talk);
    XctExchange *owner;

    switch (xct_exchange_talk_shown(talk)) {
        case XCT_EXCHANGE_TALK_LINE_START:
            LibraryOverlay_Require67();
            if (Exchange_IsActive() == 0) {
                if (talk->owner->save_failed != 0) {
                    xct_exchange_talk_say(talk, XCT_EXCHANGE_TALK_LINE_SAVE_FAILED);
                    break;
                }
                Session_StartExchange();
                MI_CpuFill8(&talk->owner->received, 0, sizeof(XctExchangePacket));
                owner = talk->owner;
                LibraryOverlay_Require67();
                Exchange_Init((u8 *) &owner->send, (u8 *) &owner->received, sizeof(XctExchangePacket));
                LibraryOverlay_Require67();
                Exchange_Start();
            }
            LibraryOverlay_Require67();
            Exchange_Start();
            TalkObject_Hold(object);
            XctExchangeTalk_SetStep(talk, XCT_EXCHANGE_TALK_STEP_EXCHANGING);
            break;
        case XCT_EXCHANGE_TALK_LINE_RECEIVED:
            XctExchange_TakeReceived(talk->owner);
            break;
        case XCT_EXCHANGE_TALK_LINE_RESTORE:
            XctExchange_RestoreBlock(talk->owner);
            break;
    }
}
CLEAN_AS(func_ov055_02260930, XctExchangeTalk_OnLineEnd)

/* ---- Its steps */

/* func_ov055_022606f4 (step 3, stopping): nothing while the lid is closed. When the exchange
 * was done after all, sound 0x69, the session's exchange ends and line 0x3c; else while the
 * library does not run, it is told to stop again and the step stays. Then the talk is released
 * and step 0 taken. */
void XctExchangeTalk_StepStopping(XctExchangeTalk *talk)
{
    TalkObject *object = xct_exchange_talk_object(talk);

    if (xct_exchange_talk_lid_closed()) {
        return;
    }
    LibraryOverlay_Require67();
    if (Exchange_IsDone() != 0) {
        SoundSys_PlaySe(XCT_EXCHANGE_TALK_SOUND);
        Session_EndExchange();
        xct_exchange_talk_say(talk, XCT_EXCHANGE_TALK_LINE_RECEIVED);
    } else {
        LibraryOverlay_Require67();
        if (Exchange_IsActive() != 1) {
            LibraryOverlay_Require67();
            Exchange_Call0226883c();
            return;
        }
    }
    TalkObject_Release(object);
    XctExchangeTalk_SetStep(talk, XCT_EXCHANGE_TALK_STEP_NONE);
}
CLEAN_AS(func_ov055_022606f4, XctExchangeTalk_StepStopping)

/* func_ov055_0226076c (step 2, done): once the lid is open, sound 0x69, the talk released and
 * step 0 taken. */
void XctExchangeTalk_StepDone(XctExchangeTalk *talk)
{
    if (xct_exchange_talk_lid_closed()) {
        return;
    }
    SoundSys_PlaySe(XCT_EXCHANGE_TALK_SOUND);
    TalkObject_Release(xct_exchange_talk_object(talk));
    XctExchangeTalk_SetStep(talk, XCT_EXCHANGE_TALK_STEP_NONE);
}
CLEAN_AS(func_ov055_0226076c, XctExchangeTalk_StepDone)

/* func_ov055_022607a0 (step 1, exchanging): the lid's state noted in the owner. When the
 * exchange is done, the session's exchange ends, line 0x3c and step 2; else when the player
 * presses A, taps the screen or has just opened the lid, the library is told to stop, line 0x3a
 * and step 3. */
void XctExchangeTalk_StepExchanging(XctExchangeTalk *talk)
{
    int closed = xct_exchange_talk_lid_closed();
    XctExchange *owner = talk->owner;
    int opened = owner->lid_closed == 1 && !closed;
    owner->lid_closed = (u8) closed;

    LibraryOverlay_Require67();
    if (Exchange_IsDone() != 0) {
        Session_EndExchange();
        xct_exchange_talk_say(talk, XCT_EXCHANGE_TALK_LINE_RECEIVED);
        XctExchangeTalk_SetStep(talk, XCT_EXCHANGE_TALK_STEP_DONE);
        return;
    }
    if ((data_021fbe40.pressed & XCT_EXCHANGE_TALK_BUTTON_A) == 0) {
        int tapped = data_021fbdd8 != 0 && data_021fbddc != 0;
        if (!tapped && !opened) {
            return;
        }
    }
    LibraryOverlay_Require67();
    Exchange_Call0226883c();
    xct_exchange_talk_say(talk, XCT_EXCHANGE_TALK_LINE_STOP);
    XctExchangeTalk_SetStep(talk, XCT_EXCHANGE_TALK_STEP_STOPPING);
}
CLEAN_AS(func_ov055_022607a0, XctExchangeTalk_StepExchanging)
