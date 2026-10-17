/* Overlay 55's exchange character (xct_exchange.h): his object's vtable slots, the packets he
 * exchanges and his states. */
#include "xct_exchange.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/card_save.h"
#include "main/constellations.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/library_overlay.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_exit.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_share.h"
#include "main/scene_standard_anims.h"
#include "main/scene_tables.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/screen_transition.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "ov004/room_camera.h"
#include "xct_exchange_talk.h"

static_assert(sizeof(ExchangeBlock) == 0x950 && sizeof(WaitingLetter) == 0x104, "the packet's parts");
static_assert(offsetof(XctExchangePacket, letter) == 0x950 && offsetof(XctExchangePacket, kind) == 0xa54, "packet");
static_assert(sizeof(XctExchangePacket) == 0xa58, "the size Exchange_Init is given");
static_assert(offsetof(XctExchange, state) == 0x654 && offsetof(XctExchange, talk) == 0x658, "XctExchange");
static_assert(offsetof(XctExchange, save_failed) == 0x710 && offsetof(XctExchange, lid_closed) == 0x711, "XctExchange");
static_assert(offsetof(XctExchange, send) == 0x714 && offsetof(XctExchange, received) == 0x116c, "XctExchange");
static_assert(sizeof(XctExchange) == 0x1bc4, "the size XctExchange_Create allocates");
static_assert(sizeof(XctExchangeStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define XCT_EXCHANGE_POSITION 0x5c        /* Vec3: where he stands */
#define XCT_EXCHANGE_PERSON 0xea          /* u16: his person code */
#define XCT_EXCHANGE_MODEL 0xec           /* LayeredModel */
#define XCT_EXCHANGE_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define XCT_EXCHANGE_FACE 0x2ac           /* SceneFace */
#define XCT_EXCHANGE_ANIM 0x334           /* SpeakerAnim */
#define XCT_EXCHANGE_MOVER 0x350          /* SceneMover */
#define XCT_EXCHANGE_PROBE 0x3a8          /* the probe */
#define XCT_EXCHANGE_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define XCT_EXCHANGE_LOOK 0x3b0           /* SceneLook */
#define XCT_EXCHANGE_TALK_STATE 0x418     /* SceneTalkState */
#define XCT_EXCHANGE_EFFECTS 0x420        /* ActEffects */
#define XCT_EXCHANGE_COLLIDER 0x49c       /* CollisionContacts */
#define XCT_EXCHANGE_CARRIER 0x4cc        /* FieldOwnedBody */
#define XCT_EXCHANGE_EMITTER 0x514        /* SoundEmitterObject */
#define XCT_EXCHANGE_FOOTSTEPS 0x558      /* Footsteps */
#define XCT_EXCHANGE_MOTION 0x564         /* SceneMotion */
#define XCT_EXCHANGE_ACTION 0x618         /* SceneAction */
#define XCT_EXCHANGE_HEAP 0x640           /* PoolLink */

#define XCT_EXCHANGE_NO_PERSON 0xfff1

/* The slot of the town's own exchange block (ExchangeBlock_OfSlot). */
#define XCT_EXCHANGE_OWN_SLOT 4

/* The results of CardSave_WriteExchangeBlock taken for a failed save. */
#define XCT_EXCHANGE_SAVE_FAILED 1
#define XCT_EXCHANGE_SAVE_FAILED_4 4

/* The field actor of this console's player. */
#define XCT_EXCHANGE_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player talked to him, the
 * event of kind 6 he asked for, the event ended. */
#define XCT_EXCHANGE_EVENT_TALK 0
#define XCT_EXCHANGE_EVENT_OWN 1
#define XCT_EXCHANGE_EVENT_ENDED 8

/* The vtable slot of his talk scene that resets it (SceneBase_Reset). */
#define XCT_EXCHANGE_SLOT_RESET 0x08

/* The scene main's entry record takes after his talk, and its arguments. */
#define XCT_EXCHANGE_NEXT_SCENE 0x2c
#define XCT_EXCHANGE_NEXT_ARG 2

/* The motion kind he stands with (scene_motion_request.h). */
#define XCT_EXCHANGE_MOTION_STAND 0

/* The vtables of his class and of the classes he derives from. */
extern const u8 data_ov055_02260fd4[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model and texture file names: "npc_sp/model/xct.nsbmd", "npc_sp/model/xct_tex.nsbtx". */
extern const char data_ov055_02260ec0[];
extern const char data_ov055_02260ef0[];
/* The functions of his states (filled at start-up by __sinit_ov055_02260db4). */
extern XctExchangeStep data_ov055_02261084[XCT_EXCHANGE_STATES];
/* Him, from his start to his leaving. */
extern XctExchange *data_ov055_02261080;
/* The slot of the library overlays, and the overlays it is given. */
extern LibraryOverlaySlot data_021d11c4;
extern char SDK_OVERLAY_ov067_ID;
extern char SDK_OVERLAY_ov068_ID;
/* The letter waiting for the current player (part_1704c of the state block). */
extern WaitingLetter data_021f37f4;
/* The screen's transition between scenes. */
extern ScreenTransition data_021c75b8;
/* The word his motion requests carry. */
extern u16 data_020c80f8;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static u8 *xct_exchange_part(XctExchange *xct, u32 offset)
{
    return xct->base + offset;
}

static SceneAction *xct_exchange_action(XctExchange *xct)
{
    return (SceneAction *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_ACTION);
}

static ExchangeBlock *xct_exchange_own_block(void)
{
    return (ExchangeBlock *) (uintptr_t) (u32) ExchangeBlock_OfSlot(XCT_EXCHANGE_OWN_SLOT);
}

static int xct_exchange_overlay(const char *id)
{
    return (int) (uintptr_t) id;
}

static int xct_exchange_agrees(XctExchange *xct)
{
    if (SceneAction_IsBusy(xct_exchange_action(xct)) != 0) {
        return 0;
    }
    return SceneShare_IsHeld(xct->base) == 0;
}

/* ---- His object */

/* func_ov055_02260420 (vtable slot 0x40): the destructors of the two packets' letters and
 * blocks (the received packet first), his talk scene's, then the special character's; the
 * object. */
XctExchange *XctExchange_Destruct(XctExchange *xct)
{
    *(const u8 **) (void *) xct->base = data_ov055_02260fd4;
    WaitingLetter_Destruct(&xct->received.letter);
    ExchangeBlock_Destruct(&xct->received.block);
    WaitingLetter_Destruct(&xct->send.letter);
    ExchangeBlock_Destruct(&xct->send.block);
    XctExchangeTalk_Destruct(&xct->talk);
    SpecialSceneObject_DestructBody(xct);
    return xct;
}
CLEAN_AS(func_ov055_02260420, XctExchange_Destruct)

/* func_ov055_02260478 (vtable slot 0x44): the same, then the object freed. */
XctExchange *XctExchange_DestructDelete(XctExchange *xct)
{
    *(const u8 **) (void *) xct->base = data_ov055_02260fd4;
    WaitingLetter_Destruct(&xct->received.letter);
    ExchangeBlock_Destruct(&xct->received.block);
    WaitingLetter_Destruct(&xct->send.letter);
    ExchangeBlock_Destruct(&xct->send.block);
    XctExchangeTalk_Destruct(&xct->talk);
    SpecialSceneObject_DestructBody(xct);
    Heap_FreeAux(xct);
    return xct;
}
CLEAN_AS(func_ov055_02260478, XctExchange_DestructDelete)

/* func_ov055_022604d4: the library slot's overlay ended and overlay 68 loaded into it. */
void XctExchange_LoadLibrary68(void *unused)
{
    (void) unused;
    LibraryOverlay_End(&data_021d11c4);
    LibraryOverlay_Load(&data_021d11c4, xct_exchange_overlay(&SDK_OVERLAY_ov068_ID));
}
CLEAN_AS(func_ov055_022604d4, XctExchange_LoadLibrary68)

/* func_ov055_022604f4: the library slot's overlay ended and overlay 67 (the exchange library)
 * loaded into it. */
void XctExchange_LoadLibrary67(void *unused)
{
    (void) unused;
    LibraryOverlay_End(&data_021d11c4);
    LibraryOverlay_Load(&data_021d11c4, xct_exchange_overlay(&SDK_OVERLAY_ov067_ID));
}
CLEAN_AS(func_ov055_022604f4, XctExchange_LoadLibrary67)

/* func_ov055_02260514: unless a save failed before, the exchange block saved; a failure is
 * remembered.
 * QUIRK: the town's own block is looked up first, and its address left unused. */
void XctExchange_SaveBlock(XctExchange *xct)
{
    if (xct->save_failed != 0) {
        return;
    }
    (void) ExchangeBlock_OfSlot(XCT_EXCHANGE_OWN_SLOT);
    int result = CardSave_WriteExchangeBlock();
    if (result == XCT_EXCHANGE_SAVE_FAILED || result == XCT_EXCHANGE_SAVE_FAILED_4) {
        xct->save_failed = 1;
    }
}
CLEAN_AS(func_ov055_02260514, XctExchange_SaveBlock)

/* func_ov055_02260544: a random constellation drafted; the town's own exchange block moved
 * into the packet he sends (which then carries a block) and cleared in the town; then, unless
 * a save failed before, the exchange block saved and a failure remembered. */
void XctExchange_PrepareSend(XctExchange *xct)
{
    Constellations_DraftRandom();
    ExchangeBlock *own = xct_exchange_own_block();
    MI_CpuCopy8(own, &xct->send.block, sizeof(ExchangeBlock));
    xct->send.kind = XCT_EXCHANGE_CARRIES_BLOCK;
    ExchangeBlock_Clear(own);
    if (xct->save_failed == 0) {
        int result = CardSave_WriteExchangeBlock();
        if (result == XCT_EXCHANGE_SAVE_FAILED || result == XCT_EXCHANGE_SAVE_FAILED_4) {
            xct->save_failed = 1;
        }
    }
}
CLEAN_AS(func_ov055_02260544, XctExchange_PrepareSend)

/* func_ov055_022605a0 (vtable slot 0x4c, an event about him): when the player talked to him or
 * his own event starts, his talk scene is reset and given the player's field actor, and he
 * talks (state 1); once the event ended he waits (state 0). */
void XctExchange_OnEvent(XctExchange *xct, int code)
{
    switch (code) {
        case XCT_EXCHANGE_EVENT_TALK:
        case XCT_EXCHANGE_EVENT_OWN: {
            u32 vtable = *(const u32 *) (const void *) &xct->talk;
            u32 reset = *(const u32 *) (uintptr_t) (vtable + XCT_EXCHANGE_SLOT_RESET);
            ((void (*)(XctExchangeTalk *))(uintptr_t) reset)(&xct->talk);
            SceneBase_SetMotionArg(&xct->talk.base, SceneObject_ActorObject(xct->base, XCT_EXCHANGE_PLAYER_ACTOR));
            XctExchange_SetState(xct, XCT_EXCHANGE_TALK);
            break;
        }
        case XCT_EXCHANGE_EVENT_ENDED:
            XctExchange_SetState(xct, XCT_EXCHANGE_WAIT);
            break;
    }
}
CLEAN_AS(func_ov055_022605a0, XctExchange_OnEvent)

/* func_ov055_02260610 (vtable slot 0x58): his own event may start while his action is idle and
 * nothing holds him. */
int XctExchange_AgreesToOwnEvent(XctExchange *xct)
{
    return xct_exchange_agrees(xct);
}
CLEAN_AS(func_ov055_02260610, XctExchange_AgreesToOwnEvent)

/* func_ov055_0226063c (vtable slot 0x48): the player may talk to him under the same terms. */
int XctExchange_AgreesToTalk(XctExchange *xct)
{
    return xct_exchange_agrees(xct);
}
CLEAN_AS(func_ov055_0226063c, XctExchange_AgreesToTalk)

/* func_ov055_02260668: the block of the packet he sends copied back to the town's own. */
void XctExchange_RestoreBlock(XctExchange *xct)
{
    MI_CpuCopy8(&xct->send.block, xct_exchange_own_block(), sizeof(ExchangeBlock));
}
CLEAN_AS(func_ov055_02260668, XctExchange_RestoreBlock)

/* func_ov055_0226068c: what came put in place. A letter becomes the letter waiting for the
 * current player and the town gets its own block back; an exchange block replaces the town's,
 * its bottle drifted once more and set to arrive at once. Anything else is dropped. */
void XctExchange_TakeReceived(XctExchange *xct)
{
    ExchangeBlock *own = xct_exchange_own_block();

    if (xct->received.kind == XCT_EXCHANGE_CARRIES_LETTER) {
        MI_CpuCopy8(&xct->received.letter, &data_021f37f4, sizeof(WaitingLetter));
        XctExchange_RestoreBlock(xct);
    } else if (xct->received.kind == XCT_EXCHANGE_CARRIES_BLOCK) {
        MI_CpuCopy8(&xct->received.block, own, sizeof(ExchangeBlock));
        ExchangeBlock_AddDrift(own);
        ExchangeBlock_SetArrivesAtOnce(own, 1);
    }
}
CLEAN_AS(func_ov055_0226068c, XctExchange_TakeReceived)

/* func_ov055_02260b24: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded); him at a word-aligned address, as
 * every object of the game (the ROM's store drops the low two bits). */
void XctExchange_SetState(XctExchange *xct, int state)
{
    const XctExchangeStep *step = &data_ov055_02261084[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, xct);
    }
    if (taken != 0) {
        xct->state = state;
    }
}
CLEAN_AS(func_ov055_02260b24, XctExchange_SetState)

/* func_ov055_02260b68 (vtable slot 0x68, each frame): his state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: his state is 0 to 2. */
int XctExchange_Update(XctExchange *xct)
{
    const XctExchangeStep *step = &data_ov055_02261084[xct->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, xct);
}
CLEAN_AS(func_ov055_02260b68, XctExchange_Update)

/* func_ov055_02260bb4 (vtable slot 0x70): his model's file name. */
int XctExchange_ModelName(void)
{
    return (int) (uintptr_t) data_ov055_02260ec0;
}
CLEAN_AS(func_ov055_02260bb4, XctExchange_ModelName)

/* func_ov055_02260bbc (vtable slot 0x6c): his texture's file name. */
int XctExchange_TextureName(void)
{
    return (int) (uintptr_t) data_ov055_02260ef0;
}
CLEAN_AS(func_ov055_02260bbc, XctExchange_TextureName)

/* func_ov055_02260bc4 (vtable slot 0x0c, his leaving): unless the special character refuses
 * to leave, he is no longer the one there, the library slot gets overlay 68 back, the event
 * queue's flag 1 is cleared and the exchange block saved. Whether he left. */
int XctExchange_Leave(XctExchange *xct)
{
    if (SpecialSceneObject_Leave(xct) == 0) {
        return 0;
    }
    data_ov055_02261080 = NULL;
    XctExchange_LoadLibrary68(xct);
    EventQueue_ClearFlag1();
    XctExchange_SaveBlock(xct);
    return 1;
}
CLEAN_AS(func_ov055_02260bc4, XctExchange_Leave)

/* func_ov055_02260bf8 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he is the one there, the library slot gets overlay 67, he waits (state 0), the room's
 * camera looks at him, the event queue's flag 1 is set and his packet is made ready. Whether
 * he started. */
int XctExchange_Start(XctExchange *xct)
{
    if (SpecialSceneObject_Start(xct) == 0) {
        return 0;
    }
    data_ov055_02261080 = xct;
    XctExchange_LoadLibrary67(xct);
    XctExchange_SetState(xct, XCT_EXCHANGE_WAIT);
    RoomCamera_SetModeLookAt((const Vec3 *) (const void *) xct_exchange_part(xct, XCT_EXCHANGE_POSITION));
    EventQueue_SetFlag1();
    XctExchange_PrepareSend(xct);
    return 1;
}
CLEAN_AS(func_ov055_02260bf8, XctExchange_Start)

/* func_ov055_02260c38 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int XctExchange_Init(XctExchange *xct)
{
    if (SpecialSceneObject_Init(xct) == 0) {
        return 0;
    }
    SceneObject_SetScene(xct->base, &xct->talk.base);
    XctExchangeTalk_Begin(&xct->talk, xct);
    return 1;
}
CLEAN_AS(func_ov055_02260c38, XctExchange_Init)

/* func_ov055_02260c68 (his record's create function): a zeroed block of 0x1bc4 bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and members
 * in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link, then his
 * class's vtable, his talk scene and the two packets' blocks and letters. Null when there is no
 * room. */
void *XctExchange_Create(void)
{
    XctExchange *xct = (XctExchange *) Heap_AllocAuxZeroed(sizeof(XctExchange));
    if (xct == NULL) {
        return NULL;
    }
    u8 *object = xct->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_PERSON) = XCT_EXCHANGE_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_ANIM));
    SceneMover_Construct((SceneMover *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_MOVER));
    SceneProbe_Construct(xct_exchange_part(xct, XCT_EXCHANGE_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_MOTION));
    SceneAction_Construct(xct_exchange_action(xct));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_HEAP));
    *(const u8 **) (void *) object = data_ov055_02260fd4;
    XctExchangeTalk_Construct(&xct->talk);
    ExchangeBlock_Construct(&xct->send.block);
    WaitingLetter_Construct(&xct->send.letter);
    ExchangeBlock_Construct(&xct->received.block);
    WaitingLetter_Construct(&xct->received.letter);
    return xct;
}
CLEAN_AS(func_ov055_02260c68, XctExchange_Create)

