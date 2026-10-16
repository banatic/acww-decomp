/* The process of a scene on the field, and process class 3 (scene_process.h). */
#include "scene_process.h"

#include "clean.h"
#include "main/actor_table.h"
#include "main/bg_models.h"
#include "main/block_02034858.h"
#include "main/design_assets.h"
#include "main/display_frame.h"
#include "main/furniture_info.h"
#include "main/music_queue.h"
#include "main/overlay_slots.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/quick_message.h"
#include "main/resource_pools.h"
#include "main/scene_claim.h"
#include "main/scene_display.h"
#include "main/scene_kinds.h"
#include "main/scene_place.h"
#include "main/scene_query.h"
#include "main/scene_setup.h"
#include "main/scene_sound.h"
#include "main/scene_tables.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/shadow.h"
#include "main/shops.h"
#include "ov004/member_pointer.h"

static_assert(offsetof(SceneInfo, overlays) == 0x10, "overlays");
static_assert(sizeof(SceneInfo) == 0x18, "scene info");

#define REG16(addr) (*(volatile u16 *) (uintptr_t) (addr))
#define REG_BG0CNT 0x04000008u
#define BGCNT_PRIORITY 3u
/* The first background's priority while a scene runs. */
#define SCENE_PROCESS_BG0_PRIORITY 2u

/* The creation's steps (data_021f42f0 is 1-6 while they run) and a frame's budget for them,
 * in milliseconds (the ticks run at 33.514 MHz / 64). */
#define SCENE_PROCESS_STEPS 6
#define SCENE_PROCESS_BUDGET_MS 40
/* What the creation answers: done, or to be called again. */
#define SCENE_PROCESS_CREATED 1
#define SCENE_PROCESS_NOT_CREATED (-1)
/* The overlay every scene on the field needs, and the overlay ids' "none". */
#define SCENE_PROCESS_COMMON_OVERLAY 2
#define SCENE_PROCESS_NO_OVERLAY (-1)
/* The VBlanks a frame takes while a scene runs (itcm/interrupts.c). */
#define SCENE_PROCESS_FRAME_VBLANKS 3
/* SceneInfo's flag for a field loaded whole. */
#define SCENE_PROCESS_FULL 1
/* The players of a session, and "no player" in its numbers. */
#define SCENE_PROCESS_PLAYERS 4
#define SCENE_PROCESS_NO_PLAYER 4
/* data_021c75b8 while the player may steer. */
#define SCENE_PROCESS_STEERING 2
/* The link value of data_021f4320 the scenes 0x0c-0x0e, 0x2e and 0x2f set, and the one the
 * end of scene 0x0e leaves. */
#define SCENE_PROCESS_LINK_IDLE 4
/* Scenes the code below tests. */
#define SCENE_PROCESS_SCENE_0C 0x0c
#define SCENE_PROCESS_SCENE_0D 0x0d
#define SCENE_PROCESS_SCENE_0E 0x0e
#define SCENE_PROCESS_SCENE_2C 0x2c
#define SCENE_PROCESS_SCENE_2D 0x2d
#define SCENE_PROCESS_SCENE_2E 0x2e
#define SCENE_PROCESS_SCENE_2F 0x2f
/* In scene 0x0e the link's player number 1-3 has record 3 above it. */
#define SCENE_PROCESS_LINK_PLAYER_FIRST 1
#define SCENE_PROCESS_LINK_PLAYER_LAST 3
#define SCENE_PROCESS_LINK_RECORD_OFFSET 3

/* The vtables: class 6's, class 3's, the scene base class's and the root class's. */
extern const u32 data_020e5574[];
extern const u32 data_020e5764[];
extern const u32 data_020e3c94[];
extern const u32 data_020da13c[];

/* The creation's table of member pointers (filled once, bit 0 of the guard) and its
 * constants; and the step reached (the scene base's). */
