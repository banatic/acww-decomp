/* Behaviours 2, 3, 4 and 12 of a villager out walking in the town: its house
 * (outdoor_villager_home.h). */
#include "outdoor_villager_home.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/footsteps.h"
#include "main/main_random.h"
#include "main/path_walker.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/session_players.h"
#include "main/speaker_anim.h"
#include "main/villager_entry.h"
#include "main/villager_furniture.h"
#include "main/villager_home.h"
#include "main/villager_mood.h"
#include "main/villager_scene_held.h"
#include "main/villager_scene_object.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "ov004/member_pointer.h"
#include "outdoor_villager.h"
#include "outdoor_villager_walks.h"
#include "outdoor_villager_watch.h"

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;

/* Overlay 3: the house of the villager of index `index` (the actor of character 0x5001 +
 * index) asked to let it out (02220318) or in (02220340); nonzero once it does. */
extern int func_ov003_02220318(int index);
extern int func_ov003_02220340(int index);
/* The held item shown at once: the held item link takes it, scale 1.0, the byte at 0x9f0 set
 * (nothing without a held item). */
void OutdoorVillagerObject_ShowHeldItem(u8 *villager);

/* The draw hook behaviour 4 sets (OutdoorVillagerObject_DrawWithItem: the villager drawn with its held item
 * link). */
extern const MemberPointer data_ov068_02276f50;

/* The updates' step tables (each filled once, bit 0 of its guard), and the member pointers
 * they are filled from. */
extern u32 data_ov068_02278290;
extern MemberPointer data_ov068_022782ec[2];
extern const MemberPointer data_ov068_02276e78, data_ov068_02276e88;
extern u32 data_ov068_022782b0;
extern MemberPointer data_ov068_022782dc[2];
extern const MemberPointer data_ov068_02276f70, data_ov068_02276e60;
extern u32 data_ov068_02278284;
extern MemberPointer data_ov068_022782cc[2];
extern const MemberPointer data_ov068_02276f90, data_ov068_02276f88;
extern u32 data_ov068_02278270;
extern MemberPointer data_ov068_0227837c[3];
extern const MemberPointer data_ov068_02277120, data_ov068_02277150, data_ov068_02277160;

/* The parts of the villager read here besides outdoor_villager.h's (main's scene_object.c). */
#define HOME_ANGLE 0x8e       /* s16: where it faces */
#define HOME_WALK_ANGLE 0x94  /* s16: where it walks */
#define HOME_MOVER 0x350      /* SceneMover */
#define HOME_SHADOW 0x511     /* u8: its shadow is drawn */
#define HOME_ENABLED 0x561    /* u8: 0 stops its frame after the mover, and its drawing */
#define HOME_POSED 0x562      /* u8: 0 keeps its joints' points at its position */
#define HOME_LOCAL 0x563      /* u8: not shared with a session */
#define HOME_DRAW_HOOK 0x8b0  /* MemberPointer: called to draw in place of the plain joints */
#define HOME_ITEM_SHOWN 0x9f0 /* u8: set while the held item is out */
/* The parts of the behaviour member read here besides outdoor_villager.h's. */
#define HOME_ITEM_CHECK 0x34 /* s16: frames to the next look at the held item (walks.h) */
#define HOME_WALKER 0x3c     /* PathWalker */
#define HOME_RAISE 0xf8      /* s32: frames to the next raise of the record's byte 0x1e */

/* The object's flag set while it is held (main's scene_action.h). */
#define HOME_FLAG_HELD 2
#define HOME_PRIORITY 1
#define HOME_PRIORITY_HIGH 2
#define HOME_MOTION_WALK 1
#define HOME_MOTION_TURN 3
#define HOME_FACING_HOUSE (-0x8000)
#define HOME_ANIM_IN 0x3b
#define HOME_ANIM_OUT 0x3d
#define HOME_ANIM_MODE 1
#define HOME_ANIM_OUT_WORD 1
#define HOME_DRAW_STEP 0x400 /* how far a frame it is drawn to the tile's centre going in */
#define HOME_RAISED 0x1000   /* how high above the tile it starts coming out */
#define HOME_COLLIDER 0xd00
#define HOME_NO_ITEM 0xfff1
#define HOME_ITEM_DELAY 300 /* frames added to the held item's check when it comes out with one */
#define HOME_WAIT_BASE 600
#define HOME_WAIT_SPREAD 40
#define HOME_RAISE_FRAMES 900
#define HOME_PLAYER_NEAR 0x6000
#define HOME_PLAYER_FLAG_1 1
#define HOME_ASLEEP 2 /* the state entry's byte 0x01, VillagerStatus_Get's 2 */
#define HOME_STATE_IN 0
#define HOME_STATE_OUT 1

