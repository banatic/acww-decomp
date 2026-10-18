/* The museum's aquarium (museum_aquarium.h). */
#include "museum_aquarium.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/c_library.h"
#include "main/collision_query.h"
#include "main/model_object.h"
#include "main/museum_record.h"
#include "main/rom_file.h"
#include "main/scene_query.h"
#include "main/sound.h"
#include "main/sound_emitter.h"
#include "member_pointer.h"
#include "aquarium_objects.h"
#include "aquarium_swim.h"

static_assert(sizeof(AquariumRock) == 0x64, "rock");
static_assert(offsetof(MuseumAquarium, rocks) == 0x50, "rocks");
static_assert(offsetof(MuseumAquarium, glass) == 0x2a8, "glass");
static_assert(offsetof(MuseumAquarium, glass[1]) == 0x550, "second glass");
static_assert(offsetof(MuseumAquarium, pool) == 0x7f8, "pool");

/* The room shown, and the kinds of its fish: data_ov004_022593a4 up to (not including)
 * data_ov004_02255c30. */
extern u8 data_ov004_022593a0;
extern u8 data_ov004_022593a4;
extern u8 data_ov004_02255c30;
/* The rocks entered on the field. */
extern u8 data_ov004_02255c34;
/* The fish, by kind. */
extern AquariumFish *data_ov004_022594d4[AQUARIUM_FISH_KINDS];
/* Three fish whose classes keep a pointer to them: kind 11 (with a sound source at 0x1fc),
 * kind 36 (the scale it is drawn at at 0x258, its body's point at 0x26c) and kind 35 (its
 * body's point at 0x264). */
extern AquariumFish *data_ov004_022593ac;
extern AquariumFish *data_ov004_022593b4;
extern AquariumFish *data_ov004_022593b8;
/* The tanks' centres: the first (the sea room's only one) and the river room's second. */
extern Vec3 data_ov004_022593dc;
extern Vec3 data_ov004_022593c4;
/* What each kind is like. */
extern const AquariumFishInfo data_ov004_02247924[];
/* The member functions run for the fish's states, filled by the overlay's static
 * initialiser. */
extern const MemberPointer data_ov004_0225940c[3];
/* The formats of the fish's file names: the model below kind 10 and from it, the animations
 * likewise. */
extern const char data_ov004_02255f04[];
extern const char data_ov004_02255f20[];
extern const char data_ov004_02255f38[];
extern const char data_ov004_02255f54[];

