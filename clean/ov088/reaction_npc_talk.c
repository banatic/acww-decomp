/* The talk scene of overlay 88's character: its lessons of reactions, the answers it offers
 * and its steps (reaction_npc_talk.h). */
#include "reaction_npc_talk.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "main/main_random.h"
#include "main/message_reader.h"
#include "main/message_receiver.h"
#include "main/motion_slots.h"
#include "main/obj_020d8c64.h"
#include "main/obj_020d9ff8.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/select_bmg.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/text_base.h"

static_assert(sizeof(ReactionNpcLine) == 8, "a line");
static_assert(sizeof(ReactionNpcTalkStep) == 0xc, "a step");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");

/* The talk scene's vtable. */
extern const u8 data_ov088_02279c58[];
/* The message files: "sp_npc_reaction" (its lines), "st_learn" (the reactions' names) and
 * "st_learn_talk" (the reactions as answers). */
extern const char data_ov088_02279d98[];
extern const char data_ov088_02279da8[];
extern const char data_ov088_02279db4[];
/* The scene's steps (filled at start-up by __sinit_ov088_022799c4, the flags initialised). */
extern ReactionNpcTalkStep data_ov088_02279c14[REACTION_NPC_STEPS];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The talk scene's vtable slots called through: its reset, and the answers offered. */
#define RT_SLOT_RESET 0x08
#define RT_SLOT_SET_ANSWERS 0x88

/* The daily bit of the current player and the player record's flag. */
#define RT_DAILY_TAUGHT 0x0e
#define RT_FLAG_TAUGHT 0x10

/* The first lesson's reaction, and the slot it goes into. */
#define RT_FIRST_REACTION 0x17
#define RT_FIRST_SLOT 0

/* The watch of a reaction: the frames the first lesson keeps resetting it to, the frames a
 * later one starts it from; taken in time while it is above 2. The pause before the next line. */
#define RT_WATCH_FIRST 0x14
#define RT_WATCH_LATER 0x34
#define RT_WATCH_IN_TIME 2
#define RT_PAUSE 0x14

/* The fifth answer (the slots offered): message 5 of the file of answer style 1. */
#define RT_EXTRA_ANSWER 4
#define RT_EXTRA_MESSAGE 5
#define RT_EXTRA_SELECT2 1 /* the select file "select2" */

/* No motion number (Obj020d8c64_LastMotionNumber). */
#define RT_NO_NUMBER (-1)

static u8 rt_line_shown(const ReactionNpcTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static TalkObject *rt_talk_object(ReactionNpcTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* Message `message` of "sp_npc_reaction" shown in `object`. */
static void rt_say(TalkObject *object, u8 message)
{
    TalkObject_SetMessage(object, &message, data_ov088_02279d98);
}

/* The name of reaction `reaction` ("st_learn") put in the talk's part `part`. */
static void rt_put_name(TalkObject *object, int part, u8 reaction)
{
    TalkObject_LoadPart(object, part, &reaction, (unsigned int) (uintptr_t) data_ov088_02279da8);
}

/* The byte `index` places after `base`, as the ROM's code addresses it (unbounded). */
static u8 *rt_byte(u8 *base, unsigned int index)
{
    return (u8 *) (uintptr_t) ((uintptr_t) base + index);
}

/* The talk scene's vtable slot `offset` called with `argument`. */
static void rt_call_slot(ReactionNpcTalk *talk, u32 offset, int argument)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + offset);
    ((void (*)(ReactionNpcTalk *, int))(uintptr_t) code)(talk, argument);
}

/* func_ov088_02278afc (slot 0x18, the player's answer), by the line shown:
 * - 0x17, 0x18: the reaction offered as that answer is chosen, and its line shown (0x1c plus
 *   it);
 * - 0x1a: the fifth answer, line 0x1b; another, the name of the reaction in that motion slot
 *   in part 1, the reaction chosen put in its place, its name in part 0, line 0x1c.
 * The line, when one was picked, is shown. */
