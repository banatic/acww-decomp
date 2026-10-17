/* The constructors and destructors of the museum's aquarium, its rocks and its fish's classes
 * (aquarium_objects.h). */
#include "aquarium_objects.h"

#include <stdint.h>

#include "aquarium_swim.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/model_pool.h"
#include "main/sound_emitter.h"
#include "main/touch_pick_shapes.h"

static_assert(offsetof(AquariumSwimmerFields, own.unk_21c) == 0x21c, "swimmer 0x21c");
static_assert(offsetof(AquariumSwimmerFields, own.unk_220) == 0x220, "swimmer 0x220");
static_assert(offsetof(AquariumSwimmerFields, own.bending) == 0x22e, "swimmer bending");
static_assert(offsetof(AquariumSwimmerFields, own.unk_238) == 0x238, "swimmer 0x238");
static_assert(offsetof(AquariumLaneFish, own.unk_256) == 0x256, "lane fish");
static_assert(offsetof(AquariumFish, ends) == 0x1d0, "fish ends");
static_assert(offsetof(AquariumFish, anims) == 0x54, "fish anims");
static_assert(offsetof(AquariumKind11, own.sound) == 0x1fc, "kind 11 sound");
static_assert(offsetof(MuseumAquarium, rocks[AQUARIUM_EXTRA_ROCK]) == 0x244, "extra rock");
static_assert(sizeof(MuseumAquarium) == 0x810, "aquarium");
static_assert(sizeof(TouchPickFace[AQUARIUM_GLASS_FACES]) == 0x2a8, "a tank's glass");

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The constructors and destructors the arrays are built and destroyed with: the game's. */
extern void func_020012e8(void *object);     /* TrivialObject_Construct */
extern void func_020012dc(void *object);     /* TrivialObject_Destruct */
extern void func_020b82ec(void *faces);      /* TouchPickFaces_ConstructBox */
extern void func_020b82d0(void *faces);      /* TouchPickFaces_DestructBox */
extern void func_ov004_02239da8(void *rock); /* AquariumRock_Construct */
extern void func_ov004_02239c5c(void *rock); /* AquariumRock_Destruct */

/* The vtables: the process base and the aquarium; the fish's classes. */
extern const u32 data_020da13c[];
extern const u32 data_ov004_02255ebc[];
extern const u32 data_ov004_02255db4[]; /* AquariumFish */
extern const u32 data_ov004_02255ea4[]; /* AquariumSwimmer */
extern const u32 data_ov004_02255e2c[]; /* kind 48 */
extern const u32 data_ov004_02255e5c[]; /* kind 47 */
extern const u32 data_ov004_02255d3c[]; /* kinds 12 and 38 */
extern const u32 data_ov004_02255d54[]; /* kinds 5 and 6 */
extern const u32 data_ov004_02255d9c[]; /* kind 30 */
extern const u32 data_ov004_02255dcc[]; /* kind 40 */
extern const u32 data_ov004_02255e8c[]; /* kind 10 */
extern const u32 data_ov004_02255de4[]; /* kind 37 */
extern const u32 data_ov004_02255dfc[]; /* kind 35 */
extern const u32 data_ov004_02255e44[]; /* kind 15 */
extern const u32 data_ov004_02255e74[]; /* kind 11 */
extern const u32 data_ov004_02255d6c[]; /* kinds 52 to 54 */
extern const u32 data_ov004_02255d84[]; /* kinds 50 and 51 */
extern const u32 data_ov004_02255e14[]; /* kind 36 */
/* A sound source's class, set over its base's. */
extern const u32 data_0213efe8[];
extern const u32 data_0213f020[];

/* The fish's joint animations, its tanks' glass, and an AquariumSwimmer's set-up values. */
#define AQUARIUM_FISH_ANIMS 4
#define AQUARIUM_TANKS 2
#define SWIMMER_GLASS_STEP 3
#define SWIMMER_SWIM_224 0x28
#define SWIMMER_LEVEL 0x3000
#define SWIMMER_SWIM_228 0x1000

