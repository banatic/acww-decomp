/* A room object's body (room_object_body.h). */
#include "room_object_body.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/fx_math.h"
#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "cells.h"
#include "clean.h"
#include "main/item_code.h"
#include "room_object_light.h"
#include "room_object_map.h"
#include "room_object_methods.h"
#include "room_object_parts.h"

#define ONE 0x1000             /* 1 in 20.12 fixed point */
#define PLAYER 4               /* the actor func_020961a8 is asked for */
#define LAYER_FLOOR 0          /* RoomObject.unk_288 */
#define LAYER_ON_TOP 1         /* standing on another object */
#define CARRIES_ITEMS 1        /* RoomObject.unk_788: what stands on its cells moves with it */
#define FOOTPRINT_TWO 1        /* RoomObject.unk_784: two cells along its X axis */
#define FOOTPRINT_TWO_BY_TWO 2 /* 2x2 cells, its position at their middle */
#define MODE_PREVIEW 2         /* RoomObject.unk_76C */
#define LAST_NUMBER 0x6e8      /* the highest furniture number the tables have */
#define BLOCK_CELLS 16
#define AREA_ROOM 10            /* func_020b65c4: the area where the floor's height is looked up */
#define PREVIEW_SCALE 0x400     /* a preview is shown at a quarter of its size... */
#define PREVIEW_DISTANCE 0x4000 /* ...4 units along the camera's line */
#define STATE_CHANGE_EXIT 2     /* the value of vtable slot 0x14's argument handled here */
#define LEFT_BEHIND 0x1547      /* the item put where a vanishing object stood */
#define SHADOW_SHRINK 0xc00     /* the shadow is 3/4 of the object */
#define BOX_HEIGHT 0x4000
#define SHADOW_PLAIN 8      /* the shadow's flags... */
#define SHADOW_020B67AC 0xf /* ...when func_020b67ac says so */

/* Placement word fields. */
#define PLACE_X(word) ((word) & 0xf)
#define PLACE_Y(word) (((word) >> 4) & 0xf)
#define PLACE_NUMBER(word) (((word) >> 8) & 0xffff)
#define PLACE_SIDE(word) (((word) >> 24) & 3)
#define PLACE_ON_TOP(word) (((word) >> 28) & 1)

/* The town's map. */
extern void *data_021c80bc;
/* The scratch matrix of overlay 4's objects. */
extern Mtx43 data_021fbe48;
/* NitroSDK's table of sines and cosines, interleaved, for 4096 angles. */
extern const s16 FX_SinCosTable_[];
/* The two points a preview is placed between: the camera's position (as the sounds use it,
 * main/sound.c) and a point after it, by their use here the one it looks at. */
extern Vec3 data_021c67b8;
extern Vec3 data_021c67d0;
/* The angles a preview is turned by about X and Y (set up by RoomObject_SetUp). */
extern u16 data_ov004_02256c40;
extern u16 data_ov004_02256c3c;
/* The first state for each mode (RoomObject.unk_76C). */
extern const s32 data_ov004_02247634[];
/* A byte for each index among the room's objects, given to func_02055d80. */
extern const u8 data_ov004_02247640[];
/* The names of the clock's hand nodes, "kh_j" and "km_j". */
extern const char data_ov004_02250018[];
extern const char data_ov004_02250020[];
/* For each footprint (RoomObject.unk_784), the address of its four corners in its own space. */
extern const u32 data_ov004_0224fe10[];
/* The pool the objects' slots are in (RoomObject.slot). */
extern u8 data_ov004_02259698[];

/* The function-local statics of RoomObject_Size and RoomObject_PointBeforePlayer: guards, the
 * values and their records in the C++ runtime's list of objects to destroy. */
