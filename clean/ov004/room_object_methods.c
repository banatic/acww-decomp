/* Methods of the room objects outside their states (room_object_methods.h). */
#include "room_object_methods.h"

#include <assert.h>
#include <stddef.h>

#include "cells.h"
#include "clean.h"
#include "main/item_code.h"
#include "room_object_body.h"

static_assert(offsetof(NodeHookState, unk_B8) == 0xb8, "node hook state");
static_assert(offsetof(NodeHookState, hooks) == 0x0c, "hooks");
static_assert(offsetof(NodeHookState, hook_timings) == 0x8c, "hook timings");
static_assert(offsetof(G3dRenderObject, user) == 0x2c, "render object's user");

#define PLAYER 4             /* the actor func_02095794 is asked for */
#define KIND_NO_ITEM 0x1c    /* unk_780 of an object that is no item of the map */
#define EFFECT_3D 0x3d       /* what func_ov004_0220e61c gives func_02091230 */
#define BLOCK_CELLS 16       /* cells along a block of the town's map */
#define INDEX_BITS 0x1ff     /* a reference by index: the index, 9 bits... */
#define INDEX_TOWN_BITS 0x7f /* ...and the town, 7 bits */
#define CELL_TOWN_BITS 0x3f  /* a reference by cell: the town in 6 bits */

/* The town's map (func_0204f5e0 finds the item on a cell of it). */
extern void *data_021c80bc;
/* The farthest distance there is, to start a search for the nearest. */
extern const fx32 data_020ca0ec;

extern int func_ov004_02211280(RoomObject *object);
extern int func_ov004_02211294(RoomObject *object);
extern int func_ov004_0221132c(RoomObject *object);
extern int func_ov004_0221134c(RoomObject *object);
extern void func_020b3188(NodeHookState *state);
extern void func_020b3220(NodeHookState *state);
extern int func_ov004_0220fde0(RoomObject *object);
extern void func_ov004_0220ff4c(RoomObject *object, Vec3 *corner, int index);
extern void func_ov004_0220fefc(RoomObject *object, Vec3 *centre);
extern int func_02091230(int kind, Vec3 *point, int a2, int a3);
extern Vec3 *func_02095794(int actor);
extern s16 func_0200322c(const Vec3 *from, const Vec3 *to);
extern int func_ov004_0223e7b4(Vec3 *point, u16 *rotation);
extern void func_0204f794(Vec3 *centre, unsigned int x, unsigned int y);
extern ItemCode *func_0204f5e0(void *map, int block_x, int block_y, int x, int y, int layer);
extern int func_020b67ac(void);
extern unsigned char func_020b65c4(void);
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(void *objects, RoomObject *object);

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* func_ov004_0220e504 (vtable slot 0x64): for a node of the node set, its value goes to the
 * word the state points to; the value, or 0 for other nodes. */
