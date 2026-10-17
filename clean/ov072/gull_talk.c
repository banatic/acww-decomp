/* The talk scene of overlay 72's character (gull_talk.h). */
#include "gull_talk.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "gull.h"
#include "gull_spots.h"
#include "main/current_pockets.h"
#include "main/event_schedule.h"
#include "main/item_1568_count.h"
#include "main/item_lists.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/obj_020d9ff8.h"
#include "main/scene_command.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/scene_standard_anims.h"
#include "main/speaker_anim.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"

static_assert(offsetof(GullTalk, step) == 0xb0 && offsetof(GullTalk, step_state) == 0xb4, "GullTalk");
static_assert(offsetof(GullTalk, topic) == 0xb8 && offsetof(GullTalk, owner) == 0xbc, "GullTalk");
static_assert(sizeof(GullTalk) == 0xc0, "GullTalk");
static_assert(sizeof(GullTalkLine) == 8 && sizeof(GullTalkStep) == 0xc, "GullTalk rows");

/* "sp_npc_gull", the archive of its lines. */
extern const char data_ov072_02279a00[];
/* The first line of each topic (the archive and the line; the topics 0 and 3 draw theirs). */
extern const GullTalkLine data_ov072_02279874[GULL_TALK_TOPICS];
/* The count of item 0x1568 (item_1568_count.h). */
extern u8 data_021ebcd2[];
/* The word of a motion request. */
extern u16 data_020c80f8;

/* The class's vtable. */
extern const u8 data_ov072_02279a78[];

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define GULL_TALK_SLOT_RESET 2

/* The item it takes, counts and places, and how many it counts at most. */
#define GULL_TALK_ITEM 0x1568
#define GULL_TALK_COUNT_MAX 5
/* The pockets' slots, the most it can take at once. */
#define GULL_TALK_POCKET_SLOTS 15

/* The player's daily bits (talk_checks.h): talked today, and brought item 0x1568 today. */
#define GULL_TALK_DAILY_TALKED 0x14
#define GULL_TALK_DAILY_BROUGHT 0x15

/* The parts of the talk the lines put values in (SceneBase_PutValue, format 2). */
#define GULL_TALK_PART_MISSING 0 /* how many more it needs */
#define GULL_TALK_PART_TAKEN 1   /* how many it took */
#define GULL_TALK_VALUE_FORMAT 2

/* The lines whose showing it follows up (GullTalk_OnLineShown). */
#define GULL_TALK_LINE_FIRST_END 0x00 /* the first talk ends: step 1 */
#define GULL_TALK_LINE_PLACE 0x0b     /* the items it was given placed in the town */
#define GULL_TALK_LINE_TAKE_A 0x14    /* the items taken in its hand */
#define GULL_TALK_LINE_TAKE_B 0x15
#define GULL_TALK_LINE_COUNT 0x16 /* line 0x17 when five were counted, else 0x19 plus the count */
#define GULL_TALK_LINE_GIFT 0x18  /* an item given, then line 0x19 */
#define GULL_TALK_LINE_GIFT_END 0x19
#define GULL_TALK_NO_LINE 0xff

/* The talk's mode while its window goes away, and the event the gift ends. */
#define GULL_TALK_MODE_CLOSE 0
#define GULL_TALK_EVENT 0x44

/* The scene command's motion of the item in hand (scene_command.h). */
#define GULL_TALK_HAND_MOTION 5

/* The gift: an item of kind 0 (furniture), group 0x13 (item_lists.h). */
#define GULL_TALK_GIFT_KIND 0
#define GULL_TALK_GIFT_GROUP 0x13

/* Step 1: the character's animation 0xd5 (priority 2, mode 1), then its turn to the player
 * (motion 3), then one of the lines 5-9. */
#define GULL_TALK_STEP_ANIMATION 0xd5
#define GULL_TALK_STEP_PRIORITY 2
#define GULL_TALK_STEP_TURN 3
#define GULL_TALK_STEP_PLAYER 4
#define GULL_TALK_STEP_LINE_FIRST 5
#define GULL_TALK_STEP_LINES 5
#define GULL_TALK_STEP_ANIMATE 0
#define GULL_TALK_STEP_TURNING 1
#define GULL_TALK_STEP_ENDING 2

/* The members of the character this scene reaches (scene_object.h). */
#define GULL_TALK_OWNER_STANDARD_ANIMS 0x2a0
#define GULL_TALK_OWNER_ANIM 0x334
#define GULL_TALK_OWNER_MOTION 0x564

