/* The jobs 6 to 0x13 of the activity process (activity_jobs.h). */
#include "activity_jobs.h"

#include "acre_map.h"
#include "activity_card.h"
#include "activity_talk.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_exit.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "start_kind.h"
#include "state_block.h"
#include "villager_state.h"
#include "activity_process.h"
#include "player_id.h"
#include "scene_process_base.h"
#include "talk_object.h"

static_assert(offsetof(Activity, state) == 0xa1 && offsetof(Activity, card_parts) == 0x10e, "activity");
static_assert(offsetof(StateBlock, players) == 0x14 && offsetof(StateBlock, part_17254) == 0x17254, "state block");

extern StateBlock data_021dc7a8;
/* The town record the title's menu chose (activity_vars.h). */
extern int data_021f3c34;
/* A state byte of the game the jobs 0xe and 0xf wait to be 2 (the field actors read it too). */
extern u8 data_021c75b8;

extern const char data_020e3c54[]; /* "sp_etc_sequence1" */
extern const char data_020e3c68[]; /* "sp_etc_sequence3" */

/* Where the jobs 9 and 0xa enter their scene. */
extern const Vec3 data_020d1bfc;
extern const Vec3 data_020d1c14;

/* A player's name as text (0x24 bytes): built by func_02094fd4, destroyed by func_02094fbc. */
typedef struct ActivityJobsText {
    u32 words[0x24 / 4];
} ActivityJobsText;

#define TALK_INDEX 0
#define TALK_CLOSED 0

#define STATE_BLOCK_FLAG_12 0x12
#define STATE_BLOCK_17276 (0x17276 - 0x17254) /* a byte of part_17254 cleared with the last player */

enum ActivityJobsStateBlockMode {
    STATE_BLOCK_MODE_3 = 3, /* the save loaded */
    STATE_BLOCK_MODE_4 = 4, /* no save */
};

#define SEQUENCE1_REMOVED 7
#define SEQUENCE3_MESSAGE 39
#define CARD_PART_LETTERS 2

/* The copy the activity writes (bits 4-7 of card_parts) and the one it read (bits 0-3). */
static int write_part(const Activity *activity)
{
    return activity->card_parts >> 4;
}

static int read_part(const Activity *activity)
{
    return activity->card_parts & 0xf;
}

/* Talk 0 when it is closed: its receiver unlinked and it given; else NULL. */
static ActivityTalk *closed_talk(void)
{
    ActivityTalk *talk = (ActivityTalk *) TalkObject_Get(TALK_INDEX);
    if (talk->state != TALK_CLOSED) {
        return NULL;
    }
    TalkObject_DetachReceiver((TalkObject *) talk);
    return talk;
}

static SceneExit *entry_record(void)
{
    return (SceneExit *) (uintptr_t) SceneTables_EntryRecord();
}

/* func_020a4840: job 6 starts: the name of the town player data_021f3c34 put in talk 0's text
 * slot 0, that player's record cleared and the player forgotten by the state block, message 7
 * of "sp_etc_sequence1" shown; with no town player left, byte 0x17276 of the state block
 * cleared. */
void ActivityJobs_Start06(Activity *activity)
{
    ActivityTalk *talk = (ActivityTalk *) TalkObject_Get(TALK_INDEX);
    StateBlock *block = &data_021dc7a8;
    u8 *record = PlayerRecords_TownRecord(data_021dc7a8.players, data_021f3c34);
    ActivityJobsText name;
    PlayerIdText_Construct((PlayerIdText *) &name);
    PlayerId_NameToText(PlayerRecord_Player(record), (TextBase *) &name);
    TalkObject_SetPart((TalkObject *) talk, 0, (TextBase *) &name);
    PlayerRecord_Clear(record);
    StateBlock_ForgetPlayer(block, data_021f3c34);
    ActivityTalk_Show(activity, data_020e3c54, SEQUENCE1_REMOVED);
    if (PlayerRecords_CountTown(data_021dc7a8.players) == 0) {
        block->part_17254[STATE_BLOCK_17276] = 0;
    }
    activity->state = 0;
    PlayerIdText_Destruct((PlayerIdText *) &name);
}
CLEAN_AS(func_020a4840, ActivityJobs_Start06)

