/* The museum's insect rooms (museum_insects.h). */
#include "museum_insects.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/c_library.h"
#include "main/calendar.h"
#include "main/collision_box.h"
#include "main/collision_query.h"
#include "main/frame_ctrl.h"
#include "main/globe.h"
#include "main/museum_record.h"
#include "main/rom_file.h"
#include "main/shadow.h"

static_assert(sizeof(InsectKindInfo) == 4, "kind info");
static_assert(offsetof(MuseumInsect, sound) == 0x24, "insect sound");
static_assert(offsetof(MuseumInsect, low) == 0x58, "insect bounds");
static_assert(offsetof(MuseumInsect, contacts) == 0x68, "insect contacts");
static_assert(offsetof(MuseumInsect, model) == 0xb0, "insect model");
static_assert(offsetof(MuseumInsect, mode) == 0x172, "insect mode");
static_assert(offsetof(MuseumInsect, unk_178) == 0x178, "insect 0x178");
static_assert(offsetof(MuseumInsect, kind) == 0x196, "insect kind");
static_assert(offsetof(MuseumInsect, body) == 0x19c, "insect body");
static_assert(offsetof(MuseumInsect, unk_1e8) == 0x1e8, "insect 0x1e8");
static_assert(offsetof(MuseumInsect, files) == 0x288, "insect files");
static_assert(offsetof(MuseumInsect, position) == 0x2c8, "insect position");
static_assert(sizeof(MuseumInsect) == 0x2d8, "insect");
static_assert(offsetof(InsectRoom, pool) == 0x180, "room pool");
static_assert(sizeof(InsectRoom) == 0x1a0, "room");

/* The insects' entries, and the entries of kinds 55 and 56 once found (-1 before). */
extern MuseumInsect data_ov004_02259a34[MUSEUM_INSECT_ENTRIES];
extern s8 data_ov004_0225628c;
extern s8 data_ov004_02256290;
/* The frames the rooms have run. */
extern u8 data_ov004_02259a24;
/* What each kind is like (kind 37's entry is changed by InsectRoom_LoadInsect), and its
 * functions. */
extern InsectKindInfo data_ov004_02256308[MUSEUM_INSECT_KINDS];
extern const InsectKindCode data_ov004_022563ec[MUSEUM_INSECT_KINDS];
/* The scale kind 48 is drawn at. */
extern const Vec3 data_ov004_0225629c;
/* The file names: kind 37 asleep, kind 24, kind 35, kind 56, the kinds by tens, the model,
 * the visibility and joint animations, and kind 24's texture animation. */
extern const char data_ov004_022565b4[];
extern const char data_ov004_022565c8[];
extern const char data_ov004_022565dc[];
extern const char data_ov004_022565f0[];
extern const char data_ov004_02256604[];
extern const char data_ov004_02256618[];
extern const char data_ov004_0225662c[];
extern const char data_ov004_02256640[];
extern const char data_ov004_02256654[];
extern const char data_ov004_02256668[];
extern const char data_ov004_0225667c[];
extern const char data_ov004_02256688[];
extern const char data_ov004_02256694[];
extern const char data_ov004_022566a0[];

/* The vtables: the insects' base animation, the room and the process base. */
extern const u32 data_ov004_022562b0[];
extern const u32 data_ov004_022562c0[];
extern const u32 data_020da13c[];
/* A sound source's class, set over its base's. */
extern const u32 data_0213efe8[];
extern const u32 data_0213f020[];

extern MuseumRecord data_021f38f8;
extern Heap *data_021fbe94; /* the current heap */
extern Mtx43 data_021fbe48; /* the matrix being built */

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void *NNS_G3dGetVisAnmSet(void *file);
extern void *NNS_G3dGetJntAnmSet(void *file);
extern void *NNS_G3dGetTexSRTAnmSet(void *file);
extern u8 *func_02107cf0(void *set, u32 index);
extern u8 *func_02107b44(void *set, u32 index);
extern u8 *func_02107bbc(void *set, u32 index);
extern int NNS_G3dMdlGetMdlAlpha(int model, u32 material);
/* Clears `size` bytes at `dst`. */
extern void *func_02137550(void *dst, u32 size);
/* The kind's sound (0 for none) for a variant. */
extern int func_ov004_02244ae4(int kind, int variant);

/* The members' constructors and destructors handed to __cxa_vec_ctor and __cxa_vec_cleanup:
 * the game's (FieldPointBody_Construct, FieldPointBody_Destruct2, TrivialObject_Construct and
 * TrivialObject_Destruct in Clean). */
extern FieldPointBody *func_02089b50(FieldPointBody *body);
extern FieldPointBody *func_02089b38(FieldPointBody *body);
extern void func_020012e8(void *object);
extern void func_020012dc(void *object);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The model pool's heap hooks, handed to the pool: the game's (SceneHeaps_CreateOv004PoolB and
 * SceneHeaps_DestroyOv004PoolB in Clean). */
extern int func_0205c994(int size, int parent);
extern void func_0205c978(void);

#define ONE 0x1000
#define MUSEUM_INSECT_FIRST_ITEM 0x12b0

