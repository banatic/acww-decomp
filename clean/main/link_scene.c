/* The linked systems moving between scenes (link_scene.h).
 *
 * QUIRK: several functions take the link state as a parameter but read slots' places through
 * helpers of the one link state the game has (data_021f4320, func_020a72d0, func_020a7300,
 * func_020a7330, func_020a7394); every caller passes that one. */
#include "link_scene.h"

#include "clean.h"
#include "scene_exit.h"
#include "scene_query.h"
#include "session.h"

static_assert(sizeof(LinkStatePlace) == 3 && sizeof(LinkStateMove) == 8, "link state places");
static_assert(offsetof(LinkState, moves) == 0x0c && offsetof(LinkState, arrived) == 0x2c, "link state");
static_assert(offsetof(LinkState, changes) == 0x3c && offsetof(LinkState, enters_first) == 0x5c, "link state");
static_assert(offsetof(LinkState, scene_phase) == 0x60 && offsetof(LinkState, acked) == 0x68, "link state");
static_assert(offsetof(LinkState, leaving_holder) == 0x6c && offsetof(LinkState, released) == 0x7c, "link state");
static_assert(offsetof(LinkState, leaving_guest) == 0x80, "link state");

extern NetSession *data_020ccf94;
extern LinkState data_021f4320;
/* The process class of the scene asked for (scene_process_base.h); 5 is the process between
 * scenes. */
extern u16 data_020e3c80;
/* The screen's state (scene_process_base.h); 0 while it is closed. */
extern u8 data_021c75b8;
/* The slots and masks LinkScene_HostStep starts from: both LINK_STATE_SLOTS. */
extern const u32 data_020e3cdc[2];

/* A slot's place read through data_021f4320: whether it moves (0 for no slot), whether it holds
 * its scene (1 for no slot) and its scene (LINK_SCENE_NONE for no slot). */
extern int func_020a72d0(int slot);
extern u8 func_020a7300(int slot);
extern int func_020a7330(int slot);
/* data_021f4320's place of `slot` given the fields of `mask` (bit 0 the scene, 1 holder, 2
 * moving), then the held session messages routed (Session_RouteHeldMessages). */
extern void func_020a7394(int slot, int scene, int holder, int moving, int mask);
/* data_021f4320's pending changes of `slot` added to (fields of `mask`). */
extern void func_020a7360(int slot, int scene, int holder, int moving, int mask);
/* data_021f4320's arrived word of `slot` set. */
extern void func_020a7380(int slot, int value);
/* Both always 0. */
extern int func_020a7450(void);
extern int func_020a744c(void);
/* The sections of the received bundle 16 and bundle 15 handed out (session.h). */
extern void func_020a7454(void);
extern void func_020a753c(void);
/* Bundle 16 built and sent to `slot`; bundle 15 built and sent to `slot`. */
extern void func_020a7064(int slot);
extern void func_020a70a8(int slot);
/* The move to the entry record's next scene asked of the host (message 8, or the host's own
 * queue directly). */
extern void func_020a6f88(void);
/* Whether this system's place moves (1 without a slot). */
extern int func_020a7258(void);

/* The parts' own helpers: an arrived word cleared and read; a move reset (no slot, no scene)
 * and read; a place read; a pending change cleared and read. */
extern void func_020a76d0(u32 *arrived);
extern void func_020a76d8(const u32 *arrived, u32 *value);
extern void func_020a76f8(LinkStateMove *move);
extern void func_020a7704(const LinkStateMove *move, s32 *slot, u8 *scene);
extern void func_020a7738(const LinkStatePlace *place, u8 *scene, u8 *holder, u8 *moving);
extern void func_020a7768(LinkStatePlaceChange *change);
extern void func_020a7778(const LinkStatePlaceChange *change, u8 *scene, u8 *holder, u8 *moving, u32 *mask);
/* A place as the two bytes of message 9: made, filled (with its slot) and ended; and as the
 * two bytes of message 11 (always for slot 0). */
