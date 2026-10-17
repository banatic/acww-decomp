/* The gatekeeper's own states 9 to 0x11 (gatekeeper_states.h). */
#include "gatekeeper_states.h"

#include <stdint.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/activity_job.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/block_021d27ac.h"
#include "main/block_021d27ac_parts.h"
#include "main/camera_control.h"
#include "main/link_global.h"
#include "main/message_receiver.h"
#include "main/player_actor_ops.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_exit.h"
#include "main/scene_object.h"
#include "main/scene_place.h"
#include "main/scene_share.h"
#include "main/scene_tables.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/talk_object.h"
#include "ov004/member_pointer.h"

/* The steps of states 9 and 0xb. */
#define GATEKEEPER_STATES_STEPS 4

/* The field actor that is the player, for SessionPlayers_ActorOf and SceneObject_ActorObject. */
#define GATEKEEPER_STATES_PLAYER 4

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define GATEKEEPER_STATES_SLOT_RESET 2

/* The scenes it leaves for, with SceneExit's change and next arguments. */
#define GATEKEEPER_STATES_SCENE_C 0xc
#define GATEKEEPER_STATES_SCENE_2E 0x2e
/* The player's parameter of the place in scene 0xc. */
#define GATEKEEPER_STATES_PLAYER_PARAM 0x00800000

/* The kinds of the block's part 0x20 (block_021d27ac_parts.h) it sets with its own y angle. */
#define GATEKEEPER_STATES_PART20_KIND_C 1
#define GATEKEEPER_STATES_PART20_KIND_D 2

/* Line 0x7b of "sp_npc_gatekeeper", with the served player's name in part 1. */
#define GATEKEEPER_STATES_LINE_NAME 0x7b
#define GATEKEEPER_STATES_PART_NAME 1
/* The acceleration the served player walks with. */
#define GATEKEEPER_STATES_WALK 0x35c
/* The scene's exit the served player takes. */
#define GATEKEEPER_STATES_EXIT 1

/* The screen's transition (screen_transition.h): its state, 2 while the screen is shown. */
extern u8 data_021c75b8;
#define GATEKEEPER_STATES_SCREEN_SHOWN 2

/* The session. */
extern NetSession *data_020ccf94;
/* "sp_npc_gatekeeper", the archive of its lines (the first word of data_ov048_02263d20). */
extern const char *const data_ov048_02263d20;
/* The point the served player walks to: (16.0, 0, 5.0). */
extern const Vec3 data_ov048_022639a4;

/* The gatekeeper's state; the six steps of state 0xa and their reset. */
extern void func_ov048_022635f4(Gatekeeper *self, int state);
extern int _ZN18Obj_ov048_0226429819func_ov048_02262db0Ev(Gatekeeper *self);
extern int func_ov048_02262e68(Gatekeeper *self);

/* The steps of states 0xb and 9, filled from their constants on the first call (bit 0 of the
 * guard). */
extern MemberPointer data_ov048_02264758[GATEKEEPER_STATES_STEPS];
extern u32 data_ov048_02264728;
extern const MemberPointer data_ov048_02263f14, data_ov048_02263f0c, data_ov048_02263df4, data_ov048_02263efc;
extern MemberPointer data_ov048_02264738[GATEKEEPER_STATES_STEPS];
extern u32 data_ov048_02264730;
extern const MemberPointer data_ov048_02263e0c, data_ov048_022640e4, data_ov048_02263d84, data_ov048_02263f3c;

/* ---- Helpers */

static u8 *gatekeeper_states_object(Gatekeeper *self)
{
    return (u8 *) self;
}

/* Its talk reset (the talk's vtable slot 2). */
static void gatekeeper_states_reset_talk(Gatekeeper *self)
{
    const u32 *vtable = (const u32 *) (const void *) self->talk.scene.vtable;
    ((void (*)(GatekeeperTalk *))(uintptr_t) vtable[GATEKEEPER_STATES_SLOT_RESET])(&self->talk);
}

