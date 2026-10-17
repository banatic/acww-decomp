/* The town pelican's talk scene (town_pelican_talk.h). */
#include "town_pelican_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_command.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/scene_standard_anims.h"
#include "main/speaker_anim.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(sizeof(TownPelicanTalkStep) == 12, "a sequence's function");
static_assert(sizeof(TownPelicanLine) == 8, "a line");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");
static_assert(offsetof(TalkObject, state) == 4, "the talk object's state");

/* The talk scene's vtable. */
extern const u8 data_ov075_0227996c[];
/* The message file's name, "sp_npc_mpelican". */
extern const char data_ov075_02279aa8[];
/* The sequences' functions (filled at start-up by __sinit_ov075_02279724). */
extern TownPelicanTalkStep data_ov075_02279930[TOWN_PELICAN_TALK_SEQUENCES];
/* The word his motion requests carry. */
extern u16 data_020c80f8;

/* The current player's flag (PlayerRecord_TestFlag) of having met him, and the daily bit
 * (TalkChecks_TestSetDailyBit) set when he is met. */
#define TPEL_TALK_FLAG_MET 6
#define TPEL_TALK_DAILY_MET 0x12

/* The talk object's state once the line is shown to its end. */
#define TPEL_TALK_LINE_SHOWN 5

/* The animation he plays, and the motion of a turn in place (scene_motion_kinds.h). */
#define TPEL_TALK_ANIMATION 0xd5
#define TPEL_TALK_MOTION_TURN 3

/* The lines he says once met again: one of 12 from 0. */
#define TPEL_TALK_LINES_AGAIN 12

/* His parts used here (main's scene_object.h). */
#define TPEL_TALK_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TPEL_TALK_ANIM 0x334           /* SpeakerAnim */
#define TPEL_TALK_MOTION 0x564         /* SceneMotion */

/* The field actor of this console's player. */
#define TPEL_TALK_PLAYER_ACTOR 4

/* The vtable slot its talks call first. */
#define TPEL_TALK_SLOT_08 0x08

