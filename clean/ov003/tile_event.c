/* Overlay 3's tile events (tile_event.h). */
#include "tile_event.h"

#include "autoload_2/heap.h" /* Heap_FreeAux */
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor.h"       /* Actor */
#include "main/actor_table.h" /* Position, Position_Tile */
#include "main/angle_sector.h"
#include "main/session.h"
#include "main/session_players.h"

static_assert(sizeof(ModelObject) == 0x9c, "model object");
static_assert(sizeof(ModelSet) == 0x10, "model set");
static_assert(offsetof(TileEventProcess, models_0174) == 0x174, "models_0174");
static_assert(offsetof(TileEventProcess, models_0c6c) == 0xc6c, "models_0c6c");
static_assert(offsetof(TileEventProcess, models_1014) == 0x1014, "models_1014");
static_assert(offsetof(TileEventProcess, models_11e8) == 0x11e8, "models_11e8");
static_assert(offsetof(TileEventProcess, models_1590) == 0x1590, "models_1590");
static_assert(offsetof(TileEventProcess, models_2df0) == 0x2df0, "models_2df0");
static_assert(offsetof(TileEventProcess, models_3068) == 0x3068, "models_3068");
static_assert(offsetof(TileEventProcess, models_43e8) == 0x43e8, "models_43e8");
static_assert(offsetof(TileEventProcess, models_4708) == 0x4708, "models_4708");
static_assert(offsetof(TileEventProcess, models_4840) == 0x4840, "models_4840");
static_assert(offsetof(TileEventProcess, models_49a8) == 0x49a8, "models_49a8");
static_assert(offsetof(TileEventProcess, sets) == 0x4ae0, "sets");
static_assert(offsetof(TileEventProcess, member_4b20) == 0x4b20, "member_4b20");
static_assert(sizeof(TileEventProcess) == 0x6a70, "the size func_ov003_02227454 allocates");

/* The events' table. */
extern u8 data_ov003_0223cfe4[];
/* The session. */
extern NetSession *data_020ccf94;
/* The vtables: the process class's and the process's. */
extern const u32 data_020da13c[];
extern const u32 data_ov003_0223bc7c[];
/* The tile and its eight neighbours, each a byte: x + 8 in the high nibble, z + 8 in the low. */
extern const u8 data_ov003_02236670[9];

/* Starts an event of kind `kind` for `player` (in the table `table`), tile `tile`, point
 * `position`, id `id`, `angle` and `extra`: 1 when a free entry took it, 0 when there was none
 * or no town map. func_ov003_0222139c first makes the player 0 unless the session is linked. */
extern int func_ov003_022213f8(void *table, int player, const int *tile, const int *position, int kind, int id, int angle,
                               int extra);
extern int func_ov003_0222139c(void *table, int player, const int *tile, const int *position, int kind, int id, int angle,
                               int extra);
/* The process's member at 0x4b20: its destructor. */
extern void *func_ov003_02223b34(void *member);
/* The array helper and what it is handed: the game's own model object destructor. */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_02055764(void *model);

/* The event kinds started here. */
#define TILE_EVENT_KIND_3 3
#define TILE_EVENT_KIND_4 4
#define TILE_EVENT_KIND_5 5
#define TILE_EVENT_KIND_6 6
#define TILE_EVENT_KIND_7 7
#define TILE_EVENT_KIND_8 8
#define TILE_EVENT_KIND_9 9
#define TILE_EVENT_KIND_A 0xa
#define TILE_EVENT_KIND_B 0xb
#define TILE_EVENT_KIND_C 0xc
#define TILE_EVENT_KIND_D 0xd
#define TILE_EVENT_KIND_E 0xe

/* The ids of kinds 0xa and 0xe: by the town map's unit byte 9 at the tile. */
#define TILE_EVENT_ID_UNIT_0 0xfc
#define TILE_EVENT_ID_UNIT_SET 0xfd
/* The item code of an empty tile. */
#define TILE_EVENT_EMPTY 0xfff1

/* The town's map, or NULL. */
static AcreMap *tile_event_town(void)
{
    return (AcreMap *) (uintptr_t) AcreMap_Town();
}

