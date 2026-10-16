/* The life of the room objects (room_object_life.h). */
#include "room_object_life.h"

#include <string.h>

#include "clean.h"
#include "main/actor.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_light.h"
#include "room_object_methods.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObjectVtable, material_hook) == 0x60, "vtable slot 0x60");
static_assert(offsetof(RoomObjectVtable, vfunc_70) == 0x70, "vtable slot 0x70");
static_assert(offsetof(RoomObjectVtable, on_model_bound) == 0x7c, "vtable slot 0x7c");
static_assert(offsetof(RoomObjectVtable, keeps_texture_copy) == 0x8c, "vtable slot 0x8c");
static_assert(offsetof(RoomObject, receiver_vtable) == 0xec, "receiver part");
static_assert(offsetof(RoomObject, receiver_state) == 0x10a, "receiver state byte");
static_assert(offsetof(RoomObject, link) == 0x12c, "receiver's link");
static_assert(offsetof(RoomObject, slot) == 0x132, "slot");
static_assert(offsetof(RoomObject, item_shadows) == 0x1d0, "item shadows");
static_assert(offsetof(RoomObject, sound) == 0x798, "sound");
static_assert(offsetof(RoomObject, anims) == 0x7c4, "anims");
static_assert(sizeof(RoomObject) == 0x844, "the size RoomObject_Create allocates");

#define ROOM_OBJECT_SIZE 0x844
#define RECEIVER_OFFSET 0xec
#define MODE_FIRST 0         /* RoomObject.unk_76C: its model is loaded at once */
#define STATE_CHANGE_START 2 /* the value of vtable slot 0x08's argument handled here */
#define LOADING (-1)         /* RoomObject_Init: the model is not loaded yet */
#define ITEM_SHADOW_SIZE 0x20
#define ANIM_SIZE 0x20

/* The vtables of the base class and of its receiver part. */
extern const u8 data_ov004_0224fe6c[];
extern const u8 data_ov004_0224ff18[];
/* The pool the objects' slots are in (RoomObject.slot). */
extern u8 data_ov004_02259698[];

/* NitroSystem's 3D state; the light colours (the hardware's LIGHT_COLOR command, the light's
 * number in bits 30-31) are at 0xa8. */
extern struct {
    u8 unk_00[0xa8];
    u32 light_colors[4];
} NNS_G3dGlb;

#define LIGHT_WHITE 0x7fff

/* The C++ runtime's arrays. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The members' constructors and destructors the arrays are given (the game's functions). */
extern void func_020b7ee8(void *shadow);
extern void func_020b7ed8(void *shadow);
extern void func_ov004_0220e4ec(void *anim);
extern void func_ov004_0220e4d4(void *anim);

/* The scene object's slots, and its other members. */
extern void func_0203f004(RoomObject *object, int mode);
extern unsigned long func_0203efbc(RoomObject *object);
extern void func_0203efb0(RoomObject *object, unsigned int reference);
extern void *func_0203f130(RoomObject *object);
extern void *func_0203f080(RoomObject *object);
extern void *func_02066a30(void *receiver);
extern void *func_02066994(void *receiver);
extern void func_0209d34c(u16 *slot);
extern void func_0209d340(u16 *slot);
extern void *func_0209d238(u8 *pool, u16 *slot);
extern void *func_020b82ec(void *shadow);
extern void *func_020b82d0(void *shadow);
extern void *func_02054e54(void *model);
extern void *func_02054e18(void *model);
extern void func_0205510c(void *model, const int *scale);
extern int func_02055f2c(void *model, u8 *model_resource, u8 *texture);
extern void func_ov004_0223b250(void *mover);
extern void func_ov004_0223b248(void *mover);
extern void func_ov004_0223cfbc(RoomSound *sound);
extern void func_ov004_0223cfb8(RoomSound *sound);
extern void func_ov004_0223cf80(RoomSound *sound);

/* The room's objects and its heap. */
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223ce18(void *objects, RoomObject *object);
extern void **func_ov004_0223cf10(void);
extern void func_ov004_0223ce8c(void **heap, void *block);
extern void *func_ov004_0223ce98(void **heap, u32 size);