int RoomObject_NodeSetHook(RoomObject *object, int node, NodeHookState *state)
{
    if (ByteSet_Contains(&object->node_set, node)) {
        int value = ByteSet_Value(&object->node_set);
        *state->unk_B8 = (u32) value;
        return value;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220e504, RoomObject_NodeSetHook)

/* func_ov004_0220e534 (vtable slot 0x6c): turns the clock's hands, "kh_j" by the hour
 * (func_020b3220) and "km_j" by the minute (func_020b3188), when the model has them. */
void RoomObject_ClockHandsHook(RoomObject *object, int node, NodeHookState *state)
{
    if (object->nodes.found) {
        if (object->nodes.nodes[0] == node) {
            func_020b3220(state);
        } else if (object->nodes.nodes[1] == node) {
            func_020b3188(state);
        }
    }
}
CLEAN_AS(func_ov004_0220e534, RoomObject_ClockHandsHook)

/* func_ov004_0220e570 (vtable slot 0x68): nothing to do. */
void RoomObject_IgnoreHook68(void) {}
CLEAN_AS(func_ov004_0220e570, RoomObject_IgnoreHook68)

/* func_ov004_0220e574 (vtable slot 0x60): nothing to do. */
void RoomObject_IgnoreHook60(void) {}
CLEAN_AS(func_ov004_0220e574, RoomObject_IgnoreHook60)

/* func_ov004_0220e578: the object's item code: its furniture number without a variant, or
 * nothing for the kind that is no item. */
void RoomObject_ItemCode(ItemCode *code, RoomObject *object)
{
    if (object->unk_780 == KIND_NO_ITEM) {
        *code = ITEM_CODE_NONE;
    } else {
        *code = ItemCode_MakeVariant(func_ov004_0220fde0(object), 0);
    }
}
CLEAN_AS(func_ov004_0220e578, RoomObject_ItemCode)

/* func_ov004_0220e5a8: what func_ov004_02211280 says (unk_780 is 0x18). */
int RoomObject_Unk780Is18(RoomObject *object)
{
    return func_ov004_02211280(object);
}
CLEAN_AS(func_ov004_0220e5a8, RoomObject_Unk780Is18)

/* func_ov004_0220e5b0: what func_ov004_02211294 says (unk_00C is 0x36 or 0x37). */
int RoomObject_Unk00CIs36Or37(RoomObject *object)
{
    return func_ov004_02211294(object);
}
CLEAN_AS(func_ov004_0220e5b0, RoomObject_Unk00CIs36Or37)

/* func_ov004_0220e5b8: what func_ov004_0221132c says (unk_00C is 0x3a). */
int RoomObject_Unk00CIs3A(RoomObject *object)
{
    return func_ov004_0221132c(object);
}
CLEAN_AS(func_ov004_0220e5b8, RoomObject_Unk00CIs3A)

/* func_ov004_0220e5c0: what func_ov004_0221134c says (func_02053818 accepts the furniture's
 * number and unk_76C is not 2). */
int RoomObject_Check0221134c(RoomObject *object)
{
    return func_ov004_0221134c(object);
}
CLEAN_AS(func_ov004_0220e5c0, RoomObject_Check0221134c)

/* func_ov004_0220e5c8 */
int RoomObject_Unk76CIs2(const RoomObject *object)
{
    return object->unk_76C == 2;
}
CLEAN_AS(func_ov004_0220e5c8, RoomObject_Unk76CIs2)

/* func_ov004_0220e5dc: the effect of RoomObject_Effect3dAt halfway between corner `corner`
 * (func_ov004_0220ff4c) and the centre of the object, at the object's height. */
void RoomObject_EffectNearCorner(RoomObject *object, int corner)
{
    Vec3 at_corner;
    Vec3 centre;
    func_ov004_0220ff4c(object, &at_corner, corner);
    func_ov004_0220fefc(object, &centre);
    Vec3 point;
    point.x = shift_right(at_corner.x + centre.x, 1);
    point.y = object->position.y;
    point.z = shift_right(at_corner.z + centre.z, 1);
    RoomObject_Effect3dAt(object, &point);
}
CLEAN_AS(func_ov004_0220e5dc, RoomObject_EffectNearCorner)

/* func_ov004_0220e61c: func_02091230 with EFFECT_3D at a copy of `point`. */
int RoomObject_Effect3dAt(RoomObject *object, const Vec3 *point)
{
    (void) object;
    Vec3 copy = *point;
    return func_02091230(EFFECT_3D, &copy, 0, 0);
}
CLEAN_AS(func_ov004_0220e61c, RoomObject_Effect3dAt)

/* func_ov004_0220e640: the effect of RoomEffect_SpawnC0 at the object's centre, turned towards
 * the player; 0 without a player. */
int RoomObject_EffectTowardsPlayer(RoomObject *object)
{
    Vec3 *player = func_02095794(PLAYER);
    if (player == NULL) {
        return 0;
    }
    Vec3 centre;
    func_ov004_0220fefc(object, &centre);
    return RoomEffect_SpawnC0(&centre, func_0200322c(&centre, player));
}
CLEAN_AS(func_ov004_0220e640, RoomObject_EffectTowardsPlayer)

/* func_ov004_0220e674: the effect of RoomEffect_SpawnC0 at the centre of the object's cell
 * farthest from the player (nearest unless `farthest`), turned towards the player.
 * QUIRK: the farthest cell is searched from distance 0 and the nearest from data_020ca0ec, by
 * strict comparisons: on equal distances the first cell wins. */
void RoomObject_EffectAtCellTowardsPlayer(RoomObject *object, int farthest)
{
    Vec3 *player = func_02095794(PLAYER);
    if (player == NULL) {
        return;
    }
    CellList cells;
    CellList_Construct(&cells);
    func_ov004_0220f27c(object, &cells, NULL, 0);
    fx32 far_distance = 0;
    int far_index = -1;
    int near_index = -1;
    fx32 near_distance = data_020ca0ec;
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        int x = CellList_At(&cells, (int) i)->x;
        int y = CellList_At(&cells, (int) i)->y;
        Vec3 centre;
        func_0204f794(&centre, (unsigned int) x, (unsigned int) y);
        fx32 distance = Vec_DistanceXZ(player, &centre);
        if (distance > far_distance) {
            far_index = (int) i;
            far_distance = distance;
        }
        if (distance < near_distance) {
            near_index = (int) i;
            near_distance = distance;
        }
    }
    int chosen = farthest ? far_index : near_index;
    if (chosen != -1) {
        int x = CellList_At(&cells, chosen)->x;
        int y = CellList_At(&cells, chosen)->y;
        Vec3 centre;
        func_0204f794(&centre, (unsigned int) x, (unsigned int) y);
        RoomEffect_SpawnC0(&centre, func_0200322c(&centre, player));
    }
    CellList_Destruct(&cells);
}
CLEAN_AS(func_ov004_0220e674, RoomObject_EffectAtCellTowardsPlayer)