extern u32 data_ov004_02256c70;
extern Vec3 data_ov004_02256e58[]; /* a size for each footprint */
extern Vec3 data_ov004_02256e64;   /* the second of them */
extern Vec3 data_ov004_02256e70;   /* the third */
extern u8 data_ov004_02256de0[];
extern u8 data_ov004_02256dec[];
extern u8 data_ov004_02256df8[];
extern u32 data_ov004_02256c68;
extern Vec3 data_ov004_02256dc8;
extern u8 data_ov004_02256dbc[];

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020012dc(void *object);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(void *objects, RoomObject *object);
extern RoomObject *func_ov004_0223cd58(void *objects, int index);
extern void func_ov004_0223cde8(void *objects, RoomObject *object);
extern void func_02055d80(void *model, int value);
extern int func_0205790c(G3dModel *model, const char *name);
extern void func_02055dc8(void *model, void *callback, RoomObject *object);
extern void func_ov004_02211450(void);
extern int NNS_G3dBindMdlTex(u8 *model, u8 *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, u8 *texture);
extern void func_0204f7ac(Vec3 *position, int block_x, int block_y, int x, int y);
extern int func_ov004_0223c5a4(Vec3 *point);
extern int func_ov004_0223c5b8(int x, int y);
extern unsigned char func_020b65c4(void);
extern unsigned char func_ov004_0223d348(void);
extern u8 func_02053de4(int number);
extern int func_02053dac(int number);
extern u8 func_02053be0(int number);
extern int func_02053d60(int number);
extern int func_02053d24(int number);
extern int func_020538dc(int number);
extern int func_0205389c(int number);
extern int func_0205395c(int number);
extern int func_02053818(int number);
extern int func_020537a8(int number);
extern s8 func_02053658(int number);
extern ItemCode *func_0204f5e0(void *map, int block_x, int block_y, int x, int y, int layer);
extern void func_0204f794(Vec3 *centre, unsigned int x, unsigned int y);
extern void *func_020b6590(void);
extern void *func_020b7d3c(void *shadows, void *shadow, Vec3 *point, fx32 size, int a4, int a5, u8 a6);
extern int func_020b7dc8(void *shadows, void *shadow, Vec3 *centre, fx32 x, fx32 z, fx32 y, s16 angle, int flags, u8 index);
extern int func_020b7e04(void *shadows, void *shadow);
extern int func_020b67ac(void);
extern int func_02032214(PushBox *box, Vec3 *centre, s16 angle, Vec3 *scale);
extern int func_020321bc(PushBox *box, fx32 x, fx32 z, fx32 height, Vec3 *centre, s16 angle, Vec3 *scale);
extern int func_02032180(PushBox *box);
extern MapActor *func_020961a8(int actor);
extern void func_ov004_0223cf68(RoomSound *sound);
extern void func_0209d200(u8 *pool, u16 *slot);
extern int func_020b6694(int area);
extern int func_020b67e8(int area);
extern int func_0204f538(void *map, ItemCode *item, int x, int y, int layer);
extern void func_02003510(RoomObject *object, int mode);
extern int func_0203efdc(RoomObject *object);

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

