/* The link state: the agreement of the linked systems on a join or a leave (link_state.h). */
#include "link_state.h"

#include <string.h>

#include "activity_job.h"
#include "activity_vars.h"
#include "autoload_2/network.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "event_queue.h"
#include "field_label.h"
#include "player_record.h"
#include "player_records.h"
#include "scene_exit.h"
#include "scene_place.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"
#include "session_link.h"
#include "start_menu.h"
#include "state_block.h"
#include "link_parts.h"
#include "paired_town.h"
#include "state_flags.h"

static_assert(offsetof(LinkState, status) == 0x84 && offsetof(LinkState, half_98) == 0x98, "link state");
static_assert(offsetof(LinkState, host_phase) == 0x9c && offsetof(LinkState, answers) == 0xa8, "link state");
static_assert(offsetof(LinkState, wait_frames) == 0xb8 && offsetof(LinkState, hold_frames) == 0xbc, "link state");
static_assert(offsetof(LinkState, done_kind) == 0xc0 && offsetof(LinkState, byte_c4) == 0xc4, "link state");
static_assert(offsetof(StateBlock, town) == 2, "state block");

extern NetSession *data_020ccf94;
extern LinkState data_021f4320;
extern StateBlock data_021dc7a8;

/* The step of the running scene's creation (scene_process_base.h); 0 once it is created. */
extern u8 data_021f42f0;

/* Where a joining player arrives in scene 0xd: a function-local static object (bit 0 of
 * data_021f42f8 once it is made, data_021f4308 its record for the C++ runtime). */
extern Vec3 data_021f4314;
extern u32 data_021f42f8;
extern u8 data_021f4308[];
extern void func_020012dc(void *object);
extern void __register_global_object(void *object, void *destruct, void *record);

#define HOST_SLOT 0
#define GUEST_RECORD_FIRST 3 /* a slot's player record number, less this */
#define WAIT_LIMIT 0xa0      /* the frames a system waits before it refuses */
#define HOLD_FRAMES 0x28     /* the frames between accepting and carrying out */

/* Session messages: the handler of status bytes, and the one of a slot's link status. */
#define HANDLER_STATUS_BYTE 0xc
#define HANDLER_LINK_STATUS 1

/* Link statuses (func_020a6170): 0-3 a request of that kind; then the request's outcome. */
enum {
    STATUS_REQUEST_LAST = 3,
    STATUS_SERVED = 4,
    STATUS_GO = 5,
    STATUS_DONE = 6,
    STATUS_TOLD = 7,
};

enum {
    KIND_JOIN = 0,
    KIND_LEAVE = 1,
    KIND_END_STAY = 2,
};

enum {
    SCENE_0C = 0x0c,
    SCENE_0D = 0x0d,
    SCENE_0E = 0x0e,
    SCENE_2E = 0x2e,
    SCENE_2F = 0x2f,
    SCENE_3F = 0x3f, /* the entry record's scene while no exit is taken */
};

#define EXIT_ARG 2
#define LEAVE_NEXT_ARG 3
#define JOIN_PLAYER_PARAM 0x800000

static SceneExit *entry_record(void)
{
    return (SceneExit *) (uintptr_t) SceneTables_EntryRecord();
}

/* A status byte (`answer`, `kind`, the slot served) sent to `to` as a session message. */
static void send_answer(NetSession *session, int answer, int kind, int served, int to)
{
    u8 byte;
    LinkPart_MakeStatusByte(&byte);
    LinkPart_PackStatusByte(&byte, answer, kind, served);
    Session_BeginMessage(session);
    Session_AppendMessage(session, &byte, 1);
    Session_EndMessage(session, HANDLER_STATUS_BYTE, (u32) to);
    LinkPart_EndStatusByte(&byte);
}

/* The link status `status` sent to `to`. */
static void send_link_status(NetSession *session, int status, int to)
{
    u8 byte = (u8) status;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &byte, 1);
    Session_EndMessage(session, HANDLER_LINK_STATUS, (u32) to);
}

/* func_020a5710 */
u8 LinkState_ByteC4(LinkState *state)
{
    return state->byte_c4;
}
CLEAN_AS(func_020a5710, LinkState_ByteC4)