/* The speeds kinds 37, 35 and 36 start at, and kind 36's pulse. */
#define KIND37_SPEED 0xa3
#define KIND35_SPEED 0x41
#define KIND36_SPEED 0x41
#define KIND36_PULSE_RATE 0x14
#define KIND36_LEAST_SCALE 0xccd

/* A rock's body is a fish's body (0x50 bytes) of no fish. */
static AquariumFishBody *AquariumObjects_rock_body(AquariumRock *rock)
{
    return (AquariumFishBody *) (void *) rock;
}

static AquariumFish *AquariumObjects_swimmer_base(AquariumFish *fish, const u32 *vtable)
{
    AquariumSwimmer_ConstructBase(fish);
    fish->vtable = vtable;
    return fish;
}

/* ---- The aquarium and its rocks */

/* func_ov004_02239c5c: a rock's destructor: its body's. The rock, as a number. */
int AquariumRock_Destruct(AquariumRock *rock)
{
    AquariumFishBody_Destruct(AquariumObjects_rock_body(rock));
    return (int) (intptr_t) rock;
}
CLEAN_AS(func_ov004_02239c5c, AquariumRock_Destruct)

/* The aquarium's destructor, but for the process base's. */
static void Aquarium_destruct_own(MuseumAquarium *self)
{
    self->base.vtable = data_ov004_02255ebc;
    ModelPool_Destruct(&self->pool);
    __cxa_vec_cleanup(self->glass, AQUARIUM_TANKS, sizeof(self->glass[0]), func_020b82d0);
    AquariumFishBody_Destruct(AquariumObjects_rock_body(&self->rocks[AQUARIUM_EXTRA_ROCK]));
    __cxa_vec_cleanup(self->rocks, AQUARIUM_ROCKS, sizeof(AquariumRock), func_ov004_02239c5c);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_ov004_02239c6c (slot 10 of the aquarium's vtable): the destructor, then the aquarium
 * freed (Heap_FreeAux). */
MuseumAquarium *Aquarium_DestructFree(MuseumAquarium *self)
{
    Aquarium_destruct_own(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02239c6c, Aquarium_DestructFree)

/* func_ov004_02239cd4 (slot 9 of the aquarium's vtable): the destructor: the model pool, the
 * glass of both tanks, the rocks (the extra one first), then the process base. */
MuseumAquarium *Aquarium_Destruct(MuseumAquarium *self)
{
    Aquarium_destruct_own(self);
    return self;
}
CLEAN_AS(func_ov004_02239cd4, Aquarium_Destruct)

/* func_ov004_02239d34: the constructor: the process base, the rocks, the glass of both tanks
 * and the model pool. */
MuseumAquarium *Aquarium_Construct(MuseumAquarium *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_02255ebc;
    __cxa_vec_ctor(self->rocks, AQUARIUM_ROCKS, sizeof(AquariumRock), func_ov004_02239da8, func_ov004_02239c5c);
    AquariumFishBody_Construct(AquariumObjects_rock_body(&self->rocks[AQUARIUM_EXTRA_ROCK]));
    __cxa_vec_ctor(self->glass, AQUARIUM_TANKS, sizeof(self->glass[0]), func_020b82ec, func_020b82d0);
    ModelPool_Init(&self->pool);
    return self;
}
CLEAN_AS(func_ov004_02239d34, Aquarium_Construct)

/* func_ov004_02239da8: a rock's constructor: its body's. The rock, as a number. */
int AquariumRock_Construct(AquariumRock *rock)
{
    AquariumFishBody_Construct(AquariumObjects_rock_body(rock));
    return (int) (intptr_t) rock;
}
CLEAN_AS(func_ov004_02239da8, AquariumRock_Construct)

/* ---- Kind 48: an AquariumFish */

/* func_ov004_02239db8 */
AquariumFish *AquariumKind48_Delete(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255e2c;
    AquariumFish_DestructBase(fish);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_02239db8, AquariumKind48_Delete)

/* func_ov004_02239dd8 */
AquariumFish *AquariumKind48_Destruct(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255e2c;
    AquariumFish_DestructBase(fish);
    return fish;
}
CLEAN_AS(func_ov004_02239dd8, AquariumKind48_Destruct)

/* func_ov004_02239df0 */
AquariumFish *AquariumKind48_Construct(AquariumFish *fish)
{
    AquariumFish_Construct(fish);
    fish->vtable = data_ov004_02255e2c;
    return fish;
}
CLEAN_AS(func_ov004_02239df0, AquariumKind48_Construct)

/* ---- Kind 47: an AquariumSwimmer */

/* func_ov004_02239e08 */
AquariumKind47 *AquariumKind47_Delete(AquariumKind47 *fish)
{
    fish->base.vtable = data_ov004_02255e5c;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_02239e08, AquariumKind47_Delete)

/* func_ov004_02239e28 */
AquariumKind47 *AquariumKind47_Destruct(AquariumKind47 *fish)
{
    fish->base.vtable = data_ov004_02255e5c;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_02239e28, AquariumKind47_Destruct)

/* func_ov004_02239e40: its mode does not run yet. */
AquariumKind47 *AquariumKind47_Construct(AquariumKind47 *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255e5c);
    fish->own.may_swim = 0;
    return fish;
}
CLEAN_AS(func_ov004_02239e40, AquariumKind47_Construct)

/* ---- Kinds 12 and 38: an AquariumSwimmer */

/* func_ov004_02239e64 */
AquariumHomeFish *AquariumHomeFish_Delete(AquariumHomeFish *fish)
{
    fish->base.vtable = data_ov004_02255d3c;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_02239e64, AquariumHomeFish_Delete)

/* func_ov004_02239e84 */
AquariumHomeFish *AquariumHomeFish_Destruct(AquariumHomeFish *fish)
{
    fish->base.vtable = data_ov004_02255d3c;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_02239e84, AquariumHomeFish_Destruct)

/* func_ov004_02239e9c: its own fields are left for its set-up. */
AquariumHomeFish *AquariumHomeFish_Construct(AquariumHomeFish *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255d3c);
    return fish;
}
CLEAN_AS(func_ov004_02239e9c, AquariumHomeFish_Construct)

/* ---- Kinds 5 and 6: an AquariumSwimmer */

/* func_ov004_02239eb4 */
AquariumRisingFish *AquariumRisingFish_Delete(AquariumRisingFish *fish)
{
    fish->base.vtable = data_ov004_02255d54;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_02239eb4, AquariumRisingFish_Delete)

/* func_ov004_02239ed4 */
AquariumRisingFish *AquariumRisingFish_Destruct(AquariumRisingFish *fish)
{
    fish->base.vtable = data_ov004_02255d54;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_02239ed4, AquariumRisingFish_Destruct)

/* func_ov004_02239eec: swimming on, not rising, its climb set upwards. */
AquariumRisingFish *AquariumRisingFish_Construct(AquariumRisingFish *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255d54);
    fish->own.stage = 0;
    fish->own.frames_up = 0;
    fish->own.rising = 0;
    fish->own.climb = 1;
    fish->own.came_down = 0;
    return fish;
}
CLEAN_AS(func_ov004_02239eec, AquariumRisingFish_Construct)

