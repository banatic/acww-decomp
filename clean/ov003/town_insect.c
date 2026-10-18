/* The insects of the town in overlay 3 (town_insect.h). */
#include "town_insect.h"

#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/acre_record.h"
#include "main/acre_tile.h"   /* AcreTile_IsMarked, AcreTile_ItemInAcre */
#include "main/actor.h"       /* Actor, Vec_YawTo */
#include "main/actor_table.h" /* Position_Tile, Actors_GetEByIndex */
#include "main/block_02042200.h"
#include "main/building_shapes.h"
#include "main/calendar.h"
#include "main/c_library.h"
#include "main/camera_control.h"
#include "main/clock.h"
#include "main/collision_query.h"
#include "main/effect_system.h"
#include "main/globe.h"
#include "main/insect_draw.h" /* InsectDrawList */
#include "main/insect_tables.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/map_code.h"
#include "main/player_actor_ops.h"
#include "main/rom_file.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/shadow.h"
#include "main/sky.h"
#include "main/tile_requests.h"
#include "main/town_day.h"
#include "main/unit_type_info.h"
#include "ov003/field_actor.h" /* FieldActor_PlayerFlag9 */
#include "ov003/snowman.h"
#include "ov003/town_insect_moves.h"
#include "ov003/town_insect_tables.h"
#include "ov003/town_tile_mask.h"
#include "ov009/scene_actor.h"
#include "object_actors.h"
#include "ov068/insect_paths.h"

static_assert(offsetof(TownInsectModel, frames) == 0x9c, "TownInsectModel.frames");
static_assert(sizeof(TownInsectModel) == 0xb8, "TownInsectModel");
static_assert(offsetof(TownInsect, contacts) == 0x20, "TownInsect.contacts");
static_assert(offsetof(TownInsect, model) == 0x50, "TownInsect.model");
static_assert(offsetof(TownInsect, sphere) == 0x108, "TownInsect.sphere");
static_assert(offsetof(TownInsect, files) == 0x130, "TownInsect.files");
static_assert(offsetof(TownInsect, source) == 0x174, "TownInsect.source");
static_assert(offsetof(TownInsect, matrix) == 0x180, "TownInsect.matrix");
static_assert(offsetof(TownInsect, start) == 0x1c8, "TownInsect.start");
static_assert(offsetof(TownInsect, target) == 0x1d4, "TownInsect.target");
static_assert(offsetof(TownInsect, unk_1ec) == 0x1ec, "TownInsect.unk_1ec");
static_assert(offsetof(TownInsect, position) == 0x204, "TownInsect.position");
static_assert(offsetof(TownInsect, effect) == 0x22c, "TownInsect.effect");
static_assert(offsetof(TownInsect, slot) == 0x230, "TownInsect.slot");
static_assert(offsetof(TownInsect, angle_x) == 0x238, "TownInsect.angle_x");
static_assert(offsetof(TownInsect, frames_left) == 0x242, "TownInsect.frames_left");
static_assert(offsetof(TownInsect, used) == 0x248, "TownInsect.used");
static_assert(offsetof(TownInsect, kind) == 0x24d, "TownInsect.kind");
static_assert(offsetof(TownInsect, state) == 0x250, "TownInsect.state");
static_assert(offsetof(TownInsect, unk_254) == 0x254, "TownInsect.unk_254");
static_assert(offsetof(TownInsect, players_near) == 0x258, "TownInsect.players_near");
static_assert(sizeof(TownInsect) == 0x25c, "TownInsect");
static_assert(sizeof(TownInsectKindInfo) == 6, "TownInsectKindInfo");
static_assert(offsetof(TownInsectProcess, blocks) == 0x98, "TownInsectProcess.blocks");
static_assert(sizeof(TownInsectMask) == 0x200, "TownInsectMask");

/* The player at this console, for SessionPlayers_ActorOf and FieldActor_PlayerFlag9. */
#define TOWN_INSECT_THIS_PLAYER 4
/* The scene SessionPlayers_ScenePoint names for the town. */
#define TOWN_INSECT_SCENE_TOWN 0

/* The three tables (town_insect.h) and the kinds' table. */
extern TownInsect data_ov003_02260994[TOWN_INSECT_EVENT_COUNT];
extern TownInsect data_ov003_02260e4c[TOWN_INSECT_HELD_COUNT];
extern TownInsect data_ov003_022617bc[TOWN_INSECT_TOWN_COUNT];
extern const TownInsectKindInfo data_ov003_0223c144[TOWN_INSECT_KINDS];

/* The insect kinds' start and update functions (town_insect_kinds.h): the start function is run
 * once the kind's files are loaded (TownInsect_Load) or when a player lets the insect go
 * (TownInsect_LetGo); the update function is kept in TownInsect.unk_170 and run each frame. */
typedef void (*TownInsectKindFn)(TownInsect *insect);
typedef struct TownInsectKindFunctions {
    u32 start;  /* a TownInsectKindFn */
    u32 update; /* a TownInsectKindFn */
} TownInsectKindFunctions;
extern const TownInsectKindFunctions data_ov003_0223c2ac[TOWN_INSECT_KINDS];

/* The insect animation's vtable. */
extern const u32 data_ov003_0223c0ec[];
/* The sound source's base class's vtable and its own (sound_emitter.h). */
extern const u32 data_0213efe8[];
extern const u32 data_0213f020[];

/* The masks of town_tile_mask.h. */
extern u16 data_ov003_02260794[TOWN_TILE_MASK_SIZE / 2];
extern u16 data_ov003_02260594[TOWN_TILE_MASK_SIZE / 2];

/* The process's frame counter for placing insects (TownInsect_UpdateTown). */
extern u8 data_ov003_02260534;
/* Set by main (block_02042200.c) for the event insect of kind 0x3b; cleared once placed. */
extern u8 data_ov003_02260538;
/* Set by the session's handler 41 (session_message.c); TownInsect_Release reads it. */
extern u8 data_ov003_0226053c;
/* The point ahead of this console's player and its flag, kept by the field actor. */
extern u8 data_ov003_02260540;
extern Vec3 data_ov003_02260558;
/* Kind 0x3b's placing (TownInsect_PickTile): whether a tile was found, how many acres were
 * tried, and which (a bit for each of the 16). */
extern u8 data_ov003_02260544;
extern u8 data_ov003_02260548;
extern u16 data_ov003_02260550;
/* Set by TownInsect_SetFlag54c (from main); cleared when kind 0x33 found no tile. */
extern u8 data_ov003_0226054c;
/* TownInsect_ClearFailed's frame counter. */
extern u16 data_ov003_02260554;

/* The six lists of each month (insect_draw.h). */
extern const InsectDrawList *const data_020dded8[12];

/* The field camera (itcm/camera.h): its first word and the point at 0x2c. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;
/* Main's scratch matrix. */
extern Mtx43 data_021fbe48;
/* The session (session.h). */
extern NetSession *data_020ccf94;
extern const s16 FX_SinCosTable_[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void MTX_MultVec43(const Vec3 *v, const Mtx43 *m, Vec3 *out);
extern int NNS_G3dMdlGetMdlAlpha(void *model, int material);
extern void NNS_G3dMdlSetMdlAlpha(void *model, int material, int alpha);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The constructor and destructor of the two objects at 0x1ec, handed to the two above. */
extern void func_020012e8(void *object);
extern void func_020012dc(void *object);

/* Whether the tile's item code suits insect kind 2 or 3 of place 1. */
/* Loose snowball `index` (0 or 1) when it is idle, else NULL. */
/* A town insect's message from the session (kind, point, byte 0x254). */

/* `value` shifted as the ARM does by a register: by its low byte, 0 from 32 on. */
static u32 town_insect_shl(u32 value, int amount)
{
    u32 by = (u32) amount & 0xff;
    return by >= 32 ? 0 : value << by;
}

static u32 town_insect_lsr(u32 value, int amount)
{
    u32 by = (u32) amount & 0xff;
    return by >= 32 ? 0 : value >> by;
}

/* Record `index` of a table, by address as the game computes it (any index). */
static TownInsect *town_insect_at(TownInsect *table, int index)
{
    return (TownInsect *) ((uintptr_t) table + (uintptr_t) (u32) (index * (int) sizeof(TownInsect)));
}

/* The record an id names (TOWN_INSECT_ID_*), or `otherwise` for an id of neither table. */
static TownInsect *town_insect_by_id(int id, TownInsect *otherwise)
{
    int index = (u8) (id & TOWN_INSECT_ID_INDEX);
    if ((id >> 4) & 1) {
        return town_insect_at(data_ov003_022617bc, index);
    }
    if ((id >> 5) & 1) {
        return town_insect_at(data_ov003_02260994, index);
    }
    return otherwise;
}

static const TownInsectKindInfo *town_insect_kind_info(int kind)
{
    return (const TownInsectKindInfo *) ((uintptr_t) data_ov003_0223c144 +
                                         (uintptr_t) (u32) (kind * (int) sizeof(TownInsectKindInfo)));
}

/* Whether this system has a slot in the session. */
static int town_insect_in_session(void)
{
    return Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) != 0;
}

static void *town_insect_model(TownInsect *insect)
{
    return (void *) (uintptr_t) ModelPoolFiles_Model(&insect->files);
}

/* A message of one byte, the insect's id, sent to the session. */
static void town_insect_send(u8 *id, u32 handler, u32 kind)
{
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, id, 1);
    Session_EndMessage(session, handler, kind);
}

/* The item codes TownInsect_CountTiles leaves out for place 1 and TownInsect_OnItsTile asks
 * for: 0x26-0x2a, 0x2f-0x61 but 0x5c, 0x66-0x6d and 0xc8-0xcf. */
static int town_insect_code_in_set_a(u16 code)
{
    return (code >= 0x26 && code <= 0x2a) || (code >= 0x2f && code <= 0x61 && code != 0x5c) ||
           (code >= 0x66 && code <= 0x6d) || (code >= 0xc8 && code <= 0xcf);
}

/* The item codes that count for places 1 and 2: 0-0x1a, 0x1c, 0x1d and 0x8a-0xa5. */
static int town_insect_code_in_set_b(u16 code)
{
    return code <= 0x1a || code == 0x1c || code == 0x1d || (code >= 0x8a && code <= 0xa5);
}

/* func_ov003_0222c888: how many tiles of the inner acre (*acre_x, *acre_z) suit insect `kind`
 * of place `place`, marking in `mask` (the acre's 16 rows) each tile that was looked at and did
 * not suit. Tiles already marked, and tiles without an item code, are passed over. When some
 * suit, one of the unmarked tiles of the acre is picked at random (TownTileMask_PickFree, which
 * leaves its world point in *acre_x and *acre_z) and 1 is returned; for places 1 and 8, and
 * place 7 for kind 0x33, also one of the tiles must have set the "found" flag below.
 *
 * Places, by the tile (its world tile (wx, wz), its item code):
 *   0  an empty tile (0xfff1);
 *   1  any code but set A; the found flag by a code of set B (for kinds 2 and 3 only when
 *      TownInsectMove_SuitsCode also agrees);
 *   2  a code of set B (for kind 0xf only when TownInsectMove_SuitsCode agrees);
 *   3  none;
 *   4  an empty tile of unit type 3;
 *   5  a tile of unit group 2;
 *   6  a tile of unit type 7, or, in an acre whose record (the next one across and down) has
 *      flag 0x100, a tile of unit group 2 four or more tiles from the acre's edges; NULL acre:
 *      0 at once;
 *   7  codes 0x154a-0x1553 on an unmarked tile; for kind 0x33 also 0x1320-0x1322 there (setting
 *      the found flag), and empty tiles;
 *   8  code 0x1b (setting the found flag) and empty tiles;
 *   9  an empty tile whose unit has byte 9 clear;
 *   10 codes 0xe3-0xe7;
 *   11 every tile;
 *   12-15 the codes TownTileMask_IsCodeOfList, TownTileMask_IsCode5bOr66To6d and
 *      TownTileMask_IsCodeCcToCf name (12 the first, 13 the last, 14 the first two, 15 all).
 * QUIRK: a tile passed over for being marked is marked again when no tile has counted since the
 * last tile looked at (the same value written back). */