/* The kinds with something of their own. */
#define KIND_9 9
#define KIND_23 23
#define KIND_24 24 /* plays a texture animation too */
#define KIND_37 37 /* has another model while asleep */
#define KIND_48 48 /* drawn at twice its size */
#define KIND_53 53
#define KIND_24_FILE 60 /* the number in kind 24's file names */

/* The bodies' flags. */
#define INSECT_BODY_FLAGS 0x80
#define INSECT_BODY_FLAGS_HIGH 0x82
#define INSECT_BODY_FLAGS_PARTNER 0x42
#define INSECT_BODY_TOUCHES 0xc0
#define INSECT_PARTNER_HEIGHT 0x1200
#define INSECT_TOUCHED_KEEP 0x40
#define INSECT_TOUCHED_MARK 0x80
#define INSECT_MOVE_FLAGS 11
#define ROOM_BODY_FLAGS 0x42
#define ROOM_BODY_TOUCHES 0x80
#define ROOM_BODY_INDEX 0xff

#define SHADOW_FADE_HEIGHT 0x9000

/* The model pool. */
#define INSECT_POOL_TEXTURES 0x400
#define INSECT_POOL_PALETTES 0x40
#define INSECT_POOL_HEAP 0x9c4

static AnimatedModel *insect_model(MuseumInsect *insect)
{
    return (AnimatedModel *) (void *) &insect->model;
}

/* A kind's entry of data_ov004_02256308, read the way the ROM's code does for any kind (an
 * entry without an insect, kind -1, reads the bytes before the table). */
static InsectKindInfo *kind_info(int kind)
{
    return (InsectKindInfo *) ((uintptr_t) data_ov004_02256308 + (uintptr_t) (kind * 4));
}

/* func_ov004_0223ea78: the band of the day the hour now is in, as a bit: 4-7 0x02, 8-15 0x04,
 * 16 0x08, 17-18 0x10, 19-22 0x20, else (23-3) 0x01. */
int InsectRoom_HourBand(void)
{
    Time now;
    Calendar_Now(&now);
    u8 hour = now.hour;
    if (hour >= 4 && hour <= 7) {
        return 0x02;
    }
    if (hour >= 8 && hour <= 15) {
        return 0x04;
    }
    if (hour == 16) {
        return 0x08;
    }
    if (hour == 17 || hour == 18) {
        return 0x10;
    }
    if (hour >= 19 && hour <= 22) {
        return 0x20;
    }
    return 0x01;
}
CLEAN_AS(func_ov004_0223ea78, InsectRoom_HourBand)

/* func_ov004_0223eacc (the base animation's deleting destructor) */
ModelAnim *InsectAnim_Delete(ModelAnim *self)
{
    self->ctrl.vtable = data_ov004_022562b0;
    ModelAnim_Destruct(self);
    Heap_OperatorDeleteB(self);
    return self;
}
CLEAN_AS(func_ov004_0223eacc, InsectAnim_Delete)

/* func_ov004_0223eaec (the base animation's destructor) */
ModelAnim *InsectAnim_Destruct(ModelAnim *self)
{
    self->ctrl.vtable = data_ov004_022562b0;
    ModelAnim_Destruct(self);
    return self;
}
CLEAN_AS(func_ov004_0223eaec, InsectAnim_Destruct)

/* func_ov004_0223eb04 (the base animation's constructor) */
ModelAnim *InsectAnim_Construct(ModelAnim *self)
{
    ModelAnim_ConstructBase(self);
    self->ctrl.vtable = data_ov004_022562b0;
    return self;
}
CLEAN_AS(func_ov004_0223eb04, InsectAnim_Construct)

/* The room's members taken down. */
static void InsectRoom_destruct_members(InsectRoom *self)
{
    self->base.vtable = data_ov004_022562c0;
    ModelPool_Destruct(&self->pool);
    __cxa_vec_cleanup(self->bodies, INSECT_ROOM_BODIES, sizeof(FieldPointBody), (void (*)(void *))(uintptr_t) func_02089b38);
    self->base.vtable = data_020da13c;
    Process_Destruct(&self->base);
}