/* Whether talk 0's window is gone. */
static int gatekeeper_states_talk_gone(void)
{
    return TalkObject_Get(0)->state == TALK_OBJECT_GONE;
}

static SceneExit *gatekeeper_states_exit(void)
{
    return (SceneExit *) (uintptr_t) SceneTables_EntryRecord();
}

/* A step of a sequence through `table`; the next step once it agrees. */
static void gatekeeper_states_step(Gatekeeper *self, const MemberPointer *table)
{
    if (self->setup_step < GATEKEEPER_STATES_STEPS) {
        if (MemberPointer_CallInt(&table[self->setup_step], self)) {
            self->setup_step++;
        }
    }
}

/* ---- States 0x10 and 0x11 */

/* func_ov048_0226277c (state 0x10's run): nothing; agrees. */
int Gatekeeper_RunState10(void)
{
    return 1;
}
CLEAN_AS(func_ov048_0226277c, Gatekeeper_RunState10)

/* func_ov048_02262780 (state 0x10's entry): agrees. */
int Gatekeeper_EnterState10(void)
{
    return 1;
}
CLEAN_AS(func_ov048_02262780, Gatekeeper_EnterState10)

/* func_ov048_02262784 (state 0x11's run): when the object is ours, the shared slots read show
 * no owner and the link holds the scene: this system the owner, no holder, and state 4. Agrees
 * always. */
int Gatekeeper_RunState11(Gatekeeper *self)
{
    int owner;
    int holder;

    if (!SceneShare_IsOurs(gatekeeper_states_object(self))) {
        return 1;
    }
    owner = SCENE_SHARE_NO_SLOT;
    holder = SCENE_SHARE_NO_SLOT;
    if (!SceneShare_ReadSlots(gatekeeper_states_object(self), &owner, &holder)) {
        return 1;
    }
    if (owner != SCENE_SHARE_NO_SLOT) {
        return 1;
    }
    if (!LinkGlobal_HoldsScene()) {
        return 1;
    }
    SceneShare_SetSlotsIfOurs(gatekeeper_states_object(self), 1, data_020ccf94->local_slot, SCENE_SHARE_NO_SLOT);
    func_ov048_022635f4(self, GATEKEEPER_STATE_4);
    return 1;
}
CLEAN_AS(func_ov048_02262784, Gatekeeper_RunState11)

/* func_ov048_022627dc (state 0x11's entry): agrees. */
int Gatekeeper_EnterState11(void)
{
    return 1;
}
CLEAN_AS(func_ov048_022627dc, Gatekeeper_EnterState11)

/* ---- States 0xf and 0xe */

/* func_ov048_022627e0 (state 0xf's run): when the object is ours: when the shared slots read
 * have this system as both owner and holder, they are set so again, the talk reset and given
 * the player's object as its motion argument, and state 2; else, when the link holds the scene
 * and there is no holder, this system the owner, no holder, and state 1. Agrees always. */
int Gatekeeper_RunStateF(Gatekeeper *self)
{
    u8 *object = gatekeeper_states_object(self);
    int owner;
    int holder;

    if (!SceneShare_IsOurs(object)) {
        return 1;
    }
    owner = SCENE_SHARE_NO_SLOT;
    holder = SCENE_SHARE_NO_SLOT;
    if (SceneShare_ReadSlots(object, &owner, &holder) && owner == data_020ccf94->local_slot && owner == holder) {
        SceneShare_SetSlotsIfOurs(object, 1, data_020ccf94->local_slot, data_020ccf94->local_slot);
        gatekeeper_states_reset_talk(self);
        SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject(object, GATEKEEPER_STATES_PLAYER));
        func_ov048_022635f4(self, GATEKEEPER_STATE_2);
    } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
        SceneShare_SetSlotsIfOurs(object, 1, data_020ccf94->local_slot, SCENE_SHARE_NO_SLOT);
        func_ov048_022635f4(self, GATEKEEPER_STATE_1);
    }
    return 1;
}
CLEAN_AS(func_ov048_022627e0, Gatekeeper_RunStateF)

