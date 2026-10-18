/* The gatekeeper's own states 9 to 0x11 (gatekeeper_states.h). */
#include "gatekeeper_states.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/network.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/activity.h"
#include "main/activity_job.h"
#include "main/activity_vars.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/block_021d27ac.h"
#include "main/block_021d27ac_parts.h"
#include "main/camera_control.h"
#include "main/event_queue.h"
#include "main/field_label.h"
#include "main/library_overlay.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/player_actor_ops.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_exit.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_place.h"
#include "main/scene_share.h"
#include "main/scene_sound.h"
#include "main/scene_tables.h"
#include "main/screen_transition.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/session_players.h"
#include "main/speaker_anim.h"
#include "main/talk_object.h"
#include "main/town_name.h"
#include "gatekeeper_talk_lines.h"
#include "ov004/member_pointer.h"
#include "ov004/check_in_gate.h"
#include "ov004/room_camera.h"

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
    Gatekeeper_SetState(self, GATEKEEPER_STATE_4);
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
        Gatekeeper_SetState(self, GATEKEEPER_STATE_2);
    } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
        SceneShare_SetSlotsIfOurs(object, 1, data_020ccf94->local_slot, SCENE_SHARE_NO_SLOT);
        Gatekeeper_SetState(self, GATEKEEPER_STATE_1);
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
        Gatekeeper_SetState(self, GATEKEEPER_STATE_3);
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
    Gatekeeper_SetState(self, GATEKEEPER_STATE_3);
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
    Gatekeeper_SetState(self, GATEKEEPER_STATE_3);
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
 * (Gatekeeper_RunState8, the same steps as state 8). */
void Gatekeeper_RunStateA(Gatekeeper *self)
{
    Gatekeeper_RunState8(self);
}
CLEAN_AS(_ZN18Obj_ov048_0226429819func_ov048_02262bb8Ev, Gatekeeper_RunStateA)

/* func_ov048_02262bc0 (state 0xa's entry): Gatekeeper_EnterState8, which resets its steps. */
void Gatekeeper_EnterStateA(Gatekeeper *self)
{
    Gatekeeper_EnterState8(self);
}
CLEAN_AS(func_ov048_02262bc0, Gatekeeper_EnterStateA)

/* func_ov048_02262bc8 (state 9's run): its step (Gatekeeper.setup_step, 0-3) run until it
 * agrees: Gatekeeper_State9WalkIn, Gatekeeper_State9SayName, Gatekeeper_State9CloseTalk,
 * Gatekeeper_State9TakeExit; at step 4 nothing. Agrees always. */
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

/* ---- State 9: a player arrives */

/* The point a player arriving walks to: (16.0, 0, 17.5). */
extern const Vec3 data_ov048_02263998;
/* The acceleration the arriving player walks with. */
#define GATEKEEPER_STATES_ARRIVE_WALK 0x35c
/* Line 0x67 of "sp_npc_gatekeeper", with the arriving player's name in part 1. */
#define GATEKEEPER_STATES_LINE_ARRIVED 0x67

/* func_ov048_02262c64 (state 9's entry): its steps from the first; agrees. */
int Gatekeeper_EnterState9(Gatekeeper *self)
{
    self->setup_step = 0;
    return 1;
}
CLEAN_AS(func_ov048_02262c64, Gatekeeper_EnterState9)

/* func_ov048_02262c74 (state 9's step 3): the scene's exit 1 taken; agrees. */
int Gatekeeper_State9TakeExit(void)
{
    SceneExit_Take(gatekeeper_states_exit(), GATEKEEPER_STATES_EXIT);
    return 1;
}
CLEAN_AS(func_ov048_02262c74, Gatekeeper_State9TakeExit)

/* func_ov048_02262c8c (state 9's step 2): once talk 0 is closed: while the activity's byte 0xd6
 * is 0 the field's label shows its message 0x10 and the step waits; else talk 0's receiver is
 * let go and the step agrees. */
int Gatekeeper_State9CloseTalk(void)
{
    TalkObject *talk = TalkObject_Get(0);

    if (talk->state != TALK_OBJECT_CLOSED) {
        return 0;
    }
    if (Activity_CurrentByteD6() == 0) {
        FieldLabel_ShowMessage10();
        return 0;
    }
    TalkObject_DetachReceiver(talk);
    return 1;
}
CLEAN_AS(func_ov048_02262c8c, Gatekeeper_State9CloseTalk)

/* func_ov048_02262cc0 (state 9's step 1): once the arriving player's actor (the activity's slot
 * 0x3c1c) is not busy, its talk reset and shown through talk 0 with line 0x67, that player's
 * name in part 1, and talk 0 asked to open; whether the actor was not busy. */