/* ---- Kind 30: an AquariumSwimmer */

/* func_ov004_02239f30 */
AquariumKind30 *AquariumKind30_Delete(AquariumKind30 *fish)
{
    fish->base.vtable = data_ov004_02255d9c;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_02239f30, AquariumKind30_Delete)

/* func_ov004_02239f50 */
AquariumKind30 *AquariumKind30_Destruct(AquariumKind30 *fish)
{
    fish->base.vtable = data_ov004_02255d9c;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_02239f50, AquariumKind30_Destruct)

/* func_ov004_02239f68: wandering, its snap waiting. */
AquariumKind30 *AquariumKind30_Construct(AquariumKind30 *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255d9c);
    fish->own.state = AQUARIUM_KIND30_WANDER;
    fish->own.snap = AQUARIUM_SNAP_WAIT;
    fish->own.count = 0;
    return fish;
}
CLEAN_AS(func_ov004_02239f68, AquariumKind30_Construct)

/* ---- Kind 40: an AquariumSwimmer */

/* func_ov004_02239f9c */
AquariumKind40 *AquariumKind40_Delete(AquariumKind40 *fish)
{
    fish->base.vtable = data_ov004_02255dcc;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_02239f9c, AquariumKind40_Delete)

/* func_ov004_02239fbc */
AquariumKind40 *AquariumKind40_Destruct(AquariumKind40 *fish)
{
    fish->base.vtable = data_ov004_02255dcc;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_02239fbc, AquariumKind40_Destruct)

