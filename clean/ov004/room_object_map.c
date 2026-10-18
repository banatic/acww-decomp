/* A room object on the town's map (room_object_map.h). */
#include "room_object_map.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/fx_math.h"
#include "autoload_2/vector.h"
#include "cells.h"
#include "clean.h"
#include "main/item_code.h"
#include "room_object_body.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/collision_map.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/room_sync.h"
#include "main/scene_kinds.h"
#include "main/scene_object_base.h"
#include "main/scene_query.h"
#include "main/session_players.h"
#include "main/unit_type_info.h"
#include "room_manager.h"
#include "room_objects.h"

static_assert(offsetof(RoomObject, placement) == 0x8, "placement");
static_assert(offsetof(RoomObject, slot) == 0x132, "slot");
static_assert(offsetof(RoomObject, item_shadows) == 0x1d0, "item shadows");
static_assert(offsetof(RoomObject, base_matrix) == 0x254, "base matrix");
static_assert(offsetof(RoomObject, is_set_up) == 0x289, "set up");
static_assert(offsetof(RoomObject, shadow) == 0x28c, "shadow");
static_assert(offsetof(RoomObject, model_resource) == 0x594, "model resource");
static_assert(offsetof(RoomObject, joint_frame) == 0x5dc, "joint frame");
static_assert(offsetof(RoomObject, unk_774) == 0x774, "unk_774");
static_assert(offsetof(RoomObject, unk_77C) == 0x77c, "unk_77C");
static_assert(offsetof(RoomObject, light_kind) == 0x794, "light kind");
static_assert(offsetof(RoomObject, sound) == 0x798, "sound");
static_assert(offsetof(RoomObject, anims) == 0x7c4, "anims");
static_assert(offsetof(RoomObjectVtable, vfunc_78) == 0x78, "vtable slot 0x78");
static_assert(offsetof(MapActor, angle) == 0x8e, "actor angle");
static_assert(offsetof(PushBox, base.active) == 0x98, "push box active");
static_assert(offsetof(FurnitureAnim, base.ctrl.frame) == 0x08, "anim frame");

#define PLAYER 4            /* the actor SessionPlayers_ActorOf is asked for: the one played here */
#define OTHER_PLAYERS 4     /* actors 0 to 3 */
#define LAYER_FLOOR 0       /* RoomObject.unk_288: on the floor */
#define LAYER_ON_TOP 1      /* standing on another object */
#define BLOCK_CELLS 16      /* cells along a block of the town's map */
#define CELL 0x2000         /* the width of a cell, 20.12 fixed point */
#define HALF_CELL 0x1000    /* half of it */
#define NO_ACTOR (-1)       /* func_02030890 finds no one on the point */
#define CARRIES_ITEMS 1     /* RoomObject.unk_788: the objects on its cells move with it */
#define FOOTPRINT_ONE 0     /* RoomObject.unk_784: one cell */
#define FOOTPRINT_TWO 1     /* two cells along its X axis */
#define ANGLE_SIDE_1 0x2000 /* the sides of Angle_Side start here... */
#define ANGLE_SIDE_2 0x6000
#define ANGLE_SIDE_3 0xa000
#define ANGLE_SIDE_0 0xe000 /* ...and side 0 wraps round 0 */

/* The town's map (AcreTile_ItemInAcre finds the item on a cell of it). */
extern void *data_021c80bc;
/* The scratch matrix of overlay 4's objects. */
extern Mtx43 data_021fbe48;

/* The function-local statics of RoomObject_PutOnMap: two guards, the vectors and their records
 * in the C++ runtime's list of objects to destroy. */
