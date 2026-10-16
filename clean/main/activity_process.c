/* The activity process as a process, and its jobs 0 to 5 (activity_process.h). */
#include "activity_process.h"

#include <string.h>

#include "acre_map.h"
#include "activity_card.h"
#include "activity_talk.h"
#include "activity_vars.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "backup_card.h"
#include "card_save.h"
#include "clean.h"
#include "clock.h"
#include "letter_store.h"
#include "library_overlay.h"
#include "ov004/member_pointer.h"
#include "player_options.h"
#include "player_record.h"
#include "player_records.h"
#include "save_stamp.h"
#include "scene_query.h"
#include "session.h"
#include "session_link.h"
#include "state_block.h"
#include "town_pack.h"
#include "villager_town.h"
#include "wfc_session.h"

static_assert(offsetof(Activity, unk_50) == 0x50 && offsetof(Activity, receiver) == 0x54, "activity");
static_assert(offsetof(Activity, state) == 0xa1 && offsetof(Activity, block_copy) == 0xb8, "activity");
static_assert(offsetof(Activity, exchange_block) == 0xc0 && offsetof(Activity, pack_thread) == 0xcc, "activity");
static_assert(offsetof(Activity, date_time) == 0xdc && offsetof(Activity, card_parts) == 0x10e, "activity");
static_assert(offsetof(StateBlock, part_173f8) == 0x173f8 && sizeof(StateBlock) == 0x173fc, "state block");

/* The activity's words at 0xac-0xbc, which activity.h leaves unnamed: the heap its buffers come
 * from and the two card buffers (activity_card.h), the copy of the state block, and a buffer
 * only scene 9 has. */
typedef struct ActivityBuffers {
    u8 unk_00[0xac];
    Heap *heap;       /* 0xac */
    u8 *image;        /* 0xb0: ActivityCard.image */
    u8 *card;         /* 0xb4: ActivityCard.card */
    u8 *block_copy;   /* 0xb8: Activity.block_copy */
    u8 *scene9_block; /* 0xbc */
} ActivityBuffers;

static_assert(offsetof(ActivityBuffers, block_copy) == offsetof(Activity, block_copy), "buffers");

/* A job's two functions (C++ member pointers of the activity), as the table data_021f3ea4
 * keeps them: its start and its step. */
typedef struct ActivityJobEntry {
    MemberPointer start;
    MemberPointer step;
} ActivityJobEntry;

extern ActivityJobEntry data_021f3ea4[];

/* The vtables of the activity's class and of the processes' root class. */
extern const u32 data_020e3ae8[];
extern const u32 data_020da13c[];

extern NetSession *data_020ccf94;
extern Heap *data_021fbe94; /* the current heap */
extern StateBlock data_021dc7a8;
extern VillagerTown data_021e5a2c;

/* The current activity, or NULL; the job asked for next (activity_job.h); the received state
 * block (activity_vars.h). */
extern Activity *data_021f3c3c;
extern s32 data_021f3c38;
extern StateBlock *data_021f3c24;
extern u8 data_021f3c08;

/* The screen's transition (scene_process_base.h): 2 while the screen is shown. */
extern u8 data_021c75b8;

extern const char data_020e3c2c[]; /* "sp_npc_gatekeeper" */
extern const char data_020e3c40[]; /* "sp_etc_sequence2" */
extern const char data_020e3c54[]; /* "sp_etc_sequence1" */

/* A 4-byte value func_0204cdc8 keeps up to date (func_0209df64 makes the new one). */
extern u8 data_021f39fc[4];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
/* The jobs 1 and 2: three calls of func_0206fee0 (with 8, 0x20 and 0x40), and func_0204cdc8. */
extern void func_0206f74c(void);
extern void func_0204cdc8(u8 *value);
/* The object at data_021c779c + 0x20: allocated (0x10ec bytes) and set up; whether it is done
 * (func_02042324, which first lets it work) and whether its byte 0x10e9 is set
 * (func_020422f8); both release it with func_020422a0 when they give 1. */
extern void func_02042458(void);
extern int func_02042324(void);
extern int func_020422f8(void);
/* The town map's own models (activity_save.c). */
extern void func_0204d0ac(AcreMap *map);

#define TALK_WAIT_NONE 0

enum ActivityProcessScene {
    SCENE_06 = 0x06,
    SCENE_09 = 0x09,
    SCENE_0B = 0x0b,
    SCENE_0C = 0x0c,
    SCENE_0D = 0x0d,
    SCENE_2E = 0x2e,
    SCENE_2F = 0x2f,
};