static u8 tpel_talk_line_shown(const TownPelicanTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *tpel_talk_object(TownPelicanTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

static SceneMotion *tpel_talk_owner_motion(TownPelicanTalk *talk)
{
    return (SceneMotion *) (void *) (talk->owner->base + TPEL_TALK_MOTION);
}

/* func_ov075_02278aec (slot 0x18, the player's answer): the answer picked is asked for, and
 * nothing done with it. */
void TownPelicanTalk_OnAnswer(TownPelicanTalk *talk)
{
    TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
}
CLEAN_AS(func_ov075_02278aec, TownPelicanTalk_OnAnswer)

/* func_ov075_02278b00 (slot 0x14, a line ended): the current player's record is asked for (and
 * not used); at the end of line 0x1a the talk waits in talk mode 0 and sequence 1 begins. */
void TownPelicanTalk_OnLineEnded(TownPelicanTalk *talk)
{
    PlayerRecords_Current();
    if (tpel_talk_line_shown(talk) == TOWN_PELICAN_LINE_FIRST) {
        SceneCommand_RequestTalkMode((SceneCommandScene *) (void *) talk, 0);
        TownPelicanTalk_SetSequence(talk, TOWN_PELICAN_TALK_SEQUENCE_WAKE);
    }
}
CLEAN_AS(func_ov075_02278b00, TownPelicanTalk_OnLineEnded)

/* func_ov075_02278b24 (slot 0x78, the line the talk starts with), of "sp_npc_mpelican": 0x1a,
 * or, when he was met and the current player has flag 6, one of 0x0c to 0x0f at random. */
void TownPelicanTalk_Line(TownPelicanTalk *talk, TownPelicanLine *out)
{
    out->message = TOWN_PELICAN_LINE_FIRST;
    if (talk->owner->met != 0 && PlayerRecord_TestFlag(PlayerRecords_Current(), TPEL_TALK_FLAG_MET)) {
        out->message = (u8) (MainRandom_Below(4) + TOWN_PELICAN_LINE_AGAIN);
    }
    out->text = (u32) (uintptr_t) data_ov075_02279aa8;
}
CLEAN_AS(func_ov075_02278b24, TownPelicanTalk_Line)

/* func_ov075_02278b64: its talk scene told through its vtable slot 0x08 and given its owner. */
void TownPelicanTalk_Begin(TownPelicanTalk *talk, int owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + TPEL_TALK_SLOT_08);
    ((void (*)(TownPelicanTalk *))(uintptr_t) code)(talk);
    talk->owner = (TownPelican *) (uintptr_t) (u32) owner;
}
CLEAN_AS(func_ov075_02278b64, TownPelicanTalk_Begin)

/* func_ov075_02278b80 (slot 0x04): its destructor, then the scene freed. */
void *TownPelicanTalk_Delete(void *talk)
{
    *(const u8 **) talk = data_ov075_0227996c;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov075_02278b80, TownPelicanTalk_Delete)

/* func_ov075_02278ba0 (slot 0x00): the scene class 0x020d9ff8's destructor. */
TownPelicanTalk *TownPelicanTalk_Destroy(TownPelicanTalk *talk)
{
    talk->base.vtable = data_ov075_0227996c;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov075_02278ba0, TownPelicanTalk_Destroy)

/* func_ov075_02278bb8: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
void *TownPelicanTalk_Construct(void *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) talk = data_ov075_0227996c;
    return talk;
}
CLEAN_AS(func_ov075_02278bb8, TownPelicanTalk_Construct)

/* func_ov075_02278bd0 (sequence 1, before each step), by its step:
 * - 0: once the talk's line is shown to its end, his animation 0xd5 (priority 2, played once)
 *   and his standard animations' first set to 0; step 1;
 * - 1: once he plays animation 0xd5 and his motion is done, he turns in place to the player
 *   (priority 2); step 2;
 * - 2: once the turn is done: he counts as met, the next line is asked for, the daily bit 0x12
 *   set; the line is 0x10 when the current player has not met him (the player's flag 6 then
 *   set), else one of 0 to 11 at random; the sequence ends. */
void TownPelicanTalk_Wake(TownPelicanTalk *talk)
{
    TownPelican *owner = talk->owner;
    SceneMotion *motion = tpel_talk_owner_motion(talk);

    switch (talk->step) {
        case TOWN_PELICAN_TALK_STEP_ANIMATE:
            if (tpel_talk_object(talk)->state == TPEL_TALK_LINE_SHOWN) {
                SceneMotion_RequestAnimation(motion, 2, TPEL_TALK_ANIMATION, 1, data_020c80f8, 0);
                SceneStandardAnims_SetFirst((SceneStandardAnims *) (void *) (owner->base + TPEL_TALK_STANDARD_ANIMS), 0);
                talk->step++;
            }
            break;
        case TOWN_PELICAN_TALK_STEP_TURN:
            if (SpeakerAnim_Number((SpeakerAnim *) (void *) (owner->base + TPEL_TALK_ANIM), 0) == TPEL_TALK_ANIMATION &&
                SceneMotion_IsDone(motion)) {
                int angle = (int) (uintptr_t) SceneObject_YawToActor(owner->base, TPEL_TALK_PLAYER_ACTOR);
                SceneMotion_Request(motion, TPEL_TALK_MOTION_TURN, 2, 0, 0, 0, (s16) angle, 0, 0, data_020c80f8, 0);
                talk->step++;
            }
            break;
        case TOWN_PELICAN_TALK_STEP_MEET:
            if (SceneMotion_Kind(motion) == TPEL_TALK_MOTION_TURN && SceneMotion_IsDone(motion)) {
                u8 *record = PlayerRecords_Current();
                u8 message;
                owner->met = 1;
                SceneCommand_RequestNextLine((SceneCommandScene *) (void *) talk);
                if (PlayerRecord_TestFlag(record, TPEL_TALK_FLAG_MET) == 0) {
                    PlayerRecord_SetFlag(record, TPEL_TALK_FLAG_MET);
                    TalkChecks_TestSetDailyBit(TPEL_TALK_DAILY_MET, 1);
                    message = TOWN_PELICAN_LINE_MET;
                } else {
                    TalkChecks_TestSetDailyBit(TPEL_TALK_DAILY_MET, 1);
                    message = (u8) MainRandom_Below(TPEL_TALK_LINES_AGAIN);
                }
                TalkObject_SetMessage(tpel_talk_object(talk), &message, data_ov075_02279aa8);
                TownPelicanTalk_SetSequence(talk, TOWN_PELICAN_TALK_SEQUENCE_NONE);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov075_02278bd0, TownPelicanTalk_Wake)

/* func_ov075_02278d44: its sequence set, from its first step. */
void TownPelicanTalk_SetSequence(TownPelicanTalk *talk, int sequence)
{
    talk->sequence = (u32) sequence;
    talk->step = 0;
}
CLEAN_AS(func_ov075_02278d44, TownPelicanTalk_SetSequence)

/* func_ov075_02278d54 (slot 0x84, a command of the scene ended): a sequence not run each step
 * and with a function runs, and the sequence goes back to 0.
 * REQUIRES: the sequence is 0 or 1. */
void TownPelicanTalk_RunCommandSequence(TownPelicanTalk *talk)
{
    const TownPelicanTalkStep *step = &data_ov075_02279930[talk->sequence];
    if (step->each_step != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
    TownPelicanTalk_SetSequence(talk, TOWN_PELICAN_TALK_SEQUENCE_NONE);
}
CLEAN_AS(func_ov075_02278d54, TownPelicanTalk_RunCommandSequence)

/* func_ov075_02278da4 (slot 0x80, before each step of the scene): a sequence run each step
 * runs, when it has a function.
 * REQUIRES: the sequence is 0 or 1. */
void TownPelicanTalk_RunStepSequence(TownPelicanTalk *talk)
{
    const TownPelicanTalkStep *step = &data_ov075_02279930[talk->sequence];
    if (step->each_step != 0 && step->run.function != 0) {
        MemberPointer_CallVoid(&step->run, talk);
    }
}
CLEAN_AS(func_ov075_02278da4, TownPelicanTalk_RunStepSequence)