/* Behaviours started here. */
#define HOME_DO_WALK 0
#define HOME_DO_IN 3
#define HOME_DO_OUT 4
#define HOME_DO_ITEM_OUT 15

static u8 *home_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static SceneMotion *home_motion(u8 *villager)
{
    return (SceneMotion *) (void *) home_at(villager, OUTDOOR_VILLAGER_MOTION);
}

static SpeakerAnim *home_anim(u8 *villager)
{
    return (SpeakerAnim *) (void *) home_at(villager, OUTDOOR_VILLAGER_ANIM);
}

static VillagerMood *home_mood(u8 *villager)
{
    return (VillagerMood *) (void *) home_at(villager, OUTDOOR_VILLAGER_MOOD);
}

static Vec3 *home_position(u8 *villager)
{
    return (Vec3 *) (void *) home_at(villager, OUTDOOR_VILLAGER_POSITION);
}

static Footsteps *home_footsteps(u8 *villager)
{
    return (Footsteps *) (void *) home_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS);
}

static PathWalker *home_walker(OutdoorVillagerBehaviour *self)
{
    return (PathWalker *) (void *) home_at(self, HOME_WALKER);
}

static s32 *home_raise(OutdoorVillagerBehaviour *self)
{
    return (s32 *) (void *) home_at(self, HOME_RAISE);
}

static u32 *home_flags(u8 *villager)
{
    return (u32 *) (void *) home_at(villager, OUTDOOR_VILLAGER_FLAGS);
}

/* Its town record (vtable slot 0x64), or null. */
static u8 *home_record(u8 *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager;
    u32 code = *(const u32 *) (uintptr_t) (vtable + OUTDOOR_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *))(uintptr_t) code)(villager);
}

/* The body animation's whole frame, as 16 bits. */
static u32 home_frame(u8 *villager)
{
    u32 frame = *(const u32 *) (const void *) home_at(villager, OUTDOOR_VILLAGER_ANIM_FRAME);
    return (frame << 4) >> 16;
}

/* The watch held on nothing. */
static void home_hold_nothing(u8 *villager)
{
    OutdoorVillagerWatch_Hold((OutdoorVillagerWatch *) (void *) home_at(villager, OUTDOOR_VILLAGER_WATCH), villager, 0, 0, 0,
                              &data_021fbee8, OUTDOOR_VILLAGER_PLAYER_ACTOR, data_020c814c, 1);
}

/* Its last position made its position, a field at a time. */
static void home_settle(u8 *villager)
{
    Vec3 *position = home_position(villager);
    Vec3 *last = (Vec3 *) (void *) home_at(villager, OUTDOOR_VILLAGER_LAST_POSITION);
    last->x = position->x;
    last->y = position->y;
    last->z = position->z;
}

/* A step of an update's table run (when it is in the table). */
static void home_run_step(MemberPointer *table, int count, OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->step < count) {
        const MemberPointer *member = &table[self->step];
        void *object = MemberPointer_Object(member, self);
        ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, object))(object, villager);
    }
}

/* The wait before an awake villager comes out: 600 to 639 frames. */
static s32 home_wait(void)
{
    return (s32) MainRandom_Below(HOME_WAIT_SPREAD) + HOME_WAIT_BASE;
}

/* ---- Behaviour 4: coming out of the house */

/* _ZN18Obj_ov068_022771c019func_ov068_0226b080Ei: behaviour 4's update: Open4, Leave4. */
int OutdoorVillagerHome_Update4(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276e78, /* OutdoorVillagerHome_Open4 */
        &data_ov068_02276e88, /* OutdoorVillagerHome_Leave4 */
    };
    MemberTable_InitOnce(&data_ov068_02278290, data_ov068_022782ec, steps, 2);
    home_run_step(data_ov068_022782ec, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_0226b080Ei, OutdoorVillagerHome_Update4)