int Gatekeeper_State9SayName(Gatekeeper *self)
{
    int player = ActivityVars_Slot3C1C();
    u8 *record = PlayerRecords_OfPlayer(player);
    TalkObject *talk;
    PlayerIdText name;

    if (PlayerActorOps_IsBusy(player) != 0) {
        return 0;
    }
    talk = TalkObject_Get(0);
    gatekeeper_states_reset_talk(self);
    MessageReceiver_SetName((MessageReceiver *) (void *) &self->talk, data_ov048_02263d20);
    ((MessageReceiver *) (void *) &self->talk)->message = GATEKEEPER_STATES_LINE_ARRIVED;
    TalkObject_AttachReceiver(talk, (TalkReceiver *) (void *) &self->talk);
    PlayerIdText_Construct(&name);
    PlayerId_NameToText(PlayerRecord_Player(record), (TextBase *) (void *) &name);
    TalkObject_SetPart(talk, GATEKEEPER_STATES_PART_NAME, (TextBase *) (void *) &name);
    talk->next_state = TALK_OBJECT_OPENING;
    PlayerIdText_Destruct(&name);
    return 1;
}
CLEAN_AS(func_ov048_02262cc0, Gatekeeper_State9SayName)

/* func_ov048_02262d4c (state 9's step 0): once the screen is shown and the arriving player's
 * actor (the activity's slot 0x3c1c) takes its flag 0x10, this player's actor gets its flag
 * 0x0e and the arriving one is asked to walk to (16.0, 0, 17.5); whether it was. */
int Gatekeeper_State9WalkIn(void)
{
    int player = ActivityVars_Slot3C1C();

    if (data_021c75b8 != GATEKEEPER_STATES_SCREEN_SHOWN) {
        return 0;
    }
    if (PlayerActorOps_SwitchFlag10(1, player) == 0) {
        return 0;
    }
    PlayerActorOps_SwitchFlag0e(1, GATEKEEPER_STATES_PLAYER);
    Vec3 point = data_ov048_02263998;
    PlayerActorOps_MoveTo(&point, GATEKEEPER_STATES_ARRIVE_WALK, player);
    return 1;
}
CLEAN_AS(func_ov048_02262d4c, Gatekeeper_State9WalkIn)

/* ---- States 8 and 0xa: the player passes through the gate */

/* The other gatekeeper (overlay 4's gatekeeper2.h), the object of this profile. */
#define GATEKEEPER_STATES_OTHER_PROFILE 0x73

/* The members of a scene object by place (scene_object.h), its own's and the other's. */
#define GATEKEEPER_STATES_STANDARD_ANIMS 0x2a0
#define GATEKEEPER_STATES_ANIM 0x334
#define GATEKEEPER_STATES_MOVER 0x350
#define GATEKEEPER_STATES_LOOK 0x3b0
#define GATEKEEPER_STATES_MOTION 0x564
#define GATEKEEPER_STATES_ACTION 0x618

/* The motions' kinds and the priority they are asked with (scene_motion_kinds.h). */
#define GATEKEEPER_STATES_MOTION_STAND 0
#define GATEKEEPER_STATES_MOTION_TURN 3
#define GATEKEEPER_STATES_PRIORITY 1

/* The animations both gatekeepers play while the player passes, the first in play mode 1. */
#define GATEKEEPER_STATES_ANIM_81 0x81
#define GATEKEEPER_STATES_ANIM_82 0x82

/* The angles they turn to, and the player's. */
#define GATEKEEPER_STATES_ANGLE_OWN (-0x4000)
#define GATEKEEPER_STATES_ANGLE_OTHER 0x4000
#define GATEKEEPER_STATES_ANGLE_PLAYER (-0x8000)

/* The waits: a random 5 to 9 frames, and 22 frames of the animations. */
#define GATEKEEPER_STATES_WAIT_RANDOM 5
#define GATEKEEPER_STATES_WAIT_BASE 5
#define GATEKEEPER_STATES_WAIT_ANIM 0x16
/* The frames of the wait left when both looks are locked. */
#define GATEKEEPER_STATES_WAIT_LOOK 2

/* The points the player walks to: before the gate (16.0, 0, 19.0), then through it
 * (16.0, 0, 2.0); with these accelerations. */
extern const Vec3 data_ov048_02263980;
extern const Vec3 data_ov048_0226398c;
#define GATEKEEPER_STATES_WALK_TO_GATE 0x400
#define GATEKEEPER_STATES_WALK_THROUGH 0x666

/* The screen is closed as a circle (screen_transition.h) over 15 frames. */
#define GATEKEEPER_STATES_CLOSE_KIND 2
#define GATEKEEPER_STATES_CLOSE_FRAMES 0xf

/* The word its motion requests carry. */
extern u16 data_020c80f8;

/* The six steps of states 8 and 0xa, filled from their constants on the first call (bit 0 of
 * the guard). */
#define GATEKEEPER_STATES_PASS_STEPS 6
extern MemberPointer data_ov048_02264778[GATEKEEPER_STATES_PASS_STEPS];
extern u32 data_ov048_02264720;
extern const MemberPointer data_ov048_02263f9c, data_ov048_02263f94, data_ov048_02263f8c, data_ov048_02263f84,
    data_ov048_02263f7c, data_ov048_02263f74;

static u8 *gatekeeper_states_at(void *object, int offset)
{
    return (u8 *) object + offset;
}

static SceneMotion *gatekeeper_states_motion(void *object)
{
    return (SceneMotion *) (void *) gatekeeper_states_at(object, GATEKEEPER_STATES_MOTION);
}

static SceneAction *gatekeeper_states_action(Gatekeeper *self)
{
    return (SceneAction *) (void *) gatekeeper_states_at(self, GATEKEEPER_STATES_ACTION);
}

