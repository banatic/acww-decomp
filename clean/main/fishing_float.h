/* The float of a fishing rod ("Uki"): its models and its flight, bobbing and reeling.
 *
 * The pool of float models (data_021cad80, a global C++ object) has nine entries, one per
 * item held in the scene, numbered as the held items' pool (held_item_pool.h): the first four
 * the players', the others the scene's other actors'. Each keeps a buffer for the model file
 * ("/PItm/Uki0/<model>.nsbmd", taken from the scene's heap at data_021c9ac8), the VRAM region
 * its texture is placed in and the task that takes the texture there, the model, and the
 * float that uses the entry.
 *
 * A float (0x40 bytes, at 0x28 in a field actor's held item) is set up for a rod when the
 * item is taken (FishingFloat_Setup; the rods 0x1374, 0x1375, 0x137a and 0x137b) and moved
 * once a frame (FishingFloat_Update) by the step function of its state, from the table of
 * member functions at data_021cad30:
 *
 *   0 FISHING_FLOAT_NONE      nothing
 *   1 FISHING_FLOAT_HELD      at the rod's tip, where the drawing puts it
 *   2 FISHING_FLOAT_SWING     the rod swung back, then the float thrown ahead (frames 15-20)
 *   3 FISHING_FLOAT_CAST      swung back, then flying on its arc until it lands in water
 *   4 FISHING_FLOAT_FLOATING  bobbing on the water, drifting with it, held at the line's length
 *   5 FISHING_FLOAT_SINKING   pulled under the surface
 *   6 FISHING_FLOAT_RIPPLING  rippling the water (raised while a fish is on it)
 *   7 FISHING_FLOAT_REEL      reeled in on a low arc to the rod's tip
 *   8 FISHING_FLOAT_REEL_HIGH reeled in on a higher arc
 *   9 FISHING_FLOAT_RISE      rising until 40.0 high, then none
 *
 * The ground under the float (field_collision.h) is taken as water where its unk_30 is not 0,
 * the surface at its `limit`; the effects (func_020912d4) are 12 (landing), 13 (reeled out of
 * the water), 14 (the line's pull), 15 (bobbing up), 16 (pulled under) and 17 (ripples). */
#ifndef CLEAN_MAIN_FISHING_FLOAT_H
#define CLEAN_MAIN_FISHING_FLOAT_H

#include "autoload_2/vector.h"
#include "main/actor.h"
#include "main/model_loader.h"
#include "main/model_object.h"
#include "main/vram_region.h"
#include "types.h"

/* The number of entries of the pool, also a float's entry for none. */
#define FISHING_FLOAT_POOL_COUNT 9

/* FishingFloat.state */
#define FISHING_FLOAT_NONE 0
#define FISHING_FLOAT_HELD 1
#define FISHING_FLOAT_SWING 2
#define FISHING_FLOAT_CAST 3
#define FISHING_FLOAT_FLOATING 4
#define FISHING_FLOAT_SINKING 5
#define FISHING_FLOAT_RIPPLING 6
#define FISHING_FLOAT_REEL 7
#define FISHING_FLOAT_REEL_HIGH 8
#define FISHING_FLOAT_RISE 9
#define FISHING_FLOAT_STATES 10

/* FishingFloat.ripple and .player for none. */
#define FISHING_FLOAT_NO_EFFECT (-1)
#define FISHING_FLOAT_NO_PLAYER (-1)

typedef struct FishingFloat {
    u8 entry; /* 0x00: its entry in the pool, FISHING_FLOAT_POOL_COUNT for none */
    u8 pad_01[3];
    int state;     /* 0x04: FISHING_FLOAT_* */
    Vec3 position; /* 0x08 */
    fx32 gravity;  /* 0x14: taken from the vertical speed each frame of flight */
    fx32 speed;    /* 0x18: the vertical speed */
    Vec3 target;   /* 0x1c: where it flies to */
    Actor *holder; /* 0x28: the actor holding the rod */
    u8 *fish;      /* 0x2c: the fish on it (ov003), NULL for none */
    int frames;    /* 0x30: frames in the state */
    int ripple;    /* 0x34: the effect following it, FISHING_FLOAT_NO_EFFECT for none */
    u8 landed;     /* 0x38: set in the frame it lands in water */
    u8 pad_39[3];
    int player; /* 0x3c: the holder's player slot, FISHING_FLOAT_NO_PLAYER for none */
} FishingFloat;