/* func_ov068_0226b0ec: during animation 0x3d: once it is done, its shadow on, its collider
 * 0xd00, no longer held; with a held item behaviour 15 (behaviour 0 to resume) and the held
 * item's check put off 300 frames, else behaviour 0. Until then its footsteps at frames 13,
 * 17, 23, 28, 37 and 40. */
void OutdoorVillagerHome_Leave4(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(home_anim(villager), 0) != HOME_ANIM_OUT) {
        return;
    }
    if (SceneMotion_IsDone(home_motion(villager)) == 0) {
        switch (home_frame(villager)) {
            case 13:
            case 17:
            case 23:
            case 28:
            case 37:
            case 40:
                Footsteps_PlaySound(home_footsteps(villager), villager);
                break;
            default:
                break;
        }
        return;
    }
    *home_at(villager, HOME_SHADOW) = 1;
    SceneObject_SetColliderSize(villager, HOME_COLLIDER);
    *home_flags(villager) &= ~(u32) HOME_FLAG_HELD;
    u16 item;
    VillagerSceneHeld_Item(&item, villager);
    if (item != HOME_NO_ITEM) {
        OutdoorVillagerBehaviour_Start(self, villager, HOME_DO_ITEM_OUT);
        OutdoorVillagerBehaviour_SetResume(self, HOME_DO_WALK);
        s16 *check = (s16 *) (void *) home_at(self, HOME_ITEM_CHECK);
        *check = (s16) (*check + HOME_ITEM_DELAY);
    } else {
        OutdoorVillagerBehaviour_Start(self, villager, HOME_DO_WALK);
    }
}
CLEAN_AS(func_ov068_0226b0ec, OutdoorVillagerHome_Leave4)

/* func_ov068_0226b1d0: once the house lets the villager out: animation 0x3d (priority 2, word
 * 1), the draw hook data_ov068_02276f50, its state entry's state 1 and byte 0x01 cleared, the
 * object enabled and posed, its collider 0; step 1.
 * REQUIRES: its record has a state entry. */
void OutdoorVillagerHome_Open4(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *record = home_record(villager);
    VillagerState *entry = VillagerStatus_StateEntry(record);
    if (func_ov003_02220318(VillagerStatus_Index(record)) == 0) {
        return;
    }
    SceneMotion_RequestAnimation(home_motion(villager), HOME_PRIORITY_HIGH, HOME_ANIM_OUT, HOME_ANIM_MODE, HOME_ANIM_OUT_WORD,
                                 0);
    *(MemberPointer *) (void *) home_at(villager, HOME_DRAW_HOOK) = data_ov068_02276f50;
    VillagerState_SetState(entry, HOME_STATE_OUT);
    VillagerState_SetByte01(entry, 0);
    *home_at(villager, HOME_ENABLED) = 1;
    *home_at(villager, HOME_POSED) = 1;
    SceneObject_SetColliderSize(villager, 0);
    self->step = 1;
}
CLEAN_AS(func_ov068_0226b1d0, OutdoorVillagerHome_Open4)

/* func_ov068_0226b260: behaviour 4's start: a running act's effects reset, the watch held on
 * nothing, the villager put 0x1000 above the centre of the tile in front of its house, facing
 * and walking at angle 0 (its mover too), its last position the same; the byte at 0x838 set,
 * held, the raise timer off (-1), the held item not shown, its mood's sounds off. */