/* Whether the object's animation player plays its body animation `number`. */
static int gatekeeper_states_plays(void *object, int number)
{
    return SpeakerAnim_IsBody((SpeakerAnim *) (void *) gatekeeper_states_at(object, GATEKEEPER_STATES_ANIM), number,
                              gatekeeper_states_at(object, GATEKEEPER_STATES_STANDARD_ANIMS));
}

/* The other gatekeeper.
 * REQUIRES: it exists (the gate's scene has both). */
static u8 *gatekeeper_states_other(void)
{
    return (u8 *) Actor_FindNextOfProfile(GATEKEEPER_STATES_OTHER_PROFILE, NULL);
}

/* _ZN18Obj_ov048_0226429819func_ov048_02262db0Ev (state 8's run, and 0xa's): its step
 * (Gatekeeper.setup_step, 0-5) run until it agrees: Gatekeeper_PassWalkToGate,
 * Gatekeeper_PassTurn, Gatekeeper_PassOtherTurns, Gatekeeper_PassWalkThrough,
 * Gatekeeper_PassAnimate, Gatekeeper_PassLeave; at step 6 nothing. Agrees always. */
int Gatekeeper_RunState8(Gatekeeper *self)
{
    static const MemberPointer *const steps[GATEKEEPER_STATES_PASS_STEPS] = {
        &data_ov048_02263f9c, /* Gatekeeper_PassWalkToGate */
        &data_ov048_02263f94, /* Gatekeeper_PassTurn */
        &data_ov048_02263f8c, /* Gatekeeper_PassOtherTurns */
        &data_ov048_02263f84, /* Gatekeeper_PassWalkThrough */
        &data_ov048_02263f7c, /* Gatekeeper_PassAnimate */
        &data_ov048_02263f74, /* Gatekeeper_PassLeave */
    };
    MemberTable_InitOnce(&data_ov048_02264720, data_ov048_02264778, steps, GATEKEEPER_STATES_PASS_STEPS);
    if (self->setup_step < GATEKEEPER_STATES_PASS_STEPS) {
        if (MemberPointer_CallInt(&data_ov048_02264778[self->setup_step], self)) {
            self->setup_step++;
        }
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov048_0226429819func_ov048_02262db0Ev, Gatekeeper_RunState8)

/* func_ov048_02262e68 (state 8's entry, and 0xa's): its steps from the first, and its mover
 * turned to the angle it started with; agrees. */
int Gatekeeper_EnterState8(Gatekeeper *self)
{
    self->setup_step = 0;
    SceneMover_SetAngle((SceneMover *) (void *) gatekeeper_states_at(self, GATEKEEPER_STATES_MOVER), self->home_angle);
    return 1;
}
CLEAN_AS(func_ov048_02262e68, Gatekeeper_EnterState8)

/* func_ov048_02262e94 (step 5): in state 8, once the screen is closed, the activity's flag
 * 0x3c08 set, and state 3 (it waits while the screen is not closed); in state 0xa, the scene's
 * exit 0 taken and state 3. */
int Gatekeeper_PassLeave(Gatekeeper *self)
{
    if (self->state == GATEKEEPER_STATE_8) {
        if (data_021c75b8 != 0) {
            return 0;
        }
        ActivityVars_SetFlag3C08();
        Gatekeeper_SetState(self, GATEKEEPER_STATE_3);
    } else {
        SceneExit_Take(gatekeeper_states_exit(), 0);
        Gatekeeper_SetState(self, GATEKEEPER_STATE_3);
    }
    return 1;
}
CLEAN_AS(func_ov048_02262e94, Gatekeeper_PassLeave)

/* func_ov048_02262f58 (step 4): the two gatekeepers' animations:
 * - once its own wait (Gatekeeper.anim_countdown) is over, the other plays animation 0x81
 *   unless it plays 0x81 or 0x82 already;
 * - each that has played 0x81 to its end plays 0x82 (play mode 0);
 * - with 2 frames of the wait (Gatekeeper.countdown) left, both looks are locked.
 * Once the wait is over: in state 8 the screen is asked to close (a circle, 15 frames) and
 * when it is, the scene's sounds stopped and the step agrees; in state 0xa it agrees then. */
int Gatekeeper_PassAnimate(Gatekeeper *self)
{
    u8 *other = gatekeeper_states_other();

    if (Countdown_Tick8(&self->anim_countdown) == 0 && !gatekeeper_states_plays(other, GATEKEEPER_STATES_ANIM_81) &&
        !gatekeeper_states_plays(other, GATEKEEPER_STATES_ANIM_82)) {
        SceneMotion_RequestAnimation(gatekeeper_states_motion(other), GATEKEEPER_STATES_PRIORITY, GATEKEEPER_STATES_ANIM_81, 1,
                                     data_020c80f8, 0);
    }
    if (gatekeeper_states_plays(self, GATEKEEPER_STATES_ANIM_81) && SceneMotion_IsDone(gatekeeper_states_motion(self))) {
        SceneMotion_RequestAnimation(gatekeeper_states_motion(self), GATEKEEPER_STATES_PRIORITY, GATEKEEPER_STATES_ANIM_82, 0,
                                     data_020c80f8, 0);
    }
    if (gatekeeper_states_plays(other, GATEKEEPER_STATES_ANIM_81) && SceneMotion_IsDone(gatekeeper_states_motion(other))) {
        SceneMotion_RequestAnimation(gatekeeper_states_motion(other), GATEKEEPER_STATES_PRIORITY, GATEKEEPER_STATES_ANIM_82, 0,
                                     data_020c80f8, 0);
    }
    if (self->countdown == GATEKEEPER_STATES_WAIT_LOOK) {
        SceneLook_Lock((SceneLook *) (void *) gatekeeper_states_at(self, GATEKEEPER_STATES_LOOK));
        SceneLook_Lock((SceneLook *) (void *) gatekeeper_states_at(other, GATEKEEPER_STATES_LOOK));
    }
    if (Countdown_Tick16(&self->countdown) != 0) {
        return 0;
    }
    if (self->state != GATEKEEPER_STATE_8) {
        return 1;
    }
    if (ScreenTransition_Close(GATEKEEPER_STATES_CLOSE_KIND, GATEKEEPER_STATES_CLOSE_FRAMES) == 0) {
        return 0;
    }
    SceneSound_Stop();
    return 1;
}
CLEAN_AS(func_ov048_02262f58, Gatekeeper_PassAnimate)

/* func_ov048_02263084 (step 3): each gatekeeper that has turned stands (its own with the stand
 * request, the other facing -0x4000); once both stand, the player is asked to walk through the
 * gate to (16.0, 0, 2.0), it plays animation 0x81 (play mode 1), the other waits 5 to 9 frames
 * and both 22 frames, and the camera takes mode 0xf. Whether both stood. */
int Gatekeeper_PassWalkThrough(Gatekeeper *self)
{
    SceneMotion *own = gatekeeper_states_motion(self);
    SceneMotion *other = gatekeeper_states_motion(gatekeeper_states_other());

    if (SceneMotion_Kind(own) == GATEKEEPER_STATES_MOTION_TURN && SceneMotion_IsDone(own)) {
        SceneMotion_RequestStand(own, GATEKEEPER_STATES_PRIORITY, data_020c80f8);
    }
    if (SceneMotion_Kind(other) == GATEKEEPER_STATES_MOTION_TURN && SceneMotion_IsDone(other)) {
        SceneMotion_Request(other, GATEKEEPER_STATES_MOTION_STAND, GATEKEEPER_STATES_PRIORITY, 0, 0, 0,
                            GATEKEEPER_STATES_ANGLE_OWN, 0, 0, data_020c80f8, 0);
    }
    if (SceneMotion_Kind(own) != GATEKEEPER_STATES_MOTION_STAND || SceneMotion_Kind(other) != GATEKEEPER_STATES_MOTION_STAND) {
        return 0;
    }
    Vec3 point = data_ov048_0226398c;
    PlayerActorOps_MoveTo(&point, GATEKEEPER_STATES_WALK_THROUGH, GATEKEEPER_STATES_PLAYER);
    SceneMotion_RequestAnimation(own, GATEKEEPER_STATES_PRIORITY, GATEKEEPER_STATES_ANIM_81, 1, data_020c80f8, 0);
    self->anim_countdown = (u8) (MainRandom_Below(GATEKEEPER_STATES_WAIT_RANDOM) + GATEKEEPER_STATES_WAIT_BASE);
    self->countdown = GATEKEEPER_STATES_WAIT_ANIM;
    RoomCamera_SetMode15();
    return 1;
}
CLEAN_AS(func_ov048_02263084, Gatekeeper_PassWalkThrough)

/* func_ov048_02263174 (step 2): once its wait is over, the other gatekeeper turns to 0x4000;
 * whether it did. */
int Gatekeeper_PassOtherTurns(Gatekeeper *self)
{
    if (Countdown_Tick16(&self->countdown) != 0) {
        return 0;
    }
    SceneMotion_Request(gatekeeper_states_motion(gatekeeper_states_other()), GATEKEEPER_STATES_MOTION_TURN,
                        GATEKEEPER_STATES_PRIORITY, 0, 0, 0, GATEKEEPER_STATES_ANGLE_OTHER, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov048_02263174, Gatekeeper_PassOtherTurns)

/* func_ov048_022631cc (step 1): once the player's actor is not busy, it is turned to -0x8000,
 * this gatekeeper turns to -0x4000 and waits 5 to 9 frames; whether the actor was not busy.
 * QUIRK: the wait is truncated to 8 bits before it is stored (it fits). */
int Gatekeeper_PassTurn(Gatekeeper *self)
{
    if (PlayerActorOps_IsBusy(GATEKEEPER_STATES_PLAYER) != 0) {
        return 0;
    }
    PlayerActorOps_Turn(GATEKEEPER_STATES_ANGLE_PLAYER, GATEKEEPER_STATES_PLAYER);
    SceneMotion_Request(gatekeeper_states_motion(self), GATEKEEPER_STATES_MOTION_TURN, GATEKEEPER_STATES_PRIORITY, 0, 0, 0,
                        GATEKEEPER_STATES_ANGLE_OWN, 0, 0, data_020c80f8, 0);
    self->countdown = (u8) (MainRandom_Below(GATEKEEPER_STATES_WAIT_RANDOM) + GATEKEEPER_STATES_WAIT_BASE);
    return 1;
}
CLEAN_AS(func_ov048_022631cc, Gatekeeper_PassTurn)

/* func_ov048_02263238 (step 0): once no action of its runs, the camera takes mode 0xe, the
 * player is asked to walk before the gate to (16.0, 0, 19.0) and its actor gets its flag 0x0e;
 * whether no action ran. */
int Gatekeeper_PassWalkToGate(Gatekeeper *self)
{
    if (SceneAction_IsBusy(gatekeeper_states_action(self))) {
        return 0;
    }
    RoomCamera_SetMode14();
    Vec3 point = data_ov048_02263980;
    PlayerActorOps_MoveTo(&point, GATEKEEPER_STATES_WALK_TO_GATE, GATEKEEPER_STATES_PLAYER);
    PlayerActorOps_SwitchFlag0e(1, GATEKEEPER_STATES_PLAYER);
    return 1;
}
CLEAN_AS(func_ov048_02263238, Gatekeeper_PassWalkToGate)

/* ---- States 7 and 6: the town closed and opened to visitors */

/* The steps of states 5, 6 and 7 (Gatekeeper.setup_step). */
#define GATEKEEPER_STATES_STEP_ACTION 0 /* until no action of its runs */
#define GATEKEEPER_STATES_STEP_CAMERA 1 /* until the camera stands still (state 5: at once) */
#define GATEKEEPER_STATES_STEP_WAIT 2   /* until the wait is over */
#define GATEKEEPER_STATES_STEP_WALKED 3 /* state 5: until the player's actor is not busy */

/* The frames states 6 and 7 wait. */
#define GATEKEEPER_STATES_WAIT_GATE 0x3c

/* The network modes of the Wi-Fi Connection (autoload_2/network.h). */
#define GATEKEEPER_STATES_MODE_HOSTING 3
#define GATEKEEPER_STATES_MODE_JOINING 4

/* The lines whose end enters state 6 (GatekeeperTalk_SetOwnerState6). */
#define GATEKEEPER_STATES_LINE_OPEN_46 0x46
#define GATEKEEPER_STATES_LINE_OPEN_6C 0x6c

/* The data a parent of this game carries (GATEKEEPER_PARENT_DATA_SIZE): the town's name, the
 * player's name and a 0. */
#define GATEKEEPER_STATES_NAME_SIZE 12
#define GATEKEEPER_STATES_PARENT_BUFFER 0x1c
/* The session's mode a local parent starts (GatekeeperTalk_StartSession). */
#define GATEKEEPER_STATES_SESSION_PARENT 1

/* This town (number and name, town_name.h). */
extern const u8 data_021dc7aa[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The message the talk shows (its receiver's, byte 0x1e of the talk). */
static u8 gatekeeper_states_line(Gatekeeper *self)
{
    return ((const MessageReceiver *) (const void *) &self->talk)->message;
}

/* func_ov048_02263284 (state 7's run): once no action of its runs and the camera stands
 * still, overlay 4's CheckInGate_Close and a wait of 60 frames; then the event ends. Agrees
 * always. */
int Gatekeeper_RunState7(Gatekeeper *self)
{
    switch (self->setup_step) {
        case GATEKEEPER_STATES_STEP_ACTION:
            if (!SceneAction_IsBusy(gatekeeper_states_action(self))) {
                self->setup_step = GATEKEEPER_STATES_STEP_CAMERA;
            }
            break;
        case GATEKEEPER_STATES_STEP_CAMERA:
            if (!CameraControl_IsMoving()) {
                CheckInGate_Close();
                self->countdown = GATEKEEPER_STATES_WAIT_GATE;
                self->setup_step = GATEKEEPER_STATES_STEP_WAIT;
            }
            break;
        case GATEKEEPER_STATES_STEP_WAIT:
            if (Countdown_Tick16(&self->countdown) == 0) {
                EventQueue_FinishObjectEvent(self);
            }
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov048_02263284, Gatekeeper_RunState7)

/* func_ov048_022632f0 (state 7's entry): its steps from the first; agrees. */
int Gatekeeper_EnterState7(Gatekeeper *self)
{
    self->setup_step = 0;
    return 1;
}
CLEAN_AS(func_ov048_022632f0, Gatekeeper_EnterState7)

/* The parent's data of a local session sent: this town's name and the current player's. */
static void gatekeeper_states_host_local(Gatekeeper *self)
{
    u8 data[GATEKEEPER_STATES_PARENT_BUFFER] = {0};
    u8 *record;

    GatekeeperTalk_StartSession(&self->talk, GATEKEEPER_STATES_SESSION_PARENT, 0);
    record = PlayerRecords_Current();
    MI_CpuCopy8((const void *) (uintptr_t) TownName_Name((int) (uintptr_t) data_021dc7aa), data, GATEKEEPER_STATES_NAME_SIZE);
    MI_CpuCopy8((const void *) (uintptr_t) PlayerId_Name((int) (uintptr_t) PlayerRecord_Player(record)),
                data + GATEKEEPER_STATES_NAME_SIZE, GATEKEEPER_STATES_NAME_SIZE);
    data[2 * GATEKEEPER_STATES_NAME_SIZE] = 0;
    LibraryOverlay_Require66();
    Local_Call02269638(data, GATEKEEPER_PARENT_DATA_SIZE);
    Session_Host();
}

/* func_ov048_02263300 (state 6's run): once no action of its runs and the camera stands
 * still, overlay 4's CheckInGate_Open and a wait of 60 frames; a system joining over the
 * Wi-Fi Connection then hosts its game instead (overlay 65, Wfc_HostGame, connect mode 0, the
 * session hosted). Once the wait is over, after line 0x46 or 0x6c: when hosting over the Wi-Fi
 * Connection, the event ends once the connection is updated; else a local session is started
 * as a parent (mode 1) carrying this town's name and the current player's, overlay 66 switched
 * in and the session hosted, and the event ends. While it waits, a host over the Wi-Fi
 * Connection keeps the connection updated. Agrees always.
 * BUG: of the 0x1a bytes of the parent's data, byte 0x19 is never set (the ROM sends whatever
 * its stack held there); this sends 0. */
int Gatekeeper_RunState6(Gatekeeper *self)
{
    switch (self->setup_step) {
        case GATEKEEPER_STATES_STEP_ACTION:
            if (!SceneAction_IsBusy(gatekeeper_states_action(self))) {
                self->setup_step = GATEKEEPER_STATES_STEP_CAMERA;
            }
            break;
        case GATEKEEPER_STATES_STEP_CAMERA:
            if (!CameraControl_IsMoving()) {
                CheckInGate_Open();
                self->countdown = GATEKEEPER_STATES_WAIT_GATE;
                self->setup_step = GATEKEEPER_STATES_STEP_WAIT;
                if (Net_GetMode() == GATEKEEPER_STATES_MODE_JOINING) {
                    LibraryOverlay_Require65();
                    Wfc_HostGame();
                    Session_SetConnectMode(data_020ccf94, 0);
                    Session_Host();
                }
            }
            break;
        case GATEKEEPER_STATES_STEP_WAIT:
            if (Countdown_Tick16(&self->countdown) != 0) {
                if (Net_GetMode() == GATEKEEPER_STATES_MODE_HOSTING) {
                    LibraryOverlay_RequireAny();
                    Net_UpdateConnection();
                }
                break;
            }
            if (gatekeeper_states_line(self) != GATEKEEPER_STATES_LINE_OPEN_46 &&
                gatekeeper_states_line(self) != GATEKEEPER_STATES_LINE_OPEN_6C) {
                break;
            }
            if (Net_GetMode() == GATEKEEPER_STATES_MODE_HOSTING) {
                LibraryOverlay_RequireAny();
                if (Net_UpdateConnection() != 0) {
                    EventQueue_FinishObjectEvent(self);
                }
            } else {
                gatekeeper_states_host_local(self);
                EventQueue_FinishObjectEvent(self);
            }
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov048_02263300, Gatekeeper_RunState6)

/* func_ov048_02263420 (state 6's entry): its steps from the first; agrees. */
int Gatekeeper_EnterState6(Gatekeeper *self)
{
    self->setup_step = 0;
    return 1;
}
CLEAN_AS(func_ov048_02263420, Gatekeeper_EnterState6)

/* ---- States 5 to 0 */

/* The point the player walks to in state 5: (16.0, 0, 17.5), with this acceleration. */
extern const Vec3 data_ov048_02263974;
#define GATEKEEPER_STATES_WALK_BACK 0x266

/* func_ov048_02263430 (state 5's run): once no action of its runs, the player is asked to walk
 * to (16.0, 0, 17.5); once the player's actor is not busy, the event ends. Agrees always.
 * QUIRK: the current player's record and the player's start position are fetched and not
 * used, and the steps go from 1 to 3.
 * REQUIRES: the player's field actor exists (PlayerActorOps_StartPosition is not NULL). */
int Gatekeeper_RunState5(Gatekeeper *self)
{
    PlayerRecords_Current();
    PlayerActorOps_StartPosition(GATEKEEPER_STATES_PLAYER);

    switch (self->setup_step) {
        case GATEKEEPER_STATES_STEP_ACTION:
            if (!SceneAction_IsBusy(gatekeeper_states_action(self))) {
                self->setup_step = GATEKEEPER_STATES_STEP_CAMERA;
            }
            break;
        case GATEKEEPER_STATES_STEP_CAMERA: {
            Vec3 point = data_ov048_02263974;
            PlayerActorOps_MoveTo(&point, GATEKEEPER_STATES_WALK_BACK, GATEKEEPER_STATES_PLAYER);
            self->setup_step = GATEKEEPER_STATES_STEP_WALKED;
            break;
        }
        case GATEKEEPER_STATES_STEP_WALKED:
            if (PlayerActorOps_IsBusy(GATEKEEPER_STATES_PLAYER) == 0) {
                EventQueue_FinishObjectEvent(self);
            }
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov048_02263430, Gatekeeper_RunState5)

/* func_ov048_022634bc (state 5's entry): its steps from the first; agrees. */
int Gatekeeper_EnterState5(Gatekeeper *self)
{
    self->setup_step = 0;
    return 1;
}
CLEAN_AS(func_ov048_022634bc, Gatekeeper_EnterState5)

/* func_ov048_022634cc (state 4's run): unless it calls the player (Gatekeeper_CallPlayer),
 * state 1 once it has turned back. Agrees always. */
int Gatekeeper_RunState4(Gatekeeper *self)
{
    SceneMotion *motion = gatekeeper_states_motion(self);

    if (Gatekeeper_CallPlayer(self)) {
        return 1;
    }
    if (SceneMotion_Kind(motion) == GATEKEEPER_STATES_MOTION_TURN && SceneMotion_IsDone(motion)) {
        Gatekeeper_SetState(self, GATEKEEPER_STATE_1);
    }
    return 1;
}
CLEAN_AS(func_ov048_022634cc, Gatekeeper_RunState4)

/* func_ov048_02263508 (state 4's entry): it turns back to the angle it started with; agrees. */
int Gatekeeper_EnterState4(Gatekeeper *self)
{
    SceneMotion_Request(gatekeeper_states_motion(self), GATEKEEPER_STATES_MOTION_TURN, GATEKEEPER_STATES_PRIORITY, 0, 0, 0,
                        self->home_angle, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov048_02263508, Gatekeeper_EnterState4)

/* func_ov048_02263544 (state 3's run): nothing; agrees. */
int Gatekeeper_RunState3(void)
{
    return 1;
}
CLEAN_AS(func_ov048_02263544, Gatekeeper_RunState3)

/* func_ov048_02263548 (state 3's entry): agrees. */
int Gatekeeper_EnterState3(void)
{
    return 1;
}
CLEAN_AS(func_ov048_02263548, Gatekeeper_EnterState3)

/* func_ov048_0226354c (state 2's run): once no action of its runs, the event ends. Agrees
 * always. */
int Gatekeeper_RunState2(Gatekeeper *self)
{
    if (!SceneAction_IsBusy(gatekeeper_states_action(self))) {
        EventQueue_FinishObjectEvent(self);
    }
    return 1;
}
CLEAN_AS(func_ov048_0226354c, Gatekeeper_RunState2)

/* func_ov048_02263570 (state 2's entry): its action asked to turn to the object its talk is
 * with (its motion argument; angle 0 without one) and talk; agrees. */
int Gatekeeper_EnterState2(Gatekeeper *self)
{
    int target = SceneBase_MotionArg(&self->talk.scene);
    int angle = 0;

    if (target != 0) {
        angle = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) target);
    }
    SceneAction_RequestTurnAndTalk(gatekeeper_states_action(self), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov048_02263570, Gatekeeper_EnterState2)

/* func_ov048_022635a8 (state 1's run): it calls the player when it may
 * (Gatekeeper_CallPlayer). Agrees always. */
int Gatekeeper_RunState1(Gatekeeper *self)
{
    Gatekeeper_CallPlayer(self);
    return 1;
}
CLEAN_AS(func_ov048_022635a8, Gatekeeper_RunState1)

/* func_ov048_022635b8 (state 1's entry): it stands; agrees. */
int Gatekeeper_EnterState1(Gatekeeper *self)
{
    SceneMotion_RequestStand(gatekeeper_states_motion(self), GATEKEEPER_STATES_PRIORITY, data_020c80f8);
    return 1;
}
CLEAN_AS(func_ov048_022635b8, Gatekeeper_EnterState1)

/* func_ov048_022635dc (state 0's run): an event of kind 6 asked for it (a talk). Agrees
 * always. */
int Gatekeeper_RunState0(Gatekeeper *self)
{
    EventQueue_RequestKind6(self, 0);
    return 1;
}
CLEAN_AS(func_ov048_022635dc, Gatekeeper_RunState0)

/* func_ov048_022635f0 (state 0's entry): agrees. */
int Gatekeeper_EnterState0(void)
{
    return 1;
}
CLEAN_AS(func_ov048_022635f0, Gatekeeper_EnterState0)

/* ---- Entering and running a state */

/* A state's row: its entry and its run (the null member pointer when it has none). */
typedef struct GatekeeperStateRow {
    MemberPointer enter;
    MemberPointer run;
} GatekeeperStateRow;
#define GATEKEEPER_STATES 0x12
extern GatekeeperStateRow data_ov048_022647a8[GATEKEEPER_STATES];

/* func_ov048_022635f4: state `state` entered when its entry agrees (or it has none).
 * REQUIRES: `state` is below 0x12 (the game's are). */
void Gatekeeper_SetState(Gatekeeper *self, int state)
{
    const GatekeeperStateRow *row = &data_ov048_022647a8[state];
    int agreed = 1;

    if (row->enter.function != 0) {
        agreed = MemberPointer_CallInt(&row->enter, self);
    }
    if (agreed) {
        self->state = state;
    }
}
CLEAN_AS(func_ov048_022635f4, Gatekeeper_SetState)

/* func_ov048_02263638 (vtable slot 0x68, each frame): its state's run, when it has one, and
 * what that answers; else 0.
 * REQUIRES: its state is below 0x12. */
int Gatekeeper_UpdateState(Gatekeeper *self)
{
    const GatekeeperStateRow *row = &data_ov048_022647a8[self->state];

    if (row->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&row->run, self);
}
CLEAN_AS(func_ov048_02263638, Gatekeeper_UpdateState)

/* ---- The tables, filled at start-up */

/* The talk's states (gatekeeper_talk.h): their functions; the null member pointer for state 0. */
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_ov048_02263eec, data_ov048_02263dc4, data_ov048_02263e04, data_ov048_02264104,
    data_ov048_02263f2c, data_ov048_02263d4c, data_ov048_02263f24, data_ov048_02263d54, data_ov048_02263de4,
    data_ov048_02263ec4, data_ov048_02264114, data_ov048_02263e3c, data_ov048_02263d7c, data_ov048_02263d6c,
    data_ov048_02263f04, data_ov048_02264124, data_ov048_02263d5c, data_ov048_0226412c, data_ov048_02263ef4,
    data_ov048_0226411c, data_ov048_02263ed4, data_ov048_0226410c;
/* Its own states: each one's entry, then its run. */
extern const MemberPointer data_ov048_022640fc, data_ov048_022640f4, data_ov048_022640ec, data_ov048_02263f4c,
    data_ov048_022640dc, data_ov048_02263f64, data_ov048_02263fcc, data_ov048_022640c4, data_ov048_022640bc,
    data_ov048_022640b4, data_ov048_022640ac, data_ov048_022640a4, data_ov048_0226409c, data_ov048_02264094,
    data_ov048_0226408c, data_ov048_02264084, data_ov048_0226407c, data_ov048_02264074, data_ov048_0226406c,
    data_ov048_02264064, data_ov048_0226405c, data_ov048_02264054, data_ov048_0226404c, data_ov048_02264044,
    data_ov048_0226403c, data_ov048_02264034, data_ov048_0226402c, data_ov048_02264024, data_ov048_0226401c,
    data_ov048_02264014, data_ov048_0226400c, data_ov048_02264004, data_ov048_02263ffc, data_ov048_02263ff4,
    data_ov048_02263fec, data_ov048_02263fe4;

/* __sinit_ov048_022639b0: the functions of the talk's 23 states (their flags are not written),
 * then the entries and runs of its own 18 states, in order. */
void Gatekeeper_InitTables(void)
{
    static const MemberPointer *const talk_states[GATEKEEPER_TALK_STATES] = {
        &__ptmf_null,         &data_ov048_02263eec, &data_ov048_02263dc4, &data_ov048_02263e04, &data_ov048_02264104,
        &data_ov048_02263f2c, &data_ov048_02263d4c, &data_ov048_02263f24, &data_ov048_02263d54, &data_ov048_02263de4,
        &data_ov048_02263ec4, &data_ov048_02264114, &data_ov048_02263e3c, &data_ov048_02263d7c, &data_ov048_02263d6c,
        &data_ov048_02263f04, &data_ov048_02264124, &data_ov048_02263d5c, &data_ov048_0226412c, &data_ov048_02263ef4,
        &data_ov048_0226411c, &data_ov048_02263ed4, &data_ov048_0226410c,
    };
    static const MemberPointer *const states[2 * GATEKEEPER_STATES] = {
        &data_ov048_022640fc, &data_ov048_022640f4, /* 0 */
        &data_ov048_022640ec, &data_ov048_02263f4c, /* 1 */
        &data_ov048_022640dc, &data_ov048_02263f64, /* 2 */
        &data_ov048_02263fcc, &data_ov048_022640c4, /* 3 */
        &data_ov048_022640bc, &data_ov048_022640b4, /* 4 */
        &data_ov048_022640ac, &data_ov048_022640a4, /* 5 */
        &data_ov048_0226409c, &data_ov048_02264094, /* 6 */
        &data_ov048_0226408c, &data_ov048_02264084, /* 7 */
        &data_ov048_0226407c, &data_ov048_02264074, /* 8 */
        &data_ov048_0226406c, &data_ov048_02264064, /* 9 */
        &data_ov048_0226405c, &data_ov048_02264054, /* 0xa */
        &data_ov048_0226404c, &data_ov048_02264044, /* 0xb */
        &data_ov048_0226403c, &data_ov048_02264034, /* 0xc */
        &data_ov048_0226402c, &data_ov048_02264024, /* 0xd */
        &data_ov048_0226401c, &data_ov048_02264014, /* 0xe */
        &data_ov048_0226400c, &data_ov048_02264004, /* 0xf */
        &data_ov048_02263ffc, &data_ov048_02263ff4, /* 0x10 */
        &data_ov048_02263fec, &data_ov048_02263fe4, /* 0x11 */
    };
    for (int i = 0; i < GATEKEEPER_TALK_STATES; i++) {
        data_ov048_02264344[i].run = *talk_states[i];
    }
    for (int i = 0; i < GATEKEEPER_STATES; i++) {
        data_ov048_022647a8[i].enter = *states[2 * i];
        data_ov048_022647a8[i].run = *states[2 * i + 1];
    }
}
CLEAN_AS(__sinit_ov048_022639b0, Gatekeeper_InitTables)