/* func_ov004_0220e73c: effect 0xc0 at `point`, turned by `angle` about the vertical axis
 * (func_ov004_0223e7b4, which runs up to three at once); whether it started. */
int RoomEffect_SpawnC0(Vec3 *point, int angle)
{
    u16 rotation[3] = {0, (u16) angle, 0};
    return func_ov004_0223e7b4(point, rotation);
}
CLEAN_AS(func_ov004_0220e73c, RoomEffect_SpawnC0)

/* func_ov004_0220e758: the first of the cells the object would cover (moved by `offset` and
 * turned by `turn`, func_ov004_0220f27c) where the town's map holds, on the object's layer, an
 * item code with a variant; whether there is one. */
int RoomObject_FindVariantCell(RoomObject *object, int *x, int *y, Vec3 *offset, s16 turn)
{
    CellList cells;
    CellList_Construct(&cells);
    func_ov004_0220f27c(object, &cells, offset, turn);
    void *map = data_021c80bc;
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        int layer = object->unk_288;
        s32 cell_y = CellList_At(&cells, (int) i)->y;
        s32 cell_x = CellList_At(&cells, (int) i)->x;
        ItemCode *item = func_0204f5e0(map, shift_right(cell_x, 4), shift_right(cell_y, 4), cell_x & (BLOCK_CELLS - 1),
                                       cell_y & (BLOCK_CELLS - 1), layer);
        if (item != NULL && ItemCode_HasVariant(item)) {
            *x = CellList_At(&cells, (int) i)->x;
            *y = CellList_At(&cells, (int) i)->y;
            CellList_Destruct(&cells);
            return 1;
        }
    }
    CellList_Destruct(&cells);
    return 0;
}
CLEAN_AS(func_ov004_0220e758, RoomObject_FindVariantCell)

/* func_ov004_0220e808: the object's reference. When func_020b67ac says so or unk_76C is 2: its
 * index among the room's objects (bits 0-8) and the town (func_020b65c4, bits 9-15). Else, by
 * the cell RoomObject_FindVariantCell finds: x and y within their block (bits 0-3 and 4-7),
 * the object's layer (bit 8) and the town (bits 9-14); 0 when there is none.
 * BUG: bit 15 of a reference by cell is left from whatever the stack held; here it is 0. */
u16 RoomObject_Reference(RoomObject *object, Vec3 *offset, int turn)
{
    if (func_020b67ac() != 0 || RoomObject_Unk76CIs2(object)) {
        int index = func_ov004_0223cd78(func_ov004_0223ce84(), object);
        u16 reference = (u16) (index & INDEX_BITS);
        reference |= (u16) ((func_020b65c4() & INDEX_TOWN_BITS) << 9);
        return reference;
    }
    int x;
    int y;
    if (RoomObject_FindVariantCell(object, &x, &y, offset, (s16) turn) != 0) {
        u16 reference = (u16) (x & (BLOCK_CELLS - 1));
        reference |= (u16) ((y & (BLOCK_CELLS - 1)) << 4);
        reference |= (u16) ((object->unk_288 & 1) << 8);
        reference |= (u16) ((func_020b65c4() & CELL_TOWN_BITS) << 9);
        return reference;
    }
    return 0;
}
CLEAN_AS(func_ov004_0220e808, RoomObject_Reference)