#define SCREEN_SHOWN 2

/* The buffers' sizes. */
#define LETTERS_SIZE 0xc804
#define SCENE9_BLOCK_SIZE 0x249c
#define EXCHANGE_BLOCK_SIZE 0x950
#define PACK_BUFFER_SIZE 0x17400
#define PACK_THREAD_SIZE 0x10cc
#define ACTIVITY_SIZE 0x110

#define CARD_PART_LETTERS 2
#define PLAYER_FLAG_2 2
#define STATE_BLOCK_MODE_NEW 2

enum {
    JOB_NONE = 0,
    JOB_4 = 0x04,
    JOB_0C = 0x0c,
    JOB_0D = 0x0d,
    JOB_10 = 0x10,
    JOB_12 = 0x12,
    JOB_13 = 0x13,
    JOB_14 = 0x14,
    JOB_15 = 0x15,
    JOB_1F = 0x1f,
};

enum {
    SEQUENCE1_JOB5 = 12,
    SEQUENCE1_JOB3 = 0x28,
    SEQUENCE2_JOB1 = 1,
    GATEKEEPER_JOB2 = 0x66,
};

static ActivityBuffers *buffers(Activity *activity)
{
    return (ActivityBuffers *) (void *) activity;
}

/* The copy the activity writes (bits 4-7 of card_parts) and the one it read (bits 0-3). */
static int write_part(const Activity *activity)
{
    return activity->card_parts >> 4;
}

static int read_part(const Activity *activity)
{
    return activity->card_parts & 0xf;
}

static AcreMap *town_map(void)
{
    return (AcreMap *) (uintptr_t) AcreMap_Town();
}

/* The scenes that keep the card buffers and the letters. */
static int scene_has_card_buffers(int scene)
{
    return scene == SCENE_2E || scene == SCENE_06 || scene == SCENE_09 || scene == SCENE_0B;
}

/* func_020a48cc: job 5's steps: once talk 0 waits, the save's marks cleared, then its parts 0,
 * 1 and 2 erased; talk 0 closed and job 0xc started. */
void ActivityProcess_StepJob5(Activity *activity)
{
    int result;
    switch (activity->state) {
        case 0:
            if (ActivityTalk_FinishWaiting(activity, TALK_WAIT_NONE)) {
                activity->state = 1;
            }
            break;
        case 1:
            result = CardSave_WriteClearedMarks();
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 5;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 2;
            }
            break;
        case 2:
            result = ActivityCard_StepErasePart(activity, 0);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 5;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 3;
            }
            break;
        case 3:
            result = ActivityCard_StepErasePart(activity, 1);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 5;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 4;
            }
            break;
        case 4:
            result = ActivityCard_StepErasePart(activity, 2);
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
            ActivityProcess_StartJob(activity, JOB_0C);
            break;
    }
}
CLEAN_AS(func_020a48cc, ActivityProcess_StepJob5)

/* func_020a49a0: job 5 starts: message 12 of "sp_etc_sequence1" shown. */
void ActivityProcess_StartJob5(Activity *activity)
{
    ActivityTalk_Show(activity, data_020e3c54, SEQUENCE1_JOB5);
    activity->state = 0;
}
CLEAN_AS(func_020a49a0, ActivityProcess_StartJob5)

/* func_020a49bc: job 4's steps: once the object at data_021c779c + 0x20 is done (when
 * func_02042324 says it was not, until func_020422f8 says so), the card checked, then the copy
 * to write and the other copy written; talk 0 closed and job 0x10 started. */
void ActivityProcess_StepJob4(Activity *activity)
{
    int result;
    switch (activity->state) {
        case 0:
            activity->state = 1;
            break;
        case 1:
            if (func_02042324()) {
                activity->state = 2;
            } else {
                activity->state = 3;
            }
            break;
        case 2:
            if (func_020422f8()) {
                activity->state = 3;
            }
            break;
        case 3:
            result = ActivityCard_StepCheck(activity);
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 6;
            } else if (result != ACTIVITY_CARD_BUSY) {
                activity->state = 4;
            }
            break;
        case 4:
            result = ActivityCard_StepWritePart(activity, write_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 6;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 5;
            }
            break;
        case 5:
            result = ActivityCard_StepWritePart(activity, read_part(activity));
            if (result == ACTIVITY_CARD_FAILED) {
                activity->state = 6;
            } else if (result == ACTIVITY_CARD_DONE) {
                activity->state = 8;
            }
            break;
        case 6:
            ActivityTalk_QueueMessage10(activity);
            activity->state = 7;
            break;
        case 7:
            break;
        default:
            ActivityTalk_Close(activity);
            ActivityProcess_StartJob(activity, JOB_10);
            break;
    }
}
CLEAN_AS(func_020a49bc, ActivityProcess_StepJob4)