static void set_vec(Vec3 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

static void set_scale(RoomObject *object, fx32 scale)
{
    object->scale_x = scale;
    object->scale_y = scale;
    object->scale_z = scale;
}

/* func_ov004_0220f450: func_02055d80 on the model with the byte of data_ov004_02247640 for the
 * object's index among the room's objects, when it has one. */
void RoomObject_SetModelByIndex(RoomObject *object)
{
    int index = func_ov004_0223cd78(func_ov004_0223ce84(), object);
    if (index != -1) {
        func_02055d80(object->unk_538, data_ov004_02247640[index]);
    }
}
CLEAN_AS(func_ov004_0220f450, RoomObject_SetModelByIndex)

/* func_ov004_0220f484: binds the loaded model: the clock's hand nodes, the model's callback
 * (func_ov004_02211450, given the object), the node set, the texture and palettes of the
 * furniture's texture file, then RoomObject_SetModelByIndex. */
void RoomObject_BindModel(RoomObject *object)
{
    G3dModel *model = object->model_resource;
    int hour_hand = func_0205790c(model, data_ov004_02250018);
    int minute_hand = func_0205790c(model, data_ov004_02250020);
    NodePair_Set(&object->nodes, (s8) hour_hand, (s8) minute_hand);
    func_02055dc8(object->unk_538, (void *) func_ov004_02211450, object);
    ByteSet_Bind(&object->node_set, object->model_resource, 1);
    NNS_G3dBindMdlTex(FurnitureModel_Model(&object->model_files), FurnitureModel_Texture(&object->model_files));
    NNS_G3dBindMdlPltt(FurnitureModel_Model(&object->model_files), FurnitureModel_Texture(&object->model_files));
    RoomObject_SetModelByIndex(object);
}
CLEAN_AS(func_ov004_0220f484, RoomObject_BindModel)

/* func_ov004_0220f52c: sets the object up once from its placement word: its position (the
 * centre of its cell, at the height func_ov004_0223c5a4 finds), angle, number (at most
 * LAST_NUMBER), layer, and the furniture's values from the main program's tables; then its
 * matrices, switch, place on the map, first state, box and shadow. A preview instead stands 4
 * units from data_021c67b8 towards data_021c67d0, at a quarter of its size, and the angles it
 * is turned by are set to face along that line. An object on the floor stands at height 0,
 * except in area 10; one on top of another is mounted on it.
 * QUIRK: the item code of the number is made (func_0204bc50) and not used. */
void RoomObject_SetUp(RoomObject *object)
{
    if (object->is_set_up) {
        return;
    }
    u32 word = object->placement;
    if (!RoomObject_Unk76CIs2(object)) {
        func_0204f7ac(&object->position, 0, 0, (int) PLACE_X(word), (int) PLACE_Y(word));
        object->position.y = func_ov004_0223c5a4(&object->position);
        set_scale(object, ONE);
        object->unk_15C = ONE;
    } else {
        Vec3 from = data_021c67b8;
        Vec3 to = data_021c67d0;
        Vec3 direction;
        Vec_Subtract(&direction, &to, &from);
        Vec_NormalizeNonZero(&direction);
        fx32 x = FX_MulFunc(direction.x, PREVIEW_DISTANCE);
        fx32 y = FX_MulFunc(direction.y, PREVIEW_DISTANCE);
        fx32 z = FX_MulFunc(direction.z, PREVIEW_DISTANCE);
        object->position.x = from.x + x;
        object->position.y = from.y + y;
        object->position.z = from.z + z;
        set_scale(object, PREVIEW_SCALE);
        object->unk_15C = ONE;
        data_ov004_02256c40 = (u16) (Math_Atan2(direction.z, direction.y) - 0xb000);
        data_ov004_02256c3c = (u16) (Math_Atan2(direction.x, direction.z) + 0x8000);
    }
    object->angle = (s16) (PLACE_SIDE(word) << 14);
    object->unk_284 = (s32) PLACE_NUMBER(word);
    if (object->unk_284 > LAST_NUMBER) {
        object->unk_284 = LAST_NUMBER;
    }
    (void) ItemCode_MakeVariant(object->unk_284, 0);
    object->unk_288 = (u8) PLACE_ON_TOP(word);
    if (!RoomObject_Unk76CIs2(object) && object->unk_288 == LAYER_FLOOR) {
        object->position.y = 0;
        if (func_020b65c4() == AREA_ROOM) {
            object->position.y = func_ov004_0223c5a4(&object->position);
        }
    }
    object->unk_780 = func_02053de4(object->unk_284);
    object->top_height = func_02053dac(object->unk_284);
    object->unk_784 = func_02053be0(object->unk_284);
    object->unk_774 = func_02053d60(object->unk_284);
    object->unk_778 = func_02053d24(object->unk_284);
    object->unk_78C = (u8) func_020538dc(object->unk_284);
    object->unk_78D = (u8) func_0205389c(object->unk_284);
    object->unk_788 = (u32) func_0205395c(object->unk_284);
    object->light_kind = func_02053818(object->unk_284);
    if (!RoomObject_Unk76CIs2(object)) {
        if (object->unk_784 == FOOTPRINT_TWO_BY_TWO) {
            object->position.x += ONE;
            object->position.z += ONE;
        }
        if (object->unk_288 == LAYER_ON_TOP) {
            Mount_AttachAt(&object->mount, (int) PLACE_X(word), (int) PLACE_Y(word), object->angle);
        }
    }
    RoomObject_UpdateMatrices(object);
    Switch_Load(&object->light_switch, object);
    RoomObject_PutOnMap(object, 1, NULL, 0, 0);
    RoomObject_EnterFirstState(object);
    RoomObject_SetUpBoxAndShadow(object);
    object->is_set_up = 1;
}
CLEAN_AS(func_ov004_0220f52c, RoomObject_SetUp)

/* func_ov004_0220f7d4: enters the first state of the object's mode. */
int RoomObject_EnterFirstState(RoomObject *object)
{
    return RoomObject_EnterState(object, data_ov004_02247634[object->unk_76C]);
}
CLEAN_AS(func_ov004_0220f7d4, RoomObject_EnterFirstState)

/* func_ov004_0220f7f0: for an object on the floor that carries what stands on it, a shadow
 * (func_020b7d3c, its slot by cell) under each pile item lying on its cells, at the height
 * func_ov004_0223c5b8 finds. */
void RoomObject_ShadowItemsOnTop(RoomObject *object)
{
    if (object->unk_288 != LAYER_FLOOR || object->unk_788 != CARRIES_ITEMS) {
        return;
    }
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, NULL, 0);
    void *map = data_021c80bc;
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        int x = CellList_At(&cells, (int) i)->x;
        int y = CellList_At(&cells, (int) i)->y;
        ItemCode *item = func_0204f5e0(map, shift_right(x, 4), shift_right(y, 4), x & (BLOCK_CELLS - 1), y & (BLOCK_CELLS - 1),
                                       LAYER_ON_TOP);
        if (item != NULL && ItemCode_IsKind1(item)) {
            Vec3 point;
            func_0204f794(&point, (unsigned int) x, (unsigned int) y);
            point.y = func_ov004_0223c5b8(x, y);
            func_020b7d3c(func_020b6590(), object->item_shadows[i], &point, 0xccd, 0x100, 0xa, 0xff);
        }
    }
    CellList_Destruct(&cells);
}
CLEAN_AS(func_ov004_0220f7f0, RoomObject_ShadowItemsOnTop)

