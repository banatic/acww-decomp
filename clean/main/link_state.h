/* The link state (data_021f4320, session_link.h): next to the session, what the linked systems
 * agree on before one of them joins or leaves.
 *
 * A slot asks by its link status (status[slot], func_020a6170): 0-3 asks for a change of the
 * kind of that number. The host (slot 0) serves one request at a time (LinkState_HostStep):
 * the slot served becomes `chosen` and its kind `kind`, and the host polls every other slot of
 * the session with a status byte (func_020a76ac: an answer in bits 0-2, the kind in bits 5-7,
 * the slot served in bits 3-4) sent as a session message of handler 0xc. Each system answers
 * in its `answers` entry (LinkState_SystemStep): it accepts (2) once it is in a scene where
 * the change can happen, or refuses (3) after 160 frames; the host then has every slot carry it
 * out (5) or cancel it (4), and each says when it is done (6).
 *
 * The kinds: 0 a system joins (the host runs the activity's job 0x15, a guest job 0x16 and
 * goes to scene 0xd, or 0x2f when the joining player is paired with this town); 1 a system
 * leaves (jobs 0x18 and 0x19, scene 0x2e); 2 and 3 the session ends (job 0x1b with the start
 * menu's leave choice 0 or 1, scene 0x2e). */
#ifndef CLEAN_MAIN_LINK_STATE_H
#define CLEAN_MAIN_LINK_STATE_H

#include "types.h"

#define LINK_STATE_SLOTS 4

/* Where a slot is (link_scene.h): the scene it is in (0x3f for none), whether it holds that
 * scene's state, and whether the host let it move to another scene. */
typedef struct LinkStatePlace {
    u8 scene;
    u8 holder;
    u8 moving;
} LinkStatePlace;

/* A move asked of the host: the slot (LINK_STATE_SLOTS for none) and the scene it goes to. */
typedef struct LinkStateMove {
    s32 slot;
    u8 scene;
    u8 unk_05[3];
} LinkStateMove;

/* Changes to a slot's place the host has still to apply and send: the values, and in `mask`
 * the fields they are for (bit 0 the scene, bit 1 holder, bit 2 moving). */
typedef struct LinkStatePlaceChange {
    u8 scene;
    u8 holder;
    u8 moving;
    u8 unk_03;
    u32 mask;
} LinkStatePlaceChange;

typedef struct LinkState {
    LinkStatePlace places[LINK_STATE_SLOTS];        /* 0x00 */
    LinkStateMove moves[LINK_STATE_SLOTS];          /* 0x0c: the host's queue, oldest first */
    u32 arrived[LINK_STATE_SLOTS];                  /* 0x2c: 1 once the slot is in its new scene */
    LinkStatePlaceChange changes[LINK_STATE_SLOTS]; /* 0x3c */
    u8 enters_first;                                /* 0x5c: no system held the scene entered */
    u8 unk_5d[3];
    s32 scene_phase;            /* 0x60: LinkScenePhase (link_scene.h) */
    s32 successor;              /* 0x64: the slot handed the scene's state on leaving it */
    u8 acked[LINK_STATE_SLOTS]; /* 0x68: the slots that saw this system leave as holder */
    s32 leaving_holder;         /* 0x6c: the moving holder this system last acknowledged */
    s32 next_holder;            /* 0x70: the holder of the scene this system enters */
    s32 state_asker;            /* 0x74: the slot that asked this system for its scene's state */
    s32 state_sent_to;          /* 0x78: the slot this system sent its scene's state to */
    u8 released;                /* 0x7c: the scene's holder let this system leave */
    u8 unk_7d[3];
    u32 leaving_guest;            /* 0x80: the moving slot this system last released */
    s32 status[LINK_STATE_SLOTS]; /* 0x84: each slot's link status (func_020a6170) */
    u32 served_slot;              /* 0x94: the slot of the last change carried out */
    u16 half_98;                  /* 0x98 */
    u8 unk_9a[2];
    u32 host_phase;                /* 0x9c: LinkStateHostPhase */
    s32 chosen;                    /* 0xa0: the slot whose request is served */
    u32 kind;                      /* 0xa4: its kind; LINK_STATE_KIND_NONE for none */
    s32 answers[LINK_STATE_SLOTS]; /* 0xa8: LinkStateAnswer of each slot */
    u32 wait_frames;               /* 0xb8: the frames this system waited to accept */
    u8 hold_frames;                /* 0xbc: the frames left before this system carries it out */
    u8 unk_bd[3];
    u32 done_kind; /* 0xc0: the kind of the last change this system carried out */
    u8 byte_c4;    /* 0xc4: cleared when a join is carried out */
} LinkState;