int OutdoorVillagerHome_Start4(OutdoorVillagerBehaviour *self, u8 *villager)
{
    VillagerPlot *home = VillagerHome_Tile(home_record(villager));
    OutdoorVillagerObject_ResetActEffects(villager);
    home_hold_nothing(villager);
    AcreTile_TileCentre(home_position(villager), home->x, (u32) home->z + 1);
    *(s16 *) (void *) home_at(villager, HOME_ANGLE) = 0;
    *(s16 *) (void *) home_at(villager, HOME_WALK_ANGLE) = 0;
    SceneMover_SetAngle((SceneMover *) (void *) home_at(villager, HOME_MOVER), 0);
    Vec3 *position = home_position(villager);
    position->y = (fx32) ((u32) position->y + HOME_RAISED);
    home_settle(villager);
    VillagerSceneObject_SetByte838(villager);
    *home_flags(villager) |= HOME_FLAG_HELD;
    *home_raise(self) = -1;
    *home_at(villager, HOME_ITEM_SHOWN) = 0;
    VillagerMood_SoundsOff(home_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226b260, OutdoorVillagerHome_Start4)

/* ---- Behaviour 12: staying in for good */

/* _ZN18Obj_ov068_022771c019func_ov068_0226b330Ei: behaviour 12's update: Begin12, Hide12. */
int OutdoorVillagerHome_Update12(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276f70, /* OutdoorVillagerHome_Begin12 */
        &data_ov068_02276e60, /* OutdoorVillagerHome_Hide12 */
    };
    MemberTable_InitOnce(&data_ov068_022782b0, data_ov068_022782dc, steps, 2);
    home_run_step(data_ov068_022782dc, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_0226b330Ei, OutdoorVillagerHome_Update12)

/* func_ov068_0226b39c: the villager disabled; step 2 (nothing more). */
void OutdoorVillagerHome_Hide12(OutdoorVillagerBehaviour *self, u8 *villager)
{
    *home_at(villager, HOME_ENABLED) = 0;
    self->step = 2;
}
CLEAN_AS(func_ov068_0226b39c, OutdoorVillagerHome_Hide12)

/* func_ov068_0226b3ac: step 1. */
void OutdoorVillagerHome_Begin12(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) villager;
    self->step = 1;
}
CLEAN_AS(func_ov068_0226b3ac, OutdoorVillagerHome_Begin12)

/* func_ov068_0226b3b4: behaviour 12's start: it stands, the watch held on nothing; its state
 * entry's state 0 when it reads 1, the entry's flag 1 cleared; the byte at 0x838 set, unposed
 * and not shared; put at the centre of its house's own tile, its last position the same; the
 * held item not shown, its mood's sounds off.
 * REQUIRES: its record has a state entry. */
int OutdoorVillagerHome_Start12(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    u8 *record = home_record(villager);
    VillagerState *entry = VillagerStatus_StateEntry(record);
    VillagerPlot *home = VillagerHome_Tile(record);
    SceneMotion_RequestStand(home_motion(villager), HOME_PRIORITY, data_020c80f8);
    home_hold_nothing(villager);
    if (VillagerState_LinkedState(entry) == HOME_STATE_OUT) {
        VillagerState_SetState(entry, HOME_STATE_IN);
    }
    entry->flags &= (u8) ~VILLAGER_STATE_FLAG_1;
    VillagerSceneObject_SetByte838(villager);
    *home_at(villager, HOME_POSED) = 0;
    *home_at(villager, HOME_LOCAL) = 1;
    AcreTile_TileCentre(home_position(villager), home->x, home->z);
    home_settle(villager);
    *home_at(villager, HOME_ITEM_SHOWN) = 0;
    VillagerMood_SoundsOff(home_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226b3b4, OutdoorVillagerHome_Start12)

/* ---- Behaviour 3: in the house */

/* _ZN18Obj_ov068_022771c019func_ov068_0226b48cEi: behaviour 3's update: Begin3, Stay3. */
int OutdoorVillagerHome_Update3(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276f90, /* OutdoorVillagerHome_Begin3 */
        &data_ov068_02276f88, /* OutdoorVillagerHome_Stay3 */
    };
    MemberTable_InitOnce(&data_ov068_02278284, data_ov068_022782cc, steps, 2);
    home_run_step(data_ov068_022782cc, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_0226b48cEi, OutdoorVillagerHome_Update3)

/* func_ov068_0226b4f8: the villager disabled. Asleep (status 2), once its sleep time is over
 * it wakes (byte 0x01 cleared, the wait 600 to 639, when it has a state entry) and comes out;
 * awake, it comes out when the wait is out. Coming out on screen: behaviour 4 with its walker
 * reset, unless this console's player is within 0x6000 (then it stays); off screen: its state
 * entry's state 1 and byte 0x01 cleared, put at the centre of the tile in front of its house
 * (its last position the same), its walker reset, behaviour 0, and its held item shown.
 * While it stays, every 900 frames its record's byte 0x1e rises.
 * REQUIRES: coming out off screen, its record has a state entry. */
void OutdoorVillagerHome_Stay3(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *record = home_record(villager);
    int out = 0;
    *home_at(villager, HOME_ENABLED) = 0;
    if (VillagerStatus_Get(record) == HOME_ASLEEP) {
        if (VillagerEntry_IsSleepTime(record, NULL) == 0) {
            if (VillagerStatus_StateEntry(record) != NULL) {
                VillagerState_SetByte01(VillagerStatus_StateEntry(record), 0);
                self->wait = home_wait();
            }
            out = 1;
        }
    } else if (self->wait == 0) {
        out = 1;
    }

    if (!out) {
        if (*home_raise(self) == 0) {
            if (home_record(villager) != NULL) {
                VillagerEntry_RaiseByte1E(home_record(villager), NULL);
            }
            *home_raise(self) = HOME_RAISE_FRAMES;
        }
        return;
    }

    if (OutdoorVillagerWalks_OnScreen(self, villager) != 0) {
        u8 *player = (u8 *) (uintptr_t) SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
        if (SceneObject_IsNear(villager, player, HOME_PLAYER_NEAR) == 0) {
            PathWalker_Init(home_walker(self));
            OutdoorVillagerBehaviour_Start(self, villager, HOME_DO_OUT);
        }
        return;
    }
    VillagerState *entry = VillagerStatus_StateEntry(record);
    VillagerPlot *home = VillagerHome_Tile(record);
    VillagerState_SetState(entry, HOME_STATE_OUT);
    VillagerState_SetByte01(entry, 0);
    AcreTile_TileCentre(home_position(villager), home->x, (u32) home->z + 1);
    home_settle(villager);
    PathWalker_Init(home_walker(self));
    OutdoorVillagerBehaviour_Start(self, villager, HOME_DO_WALK);
    u16 item;
    VillagerSceneHeld_Item(&item, villager);
    if (item != HOME_NO_ITEM) {
        OutdoorVillagerObject_ShowHeldItem(villager);
    }
}
CLEAN_AS(func_ov068_0226b4f8, OutdoorVillagerHome_Stay3)

/* func_ov068_0226b640: step 1. */
void OutdoorVillagerHome_Begin3(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) villager;
    self->step = 1;
}
CLEAN_AS(func_ov068_0226b640, OutdoorVillagerHome_Begin3)