extern u32 data_021f6930;
extern MemberPointer data_021f6a3c[SCENE_PROCESS_STEPS];
extern const MemberPointer data_020e54c4; /* SceneProcess_Enter */
extern const MemberPointer data_020e54cc; /* SceneProcess_SetUpPlayers */
extern const MemberPointer data_020e54d4; /* SceneProcess_LoadResources */
extern const MemberPointer data_020e54e4; /* SceneProcess_SpawnSetupEnd */
extern const MemberPointer data_020e54fc; /* SceneProcess_RunSetup */
extern const MemberPointer data_020e54dc; /* SceneProcess_Finish */
extern u8 data_021f42f0;

/* The running scene, NULL between scenes; the step and item its setup has reached. */
extern SceneInfo *data_021f6948;
extern u8 data_021f42dc;
extern u8 data_021f42e4;
/* Each scene's SceneInfo, mode and own overlay (-1 for none); each mode's overlay. */
extern SceneInfo *data_020e55bc[];
extern const u8 data_020e5538[];
extern const s32 data_020e5688[];
extern const u32 data_020e54f4[2];
/* The overlays loaded: the SceneInfo's two, the mode's and the scene's own (-1 for none). */
extern s32 data_020e54b4;
extern s32 data_020e54bc;
extern s32 data_020e54b8;
extern s32 data_020e54c0;
/* The scene whose overlays are loaded. */
extern s32 data_021f6944;
/* The current and the previous scene, and the mode. */
extern u8 data_020e54ac;
extern u8 data_020e54b0;
extern u8 data_020e54a8;
/* Main's entry record (scene_exit.h). */
extern SceneExit data_021f69d0;
/* The running scene's display hooks, and the ones a scene on the field runs with. */
extern DisplayFrameHooks *data_021c8ca0;
extern DisplayFrameHooks data_021f693c;
/* The session, and the heap the resource loaders are given. */
extern NetSession *data_020ccf94;
extern Heap *data_021fbe94;
/* The VBlanks a frame takes. */
extern int data_020dd828;
/* 2 while the player may steer; set when a change of scene is asked for otherwise. */
extern u8 data_021c75b8;
extern u8 data_021c75b0;
/* The touch screen: the pen is down, and the touch's x and y. */
extern u8 data_021fbdd8;
extern u16 data_021fbde0;
extern u16 data_021fbde4;
/* Cleared when a scene starts. */
extern u8 data_021f692c;
/* Cleared when a scene starts and ends. */
extern s32 data_021d3124;

extern u64 OS_GetTick(void);
extern void NNS_G3dGeFlushBuffer(void);
/* The field object's (SceneQuery_FieldObject) reset, at the end and the start of a scene. */
extern void func_020b7e6c(void *field);
extern void func_020b7e84(void *field);
/* The pen on the field: the field object, the touch's x and y, whether the pen is down. */
extern void func_020b75b8(int field, unsigned char x, unsigned char y, int down);
/* The drawing's last step. */
extern void func_02089ce0(void);
/* A value of the link (data_021f4320) and setting it; the player number it keeps, and
 * setting that. */
extern int func_020a6ee0(void);
extern void func_020a6ef0(int value);
extern int func_020a6ed0(void);
extern void func_020a6ec0(int value);
/* The link's work of a frame the scene base also does when its creation ends. */
extern void func_020a6c08(void);
extern void func_02046600(void);
/* A session player's record number (7 for none) and setting it, freeing it; and the byte
 * kept for each player at 0x14 of the same table (data_021d5684). */