/* The item at tile (x, z) of `map`, layer 0. */
static u16 *tile_event_item(AcreMap *map, int x, int z)
{
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    return AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x & 0xf, z & 0xf, 0);
}

/* Kinds 0xa and 0xe: on the town's map (0 without one), an event at the tile of `position`, its
 * point zero, its id by the tile's unit byte 9. */
static int tile_event_start_unit(int player, const Vec3 *position, int kind)
{
    AcreMap *map = tile_event_town();
    if (map == NULL) {
        return 0;
    }
    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) (const void *) position);
    int id = AcreTile_UnitByte09(map, tile[0], tile[1]) == 0 ? TILE_EVENT_ID_UNIT_0 : TILE_EVENT_ID_UNIT_SET;
    int point[3] = {0, 0, 0};
    return func_ov003_0222139c(data_ov003_0223cfe4, player, tile, point, kind, id, 0, 0);
}

/* func_ov003_02220b44: kind 0xe at the tile of `position` (the player of state 0x75). */
int TileEvent_StartKindE(int player, const Vec3 *position)
{
    return tile_event_start_unit(player, position, TILE_EVENT_KIND_E);
}
CLEAN_AS(func_ov003_02220b44, TileEvent_StartKindE)

/* func_ov003_02220bb0: kind 0xd with `id` at `tile` and `position`. */
void TileEvent_StartKindD(int player, int id, const TileChangesTile *tile, const Vec3 *position)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    func_ov003_022213f8(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_D, id, 0, 0);
}
CLEAN_AS(func_ov003_02220bb0, TileEvent_StartKindD)

/* func_ov003_02220bf0: on the town's map, of `tile` and its eight neighbours (in the order of
 * data_ov003_02236670) the first that is empty and has no tile change in layer 0
 * (TileChanges_FindAt) ends the search: when the town map's unit byte 4 there is set, `tile`
 * becomes it and the answer is 0. 2 otherwise, also without a town map. */
int TileEvent_FindFreeTileAround(TileChangesTile *tile)
{
    AcreMap *map = tile_event_town();
    int result = 2;
    if (map == NULL) {
        return result;
    }
    for (int i = 0; i < 9; i++) {
        u8 offset = data_ov003_02236670[i];
        int x = tile->x + ((offset >> 4) - 8);
        int z = tile->z + ((offset & 0xf) - 8);
        u16 *item = tile_event_item(map, x, z);
        if (item != NULL && *item == TILE_EVENT_EMPTY) {
            TileChangesTile at = {x, z};
            if (TileChanges_FindAt(&at, 0) < 0) {
                if (AcreTile_UnitByte04(map, x, z) != 0) {
                    tile->x = x;
                    tile->z = z;
                    result = 0;
                }
                break;
            }
        }
    }
    return result;
}
CLEAN_AS(func_ov003_02220bf0, TileEvent_FindFreeTileAround)

/* func_ov003_02220c8c: kind 0xc for this system's player (0 unless the session is linked), id
 * 0x156b for variant 0 else 0x137b. Its point: the position of player 4's actor moved by
 * `x` * 256 along x (zero without that actor), at height 0xa000; with the actor its tile is the
 * one of that point with z put on the first tile of its acre plus 1, and the point's z that
 * tile's centre's. (The sky shots of main.)
 * QUIRK: `x` is shifted left by 12 and back right by 4, so its top 12 bits are lost. */
int TileEvent_StartKindC(int variant, int x)
{
    Vec3 point = {0, 0, 0};
    int tile[2] = {0, 0};

    Actor *actor = SessionPlayers_ActorOf(4);
    if (actor != NULL) {
        point = actor->position;
        point.x = actor->position.x + ((int) ((u32) x << 12) >> 4);
        Position_Tile(&tile[0], &tile[1], (const Position *) (const void *) &point);
        tile[1] = tile[1] / 16 * 16 + 1;
        Vec3 centre;
        AcreTile_TileCentre(&centre, (u32) tile[0], (u32) tile[1]);
        point.z = centre.z;
    }
    point.y = 0xa000;
    int id = variant == 0 ? 0x156b : 0x137b;
    NetSession *session = data_020ccf94;
    int player = Session_IsLinked(session) ? session->local_slot : 0;
    int at[3] = {point.x, point.y, point.z};
    return func_ov003_022213f8(data_ov003_0223cfe4, player, tile, at, TILE_EVENT_KIND_C, id, 0, 0);
}
CLEAN_AS(func_ov003_02220c8c, TileEvent_StartKindC)