/* func_020a475c: job 6's steps: once talk 0 waits (given 0), the card checked, then the copy to
 * write, the other copy and the letters written. When a card step fails, message 10 of
 * "sp_etc_sequence2" is queued and the job stays (step 6) for good; else talk 0 is closed and
 * job 0xc started. */
void ActivityJobs_Step06(Activity *activity)
{
    int result;
    switch (activity->state) {
        case 0:
            if (ActivityTalk_FinishWaiting(activity, 0)) {
                activity->state = 1;
            }
            break;
        case 1:
            result = ActivityCard_StepCheck(activity);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 5;
            } else if (result != ACTIVITY_CARD_BUSY) {
                activity->state = 2;
            }
            break;
        case 2:
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 5;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 3;
            }
            break;
        case 3:
            result = ActivityCard_StepWritePart(activity, read_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 5;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 4;
            }
            break;
        case 4:
            result = ActivityCard_StepWritePart(activity, CARD_PART_LETTERS);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 5;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 7;
            }
            break;
        case 5:
            ActivityTalk_QueueMessage10(activity);
            activity->state = 6;
            break;
        case 6:
            break;
        default:
            ActivityTalk_Close(activity);
            ActivityProcess_StartJob(activity, 0xc);
            break;
    }
}
CLEAN_AS(func_020a475c, ActivityJobs_Step06)

/* func_020a4740: job 7 starts: message 39 of "sp_etc_sequence3" shown. */
void ActivityJobs_Start07(Activity *activity)
{
    ActivityTalk_Show(activity, data_020e3c68, SEQUENCE3_MESSAGE);
    activity->state = 0;
}
CLEAN_AS(func_020a4740, ActivityJobs_Start07)

/* func_020a467c: job 7's steps: once talk 0 waits (given 0), the card checked, then the copy to
 * write and the other copy written. When a card step fails, message 10 of "sp_etc_sequence2"
 * is queued and the job stays (step 5) for good; else talk 0 is closed and job 0xf started. */
void ActivityJobs_Step07(Activity *activity)
{
    int result;
    switch (activity->state) {
        case 0:
            if (ActivityTalk_FinishWaiting(activity, 0)) {
                activity->state = 1;
            }
            break;
        case 1:
            result = ActivityCard_StepCheck(activity);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 4;
            } else if (result != ACTIVITY_CARD_BUSY) {
                activity->state = 2;
            }
            break;
        case 2:
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 4;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 3;
            }
            break;
        case 3:
            result = ActivityCard_StepWritePart(activity, read_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 4;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 6;
            }
            break;
        case 4:
            ActivityTalk_QueueMessage10(activity);
            activity->state = 5;
            break;
        case 5:
            break;
        default:
            ActivityTalk_Close(activity);
            ActivityProcess_StartJob(activity, 0xf);
            break;
    }
}
CLEAN_AS(func_020a467c, ActivityJobs_Step07)

/* func_020a4678: job 8 starts; nothing to do. */
void ActivityJobs_Start08(void) {}
CLEAN_AS(func_020a4678, ActivityJobs_Start08)

/* func_020a464c: job 8's step: once talk 0 is closed, the entry record's exit 1 taken; job 0. */
void ActivityJobs_Step08(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    SceneExit_Take(entry_record(), 1);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a464c, ActivityJobs_Step08)

/* func_020a4648: job 9 starts; nothing to do. */
void ActivityJobs_Start09(void) {}
CLEAN_AS(func_020a4648, ActivityJobs_Start09)

/* func_020a45f0: job 9's step: once talk 0 is closed, the scene 13 entered at data_020d1bfc
 * (player parameter 0x800000, angle 0, arguments 3 and 2); job 0. */
void ActivityJobs_Step09(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    Vec3 point = data_020d1bfc;
    SceneExit_SetTo(entry_record(), 13, &point, 0x800000, 0, 3, 2);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a45f0, ActivityJobs_Step09)

/* func_020a45ec: job 0xa starts; nothing to do. */
void ActivityJobs_Start0A(void) {}
CLEAN_AS(func_020a45ec, ActivityJobs_Start0A)