/* func_020a5718 */
void LinkState_SetByteC4(LinkState *state, u8 value)
{
    state->byte_c4 = value;
}
CLEAN_AS(func_020a5718, LinkState_SetByteC4)

/* func_020a5720 */
u32 LinkState_DoneKind(LinkState *state)
{
    return state->done_kind;
}
CLEAN_AS(func_020a5720, LinkState_DoneKind)

/* func_020a5728 */
void LinkState_SetDoneKind(LinkState *state, u32 kind)
{
    state->done_kind = kind;
}
CLEAN_AS(func_020a5728, LinkState_SetDoneKind)

/* func_020a5730 */
u8 LinkState_HoldFrames(LinkState *state)
{
    return state->hold_frames;
}
CLEAN_AS(func_020a5730, LinkState_HoldFrames)

/* func_020a5738 */
void LinkState_SetHoldFrames(LinkState *state, u8 frames)
{
    state->hold_frames = frames;
}
CLEAN_AS(func_020a5738, LinkState_SetHoldFrames)

/* func_020a5740 */
u32 LinkState_WaitFrames(LinkState *state)
{
    return state->wait_frames;
}
CLEAN_AS(func_020a5740, LinkState_WaitFrames)

/* func_020a5748 */
void LinkState_SetWaitFrames(LinkState *state, u32 frames)
{
    state->wait_frames = frames;
}
CLEAN_AS(func_020a5748, LinkState_SetWaitFrames)

/* The change carried out by this system (slot `slot`): unless it must hold on, this system's
 * player placed where it stands, the entry record pointed at the change's scene and the
 * activity asked for the change's job; then the host told it is done. A join holds on while
 * the joining player's record is missing; the host then notes the peer missing when its slot
 * is not connected (REQUIRES: the slot served is 0-3). */
static void carry_out(LinkState *state, NetSession *session, int slot)
{
    u32 kind = LinkState_Kind(state);
    int hold;
    u8 frames;

    FieldLabel_ShowTableMessage((int) kind);
    /* QUIRK: the frames counted down are data_021f4320's, the frames tested `state`'s (the game
     * only has the one). */
    frames = LinkState_HoldFrames(&data_021f4320);
    if (frames != 0) {
        LinkState_SetHoldFrames(&data_021f4320, (u8) (frames - 1));
    }
    hold = LinkState_HoldFrames(state) != 0;
    if (!hold) {
        if (kind == KIND_JOIN) {
            int joining = LinkState_Chosen(state);
            if (PlayerRecords_Exists(joining + GUEST_RECORD_FIRST) == 0) {
                hold = 1;
                if (slot == HOST_SLOT) {
                    int connected = Net_GetConnectedMask();
                    u16 bit = (u16) (1u << joining);
                    if (bit != (bit & connected)) {
                        u32 flags = Session_GetErrorFlags(session);
                        if ((flags & SESSION_ERROR_PEER_MISSING) == 0) {
                            Session_SetErrorFlags(session, (int) (flags | SESSION_ERROR_PEER_MISSING));
                        }
                    }
                }
            }
        } else if (kind == KIND_LEAVE) {
            LinkState_SetServedSlot(state, (u32) LinkState_Chosen(state));
        }
    }
    if (hold) {
        return;
    }

    LinkState_SetDoneKind(state, LinkState_Kind(state));
    ActivityVars_SetSlot3C1C((u32) LinkState_Chosen(state));
    ScenePlace_SavePlayer(SceneTables_EntryRecord(), 0);
    if (LinkState_Kind(state) == KIND_JOIN) {
        const StateBlockTown *town = &data_021dc7a8.town;
        u8 *record = PlayerRecords_Get(LinkState_Chosen(state) + GUEST_RECORD_FIRST);
        const StateBlockTown *paired = NULL;
        if (record != NULL && PairedTown_Flag5(PlayerRecord_Field242C(record)) != 0) {
            paired = (const StateBlockTown *) (void *) PairedTown_Town(PlayerRecord_Field242C(record));
        }
        if (paired != NULL && paired->number == town->number && memcmp(paired->name, town->name, sizeof(town->name)) == 0) {
            SceneExit_SetToScene(entry_record(), SCENE_2F, EXIT_ARG, EXIT_ARG);
        } else {
            if ((data_021f42f8 & 1) == 0) {
                data_021f4314.x = 0x10000;
                data_021f4314.y = 0;
                data_021f4314.z = 0x5000;
                __register_global_object(&data_021f4314, (void *) (uintptr_t) func_020012dc, data_021f4308);
                data_021f42f8 |= 1;
            }
            SceneExit_SetTo(entry_record(), SCENE_0D, &data_021f4314, JOIN_PLAYER_PARAM, 0, EXIT_ARG, EXIT_ARG);
        }
    } else {
        SceneExit_SetToScene(entry_record(), SCENE_2E, EXIT_ARG, LEAVE_NEXT_ARG);
    }

    if (Session_IsLocalSlot(session, HOST_SLOT)) {
        if (kind == KIND_JOIN) {
            ActivityJob_Ask15();
        } else if (kind == KIND_LEAVE) {
            ActivityJob_Ask18();
        }
    } else if (kind == KIND_JOIN) {
        ActivityJob_Ask16();
    } else if (kind == KIND_LEAVE) {
        ActivityJob_Ask19();
    } else if (kind == KIND_END_STAY) {
        ActivityJob_Ask1B();
        StartMenu_SetLeaveChoice(0);
    } else {
        ActivityJob_Ask1B();
        StartMenu_SetLeaveChoice(1);
    }

    if (slot != HOST_SLOT) {
        send_answer(session, LINK_STATE_ANSWER_DONE, LINK_STATE_KIND_NONE, LinkState_Chosen(state), HOST_SLOT);
    }
    LinkState_SetAnswer(state, slot, LINK_STATE_ANSWER_DONE);
}