static TalkObject *gull_talk_object(const GullTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

static SceneCommandScene *gull_talk_command(GullTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

static u8 *gull_talk_owner_at(GullTalk *talk, int offset)
{
    return (u8 *) talk->owner + offset;
}

static SceneMotion *gull_talk_owner_motion(GullTalk *talk)
{
    return (SceneMotion *) (void *) gull_talk_owner_at(talk, GULL_TALK_OWNER_MOTION);
}

/* Line `line` of "sp_npc_gull" shown by `object`. */
static void gull_talk_say(TalkObject *object, u8 line)
{
    TalkObject_SetMessage(object, &line, data_ov072_02279a00);
}

/* The slot of the first of item 0x1568 in the player's pockets, or a negative number. */
static int gull_talk_find_item(void)
{
    u16 item = GULL_TALK_ITEM;
    return CurrentPockets_FindItem(&item);
}

/* ---- Its life */

/* func_ov072_02278d54: the talk reset (its vtable slot 2), `owner` its owner and topic 0. */
void GullTalk_Begin(GullTalk *talk, struct Gull *owner)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(GullTalk *))(uintptr_t) vtable[GULL_TALK_SLOT_RESET])(talk);
    talk->owner = owner;
    talk->topic = GULL_TALK_TOPIC_FIRST_MEETING;
}
CLEAN_AS(func_ov072_02278d54, GullTalk_Begin)

/* func_ov072_02278d78 (slot 0x04): destructed, then freed. */
GullTalk *GullTalk_DestructDelete(GullTalk *talk)
{
    talk->scene.vtable = data_ov072_02279a78;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov072_02278d78, GullTalk_DestructDelete)

/* func_ov072_02278d98 (slot 0x00): the destructor: its class's vtable, then the base class's
 * body. */
GullTalk *GullTalk_Destruct(GullTalk *talk)
{
    talk->scene.vtable = data_ov072_02279a78;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov072_02278d98, GullTalk_Destruct)

/* func_ov072_02278db0: the base class constructed, then its class's vtable. */
GullTalk *GullTalk_Construct(GullTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    talk->scene.vtable = data_ov072_02279a78;
    return talk;
}
CLEAN_AS(func_ov072_02278db0, GullTalk_Construct)

/* ---- Its slots */

/* func_ov072_02278ad4 (slot 0x18): the player's answer read; nothing follows from it. */
void GullTalk_OnAnswer(GullTalk *talk)
{
    TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->scene));
}
CLEAN_AS(func_ov072_02278ad4, GullTalk_OnAnswer)

/* func_ov072_02278ae8 (slot 0x14): what follows the line shown:
 * - 0x00: the talk's window goes away (talk mode 0) and step 1 starts;
 * - 0x0b: up to five of item 0x1568 placed in the town (GullSpots_PlaceItems);
 * - 0x14, 0x15: item 0x1568 in its hand, then line 0x16;
 * - 0x16: line 0x17 when five were counted, else line 0x19 plus the count;
 * - 0x18: an item of kind 0, group 0x13 drawn, put in its hand and given to the player, then
 *   line 0x19;
 * - 0x19: event 0x44 marked as taken part in. */
void GullTalk_OnLineShown(GullTalk *talk)
{
    u8 shown = ((const MessageReceiver *) (const void *) talk)->message;
    int line = GULL_TALK_NO_LINE;

    switch (shown) {
        case GULL_TALK_LINE_FIRST_END:
            SceneCommand_RequestTalkMode(gull_talk_command(talk), GULL_TALK_MODE_CLOSE);
            GullTalk_SetStep(talk, GULL_TALK_STEP_TURN_TO_PLAYER);
            break;
        case GULL_TALK_LINE_PLACE:
            GullSpots_PlaceItems();
            break;
        case GULL_TALK_LINE_TAKE_A:
        case GULL_TALK_LINE_TAKE_B: {
            u16 item = GULL_TALK_ITEM;
            SceneCommand_RequestMotion14(gull_talk_command(talk), &item, 0, GULL_TALK_HAND_MOTION, 0);
            line = GULL_TALK_LINE_COUNT;
            break;
        }
        case GULL_TALK_LINE_COUNT:
            if (Item1568Count_Get(data_021ebcd2) >= GULL_TALK_COUNT_MAX) {
                line = 0x17;
            } else {
                line = (u8) (Item1568Count_Get(data_021ebcd2) + 0x19);
            }
            break;
        case GULL_TALK_LINE_GIFT: {
            ItemList list;
            u16 gift;
            ItemList_Construct(&list, GULL_TALK_GIFT_KIND, GULL_TALK_GIFT_GROUP);
            ItemLists_Draw(&gift, &list, 0, 0, 1, 1, 0);
            ItemList_Destruct(&list);
            SceneCommand_RequestMotion13(gull_talk_command(talk), &gift, 0, GULL_TALK_HAND_MOTION, 0);
            CurrentPockets_Give(&gift, 0);
            line = GULL_TALK_LINE_GIFT_END;
            break;
        }
        case GULL_TALK_LINE_GIFT_END:
            EventSchedule_MarkTakenPart(GULL_TALK_EVENT);
            break;
        default:
            break;
    }
    if (line != GULL_TALK_NO_LINE) {
        gull_talk_say(gull_talk_object(talk), (u8) line);
    }
}
CLEAN_AS(func_ov072_02278ae8, GullTalk_OnLineShown)

