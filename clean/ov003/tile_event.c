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
#include "autoload_2/matrix.h"
#include "field_actor.h" /* FieldActor_PlayerFacePoint */
#include "itcm/vector.h" /* Vec_Add */
#include "main/block_020ba298.h"
#include "main/effect_system.h"
#include "main/field_collision.h"
#include "main/globe.h"
#include "main/map_item.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sound_emitter.h"
#include "main/tile_effects.h"
#include "main/tile_requests.h"
#include "town_insect.h"
#include "autoload_2/sound_emitter_class.h"
#include "growth_model.h" /* GrowthModels_Construct */

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
extern TileEventEntry data_ov003_0223cfe4[];
/* The session. */
extern NetSession *data_020ccf94;
/* The vtables: the process class's and the process's. */
extern const u32 data_020da13c[];
extern const u32 data_ov003_0223bc7c[];
/* The tile and its eight neighbours, each a byte: x + 8 in the high nibble, z + 8 in the low. */
extern const u8 data_ov003_02236670[9];

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
    return TileEvent_StartLocal(data_ov003_0223cfe4, player, tile, point, kind, id, 0, 0);
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
    TileEvent_Start(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_D, id, 0, 0);
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
    return TileEvent_Start(data_ov003_0223cfe4, player, tile, at, TILE_EVENT_KIND_C, id, 0, 0);
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
    TileEvent_Start(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_B, id, angle, 0);
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
    TileEvent_Start(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_9, id, 0, 0);
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
    return TileEvent_StartLocal(data_ov003_0223cfe4, player, tile, point, TILE_EVENT_KIND_8, id, angle, 0);
}
CLEAN_AS(func_ov003_02220f40, TileEvent_StartKind8)

/* func_ov003_02221054: kind 7 with `id` at `tile` and `position`. */
void TileEvent_StartKind7(int player, u32 id, const TileChangesTile *tile, const Vec3 *position)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    TileEvent_Start(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_7, (int) id, 0, 0);
}
CLEAN_AS(func_ov003_02221054, TileEvent_StartKind7)

/* func_ov003_02221094: kind 6 with `id` at `tile` and `position`, and `extra`. */
void TileEvent_StartKind6(int player, int id, const TileChangesTile *tile, const Vec3 *position, int extra)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    TileEvent_Start(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_6, id, 0, extra);
}
CLEAN_AS(func_ov003_02221094, TileEvent_StartKind6)

/* func_ov003_022210d4: kind 5 with `id` at `tile` and `position`, `angle` and `extra`. */
void TileEvent_StartKind5(int player, int id, const TileChangesTile *tile, const Vec3 *position, short angle, int extra)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    TileEvent_Start(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_5, id, angle, extra);
}
CLEAN_AS(func_ov003_022210d4, TileEvent_StartKind5)

/* func_ov003_02221118: kind 4 with `id` at `tile`, its point zero. (The tile request grants of
 * main.) */