extern u8 func_02096284(int player);
extern void func_020962a4(int player, int record);
extern void func_02096294(int player);
extern void func_020961f0(int player, int value);
/* Calls at the start (and end) of a scene whose work is elsewhere. */
extern void func_02041a9c(void);
extern void func_0203f070(void);
extern void func_0208f8fc(void);
extern void func_02030dcc(void);
extern void func_0208a0a0(void);
extern void func_0208a0ac(void);
extern void func_02091300(void);
extern void func_0203ecac(void);
extern void func_02062ae4(int full);
extern int func_02062ad4(void);
/* The field's resource loaders, given the current heap, and their releases. */
extern void func_0205cf84(Heap *heap);
extern void func_0205d724(Heap *heap);
extern void func_0205dd98(Heap *heap);
extern void func_0205db10(Heap *heap);
extern void func_0205dc58(Heap *heap);
extern void func_0205f820(Heap *heap);
extern void func_0205d234(Heap *heap);
extern void func_0205e8b0(Heap *heap);
extern void func_0205f9ac(Heap *heap);
extern void func_0205e0f0(Heap *heap);
extern void func_0205f6f8(Heap *heap);
extern void func_0206094c(Heap *heap);
extern void func_0205c1a4(Heap *heap);
extern void func_0205c188(void);
extern void func_02060934(void);
extern void func_0205f6dc(void);
extern void func_0205f994(void);
extern void func_0205e0d8(void);
extern void func_0205e898(void);
extern void func_0205d21c(void);
extern void func_0205f808(void);
extern void func_0205dc40(void);
extern void func_0205daf8(void);
extern void func_0205dd80(void);
extern void func_0205d70c(void);
extern void func_0205cf6c(void);

/* ---- Process class 6 */

/* func_020b6a28 (slot 12): nothing. */
void SceneProcess_Slot12(void) {}
CLEAN_AS(func_020b6a28, SceneProcess_Slot12)

/* func_020b6a2c (slot 9): the drawing: the fog applied and the geometry flushed, the pen
 * handled on the field, then the drawing's last steps; done. */
int SceneProcess_Draw(void *process)
{
    SceneDisplay_ApplyFog(process);
    NNS_G3dGeFlushBuffer();
    int field = SceneQuery_FieldObject();
    int down = data_021fbdd8 != 0;
    func_020b75b8(field, (unsigned char) data_021fbde0, (unsigned char) data_021fbde4, down);
    Block02034858_AfterDraw();
    func_02089ce0();
    return 1;
}
CLEAN_AS(func_020b6a2c, SceneProcess_Draw)

/* func_020b6a7c (slot 6): each frame, while the player may steer or once data_021c75b0 is
 * set, the change of scene asked for (SceneExit_RequestChange, with the entry record's two
 * bytes) when main's entry record names a scene; always 1. */
int SceneProcess_Update(int unused)
{
    (void) unused;
    func_02030dcc();
    func_0208a0a0();
    if (data_021c75b8 != SCENE_PROCESS_STEERING && data_021c75b0 == 0) {
        return 1;
    }
    if (ScenePlace_IsScene((unsigned int) SceneExit_Scene(&data_021f69d0)) != 0) {
        int change_arg = SceneExit_ChangeArg((const SceneExit *) (uintptr_t) SceneTables_EntryRecord());
        int next_arg = SceneExit_NextArg((const SceneExit *) (uintptr_t) SceneTables_EntryRecord());
        SceneExit_RequestChange(change_arg, next_arg);
    }
    return 1;
}
CLEAN_AS(func_020b6a7c, SceneProcess_Update)

/* func_020b6ae0 (slot 3): the scene's end: its music told, the field object reset, the
 * display hooks cleared, the field's resources released in turn and the display taken down.
 * Then the session's players' record numbers for the next scene: after scene 6 player 0 takes
 * this system's player's number (which becomes 0) and the others are freed; after scene 7
 * players 3, 2 and 1 are freed; after scene 0x0e the link's player number, when 1-3, has its
 * record (3 above it) cleared and its number freed, and the link's number becomes 4. Last
 * the overlays are released, the running scene cleared and the mode is 2; done. */
