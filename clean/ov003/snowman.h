/* The snowman of overlay 3 (class Obj_ov003_022382ac, vtable 0x022382ac; its receiver part at
 * 0xec, whose name is "sp_npc_snowman"): how it talks.
 *
 * Like the other scene objects it is a Base_0203f080 with a message receiver (Base_02066994) at
 * 0xec. Its update runs two state machines; the first (the word at 0x39c) lives mostly in
 * overlay 68, the second (the word at 0x3a0, SnowmanTalkState) is here and is driven through
 * tables of member pointers (ov004/member_pointer.h):
 *
 *   0 idle:     nothing happens; scene event 0 or 1 starts a talk.
 *   1 talk:     entering it takes the receiver, names it, picks one of three messages for the
 *               snowman's kind (bits 2-3 of the flags at 0x378), from the first set while flag
 *               0x100 is still set and the second set after, raises the link's request and sets
 *               the receiver's speaker name (message 0x26 of "st_spnpc_name"); flag 0x100 is
 *               cleared. Once the link reports itself open it moves to state 2.
 *   2 talk end: once the link closes it hands the receiver back and lets the scene go on.
 *
 * Scene event 8 makes it idle again. Another actor can talk to it while it stands within 2.5 of
 * it and the first machine is in state 0xb (vtable slot 0x48). */
#ifndef CLEAN_OV003_SNOWMAN_H
#define CLEAN_OV003_SNOWMAN_H

#include "autoload_2/approach.h" /* Vec3 */
#include "types.h"

/* What the receiver's link (Base_02066994's word at 0x40) points at. */
typedef struct SnowmanLink {
    int unk_00;
    int open;      /* nonzero while what the request opened is up */
    int requested; /* set to 1 when a talk starts */
} SnowmanLink;

enum SnowmanTalkState { SNOWMAN_TALK_IDLE, SNOWMAN_TALK_OPEN, SNOWMAN_TALK_END, SNOWMAN_TALK_STATES };

/* Bits of Snowman.flags. */
#define SNOWMAN_FLAG_FIRST_TALK 0x100 /* messages 0-0xb while set, 0xc-0x17 after */
#define SNOWMAN_KIND_SHIFT 2          /* bits 2-3: which three messages of a set */

typedef struct Snowman {
    const void *vtable; /* data_ov003_022382ac */
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
    u8 unk_68[0xec - 0x68];
    /* The message receiver (Base_02066994) */
    const void *receiver_vtable; /* data_ov003_02238314 */
    char receiver_name[25];      /* written by func_020a8164 */
    u8 unk_109;
    u8 message; /* Base_02066994's byte at 0x1e: the message to show */
    u8 unk_10B[0x12c - 0x10b];
    SnowmanLink *link; /* Base_02066994's word at 0x40 */
    u8 unk_130[0x378 - 0x130];
    u16 flags;
    u8 unk_37A[0x39c - 0x37a];
    int scene_state; /* the first machine's state (overlay 68) */
    int talk_state;  /* enum SnowmanTalkState */
} Snowman;

/* What SnowmanTalk_CanTalkTo reads of the other actor. */
typedef struct SnowmanVisitor {
    u8 unk_00[0x5c];
    Vec3 position;
} SnowmanVisitor;

void SnowmanTalk_UpdateEnd(Snowman *snowman);
int SnowmanTalk_EnterEnd(void);
void SnowmanTalk_UpdateOpen(Snowman *snowman);
int SnowmanTalk_EnterOpen(Snowman *snowman);
void SnowmanTalk_UpdateIdle(Snowman *snowman);
int SnowmanTalk_EnterIdle(void);
void SnowmanTalk_Update(Snowman *snowman);
int SnowmanTalk_SetState(Snowman *snowman, int state);
void SnowmanTalk_OnSceneEvent(Snowman *snowman, int event);
int SnowmanTalk_CanTalkTo(Snowman *snowman, const SnowmanVisitor *visitor);

#endif
