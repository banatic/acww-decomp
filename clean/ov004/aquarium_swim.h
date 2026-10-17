/* What the museum's aquarium fish (aquarium_fish.h) share for swimming: random numbers and
 * angles, moving along a yaw, climbing and diving, tilting their pitch, the joint animations
 * that bend them when they turn, and turning from the glass of the river room's tanks. Also
 * the constructor and destructor of a fish's body (AquariumFishBody, vtable 0x02255d28).
 *
 * Bending: a fish turning holds its animation at frame 3 (bent one way) or 10 (the other,
 * AquariumFish.unk_1fe says which). A fish of three animations (unk_1c6) instead plays its
 * animation 1 or 2 once its current one ends, held at that frame, and plays animation 0 again
 * at the end of the bending one. */
#ifndef CLEAN_OV004_AQUARIUM_SWIM_H
#define CLEAN_OV004_AQUARIUM_SWIM_H

#include "aquarium_fish.h"
#include "autoload_2/vector.h"
#include "types.h"

/* The fields of a fish its swimming helpers name, which aquarium_fish.h leaves unnamed. */
typedef union AquariumSwimmer {
    AquariumFish base;
    struct {
        u8 head[0x22e];
        u8 bending; /* 0x22e: its bending animation (1 or 2) plays */
    } bend;
    struct {
        u8 head[0x250];
        s16 glass_turned; /* 0x250: how far it has turned from the glass, by glass_step */
    } glass;
} AquariumSwimmer;

/* The frames a turning fish holds its animation at (AquariumFish.unk_1fe). */
enum {
    AQUARIUM_BEND_RIGHT = 3,
    AQUARIUM_BEND_LEFT = 10,
};

int AquariumSwim_TurnTowards(s16 *yaw, const Vec3 *from, const Vec3 *to, fx32 near);
int AquariumSwim_Random(int low, int high);
s16 AquariumSwim_RandomAngle(int high, int low);
fx32 AquariumSwim_RandomUnits(int low, int high);
void AquariumSwim_TiltEased(AquariumFish *fish, int most);
void AquariumSwim_TiltBySpeed(AquariumFish *fish, int most, int rate);
void AquariumSwim_TiltFixed(AquariumFish *fish);
void AquariumSwim_ClimbByFocus(AquariumFish *fish);
void AquariumSwim_Climb(AquariumFish *fish);
void AquariumSwim_ClimbWithin(AquariumFish *fish, int step, fx32 top, fx32 bottom);
int AquariumSwim_TurnRound(AquariumFish *fish);
int AquariumSwim_Straighten(AquariumFish *fish);
void AquariumSwim_PlayAnim(AquariumFish *fish, int anim);
int AquariumSwim_EndBend(AquariumFish *fish);
void AquariumSwim_Bend(AquariumFish *fish, int frame);
void AquariumSwim_StartGlassTurn(AquariumFish *fish, int x_first, int low, int high);
void AquariumSwim_TurnFromGlass(AquariumFish *fish);
void AquariumSwim_WatchGlass(AquariumFish *fish);
int AquariumSwim_NearGlass(AquariumFish *fish);
int AquariumSwim_GroundIsHalf(const Vec3 *point);
int AquariumSwim_EdgeNearerAlongX(const Vec3 *point, int yaw);
int AquariumSwim_Move(Vec3 *point, fx32 distance, int yaw);
fx32 AquariumSwim_MoveZ(fx32 *z, fx32 distance, int yaw);
void AquariumSwim_MoveX(fx32 *x, fx32 distance, int yaw);
AquariumFishBody *AquariumFishBody_Destruct(AquariumFishBody *body);
AquariumFishBody *AquariumFishBody_Construct(AquariumFishBody *body);

#endif