extern u32 data_ov004_02256c50;
extern u32 data_ov004_02256c88;
extern Vec3 data_ov004_02256cb4; /* (0, 0, 0) */
extern Vec3 data_ov004_02256cd8; /* (0, 0, 1) */
extern u8 data_ov004_02256ca8[];
extern u8 data_ov004_02256ccc[];
/* The function-local statics of RoomObject_ListCells. */
extern u32 data_ov004_02256c78;
extern u32 data_ov004_02256c54;
extern Vec3 data_ov004_02256e10[2]; /* the centres of the two cells: (0, 0, 0) and (CELL, 0, 0) */
extern Vec3 data_ov004_02256e1c;    /* the second of them */
extern Vec3 data_ov004_02256c9c;    /* the centre of one cell: (0, 0, 0) */
extern u8 data_ov004_02256e04[];
extern u8 data_ov004_02256d14[];
extern u8 data_ov004_02256c90[];

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020012dc(void *object);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* An arithmetic shift right, for negative values too. */
static s32 shift_right(s32 value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* The item the town's map holds on cell (x, y) of `layer`, or none. */
static ItemCode *map_item(void *map, int x, int y, int layer)
{
    return AcreTile_ItemInAcre(map, shift_right(x, 4), shift_right(y, 4), x & (BLOCK_CELLS - 1), y & (BLOCK_CELLS - 1), layer);
}

static void set_vec(Vec3 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* func_ov004_0220e8f0: whether the object may move by `offset`, or else turn by `turn`. Not
 * when unk_77D is set, when SceneKinds_CurrentIsHouseRoom or Room_Check0220fed0 say no, when it stands on
 * another object, without the town's map or the player, or when CarriedItems_CellsAreClear
 * says no. Else it is taken off the map for the test, and each cell it would cover must hold no
 * item on the floor, pass UnitTypeInfo_Byte04At and have no object on top that is not idle. Without
 * `offset`, a cell may not be the player's, and the cells at half the turn must hold no item on
 * the floor either. With `turn` 0, the player's position moved by `offset` must hold no other
 * object (but one with unk_78C), CollisionMap_UnclaimedObjectAtPoint must find nothing there (-1) and
 * RoomObjects_HeightAtPoint must give 0.
 * QUIRK: the tests on the player's position are made again for each cell. The object is put
 * back on the map (without its reference) either way. */
int RoomObject_CanMoveOrTurn(RoomObject *object, Vec3 *offset, int turn)
{
    if (object->unk_77D) {
        return 0;
    }
    if (!SceneKinds_CurrentIsHouseRoom()) {
        return 0;
    }
    if (!Room_Check0220fed0()) {
        return 0;
    }
    void *map = data_021c80bc;
    MapActor *player = SessionPlayers_ActorOf(PLAYER);
    if (object->unk_288 == LAYER_ON_TOP) {
        return 0;
    }
    if (map == NULL || player == NULL) {
        return 0;
    }
    if (!CarriedItems_CellsAreClear(&object->carried, object)) {
        return 0;
    }

    Vec3 start = player->position;
    int start_x;
    int start_y;
    Position_Tile(&start_x, &start_y, (const Position *) (const void *) &start);
    Vec3 destination = start;
    if (offset != NULL) {
        VEC_Add(&destination, offset, &destination);
    }
    int destination_x;
    int destination_y;
    Position_Tile(&destination_x, &destination_y, (const Position *) (const void *) &destination);
    RoomObject *in_the_way = RoomObjects_GridObjectAt(RoomObjects_Grid(), destination_x, destination_y, LAYER_FLOOR);

    RoomObject_TakeOffMap(object, 0, 0);
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, offset, turn);
    CellList half_cells;
    CellList_Construct(&half_cells);
    RoomObject_ListCells(object, &half_cells, offset, shift_right(turn, 1));

    int free = 1;
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        int x = CellList_At(&cells, (int) i)->x;
        int y = CellList_At(&cells, (int) i)->y;
        ItemCode *item = map_item(map, x, y, LAYER_FLOOR);
        if (offset == NULL && start_x == x && start_y == y) {
            free = 0;
            break;
        }
        if (offset == NULL) {
            int half_y = CellList_At(&half_cells, (int) i)->y;
            int half_x = CellList_At(&half_cells, (int) i)->x;
            ItemCode *swept = map_item(map, half_x, half_y, LAYER_FLOOR);
            if (swept != NULL && *swept != ITEM_CODE_NONE) {
                free = 0;
                break;
            }
        }
        if (item != NULL && *item != ITEM_CODE_NONE) {
            free = 0;
            break;
        }
        if (!UnitTypeInfo_Byte04At(x, y)) {
            free = 0;
            break;
        }
        RoomObject *on_top = RoomObjects_GridObjectAt(RoomObjects_Grid(), x, y, LAYER_ON_TOP);
        if (on_top != NULL && RoomObject_IsNotIdle(on_top)) {
            free = 0;
            break;
        }
        if (turn == 0) {
            if ((in_the_way != NULL && !in_the_way->unk_78C && in_the_way != object) ||
                CollisionMap_UnclaimedObjectAtPoint(&destination) != NO_ACTOR || RoomObjects_HeightAtPoint(&destination)) {
                free = 0;
                break;
            }
        }
    }
    RoomObject_PutOnMap(object, 0, NULL, 0, 0);
    CellList_Destruct(&half_cells);
    CellList_Destruct(&cells);
    return free;
}
CLEAN_AS(func_ov004_0220e8f0, RoomObject_CanMoveOrTurn)