/* func_ov004_022109e4 (vtable slot 0x28): draws the model at its scale (when it has one) unless
 * the scene object (Actor_CanDraw) or the class (vtable slot 0x88) says not to, then what it
 * carries. A preview (RoomObject_Unk76CIs2) is drawn with every light white and carries
 * nothing. Whether it was drawn.
 * REQUIRES: whether it is a preview does not change while its model is drawn (the ROM would
 * then put back light colours it never saved). */
int RoomObject_Draw(RoomObject *object)
{
    if (!Actor_CanDraw((Actor *) object)) {
        return 0;
    }
    if (!object->vtable->can_draw(object)) {
        return 0;
    }
    if (object->scale_x != 0 || object->scale_y != 0 || object->scale_z != 0) {
        u32 saved[4] = {0};
        if (RoomObject_Unk76CIs2(object)) {
            for (u32 light = 0; light < 4; light++) {
                saved[light] = NNS_G3dGlb.light_colors[light];
                NNS_G3dGlb.light_colors[light] = light << 30 | LIGHT_WHITE;
            }
        }
        func_0205510c(object->unk_538, &object->scale_x);
        if (RoomObject_Unk76CIs2(object)) {
            for (u32 light = 0; light < 4; light++) {
                NNS_G3dGlb.light_colors[light] = saved[light];
            }
        }
    }
    if (!RoomObject_Unk76CIs2(object)) {
        CarriedItems_Draw(&object->carried, object);
    }
    return 1;
}
CLEAN_AS(func_ov004_022109e4, RoomObject_Draw)

/* func_ov004_02210ab4 (vtable slot 0x84, each frame while appearing or vanishing) */
int RoomObject_Vfunc84(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02210ab4, RoomObject_Vfunc84)

/* func_ov004_02210ab8 (vtable slot 0x80, each frame while neither appearing nor vanishing) */
int RoomObject_Vfunc80(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02210ab8, RoomObject_Vfunc80)

/* _ZN10RoomObject19func_ov004_02210abcEv (vtable slot 0x18, each frame): its sound follows its
 * centre, then the state's update, the box, shadow and matrices. While neither appearing nor
 * vanishing the class's slot 0x80 runs (after func_ov004_0221081c's lookup when unk_780 is 0);
 * otherwise slot 0x84 runs and a switch that was asked to change is put back (Switch_Toggle
 * with the change shown). Then, except for a preview, the light, the switch and the shadows of
 * what stands on it. */
int RoomObject_Update(RoomObject *object)
{
    if (!RoomObject_Unk76CIs2(object)) {
        Vec3 centre;
        func_ov004_0223cf80(&object->sound);
        RoomObject_Centre(object, &centre);
        object->sound.position = centre;
    }
    RoomObject_UpdateState(object);
    RoomObject_UpdateBoxAndShadow(object);
    RoomObject_UpdateMatrices(object);
    if (!RoomObject_IsInState(object, ROOM_OBJECT_APPEAR) && !RoomObject_IsInState(object, ROOM_OBJECT_VANISH)) {
        if (object->unk_780 == 0) {
            RoomObject_Lookup020537a8(object);
        }
        object->vtable->update_settled(object);
    } else {
        object->vtable->update_unsettled(object);
        if (Switch_IsPending(&object->light_switch)) {
            Switch_Toggle(&object->light_switch, 0);
        }
    }
    if (!RoomObject_Unk76CIs2(object)) {
        RoomObject_UpdateLight(object);
        Switch_Apply(&object->light_switch, object);
        RoomObject_ShadowItemsOnTop(object);
    }
    return 1;
}
CLEAN_AS(_ZN10RoomObject19func_ov004_02210abcEv, RoomObject_Update)

/* func_ov004_02210b94 (vtable slot 0x08): with 2 a light starts (RoomObject_StartLight); the
 * scene object's slot (func_0203f004) runs for every value. */
