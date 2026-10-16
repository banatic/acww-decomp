/* The objects of kind 3 (entry 30, added at night by SkyEvents_AddKind3) and of kind 2.
 *
 * Kind 3 starts off the screen's right or top edge and crosses fast (7.5 pixels a frame)
 * towards a point on the left edge at y 128 to 150, turned along its way. While it is on the
 * screen and not marked (its parameter 0) the byte at 0x2f50 of the objects is set
 * (SkyObjects.unk_2f50); SkyObjects_Add2Mark3 marks it and adds a kind-2 object that follows
 * it.
 *
 * Kind 2 does one of three things by the low four bits of its parameter: 0, a short-lived
 * object that drifts, slowed by drag, until its animation is done (SkyKind7_AddSparkle gives
 * one); 1, a follower kept behind the object of kind 3 (16 pixels over that object's
 * height scale: 32 pixels),
 * turning and sized from a table for 23 frames, done once there is no running kind 3; others
 * (SkyKind6_Sparkle gives 2 and 3), done after 6 frames. */
#ifndef CLEAN_MAIN_SKY_KIND3_H
#define CLEAN_MAIN_SKY_KIND3_H

#include "sky_object_kinds.h"
#include "sky_objects.h"
#include "types.h"

/* Kind 2's parameter (its low four bits). */
enum SkyKind2Mode {
    SKY_KIND2_DRIFT = 0,
    SKY_KIND2_FOLLOW = 1,
};

/* The words at 0x60 of an object of kind 2 or 3. */
typedef struct SkyKind2Vars {
    u32 param;  /* 0x60: kind 2: SkyKind2Mode; kind 3: 1 once marked */
    s32 timer;  /* 0x64: kind 2: its frames */
    u32 unk_68; /* 0x68 */
    u32 unk_6c; /* 0x6c */
    u32 unk_70; /* 0x70 */
} SkyKind2Vars;

void SkyKind3_TakeDown(SkyObject *object);
void SkyKind3_Run(SkyObject *object);
void SkyKind3_SetUp(SkyObject *object);
void SkyKind2_TakeDown(SkyObject *object);
void SkyKind2_Run(SkyObject *object);
void SkyKind2_SetUp(SkyObject *object, int param);
int SkyKind2_Follow(SkyObject *object);

#endif