int SceneProcess_End(void)
{
    Music_OnSceneEnd();
    func_020b7e6c((void *) (uintptr_t) SceneQuery_FieldObject());
    data_021c8ca0 = NULL;
    func_0205c188();
    PoolLink_FreeAllAtSceneEnd();
    ResourcePools_Shutdown();
    Actors_Init();
    func_02060934();
    func_0205f6dc();
    func_0205f994();
    func_0205e0d8();
    func_0205e898();
    func_0205d21c();
    func_0205f808();
    func_0205dc40();
    func_0205daf8();
    func_0205dd80();
    func_0205d70c();
    func_0205cf6c();
    DesignManager_Shutdown((DesignManager *) (uintptr_t) DesignManager_Get());
    FurnitureInfo_FreeIndoor();
    func_02062ad4();
    CharaShadow_Unload();
    ObjShadow_FreeAll();
    BgModels_Release((BgModels *) (uintptr_t) BgModels_Get());
    SceneDisplay_TearDown();
    data_021d3124 = 0;

    if (SceneQuery_Current() == SCENE_KINDS_SESSION_FIRST) {
        NetSession *session = data_020ccf94;
        for (int player = 0; player < SCENE_PROCESS_PLAYERS; player++) {
            if (player == 0) {
                func_020962a4(0, session->local_player);
                session->local_player = 0;
            } else {
                func_02096294(player);
            }
        }
    } else if (SceneQuery_Current() == SCENE_KINDS_SESSION_SECOND) {
        for (int player = SCENE_PROCESS_PLAYERS - 1; player >= 1; player--) {
            func_02096294(player);
        }
    } else if (SceneQuery_Current() == SCENE_PROCESS_SCENE_0E) {
        int player = func_020a6ed0();
        if (player >= SCENE_PROCESS_LINK_PLAYER_FIRST && player <= SCENE_PROCESS_LINK_PLAYER_LAST) {
            u8 *record = PlayerRecords_Get(player + SCENE_PROCESS_LINK_RECORD_OFFSET);
            if (record != NULL) {
                PlayerRecord_Clear(record);
            }
            func_02096294(player);
        }
        func_020a6ec0(SCENE_PROCESS_LINK_IDLE);
    }

    SceneProcess_ReleaseOverlays();
    data_021f6948 = NULL;
    SceneProcess_ReleaseCommonOverlay();
    data_020e54a8 = SCENE_MODE_NONE;
    return 1;
}
CLEAN_AS(func_020b6ae0, SceneProcess_End)

/* Whether more than the frame's budget has passed since `start`. */
static int scene_process_over_budget(u64 start)
{
    return (u32) ((OS_GetTick() - start) * 64 / 33514) > SCENE_PROCESS_BUDGET_MS;
}

/* A creation step: the member pointer's function called with the process and the frame's
 * start; whether the step is done. */
static int scene_process_run_step(const MemberPointer *step, void *process, u64 start)
{
    void *self = MemberPointer_Object(step, process);
    return ((int (*)(void *, u64))(uintptr_t) MemberPointer_Code(step, self))(self, start);
}

/* func_020b6c0c (slot 0): the creation: the steps from the one reached (data_021f42f0) on, in
 * turn, through the table of member pointers (filled from its constants the first time). 1
 * once the last is done (or the step reached is not 1-6); -1 when a step is not done or the
 * frame's 40 ms are spent with steps left, after the link's work of the frame (Session_Deliver,
 * func_020a6c08, func_02046600). */