void RoomObject_Vfunc08(RoomObject *object, int mode)
{
    if (mode == STATE_CHANGE_START) {
        RoomObject_StartLight(object);
    }
    func_0203f004(object, mode);
}
CLEAN_AS(func_ov004_02210b94, RoomObject_Vfunc08)

/* Once the model files are in: the model and its texture to the model object, then
 * RoomObject_BindModel with unk_77E set, cleared again when the class (vtable slot 0x7c) says
 * it is done. Whether it is. */
static int bind_model(RoomObject *object)
{
    u8 *model = FurnitureModel_Model(&object->model_files);
    func_02055f2c(object->unk_538, model, FurnitureModel_Texture(&object->model_files));
    object->unk_77E = 1;
    RoomObject_BindModel(object);
    if (object->vtable->on_model_bound(object)) {
        object->unk_77E = 0;
        return 1;
    }
    return 0;
}

/* func_ov004_02210bb4 (vtable slot 0x00, run until it gives 1): its mode from its placement
 * word, a place among the room's objects (func_ov004_0223ce18) and a slot in the pool, then
 * RoomObject_SetUp; the scene object's reference (func_0203efbc) is set to
 * RoomObject_Reference when it has none. In mode 0 the model files are loaded at once; in the
 * others a step a frame (FurnitureModel_LoadStep), and -1 while they are not in. Then
 * bind_model. */
int RoomObject_Init(RoomObject *object)
{
    object->unk_76C = (s32) ((object->placement >> 26) & 3);
    func_ov004_0223ce18(func_ov004_0223ce84(), object);
    void *slot = func_0209d238(data_ov004_02259698, &object->slot);
    RoomObject_SetUp(object);
    if (!func_0203efbc(object)) {
        func_0203efb0(object, RoomObject_Reference(object, NULL, 0));
    }
    if (object->unk_76C == MODE_FIRST) {
        FurnitureModel_Load(&object->model_files, slot, object->unk_284, object->vtable->keeps_texture_copy(object));
        return bind_model(object);
    }
    if (FurnitureModel_LoadStep(&object->model_files, slot, object->unk_284, object->vtable->keeps_texture_copy(object))) {
        return bind_model(object);
    }
    return LOADING;
}
CLEAN_AS(func_ov004_02210bb4, RoomObject_Init)

/* The destructor's body: the vtables of the base class, then the members from the last to the
 * first and the two bases. */
static void destroy(RoomObject *object)
{
    object->vtable = (const RoomObjectVtable *) data_ov004_0224fe6c;
    object->receiver_vtable = data_ov004_0224ff18;
    __cxa_vec_cleanup(object->anims, 4, ANIM_SIZE, func_ov004_0220e4d4);
    func_ov004_0223cfb8(&object->sound);
    ByteSet_Destruct(&object->node_set);
    Glow_Destruct(&object->glow);
    NodePair_Destruct(&object->nodes);
    Switch_Destruct(&object->light_switch);
    FurnitureModel_Destruct(&object->model_files);
    PushBox_Destruct(&object->push_box);
    func_02054e18(object->unk_538);
    func_020b82d0(object->shadow);
    func_ov004_0223b248(object->unk_250);
    __cxa_vec_cleanup(object->item_shadows, 4, ITEM_SHADOW_SIZE, func_020b7ed8);
    CarriedItems_Destruct(&object->carried);
    Mount_Destruct(&object->mount);
    func_0209d340(&object->slot);
    func_02066994(&object->receiver_vtable);
    func_0203f080(object);
}

/* func_ov004_02210cf0 (the destructor the derived classes' destructors end with) */
RoomObject *RoomObject_DestructBase(RoomObject *object)
{
    destroy(object);
    return object;
}
CLEAN_AS(func_ov004_02210cf0, RoomObject_DestructBase)

/* func_ov004_02210de8 (the deleting destructor, vtable slot 0x44) */
RoomObject *RoomObject_Delete(RoomObject *object)
{
    destroy(object);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02210de8, RoomObject_Delete)

/* func_ov004_02210ee4 (the destructor, vtable slot 0x40) */
RoomObject *RoomObject_Destroy(RoomObject *object)
{
    destroy(object);
    return object;
}
CLEAN_AS(func_ov004_02210ee4, RoomObject_Destroy)