int TileEvent_StartKind4(int player, int id, const TileChangesTile *tile)
{
    int point[3] = {0, 0, 0};
    int at[2] = {tile->x, tile->z};
    return TileEvent_Start(data_ov003_0223cfe4, player, at, point, TILE_EVENT_KIND_4, id, 0, 0);
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
    TileEvent_StartLocal(data_ov003_0223cfe4, player, tile, point, TILE_EVENT_KIND_3, id, 0, 0);
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

/* ---- The events themselves: starting one, each kind's start and step, drawing them. */

static_assert(sizeof(TileEventEntry) == 0xa4, "a table entry");
static_assert(offsetof(TileEventEntry, tile) == 0x10, "tile");
static_assert(offsetof(TileEventEntry, scale) == 0x3c, "scale");
static_assert(offsetof(TileEventEntry, angle) == 0x48, "angle");
static_assert(offsetof(TileEventEntry, point) == 0x54, "point");
static_assert(offsetof(TileEventEntry, sound) == 0x60, "sound");
static_assert(offsetof(TileEventEntry, finish_change) == 0xa0, "finish_change");
static_assert(offsetof(TileEventDraw, bent) == 0x04, "bent");
static_assert(offsetof(TileEventDraw, sum) == 0x28, "sum");
static_assert(offsetof(TileEventDraw, growth_point) == 0x4c, "growth_point");

/* The process (made by func_ov003_02227454); the drawers take it. */
extern TileEventProcess *data_ov003_0223cf70;
/* The matrix the drawers are handed (built here in place). */
extern Mtx43 data_021fbe48;
/* NitroSDK's table of sines and cosines, by angle >> 4. */
extern const fx16 FX_SinCosTable_[];
/* Kind 12's point for its effects (TileEvent_PlaceKind12Effect reads it). */
extern Vec3 data_ov003_0223cf88;
/* The setup handed with kind 12's effect sets. */
extern void *data_020e25d4;
/* Kind 4's scales by frame, 17 each: x and z, then y. */
extern const fx32 data_ov003_02236c18[];
extern const fx32 data_ov003_02236c5c[];

/* NitroSDK's VEC_Add. */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
/* Writes `item` to tile (x, z) of the town's map (data_021c80bc) and updates the tile's marks
 * (by func_0204f380 when the item is not 0xfff1 and `flag` is set, else func_0204f31c). */
extern void func_ov003_02224140(int x, int z, u16 item, int flag);
/* The setup kind 12 hands EffectSystem_StartModel: the game's symbol of TileEvent_PlaceKind12Effect. */
extern void func_ov003_02221c9c(void *transform);
/* The drawers of the codes (the process, the record, the matrix). */
extern void *func_ov003_02225404(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_02225598(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_02225538(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_02225474(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_022252fc(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_02225608(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_02225768(TileEventProcess *process, TileEventDraw *draw, int x, int z, Vec3 *point, Mtx43 matrix);
extern void *func_ov003_02225694(TileEventProcess *process, TileEventDraw *draw, int x, int z, Mtx43 matrix);
extern void *func_ov003_022253a8(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_02225240(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
extern void *func_ov003_022251e8(TileEventProcess *process, TileEventDraw *draw, Mtx43 matrix);
/* The drawer of items (codes of kinds 1, 3 and 4). */
extern int func_ov003_02225da0(TileEventProcess *process, int id, Vec3 *point, void *countdown, Vec3 *scale, short a, short b,
                               short c);

/* The sounds the kinds play. */
#define TILE_EVENT_SOUND_LAND 0x70
#define TILE_EVENT_VOLUME 0x7f
/* What an entry ends as. */
#define TILE_EVENT_KIND_ENDED 15
/* 1.0 in 20.12 fixed point. */
#define TILE_EVENT_ONE 0x1000

static SoundEmitter *tile_event_sound(TileEventEntry *entry)
{
    return (SoundEmitter *) (void *) entry->sound;
}

static fx32 tile_event_sin(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2];
}

static fx32 tile_event_cos(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2 + 1];
}

/* Items 0x1492-0x14fd: the kinds play their own sounds for them. */
static int tile_event_is_14xx(u16 code)
{
    return code >= 0x1492 && code <= 0x14fd;
}

static void tile_event_set_scale(TileEventEntry *entry, fx32 x, fx32 y, fx32 z)
{
    entry->scale.x = x;
    entry->scale.y = y;
    entry->scale.z = z;
}

static void tile_event_stop(TileEventEntry *entry)
{
    entry->velocity.x = 0;
    entry->velocity.y = 0;
    entry->velocity.z = 0;
}

/* The position set from `from` a word at a time, x first, as the original does: `from` may
 * overlap the entry. */
static void tile_event_place(TileEventEntry *entry, const Vec3 *from)
{
    entry->position.x = from->x;
    entry->position.y = from->y;
    entry->position.z = from->z;
}

/* The centre of `tile`, at the height of the ground. */
static void tile_event_centre(Vec3 *centre, const TileChangesTile *tile)
{
    AcreTile_TileCentre(centre, (u32) tile->x, (u32) tile->z);
}

/* An entry made free: the fields TileEvent_Clear and TileEvent_End set. */
static void tile_event_free(TileEventEntry *entry)
{
    entry->active = 0;
    entry->kind = TILE_EVENT_KIND_ENDED;
    entry->id = TILE_EVENT_EMPTY;
    entry->under = TILE_EVENT_EMPTY;
}

/* Kinds 3, 2 and 1 at the tile of `position`, as tile_event_start_unit, with `extra`. */
static int tile_event_start_unit_kind(int player, const Vec3 *position, int kind, int extra)
{
    AcreMap *map = tile_event_town();
    if (map == NULL) {
        return 0;
    }
    int tile[2] = {0, 0};
    Position_Tile(&tile[0], &tile[1], (const Position *) (const void *) position);
    int id = AcreTile_UnitByte09(map, tile[0], tile[1]) == 0 ? TILE_EVENT_ID_UNIT_0 : TILE_EVENT_ID_UNIT_SET;
    int point[3] = {0, 0, 0};
    return TileEvent_StartLocal(data_ov003_0223cfe4, player, tile, point, kind, (u16) id, 0, extra);
}

/* func_ov003_022211bc: kind 3 at the tile of `position` (the player of state 0x62). */
int TileEvent_StartUnitKind3(int player, const Vec3 *position)
{
    return tile_event_start_unit_kind(player, position, TILE_EVENT_KIND_3, 0);
}
CLEAN_AS(func_ov003_022211bc, TileEvent_StartUnitKind3)

/* func_ov003_02221228: kind 2 at the tile of `position` (the player of state 0x73). */
int TileEvent_StartUnitKind2(int player, const Vec3 *position)
{
    return tile_event_start_unit_kind(player, position, 2, 0);
}
CLEAN_AS(func_ov003_02221228, TileEvent_StartUnitKind2)

/* func_ov003_02221294: kind 1 at the tile of `position`, with `extra` (the player of state
 * 0x5f hands its kind). */
int TileEvent_StartUnitKind1(int player, const Vec3 *position, int extra)
{
    return tile_event_start_unit_kind(player, position, 1, extra);
}
CLEAN_AS(func_ov003_02221294, TileEvent_StartUnitKind1)

/* func_ov003_02221304: kind 0 with `id` at `tile` and `position`. (The item requests of
 * main.) */
int TileEvent_StartKind0(u32 player, u32 id, const TileChangesTile *tile, const Vec3 *position)
{
    int point[3] = {position->x, position->y, position->z};
    int at[2] = {tile->x, tile->z};
    return TileEvent_Start(data_ov003_0223cfe4, (int) player, at, point, 0, (u16) id, 0, 0);
}
CLEAN_AS(func_ov003_02221304, TileEvent_StartKind0)

/* func_ov003_02221340: the first active event of `player` at `tile` is ended (TileEvent_End);
 * 1 when it was to finish its tile change (which it does in ending), else 0. (Main asks before
 * letting go of a tile change.) */
int TileEvent_EndAt(int player, const TileChangesTile *tile)
{
    TileEventEntry *entry = &data_ov003_0223cfe4[player * TILE_EVENT_PLAYER_ENTRIES];
    int finished = 0;
    for (int i = 0; i < TILE_EVENT_PLAYER_ENTRIES; i++, entry++) {
        if (entry->active != 0 && entry->tile.x == tile->x && entry->tile.z == tile->z) {
            if (entry->finish_change != 0) {
                finished = 1;
            }
            TileEvent_End(entry);
            break;
        }
    }
    return finished;
}
CLEAN_AS(func_ov003_02221340, TileEvent_EndAt)

/* func_ov003_0222139c: TileEvent_Start for this system's player: `player` becomes 0 unless the
 * session is linked. */
int TileEvent_StartLocal(TileEventEntry *table, int player, const int *tile, const int *point, int kind, u16 id, s16 angle,
                         int extra)
{
    if (!Session_IsLinked(data_020ccf94)) {
        player = 0;
    }
    return TileEvent_Start(table, player, tile, point, kind, id, angle, extra);
}
CLEAN_AS(func_ov003_0222139c, TileEvent_StartLocal)

/* func_ov003_022213f8: on the town's map, an event of `kind` begins in a free entry of
 * `player` (TileEvent_Begin) at `tile` (x, z) and `point` (x, y, z): 1, or 0 without a town map
 * or a free entry. */
int TileEvent_Start(TileEventEntry *table, int player, const int *tile, const int *point, int kind, u16 id, s16 angle,
                    int extra)
{
    AcreMap *map = tile_event_town();
    if (map == NULL) {
        return 0;
    }
    TileEventEntry *entry = TileEvent_FreeEntry(table, player);
    if (entry == NULL) {
        return 0;
    }
    TileEvent_Begin(entry, player, tile, point, kind, id, map, angle, extra);
    return 1;
}
CLEAN_AS(func_ov003_022213f8, TileEvent_Start)

/* func_ov003_02221464: the first of `player`'s four entries that is not active, or NULL. */
TileEventEntry *TileEvent_FreeEntry(TileEventEntry *table, int player)
{
    TileEventEntry *entry = &table[player * TILE_EVENT_PLAYER_ENTRIES];
    for (int i = 0; i < TILE_EVENT_PLAYER_ENTRIES; i++, entry++) {
        if (entry->active == 0) {
            return entry;
        }
    }
    return NULL;
}
CLEAN_AS(func_ov003_02221464, TileEvent_FreeEntry)

/* func_ov003_02221488: every active event ended, every entry's sound let go (vtable slot 0x10
 * of its emitter). */
void TileEvent_ReleaseAll(TileEventEntry *entries)
{
    for (int i = 0; i < TILE_EVENT_ENTRIES; i++, entries++) {
        if (entries->active != 0) {
            TileEvent_End(entries);
        }
        SoundEmitter_Vfunc10B(tile_event_sound(entries));
    }
}
CLEAN_AS(func_ov003_02221488, TileEvent_ReleaseAll)

/* Codes drawn by func_ov003_02225598: the map item families A and C (main/map_item.h), with
 * 0x1c and 0xa5. */
static int tile_event_drawn_as_family(u16 code)
{
    return code <= 0x19 || code == 0x1c || (code >= 0x8a && code <= 0xa3) || code == 0xa5;
}

/* Codes drawn by func_ov003_02225768 with the tile: the growth lines and 0x66-0x6d. */
static int tile_event_drawn_as_growth(u16 code)
{
    return (code >= 0x26 && code <= 0x2a) || (code >= 0x2f && code <= 0x5b) || (code >= 0x5d && code <= 0x61) ||
           (code >= 0x66 && code <= 0x6d) || (code >= 0xc8 && code <= 0xcf);
}

/* Codes drawn by func_ov003_02225608: the four short lines. */
static int tile_event_drawn_as_short(u16 code)
{
    return (code >= 0x2b && code <= 0x2e) || (code >= 0xff && code <= 0x102) || (code >= 0x62 && code <= 0x65) ||
           (code >= 0xd0 && code <= 0xd3);
}

/* One entry's code drawn: item codes (kinds 1, 3 and 4) by func_ov003_02225da0 at the point
 * at scale 1.0; map codes in the matrix (the point bent over the globe, turned by the bend about
 * X, scaled by the entry's scale) by the drawer of their set; other codes are not drawn. */
static void tile_event_draw(TileEventEntry *entry, TileEventDraw *draw)
{
    Vec_Add(&draw->sum, &entry->position, &entry->offset);
    draw->point = draw->sum;
    draw->id = entry->id;
    switch ((draw->id & 0xf000) >> 12) {
        case 1:
        case 3:
        case 4:
            draw->item_point = draw->point;
            draw->item_scale.x = TILE_EVENT_ONE;
            draw->item_scale.y = TILE_EVENT_ONE;
            draw->item_scale.z = TILE_EVENT_ONE;
            func_ov003_02225da0(data_ov003_0223cf70, entry->id, &draw->item_point, (void *) (intptr_t) entry->countdown,
                                &draw->item_scale, 0, 0, 0);
            return;
    }

    draw->scale = entry->scale;
    int tilt = Globe_BendFar(&draw->bent, &draw->point);
    Mtx43_Translation(&data_021fbe48, draw->bent.x, draw->bent.y, draw->bent.z);
    Mtx43_RotateX(&data_021fbe48, tilt);
    Mtx43_Scale(&data_021fbe48, draw->scale.x, draw->scale.y, draw->scale.z);

    u16 code = draw->id;
    if (code >= 0x1f && code <= 0x24) {
        func_ov003_02225404(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (tile_event_drawn_as_family(code)) {
        func_ov003_02225598(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (code >= 0x6e && code <= 0x87) {
        /* Family B. */
        func_ov003_02225538(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (code == 0x1a || code == 0x1b || code == 0x1d || code == 0x1e || code == 0x88 || code == 0x89) {
        func_ov003_02225474(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (code == TILE_EVENT_ID_UNIT_0 || code == TILE_EVENT_ID_UNIT_SET) {
        func_ov003_022252fc(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (tile_event_drawn_as_short(code)) {
        func_ov003_02225608(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (tile_event_drawn_as_growth(code)) {
        draw->growth_point = draw->point;
        func_ov003_02225768(data_ov003_0223cf70, draw, entry->tile.x, entry->tile.z, &draw->growth_point, data_021fbe48);
    } else if (code == 0x25 || code == 0x5c || code == 0xc7) {
        func_ov003_02225694(data_ov003_0223cf70, draw, entry->tile.x, entry->tile.z, data_021fbe48);
    } else if (code >= 0xe3 && code <= 0xfb) {
        func_ov003_022253a8(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (code >= 0xd4 && code <= 0xe1) {
        func_ov003_02225240(data_ov003_0223cf70, draw, data_021fbe48);
    } else if (code >= 0xa7 && code <= 0xc6) {
        func_ov003_022251e8(data_ov003_0223cf70, draw, data_021fbe48);
    }
}

/* func_ov003_022214b4: every active entry with a code drawn (tile_event_draw). */
void TileEvent_DrawAll(TileEventEntry *entries)
{
    TileEventDraw draw;
    draw.id = TILE_EVENT_EMPTY;
    for (int i = 0; i < TILE_EVENT_ENTRIES; i++, entries++) {
        if (entries->active != 0 && entries->id != TILE_EVENT_EMPTY) {
            tile_event_draw(entries, &draw);
        }
    }
}
CLEAN_AS(func_ov003_022214b4, TileEvent_DrawAll)

/* func_ov003_02221948: each active entry counts a frame and runs its kind's step; then its
 * sound follows its position.
 * QUIRK: whether the session is linked is asked first and not used. */
void TileEvent_StepAll(TileEventEntry *entries)
{
    Session_IsLinked(data_020ccf94);
    for (int i = 0; i < TILE_EVENT_ENTRIES; i++, entries++) {
        if (entries->active == 0) {
            continue;
        }
        entries->frames++;
        switch (entries->kind) {
            case 0:
            case TILE_EVENT_KIND_D:
                TileEvent_StepKind0(entries);
                break;
            case 1:
            case 2:
                TileEvent_StepKind1(entries);
                break;
            case TILE_EVENT_KIND_3:
            case TILE_EVENT_KIND_E:
                TileEvent_StepKind3(entries);
                break;
            case TILE_EVENT_KIND_4:
                TileEvent_StepKind4(entries);
                break;
            case TILE_EVENT_KIND_5:
                TileEvent_StepKind5(entries);
                break;
            case TILE_EVENT_KIND_6:
                TileEvent_StepKind6(entries);
                break;
            case TILE_EVENT_KIND_7:
                TileEvent_StepKind7(entries);
                break;
            case TILE_EVENT_KIND_8:
                TileEvent_StepKind8(entries);
                break;
            case TILE_EVENT_KIND_9:
                TileEvent_StepKind9(entries);
                break;
            case TILE_EVENT_KIND_A:
                TileEvent_StepKind10(entries);
                break;
            case TILE_EVENT_KIND_B:
                TileEvent_StepKind11(entries);
                break;
            case TILE_EVENT_KIND_C:
                TileEvent_StepKind12(entries);
                break;
        }
        Vec3 at = entries->position;
        SoundEmitter_UpdateAtB(tile_event_sound(entries), &at);
    }
}
CLEAN_AS(func_ov003_02221948, TileEvent_StepAll)

/* func_ov003_02221a38: every entry free (not active, code 0xfff1) and its sound stopped. */
void TileEvent_InitAll(TileEventEntry *entries)
{
    for (int i = 0; i < TILE_EVENT_ENTRIES; i++, entries++) {
        entries->active = 0;
        entries->id = TILE_EVENT_EMPTY;
        SoundEmitter_StopB(tile_event_sound(entries));
    }
}
CLEAN_AS(func_ov003_02221a38, TileEvent_InitAll)

/* func_ov003_02221a64: kind 0xe's start: at the tile's centre, its code 0xfc or 0xfd by the
 * town map's unit byte 9 there, scale 1.0, still; the tile emptied on the map, and the item of
 * the tile change at the tile in layer 0 made 0xfff1. */
void TileEvent_InitKind14(TileEventEntry *entry, const TileChangesTile *tile, struct AcreMap *map)
{
    tile_event_centre(&entry->position, tile);
    entry->id = AcreTile_UnitByte09(map, tile->x, tile->z) == 0 ? TILE_EVENT_ID_UNIT_0 : TILE_EVENT_ID_UNIT_SET;
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    tile_event_stop(entry);
    func_ov003_02224140(tile->x, tile->z, TILE_EVENT_EMPTY, 0);
    TileChangesTile at = entry->tile;
    int index = TileChanges_FindAt(&at, 0);
    if (index >= 0) {
        ((TileChange *) (uintptr_t) TileChanges_At(index))->item = TILE_EVENT_EMPTY;
    }
}
CLEAN_AS(func_ov003_02221a64, TileEvent_InitKind14)

/* func_ov003_02221ad8: kind 0xc's step, by the ground under the entry (CollisionGround_Init):
 *
 * - over ground with unk_30 set: falling until below the ground's limit, where effect sets
 *   0x45 and 0x4a and effect model 2 start at the point on the limit (data_ov003_0223cf88), it
 *   sinks 2.0 and waits 12 frames (Block020ba298_SetByte7Or8(1)); then
 *   Block020ba298_SetByte6, the player faces it, and it ends without finishing its change;
 * - else: falling to the ground (height 0), then thrown up (1.0) towards the centre of a free
 *   tile around (TileEvent_FindFreeTileAround, in 8 frames; Block020ba298_SetByte7Or8(0)),
 *   falling with gravity 0.25 per frame; on the ground again Block020ba298_SetByte6, and when a
 *   tile was found its code is put there (item 0x137b also sets flag 0x30 of the current player
 *   record); it ends without finishing its change. */
void TileEvent_StepKind12(TileEventEntry *entry)
{
    CollisionGround ground;
    CollisionGround_Init(&ground, &entry->position, 0, 0);

    if (ground.unk_30 != 0) {
        if (entry->state == 0) {
            VEC_Add(&entry->position, &entry->velocity, &entry->position);
            fx32 limit = ground.limit;
            if (entry->position.y < limit) {
                entry->velocity.y = 0;
                data_ov003_0223cf88 = entry->position;
                data_ov003_0223cf88.y = limit;
                EffectSystem_StartSet(0x45, &data_ov003_0223cf88, NULL, &data_020e25d4);
                EffectSystem_StartSet(0x4a, &data_ov003_0223cf88, NULL, &data_020e25d4);
                EffectSystem_StartModel(2, func_ov003_02221c9c);
                entry->state = 1;
                entry->counter = 0xc;
                entry->position.y -= 0x2000;
                Block020ba298_SetByte7Or8(1);
            }
        } else {
            entry->counter--;
            if (entry->counter < 0) {
                Block020ba298_SetByte6();
                FieldActor_PlayerFacePoint(&entry->position);
                entry->finish_change = 0;
                TileEvent_End(entry);
            }
        }
    } else if (entry->state == 0) {
        VEC_Add(&entry->position, &entry->velocity, &entry->position);
        if (entry->position.y < 0) {
            entry->position.y = 0;
            entry->counter = (s16) TileEvent_FindFreeTileAround(&entry->tile);
            Vec3 centre;
            tile_event_centre(&centre, &entry->tile);
            fx32 dz = (centre.z - entry->position.z) / 8;
            entry->velocity.x = (centre.x - entry->position.x) / 8;
            entry->velocity.y = TILE_EVENT_ONE;
            entry->velocity.z = dz;
            entry->state = 1;
            Block020ba298_SetByte7Or8(0);
        }
    } else {
        entry->velocity.y -= 0x400;
        VEC_Add(&entry->position, &entry->velocity, &entry->position);
        if (entry->position.y < 0) {
            entry->position.y = 0;
            tile_event_stop(entry);
            Block020ba298_SetByte6();
            if (entry->counter == 0) {
                if (entry->id == 0x137b) {
                    PlayerRecord_SetFlag(PlayerRecords_Current(), 0x30);
                }
                func_ov003_02224140(entry->tile.x, entry->tile.z, entry->id, 0);
            }
            entry->finish_change = 0;
            TileEvent_End(entry);
        }
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov003_02221ad8, TileEvent_StepKind12)

/* func_ov003_02221c80: kind 0xc's start: at `point`, falling at 0.75 per frame. */
void TileEvent_InitKind12(TileEventEntry *entry, const Vec3 *point)
{
    tile_event_place(entry, point);
    entry->velocity.x = 0;
    entry->velocity.y = -0xc00;
    entry->velocity.z = 0;
}
CLEAN_AS(func_ov003_02221c80, TileEvent_InitKind12)

/* func_ov003_02221c9c (kind 0xc's setup of effect model 2): its point, after the first word, is
 * data_ov003_0223cf88. */
void TileEvent_PlaceKind12Effect(int *transform)
{
    transform[1] = data_ov003_0223cf88.x;
    transform[2] = data_ov003_0223cf88.y;
    transform[3] = data_ov003_0223cf88.z;
}
CLEAN_AS(func_ov003_02221c9c, TileEvent_PlaceKind12Effect)

/* func_ov003_02221cb4: kind 0xb's step: half a turn of a hop in 8 frames from `point`, half a
 * tile high at its top, along the direction `angle` (x by its sine, z by its cosine); it ends
 * once the phase passes the half turn. */
void TileEvent_StepKind11(TileEventEntry *entry)
{
    entry->counter = (s16) (entry->counter + 0x2000);
    fx32 lift = tile_event_sin((u16) entry->counter) >> 1;
    Vec3 step;
    step.x = (lift * tile_event_sin((u16) entry->angle)) >> 12;
    step.y = 0;
    step.z = (tile_event_cos((u16) entry->angle) * lift) >> 12;
    Vec3 at;
    Vec_Add(&at, &entry->point, &step);
    entry->position = at;
    if (entry->counter < 0) {
        TileEvent_End(entry);
    }
}
CLEAN_AS(func_ov003_02221cb4, TileEvent_StepKind11)

/* func_ov003_02221d3c: kind 0xb's start: scale 1.0; the tile emptied on the map. */
void TileEvent_InitKind11(TileEventEntry *entry, const TileChangesTile *tile)
{
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    func_ov003_02224140(tile->x, tile->z, TILE_EVENT_EMPTY, 0);
}
CLEAN_AS(func_ov003_02221d3c, TileEvent_InitKind11)

/* func_ov003_02221d64: kind 0xa's step: on frames 6-10 and from 18 on the scale's x and z
 * shrink by 410/4096; at 0 it ends. */
void TileEvent_StepKind10(TileEventEntry *entry)
{
    u16 frames = entry->frames;
    if ((frames >= 6 && frames <= 10) || frames >= 18) {
        entry->scale.x -= 410;
    }
    if (entry->scale.x <= 0) {
        entry->scale.x = 0;
        TileEvent_End(entry);
    }
    entry->scale.z = entry->scale.x;
}
CLEAN_AS(func_ov003_02221d64, TileEvent_StepKind10)

/* func_ov003_02221da0: kind 0xa's start: at the tile's centre, scale 1.0, still; the tile
 * change let go at once (TileEvent_LetGoChange). */
void TileEvent_InitKind10(TileEventEntry *entry, const TileChangesTile *tile)
{
    tile_event_centre(&entry->position, tile);
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    tile_event_stop(entry);
    TileEvent_LetGoChange(entry);
}
CLEAN_AS(func_ov003_02221da0, TileEvent_InitKind10)

/* A fall with gravity 0.25 per frame; true when it took the entry below the ground. */
static int tile_event_fall(TileEventEntry *entry)
{
    entry->velocity.y -= 0x400;
    VEC_Add(&entry->position, &entry->velocity, &entry->position);
    return entry->position.y < 0;
}

/* func_ov003_02221dd0: kind 9's step: the scale's x and z grow by 410/4096 a frame to 1.0; it
 * falls; on the ground (height 0) it stops and ends, with sound 0x70 the first time when the
 * item under it is one of 0x1492-0x14fd. */
void TileEvent_StepKind9(TileEventEntry *entry)
{
    entry->scale.x += 0x19a;
    if (entry->scale.x >= TILE_EVENT_ONE) {
        entry->scale.x = TILE_EVENT_ONE;
    }
    entry->scale.z = entry->scale.x;
    if (tile_event_fall(entry)) {
        entry->position.y = 0;
        tile_event_stop(entry);
        if (entry->state == 0 && tile_event_is_14xx(entry->under)) {
            SoundEmitter_PlayB(tile_event_sound(entry), TILE_EVENT_SOUND_LAND, TILE_EVENT_VOLUME, 0);
        }
        entry->state = 1;
        TileEvent_End(entry);
    }
}
CLEAN_AS(func_ov003_02221dd0, TileEvent_StepKind9)

/* func_ov003_02221e78: kind 9's start: from `from`, thrown up (1.0) towards the tile's centre in
 * 8 frames, its scale's x and z 0; it will not finish its tile change; sound 0x74 for items
 * 0x1492-0x14fd, else 0x75. */
void TileEvent_InitKind9(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from, u16 id)
{
    Vec3 centre;
    tile_event_centre(&centre, tile);
    fx32 dz = (centre.z - from->z) / 8;
    entry->velocity.x = (centre.x - from->x) / 8;
    entry->velocity.y = TILE_EVENT_ONE;
    entry->velocity.z = dz;
    tile_event_place(entry, from);
    tile_event_set_scale(entry, 0, TILE_EVENT_ONE, 0);
    entry->finish_change = 0;
    SoundEmitter_PlayB(tile_event_sound(entry), tile_event_is_14xx(id) ? 0x74 : 0x75, TILE_EVENT_VOLUME, 0);
}
CLEAN_AS(func_ov003_02221e78, TileEvent_InitKind9)

/* func_ov003_02221f14: kind 8's step: it falls; on the ground it stops and ends. */
void TileEvent_StepKind8(TileEventEntry *entry)
{
    if (!tile_event_fall(entry)) {
        return;
    }
    entry->position.y = 0;
    tile_event_stop(entry);
    TileEvent_End(entry);
}
CLEAN_AS(func_ov003_02221f14, TileEvent_StepKind8)

/* func_ov003_02221f50: kind 8's start: at the tile's centre, thrown up (1.0) and 0.25 a frame
 * along `angle` (x by its sine, z by its cosine), scale 1.0; it will not finish its tile change;
 * the tile emptied on the map. */
void TileEvent_InitKind8(TileEventEntry *entry, const TileChangesTile *tile, int angle)
{
    tile_event_centre(&entry->position, tile);
    entry->velocity.x = (tile_event_sin((u16) angle) * 0x400) >> 12;
    entry->velocity.y = TILE_EVENT_ONE;
    entry->velocity.z = (tile_event_cos((u16) angle) * 0x400) >> 12;
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    entry->finish_change = 0;
    func_ov003_02224140(tile->x, tile->z, TILE_EVENT_EMPTY, 0);
}
CLEAN_AS(func_ov003_02221f50, TileEvent_InitKind8)

/* func_ov003_02221fb0: kind 7's step: it falls and bounces once (1.0 up), then lands; 20
 * frames on the event's insect is put at it (TownInsect_SetEventPoint); 30 frames later it
 * waits for its countdown to pass 0 and is made free without letting go of its change
 * (TileEvent_Clear). */
void TileEvent_StepKind7(TileEventEntry *entry)
{
    switch (entry->state) {
        case 0:
            if (tile_event_fall(entry)) {
                entry->position.y = 0;
                entry->velocity.x = 0;
                entry->velocity.y = TILE_EVENT_ONE;
                entry->velocity.z = 0;
                entry->state = 1;
            }
            break;
        case 1:
            if (tile_event_fall(entry)) {
                entry->position.y = 0;
                tile_event_stop(entry);
                entry->state = 2;
                entry->counter = 0x14;
            }
            break;
        case 2:
            entry->counter--;
            if (entry->counter < 0) {
                TownInsect_SetEventPoint((int *) (void *) &entry->position);
                entry->counter = 0x1e;
                entry->state = 3;
            }
            break;
        case 3:
            entry->counter--;
            if (entry->counter < 0) {
                entry->state = 4;
            }
            break;
        default:
            entry->countdown--;
            if (entry->countdown < 0) {
                TileEvent_Clear(entry);
            }
            break;
    }
}
CLEAN_AS(func_ov003_02221fb0, TileEvent_StepKind7)

/* func_ov003_022220a4: kind 7's start: from `from`, thrown up 0.5 and 0.1875 a frame along z,
 * scale 1.0; sound 0x7d6; the tile change let go at once, and main told no item may be dropped
 * (TileRequests_ForbidItemDrop). */
void TileEvent_InitKind7(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from)
{
    (void) tile;
    entry->velocity.x = 0;
    entry->velocity.y = 0x800;
    entry->velocity.z = 0x300;
    tile_event_place(entry, from);
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    SoundEmitter_PlayB(tile_event_sound(entry), 0x7d6, TILE_EVENT_VOLUME, 0);
    TileEvent_LetGoChange(entry);
    TileRequests_ForbidItemDrop();
}
CLEAN_AS(func_ov003_022220a4, TileEvent_InitKind7)

/* func_ov003_022220f4: kind 6's step: it moves by its velocity, swaying along x by half the sine
 * of a phase stepped 0x888 a frame (in `frames`); below the ground it stops and ends. */
void TileEvent_StepKind6(TileEventEntry *entry)
{
    VEC_Add(&entry->position, &entry->velocity, &entry->position);
    entry->frames += 0x888;
    entry->offset.x = tile_event_sin(entry->frames) >> 1;
    if (entry->position.y < 0) {
        entry->position.y = 0;
        tile_event_stop(entry);
        TileEvent_End(entry);
    }
}
CLEAN_AS(func_ov003_022220f4, TileEvent_StepKind6)

/* func_ov003_0222214c: kind 6's start: from `from`, moving to the tile's centre at height 0 in
 * 30 frames, scale 1.0; with `angle` set the tile change is let go at once; sound 0x7eb. */
void TileEvent_InitKind6(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from)
{
    Vec3 centre;
    tile_event_centre(&centre, tile);
    fx32 dz = (centre.z - from->z) / 30;
    fx32 dy = -(from->y / 30);
    fx32 dx = (centre.x - from->x) / 30;
    entry->velocity.x = dx;
    entry->velocity.y = dy;
    entry->velocity.z = dz;
    tile_event_place(entry, from);
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    if (entry->angle != 0) {
        TileEvent_LetGoChange(entry);
    }
    SoundEmitter_PlayB(tile_event_sound(entry), 0x7eb, TILE_EVENT_VOLUME, 0);
}
CLEAN_AS(func_ov003_0222214c, TileEvent_InitKind6)

/* func_ov003_022221cc: kind 5's step: it falls; the first time on the ground it is thrown up
 * (1.0) towards the tile's centre in 8 frames, with sound 0x70 for items 0x1492-0x14fd; the
 * second time it stops and ends. */
void TileEvent_StepKind5(TileEventEntry *entry)
{
    if (!tile_event_fall(entry)) {
        return;
    }
    if (entry->state == 0) {
        Vec3 centre;
        tile_event_centre(&centre, &entry->tile);
        fx32 dz = (centre.z - entry->position.z) / 8;
        entry->velocity.x = (centre.x - entry->position.x) / 8;
        entry->velocity.y = TILE_EVENT_ONE;
        entry->velocity.z = dz;
        entry->state = 1;
        if (tile_event_is_14xx(entry->id)) {
            SoundEmitter_PlayB(tile_event_sound(entry), TILE_EVENT_SOUND_LAND, TILE_EVENT_VOLUME, 0);
        }
    } else {
        tile_event_stop(entry);
        TileEvent_End(entry);
    }
    entry->position.y = 0;
}
CLEAN_AS(func_ov003_022221cc, TileEvent_StepKind5)

/* func_ov003_0222228c: kind 5's start: from `from`, thrown up 0.5 and 0.1875 a frame along z,
 * scale 1.0; with `angle` set it will not finish its tile change; unless `extra` is set, sound
 * 0x74 for items 0x1492-0x14fd, else 0x7d6. */
void TileEvent_InitKind5(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from, int extra)
{
    (void) tile;
    entry->velocity.x = 0;
    entry->velocity.y = 0x800;
    entry->velocity.z = 0x300;
    tile_event_place(entry, from);
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    if (entry->angle != 0) {
        entry->finish_change = 0;
    }
    if (extra != 0) {
        return;
    }
    SoundEmitter_PlayB(tile_event_sound(entry), tile_event_is_14xx(entry->id) ? 0x74 : 0x7d6, TILE_EVENT_VOLUME, 0);
}
CLEAN_AS(func_ov003_0222228c, TileEvent_InitKind5)

/* func_ov003_02222318: kind 4's step: the scale by frame from the two tables (x and z, then y);
 * at frame 16 it ends (and stays at 16). */
void TileEvent_StepKind4(TileEventEntry *entry)
{
    if (entry->frames >= 16) {
        entry->frames = 16;
        TileEvent_End(entry);
    }
    entry->scale.x = data_ov003_02236c18[entry->frames];
    entry->scale.z = entry->scale.x;
    entry->scale.y = data_ov003_02236c5c[entry->frames];
}
CLEAN_AS(func_ov003_02222318, TileEvent_StepKind4)

/* func_ov003_02222360: kind 4's start: at the tile's centre, scale 0; sound 0x7f0 for codes
 * 0xa7-0xc6, else 0x813. */
void TileEvent_InitKind4(TileEventEntry *entry, const TileChangesTile *tile)
{
    tile_event_centre(&entry->position, tile);
    tile_event_set_scale(entry, 0, 0, 0);
    int sound = entry->id >= 0xa7 && entry->id <= 0xc6 ? 0x7f0 : 0x813;
    SoundEmitter_PlayB(tile_event_sound(entry), sound, TILE_EVENT_VOLUME, 0);
}
CLEAN_AS(func_ov003_02222360, TileEvent_InitKind4)

/* Codes that kinds 3 and 0xe hand on to kind 4 when they end: families A and C (with 0x1a,
 * 0x1c, 0x1d, 0xa4 and 0xa5), the growth lines with 0x66-0x6d, and 0xd4-0xda. */
static int tile_event_regrows(u16 code)
{
    return code <= 0x1a || code == 0x1c || code == 0x1d || (code >= 0x8a && code <= 0xa5) || (code >= 0x26 && code <= 0x2a) ||
           (code >= 0x2f && code <= 0x5b) || (code >= 0x5d && code <= 0x61) || (code >= 0x66 && code <= 0x6d) ||
           (code >= 0xc8 && code <= 0xcf) || (code >= 0xd4 && code <= 0xda);
}

/* func_ov003_022223bc: kinds 3 and 0xe's step: the scale's x and z shrink by 0x154/4096 a
 * frame; at 0 it ends, but for an item under it of tile_event_regrows only once kind 4 has
 * started with that item at the tile (TileEvent_StartKind4), then without finishing its
 * change. */
void TileEvent_StepKind3(TileEventEntry *entry)
{
    entry->scale.x -= 0x154;
    if (entry->scale.x < 0) {
        entry->scale.x = 0;
        if (tile_event_regrows(entry->under)) {
            TileChangesTile at = entry->tile;
            if (TileEvent_StartKind4(entry->player, entry->under, &at) != 0) {
                entry->finish_change = 0;
                TileEvent_End(entry);
            }
        } else {
            TileEvent_End(entry);
        }
    }
    entry->scale.z = entry->scale.x;
}
CLEAN_AS(func_ov003_022223bc, TileEvent_StepKind3)

/* func_ov003_0222250c: kind 3's start: as kind 0xe's (TileEvent_InitKind14) without touching
 * the tile change. */
void TileEvent_InitKind3(TileEventEntry *entry, const TileChangesTile *tile, struct AcreMap *map)
{
    tile_event_centre(&entry->position, tile);
    entry->id = AcreTile_UnitByte09(map, tile->x, tile->z) == 0 ? TILE_EVENT_ID_UNIT_0 : TILE_EVENT_ID_UNIT_SET;
    tile_event_set_scale(entry, TILE_EVENT_ONE, TILE_EVENT_ONE, TILE_EVENT_ONE);
    tile_event_stop(entry);
    func_ov003_02224140(tile->x, tile->z, TILE_EVENT_EMPTY, 0);
}
CLEAN_AS(func_ov003_0222250c, TileEvent_InitKind3)

/* func_ov003_02222560: kind 2's start: at the tile's centre, its scale's x and z 0, still; its
 * tile change will be released rather than finished. */
void TileEvent_InitKind2(TileEventEntry *entry, const TileChangesTile *tile)
{
    tile_event_centre(&entry->position, tile);
    tile_event_set_scale(entry, 0, TILE_EVENT_ONE, 0);
    tile_event_stop(entry);
    entry->finish_change = 0;
    entry->release_change = 1;
}
CLEAN_AS(func_ov003_02222560, TileEvent_InitKind2)

/* func_ov003_02222598: kinds 1 and 2's step: the scale's x and z grow by 0x571/4096 a frame;
 * at 1.0 it ends. */
void TileEvent_StepKind1(TileEventEntry *entry)
{
    entry->scale.x += 0x571;
    if (entry->scale.x >= TILE_EVENT_ONE) {
        entry->scale.x = TILE_EVENT_ONE;
        TileEvent_End(entry);
    }
    entry->scale.z = entry->scale.x;
}
CLEAN_AS(func_ov003_02222598, TileEvent_StepKind1)

/* func_ov003_022225c4: kind 1's start: as kind 2's for position and scale; then, with an item
 * at the tile on `map`: map item families (MapItem_InFamilies) start tile effects
 * (TileEffects_Start), codes 0x1f-0x24 TileEffects_Start1f, 0xe2 TileEffects_StartE2; for
 * other codes on a marked tile (AcreTile_IsMarked) or of 0xd4-0xe1, with `extra` set the tile
 * change will be released rather than finished. A marked tile is then emptied on the map. */
void TileEvent_InitKind1(TileEventEntry *entry, const TileChangesTile *tile, struct AcreMap *map, int extra)
{
    tile_event_centre(&entry->position, tile);
    tile_event_set_scale(entry, 0, TILE_EVENT_ONE, 0);
    tile_event_stop(entry);

    u16 *item = tile_event_item(map, tile->x, tile->z);
    if (item == NULL) {
        return;
    }
    int marked = AcreTile_IsMarked(map, tile->x, tile->z);
    TileEffectsTile at = {tile->x, tile->z};
    if (MapItem_InFamilies(item)) {
        TileEffects_Start(item, &at, 0, 0);
    } else {
        u16 code = *item;
        if (code >= 0x1f && code <= 0x24) {
            TileEffects_Start1f(item, &at);
        } else if (code == 0xe2) {
            TileEffects_StartE2(&at);
        } else if (marked != 0 || (code >= 0xd4 && code <= 0xe1)) {
            if (extra != 0) {
                entry->finish_change = 0;
                entry->release_change = 1;
            }
        }
    }
    if (AcreTile_IsMarked(map, tile->x, tile->z) != 0) {
        func_ov003_02224140(tile->x, tile->z, TILE_EVENT_EMPTY, 0);
    }
}
CLEAN_AS(func_ov003_022225c4, TileEvent_InitKind1)

/* func_ov003_022226c8: kinds 0 and 0xd's step: the scale's x and z grow by 410/4096 a frame to
 * 1.0; it falls; the first time on the ground it bounces (0.375 up, its sideways speed times
 * 0x4cd/4096) with sound 0x70 for items 0x1492-0x14fd; the second time it stops and ends. */
void TileEvent_StepKind0(TileEventEntry *entry)
{
    entry->scale.x += 0x19a;
    if (entry->scale.x >= TILE_EVENT_ONE) {
        entry->scale.x = TILE_EVENT_ONE;
    }
    entry->scale.z = entry->scale.x;
    if (!tile_event_fall(entry)) {
        return;
    }
    entry->position.y = 0;
    if (entry->state == 0) {
        entry->state = 1;
        entry->velocity.x = (entry->velocity.x * 0x4cd) >> 12;
        entry->velocity.y = 0x600;
        entry->velocity.z = (entry->velocity.z * 0x4cd) >> 12;
        if (tile_event_is_14xx(entry->id)) {
            SoundEmitter_PlayB(tile_event_sound(entry), TILE_EVENT_SOUND_LAND, TILE_EVENT_VOLUME, 0);
        }
    } else {
        entry->state = 2;
        tile_event_stop(entry);
        TileEvent_End(entry);
    }
}
CLEAN_AS(func_ov003_022226c8, TileEvent_StepKind0)

/* func_ov003_02222798: kinds 0 and 0xd's start: from `from`, thrown up (1.0) towards the tile's
 * centre in 9 frames, its scale's x and z 0. Sound: for items 0x1492-0x14fd 0x74 (kind 0xd:
 * 0x815 from item 0x149b on, else none), for other codes 0x75. */
void TileEvent_InitKind0(TileEventEntry *entry, const TileChangesTile *tile, const Vec3 *from)
{
    Vec3 centre;
    tile_event_centre(&centre, tile);
    fx32 dz = (centre.z - from->z) / 9;
    entry->velocity.x = (centre.x - from->x) / 9;
    entry->velocity.y = TILE_EVENT_ONE;
    entry->velocity.z = dz;
    tile_event_place(entry, from);
    tile_event_set_scale(entry, 0, TILE_EVENT_ONE, 0);

    int sound = -1;
    if (!tile_event_is_14xx(entry->id)) {
        sound = 0x75;
    } else if (entry->kind != TILE_EVENT_KIND_D) {
        sound = 0x74;
    } else if (entry->id >= 0x149b) {
        sound = 0x815;
    }
    if (sound >= 0) {
        SoundEmitter_PlayB(tile_event_sound(entry), sound, TILE_EVENT_VOLUME, 0);
    }
}
CLEAN_AS(func_ov003_02222798, TileEvent_InitKind0)

/* func_ov003_0222284c: the entry made free without letting go of its tile change. */
void TileEvent_Clear(TileEventEntry *entry)
{
    tile_event_free(entry);
}
CLEAN_AS(func_ov003_0222284c, TileEvent_Clear)

/* func_ov003_02222860: the event ended: its tile change let go (TileEvent_LetGoChange), the
 * entry made free. */
void TileEvent_End(TileEventEntry *entry)
{
    TileEvent_LetGoChange(entry);
    tile_event_free(entry);
}
CLEAN_AS(func_ov003_02222860, TileEvent_End)

/* func_ov003_02222880: an event begins in `entry`: active, for `player` at `tile` and `point`,
 * of `kind` with `id`, `angle` and `extra`; it will finish its tile change; the item under it
 * is the one of the tile change at the tile in layer 0 (0xfff1 without one); then the kind's
 * start. */
void TileEvent_Begin(TileEventEntry *entry, int player, const int *tile, const int *point, int kind, u16 id,
                     struct AcreMap *map, s16 angle, int extra)
{
    entry->player = player;
    entry->active = 1;
    entry->kind = kind;
    entry->tile.x = tile[0];
    entry->tile.z = tile[1];
    entry->angle = angle;
    entry->unk_4a = 0;
    entry->point.x = point[0];
    entry->point.y = point[1];
    entry->point.z = point[2];
    entry->finish_change = 1;
    entry->release_change = 0;
    entry->offset.x = 0;
    entry->offset.y = 0;
    entry->offset.z = 0;

    TileChangesTile at = entry->tile;
    int index = TileChanges_FindAt(&at, 0);
    if (index >= 0) {
        entry->under = ((const TileChange *) (uintptr_t) TileChanges_At(index))->item;
    } else {
        entry->under = TILE_EVENT_EMPTY;
    }
    entry->id = id;
    entry->state = 0;
    entry->frames = 0;
    entry->counter = 0;
    entry->countdown = 0x1f;

    TileChangesTile on = {tile[0], tile[1]};
    Vec3 from = {point[0], point[1], point[2]};
    switch (kind) {
        case 0:
        case TILE_EVENT_KIND_D:
            TileEvent_InitKind0(entry, &on, &from);
            break;
        case 1:
            TileEvent_InitKind1(entry, &on, map, extra);
            break;
        case 2:
            TileEvent_InitKind2(entry, &on);
            break;
        case TILE_EVENT_KIND_3:
            TileEvent_InitKind3(entry, &on, map);
            break;
        case TILE_EVENT_KIND_4:
            TileEvent_InitKind4(entry, &on);
            break;
        case TILE_EVENT_KIND_5:
            TileEvent_InitKind5(entry, &on, &from, extra);
            break;
        case TILE_EVENT_KIND_6:
            TileEvent_InitKind6(entry, &on, &from);
            break;
        case TILE_EVENT_KIND_7:
            TileEvent_InitKind7(entry, &on, &from);
            break;
        case TILE_EVENT_KIND_8:
            TileEvent_InitKind8(entry, &on, angle);
            break;
        case TILE_EVENT_KIND_9:
            TileEvent_InitKind9(entry, &on, &from, id);
            break;
        case TILE_EVENT_KIND_A:
            TileEvent_InitKind10(entry, &on);
            break;
        case TILE_EVENT_KIND_B:
            TileEvent_InitKind11(entry, &on);
            break;
        case TILE_EVENT_KIND_C:
            TileEvent_InitKind12(entry, &from);
            break;
        case TILE_EVENT_KIND_E:
            TileEvent_InitKind14(entry, &on, map);
            break;
    }
}
CLEAN_AS(func_ov003_02222880, TileEvent_Begin)

/* func_ov003_02222aa4: the entry's tile change let go once, in layer 0: finished
 * (TileChanges_FinishAtTile) when `finish_change` was set, else released
 * (TileChanges_ReleaseAt) when `release_change` was; that flag is cleared first. */
void TileEvent_LetGoChange(TileEventEntry *entry)
{
    if (entry->finish_change != 0) {
        entry->finish_change = 0;
        TileChangesTile at = entry->tile;
        TileChanges_FinishAtTile(&at, 0);
    } else if (entry->release_change != 0) {
        entry->release_change = 0;
        TileChangesTile at = entry->tile;
        TileChanges_ReleaseAt(&at, 0);
    }
}
CLEAN_AS(func_ov003_02222aa4, TileEvent_LetGoChange)

/* ---- Writing the town's map, and the events that tile changes leave. */

#include "main/scene_query.h"

/* The town's map the process draws. */
extern AcreMap *data_021c80bc;

/* func_ov003_02224140: `item` written to tile (x, z) of the town's map (data_021c80bc, layer 0)
 * when there is one, then the tile marked (AcreTile_Mark) when the item is not 0xfff1 and
 * `mark` is set, else unmarked.
 * QUIRK: whether the current scene is 0 is asked first and not used. */
void TileEvent_SetTownItem(int x, int z, u16 item, int mark)
{
    SceneQuery_CurrentIs0();
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return;
    }
    u16 code = item;
    AcreTile_SetItem(map, &code, x, z, 0);
    if (item != TILE_EVENT_EMPTY && mark != 0) {
        AcreTile_Mark(map, x, z);
    } else {
        AcreTile_Unmark(map, x, z);
    }
}
CLEAN_AS(func_ov003_02224140, TileEvent_SetTownItem)

/* func_ov003_022241a4: for this console's session slot: with a tile change tagged 4, kind 0xb
 * with its item at `tile` (TileEvent_StartKindB); with one tagged 3, kind 0xd with its item at
 * its own tile, from the centre of `tile` (TileEvent_StartKindD). */
void TileEvent_StartFromChanges(const TileChangesTile *tile)
{
    int slot = data_020ccf94->local_slot;
    int index = TileChanges_FindByTag((u8) slot, 4);
    if (index >= 0) {
        const TileChange *change = (const TileChange *) (uintptr_t) TileChanges_At(index);
        TileChangesTile at = *tile;
        TileEvent_StartKindB(slot, change->item, &at);
    }
    index = TileChanges_FindByTag((u8) slot, 3);
    if (index >= 0) {
        const TileChange *change = (const TileChange *) (uintptr_t) TileChanges_At(index);
        Vec3 centre;
        AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
        u16 packed = change->tile;
        TileChangesTile to = {packed >> 8, packed & 0xff};
        Vec3 from = centre;
        TileEvent_StartKindD(slot, change->item, &to, &from);
    }
}
CLEAN_AS(func_ov003_022241a4, TileEvent_StartFromChanges)

/* ---- The process's creation, and the table's entries' constructor and destructor. */

/* The array helpers and what they are handed: the game's own model object constructor and
 * destructor, and an entry's destructor (TileEvent_DestructEntry). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void func_0205577c(void *model);
extern void func_ov003_022275d8(void *entry);

/* The model holder arrays of the process: where, and how many. */
static void tile_event_construct_models(ModelObject *models, int count)
{
    __cxa_vec_ctor(models, count, sizeof(ModelObject), func_0205577c, func_02055764);
}

/* func_ov003_02227454: a new process (0x6a70 bytes, cleared): the process class's constructor,
 * its vtable (the class's, then its own), its model holders, its four model sets and its
 * growth models (the member at 0x4b20); NULL when there is no memory. */
TileEventProcess *TileEvent_NewProcess(void)
{
    TileEventProcess *process = Heap_AllocAuxZeroed(sizeof(TileEventProcess));
    if (process != NULL) {
        Process_Construct(&process->process);
        process->process.vtable = data_020da13c;
        process->process.vtable = data_ov003_0223bc7c;
        tile_event_construct_models(process->models_0174, 0x12);
        tile_event_construct_models(process->models_0c6c, 6);
        tile_event_construct_models(process->models_1014, 3);
        tile_event_construct_models(process->models_11e8, 6);
        tile_event_construct_models(process->models_1590, 0x28);
        tile_event_construct_models(process->models_2df0, 4);
        tile_event_construct_models(process->models_3068, 0x20);
        tile_event_construct_models(process->models_43e8, 5);
        tile_event_construct_models(process->models_4708, 2);
        tile_event_construct_models(process->models_4840, 2);
        tile_event_construct_models(process->models_49a8, 2);
        for (int i = 0; i < 4; i++) {
            ModelSet_Construct(&process->sets[i]);
        }
        GrowthModels_Construct((GrowthModels *) (void *) process->member_4b20);
    }
    return process;
}
CLEAN_AS(func_ov003_02227454, TileEvent_NewProcess)

/* func_ov003_022275bc (registered at the overlay's start for the table): the twenty entries
 * destroyed (TileEvent_DestructEntry); returns `entries`. */
void *TileEvent_DestroyEntries(TileEventEntry *entries)
{
    __cxa_vec_cleanup(entries, TILE_EVENT_ENTRIES, sizeof(TileEventEntry), func_ov003_022275d8);
    return entries;
}
CLEAN_AS(func_ov003_022275bc, TileEvent_DestroyEntries)

/* func_ov003_022275d8: an entry's destructor: its sound emitter's. */
TileEventEntry *TileEvent_DestructEntry(TileEventEntry *entry)
{
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) (void *) entry->sound);
    return entry;
}
CLEAN_AS(func_ov003_022275d8, TileEvent_DestructEntry)

/* func_ov003_022275ec: an entry's constructor: its tile (0, 0) and its sound emitter. */
TileEventEntry *TileEvent_ConstructEntry(TileEventEntry *entry)
{
    entry->tile.x = 0;
    entry->tile.z = 0;
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) (void *) entry->sound);
    return entry;
}
CLEAN_AS(func_ov003_022275ec, TileEvent_ConstructEntry)