int SceneProcess_Create(Process *process)
{
    static const MemberPointer *const steps[SCENE_PROCESS_STEPS] = {
        &data_020e54c4, /* SceneProcess_Enter */
        &data_020e54cc, /* SceneProcess_SetUpPlayers */
        &data_020e54d4, /* SceneProcess_LoadResources */
        &data_020e54e4, /* SceneProcess_SpawnSetupEnd */
        &data_020e54fc, /* SceneProcess_RunSetup */
        &data_020e54dc, /* SceneProcess_Finish */
    };
    MemberTable_InitOnce(&data_021f6930, data_021f6a3c, steps, SCENE_PROCESS_STEPS);

    u64 start = OS_GetTick();
    int stopped = 0;
    for (;;) {
        unsigned int index = (unsigned int) data_021f42f0 - 1;
        if (index >= SCENE_PROCESS_STEPS) {
            break;
        }
        if (scene_process_run_step(&data_021f6a3c[index], process, start) == 0) {
            stopped = 1;
            break;
        }
        data_021f42f0++;
        if (data_021f42f0 > SCENE_PROCESS_STEPS) {
            break;
        }
        if (scene_process_over_budget(start)) {
            stopped = 1;
            break;
        }
    }
    if (stopped) {
        Session_Deliver(0);
        func_020a6c08();
        func_02046600();
        return SCENE_PROCESS_NOT_CREATED;
    }
    return SCENE_PROCESS_CREATED;
}
CLEAN_AS(func_020b6c0c, SceneProcess_Create)

/* func_020b6d20 (step 6): the fog reset, the first background's priority 2, main's entry
 * record cleared, three VBlanks a frame, the quick messages dismissed in scenes 0x2e, 0x0d
 * and 0x2f, and the scene's music started; done.
 * HW: BG0CNT is read and written between func_02091300 and func_0208a0ac. */
int SceneProcess_Finish(void *process)
{
    SceneDisplay_ResetFog(process);
    func_02091300();
    REG16(REG_BG0CNT) = (u16) ((REG16(REG_BG0CNT) & ~BGCNT_PRIORITY) | SCENE_PROCESS_BG0_PRIORITY);
    func_0208a0ac();
    data_021d3124 = 0;
    SceneExit_Clear(&data_021f69d0);
    data_020dd828 = SCENE_PROCESS_FRAME_VBLANKS;
    func_0203ecac();
    if (SceneQuery_Current() == SCENE_PROCESS_SCENE_2E || SceneQuery_Current() == SCENE_PROCESS_SCENE_0D ||
        SceneQuery_Current() == SCENE_PROCESS_SCENE_2F) {
        QuickMessage_DismissAll();
    }
    Music_OnSceneStart();
    return 1;
}
CLEAN_AS(func_020b6d20, SceneProcess_Finish)

/* func_020b6d8c (step 5): the scene's setup run on from the step and item reached.
 * QUIRK: declared without a result; in the ROM SceneSetup_Run's answer (whether the setup is
 * done) is still in r0 when it returns, and SceneProcess_Create reads it as the step's. */
void SceneProcess_RunSetup(int unused, u64 start)
{
    (void) unused;
    SceneSetup_Run((SceneSetup *) (void *) data_021f6948, &data_021f42dc, &data_021f42e4, start);
}
CLEAN_AS(func_020b6d8c, SceneProcess_RunSetup)

/* func_020b6db4 (step 4): the scene's setup end object made (SceneSetup_End); done. */
int SceneProcess_SpawnSetupEnd(void)
{
    SceneSetup_End((SceneSetup *) (void *) data_021f6948);
    return 1;
}
CLEAN_AS(func_020b6db4, SceneProcess_SpawnSetupEnd)

/* Whether the running scene's field is loaded whole (read again at each use). */
static int scene_process_full(void)
{
    return (u8) data_021f6948->base.setup.unk_04 == SCENE_PROCESS_FULL;
}

/* func_020b6dcc (step 3): the field's resources loaded in turn (the background models, the
 * indoor furniture, the designs, the loaders given the current heap, the shadows, the pools
 * and the actors), the scene claim left; in scenes 0x2c and 0x2d the marked place reset; then
 * the shops' pending changes applied; done. */