extern u8 *func_020a7820(u8 *packed);
extern void func_020a77f4(u8 *packed, int slot, int scene, int holder, u8 moving, u32 mask);
extern u8 *func_020a7810(u8 *packed);
extern u8 *func_020a7880(u8 *packed);
extern void func_020a7850(u8 *packed, int scene, int holder, int moving, int mask);
extern u8 *func_020a7870(u8 *packed);

/* Clears `size` bytes at `dst`. */
extern void *func_02137550(void *dst, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define CHANGE_CLASS 5 /* the process class between scenes */

#define MASK_SCENE 1
#define MASK_HOLDER 2
#define MASK_MOVING 4
#define MASK_ALL 7

/* Session messages (session_message.h) and where they are sent. */
enum {
    MESSAGE_PLACE = 9,
    MESSAGE_ARRIVED = 10,
    MESSAGE_PLACE_CHANGE = 11,
    MESSAGE_ACK = 13,
    MESSAGE_ASK_STATE = 14,
    MESSAGE_RELEASE = 17,
};
#define TO_HOST 0
#define TO_ALL 4

#define HOST_SLOT 0

/* The highest slot in the session that moves, or LINK_STATE_SLOTS. */
static int moving_slot(NetSession *session)
{
    for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) && func_020a72d0(slot)) {
            return slot;
        }
    }
    return LINK_STATE_SLOTS;
}

/* A message without payload sent. */
static void send_empty(int handler, int to)
{
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_EndMessage(session, (u32) handler, (u32) to);
}

/* func_020a6188: the slot that moves (the highest), when it is new: if this system holds its
 * scene and that slot is another system in the same scene, the slot is let go (message 17)
 * unless the scene is one a join or leave passes through. The slot is then noted. */
void LinkScene_ReleaseLeavingGuest(LinkState *state)
{
    NetSession *session = data_020ccf94;
    int own = session->local_slot;
    int mover = moving_slot(session);

    if ((u32) mover == LinkScene_LeavingGuest(state)) {
        return;
    }
    if (mover >= LINK_STATE_SLOTS) {
        LinkScene_SetLeavingGuest(state, LINK_STATE_SLOTS);
        return;
    }
    if (!Session_IsLocalSlot(session, mover) && func_020a7300(own) != 0 && func_020a7330(mover) == SceneQuery_Current() &&
        !LinkScene_IsLinkingScene(SceneQuery_Current())) {
        send_empty(MESSAGE_RELEASE, mover);
    }
    LinkScene_SetLeavingGuest(state, (u32) mover);
}
CLEAN_AS(func_020a6188, LinkScene_ReleaseLeavingGuest)

/* func_020a6230 */
u32 LinkScene_LeavingGuest(LinkState *state)
{
    return state->leaving_guest;
}
CLEAN_AS(func_020a6230, LinkScene_LeavingGuest)

/* func_020a6238 */
void LinkScene_SetLeavingGuest(LinkState *state, u32 slot)
{
    state->leaving_guest = slot;
}
CLEAN_AS(func_020a6238, LinkScene_SetLeavingGuest)

/* func_020a6240 */
u8 LinkScene_Released(LinkState *state)
{
    return state->released;
}
CLEAN_AS(func_020a6240, LinkScene_Released)

/* func_020a6248 */
void LinkScene_SetReleased(LinkState *state, u8 released)
{
    state->released = released;
}
CLEAN_AS(func_020a6248, LinkScene_SetReleased)

/* func_020a6250: the slot this system sent its scene's state to forgotten once it is in this
 * system's scene. */
void LinkScene_CheckStateSent(LinkState *state)
{
    int slot = LinkScene_StateSentTo(state);
    if (slot < LINK_STATE_SLOTS && func_020a7330(slot) == SceneQuery_Current()) {
        LinkScene_SetStateSentTo(state, LINK_STATE_SLOTS);
    }
}
CLEAN_AS(func_020a6250, LinkScene_CheckStateSent)

/* func_020a627c */
int LinkScene_StateSentTo(LinkState *state)
{
    return state->state_sent_to;
}
CLEAN_AS(func_020a627c, LinkScene_StateSentTo)

/* func_020a6280 */
void LinkScene_SetStateSentTo(LinkState *state, int slot)
{
    state->state_sent_to = slot;
}
CLEAN_AS(func_020a6280, LinkScene_SetStateSentTo)