/* func_ov004_0223eb1c (the room's deleting destructor) */
InsectRoom *InsectRoom_Delete(InsectRoom *self)
{
    InsectRoom_destruct_members(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0223eb1c, InsectRoom_Delete)

/* func_ov004_0223eb64 (the room's destructor) */
InsectRoom *InsectRoom_Destruct(InsectRoom *self)
{
    InsectRoom_destruct_members(self);
    return self;
}
CLEAN_AS(func_ov004_0223eb64, InsectRoom_Destruct)

/* func_ov004_0223eba4 (the room's constructor): the base's vtable set before the class's. */
InsectRoom *InsectRoom_Construct(InsectRoom *self)
{
    Process_Construct(&self->base);
    self->base.vtable = data_020da13c;
    self->base.vtable = data_ov004_022562c0;
    __cxa_vec_ctor(self->bodies, INSECT_ROOM_BODIES, sizeof(FieldPointBody), (void (*)(void *))(uintptr_t) func_02089b50,
                   (void (*)(void *))(uintptr_t) func_02089b38);
    ModelPool_Init(&self->pool);
    return self;
}
CLEAN_AS(func_ov004_0223eba4, InsectRoom_Construct)

/* func_ov004_0223ebf0: entry `index` (0-31; nothing for others) emptied: the animation file
 * the room keeps for kind 35 or 56 freed, the model's animation detached, the base animation
 * forgotten, its sound released, the entry off and at rest with no kind, its model files
 * released and its pool entry given back.
 * QUIRK: an entry without an insect (kind -1) reads the byte before the kinds' table to choose
 * the animation to detach. */
void InsectRoom_ReleaseInsect(InsectRoom *self, int index)
{
    if (index < 0 || index >= MUSEUM_INSECT_ENTRIES) {
        return;
    }
    MuseumInsect *insect = &data_ov004_02259a34[index];
    int kind = insect->kind;
    if (kind == MUSEUM_INSECT_PARTNER) {
        Heap_FreeCurrent(self->partner_anim);
        self->partner_anim = NULL;
    } else if (kind == MUSEUM_INSECT_WITH_PARTNER) {
        Heap_FreeCurrent(self->with_partner_anim);
        self->with_partner_anim = NULL;
    }
    if (kind_info(kind)->visibility_anim) {
        AnimatedModel_DetachVisibility(insect_model(insect));
    } else {
        AnimatedModel_DetachJoints(insect_model(insect));
    }
    insect->anim.anim = NULL;
    insect->anim.model = NULL;
    SoundSource_Release(&insect->sound);
    insect->kind = -1;
    insect->yaw = 0;
    insect->state = MUSEUM_INSECT_OFF;
    insect->unk_168 = 0;
    insect->mode = MUSEUM_INSECT_MODE_REST;
    ModelPoolFiles_Release(&insect->files);
    ModelPool_Release(&self->pool, &insect->pool_slot);
    insect->frame = NULL;
}
CLEAN_AS(func_ov004_0223ebf0, InsectRoom_ReleaseInsect)

/* func_ov004_0223ecc8 (an insect's destructor): the members in reverse order, then the base. */
MuseumInsect *MuseumInsect_Destruct(MuseumInsect *self)
{
    ModelPoolFiles_Destruct(&self->files);
    ModelPoolSlot_Destruct(&self->pool_slot);
    ModelObject_DestructComplete(&self->unk_1e8);
    FieldPointBody_Destruct2(&self->body);
    __cxa_vec_cleanup(self->unk_178, 2, sizeof(Vec3), func_020012dc);
    AnimatedModel_DestructComplete(insect_model(self));
    CollisionContacts_Destroy(&self->contacts);
    InsectAnim_Destruct(&self->anim);
    return self;
}
CLEAN_AS(func_ov004_0223ecc8, MuseumInsect_Destruct)

/* func_ov004_0223ed30 (an insect's constructor): off, with no kind and no frame function. */
MuseumInsect *MuseumInsect_Construct(MuseumInsect *self)
{
    InsectAnim_Construct(&self->anim);
    self->sound.vtable = (const SoundSourceVtable *) data_0213efe8;
    self->sound.vtable = (const SoundSourceVtable *) data_0213f020;
    CollisionContacts_Construct(&self->contacts);
    AnimatedModel_Construct(insect_model(self));
    __cxa_vec_ctor(self->unk_178, 2, sizeof(Vec3), func_020012e8, func_020012dc);
    FieldPointBody_Construct(&self->body);
    ModelObject_Construct(&self->unk_1e8);
    ModelPoolSlot_Construct(&self->pool_slot);
    ModelPoolFiles_Construct(&self->files);
    self->kind = -1;
    ModelPoolFiles_Reset(&self->files);
    self->frame = NULL;
    self->state = MUSEUM_INSECT_OFF;
    return self;
}
CLEAN_AS(func_ov004_0223ed30, MuseumInsect_Construct)

/* The entry of `kind` that is not off, its index noted in `found`; once noted, that entry.
 * QUIRK: the noted entry is not looked at again. */
static MuseumInsect *InsectRoom_find(s8 *found, int kind)
{
    if (*found >= 0) {
        return &data_ov004_02259a34[*found];
    }
    for (u8 i = 0; i < MUSEUM_INSECT_ENTRIES; i++) {
        MuseumInsect *insect = &data_ov004_02259a34[i];
        if (insect->kind == kind && insect->state != MUSEUM_INSECT_OFF) {
            *found = (s8) i;
            return insect;
        }
    }
    return NULL;
}

/* func_ov004_0223edd8: kind 56's entry (InsectRoom_find), or NULL. */
MuseumInsect *InsectRoom_FindPartner(void)
{
    return InsectRoom_find(&data_ov004_02256290, MUSEUM_INSECT_PARTNER);
}
CLEAN_AS(func_ov004_0223edd8, InsectRoom_FindPartner)

/* func_ov004_0223ee38: kind 55's entry (InsectRoom_find), or NULL. */
MuseumInsect *InsectRoom_FindPairSecond(void)
{
    return InsectRoom_find(&data_ov004_0225628c, MUSEUM_INSECT_PAIR_SECOND);
}
CLEAN_AS(func_ov004_0223ee38, InsectRoom_FindPairSecond)

/* func_ov004_0223ee98: the room a kind is shown in: 0 for kinds 0-8, 10, 14, 15, 25, 26, 30,
 * 32, 36, 37, 45-48 and 50-52, 1 for the others. */
int InsectRoom_RoomOf(InsectRoom *self, unsigned int kind)
{
    (void) self;
    switch (kind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 14:
        case 15:
        case 25:
        case 26:
        case 30:
        case 32:
        case 36:
        case 37:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
        case 51:
        case 52:
            return 0;
        default:
            return 1;
    }
}
CLEAN_AS(func_ov004_0223ee98, InsectRoom_RoomOf)

/* func_ov004_0223ef1c: each kind of the room shown that the record has been given added, and
 * kind 56 after kind 35 was. */
void InsectRoom_AddGivenInsects(InsectRoom *self)
{
    u8 room = (u8) self->base.param;
    int partner = 0;
    for (u8 kind = 0; kind < MUSEUM_INSECT_KINDS; kind++) {
        if ((u8) InsectRoom_RoomOf(self, kind) != room) {
            continue;
        }
        u16 item = kind < MUSEUM_INSECT_GIVEN_KINDS ? (u16) (MUSEUM_INSECT_FIRST_ITEM + kind) : MUSEUM_INSECT_FIRST_ITEM;
        if (kind == MUSEUM_INSECT_PARTNER) {
            if (partner) {
                InsectRoom_AddInsect(self, kind);
            }
        } else if (MuseumRecord_IsGiven(&data_021f38f8, &item)) {
            InsectRoom_AddInsect(self, kind);
            if (kind == MUSEUM_INSECT_WITH_PARTNER) {
                partner = 1;
            }
        }
    }
}
CLEAN_AS(func_ov004_0223ef1c, InsectRoom_AddGivenInsects)

/* func_ov004_0223ef98 (vtable slot 3, the deletion): every entry emptied and the model pool
 * destroyed. */
int InsectRoom_Release(InsectRoom *self)
{
    for (int i = 0; i < MUSEUM_INSECT_ENTRIES; i++) {
        InsectRoom_ReleaseInsect(self, i);
    }
    ModelPool_Destroy(&self->pool);
    return 1;
}
CLEAN_AS(func_ov004_0223ef98, InsectRoom_Release)

/* func_ov004_0223efc4: whether an insect casts a shadow: not those of kinds 9, 16-20, 24, 25,
 * 31, 33-36, 38-48, 50, 51 and 56, and kind 30 only out of its rest. */
int InsectRoom_CastsShadow(InsectRoom *self, MuseumInsect *insect)
{
    (void) self;
    switch (insect->kind) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 24:
        case 25:
        case 31:
        case 33:
        case 34:
        case 35:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 50:
        case 51:
        case 56:
            return 0;
        case 30:
            return insect->mode != MUSEUM_INSECT_MODE_REST;
        default:
            return 1;
    }
}
CLEAN_AS(func_ov004_0223efc4, InsectRoom_CastsShadow)