int SceneProcess_LoadResources(void)
{
    int bg_models = BgModels_Get();
    BgModels_SetUp((BgModels *) (uintptr_t) bg_models, scene_process_full());
    FurnitureInfo_LoadIndoor((void *) (uintptr_t) scene_process_full());
    func_02062ae4(scene_process_full());
    DesignManager_Startup((DesignManager *) (uintptr_t) DesignManager_Get());
    func_0205cf84(data_021fbe94);
    func_0205d724(data_021fbe94);
    func_0205dd98(data_021fbe94);
    func_0205db10(data_021fbe94);
    func_0205dc58(data_021fbe94);
    func_0205f820(data_021fbe94);
    func_0205d234(data_021fbe94);
    func_0205e8b0(data_021fbe94);
    func_0205f9ac(data_021fbe94);
    func_0205e0f0(data_021fbe94);
    func_0205f6f8(data_021fbe94);
    func_0206094c(data_021fbe94);
    ObjShadow_LoadAll(scene_process_full());
    CharaShadow_Load();
    ResourcePools_Startup();
    PoolLink_FreeAllAtSceneStart();
    Actors_Init();
    func_0205c1a4(data_021fbe94);
    SceneClaim_Leave();
    if (SceneQuery_Current() == SCENE_PROCESS_SCENE_2C || SceneQuery_Current() == SCENE_PROCESS_SCENE_2D) {
        (void) SceneTables_EntryRecord();
        ScenePlace_ResetMarked();
    }
    Shops_ApplyPending();
    return 1;
}
CLEAN_AS(func_020b6dcc, SceneProcess_LoadResources)

/* func_020b6ed4 (step 2): the display set up and the scene's sound made; then the session's
 * players. When this system has a slot of the session, every player's byte at 0x14 is 4.
 * Otherwise in scenes 6 and 7 the session has four players, each with its own number there;
 * elsewhere one player and 4 for all. Then in scene 6 this system's player is 4 and players
 * 3-0 take the record numbers 3-0; in scene 7 the players other than this system's take, from
 * player 3 down, the numbers from 0 up, leaving out this system's player's own; outside scenes
 * 6 and 7, in scene 0x2c, the session's slot and player are 4 and the players' numbers freed
 * (from player 3 down); done. */
int SceneProcess_SetUpPlayers(void)
{
    SceneDisplay_SetUp();
    func_02041a9c();
    func_0208f8fc();
    SceneSound_Create();

    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) != 0) {
        for (int player = 0; player < SCENE_PROCESS_PLAYERS; player++) {
            func_020961f0(player, SCENE_PROCESS_NO_PLAYER);
        }
    } else if (SceneKinds_CurrentIsSession() != 0) {
        Session_SetPlayerCount(session, SCENE_PROCESS_PLAYERS);
        for (int player = 0; player < SCENE_PROCESS_PLAYERS; player++) {
            func_020961f0(player, player);
        }
    } else {
        Session_SetPlayerCount(session, 1);
        for (int player = 0; player < SCENE_PROCESS_PLAYERS; player++) {
            func_020961f0(player, SCENE_PROCESS_NO_PLAYER);
        }
    }

    if (SceneKinds_CurrentIsSession() != 0) {
        if (SceneQuery_Current() == SCENE_KINDS_SESSION_FIRST) {
            session->local_player = SCENE_PROCESS_NO_PLAYER;
            for (int player = SCENE_PROCESS_PLAYERS - 1; player >= 0; player--) {
                func_020962a4(player, player);
            }
        } else if (SceneQuery_Current() == SCENE_KINDS_SESSION_SECOND) {
            int local = session->local_player;
            int own_record = func_02096284(local);
            int record = 0;
            for (int player = SCENE_PROCESS_PLAYERS - 1; player >= 0; player--) {
                if (player == local) {
                    continue;
                }
                if (record == own_record) {
                    record++;
                }
                func_020962a4(player, record);
                record++;
            }
        }
    } else if (SceneQuery_Current() == SCENE_PROCESS_SCENE_2C) {
        NetSession *now = data_020ccf94;
        now->local_slot = SCENE_PROCESS_NO_PLAYER;
        now->local_player = SCENE_PROCESS_NO_PLAYER;
        for (int player = SCENE_PROCESS_PLAYERS - 1; player >= 0; player--) {
            func_02096294(player);
        }
    }
    return 1;
}
CLEAN_AS(func_020b6ed4, SceneProcess_SetUpPlayers)