/* func_020a4594: job 0xa's step: once talk 0 is closed, the scene 14 entered at data_020d1c14
 * (player parameter 0x800000, angle 0, arguments 3 and 2); job 0. */
void ActivityJobs_Step0A(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    Vec3 point = data_020d1c14;
    SceneExit_SetTo(entry_record(), 14, &point, 0x800000, 0, 3, 2);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a4594, ActivityJobs_Step0A)

/* func_020a4590: job 0xb starts; nothing to do. */
void ActivityJobs_Start0B(void) {}
CLEAN_AS(func_020a4590, ActivityJobs_Start0B)

/* func_020a4560: job 0xb's step: once talk 0 is closed, the scene 0x2f entered (arguments 3 and
 * 2); job 0. */
void ActivityJobs_Step0B(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    SceneExit_SetToScene(entry_record(), 0x2f, 3, 2);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a4560, ActivityJobs_Step0B)

/* func_020a455c: job 0xc starts; nothing to do. */
void ActivityJobs_Start0C(void) {}
CLEAN_AS(func_020a455c, ActivityJobs_Start0C)

/* func_020a44f0: job 0xc's step: once talk 0 is closed, the save loaded; when that gives 4 or 1
 * the state block is set up anew (StateBlock_Init, the guests' records and the villagers'
 * state cleared) and started in mode 3, else started in mode 4; then the start finished and
 * the scene 0x2c entered (arguments 3 and 2); job 0. */
void ActivityJobs_Step0C(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    int loaded = ActivityCard_LoadSave();
    if (loaded == ACTIVITY_CARD_BAD || loaded == ACTIVITY_CARD_FAILED) {
        StateBlock_Init(&data_021dc7a8);
        PlayerRecords_ClearGuests();
        VillagerState_Reset();
        StateBlock_Start(&data_021dc7a8, STATE_BLOCK_MODE_3);
    } else {
        StateBlock_Start(&data_021dc7a8, STATE_BLOCK_MODE_4);
    }
    StateBlock_FinishStart(&data_021dc7a8);
    VillagerState_CallNoOp();
    SceneExit_SetToScene(entry_record(), 0x2c, 3, 2);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a44f0, ActivityJobs_Step0C)

/* func_020a44ec: job 0xd starts; nothing to do. */
void ActivityJobs_Start0D(void) {}
CLEAN_AS(func_020a44ec, ActivityJobs_Start0D)

/* func_020a44bc: job 0xd's step: once talk 0 is closed, func_020a53ec told (2, 3, 0, 0); job 0. */
void ActivityJobs_Step0D(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    SceneProcessBase_Request(2, 3, 0, 0);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a44bc, ActivityJobs_Step0D)

/* func_020a44b8: job 0xe starts; nothing to do. */
void ActivityJobs_Start0E(void) {}
CLEAN_AS(func_020a44b8, ActivityJobs_Start0E)

/* func_020a4454: job 0xe's step: with data_021c75b8 2 and talk 0 closed, the start kind set to
 * START_KIND_PLAYER_0 when flag 0x12 of the state block is set, else START_KIND_UNCHANGED, and
 * applied; then the scene 0x2d entered (arguments 3 and 0); job 0. */
void ActivityJobs_Step0E(Activity *activity)
{
    ActivityTalk *talk = (ActivityTalk *) TalkObject_Get(TALK_INDEX);
    if (data_021c75b8 != 2 || talk->state != TALK_CLOSED) {
        return;
    }
    TalkObject_DetachReceiver((TalkObject *) talk);
    if (StateBlock_TestFlag((u32 *) (void *) &data_021dc7a8, STATE_BLOCK_FLAG_12)) {
        StartKind_SetPlayer0();
    } else {
        StartKind_SetUnchanged();
    }
    StartKind_Apply();
    SceneExit_SetToScene(entry_record(), 0x2d, 3, 0);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a4454, ActivityJobs_Step0E)

/* func_020a4450: job 0xf starts; nothing to do. */
void ActivityJobs_Start0F(void) {}
CLEAN_AS(func_020a4450, ActivityJobs_Start0F)

