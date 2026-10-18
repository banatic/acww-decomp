/* The ATM: a scene object of overlay 4 (C++ class with vtable 0x0224fc4c) that the player
 * talks to. Its receiver part is named "sp_npc_atm" and its messages come from "st_atm" (the
 * strings at 0x0224fc20 and 0x0224fbe8). One exists at a time: data_ov004_02256c00 points at
 * it once it is set up, and TouchPick_Atm hands it out.
 *
 * Its conversation shows a 16-bit count kept in the player's data (at offset 0x2404 of the
 * record PlayerRecords_Current returns) with the level ShopPoints_Level gives it (0 to 4) and the amount
 * left to the next level (ShopPoints_ToNextLevel). */
#ifndef CLEAN_OV004_ATM_H
#define CLEAN_OV004_ATM_H

#include "types.h"

#include "autoload_2/approach.h"
#include "main/collision_box.h"
#include "main/scene_object_base.h"
#include "main/talk_object.h"
#include "main/talk_receiver.h"
#include "main/touch_pick_shapes.h"

typedef struct Atm {
    union {
        SceneObjectBase base; /* the main program's scene object it extends */
        struct {
            const void *vtable; /* 0x0224fc4c */
            u8 unk_004[0x58];
            Vec3 position;
            u8 unk_068[0x26];
            s16 angle;
            u8 unk_090[0x5c];
        };
    };
    union {
        TalkReceiver receiver; /* its receiver part, at 0xec */
        struct {
            const void *receiver_vtable; /* 0x0224fcc0 */
            u8 unk_0f0[0x1a];
            u8 talk_state; /* the receiver's state byte */
            u8 unk_10b[0x21];
            /* The conversation the receiver part is attached to (set by the code that starts
             * it): the ATM waits for its state to become non-zero, then for it to become 0
             * again, and sets its next state to 1 when it starts talking. */
            TalkObject *talk;
            u8 unk_130[4];
        };
    };
    s32 state;               /* AtmState */
    CollisionBox box;        /* in the list at data_021c30e4 (CollisionBox_Add adds it) */
    TouchPickFace faces[10]; /* the faces TouchPick_AddFaces walks */
} Atm;

enum AtmState {
    ATM_IDLE = 0,
    ATM_TALK = 1,     /* waits for the conversation's state */
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