typedef struct FishingFloatPool {
    u8 *model_file[FISHING_FLOAT_POOL_COUNT];       /* 0x000: FishingFloatPool_ModelFileSize bytes */
    VramRegion region[FISHING_FLOAT_POOL_COUNT];    /* 0x024 */
    ModelLoaderTask task[FISHING_FLOAT_POOL_COUNT]; /* 0x0d8: a VramCopyTask */
    ModelObject model[FISHING_FLOAT_POOL_COUNT];    /* 0x1d4 */
    FishingFloat *owner[FISHING_FLOAT_POOL_COUNT];  /* 0x750: the float using the entry */
} FishingFloatPool;

int FishingFloat_Fly(const Vec3 *target, fx32 gravity, Vec3 *position, fx32 *speed, unsigned char ease_down);
void FishingFloat_Arc(const Vec3 *target, const Vec3 *position, fx32 *gravity, fx32 *speed, unsigned char arc);
void FishingFloat_SwingBack(FishingFloat *self);
void FishingFloat_StepRise(FishingFloat *self);
void FishingFloat_StepReelHigh(FishingFloat *self);
void FishingFloat_StepReel(FishingFloat *self);
void FishingFloat_StepRippling(FishingFloat *self);
void FishingFloat_StepSinking(FishingFloat *self);
void FishingFloat_StepFloating(FishingFloat *self);
void FishingFloat_StepCast(FishingFloat *self);
void FishingFloat_StepSwing(FishingFloat *self);
void FishingFloat_StepHeld(void);
void FishingFloat_StepNone(void);
void FishingFloat_Draw(FishingFloat *self, const Mtx43 *hand, const Vec3 *scale);
void FishingFloat_Update(FishingFloat *self);
void FishingFloat_SetState(FishingFloat *self, int state);
void FishingFloat_SetPosition(FishingFloat *self, const Vec3 *position);
void FishingFloat_SetTarget(FishingFloat *self, const Vec3 *target);
void FishingFloat_TellPlayerFish(FishingFloat *self);
void FishingFloat_LetFishGo(FishingFloat *self);
int FishingFloat_FishFlag80(FishingFloat *self);
void FishingFloat_ToSurface(FishingFloat *self);
int FishingFloat_FishBite(FishingFloat *self);
int FishingFloat_FishPull(FishingFloat *self);
int FishingFloat_IsInWater(FishingFloat *self);
u8 *FishingFloat_Fish(FishingFloat *self);
void FishingFloat_SetFish(FishingFloat *self, u8 *fish);
void FishingFloat_SetPlayer(FishingFloat *self, int player);
int FishingFloat_Entry(FishingFloat *self);
int FishingFloatPool_FloatingOf(FishingFloatPool *pool, int entry);
void FishingFloatPool_SetOwner(FishingFloatPool *pool, int entry, FishingFloat *owner);
int FishingFloatPool_UploadTexture(FishingFloatPool *pool, int entry);
void FishingFloatPool_PlaceTexture(FishingFloatPool *pool, int entry);
int FishingFloatPool_LoadModel(FishingFloatPool *pool, int entry, int model);
void FishingFloatPool_StopUpload(FishingFloatPool *pool, int entry);
void FishingFloat_Release(FishingFloat *self);
void FishingFloat_Setup(FishingFloat *self, int entry, Actor *holder, unsigned int model);
void FishingFloat_Destruct(void *self);
void FishingFloat_Construct(FishingFloat *self);
ModelObject *FishingFloatPool_Model(FishingFloatPool *pool, int entry);
ModelLoaderTask *FishingFloatPool_Task(FishingFloatPool *pool, int entry);
VramRegion *FishingFloatPool_Region(FishingFloatPool *pool, int entry);
unsigned long FishingFloatPool_ModelFile(FishingFloatPool *pool, int entry);
void FishingFloatPool_Clear(FishingFloatPool *pool);
void FishingFloatPool_AllocEntries(FishingFloatPool *pool);
FishingFloatPool *FishingFloatPool_Destruct(FishingFloatPool *pool);
FishingFloatPool *FishingFloatPool_Construct(FishingFloatPool *pool);
int FishingFloatPool_PaletteSize(void);
int FishingFloatPool_Texture4x4Size(void);
int FishingFloatPool_TextureSize(void);
int FishingFloatPool_ModelFileSize(void);
char *FishingFloatPool_ModelPath(int model);
int FishingFloat_FloatingOf(int entry);
void FishingFloat_EndScene(void);
void FishingFloat_StartScene(struct Heap *parent);

#endif