/* func_ov004_0220ebd4 */
int RoomObject_CanMove(RoomObject *object, Vec3 *offset)
{
    return RoomObject_CanMoveOrTurn(object, offset, 0);
}
CLEAN_AS(func_ov004_0220ebd4, RoomObject_CanMove)

/* func_ov004_0220ebe0 */
int RoomObject_CanTurn(RoomObject *object, int turn)
{
    return RoomObject_CanMoveOrTurn(object, NULL, turn);
}
CLEAN_AS(func_ov004_0220ebe0, RoomObject_CanTurn)

/* func_ov004_0220ebec: whether an object on the floor that carries what stands on it holds an
 * item on one of its cells (layer 1 of the town's map). */
int RoomObject_HasItemsOnTop(RoomObject *object)
{
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, NULL, 0);
    void *map = data_021c80bc;
    int found = 0;
    if (object->unk_288 == LAYER_FLOOR && object->unk_788 == CARRIES_ITEMS) {
        for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
            int y = CellList_At(&cells, (int) i)->y;
            int x = CellList_At(&cells, (int) i)->x;
            ItemCode *item = map_item(map, x, y, LAYER_ON_TOP);
            if (item != NULL && *item != ITEM_CODE_NONE) {
                found = 1;
                break;
            }
        }
    }
    CellList_Destruct(&cells);
    return found;
}
CLEAN_AS(func_ov004_0220ebec, RoomObject_HasItemsOnTop)

/* func_ov004_0220ee90: moves the object on the map by `offset` and `turn` from where it is,
 * with the objects standing on its cells: all are taken off the map, then put back moved, with
 * new references. */
void RoomObject_MoveOnMap(RoomObject *object, Vec3 *offset, int turn)
{
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, NULL, 0);
    ObjectSet on_top;
    ObjectSet_Construct(&on_top, &cells, object->unk_288);
    RoomObject_TakeOffMap(object, 1, 1);
    RoomObject_PutOnMap(object, 1, offset, turn, 1);
    for (unsigned long i = 0; i < ObjectSet_Count(&on_top); i++) {
        RoomObject *other = ObjectSet_At(&on_top, (int) i);
        if (other != NULL) {
            RoomObject_PutOnMap(other, 1, offset, turn, 1);
        }
    }
    ObjectSet_Destruct(&on_top);
    CellList_Destruct(&cells);
}
CLEAN_AS(func_ov004_0220ee90, RoomObject_MoveOnMap)

/* func_ov004_0220ef14: puts the object on the map as it would be moved by `offset` and turned
 * by `turn`: its item code, with the side it faces as variant, goes into the map's record at
 * its first cell (RoomSync_PutFurniture), and the object into the room's grid at each of its cells.
 * With `update_reference`, its reference (RoomObject_Reference) is kept when it changed. An
 * object on top of another faces the way the matrix RoomObject_ListCells left says. Nothing
 * for a preview (unk_76C 2).
 * QUIRK: the first call on top of another object builds two function-local static vectors and
 * registers them for destruction (TrivialObject_Destruct, which does nothing). */
void RoomObject_PutOnMap(RoomObject *object, int unused, Vec3 *offset, int turn, u8 update_reference)
{
    (void) unused;
    if (RoomObject_Unk76CIs2(object)) {
        return;
    }
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, offset, turn);

    ItemCode code;
    if (object->unk_288 == LAYER_ON_TOP) {
        if ((data_ov004_02256c50 & 1) == 0) {
            set_vec(&data_ov004_02256cb4, 0, 0, 0);
            __register_global_object(&data_ov004_02256cb4, (void *) func_020012dc, data_ov004_02256ca8);
            data_ov004_02256c50 |= 1;
        }
        if ((data_ov004_02256c88 & 1) == 0) {
            set_vec(&data_ov004_02256cd8, 0, 0, HALF_CELL);
            __register_global_object(&data_ov004_02256cd8, (void *) func_020012dc, data_ov004_02256ccc);
            data_ov004_02256c88 |= 1;
        }
        Vec3 origin;
        Vec3 forward;
        MTX_MultVec43(&data_ov004_02256cb4, &data_021fbe48, &origin);
        MTX_MultVec43(&data_ov004_02256cd8, &data_021fbe48, &forward);
        RoomObject_FacingItemCode(&code, object, Math_Atan2(forward.x - origin.x, forward.z - origin.z));
    } else {
        RoomObject_FacingItemCode(&code, object, (s16) (object->angle + turn));
    }
    SceneQuery_Current();
    RoomManager_ShopMode();
    int option = object->is_set_up ? RoomObject_Unk780Is18(object) : 0;
    int kind = object->vtable->vfunc_78(object);

    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        if (i == 0) {
            int on = Switch_Value(&object->light_switch);
            int town = SceneQuery_Current();
            int x = CellList_At(&cells, (int) i)->x;
            int y = CellList_At(&cells, (int) i)->y;
            RoomSync_PutFurniture(town, x, y, object->unk_288, on, option, kind, &code, 1);
        }
        void *grid = RoomObjects_Grid();
        int x = CellList_At(&cells, (int) i)->x;
        int y = CellList_At(&cells, (int) i)->y;
        RoomObjects_GridSetCell(grid, object, x, y, object->unk_288);
    }
    if (update_reference) {
        u16 reference = RoomObject_Reference(object, offset, turn);
        if (reference != SceneObjectBase_Id(&object->scene)) {
            SceneObjectBase_SetId(&object->scene, reference);
        }
    }
    CellList_Destruct(&cells);
}
CLEAN_AS(func_ov004_0220ef14, RoomObject_PutOnMap)