/* func_ov072_02278bfc (slot 0x78): the topic picked and its first line given:
 * - the first talk of the day (daily bit 0x14 not set): with the count's mark, topic 2 and the
 *   bit set; without, topic 0;
 * - else five counted: topic 3;
 * - else none of item 0x1568 in the pockets: topic 4 when none was counted, else topic 5 with
 *   how many more it needs in part 0;
 * - else topic 6 when daily bit 0x15 was set already, else 7 (the bit set either way); then each
 *   of item 0x1568 in the pockets (at most 15) taken out and counted while fewer than five
 *   are, and how many were taken in part 1.
 * The line: topic 0 one of 0-4, topic 3 one of 0xd-0x11, the others the table's.
 * QUIRK: the pockets are looked at before anything else, even when the result is not used. */
void GullTalk_Line(GullTalk *talk, GullTalkLine *line)
{
    int slot = gull_talk_find_item();

    if (TalkChecks_TestSetDailyBit(GULL_TALK_DAILY_TALKED, 0) == 0) {
        if (Item1568Count_HasMark(data_021ebcd2) != 0) {
            talk->topic = GULL_TALK_TOPIC_FIRST_MARKED;
            TalkChecks_TestSetDailyBit(GULL_TALK_DAILY_TALKED, 1);
        } else {
            talk->topic = GULL_TALK_TOPIC_FIRST_MEETING;
        }
    } else if (Item1568Count_Get(data_021ebcd2) >= GULL_TALK_COUNT_MAX) {
        talk->topic = GULL_TALK_TOPIC_ALL_COUNTED;
    } else if (slot < 0) {
        if (Item1568Count_Get(data_021ebcd2) == 0) {
            talk->topic = GULL_TALK_TOPIC_NONE_YET;
        } else {
            int missing;
            talk->topic = GULL_TALK_TOPIC_MORE_NEEDED;
            missing = GULL_TALK_COUNT_MAX - Item1568Count_Get(data_021ebcd2);
            if (missing < 0) {
                missing = 0;
            }
            SceneBase_PutValue(&talk->scene, missing, GULL_TALK_PART_MISSING, GULL_TALK_VALUE_FORMAT, 0, 0);
        }
    } else {
        int taken;
        if (TalkChecks_TestSetDailyBit(GULL_TALK_DAILY_BROUGHT, 1) != 0) {
            talk->topic = GULL_TALK_TOPIC_BROUGHT_AGAIN;
        } else {
            talk->topic = GULL_TALK_TOPIC_BROUGHT;
        }
        for (taken = 1; taken <= GULL_TALK_POCKET_SLOTS; taken++) {
            CurrentPockets_Empty(slot);
            if (Item1568Count_Get(data_021ebcd2) < GULL_TALK_COUNT_MAX) {
                Item1568Count_Increment(data_021ebcd2);
            }
            slot = gull_talk_find_item();
            if (slot < 0) {
                break;
            }
        }
        SceneBase_PutValue(&talk->scene, taken, GULL_TALK_PART_TAKEN, GULL_TALK_VALUE_FORMAT, 0, 0);
    }

    if (talk->topic >= 0 && talk->topic < GULL_TALK_TOPICS) {
        line->name = data_ov072_02279874[talk->topic].name;
        if (talk->topic == GULL_TALK_TOPIC_FIRST_MEETING) {
            line->message = (u8) MainRandom_Below(5);
        } else if (talk->topic == GULL_TALK_TOPIC_ALL_COUNTED) {
            line->message = (u8) (MainRandom_Below(5) + 0xd);
        } else {
            line->message = data_ov072_02279874[talk->topic].message;
        }
    }
}
CLEAN_AS(func_ov072_02278bfc, GullTalk_Line)

