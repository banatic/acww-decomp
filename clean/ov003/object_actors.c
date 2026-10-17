/* Overlay 3's object actors (object_actors.h). */
#include "object_actors.h"

#include "autoload_2/heap.h" /* Heap_FreeAux, Heap_AllocAuxZeroed */
#include "clean.h"
#include "house_files.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/acre_tile.h"
#include "main/actor.h"          /* Actor_Spawn */
#include "main/actor_table.h"    /* Position, Position_Tile */
#include "main/block_020b220c.h" /* Block020b220c_Flag4b18, Block020b220c_Flag4b1c */
#include "main/building_shapes.h"
#include "main/building_taker.h"
#include "main/collision_map.h"
#include "main/game_process.h"
#include "main/item_code.h"
#include "main/scene_heaps.h"
#include "main/scene_query.h"
#include "main/session.h"
#include "main/town_objects.h"

static_assert(sizeof(ObjectActors) == 0x50, "the size ObjectActors_New allocates");
static_assert(sizeof(SceneActorRecord) == 10, "a record of data_020d1f24");
static_assert(offsetof(SceneActor, tile_x) == 0x22c, "tile_x");
static_assert(offsetof(SceneActor, tile_z) == 0x230, "tile_z");

/* The list. */
extern SceneActor *data_ov003_0223cef0[OBJECT_ACTORS_MAX];
/* The byte ObjectActors_PoseFlag gives: overlay 9's scene actors and overlay 68 set it, and the
 * player entering state 0x3c takes animation 0x34 while it is set, else 0x35. */
extern u8 data_ov003_0223ce50;
/* How many objects whose record's byte 3 is 1 ObjectActors_PlaceAll placed; each sign board
 * takes it as its number when it is set up (sign_board.h). */
extern u16 data_ov003_0223ce54;
/* The houses' three sets of files (house_files.h). */
extern HousePalette data_ov003_0223ce58;
extern HouseXFiles data_ov003_0223ce80;
extern HouseTextures data_ov003_0223cea0;
/* The vtables: the process class's and this process's. */
extern const u32 data_020da13c[];
extern const u32 data_ov003_02239b2c[];
/* The map of the scene shown. */
extern AcreMap *data_021c80bc;
/* The session. */
extern NetSession *data_020ccf94;
/* The objects' records, by index (a code's low twelve bits). */
extern const SceneActorRecord data_020d1f24[TOWN_OBJECTS_COUNT];
/* The parent of the process ObjectActors_SetUp spawns. */
extern int data_021f42f4;

/* The class of the process the set up spawns, and the size of the countdown heap it makes. */
#define OBJECT_ACTORS_CHILD_CLASS 0xf
#define OBJECT_ACTORS_COUNTDOWN_HEAP 0x1f000
/* The tiles ObjectActors_FindNear searches round a position's tile: up to 5 behind it along z
 * and 3 to each side along x. */
#define OBJECT_ACTORS_NEAR_BACK 5
#define OBJECT_ACTORS_NEAR_SIDE 3
/* Objects: the one put on acres of models 0x1a-0x1c at tile (7, 0) before they are searched,
 * the one placed only in the snow season, and the one put before 0x5000's front. */
#define OBJECT_ACTORS_ACRE_OBJECT 0x500b
#define OBJECT_ACTORS_ACRE_OBJECT_X 7
#define OBJECT_ACTORS_ACRE_OBJECT_Z 0
#define OBJECT_ACTORS_SNOW_OBJECT 0x501e
#define OBJECT_ACTORS_FRONT_OBJECT 0x501b
/* A record's byte 3: 1 is counted in data_ov003_0223ce54; 2 is not placed while either of
 * Block020b220c's flags 0x4b18 and 0x4b1c is set. */
#define OBJECT_ACTORS_MODE_COUNTED 1
#define OBJECT_ACTORS_MODE_FLAGGED 2

