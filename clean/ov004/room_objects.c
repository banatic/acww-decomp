/* The room's objects as a whole (room_objects.h). */
#include "room_objects.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/collision_map.h"
#include "main/field_collision.h"
#include "main/furniture_info.h"
#include "main/item_code.h"
#include "main/item_footprint.h"
#include "main/main_random.h"
#include "main/room_sync.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/session_players.h"
#include "room_object_02252374.h"
#include "room_object_02253058.h"
#include "room_object_body.h"
#include "room_object_map.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "room_object_switch_shown.h"

static_assert(offsetof(RoomObject, position) == 0x5c, "position");
static_assert(offsetof(RoomObject, scale_x) == 0x150, "scale");
static_assert(offsetof(RoomObject, unk_288) == 0x288, "unk_288");
static_assert(offsetof(RoomObject, light_switch) == 0x740, "switch");
static_assert(offsetof(RoomObject, unk_774) == 0x774, "unk_774");
static_assert(offsetof(RoomObject, unk_778) == 0x778, "unk_778");
static_assert(offsetof(RoomObject, unk_780) == 0x780, "unk_780");
static_assert(offsetof(RoomObject, unk_788) == 0x788, "unk_788");
static_assert(offsetof(RoomObject, unk_78C) == 0x78c, "unk_78C");
static_assert(offsetof(RoomObject, top_height) == 0x790, "top height");
static_assert(offsetof(MapActor, angle) == 0x8e, "actor angle");

/* The player's actor (SessionPlayers_ActorOf). */
#define ROOM_OBJECTS_PLAYER 4

/* The kinds of RoomObject.unk_780 that RoomObjects_RequestOn and RoomObjects_RequestOff
 * switch, and the one RoomObjects_IsFreeAt270 and RoomObjects_IsFreeAt90 accept below the
 * point. */
#define KIND_780_SWITCHED_02252374 0x1b
#define KIND_780_ROOM_FLOOR 0x26
#define KIND_780_SWITCH_SHOWN 0x27

/* The RoomObject.unk_00C of the objects RoomObjects_CheckStep asks (room_object_02253058.h). */
#define KIND_00C_STEP 0x37

/* How far ahead RoomObjects_FindAhead looks for an item on the floor (1.05 cells), and the
 * reach of the RoomObjects_IsFree tests (one cell). */
#define FLOOR_ITEM_REACH 0x10cd
#define FREE_REACH 0x2000

#define CELL_SHIFT 13
#define HALF_CELL 0x1000

/* The town's map, the room being its only acre. */
extern AcreMap *data_021c80bc;

extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The steps to the cell next to one, for the sixteen directions of an angle (angle >> 12),
 * built on the first call of RoomObjects_CellAhead (bit 0 of the guard), and the direction
 * each pass adds: none, two to one side and two to the other. */
extern u32 data_ov004_022595d0;
extern FootprintCell data_ov004_022596d4[16];
extern const s8 data_ov004_02247ce0[4];

/* The greatest distance from a position to the centre of the cell ahead, by layer. */
extern const fx32 data_ov004_02247cec[2];

/* Where the last object taken away stands (RoomObjects_SetVanishPoint). */
extern Vec3 data_ov004_0225967c;

/* The two offsets of RoomObjects_CheckStepXMinus and RoomObjects_CheckStepXPlus, built on the
 * first call (bit 0 of each guard) and registered for destruction (TrivialObject_Destruct, which does
 * nothing). */
extern u32 data_ov004_022595c8;
extern Vec3 data_ov004_02259664;
extern u8 data_ov004_02259658[];
extern u32 data_ov004_022595cc;
extern Vec3 data_ov004_0225964c;
extern u8 data_ov004_02259640[];
extern void func_020012dc(void *object);
extern void __register_global_object(void *object, void *destruct, void *record);

/* The actor profile spawned for each value of FurnitureInfo_DmaUnk18 (0x30 of them). */
extern const u16 data_ov004_02247f54[0x30];

/* The room (room_manager.h). */
struct RoomManager;
extern struct RoomManager *data_ov004_022595c0;

/* The test RoomObjects_Spawn counts lamps of kind 0x18 with (RoomObject_TestUnk780Is18). */
extern int func_ov004_02211280(RoomObject *object);

#define LAMP_KIND 0x18
#define LAMPS_ON_MAX 4

static RoomObject *object_of(unsigned int index)
{
    return RoomObjects_At(RoomObjects_Table(), index);
}

/* func_ov004_0223b334: 1. */
int RoomObjects_Stub0223b334(Vec3 *position, s16 angle)
{
    (void) position;
    (void) angle;
    return 1;
}
CLEAN_AS(func_ov004_0223b334, RoomObjects_Stub0223b334)

/* func_ov004_0223b338: 1. */
int RoomObjects_Stub0223b338(Vec3 *position, s16 angle)
{
    (void) position;
    (void) angle;
    return 1;
}
CLEAN_AS(func_ov004_0223b338, RoomObjects_Stub0223b338)

/* func_ov004_0223b33c: 1. */
int RoomObjects_Stub0223b33c(Vec3 *position, s16 angle)
{
    (void) position;
    (void) angle;
    return 1;
}
CLEAN_AS(func_ov004_0223b33c, RoomObjects_Stub0223b33c)