/* func_020a6284 */
int LinkScene_StateAsker(LinkState *state)
{
    return state->state_asker;
}
CLEAN_AS(func_020a6284, LinkScene_StateAsker)

/* func_020a6288 */
void LinkScene_SetStateAsker(LinkState *state, int slot)
{
    state->state_asker = slot;
}
CLEAN_AS(func_020a6288, LinkScene_SetStateAsker)

/* func_020a628c */
int LinkScene_NextHolder(LinkState *state)
{
    return state->next_holder;
}
CLEAN_AS(func_020a628c, LinkScene_NextHolder)

/* func_020a6290 */
void LinkScene_SetNextHolder(LinkState *state, int slot)
{
    state->next_holder = slot;
}
CLEAN_AS(func_020a6290, LinkScene_SetNextHolder)

/* func_020a6294: the slot that moves (the highest), when it is new: if it is another system
 * that holds this system's scene, it is told this system saw it go (message 13) unless the
 * scene is one a join or leave passes through. The slot is then noted. */
void LinkScene_AckLeavingHolder(LinkState *state)
{
    NetSession *session = data_020ccf94;
    int mover = moving_slot(session);

    if (mover == LinkScene_LeavingHolder(state)) {
        return;
    }
    if (mover >= LINK_STATE_SLOTS) {
        LinkScene_SetLeavingHolder(state, LINK_STATE_SLOTS);
        return;
    }
    if (!Session_IsLocalSlot(session, mover) && func_020a7330(mover) == SceneQuery_Current() && func_020a7300(mover) != 0 &&
        !LinkScene_IsLinkingScene(SceneQuery_Current())) {
        send_empty(MESSAGE_ACK, mover);
    }
    LinkScene_SetLeavingHolder(state, mover);
}
CLEAN_AS(func_020a6294, LinkScene_AckLeavingHolder)

/* func_020a6338 */
int LinkScene_LeavingHolder(LinkState *state)
{
    return state->leaving_holder;
}
CLEAN_AS(func_020a6338, LinkScene_LeavingHolder)

/* func_020a633c */
void LinkScene_SetLeavingHolder(LinkState *state, int slot)
{
    state->leaving_holder = slot;
}
CLEAN_AS(func_020a633c, LinkScene_SetLeavingHolder)

/* func_020a6340 */
void LinkScene_ResetAcked(LinkState *state)
{
    for (int slot = 0; slot < LINK_STATE_SLOTS; slot++) {
        state->acked[slot] = 0;
    }
}
CLEAN_AS(func_020a6340, LinkScene_ResetAcked)

/* func_020a6354 */
int LinkScene_Acked(LinkState *state, int slot)
{
    return state->acked[slot];
}
CLEAN_AS(func_020a6354, LinkScene_Acked)

/* func_020a635c */
void LinkScene_SetAcked(LinkState *state, int slot, int acked)
{
    state->acked[slot] = (u8) acked;
}
CLEAN_AS(func_020a635c, LinkScene_SetAcked)

/* func_020a6364 */
int LinkScene_Successor(LinkState *state)
{
    return state->successor;
}
CLEAN_AS(func_020a6364, LinkScene_Successor)

/* func_020a6368 */
void LinkScene_SetSuccessor(LinkState *state, int slot)
{
    state->successor = slot;
}
CLEAN_AS(func_020a6368, LinkScene_SetSuccessor)

/* Phase 1: a holder chooses as successor the lowest other system in its scene, and waits for
 * the scene's systems to see it go; without one, or when this system does not hold its scene,
 * there is none (when not holding, it waits to be let go). */