/* The kinds (RoomObject.unk_780 and unk_00C) the questions below ask about. */
#define KIND_780_10 0x10
#define KIND_780_11 0x11
#define KIND_780_18 0x18
#define KIND_780_2B 0x2b
#define KIND_00C_36 0x36
#define KIND_00C_37 0x37
#define KIND_00C_3A 0x3a
#define KIND_00C_3B 0x3b
#define KIND_00C_3C 0x3c

/* The value func_ov004_0223a730 gives for none (0xffff). */
extern const u16 data_ov004_0224fd38;
extern int func_ov004_0223a730(int number);
extern int func_02053818(int number);

/* Whether the object is neither appearing nor vanishing. */
static int is_settled(const RoomObject *object)
{
    return !RoomObject_IsInState(object, ROOM_OBJECT_APPEAR) && !RoomObject_IsInState(object, ROOM_OBJECT_VANISH);
}

/* func_ov004_022111f0: for an object neither appearing nor vanishing, whether its unk_780 is
 * 0x10, or is 0x11 or 0x2b and func_ov004_0223a730 has a value for its furniture's number.
 * func_ov004_0223bf40 looks for the nearest such object to the player. */
int RoomObject_Check022111f0(RoomObject *object)
{
    if (!is_settled(object)) {
        return 0;
    }
    switch (object->unk_780) {
        case KIND_780_10:
            return 1;
        case KIND_780_11:
        case KIND_780_2B:
            return func_ov004_0223a730(RoomObject_Number(object)) != data_ov004_0224fd38;
    }
    return 0;
}
CLEAN_AS(func_ov004_022111f0, RoomObject_Check022111f0)

/* func_ov004_0221124c: for an object neither appearing nor vanishing, whether its unk_780 is
 * 0x10. */
int RoomObject_SettledUnk780Is10(RoomObject *object)
{
    return is_settled(object) && object->unk_780 == KIND_780_10;
}
CLEAN_AS(func_ov004_0221124c, RoomObject_SettledUnk780Is10)

/* func_ov004_02211280: whether unk_780 is 0x18 (RoomObject_Unk780Is18 asks through it). */
int RoomObject_TestUnk780Is18(const RoomObject *object)
{
    return object->unk_780 == KIND_780_18;
}
CLEAN_AS(func_ov004_02211280, RoomObject_TestUnk780Is18)

/* func_ov004_02211294: whether unk_00C is 0x36 or 0x37 (RoomObject_Unk00CIs36Or37 asks through
 * it). */
int RoomObject_TestUnk00CIs36Or37(const RoomObject *object)
{
    return object->unk_00C == KIND_00C_36 || object->unk_00C == KIND_00C_37;
}
CLEAN_AS(func_ov004_02211294, RoomObject_TestUnk00CIs36Or37)

/* func_ov004_022112c4: whether unk_00C is 0x3b or 0x3c and the switch is on (wanted on).
 * func_ov004_0223bdac looks for the nearest such object to the player. */
int RoomObject_Unk00CIs3BOr3CAndOn(RoomObject *object)
{
    if (object->unk_00C != KIND_00C_3B && object->unk_00C != KIND_00C_3C) {
        return 0;
    }
    return Switch_Value(&object->light_switch) != 0;
}
CLEAN_AS(func_ov004_022112c4, RoomObject_Unk00CIs3BOr3CAndOn)

/* func_ov004_02211308: whether unk_00C is 0x3a (RoomObject_TestUnk00CIs3A) and then the
 * switch's wanted value. */
int RoomObject_Unk00CIs3AAndOn(RoomObject *object)
{
    if (RoomObject_TestUnk00CIs3A(object)) {
        return Switch_Value(&object->light_switch);
    }
    return 0;
}
CLEAN_AS(func_ov004_02211308, RoomObject_Unk00CIs3AAndOn)

/* func_ov004_0221132c: whether `object` (or NULL) has unk_00C 0x3a (RoomObject_Unk00CIs3A asks
 * through it). */
int RoomObject_TestUnk00CIs3A(const RoomObject *object)
{
    return object != NULL && object->unk_00C == KIND_00C_3A;
}
CLEAN_AS(func_ov004_0221132c, RoomObject_TestUnk00CIs3A)