/* func_ov048_0226287c (state 0xf's entry): agrees. */
int Gatekeeper_EnterStateF(void)
{
    return 1;
}
CLEAN_AS(func_ov048_0226287c, Gatekeeper_EnterStateF)

/* func_ov048_02262880 (state 0xe's run, after the player's yes to line 0x2c): once talk 0 is
 * gone, the activity's job 2 asked for, the exit set to scene 0x2e (arguments 2 and 3) and
 * state 3. Agrees always. */
int Gatekeeper_RunStateE(Gatekeeper *self)
{
    if (gatekeeper_states_talk_gone()) {
        ActivityJob_Ask2();
        SceneExit_SetToScene(gatekeeper_states_exit(), GATEKEEPER_STATES_SCENE_2E, 2, 3);
        func_ov048_022635f4(self, GATEKEEPER_STATE_3);
    }
    return 1;
}
CLEAN_AS(func_ov048_02262880, Gatekeeper_RunStateE)

/* func_ov048_022628b4 (state 0xe's entry): agrees. */
int Gatekeeper_EnterStateE(void)
{
    return 1;
}
CLEAN_AS(func_ov048_022628b4, Gatekeeper_EnterStateE)

/* ---- States 0xd and 0xc: leaving after a connection */

/* func_ov048_022628b8 (state 0xd's run): once talk 0 is gone: the block's part 0x20 of kind 2
 * with the gatekeeper's y angle; the player's place (its position, y angle and tile) saved for
 * scene 0xc; the camera's view kept; the activity's job 0x17 asked for; the exit set to scene
 * 0x2e (arguments 2 and 3); state 3. Agrees always. */
int Gatekeeper_RunStateD(Gatekeeper *self)
{
    Block021d27acPart20 *part;
    const Actor *player;
    Vec3 position;
    short angle;
    int tile_x;
    int tile_z;

    if (!gatekeeper_states_talk_gone()) {
        return 1;
    }
    part = (Block021d27acPart20 *) (void *) Block021d27ac_Part20(Block021d27ac_Get());
    player = SessionPlayers_ActorOf(GATEKEEPER_STATES_PLAYER);
    position = player->position;
    angle = player->angle[1];
    tile_x = 0;
    tile_z = 0;
    Position_Tile(&tile_x, &tile_z, (const Position *) (const void *) &position);
    Block021d27acPart20_SetKind(part, GATEKEEPER_STATES_PART20_KIND_D);
    Block021d27acPart20_SetValue(part, ((const Actor *) (const void *) self)->angle[1]);
    ScenePlace_SetSaved(SceneTables_EntryRecord(), GATEKEEPER_STATES_SCENE_C, &position, GATEKEEPER_STATES_PLAYER_PARAM, angle,
                        tile_x, tile_z);
    CameraControl_KeepView();
    ActivityJob_Ask17();
    SceneExit_SetToScene(gatekeeper_states_exit(), GATEKEEPER_STATES_SCENE_2E, 2, 3);
    func_ov048_022635f4(self, GATEKEEPER_STATE_3);
    return 1;
}
CLEAN_AS(func_ov048_022628b8, Gatekeeper_RunStateD)

/* func_ov048_02262954 (state 0xd's entry): agrees. */
int Gatekeeper_EnterStateD(void)
{
    return 1;
}
CLEAN_AS(func_ov048_02262954, Gatekeeper_EnterStateD)

/* func_ov048_02262958 (state 0xc's run): once talk 0 is gone: the block's part 0x20 of kind 1
 * with the gatekeeper's y angle; the camera's view kept; the activity's job 0x14 asked for; the
 * exit set to scene 0xc at the player's position and y angle (arguments 2 and 2); state 3.
 * Agrees always.
 * QUIRK: the player's tile is worked out and not used. */
