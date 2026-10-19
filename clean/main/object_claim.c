/* Objects claimed through the session, and the events about them sent to the other systems
 * (object_claim.h). */
#include "object_claim.h"

#include "clean.h"
#include "scene_object_base.h"
#include "session.h"
#include "link_global.h"
#include "session_players.h"

/* The session. */
extern NetSession *data_020ccf94;
/* The answer this system waits for (object_claim.h). */
extern u8 data_020dab94;
/* The id each slot has claimed, kept by the host (0: none). */
extern u32 OSiHeapInfo[SESSION_SLOTS];
/* An id no slot may claim. */
extern u32 data_021c72d4;

/* A handler of message 23, by payload byte 0. */
typedef void ObjectClaimHandler(const u8 *payload, int slot);
extern ObjectClaimHandler *const data_020dab98[];

/* The id in payload bytes 1-4 (little-endian). */
static u32 payload_id(const u8 *payload)
{
    return (u32) payload[1] | (u32) payload[2] << 8 | (u32) payload[3] << 16 | (u32) payload[4] << 24;
}

/* The id written to payload bytes 1-4. */
static void put_id(u8 *payload, u32 id)
{
    payload[1] = (u8) id;
    payload[2] = (u8) (id >> 8);
    payload[3] = (u8) (id >> 16);
    payload[4] = (u8) (id >> 24);
}

/* `object` told of `code` (its vtable slot 0x4c), for `participant`. */
static void tell(SceneObjectBase *object, int code, u8 participant)
{
    ((SceneObjectBaseOnEvent *) SceneObjectBase_Slot(object, SCENE_OBJECT_BASE_SLOT_ON_EVENT))(object, code, participant);
}

/* The object's question in vtable slot `offset` about `player`. */
static int ask(SceneObjectBase *object, u32 offset, int player)
{
    return ((SceneObjectBaseAsk *) SceneObjectBase_Slot(object, offset))(object, (SceneObjectBase *) (uintptr_t) player);
}

/* ---- Received ---- */

/* func_0203f15c (codes 4 and 5): an act or an event about the object of the payload's id, from
 * `slot`. Without that object or the sender's player, an act is answered no (to the sender; to
 * this system's own act, by the answer byte at once). An event is told to the object for the
 * sender. An act is asked of the object (act 0: slot 0x48, may act; 5: slot 0x54; 1: slot 0x58;
 * any other: no) about the sender's player: yes tells the object the act starts and answers
 * yes, no answers no. For this system's own act the object is told it is for this system's
 * player (4) and the answer goes to the answer byte. */
void ObjectClaim_HandleObjectMessage(const u8 *payload, int slot)
{
    u8 value = payload[5];
    SceneObjectBase *object = (SceneObjectBase *) (uintptr_t) SceneObjectBase_FindAddress((int) payload_id(payload));
    int player = (int) (uintptr_t) SessionPlayers_ActorOf(slot);

    if (object == NULL || player == 0) {
        if (payload[0] == OBJECT_CLAIM_ACT) {
            if (Session_IsLocalSlot(data_020ccf94, slot) == 0) {
                ObjectClaim_SendAnswer(OBJECT_CLAIM_NO, slot);
            } else {
                data_020dab94 = OBJECT_CLAIM_NO;
            }
        }
        return;
    }
    if (payload[0] == OBJECT_CLAIM_EVENT) {
        tell(object, value, (u8) slot);
        return;
    }

    int agreed = 0;
    switch (value) {
        case 0:
            agreed = ask(object, SCENE_OBJECT_BASE_SLOT_MAY_ACT, player);
            break;
        case 5:
            agreed = ask(object, SCENE_OBJECT_BASE_SLOT_ASK_54, player);
            break;
        case 1:
            agreed = ask(object, SCENE_OBJECT_BASE_SLOT_ASK_58, player);
            break;
    }
    if (Session_IsLocalSlot(data_020ccf94, slot) == 0) {
        if (agreed) {
            tell(object, 3, (u8) slot);
            ObjectClaim_SendAnswer(OBJECT_CLAIM_YES, slot);
        } else {
            ObjectClaim_SendAnswer(OBJECT_CLAIM_NO, slot);
        }
    } else {
        if (agreed) {
            tell(object, 3, 4);
            data_020dab94 = OBJECT_CLAIM_YES;
        } else {
            data_020dab94 = OBJECT_CLAIM_NO;
        }
    }
}
CLEAN_AS(func_0203f15c, ObjectClaim_HandleObjectMessage)