#define LINK_STATE_KIND_NONE 4

/* The host's progress with a request (host_phase). */
enum LinkStateHostPhase {
    LINK_STATE_HOST_ASK = 0,     /* the other slots to be asked */
    LINK_STATE_HOST_COLLECT = 1, /* their answers awaited */
    LINK_STATE_HOST_GO = 2,      /* carried out: the other slots awaited */
    LINK_STATE_HOST_CANCEL = 3,  /* cancelled: the other slots awaited */
    LINK_STATE_HOST_IDLE = 4,
};

/* A slot's answer (answers[]) and the status bytes sent with them. */
enum LinkStateAnswer {
    LINK_STATE_ANSWER_ASKED = 0, /* the host's own slot, asked */
    LINK_STATE_ANSWER_WAIT = 1,  /* asked: deciding */
    LINK_STATE_ANSWER_YES = 2,
    LINK_STATE_ANSWER_NO = 3,
    LINK_STATE_ANSWER_CANCEL = 4, /* told to cancel */
    LINK_STATE_ANSWER_GO = 5,     /* told to carry it out */
    LINK_STATE_ANSWER_DONE = 6,
};

u8 LinkState_ByteC4(LinkState *state);
void LinkState_SetByteC4(LinkState *state, u8 value);
u32 LinkState_DoneKind(LinkState *state);
void LinkState_SetDoneKind(LinkState *state, u32 kind);
u8 LinkState_HoldFrames(LinkState *state);
void LinkState_SetHoldFrames(LinkState *state, u8 frames);
u32 LinkState_WaitFrames(LinkState *state);
void LinkState_SetWaitFrames(LinkState *state, u32 frames);
void LinkState_SystemStep(LinkState *state);
void LinkState_ResetAnswers(LinkState *state);
void LinkState_ResetAnswer(LinkState *state, int slot);
int LinkState_Answer(LinkState *state, int slot);
void LinkState_SetAnswer(LinkState *state, int slot, int answer);
void LinkState_ResetKind(LinkState *state);
u32 LinkState_Kind(LinkState *state);
void LinkState_SetKind(LinkState *state, u32 kind);
void LinkState_ResetChosen(LinkState *state);
int LinkState_Chosen(LinkState *state);
void LinkState_SetChosen(LinkState *state, int slot);
void LinkState_ResetHostPhase(LinkState *state);
u32 LinkState_HostPhase(LinkState *state);
void LinkState_SetHostPhase(LinkState *state, u32 phase);
u16 LinkState_Half98(LinkState *state);
void LinkState_SetHalf98(LinkState *state, u16 value);
u32 LinkState_ServedSlot(LinkState *state);
void LinkState_SetServedSlot(LinkState *state, u32 slot);
void LinkState_HostStep(LinkState *state);

void LinkState_RefuseRequest(LinkState *state, int slot, int direct);
void LinkState_ResetStatuses(LinkState *state);
int LinkState_Status(LinkState *state, int slot);
void LinkState_SetStatus(LinkState *state, int slot, int status);
void LinkState_Reset(LinkState *state);
void LinkState_ForgetSlot(LinkState *state, int slot);
LinkState *LinkState_Destruct(LinkState *state);
LinkState *LinkState_Construct(LinkState *state);
void LinkState_GlobalForgetSlot(int slot);
void LinkState_GlobalReset(void);
u8 LinkState_GlobalByteC4(void);
void LinkState_GlobalSetByteC4(int value);

#endif
