/* The room object of "obj_ms_cafe" and "obj_cf_chr" (cafe_room.h). */
#include "cafe_room.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "main/animated_model.h"
#include "ov004/member_pointer.h"
#include "ov004/rmo_model.h"
#include "ov004/rmo_object_base.h"
#include "ov004/rmo_object_slots.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(CafeRoom, alpha) == 0x290, "alpha");
static_assert(offsetof(CafeRoom, target_alpha) == 0x294, "target alpha");
static_assert(offsetof(CafeRoom, has_chr) == 0x298, "has chr");
static_assert(offsetof(CafeRoom, chr) == 0x29c, "chr");
static_assert(offsetof(CafeRoom, chr_model) == 0x354, "chr model");
static_assert(offsetof(CafeRoom, chr_texture) == 0x3f8, "chr texture");
static_assert(sizeof(CafeRoom) == 0x3fc, "the size CafeRoom_New allocates");

#define CAFE_ROOM_MODE 0x24c /* u8, in the RMO object's unk_24c */

/* The one that exists, NULL for none. */
extern CafeRoom *data_ov068_022788b0;

/* The modes' updates and entries (function-local statics filled once), their guards and
 * constants. */
extern u32 data_ov068_02278890;
extern MemberPointer data_ov068_022788c4[CAFE_ROOM_MODES];
extern const MemberPointer data_ov068_02277efc, data_ov068_02277f14;
extern u32 data_ov068_022788a0;
extern MemberPointer data_ov068_022788b4[CAFE_ROOM_MODES];
extern const MemberPointer data_ov068_02277f04, data_ov068_02277f0c;

static u8 *mode_of(CafeRoom *self)
{
    return (u8 *) self + CAFE_ROOM_MODE;
}

/* func_ov068_02274ee0 (update of mode 1) */
void CafeRoom_UpdateShown(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_SHOWN;
}
CLEAN_AS(func_ov068_02274ee0, CafeRoom_UpdateShown)

/* func_ov068_02274eec (entry of mode 1) */
int CafeRoom_EnterShown(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_SHOWN;
    return 1;
}
CLEAN_AS(func_ov068_02274eec, CafeRoom_EnterShown)

/* func_ov068_02274efc (update of mode 0) */
void CafeRoom_UpdateFaded(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_FADED;
}
CLEAN_AS(func_ov068_02274efc, CafeRoom_UpdateFaded)

/* func_ov068_02274f08 (entry of mode 0) */
int CafeRoom_EnterFaded(CafeRoom *self)
{
    self->target_alpha = CAFE_ROOM_ALPHA_FADED;
    return 1;
}
CLEAN_AS(func_ov068_02274f08, CafeRoom_EnterFaded)

/* func_ov068_02274f18: the update of its mode (through a table filled once); modes 2 and above
 * do nothing. */
void CafeRoom_UpdateMode(CafeRoom *self)
{
    static const MemberPointer *const updates[CAFE_ROOM_MODES] = {
        &data_ov068_02277efc, /* CafeRoom_UpdateFaded */
        &data_ov068_02277f14, /* CafeRoom_UpdateShown */
    };
    MemberTable_InitOnce(&data_ov068_02278890, data_ov068_022788c4, updates, CAFE_ROOM_MODES);
    u8 mode = *mode_of(self);
    if (mode < CAFE_ROOM_MODES) {
        MemberPointer_CallVoid(&data_ov068_022788c4[mode], self);
    }
}
CLEAN_AS(_ZN18Obj_ov068_02277f3c19func_ov068_02274f18Ev, CafeRoom_UpdateMode)

/* func_ov068_02274f84 (vtable slot 0x60): `mode` taken when its entry (through a table filled
 * once) agrees and the shared value takes it (func_ov004_0222c558); whether it was. Modes 2
 * and above do not exist. */
int CafeRoom_SetMode(CafeRoom *self, unsigned int mode)
{
    static const MemberPointer *const entries[CAFE_ROOM_MODES] = {
        &data_ov068_02277f04, /* CafeRoom_EnterFaded */
        &data_ov068_02277f0c, /* CafeRoom_EnterShown */
    };
    MemberTable_InitOnce(&data_ov068_022788a0, data_ov068_022788b4, entries, CAFE_ROOM_MODES);
    if (mode >= CAFE_ROOM_MODES || MemberPointer_CallInt(&data_ov068_022788b4[mode], self) == 0 ||
        RmoObjectSlots_SetSharedValue(&self->base, mode) == 0) {
        return 0;
    }
    *mode_of(self) = (u8) mode;
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_02277f3c19func_ov068_02274f84Ej, CafeRoom_SetMode)

/* func_ov068_02275010 (vtable slot 0x0c): the body's archive released, and chr's when it was
 * loaded; no room object any more. */
int CafeRoom_Release(CafeRoom *self)
{
    RmoObjectSlots_ReleaseBody(&self->base);
    if (self->has_chr != 0) {
        RmoModel_ReleaseWithTexture(&self->chr_model, &self->chr_texture);
    }
    data_ov068_022788b0 = NULL;
    return 1;
}
CLEAN_AS(func_ov068_02275010, CafeRoom_Release)