/* func_020a5750: this system's part of a request, once a frame. Asked, it waits until it is
 * out of the linked scenes (0xc-0xe, 0x2e, 0x2f) with no exit taken and no scene being created,
 * and an event of kind 13 starts: then it accepts (and holds 40 frames before carrying the
 * change out), lets every member of the session in and shows the kind's label; after 160
 * frames it refuses instead (the host's own slot answers no, a guest's is done at once). Told
 * to cancel, it ends the event and is done; told to go, it carries the change out
 * (carry_out). A guest tells the host each answer. */
void LinkState_SystemStep(LinkState *state)
{
    NetSession *session = data_020ccf94;
    int slot = session->local_slot;

    if (LinkState_Answer(state, slot) == LINK_STATE_ANSWER_ASKED) {
        LinkState_SetWaitFrames(state, 0);
        LinkState_SetAnswer(state, slot, LINK_STATE_ANSWER_WAIT);
    }

    slot = session->local_slot;
    if (LinkState_Answer(state, slot) == LINK_STATE_ANSWER_WAIT) {
        int scene = SceneQuery_Current();
        int ready = scene != SCENE_2E && scene != SCENE_0C && scene != SCENE_0D && scene != SCENE_0E && scene != SCENE_2F &&
                    SceneExit_Scene(entry_record()) == SCENE_3F && data_021f42f0 == 0 && EventQueue_StartKind13();
        u32 kind = LinkState_Kind(state);
        if (ready) {
            LinkState_SetHoldFrames(state, HOLD_FRAMES);
            LinkState_SetWaitFrames(state, 0);
            if (slot != HOST_SLOT) {
                send_answer(session, LINK_STATE_ANSWER_YES, LINK_STATE_KIND_NONE, LinkState_Chosen(state), HOST_SLOT);
            }
            FieldLabel_ShowTableMessage((int) kind);
            LinkState_SetAnswer(state, slot, LINK_STATE_ANSWER_YES);
            Session_SetSlotMask(session, (u16) Session_GetMemberMask());
        } else {
            u32 frames = LinkState_WaitFrames(state) + 1;
            if (frames >= WAIT_LIMIT) {
                if (slot == HOST_SLOT) {
                    LinkState_SetAnswer(state, HOST_SLOT, LINK_STATE_ANSWER_NO);
                } else {
                    send_answer(session, LINK_STATE_ANSWER_NO, LINK_STATE_KIND_NONE, LinkState_Chosen(state), HOST_SLOT);
                    LinkState_SetAnswer(state, slot, LINK_STATE_ANSWER_DONE);
                }
                StateFlags_EndMenuClose();
                LinkState_SetWaitFrames(state, 0);
            } else {
                LinkState_SetWaitFrames(state, frames);
            }
            FieldLabel_ChooseMessage((int) kind);
        }
    }

    slot = session->local_slot;
    switch (LinkState_Answer(state, slot)) {
        case LINK_STATE_ANSWER_YES:
            FieldLabel_ShowTableMessage((int) LinkState_Kind(state));
            break;
        case LINK_STATE_ANSWER_CANCEL:
            EventQueue_FinishKind13();
            StateFlags_EndMenuClose();
            FieldLabel_ShowMessage9();
            LinkState_SetHoldFrames(state, 0);
            if (slot != HOST_SLOT) {
                send_answer(session, LINK_STATE_ANSWER_DONE, LINK_STATE_KIND_NONE, LinkState_Chosen(state), HOST_SLOT);
            }
            LinkState_SetAnswer(state, slot, LINK_STATE_ANSWER_DONE);
            break;
        case LINK_STATE_ANSWER_GO:
            carry_out(state, session, slot);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020a5750, LinkState_SystemStep)

/* func_020a5b98: every slot's answer done. */
void LinkState_ResetAnswers(LinkState *state)
{
    for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
        state->answers[slot] = LINK_STATE_ANSWER_DONE;
    }
}
CLEAN_AS(func_020a5b98, LinkState_ResetAnswers)