static int object_actors_is_object(u16 code)
{
    return code >= TOWN_OBJECTS_FIRST && code <= TOWN_OBJECTS_LAST;
}

/* An object code's record: the one of its index, the first for any other code. */
static const SceneActorRecord *object_actors_record(u16 code)
{
    unsigned int index = object_actors_is_object(code) ? (code & 0xfffu) : 0xffffffffu;
    if (index < TOWN_OBJECTS_COUNT) {
        return &data_020d1f24[index];
    }
    return &data_020d1f24[0];
}

/* Whether `item` is `code`: compared by their variants' item when `item` has variants. */
static int object_actors_is_code(const u16 *item, u16 code)
{
    if (ItemCode_HasVariant(item)) {
        int variant_item = ItemCode_VariantItem(item);
        return variant_item == ItemCode_VariantItem(&code);
    }
    return *item == code;
}

/* func_ov003_02220120: the list emptied, when the process is released. */
void ObjectActors_ReleaseList(void)
{
    for (unsigned int i = 0; i < OBJECT_ACTORS_MAX; i++) {
        data_ov003_0223cef0[i] = NULL;
    }
}
CLEAN_AS(func_ov003_02220120, ObjectActors_ReleaseList)

/* func_ov003_02220138: the list emptied, when the process is made or set up. */
void ObjectActors_ClearList(void)
{
    for (unsigned int i = 0; i < OBJECT_ACTORS_MAX; i++) {
        data_ov003_0223cef0[i] = NULL;
    }
}
CLEAN_AS(func_ov003_02220138, ObjectActors_ClearList)

/* func_ov003_02220150: the actor's place in the list, -1 when it is not in it. */
int ObjectActors_IndexOf(SceneActor *actor)
{
    for (unsigned int i = 0; i < OBJECT_ACTORS_MAX; i++) {
        if (data_ov003_0223cef0[i] == actor) {
            return (int) i;
        }
    }
    return -1;
}
CLEAN_AS(func_ov003_02220150, ObjectActors_IndexOf)

/* func_ov003_02220174: the first actor in the list of object `code` (compared by the variants'
 * item when the actor's code has variants), or NULL. */
SceneActor *ObjectActors_FindByCode(u16 code)
{
    for (unsigned int i = 0; i < OBJECT_ACTORS_MAX; i++) {
        SceneActor *actor = data_ov003_0223cef0[i];
        if (actor != NULL) {
            const u16 *actor_code = (const u16 *) (uintptr_t) SceneActor_CodeAddress(actor);
            if (object_actors_is_code(actor_code, code)) {
                return actor;
            }
        }
    }
    return NULL;
}
CLEAN_AS(func_ov003_02220174, ObjectActors_FindByCode)

/* func_ov003_022201e4: the list's entry `index`, NULL outside 0-31. */
SceneActor *ObjectActors_At(int index)
{
    if (index >= 0 && index < OBJECT_ACTORS_MAX) {
        return data_ov003_0223cef0[index];
    }
    return NULL;
}
CLEAN_AS(func_ov003_022201e4, ObjectActors_At)

/* func_ov003_022201fc: the first actor in the list standing on tile (x, z), or NULL. */
SceneActor *ObjectActors_FindAtTile(u32 x, u32 z)
{
    for (unsigned int i = 0; i < OBJECT_ACTORS_MAX; i++) {
        SceneActor *actor = data_ov003_0223cef0[i];
        if (actor != NULL && (u32) actor->tile_x == x && (u32) actor->tile_z == z) {
            return actor;
        }
    }
    return NULL;
}
CLEAN_AS(func_ov003_022201fc, ObjectActors_FindAtTile)