/* func_ov003_02220d50: kind 0xb with `id` at `tile` and its centre; its angle is the eighth of
 * the turn player 4's actor faces (AngleSector_Eight) as an angle, 0 without that actor. */
void TileEvent_StartKindB(int player, int id, const TileChangesTile *tile)
{
    Vec3 centre;
    int angle = 0;

    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    Actor *actor = SessionPlayers_ActorOf(4);
    if (actor != NULL) {
        /* The sector's three low bits as the top of a 16-bit angle, sign-extended. */
        angle = (s16) (u16) ((AngleSector_Eight(actor->angle[1]) & 7) << 13);
    }
    int point[3] = {centre.x, centre.y, centre.z};
    int at[2] = {tile->x, tile->z};
    func_ov003_022213f8(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_B, id, angle, 0);
}
CLEAN_AS(func_ov003_02220d50, TileEvent_StartKindB)

/* func_ov003_02220db4: kind 0xa at the tile of `position` (the player of state 0x67). */
int TileEvent_StartKindA(int player, const Vec3 *position)
{
    return tile_event_start_unit(player, position, TILE_EVENT_KIND_A);
}
CLEAN_AS(func_ov003_02220db4, TileEvent_StartKindA)

/* Whether kind 9 shows item `code` (its low 16 bits) as item 0x1408: the map item families A
 * and C (main/map_item.h, with 0x1a, 0x1c and 0x1d after family A and 0xa4 and 0xa5 after C)
 * and items 0x14fe-0x1517. */
static int tile_event_shown_as_1408(u16 code)
{
    return code <= 0x1a || code == 0x1c || code == 0x1d || (code >= 0x8a && code <= 0xa5) ||
           (code >= 0x14fe && code <= 0x1517);
}

/* func_ov003_02220e20: kind 9 with `id` at `tile` and `position`; an id of the codes of
 * tile_event_shown_as_1408, or exactly 0x1567, goes as 0x1408. (The tile requests of main.) */
void TileEvent_StartKind9(int player, int id, const TileChangesTile *tile, const Vec3 *position)
{
    if (tile_event_shown_as_1408((u16) id) || id == 0x1567) {
        id = 0x1408;
    }
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    func_ov003_022213f8(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_9, id, 0, 0);
}
CLEAN_AS(func_ov003_02220e20, TileEvent_StartKind9)

/* Whether kind 8 keeps the code at the tile as its id: the growth lines with the codes at their
 * last stage (0x25-0x6d, with 0x25 and 0x5c), 0xc7-0xcf and the four short lines (0x2b-0x2e,
 * 0x62-0x65, 0xd0-0xd3, 0xff-0x102) of main/map_item.h. */
static int tile_event_keeps_code(unsigned int code)
{
    return (code >= 0x25 && code <= 0x6d) || (code >= 0xc7 && code <= 0xd3) || (code >= 0xff && code <= 0x102);
}

/* func_ov003_02220f40: on the town's map (0 without one), kind 8 at the tile of `position`, its
 * point zero, `angle` (the player's yaw); the id is the code at the tile when
 * tile_event_keeps_code says so, else 0x2b. (The player of state 0x5e.) */
int TileEvent_StartKind8(int player, const Vec3 *position, int angle)
{
    AcreMap *map = tile_event_town();
    if (map == NULL) {
        return 0;
    }
    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) (const void *) position);
    u16 *item = tile_event_item(map, tile[0], tile[1]);
    int id = 0x2b;
    if (item != NULL && tile_event_keeps_code(*item)) {
        id = *item;
    }
    int point[3] = {0, 0, 0};
    return func_ov003_0222139c(data_ov003_0223cfe4, player, tile, point, TILE_EVENT_KIND_8, id, angle, 0);
}
CLEAN_AS(func_ov003_02220f40, TileEvent_StartKind8)