/* func_ov004_0221134c: whether `object` (or NULL) is a light: func_02053818 accepts its
 * furniture's number and it is not a preview (RoomObject_Unk76CIs2). The lights' code
 * (room_object_light.c) hands this function to func_ov004_0223c264 to count the lights. */
int RoomObject_IsLight(RoomObject *object)
{
    if (object == NULL) {
        return 0;
    }
    return func_02053818(RoomObject_Number(object)) != 0 && !RoomObject_Unk76CIs2(object);
}
CLEAN_AS(func_ov004_0221134c, RoomObject_IsLight)

/* The hooks a room object's model runs while it is drawn (set up by RoomObject_SetModelHooks).
 * Each passes byte 1 of the command (the node or material) and the render state to a slot of
 * the room object's vtable; nothing without a room object. */
static RoomObject *hooked_object(const NodeHookState *state)
{
    return state->render_object->user;
}

extern int func_ov004_02211480(NodeHookState *state);
extern void func_ov004_022114a0(NodeHookState *state);
extern void func_ov004_022114cc(NodeHookState *state);
extern int func_ov004_022114f8(NodeHookState *state);

/* The hooks are the game's functions: their addresses go into the render state. */
#define HOOK(function) ((u32) (uintptr_t) (function))

static void set_hook(NodeHookState *state, int command, u32 hook, u8 timing)
{
    state->hooks[command] = hook;
    state->hook_timings[command] = timing;
}

/* func_ov004_02211450 (the hook func_02055dc8 is given, run before the model is drawn): sets the
 * hooks for materials (after), nodes (after) and nodes' descriptions (before). */
void RoomObject_SetModelHooks(NodeHookState *state)
{
    set_hook(state, G3D_COMMAND_MATERIAL, HOOK(func_ov004_022114f8), G3D_TIMING_AFTER);
    set_hook(state, G3D_COMMAND_NODE, HOOK(func_ov004_02211480), G3D_TIMING_AFTER);
    set_hook(state, G3D_COMMAND_NODE_DESC, HOOK(func_ov004_022114cc), G3D_TIMING_BEFORE);
}
CLEAN_AS(func_ov004_02211450, RoomObject_SetModelHooks)

/* func_ov004_02211480: a node's hook (vtable slot 0x64); its result, or 0 without an object. */
int RoomObject_RunNodeHook(NodeHookState *state)
{
    RoomObject *object = hooked_object(state);
    if (object == NULL) {
        return 0;
    }
    return object->vtable->node_hook(object, state->command[1], state);
}
CLEAN_AS(func_ov004_02211480, RoomObject_RunNodeHook)

/* func_ov004_022114a0: after a node's description, its hook (vtable slot 0x6c); then the hook
 * before the next description is set back. */
void RoomObject_RunNodeDescAfterHook(NodeHookState *state)
{
    RoomObject *object = hooked_object(state);
    if (object != NULL) {
        object->vtable->node_desc_after_hook(object, state->command[1], state);
    }
    set_hook(state, G3D_COMMAND_NODE_DESC, HOOK(func_ov004_022114cc), G3D_TIMING_BEFORE);
}
CLEAN_AS(func_ov004_022114a0, RoomObject_RunNodeDescAfterHook)

/* func_ov004_022114cc: before a node's description, its hook (vtable slot 0x68); then the hook
 * after it is set. */
void RoomObject_RunNodeDescHook(NodeHookState *state)
{
    RoomObject *object = hooked_object(state);
    if (object != NULL) {
        object->vtable->node_desc_hook(object, state->command[1], state);
    }
    set_hook(state, G3D_COMMAND_NODE_DESC, HOOK(func_ov004_022114a0), G3D_TIMING_AFTER);
}
CLEAN_AS(func_ov004_022114cc, RoomObject_RunNodeDescHook)

/* func_ov004_022114f8: a material's hook (vtable slot 0x60); its result, or 0 without an
 * object. */
int RoomObject_RunMaterialHook(NodeHookState *state)
{
    RoomObject *object = hooked_object(state);
    if (object == NULL) {
        return 0;
    }
    return object->vtable->material_hook(object, state->command[1], state);
}
CLEAN_AS(func_ov004_022114f8, RoomObject_RunMaterialHook)
