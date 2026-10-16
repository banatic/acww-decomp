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

typedef struct LinkState {
    u8 unk_00[0x84];
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

#endif