static void choose_successor(LinkState *state, NetSession *session, int own)
{
    u8 scene = 0;
    u8 holder = 0;
    u8 moving = 0;

    if (func_020a7450() || func_020a744c()) {
        return;
    }
    LinkScene_GlobalPlace(own, &scene, &holder, &moving);
    if (!holder) {
        LinkScene_SetSuccessor(state, LINK_STATE_SLOTS);
        LinkScene_SetPhase(state, LINK_SCENE_WAIT_RELEASE);
        return;
    }
    int successor = LINK_STATE_SLOTS;
    for (int slot = 0; slot < LINK_STATE_SLOTS; slot++) {
        if (slot != own && Session_IsSlotTaken(session, slot) && func_020a7330(slot) == scene) {
            successor = slot;
            break;
        }
    }
    if (successor < LINK_STATE_SLOTS) {
        LinkScene_SetSuccessor(state, successor);
        LinkScene_SetPhase(state, LINK_SCENE_WAIT_ACKS);
    } else {
        LinkScene_SetSuccessor(state, LINK_STATE_SLOTS);
        LinkScene_SetPhase(state, LINK_SCENE_LEAVE);
    }
}

/* Phase 2: once every other system of the current scene saw this one go (outside the linking
 * scenes) and no session message waits in a queue, the acks cleared, bundle 15 emptied and the
 * state sent next. */
static void wait_acks(LinkState *state, NetSession *session, int own)
{
    if (!LinkScene_IsLinkingScene(SceneQuery_Current())) {
        for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
            if (slot == own || !Session_IsSlotTaken(session, slot)) {
                continue;
            }
            if (func_020a7330(slot) != SceneQuery_Current()) {
                continue;
            }
            if (!LinkScene_Acked(state, slot)) {
                return;
            }
        }
    }
    if (Session_GetHeldQueueLength(session) || Session_GetSceneQueueLength(session) || Session_GetLocalQueueLength(session) ||
        func_020a744c()) {
        return;
    }
    LinkScene_ResetAcked(state);
    Session_ClearBundle15Length(session);
    LinkScene_SetPhase(state, LINK_SCENE_SEND_STATE);
}

/* Phase 9: the holder of the scene entered (the highest other system there that holds it) is
 * asked for its state (message 14, outside the linking scenes), bundle 16 emptied for it;
 * without one this system enters first. */
static void find_holder(LinkState *state, NetSession *session, int own)
{
    int next = SceneExit_NextScene();
    int holder_slot = LINK_STATE_SLOTS;

    for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
        u8 scene = 0;
        u8 holder = 0;
        u8 moving = 0;
        if (slot == own || !Session_IsSlotTaken(session, slot)) {
            continue;
        }
        LinkScene_GlobalPlace(slot, &scene, &holder, &moving);
        if (scene == next && holder) {
            holder_slot = slot;
            break;
        }
    }
    if (holder_slot < LINK_STATE_SLOTS) {
        LinkScene_SetNextHolder(state, holder_slot);
        LinkScene_SetEntersFirst(state, 0);
        Session_ClearBundle16Length(session);
        if (!LinkScene_IsLinkingScene(SceneExit_NextScene())) {
            NetSession *sender = data_020ccf94;
            Session_BeginMessage(sender);
            Session_EndMessage(sender, MESSAGE_ASK_STATE, (u32) LinkScene_NextHolder(state));
        }
        LinkScene_SetPhase(state, LINK_SCENE_WAIT_STATE);
    } else {
        LinkScene_SetNextHolder(state, LINK_STATE_SLOTS);
        LinkScene_SetEntersFirst(state, 1);
        LinkScene_SetPhase(state, LINK_SCENE_ENTER);
    }
}

/* func_020a636c: this system's move, once a frame (LinkScenePhase). Idle, it starts when the
 * process between scenes is asked for: the move asked of the host, the acks and the release
 * cleared. REQUIRES: this system has a slot (LinkScene_Update checks it).
 * QUIRK: the idle phase moves on data_021f4320's phase, not `state`'s (the game has only the
 * one). */