/* func_ov003_02221054: kind 7 with `id` at `tile` and `position`. */
void TileEvent_StartKind7(int player, u32 id, const TileChangesTile *tile, const Vec3 *position)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    func_ov003_022213f8(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_7, (int) id, 0, 0);
}
CLEAN_AS(func_ov003_02221054, TileEvent_StartKind7)

/* func_ov003_02221094: kind 6 with `id` at `tile` and `position`, and `extra`. */
void TileEvent_StartKind6(int player, int id, const TileChangesTile *tile, const Vec3 *position, int extra)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    func_ov003_022213f8(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_6, id, 0, extra);
}
CLEAN_AS(func_ov003_02221094, TileEvent_StartKind6)

/* func_ov003_022210d4: kind 5 with `id` at `tile` and `position`, `angle` and `extra`. */
void TileEvent_StartKind5(int player, int id, const TileChangesTile *tile, const Vec3 *position, short angle, int extra)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    func_ov003_022213f8(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_5, id, angle, extra);
}
CLEAN_AS(func_ov003_022210d4, TileEvent_StartKind5)

/* func_ov003_02221118: kind 4 with `id` at `tile`, its point zero. (The tile request grants of
 * main.) */
int TileEvent_StartKind4(int player, int id, const TileChangesTile *tile)
{
    int point[3] = {0, 0, 0};
    int at[2] = {tile->x, tile->z};
    return func_ov003_022213f8(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_4, id, 0, 0);
}
CLEAN_AS(func_ov003_02221118, TileEvent_StartKind4)

/* func_ov003_02221150: kind 3 at the tile of `position`, its point zero; the id is the item of
 * the tile change in layer 0 at that tile (TileChanges_FindAt), 0xfff1 without one. (Another
 * player of state 0x62.) */
void TileEvent_StartKind3(int player, const Vec3 *position)
{
    int tile[2] = {0, 0};
    int id = TILE_EVENT_EMPTY;

    Position_Tile(&tile[0], &tile[1], (const Position *) (const void *) position);
    TileChangesTile at = {tile[0], tile[1]};
    int index = TileChanges_FindAt(&at, 0);
    if (index >= 0) {
        const TileChange *change = (const TileChange *) (uintptr_t) TileChanges_At(index);
        if (change != NULL) {
            id = change->item;
        }
    }
    int point[3] = {0, 0, 0};
    func_ov003_0222139c(data_ov003_0223cfe4, player, tile, point, TILE_EVENT_KIND_3, id, 0, 0);
}
CLEAN_AS(func_ov003_02221150, TileEvent_StartKind3)

/* The process's members' destructors, last to first, and the process's. */
static void tile_event_destroy_process(TileEventProcess *process)
{
    process->process.vtable = data_ov003_0223bc7c;
    func_ov003_02223b34(process->member_4b20);
    for (int i = 3; i >= 0; i--) {
        ModelSet_Destruct(&process->sets[i]);
    }
    __cxa_vec_cleanup(process->models_49a8, 2, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_4840, 2, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_4708, 2, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_43e8, 5, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_3068, 0x20, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_2df0, 4, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_1590, 0x28, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_11e8, 6, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_1014, 3, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_0c6c, 6, sizeof(ModelObject), func_02055764);
    __cxa_vec_cleanup(process->models_0174, 0x12, sizeof(ModelObject), func_02055764);
    process->process.vtable = data_020da13c;
    Process_Destruct(&process->process);
}

/* func_ov003_022208ec (vtable slot 16 of 0x0223bc7c): destroys the process; returns it. */
TileEventProcess *TileEvent_DestroyProcess(TileEventProcess *process)
{
    tile_event_destroy_process(process);
    return process;
}
CLEAN_AS(func_ov003_022208ec, TileEvent_DestroyProcess)

/* func_ov003_02220a14 (vtable slot 17 of 0x0223bc7c): destroys the process and frees it;
 * returns it. */
TileEventProcess *TileEvent_DestroyAndFreeProcess(TileEventProcess *process)
{
    tile_event_destroy_process(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_ov003_02220a14, TileEvent_DestroyAndFreeProcess)