/* The shadow's flags. */
static int shadow_flags(void)
{
    return func_020b67ac() != 0 ? SHADOW_020B67AC : SHADOW_PLAIN;
}

/* func_ov004_0220f8c0 (each frame): moves the box to the object (func_02032214, when the box
 * is set up and the object has one: not with unk_78C) and its shadow, 3/4 of its size, with
 * it; the shadow goes (func_020b7e04) when the box did not move. Nothing for a preview. */
void RoomObject_UpdateBoxAndShadow(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return;
    }
    Vec3 size;
    RoomObject_Size(object, &size);
    Vec3 scale;
    set_vec(&scale, object->unk_15C, object->unk_15C, object->unk_15C);
    Vec3 centre;
    RoomObject_Centre(object, &centre);
    int shown = 0;
    if (!object->unk_78C) {
        if (object->push_box.unk_98) {
            shown = func_02032214(&object->push_box, &centre, object->angle, &scale);
        } else {
            shown = 1;
        }
    }
    size.x = FX_MulFunc(size.x, SHADOW_SHRINK);
    size.z = FX_MulFunc(size.z, SHADOW_SHRINK);
    if (shown) {
        u8 index = (u8) func_ov004_0223cd78(func_ov004_0223ce84(), object);
        int flags = shadow_flags();
        func_020b7dc8(func_020b6590(), object->shadow, &centre, size.x, size.z, size.y, object->angle, flags, index);
    } else {
        func_020b7e04(func_020b6590(), object->shadow);
    }
}
CLEAN_AS(func_ov004_0220f8c0, RoomObject_UpdateBoxAndShadow)

/* func_ov004_0220f994: takes the box out of the world, when the object has one. */
void RoomObject_RemoveBox(RoomObject *object)
{
    if (!RoomObject_Unk76CIs2(object) && !object->unk_78C) {
        func_02032180(&object->push_box);
        PushBox_ClearOwner(&object->push_box);
    }
}
CLEAN_AS(func_ov004_0220f994, RoomObject_RemoveBox)