extern MuseumRecord data_021f38f8;
extern Heap *data_021fbe94; /* the current heap */
extern Mtx43 data_021fbe48; /* the matrix being built */
extern const fx16 FX_SinCosTable_[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern u8 *func_02107b44(void *set, u32 index);

/* The model pool's heap hooks, handed to the pool: the game's. */
extern int func_0205c8c4(int size, int unused);
extern void func_0205c8a8(void);

#define ONE 0x1000

/* The process's sound, played while it lives. */
#define AQUARIUM_SOUND 0x4da

/* The bodies: the fish's and the rocks'. */
#define FISH_BODY_FLAGS 0x100
#define FISH_BODY_TOUCHES 0x140
#define FISH_BODY_TOUCHES_SEA 0x340
#define FISH_BODY_KIND 20
#define ROCK_FLAGS 0x102
#define EXTRA_ROCK_FLAGS 0x202
#define ROCK_TOUCHES 0x140
#define ROCK_INDEX 0xff

/* A body's index from this one on is a rock's (the fish's are their kinds). */
#define FIRST_ROCK_INDEX AQUARIUM_FISH_KINDS

/* The tanks: the boxes touched and the parts of them the fish keep to. */
#define RIVER_TANK_WIDTH 0x11c00
#define RIVER_TANK_DEPTH 0x5c00
#define SEA_TANK_WIDTH 0x26000
#define SEA_TANK_DEPTH 0x4dc3
#define TANK_HEIGHT 0x3800
#define GLASS_KIND 0x13

/* The kinds with something of their own. */
#define KIND_FISH_11 11
#define KIND_FISH_25 25
#define KIND_FISH_35 35
#define KIND_FISH_36 36
#define KIND_FISH_38 38
#define FIRST_SECOND_TANK_KIND 17

/* A joint animation's first frame and length as AnimatedModel_Start takes them. */
#define FISH_ANIM_FLAGS 0
#define FISH_ANIM_START 1
#define FISH_ANIM_FRAMES 0

/* How much of its push from the bodies touched a fish follows, and the most it follows in one
 * frame after touching a rock (in the river room). */
#define RIVER_PUSH_SHARE 0x99a
#define SEA_PUSH_SHARE 0x866
#define MOST_ROCK_PUSH 143

static TouchPick *Aquarium_pick(void)
{
    return (TouchPick *) (intptr_t) SceneQuery_FieldObject();
}

static Heap *Aquarium_entry_heap(ModelPoolEntry *entry)
{
    return (Heap *) (intptr_t) ModelPoolEntry_Heap(entry);
}

/* The fish's own virtual functions: slot 0 sets it up, slot 1 runs its frame. */
static void AquariumFish_call(AquariumFish *fish, int slot)
{
    ((void (*)(AquariumFish *))(uintptr_t) fish->vtable[slot])(fish);
}

static Vec3 *Aquarium_fish_field(AquariumFish *fish, u32 offset)
{
    return (Vec3 *) ((u8 *) fish + offset);
}

/* func_ov004_02234024: `coordinate` moved by the larger (in size) of the two ends' shifts,
 * the head's on a tie. */
void Aquarium_ApplyLargerShift(MuseumAquarium *self, fx32 *coordinate, fx32 head_before, fx32 head_after, fx32 tail_before,
                               fx32 tail_after)
{
    (void) self;
    s32 head = (s32) ((u32) head_after - (u32) head_before);
    s32 tail = (s32) ((u32) tail_after - (u32) tail_before);
    /* QUIRK: a shift of -2^31 counts as the smallest (its size wraps) */
    s32 head_size = head < 0 ? (s32) (0u - (u32) head) : head;
    s32 tail_size = tail < 0 ? (s32) (0u - (u32) tail) : tail;
    s32 shift = head_size >= tail_size ? head : tail;
    *coordinate = (fx32) ((u32) *coordinate + (u32) shift);
}
CLEAN_AS(func_ov004_02234024, Aquarium_ApplyLargerShift)

/* The body of a fish set for this frame. */
static void Aquarium_set_fish_body(AquariumFish *fish, const Vec3 *point, fx32 radius, fx32 height, int touches, int kind,
                                   fx32 weight)
{
    FieldPointBody_Set(&fish->body.base, point, radius, height, FISH_BODY_FLAGS, touches, FISH_BODY_KIND, (u8) kind, weight);
}

/* func_ov004_0223405c: a solid fish's body entered on the field (in the sea room kinds 35 and
 * 36 at points of their own, kind 38 touching fewer bodies), then its head and tail (its
 * length less its margin apart, before and behind its position) kept inside its tank; the
 * fish follows the larger of the two ends' shifts on each axis. In the sea room the fish
 * keeps to a part of the tank by its area and notes when an end was moved. Its previous
 * position becomes this one.
 * QUIRK: in the sea room, kind 35 or 36 without its pointer has its body entered as it was
 * last set. */
void Aquarium_KeepInTank(MuseumAquarium *self, AquariumFish **slot, int kind)
{
    AquariumFish *fish = *slot;
    const AquariumFishInfo *info = &data_ov004_02247924[kind];
    fx32 weight = (fx32) fish->size << 9;
    fx32 length = (fx32) info->body_radius << 5;
    if (!fish->solid) {
        return;
    }
    fx32 height = (fx32) info->body_height << 5;
    if (data_ov004_022593a0 == AQUARIUM_RIVER_ROOM) {
        Aquarium_set_fish_body(fish, &fish->position, length, height, FISH_BODY_TOUCHES, kind, weight);
    } else if (data_ov004_022593a0 == AQUARIUM_SEA_ROOM) {
        if (kind == KIND_FISH_36) {
            if (data_ov004_022593b4 != NULL) {
                Aquarium_set_fish_body(fish, Aquarium_fish_field(data_ov004_022593b4, 0x26c), length, height,
                                       FISH_BODY_TOUCHES_SEA, kind, weight);
            }
        } else if (kind == KIND_FISH_35) {
            if (data_ov004_022593b8 != NULL) {
                Aquarium_set_fish_body(fish, Aquarium_fish_field(data_ov004_022593b8, 0x264), length, height,
                                       FISH_BODY_TOUCHES_SEA, kind, weight);
            }
        } else if (kind == KIND_FISH_38) {
            Aquarium_set_fish_body(fish, &fish->position, length, height, FISH_BODY_TOUCHES, kind, weight);
        } else {
            Aquarium_set_fish_body(fish, &fish->position, length, height, FISH_BODY_TOUCHES_SEA, kind, weight);
        }
    }
    FieldBody_Enter(&fish->body.base.body);

    fx32 margin = (fx32) info->margin << 5;
    fx32 reach = length - (margin >> 1);
    fx32 before[2][2]; /* each end's x and z before it was kept inside */
    fx32 after[2][2];
    for (int end = 0; end < 2; end++) {
        Vec3 *point = &fish->ends[end];
        *point = fish->position;
        u16 angle = end == 0 ? (u16) fish->yaw : (u16) (fish->yaw + 0x8000);
        int at = (angle >> 4) * 2;
        point->x += FX_MulFunc(reach, FX_SinCosTable_[at]);
        point->z += FX_MulFunc(reach, FX_SinCosTable_[at + 1]);
        before[end][0] = point->x;
        before[end][1] = point->z;
        if (data_ov004_022593a0 == AQUARIUM_RIVER_ROOM) {
            const Vec3 *centre =
                kind < FIRST_SECOND_TANK_KIND || kind == KIND_FISH_25 ? &data_ov004_022593dc : &data_ov004_022593c4;
            CollisionQuery_ClampToRect(point, margin, centre, RIVER_TANK_WIDTH, RIVER_TANK_DEPTH);
        } else {
            static const fx32 widths[3] = {0x1a000, 0x26000, 0x2a000};
            if (fish->area < 3 &&
                CollisionQuery_ClampToRect(point, margin, &data_ov004_022593dc, widths[fish->area], SEA_TANK_DEPTH)) {
                fish->hit_glass = 1;
            }
        }
        after[end][0] = point->x;
        after[end][1] = point->z;
    }
    Aquarium_ApplyLargerShift(self, &fish->position.x, before[0][0], after[0][0], before[1][0], after[1][0]);
    Aquarium_ApplyLargerShift(self, &fish->position.z, before[0][1], after[0][1], before[1][1], after[1][1]);
    fish->previous = fish->position;
}
CLEAN_AS(func_ov004_0223405c, Aquarium_KeepInTank)

/* The fish of `kind` in the record. */
static int Aquarium_given(int kind)
{
    u16 item = (u32) kind < AQUARIUM_FISH_KINDS ? (u16) (0x12e8 + kind) : 0x12e8;
    return MuseumRecord_IsGiven(&data_021f38f8, &item);
}

/* A placed fish at its height, its previous position the same, its size from the table; then
 * shown. */
static void Aquarium_finish_place(MuseumAquarium *self, AquariumFish *fish, int kind)
{
    const AquariumFishInfo *info = &data_ov004_02247924[kind];
    fish->position.y = ((fx32) info->depth << 6) - ONE;
    fish->previous = fish->position;
    fish->size = info->size;
    Aquarium_ActivateFish(self, kind);
}

/* func_ov004_02234418: each of the sea room's fish the record has put in the tank: kinds 52-54
 * along its front, 35, 37 and 38 at their places, the others at random. */
void Aquarium_PlaceSeaFish(MuseumAquarium *self)
{
    for (int kind = data_ov004_022593a4; kind < (int) data_ov004_02255c30; kind++) {
        if (!Aquarium_given(kind)) {
            continue;
        }
        AquariumFish *fish = data_ov004_022594d4[kind];
        switch (kind) {
            case 52:
            case 53:
            case 54:
                fish->position.z = 0x12000;
                fish->position.x = AquariumSwim_RandomUnits(5, 30);
                break;
            case 38:
                fish->position.z = 0x14700;
                fish->position.x = 0x9e00;
                break;
            case 35:
                fish->position.z = 0x14a00;
                fish->position.x = 0x6000;
                break;
            case 37:
                fish->position.z = 0x14a00;
                fish->position.x = 0x7000;
                break;
            default:
                fish->position.z = AquariumSwim_RandomUnits(18, 22);
                fish->position.x = AquariumSwim_RandomUnits(5, 30);
                break;
        }
        Aquarium_finish_place(self, fish, kind);
    }
}
CLEAN_AS(func_ov004_02234418, Aquarium_PlaceSeaFish)

/* func_ov004_02234570: each of the river room's fish the record has put in its tank (the
 * second for kinds 17 on but 25): kinds 10 and 12 at their places, the others at random. */
void Aquarium_PlaceRiverFish(MuseumAquarium *self)
{
    for (int kind = data_ov004_022593a4; kind < (int) data_ov004_02255c30; kind++) {
        if (!Aquarium_given(kind)) {
            continue;
        }
        AquariumFish *fish = data_ov004_022594d4[kind];
        if (kind >= FIRST_SECOND_TANK_KIND && kind != KIND_FISH_25) {
            fish->position.x = AquariumSwim_RandomUnits(9, 26);
            fish->position.z = AquariumSwim_RandomUnits(5, 10);
        } else if (kind == 10) {
            fish->position.z = 0x14a00;
            fish->position.x = 0xc800;
        } else if (kind == 12) {
            fish->position.z = 0x13900;
            fish->position.x = 0x15900;
        } else {
            fish->position.x = AquariumSwim_RandomUnits(9, 26);
            fish->position.z = AquariumSwim_RandomUnits(19, 24);
        }
        Aquarium_finish_place(self, fish, kind);
    }
}
CLEAN_AS(func_ov004_02234570, Aquarium_PlaceRiverFish)

/* func_ov004_022346a0 (the process's release): every fish released and freed, the model pool
 * destroyed and the sound stopped. */
int Aquarium_Release(MuseumAquarium *self)
{
    for (int kind = data_ov004_022593a4; kind < (int) data_ov004_02255c30; kind++) {
        AquariumFish **slot = &data_ov004_022594d4[kind];
        if (*slot != NULL) {
            Aquarium_ReleaseFish(self, kind);
            Heap_Free(data_021fbe94, *slot);
            *slot = NULL;
        }
    }
    ModelPool_Destroy(&self->pool);
    SoundSys_StopSound(AQUARIUM_SOUND, 1);
    return 1;
}
CLEAN_AS(func_ov004_022346a0, Aquarium_Release)

/* func_ov004_0223470c (the process's draw): each fish shown, at scale 1 (kind 36 at its own
 * scale while its pointer is set); kind 11's matrix is set again first. */
int Aquarium_Draw(MuseumAquarium *self)
{
    for (int kind = data_ov004_022593a4; kind < data_ov004_02255c30; kind++) {
        AquariumFish **slot = &data_ov004_022594d4[kind];
        AquariumFish *fish = *slot;
        if (fish == NULL || fish->state != AQUARIUM_FISH_SHOWN) {
            continue;
        }
        Vec3 scale = {ONE, ONE, ONE};
        if (fish->index == KIND_FISH_11) {
            Aquarium_SetFishMatrix(self, slot);
        } else if (fish->index == KIND_FISH_36 && data_ov004_022593b4 != NULL) {
            scale = *Aquarium_fish_field(data_ov004_022593b4, 0x258);
        }
        AnimatedModel_Draw(&(*slot)->model, &scale);
    }
    return 1;
}
CLEAN_AS(func_ov004_0223470c, Aquarium_Draw)

/* func_ov004_022347b8: the fish's model matrix: at its position, turned by its yaw and
 * pitch. */
void Aquarium_SetFishMatrix(MuseumAquarium *self, AquariumFish **slot)
{
    (void) self;
    AquariumFish *fish = *slot;
    Mtx43_Translation(&data_021fbe48, fish->position.x, fish->position.y, fish->position.z);
    Mtx43_RotateY(&data_021fbe48, fish->yaw);
    Mtx43_RotateX(&data_021fbe48, fish->pitch);
    memcpy(fish->model.object.unk_64, &data_021fbe48, sizeof(Mtx43));
}
CLEAN_AS(func_ov004_022347b8, Aquarium_SetFishMatrix)

/* func_ov004_02234810: the fish's model loaded into its pool entry; once it is, the fish faces
 * a random way, is set up by its class, and its first joint animation starts on a loop; it is
 * shown, paying attention to nobody. Whether it is shown; a fish without animations is
 * released. */
int Aquarium_LoadFish(MuseumAquarium *self, AquariumFish **slot, int kind)
{
    AquariumFish *fish = *slot;
    int index = fish->index;
    ModelPoolEntry *entry = ModelPool_Take(&self->pool, &fish->pool_slot);
    ModelPoolFiles *files = &fish->files;
    char name[24];
    CLib_SPrintf(name, index < 10 ? data_ov004_02255f04 : data_ov004_02255f20, index / 10 + 10, index);
    if (!ModelPoolFiles_Load(files, entry, name)) {
        return 0;
    }
    fish->yaw = AquariumSwim_RandomAngle(0x168, 0);
    fish->target_yaw = fish->yaw;
    AquariumFish_call(fish, 0);
    AnimatedModel *model = &fish->model;
    ModelObject_SetModel(&model->object, (u8 *) (intptr_t) ModelPoolFiles_Model(files), NULL);
    Heap *heap = Aquarium_entry_heap(entry);
    if (fish->anims[0] == NULL) {
        Aquarium_ReleaseFish(self, kind);
        return 0;
    }
    u8 *track = func_02107b44(NNS_G3dGetJntAnmSet(fish->anims[0]), 0);
    if (!AnimatedModel_LoadAnim(model, heap)) {
        return 0;
    }
    AnimatedModel_Start(model, track, FISH_ANIM_FLAGS, ONE, FISH_ANIM_START, FISH_ANIM_FRAMES);
    AnimatedModel_Attach(model);
    ModelObject_AllocJointResults(&model->object, Aquarium_entry_heap(entry));
    fish->state = AQUARIUM_FISH_SHOWN;
    fish->focus = (u8) fish->index;
    Aquarium_SetFishMatrix(self, slot);
    return 1;
}
CLEAN_AS(func_ov004_02234810, Aquarium_LoadFish)

/* func_ov004_0223494c: the first `count` rocks entered on the field, and in the sea room the
 * extra body. */
void Aquarium_EnterRocks(MuseumAquarium *self, int count)
{
    for (int i = 0; i < count; i++) {
        AquariumRock *rock = &self->rocks[i];
        FieldPointBody_Set(&rock->body, &rock->point, rock->radius, rock->height, ROCK_FLAGS, ROCK_TOUCHES, 0, ROCK_INDEX,
                           ONE);
        FieldBody_Enter(&rock->body.body);
    }
    if (data_ov004_022593a0 == AQUARIUM_SEA_ROOM) {
        AquariumRock *rock = &self->rocks[AQUARIUM_EXTRA_ROCK];
        FieldPointBody_Set(&rock->body, &rock->point, rock->radius, rock->height, EXTRA_ROCK_FLAGS, ROCK_TOUCHES, 0,
                           ROCK_INDEX, ONE);
        FieldBody_Enter(&rock->body.body);
    }
}
CLEAN_AS(func_ov004_0223494c, Aquarium_EnterRocks)

/* func_ov004_02234a04 (the process's update): the tanks' glass offered to the stylus, each
 * fish's state run (from the last kind down), then the rocks entered. */
int Aquarium_Update(MuseumAquarium *self)
{
    u8 room = data_ov004_022593a0;
    if (room == AQUARIUM_RIVER_ROOM) {
        TouchPick_AddFaces(Aquarium_pick(), self->glass[0]);
        TouchPick_AddFaces(Aquarium_pick(), self->glass[1]);
    } else if (room == AQUARIUM_SEA_ROOM) {
        TouchPick_AddFaces(Aquarium_pick(), self->glass[0]);
    }
    for (int kind = data_ov004_02255c30 - 1; kind >= data_ov004_022593a4; kind--) {
        AquariumFish **slot = &data_ov004_022594d4[kind];
        if (*slot != NULL) {
            Aquarium_RunFishState(self, slot, kind);
        }
    }
    Aquarium_EnterRocks(self, data_ov004_02255c34);
    return 1;
}
CLEAN_AS(func_ov004_02234a04, Aquarium_Update)

/* A fish's push from the bodies it touched, as much of it as it follows. */
static fx32 Aquarium_push_share(fx32 push, fx32 share)
{
    return FX_MulFunc(push, share);
}

/* func_ov004_02234a98 (the state shown): the fish follows its share of the push from what it
 * touched (in the river room at most MOST_ROCK_PUSH each way after touching a rock), swims
 * (its class's slot 1), forgets this frame's meetings, is kept in its tank, and its matrix and
 * animation are updated. */
void Aquarium_SwimFish(MuseumAquarium *self, AquariumFish **slot, int kind)
{
    AquariumFish *fish = *slot;
    FieldBody *body = &fish->body.base.body;
    if (data_ov004_022593a0 == AQUARIUM_RIVER_ROOM) {
        fx32 x = Aquarium_push_share(body->push.x, RIVER_PUSH_SHARE);
        fx32 z = Aquarium_push_share(body->push.z, RIVER_PUSH_SHARE);
        if (body->touched) {
            if (body->touch_index >= FIRST_ROCK_INDEX) {
                if ((x < 0 ? -x : x) > MOST_ROCK_PUSH) {
                    x = x > 0 ? MOST_ROCK_PUSH : -MOST_ROCK_PUSH;
                }
                if ((z < 0 ? -z : z) > MOST_ROCK_PUSH) {
                    z = z > 0 ? MOST_ROCK_PUSH : -MOST_ROCK_PUSH;
                }
            }
            fish->position.x += x;
            fish->position.z += z;
        }
    } else if (data_ov004_022593a0 == AQUARIUM_SEA_ROOM) {
        fx32 x = Aquarium_push_share(body->push.x, SEA_PUSH_SHARE);
        fx32 z = Aquarium_push_share(body->push.z, SEA_PUSH_SHARE);
        if (body->touched) {
            fish->position.x += x;
            fish->position.z += z;
        }
    }
    AquariumFish_call(*slot, 1);
    AquariumFish_ClearMeetings(*slot);
    Aquarium_KeepInTank(self, slot, kind);
    Aquarium_SetFishMatrix(self, slot);
    AnimatedModel_Update(&(*slot)->model);
}
CLEAN_AS(func_ov004_02234a98, Aquarium_SwimFish)

/* func_ov004_02234b90 (the state loading). */
void Aquarium_FishStateLoad(MuseumAquarium *self, AquariumFish **slot, int kind)
{
    Aquarium_LoadFish(self, slot, kind);
}
CLEAN_AS(func_ov004_02234b90, Aquarium_FishStateLoad)

/* func_ov004_02234b98 (the state off): nothing to do. */
void Aquarium_FishStateOff(void) {}
CLEAN_AS(func_ov004_02234b98, Aquarium_FishStateOff)

/* func_ov004_02234b9c: the member function of the fish's state (its low byte), for states
 * 0-2. */
void Aquarium_RunFishState(MuseumAquarium *self, AquariumFish **slot, int kind)
{
    u8 state = (u8) (*slot)->state;
    if (state < 3) {
        const MemberPointer *member = &data_ov004_0225940c[state];
        void *object = MemberPointer_Object(member, self);
        ((void (*)(void *, AquariumFish **, int))(uintptr_t) MemberPointer_Code(member, object))(object, slot, kind);
    }
}
CLEAN_AS(func_ov004_02234b9c, Aquarium_RunFishState)

/* func_ov004_02234be0: the fish's `count` joint animations loaded from the current heap
 * ("/fish/<group>/m_fish<kind><n>.nsbca"); 0 at the first that fails. */
int Aquarium_LoadFishAnims(MuseumAquarium *self, AquariumFish **slot, int kind, int count)
{
    (void) self;
    int group = kind / 10 + 10;
    for (int i = 0; i < count; i++) {
        char name[28];
        CLib_SPrintf(name, kind < 10 ? data_ov004_02255f38 : data_ov004_02255f54, group, kind, i);
        (*slot)->anims[i] = RomFile_Load(name, data_021fbe94, 4, NULL);
        if ((*slot)->anims[i] == NULL) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02234be0, Aquarium_LoadFishAnims)

/* A fish of `size` bytes from `heap` put in the table at `kind` (NULL when there is no room). */
static void *Aquarium_alloc(Heap *heap, int kind, int size)
{
    data_ov004_022594d4[kind] = Heap_Alloc(heap, size);
    return data_ov004_022594d4[kind];
}

/* After a fish is made: those of three animations note it, and their animations are loaded.
 * 0 when the fish or its animations are missing (the fish is then released). */
static int Aquarium_finish_create(MuseumAquarium *self, int kind)
{
    AquariumFish **slot = &data_ov004_022594d4[kind];
    if (*slot == NULL) {
        return 0;
    }
    int anims = data_ov004_02247924[kind].anims;
    if (anims == 3) {
        (*slot)->unk_1c6 = 1;
    }
    if (!Aquarium_LoadFishAnims(self, slot, kind, anims)) {
        Aquarium_ReleaseFish(self, kind);
        (*slot)->unk_1c6 = 0;
        return 0;
    }
    return 1;
}

/* func_ov004_02234c64: the sea room's fish (kinds 35-55) made, each of its class, with their
 * animations, then placed; the tank's centre (17.0, 0, about 19.43). 0 when one fails. */
int Aquarium_CreateSeaFish(MuseumAquarium *self)
{
    data_ov004_022593a4 = AQUARIUM_RIVER_FISH;
    data_ov004_02255c30 = AQUARIUM_FISH_KINDS;
    data_ov004_022593dc.x = 0x11000;
    data_ov004_022593dc.y = 0;
    data_ov004_022593dc.z = 0x136e1;
    Heap *heap = data_021fbe94;
    for (int kind = AQUARIUM_RIVER_FISH; kind < data_ov004_02255c30; kind++) {
        void *fish;
        switch (kind) {
            case 36:
                if ((fish = Aquarium_alloc(heap, kind, 0x28c)) != NULL) {
                    AquariumKind36_Construct(fish);
                }
                break;
            case 50:
            case 51:
                if ((fish = Aquarium_alloc(heap, kind, 0x258)) != NULL) {
                    AquariumNonstopFish_Construct(fish);
                }
                break;
            case 52:
            case 53:
            case 54:
                if ((fish = Aquarium_alloc(heap, kind, 0x258)) != NULL) {
                    AquariumLaneFish_Construct(fish);
                }
                break;
            case 35:
                if ((fish = Aquarium_alloc(heap, kind, 0x278)) != NULL) {
                    AquariumKind35_Construct(fish);
                }
                break;
            case 37:
                if ((fish = Aquarium_alloc(heap, kind, 0x26c)) != NULL) {
                    AquariumKind37_Construct(fish);
                }
                break;
            case 40:
                if ((fish = Aquarium_alloc(heap, kind, 0x25c)) != NULL) {
                    AquariumKind40_Construct(fish);
                }
                break;
            case 38:
                if ((fish = Aquarium_alloc(heap, kind, 0x27c)) != NULL) {
                    AquariumHomeFish_Construct(fish);
                }
                break;
            case 47:
                if ((fish = Aquarium_alloc(heap, kind, 0x258)) != NULL) {
                    AquariumKind47_Construct(fish);
                }
                break;
            case 48:
                if ((fish = Aquarium_alloc(heap, kind, 0x1fc)) != NULL) {
                    AquariumKind48_Construct(fish);
                }
                break;
            default:
                if ((fish = Aquarium_alloc(heap, kind, 0x258)) != NULL) {
                    AquariumSwimmer_Construct(fish);
                }
                break;
        }
        if (!Aquarium_finish_create(self, kind)) {
            return 0;
        }
    }
    Aquarium_PlaceSeaFish(self);
    return 1;
}
CLEAN_AS(func_ov004_02234c64, Aquarium_CreateSeaFish)

/* func_ov004_02234eac: the river room's fish (kinds 0-34) made, each of its class, with their
 * animations, then placed; the first tank's centre (17.0, 0, 21.0). 0 when one fails. */
int Aquarium_CreateRiverFish(MuseumAquarium *self)
{
    data_ov004_022593a4 = 0;
    data_ov004_02255c30 = AQUARIUM_RIVER_FISH;
    data_ov004_022593dc.x = 0x11000;
    data_ov004_022593dc.y = 0;
    data_ov004_022593dc.z = 0x15000;
    Heap *heap = data_021fbe94;
    for (int kind = 0; kind < data_ov004_02255c30; kind++) {
        void *fish;
        switch (kind) {
            case 11:
                if ((fish = Aquarium_alloc(heap, kind, 0x214)) != NULL) {
                    AquariumKind11_Construct(fish);
                }
                break;
            case 15:
                if ((fish = Aquarium_alloc(heap, kind, 0x210)) != NULL) {
                    AquariumKind15_Construct(fish);
                }
                break;
            case 12:
                if ((fish = Aquarium_alloc(heap, kind, 0x27c)) != NULL) {
                    AquariumHomeFish_Construct(fish);
                }
                break;
            case 10:
                if ((fish = Aquarium_alloc(heap, kind, 0x220)) != NULL) {
                    AquariumKind10_Construct(fish);
                }
                break;
            case 30:
                if ((fish = Aquarium_alloc(heap, kind, 0x25c)) != NULL) {
                    AquariumKind30_Construct(fish);
                }
                break;
            case 5:
            case 6:
                if ((fish = Aquarium_alloc(heap, kind, 0x25c)) != NULL) {
                    AquariumRisingFish_Construct(fish);
                }
                break;
            default:
                if ((fish = Aquarium_alloc(heap, kind, 0x258)) != NULL) {
                    AquariumSwimmer_Construct(fish);
                }
                break;
        }
        if (!Aquarium_finish_create(self, kind)) {
            return 0;
        }
    }
    Aquarium_PlaceRiverFish(self);
    return 1;
}
CLEAN_AS(func_ov004_02234eac, Aquarium_CreateRiverFish)

static void Aquarium_set_rock(AquariumRock *rock, fx32 x, fx32 y, fx32 z, fx32 radius, fx32 height)
{
    rock->point.x = x;
    rock->point.y = y;
    rock->point.z = z;
    rock->radius = radius;
    rock->height = height;
}

/* func_ov004_0223507c (the process's init): the model pool for the fish (0x38 entries), the
 * room from the process's parameter, its rocks, its fish and its tanks' touch boxes; then the
 * aquarium's sound. */
int Aquarium_Init(MuseumAquarium *self)
{
    ModelPool_Create(&self->pool, 0x38, 0x800, 0x80, 0xc00, func_0205c8c4, func_0205c8a8, NULL);
    data_ov004_022593a0 = (u8) self->base.param;
    if (data_ov004_022593a0 == AQUARIUM_RIVER_ROOM) {
        Aquarium_set_rock(&self->rocks[0], 0xc000, 0x700, 0x5600, 0x1000, 0x800);
        Aquarium_set_rock(&self->rocks[1], 0x15200, 0x700, 0x6200, 0x1000, 0xd00);
        Aquarium_set_rock(&self->rocks[2], 0x9c00, 0x700, 0x14b00, 0xa00, 0xa00);
        Aquarium_set_rock(&self->rocks[3], 0x15900, 0x700, 0x13900, 0x1000, 0x800);
        Aquarium_set_rock(&self->rocks[4], 0x14c00, 0x700, 0x14a00, 0x700, 0x700);
        data_ov004_02255c34 = 5;
        Aquarium_CreateRiverFish(self);
        TouchPick_SetBoxAndAdd(Aquarium_pick(), self->glass[0], &data_ov004_022593dc, RIVER_TANK_WIDTH, RIVER_TANK_DEPTH,
                               TANK_HEIGHT, 0, GLASS_KIND, 0);
        TouchPick_SetBoxAndAdd(Aquarium_pick(), self->glass[1], &data_ov004_022593c4, RIVER_TANK_WIDTH, RIVER_TANK_DEPTH,
                               TANK_HEIGHT, 0, GLASS_KIND, 1);
    } else {
        Aquarium_set_rock(&self->rocks[0], 0x8b00, -0xd00, 0x13e00, 0x800, 0x1200);
        Aquarium_set_rock(&self->rocks[1], 0x9e00, -0xd00, 0x14700, 0x1100, 0x1500);
        Aquarium_set_rock(&self->rocks[2], 0x12f00, -0xd00, 0x13d00, 0xa00, 0xd00);
        Aquarium_set_rock(&self->rocks[3], 0x16e00, -0xd00, 0x13100, 0x1200, 0x1400);
        data_ov004_02255c34 = 4;
        Aquarium_set_rock(&self->rocks[AQUARIUM_EXTRA_ROCK], 0x9e00, -0xd00, 0x14700, 0xc00, 0x2000);
        Aquarium_CreateSeaFish(self);
        TouchPick_SetBoxAndAdd(Aquarium_pick(), self->glass[0], &data_ov004_022593dc, SEA_TANK_WIDTH, SEA_TANK_DEPTH,
                               TANK_HEIGHT, 0, GLASS_KIND, 0);
    }
    SoundSys_StartOnHandle38(AQUARIUM_SOUND);
    return 1;
}
CLEAN_AS(func_ov004_0223507c, Aquarium_Init)

/* func_ov004_02235374: the fish of `kind` (one of the room's) hidden and its resources
 * released: its animation files, its model and its pool entry; the pointers kept to kinds 11,
 * 35 and 36 cleared (kind 11's sound source released); its kind becomes -1. */
void Aquarium_ReleaseFish(MuseumAquarium *self, int kind)
{
    if (kind < data_ov004_022593a4 || kind >= data_ov004_02255c30) {
        return;
    }
    AquariumFish *fish = data_ov004_022594d4[kind];
    for (int i = 0; i < 4; i++) {
        if (fish->anims[i] != NULL) {
            Heap_FreeCurrent(fish->anims[i]);
            fish->anims[i] = NULL;
        }
    }
    fish->state = AQUARIUM_FISH_OFF;
    AnimatedModel_DetachJoints(&fish->model);
    ModelObject_Release(&fish->model.object);
    ModelPoolFiles_Release(&fish->files);
    ModelPool_Release(&self->pool, &fish->pool_slot);
    switch (fish->index) {
        case KIND_FISH_11:
            if (data_ov004_022593ac != NULL) {
                SoundSource_Release((SoundSource *) ((u8 *) data_ov004_022593ac + 0x1fc));
                data_ov004_022593ac = NULL;
            }
            break;
        case KIND_FISH_36:
            if (data_ov004_022593b4 != NULL) {
                data_ov004_022593b4 = NULL;
            }
            break;
        case KIND_FISH_35:
            if (data_ov004_022593b8 != NULL) {
                data_ov004_022593b8 = NULL;
            }
            break;
    }
    fish->index = -1;
}
CLEAN_AS(func_ov004_02235374, Aquarium_ReleaseFish)

/* func_ov004_0223546c: the fish of `kind` (one of the room's) to be loaded on the next frame,
 * its pool entry taken and its files reset; whether there is such a fish. */
int Aquarium_ActivateFish(MuseumAquarium *self, int kind)
{
    if (kind < (int) data_ov004_022593a4 || kind >= (int) data_ov004_02255c30) {
        return 0;
    }
    AquariumFish *fish = data_ov004_022594d4[kind];
    if (fish == NULL) {
        return 0;
    }
    fish->index = kind;
    fish->state = AQUARIUM_FISH_LOADING;
    ModelPool_Take(&self->pool, &fish->pool_slot);
    ModelPoolFiles_Reset(&fish->files);
    return 1;
}
CLEAN_AS(func_ov004_0223546c, Aquarium_ActivateFish)