int TownInsect_CountTiles(u16 *mask, int kind, int *acre_x, int *acre_z, AcreMap *map, int place)
{
    u16 *rows = (u16 *) ((uintptr_t) mask + (uintptr_t) (u32) ((*acre_x + *acre_z * 4) << 5));
    int before = 0;
    int count = 0;
    int found = 0;
    int flagged_acre = 0;
    if (place == 6) {
        u32 next_x = (u32) *acre_x + 1;
        u32 next_z = (u32) *acre_z + 1;
        AcreRecord *acre = NULL;
        if (next_x < (u32) map->acres_wide && next_z < (u32) map->acres_high && map->acres != NULL) {
            acre = (AcreRecord *) (map->acres + (next_x + next_z * (u32) map->acres_wide) * ACRE_MAP_ACRE_SIZE);
        }
        if (acre == NULL) {
            return 0;
        }
        if ((AcreRecord_Flags(acre) & 0x100) != 0) {
            flagged_acre = 1;
        }
    }
    int first_x = (*acre_x + 1) << 4;
    int first_z = (*acre_z + 1) << 4;
    u8 kind_minus_2 = (u8) (kind - 2);
    for (int row = 0; row < 16; row++) {
        u16 *bits = &rows[row];
        int wz = first_z + row;
        for (int column = 0; column < 16; column++) {
            if (((*bits >> column) & 1) == 0) {
                int wx = first_x + column;
                before = count;
                int cx = wx >> 4;
                int cz = wz >> 4;
                u16 *code = AcreTile_ItemInAcre(map, (u32) cx, (u32) cz, wx - (cx << 4), wz - (cz << 4), 0);
                if (code == NULL) {
                    continue;
                }
                switch (place) {
                    case 7:
                        if (kind == 0x33) {
                            u16 id = *code;
                            if (((id >= 0x154a && id <= 0x1553) || (id >= 0x1320 && id <= 0x1322)) &&
                                AcreTile_IsMarked(map, wx, wz) == 0) {
                                found = 1;
                                count++;
                            } else if (*code == ACRE_MAP_ITEM_NONE) {
                                count++;
                            }
                        } else if (*code >= 0x154a && *code <= 0x1553 && AcreTile_IsMarked(map, wx, wz) == 0) {
                            count++;
                        }
                        break;
                    case 4:
                        if (UnitTypeInfo_IsType03At(wx, wz) != 0 && *code == ACRE_MAP_ITEM_NONE) {
                            count++;
                        }
                        break;
                    case 6:
                        if (UnitTypeInfo_IsType07At(wx, wz) != 0) {
                            count++;
                        } else if (flagged_acre && column > 3 && row > 3 && column < 13 && row < 13 &&
                                   UnitTypeInfo_GroupAt(wx, wz) == 2) {
                            count++;
                        }
                        break;
                    case 1: {
                        u16 id = *code;
                        if (town_insect_code_in_set_a(id)) {
                            break;
                        }
                        if (!found && town_insect_code_in_set_b(id)) {
                            if (kind_minus_2 <= 1) {
                                if (TownInsectMove_SuitsCode(kind, code) != 0) {
                                    found = 1;
                                }
                            } else {
                                found = 1;
                            }
                        }
                        count++;
                        break;
                    }
                    case 2:
                        if (town_insect_code_in_set_b(*code) && (kind != 0xf || TownInsectMove_SuitsCode(kind, code) != 0)) {
                            count++;
                        }
                        break;
                    case 9:
                        if (UnitTypeInfo_Byte09At(wx, wz) == 0 && *code == ACRE_MAP_ITEM_NONE) {
                            count++;
                        }
                        break;
                    case 8:
                        if (*code == 0x1b) {
                            found = 1;
                            count++;
                        } else if (*code == ACRE_MAP_ITEM_NONE) {
                            count++;
                        }
                        break;
                    case 0:
                        if (*code == ACRE_MAP_ITEM_NONE) {
                            count++;
                        }
                        break;
                    case 11:
                        /* QUIRK: the original tests (row << column) & 1, which is never set here
                         * (bit `column` is clear, and bit 0 of the shifted row is clear for any
                         * other column), so every tile counts. */
                        count++;
                        break;
                    case 10:
                        if (*code >= 0xe3 && *code <= 0xe7) {
                            count++;
                        }
                        break;
                    case 12:
                        if (TownTileMask_IsCodeOfList(code) != 0) {
                            count++;
                        }
                        break;
                    case 14:
                        if (TownTileMask_IsCodeOfList(code) != 0 || TownTileMask_IsCode5bOr66To6d(code) != 0) {
                            count++;
                        }
                        break;
                    case 15:
                        if (TownTileMask_IsCodeOfList(code) != 0 || TownTileMask_IsCode5bOr66To6d(code) != 0 ||
                            TownTileMask_IsCodeCcToCf(code) != 0) {
                            count++;
                        }
                        break;
                    case 13:
                        if (TownTileMask_IsCodeCcToCf(code) != 0) {
                            count++;
                        }
                        break;
                    case 5:
                        if (UnitTypeInfo_GroupAt(wx, wz) == 2) {
                            count++;
                        }
                        break;
                    default:
                        break;
                }
            }
            if (count == before) {
                *bits = (u16) (*bits | (1u << column));
            }
        }
    }
    if (place == 1 || place == 8 || (place == 7 && kind == 0x33)) {
        if (count > 0 && found) {
            TownTileMask_PickFree(count, rows, acre_x, acre_z);
            return 1;
        }
    } else if (count > 0) {
        TownTileMask_PickFree(count, rows, acre_x, acre_z);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222c888, TownInsect_CountTiles)

/* func_ov003_0222ce50: in `mask`, the tiles around each building (its shape's 'M' tiles) whose
 * scene actor has the member at 0x1f4 set made free again (their bits cleared), for the 0x22
 * buildings that have a shape and an actor.
 * QUIRK: the tile's place in the mask is found by C's division and remainder by 16 from tile 16
 * on, as the original does; a bit of 16 or more (or a negative remainder) clears nothing. */
void TownInsect_UnmarkSceneActors(TownInsectMask *mask)
{
    for (u32 i = 0; i < BUILDING_SHAPES_COUNT; i++) {
        u16 code = MapCode_Building(i);
        BuildingShapeEntry *shape = BuildingShapes_Of(&code);
        if (shape == NULL) {
            continue;
        }
        u32 tiles = (u32) BuildingShapes_MCount(shape);
        if (tiles == 0) {
            continue;
        }
        SceneActor *actor = ObjectActors_FindByCode(code);
        if (actor == NULL) {
            continue;
        }
        for (u32 j = 0; j < tiles; j++) {
            int x;
            int z;
            if (BuildingShapes_MTile((unsigned int) (uintptr_t) shape, (unsigned int) (uintptr_t) &x,
                                     (unsigned int) (uintptr_t) &z, j) == 0) {
                continue;
            }
            if (SceneActor_Member1F4IsSet(actor) != 1) {
                continue;
            }
            int tile_x = x + SceneActor_TileX(actor);
            int tile_z = (int) ((u32) z + SceneActor_TileZ(actor));
            int acre_x = (tile_x - 0x10) / 0x10;
            int acre_z = (tile_z - 0x10) / 0x10;
            int row = tile_z % 0x10;
            int column = tile_x % 0x10;
            u16 *bits = (u16 *) ((uintptr_t) mask + (uintptr_t) (u32) (acre_x * 32 + acre_z * 128 + row * 2));
            *bits = (u16) (*bits & (0xffffu - town_insect_shl(1, column)));
        }
    }
}
CLEAN_AS(func_ov003_0222ce50, TownInsect_UnmarkSceneActors)

/* func_ov003_0222cf1c: `mask` with every tile marked, then the tiles around the scene actors'
 * buildings freed (TownInsect_UnmarkSceneActors). */
void TownInsect_FillMask(TownInsectMask *mask)
{
    for (int i = 0; i < 0x100; i++) {
        mask->rows[i] = 0xffff;
    }
    TownInsect_UnmarkSceneActors(mask);
}
CLEAN_AS(func_ov003_0222cf1c, TownInsect_FillMask)

/* An acre of the 16 not yet tried in `tried` picked at random (its bit set) from `left` of
 * them; 16 when none is left to pick. */
static unsigned int town_insect_pick_acre(u32 *tried, int left)
{
    unsigned int acre = 0;
    for (int i = 0; i < 16; i++) {
        if (((*tried >> i) & 1) == 0 && left-- == 0) {
            *tried |= 1u << i;
            break;
        }
        acre++;
    }
    return acre;
}

/* func_ov003_0222cf60: a tile for insect `kind` of place `place` found in one of the 16 inner
 * acres, tried in a random order, with `mask`; its world point is written to the insect's
 * position (x and z) and 1 returned, else 0.
 *
 * Kind 0x3b tries one acre a call, remembering which across calls (data_ov003_02260550, count
 * in data_ov003_02260548); the tile is taken only when farther than 16.0 from this console's
 * player. After the 16th try without one the tries start again, and data_ov003_02260538 is
 * cleared when no acre had a suitable tile. Kind 0x33 also wants the tile farther than 16.0
 * from the player, and clears data_ov003_0226054c when no acre had one at all.
 * QUIRK: an acre index of 16 (when the random pick passes the last acre) is tried as acre
 * (4, 0). */
int TownInsect_PickTile(TownInsect *insect, TownInsectMask *mask, int kind, int place)
{
    int x = 0;
    int z = 0;
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return 0;
    }
    if (kind == TOWN_INSECT_KIND_3B) {
        int left = (int) MainRandom_Below(0x10 - data_ov003_02260548);
        u32 tried = data_ov003_02260550;
        unsigned int acre = 0;
        for (int i = 0; i < 16; i++) {
            if (((tried >> i) & 1) == 0 && left-- == 0) {
                data_ov003_02260550 = (u16) (data_ov003_02260550 | (1u << i));
                break;
            }
            acre++;
        }
        x = (int) (acre >> 2);
        z = (int) (acre & 3);
        data_ov003_02260548 = (u8) (data_ov003_02260548 + 1);
        if (TownInsect_CountTiles(mask->rows, kind, &x, &z, map, (u8) place) != 0) {
            Actor *player = SessionPlayers_ActorOf(TOWN_INSECT_THIS_PLAYER);
            data_ov003_02260544 = 1;
            if (player != NULL) {
                Vec3 point = {x, 0, z};
                if (Vec_DistanceXZ(&player->position, &point) > 0x10000) {
                    insect->position.x = x;
                    insect->position.z = z;
                    data_ov003_02260550 = 0;
                    data_ov003_02260548 = 0;
                    data_ov003_02260544 = 0;
                    return 1;
                }
            }
        }
        if (data_ov003_02260548 >= 0x10) {
            data_ov003_02260550 = 0;
            data_ov003_02260548 = 0;
            if (data_ov003_02260544 != 0) {
                data_ov003_02260544 = 0;
            } else {
                data_ov003_02260538 = 0;
            }
        }
    } else if (kind == 0x33) {
        u32 tried = 0;
        int found = 0;
        for (int k = 0; k < 16; k++) {
            unsigned int acre = town_insect_pick_acre(&tried, (int) MainRandom_Below(0x10 - k));
            x = (int) (acre >> 2);
            z = (int) (acre & 3);
            if (TownInsect_CountTiles(mask->rows, kind, &x, &z, map, (u8) place) != 0) {
                Actor *player = SessionPlayers_ActorOf(TOWN_INSECT_THIS_PLAYER);
                if (player != NULL) {
                    Vec3 point = {x, 0, z};
                    if (Vec_DistanceXZ(&player->position, &point) > 0x10000) {
                        insect->position.x = x;
                        insect->position.z = z;
                        return 1;
                    }
                }
                found = 1;
            }
        }
        if (!found) {
            data_ov003_0226054c = 0;
        }
    } else {
        u32 tried = 0;
        for (int k = 0; k < 16; k++) {
            unsigned int acre = town_insect_pick_acre(&tried, (int) MainRandom_Below(0x10 - k));
            x = (int) (acre >> 2);
            z = (int) (acre & 3);
            if (TownInsect_CountTiles(mask->rows, kind, &x, &z, map, (u8) place) != 0) {
                insect->position.x = x;
                insect->position.z = z;
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0222cf60, TownInsect_PickTile)

/* func_ov003_0222d1bc: a copy of the mask for `place`: the first mask of town_tile_mask.h for
 * places 0, 5 and 6, the second for the others. */
void TownInsect_CopyMask(void *dst, int place)
{
    switch (place) {
        case 0:
        case 5:
        case 6:
            MI_CpuCopy8(data_ov003_02260794, dst, TOWN_TILE_MASK_SIZE);
            break;
        default:
            MI_CpuCopy8(data_ov003_02260594, dst, TOWN_TILE_MASK_SIZE);
            break;
    }
}
CLEAN_AS(func_ov003_0222d1bc, TownInsect_CopyMask)

/* func_ov003_0222d1f8 (vtable data_ov003_0223c0ec): the insect's animation destroyed and freed. */
ModelAnim *TownInsectAnim_DestructDelete(ModelAnim *anim)
{
    anim->ctrl.vtable = data_ov003_0223c0ec;
    ModelAnim_Destruct(anim);
    Heap_OperatorDeleteB(anim);
    return anim;
}
CLEAN_AS(func_ov003_0222d1f8, TownInsectAnim_DestructDelete)

/* func_ov003_0222d218: the insect's animation's destructor. */
ModelAnim *TownInsectAnim_Destruct(ModelAnim *anim)
{
    anim->ctrl.vtable = data_ov003_0223c0ec;
    ModelAnim_Destruct(anim);
    return anim;
}
CLEAN_AS(func_ov003_0222d218, TownInsectAnim_Destruct)

/* func_ov003_0222d230: the insect's animation's constructor. */
ModelAnim *TownInsectAnim_Construct(ModelAnim *anim)
{
    ModelAnim_ConstructBase(anim);
    anim->ctrl.vtable = data_ov003_0223c0ec;
    return anim;
}
CLEAN_AS(func_ov003_0222d230, TownInsectAnim_Construct)

/* func_ov003_0222d248: what insect `kind` does in the weather `falling` (Sky_Falling: 0 none,
 * 1 and 2 falling): TOWN_INSECT_WEATHER_QUIET for kinds 16-20 while something falls;
 * TOWN_INSECT_WEATHER_AWAY for the kinds listed below while something falls, kind 59 in weather
 * 1 and kind 26 in any weather but 1; TOWN_INSECT_WEATHER_OUT otherwise. */
int TownInsect_Weather(int kind, int falling)
{
    int falls = falling == 1 || falling == 2;
    switch (kind) {
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            return falls ? TOWN_INSECT_WEATHER_QUIET : TOWN_INSECT_WEATHER_OUT;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 12:
        case 13:
        case 14:
        case 15:
        case 21:
        case 22:
        case 23:
        case 25:
        case 27:
        case 28:
        case 29:
        case 32:
        case 37:
        case 50:
        case 51:
        case 54:
        case 55:
            return falls ? TOWN_INSECT_WEATHER_AWAY : TOWN_INSECT_WEATHER_OUT;
        case 59:
            return falling == 1 ? TOWN_INSECT_WEATHER_AWAY : TOWN_INSECT_WEATHER_OUT;
        case 26:
            return falling != 1 ? TOWN_INSECT_WEATHER_AWAY : TOWN_INSECT_WEATHER_OUT;
        default:
            return TOWN_INSECT_WEATHER_OUT;
    }
}
CLEAN_AS(func_ov003_0222d248, TownInsect_Weather)

/* func_ov003_0222d300: every 121st frame, the town records kept after a failed placing freed,
 * and the town insects that are active, out of view and with unk_234 clear sent away. */
void TownInsect_ClearFailed(void)
{
    data_ov003_02260554++;
    if (data_ov003_02260554 <= 0x78) {
        return;
    }
    data_ov003_02260554 = 0;
    for (int i = 0; i < TOWN_INSECT_TOWN_COUNT; i++) {
        TownInsect *insect = &data_ov003_022617bc[i];
        if (insect->kind == TOWN_INSECT_KIND_FAILED) {
            insect->kind = TOWN_INSECT_NO_KIND;
            insect->used = 0;
        } else if (insect->in_view == 0 && insect->unk_234 == 0 && insect->state == TOWN_INSECT_STATE_ACTIVE) {
            insect->state = TOWN_INSECT_STATE_LEAVING;
            insect->action = TOWN_INSECT_ACTION_END;
        }
    }
}
CLEAN_AS(func_ov003_0222d300, TownInsect_ClearFailed)

/* func_ov003_0222d388: an insect drawn from list `time_slot` of month `month` (insect_draw.h):
 * a level drawn below 100, and the first entry whose running weight is above it taken. Its
 * kind is written to *kind and 1 returned when it is not 0x30, is allowed
 * (TownInsect_KindAllowed) and does not keep away in this weather; 0 otherwise.
 * REQUIRES: `month` is 0-11 (TownInsect_DrawKindNow clamps it). */
int TownInsect_DrawKind(int month, int time_slot, u8 *kind)
{
    u8 level = (u8) MainRandom_Below(100);
    const InsectDrawList *lists = data_020dded8[month];
    if (lists == NULL) {
        return 0;
    }
    u8 count = lists[time_slot].count;
    int falling = Sky_Falling();
    for (u8 i = 0; i < count; i++) {
        const u8 *entry = &lists[time_slot].entries[i * 2];
        u8 found = entry[0];
        if (entry[1] <= level) {
            continue;
        }
        if (found != 0x30 && TownInsect_KindAllowed(found) != 0 &&
            TownInsect_Weather((s8) found, falling) != TOWN_INSECT_WEATHER_AWAY) {
            *kind = found;
            return 1;
        }
        return 0;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222d388, TownInsect_DrawKind)

/* func_ov003_0222d40c: whether insect `kind` may appear: always outside a session; in one, all
 * but kinds 8, 0xa, 0x19, 0x23, 0x30, 0x32, 0x33, 0x35-0x37, 0x3a and 0x3b. */
int TownInsect_KindAllowed(int kind)
{
    if (!town_insect_in_session()) {
        return 1;
    }
    switch (kind) {
        case 8:
        case 0xa:
        case 0x19:
        case 0x23:
        case 0x30:
        case 0x32:
        case 0x33:
        case 0x35:
        case 0x36:
        case 0x37:
        case TOWN_INSECT_KIND_3A:
        case TOWN_INSECT_KIND_3B:
            return 0;
        default:
            return 1;
    }
}
CLEAN_AS(func_ov003_0222d40c, TownInsect_KindAllowed)

/* func_ov003_0222d484: whether a special insect is due, with its kind and place. For the town
 * (`town` set) when nothing falls: kind 0x33 of place 8 when the town day has a spot
 * (TownDay_SpotPosition), else, with data_ov003_0226054c set, kind 0x33 of place 7 one time in
 * five. Otherwise, unless weather 1: kind 0x3b of place 7 when main asked for it
 * (data_ov003_02260538) and the second event insect is active and shown. */
int TownInsect_SpecialKind(u8 *kind, u8 *place, int town)
{
    Vec3 spot;
    int falling = Sky_Falling();
    if (town != 0) {
        if (falling == 0) {
            if (TownDay_SpotPosition(&spot) != 0) {
                *kind = 0x33;
                *place = 8;
                return 1;
            }
            if ((s8) data_ov003_0226054c > 0 && (int) MainRandom_Below(100) < 20) {
                *kind = 0x33;
                *place = 7;
                return 1;
            }
        }
    } else if (falling != 1) {
        TownInsect *event = &data_ov003_02260994[1];
        if (data_ov003_02260538 != 0 && event->state == TOWN_INSECT_STATE_ACTIVE &&
            event->action == TOWN_INSECT_ACTION_SHOWN) {
            *kind = TOWN_INSECT_KIND_3B;
            *place = 7;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0222d484, TownInsect_SpecialKind)

/* func_ov003_0222d518: the speed of the insect's animation. */
void TownInsect_SetAnimSpeed(TownInsect *insect, unsigned long speed)
{
    insect->model.frames.speed = (fx32) speed;
}
CLEAN_AS(func_ov003_0222d518, TownInsect_SetAnimSpeed)

/* func_ov003_0222d520: an insect's destructor (its parts in reverse). */
TownInsect *TownInsect_Destruct(TownInsect *insect)
{
    ModelPoolSlot_Destruct(&insect->slot);
    __cxa_vec_cleanup(insect->unk_1ec, 2, sizeof insect->unk_1ec[0], func_020012dc);
    ModelPoolFiles_Destruct(&insect->files);
    CatchSphere_Destruct(&insect->sphere);
    AnimatedModel_DestructComplete((AnimatedModel *) &insect->model);
    CollisionContacts_Destroy(&insect->contacts);
    TownInsectAnim_Destruct(&insect->anim);
    return insect;
}
CLEAN_AS(func_ov003_0222d520, TownInsect_Destruct)

/* func_ov003_0222d57c: an insect's constructor: its parts, its files reset, no kind, state or
 * effect, shown. */
TownInsect *TownInsect_Construct(TownInsect *insect)
{
    TownInsectAnim_Construct(&insect->anim);
    CollisionContacts_Construct(&insect->contacts);
    AnimatedModel_Construct((AnimatedModel *) &insect->model);
    CatchSphere_Construct(&insect->sphere);
    ModelPoolFiles_Construct(&insect->files);
    /* the sound source's base class's vtable, then its own */
    insect->source.vtable = (const SoundSourceVtable *) data_0213efe8;
    insect->source.vtable = (const SoundSourceVtable *) data_0213f020;
    __cxa_vec_ctor(insect->unk_1ec, 2, sizeof insect->unk_1ec[0], func_020012e8, func_020012dc);
    ModelPoolSlot_Construct(&insect->slot);
    ModelPoolFiles_Reset(&insect->files);
    insect->action = TOWN_INSECT_ACTION_SHOWN;
    insect->counter = 0;
    insect->angle_y = 0;
    insect->angle_z = 0;
    insect->angle_x = 0;
    insect->kind = TOWN_INSECT_NO_KIND;
    insect->state = TOWN_INSECT_STATE_NONE;
    insect->unk_170 = 0;
    insect->unk_24c = 1;
    insect->frames_left = 0;
    insect->unk_24b = 1;
    insect->unk_24a = 0;
    insect->used = 0;
    insect->in_view = 0;
    insect->unk_252 = 0;
    insect->effect = -1;
    return insect;
}
CLEAN_AS(func_ov003_0222d57c, TownInsect_Construct)

/* func_ov003_0222d68c: the counter at 0x24f stepped, back to 0 after 0x50. */
void TownInsect_StepCounter(TownInsect *insect)
{
    insect->counter++;
    if (insect->counter > 0x50) {
        insect->counter = 0;
    }
}
CLEAN_AS(func_ov003_0222d68c, TownInsect_StepCounter)

/* func_ov003_0222d6a8: the time slot of the hour now, as InsectTables_TimeSlot gives it: 1 for
 * 4-7, 2 for 8-15, 3 for 16, 4 for 17-18, 5 for 19-22, 0 for the rest. */
int TownInsect_TimeSlot(void)
{
    Time now;
    Calendar_Now(&now);
    u8 hour = now.hour;
    if (hour >= 4 && hour <= 7) {
        return 1;
    }
    if (hour >= 8 && hour <= 15) {
        return 2;
    }
    if (hour == 16) {
        return 3;
    }
    if (hour == 17 || hour == 18) {
        return 4;
    }
    if (hour >= 19 && hour <= 22) {
        return 5;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222d6a8, TownInsect_TimeSlot)

/* func_ov003_0222d6fc: an insect of this month and hour drawn into *kind (TownInsect_DrawKind);
 * a month out of range counts as January. */
int TownInsect_DrawKindNow(s8 *kind)
{
    u8 day_month[4];
    Clock_GetDayMonth(day_month);
    u8 month = (u8) (day_month[1] - 1);
    if (month > 11) {
        month = 0;
    }
    return TownInsect_DrawKind(month, TownInsect_TimeSlot(), (u8 *) kind) != 0;
}
CLEAN_AS(func_ov003_0222d6fc, TownInsect_DrawKindNow)

/* func_ov003_0222d738: whether `point` is on the tile of the point ahead of this console's
 * player, while the field actor keeps one (data_ov003_02260540). */
int TownInsect_OnPlayersAheadTile(const Vec3 *point)
{
    if (data_ov003_02260540 == 0) {
        return 0;
    }
    int x;
    int z;
    int ahead_x;
    int ahead_z;
    Position_Tile(&x, &z, (const Position *) point);
    Position_Tile(&ahead_x, &ahead_z, (const Position *) &data_ov003_02260558);
    return ahead_x == x && ahead_z == z;
}
CLEAN_AS(func_ov003_0222d738, TownInsect_OnPlayersAheadTile)

/* func_ov003_0222d77c: outside a session, whether the first event insect is shown: its model's
 * alpha above 0x1e, active, and of a kind other than 0x13. */
int TownInsect_EventShown(void)
{
    if (town_insect_in_session()) {
        return 0;
    }
    TownInsect *event = &data_ov003_02260994[0];
    return NNS_G3dMdlGetMdlAlpha(town_insect_model(event), 0) > 0x1e && event->state == TOWN_INSECT_STATE_ACTIVE &&
           event->kind != 0x13;
}
CLEAN_AS(func_ov003_0222d77c, TownInsect_EventShown)

/* func_ov003_0222d7d0: the insect `id` names hidden (TOWN_INSECT_ACTION_HIDDEN) and 0 returned
 * when it is active and its action is none of 9, 0xa, 0xb and 0x10; 1 otherwise.
 * QUIRK: an id with neither table's bit is taken as the record's address. */
int TownInsect_Hide(int id)
{
    TownInsect *insect = town_insect_by_id(id, (TownInsect *) (uintptr_t) (u32) id);
    u8 action = insect->action;
    if (action != TOWN_INSECT_ACTION_END && action != TOWN_INSECT_ACTION_LET_GO && action != 9 &&
        action != TOWN_INSECT_ACTION_HIDDEN && insect->state == TOWN_INSECT_STATE_ACTIVE) {
        insect->action = TOWN_INSECT_ACTION_HIDDEN;
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_0222d7d0, TownInsect_Hide)

/* fx32 degrees in the angle units of the game (0xb6 to a degree), through FX_MulFunc. */
static s16 town_insect_degrees(fx32 degrees)
{
    return (s16) FX_MulFunc(0xb6, degrees);
}

/* func_ov003_0222d83c: player `player`'s held insect placed by the matrix of the player's hand
 * (its position the matrix's translation, unbent from the globe) at `*scale` percent, turned
 * the way its kind is held up; an active one of some kinds also has its animation set. When
 * `end`, its action becomes TOWN_INSECT_ACTION_END and kind 0x39's effect ends. 0 when the
 * insect is in state 0 or 2, else 1. */
int TownInsect_HeldFromMatrix(int player, short *scale, Mtx43 *matrix, int end)
{
    TownInsect *insect = town_insect_at(data_ov003_02260e4c, player);
    int result = 1;
    insect->matrix = *matrix;
    TownInsect_SetScale(insect, *scale);
    insect->position.x = insect->matrix.m[3][0];
    insect->position.y = insect->matrix.m[3][1];
    insect->position.z = insect->matrix.m[3][2];
    Globe_Unbend(&insect->position, &insect->position);
    if (insect->action != TOWN_INSECT_ACTION_LET_GO) {
        short kind = insect->kind;
        if (kind == 0x1a) {
            insect->angle_x = 0;
            insect->angle_y = town_insect_degrees(0xc8000);
            insect->angle_z = town_insect_degrees(0x1e000);
        } else if (kind == 0xc || kind == 0xd || kind == 0x1d) {
            insect->angle_x = town_insect_degrees(0x91000);
            insect->angle_y = town_insect_degrees(0xc8000);
            insect->angle_z = town_insect_degrees(0x96000);
        } else if (kind == 0x35) {
            insect->angle_x = town_insect_degrees(0x91000);
            insect->angle_y = town_insect_degrees(0x64000);
            insect->angle_z = 0;
        } else {
            insect->angle_x = town_insect_degrees(0x35000);
            insect->angle_y = town_insect_degrees(0xc8000);
            insect->angle_z = town_insect_degrees(0x54000);
            if (insect->state == TOWN_INSECT_STATE_ACTIVE) {
                TownInsectModel *model = &insect->model;
                if (kind == 0x14 && (u16) (model->frames.frame >> 12) == 0) {
                    FrameCtrl_Init(&model->frames, 4, 1, 0x1000, 0);
                    model->frames.frame = 0x4000;
                } else if (kind == 0xa || kind == 0xb) {
                    AnimatedModel_SetFrame((AnimatedModel *) model, (u16) (model->frames.frame >> 12) == 0 ? 1 : 0);
                } else if (kind == 0x37) {
                    u16 frames = (u16) (model->frames.end >> 12);
                    if (frames == 0xe && (u16) (model->frames.frame >> 12) == 0xd) {
                        model->frames.frame = 0xa000;
                    } else if (frames != 0xe) {
                        FrameCtrl_Init(&model->frames, 0xe, 0, 0x1000, 0xa);
                    }
                }
            }
        }
    }
    if (insect->state == TOWN_INSECT_STATE_2 || insect->state == TOWN_INSECT_STATE_NONE) {
        result = 0;
    }
    if (end != 0) {
        insect->action = TOWN_INSECT_ACTION_END;
        if (insect->kind == TOWN_INSECT_KIND_GLOWING && insect->effect != -1) {
            EffectSystem_EndHandle(insect->effect);
            insect->effect = -1;
        }
    }
    return result;
}
CLEAN_AS(func_ov003_0222d83c, TownInsect_HeldFromMatrix)

/* func_ov003_0222da78: the first event insect put in view at `point`, with action 4. */
void TownInsect_SetEventPoint(int *point)
{
    TownInsect *event = &data_ov003_02260994[0];
    event->in_view = 1;
    /* a word at a time, as the original copies */
    event->position.x = point[0];
    event->position.y = point[1];
    event->position.z = point[2];
    event->action = 4;
}
CLEAN_AS(func_ov003_0222da78, TownInsect_SetEventPoint)

/* func_ov003_0222da9c: a new insect placed in the first free town record (TownInsect_Place):
 * of kind 0x33 at `place`, or of a kind drawn for this month and hour at its kind's place. When
 * that fails (and the kind is not 0x33) the record is kept as used with kind
 * TOWN_INSECT_KIND_FAILED until TownInsect_ClearFailed frees it. 0 without a free record. */
int TownInsect_PlaceNew(TownInsectProcess *process, int mode, s8 kind, int place)
{
    int placed = 0;
    for (u8 i = 0; i < TOWN_INSECT_TOWN_COUNT; i++) {
        TownInsect *insect = &data_ov003_022617bc[i];
        if (insect->used != 0) {
            continue;
        }
        if (kind == 0x33) {
            placed = TownInsect_Place(process, kind, (u8) place, mode);
        } else if (TownInsect_DrawKindNow(&kind) != 0) {
            placed = TownInsect_Place(process, kind, InsectTables_Place((u8) kind), mode);
        }
        if (placed == 0 && kind != 0x33) {
            insect->used = 1;
            insect->kind = TOWN_INSECT_KIND_FAILED;
        }
        return placed;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222da9c, TownInsect_PlaceNew)

/* func_ov003_0222db40: an insect of `kind` placed at a tile of `place` (TOWN_INSECT_MODE_TOWN:
 * in a free town record, TOWN_INSECT_MODE_EVENT: in the second event record); 1 when placed.
 *
 * The tiles start from a copy of the place's mask (kind 8: every tile marked but those around
 * the buildings with scene actors). For the town, the tiles around the other town insects are
 * marked (none for kind 0x33 or 8) and, but for kind 0x33, those around the players: each
 * player in the town in a session, else this console's player. A second insect of kind 0x23
 * is not placed. Outside a session kind 0x23 is placed beside a loose snowball farther than 12.0
 * from this console's player, at the snowball's size from it in a random direction, facing
 * away from it. A town insect placed is handed to func_ov003_0222ff2c. */
int TownInsect_Place(TownInsectProcess *process, int kind, int place, int mode)
{
    TownInsectMask mask;
    int slot = -1;
    TownInsect *insect;
    if (kind != 8) {
        TownInsect_CopyMask(&mask, place);
    } else {
        TownInsect_FillMask(&mask);
    }
    if (mode == TOWN_INSECT_MODE_TOWN) {
        for (u32 k = 0; k < TOWN_INSECT_TOWN_COUNT; k++) {
            TownInsect *other = &data_ov003_022617bc[k];
            if (other->used != 0) {
                if (kind != 0x33) {
                    if (kind == 0x23 && other->kind == 0x23) {
                        return 0;
                    }
                    if (kind != 8) {
                        TownTileMask_MarkAround(mask.rows, other->position.x, other->position.z, 1, 1, 1);
                    }
                }
            } else if (slot < 0) {
                slot = (int) k;
            }
        }
    }
    if (slot < 0 && mode != TOWN_INSECT_MODE_EVENT) {
        return 0;
    }
    Actor *player = SessionPlayers_ActorOf(TOWN_INSECT_THIS_PLAYER);
    if (player != NULL && mode == TOWN_INSECT_MODE_TOWN && kind != 0x33) {
        if (town_insect_in_session()) {
            for (int j = 0; j < 4; j++) {
                u8 scene;
                int x;
                int z;
                if (SessionPlayers_ScenePoint(&scene, &x, &z, -1, j) != 0 && scene == TOWN_INSECT_SCENE_TOWN) {
                    TownTileMask_MarkAround(mask.rows, x, z, 5, 8, 5);
                }
            }
        } else {
            TownTileMask_MarkAround(mask.rows, player->position.x, player->position.z, 5, 8, 5);
        }
    }
    if (mode == TOWN_INSECT_MODE_TOWN) {
        insect = &data_ov003_022617bc[slot];
    } else {
        insect = &data_ov003_02260994[1];
    }
    if (kind == 0x23 && !town_insect_in_session()) {
        for (u32 n = 0; n < 2; n++) {
            Snowman *ball = Snowman_IdleLooseBall((int) n);
            if (ball == NULL) {
                continue;
            }
            fx32 size = Snowman_Size(ball);
            short angle = TownInsectMove_RandomTurn(0x20, 1);
            if (player != NULL && Vec_DistanceXZ(&player->position, &ball->position) > 0xc000) {
                Vec3 *position = &insect->position;
                position->x = ball->position.x;
                position->y = ball->position.y;
                position->z = ball->position.z;
                int index = ((u16) angle >> 4) * 2;
                position->x += FX_MulFunc(FX_SinCosTable_[index], size);
                position->z += FX_MulFunc(FX_SinCosTable_[index + 1], size);
                insect->angle_y = Vec_YawTo(&ball->position, position);
                insect->used = 1;
                insect->kind = (s8) kind;
                insect->in_view = 0;
                insect->unk_21c = (int) n;
                TownInsect_StartTown(process, insect);
                return 1;
            }
        }
        return 0;
    }
    if (TownInsect_PickTile(insect, &mask, kind, place) != 0) {
        insect->used = 1;
        insect->kind = (s8) kind;
        insect->in_view = 0;
        insect->start.x = insect->position.x;
        insect->start.y = insect->position.y;
        insect->start.z = insect->position.z;
        if (mode == TOWN_INSECT_MODE_TOWN) {
            TownInsect_StartTown(process, insect);
        }
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov003_0222db40, TownInsect_Place)

/* func_ov003_0222ddac (called by main): the flag that lets kind 0x33 appear at random set. */
void TownInsect_SetFlag54c(void)
{
    data_ov003_0226054c = 1;
}
CLEAN_AS(func_ov003_0222ddac, TownInsect_SetFlag54c)

/* func_ov003_0222ddb8: the insects of a table (town or event, by `mode`) checked against the
 * box around the camera's point (2.0 across, from 7.0 behind to 3.0 ahead): those that keep
 * away in this weather and are out of view removed; the others have unk_246 set by the weather
 * and in_view by the box. Nothing while the camera's first word is 0. */
void TownInsect_UpdateView(TownInsectProcess *process, int mode)
{
    TownInsect *insect;
    int count;
    if (mode == TOWN_INSECT_MODE_TOWN) {
        insect = data_ov003_022617bc;
        count = TOWN_INSECT_TOWN_COUNT;
    } else {
        insect = data_ov003_02260994;
        count = TOWN_INSECT_EVENT_COUNT;
    }
    if (data_021c67a4 == 0) {
        return;
    }
    int left = data_021c67d0.x - 0x10000;
    int back = data_021c67d0.z - 0x1c000;
    int right = data_021c67d0.x + 0x10000;
    int front = data_021c67d0.z + 0xc000;
    int falling = Sky_Falling();
    for (u8 i = 0; i < count; i++, insect++) {
        if (insect->used == 0 || insect->kind < 0) {
            continue;
        }
        int weather = TownInsect_Weather(insect->kind, falling);
        if (insect->in_view == 0 && weather == TOWN_INSECT_WEATHER_AWAY) {
            TownInsect_Remove(process, insect, mode);
        } else {
            insect->unk_246 = weather == TOWN_INSECT_WEATHER_QUIET ? 0 : 1;
            int x = insect->position.x;
            int z = insect->position.z;
            insect->in_view = left < x && right > x && back < z && front > z;
        }
    }
}
CLEAN_AS(func_ov003_0222ddb8, TownInsect_UpdateView)

/* func_ov003_0222dec4: in a session, the insects of a table checked against the box around
 * player `player`'s point (x, z), as TownInsect_UpdateView does: those that keep away in this
 * weather (not when this system does not hold the scene) and are out of view removed; the
 * others coming into the box are put in view with the player's bit set, those out of it have
 * the bit cleared, and a town insect in view that no player's bit holds is put out of view.
 * REQUIRES: `player` is 0-3. */
void TownInsect_UpdatePlayerView(TownInsectProcess *process, int mode, int player, int x, int z)
{
    TownInsect *insect;
    int count;
    if (mode == TOWN_INSECT_MODE_TOWN) {
        insect = data_ov003_022617bc;
        count = TOWN_INSECT_TOWN_COUNT;
    } else {
        insect = data_ov003_02260994;
        count = TOWN_INSECT_EVENT_COUNT;
    }
    int left = x - 0x10000;
    int back = z - 0x1c000;
    int right = x + 0x10000;
    int front = z + 0xc000;
    int falling = Sky_Falling();
    u32 bit = town_insect_shl(1, player);
    u32 keep = ~(bit & 0xf);
    for (u8 i = 0; i < count; i++, insect++) {
        if (insect->used == 0 || insect->kind < 0) {
            continue;
        }
        u32 near = insect->players_near;
        int weather = TownInsect_Weather(insect->kind, falling);
        if (LinkGlobal_HoldsScene() == 0 && weather == TOWN_INSECT_WEATHER_AWAY) {
            weather = TOWN_INSECT_WEATHER_OUT;
        }
        u8 in_view = insect->in_view;
        if (in_view == 0 && weather == TOWN_INSECT_WEATHER_AWAY) {
            TownInsect_Remove(process, insect, mode);
            continue;
        }
        int px = insect->position.x;
        if (left < px && right > px && back < insect->position.z && front > insect->position.z) {
            if (in_view == 0) {
                insect->in_view = 1;
                near |= bit;
                insect->players_near = (u8) near;
            }
        } else if ((town_insect_lsr(near, player) & 1) != 0) {
            near &= keep;
            insect->players_near = (u8) near;
        } else if (in_view != 0 && near == 0 && mode == TOWN_INSECT_MODE_TOWN) {
            insect->in_view = 0;
        }
    }
}
CLEAN_AS(func_ov003_0222dec4, TownInsect_UpdatePlayerView)

/* func_ov003_0222e008: every insect removed, the process's two blocks freed with the event
 * insects, its three model pools destroyed and item drops allowed again. Always 1. */
int TownInsect_RemoveAll(TownInsectProcess *process)
{
    for (int i = 0; i < TOWN_INSECT_TOWN_COUNT; i++) {
        TownInsect_Remove(process, &data_ov003_022617bc[i], TOWN_INSECT_MODE_TOWN);
    }
    for (int i = 0; i < TOWN_INSECT_EVENT_COUNT; i++) {
        TownInsect_Remove(process, &data_ov003_02260994[i], TOWN_INSECT_MODE_EVENT);
        Heap_FreeCurrent(process->blocks[i]);
        process->blocks[i] = NULL;
    }
    for (int i = 0; i < TOWN_INSECT_HELD_COUNT; i++) {
        TownInsect_Remove(process, &data_ov003_02260e4c[i], TOWN_INSECT_MODE_HELD);
    }
    ModelPool_Destroy(&process->pools[0]);
    ModelPool_Destroy(&process->pools[1]);
    ModelPool_Destroy(&process->pools[2]);
    TileRequests_AllowItemDrop();
    return 1;
}
CLEAN_AS(func_ov003_0222e008, TownInsect_RemoveAll)

/* func_ov003_0222e0ac: the three tables drawn (TownInsect_DrawTable). Always 1. */
int TownInsect_DrawAll(TownInsectProcess *process)
{
    int result = TownInsect_DrawTable(process, data_ov003_022617bc, TOWN_INSECT_TOWN_COUNT);
    result &= TownInsect_DrawTable(process, data_ov003_02260994, TOWN_INSECT_EVENT_COUNT);
    result &= TownInsect_DrawTable(process, data_ov003_02260e4c, TOWN_INSECT_HELD_COUNT);
    return result;
}
CLEAN_AS(func_ov003_0222e0ac, TownInsect_DrawAll)

/* func_ov003_0222e0ec: the model's matrix built in main's scratch matrix: a held insect's
 * (`held`) from its player's hand turned about x, any other's from its position bent onto the
 * globe, turned about x by the globe's angle plus its own; then turned about y and z when those
 * angles are set. A held insect of kind 0x39 also has its effect 0x3a, at a point ahead of it
 * by its scale times -0.2 along the matrix's z, started (the first time) or moved. */
void TownInsect_SetMatrix(int unused, TownInsect *insect, int held)
{
    (void) unused;
    Vec3 bent;
    int angle = Globe_BendFar(&bent, &insect->position);
    if (held != 0) {
        data_021fbe48 = insect->matrix;
        Mtx43_RotateX(&data_021fbe48, insect->angle_x);
    } else {
        Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
        Mtx43_RotateX(&data_021fbe48, (short) (angle + insect->angle_x));
    }
    if (insect->angle_y != 0) {
        Mtx43_RotateY(&data_021fbe48, insect->angle_y);
    }
    if (insect->angle_z != 0) {
        Mtx43_RotateZ(&data_021fbe48, insect->angle_z);
    }
    insect->model.matrix = data_021fbe48;
    if (held == 0 || insect->kind != TOWN_INSECT_KIND_GLOWING) {
        return;
    }
    Mtx43 rotation = data_021fbe48;
    Vec3 point = {rotation.m[3][0], rotation.m[3][1], rotation.m[3][2]};
    rotation.m[3][2] = 0;
    rotation.m[3][1] = 0;
    rotation.m[3][0] = 0;
    Vec3 ahead = {0, 0, FX_MulFunc(insect->scale.x, -0x333)};
    Vec3 moved;
    MTX_MultVec43(&ahead, &rotation, &moved);
    point.x += moved.x;
    point.y += moved.y;
    point.z += moved.z;
    Globe_Unbend(&point, &point);
    if (insect->unk_21c == 0) {
        s16 extra = (s16) insect->scale.x;
        insect->effect = EffectSystem_StartKind(0x3a, &point, NULL, &extra);
        insect->unk_21c = 1;
    } else {
        s16 extra = (s16) insect->scale.x;
        if (insect->effect != -1) {
            EffectSystem_MoveHandle(insect->effect, &point, NULL, &extra);
        }
    }
}
CLEAN_AS(func_ov003_0222e0ec, TownInsect_SetMatrix)

/* func_ov003_0222e264: whether the insect casts a shadow: its kind's size above 1, and not of
 * kinds 0x18, 0x30, 0x32, 0x33, 0x3a, 0x3b, nor of kinds 0x1e and 0x31 while shown. */
int TownInsect_HasShadow(int unused, TownInsect *insect)
{
    (void) unused;
    int kind = insect->kind;
    if (town_insect_kind_info(kind)->size <= 1) {
        return 0;
    }
    switch (kind) {
        case 0x1e:
        case 0x31:
            return insect->action != TOWN_INSECT_ACTION_SHOWN;
        case 0x18:
        case 0x30:
        case 0x32:
        case 0x33:
        case TOWN_INSECT_KIND_3A:
        case TOWN_INSECT_KIND_3B:
            return 0;
        default:
            return 1;
    }
}
CLEAN_AS(func_ov003_0222e264, TownInsect_HasShadow)

/* func_ov003_0222e2d8: the insect drawn at its scale when that is above 0, with its shadow
 * (TownInsect_HasShadow) of its kind's size, fading as its model's alpha falls (level
 * 0x1f - 2 * (0x1f - alpha), 0 at the least). */
void TownInsect_Draw(void *unused, TownInsect *insect)
{
    if (insect->scale.x <= 0) {
        return;
    }
    int faded = (0x1f - NNS_G3dMdlGetMdlAlpha(town_insect_model(insect), 0)) * 2;
    int level = faded > 0x1f ? 0 : 0x1f - faded;
    AnimatedModel_Draw((AnimatedModel *) &insect->model, &insect->scale);
    if (TownInsect_HasShadow((int) (uintptr_t) unused, insect) != 0) {
        CharaShadow_DrawLevel(&insect->position, town_insect_kind_info(insect->kind)->size, 0x9000, (u8) level);
    }
}
CLEAN_AS(func_ov003_0222e2d8, TownInsect_Draw)

/* func_ov003_0222e358: the insect's scale, the same on the three axes, set to `percent` of 1.0
 * (by FX_Div but at 100). */
void TownInsect_SetScale(TownInsect *insect, int percent)
{
    if (percent == 100) {
        insect->scale.x = 0x1000;
        insect->scale.y = 0x1000;
        insect->scale.z = 0x1000;
    } else {
        insect->scale.x = FX_Div((fx32) ((u32) percent << 12), 0x64000);
        insect->scale.y = insect->scale.x;
        insect->scale.z = insect->scale.x;
    }
}
CLEAN_AS(func_ov003_0222e358, TownInsect_SetScale)

/* func_ov003_0222e3a4: the insect `id` names caught by this console's player: 0 when it cannot
 * be (not a town or event insect, not active, its action 9, 0xb or 0x10, kinds 0x1e, 0x31 and
 * 0x35 not fully shown, kind 0x35 shown); else hidden (but kinds 0x3a and 0x3b), and in a
 * session where this system does not hold the scene the catch is sent (handler 0x28, kind 6)
 * with data_ov003_0226053c set to 2 to wait for the answer. 1 when caught.
 * QUIRK: the original also refuses a kind of -1, read as an unsigned byte, which never
 * matches. */
int TownInsect_Catch(u8 id)
{
    TownInsect *insect = town_insect_by_id(id, NULL);
    if (insect == NULL) {
        return 0;
    }
    u8 action = insect->action;
    u8 kind = (u8) insect->kind;
    if (insect->state != TOWN_INSECT_STATE_ACTIVE || action == TOWN_INSECT_ACTION_LET_GO || action == 9 ||
        action == TOWN_INSECT_ACTION_HIDDEN) {
        return 0;
    }
    if ((kind == 0x31 || kind == 0x1e || kind == 0x35) && NNS_G3dMdlGetMdlAlpha(town_insect_model(insect), 0) < 0x1f) {
        return 0;
    }
    if (kind == 0x35 && action == TOWN_INSECT_ACTION_SHOWN) {
        return 0;
    }
    if (insect->kind != TOWN_INSECT_KIND_3A && insect->kind != TOWN_INSECT_KIND_3B) {
        NNS_G3dMdlSetMdlAlpha(town_insect_model(insect), 0, 0);
        insect->action = TOWN_INSECT_ACTION_HIDDEN;
    }
    if (town_insect_in_session() && LinkGlobal_HoldsScene() == 0) {
        data_ov003_0226053c = 2;
        town_insect_send(&id, 0x28, 6);
    }
    return 1;
}
CLEAN_AS(func_ov003_0222e3a4, TownInsect_Catch)

/* func_ov003_0222e4c0: the insect `id` names shown again (alpha 0x1f, TOWN_INSECT_ACTION_SHOWN)
 * when it is hidden and has a kind.
 * QUIRK: an id with neither table's bit is taken as the record's address. */
void TownInsect_Show(int id)
{
    TownInsect *insect = town_insect_by_id(id, (TownInsect *) (uintptr_t) (u32) id);
    if (insect->action != TOWN_INSECT_ACTION_HIDDEN || insect->kind < 0) {
        return;
    }
    insect->action = TOWN_INSECT_ACTION_SHOWN;
    NNS_G3dMdlSetMdlAlpha(town_insect_model(insect), 0, 0x1f);
}
CLEAN_AS(func_ov003_0222e4c0, TownInsect_Show)

/* func_ov003_0222e538: a catch that did not happen undone: the insect shown again
 * (TownInsect_Show) and, in a session where this system does not hold the scene, the release
 * sent (handler 0x2f, kind 4). For a town or event insect in such a session it happens only
 * when data_ov003_0226053c (the answer to TownInsect_Catch) is 1; the result is that value
 * there, else 1 (0 when it did not happen otherwise). */
u8 TownInsect_Release(int id, u8 unused)
{
    (void) unused;
    TownInsect *insect = town_insect_by_id(id, NULL);
    int release = insect == NULL ? 1 : 0;
    if (release != 1 && town_insect_in_session() && LinkGlobal_HoldsScene() == 0) {
        release = data_ov003_0226053c;
    }
    if (release == 1) {
        TownInsect_Show(id);
        u8 byte = (u8) id;
        if (town_insect_in_session() && LinkGlobal_HoldsScene() == 0) {
            town_insect_send(&byte, 0x2f, 4);
        }
    }
    return (u8) release;
}
CLEAN_AS(func_ov003_0222e538, TownInsect_Release)

/* func_ov003_0222e5fc: the insect `id` names taken: leaving, the catch sent in a session
 * (handler 0x30, kind 4). The kind caught is returned: kinds 0x3a and 0x3b stay active with
 * action 8 and are caught as kinds 0xb and 0x18.
 * REQUIRES: `id` names a town or event insect (the original reads no record otherwise). */
int TownInsect_Caught(u8 id)
{
    TownInsect *insect = town_insect_by_id(id, NULL);
    insect->frames_left = 0;
    insect->state = TOWN_INSECT_STATE_LEAVING;
    if (town_insect_in_session()) {
        town_insect_send(&id, 0x30, 4);
    }
    int kind = insect->kind;
    switch (kind) {
        case TOWN_INSECT_KIND_3A:
            insect->action = 8;
            insect->state = TOWN_INSECT_STATE_ACTIVE;
            return 0xb;
        case TOWN_INSECT_KIND_3B:
            insect->action = 8;
            insect->state = TOWN_INSECT_STATE_ACTIVE;
            return 0x18;
        default:
            return kind;
    }
}
CLEAN_AS(func_ov003_0222e5fc, TownInsect_Caught)

/* func_ov003_0222e6c4: player `player`'s held insect ended (TOWN_INSECT_ACTION_END), its effect
 * ended; with `send` and in a session, when the player is this system's, it is sent (handler
 * 0x30, kind 4). */
void TownInsect_EndHeld(u8 player, int send)
{
    TownInsect *insect = town_insect_at(data_ov003_02260e4c, player);
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) != 0 && send != 0 && Session_IsLocalSlot(session, player) != 0) {
        town_insect_send(&player, 0x30, 4);
    }
    if (insect->effect != -1) {
        EffectSystem_EndHandle(insect->effect);
        insect->effect = -1;
    }
    insect->action = TOWN_INSECT_ACTION_END;
}
CLEAN_AS(func_ov003_0222e6c4, TownInsect_EndHeld)

/* func_ov003_0222e750: the insect `id` names hidden: its alpha set to 0 when active, and its
 * action TOWN_INSECT_ACTION_HIDDEN.
 * REQUIRES: `id` names a town or event insect (the original reads no record otherwise). */
void TownInsect_HideById(int id)
{
    TownInsect *insect = town_insect_by_id(id, NULL);
    if (insect->state == TOWN_INSECT_STATE_ACTIVE) {
        NNS_G3dMdlSetMdlAlpha(town_insect_model(insect), 0, 0);
    }
    insect->action = TOWN_INSECT_ACTION_HIDDEN;
}
CLEAN_AS(func_ov003_0222e750, TownInsect_HideById)

/* func_ov003_0222e7bc: whether kind `kind` flies off when startled (TownInsect_Startle): kinds
 * 0xc, 0xd and 0x1b-0x1e and 0x31. */
int TownInsect_KindFlees(int kind)
{
    switch (kind) {
        case 0xc:
        case 0xd:
        case 0x1b:
        case 0x1c:
        case 0x1d:
        case 0x1e:
        case 0x31:
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov003_0222e7bc, TownInsect_KindFlees)

/* func_ov003_0222e7f8: the insect `id` names startled: one of the kinds of TownInsect_KindFlees
 * that is not leaving, hidden or ended goes to action 0x11 (with its timer cut to 6) unless
 * already there or its timer is 6 or less; any other leaves.
 * REQUIRES: `id` names a town or event insect (the original reads no record otherwise). */
void TownInsect_Startle(int id)
{
    TownInsect *insect = town_insect_by_id(id, NULL);
    insect->frames_left = 0;
    u8 action = insect->action;
    if (TownInsect_KindFlees(insect->kind) != 0 && insect->state != TOWN_INSECT_STATE_LEAVING &&
        action != TOWN_INSECT_ACTION_HIDDEN && action != TOWN_INSECT_ACTION_END) {
        if (action != TOWN_INSECT_ACTION_11 && insect->timer > 6) {
            insect->timer = 6;
            insect->action = TOWN_INSECT_ACTION_11;
        }
    } else {
        insect->state = TOWN_INSECT_STATE_LEAVING;
    }
}
CLEAN_AS(func_ov003_0222e7f8, TownInsect_Startle)

/* func_ov003_0222e898: player `player`'s held insect taken up as kind `kind` (0x25 as 0x39,
 * 0x3a as 0xb, 0x3b as 0x18), hidden, in state 1; when the player's actor exists it is put 1.7
 * above it and 0.98 ahead of it, facing its way. */
void TownInsect_TakeHeld(int kind, int player)
{
    TownInsect *insect = town_insect_at(data_ov003_02260e4c, player);
    Actor *actor = SessionPlayers_ActorOf(player);
    if (actor != NULL) {
        Vec3 *position = &insect->position;
        position->x = actor->position.x;
        position->y = actor->position.y;
        position->z = actor->position.z;
        position->y += 0x1b34;
        s16 angle = actor->angle[1];
        insect->angle_y = angle;
        int index = ((u16) angle >> 4) * 2;
        position->x += FX_MulFunc(0xfae, FX_SinCosTable_[index]);
        position->z += FX_MulFunc(0xfae, FX_SinCosTable_[index + 1]);
    }
    insect->state = TOWN_INSECT_STATE_1;
    insect->action = TOWN_INSECT_ACTION_HIDDEN;
    switch (kind) {
        case 0x25:
            insect->kind = TOWN_INSECT_KIND_GLOWING;
            break;
        case TOWN_INSECT_KIND_3A:
            insect->kind = 0xb;
            break;
        case TOWN_INSECT_KIND_3B:
            insect->kind = 0x18;
            break;
        default:
            insect->kind = (s8) kind;
            break;
    }
}
CLEAN_AS(func_ov003_0222e898, TownInsect_TakeHeld)

/* func_ov003_0222e970: where player `player`'s held insect is. */
Vec3 *TownInsect_HeldPosition(int player)
{
    return &town_insect_at(data_ov003_02260e4c, player)->position;
}
CLEAN_AS(func_ov003_0222e970, TownInsect_HeldPosition)

/* func_ov003_0222e98c: whether kind `kind` lives high up, out of the camera's sight when it
 * is past the goal (TownInsect_DrawTable): the kinds of places 13, 14 and 16 and kind 0x35
 * (InsectTables_Place). */
int TownInsect_KindHighUp(int unused, int kind)
{
    (void) unused;
    switch (kind) {
        case 9:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x1f:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x34:
        case 0x35:
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov003_0222e98c, TownInsect_KindHighUp)

/* func_ov003_0222ea04: the active insects in view of a table of `count` drawn
 * (TownInsect_Draw); the town's insects of the kinds of TownInsect_KindHighUp only while the
 * camera is not past the goal for their point. Always 1. */
int TownInsect_DrawTable(void *unused, TownInsect *insects, int count)
{
    for (int i = 0; i < count; i++, insects++) {
        if (insects->state != TOWN_INSECT_STATE_ACTIVE || insects->in_view == 0) {
            continue;
        }
        if (count == TOWN_INSECT_TOWN_COUNT) {
            if (TownInsect_KindHighUp((int) (uintptr_t) unused, (u8) insects->kind) == 0 ||
                CameraControl_IsPastGoalZ(&insects->position, 0x2000, 0x2000) == 0) {
                TownInsect_Draw(unused, insects);
            }
        } else {
            TownInsect_Draw(unused, insects);
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_0222ea04, TownInsect_DrawTable)

/* func_ov003_0222ea84: player `player`'s held insect's state; one without a kind is ended
 * first (TOWN_INSECT_ACTION_END, state 0). */
u8 TownInsect_HeldState(int player)
{
    TownInsect *insect = town_insect_at(data_ov003_02260e4c, player);
    if (insect->kind < 0) {
        insect->action = TOWN_INSECT_ACTION_END;
        insect->state = TOWN_INSECT_STATE_NONE;
    }
    return insect->state;
}
CLEAN_AS(func_ov003_0222ea84, TownInsect_HeldState)

/* func_ov003_0222eabc: player `player`'s held insect let go facing `angle`, at full scale: its
 * kind's start function (data_ov003_0223c2ac) run, then kinds 0xc, 0xd and 0x1b-0x1d handed to
 * func_ov003_02234030 and kind 0x39's effect ended. Without a kind of the table it is ended
 * and leaves. */
void TownInsect_LetGo(int player, int angle)
{
    TownInsect *insect = town_insect_at(data_ov003_02260e4c, player);
    insect->action = TOWN_INSECT_ACTION_LET_GO;
    insect->angle_x = 0;
    insect->angle_z = 0;
    TownInsect_SetScale(insect, 100);
    insect->angle_y = (s16) angle;
    int kind = insect->kind;
    if (kind >= 0 && kind < TOWN_INSECT_KINDS) {
        ((TownInsectKindFn) (uintptr_t) data_ov003_0223c2ac[kind].start)(insect);
        switch (insect->kind) {
            case 0xc:
            case 0xd:
            case 0x1b:
            case 0x1c:
            case 0x1d:
                TownInsectMove_TurnToHeading(insect, 1);
                break;
            case TOWN_INSECT_KIND_GLOWING:
                if (insect->effect != -1) {
                    EffectSystem_EndHandle(insect->effect);
                    insect->effect = -1;
                }
                break;
            default:
                break;
        }
    } else {
        TownInsect_EndHeld((u8) player, 0);
        insect->state = TOWN_INSECT_STATE_LEAVING;
    }
}
CLEAN_AS(func_ov003_0222eabc, TownInsect_LetGo)

/* func_ov003_0222eb94: whether the insect can be caught. Always while its action is 9 or 0xb;
 * otherwise never for kinds 0x3a and 0x3b or in a session where this system does not hold the
 * scene; with an action other than 7, never for the kinds of places 13 and 14 and kinds 0x32
 * and 0x35 (TownInsect_KindHighPlace's, and those two), nor for kind 0x33 while its words at
 * 0x220 and 0x228 differ, nor for kind 0x31 in action 6. */
int TownInsect_CanBeCaught(int unused, TownInsect *insect)
{
    (void) unused;
    u8 action = insect->action;
    s8 kind = insect->kind;
    if (action == 9 || action == TOWN_INSECT_ACTION_LET_GO) {
        return 1;
    }
    if (kind == TOWN_INSECT_KIND_3A || kind == TOWN_INSECT_KIND_3B ||
        (town_insect_in_session() && LinkGlobal_HoldsScene() == 0)) {
        return 0;
    }
    if (action == 7) {
        return 1;
    }
    switch (kind) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 31:
        case 33:
        case 34:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 50:
        case 52:
        case 53:
            return 0;
        case 0x33:
            return insect->unk_220 == insect->unk_228;
        case 0x31:
            return action != 6;
        default:
            return 1;
    }
}
CLEAN_AS(func_ov003_0222eb94, TownInsect_CanBeCaught)

/* func_ov003_0222ec74: the players' held insects run. One whose player is not this system's
 * (slot 4 counting as 0), that is not being let go and whose player is in none of states 6,
 * 0x57, 0x58 and 0x76 is removed (kind 0x39's effect ended first); the others by their state:
 * 1 func_ov003_0222ffdc, 2 func_ov003_0222fa20 and a collision move in place with its kind's
 * radius, 3 func_ov003_0222f6b0, 4 ended and removed.
 * QUIRK: kind 0x39's effect is ended without checking it has one (handle -1). */
void TownInsect_UpdateHeld(TownInsectProcess *process)
{
    int local = data_020ccf94->local_slot;
    if (local == 4) {
        local = 0;
    }
    TownInsect *insect = data_ov003_02260e4c;
    for (u8 i = 0; i < TOWN_INSECT_HELD_COUNT; i++, insect++) {
        int state = PlayerActorOps_State(i);
        if (local != i && insect->action != TOWN_INSECT_ACTION_LET_GO && state != 0x57 && state != 0x58 && state != 0x76 &&
            state != 6) {
            if (insect->kind == TOWN_INSECT_KIND_GLOWING) {
                EffectSystem_EndHandle(insect->effect);
                insect->effect = -1;
            }
            TownInsect_Remove(process, insect, TOWN_INSECT_MODE_HELD);
            continue;
        }
        switch (insect->state) {
            case TOWN_INSECT_STATE_1:
                TownInsect_StartHeld(process, insect);
                break;
            case TOWN_INSECT_STATE_2:
                TownInsect_Load(process, insect, 2);
                CollisionQuery_Move(&insect->contacts, &insect->position, &insect->position, insect->angle_y,
                                    town_insect_kind_info(insect->kind)->size, NULL, 0xa);
                break;
            case TOWN_INSECT_STATE_ACTIVE:
                TownInsect_Run(process, insect, i, TOWN_INSECT_MODE_HELD);
                break;
            case TOWN_INSECT_STATE_LEAVING:
                insect->action = TOWN_INSECT_ACTION_END;
                TownInsect_Remove(process, insect, TOWN_INSECT_MODE_HELD);
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov003_0222ec74, TownInsect_UpdateHeld)

/* func_ov003_0222ed90: the event insects run by their state: 2 func_ov003_0222fa20, 3
 * func_ov003_0222f6b0 while its x is above 1.0, 4 ended and removed. */
void TownInsect_UpdateEvent(TownInsectProcess *process)
{
    TownInsect *insect = data_ov003_02260994;
    for (u8 i = 0; i < TOWN_INSECT_EVENT_COUNT; i++, insect++) {
        switch (insect->state) {
            case TOWN_INSECT_STATE_2:
                TownInsect_Load(process, insect, 1);
                break;
            case TOWN_INSECT_STATE_ACTIVE:
                if (insect->position.x > 0x1000) {
                    TownInsect_Run(process, insect, i, TOWN_INSECT_MODE_EVENT);
                }
                break;
            case TOWN_INSECT_STATE_LEAVING:
                insect->action = TOWN_INSECT_ACTION_END;
                TownInsect_Remove(process, insect, TOWN_INSECT_MODE_EVENT);
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov003_0222ed90, TownInsect_UpdateEvent)

/* func_ov003_0222ee10: whether the insect is on a tile it may be on: one of the kinds of places
 * 13, 14 and 16 (InsectTables_Place) must be on a tile whose item code is of set A (0 without an
 * item there); the others always (0 without a kind). */
int TownInsect_OnItsTile(int unused, TownInsect *insect)
{
    (void) unused;
    int kind = insect->kind;
    if (kind < 0) {
        return 0;
    }
    switch (kind) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 31:
        case 33:
        case 34:
        case 35:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 52: {
            int x = 0;
            int z = 0;
            Position_Tile(&x, &z, (const Position *) &insect->position);
            AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
            if (map == NULL) {
                break;
            }
            int acre_x = x >> 4;
            int acre_z = z >> 4;
            u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - (acre_x << 4), z - (acre_z << 4), 0);
            if (code == NULL || !town_insect_code_in_set_a(*code)) {
                return 0;
            }
            break;
        }
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov003_0222ee10, TownInsect_OnItsTile)

/* func_ov003_0222ef80: whether a linked insect's message no longer matches it: 0 when no point
 * came (x 0); 1 when it has no kind or another than `kind`; else 0.
 * QUIRK: in the last case the distance from its position to (x, 0, z) is computed and thrown
 * away. */
int TownInsect_CheckTarget(int unused, TownInsect *insect, int kind, int x, int z)
{
    (void) unused;
    int own = insect->kind;
    if (x == 0) {
        return 0;
    }
    if (own < 0 || own != kind) {
        return 1;
    }
    Vec3 point = {x, 0, z};
    Vec_DistanceXZ(&insect->position, &point);
    return 0;
}
CLEAN_AS(func_ov003_0222ef80, TownInsect_CheckTarget)

/* func_ov003_0222efc0: the town insects run while linked. For each, in a session, the
 * session's message of it is read (TownInsectTables_PublishRecord, then TownInsectTables_ReadRecord with its kind,
 * point and byte 0x254): a free record whose message names a kind and a point (x above 1)
 * becomes that insect, in state 2; a message of byte 0xff or x 1 removes it (not kind 0x1e in
 * actions 9 and 0x11); another moves its target. Then by its state:
 *   2  removed when in a session (this system not holding the scene) the message's kind is
 *      another and x is set, else run by func_ov003_0222fa20 while on its tile
 *      (TownInsect_OnItsTile); outside, always run;
 *   3  in a session, ended and removed when the message no longer matches it (this system not
 *      holding the scene), unk_246 set by the weather; then run by func_ov003_0222f6b0;
 *   4  outside a session ended and removed; holding the scene, its sound moved and, the first
 *      time, its byte 0x254 set to 0xff, its target and position to (1, 1, 1) and its id sent
 *      (handler 0x30, kind 7), then removed after 200 frames; else its sound moved and removed
 *      when its byte 0x254 is 0xff.
 * QUIRK: the x and z and the kind of the message are those of the last insect read when this
 * one's was not (TownInsectTables_PublishRecord answered).
 * QUIRK: sending an id (bit 4 set) ends the loop, so the insects after it wait a frame.
 * REQUIRES: whether this system is in the session does not change during the loop (the original
 * reads the message's kind uninitialised otherwise). */
void TownInsect_UpdateLinked(TownInsectProcess *process)
{
    TownInsect *insect = data_ov003_022617bc;
    int x = 0;
    int z = 0;
    s8 kind = -1;
    NetSession *session = data_020ccf94;
    for (u8 i = 0; i < TOWN_INSECT_TOWN_COUNT; i++, insect++) {
        int state = insect->state;
        if (Session_IsSlotTaken(session, session->local_slot) != 0) {
            kind = -1;
            if (TownInsectTables_PublishRecord(process, i, insect->kind, &insect->target, insect->unk_254, 1) == 0) {
                u8 byte254 = 0;
                if (TownInsectTables_ReadRecord(process, i, &kind, &x, &z, &byte254) != 0) {
                    if (state == TOWN_INSECT_STATE_NONE) {
                        if (x > 1 && kind >= 0) {
                            insect->position.x = x;
                            insect->position.z = z;
                            insect->target.x = insect->position.x;
                            insect->target.y = insect->position.y;
                            insect->target.z = insect->position.z;
                            insect->kind = kind;
                            insect->used = 1;
                            insect->in_view = 0;
                            insect->start.x = insect->position.x;
                            insect->start.y = insect->position.y;
                            insect->start.z = insect->position.z;
                            insect->state = TOWN_INSECT_STATE_2;
                        }
                    } else if (byte254 == TOWN_INSECT_BYTE254_GONE || x == 1) {
                        if (!(kind == 0x1e && (insect->action == 9 || insect->action == TOWN_INSECT_ACTION_11))) {
                            TownInsect_Remove(process, insect, TOWN_INSECT_MODE_TOWN);
                        }
                    } else {
                        if (insect->target.x != x || insect->target.z != z) {
                            insect->target.x = x;
                            insect->target.z = z;
                            insect->start.x = insect->position.x;
                            insect->start.y = insect->position.y;
                            insect->start.z = insect->position.z;
                        }
                        insect->unk_254 = byte254;
                    }
                }
            }
        }
        switch (state) {
            case TOWN_INSECT_STATE_2:
                if (LinkGlobal_HoldsScene() == 0 && Session_IsSlotTaken(session, session->local_slot) != 0) {
                    if (kind != insect->kind && x > 0) {
                        TownInsect_Remove(process, insect, TOWN_INSECT_MODE_TOWN);
                    } else if (TownInsect_OnItsTile((int) (uintptr_t) process, insect) != 0) {
                        TownInsect_Load(process, insect, 0);
                    }
                } else {
                    TownInsect_Load(process, insect, 0);
                }
                break;
            case TOWN_INSECT_STATE_ACTIVE:
                if (Session_IsSlotTaken(session, session->local_slot) != 0) {
                    if (LinkGlobal_HoldsScene() == 0 &&
                        TownInsect_CheckTarget((int) (uintptr_t) process, insect, kind, x, z) != 0) {
                        insect->action = TOWN_INSECT_ACTION_END;
                        TownInsect_Remove(process, insect, TOWN_INSECT_MODE_TOWN);
                    }
                    int own = insect->kind;
                    insect->unk_246 = TownInsect_Weather(own, Sky_Falling()) == TOWN_INSECT_WEATHER_QUIET ? 0 : 1;
                }
                TownInsect_Run(process, insect, i, TOWN_INSECT_MODE_TOWN);
                break;
            case TOWN_INSECT_STATE_LEAVING:
                if (Session_IsSlotTaken(session, session->local_slot) == 0) {
                    insect->action = TOWN_INSECT_ACTION_END;
                    TownInsect_Remove(process, insect, TOWN_INSECT_MODE_TOWN);
                } else if (LinkGlobal_HoldsScene() != 0) {
                    Vec3 at = insect->position;
                    SoundSource_UpdateAt(&insect->source, &at);
                    if (insect->unk_254 != TOWN_INSECT_BYTE254_GONE) {
                        insect->unk_254 = TOWN_INSECT_BYTE254_GONE;
                        i |= TOWN_INSECT_ID_TOWN;
                        insect->target.x = 1;
                        insect->target.y = 1;
                        insect->target.z = 1;
                        insect->position.x = 1;
                        insect->position.y = 1;
                        insect->position.z = 1;
                        Session_BeginMessage(session);
                        Session_AppendMessage(session, &i, 1);
                        Session_EndMessage(session, 0x30, 7);
                    }
                    insect->frames_left++;
                    if (insect->frames_left > 200) {
                        insect->action = TOWN_INSECT_ACTION_END;
                        TownInsect_Remove(process, insect, TOWN_INSECT_MODE_TOWN);
                    }
                } else {
                    Vec3 at = insect->position;
                    SoundSource_UpdateAt(&insect->source, &at);
                    if (insect->unk_254 == TOWN_INSECT_BYTE254_GONE) {
                        insect->action = TOWN_INSECT_ACTION_END;
                    }
                    if (insect->action == TOWN_INSECT_ACTION_END) {
                        TownInsect_Remove(process, insect, TOWN_INSECT_MODE_TOWN);
                    }
                }
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov003_0222efc0, TownInsect_UpdateLinked)

/* func_ov003_0222f320: the process's frame for the town and event insects. Outside a session,
 * or holding the scene, a frame counter places insects: every 20th frame first
 * TownInsect_ClearFailed; on the 60th a new town insect (and the count starts again); on the
 * 40th, outside a session, a town insect of kind 0x33 when due (TownInsect_SpecialKind; the
 * count starts again when placed); on the 20th, outside a session, the event insect of kind
 * 0x3b when due, shown by overlay 68 and main's flag cleared. Then the insects' view: in a
 * session around each player in the town (TownInsect_UpdatePlayerView), else around the camera
 * (TownInsect_UpdateView, the town's and the event's). */
void TownInsect_UpdateTown(TownInsectProcess *process)
{
    int linked = town_insect_in_session();
    if (linked == 0 || LinkGlobal_HoldsScene() != 0) {
        if (data_ov003_02260534 % 20 == 0) {
            TownInsect_ClearFailed();
        }
        data_ov003_02260534++;
        u8 frame = data_ov003_02260534;
        if (frame == 60) {
            TownInsect_PlaceNew(process, TOWN_INSECT_MODE_TOWN, 0, -1);
            data_ov003_02260534 = 0;
        } else if (frame == 40 && linked == 0) {
            u8 kind = 0;
            u8 place = 0xff;
            if (TownInsect_SpecialKind(&kind, &place, 1) != 0 &&
                TownInsect_PlaceNew(process, TOWN_INSECT_MODE_TOWN, (s8) kind, (s8) place) != 0) {
                data_ov003_02260534 = 0;
            }
        } else if (frame == 20 && linked == 0) {
            u8 kind = 0;
            u8 place = 0xff;
            if (TownInsect_SpecialKind(&kind, &place, 0) != 0 &&
                TownInsect_Place(process, (s8) kind, place, TOWN_INSECT_MODE_EVENT) != 0) {
                InsectPath_Show(&data_ov003_02260994[1]);
                data_ov003_02260538 = 0;
            }
        }
    }
    if (linked != 0) {
        for (u8 i = 0; i < 4; i++) {
            u8 scene;
            int x;
            int z;
            if (SessionPlayers_ScenePoint(&scene, &x, &z, -1, i) != 0 && scene == TOWN_INSECT_SCENE_TOWN) {
                TownInsect_UpdatePlayerView(process, TOWN_INSECT_MODE_TOWN, i, x, z);
            }
        }
    } else {
        TownInsect_UpdateView(process, TOWN_INSECT_MODE_TOWN);
        TownInsect_UpdateView(process, TOWN_INSECT_MODE_EVENT);
    }
}
CLEAN_AS(func_ov003_0222f320, TownInsect_UpdateTown)

/* func_ov003_0222f458: where town insect `id` (its low four bits) is, and its kind. */
int TownInsect_GetPosition(Vec3 *position, int id)
{
    TownInsect *insect = town_insect_at(data_ov003_022617bc, (u8) (id & TOWN_INSECT_ID_INDEX));
    /* a word at a time, as the original copies */
    position->x = insect->position.x;
    position->y = insect->position.y;
    position->z = insect->position.z;
    return insect->kind;
}
CLEAN_AS(func_ov003_0222f458, TownInsect_GetPosition)

/* func_ov003_0222f490: whether town insect `id` (its low four bits) is of a kind of places 13
 * and 14 (InsectTables_Place). */
int TownInsect_KindHighPlace(int id)
{
    switch (town_insect_at(data_ov003_022617bc, (u8) (id & TOWN_INSECT_ID_INDEX))->kind) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 31:
        case 33:
        case 34:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 52:
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov003_0222f490, TownInsect_KindHighPlace)

/* func_ov003_0222f524: town insect `id`'s kind; when it has one, *reached tells whether its byte
 * 0x254 has reached its byte 0x255. */
int TownInsect_Byte254Reached(u8 *reached, int id)
{
    TownInsect *insect = town_insect_at(data_ov003_022617bc, (u8) (id & TOWN_INSECT_ID_INDEX));
    int kind = insect->kind;
    if (kind >= 0) {
        *reached = insect->unk_254 >= insect->unk_255 ? 1 : 0;
    }
    return kind;
}
CLEAN_AS(func_ov003_0222f524, TownInsect_Byte254Reached)

/* Slot 43 of an actor's vtable (Actors_GetEByIndex's objects): whether it counts as near. */
typedef int (*TownInsectActorNearFn)(void *actor);
#define TOWN_INSECT_SLOT_COUNTS_NEAR 43

/* func_ov003_0222f570: the insect's byte 0x254 set to TOWN_INSECT_BYTE254_NEAR when something
 * comes within its reach: in a session (only while this system holds the scene) a player in the
 * town with flag 9 set (FieldActor_PlayerFlag9); else this console's player when its flag 9 is
 * set; else one of the eight actors of the table that its slot 43 says counts. */
void TownInsect_CheckNear(int unused, TownInsect *insect)
{
    (void) unused;
    if (town_insect_in_session()) {
        if (LinkGlobal_HoldsScene() == 0) {
            return;
        }
        for (u8 i = 0; i < 4; i++) {
            u8 scene;
            int x;
            int z;
            if (SessionPlayers_ScenePoint(&scene, &x, &z, -1, i) != 0 && scene == TOWN_INSECT_SCENE_TOWN &&
                FieldActor_PlayerFlag9(i) != 0) {
                Vec3 point = {x, 0, z};
                if (Vec_DistanceXZ(&insect->position, &point) < insect->reach) {
                    insect->unk_254 = TOWN_INSECT_BYTE254_NEAR;
                }
            }
        }
    } else if (FieldActor_PlayerFlag9(TOWN_INSECT_THIS_PLAYER) != 0) {
        Actor *player = SessionPlayers_ActorOf(TOWN_INSECT_THIS_PLAYER);
        if (player != NULL && Vec_DistanceXZ(&insect->position, &player->position) < insect->reach) {
            insect->unk_254 = TOWN_INSECT_BYTE254_NEAR;
        }
    } else {
        for (u8 i = 0; i < 8; i++) {
            Actor *actor = Actors_GetEByIndex(i);
            if (actor == NULL) {
                continue;
            }
            if (Vec_DistanceXZ(&insect->position, &actor->position) < insect->reach) {
                const u32 *vtable = (const u32 *) actor->vtable;
                if (((TownInsectActorNearFn) (uintptr_t) vtable[TOWN_INSECT_SLOT_COUNTS_NEAR])(actor) != 0) {
                    insect->unk_254 = TOWN_INSECT_BYTE254_NEAR;
                }
            }
        }
    }
}
CLEAN_AS(func_ov003_0222f570, TownInsect_CheckNear)

/* ---- The process: its frame, and each insect loaded, run and removed */

/* The process's vtable, and its base class's (Process). */
extern const u32 data_ov003_0223c0fc[];
extern const u32 data_020da13c[];
/* The current heap (heap.h). */
extern Heap *data_021fbe94;
/* An insect's file name by the tens of its kind ("/insect/01/bug0%d" for 0-9, "/insect/11/bug%d"
 * for 10-19, ... "/insect/51/bug%d" from 50), and the files: the model "%s.nsbmd", its
 * visibility animation "%s.nsbva" or joint animation "%s.nsbca", and kinds 0x3a and 0x3b's
 * texture animation "/insect/51/bug%d.nsbta". */
extern const char data_ov003_0223c48c[];
extern const char data_ov003_0223c4a0[];
extern const char data_ov003_0223c4b4[];
extern const char data_ov003_0223c4c8[];
extern const char data_ov003_0223c4dc[];
extern const char data_ov003_0223c4f0[];
extern const char data_ov003_0223c504[];
extern const char data_ov003_0223c510[];
extern const char data_ov003_0223c51c[];
extern const char data_ov003_0223c528[];

/* `size` bytes cleared. */
extern void *func_02137550(void *dst, u32 size);
/* NitroSystem's G3D: an animation file's set of visibility, joint or texture SRT animations,
 * and the animation of a set by its number. */
extern void *NNS_G3dGetVisAnmSet(u8 *file);
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern void *NNS_G3dGetTexSRTAnmSet(u8 *file);
extern u8 *func_02107cf0(void *set, u32 index);
extern u8 *func_02107b44(void *set, u32 index);
extern u8 *func_02107bbc(void *set, u32 index);
/* The hooks the three model pools are given (scene_heaps.h): the game's own functions. */
extern int func_0205c9c8(int size, int parent);
extern void func_0205c9ac(void);
extern int func_0205ca30(int size, int parent);
extern void func_0205ca14(void);
extern int func_0205c9fc(int size, int parent);
extern void func_0205c9e0(void);

/* Whether a kind animates by visibility ("%s.nsbva", stepped by the model's own frames) rather
 * than by its joints ("%s.nsbca", stepped each frame here): byte 0 of its entry. */
static int town_insect_kind_visibility(int kind)
{
    return (u8) town_insect_kind_info(kind)->unk_0 != 0;
}

static AnimatedModel *town_insect_animated(TownInsect *insect)
{
    return (AnimatedModel *) &insect->model;
}

/* func_ov003_0222f67c (vtable slot 6): the process's frame: the town insects while linked, the
 * event insects outside a session, the held insects, then the town's frame. */
int TownInsect_ProcessUpdate(TownInsectProcess *process)
{
    TownInsect_UpdateLinked(process);
    if (town_insect_in_session() == 0) {
        TownInsect_UpdateEvent(process);
    }
    TownInsect_UpdateHeld(process);
    TownInsect_UpdateTown(process);
    return 1;
}
CLEAN_AS(func_ov003_0222f67c, TownInsect_ProcessUpdate)

/* func_ov003_0222f6b0: an active insect's frame, `index` its index in the table of `mode`
 * (TOWN_INSECT_MODE_*). It counts as in view when within the camera's box, or in a session when
 * a player's box holds it. Out of view its timers run down (TownInsect_CountDown). A town insect
 * outside a session (or holding the scene) stays 1200 frames while in view; out of view that
 * many frames run down and then it leaves.
 *
 * An insect with an update function, in view or of the event or held table, then runs: its
 * counter steps; unless hidden, without a kind or ending, it checks what comes near, runs its
 * kind's update and, when it can be caught, moves by the collisions from where it was (with the
 * radius of its kind; a held insect over ground above 4.0 with flags 0xa, else 0xb); kind 0x33's
 * first record has its word 0x21c set; and it adds its catch sphere (the reach of its kind,
 * radius 0xd48) named by its index with bit 3 + mode, kind 0x35's 1.5 lower on frames 30-39 of
 * its animation. A kind animated by its joints steps its frames (kinds 0x3a and 0x3b also their
 * texture animation); a hidden or kindless insect steps them only for kinds 0x14 and 0x37.
 * Last, an ending insect is removed; any other has its matrix built (as held when it is a
 * hidden held insect) and its sound placed. */
void TownInsect_Run(TownInsectProcess *process, TownInsect *insect, int index, int mode)
{
    int in_view = insect->in_view;
    int linked = town_insect_in_session();
    if (linked != 0 && insect->players_near != 0) {
        in_view = 1;
    }
    if (in_view == 0) {
        TownInsect_CountDown((int) (uintptr_t) process, insect);
    }
    if (mode == TOWN_INSECT_MODE_TOWN && (linked == 0 || LinkGlobal_HoldsScene() != 0)) {
        if (in_view != 0) {
            insect->unk_234 = 1200;
        } else if (insect->unk_234 > 0) {
            insect->unk_234--;
            if (insect->unk_234 == 0) {
                insect->state = TOWN_INSECT_STATE_LEAVING;
                return;
            }
        }
    }
    if (insect->unk_170 == 0) {
        return;
    }
    if (in_view == 0 && mode != TOWN_INSECT_MODE_EVENT && mode != TOWN_INSECT_MODE_HELD) {
        return;
    }
    s8 kind = insect->kind;
    u8 action = insect->action;
    TownInsect_StepCounter(insect);
    if (action == TOWN_INSECT_ACTION_HIDDEN || kind < 0) {
        if (kind == 0x14 || kind == 0x37) {
            AnimatedModel_StepFrames(town_insect_animated(insect));
        }
    } else {
        if (action != TOWN_INSECT_ACTION_END) {
            Vec3 previous = insect->position;
            TownInsect_CheckNear((int) (uintptr_t) process, insect);
            ((TownInsectKindFn) (uintptr_t) (u32) insect->unk_170)(insect);
            if (TownInsect_CanBeCaught((int) (uintptr_t) process, insect) != 0) {
                int flags = 0xb;
                if (mode == TOWN_INSECT_MODE_HELD) {
                    CollisionGround ground;
                    CollisionGround_Init(&ground, &insect->position, 0, 0);
                    int high = CollisionGround_GetHeight(&ground, 0) > 0x4000;
                    CollisionGround_Destroy(&ground);
                    if (high) {
                        flags = 0xa;
                    }
                }
                CollisionQuery_Move(&insect->contacts, &insect->position, &previous, insect->angle_y,
                                    town_insect_kind_info(kind)->size, NULL, flags);
            }
            if (insect->kind == 0x33 && index == 0) {
                insect->unk_21c = 1;
            }
            u32 id = (u32) index | town_insect_shl(1, mode + 3);
            Vec3 centre = insect->position;
            if (insect->kind == 0x35) {
                u32 frame = ((u32) insect->model.frames.frame << 4) >> 16;
                if (frame >= 30 && frame < 40) {
                    centre.y -= 0x1800;
                }
            }
            CatchSphere_Add(&insect->sphere, &centre, town_insect_kind_info(kind)->unk_4, 0xd48, (u8) id);
        }
        if (town_insect_kind_visibility(kind) == 0) {
            AnimatedModel_StepFrames(town_insect_animated(insect));
            if (kind == TOWN_INSECT_KIND_3A || kind == TOWN_INSECT_KIND_3B) {
                FrameCtrl_Step(&insect->anim.ctrl);
                insect->anim.anim->frame = insect->anim.ctrl.frame;
            }
        }
    }
    if (action == TOWN_INSECT_ACTION_END) {
        TownInsect_Remove(process, insect, mode);
        return;
    }
    TownInsect_SetMatrix((int) (uintptr_t) process, insect,
                         mode == TOWN_INSECT_MODE_HELD && action == TOWN_INSECT_ACTION_HIDDEN);
    Vec3 position = insect->position;
    SoundSource_UpdateAt(&insect->source, &position);
}
CLEAN_AS(func_ov003_0222f6b0, TownInsect_Run)

/* func_ov003_0222f958: an insect out of view running down to leaving (func_ov003_02230f60):
 * kind 0x1e in actions 4, 5 and 0x11 while its timer is above 5, kind 0x31 in actions 4, 5, 7
 * and 0x11 while it is above 0, kinds 0x36 and 0x37 with the word 0x236 at 1-300 while it is
 * above 31. Nothing without an update function. */
void TownInsect_CountDown(int unused, TownInsect *insect)
{
    (void) unused;
    if (insect->unk_170 == 0) {
        return;
    }
    u8 action = insect->action;
    switch (insect->kind) {
        case 0x1e:
            if (action == 4 || action == 5 || action == TOWN_INSECT_ACTION_11) {
                if (insect->timer > 5) {
                    insect->timer--;
                } else {
                    TownInsectMove_Leave(insect);
                }
            }
            break;
        case 0x31:
            if (action == 4 || action == 5 || action == 7 || action == TOWN_INSECT_ACTION_11) {
                if (insect->timer > 0) {
                    insect->timer--;
                } else {
                    TownInsectMove_Leave(insect);
                }
            }
            break;
        case 0x36:
        case 0x37:
            if (insect->unk_236 > 0 && insect->unk_236 <= 300) {
                if (insect->unk_236 > 0x1f) {
                    insect->unk_236--;
                } else {
                    TownInsectMove_Leave(insect);
                }
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov003_0222f958, TownInsect_CountDown)

/* func_ov003_0222fa20: an insect of TOWN_INSECT_STATE_2 loaded into the process's model pool
 * `pool` (0 the town's, 1 the event's, else the held insects'), and started. Its kind (0-0x3b)
 * names its files (see above); it stops at any file missing or not loaded. The model goes to its
 * model object; the animation file is read into the pool entry's heap, but for the event insects
 * into the current heap, kept in the process's block 0 (kind 0x3a) or 1. Its first animation
 * starts at speed 1.0 (0 for kinds 9 and 0x35; kind 9 then holds frame 9 of 9), and kinds 0x3a
 * and 0x3b also need their texture animation. Once loaded, its sound is set up, its kind's start
 * function runs, the kind's update function is kept, and it becomes active with its matrix
 * built; a held insect keeps the scale it had.
 * QUIRK: the texture animation's file is not checked; the check made is of the first
 * animation's file, which is never NULL there. */
void TownInsect_Load(TownInsectProcess *process, TownInsect *insect, int pool)
{
    char name[0x11];
    char path[0x17];
    func_02137550(name, sizeof name);
    func_02137550(path, sizeof path);
    int kind = insect->kind;
    if (kind < 0 || kind >= TOWN_INSECT_KINDS) {
        return;
    }
    const char *format;
    if (kind < 10) {
        format = data_ov003_0223c48c;
    } else if (kind < 20) {
        format = data_ov003_0223c4a0;
    } else if (kind < 30) {
        format = data_ov003_0223c4b4;
    } else if (kind < 40) {
        format = data_ov003_0223c4c8;
    } else if (kind < 50) {
        format = data_ov003_0223c4dc;
    } else {
        format = data_ov003_0223c4f0;
    }
    CLib_SPrintf(name, format, kind);
    CLib_SPrintf(path, data_ov003_0223c504, name);
    if (RomFile_Exists(path) == 0) {
        return;
    }
    int which = pool == 0 ? 0 : pool == 1 ? 1 : 2;
    ModelPoolEntry *entry = ModelPool_Take(&process->pools[which], &insect->slot);
    if (ModelPoolFiles_Load(&insect->files, entry, path) == 0) {
        return;
    }
    AnimatedModel *model = town_insect_animated(insect);
    ModelObject_SetModel(&model->object, (u8 *) (uintptr_t) ModelPoolFiles_Model(&insect->files), NULL);
    int visibility = town_insect_kind_visibility(kind);
    CLib_SPrintf(path, visibility ? data_ov003_0223c510 : data_ov003_0223c51c, name);
    if (RomFile_Exists(path) == 0) {
        return;
    }
    Heap *heap = (Heap *) (uintptr_t) ModelPoolEntry_Heap(entry);
    u8 *file;
    if (pool == 1) {
        int block = kind == TOWN_INSECT_KIND_3A ? 0 : 1;
        process->blocks[block] = RomFile_Load(path, data_021fbe94, 4, NULL);
        file = process->blocks[block];
    } else {
        file = RomFile_Load(path, heap, 4, NULL);
    }
    if (file == NULL) {
        return;
    }
    u8 *anim;
    if (visibility) {
        anim = func_02107cf0(NNS_G3dGetVisAnmSet(file), 0);
    } else {
        anim = func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
    }
    if (AnimatedModel_LoadAnim(model, heap) == 0) {
        return;
    }
    int loaded = 1;
    fx32 speed = (kind == 0x35 || kind == 9) ? 0 : 0x1000;
    AnimatedModel_Start(model, anim, 0, speed, 0, 0);
    AnimatedModel_Attach(model);
    if (kind == 9) {
        FrameCtrl_Init(&insect->model.frames, 9, FRAME_CTRL_ONCE, 0, 9);
    }
    if (kind == TOWN_INSECT_KIND_3A || kind == TOWN_INSECT_KIND_3B) {
        CLib_SPrintf(path, data_ov003_0223c528, kind);
        loaded = 0;
        if (RomFile_Exists(path) != 0) {
            u8 *texture_file = RomFile_Load(path, heap, 4, NULL);
            if (file != NULL) {
                u8 *texture_anim = func_02107bbc(NNS_G3dGetTexSRTAnmSet(texture_file), 0);
                if (ModelAnim_AllocMaterialAnim(&insect->anim, model->object.model, heap) != 0) {
                    ModelAnim_Start(&insect->anim, texture_anim, 0, 0x1000, 0);
                    ModelAnim_Attach(&insect->anim, ModelObject_RenderObject(&model->object));
                    loaded = 1;
                }
            }
        }
    }
    if (loaded == 0) {
        return;
    }
    Vec3 scale = insect->scale;
    SoundSource_Init(&insect->source);
    ((TownInsectKindFn) (uintptr_t) data_ov003_0223c2ac[kind].start)(insect);
    insect->unk_170 = (int) data_ov003_0223c2ac[kind].update;
    insect->state = TOWN_INSECT_STATE_ACTIVE;
    insect->unk_24a = 0;
    TownInsect_SetMatrix((int) (uintptr_t) process, insect, 0);
    if (pool == 2) {
        /* a word at a time, as the original copies */
        insect->scale.x = scale.x;
        insect->scale.y = scale.y;
        insect->scale.z = scale.z;
    }
}
CLEAN_AS(func_ov003_0222fa20, TownInsect_Load)

/* func_ov003_0222fd60 (vtable slot 0): the process set up: its three model pools (eight town
 * insects, two event insects, four held ones, each with its heap of scene_heaps.h), the two
 * event insects of kinds 0x3a and 0x3b outside a session, and the town's tile masks. */
int TownInsect_ProcessSetUp(TownInsectProcess *process)
{
    ModelPool_Create(&process->pools[0], TOWN_INSECT_TOWN_COUNT, 0x400, 0x40, 0x9c4, func_0205c9c8, func_0205c9ac, NULL);
    ModelPool_Create(&process->pools[1], TOWN_INSECT_EVENT_COUNT, 0x400, 0x40, 0x6e8, func_0205ca30, func_0205ca14, NULL);
    ModelPool_Create(&process->pools[2], TOWN_INSECT_HELD_COUNT, 0x400, 0x40, 0x9c4, func_0205c9fc, func_0205c9e0, NULL);
    if (town_insect_in_session() == 0) {
        TownInsect_StartEvent(process, TOWN_INSECT_KIND_3A, 0);
        TownInsect_StartEvent(process, TOWN_INSECT_KIND_3B, 1);
    }
    TownTileMask_Build();
    return 1;
}
CLEAN_AS(func_ov003_0222fd60, TownInsect_ProcessSetUp)

/* func_ov003_0222fe18: an insect removed from the table of `mode` (TOWN_INSECT_MODE_*, any
 * other the held insects'): kind 0x33's end told to main (Block02042200_Update), its animation
 * detached, its sound released, its files released and its pool entry given back; it is left
 * with no kind or state, shown, at (1, 1, 1). */
void TownInsect_Remove(TownInsectProcess *process, TownInsect *insect, int mode)
{
    if (insect->kind == 0x33) {
        Block02042200_Update();
    }
    if (insect->kind >= 0) {
        AnimatedModel_DetachAnim(town_insect_animated(insect));
    }
    insect->state = TOWN_INSECT_STATE_NONE;
    insect->unk_21c = 0;
    SoundSource_Release(&insect->source);
    insect->position.x = 1;
    insect->position.y = 1;
    insect->position.z = 1;
    insect->target.x = 1;
    insect->target.y = 1;
    insect->target.z = 1;
    insect->used = 0;
    insect->in_view = 0;
    insect->players_near = 0;
    insect->kind = TOWN_INSECT_NO_KIND;
    insect->angle_y = 0;
    insect->frames_left = 0;
    insect->action = TOWN_INSECT_ACTION_SHOWN;
    ModelPoolFiles_Release(&insect->files);
    insect->anim.anim = NULL;
    insect->anim.model = NULL;
    insect->unk_254 = 0;
    insect->unk_24a = 0;
    insect->unk_236 = 0;
    int which = mode == TOWN_INSECT_MODE_TOWN ? 0 : mode == TOWN_INSECT_MODE_EVENT ? 1 : 2;
    ModelPool_Release(&process->pools[which], &insect->slot);
    insect->unk_170 = 0;
}
CLEAN_AS(func_ov003_0222fe18, TownInsect_Remove)

/* func_ov003_0222ff2c: a free town insect taken up for loading (TOWN_INSECT_STATE_2, an entry of
 * the town's pool, its files reset, out of view); whether it was free. */
int TownInsect_StartTown(TownInsectProcess *process, TownInsect *insect)
{
    if (insect->state != TOWN_INSECT_STATE_NONE) {
        return 0;
    }
    insect->state = TOWN_INSECT_STATE_2;
    ModelPool_Take(&process->pools[0], &insect->slot);
    ModelPoolFiles_Reset(&insect->files);
    insect->in_view = 0;
    return 1;
}
CLEAN_AS(func_ov003_0222ff2c, TownInsect_StartTown)

/* func_ov003_0222ff74: event insect `index` taken up for loading as `kind` when free (an entry
 * of the event's pool, its files reset, in view, no texture animation); whether it was free. */
int TownInsect_StartEvent(TownInsectProcess *process, int kind, int index)
{
    TownInsect *insect = town_insect_at(data_ov003_02260994, index);
    if (insect->state != TOWN_INSECT_STATE_NONE) {
        return 0;
    }
    ModelPool_Take(&process->pools[1], &insect->slot);
    ModelPoolFiles_Reset(&insect->files);
    insect->in_view = 1;
    insect->anim.anim = NULL;
    insect->anim.model = NULL;
    insect->kind = (s8) kind;
    insect->state = TOWN_INSECT_STATE_2;
    return 1;
}
CLEAN_AS(func_ov003_0222ff74, TownInsect_StartEvent)

/* func_ov003_0222ffdc: a held insect taken up for loading (an entry of the held insects' pool,
 * its files reset, in view). One in use is removed first, keeping its kind, action, position,
 * point and angle about y. Always 1. */
int TownInsect_StartHeld(TownInsectProcess *process, TownInsect *insect)
{
    if (insect->state != TOWN_INSECT_STATE_NONE) {
        s8 kind = insect->kind;
        u8 action = insect->action;
        Vec3 position = insect->position;
        Vec3 target = insect->target;
        s16 angle_y = insect->angle_y;
        TownInsect_Remove(process, insect, TOWN_INSECT_MODE_HELD);
        insect->kind = kind;
        insect->action = action;
        insect->position.x = position.x;
        insect->position.y = position.y;
        insect->position.z = position.z;
        insect->angle_y = angle_y;
        insect->target.x = target.x;
        insect->target.y = target.y;
        insect->target.z = target.z;
    }
    insect->state = TOWN_INSECT_STATE_2;
    ModelPool_Take(&process->pools[2], &insect->slot);
    ModelPoolFiles_Reset(&insect->files);
    insect->in_view = 1;
    return 1;
}
CLEAN_AS(func_ov003_0222ffdc, TownInsect_StartHeld)

/* The process's members destroyed, last to first, then the process. */
static void town_insect_process_destroy(TownInsectProcess *process)
{
    Process *base = (Process *) (void *) process;
    base->vtable = data_ov003_0223c0fc;
    ModelPool_Destruct(&process->pools[2]);
    ModelPool_Destruct(&process->pools[1]);
    ModelPool_Destruct(&process->pools[0]);
    TownInsectTables_DestroyProcessPart(process);
    base->vtable = data_020da13c;
    Process_Destruct(base);
}

/* func_ov003_02230098 (vtable slot 17): the process destroyed and freed; returns it. */
TownInsectProcess *TownInsect_ProcessDelete(TownInsectProcess *process)
{
    town_insect_process_destroy(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_ov003_02230098, TownInsect_ProcessDelete)

/* func_ov003_022300e0 (vtable slot 16): the process destroyed; returns it. */
TownInsectProcess *TownInsect_ProcessDestruct(TownInsectProcess *process)
{
    town_insect_process_destroy(process);
    return process;
}
CLEAN_AS(func_ov003_022300e0, TownInsect_ProcessDestruct)

/* func_ov003_02230120: the process's constructor: the process, its three model pools, and the
 * flag of the point ahead of this console's player cleared; returns it. */
TownInsectProcess *TownInsect_ProcessConstruct(TownInsectProcess *process)
{
    Process *base = (Process *) (void *) process;
    Process_Construct(base);
    base->vtable = data_020da13c;
    TownInsectTables_ConstructProcessPart(process);
    base->vtable = data_ov003_0223c0fc;
    ModelPool_Init(&process->pools[0]);
    ModelPool_Init(&process->pools[1]);
    ModelPool_Init(&process->pools[2]);
    data_ov003_02260540 = 0;
    return process;
}
CLEAN_AS(func_ov003_02230120, TownInsect_ProcessConstruct)

/* func_ov003_02230168: the process made (0xa0 bytes, cleared) when there is room. */
void TownInsect_ProcessCreate(void)
{
    TownInsectProcess *process = Heap_AllocAuxZeroed(0xa0);
    if (process != NULL) {
        TownInsect_ProcessConstruct(process);
    }
}
CLEAN_AS(func_ov003_02230168, TownInsect_ProcessCreate)