/* func_ov004_02239fd4: calm and untouched. */
AquariumKind40 *AquariumKind40_Construct(AquariumKind40 *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255dcc);
    fish->own.touched = 0;
    fish->own.phase = AQUARIUM_KIND40_CALM;
    fish->own.held = 0;
    return fish;
}
CLEAN_AS(func_ov004_02239fd4, AquariumKind40_Construct)

/* ---- Kind 10: an AquariumFish */

/* func_ov004_0223a008 */
AquariumKind10 *AquariumKind10_Delete(AquariumKind10 *fish)
{
    fish->base.vtable = data_ov004_02255e8c;
    AquariumFish_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a008, AquariumKind10_Delete)

/* func_ov004_0223a028 */
AquariumKind10 *AquariumKind10_Destruct(AquariumKind10 *fish)
{
    fish->base.vtable = data_ov004_02255e8c;
    AquariumFish_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_0223a028, AquariumKind10_Destruct)

/* func_ov004_0223a040: at its start. */
AquariumKind10 *AquariumKind10_Construct(AquariumKind10 *fish)
{
    AquariumFish_Construct(&fish->base);
    fish->base.vtable = data_ov004_02255e8c;
    fish->own.state = AQUARIUM_KIND10_START;
    return fish;
}
CLEAN_AS(func_ov004_0223a040, AquariumKind10_Construct)

/* ---- Kind 37: an AquariumSwimmer */

/* func_ov004_0223a064 */
AquariumKind37 *AquariumKind37_Delete(AquariumKind37 *fish)
{
    fish->base.vtable = data_ov004_02255de4;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a064, AquariumKind37_Delete)

/* func_ov004_0223a084 */
AquariumKind37 *AquariumKind37_Destruct(AquariumKind37 *fish)
{
    fish->base.vtable = data_ov004_02255de4;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_0223a084, AquariumKind37_Destruct)

/* func_ov004_0223a09c: coasting from the start of its climb at a speed of 0xa3, its pitch
 * rocking down. */
AquariumKind37 *AquariumKind37_Construct(AquariumKind37 *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255de4);
    fish->own.climb = AQUARIUM_CLIMB_COAST;
    fish->climber.own.climb_frames = 0;
    fish->base.speed = KIND37_SPEED;
    fish->own.pitch_up = 0;
    return fish;
}
CLEAN_AS(func_ov004_0223a09c, AquariumKind37_Construct)

/* ---- Kind 35: an AquariumSwimmer */

/* func_ov004_0223a0dc */
AquariumKind35 *AquariumKind35_Delete(AquariumKind35 *fish)
{
    fish->base.vtable = data_ov004_02255dfc;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a0dc, AquariumKind35_Delete)