/* func_020a4aa0: job 4 starts at its first step. */
void ActivityProcess_StartJob4(Activity *activity)
{
    activity->state = 0;
}
CLEAN_AS(func_020a4aa0, ActivityProcess_StartJob4)

/* func_020a4aa8: job 3's steps, one a frame: once talk 0 waits the clock set up, the villagers
 * updated, the state block started anew, the object at data_021c779c + 0x20 made and the state
 * block's start finished; then job 4. */
void ActivityProcess_StepJob3(Activity *activity)
{
    switch (activity->state) {
        case 0:
            if (!ActivityTalk_FinishWaiting(activity, TALK_WAIT_NONE)) {
                break;
            }
            Clock_Init();
            activity->state++;
            break;
        case 1:
            VillagerTown_Update(&data_021e5a2c, 0);
            activity->state++;
            break;
        case 2:
            StateBlock_Start(&data_021dc7a8, STATE_BLOCK_MODE_NEW);
            activity->state++;
            break;
        case 3:
            func_02042458();
            activity->state++;
            break;
        case 4:
            StateBlock_FinishStart(&data_021dc7a8);
            activity->state++;
            break;
        default:
            ActivityProcess_StartJob(activity, JOB_4);
            break;
    }
}
CLEAN_AS(func_020a4aa8, ActivityProcess_StepJob3)

/* func_020a4b54: job 3 starts: message 0x28 of "sp_etc_sequence1" shown and the player's
 * options stored. */
void ActivityProcess_StartJob3(Activity *activity)
{
    ActivityTalk_Show(activity, data_020e3c54, SEQUENCE1_JOB3);
    PlayerOptions_Store();
    activity->state = 0;
}
CLEAN_AS(func_020a4b54, ActivityProcess_StartJob3)

/* The steps the jobs 1 and 2 share, before `next` starts: once talk 0 waits, when this
 * system's slot of the session is taken the link status reset and, when the Wi-Fi session
 * ends, the library overlay 68 switched; then the card checked and both copies written. */