int Gatekeeper_RunStateC(Gatekeeper *self)
{
    Block021d27acPart20 *part;
    const Actor *player;
    Vec3 position;
    short angle;
    int tile_x;
    int tile_z;

    if (!gatekeeper_states_talk_gone()) {
        return 1;
    }
    part = (Block021d27acPart20 *) (void *) Block021d27ac_Part20(Block021d27ac_Get());
    player = SessionPlayers_ActorOf(GATEKEEPER_STATES_PLAYER);
    position = player->position;
    angle = player->angle[1];
    tile_x = 0;
    tile_z = 0;
    Position_Tile(&tile_x, &tile_z, (const Position *) (const void *) &position);
    Block021d27acPart20_SetKind(part, GATEKEEPER_STATES_PART20_KIND_C);
    Block021d27acPart20_SetValue(part, ((const Actor *) (const void *) self)->angle[1]);
    CameraControl_KeepView();
    ActivityJob_Ask14();
    SceneExit_SetTo(gatekeeper_states_exit(), GATEKEEPER_STATES_SCENE_C, &position, GATEKEEPER_STATES_PLAYER_PARAM, angle, 2,
                    2);
    func_ov048_022635f4(self, GATEKEEPER_STATE_3);
    return 1;
}
CLEAN_AS(func_ov048_02262958, Gatekeeper_RunStateC)

/* func_ov048_022629e4 (state 0xc's entry): agrees. */
int Gatekeeper_EnterStateC(void)
{
    return 1;
}
CLEAN_AS(func_ov048_022629e4, Gatekeeper_EnterStateC)

/* ---- State 0xb: the served player sent off */

/* func_ov048_022629e8 (state 0xb's run): its step (Gatekeeper.setup_step, 0-3) run until it
 * agrees: Gatekeeper_StateBSayName, Gatekeeper_StateBMovePlayer, Gatekeeper_StateBClearRecord,
 * Gatekeeper_StateBTakeExit; at step 4 nothing. Agrees always. */
int Gatekeeper_RunStateB(Gatekeeper *self)
{
    static const MemberPointer *const steps[GATEKEEPER_STATES_STEPS] = {
        &data_ov048_02263f14, /* Gatekeeper_StateBSayName */
        &data_ov048_02263f0c, /* Gatekeeper_StateBMovePlayer */
        &data_ov048_02263df4, /* Gatekeeper_StateBClearRecord */
        &data_ov048_02263efc, /* Gatekeeper_StateBTakeExit */
    };
    MemberTable_InitOnce(&data_ov048_02264728, data_ov048_02264758, steps, GATEKEEPER_STATES_STEPS);
    gatekeeper_states_step(self, data_ov048_02264758);
    return 1;
}
CLEAN_AS(func_ov048_022629e8, Gatekeeper_RunStateB)

/* func_ov048_02262a84 (state 0xb's entry): its steps from the first; agrees. */
int Gatekeeper_EnterStateB(Gatekeeper *self)
{
    self->setup_step = 0;
    return 1;
}
CLEAN_AS(func_ov048_02262a84, Gatekeeper_EnterStateB)

/* func_ov048_02262a94 (state 0xb's step 3): the scene's exit 1 taken; agrees. */
int Gatekeeper_StateBTakeExit(void)
{
    SceneExit_Take(gatekeeper_states_exit(), GATEKEEPER_STATES_EXIT);
    return 1;
}
CLEAN_AS(func_ov048_02262a94, Gatekeeper_StateBTakeExit)

/* func_ov048_02262aac (state 0xb's step 2): once the served player's actor is not busy, its
 * player record cleared; whether it was. */