/* func_ov004_0223f05c (vtable slot 9, the drawing): each shown insect's model (kind 48's at
 * its scale), and its shadow at its kind's size, as opaque as its model. */
int InsectRoom_Draw(InsectRoom *self)
{
    for (u8 i = 0; i < MUSEUM_INSECT_ENTRIES; i++) {
        MuseumInsect *insect = &data_ov004_02259a34[i];
        if (insect->state != MUSEUM_INSECT_SHOWN) {
            continue;
        }
        int kind = insect->kind;
        if (kind == KIND_48) {
            Vec3 scale = data_ov004_0225629c;
            AnimatedModel_Draw(insect_model(insect), &scale);
        } else {
            AnimatedModel_Draw(insect_model(insect), NULL);
        }
        if (InsectRoom_CastsShadow(self, insect)) {
            int alpha = NNS_G3dMdlGetMdlAlpha(ModelPoolFiles_Model(&insect->files), 0);
            CharaShadow_DrawLevel(&insect->position, kind_info(kind)->size, SHADOW_FADE_HEIGHT, (u8) alpha);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0223f05c, InsectRoom_Draw)

/* A fixed body of a room: where it stands, its radius and height. */
typedef struct InsectRoomBody {
    Vec3 point;
    fx32 radius;
    fx32 height;
} InsectRoomBody;

/* func_ov004_0223f110: the room's fixed bodies set and entered on the field: four in room 1,
 * two in the other. */
void InsectRoom_EnterBodies(InsectRoom *self)
{
    static const InsectRoomBody room1[4] = {
        {{0x13000, 0x800, 0xe300}, 0x1000, 0x1000},
        {{0x19400, 0x800, 0xf300}, 0x1000, 0x1000},
        {{0x10800, 0x600, 0xc600}, 0x600, 0xc00},
        {{0x10800, 0x600, 0x15700}, 0x600, 0xc00},
    };
    static const InsectRoomBody room0[2] = {
        {{0x7900, 0x800, 0xe100}, 0x800, 0x3c00},
        {{0xaa00, 0x800, 0xcd00}, 0x800, 0x3c00},
    };
    const InsectRoomBody *bodies = self->base.param == 1 ? room1 : room0;
    u8 count = self->base.param == 1 ? 4 : 2;
    for (u8 i = 0; i < count; i++) {
        Vec3 point = bodies[i].point;
        FieldPointBody_Set(&self->bodies[i], &point, bodies[i].radius, bodies[i].height, ROOM_BODY_FLAGS, ROOM_BODY_TOUCHES, 0,
                           ROOM_BODY_INDEX, ONE);
        FieldBody_Enter(&self->bodies[i].body);
    }
}
CLEAN_AS(func_ov004_0223f110, InsectRoom_EnterBodies)

/* A box of the collision map standing for a case of the room: the middle of its bottom, and
 * whether it is turned (wide along X rather than along Z). */
typedef struct InsectRoomCase {
    fx32 x;
    fx32 z;
    u8 wide;
} InsectRoomCase;

#define INSECT_CASE_LONG 0x4000
#define INSECT_CASE_SHORT 0x1000
#define INSECT_CASE_HEIGHT 0x6000

/* func_ov004_0223f218 (vtable slot 6, the frame): the room's cases added to the collision map
 * (three in room 0, two in the other), the frame counted, the fixed bodies entered, each entry
 * loading loaded and each shown insect run, and the cases removed again.
 * BUG: the cases' height above the floor (their position's y) is never set; the ROM's code
 * hands the stack's leftover. Here it is 0. */
int InsectRoom_Update(InsectRoom *self)
{
    static const InsectRoomCase room0[3] = {
        {0x3800, 0x8000, 0},
        {0x3800, 0x1a000, 0},
        {0x16000, 0x1c800, 1},
    };
    static const InsectRoomCase room1[2] = {
        {0x1c800, 0x8000, 0},
        {0x1c800, 0x1a000, 0},
    };
    CollisionBox boxes[3];
    u8 added[3];
    CollisionBox_Construct(&boxes[0]);
    CollisionBox_Construct(&boxes[1]);
    CollisionBox_Construct(&boxes[2]);
    const InsectRoomCase *cases = self->base.param == 0 ? room0 : room1;
    u8 count = self->base.param == 0 ? 3 : 2;
    for (u8 i = 0; i < count; i++) {
        Vec3 centre = {cases[i].x, 0, cases[i].z};
        fx32 width = cases[i].wide ? INSECT_CASE_LONG : INSECT_CASE_SHORT;
        fx32 depth = cases[i].wide ? INSECT_CASE_SHORT : INSECT_CASE_LONG;
        added[i] = (u8) CollisionBox_Add(&boxes[i], width, depth, INSECT_CASE_HEIGHT, &centre, 0, NULL);
    }
    data_ov004_02259a24++;
    InsectRoom_EnterBodies(self);
    for (u8 i = 0; i < MUSEUM_INSECT_ENTRIES; i++) {
        MuseumInsect *insect = &data_ov004_02259a34[i];
        switch (insect->state) {
            case MUSEUM_INSECT_LOADING:
                InsectRoom_LoadInsect(self, insect);
                break;
            case MUSEUM_INSECT_SHOWN:
                InsectRoom_UpdateInsect(self, insect);
                break;
        }
    }
    for (u8 i = 0; i < count; i++) {
        if (added[i]) {
            CollisionBox_Remove(&boxes[i]);
        }
    }
    CollisionBox_Destruct(&boxes[2]);
    CollisionBox_Destruct(&boxes[1]);
    CollisionBox_Destruct(&boxes[0]);
    return 1;
}
CLEAN_AS(func_ov004_0223f218, InsectRoom_Update)

/* func_ov004_0223f398: whether an insect of `kind` in `mode` has a body on the field: not those
 * of kinds 9, 11, 16-20, 25, 31, 33-36, 38-47, 49 and 53, and kind 30 only in modes 3 and 4. */
int InsectRoom_IsSolid(InsectRoom *self, int kind, int mode)
{
    (void) self;
    switch (kind) {
        case 9:
        case 11:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 25:
        case 31:
        case 33:
        case 34:
        case 35:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 49:
        case 53:
            return 0;
        case 30:
            return mode == 4 || mode == 3;
        default:
            return 1;
    }
}
CLEAN_AS(func_ov004_0223f398, InsectRoom_IsSolid)

/* The flags of a solid insect's body: higher for kinds 14, 15, 26 and 32, and for kinds 0-7,
 * 10, 37 and 51 out of mode 0. */
static int InsectRoom_body_flags(const MuseumInsect *insect, int kind)
{
    switch (kind) {
        case 14:
        case 15:
        case 26:
        case 32:
            return INSECT_BODY_FLAGS_HIGH;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 10:
        case 37:
        case 51:
            return insect->mode != 0 ? INSECT_BODY_FLAGS_HIGH : INSECT_BODY_FLAGS;
        default:
            return INSECT_BODY_FLAGS;
    }
}

/* func_ov004_0223f41c: a shown insect's frame, once it has a frame function. Pushed by the
 * bodies it touched (kept within its bounds, back where it was on each axis it would leave
 * them; touching one of flags 0x40 keeps its position, and marks kind 23; one of flags 0x80
 * marks it), it runs its kind's frame function. A solid one moves on the collision map from
 * where it was and has its body set where it was before that move (kind 56's at its first
 * joint, taken back from the drawn world); its joint animation steps (kind 24's texture
 * animation too), its kind's sound follows it, and its model's matrix is built from its
 * position as drawn and its angles (the sinking of the ground far away added to its pitch).
 * REQUIRES: its kind is one of the 57. */
void InsectRoom_UpdateInsect(InsectRoom *self, MuseumInsect *insect)
{
    if (insect->frame == NULL) {
        return;
    }
    FieldPointBody *body = &insect->body;
    Vec3 *position = &insect->position;
    int kind = (u8) insect->kind;
    Vec3 previous = *position;
    if (body->body.touched) {
        position->x += body->body.push.x;
        position->z += body->body.push.z;
        InsectRoom_KeepInBounds(self, insect, &previous);
        if (FieldBody_TouchedWith(&body->body, INSECT_TOUCHED_KEEP)) {
            insect->kept = *position;
            if (kind == KIND_23) {
                insect->unk_20 = 1;
            }
        } else if (FieldBody_TouchedWith(&body->body, INSECT_TOUCHED_MARK)) {
            insect->unk_20 = 1;
        }
    }
    insect->frame(insect);
    if (InsectRoom_IsSolid(self, kind, (u8) insect->mode)) {
        Vec3 origin = *position;
        int flags;
        fx32 height;
        if (kind == MUSEUM_INSECT_PARTNER) {
            Mtx43 joint;
            if (ModelObject_JointMatrix(&insect->model.object, &joint, 0)) {
                Vec3 drawn = {joint.m[3][0], joint.m[3][1], joint.m[3][2]};
                Globe_Unbend(&origin, &drawn);
            }
            flags = INSECT_BODY_FLAGS_PARTNER;
            height = INSECT_PARTNER_HEIGHT;
        } else {
            flags = InsectRoom_body_flags(insect, kind);
            height = kind_info(kind)->size;
        }
        CollisionQuery_Move(&insect->contacts, position, &previous, insect->yaw, kind_info(kind)->size, NULL,
                            INSECT_MOVE_FLAGS);
        FieldPointBody_Set(body, &origin, kind_info(kind)->size, height, flags, INSECT_BODY_TOUCHES, 0, 0xff, ONE);
        FieldBody_Enter(&body->body);
    }
    if (kind_info(kind)->visibility_anim == 0) {
        AnimatedModel_StepFrames(insect_model(insect));
        if (kind == KIND_24) {
            FrameCtrl_Step(&insect->anim.ctrl);
            insect->anim.anim->frame = insect->anim.ctrl.frame;
        }
    }
    if (func_ov004_02244ae4((s8) kind, 0) > 0) {
        Vec3 at = *position;
        SoundSource_UpdateAt(&insect->sound, &at);
    }
    Vec3 drawn;
    int sinking = Globe_BendFar(&drawn, &insect->position);
    Mtx43_Translation(&data_021fbe48, drawn.x, drawn.y, drawn.z);
    Mtx43_RotateX(&data_021fbe48, (s16) (sinking + insect->pitch));
    Mtx43_RotateY(&data_021fbe48, insect->yaw);
    Mtx43_RotateZ(&data_021fbe48, insect->roll);
    memcpy(insect->model.object.unk_64, &data_021fbe48, sizeof(Mtx43));
}
CLEAN_AS(func_ov004_0223f41c, InsectRoom_UpdateInsect)

/* func_ov004_0223f69c: an insect's x and z kept within its bounds: either, outside them, goes
 * back to `fallback`'s. */
void InsectRoom_KeepInBounds(InsectRoom *self, MuseumInsect *insect, const Vec3 *fallback)
{
    (void) self;
    if (insect->position.x < insect->low[0] || insect->position.x > insect->high[0]) {
        insect->position.x = fallback->x;
    }
    if (insect->position.z < insect->low[1] || insect->position.z > insect->high[1]) {
        insect->position.z = fallback->z;
    }
}
CLEAN_AS(func_ov004_0223f69c, InsectRoom_KeepInBounds)

/* An insect's file name without its extension. */
static void InsectRoom_file_name(char *name, MuseumInsect *insect, int kind)
{
    if (kind == KIND_37 && !insect->awake) {
        CLib_SPrintf(name, data_ov004_022565b4);
        /* QUIRK: from now on the kind's animation is taken for a visibility one, awake or
         * not, until the overlay is loaded again */
        kind_info(kind)->visibility_anim = 1;
    } else if (kind == KIND_24) {
        CLib_SPrintf(name, data_ov004_022565c8, KIND_24_FILE);
    } else if (kind == MUSEUM_INSECT_WITH_PARTNER) {
        CLib_SPrintf(name, data_ov004_022565dc);
    } else if (kind == MUSEUM_INSECT_PARTNER) {
        CLib_SPrintf(name, data_ov004_022565f0);
    } else if (kind < 10) {
        CLib_SPrintf(name, data_ov004_02256604, kind);
    } else if (kind < 20) {
        CLib_SPrintf(name, data_ov004_02256618, kind);
    } else if (kind < 30) {
        CLib_SPrintf(name, data_ov004_0225662c, kind);
    } else if (kind < 40) {
        CLib_SPrintf(name, data_ov004_02256640, kind);
    } else if (kind < 50) {
        CLib_SPrintf(name, data_ov004_02256654, kind);
    } else {
        CLib_SPrintf(name, data_ov004_02256668, kind);
    }
}

/* Kind 24's texture animation loaded and played on its model; whether it was. */
static int InsectRoom_load_texture_anim(MuseumInsect *insect, Heap *heap)
{
    char path[33];
    CLib_SPrintf(path, data_ov004_022566a0, KIND_24_FILE);
    if (!RomFile_Exists(path)) {
        return 0;
    }
    void *file = RomFile_Load(path, heap, 4, NULL);
    if (file == NULL) {
        return 0;
    }
    u8 *textures = func_02107bbc(NNS_G3dGetTexSRTAnmSet(file), 0);
    if (!ModelAnim_AllocMaterialAnim(&insect->anim, insect->model.object.model, heap)) {
        return 0;
    }
    ModelAnim_Start(&insect->anim, textures, 0, ONE, 0);
    ModelAnim_Attach(&insect->anim, ModelObject_RenderObject(&insect->model.object));
    return 1;
}

/* func_ov004_0223f6dc: a loading insect's files from its entry of the room's model pool: its
 * model (nothing more when it is missing), then its animation (kinds 35 and 56 keep theirs on
 * the current heap, for the room to free), started at speed 1 (0 for kinds 9 and 53); kind 24
 * also needs its texture animation. When all is there, its kind's initialiser runs, its sound
 * starts, its kind's frame function is taken and it is shown. */
void InsectRoom_LoadInsect(InsectRoom *self, MuseumInsect *insect)
{
    ModelPoolEntry *entry = ModelPool_Take(&self->pool, &insect->pool_slot);
    char name[17];
    char path[23];
    func_02137550(name, sizeof(name));
    func_02137550(path, sizeof(path));
    int kind = insect->kind;
    InsectRoom_file_name(name, insect, kind);
    CLib_SPrintf(path, data_ov004_0225667c, name);
    if (!RomFile_Exists(path)) {
        return;
    }
    if (!ModelPoolFiles_Load(&insect->files, entry, path)) {
        return;
    }
    ModelObject_SetModel(&insect->model.object, (u8 *) (intptr_t) ModelPoolFiles_Model(&insect->files), NULL);
    InsectKindInfo *info = kind_info(kind);
    CLib_SPrintf(path, info->visibility_anim ? data_ov004_02256688 : data_ov004_02256694, name);
    if (!RomFile_Exists(path)) {
        return;
    }
    Heap *heap = (Heap *) (intptr_t) ModelPoolEntry_Heap(entry);
    void *file;
    if (kind == MUSEUM_INSECT_PARTNER) {
        self->partner_anim = RomFile_Load(path, data_021fbe94, 4, NULL);
        file = self->partner_anim;
    } else if (kind == MUSEUM_INSECT_WITH_PARTNER) {
        self->with_partner_anim = RomFile_Load(path, data_021fbe94, 4, NULL);
        file = self->with_partner_anim;
    } else {
        file = RomFile_Load(path, heap, 4, NULL);
    }
    if (file == NULL) {
        return;
    }
    u8 *anim;
    if (info->visibility_anim) {
        anim = func_02107cf0(NNS_G3dGetVisAnmSet(file), 0);
    } else {
        anim = func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
    }
    if (AnimatedModel_LoadAnim(insect_model(insect), heap)) {
        fx32 speed = kind == KIND_53 || kind == KIND_9 ? 0 : ONE;
        AnimatedModel_Start(insect_model(insect), anim, 0, speed, 0, 0);
        AnimatedModel_Attach(insect_model(insect));
    }
    int ready = 1;
    if (kind == KIND_24) {
        ready = InsectRoom_load_texture_anim(insect, heap);
    }
    if (ready) {
        data_ov004_022563ec[kind].init(insect);
        SoundSource_Init(&insect->sound);
        insect->frame = data_ov004_022563ec[kind].frame;
        insect->state = MUSEUM_INSECT_SHOWN;
    }
}
CLEAN_AS(func_ov004_0223f6dc, InsectRoom_LoadInsect)

/* func_ov004_0223f9c8 (vtable slot 0, the creation): the model pool (32 entries) made and the
 * room's given insects added. */
int InsectRoom_Init(InsectRoom *self)
{
    ModelPool_Create(&self->pool, MUSEUM_INSECT_ENTRIES, INSECT_POOL_TEXTURES, INSECT_POOL_PALETTES, INSECT_POOL_HEAP,
                     func_0205c994, func_0205c978, NULL);
    InsectRoom_AddGivenInsects(self);
    return 1;
}
CLEAN_AS(func_ov004_0223f9c8, InsectRoom_Init)

/* func_ov004_0223fa10: an insect of `kind` put in the first free entry, to be loaded: an
 * entry of the model pool taken, its files reset, placed at its kind's spot, no base
 * animation yet; whether there was a free entry. */
int InsectRoom_AddInsect(InsectRoom *self, int kind)
{
    int index = InsectRoom_FreeEntry();
    if (index == -1) {
        return 0;
    }
    MuseumInsect *insect = &data_ov004_02259a34[index];
    insect->kind = (s8) kind;
    insect->state = MUSEUM_INSECT_LOADING;
    ModelPool_Take(&self->pool, &insect->pool_slot);
    ModelPoolFiles_Reset(&insect->files);
    InsectRoom_PlaceInsect(self, insect);
    insect->anim.anim = NULL;
    insect->anim.model = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0223fa10, InsectRoom_AddInsect)

/* func_ov004_0223fa80: the first entry that is off, or -1. */
int InsectRoom_FreeEntry(void)
{
    for (u8 i = 0; i < MUSEUM_INSECT_ENTRIES; i++) {
        if (data_ov004_02259a34[i].state == MUSEUM_INSECT_OFF) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_ov004_0223fa80, InsectRoom_FreeEntry)

/* func_ov004_0223fab4 (the room's profile maker) */
void InsectRoom_New(void)
{
    InsectRoom *self = Heap_AllocAuxZeroed(sizeof(InsectRoom));
    if (self != NULL) {
        InsectRoom_Construct(self);
    }
}
CLEAN_AS(func_ov004_0223fab4, InsectRoom_New)

/* Where a kind is placed, in 1/16 units, and the hour bands it is awake in. */
typedef struct InsectSpot {
    s16 x;
    s16 y;
    s16 z;
    u8 hours;
} InsectSpot;

static const InsectSpot InsectRoom_spots[MUSEUM_INSECT_KINDS] = {
    {0x176, 0x13, 0x71, 0x0c},  {0x170, 0x13, 0x9c, 0x0c},  {0x17f, 0x13, 0x85, 0x0c},  {0x177, 0x13, 0xd0, 0x0c},
    {0x184, 0x13, 0xb5, 0x0c},  {0x187, 0x13, 0xe4, 0x0c},  {0x178, 0x13, 0xfb, 0x0c},  {0x170, 0x13, 0x123, 0x0c},
    {0x128, 0x40, 0x66, 0x21},  {0x82, 0x1c, 0x1aa, 0x21},  {0xd0, 0x13, 0xfc, 0x0c},   {0x86, 0x26, 0x1a6, 0x0e},
    {0x146, 0x08, 0xf6, 0x1c},  {0x185, 0x08, 0x140, 0x1c}, {0xb5, 0x13, 0x141, 0x0c},  {0x181, 0x13, 0x13f, 0x0c},
    {0x8e, 0x24, 0xd1, 0x0c},   {0x8a, 0x1a, 0xd5, 0x0c},   {0xbe, 0x1a, 0x4d, 0x0c},   {0xb8, 0x22, 0x4b, 0x1a},
    {0xf1, 0x24, 0x3d, 0x1b},   {0x16c, 0x14, 0xd2, 0x1c},  {0x132, 0x14, 0x10d, 0x0c}, {0x178, 0x14, 0x122, 0x0c},
    {0x89, 0x09, 0x104, 0x0c},  {0x7a, 0x00, 0x12c, 0x1c},  {0xaa, 0x13, 0xfa, 0x1c},   {0x15e, 0x08, 0x118, 0x33},
    {0x19f, 0x08, 0x11a, 0x33}, {0x16f, 0x08, 0xf2, 0x0c},  {0xe2, 0x08, 0x13e, 0x3f},  {0x1a2, 0x24, 0x4c, 0x1e},
    {0x91, 0x13, 0xdf, 0x0c},   {0x82, 0x18, 0x65, 0x33},   {0x88, 0x22, 0x62, 0x03},   {0x165, 0x08, 0xec, 0x23},
    {0xae, 0x2a, 0xcd, 0x23},   {0x53, 0x13, 0x146, 0x21},  {0xeb, 0x16, 0x42, 0x0c},   {0x122, 0x22, 0x52, 0x0c},
    {0x128, 0x18, 0x55, 0x23},  {0x15e, 0x16, 0x47, 0x23},  {0x164, 0x20, 0x43, 0x03},  {0x82, 0x21, 0x138, 0x23},
    {0x19c, 0x16, 0x51, 0x23},  {0xaa, 0x1a, 0xd3, 0x23},   {0x79, 0x1a, 0xe8, 0x23},   {0x7d, 0x2a, 0xe2, 0x03},
    {0x12c, 0x00, 0x12c, 0x3f}, {0x00, 0x00, 0x00, 0x3f},   {0xb4, 0x19, 0xfa, 0x3f},   {0x118, 0x23, 0xf0, 0x3f},
    {0x14a, 0x00, 0xb4, 0x3f},  {0x96, 0x29, 0x133, 0x3f},  {0x134, 0x08, 0x11e, 0x21}, {0x128, 0x08, 0x136, 0x21},
    {0x165, 0x08, 0xec, 0x23}, /* kind 56 at kind 35's */
};

/* The ROM's 1/16 units to world units, through the SDK's multiply. */
static fx32 sixteenths(fx32 value)
{
    return FX_MulFunc((fx32) ((u32) value << 12), 0x100);
}

/* func_ov004_0223fad0: an insect placed at its kind's spot, awake when the hour now is in one
 * of its kind's bands.
 * QUIRK: an insect of no kind keeps its position and its awake byte; its position is still
 * converted again. */
void InsectRoom_PlaceInsect(InsectRoom *self, MuseumInsect *insect)
{
    (void) self;
    int bands = InsectRoom_HourBand();
    int kind = insect->kind;
    if (kind >= 0 && kind < MUSEUM_INSECT_KINDS) {
        const InsectSpot *spot = &InsectRoom_spots[kind];
        insect->position.x = spot->x;
        insect->position.y = spot->y;
        insect->position.z = spot->z;
        insect->awake = (u8) (bands & spot->hours);
    }
    insect->position.x = sixteenths(insect->position.x);
    insect->position.y = sixteenths(insect->position.y);
    insect->position.z = sixteenths(insect->position.z);
}
CLEAN_AS(func_ov004_0223fad0, InsectRoom_PlaceInsect)
