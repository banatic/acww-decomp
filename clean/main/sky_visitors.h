/* The objects of kinds 5, 6 and 7 that cross the sky in entry 45 (sky_events.h adds them):
 * each goes along the path across the town's six acres (SkyObjectKinds_StartPath), bobbing,
 * until it passes the end or a shot of this system's player hits it (SkyShots_HitsBox). On
 * the hit it changes its resource, the player looks at it (SkyShots_StartLook2, 4 or 7, with
 * the point the look follows given each frame, SkyShots_SetHitPoint) and it falls off the
 * bottom of the screen, which ends the look (SkyShots_StartDrop3, StartFall5 or StartFall8).
 *
 * - Kind 5 (resource kept, parameter 1: the variant handed to SkyShots_StartLook2): falls
 *   straight down, slowed by drag.
 * - Kind 6 (it sets flag 9 of the state block when set up): plays two animations as it is
 *   thrown up and sideways, then falls with a drift, giving off small objects of kind 2 every
 *   two or three frames (SkyKind6_Sparkle); off the screen it marks calendar event 0x44 for
 *   today and has object 0x5020 placed at the player's position (EventBuildings_Place5020).
 * - Kind 7 (west to east when its resource is 0x28): gives one object of kind 2 where it was
 *   hit (SkyKind7_AddSparkle), shrinks for a frame, then falls; off the screen it marks event
 *   0x45 for today. */
#ifndef CLEAN_MAIN_SKY_VISITORS_H
#define CLEAN_MAIN_SKY_VISITORS_H

#include "autoload_2/vector.h"
#include "sky_object_kinds.h"
#include "sky_objects.h"
#include "types.h"

/* The words at 0x60 of a visitor. */
typedef struct SkyVisitorVars {
    s32 state;  /* 0x60: SkyVisitorState */
    s32 count;  /* 0x64: kind 5: its variant; kind 6: frames to its next sparkle, 0: none;
                * kind 7: frames of its sound or of its shrinking */
    s32 unk_68; /* 0x68: cleared, never read */
} SkyVisitorVars;

/* SkyVisitorVars.state. */
enum SkyVisitorState {
    SKY_VISITOR_CROSSING = 0,
    SKY_VISITOR_HIT = 1,
    SKY_VISITOR_THROWN = 2,   /* kind 6: its first animation; kind 7: shrunk for a frame */
    SKY_VISITOR_TURNING = 3,  /* kind 6: its second animation starts */
    SKY_VISITOR_FALLING = 4,  /* kind 6 */
    SKY_VISITOR_DROPPING = 6, /* kind 7 */
};

void SkyKind7_TakeDown(SkyObject *object);
void SkyKind7_Run(SkyObject *object);
void SkyKind7_SetUp(SkyObject *object);
void SkyKind7_AddSparkle(const Vec3 *at, fx32 scale, fx32 speed);
void SkyKind6_TakeDown(SkyObject *object);
void SkyKind6_Run(SkyObject *object);
void SkyKind6_SetUp(SkyObject *object);
void SkyKind6_Sparkle(SkyObject *object);
void SkyKind5_TakeDown(SkyObject *object);
void SkyKind5_Run(SkyObject *object);
void SkyKind5_SetUp(SkyObject *object, int param);

#endif