/* func_ov004_0220f100: takes the object off the map: its item code out of the map's record
 * (RoomSync_TakeFurniture, with `with_top` and `flag`) at each cell where the map holds an item with a
 * variant, and the object out of the room's grid at each cell. With `with_top`, an object on
 * the floor also leaves the grid's layer 1 where that holds one. Nothing for a preview. */
void RoomObject_TakeOffMap(RoomObject *object, u8 flag, int with_top)
{
    if (RoomObject_Unk76CIs2(object)) {
        return;
    }
    CellList cells;
    CellList_Construct(&cells);
    RoomObject_ListCells(object, &cells, NULL, 0);
    void *map = data_021c80bc;
    SceneQuery_Current();
    RoomManager_ShopMode();
    for (unsigned long i = 0; i < CellList_Count(&cells); i++) {
        int x = CellList_At(&cells, (int) i)->x;
        int y = CellList_At(&cells, (int) i)->y;
        ItemCode *item = map_item(map, x, y, object->unk_288);
        if (item != NULL && ItemCode_HasVariant(item)) {
            int town = SceneQuery_Current();
            RoomSync_TakeFurniture(town, x, y, object->unk_288, Switch_Value(&object->light_switch), item, with_top, flag);
        }
        RoomObjects_GridClearCell(RoomObjects_Grid(), object, x, y, object->unk_288);
        if (with_top && object->unk_288 == LAYER_FLOOR &&
            RoomObjects_GridIndexAt(RoomObjects_Grid(), x, y, LAYER_ON_TOP) != -1) {
            RoomObjects_GridClearCell(RoomObjects_Grid(), object, x, y, LAYER_ON_TOP);
        }
    }
    CellList_Destruct(&cells);
}
CLEAN_AS(func_ov004_0220f100, RoomObject_TakeOffMap)

/* func_ov004_0220f218: the object's item code with the side `angle` faces as its variant, into
 * `code` and as the result. */
int RoomObject_FacingItemCode(ItemCode *code, RoomObject *object, int angle)
{
    int side = Angle_Side(angle);
    u16 value = ItemCode_MakeVariant(object->unk_284, side);
    *code = value;
    return value;
}
CLEAN_AS(func_ov004_0220f218, RoomObject_FacingItemCode)

/* func_ov004_0220f240: the quarter turn the 16-bit angle is nearest: 0 round 0, 1 round 0x4000,
 * 2 round 0x8000 and 3 round 0xc000; the bounds go to the higher quarter. */
int Angle_Side(int angle)
{
    u16 a = (u16) angle;
    if (a >= ANGLE_SIDE_0 || a < ANGLE_SIDE_1) {
        return 0;
    }
    if (a < ANGLE_SIDE_2) {
        return 1;
    }
    if (a < ANGLE_SIDE_3) {
        return 2;
    }
    return 3;
}
CLEAN_AS(func_ov004_0220f240, Angle_Side)

/* func_ov004_0220f27c: adds to `cells` the cells the object covers when moved by `offset` and
 * turned by `turn`: one cell, or two along its X axis, through its matrix (RoomObject_BuildMatrix,
 * or the one it has when neither is asked for, which stays in data_021fbe48); else the 2x2
 * cells round its position, where `turn` does not matter.
 * QUIRK: the first calls build three function-local static vectors and register them for
 * destruction (TrivialObject_Destruct, which does nothing). */