/* func_020a5bac */
void LinkState_ResetAnswer(LinkState *state, int slot)
{
    state->answers[slot] = LINK_STATE_ANSWER_DONE;
}
CLEAN_AS(func_020a5bac, LinkState_ResetAnswer)

/* func_020a5bb8 */
int LinkState_Answer(LinkState *state, int slot)
{
    return state->answers[slot];
}
CLEAN_AS(func_020a5bb8, LinkState_Answer)

/* func_020a5bc4 */
void LinkState_SetAnswer(LinkState *state, int slot, int answer)
{
    state->answers[slot] = answer;
}
CLEAN_AS(func_020a5bc4, LinkState_SetAnswer)

/* func_020a5bd0 */
void LinkState_ResetKind(LinkState *state)
{
    state->kind = LINK_STATE_KIND_NONE;
}
CLEAN_AS(func_020a5bd0, LinkState_ResetKind)

/* func_020a5bd8 */
u32 LinkState_Kind(LinkState *state)
{
    return state->kind;
}
CLEAN_AS(func_020a5bd8, LinkState_Kind)

/* func_020a5be0 */
void LinkState_SetKind(LinkState *state, u32 kind)
{
    state->kind = kind;
}
CLEAN_AS(func_020a5be0, LinkState_SetKind)

/* func_020a5be8: no slot served (4). */
void LinkState_ResetChosen(LinkState *state)
{
    state->chosen = LINK_STATE_SLOTS;
}
CLEAN_AS(func_020a5be8, LinkState_ResetChosen)

/* OSi_GetSystemErrno (0x020a5bf0; the symbol's name is not this function's). */
int LinkState_Chosen(LinkState *state)
{
    return state->chosen;
}
CLEAN_AS(OSi_GetSystemErrno, LinkState_Chosen)

/* OSi_SetSystemErrno (0x020a5bf8; the symbol's name is not this function's). */
void LinkState_SetChosen(LinkState *state, int slot)
{
    state->chosen = slot;
}
CLEAN_AS(OSi_SetSystemErrno, LinkState_SetChosen)

/* func_020a5c00 */
void LinkState_ResetHostPhase(LinkState *state)
{
    state->host_phase = LINK_STATE_HOST_IDLE;
}
CLEAN_AS(func_020a5c00, LinkState_ResetHostPhase)

/* func_020a5c08 */
u32 LinkState_HostPhase(LinkState *state)
{
    return state->host_phase;
}
CLEAN_AS(func_020a5c08, LinkState_HostPhase)

/* func_020a5c10 */
void LinkState_SetHostPhase(LinkState *state, u32 phase)
{
    state->host_phase = phase;
}
CLEAN_AS(func_020a5c10, LinkState_SetHostPhase)