/* func_ov004_0220f9c8: sets up the box (func_020321bc, BOX_HEIGHT high, when the object has
 * one) and the shadow, as RoomObject_UpdateBoxAndShadow. Nothing for a preview.
 * QUIRK: the object it stands on is looked up (func_ov004_0223cd58) and not used. */
void RoomObject_SetUpBoxAndShadow(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return;
    }
    Vec3 size;
    RoomObject_Size(object, &size);
    Vec3 scale;
    set_vec(&scale, object->unk_15C, object->unk_15C, object->unk_15C);
    Vec3 centre;
    RoomObject_Centre(object, &centre);
    if (!object->unk_78C) {
        PushBox_SetOwner(&object->push_box, object);
        void *objects = func_ov004_0223ce84();
        (void) func_ov004_0223cd58(objects, Mount_Parent(&object->mount));
        func_020321bc(&object->push_box, size.x, size.z, BOX_HEIGHT, &centre, object->angle, &scale);
    }
    u8 index = (u8) func_ov004_0223cd78(func_ov004_0223ce84(), object);
    size.x = FX_MulFunc(size.x, SHADOW_SHRINK);
    size.z = FX_MulFunc(size.z, SHADOW_SHRINK);
    int flags = shadow_flags();
    func_020b7dc8(func_020b6590(), object->shadow, &centre, size.x, size.z, size.y, object->angle, flags, index);
}
CLEAN_AS(func_ov004_0220f9c8, RoomObject_SetUpBoxAndShadow)

/* func_ov004_0220faac: the object's size by footprint (one cell, two, or 2x2), its height
 * what stands on it (halved unless func_ov004_0223d348 says so), or 0x200 when that is 0.
 * QUIRK: the first call builds the three function-local static sizes and registers them for
 * destruction (func_020012dc, which does nothing); func_020b65c4 is called and not used. */
void RoomObject_Size(RoomObject *object, Vec3 *size)
{
    if ((data_ov004_02256c70 & 1) == 0) {
        set_vec(&data_ov004_02256e58[0], 0x2000, 0x2000, 0x2000);
        __register_global_object(&data_ov004_02256e58[0], (void *) func_020012dc, data_ov004_02256de0);
        set_vec(&data_ov004_02256e64, 0x4000, 0x2000, 0x2000);
        __register_global_object(&data_ov004_02256e64, (void *) func_020012dc, data_ov004_02256dec);
        set_vec(&data_ov004_02256e70, 0x4000, 0x2000, 0x4000);
        __register_global_object(&data_ov004_02256e70, (void *) func_020012dc, data_ov004_02256df8);
        data_ov004_02256c70 |= 1;
    }
    func_020b65c4();
    Vec3 result = data_ov004_02256e58[object->unk_784];
    if (object->top_height == 0) {
        result.y = 0x200;
    } else if (func_ov004_0223d348() != 0) {
        result.y = object->top_height;
    } else {
        result.y = shift_right(object->top_height, 1);
    }
    *size = result;
}
CLEAN_AS(func_ov004_0220faac, RoomObject_Size)

/* func_ov004_0220fb90: the object's matrices: `matrix` is its place for drawing, and
 * base_matrix its place about its pivot (RoomObject_BuildMatrix). An object two cells long is
 * drawn moved along X by 1 less its scale. A preview is turned by the angles RoomObject_SetUp
 * set, moved back along X by its scale when it is two cells long, and raised by 100 times
 * func_02053658 of its number, less 600. Both leave the matrix in data_021fbe48. */