/* func_ov003_02220240: takes the actor off the list; 1 when it was in it, else 0. */
int ObjectActors_Remove(SceneActor *actor)
{
    int index = ObjectActors_IndexOf(actor);
    if (index != -1) {
        data_ov003_0223cef0[index] = NULL;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_02220240, ObjectActors_Remove)

/* func_ov003_02220268: puts the actor in the list's first empty entry; 0 when it is full. */
int ObjectActors_Add(SceneActor *actor)
{
    for (unsigned int i = 0; i < OBJECT_ACTORS_MAX; i++) {
        if (data_ov003_0223cef0[i] == NULL) {
            data_ov003_0223cef0[i] = actor;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_02220268, ObjectActors_Add)

/* func_ov003_02220294: the actor of the first object found on the scene's map near `position`:
 * the tiles from the position's own along z back to 5 tiles behind it, each row from 3 tiles
 * left to 3 tiles right of it; NULL when there is none or no map. */
SceneActor *ObjectActors_FindNear(const Vec3 *position)
{
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return NULL;
    }
    int x;
    int z;
    Position_Tile(&x, &z, (const Position *) (const void *) position);
    for (int tile_z = z; tile_z >= z - OBJECT_ACTORS_NEAR_BACK; tile_z--) {
        for (int tile_x = x - OBJECT_ACTORS_NEAR_SIDE; tile_x <= x + OBJECT_ACTORS_NEAR_SIDE; tile_x++) {
            int acre_x = tile_x >> 4;
            int acre_z = tile_z >> 4;
            u16 *item = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, tile_x & 0xf, tile_z & 0xf, 0);
            if (item != NULL && object_actors_is_object(*item)) {
                SceneActor *actor = ObjectActors_FindByCode(*item);
                if (actor != NULL) {
                    return actor;
                }
            }
        }
    }
    return NULL;
}
CLEAN_AS(func_ov003_02220294, ObjectActors_FindNear)

/* func_ov003_02220318: the actor of villager `villager`'s house (object 0x5001 + villager), if
 * there is one, gets SceneActor_IdleSetModeByKindA and its answer is returned; else 0. */
int ObjectActors_IdleSetHouseModeA(int villager)
{
    SceneActor *actor = ObjectActors_FindByCode((u16) (villager + 0x5001));
    if (actor != NULL) {
        return SceneActor_IdleSetModeByKindA(actor);
    }
    return 0;
}
CLEAN_AS(func_ov003_02220318, ObjectActors_IdleSetHouseModeA)

/* func_ov003_02220340: as ObjectActors_IdleSetHouseModeA with SceneActor_IdleSetModeByKindB. */
int ObjectActors_IdleSetHouseModeB(int villager)
{
    SceneActor *actor = ObjectActors_FindByCode((u16) (villager + 0x5001));
    if (actor != NULL) {
        return SceneActor_IdleSetModeByKindB(actor);
    }
    return 0;
}
CLEAN_AS(func_ov003_02220340, ObjectActors_IdleSetHouseModeB)

/* func_ov003_02220368: the actor near `position` (ObjectActors_FindNear), if there is one, gets
 * SceneActor_SetModeByKindA and its answer is returned; else 0. */
int ObjectActors_SetNearModeA(const Vec3 *position)
{
    SceneActor *actor = ObjectActors_FindNear(position);
    return actor != NULL ? SceneActor_SetModeByKindA(actor) : 0;
}
CLEAN_AS(func_ov003_02220368, ObjectActors_SetNearModeA)

/* func_ov003_02220384: as ObjectActors_SetNearModeA with SceneActor_SetModeByKindB. */
int ObjectActors_SetNearModeB(const Vec3 *position)
{
    SceneActor *actor = ObjectActors_FindNear(position);
    return actor != NULL ? SceneActor_SetModeByKindB(actor) : 0;
}
CLEAN_AS(func_ov003_02220384, ObjectActors_SetNearModeB)

/* func_ov003_022203a0 */
void ObjectActors_SetPoseFlag(u8 flag)
{
    data_ov003_0223ce50 = flag;
}
CLEAN_AS(func_ov003_022203a0, ObjectActors_SetPoseFlag)

/* func_ov003_022203ac */
u8 ObjectActors_PoseFlag(void)
{
    return data_ov003_0223ce50;
}
CLEAN_AS(func_ov003_022203ac, ObjectActors_PoseFlag)

/* func_ov003_022203d0 */
u16 ObjectActors_Mode1Count(void)
{
    return data_ov003_0223ce54;
}
CLEAN_AS(func_ov003_022203d0, ObjectActors_Mode1Count)

/* func_ov003_022203f4: the countdown heap destroyed, when the process is released. */
void ObjectActors_DestroyCountdownHeap(ObjectActors *self)
{
    (void) self;
    SceneHeaps_DestroyCountdown();
}
CLEAN_AS(func_ov003_022203f4, ObjectActors_DestroyCountdownHeap)

/* func_ov003_022203fc: the countdown heap made, 0x1f000 bytes, when the process is set up. */
void ObjectActors_CreateCountdownHeap(ObjectActors *self)
{
    (void) self;
    SceneHeaps_CreateCountdown(OBJECT_ACTORS_COUNTDOWN_HEAP, NULL);
}
CLEAN_AS(func_ov003_022203fc, ObjectActors_CreateCountdownHeap)

/* func_ov003_0222040c: every 'S' entry of object `code`'s shape (main/building_shapes.h), when
 * it has one, retypes the collision map's tile at (x, z) moved by the entry's offset with the
 * entry's value as its sides. 1. */
int ObjectActors_RetypeShape(ObjectActors *self, u16 *code, int x, int z)
{
    (void) self;
    BuildingShapeEntry *shape = BuildingShapes_Of(code);
    if (shape != NULL) {
        unsigned int count = (unsigned int) BuildingShapes_SCount(shape);
        for (unsigned int i = 0; i < count; i++) {
            int value;
            int offset_x;
            int offset_z;
            if (BuildingShapes_STile(shape, &value, &offset_x, &offset_z, i)) {
                CollisionMap_RetypeWithSides(x + offset_x, z + offset_z, (u8) value);
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_0222040c, ObjectActors_RetypeShape)

/* func_ov003_02220460: spawns the scene actor of object `*code` at the centre of tile (x, z):
 * actor profile from the object's record (TownObjects_RecordCode), the code as its parameter.
 * When it spawned and `stamp` is set, the object is also put down on the scene's map at the
 * tile (AcreTile_StampBuildingNoting, not handed back here) and its shape's tiles retyped in
 * the collision map. 1 when the actor spawned, else 0. */
int ObjectActors_Place(ObjectActors *self, u16 *code, int x, int z, u8 stamp)
{
    Vec3 centre = {0, 0, 0};
    SceneActorRecord record;

    AcreTile_TileCentre(&centre, (u32) x, (u32) z);
    TownObjects_CopyRecord(&record, object_actors_record(*code));
    if (Actor_Spawn(TownObjects_RecordCode(&record), *code, &centre, NULL, NULL) == 0) {
        TownObjects_DestroyRecord(&record);
        return 0;
    }
    if (stamp != 0) {
        AcreTile_StampBuildingNoting(data_021c80bc, code, x, z, 0);
        ObjectActors_RetypeShape(self, code, x, z);
    }
    TownObjects_DestroyRecord(&record);
    return 1;
}
CLEAN_AS(func_ov003_02220460, ObjectActors_Place)

/* func_ov003_02220520: places every object on the scene's map (ObjectActors_Place, put down
 * too), acre by acre and in each acre tile by tile (layer 0), counting those whose record's
 * byte 3 is 1 in data_ov003_0223ce54 (cleared first). Before an acre of model 0x1a-0x1c is
 * searched, object 0x500b is put on its tile (7, 0). Not placed: an object whose byte 3 is 2
 * while Block020b220c's flag 0x4b18 or 0x4b1c is set, and object 0x501e (or a variant of it)
 * outside the snow season. Then, when SceneQuery_CurrentIs0 says so, this system's session slot
 * is not taken, one of those flags is set and the town's map has object 0x5000, object 0x501b
 * is placed (not put down) one tile further along z than the tile AcreMap_FindBuilding5000Front
 * gives. The number of objects placed from the map. */
int ObjectActors_PlaceAll(ObjectActors *self)
{
    data_ov003_0223ce54 = 0;
    AcreMap *map = data_021c80bc;
    u32 acres_wide = (u32) map->acres_wide;
    u32 acres_high = (u32) map->acres_high;
    int flagged = Block020b220c_Flag4b18() != 0 || Block020b220c_Flag4b1c() != 0;
    int placed = 0;

    for (u32 acre_z = 0; acre_z < acres_high; acre_z++) {
        for (u32 acre_x = 0; acre_x < acres_wide; acre_x++) {
            AcreRecord *acre = NULL;
            if (acre_x < (u32) map->acres_wide && acre_z < (u32) map->acres_high && map->acres != NULL) {
                acre = (AcreRecord *) (void *) (map->acres + ACRE_MAP_ACRE_SIZE * (acre_x + acre_z * (u32) map->acres_wide));
            }
            int model = AcreRecord_Model(acre);
            if (model >= 0x1a && model <= 0x1c) {
                u16 acre_object = OBJECT_ACTORS_ACRE_OBJECT;
                AcreRecord_SetTile(acre, &acre_object, OBJECT_ACTORS_ACRE_OBJECT_X, OBJECT_ACTORS_ACRE_OBJECT_Z, 0);
            }
            for (u32 tile_z = 0; tile_z < ACRE_RECORD_SIDE; tile_z++) {
                for (u32 tile_x = 0; tile_x < ACRE_RECORD_SIDE; tile_x++) {
                    u16 *item = AcreRecord_Tile(acre, tile_x, tile_z, 0);
                    if (item == NULL || !object_actors_is_object(*item)) {
                        continue;
                    }
                    int x;
                    int z;
                    AcreTile_TileOfAcre(&x, &z, (int) acre_x, (int) acre_z, (int) tile_x, (int) tile_z);
                    SceneActorRecord record;
                    TownObjects_CopyRecord(&record, object_actors_record(*item));
                    int mode = TownObjects_RecordByte3(&record);
                    int wanted = !flagged || mode != OBJECT_ACTORS_MODE_FLAGGED;
                    if (object_actors_is_code(item, OBJECT_ACTORS_SNOW_OBJECT) && SceneQuery_IsSnowSeason() == 0) {
                        wanted = 0;
                    }
                    if (wanted && ObjectActors_Place(self, item, x, z, 1) != 0) {
                        if (mode == OBJECT_ACTORS_MODE_COUNTED) {
                            data_ov003_0223ce54++;
                        }
                        placed++;
                    }
                    TownObjects_DestroyRecord(&record);
                }
            }
        }
    }

    if (SceneQuery_CurrentIs0() != 0 && Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) == 0) {
        unsigned int town = AcreMap_Town();
        if (Block020b220c_Flag4b18() != 0 || Block020b220c_Flag4b1c() != 0) {
            int front[4]; /* the point (x, y, z) and a word the ROM leaves room for */
            int x;
            int z;
            if (AcreMap_FindBuilding5000Front((int) town, front, &x, &z) != 0) {
                u16 front_object = OBJECT_ACTORS_FRONT_OBJECT;
                ObjectActors_Place(self, &front_object, x, z + 1, 0);
            }
        }
    }
    return placed;
}
CLEAN_AS(func_ov003_02220520, ObjectActors_PlaceAll)

/* func_ov003_02220794: a step of the set up that does nothing. */
void ObjectActors_SetUpNothingA(ObjectActors *self)
{
    (void) self;
}
CLEAN_AS(func_ov003_02220794, ObjectActors_SetUpNothingA)

/* func_ov003_02220798: another step of the set up that does nothing. */
void ObjectActors_SetUpNothingB(ObjectActors *self)
{
    (void) self;
}
CLEAN_AS(func_ov003_02220798, ObjectActors_SetUpNothingB)

/* func_ov003_0222079c (vtable slot 3, released): the list emptied, main's building slot given
 * up, the house textures and X files forgotten, the palettes left, the countdown heap
 * destroyed. 1. */
int ObjectActors_Release(ObjectActors *self)
{
    ObjectActors_ReleaseList();
    BuildingTaker_Release(self);
    HouseTextures_Clear(&data_ov003_0223cea0);
    HouseXFiles_Release(&data_ov003_0223ce80);
    HousePalette_Release(&data_ov003_0223ce58);
    ObjectActors_DestroyCountdownHeap(self);
    return 1;
}
CLEAN_AS(func_ov003_0222079c, ObjectActors_Release)

/* func_ov003_022207d8 (vtable slot 9, drawn): nothing to draw. 1. */
int ObjectActors_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov003_022207d8, ObjectActors_Draw)

/* func_ov003_022207dc (vtable slot 6, each frame): nothing to do. 1. */
int ObjectActors_Update(void)
{
    return 1;
}
CLEAN_AS(func_ov003_022207dc, ObjectActors_Update)

/* func_ov003_022207e0 (vtable slot 0, set up): the objects' footprints marked, the list
 * emptied, main's kept object kept (TownObjects_KeepAtKeptTile), main's building slot claimed,
 * the countdown heap made, the houses' palettes, textures and X files loaded, every object of
 * the scene's map placed, and process class 0xf spawned under data_021f42f4. 1. */
int ObjectActors_SetUp(ObjectActors *self)
{
    TownObjects_MarkFootprints();
    ObjectActors_ClearList();
    TownObjects_KeepAtKeptTile();
    BuildingTaker_Claim(self);
    ObjectActors_CreateCountdownHeap(self);
    HousePalette_Load(&data_ov003_0223ce58);
    HouseTextures_Load(&data_ov003_0223cea0);
    HouseXFiles_Load(&data_ov003_0223ce80);
    ObjectActors_SetUpNothingB(self);
    ObjectActors_SetUpNothingA(self);
    ObjectActors_PlaceAll(self);
    GameProcess_SpawnChild(OBJECT_ACTORS_CHILD_CLASS, data_021f42f4, 0, 0);
    return 1;
}
CLEAN_AS(func_ov003_022207e0, ObjectActors_SetUp)

/* func_ov003_02220848 (vtable slot 17): destroys the process and frees it; returns `self`. */
ObjectActors *ObjectActors_DestroyAndFree(ObjectActors *self)
{
    self->process.vtable = data_ov003_02239b2c;
    self->process.vtable = data_020da13c;
    Process_Destruct(&self->process);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov003_02220848, ObjectActors_DestroyAndFree)

/* func_ov003_02220870 (vtable slot 16): destroys the process; returns it. */
ObjectActors *ObjectActors_Destroy(ObjectActors *self)
{
    self->process.vtable = data_ov003_02239b2c;
    self->process.vtable = data_020da13c;
    Process_Destruct(&self->process);
    return self;
}
CLEAN_AS(func_ov003_02220870, ObjectActors_Destroy)

/* func_ov003_02220890: the process's constructor; the list is emptied. Returns `self`. */
ObjectActors *ObjectActors_Construct(ObjectActors *self)
{
    Process_Construct(&self->process);
    self->process.vtable = data_020da13c;
    self->process.vtable = data_ov003_02239b2c;
    ObjectActors_ClearList();
    return self;
}
CLEAN_AS(func_ov003_02220890, ObjectActors_Construct)

/* func_ov003_022208b4 (the process's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void ObjectActors_New(void)
{
    ObjectActors *self = Heap_AllocAuxZeroed(sizeof(ObjectActors));
    if (self != NULL) {
        ObjectActors_Construct(self);
    }
}
CLEAN_AS(func_ov003_022208b4, ObjectActors_New)