void LinkScene_Step(LinkState *state)
{
    NetSession *session = data_020ccf94;
    int own = session->local_slot;

    switch (LinkScene_Phase(state)) {
        case LINK_SCENE_IDLE:
            if (data_020e3c80 != CHANGE_CLASS) {
                return;
            }
            func_020a6f88();
            LinkScene_ResetAcked(state);
            LinkScene_SetReleased(state, 0);
            LinkScene_GlobalSetPhase(LINK_SCENE_WAIT_TURN);
            return;
        case LINK_SCENE_WAIT_TURN:
            if (func_020a72d0(own)) {
                LinkScene_SetPhase(state, LINK_SCENE_CHOOSE);
            }
            return;
        case LINK_SCENE_CHOOSE:
            choose_successor(state, session, own);
            return;
        case LINK_SCENE_WAIT_ACKS:
            wait_acks(state, session, own);
            return;
        case LINK_SCENE_WAIT_RELEASE:
            if (!LinkScene_Released(state) && !LinkScene_IsLinkingScene(SceneQuery_Current())) {
                return;
            }
            LinkScene_SetReleased(state, 0);
            LinkScene_SetPhase(state, LINK_SCENE_LEAVE);
            return;
        case LINK_SCENE_WAIT_SUCCESSOR:
            /* The successor is read again for the test. */
            if (LinkScene_Successor(state) != LINK_STATE_SLOTS && !func_020a7300(LinkScene_Successor(state)) &&
                !LinkScene_IsLinkingScene(SceneQuery_Current())) {
                return;
            }
            LinkScene_SetPhase(state, LINK_SCENE_FIND_HOLDER);
            return;
        case LINK_SCENE_FIND_HOLDER:
            find_holder(state, session, own);
            return;
        case LINK_SCENE_WAIT_STATE:
            if (!Session_GetBundle16Length(session) && !LinkScene_IsLinkingScene(SceneExit_NextScene())) {
                return;
            }
            LinkScene_SetPhase(state, LINK_SCENE_ENTER);
            return;
        case LINK_SCENE_ARRIVE:
            func_020a7380(session->local_slot, 1);
            LinkScene_SetPhase(state, LINK_SCENE_WAIT_SETTLED);
            return;
        case LINK_SCENE_WAIT_SETTLED:
            if (func_020a7258()) {
                return;
            }
            LinkScene_SetPhase(state, LINK_SCENE_IDLE);
            return;
        default:
            return;
    }
}
CLEAN_AS(func_020a636c, LinkScene_Step)

/* func_020a6684 */
int LinkScene_Phase(LinkState *state)
{
    return state->scene_phase;
}
CLEAN_AS(func_020a6684, LinkScene_Phase)

/* func_020a6688 */
void LinkScene_SetPhase(LinkState *state, int phase)
{
    state->scene_phase = phase;
}
CLEAN_AS(func_020a6688, LinkScene_SetPhase)

/* func_020a668c */
u8 LinkScene_EntersFirst(LinkState *state)
{
    return state->enters_first;
}
CLEAN_AS(func_020a668c, LinkScene_EntersFirst)

/* func_020a6694 */
void LinkScene_SetEntersFirst(LinkState *state, u8 first)
{
    state->enters_first = first;
}
CLEAN_AS(func_020a6694, LinkScene_SetEntersFirst)

/* A slot's place, the fields of `mask`, sent to every system (message 9). */
static void send_place(NetSession *session, int slot, u8 scene, u8 holder, u8 moving, u32 mask)
{
    u8 packed[2];
    func_020a7820(packed);
    func_020a77f4(packed, slot, scene, holder, moving, mask);
    Session_BeginMessage(session);
    Session_AppendMessage(session, packed, sizeof(packed));
    Session_EndMessage(session, MESSAGE_PLACE, TO_ALL);
    func_020a7810(packed);
}

/* func_020a669c (host): each slot's pending changes applied to its place, sent to every system
 * and cleared. */
void LinkScene_SendChanges(LinkState *state)
{
    NetSession *session = data_020ccf94;
    for (unsigned int slot = 0; slot < LINK_STATE_SLOTS; slot++) {
        LinkStatePlaceChange *change = &state->changes[slot];
        u8 scene;
        u8 holder;
        u8 moving;
        u32 mask;
        func_020a7778(change, &scene, &holder, &moving, &mask);
        if (mask == 0) {
            continue;
        }
        func_020a7394((int) slot, scene, holder, moving, (int) mask);
        {
            u8 packed[2];
            func_020a7820(packed);
            func_020a77f4(packed, (int) slot, scene, holder, moving, mask);
            Session_BeginMessage(session);
            Session_AppendMessage(session, packed, sizeof(packed));
            Session_EndMessage(session, MESSAGE_PLACE, TO_ALL);
            func_020a7768(change);
            func_020a7810(packed);
        }
    }
}
CLEAN_AS(func_020a669c, LinkScene_SendChanges)