void RoomObject_UpdateMatrices(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        Mtx43_Translation(&data_021fbe48, object->position.x, object->position.y, object->position.z);
        Mtx43_RotateX(&data_021fbe48, (s16) data_ov004_02256c40);
        Mtx43_RotateY(&data_021fbe48, (s16) (object->angle + (s16) data_ov004_02256c3c));
        if (object->unk_784 == FOOTPRINT_TWO) {
            Mtx43_Translate(&data_021fbe48, FX_MulFunc(object->scale_x, -ONE), 0, 0);
        }
        fx32 lift = 100 * func_02053658(RoomObject_Number(object)) - 600;
        Mtx43_Translate(&data_021fbe48, 0, lift, 0);
        object->matrix = data_021fbe48;
    } else {
        RoomObject_BuildMatrix(object, NULL, 0);
        object->base_matrix = data_021fbe48;
        if (object->unk_784 == FOOTPRINT_TWO) {
            Mtx43_Translate(&data_021fbe48, FX_MulFunc(ONE - object->scale_x, ONE), 0, 0);
        }
        object->matrix = data_021fbe48;
    }
}
CLEAN_AS(func_ov004_0220fb90, RoomObject_UpdateMatrices)

/* func_ov004_0220fc98: builds in data_021fbe48 the object's matrix about its pivot, moved by
 * `offset` and turned by `turn`. On top of another object: that object's matrix (built the
 * same way when moved or turned, else the one it has) then the mount's offset and angle;
 * `offset` and `turn` move the object below. */
void RoomObject_BuildMatrix(RoomObject *object, Vec3 *offset, int turn)
{
    if (Mount_IsSet(&object->mount)) {
        void *objects = func_ov004_0223ce84();
        RoomObject *below = func_ov004_0223cd58(objects, Mount_Parent(&object->mount));
        if (offset != NULL || turn != 0) {
            RoomObject_BuildMatrix(below, offset, turn);
        } else {
            data_021fbe48 = below->base_matrix;
        }
        fx32 z = Mount_Offset(&object->mount)->z;
        fx32 y = Mount_Offset(&object->mount)->y;
        fx32 x = Mount_Offset(&object->mount)->x;
        Mtx43_Translate(&data_021fbe48, x, y, z);
        Mtx43_RotateY(&data_021fbe48, Mount_Angle(&object->mount));
    } else {
        Vec3 position = object->position;
        if (offset != NULL) {
            VEC_Add(&position, offset, &position);
        }
        s16 angle = (s16) (object->angle + turn);
        Mtx43_Translation(&data_021fbe48, position.x, position.y, position.z);
        Mtx43_RotateY(&data_021fbe48, angle);
        Mtx43_Translate(&data_021fbe48, object->pivot.x, object->pivot.y, object->pivot.z);
    }
}
CLEAN_AS(func_ov004_0220fc98, RoomObject_BuildMatrix)

/* func_ov004_0220fd8c: 0 on the floor, 1 on top of another object. */
int RoomObject_Layer(RoomObject *object)
{
    return object->unk_288;
}
CLEAN_AS(func_ov004_0220fd8c, RoomObject_Layer)