/* The constructor's body: the two bases, the vtables of the base class, then the members from
 * the first to the last. */
static void construct(RoomObject *object)
{
    func_0203f130(object);
    func_02066a30(&object->receiver_vtable);
    object->vtable = (const RoomObjectVtable *) data_ov004_0224fe6c;
    object->receiver_vtable = data_ov004_0224ff18;
    func_0209d34c(&object->slot);
    Mount_Construct(&object->mount);
    CarriedItems_Construct(&object->carried);
    __cxa_vec_ctor(object->item_shadows, 4, ITEM_SHADOW_SIZE, func_020b7ee8, func_020b7ed8);
    func_ov004_0223b250(object->unk_250);
    func_020b82ec(object->shadow);
    func_02054e54(object->unk_538);
    PushBox_Construct(&object->push_box);
    FurnitureModel_Construct(&object->model_files);
    Switch_Construct(&object->light_switch);
    NodePair_Construct(&object->nodes);
    Glow_Construct(&object->glow);
    ByteSet_Construct(&object->node_set);
    func_ov004_0223cfbc(&object->sound);
    __cxa_vec_ctor(object->anims, 4, ANIM_SIZE, func_ov004_0220e4ec, func_ov004_0220e4d4);
}

/* func_ov004_02210fdc (the constructor RoomObject_Create uses) */
RoomObject *RoomObject_Construct(RoomObject *object)
{
    construct(object);
    return object;
}
CLEAN_AS(func_ov004_02210fdc, RoomObject_Construct)

/* func_ov004_022110e4 (the constructor the derived classes' constructors start with; the same
 * as RoomObject_Construct) */
RoomObject *RoomObject_ConstructBase(RoomObject *object)
{
    construct(object);
    return object;
}
CLEAN_AS(func_ov004_022110e4, RoomObject_ConstructBase)

/* func_ov004_022111ec (vtable slot 0x7c, once the model is bound): done at once. */
int RoomObject_Vfunc7C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022111ec, RoomObject_Vfunc7C)

/* func_ov004_02211518 (the class's operator delete): back to the room's heap. */
void RoomObject_Free(void *block)
{
    func_ov004_0223ce8c(func_ov004_0223cf10(), block);
}
CLEAN_AS(func_ov004_02211518, RoomObject_Free)

/* func_ov004_0221152c (the classes' operator new): `size` bytes from the room's heap, zeroed;
 * NULL when there are none. func_ov004_0223ce98 is handed the size but takes blocks of its own
 * size. */
void *RoomObject_Alloc(u32 size)
{
    void *block = func_ov004_0223ce98(func_ov004_0223cf10(), size);
    if (block == NULL) {
        return NULL;
    }
    memset(block, 0, size);
    return block;
}
CLEAN_AS(func_ov004_0221152c, RoomObject_Alloc)

/* func_ov004_02211558: a new room object of the base class; nothing when the heap has no
 * room. */
void RoomObject_Create(void)
{
    RoomObject *object = RoomObject_Alloc(ROOM_OBJECT_SIZE);
    if (object != NULL) {
        RoomObject_Construct(object);
    }
}
CLEAN_AS(func_ov004_02211558, RoomObject_Create)

/* The receiver's vtable (0x0224ff18) enters the destructors through these: each moves the
 * pointer back from the receiver part to the object. */
static RoomObject *object_of(void *receiver)
{
    return (RoomObject *) ((u8 *) receiver - RECEIVER_OFFSET);
}

/* func_ov004_02211574 */
RoomObject *RoomObjectReceiver_Delete(void *receiver)
{
    return RoomObject_Delete(object_of(receiver));
}
CLEAN_AS(_ZThn236_N10RoomObjectD0Ev, RoomObjectReceiver_Delete)

/* func_ov004_02211590 */
RoomObject *RoomObjectReceiver_Destroy(void *receiver)
{
    return RoomObject_Destroy(object_of(receiver));
}
CLEAN_AS(_ZThn236_N10RoomObjectD1Ev, RoomObjectReceiver_Destroy)