/* func_020a5c18 */
u16 LinkState_Half98(LinkState *state)
{
    return state->half_98;
}
CLEAN_AS(func_020a5c18, LinkState_Half98)

/* func_020a5c20 */
void LinkState_SetHalf98(LinkState *state, u16 value)
{
    state->half_98 = value;
}
CLEAN_AS(func_020a5c20, LinkState_SetHalf98)

/* func_020a5c28 */
u32 LinkState_ServedSlot(LinkState *state)
{
    return state->served_slot;
}
CLEAN_AS(func_020a5c28, LinkState_ServedSlot)

/* func_020a5c30 */
void LinkState_SetServedSlot(LinkState *state, u32 slot)
{
    state->served_slot = slot;
}
CLEAN_AS(func_020a5c30, LinkState_SetServedSlot)

/* A status that lets a request be served: a request (0-3) or told (7). */
static int status_is_quiet(int status)
{
    return (unsigned int) status <= STATUS_REQUEST_LAST || status == STATUS_TOLD;
}

static int scene_is_linked(int scene)
{
    return scene == SCENE_2E || scene == SCENE_2F || scene == SCENE_0D;
}

/* Whether the slot `slot` (not the one served) is in the session. */
static int is_other_member(NetSession *session, int slot, int served)
{
    return slot != served && Session_IsSlotTaken(session, slot);
}

/* Whether every other member's answer is `answer`. */
static int others_answered(LinkState *state, NetSession *session, int served, int answer)
{
    for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
        if (is_other_member(session, slot, served) && LinkState_Answer(state, slot) != answer) {
            return 0;
        }
    }
    return 1;
}

/* The outcome `status` given to the slot served: directly for a join or for the host's own
 * slot, else sent to it (its status then 7). */
static void tell_served(LinkState *state, int served, int status)
{
    NetSession *session = data_020ccf94;
    if (LinkState_Kind(state) == KIND_JOIN || Session_IsLocalSlot(session, served) != 0) {
        LinkState_SetStatus(state, served, status);
    } else {
        send_link_status(session, status, served);
        LinkState_SetStatus(state, served, STATUS_TOLD);
    }
}

/* An answer `answer` given to the other member `slot`: the host's own directly, a guest's sent
 * to it first. */
static void give_answer(LinkState *state, NetSession *session, int slot, int answer)
{
    if (slot == HOST_SLOT) {
        LinkState_SetAnswer(state, HOST_SLOT, answer);
    } else {
        send_answer(session, answer, LINK_STATE_KIND_NONE, LinkState_Chosen(state), slot);
        LinkState_SetAnswer(state, slot, answer);
    }
}

/* func_020a5c38: the host's part, once a frame. Each slot's request (status 0-3) is served
 * while the host is idle, every status is a request or 7, and neither the current scene nor
 * the entry record's is 0x2e, 0x2f or 0xd; else it is refused (func_020a6104, with the slot's
 * status set to 6 directly for a request of kind 0). A request served: every other member is
 * asked (sent the kind), then their answers collected. When all accepted, they are told to go
 * and the slot served is told so (5), the slot noted, and for a join byte 0xc4 cleared; when
 * one refused, those who accepted are told to cancel and the others are done, and once all
 * are done the slot served is told it is (6) and for a join the Wi-Fi host's time cleared. */