/* func_ov004_0220fd98: toggles the switch (to be applied), unless unk_77D; whether it did. */
int RoomObject_ToggleSwitch(RoomObject *object)
{
    if (object->unk_77D == 0) {
        Switch_Toggle(&object->light_switch, 1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220fd98, RoomObject_ToggleSwitch)

/* func_ov004_0220fdc4 (vtable slot 0x74) */
int RoomObject_Vfunc74(void)
{
    return 0;
}
CLEAN_AS(func_ov004_0220fdc4, RoomObject_Vfunc74)

/* func_ov004_0220fdc8 (vtable slot 0x70): sets unk_77C to `value` and clears unk_77D; 1. */
int RoomObject_SetUnk77C(RoomObject *object, int unused, int value)
{
    (void) unused;
    object->unk_77C = (u8) value;
    object->unk_77D = 0;
    return 1;
}
CLEAN_AS(func_ov004_0220fdc8, RoomObject_SetUnk77C)

/* func_ov004_0220fde0: the furniture's number. */
int RoomObject_Number(RoomObject *object)
{
    return object->unk_284;
}
CLEAN_AS(func_ov004_0220fde0, RoomObject_Number)

/* func_ov004_0220fefc: the middle of the object's four corners.
 * QUIRK: each coordinate of the sum is halved twice by a shift, rounding down. */
void RoomObject_Centre(RoomObject *object, Vec3 *centre)
{
    Vec3 sum;
    set_vec(&sum, 0, 0, 0);
    for (int i = 0; i < 4; i++) {
        Vec3 corner;
        RoomObject_Corner(object, &corner, i);
        VEC_Add(&sum, &corner, &sum);
    }
    sum.x = shift_right(sum.x, 2);
    sum.y = shift_right(sum.y, 2);
    sum.z = shift_right(sum.z, 2);
    *centre = sum;
}
CLEAN_AS(func_ov004_0220fefc, RoomObject_Centre)

/* func_ov004_0220ff4c: corner `index` (0 to 3, wrapping) of the object's footprint, in the
 * world. */
void RoomObject_Corner(RoomObject *object, Vec3 *corner, int index)
{
    const Vec3 *corners = (const Vec3 *) (uintptr_t) data_ov004_0224fe10[object->unk_784];
    RoomObject_ToWorld(object, corner, &corners[index & 3]);
}
CLEAN_AS(func_ov004_0220ff4c, RoomObject_Corner)

/* func_ov004_0220ff74: `point`, in the object's space about its pivot, in the world; the
 * matrix is left in data_021fbe48. */
void RoomObject_ToWorld(RoomObject *object, Vec3 *out, const Vec3 *point)
{
    data_021fbe48 = object->base_matrix;
    MTX_MultVec43(point, &data_021fbe48, out);
}
CLEAN_AS(func_ov004_0220ff74, RoomObject_ToWorld)

/* func_ov004_0221081c: func_020537a8 of the furniture's number. */
int RoomObject_Lookup020537a8(RoomObject *object)
{
    return func_020537a8(object->unk_284);
}
CLEAN_AS(func_ov004_0221081c, RoomObject_Lookup020537a8)

/* func_ov004_0221082c (vtable slot 0x78) */
int RoomObject_Unk77C(RoomObject *object)
{
    return object->unk_77C;
}
CLEAN_AS(func_ov004_0221082c, RoomObject_Unk77C)

/* func_ov004_02210838 (vtable slot 0x50): the point one unit before the player, the way the
 * player faces; the object's position without a player.
 * QUIRK: the point is a function-local static, registered for destruction (func_020012dc,
 * which does nothing) on the first call; the result points to it. */
Vec3 *RoomObject_PointBeforePlayer(RoomObject *object)
{
    if ((data_ov004_02256c68 & 1) == 0) {
        __register_global_object(&data_ov004_02256dc8, (void *) func_020012dc, data_ov004_02256dbc);
        data_ov004_02256c68 |= 1;
    }
    data_ov004_02256dc8 = object->position;
    MapActor *player = func_020961a8(PLAYER);
    if (player != NULL) {
        int index = player->angle >> 4;
        data_ov004_02256dc8.x = player->position.x + FX_SinCosTable_[index * 2];
        data_ov004_02256dc8.y = player->position.y;
        data_ov004_02256dc8.z = player->position.z + FX_SinCosTable_[index * 2 + 1];
    }
    return &data_ov004_02256dc8;
}
CLEAN_AS(func_ov004_02210838, RoomObject_PointBeforePlayer)

/* func_ov004_022108b8 (vtable slot 0x9c, each frame of a turn): nothing in the base. */
void RoomObject_OnTurnFrame(void) {}
CLEAN_AS(func_ov004_022108b8, RoomObject_OnTurnFrame)

/* func_ov004_022108bc (vtable slot 0x98, when a turn starts) */
void RoomObject_OnTurnStart(void) {}
CLEAN_AS(func_ov004_022108bc, RoomObject_OnTurnStart)

/* func_ov004_022108c0 (vtable slot 0x94, when a move starts) */
void RoomObject_OnMoveStart(void) {}
CLEAN_AS(func_ov004_022108c0, RoomObject_OnMoveStart)

/* func_ov004_022108c4 (vtable slot 0x90, when it starts to vanish) */
void RoomObject_OnVanish(void) {}
CLEAN_AS(func_ov004_022108c4, RoomObject_OnVanish)

/* func_ov004_022108c8 (vtable slot 0x88) */
int RoomObject_Vfunc88(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022108c8, RoomObject_Vfunc88)

/* func_ov004_022108cc (vtable slot 0x8c) */
int RoomObject_Vfunc8C(void)
{
    return 0;
}
CLEAN_AS(func_ov004_022108cc, RoomObject_Vfunc8C)

/* func_ov004_022108d0 (vtable slot 0x14): with 2, the object leaves: its sound stops, the
 * room's lighting follows (RoomObject_ExitLight), its box goes, its switch is saved unless it
 * is going away (vanishing or shrunk), its model's loading ends and its slot is freed. One that
 * vanishes leaves the map, with an effect towards the player: where func_ov004_0223d348 says so
 * outside areas 17 to 24 and 1 to 5, it leaves item LEFT_BEHIND on the floor at the cell
 * RoomObject_FindVariantCell finds. Then it leaves the room's objects. The base class's slot
 * (func_02003510) runs for every value.
 * BUG: when RoomObject_FindVariantCell finds no cell, the item goes to a cell left from
 * whatever the stack held; here cell (0, 0). */
void RoomObject_Vfunc14(RoomObject *object, int mode)
{
    if (mode == STATE_CHANGE_EXIT) {
        func_ov004_0223cf68(&object->sound);
        RoomObject_ExitLight(object);
        RoomObject_RemoveBox(object);
        if (!RoomObject_IsVanishing(object) && !RoomObject_IsShrunk(object)) {
            Switch_Save(&object->light_switch, object);
        }
        FurnitureModel_EndLoad(&object->model_files);
        func_0209d200(data_ov004_02259698, &object->slot);
        if (RoomObject_IsVanishing(object)) {
            int x = 0;
            int y = 0;
            RoomObject_FindVariantCell(object, &x, &y, NULL, 0);
            int area = func_020b65c4();
            if (func_ov004_0223d348() != 0 && func_020b6694(area) == 0 && func_020b67e8(area) == 0) {
                void *map = data_021c80bc;
                RoomObject_TakeOffMap(object, 0, 0);
                if (map != NULL) {
                    ItemCode item = LEFT_BEHIND;
                    func_0204f538(map, &item, x, y, LAYER_FLOOR);
                }
            } else {
                RoomObject_TakeOffMap(object, 1, 0);
            }
            RoomObject_EffectTowardsPlayer(object);
        }
        func_ov004_0223cde8(func_ov004_0223ce84(), object);
    }
    func_02003510(object, mode);
}
CLEAN_AS(func_ov004_022108d0, RoomObject_Vfunc14)

/* func_ov004_022109cc (vtable slot 0x10): whether func_0203efdc (the base class's slot) did
 * its work. */
int RoomObject_Vfunc10(RoomObject *object)
{
    return func_0203efdc(object) != 0;
}
CLEAN_AS(func_ov004_022109cc, RoomObject_Vfunc10)

/* func_ov004_0221137c: the mode of a placement word (bits 26-27, RoomObject.unk_76C). */
unsigned int Placement_Mode(unsigned int placement)
{
    return (placement >> 26) & 3;
}
CLEAN_AS(func_ov004_0221137c, Placement_Mode)

/* func_ov004_02211388: the furniture's number in a placement word (bits 8-23). */
unsigned int Placement_Number(unsigned int placement)
{
    return PLACE_NUMBER(placement);
}
CLEAN_AS(func_ov004_02211388, Placement_Number)

/* func_ov004_02211394: a placement word from its fields, each cut to its width.
 * BUG: the word is built in an uninitialised stack word and bits 29-31 are never set, so the
 * ROM returns whatever they held; here they are 0. Nothing reads them (room_object_body.h).
 * The ROM also sets a 5-bit field to 1 in the following stack word, which is not returned. */
int Placement_Make(int x, int y, int number, int side, u8 on_top, int mode)
{
    u32 word = ((u32) x & 0xf) | ((u32) y & 0xf) << 4 | ((u32) number & 0xffff) << 8 | ((u32) side & 3) << 24 |
               ((u32) mode & 3) << 26 | ((u32) on_top & 1) << 28;
    return (int) word;
}
CLEAN_AS(func_ov004_02211394, Placement_Make)