/* func_020a6738 (host): the oldest move, once its slot said it arrived: the slot's place
 * becomes the scene moved to, holding it when no other system is there, and no longer moving;
 * the arrival cleared and the move taken off the queue. Gives the slot and the place's fields
 * set (all) in `slot` and `mask`; nothing when there is no such move. */
void LinkScene_SettleArrival(LinkState *state, int *slot, int *mask)
{
    int mover = LinkScene_NextMover(state);
    u32 arrived;
    s32 move_slot;
    u8 scene;
    int holder;

    if (mover >= LINK_STATE_SLOTS) {
        return;
    }
    u32 *mover_arrived = &state->arrived[mover];
    func_020a76d8(mover_arrived, &arrived);
    if (arrived != 1) {
        return;
    }
    holder = 1;
    func_020a7704(&state->moves[0], &move_slot, &scene);
    NetSession *session = data_020ccf94;
    for (int other = LINK_STATE_SLOTS - 1; other >= 0; other--) {
        if (other == mover || !Session_IsSlotTaken(session, other)) {
            continue;
        }
        if (func_020a7330(other) != scene) {
            continue;
        }
        holder = 0;
        break;
    }
    func_020a7394(mover, scene, holder, 0, MASK_ALL);
    func_020a76d0(mover_arrived);
    LinkScene_PopMove(state);
    *slot = mover;
    *mask = MASK_ALL;
}
CLEAN_AS(func_020a6738, LinkScene_SettleArrival)

/* func_020a67d8 (guest): this system's arrival, once noted, told to the host (message 10) and
 * cleared. REQUIRES: this system has a slot. */
void LinkScene_ReportArrival(LinkState *state)
{
    u32 *arrived = &state->arrived[data_020ccf94->local_slot];
    u32 value;
    func_020a76d8(arrived, &value);
    if (value != 0) {
        u8 byte = (u8) value;
        NetSession *session = data_020ccf94;
        Session_BeginMessage(session);
        Session_AppendMessage(session, &byte, 1);
        Session_EndMessage(session, MESSAGE_ARRIVED, TO_HOST);
        func_020a76d0(arrived);
    }
}
CLEAN_AS(func_020a67d8, LinkScene_ReportArrival)

/* func_020a682c: the oldest move taken off the queue: the moves after it copied down one, up to
 * the first empty one, and the last copied from emptied. Nothing when the queue is empty. */
void LinkScene_PopMove(LinkState *state)
{
    if (LinkScene_NextMover(state) >= LINK_STATE_SLOTS) {
        return;
    }
    LinkStateMove *move = &state->moves[0];
    for (int left = LINK_STATE_SLOTS - 2; left >= 0; left--) {
        s32 slot;
        u8 scene;
        func_020a7704(move + 1, &slot, &scene);
        if (slot >= LINK_STATE_SLOTS) {
            break;
        }
        MI_CpuCopy8(move + 1, move, sizeof(LinkStateMove));
        move++;
    }
    func_020a76f8(move);
}
CLEAN_AS(func_020a682c, LinkScene_PopMove)

/* func_020a6878: the slot of the oldest move (LINK_STATE_SLOTS when there is none). */
int LinkScene_NextMover(LinkState *state)
{
    s32 slot;
    u8 scene;
    func_020a7704(&state->moves[0], &slot, &scene);
    return slot;
}
CLEAN_AS(func_020a6878, LinkScene_NextMover)

/* func_020a6890 (host): while no slot moves, the oldest move's slot let move. Gives the slot and
 * the place's field set (moving) in `slot` and `mask`; nothing otherwise. */
void LinkScene_LetNextMove(LinkState *state, int *slot, int *mask)
{
    for (int other = LINK_STATE_SLOTS - 1; other >= 0; other--) {
        if (func_020a72d0(other)) {
            return;
        }
    }
    int mover = LinkScene_NextMover(state);
    if (mover >= LINK_STATE_SLOTS) {
        return;
    }
    func_020a7394(mover, LINK_SCENE_NONE, 0, 1, MASK_MOVING);
    *slot = mover;
    *mask = MASK_MOVING;
}
CLEAN_AS(func_020a6890, LinkScene_LetNextMove)

