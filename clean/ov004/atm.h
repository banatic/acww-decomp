/* The ATM: a scene object of overlay 4 (C++ class with vtable 0x0224fc4c) that the player
 * talks to. Its receiver part is named "sp_npc_atm" and its messages come from "st_atm" (the
 * strings at 0x0224fc20 and 0x0224fbe8). One exists at a time: data_ov004_02256c00 points at
 * it once it is set up, and func_020b7424 hands it out.
 *
 * Its conversation shows a 16-bit count kept in the player's data (at offset 0x2404 of the
 * record func_020984e8 returns) with the level func_020adde4 gives it (0 to 4) and the amount
 * left to the next level (func_020adda8). */
#ifndef CLEAN_OV004_ATM_H
#define CLEAN_OV004_ATM_H

#include "types.h"

#include "autoload_2/approach.h"

/* The conversation the ATM's receiver part is attached to (set by the code that starts it). */
typedef struct AtmTalk {
    u8 unk_00[4];
    s32 unk_04; /* the ATM waits for it to become non-zero, then for it to become 0 again */
    s32 unk_08; /* set to 1 when the ATM starts talking */
} AtmTalk;

typedef struct Atm {
    const void *vtable; /* 0x0224fc4c */
    u8 unk_004[0x58];
    Vec3 position;
    u8 unk_068[0x26];
    s16 angle;
    u8 unk_090[0x5c];
    /* The message-receiver base (Base_02066994), at 0xec. */
    const void *receiver_vtable; /* 0x0224fcc0 */
    u8 unk_0f0[0x1a];
    u8 talk_state; /* the receiver's state byte */
    u8 unk_10b[0x21];
    AtmTalk *talk;
    u8 unk_130[4];
    s32 state;            /* AtmState */
    u8 unk_138[4];        /* an entry of the list at data_021c30e4 (func_020321bc adds it) */
    u8 unk_13c[0x98];     /* not touched here */
    u8 unk_1d4[10][0x44]; /* ten entries func_020b7e04 walks */
} Atm;

enum AtmState {
    ATM_IDLE = 0,
    ATM_TALK = 1,     /* waits for the conversation's unk_04 */
    ATM_TALK_END = 2, /* waits for it to clear, then lets the scene go on */
    ATM_STATE_COUNT = 3
};

void Atm_PickChoiceMessage(Atm *atm);
void Atm_PickLevelMessage(Atm *atm);
void Atm_IgnoreReceiverHook(void *object);
void Atm_UpdateTalkEnd(Atm *atm);
int Atm_EnterTalkEnd(Atm *atm);
void Atm_UpdateTalk(Atm *atm);
int Atm_EnterTalk(Atm *atm);
void Atm_UpdateIdle(void);
int Atm_EnterIdle(Atm *atm);
void Atm_UpdateState(Atm *atm);
int Atm_EnterState(Atm *atm, int state);
void Atm_HandleEvent(Atm *atm, int event);
int Atm_IsFacedBy(const Atm *atm, const Atm *other);
void Atm_ShowCount(Atm *atm);
int Atm_Unregister(Atm *atm);
void Atm_Register(Atm *atm);
int Atm_Exit(Atm *atm);
int Atm_Vfunc24(void);
int Atm_Update(Atm *atm);
int Atm_Init(Atm *atm);
Atm *Atm_Delete(Atm *atm);
Atm *Atm_Destroy(Atm *atm);
Atm *Atm_Construct(Atm *atm);
Atm *Atm_Current(void);
void Atm_Create(void);
Atm *AtmReceiver_Delete(void *receiver);
void AtmReceiver_PickChoiceMessage(void *receiver);
void AtmReceiver_PickLevelMessage(void *receiver);
void AtmReceiver_IgnoreHook(void *receiver);
Atm *AtmReceiver_Destroy(void *receiver);

#endif