/* func_0203f260 (code 3, on the host): `slot` lets its claim go. */
void ObjectClaim_HandleRelease(const u8 *payload, int slot)
{
    (void) payload;
    ObjectClaim_Clear((u8) slot);
}
CLEAN_AS(func_0203f260, ObjectClaim_HandleRelease)

/* func_0203f26c (codes 1 and 2): the host's answer. */
void ObjectClaim_HandleAnswer(const u8 *payload)
{
    data_020dab94 = payload[0];
}
CLEAN_AS(func_0203f26c, ObjectClaim_HandleAnswer)

/* func_0203f278 (code 0, on the host): `slot` asks for the payload's id; given when free, and
 * answered either way.
 * REQUIRES: `slot` is a session slot (0-3); the check reads the table at its low byte, the
 * claim writes it at the whole value. */
void ObjectClaim_HandleClaim(const u8 *payload, int slot)
{
    u32 id = payload_id(payload);

    if (ObjectClaim_IsFree((u8) slot, (int) id)) {
        OSiHeapInfo[slot] = id;
        ObjectClaim_SendAnswer(OBJECT_CLAIM_YES, slot);
    } else {
        ObjectClaim_SendAnswer(OBJECT_CLAIM_NO, slot);
    }
}
CLEAN_AS(func_0203f278, ObjectClaim_HandleClaim)

/* ---- Sent ---- */

/* func_0203f2c4: with the session linked, `code` (an act or an event) about the object `id`,
 * with `value`, sent to every system in the scene; the answer byte holds the code until an
 * answer comes. */
void ObjectClaim_SendObjectMessage(u32 id, u8 value, u8 code)
{
    u8 payload[6];

    if (Session_IsLinked(data_020ccf94) == 0) {
        return;
    }
    data_020dab94 = code;
    payload[0] = code;
    put_id(payload, id);
    payload[5] = value;
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, payload, sizeof payload);
    Session_EndMessage(session, OBJECT_CLAIM_MESSAGE, OBJECT_CLAIM_TO_SCENE);
}
CLEAN_AS(func_0203f2c4, ObjectClaim_SendObjectMessage)

/* func_0203f320: event `code` told to the object `id` sent to the scene. */
void ObjectClaim_SendEvent(int id, int code)
{
    ObjectClaim_SendObjectMessage((u32) id, (u8) code, OBJECT_CLAIM_EVENT);
}
CLEAN_AS(func_0203f320, ObjectClaim_SendEvent)

/* func_0203f32c: act `act` on the object `id` sent to the scene. */
void ObjectClaim_SendAct(int id, int act)
{
    ObjectClaim_SendObjectMessage((u32) id, (u8) act, OBJECT_CLAIM_ACT);
}
CLEAN_AS(func_0203f32c, ObjectClaim_SendAct)

/* func_0203f338: how an act on a person is decided: here (OBJECT_CLAIM_DECIDED) without a
 * linked session or when func_020a7278 says yes, else shared (OBJECT_CLAIM_SHARED). */
int ObjectClaim_Mode(void)
{
    if (Session_IsLinked(data_020ccf94) == 0) {
        return OBJECT_CLAIM_DECIDED;
    }
    if (LinkGlobal_HoldsScene() == 0) {
        return OBJECT_CLAIM_SHARED;
    }
    return OBJECT_CLAIM_DECIDED;
}
CLEAN_AS(func_0203f338, ObjectClaim_Mode)

/* func_0203f364: with the session linked, this system's claim let go: in the host's own table,
 * or by asking the host. */
void ObjectClaim_Release(void)
{
    NetSession *session = data_020ccf94;

    if (Session_IsLinked(session) == 0) {
        return;
    }
    if (session->local_slot == OBJECT_CLAIM_HOST_SLOT) {
        ObjectClaim_Clear(OBJECT_CLAIM_HOST_SLOT);
    } else {
        ObjectClaim_SendAnswer(OBJECT_CLAIM_RELEASE, OBJECT_CLAIM_HOST_SLOT);
    }
}
CLEAN_AS(func_0203f364, ObjectClaim_Release)