void LinkState_HostStep(LinkState *state)
{
    NetSession *session;
    int served;

    for (unsigned int slot = 0; slot < LINK_STATE_SLOTS; slot++) {
        unsigned int request = (unsigned int) LinkState_Status(state, (int) slot);
        int ok;
        if (request > STATUS_REQUEST_LAST) {
            continue;
        }
        ok = 1;
        for (int other = LINK_STATE_SLOTS - 1; other >= 0; other--) {
            if (!status_is_quiet(LinkState_Status(state, other))) {
                ok = 0;
                break;
            }
        }
        if (ok && LinkState_HostPhase(state) != LINK_STATE_HOST_IDLE) {
            ok = 0;
        }
        if (ok && scene_is_linked(SceneQuery_Current())) {
            ok = 0;
        }
        if (ok && scene_is_linked(SceneExit_Scene(entry_record()))) {
            ok = 0;
        }
        if (ok) {
            LinkState_SetHostPhase(state, LINK_STATE_HOST_ASK);
            LinkState_SetChosen(state, (int) slot);
            LinkState_SetKind(state, request);
            LinkState_SetStatus(state, (int) slot, STATUS_SERVED);
        } else {
            LinkState_RefuseRequest(state, (int) slot, request == KIND_JOIN);
        }
    }

    if (LinkState_HostPhase(state) == LINK_STATE_HOST_ASK) {
        served = LinkState_Chosen(state);
        session = data_020ccf94;
        for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
            if (!is_other_member(session, slot, served)) {
                continue;
            }
            if (slot == HOST_SLOT) {
                LinkState_SetAnswer(state, HOST_SLOT, LINK_STATE_ANSWER_ASKED);
            } else {
                send_answer(session, LINK_STATE_ANSWER_ASKED, (int) LinkState_Kind(state), LinkState_Chosen(state), slot);
                LinkState_SetAnswer(state, slot, LINK_STATE_ANSWER_WAIT);
            }
        }
        LinkState_SetHostPhase(state, LINK_STATE_HOST_COLLECT);
    }

    if (LinkState_HostPhase(state) == LINK_STATE_HOST_COLLECT) {
        int answered = 1;
        served = LinkState_Chosen(state);
        session = data_020ccf94;
        for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
            if (is_other_member(session, slot, served)) {
                int answer = LinkState_Answer(state, slot);
                if (answer != LINK_STATE_ANSWER_YES && answer != LINK_STATE_ANSWER_NO) {
                    answered = 0;
                    break;
                }
            }
        }
        if (answered) {
            int refused = 0;
            for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
                if (is_other_member(session, slot, served) && LinkState_Answer(state, slot) == LINK_STATE_ANSWER_NO) {
                    refused = 1;
                    break;
                }
            }
            if (!refused) {
                for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
                    if (is_other_member(session, slot, served)) {
                        give_answer(state, session, slot, LINK_STATE_ANSWER_GO);
                    }
                }
                tell_served(state, served, STATUS_GO);
                if (LinkState_Kind(state) == KIND_JOIN) {
                    LinkState_GlobalSetByteC4(0);
                }
                LinkState_SetServedSlot(state, (u32) served);
                LinkState_SetHostPhase(state, LINK_STATE_HOST_GO);
            } else {
                for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
                    if (!is_other_member(session, slot, served)) {
                        continue;
                    }
                    if (LinkState_Answer(state, slot) == LINK_STATE_ANSWER_YES) {
                        give_answer(state, session, slot, LINK_STATE_ANSWER_CANCEL);
                    } else {
                        LinkState_SetAnswer(state, slot, LINK_STATE_ANSWER_DONE);
                    }
                }
                LinkState_SetHostPhase(state, LINK_STATE_HOST_CANCEL);
            }
        }
    }

    if (LinkState_HostPhase(state) == LINK_STATE_HOST_GO) {
        served = LinkState_Chosen(state);
        if (others_answered(state, data_020ccf94, served, LINK_STATE_ANSWER_DONE)) {
            LinkState_SetHostPhase(state, LINK_STATE_HOST_IDLE);
        }
    }

    if (LinkState_HostPhase(state) == LINK_STATE_HOST_CANCEL) {
        served = LinkState_Chosen(state);
        if (others_answered(state, data_020ccf94, served, LINK_STATE_ANSWER_DONE)) {
            tell_served(state, served, STATUS_DONE);
            if (LinkState_Kind(state) == KIND_JOIN) {
                Wfc_ClearHostTime();
            }
            LinkState_SetHostPhase(state, LINK_STATE_HOST_IDLE);
        }
    }
}
CLEAN_AS(func_020a5c38, LinkState_HostStep)

/* ---- The link statuses, and the whole link state made, reset and ended */

#include "link_scene.h"

/* The parts' own helpers (link_scene.h): a place reset (no scene), a move reset (no slot, no
 * scene), an arrived word cleared and a pending change cleared; and the parts' constructors
 * and destructors handed to the C++ runtime (only their addresses are taken here; each
 * constructor returns its object). */