void RoomObject_ListCells(RoomObject *object, CellList *cells, Vec3 *offset, int turn)
{
    Vec3 position = object->position;
    if (offset != NULL) {
        VEC_Add(&position, offset, &position);
    }
    if ((data_ov004_02256c78 & 1) == 0) {
        set_vec(&data_ov004_02256e10[0], 0, 0, 0);
        __register_global_object(&data_ov004_02256e10[0], (void *) func_020012dc, data_ov004_02256e04);
        set_vec(&data_ov004_02256e1c, CELL, 0, 0);
        __register_global_object(&data_ov004_02256e1c, (void *) func_020012dc, data_ov004_02256d14);
        data_ov004_02256c78 |= 1;
    }
    Vec3 point = position;
    int x;
    int y;
    switch (object->unk_784) {
        case FOOTPRINT_ONE:
            if (offset != NULL || turn != 0) {
                RoomObject_BuildMatrix(object, offset, turn);
            } else {
                data_021fbe48 = object->base_matrix;
            }
            if ((data_ov004_02256c54 & 1) == 0) {
                set_vec(&data_ov004_02256c9c, 0, 0, 0);
                __register_global_object(&data_ov004_02256c9c, (void *) func_020012dc, data_ov004_02256c90);
                data_ov004_02256c54 |= 1;
            }
            MTX_MultVec43(&data_ov004_02256c9c, &data_021fbe48, &point);
            Position_Tile(&x, &y, (const Position *) (const void *) &point);
            CellList_Add(cells, x, y);
            break;
        case FOOTPRINT_TWO:
            if (offset != NULL || turn != 0) {
                RoomObject_BuildMatrix(object, offset, turn);
            } else {
                data_021fbe48 = object->base_matrix;
            }
            for (int i = 0; i < 2; i++) {
                Vec3 centre = data_ov004_02256e10[i];
                MTX_MultVec43(&centre, &data_021fbe48, &point);
                Position_Tile(&x, &y, (const Position *) (const void *) &point);
                CellList_Add(cells, x, y);
            }
            break;
        default:
            point.x = position.x - HALF_CELL;
            point.z = position.z - HALF_CELL;
            Position_Tile(&x, &y, (const Position *) (const void *) &point);
            CellList_Add(cells, x, y);
            CellList_Add(cells, x + 1, y);
            CellList_Add(cells, x, y + 1);
            CellList_Add(cells, x + 1, y + 1);
            break;
    }
}
CLEAN_AS(func_ov004_0220f27c, RoomObject_ListCells)

/* func_ov004_0220fdec: the object this one stands on (Mount), or 0. */
int RoomObject_MountParent(RoomObject *object)
{
    if (Mount_IsSet(&object->mount)) {
        void *objects = RoomObjects_Table();
        return (int) (uintptr_t) RoomObjects_At(objects, Mount_Parent(&object->mount));
    }
    return 0;
}
CLEAN_AS(func_ov004_0220fdec, RoomObject_MountParent)

/* func_ov004_0220fe24: whether no actor is near `point`: none of the other players (actors 0 to
 * 3, Actors_AreNear with `player_reach` and `player_radius`) and none of the twelve others of
 * Actors_Slot (with `npc_reach` and `npc_radius`). Not without the player. */
int Actors_NoneNear(Vec3 *point, fx32 player_reach, fx32 npc_reach, fx32 player_radius, fx32 npc_radius)
{
    MapActor *player = SessionPlayers_ActorOf(PLAYER);
    if (player == NULL) {
        return 0;
    }
    for (int i = 0; i < OTHER_PLAYERS; i++) {
        MapActor *other = SessionPlayers_ActorOf(i);
        if (other != NULL && other != player && Actors_AreNear(point, player_reach, &other->position, player_radius)) {
            return 0;
        }
    }
    unsigned int count = Actors_SlotCount();
    for (unsigned int j = 0; j < count; j++) {
        MapActor *other = Actors_Slot(j);
        if (other != NULL && Actors_AreNear(point, npc_reach, &other->position, npc_radius)) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0220fe24, Actors_NoneNear)

/* func_ov004_0220feac: whether `other` is nearer `point` on the ground than the two distances
 * together. */
int Actors_AreNear(Vec3 *point, fx32 reach, Vec3 *other, fx32 radius)
{
    return Vec_DistanceXZ(point, other) < reach + radius;
}
CLEAN_AS(func_ov004_0220feac, Actors_AreNear)

/* func_ov004_0220fed0: whether PlayerId_WhichTown says 0 of the child (PlayerRecord_Player) of
 * PlayerRecords_Current's object; not when either is missing. */
int Room_Check0220fed0(void)
{
    u8 *parent = PlayerRecords_Current();
    if (parent == NULL) {
        return 0;
    }
    DesignCreator *child = PlayerRecord_Player(parent);
    if (child == NULL) {
        return 0;
    }
    return PlayerId_WhichTown(child) == 0;
}
CLEAN_AS(func_ov004_0220fed0, Room_Check0220fed0)