/* ---- His states */

/* func_ov055_02260a70 (state 2's update): 1. */
int XctExchange_UpdateDone(void)
{
    return 1;
}
CLEAN_AS(func_ov055_02260a70, XctExchange_UpdateDone)

/* func_ov055_02260a74 (state 2's entry): 1. */
int XctExchange_EnterDone(void)
{
    return 1;
}
CLEAN_AS(func_ov055_02260a74, XctExchange_EnterDone)

/* func_ov055_02260a78 (state 1's update): once his action is idle, main's entry record takes
 * scene 0x2c (arguments 2, 2) and he is done (state 2). 1. */
int XctExchange_UpdateTalk(XctExchange *xct)
{
    if (SceneAction_IsBusy(xct_exchange_action(xct)) == 0) {
        SceneExit_SetToScene((SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord(), XCT_EXCHANGE_NEXT_SCENE,
                             XCT_EXCHANGE_NEXT_ARG, XCT_EXCHANGE_NEXT_ARG);
        XctExchange_SetState(xct, XCT_EXCHANGE_DONE);
    }
    return 1;
}
CLEAN_AS(func_ov055_02260a78, XctExchange_UpdateTalk)

/* func_ov055_02260aac (state 1's entry): he talks (keeping the camera). 1. */
int XctExchange_EnterTalk(XctExchange *xct)
{
    SceneAction_RequestTalk(xct_exchange_action(xct), 0, 1);
    return 1;
}
CLEAN_AS(func_ov055_02260aac, XctExchange_EnterTalk)

/* func_ov055_02260ac8 (state 0's update): once the screen's transition shows the scene, he
 * talks (state 1). 1. */
int XctExchange_UpdateWait(XctExchange *xct)
{
    if (data_021c75b8.state == SCREEN_TRANSITION_SHOWN) {
        XctExchange_SetState(xct, XCT_EXCHANGE_TALK);
    }
    return 1;
}
CLEAN_AS(func_ov055_02260ac8, XctExchange_UpdateWait)

/* func_ov055_02260af0 (state 0's entry): he stands (priority 1, the plain word). 1. */
int XctExchange_EnterWait(XctExchange *xct)
{
    SceneMotion_Request((SceneMotion *) (void *) xct_exchange_part(xct, XCT_EXCHANGE_MOTION), XCT_EXCHANGE_MOTION_STAND, 1, 0,
                        0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov055_02260af0, XctExchange_EnterWait)