void ReactionNpcTalk_OnAnswer(ReactionNpcTalk *talk)
{
    unsigned int answer = TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    int next = REACTION_NPC_NO_LINE;

    switch (rt_line_shown(talk)) {
        case REACTION_NPC_LINE_OFFER:
        case REACTION_NPC_LINE_MISSED: {
            u8 reaction = *rt_byte(talk->offered, answer);
            next = (u8) (reaction + REACTION_NPC_LINE_REPLACED);
            talk->chosen = reaction;
            break;
        }
        case REACTION_NPC_LINE_NO_SLOT:
            if (answer == RT_EXTRA_ANSWER) {
                next = REACTION_NPC_LINE_KEPT;
                break;
            }
            rt_put_name(rt_talk_object(talk), 1, (u8) MotionSlots_Get((int) answer));
            ReactionNpc_PutReaction(talk->owner, (int) answer, talk->chosen);
            rt_put_name(rt_talk_object(talk), 0, talk->chosen);
            next = REACTION_NPC_LINE_REPLACED;
            break;
        default:
            break;
    }
    if (next != REACTION_NPC_NO_LINE) {
        rt_say(rt_talk_object(talk), (u8) next);
    }
}
CLEAN_AS(func_ov088_02278afc, ReactionNpcTalk_OnAnswer)

/* func_ov088_02278ba4 (slot 0x14, a line ended), by the line shown:
 * - a reaction's line (0x1d-0x39): the talk object's mode 0 and step 3 (the reaction watched);
 * - 0x0b: the talk object's mode 0 and step 1 (the first lesson);
 * - 0x17, 0x18: the line kept (as `chosen`) and step 2 (the answers offered);
 * - 0x19: the reaction chosen put in the first empty motion slot, when there is one;
 * - 0x1a: the player's motion slots offered as answers (slot 0x88, way 2). */
void ReactionNpcTalk_OnLineEnded(ReactionNpcTalk *talk)
{
    u8 line = rt_line_shown(talk);
    if (line >= REACTION_NPC_LINE_REACTIONS && line <= REACTION_NPC_LINE_REACTIONS_LAST) {
        rt_talk_object(talk)->mode = 0;
        ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_WATCH);
    }
    switch (rt_line_shown(talk)) {
        case REACTION_NPC_LINE_LESSON:
            rt_talk_object(talk)->mode = 0;
            ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_FIRST_LESSON);
            break;
        case REACTION_NPC_LINE_OFFER:
        case REACTION_NPC_LINE_MISSED:
            talk->chosen = rt_line_shown(talk);
            ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_OFFER);
            break;
        case REACTION_NPC_LINE_LEARNT: {
            int slot = MotionSlots_FindEmpty();
            if (slot != -1) {
                ReactionNpc_PutReaction(talk->owner, slot, talk->chosen);
            }
            break;
        }
        case REACTION_NPC_LINE_NO_SLOT:
            rt_call_slot(talk, RT_SLOT_SET_ANSWERS, REACTION_NPC_ANSWERS_SLOTS);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov088_02278ba4, ReactionNpcTalk_OnLineEnded)

/* func_ov088_02278c38 (slot 0x78, the line the talk starts with), of "sp_npc_reaction": line 1
 * until the player record's flag 0x10 is set (taught once); then one of 0x13-0x14 when not
 * taught today (daily bit 0x0e), else one of 0x0d-0x0f with one motion slot filled, or of
 * 0x10-0x12 with more. */
void ReactionNpcTalk_FirstLine(ReactionNpcTalk *talk, ReactionNpcLine *out)
{
    (void) talk;
    out->text = (u32) (uintptr_t) data_ov088_02279d98;
    out->message = REACTION_NPC_LINE_FIRST;
    if (PlayerRecord_TestFlag(PlayerRecords_Current(), RT_FLAG_TAUGHT) != 1) {
        return;
    }
    if (TalkChecks_TestSetDailyBit(RT_DAILY_TAUGHT, 0) == 0) {
        out->message = (u8) (MainRandom_Below(2) + REACTION_NPC_LINE_NOT_TODAY);
    } else if (MotionSlots_Count() == 1) {
        out->message = (u8) (MainRandom_Below(3) + REACTION_NPC_LINE_ONE_KNOWN);
    } else {
        out->message = (u8) (MainRandom_Below(3) + REACTION_NPC_LINE_MORE_KNOWN);
    }
}
CLEAN_AS(func_ov088_02278c38, ReactionNpcTalk_FirstLine)

/* func_ov088_02278c94: the talk scene told through its vtable slot 0x08 and given its owner;
 * the owner not watched; no reaction marked known, none offered (0xff). */
