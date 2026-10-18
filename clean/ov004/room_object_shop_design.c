/* The room objects that show a design of the shop (room_object_shop_design.h). */
#include "room_object_shop_design.h"

#include <stdint.h>

#include "clean.h"
#include "main/design_assets.h"
#include "main/design_sets.h"
#include "main/sound_emitter.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "autoload_2/sound_emitter_class.h"
#include "main/item_code.h"
#include "main/material_bind.h"

static_assert(offsetof(ShopDesignObject, design) == 0x844, "design");
static_assert(offsetof(ShopDesignObject, emitter) == 0x848, "emitter");
static_assert(offsetof(ShopDesignObject, has_sound) == 0x888, "has sound");
static_assert(sizeof(ShopDesignObject) == 0x88c, "the size ShopDesignObject_Create allocates");
static_assert(offsetof(RoomObject, sound) == 0x798, "the object's centre is at 0x7b8");

#define SHOP_DESIGN_OBJECT_SIZE 0x88c
#define SHOP_DESIGN_ITEM_FIRST 0x3e04 /* four codes (variants) a design */
#define SHOP_DESIGN_ITEM_LAST 0x3e23
#define SHOP_DESIGNS_MASK 7
#define SHOP_DESIGN_SOUND 0x50 /* played when the shop's design changes */
#define SHOP_DESIGN_VOLUME 0x7f

/* "w", the material the design goes on. */
extern const char data_ov004_022531c8[];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251ec4[];
extern const u8 data_ov004_02251f70[];

static SoundEmitter *ShopDesignObject_emitter(ShopDesignObject *object)
{
    return (SoundEmitter *) (void *) object->emitter;
}

static DesignManager *ShopDesignObject_designs(void)
{
    return (DesignManager *) (uintptr_t) DesignManager_Get();
}

/* func_ov004_02213984 (vtable slot 0x0c): the emitter's slot 0x10 while it is in use; 1. */
int ShopDesignObject_Vfunc0C(ShopDesignObject *object)
{
    if (object->has_sound != 0) {
        SoundEmitter_Vfunc10B(ShopDesignObject_emitter(object));
    }
    return 1;
}
CLEAN_AS(func_ov004_02213984, ShopDesignObject_Vfunc0C)

/* func_ov004_022139a8 (vtable slot 0x80, each frame while neither appearing nor vanishing):
 * while the emitter is in use, plays sound 0x50 when the shop's design changed since the last
 * frame (forgetting that it did), and keeps the emitter at the object's centre. */
int ShopDesignObject_Update(ShopDesignObject *object)
{
    if (object->has_sound != 0) {
        Vec3 centre = object->base.sound.position;
        if (DesignManager_TakeShopChanged(ShopDesignObject_designs(), object->design)) {
            SoundEmitter_PlayB(ShopDesignObject_emitter(object), SHOP_DESIGN_SOUND, SHOP_DESIGN_VOLUME, 0);
        }
        SoundEmitter_UpdateAtB(ShopDesignObject_emitter(object), &centre);
    }
    return 1;
}
CLEAN_AS(func_ov004_022139a8, ShopDesignObject_Update)

/* func_ov004_02213a08 (vtable slot 0x7c, once the model is bound, until it is done): takes
 * which design the item code shows (0 for a code outside the range) and, when the code is in
 * the range and the shop's texture of that design exists, puts it on "w" and starts the
 * emitter (stopping it first) if it was not in use; done then, not done otherwise. */
int ShopDesignObject_Start(ShopDesignObject *object)
{
    u16 item = ItemCode_MakeVariant(RoomObject_Number(&object->base), 0);
    object->design = 0;
    if (item < SHOP_DESIGN_ITEM_FIRST || item > SHOP_DESIGN_ITEM_LAST) {
        return 0;
    }
    object->design = ((item - SHOP_DESIGN_ITEM_FIRST) >> 2) & SHOP_DESIGNS_MASK;
    int texture = DesignManager_ShopTexture(ShopDesignObject_designs(), (u8) object->design);
    if (texture == 0) {
        return 0;
    }
    MaterialBind_BindByIndex((u8 *) object->base.model_resource, data_ov004_022531c8, (G3dResTex *) (uintptr_t) texture, 0, 0);
    if (object->has_sound == 0) {
        SoundEmitter_StopB(ShopDesignObject_emitter(object));
        object->has_sound = 1;
    }
    return 1;
}
CLEAN_AS(func_ov004_02213a08, ShopDesignObject_Start)

static void ShopDesignObject_set_vtables(ShopDesignObject *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02251ec4;
    object->base.receiver_vtable = data_ov004_02251f70;
}

/* func_ov004_02213ab8 (the deleting destructor, vtable slot 0x44): the emitter's destructor,
 * then the base class's. */
ShopDesignObject *ShopDesignObject_Delete(ShopDesignObject *object)
{
    ShopDesignObject_set_vtables(object);
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) (void *) object->emitter);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02213ab8, ShopDesignObject_Delete)

/* func_ov004_02213af0 (the destructor, vtable slot 0x40) */
ShopDesignObject *ShopDesignObject_Destroy(ShopDesignObject *object)
{
    ShopDesignObject_set_vtables(object);
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) (void *) object->emitter);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02213af0, ShopDesignObject_Destroy)

/* func_ov004_02213b24 (the constructor): builds the emitter. Its other fields are left as the
 * allocation zeroed them. */
ShopDesignObject *ShopDesignObject_Construct(ShopDesignObject *object)
{
    RoomObject_ConstructBase(&object->base);
    ShopDesignObject_set_vtables(object);
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) (void *) object->emitter);
    return object;
}
CLEAN_AS(func_ov004_02213b24, ShopDesignObject_Construct)

/* func_ov004_02213b54: a new one from the room's heap; nothing when it has no room. */
void ShopDesignObject_Create(void)
{
    ShopDesignObject *object = RoomObject_Alloc(SHOP_DESIGN_OBJECT_SIZE);
    if (object != NULL) {
        ShopDesignObject_Construct(object);
    }
}
CLEAN_AS(func_ov004_02213b54, ShopDesignObject_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters ShopDesignObject's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static ShopDesignObject *ShopDesignObject_from_receiver(void *receiver)
{
    return (ShopDesignObject *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a9fc: the deleting destructor, entered from the receiver part. */
ShopDesignObject *ShopDesignObjectReceiver_Delete(void *receiver)
{
    return ShopDesignObject_Delete(ShopDesignObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251ec4D0Ev, ShopDesignObjectReceiver_Delete)

/* func_ov004_0221aa18: the destructor, entered from the receiver part. */
ShopDesignObject *ShopDesignObjectReceiver_Destroy(void *receiver)
{
    return ShopDesignObject_Destroy(ShopDesignObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251ec4D1Ev, ShopDesignObjectReceiver_Destroy)