/* func_ov004_0223b340: RoomObjects_RequestOn for the object on the floor at cell (x, z). */
int RoomObjects_RequestOnAt(int x, int z)
{
    return RoomObjects_RequestOn(RoomObjects_GridObjectAt(RoomObjects_Grid(), x, z, ROOM_OBJECTS_LAYER_FLOOR));
}
CLEAN_AS(func_ov004_0223b340, RoomObjects_RequestOnAt)

/* func_ov004_0223b364: asks an object of the two classes that switch this way to come on;
 * what it answers, 0 for another object or none. */
int RoomObjects_RequestOn(RoomObject *object)
{
    if (object == NULL) {
        return 0;
    }
    switch (object->unk_780) {
        case KIND_780_SWITCHED_02252374:
            return RoomObject02252374_RequestOn((RoomObject02252374 *) (void *) object);
        case KIND_780_SWITCH_SHOWN:
            return SwitchShown_RequestOn((SwitchShownObject *) (void *) object);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b364, RoomObjects_RequestOn)

/* func_ov004_0223b39c: RoomObjects_RequestOff for the object on the floor at cell (x, z). */
int RoomObjects_RequestOffAt(int x, int z)
{
    return RoomObjects_RequestOff(RoomObjects_GridObjectAt(RoomObjects_Grid(), x, z, ROOM_OBJECTS_LAYER_FLOOR));
}
CLEAN_AS(func_ov004_0223b39c, RoomObjects_RequestOffAt)

/* func_ov004_0223b3c0: the same as RoomObjects_RequestOn, to go off. */
int RoomObjects_RequestOff(RoomObject *object)
{
    if (object == NULL) {
        return 0;
    }
    switch (object->unk_780) {
        case KIND_780_SWITCHED_02252374:
            return RoomObject02252374_RequestOff((RoomObject02252374 *) (void *) object);
        case KIND_780_SWITCH_SHOWN:
            return SwitchShown_RequestOff((SwitchShownObject *) (void *) object);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b3c0, RoomObjects_RequestOff)

/* func_ov004_0223b958: the cell of `position` in (x, z) for pass 0; for passes 1 to 3 the cell
 * next to it in the direction of `angle` turned by data_ov004_02247ce0[pass] sixteenths
 * (straight ahead, then to either side); 0 for a later pass, the cell of `position` being set
 * all the same. QUIRK: the first call fills in the table of steps. */
int RoomObjects_CellAhead(int *x, int *z, const Vec3 *position, int angle, int pass)
{
    static const FootprintCell steps[16] = {
        {0, 1},  {1, 1},   {1, 1},   {1, 0},  {1, 0},  {1, -1}, {1, -1}, {0, -1},
        {0, -1}, {-1, -1}, {-1, -1}, {-1, 0}, {-1, 0}, {-1, 1}, {-1, 1}, {0, 1},
    };
    if ((data_ov004_022595d0 & 1) == 0) {
        for (int i = 0; i < 16; i++) {
            data_ov004_022596d4[i] = steps[i];
        }
        data_ov004_022595d0 |= 1;
    }
    Position_Tile(x, z, (const Position *) (const void *) position);
    if (pass == 0) {
        return 1;
    }
    if (pass < 4) {
        int direction = (((angle >> 12) & 0xf) + data_ov004_02247ce0[pass]) & 0xf;
        *x += data_ov004_022596d4[direction].x;
        *z += data_ov004_022596d4[direction].y;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b958, RoomObjects_CellAhead)

/* func_ov004_0223ba78: whether the object of `index` (0 or more) is idle with nothing on top. */
int RoomObjects_IsIdleAt(int index)
{
    if (index >= 0) {
        RoomObject *object = object_of((unsigned int) index);
        if (object != NULL) {
            return RoomObjects_IsIdleAndBare(object);
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223ba78, RoomObjects_IsIdleAt)

/* func_ov004_0223ba9c: whether `object` (or NULL) is idle (its vtable's is_idle) with nothing on
 * top of it. */
int RoomObjects_IsIdleAndBare(RoomObject *object)
{
    return object != NULL && object->vtable->is_idle(object) != 0 && RoomObject_HasItemsOnTop(object) == 0;
}
CLEAN_AS(func_ov004_0223ba9c, RoomObjects_IsIdleAndBare)

/* func_ov004_0223bac8: keeps where an object taken away stands (its centre, from the object's
 * own code as it starts to vanish). */
void RoomObjects_SetVanishPoint(const Vec3 *point)
{
    data_ov004_0225967c.x = point->x;
    data_ov004_0225967c.y = point->y;
    data_ov004_0225967c.z = point->z;
}
CLEAN_AS(func_ov004_0223bac8, RoomObjects_SetVanishPoint)

/* func_ov004_0223badc: the point of RoomObjects_SetVanishPoint once the object of `index` is
 * gone or has shrunk below 0.3 (its scale_x), else NULL. */
const Vec3 *RoomObjects_VanishPoint(int index)
{
    RoomObject *object = RoomObjects_At(RoomObjects_Table(), (unsigned int) index);
    if (object == NULL || object->scale_x < 0x4cd) {
        return &data_ov004_0225967c;
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223badc, RoomObjects_VanishPoint)

/* func_ov004_0223bb14: RoomObjects_TakeWithItem without the item codes. */
int RoomObjects_Take(int index)
{
    return RoomObjects_TakeWithItem((unsigned int) index, NULL, NULL);
}
CLEAN_AS(func_ov004_0223bb14, RoomObjects_Take)

/* func_ov004_0223bb20: sends the object of `index` away (ROOM_OBJECT_VANISH), giving its item
 * code (RoomObject_ItemCode) and the code of its furniture's number facing side 0; whether
 * there was one. Each code is ITEM_CODE_NONE without the object; NULL for either is not
 * wanted. */
int RoomObjects_TakeWithItem(unsigned int index, ItemCode *item, ItemCode *item_copy)
{
    if (item != NULL) {
        *item = ITEM_CODE_NONE;
    }
    if (item_copy != NULL) {
        *item_copy = ITEM_CODE_NONE;
    }
    RoomObject *object = object_of(index);
    if (object == NULL) {
        return 0;
    }
    RoomObject_EnterState(object, ROOM_OBJECT_VANISH);
    if (item != NULL) {
        ItemCode code;
        RoomObject_ItemCode(&code, object);
        *item = code;
    }
    if (item_copy != NULL) {
        *item_copy = ItemCode_MakeVariant(RoomObject_Number(object), 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_0223bb20, RoomObjects_TakeWithItem)

/* func_ov004_0223bb88: the byte unk_288 of the object of `index`, 0 without one. */
int RoomObjects_Unk288Of(unsigned int index)
{
    if (index < (unsigned int) RoomObjects_Capacity() && object_of(index) != NULL) {
        return object_of(index)->unk_288;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223bb88, RoomObjects_Unk288Of)

/* func_ov004_0223bbc0: RoomObjects_FindAhead for the player's actor (actor 4), -1 without it. */
int RoomObjects_FindAheadOfPlayer(int *x, int *z, ItemCode *item, ItemCode *item_copy)
{
    MapActor *player = SessionPlayers_ActorOf(ROOM_OBJECTS_PLAYER);
    if (player == NULL) {
        return ROOM_OBJECTS_AHEAD_NONE;
    }
    return RoomObjects_FindAhead(x, z, &player->position, (s16) player->angle, item, item_copy);
}
CLEAN_AS(func_ov004_0223bbc0, RoomObjects_FindAheadOfPlayer)

/* func_ov004_0223bbfc: what is in front of an actor at `position` facing `angle`.
 *
 * When the floor 1.05 cells ahead holds an item of kind 1, nothing (-1). Otherwise the cells of
 * RoomObjects_CellAhead are tried, pass by pass, first on top and then on the floor, as long
 * as the cell's centre is within the layer's reach: the first idle object with nothing on top
 * gives its index, its item code (RoomObject_ItemCode) and the code of its number facing side
 * 0; on top, a cell without an object holding an item of kind 1 gives
 * ROOM_OBJECTS_AHEAD_FLOOR_ITEM with that item's code in both. (x, z) is the last cell tried
 * in reach. The codes are ITEM_CODE_NONE when nothing is found; NULL for either is not
 * wanted.
 * QUIRK: the cell of `position` is worked out first and not used. */
int RoomObjects_FindAhead(int *x, int *z, const Vec3 *position, int angle, ItemCode *item, ItemCode *item_copy)
{
    if (item != NULL) {
        *item = ITEM_CODE_NONE;
    }
    if (item_copy != NULL) {
        *item_copy = ITEM_CODE_NONE;
    }
    int own_x;
    int own_z;
    Position_Tile(&own_x, &own_z, (const Position *) (const void *) position);
    AcreMap *map = data_021c80bc;
    if (map != NULL) {
        int index = ((u16) angle >> 4) * 2;
        Vec3 probe;
        fx32 probe_z = position->z + FX_MulFunc(FX_SinCosTable_[index + 1], FLOOR_ITEM_REACH);
        probe.x = position->x + FX_MulFunc(FX_SinCosTable_[index], FLOOR_ITEM_REACH);
        probe.y = 0;
        probe.z = probe_z;
        u16 *tile = AcreTile_ItemAt(map, &probe, ROOM_OBJECTS_LAYER_FLOOR);
        if (tile != NULL && ItemCode_IsKind1(tile)) {
            return ROOM_OBJECTS_AHEAD_NONE;
        }
    }
    for (int pass = 0; pass < 4; pass++) {
        for (int layer = ROOM_OBJECTS_LAYER_ON_TOP; layer >= ROOM_OBJECTS_LAYER_FLOOR; layer--) {
            int cell_x;
            int cell_z;
            if (!RoomObjects_CellAhead(&cell_x, &cell_z, position, angle, pass)) {
                continue;
            }
            Vec3 centre;
            AcreTile_TileCentre(&centre, (u32) cell_x, (u32) cell_z);
            if (Vec_DistanceXZ(position, &centre) > data_ov004_02247cec[layer & 1]) {
                continue;
            }
            RoomObject *object = RoomObjects_GridObjectAt(RoomObjects_Grid(), cell_x, cell_z, (u8) layer);
            *x = cell_x;
            *z = cell_z;
            if (object != NULL && object->vtable->is_idle(object) != 0 && RoomObject_HasItemsOnTop(object) == 0) {
                if (item != NULL) {
                    ItemCode code;
                    RoomObject_ItemCode(&code, object);
                    *item = code;
                }
                if (item_copy != NULL) {
                    *item_copy = ItemCode_MakeVariant(RoomObject_Number(object), 0);
                }
                return RoomObjects_IndexOf(RoomObjects_Table(), object);
            }
            if (layer == ROOM_OBJECTS_LAYER_ON_TOP && object == NULL) {
                int acre_x = cell_x >> 4;
                int acre_z = cell_z >> 4;
                u16 *tile = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, cell_x - acre_x * 16, cell_z - acre_z * 16,
                                                (u8) layer);
                if (tile != NULL && ItemCode_IsKind1(tile)) {
                    if (item != NULL) {
                        *item = *tile;
                    }
                    if (item_copy != NULL) {
                        *item_copy = *tile;
                    }
                    return ROOM_OBJECTS_AHEAD_FLOOR_ITEM;
                }
            }
        }
    }
    return ROOM_OBJECTS_AHEAD_NONE;
}
CLEAN_AS(func_ov004_0223bbfc, RoomObjects_FindAhead)

/* func_ov004_0223c10c: whether the scene is one of Nook's shops (SceneQuery_CurrentInNook) or
 * scene 0xa or 0xf; the TVs and glowing objects then do not come on by themselves. */
int RoomObjects_InNookOrScene0AOr0F(void)
{
    int scene = SceneQuery_Current();
    return SceneQuery_CurrentInNook() != 0 || scene == 0xa || scene == 0xf;
}
CLEAN_AS(func_ov004_0223c10c, RoomObjects_InNookOrScene0AOr0F)

/* func_ov004_0223c130: the entries of the table of the room's objects, by the scene. */
int RoomObjects_Capacity(void)
{
    return SceneTables_Value20e8(SceneQuery_Current());
}
CLEAN_AS(func_ov004_0223c130, RoomObjects_Capacity)

/* func_ov004_0223c144: among the objects whose unk_774 is `key` and unk_778 not -1, one picked
 * at random (MainRandom_Below); its unk_778, -1 for none. */
int RoomObjects_PickUnk778(int key)
{
    unsigned int count = (unsigned int) RoomObjects_Capacity();
    RoomObject **objects = RoomObjects_Table();
    int matches = 0;
    for (unsigned int i = 0; i < count; i++) {
        RoomObject *object = RoomObjects_At(objects, i);
        if (object != NULL && object->unk_778 != -1 && object->unk_774 == key) {
            matches++;
        }
    }
    if (matches == 0) {
        return -1;
    }
    int pick = (int) MainRandom_Below(matches);
    int seen = 0;
    for (unsigned int i = 0; i < count; i++) {
        RoomObject *object = RoomObjects_At(objects, i);
        if (object != NULL && object->unk_778 != -1 && object->unk_774 == key) {
            if (seen == pick) {
                return object->unk_778;
            }
            seen++;
        }
    }
    return -1;
}
CLEAN_AS(func_ov004_0223c144, RoomObjects_PickUnk778)

/* func_ov004_0223c1ec: among the objects `test` accepts (any, for NULL) whose switch is wanted
 * on, one picked at random (MainRandom_Below of RoomObjects_CountOn's count); its switch is
 * set off (Switch_Set with `pending`) and it is given; NULL for none.
 * QUIRK: with a NULL test RoomObjects_CountOn counts every object, switched on or not, so the
 * pick may fall past the last one switched on, and then none is given. */
RoomObject *RoomObjects_PickOn(RoomObjectsTest test, int pending)
{
    int count = RoomObjects_CountOn(test);
    if (count == 0) {
        return NULL;
    }
    int pick = (int) MainRandom_Below(count);
    int seen = 0;
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        RoomObject *object = object_of(i);
        if (object == NULL) {
            continue;
        }
        if (test != NULL && test(object) == 0) {
            continue;
        }
        if (Switch_Value(&object->light_switch) == 0) {
            continue;
        }
        if (seen == pick) {
            Switch_Set(&object->light_switch, 0, pending);
            return object;
        }
        seen++;
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223c1ec, RoomObjects_PickOn)

/* func_ov004_0223c264: the objects `test` accepts whose switch is wanted on.
 * QUIRK: with a NULL test every object counts, its switch not looked at. */
int RoomObjects_CountOn(RoomObjectsTest test)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        RoomObject *object = object_of(i);
        if (object == NULL) {
            continue;
        }
        if (test == NULL || (test(object) != 0 && Switch_Value(&object->light_switch) != 0)) {
            count++;
        }
    }
    return (int) count;
}
CLEAN_AS(func_ov004_0223c264, RoomObjects_CountOn)

/* func_ov004_0223c2b4: sets the switch of every object `test` accepts (any, for NULL) whose
 * switch is not wanted at `value` already (Switch_Set with `pending`). */
void RoomObjects_SetSwitches(int value, RoomObjectsTest test, int pending)
{
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        RoomObject *object = object_of(i);
        if (object == NULL) {
            continue;
        }
        if (test != NULL && test(object) == 0) {
            continue;
        }
        if (value == Switch_Value(&object->light_switch)) {
            continue;
        }
        Switch_Set(&object->light_switch, (u8) value, pending);
    }
}
CLEAN_AS(func_ov004_0223c2b4, RoomObjects_SetSwitches)

/* func_ov004_0223c310: for every object of kind 0x3a (RoomObject.unk_00C) whose switch is
 * wanted on, RoomSync_SetState(object, 0, 0xff, 1); 1. */
int RoomObjects_SyncKind3AOn(void)
{
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        RoomObject *object = object_of(i);
        if (object == NULL) {
            continue;
        }
        if (RoomObject_Unk00CIs3A(object) == 0) {
            continue;
        }
        if (Switch_Value(&object->light_switch) == 0) {
            continue;
        }
        RoomSync_SetState(object, 0, 0xff, 1);
    }
    return 1;
}
CLEAN_AS(func_ov004_0223c310, RoomObjects_SyncKind3AOn)

/* The object on the floor under `position` is none or of kind 0x26 (RoomObject.unk_780). */
static int floor_is_plain(Vec3 *position)
{
    RoomObject *below = RoomObjects_GridObjectAtPoint(RoomObjects_Grid(), position, ROOM_OBJECTS_LAYER_FLOOR);
    return below == NULL || below->unk_780 == KIND_780_ROOM_FLOOR;
}

/* func_ov004_0223c364: with nothing but an object of kind 0x26 under `position`, whether one
 * cell from it at `angle` + 0xc000 is ROOM_OBJECTS_POINT_FREE. */
int RoomObjects_IsFreeAt270(Vec3 *position, int angle)
{
    if (!floor_is_plain(position)) {
        return 0;
    }
    return RoomObjects_PointAheadState(position, (s16) (angle + 0xc000), FREE_REACH) == ROOM_OBJECTS_POINT_FREE;
}
CLEAN_AS(func_ov004_0223c364, RoomObjects_IsFreeAt270)

/* func_ov004_0223c3b8: the same at `angle` + 0x4000. */
int RoomObjects_IsFreeAt90(Vec3 *position, int angle)
{
    if (!floor_is_plain(position)) {
        return 0;
    }
    return RoomObjects_PointAheadState(position, (s16) (angle + 0x4000), FREE_REACH) == ROOM_OBJECTS_POINT_FREE;
}
CLEAN_AS(func_ov004_0223c3b8, RoomObjects_IsFreeAt90)

/* func_ov004_0223c40c: whether one cell from `position` at `angle` is ROOM_OBJECTS_POINT_FREE
 * (nothing is asked of the floor under it). */
int RoomObjects_IsFreeAhead(Vec3 *position, int angle)
{
    return RoomObjects_PointAheadState(position, (s16) angle, FREE_REACH) == ROOM_OBJECTS_POINT_FREE;
}
CLEAN_AS(func_ov004_0223c40c, RoomObjects_IsFreeAhead)

/* func_ov004_0223c430: the point `reach` from `position` along `angle` (at its height): blocked
 * when not at height 0 (RoomObjects_HeightAtPoint), crowded when a player or another actor is
 * near (Actors_NoneNear), free when no object claims it (CollisionMap_UnclaimedObjectAtPoint
 * -1), else blocked. */
int RoomObjects_PointAheadState(Vec3 *position, int angle, fx32 reach)
{
    int index = ((u16) angle >> 4) * 2;
    Vec3 point;
    fx32 z = position->z + FX_MulFunc(reach, FX_SinCosTable_[index + 1]);
    fx32 y = position->y;
    fx32 x = position->x + FX_MulFunc(reach, FX_SinCosTable_[index]);
    point.x = x;
    point.y = y;
    point.z = z;
    if (RoomObjects_HeightAtPoint(&point) != 0) {
        return ROOM_OBJECTS_POINT_BLOCKED;
    }
    if (Actors_NoneNear(&point, 0x800, 0x2000, 0x800, 0) == 0) {
        return ROOM_OBJECTS_POINT_CROWDED;
    }
    if (CollisionMap_UnclaimedObjectAtPoint(&point) == -1) {
        return ROOM_OBJECTS_POINT_FREE;
    }
    return ROOM_OBJECTS_POINT_BLOCKED;
}
CLEAN_AS(func_ov004_0223c430, RoomObjects_PointAheadState)

/* func_ov004_0223c4b8: RoomObjects_CheckStep with the offset (-1 cell, 0, 0).
 * QUIRK: the first call builds the offset and registers it for destruction. */
int RoomObjects_CheckStepXMinus(Vec3 *point, int angle)
{
    if ((data_ov004_022595c8 & 1) == 0) {
        data_ov004_02259664.x = -0x2000;
        data_ov004_02259664.y = 0;
        data_ov004_02259664.z = 0;
        __register_global_object(&data_ov004_02259664, (void *) func_020012dc, data_ov004_02259658);
        data_ov004_022595c8 |= 1;
    }
    return RoomObjects_CheckStep(point, angle, &data_ov004_02259664);
}
CLEAN_AS(func_ov004_0223c4b8, RoomObjects_CheckStepXMinus)

/* func_ov004_0223c510: RoomObjects_CheckStep with the offset (1 cell, 0, 0).
 * QUIRK: the first call builds the offset and registers it for destruction. */
int RoomObjects_CheckStepXPlus(Vec3 *point, int angle)
{
    if ((data_ov004_022595cc & 1) == 0) {
        data_ov004_0225964c.x = 0x2000;
        data_ov004_0225964c.y = 0;
        data_ov004_0225964c.z = 0;
        __register_global_object(&data_ov004_0225964c, (void *) func_020012dc, data_ov004_02259640);
        data_ov004_022595cc |= 1;
    }
    return RoomObjects_CheckStep(point, angle, &data_ov004_0225964c);
}
CLEAN_AS(func_ov004_0223c510, RoomObjects_CheckStepXPlus)

/* func_ov004_0223c568: what the object on the floor under `point` says of a step from it along
 * `angle` with `offset` (RoomObject02253058_CheckStep), when it is of kind 0x37; else 0. */
int RoomObjects_CheckStep(Vec3 *point, int angle, Vec3 *offset)
{
    RoomObject *object = RoomObjects_GridObjectAtPoint(RoomObjects_Grid(), point, ROOM_OBJECTS_LAYER_FLOOR);
    if (object != NULL && object->unk_00C == KIND_00C_STEP) {
        return RoomObject02253058_CheckStep((RoomObject02253058 *) (void *) object, point, angle, offset);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c568, RoomObjects_CheckStep)

/* func_ov004_0223c5a4: RoomObjects_HeightAtCell of the cell of `point`. */
fx32 RoomObjects_HeightAtPoint(const Vec3 *point)
{
    return RoomObjects_HeightAtCell(point->x >> CELL_SHIFT, point->z >> CELL_SHIFT);
}
CLEAN_AS(func_ov004_0223c5a4, RoomObjects_HeightAtPoint)

/* func_ov004_0223c5b8: the height of cell (x, z): with an object on the floor there, its height
 * (with its top height unless unk_78C is 1); else the ground's at the cell's centre. */
fx32 RoomObjects_HeightAtCell(int x, int z)
{
    RoomObject *object = RoomObjects_GridObjectAt(RoomObjects_Grid(), x, z, ROOM_OBJECTS_LAYER_FLOOR);
    if (object != NULL) {
        if (object->unk_78C == 1) {
            return object->position.y;
        }
        return object->top_height + object->position.y;
    }
    Vec3 centre;
    centre.x = (fx32) ((u32) x << CELL_SHIFT) + HALF_CELL;
    centre.y = 0;
    centre.z = (fx32) ((u32) z << CELL_SHIFT) + HALF_CELL;
    CollisionGround ground;
    CollisionGround_Init(&ground, &centre, 0, 0);
    fx32 height = CollisionGround_GetHeight(&ground, 0);
    CollisionGround_Destroy(&ground);
    return height;
}
CLEAN_AS(func_ov004_0223c5b8, RoomObjects_HeightAtCell)

/* func_ov004_0223c62c: spawns the object for furniture `number` placed at cell (x, z) facing
 * `side` (Placement_Make, RoomObjects_Spawn).
 * QUIRK: FurnitureInfo_DmaUnk18 of the number is asked first and not used. */
void RoomObjects_Place(int x, int z, int number, int side, u8 layer, int mode)
{
    FurnitureInfo_DmaUnk18(number);
    RoomObjects_Spawn((u32) Placement_Make(x, z, number, side, layer, mode));
}
CLEAN_AS(func_ov004_0223c62c, RoomObjects_Place)

/* func_ov004_0223c660: with a free entry in the table of the room's objects, spawns the actor of
 * a placed piece of furniture (the profile data_ov004_02247f54 gives for its
 * FurnitureInfo_DmaUnk18, the first for a value past the table), the room as its parent;
 * Actor_Spawn's result, 0 without a free entry. A lamp of kind 0x18 placed in mode 1 while
 * four or more are on first turns one of those off: picked at random, its switch then set on
 * with nothing pending and the switch at its point toggled for the scene
 * (RoomSync_ToggleSwitchAtPoint). */
int RoomObjects_Spawn(u32 placement)
{
    if (RoomObjects_FreeCount(RoomObjects_Table()) == 0) {
        return 0;
    }
    int kind = FurnitureInfo_DmaUnk18((int) Placement_Number(placement));
    unsigned int mode = Placement_Mode(placement);
    u16 profile = (kind >= 0 && kind < 0x30) ? data_ov004_02247f54[kind] : data_ov004_02247f54[0];
    if (kind == LAMP_KIND && mode == 1) {
        if ((unsigned int) RoomObjects_CountOn(func_ov004_02211280) >= LAMPS_ON_MAX) {
            RoomObject *lamp = RoomObjects_PickOn(func_ov004_02211280, 0);
            if (lamp != NULL) {
                Switch_Set(&lamp->light_switch, 1, 0);
                RoomSync_ToggleSwitchAtPoint(SceneQuery_Current(), &lamp->position, 0);
            }
        }
    }
    return Actor_Spawn(profile, (int) placement, NULL, NULL, data_ov004_022595c0);
}
CLEAN_AS(func_ov004_0223c660, RoomObjects_Spawn)

/* ---- The grid of the cells: for each of the two layers, 16 rows (z) of 16 cells (x), each
 * holding the index of the object on it in the table of the room's objects, or
 * ROOM_OBJECTS_NO_INDEX. Cell coordinates are taken modulo 16, the layer modulo 2. */

static u8 *grid_cell(u8 *grid, int x, int z, int layer)
{
    return grid + ((layer & 1) << 8) + ((z & 0xf) << 4) + (x & 0xf);
}

/* func_ov004_0223cbe8: RoomObjects_GridObjectAt of the cell of `point` (Position_Tile). */
RoomObject *RoomObjects_GridObjectAtPoint(u8 *grid, const Vec3 *point, int layer)
{
    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) (const void *) point);
    return RoomObjects_GridObjectAt(grid, x, z, layer);
}
CLEAN_AS(func_ov004_0223cbe8, RoomObjects_GridObjectAtPoint)

/* func_ov004_0223cc10: the object on cell (x, z) of `layer`, NULL when the cell is empty, its
 * index is past the table's entries or the entry is empty.
 * QUIRK: the entry is looked up twice. */
RoomObject *RoomObjects_GridObjectAt(u8 *grid, int x, int z, int layer)
{
    u8 *cell = grid_cell(grid, x, z, layer);
    u8 index = *cell;
    if (index != ROOM_OBJECTS_NO_INDEX && (unsigned int) index < (unsigned int) RoomObjects_Capacity() &&
        RoomObjects_At(RoomObjects_Table(), index) != NULL) {
        return RoomObjects_At(RoomObjects_Table(), *cell);
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223cc10, RoomObjects_GridObjectAt)

/* func_ov004_0223cc5c: the index on cell (x, z) of `layer`, -1 when it is empty. */
int RoomObjects_GridIndexAt(u8 *grid, int x, int z, int layer)
{
    u8 index = *grid_cell(grid, x, z, layer);
    if (index == ROOM_OBJECTS_NO_INDEX) {
        return -1;
    }
    return index;
}
CLEAN_AS(func_ov004_0223cc5c, RoomObjects_GridIndexAt)

/* func_ov004_0223cc80: empties cell (x, z) of `layer` when `object` is in the table of the
 * room's objects; whether it is.
 * QUIRK: the cell is emptied whatever object it holds. */
int RoomObjects_GridClearCell(u8 *grid, RoomObject *object, int x, int z, u8 layer)
{
    u8 *cell = grid_cell(grid, x, z, layer);
    if (RoomObjects_IndexOf(RoomObjects_Table(), object) != -1) {
        *cell = ROOM_OBJECTS_NO_INDEX;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223cc80, RoomObjects_GridClearCell)

/* func_ov004_0223ccc4: puts the index of `object` on cell (x, z) of `layer` when it is in the
 * table of the room's objects; whether it is. */
int RoomObjects_GridSetCell(u8 *grid, RoomObject *object, int x, int z, u8 layer)
{
    u8 *cell = grid_cell(grid, x, z, layer);
    int index = RoomObjects_IndexOf(RoomObjects_Table(), object);
    if (index != -1) {
        *cell = (u8) index;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223ccc4, RoomObjects_GridSetCell)

/* func_ov004_0223cd04: empties every cell of both layers. */
void RoomObjects_GridClear(u8 *grid)
{
    for (int layer = 0; layer < ROOM_OBJECTS_LAYERS; layer++) {
        for (int z = 0; z < ROOM_OBJECTS_CELLS; z++) {
            for (int x = 0; x < ROOM_OBJECTS_CELLS; x++) {
                *grid_cell(grid, x, z, layer) = ROOM_OBJECTS_NO_INDEX;
            }
        }
    }
}
CLEAN_AS(func_ov004_0223cd04, RoomObjects_GridClear)

/* func_ov004_0223cd3c: the C++ destructor of the grid; does nothing. */
void RoomObjects_GridDestruct(void *grid)
{
    (void) grid;
}
CLEAN_AS(func_ov004_0223cd3c, RoomObjects_GridDestruct)

/* func_ov004_0223cd40: the C++ constructor of the grid, which empties it. */
u8 *RoomObjects_GridConstruct(u8 *grid)
{
    RoomObjects_GridClear(grid);
    return grid;
}
CLEAN_AS(func_ov004_0223cd40, RoomObjects_GridConstruct)

/* The grid of the room's cells. */
extern u8 data_ov004_02259804[ROOM_OBJECTS_LAYERS * ROOM_OBJECTS_CELLS * ROOM_OBJECTS_CELLS];

/* func_ov004_0223cd50 */
u8 *RoomObjects_Grid(void)
{
    return data_ov004_02259804;
}
CLEAN_AS(func_ov004_0223cd50, RoomObjects_Grid)

/* ---- The table of the room's objects: ROOM_OBJECTS_TABLE_SIZE entries, of which the scene uses
 * RoomObjects_Capacity, NULL when free. The searches below ask RoomObjects_Capacity again before
 * each entry. */

/* func_ov004_0223cd58: the object of entry `index`, NULL past the scene's entries. */
RoomObject *RoomObjects_At(RoomObject **table, unsigned int index)
{
    if (index < (unsigned int) RoomObjects_Capacity()) {
        return table[index];
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223cd58, RoomObjects_At)

/* func_ov004_0223cd78: the entry holding `object`, -1 for none. */
int RoomObjects_IndexOf(RoomObject **table, RoomObject *object)
{
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        if (table[i] == object) {
            return (int) i;
        }
    }
    return -1;
}
CLEAN_AS(func_ov004_0223cd78, RoomObjects_IndexOf)

/* func_ov004_0223cda4: the entries still free. */
int RoomObjects_FreeCount(RoomObject **table)
{
    int capacity = RoomObjects_Capacity();
    return capacity - RoomObjects_UsedCount(table);
}
CLEAN_AS(func_ov004_0223cda4, RoomObjects_FreeCount)

/* func_ov004_0223cdc0: the entries holding an object. */
int RoomObjects_UsedCount(RoomObject **table)
{
    int count = 0;
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        if (table[i] != NULL) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_ov004_0223cdc0, RoomObjects_UsedCount)

/* func_ov004_0223cde8: frees the entry of `object`; whether there was one. */
int RoomObjects_Remove(RoomObject **table, RoomObject *object)
{
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        if (table[i] == object) {
            table[i] = NULL;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223cde8, RoomObjects_Remove)

/* func_ov004_0223ce18: puts `object` in the first free entry unless it has one already; whether
 * it is in the table. */
int RoomObjects_Add(RoomObject **table, RoomObject *object)
{
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        if (table[i] == object) {
            return 1;
        }
    }
    for (unsigned int i = 0; i < (unsigned int) RoomObjects_Capacity(); i++) {
        if (table[i] == NULL) {
            table[i] = object;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223ce18, RoomObjects_Add)

/* func_ov004_0223ce60: frees every entry of the table (all ROOM_OBJECTS_TABLE_SIZE). */
void RoomObjects_TableClear(RoomObject **table)
{
    for (u32 i = 0; i < ROOM_OBJECTS_TABLE_SIZE; i++) {
        table[i] = NULL;
    }
}
CLEAN_AS(func_ov004_0223ce60, RoomObjects_TableClear)

/* func_ov004_0223ce70: the C++ destructor of the table; does nothing. */
void RoomObjects_TableDestruct(void *table)
{
    (void) table;
}
CLEAN_AS(func_ov004_0223ce70, RoomObjects_TableDestruct)

/* func_ov004_0223ce74: the C++ constructor of the table, which frees every entry. */
RoomObject **RoomObjects_TableConstruct(RoomObject **table)
{
    RoomObjects_TableClear(table);
    return table;
}
CLEAN_AS(func_ov004_0223ce74, RoomObjects_TableConstruct)

/* The table of the room's objects. */
extern RoomObject *data_ov004_02259714[ROOM_OBJECTS_TABLE_SIZE];

/* func_ov004_0223ce84 */
RoomObject **RoomObjects_Table(void)
{
    return data_ov004_02259714;
}
CLEAN_AS(func_ov004_0223ce84, RoomObjects_Table)

/* ---- The room's heap, where the room's objects are made (room_object_life.h): an expanded heap
 * of one block for each entry of the table, made by the room's start and deleted by its end. */

/* The size of a block of the room's heap, and the room taken in the heap for each. */
#define ROOM_OBJECTS_BLOCK_SIZE 0x8da
#define ROOM_OBJECTS_HEAP_PER_BLOCK 0x93e

/* The heap the room's heap is made in. */
extern Heap *data_021fbe94;

/* func_ov004_0223ce8c: gives `block` back to the room's heap (Heap_Free). */
void RoomObjects_HeapFree(Heap **heap, void *block)
{
    Heap_Free(*heap, block);
}
CLEAN_AS(func_ov004_0223ce8c, RoomObjects_HeapFree)

/* func_ov004_0223ce98: a block of the room's heap (Heap_Alloc), NULL when there is none left.
 * QUIRK: `size` is not used: a block is always ROOM_OBJECTS_BLOCK_SIZE bytes. */
void *RoomObjects_HeapAlloc(Heap **heap, int size)
{
    (void) size;
    return Heap_Alloc(*heap, ROOM_OBJECTS_BLOCK_SIZE);
}
CLEAN_AS(func_ov004_0223ce98, RoomObjects_HeapAlloc)

/* func_ov004_0223cea8: deletes the room's heap if there is one (Heap_Delete), and forgets it. */
void RoomObjects_HeapDelete(Heap **heap)
{
    if (*heap != NULL) {
        Heap_Delete(*heap);
    }
    RoomObjects_HeapForget(heap);
}
CLEAN_AS(func_ov004_0223cea8, RoomObjects_HeapDelete)

/* func_ov004_0223cec4: unless there is one, makes the room's heap for `count` blocks
 * (ExpHeap_Create in data_021fbe94, NULL when it cannot); whether it was made now. */
int RoomObjects_HeapCreate(Heap **heap, int count)
{
    if (*heap == NULL) {
        *heap = ExpHeap_Create(ROOM_OBJECTS_HEAP_PER_BLOCK * count, data_021fbe94);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223cec4, RoomObjects_HeapCreate)

/* func_ov004_0223cef4 */
void RoomObjects_HeapForget(Heap **heap)
{
    *heap = NULL;
}
CLEAN_AS(func_ov004_0223cef4, RoomObjects_HeapForget)

/* func_ov004_0223cefc: the C++ destructor of the heap's holder; does nothing. */
void RoomObjects_HeapDestruct(void *heap)
{
    (void) heap;
}
CLEAN_AS(func_ov004_0223cefc, RoomObjects_HeapDestruct)

/* func_ov004_0223cf00: the C++ constructor of the heap's holder: no heap. */
Heap **RoomObjects_HeapConstruct(Heap **heap)
{
    RoomObjects_HeapForget(heap);
    return heap;
}
CLEAN_AS(func_ov004_0223cf00, RoomObjects_HeapConstruct)

/* The room's heap, NULL while there is none. */
extern Heap *data_ov004_022595c4;

/* func_ov004_0223cf10 */
Heap **RoomObjects_Heap(void)
{
    return &data_ov004_022595c4;
}
CLEAN_AS(func_ov004_0223cf10, RoomObjects_Heap)