/* func_ov004_0223a0fc */
AquariumKind35 *AquariumKind35_Destruct(AquariumKind35 *fish)
{
    fish->base.vtable = data_ov004_02255dfc;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_0223a0fc, AquariumKind35_Destruct)

/* func_ov004_0223a114: coasting from the start of its climb at a speed of 0x41, its pitch
 * rocking down. */
AquariumKind35 *AquariumKind35_Construct(AquariumKind35 *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255dfc);
    fish->own.climb = AQUARIUM_CLIMB_COAST;
    fish->climber.own.climb_frames = 0;
    fish->base.speed = KIND35_SPEED;
    fish->own.pitch_up = 0;
    return fish;
}
CLEAN_AS(func_ov004_0223a114, AquariumKind35_Construct)

/* ---- Kind 15: an AquariumFish */

/* func_ov004_0223a154 */
AquariumKind15 *AquariumKind15_Delete(AquariumKind15 *fish)
{
    fish->base.vtable = data_ov004_02255e44;
    AquariumFish_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a154, AquariumKind15_Delete)

/* func_ov004_0223a174 */
AquariumKind15 *AquariumKind15_Destruct(AquariumKind15 *fish)
{
    fish->base.vtable = data_ov004_02255e44;
    AquariumFish_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_0223a174, AquariumKind15_Destruct)

/* func_ov004_0223a18c: at its start. */
AquariumKind15 *AquariumKind15_Construct(AquariumKind15 *fish)
{
    AquariumFish_Construct(&fish->base);
    fish->base.vtable = data_ov004_02255e44;
    fish->own.state = AQUARIUM_KIND15_START;
    return fish;
}
CLEAN_AS(func_ov004_0223a18c, AquariumKind15_Construct)

/* ---- Kind 11: an AquariumFish */

/* func_ov004_0223a1b0 */
AquariumKind11 *AquariumKind11_Delete(AquariumKind11 *fish)
{
    fish->base.vtable = data_ov004_02255e74;
    AquariumFish_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a1b0, AquariumKind11_Delete)

/* func_ov004_0223a1d0 */
AquariumKind11 *AquariumKind11_Destruct(AquariumKind11 *fish)
{
    fish->base.vtable = data_ov004_02255e74;
    AquariumFish_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_0223a1d0, AquariumKind11_Destruct)

/* func_ov004_0223a1e8: its sound source (its base class's vtable, then its own) and at its
 * start. */
AquariumKind11 *AquariumKind11_Construct(AquariumKind11 *fish)
{
    AquariumFish_Construct(&fish->base);
    fish->base.vtable = data_ov004_02255e74;
    fish->own.sound.vtable = (const SoundSourceVtable *) (const void *) data_0213efe8;
    fish->own.sound.vtable = (const SoundSourceVtable *) (const void *) data_0213f020;
    fish->own.state = AQUARIUM_KIND11_START;
    return fish;
}
CLEAN_AS(func_ov004_0223a1e8, AquariumKind11_Construct)

/* ---- Kinds 52 to 54: an AquariumSwimmer */

/* func_ov004_0223a224 */
AquariumLaneFish *AquariumLaneFish_Delete(AquariumLaneFish *fish)
{
    fish->base.vtable = data_ov004_02255d6c;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a224, AquariumLaneFish_Delete)

/* func_ov004_0223a244 */
AquariumLaneFish *AquariumLaneFish_Destruct(AquariumLaneFish *fish)
{
    fish->base.vtable = data_ov004_02255d6c;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_0223a244, AquariumLaneFish_Destruct)

/* func_ov004_0223a25c */
AquariumLaneFish *AquariumLaneFish_Construct(AquariumLaneFish *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255d6c);
    fish->own.unk_255 = 0;
    fish->own.unk_256 = 0;
    return fish;
}
CLEAN_AS(func_ov004_0223a25c, AquariumLaneFish_Construct)