extern void func_020a7758(void *place);
extern void func_020a7754(void *place);
extern void func_020a771c(void *move);
extern void func_020a7718(void *move);
extern void func_020a76e8(void *arrived);
extern void func_020a76e4(void *arrived);
extern void func_020a77cc(void *change);
extern void func_020a77c8(void *change);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* func_020a6104: the request of `slot` refused: with `direct`, or for the host's own slot, its
 * status set to 6; else the status 6 sent to it (session message 1) and its status set to 7. */
void LinkState_RefuseRequest(LinkState *state, int slot, int direct)
{
    if (direct) {
        LinkState_SetStatus(state, slot, STATUS_DONE);
    } else if (slot == HOST_SLOT) {
        LinkState_SetStatus(state, HOST_SLOT, STATUS_DONE);
    } else {
        send_link_status(data_020ccf94, STATUS_DONE, slot);
        LinkState_SetStatus(state, slot, STATUS_TOLD);
    }
}
CLEAN_AS(func_020a6104, LinkState_RefuseRequest)

/* func_020a6160: every slot's status 7. */
void LinkState_ResetStatuses(LinkState *state)
{
    for (int slot = 0; slot < LINK_STATE_SLOTS; slot++) {
        state->status[slot] = STATUS_TOLD;
    }
}
CLEAN_AS(func_020a6160, LinkState_ResetStatuses)

/* func_020a6170 */
int LinkState_Status(LinkState *state, int slot)
{
    return state->status[slot];
}
CLEAN_AS(func_020a6170, LinkState_Status)

/* func_020a617c */
void LinkState_SetStatus(LinkState *state, int slot, int status)
{
    state->status[slot] = status;
}
CLEAN_AS(func_020a617c, LinkState_SetStatus)

/* func_020a6998: every part reset: the slots' places, moves, arrivals and pending changes
 * (from slot 3 down), then the request, the answers, the statuses and the moving's fields. */
void LinkState_Reset(LinkState *state)
{
    for (int slot = LINK_STATE_SLOTS - 1; slot >= 0; slot--) {
        LinkPart_ResetPlace(&state->places[slot]);
        LinkPart_ResetMove(&state->moves[slot]);
        LinkPart_ClearArrived(&state->arrived[slot]);
        LinkPart_ResetChange(&state->changes[slot]);
    }
    LinkState_ResetHostPhase(state);
    LinkState_ResetChosen(state);
    LinkState_ResetKind(state);
    LinkState_ResetAnswers(state);
    LinkState_SetWaitFrames(state, 0);
    LinkState_ResetStatuses(state);
    LinkScene_SetSuccessor(state, LINK_STATE_SLOTS);
    LinkScene_ResetAcked(state);
    LinkScene_SetLeavingHolder(state, LINK_STATE_SLOTS);
    LinkScene_SetPhase(state, LINK_SCENE_IDLE);
    LinkScene_SetStateAsker(state, LINK_STATE_SLOTS);
    LinkScene_SetStateSentTo(state, LINK_STATE_SLOTS);
    LinkScene_SetNextHolder(state, LINK_STATE_SLOTS);
    LinkScene_SetReleased(state, 0);
    LinkScene_SetLeavingGuest(state, LINK_STATE_SLOTS);
    LinkState_SetServedSlot(state, LINK_STATE_SLOTS);
    LinkScene_SetEntersFirst(state, 0);
    LinkState_SetHoldFrames(state, 0);
    LinkState_SetDoneKind(state, LINK_STATE_KIND_NONE);
    LinkState_SetByteC4(state, 0);
}
CLEAN_AS(func_020a6998, LinkState_Reset)

/* func_020a6a74: the slot `slot` forgotten: its place, move, arrival, pending change, answer
 * and ack reset, its status 7 (not for the host's slot), and every field naming it no longer
 * does. */