/* func_ov068_0226b648: behaviour 3's start: a running act's effects reset, the watch held on
 * nothing, it stands; its state entry's state 0 and flag 1 cleared, asleep (byte 0x01 2) at
 * its sleep time unless the current player has flag 1, else awake (0); its furniture's items
 * stored, the byte at 0x838 set; the wait 600 to 639 frames, unposed, the raise timer 900, its
 * mood's sounds off and the held item not shown.
 * REQUIRES: its record has a state entry. */
int OutdoorVillagerHome_Start3(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 *current = PlayerRecords_Current();
    int flag_1 = current != NULL ? PlayerRecord_TestFlag(current, HOME_PLAYER_FLAG_1) : 0;
    u8 *record = home_record(villager);
    VillagerState *entry = VillagerStatus_StateEntry(record);
    OutdoorVillagerObject_ResetActEffects(villager);
    home_hold_nothing(villager);
    SceneMotion_RequestStand(home_motion(villager), HOME_PRIORITY, data_020c80f8);
    VillagerState_SetState(entry, HOME_STATE_IN);
    entry->flags &= (u8) ~VILLAGER_STATE_FLAG_1;
    if (flag_1 == 0 && VillagerEntry_IsSleepTime(record, NULL) != 0) {
        VillagerState_SetByte01(entry, HOME_ASLEEP);
    } else {
        VillagerState_SetByte01(entry, 0);
    }
    VillagerFurniture_StoreItems(record);
    VillagerSceneObject_SetByte838(villager);
    self->wait = home_wait();
    *home_at(villager, HOME_POSED) = 0;
    *home_raise(self) = HOME_RAISE_FRAMES;
    VillagerMood_SoundsOff(home_mood(villager));
    *home_at(villager, HOME_ITEM_SHOWN) = 0;
    return 1;
}
CLEAN_AS(func_ov068_0226b648, OutdoorVillagerHome_Start3)

/* ---- Behaviour 2: going into the house */

/* _ZN18Obj_ov068_022771c019func_ov068_0226b74cEi: behaviour 2's update: AfterTurn2,
 * AfterWalk2, Enter2. */