/* func_020a68e0 (host): an arrival settled and the next move let start, each changed place sent
 * to every system (message 9). */
void LinkScene_HostStep(LinkState *state)
{
    int slots[2];
    int masks[2];

    slots[0] = (int) data_020e3cdc[0];
    slots[1] = (int) data_020e3cdc[1];
    func_02137550(masks, sizeof(masks));
    LinkScene_SettleArrival(state, &slots[0], &masks[0]);
    LinkScene_LetNextMove(state, &slots[1], &masks[1]);

    NetSession *session = data_020ccf94;
    for (unsigned int i = 0; i < 2; i++) {
        int slot = slots[i];
        u8 scene;
        u8 holder;
        u8 moving;
        if (slot >= LINK_STATE_SLOTS) {
            continue;
        }
        func_020a7738(&state->places[slot], &scene, &holder, &moving);
        send_place(session, slot, scene, holder, moving, (u32) masks[i]);
    }
}
CLEAN_AS(func_020a68e0, LinkScene_HostStep)

/* func_020a6c04 */
void LinkScene_Empty6C04(void) {}
CLEAN_AS(func_020a6c04, LinkScene_Empty6C04)

/* func_020a6c08: the link's work of a frame, while this system has a slot: the state sent
 * forgotten once its receiver arrived, moving slots released; the host settles arrivals, lets
 * moves start and sends changed places, a guest reports its arrival; then the link state's
 * system step and host step (link_state.h), this system's move and acks. */
void LinkScene_Update(void)
{
    int own = data_020ccf94->local_slot;
    if (!Session_IsSlotTaken(data_020ccf94, own)) {
        return;
    }
    LinkScene_CheckStateSent(&data_021f4320);
    LinkScene_ReleaseLeavingGuest(&data_021f4320);
    if (own == HOST_SLOT) {
        LinkScene_HostStep(&data_021f4320);
        LinkScene_SendChanges(&data_021f4320);
    }
    if (own != HOST_SLOT) {
        LinkScene_ReportArrival(&data_021f4320);
    }
    if (own == HOST_SLOT) {
        LinkState_HostStep(&data_021f4320);
    }
    LinkState_SystemStep(&data_021f4320);
    LinkScene_Step(&data_021f4320);
    LinkScene_AckLeavingHolder(&data_021f4320);
}
CLEAN_AS(func_020a6c08, LinkScene_Update)

/* func_020a6c8c */
void LinkScene_Empty6C8C(void) {}
CLEAN_AS(func_020a6c8c, LinkScene_Empty6C8C)

/* func_020a6c90 */
void LinkScene_Empty6C90(void) {}
CLEAN_AS(func_020a6c90, LinkScene_Empty6C90)

/* func_020a6c94 */
void LinkScene_Empty6C94(void) {}
CLEAN_AS(func_020a6c94, LinkScene_Empty6C94)

/* func_020a6c98: whether `scene` is one a join or a leave passes through (0xc-0xe, 0x2e,
 * 0x2f, link_state.h), where systems do not hand scenes' states over. */