void LinkState_ForgetSlot(LinkState *state, int slot)
{
    LinkPart_ResetPlace(&state->places[slot]);
    LinkPart_ResetMove(&state->moves[slot]);
    LinkPart_ClearArrived(&state->arrived[slot]);
    LinkPart_ResetChange(&state->changes[slot]);
    LinkState_ResetAnswer(state, slot);
    LinkScene_SetAcked(state, slot, 0);
    if (slot != HOST_SLOT) {
        LinkState_SetStatus(state, slot, STATUS_TOLD);
    }
    if (slot == LinkScene_Successor(state)) {
        LinkScene_SetSuccessor(state, LINK_STATE_SLOTS);
    }
    if (slot == LinkScene_LeavingHolder(state)) {
        LinkScene_SetLeavingHolder(state, LINK_STATE_SLOTS);
    }
    if ((u32) slot == LinkScene_LeavingGuest(state)) {
        LinkScene_SetLeavingGuest(state, LINK_STATE_SLOTS);
    }
    if (slot == LinkScene_StateAsker(state)) {
        LinkScene_SetStateAsker(state, LINK_STATE_SLOTS);
    }
    if (slot == LinkScene_StateSentTo(state)) {
        LinkScene_SetStateSentTo(state, LINK_STATE_SLOTS);
    }
    if (slot == LinkScene_NextHolder(state)) {
        LinkScene_SetNextHolder(state, LINK_STATE_SLOTS);
    }
}
CLEAN_AS(func_020a6a74, LinkState_ForgetSlot)

/* func_020a6b38: the destructor: the parts' arrays ended, last first. */
LinkState *LinkState_Destruct(LinkState *state)
{
    __cxa_vec_cleanup(state->changes, LINK_STATE_SLOTS, sizeof(LinkStatePlaceChange), (void (*)(void *)) func_020a77c8);
    __cxa_vec_cleanup(state->arrived, LINK_STATE_SLOTS, sizeof(u32), (void (*)(void *)) func_020a76e4);
    __cxa_vec_cleanup(state->moves, LINK_STATE_SLOTS, sizeof(LinkStateMove), (void (*)(void *)) func_020a7718);
    __cxa_vec_cleanup(state->places, LINK_STATE_SLOTS, sizeof(LinkStatePlace), (void (*)(void *)) func_020a7754);
    return state;
}
CLEAN_AS(func_020a6b38, LinkState_Destruct)

/* func_020a6b88: the constructor (data_021f4320's, at start-up): the parts' arrays made, then
 * everything reset. */
LinkState *LinkState_Construct(LinkState *state)
{
    __cxa_vec_ctor(state->places, LINK_STATE_SLOTS, sizeof(LinkStatePlace), (void (*)(void *)) func_020a7758,
                   (void (*)(void *)) func_020a7754);
    __cxa_vec_ctor(state->moves, LINK_STATE_SLOTS, sizeof(LinkStateMove), (void (*)(void *)) func_020a771c,
                   (void (*)(void *)) func_020a7718);
    __cxa_vec_ctor(state->arrived, LINK_STATE_SLOTS, sizeof(u32), (void (*)(void *)) func_020a76e8,
                   (void (*)(void *)) func_020a76e4);
    __cxa_vec_ctor(state->changes, LINK_STATE_SLOTS, sizeof(LinkStatePlaceChange), (void (*)(void *)) func_020a77cc,
                   (void (*)(void *)) func_020a77c8);
    LinkState_Reset(state);
    return state;
}
CLEAN_AS(func_020a6b88, LinkState_Construct)

/* func_020a6c6c: the slot `slot` forgotten by data_021f4320. */
void LinkState_GlobalForgetSlot(int slot)
{
    LinkState_ForgetSlot(&data_021f4320, slot);
}
CLEAN_AS(func_020a6c6c, LinkState_GlobalForgetSlot)

/* func_020a6c7c */
void LinkState_GlobalReset(void)
{
    LinkState_Reset(&data_021f4320);
}
CLEAN_AS(func_020a6c7c, LinkState_GlobalReset)

/* func_020a6cc4 */
u8 LinkState_GlobalByteC4(void)
{
    return LinkState_ByteC4(&data_021f4320);
}
CLEAN_AS(func_020a6cc4, LinkState_GlobalByteC4)

/* func_020a6cd4 */
void LinkState_GlobalSetByteC4(int value)
{
    LinkState_SetByteC4(&data_021f4320, (u8) value);
}
CLEAN_AS(func_020a6cd4, LinkState_GlobalSetByteC4)