void ReactionNpcTalk_Begin(ReactionNpcTalk *talk, ReactionNpc *owner)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + RT_SLOT_RESET);
    ((void (*)(ReactionNpcTalk *))(uintptr_t) code)(talk);
    talk->owner = owner;
    talk->owner->watch = 0;
    MI_CpuFill8(talk->known, 0, REACTION_NPC_MARKS);
    MI_CpuFill8(talk->offered, 0xff, REACTION_NPC_OFFERED_ROOM);
}
CLEAN_AS(func_ov088_02278c94, ReactionNpcTalk_Begin)

/* func_ov088_02278cd8 (slot 0x04): its destructor, then the scene freed. */
void *ReactionNpcTalk_Delete(void *talk)
{
    *(const u8 **) talk = data_ov088_02279c58;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov088_02278cd8, ReactionNpcTalk_Delete)

/* func_ov088_02278cf8 (slot 0x00): the scene class 0x020d9ff8's destructor. */
void *ReactionNpcTalk_Destroy(void *talk)
{
    *(const u8 **) talk = data_ov088_02279c58;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov088_02278cf8, ReactionNpcTalk_Destroy)

/* func_ov088_02278d10: the constructor: a scene of class 0x020d9ff8 given this class's vtable. */
void *ReactionNpcTalk_Construct(void *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) talk = data_ov088_02279c58;
    return talk;
}
CLEAN_AS(func_ov088_02278d10, ReactionNpcTalk_Construct)

/* func_ov088_02278d28 (step 4, each frame): once the owner's countdown has run out, step 0;
 * the scene's next line asked for (each frame of the step). */
void ReactionNpcTalk_StepPause(ReactionNpcTalk *talk)
{
    if (Countdown_Tick8(&talk->owner->countdown) == 0) {
        ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_NONE);
    }
    SceneCommand_RequestNextLine((SceneCommandScene *) (void *) talk);
}
CLEAN_AS(func_ov088_02278d28, ReactionNpcTalk_StepPause)

/* func_ov088_02278d54 (step 3, each frame): once the talk object's state is 5, the reaction
 * chosen is watched: the owner's watch starts at 0x34 frames and, until a number of its motion
 * was taken, counts down while above 2. Then line 0x19 when it was taken in time (above 2:
 * daily bit 0x0e set; line 0x1a without an empty motion slot), else 0x18; the reaction's name
 * in part 0; the watch over, a pause of 0x14 frames, the line shown, step 4. */
void ReactionNpcTalk_StepWatch(ReactionNpcTalk *talk)
{
    TalkObject *object = rt_talk_object(talk);
    ReactionNpc *owner = talk->owner;
    if (object->state != TALK_OBJECT_GONE) {
        return;
    }
    if (owner->watch == 0) {
        owner->watch = RT_WATCH_LATER;
    }
    if (Obj020d8c64_LastMotionNumber((s16 *) (void *) owner) == RT_NO_NUMBER &&
        Countdown_Tick8(&owner->watch) > RT_WATCH_IN_TIME) {
        return;
    }
    u8 next;
    if (owner->watch > RT_WATCH_IN_TIME) {
        next = REACTION_NPC_LINE_LEARNT;
        TalkChecks_TestSetDailyBit(RT_DAILY_TAUGHT, 1);
        if (MotionSlots_FindEmpty() == -1) {
            next = REACTION_NPC_LINE_NO_SLOT;
        }
    } else {
        next = REACTION_NPC_LINE_MISSED;
    }
    rt_put_name(object, 0, talk->chosen);
    owner->watch = 0;
    owner->countdown = RT_PAUSE;
    rt_say(object, next);
    ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_PAUSE);
}
CLEAN_AS(func_ov088_02278d54, ReactionNpcTalk_StepWatch)

/* func_ov088_02278e28 (step 2, each frame): the answers offered (slot 0x88): new reactions
 * after line 0x17, the same ones after 0x18; nothing chosen (0xff); step 0. */