/* func_0203f394: with the session linked, the object `id` claimed: the host writes its own
 * slot's claim, another system asks the host and waits (answer byte 0).
 * QUIRK: the host's claim is written without checking that it is free (ObjectClaim_Ask checks
 * it first). */
void ObjectClaim_Claim(u32 id)
{
    NetSession *session = data_020ccf94;

    if (Session_IsLinked(session) == 0) {
        return;
    }
    if (session->local_slot == OBJECT_CLAIM_HOST_SLOT) {
        OSiHeapInfo[OBJECT_CLAIM_HOST_SLOT] = id;
        return;
    }
    u8 payload[5];
    data_020dab94 = OBJECT_CLAIM_CLAIM;
    payload[0] = OBJECT_CLAIM_CLAIM;
    put_id(payload, id);
    session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, payload, sizeof payload);
    Session_EndMessage(session, OBJECT_CLAIM_MESSAGE, OBJECT_CLAIM_HOST_SLOT);
}
CLEAN_AS(func_0203f394, ObjectClaim_Claim)

/* func_0203f400: whether the object `id` may be claimed: given without a linked session; on
 * the host, given when free for the host's slot, else refused; elsewhere it must be asked. */
int ObjectClaim_Ask(int id)
{
    NetSession *session = data_020ccf94;

    if (Session_IsLinked(session) == 0) {
        return OBJECT_CLAIM_ASK_GIVEN;
    }
    if (session->local_slot != OBJECT_CLAIM_HOST_SLOT) {
        return OBJECT_CLAIM_ASK_ASKED;
    }
    if (!ObjectClaim_IsFree(OBJECT_CLAIM_HOST_SLOT, id)) {
        return OBJECT_CLAIM_ASK_REFUSED;
    }
    return OBJECT_CLAIM_ASK_GIVEN;
}
CLEAN_AS(func_0203f400, ObjectClaim_Ask)

/* ---- The host's table ---- */

/* func_0203f444: `slot`'s claim let go;
 * the table's address.
 * REQUIRES: `slot` is a session slot (0-3). */
int ObjectClaim_Clear(int slot)
{
    OSiHeapInfo[slot] = 0;
    return (int) (uintptr_t) OSiHeapInfo;
}
CLEAN_AS(func_0203f444, ObjectClaim_Clear)

/* func_0203f454: whether `slot` may claim `id`: it holds no claim, `id` is not the id that may
 * not be claimed and no slot holds it.
 * REQUIRES: `slot` is a session slot (0-3). */
int ObjectClaim_IsFree(int slot, int id)
{
    if (OSiHeapInfo[slot] != 0) {
        return 0;
    }
    if (data_021c72d4 == (u32) id) {
        return 0;
    }
    for (int i = 0; i < SESSION_SLOTS; i++) {
        if ((u32) id == OSiHeapInfo[i]) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_0203f454, ObjectClaim_IsFree)

/* func_0203f490: a message of the one byte `code` (its low byte) sent to `slot`. */
void ObjectClaim_SendAnswer(int code, int slot)
{
    NetSession *session = data_020ccf94;
    u8 payload = (u8) code;

    Session_BeginMessage(session);
    Session_AppendMessage(session, &payload, 1);
    Session_EndMessage(session, OBJECT_CLAIM_MESSAGE, (u32) slot);
}
CLEAN_AS(func_0203f490, ObjectClaim_SendAnswer)

/* func_0203f4c4: no claims, no id barred from claims (data_021c72d4) and nothing asked. */
void ObjectClaim_Reset(void)
{
    for (int i = 0; i < SESSION_SLOTS; i++) {
        OSiHeapInfo[i] = 0;
    }
    data_021c72d4 = 0;
    data_020dab94 = OBJECT_CLAIM_ANSWER_NONE;
}
CLEAN_AS(func_0203f4c4, ObjectClaim_Reset)

/* func_0203f4ec: message 23 from `slot` handed to its handler (data_020dab98), by payload byte
 * 0.
 * REQUIRES: byte 0 is a code (0-5). */
void ObjectClaim_Dispatch(const u8 *payload, int slot)
{
    data_020dab98[payload[0]](payload, slot);
}
CLEAN_AS(func_0203f4ec, ObjectClaim_Dispatch)