static void step_end_and_save(Activity *activity, int next)
{
    int result;
    switch (activity->state) {
        case 0:
            if (ActivityTalk_FinishWaiting(activity, TALK_WAIT_NONE)) {
                NetSession *session = data_020ccf94;
                if (Session_IsSlotTaken(session, session->local_slot)) {
                    Session_ResetLinkStatus();
                    if (WfcSession_End(activity) != 0) {
                        LibraryOverlay_Switch68();
                    }
                }
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
            ActivityProcess_StartJob(activity, next);
            break;
    }
}

/* func_020a4b74: job 2's steps (step_end_and_save); then job 0xd. */
void ActivityProcess_StepJob2(Activity *activity)
{
    step_end_and_save(activity, JOB_0D);
}
CLEAN_AS(func_020a4b74, ActivityProcess_StepJob2)

/* The starts of the jobs 1 and 2: message `message` of file `name` shown, func_0206f74c, the
 * current player's flag 2 cleared and func_0204cdc8. */
static void start_end_and_save(Activity *activity, const char *name, int message)
{
    u8 *player = PlayerRecords_Current();
    ActivityTalk_Show(activity, name, (char) message);
    func_0206f74c();
    PlayerRecord_ClearFlag(player, PLAYER_FLAG_2);
    func_0204cdc8(data_021f39fc);
    activity->state = 0;
}

/* func_020a4c5c: job 2 starts, with message 0x66 of "sp_npc_gatekeeper". */
void ActivityProcess_StartJob2(Activity *activity)
{
    start_end_and_save(activity, data_020e3c2c, GATEKEEPER_JOB2);
}
CLEAN_AS(func_020a4c5c, ActivityProcess_StartJob2)

/* func_020a4c9c: job 1's steps (step_end_and_save); then job 0xc. */
void ActivityProcess_StepJob1(Activity *activity)
{
    step_end_and_save(activity, JOB_0C);
}
CLEAN_AS(func_020a4c9c, ActivityProcess_StepJob1)

/* func_020a4d84: job 1 starts, with message 1 of "sp_etc_sequence2". */
void ActivityProcess_StartJob1(Activity *activity)
{
    start_end_and_save(activity, data_020e3c40, SEQUENCE2_JOB1);
}
CLEAN_AS(func_020a4d84, ActivityProcess_StartJob1)

/* The job asked for started, and no job asked for any more. */
static void start_asked(Activity *activity)
{
    ActivityProcess_StartJob(activity, data_021f3c38);
    data_021f3c38 = JOB_NONE;
}

/* func_020a4dc4: job 0's step: with the screen shown, the job asked for started where it
 * belongs: 0x12 or 0x1f in scene 9, 0x13 in scene 0xb, 3 or 4 in scene 6, 0x14 in scene 0xc,
 * and whatever was asked in the scenes 0x2e, 0x2f and 0xd.
 * QUIRK: in the scenes 0x2e, 0x2f and 0xd the asked job is started every frame, job 0 (no job)
 * included, whose start does nothing. */
void ActivityProcess_StepJob0(Activity *activity)
{
    int scene = SceneQuery_Current();
    if (data_021c75b8 != SCREEN_SHOWN) {
        return;
    }
    if (scene == SCENE_09) {
        if (data_021f3c38 == JOB_12 || data_021f3c38 == JOB_1F) {
            start_asked(activity);
        }
    } else if (scene == SCENE_0B) {
        if (data_021f3c38 == JOB_13) {
            start_asked(activity);
        }
    } else if (scene == SCENE_06) {
        if (data_021f3c38 == 3 || data_021f3c38 == 4) {
            start_asked(activity);
        }
    } else if (scene == SCENE_2E) {
        start_asked(activity);
    }
    if (scene == SCENE_0C && data_021f3c38 == JOB_14) {
        start_asked(activity);
    }
    if (scene == SCENE_2F || scene == SCENE_0D) {
        start_asked(activity);
    }
}
CLEAN_AS(func_020a4dc4, ActivityProcess_StepJob0)

/* func_020a4e90: job 0's start, which does nothing. */
void ActivityProcess_StartJob0(void) {}
CLEAN_AS(func_020a4e90, ActivityProcess_StartJob0)

/* func_020a4e94: job `job` started: its start called, when it has one, and the job noted. */
void ActivityProcess_StartJob(Activity *activity, int job)
{
    const ActivityJobEntry *entry = &data_021f3ea4[job];
    if (entry->start.function != 0) {
        MemberPointer_CallVoid(&entry->start, activity);
    }
    activity->unk_50 = (u32) job;
}
CLEAN_AS(func_020a4e94, ActivityProcess_StartJob)

/* func_020a4ecc (vtable slot 6): a frame: the step of the job, when it has one; done. */
int ActivityProcess_Execute(Activity *activity)
{
    const ActivityJobEntry *entry = &data_021f3ea4[activity->unk_50];
    if (entry->step.function != 0) {
        MemberPointer_CallVoid(&entry->step, activity);
    }
    return 1;
}
CLEAN_AS(func_020a4ecc, ActivityProcess_Execute)

/* func_020a4f0c (vtable slot 3): the deletion: in scene 6 the villagers searched. Unless the
 * scene is 9 or 0xb of a linked session, the activity stops being the current one and its
 * buffers are freed: those of ActivityProcess_Create, the received state block (forgotten)
 * and the packing thread (stopped first, then forgotten). Done. */
int ActivityProcess_Delete(Activity *activity)
{
    ActivityBuffers *own = buffers(activity);
    int scene = SceneQuery_Current();

    if (scene == SCENE_06) {
        VillagerTown_SearchAll(&data_021e5a2c);
    }
    if (Session_IsLinked(data_020ccf94) && (scene == SCENE_0B || scene == SCENE_09)) {
        return 1;
    }
    data_021f3c3c = NULL;
    if (scene_has_card_buffers(scene)) {
        Heap_Free(own->heap, own->image);
        Heap_Free(own->heap, own->card);
        Heap_Free(own->heap, activity->letters);
    }
    if (scene == SCENE_09) {
        Heap_Free(own->heap, own->scene9_block);
    }
    if (data_021f3c24 != NULL) {
        Heap_Free(own->heap, data_021f3c24);
        data_021f3c24 = NULL;
    }
    if (activity->pack_thread != NULL) {
        TownPack_KillThread(activity->pack_thread);
        Heap_Free(own->heap, activity->pack_thread);
        activity->pack_thread = NULL;
    }
    if (activity->pack_buffer != NULL) {
        Heap_Free(own->heap, activity->pack_buffer);
    }
    if (scene == SCENE_2E) {
        Heap_Free(own->heap, activity->block_copy);
        Heap_Free(own->heap, activity->exchange_block);
    }
    return 1;
}
CLEAN_AS(func_020a4f0c, ActivityProcess_Delete)

/* func_020a503c (vtable slot 0): the creation. In scene 6 the town map's and the rooms' models
 * and data set up first. In the scenes 9 and 0xb of a linked session nothing more is done
 * (0: not created yet). Else the activity becomes the current one, owns its receiver and takes
 * the current heap, from which it allocates: in the scenes 0x2e, 6, 9 and 0xb both card
 * buffers and the letters, read from the card (cleared when not ready or their sum is wrong,
 * then marked ready); in scene 9 its own block; in scene 0x2e the copy of the state block and
 * an exchange block; for the jobs 0x14 and 0x15 the packing buffer and thread (set up); for
 * job 0x14 the received state block (its stamp cleared). Done. */
int ActivityProcess_Create(Activity *activity)
{
    ActivityBuffers *own = buffers(activity);
    int scene = SceneQuery_Current();

    if (scene == SCENE_06) {
        if (AcreMap_Town() != 0) {
            AcreMap_SetTownModels(town_map());
            AcreMap_LoadTownData(town_map());
            func_0204d0ac(town_map());
        }
        AcreMap_SetRoomsModels();
        AcreMap_LoadRoomsData();
    }
    data_021f3c08 = 0;
    if (Session_IsLinked(data_020ccf94) && (scene == SCENE_0B || scene == SCENE_09)) {
        return 0;
    }
    data_021f3c3c = activity;
    ActivityReceiver_SetOwner((ActivityReceiver *) (void *) activity->receiver, activity);
    own->heap = data_021fbe94;
    if (scene_has_card_buffers(scene)) {
        u8 *letters;
        int sum;
        own->image = Heap_Alloc(own->heap, sizeof(StateBlock));
        own->card = Heap_Alloc(own->heap, sizeof(StateBlock));
        activity->letters = Heap_Alloc(own->heap, LETTERS_SIZE);
        ActivityCard_LoadPart(CARD_PART_LETTERS);
        letters = Activity_CurrentLetters();
        sum = BackupCard_Sum((unsigned short *) (void *) letters, LETTERS_SIZE);
        if (LetterStore_IsBlockReady(letters) == 0 || sum != 0) {
            MI_CpuFill8(letters, 0, LETTERS_SIZE);
        }
        LetterStore_MarkBlockReady(letters);
    }
    if (scene == SCENE_09) {
        own->scene9_block = Heap_Alloc(own->heap, SCENE9_BLOCK_SIZE);
    }
    if (scene == SCENE_2E) {
        activity->block_copy = Heap_Alloc(own->heap, sizeof(StateBlock));
        activity->exchange_block = Heap_Alloc(own->heap, EXCHANGE_BLOCK_SIZE);
    }
    if (data_021f3c38 == JOB_14 || data_021f3c38 == JOB_15) {
        activity->pack_buffer = Heap_Alloc(own->heap, PACK_BUFFER_SIZE);
        activity->pack_thread = Heap_Alloc(own->heap, PACK_THREAD_SIZE);
        TownPack_InitThread(activity->pack_thread);
    }
    if (data_021f3c38 == JOB_14) {
        data_021f3c24 = Heap_Alloc(own->heap, sizeof(StateBlock));
        SaveStamp_Clear((SaveStamp *) (void *) data_021f3c24->part_173f8);
    }
    return 1;
}
CLEAN_AS(func_020a503c, ActivityProcess_Create)

/* func_020a5210: an activity made (0x110 bytes, zeroed, from the auxiliary heap): constructed
 * as a process with its class's vtable, its receiver constructed and its date and time
 * cleared; NULL when there is no room. */
Activity *ActivityProcess_New(void)
{
    Activity *activity = Heap_AllocAuxZeroed(ACTIVITY_SIZE);
    if (activity != NULL) {
        Process_Construct(&activity->process);
        activity->process.vtable = data_020da13c;
        activity->process.vtable = data_020e3ae8;
        ActivityReceiver_Construct((ActivityReceiver *) (void *) activity->receiver);
        memset(activity->date_time, 0, sizeof(activity->date_time));
    }
    return activity;
}
CLEAN_AS(func_020a5210, ActivityProcess_New)