void ReactionNpcTalk_StepOffer(ReactionNpcTalk *talk)
{
    if (talk->chosen == REACTION_NPC_LINE_OFFER) {
        rt_call_slot(talk, RT_SLOT_SET_ANSWERS, REACTION_NPC_ANSWERS_NEW);
    } else {
        rt_call_slot(talk, RT_SLOT_SET_ANSWERS, REACTION_NPC_ANSWERS_SAME);
    }
    talk->chosen = 0xff;
    ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_NONE);
}
CLEAN_AS(func_ov088_02278e28, ReactionNpcTalk_StepOffer)

/* func_ov088_02278e64 (step 1, each frame): once the talk object's state is 5, the owner is
 * watched (0x14 frames, set again each frame); once a number of its motion was taken: the
 * name of reaction 0x17 in part 0, the watch over and a pause of 0x14 frames, the player
 * record's flag 0x10 set, reaction 0x17 put in motion slot 0, line 0x0c shown, daily bit 0x0e
 * set, step 4. */
void ReactionNpcTalk_StepFirstLesson(ReactionNpcTalk *talk)
{
    TalkObject *object = rt_talk_object(talk);
    if (object->state != TALK_OBJECT_GONE) {
        return;
    }
    talk->owner->watch = RT_WATCH_FIRST;
    if (Obj020d8c64_LastMotionNumber((s16 *) (void *) talk->owner) == RT_NO_NUMBER) {
        return;
    }
    rt_put_name(rt_talk_object(talk), 0, RT_FIRST_REACTION);
    talk->owner->watch = 0;
    talk->owner->countdown = RT_PAUSE;
    PlayerRecord_SetFlag(PlayerRecords_Current(), RT_FLAG_TAUGHT);
    ReactionNpc_PutReaction(talk->owner, RT_FIRST_SLOT, RT_FIRST_REACTION);
    rt_say(object, REACTION_NPC_LINE_LEARNT_FIRST);
    TalkChecks_TestSetDailyBit(RT_DAILY_TAUGHT, 1);
    ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_PAUSE);
}
CLEAN_AS(func_ov088_02278e64, ReactionNpcTalk_StepFirstLesson)

/* func_ov088_02278f0c: the scene's step set, from its first state. */
void ReactionNpcTalk_SetStep(ReactionNpcTalk *talk, unsigned int step)
{
    talk->step = (s32) step;
    talk->step_state = 0;
}
CLEAN_AS(func_ov088_02278f0c, ReactionNpcTalk_SetStep)

/* func_ov088_02278f1c (slot 0x84, once the talk's link has closed): a step that runs once it
 * closes, when there is one, is run, and the scene goes back to step 0 (no step of this scene
 * is one).
 * REQUIRES: the step is below 5. */