/* ---- Kinds 50 and 51: an AquariumSwimmer */

/* func_ov004_0223a288 */
AquariumFish *AquariumNonstopFish_Delete(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255d84;
    AquariumSwimmer_DestructBase(fish);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a288, AquariumNonstopFish_Delete)

/* func_ov004_0223a2a8 */
AquariumFish *AquariumNonstopFish_Destruct(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255d84;
    AquariumSwimmer_DestructBase(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a2a8, AquariumNonstopFish_Destruct)

/* func_ov004_0223a2c0 */
AquariumFish *AquariumNonstopFish_Construct(AquariumFish *fish)
{
    AquariumObjects_swimmer_base(fish, data_ov004_02255d84);
    ((AquariumSwimmerFields *) fish)->own.unk_238 = 0;
    return fish;
}
CLEAN_AS(func_ov004_0223a2c0, AquariumNonstopFish_Construct)

/* ---- Kind 36: an AquariumSwimmer */

/* func_ov004_0223a2e4 */
AquariumKind36 *AquariumKind36_Delete(AquariumKind36 *fish)
{
    fish->base.vtable = data_ov004_02255e14;
    AquariumSwimmer_DestructBase(&fish->base);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a2e4, AquariumKind36_Delete)

/* func_ov004_0223a304 */
AquariumKind36 *AquariumKind36_Destruct(AquariumKind36 *fish)
{
    fish->base.vtable = data_ov004_02255e14;
    AquariumSwimmer_DestructBase(&fish->base);
    return fish;
}
CLEAN_AS(func_ov004_0223a304, AquariumKind36_Destruct)

/* func_ov004_0223a31c: coasting from the start of its climb at a speed of 0x41, its scale
 * pulsing by 0x14 a frame down to 0.8, its pitch rocking down. */
AquariumKind36 *AquariumKind36_Construct(AquariumKind36 *fish)
{
    AquariumObjects_swimmer_base(&fish->base, data_ov004_02255e14);
    fish->own.climb = AQUARIUM_CLIMB_COAST;
    fish->climber.own.climb_frames = 0;
    fish->base.speed = KIND36_SPEED;
    fish->own.pulse_rate = KIND36_PULSE_RATE;
    fish->own.least_scale = KIND36_LEAST_SCALE;
    fish->own.pitch_up = 0;
    return fish;
}
CLEAN_AS(func_ov004_0223a31c, AquariumKind36_Construct)

/* ---- AquariumSwimmer */

/* func_ov004_0223a374: the destructor its derived classes run. */
AquariumFish *AquariumSwimmer_DestructBase(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255ea4;
    AquariumFish_DestructBase(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a374, AquariumSwimmer_DestructBase)

/* func_ov004_0223a38c */
AquariumFish *AquariumSwimmer_Delete(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255ea4;
    AquariumFish_DestructBase(fish);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a38c, AquariumSwimmer_Delete)

/* func_ov004_0223a3ac */
AquariumFish *AquariumSwimmer_Destruct(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255ea4;
    AquariumFish_DestructBase(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a3ac, AquariumSwimmer_Destruct)

/* A swimmer starts setting off on a new course, not bending nor turning from the glass. */
static AquariumFish *AquariumSwimmer_construct(AquariumFish *fish)
{
    AquariumFish_Construct(fish);
    fish->vtable = data_ov004_02255ea4;
    AquariumSwimmerFields *own = (AquariumSwimmerFields *) fish;
    fish->mode = AQUARIUM_MODE_NEW_COURSE;
    fish->unk_1fe = 2;
    fish->glass_step = SWIMMER_GLASS_STEP;
    fish->glass_turning = 0;
    own->own.unk_21c = 0;
    own->own.unk_220 = 0;
    fish->vertical = 0;
    fish->swim_224 = SWIMMER_SWIM_224;
    own->own.bending = 0;
    fish->level = SWIMMER_LEVEL;
    fish->swim_228 = SWIMMER_SWIM_228;
    fish->pad_1ef = 0;
    fish->focus_frames = 0;
    return fish;
}

/* func_ov004_0223a3c4: the constructor the aquarium runs. */
AquariumFish *AquariumSwimmer_Construct(AquariumFish *fish)
{
    return AquariumSwimmer_construct(fish);
}
CLEAN_AS(func_ov004_0223a3c4, AquariumSwimmer_Construct)

/* func_ov004_0223a458: the constructor its derived classes run, the same. */
AquariumFish *AquariumSwimmer_ConstructBase(AquariumFish *fish)
{
    return AquariumSwimmer_construct(fish);
}
CLEAN_AS(func_ov004_0223a458, AquariumSwimmer_ConstructBase)

/* ---- AquariumFish */

/* The destructor: the ends, the model's files, its pool entry, the model and the body. */
static void AquariumFish_destruct(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255db4;
    __cxa_vec_cleanup(fish->ends, 2, sizeof(Vec3), func_020012dc);
    ModelPoolFiles_Destruct(&fish->files);
    ModelPoolSlot_Destruct(&fish->pool_slot);
    AnimatedModel_DestructBlendedComplete(&fish->model);
    AquariumFishBody_Destruct(&fish->body);
}

/* func_ov004_0223a4ec: the destructor its derived classes run. */
AquariumFish *AquariumFish_DestructBase(AquariumFish *fish)
{
    AquariumFish_destruct(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a4ec, AquariumFish_DestructBase)

/* func_ov004_0223a53c */
AquariumFish *AquariumFish_Delete(AquariumFish *fish)
{
    AquariumFish_destruct(fish);
    Heap_OperatorDeleteB(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a53c, AquariumFish_Delete)

/* func_ov004_0223a594 */
AquariumFish *AquariumFish_Destruct(AquariumFish *fish)
{
    AquariumFish_destruct(fish);
    return fish;
}
CLEAN_AS(func_ov004_0223a594, AquariumFish_Destruct)

/* func_ov004_0223a5e4: the constructor: its body, model, pool entry, files and ends; of no
 * kind yet, off, its body solid, level, and with no animation files. */
AquariumFish *AquariumFish_Construct(AquariumFish *fish)
{
    fish->vtable = data_ov004_02255db4;
    AquariumFishBody_Construct(&fish->body);
    AnimatedModel_ConstructBlended(&fish->model);
    ModelPoolSlot_Construct(&fish->pool_slot);
    ModelPoolFiles_Construct(&fish->files);
    __cxa_vec_ctor(fish->ends, 2, sizeof(Vec3), func_020012e8, func_020012dc);
    fish->index = -1;
    fish->state = AQUARIUM_FISH_OFF;
    ModelPoolFiles_Reset(&fish->files);
    fish->unk_1c6 = 0;
    fish->solid = 1;
    fish->meetings = 0;
    fish->pitch = 0;
    for (int i = 0; i < AQUARIUM_FISH_ANIMS; i++) {
        fish->anims[i] = NULL;
    }
    return fish;
}
CLEAN_AS(func_ov004_0223a5e4, AquariumFish_Construct)

/* ---- The aquarium's profile */

/* func_ov004_0223a690 (the create of the aquarium's profile, data_ov004_02255d00): a new
 * aquarium (0x810 bytes from the auxiliary heap, cleared), constructed; nothing when there is
 * no room.
 * QUIRK: declared without a result, as its matching source is; the ROM's code leaves the new
 * aquarium (or NULL) in r0, the register a profile's create returns it in. */
void Aquarium_New(void)
{
    MuseumAquarium *self = Heap_AllocAuxZeroed(sizeof(MuseumAquarium));
    if (self != NULL) {
        Aquarium_Construct(self);
    }
}
CLEAN_AS(func_ov004_0223a690, Aquarium_New)