/* func_020b6fd0 (step 1): in scenes 0x2e, 0x0d, 0x0c, 0x0e and 0x2f the link's value set to 4
 * when it is not; the scene of main's entry record becomes the current one (the current one the
 * previous); overlay 2 loaded, the display hooks set, the field object reset, the mode's and the
 * scene's overlays loaded, then the scene's SceneInfo made the running one and its overlays
 * loaded; done. */
int SceneProcess_Enter(void)
{
    func_02041a9c();
    u8 scene = data_020e54ac;
    int link = func_020a6ee0();
    if (scene == SCENE_PROCESS_SCENE_2E || scene == SCENE_PROCESS_SCENE_0D || scene == SCENE_PROCESS_SCENE_0C ||
        scene == SCENE_PROCESS_SCENE_0E || scene == SCENE_PROCESS_SCENE_2F) {
        if (link != SCENE_PROCESS_LINK_IDLE) {
            func_020a6ef0(SCENE_PROCESS_LINK_IDLE);
        }
    }
    func_0203f070();
    data_020e54b0 = data_020e54ac;
    data_020e54ac = (u8) SceneExit_Scene(&data_021f69d0);
    SceneProcess_LoadCommonOverlay();
    data_021c8ca0 = &data_021f693c;
    func_020b7e84((void *) (uintptr_t) SceneQuery_FieldObject());
    data_021f692c = 0;
    data_021f6944 = data_020e54ac;
    SceneProcess_LoadModeOverlays();
    SceneInfo *info = data_020e55bc[data_020e54ac];
    data_021f6948 = info;
    SceneProcess_LoadInfoOverlays(info);
    return 1;
}
CLEAN_AS(func_020b6fd0, SceneProcess_Enter)

/* Overlay `*loaded` released and marked none, when one is loaded. */
static void scene_process_release(s32 *loaded)
{
    if (*loaded != SCENE_PROCESS_NO_OVERLAY) {
        OverlaySlots_Release((u8) *loaded);
        *loaded = SCENE_PROCESS_NO_OVERLAY;
    }
}

/* func_020b70e8: the SceneInfo's overlays released, then the scene's own and the mode's. */
void SceneProcess_ReleaseOverlays(void)
{
    SceneProcess_ReleaseInfoOverlays();
    scene_process_release(&data_020e54c0);
    scene_process_release(&data_020e54b8);
}
CLEAN_AS(func_020b70e8, SceneProcess_ReleaseOverlays)

/* func_020b7130: the overlay of the scene's mode loaded and the mode set, then the scene's own
 * overlay when it has one. */
void SceneProcess_LoadModeOverlays(void)
{
    u8 mode = data_020e5538[data_021f6944];
    u32 overlay = data_020e54f4[mode];
    OverlaySlots_Load((u8) overlay);
    data_020e54b8 = (s32) overlay;
    data_020e54a8 = mode;
    if (data_020e5688[data_021f6944] != SCENE_PROCESS_NO_OVERLAY) {
        OverlaySlots_Load((u8) data_020e5688[data_021f6944]);
        data_020e54c0 = data_020e5688[data_021f6944];
    }
}
CLEAN_AS(func_020b7130, SceneProcess_LoadModeOverlays)

/* func_020b7198: the SceneInfo's two overlays released. */
void SceneProcess_ReleaseInfoOverlays(void)
{
    scene_process_release(&data_020e54b4);
    scene_process_release(&data_020e54bc);
}
CLEAN_AS(func_020b7198, SceneProcess_ReleaseInfoOverlays)