/* func_ov068_0227504c (vtable slot 0x24): the body drawn, and chr when it was loaded. */
int CafeRoom_Draw(CafeRoom *self)
{
    AnimatedModel_Draw((AnimatedModel *) (void *) &self->base.body, NULL);
    if (self->has_chr != 0) {
        AnimatedModel_Draw((AnimatedModel *) (void *) &self->chr, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov068_0227504c, CafeRoom_Draw)

/* The archives' names ("obj_ms_cafe", "obj_cf_chr"). */
extern const char data_ov068_02277fa4[];
extern const char data_ov068_02277fb0[];
/* The class's vtable. */
extern const u8 data_ov068_02277f3c[];

/* A NitroSystem routine: the alpha of one material of a model resource. */
extern void NNS_G3dMdlSetMdlAlpha(u8 *model, unsigned int material, u8 alpha);

/* The shared value the room object takes, the frames' step of its alpha and the vtable slot of
 * its mode (CafeRoom_SetMode), called virtually. */
#define CAFE_ROOM_VALUE_NUMBER 1
#define CAFE_ROOM_ALPHA_STEP 2
#define CAFE_ROOM_SLOT_SET_MODE 0x60
/* The byte of a model resource that counts its materials. */
#define CAFE_ROOM_MODEL_MATERIALS 0x18

/* _ZN18Obj_ov068_02277f3c19func_ov068_0227507cEv (vtable slot 0x18, its update): its mode's
 * update, the alpha moved 2 towards its target, and every material of the body's model given
 * that alpha (the count read once). Always 1. */
int CafeRoom_Update(CafeRoom *self)
{
    CafeRoom_UpdateMode(self);
    if (self->alpha != self->target_alpha) {
        Approach_S32Again((int *) (void *) &self->alpha, self->target_alpha, CAFE_ROOM_ALPHA_STEP);
    }
    u8 *model = self->base.body.object.model;
    unsigned int materials = model[CAFE_ROOM_MODEL_MATERIALS];
    for (unsigned int i = 0; i < materials; i++) {
        NNS_G3dMdlSetMdlAlpha(self->base.body.object.model, i, (u8) self->alpha);
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_02277f3c19func_ov068_0227507cEv, CafeRoom_Update)

/* func_ov068_022750d0 (vtable slot 0x00, its start): it becomes the room object, takes shared
 * value 1, loads "obj_ms_cafe", starts faded (alpha and target 1), loads "obj_cf_chr" into its
 * second part and enters mode 1 (through its vtable); chr then counts as loaded whatever the
 * load said. Always 1. */
int CafeRoom_Start(CafeRoom *self)
{
    data_ov068_022788b0 = self;
    RmoObjectSlots_SetValueNumber(&self->base, CAFE_ROOM_VALUE_NUMBER);
    RmoObjectSlots_LoadNamed(&self->base, data_ov068_02277fa4);
    self->target_alpha = CAFE_ROOM_ALPHA_FADED;
    self->alpha = self->target_alpha;
    RmoModel_LoadNamed(data_ov068_02277fb0, (ModelObject *) &self->chr, &self->chr_model, &self->chr_texture);
    u32 vtable = *(const u32 *) (const void *) self;
    ((void (*)(CafeRoom *, int))(uintptr_t) *(const u32 *) (uintptr_t) (vtable + CAFE_ROOM_SLOT_SET_MODE))(self, 1);
    self->has_chr = 1;
    return 1;
}
CLEAN_AS(func_ov068_022750d0, CafeRoom_Start)

/* func_ov068_02275140 (vtable slot 0x44): CafeRoom_Destruct, then the object freed. */
CafeRoom *CafeRoom_DestructDelete(CafeRoom *self)
{
    *(const u8 **) (void *) self = data_ov068_02277f3c;
    RmoTexture_Destruct(&self->chr_texture);
    RmoModel_Destruct(&self->chr_model);
    AnimatedModel_DestructComplete((AnimatedModel *) (void *) &self->chr);
    RmoObjectSlots_Destruct(&self->base);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov068_02275140, CafeRoom_DestructDelete)

/* func_ov068_02275184 (vtable slot 0x40): the destructor: its members in the reverse order of
 * their making, then the RMO base. */
CafeRoom *CafeRoom_Destruct(CafeRoom *self)
{
    *(const u8 **) (void *) self = data_ov068_02277f3c;
    RmoTexture_Destruct(&self->chr_texture);
    RmoModel_Destruct(&self->chr_model);
    AnimatedModel_DestructComplete((AnimatedModel *) (void *) &self->chr);
    RmoObjectSlots_Destruct(&self->base);
    return self;
}
CLEAN_AS(func_ov068_02275184, CafeRoom_Destruct)

/* func_ov068_022751c4: the constructor: the RMO base, the class's vtable, its second part's
 * model, archive and texture; no room object yet. */
CafeRoom *CafeRoom_Construct(CafeRoom *self)
{
    RmoObjectBase_Construct(&self->base);
    *(const u8 **) (void *) self = data_ov068_02277f3c;
    AnimatedModel_Construct((AnimatedModel *) (void *) &self->chr);
    RmoModel_Construct(&self->chr_model);
    RmoTexture_Construct(&self->chr_texture);
    data_ov068_022788b0 = NULL;
    return self;
}
CLEAN_AS(func_ov068_022751c4, CafeRoom_Construct)

/* func_ov068_0227520c (its entry in the overlay's table of profiles): allocates (zeroed) and
 * constructs a room object.
 * QUIRK: declared void, the original leaves the object (or 0 when there was no room) as its
 * result, and its caller reads it; here the constructor's call comes last for the same. */
void CafeRoom_New(void)
{
    CafeRoom *self = Heap_AllocAuxZeroed(sizeof(CafeRoom));
    if (self != NULL) {
        CafeRoom_Construct(self);
    }
}
CLEAN_AS(func_ov068_0227520c, CafeRoom_New)