int Gatekeeper_StateBClearRecord(void)
{
    int player = (int) LinkGlobal_ServedSlot();
    u8 *record = PlayerRecords_OfPlayer(player);

    if (PlayerActorOps_IsBusy(player) == 0) {
        PlayerRecord_Clear(record);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov048_02262aac, Gatekeeper_StateBClearRecord)

/* func_ov048_02262adc (state 0xb's step 1): once talk 0 is closed, its receiver let go and the
 * served player's actor asked to walk to (16.0, 0, 5.0); whether it was closed. */
int Gatekeeper_StateBMovePlayer(void)
{
    int player = (int) LinkGlobal_ServedSlot();
    TalkObject *talk = TalkObject_Get(0);

    if (talk->state == TALK_OBJECT_CLOSED) {
        Vec3 point = data_ov048_022639a4;
        TalkObject_DetachReceiver(talk);
        PlayerActorOps_MoveTo(&point, GATEKEEPER_STATES_WALK, player);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov048_02262adc, Gatekeeper_StateBMovePlayer)

/* func_ov048_02262b24 (state 0xb's step 0): once the screen is shown, its talk reset and shown
 * through talk 0 with line 0x7b, the served player's name in part 1, and talk 0 asked to open;
 * whether the screen was shown. */
int Gatekeeper_StateBSayName(Gatekeeper *self)
{
    u8 *record = PlayerRecords_OfPlayer((int) LinkGlobal_ServedSlot());
    TalkObject *talk;
    PlayerIdText name;

    if (data_021c75b8 != GATEKEEPER_STATES_SCREEN_SHOWN) {
        return 0;
    }
    talk = TalkObject_Get(0);
    gatekeeper_states_reset_talk(self);
    MessageReceiver_SetName((MessageReceiver *) (void *) &self->talk, data_ov048_02263d20);
    ((MessageReceiver *) (void *) &self->talk)->message = GATEKEEPER_STATES_LINE_NAME;
    TalkObject_AttachReceiver(talk, (TalkReceiver *) (void *) &self->talk);
    PlayerIdText_Construct(&name);
    PlayerId_NameToText(PlayerRecord_Player(record), (TextBase *) (void *) &name);
    TalkObject_SetPart(talk, GATEKEEPER_STATES_PART_NAME, (TextBase *) (void *) &name);
    talk->next_state = TALK_OBJECT_OPENING;
    PlayerIdText_Destruct(&name);
    return 1;
}
CLEAN_AS(func_ov048_02262b24, Gatekeeper_StateBSayName)

/* ---- States 0xa and 9 */

/* Obj_ov048_02264298::func_ov048_02262bb8 (state 0xa's run): a step of its six
 * (func_ov048_02262db0). */
void Gatekeeper_RunStateA(Gatekeeper *self)
{
    _ZN18Obj_ov048_0226429819func_ov048_02262db0Ev(self);
}
CLEAN_AS(_ZN18Obj_ov048_0226429819func_ov048_02262bb8Ev, Gatekeeper_RunStateA)

/* func_ov048_02262bc0 (state 0xa's entry): func_ov048_02262e68, which resets its steps. */
void Gatekeeper_EnterStateA(Gatekeeper *self)
{
    func_ov048_02262e68(self);
}
CLEAN_AS(func_ov048_02262bc0, Gatekeeper_EnterStateA)

/* func_ov048_02262bc8 (state 9's run): its step (Gatekeeper.setup_step, 0-3) run until it
 * agrees: func_ov048_02262d4c, func_ov048_02262cc0, func_ov048_02262c8c, func_ov048_02262c74;
 * at step 4 nothing. Agrees always. */
int Gatekeeper_RunState9(Gatekeeper *self)
{
    static const MemberPointer *const steps[GATEKEEPER_STATES_STEPS] = {
        &data_ov048_02263e0c,
        &data_ov048_022640e4,
        &data_ov048_02263d84,
        &data_ov048_02263f3c,
    };
    MemberTable_InitOnce(&data_ov048_02264730, data_ov048_02264738, steps, GATEKEEPER_STATES_STEPS);
    gatekeeper_states_step(self, data_ov048_02264738);
    return 1;
}
CLEAN_AS(func_ov048_02262bc8, Gatekeeper_RunState9)
