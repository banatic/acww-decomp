/* The nameplate in front of a villager's house: an "obj_etc_board" scene object of overlay 3
 * (class vtable 0x02238010, 0x154 bytes) that shows message 0 of obj_etc_board, "<villager>'s
 * house" (sign_board.h has the town's other boards, messages 1-14).
 *
 * Up to eight exist at once, one per index 0-7 (the word at 0x08, which also picks the
 * villager of the town, the entry of the table at 0x021e5a2c, whose name it shows). A table at 0x0223c5f4 holds them by index,
 * with their count at 0x0223c5a0.
 *
 * Like the other scene objects it is a Base_0203f080 with a message receiver (Base_02066994)
 * at 0xec. Its update runs one of three states, chosen by the word at 0x134:
 *
 *   0 idle:    nothing happens; event 0 moves it to state 1.
 *   1 waiting: entering it names the receiver "obj_etc_board", fills the receiver's text from
 *              its table entry and raises the link's request; it moves to state 2 once the
 *              link reports itself open.
 *   2 open:    once the link closes it releases the receiver.
 *
 * Event 8 puts it back to state 0. */
#ifndef CLEAN_OV003_VILLAGER_NAMEPLATE_H
#define CLEAN_OV003_VILLAGER_NAMEPLATE_H

#include "autoload_2/approach.h" /* Vec3 */
#include "types.h"

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct VillagerNameplateLink {
    int unk_00;
    int open;      /* nonzero while what the request opened is up */
    int requested; /* set to 1 when the board enters state 1 */
} VillagerNameplateLink;

enum VillagerNameplateState {
    VILLAGER_NAMEPLATE_IDLE,
    VILLAGER_NAMEPLATE_WAITING,
    VILLAGER_NAMEPLATE_OPEN,
    VILLAGER_NAMEPLATE_STATES
};

typedef struct VillagerNameplate {
    const void *vtable; /* data_ov003_02238010 */
    u8 unk_04[4];
    u32 index; /* 0-7 */
    u8 unk_0c[0x5c - 0x0c];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov003_02238078 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 receiver_unk_1e; /* Base_02066994's byte at 0x1e */
    u8 unk_10b[0x12c - 0x10b];
    VillagerNameplateLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[4];
    int state;        /* enum VillagerNameplateState */
    u8 member_138[4]; /* constructed by func_020b7f70, destroyed by func_020b7f60 */
    u8 unk_13c[0x154 - 0x13c];
} VillagerNameplate;

#define VILLAGER_NAMEPLATE_MAX 8

/* What VillagerNameplate_IsFacedBy reads of the other actor. */
typedef struct VillagerNameplateViewer {
    u8 unk_00[0x5c];
    Vec3 position;
    u8 unk_68[0x8e - 0x68];
    s16 yaw; /* the direction it faces */
} VillagerNameplateViewer;

VillagerNameplate *VillagerNameplate_At(int index);
void VillagerNameplate_UpdateOpen(VillagerNameplate *board);
int VillagerNameplate_EnterOpen(VillagerNameplate *board);
void VillagerNameplate_UpdateWaiting(VillagerNameplate *board);
int VillagerNameplate_EnterWaiting(VillagerNameplate *board);
void VillagerNameplate_UpdateIdle(VillagerNameplate *board);
int VillagerNameplate_EnterIdle(VillagerNameplate *board);
void VillagerNameplate_Update(VillagerNameplate *board);
int VillagerNameplate_SetState(VillagerNameplate *board, int state);
void VillagerNameplate_HandleEvent(VillagerNameplate *board, int event);
int VillagerNameplate_IsFacedBy(VillagerNameplate *board, const VillagerNameplateViewer *viewer);
void VillagerNameplate_ClearTableIfEmpty(void);
int VillagerNameplate_Unregister(VillagerNameplate *board);
int VillagerNameplate_Slot24(void);
int VillagerNameplate_Run(VillagerNameplate *board);
int VillagerNameplate_Init(VillagerNameplate *board);
VillagerNameplate *VillagerNameplate_Delete(VillagerNameplate *board);
VillagerNameplate *VillagerNameplate_Destruct(VillagerNameplate *board);
VillagerNameplate *VillagerNameplate_Construct(VillagerNameplate *board);
void VillagerNameplate_New(void);
VillagerNameplate *VillagerNameplate_ReceiverDelete(void *receiver);
VillagerNameplate *VillagerNameplate_ReceiverDestruct(void *receiver);

#endif