int OutdoorVillagerHome_Update2(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[3] = {
        &data_ov068_02277120, /* OutdoorVillagerHome_AfterTurn2 */
        &data_ov068_02277150, /* OutdoorVillagerHome_AfterWalk2 */
        &data_ov068_02277160, /* OutdoorVillagerHome_Enter2 */
    };
    MemberTable_InitOnce(&data_ov068_02278270, data_ov068_0227837c, steps, 3);
    home_run_step(data_ov068_0227837c, 3, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_0226b74cEi, OutdoorVillagerHome_Update2)

/* func_ov068_0226b7c8: during animation 0x3b: once it is done, behaviour 3. Else the villager
 * drawn to the centre of the tile in front of its house by 0x400 along x and z, and during the
 * animation its footsteps at frames 8, 12, 22, 27 and 34. */
void OutdoorVillagerHome_Enter2(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(home_anim(villager), 0) == HOME_ANIM_IN && SceneMotion_IsDone(home_motion(villager)) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, HOME_DO_IN);
        return;
    }
    VillagerPlot *home = VillagerHome_Tile(home_record(villager));
    Vec3 door;
    AcreTile_TileCentre(&door, home->x, (u32) home->z + 1);
    Vec3 *position = home_position(villager);
    Approach_S32Again((int *) (void *) &position->x, door.x, HOME_DRAW_STEP);
    Approach_S32Again((int *) (void *) &position->z, door.z, HOME_DRAW_STEP);
    if (SpeakerAnim_Number(home_anim(villager), 0) == HOME_ANIM_IN) {
        switch (home_frame(villager)) {
            case 8:
            case 12:
            case 22:
            case 27:
            case 34:
                Footsteps_PlaySound(home_footsteps(villager), villager);
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov068_0226b7c8, OutdoorVillagerHome_Enter2)

/* Once the motion of `kind` is done and the house lets the villager in: animation 0x3b
 * (priority 2), its shadow off; step 2. */
static void home_go_in(OutdoorVillagerBehaviour *self, u8 *villager, int kind)
{
    if (SceneMotion_Kind(home_motion(villager)) != kind || SceneMotion_IsDone(home_motion(villager)) == 0) {
        return;
    }
    if (func_ov003_02220340(VillagerStatus_Index(home_record(villager))) == 0) {
        return;
    }
    VillagerHome_Tile(home_record(villager));
    SceneMotion_RequestAnimation(home_motion(villager), HOME_PRIORITY_HIGH, HOME_ANIM_IN, HOME_ANIM_MODE, data_020c80f8, 0);
    *home_at(villager, HOME_SHADOW) = 0;
    self->step = 2;
}

/* func_ov068_0226b88c: once a walk (motion kind 1) is done and the house lets the villager in,
 * animation 0x3b; step 2. QUIRK: its home's tile is read and not used. */
void OutdoorVillagerHome_AfterWalk2(OutdoorVillagerBehaviour *self, u8 *villager)
{
    home_go_in(self, villager, HOME_MOTION_WALK);
}
CLEAN_AS(func_ov068_0226b88c, OutdoorVillagerHome_AfterWalk2)

/* func_ov068_0226b904: once the turn (motion kind 3) is done and the house lets the villager
 * in, animation 0x3b; step 2. QUIRK: its home's tile is read and not used. */
void OutdoorVillagerHome_AfterTurn2(OutdoorVillagerBehaviour *self, u8 *villager)
{
    home_go_in(self, villager, HOME_MOTION_TURN);
}
CLEAN_AS(func_ov068_0226b904, OutdoorVillagerHome_AfterTurn2)

/* func_ov068_0226b97c: behaviour 2's start: a running act's effects reset, the watch held on
 * nothing, a turn to face the house (motion kind 3, priority 2, angle -0x8000); held, the byte
 * at 0x838 set and its mood's sounds off. */
int OutdoorVillagerHome_Start2(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    OutdoorVillagerObject_ResetActEffects(villager);
    home_hold_nothing(villager);
    SceneMotion_Request(home_motion(villager), HOME_MOTION_TURN, HOME_PRIORITY_HIGH, 0, 0, 0, HOME_FACING_HOUSE, 0, 0,
                        data_020c80f8, 0);
    *home_flags(villager) |= HOME_FLAG_HELD;
    VillagerSceneObject_SetByte838(villager);
    VillagerMood_SoundsOff(home_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226b97c, OutdoorVillagerHome_Start2)