/* func_020a43e4: job 0xf's step: with data_021c75b8 2 and talk 0 closed, the scene 0 entered in
 * front of the town's building 0x5000 (player parameter 0x400000, angle 0x8000, arguments 3
 * and 2); job 0.
 * REQUIRES: the town has building 0x5000. Without it the original enters the scene at whatever
 * its stack held; here at the point (0, 0, 0). */
void ActivityJobs_Step0F(Activity *activity)
{
    ActivityTalk *talk = (ActivityTalk *) TalkObject_Get(TALK_INDEX);
    if (data_021c75b8 != 2 || talk->state != TALK_CLOSED) {
        return;
    }
    TalkObject_DetachReceiver((TalkObject *) talk);
    int front[3] = {0, 0, 0};
    AcreMap_FindBuilding5000Front((int) AcreMap_Town(), front, NULL, NULL);
    SceneExit_SetTo(entry_record(), 0, (const Vec3 *) (const void *) front, 0x400000, -0x8000, 3, 2);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a43e4, ActivityJobs_Step0F)

/* func_020a43e0: job 0x10 starts; nothing to do. */
void ActivityJobs_Start10(void) {}
CLEAN_AS(func_020a43e0, ActivityJobs_Start10)

/* func_020a43a0: job 0x10's step: once talk 0 is closed, the entry record's exit 2 taken in
 * scene 6 and its exit 0 elsewhere; job 0. */
void ActivityJobs_Step10(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    if (SceneQuery_Current() == 6) {
        SceneExit_Take(entry_record(), 2);
    } else {
        SceneExit_Take(entry_record(), 0);
    }
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a43a0, ActivityJobs_Step10)

/* func_020a439c: job 0x11 starts; nothing to do. */
void ActivityJobs_Start11(void) {}
CLEAN_AS(func_020a439c, ActivityJobs_Start11)

/* func_020a4370: job 0x11's step: once talk 0 is closed, the entry record's exit 2 taken;
 * job 0. */
void ActivityJobs_Step11(Activity *activity)
{
    if (closed_talk() == NULL) {
        return;
    }
    SceneExit_Take(entry_record(), 2);
    ActivityProcess_StartJob(activity, 0);
}
CLEAN_AS(func_020a4370, ActivityJobs_Step11)

/* The steps of the jobs 0x12 and 0x13: the card checked, then the copy to write and the
 * letters written; job 0. A failed card step leaves the job at step 3 for good. */
static void write_copy_and_letters(Activity *activity)
{
    int result;
    switch (activity->state) {
        case 0:
            result = ActivityCard_StepCheck(activity);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 3;
            } else if (result != ACTIVITY_CARD_BUSY) {
                activity->state = 1;
            }
            break;
        case 1:
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 3;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 2;
            }
            break;
        case 2:
            result = ActivityCard_StepWritePart(activity, CARD_PART_LETTERS);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 3;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 4;
            }
            break;
        case 3:
            break;
        default:
            ActivityProcess_StartJob(activity, 0);
            break;
    }
}

/* func_020a4368: job 0x12 starts at step 0. */
void ActivityJobs_Start12(Activity *activity)
{
    activity->state = 0;
}
CLEAN_AS(func_020a4368, ActivityJobs_Start12)

/* func_020a42d4: job 0x12's steps (write_copy_and_letters). */
void ActivityJobs_Step12(Activity *activity)
{
    write_copy_and_letters(activity);
}
CLEAN_AS(func_020a42d4, ActivityJobs_Step12)

/* func_020a42b8: job 0x13 starts at step 0, the current player's flag 2 cleared. */
void ActivityJobs_Start13(Activity *activity)
{
    PlayerRecord_ClearFlag(PlayerRecords_Current(), 2);
    activity->state = 0;
}
CLEAN_AS(func_020a42b8, ActivityJobs_Start13)

/* func_020a4224: job 0x13's steps, the same as job 0x12's (write_copy_and_letters). */
void ActivityJobs_Step13(Activity *activity)
{
    write_copy_and_letters(activity);
}
CLEAN_AS(func_020a4224, ActivityJobs_Step13)