/* ---- Its steps */

/* func_ov072_02278dc8 (step 1, each frame while the talk's link is open):
 * - once the talk window is gone, the character plays animation 0xd5 (its first standard
 *   animation 0);
 * - once that animation shows and its motion is done, it turns to the player;
 * - once the turn is done, the count gets its mark, the talk shows its next line, daily bit
 *   0x14 is set, one of the lines 5-9 is said and the scene goes back to step 0. */
void GullTalk_StepTurnToPlayer(GullTalk *talk)
{
    switch (talk->step_state) {
        case GULL_TALK_STEP_ANIMATE:
            if (gull_talk_object(talk)->state == TALK_OBJECT_GONE) {
                SceneMotion_RequestAnimation(gull_talk_owner_motion(talk), GULL_TALK_STEP_PRIORITY, GULL_TALK_STEP_ANIMATION,
                                             1, data_020c80f8, 0);
                SceneStandardAnims_SetFirst(
                    (SceneStandardAnims *) (void *) gull_talk_owner_at(talk, GULL_TALK_OWNER_STANDARD_ANIMS), 0);
                talk->step_state++;
            }
            break;
        case GULL_TALK_STEP_TURNING:
            if (SpeakerAnim_Number((SpeakerAnim *) (void *) gull_talk_owner_at(talk, GULL_TALK_OWNER_ANIM), 0) ==
                    GULL_TALK_STEP_ANIMATION &&
                SceneMotion_IsDone(gull_talk_owner_motion(talk)) != 0) {
                int yaw = (int) (intptr_t) SceneObject_YawToActor((u8 *) talk->owner, GULL_TALK_STEP_PLAYER);
                SceneMotion_Request(gull_talk_owner_motion(talk), GULL_TALK_STEP_TURN, GULL_TALK_STEP_PRIORITY, 0, 0, 0,
                                    (s16) yaw, 0, 0, data_020c80f8, 0);
                talk->step_state++;
            }
            break;
        case GULL_TALK_STEP_ENDING:
            if (SceneMotion_Kind(gull_talk_owner_motion(talk)) == GULL_TALK_STEP_TURN &&
                SceneMotion_IsDone(gull_talk_owner_motion(talk)) != 0) {
                Item1568Count_SetMark(data_021ebcd2);
                SceneCommand_RequestNextLine(gull_talk_command(talk));
                TalkChecks_TestSetDailyBit(GULL_TALK_DAILY_TALKED, 1);
                gull_talk_say(gull_talk_object(talk),
                              (u8) (MainRandom_Below(GULL_TALK_STEP_LINES) + GULL_TALK_STEP_LINE_FIRST));
                GullTalk_SetStep(talk, GULL_TALK_STEP_NONE);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov072_02278dc8, GullTalk_StepTurnToPlayer)

/* func_ov072_02278f00: the scene's step set, from its first state. */
void GullTalk_SetStep(GullTalk *talk, int step)
{
    talk->step = step;
    talk->step_state = 0;
}
CLEAN_AS(func_ov072_02278f00, GullTalk_SetStep)

/* func_ov072_02278f10 (slot 0x84, once the talk's link has closed): a step that runs once it
 * closes, when there is one, is run, and the scene goes back to step 0.
 * REQUIRES: the step is below 2. */
void GullTalk_OnTalkClosed(GullTalk *talk)
{
    const GullTalkStep *step = &data_ov072_02279a24[talk->step];

    if (step->each_frame != 0 || step->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&step->run, talk);
    GullTalk_SetStep(talk, GULL_TALK_STEP_NONE);
}
CLEAN_AS(func_ov072_02278f10, GullTalk_OnTalkClosed)

/* func_ov072_02278f60 (slot 0x80, each frame the talk's link stays open): a step that runs
 * then, when there is one, is run.
 * REQUIRES: the step is below 2. */
void GullTalk_WhileTalkOpen(GullTalk *talk)
{
    const GullTalkStep *step = &data_ov072_02279a24[talk->step];

    if (step->each_frame != 0 && step->run.function != 0) {
        MemberPointer_CallVoid(&step->run, talk);
    }
}
CLEAN_AS(func_ov072_02278f60, GullTalk_WhileTalkOpen)