/* func_020b71dc: the two overlays `info` names noted, then loaded (those that are not none). */
void SceneProcess_LoadInfoOverlays(SceneInfo *info)
{
    s32 first = info->overlays[0];
    data_020e54b4 = first;
    data_020e54bc = info->overlays[1];
    if (first != SCENE_PROCESS_NO_OVERLAY) {
        OverlaySlots_Load((u8) first);
    }
    if (data_020e54bc != SCENE_PROCESS_NO_OVERLAY) {
        OverlaySlots_Load((u8) data_020e54bc);
    }
}
CLEAN_AS(func_020b71dc, SceneProcess_LoadInfoOverlays)

/* func_020b7218 */
void SceneProcess_ReleaseCommonOverlay(void)
{
    OverlaySlots_Release(SCENE_PROCESS_COMMON_OVERLAY);
}
CLEAN_AS(func_020b7218, SceneProcess_ReleaseCommonOverlay)

/* func_020b7228 */
void SceneProcess_LoadCommonOverlay(void)
{
    OverlaySlots_Load(SCENE_PROCESS_COMMON_OVERLAY);
}
CLEAN_AS(func_020b7228, SceneProcess_LoadCommonOverlay)

/* The scene base class's part of a construction: its vtable after the root class's, and flags
 * 1 and 4 set. */
static void scene_process_construct_scene(Process *process)
{
    process->vtable = data_020da13c;
    process->vtable = data_020e3c94;
    process->flags |= PROCESS_EXECUTE_STOPPED;
    process->flags |= PROCESS_DRAW_STOPPED;
}

/* A process of the class with `vtable`, zeroed and constructed; NULL when there is no memory. */
static Process *scene_process_new(const u32 *vtable)
{
    Process *process = Heap_AllocAuxZeroed(sizeof(Process));
    if (process != NULL) {
        Process_Construct(process);
        scene_process_construct_scene(process);
        process->vtable = vtable;
    }
    return process;
}

/* func_020b7238 (the profile's create): a new process of class 6. */
Process *SceneProcess_New(void)
{
    return scene_process_new(data_020e5574);
}
CLEAN_AS(func_020b7238, SceneProcess_New)

/* ---- Process class 3 */

/* A destructor's vtables in turn (the class's, the scene base class's, the root class's), then
 * the process destructor. */
static void scene_class3_destruct(Process *process)
{
    process->vtable = data_020e5764;
    process->vtable = data_020e3c94;
    process->vtable = data_020da13c;
    Process_Destruct(process);
}

/* func_020b727c (slot 16): the destructor. */
Process *SceneClass3_Destruct(Process *process)
{
    scene_class3_destruct(process);
    return process;
}
CLEAN_AS(func_020b727c, SceneClass3_Destruct)

/* func_020b72a4 (slot 17): destroyed and freed. */
Process *SceneClass3_Delete(Process *process)
{
    scene_class3_destruct(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_020b72a4, SceneClass3_Delete)

/* func_020b72d4 (slot 12): nothing. */
void SceneClass3_Slot12(void) {}
CLEAN_AS(func_020b72d4, SceneClass3_Slot12)

/* func_020b72d8 (slot 9): done. */
int SceneClass3_Draw(void)
{
    return 1;
}
CLEAN_AS(func_020b72d8, SceneClass3_Draw)

/* func_020b72dc (slot 6): done. */
int SceneClass3_Update(void)
{
    return 1;
}
CLEAN_AS(func_020b72dc, SceneClass3_Update)

/* func_020b72e0 (slot 3): done. */
int SceneClass3_End(void)
{
    return 1;
}
CLEAN_AS(func_020b72e0, SceneClass3_End)

/* func_020b72e4 (slot 0): the scene's sound made; done. */
int SceneClass3_Init(void)
{
    SceneSound_Create();
    return 1;
}
CLEAN_AS(func_020b72e4, SceneClass3_Init)

/* func_020b72f4 (the profile's create): a new process of class 3. */
Process *SceneClass3_New(void)
{
    return scene_process_new(data_020e5764);
}
CLEAN_AS(func_020b72f4, SceneClass3_New)