void ReactionNpcTalk_OnTalkClosed(ReactionNpcTalk *talk)
{
    const ReactionNpcTalkStep *step = &data_ov088_02279c14[talk->step];
    if (step->each_frame != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
    ReactionNpcTalk_SetStep(talk, REACTION_NPC_STEP_NONE);
}
CLEAN_AS(func_ov088_02278f1c, ReactionNpcTalk_OnTalkClosed)

/* func_ov088_02278f6c (slot 0x80, each frame the talk's link stays open): a step that runs
 * then, when there is one, is run.
 * REQUIRES: the step is below 5. */
void ReactionNpcTalk_WhileTalkOpen(ReactionNpcTalk *talk)
{
    const ReactionNpcTalkStep *step = &data_ov088_02279c14[talk->step];
    if (step->each_frame != 0 && step->run.function != 0) {
        MemberPointer_CallVoid(&step->run, talk);
    }
}
CLEAN_AS(func_ov088_02278f6c, ReactionNpcTalk_WhileTalkOpen)

/* func_ov088_02278fb0 (slot 0x88): the talk's answers set and opened (later). Reaction 0 and
 * those in the player's motion slots are marked known; then the four answers, each the text of
 * a message of "st_learn_talk" (of "st_learn" for way 2):
 * - way 0: a reaction not marked known drawn at random (ReactionNpcTalk_PickUnknown), marked
 *   and kept as offered; reaction 1 when there is none;
 * - way 1: the reactions offered last;
 * - way 2: the reactions of the four motion slots, then a fifth answer, message 5 of answer
 *   style 1's file, which is also the cancel.
 * The current player's record is asked for first, its answer unused.
 * QUIRK: the slots are marked through the first MotionSlots_Count of them, whatever they hold:
 * an empty slot (0xff) before a filled one marks the byte 0xff places on. */
void ReactionNpcTalk_SetAnswers(ReactionNpcTalk *talk, int way)
{
    (void) PlayerRecords_Current();
    TalkAnswers *answers = TalkObject_Answers(rt_talk_object(talk));
    PlayerIdText unused_name;
    PlayerIdText_Construct(&unused_name);
    SelectBmgText text;
    SelectBmgText_Construct(&text);
    TalkAnswers_Clear(answers);

    talk->known[0] = 1;
    for (int i = 0; i < MotionSlots_Count(); i++) {
        *rt_byte(talk->known, (unsigned int) MotionSlots_Get(i)) = 1;
    }

    int i;
    for (i = 0; i < REACTION_NPC_OFFERED; i++) {
        int reaction;
        if (way == REACTION_NPC_ANSWERS_NEW) {
            reaction = ReactionNpcTalk_PickUnknown((int) (u32) (uintptr_t) talk, talk->known, REACTION_NPC_MARKS);
            if (reaction != -1) {
                if (*rt_byte(talk->known, (unsigned int) reaction) == 0) {
                    *rt_byte(talk->known, (unsigned int) reaction) = 1;
                }
            } else {
                reaction = 1;
            }
            talk->offered[i] = (u8) reaction;
        } else if (way == REACTION_NPC_ANSWERS_SAME) {
            reaction = talk->offered[i];
        } else {
            reaction = MotionSlots_Get(i);
        }
        TalkAnswer *answer = TalkAnswers_Answer(answers, i);
        u8 message = (u8) reaction;
        const char *file = way != REACTION_NPC_ANSWERS_SLOTS ? data_ov088_02279db4 : data_ov088_02279da8;
        MessageReader_LoadMessage((int) (u32) (uintptr_t) &text, &message, (int) (u32) (uintptr_t) file);
        TextBase_Copy(TalkAnswers_Text(answer), (TextBase *) (void *) &text);
    }

    if (way == REACTION_NPC_ANSWERS_SLOTS) {
        TalkAnswer *extra = TalkAnswers_Answer(answers, i);
        u8 message = RT_EXTRA_MESSAGE;
        TalkAnswers_SetMessage(extra, &message);
        TalkAnswers_SetFile(extra, (int) TalkAnswers_SelectFileName(RT_EXTRA_SELECT2));
        TalkAnswers_LoadAnswerText(extra);
        TalkAnswers_SetCount(answers, i + 1);
        TalkAnswers_SetCancelToLast(answers);
    } else {
        TalkAnswers_SetCount(answers, i);
    }
    TalkObject_OpenChoices(rt_talk_object(talk), 1);
    SelectBmgText_Destruct(&text);
    PlayerIdText_Destruct(&unused_name);
}
CLEAN_AS(func_ov088_02278fb0, ReactionNpcTalk_SetAnswers)

/* func_ov088_02279100: a reaction not known, at random: the n-th of the marks of `known` that
 * are 0, n drawn below the number of them among the first `count`; -1 when there is none.
 * QUIRK: the walk looks at `count` + 1 marks (the one past the marks is the first offered
 * reaction); 0 should it pass them all. */
int ReactionNpcTalk_PickUnknown(int unused, const unsigned char *known, int count)
{
    int unknown = ReactionNpcTalk_CountUnknown(unused, (unsigned char *) (uintptr_t) known, count);
    if (unknown <= 0) {
        return -1;
    }
    int left = (int) MainRandom_Below(unknown);
    for (int i = 0; i <= count; i++) {
        if (*(const u8 *) (uintptr_t) ((uintptr_t) known + (unsigned int) i) == 0) {
            if (left == 0) {
                return i;
            }
            left--;
        }
    }
    return 0;
}
CLEAN_AS(func_ov088_02279100, ReactionNpcTalk_PickUnknown)

/* func_ov088_0227913c: how many of the `count` marks of `known` are 0. */
int ReactionNpcTalk_CountUnknown(int unused, unsigned char *known, int count)
{
    (void) unused;
    int unknown = 0;
    for (int i = 0; i < count; i++) {
        if (known[i] == 0) {
            unknown++;
        }
    }
    return unknown;
}
CLEAN_AS(func_ov088_0227913c, ReactionNpcTalk_CountUnknown)
