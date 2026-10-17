/* The bottle with a letter (item 0x1520, main/bottle_mail.h) a player throws into the water
 * (data_ov003_0225f35c, four records of 0x60 bytes, one per player).
 *
 * The player's throw (field actor state 0x89, at frame 25 of its animation) starts it
 * (ThrownBottle_Throw) from the player's hold point towards the point set before
 * (ThrownBottle_SetTarget: by the pockets screen at this console, or by a message from another
 * console). It flies on an arc (THROWN_BOTTLE_FLYING, ThrownBottle_StepFlying) and, once in
 * the water (where the shadows near it flee, for a player at this console), floats away with
 * the current for 120 frames, sinking and blinking for the last 20 (THROWN_BOTTLE_FLOATING,
 * ThrownBottle_StepFloating). Each frame the fish process steps it (ThrownBottle_Step, from the
 * member functions in data_ov003_0225f100) and the player's fish's emitter plays its sounds
 * (ThrownBottle_SoundCue). */
#ifndef CLEAN_OV003_THROWN_BOTTLE_H
#define CLEAN_OV003_THROWN_BOTTLE_H

#include "autoload_2/vector.h"
#include "main/field_collision.h"
#include "types.h"

#define THROWN_BOTTLE_COUNT 4
#define THROWN_BOTTLE_ITEM 0x1520

/* ThrownBottle.state */
#define THROWN_BOTTLE_NONE 0
#define THROWN_BOTTLE_FLYING 1
#define THROWN_BOTTLE_FLOATING 2
#define THROWN_BOTTLE_STATES 3

typedef struct ThrownBottle {
    CollisionContacts contacts; /* 0x00 */
    u8 state;                   /* 0x30: THROWN_BOTTLE_* */
    u8 pad_31[3];               /* 0x31 */
    Vec3 position;              /* 0x34 */
    Vec3 from;                  /* 0x40: the player's hold point at the throw */
    Vec3 to;                    /* 0x4c: where it lands; its height is set to -3.5 */
    int frames;                 /* 0x58: frames in the state */
    u8 local;                   /* 0x5c: thrown by the player at this console */
    u8 pad_5d[3];               /* 0x5d */
} ThrownBottle;

void ThrownBottle_StepFloating(void *self, ThrownBottle *bottle);
void ThrownBottle_StepFlying(int self, ThrownBottle *bottle);
void ThrownBottle_StepNone(void);
void ThrownBottle_Step(void *self, ThrownBottle *bottle);
int ThrownBottle_OutOfView(ThrownBottle *bottle);
int ThrownBottle_SoundCue(int player);
Vec3 *ThrownBottle_PositionOf(int player);
int ThrownBottle_Throw(int player);
int ThrownBottle_IsActive(int player);
void ThrownBottle_SetTarget(Vec3 *to, int player);
ThrownBottle *ThrownBottle_Destruct(ThrownBottle *bottle);
ThrownBottle *ThrownBottle_Construct(ThrownBottle *bottle);
void ThrownBottle_DestroyAll(void *object);

#endif