int LinkScene_IsLinkingScene(int scene)
{
    switch (scene) {
        case 0x0c:
        case 0x0d:
        case 0x0e:
        case 0x2e:
        case 0x2f:
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_020a6c98, LinkScene_IsLinkingScene)

/* func_020a6ce4: while this system has a slot, a slot that asked for this system's scene's
 * state is sent it (bundle 16) and noted as sent to. */
void LinkScene_SendAskedState(void)
{
    if (!Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    int asker = LinkScene_StateAsker(&data_021f4320);
    if (asker < LINK_STATE_SLOTS) {
        func_020a7064(asker);
        LinkScene_SetStateSentTo(&data_021f4320, asker);
        LinkScene_SetStateAsker(&data_021f4320, LINK_STATE_SLOTS);
    }
}
CLEAN_AS(func_020a6ce4, LinkScene_SendAskedState)

/* func_020a6d24: while this system has a slot and is to send its scene's state, once the screen
 * is closed: the state sent to the successor (bundle 15, outside the linking scenes) and the
 * scene may be left. */
void LinkScene_SendLeftState(void)
{
    NetSession *session = data_020ccf94;
    if (!Session_IsSlotTaken(session, session->local_slot)) {
        return;
    }
    if (LinkScene_Phase(&data_021f4320) != LINK_SCENE_SEND_STATE || data_021c75b8 != 0) {
        return;
    }
    if (!LinkScene_IsLinkingScene(SceneQuery_Current())) {
        func_020a70a8(LinkScene_Successor(&data_021f4320));
    }
    LinkScene_SetPhase(&data_021f4320, LINK_SCENE_LEAVE);
}
CLEAN_AS(func_020a6d24, LinkScene_SendLeftState)

/* func_020a6d84: while this system has a slot, a received scene state (bundle 16) handed out. */
void LinkScene_TakeEnteredState(void)
{
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) && Session_GetBundle16Length(session)) {
        func_020a7454();
    }
}
CLEAN_AS(func_020a6d84, LinkScene_TakeEnteredState)

/* func_020a6db0: while this system has a slot, the scene state its predecessor left it (bundle
 * 15) handed out; this system then holds its scene, and while linked the host is told so (a
 * guest sends message 11, the host notes the change itself). */
void LinkScene_TakeLeftState(void)
{
    NetSession *session = data_020ccf94;
    int own = session->local_slot;

    if (!Session_IsSlotTaken(session, own) || !Session_GetBundle15Length(session)) {
        return;
    }
    func_020a753c();
    func_020a7394(own, LINK_SCENE_NONE, 1, 0, MASK_HOLDER);
    if (!Session_IsLinked(session)) {
        return;
    }
    if (own != HOST_SLOT) {
        u8 packed[2];
        func_020a7880(packed);
        func_020a7850(packed, LINK_SCENE_NONE, 1, 0, MASK_HOLDER);
        NetSession *sender = data_020ccf94;
        Session_BeginMessage(sender);
        Session_AppendMessage(sender, packed, sizeof(packed));
        Session_EndMessage(sender, MESSAGE_PLACE_CHANGE, TO_HOST);
        func_020a7870(packed);
    } else {
        func_020a7360(own, LINK_SCENE_NONE, 1, 0, MASK_HOLDER);
    }
}
CLEAN_AS(func_020a6db0, LinkScene_TakeLeftState)

/* func_020a6e4c: data_021f4320's place of `slot`; nothing is written for no slot. */
void LinkScene_GlobalPlace(int slot, u8 *scene, u8 *holder, u8 *moving)
{
    if (slot < LINK_STATE_SLOTS) {
        func_020a7738(&data_021f4320.places[slot], scene, holder, moving);
    }
}
CLEAN_AS(func_020a6e4c, LinkScene_GlobalPlace)

/* func_020a6e6c */
void LinkScene_GlobalSetReleased(int released)
{
    LinkScene_SetReleased(&data_021f4320, (u8) released);
}
CLEAN_AS(func_020a6e6c, LinkScene_GlobalSetReleased)

/* func_020a6e7c */
void LinkScene_GlobalSetStateAsker(int slot)
{
    LinkScene_SetStateAsker(&data_021f4320, slot);
}
CLEAN_AS(func_020a6e7c, LinkScene_GlobalSetStateAsker)

/* func_020a6e8c */
void LinkScene_GlobalSetAcked(int slot, int acked)
{
    LinkScene_SetAcked(&data_021f4320, slot, acked);
}
CLEAN_AS(func_020a6e8c, LinkScene_GlobalSetAcked)

/* func_020a6ea0 */
int LinkScene_GlobalPhase(void)
{
    return LinkScene_Phase(&data_021f4320);
}
CLEAN_AS(func_020a6ea0, LinkScene_GlobalPhase)

/* func_020a6eb0 */
void LinkScene_GlobalSetPhase(int phase)
{
    LinkScene_SetPhase(&data_021f4320, phase);
}
CLEAN_AS(func_020a6eb0, LinkScene_GlobalSetPhase)
