/* Overlay 3's drawing of the town's map codes and items as models (town_item_models.h). */
#include "town_item_models.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "growth_model.h"
#include "itcm/field_units.h"
#include "main/acre_tile.h"
#include "main/actor_table.h" /* Position, Position_Tile */
#include "main/camera_control.h"
#include "main/globe.h"
#include "main/item_traits.h"
#include "main/map_item.h"
#include "main/scene_lights.h"
#include "main/shadow.h"
#include "main/tile_changes.h"
#include "main/town_day.h"
#include "main/town_family.h"

static_assert(offsetof(ModelObject, unk_64) == 0x64, "unk_64");
static_assert(sizeof(Mtx43) == 0x30, "a matrix");

/* The process (NULL while there is none), its heaps, and the tile events' table. */
extern TileEventProcess *data_ov003_0223cf70;
extern Heap *data_ov003_0223cf74;
extern Heap *data_ov003_0223cf78;
extern TileEventEntry data_ov003_0223cfe4[];
/* The town's map, the field camera and the point the field is drawn around. */
extern AcreMap *data_021c80bc;
extern void *data_021c67a4;
extern const Vec3 data_021c67d0;
/* The matrix models are drawn in (built here in place). */
extern Mtx43 data_021fbe48;
/* The fruit item of the eight-code lines, by line (MapItem_EightLine). */
extern const u16 data_ov003_0223667c[];
/* The offsets from a tile's centre of the three fruit of an eight-code line or code 0x69, and of
 * the two of a grown code of 0xc8-0xcf. */
extern const Vec3 data_ov003_02236b64[3];
extern const Vec3 data_ov003_02236b4c[2];

/* NitroSystem: two settings of all a model's materials: a value 0-31 (the alpha), and the
 * emission colour. */
extern void func_0210744c(u8 *model, int value);
extern void func_02107524(u8 *model, u16 colour);

/* The process's words outside the parts tile_event.h names. */
#define TOWN_ITEM_MODELS_ITEM_HOLDERS 0x0050 /* the holders of items, by ItemTraits_Unk07 */
#define TOWN_ITEM_MODELS_CODE_1D 0x3060      /* the holders of codes 0x1d and 0x1e */
#define TOWN_ITEM_MODELS_CODE_E3 0x46f4      /* five holders for the codes 0xe3-0xfb */
#define TOWN_ITEM_MODELS_SHORT 0x4978        /* twelve holders for the short lines */
#define TOWN_ITEM_MODELS_CLOCK 0x6a6c        /* frames, 0-59 */

/* Holders per line in the families' block at 0x1590. */
#define TOWN_ITEM_MODELS_PER_LINE 10
/* The alpha of an item drawn whole, and 1.0. */
#define TOWN_ITEM_MODELS_OPAQUE 0x1f
#define TOWN_ITEM_MODELS_ONE 0x1000
/* The tiles drawn at most a frame. */
#define TOWN_ITEM_MODELS_MAX_DRAWN 0xfc
/* A tile, in world units. */
#define TOWN_ITEM_MODELS_TILE 0x2000

/* The fruit items. */
#define TOWN_ITEM_MODELS_FRUIT_57 0x14b8
#define TOWN_ITEM_MODELS_FRUIT_69 0x1542
#define TOWN_ITEM_MODELS_FRUIT_C8 0x1548

/* The holder `index` holders on from `first` (the index may run on into the arrays after, as
 * the ROM computes it). */
static ModelObject *town_item_model(ModelObject *first, int index)
{
    return (ModelObject *) ((uintptr_t) first + (uintptr_t) (intptr_t) index * sizeof(ModelObject));
}

/* Pointer `index` of the holders' pointers at `offset` in the process. */
static ModelObject *town_item_pointer(TileEventProcess *process, u32 offset, int index)
{
    ModelObject *const *pointers = (ModelObject *const *) (const void *) ((const u8 *) process + offset);
    return pointers[index];
}

static int *town_item_clock(TileEventProcess *process)
{
    return (int *) (void *) ((u8 *) process + TOWN_ITEM_MODELS_CLOCK);
}

static GrowthModels *town_item_growth_models(TileEventProcess *process)
{
    return (GrowthModels *) (void *) process->member_4b20;
}

/* data_021fbe48 made the translation to `point` bent over the globe, turned by the bend about
 * X. */
static void town_item_place(const Vec3 *point)
{
    Vec3 bent;
    int tilt = Globe_BendFar(&bent, point);
    Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
    Mtx43_RotateX(&data_021fbe48, tilt);
}

/* func_ov003_0222462c: on the process (none: nothing), code or item `code` drawn at `position`
 * with `scale` turned by the three angles (TownItemModels_DrawCode). */
void TownItemModels_DrawCodeAt(int code, const Vec3 *position, const Vec3 *scale, int angle_x, short angle_y, short angle_z)
{
    TileEventProcess *process = data_ov003_0223cf70;
    if (process == NULL) {
        return;
    }
    Vec3 at = *position;
    Vec3 size = *scale;
    TownItemModels_DrawCode(process, (u16) code, &at, &size, (short) angle_x, angle_y, angle_z);
}
CLEAN_AS(func_ov003_0222462c, TownItemModels_DrawCodeAt)

/* func_ov003_02224678: on the process (none: nothing), `item` drawn whole at `position`
 * (TownItemModels_DrawItem). */
void TownItemModels_DrawItemAt(int item, const Vec3 *position, const Vec3 *scale, int angle_x, short angle_y, short angle_z)
{
    TileEventProcess *process = data_ov003_0223cf70;
    if (process == NULL) {
        return;
    }
    Vec3 at = *position;
    Vec3 size = *scale;
    TownItemModels_DrawItem(process, item, &at, TOWN_ITEM_MODELS_OPAQUE, &size, (short) angle_x, angle_y, angle_z);
}
CLEAN_AS(func_ov003_02224678, TownItemModels_DrawItemAt)

/* func_ov003_022246c8: on the process (none: nothing), the item holder `holder` drawn whole at
 * `position` (TownItemModels_DrawHolder). */
void TownItemModels_DrawHolderAt(int holder, const Vec3 *position, const Vec3 *scale, int angle_x, short angle_y,
                                 short angle_z)
{
    TileEventProcess *process = data_ov003_0223cf70;
    if (process == NULL) {
        return;
    }
    Vec3 at = *position;
    Vec3 size = *scale;
    TownItemModels_DrawHolder(process, holder, &at, TOWN_ITEM_MODELS_OPAQUE, &size, (short) angle_x, angle_y, angle_z);
}
CLEAN_AS(func_ov003_022246c8, TownItemModels_DrawHolderAt)

/* func_ov003_022248e4 (vtable slot 3 of 0x0223bc7c, the DELETE phase's work): the four model
 * sets released, the growth models released, the tile events released, every tile change
 * finished, both heaps destroyed; the process is gone (data_ov003_0223cf70 NULL). Done (1). */
int TownItemModels_DeleteProcess(TileEventProcess *process)
{
    for (int i = 0; i < 4; i++) {
        ModelSet_Release(&process->sets[i]);
    }
    GrowthModels_ReleaseAll(town_item_growth_models(process));
    TileEvent_ReleaseAll(data_ov003_0223cfe4);
    TileChanges_FinishAll();
    if (data_ov003_0223cf74 != NULL) {
        Heap_Destroy(data_ov003_0223cf74);
        data_ov003_0223cf74 = NULL;
    }
    if (data_ov003_0223cf78 != NULL) {
        Heap_Destroy(data_ov003_0223cf78);
        data_ov003_0223cf78 = NULL;
    }
    data_ov003_0223cf70 = NULL;
    return 1;
}
CLEAN_AS(func_ov003_022248e4, TownItemModels_DeleteProcess)

/* func_ov003_02224970 (vtable slot 9, the DRAW phase's work): with the town's map and the field
 * camera, the clock counts a frame (0-59), the tiles around are drawn
 * (TownItemModels_DrawAround), then the tile events and the growth models. Done (1). */
int TownItemModels_DrawProcess(TileEventProcess *process)
{
    AcreMap *map = data_021c80bc;
    void *camera = data_021c67a4;
    if (map != NULL && camera != NULL) {
        int *clock = town_item_clock(process);
        *clock = (*clock + 1) % 60;
        TownItemModels_DrawAround(process, map);
        TileEvent_DrawAll(data_ov003_0223cfe4);
        GrowthModels_DrawAll(town_item_growth_models(process));
    }
    return 1;
}
CLEAN_AS(func_ov003_02224970, TownItemModels_DrawProcess)

/* Codes the growth models show (growth_model.h): the growth lines and 0x66-0x6d. */
static int town_item_growth_code(u16 code)
{
    return (code >= 0x26 && code <= 0x2a) || (code >= 0x5d && code <= 0x61) || (code >= 0x2f && code <= 0x5b) ||
           (code >= 0x66 && code <= 0x6d) || (code >= 0xc8 && code <= 0xcf);
}

/* Codes of 0xe3-0xfb. */
static int town_item_code_e3(u16 code)
{
    return code >= 0xe3 && code <= 0xfb;
}

/* The codes of the four short lines (main/map_item.h). */
static int town_item_short_line(u16 code)
{
    return (code >= 0x2b && code <= 0x2e) || (code >= 0xff && code <= 0x102) || (code >= 0x62 && code <= 0x65) ||
           (code >= 0xd0 && code <= 0xd3);
}

/* Codes TownItemModels_DrawCode1a draws. */
static int town_item_code_1a(u16 code)
{
    return code == 0x1a || code == 0x1b || code == 0x1d || code == 0x1e || code == 0x88 || code == 0x89;
}

/* Whether a code of kind 0 at `ahead` (its row's z less the field point's) is near enough to be
 * drawn: the growth codes and 0xe3-0xfb from 0x1c200 behind to 0x8200 in front, the others
 * from 0x14a00 behind to 0x6400 in front. */
static int town_item_in_reach(u16 code, int ahead)
{
    if ((town_item_growth_code(code) || town_item_code_e3(code)) && ahead > -0x1c200 && ahead < 0x8200) {
        return 1;
    }
    return ahead > -0x14a00 && ahead < 0x6400;
}

/* A code of kind 0 at tile (x, z) drawn by the drawer of its set. */
static void town_item_draw_map_code(TileEventProcess *process, AcreMap *map, const u16 *tile, int x, int z, const Vec3 *point,
                                    Mtx43 matrix)
{
    u16 code = *tile;
    if (town_item_growth_code(code)) {
        Vec3 at = *point;
        TownItemModels_DrawGrowthWithShadow(process, tile, x, z, &at, matrix);
    } else if (code >= 0x1f && code <= 0x24) {
        TownItemModels_DrawCode1f(process, tile, matrix);
    } else if (code <= 0x19 || code == 0x1c) {
        TownItemModels_DrawFamily(process, tile, matrix);
    } else if ((code >= 0x6e && code <= 0x87) || (code >= 0x8a && code <= 0xa3) || code == 0xa5) {
        TownItemModels_DrawFamilyB(process, tile, matrix);
    } else if (town_item_code_e3(code)) {
        Vec3 at = *point;
        TownItemModels_DrawCodeE3WithShadow(process, tile, &at, matrix);
    } else if (code == 0xa6 || code == 0xfe) {
        TownItemModels_DrawCodeA6(process, tile, matrix);
    } else if (code == 0xfc || code == 0xfd) {
        TownItemModels_DrawCodeFc(process, tile, matrix);
    } else if (code == 0x25 || code == 0x5c || code == 0xc7) {
        TownItemModels_DrawCode25(process, tile, x, z, matrix);
    } else if (town_item_short_line(code)) {
        TownItemModels_DrawShortLine(process, tile, matrix);
    } else if (town_item_code_1a(code) || code == 0xa4) {
        TownItemModels_DrawCode1a(process, tile, matrix);
    } else if (FieldUnits_IsBitSet((UnitBitsGrid *) (void *) map, x, z)) {
        TownItemModels_DrawCodeA6(process, tile, matrix);
    } else if (code >= 0xa7 && code <= 0xc6) {
        TownItemModels_DrawCodeA7(process, tile, matrix);
    } else if (code >= 0xd4 && code <= 0xe2) {
        TownItemModels_DrawCodeD4(process, tile, matrix);
    }
}

/* func_ov003_022249cc: with the field camera, the tiles around the field's point drawn: rows
 * of 19 tiles from 9 tiles to its larger x to 9 to its smaller, from 4 rows to its larger z to
 * 14 to its smaller, each row in the matrix of its first tile's centre bent over the globe (the
 * translation's x moved a tile per tile). A code of a growth model that is past stage 0 and
 * whose tile is past the camera's goal is not drawn; other codes of kind 0 when near enough
 * (town_item_in_reach) by the drawer of their set; codes of kinds 1, 3 and 4 by their item's
 * holder, or as code 0xa6 where the map's unit bit is set. Each tile of kinds 0, 1, 3 and 4
 * near enough counts (drawn or not): at 252 the drawing stops. */
void TownItemModels_DrawAround(TileEventProcess *process, AcreMap *map)
{
    if (data_021c67a4 == NULL) {
        return;
    }
    Vec3 field_point = data_021c67d0;
    Vec3 centre;
    AcreTile_SnapToTileCentre(&centre, &field_point);
    int centre_x;
    int centre_z;
    Position_Tile(&centre_x, &centre_z, (const Position *) (const void *) &centre);
    Vec3 row = {centre.x + 0x12000, 0, centre.z + 0x8000};
    int counted = 0;
    for (int dz = 4; dz >= -14; row.z -= TOWN_ITEM_MODELS_TILE, dz--) {
        Vec3 point;
        AcreTile_SnapToTileCentre(&point, &row);
        town_item_place(&point);
        Mtx43 matrix = data_021fbe48;
        int ahead = point.z - centre.z;
        for (int dx = 9; dx >= -9; matrix.m[3][0] -= TOWN_ITEM_MODELS_TILE, point.x -= TOWN_ITEM_MODELS_TILE, dx--) {
            u16 *tile = AcreTile_ItemAt(map, &point, 0);
            if (tile == NULL) {
                continue;
            }
            if (town_item_growth_code(*tile) && !MapItem_IsStage0(tile) &&
                CameraControl_IsPastGoalZ(&point, 0x2000, 0x2000) != 0) {
                continue;
            }
            int x = centre_x + dx;
            int z = centre_z + dz;
            u16 code = *tile;
            switch ((code & 0xf000) >> 12) {
                case 0:
                    if (!town_item_in_reach(code, ahead)) {
                        continue;
                    }
                    town_item_draw_map_code(process, map, tile, x, z, &point, matrix);
                    break;
                case 1:
                case 3:
                case 4:
                    if (FieldUnits_IsBitSet((UnitBitsGrid *) (void *) map, x, z)) {
                        TownItemModels_DrawCodeA6(process, tile, matrix);
                    } else {
                        ModelObject *holder =
                            town_item_pointer(process, TOWN_ITEM_MODELS_ITEM_HOLDERS, ItemTraits_Unk07(tile));
                        TownItemModels_Draw(process, holder, matrix);
                    }
                    break;
                default:
                    continue;
            }
            counted++;
            if (counted >= TOWN_ITEM_MODELS_MAX_DRAWN) {
                return;
            }
        }
    }
}
CLEAN_AS(func_ov003_022249cc, TownItemModels_DrawAround)

/* func_ov003_022251a4: a holder (none: nothing) drawn in `matrix` (its shapes only), then lit by
 * the scene's emission colour. */
void TownItemModels_Draw(TileEventProcess *process, ModelObject *model, Mtx43 matrix)
{
    (void) process;
    if (model == NULL) {
        return;
    }
    memcpy(model->unk_64, &matrix, sizeof(Mtx43));
    ModelObject_DrawShapes(model, NULL);
    func_02107524(model->model, (u16) SceneLights_EmissionColour());
}
CLEAN_AS(func_ov003_022251a4, TownItemModels_Draw)

/* func_ov003_022251e8: codes 0xa7-0xc6, a holder each from 0x3068. */
ModelObject *TownItemModels_DrawCodeA7(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    ModelObject *model = town_item_model(process->models_3068, *code - 0xa7);
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_022251e8, TownItemModels_DrawCodeA7)

/* func_ov003_02225240: codes 0xd4-0xe2: the second holder at 0x49a8 for 0xe2, else the first. */
ModelObject *TownItemModels_DrawCodeD4(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    ModelObject *model = &process->models_49a8[*code == 0xe2 ? 1 : 0];
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225240, TownItemModels_DrawCodeD4)

/* func_ov003_022252a0: codes 0xa6 and 0xfe (and tiles whose unit bit is set): the second holder
 * at 0x4840 for 0xfe, else the first. */
void TownItemModels_DrawCodeA6(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    TownItemModels_Draw(process, &process->models_4840[*code == 0xfe ? 1 : 0], matrix);
}
CLEAN_AS(func_ov003_022252a0, TownItemModels_DrawCodeA6)

/* func_ov003_022252fc: codes 0xfc and 0xfd: the second holder at 0x4708 for 0xfd, else the
 * first. */
ModelObject *TownItemModels_DrawCodeFc(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    ModelObject *model = &process->models_4708[*code == 0xfd ? 1 : 0];
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_022252fc, TownItemModels_DrawCodeFc)

/* func_ov003_0222535c: a code of 0xe3-0xfb drawn (TownItemModels_DrawCodeE3), then a wide
 * shadow at `point`. */
void TownItemModels_DrawCodeE3WithShadow(TileEventProcess *process, const u16 *code, const Vec3 *point, Mtx43 matrix)
{
    TownItemModels_DrawCodeE3(process, code, matrix);
    ObjShadow_DrawWide(point);
}
CLEAN_AS(func_ov003_0222535c, TownItemModels_DrawCodeE3WithShadow)

/* func_ov003_022253a8: codes 0xe3-0xfb: the holder of the five pointers at 0x46f4 by the code
 * less 0xe3, modulo 5 (a signed remainder). */
ModelObject *TownItemModels_DrawCodeE3(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    ModelObject *model = town_item_pointer(process, TOWN_ITEM_MODELS_CODE_E3, (*code - 0xe3) % 5);
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_022253a8, TownItemModels_DrawCodeE3)

/* func_ov003_02225404: codes 0x1f-0x24: holder 4 at 0x43e8 for 0x1f and 0x20, else the code less
 * 0x21. */
ModelObject *TownItemModels_DrawCode1f(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    u16 id = *code;
    int index = id >= 0x1f && id <= 0x20 ? 4 : id - 0x21;
    ModelObject *model = town_item_model(process->models_43e8, index);
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225404, TownItemModels_DrawCode1f)

/* func_ov003_02225474: codes 0x1a (the holder at 0x2df0), 0x1b (0x2f28), 0x1d and 0x1e (the
 * pointers at 0x3060 and 0x3064), 0x88 and 0xa4 (0x2e8c), 0x89 (0x2fc4).
 * REQUIRES: `code` is one of those (as the callers give it); for others the original draws a
 * holder it never chose (here none). */
ModelObject *TownItemModels_DrawCode1a(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    ModelObject *model = NULL;
    switch (*code) {
        case 0x1a:
            model = &process->models_2df0[0];
            break;
        case 0x1b:
            model = &process->models_2df0[2];
            break;
        case 0x1d:
            model = town_item_pointer(process, TOWN_ITEM_MODELS_CODE_1D, 0);
            break;
        case 0x1e:
            model = town_item_pointer(process, TOWN_ITEM_MODELS_CODE_1D, 1);
            break;
        case 0x88:
        case 0xa4:
            model = &process->models_2df0[1];
            break;
        case 0x89:
            model = &process->models_2df0[3];
            break;
    }
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225474, TownItemModels_DrawCode1a)

/* func_ov003_02225538: family B: the first holder of the code's line (TownFamily_Line) at
 * 0x1590. */
ModelObject *TownItemModels_DrawFamilyB(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    ModelObject *model = town_item_model(process->models_1590, TOWN_ITEM_MODELS_PER_LINE * TownFamily_Line(code));
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225538, TownItemModels_DrawFamilyB)

/* func_ov003_02225598: families A and C: the holder of the code's line and stage
 * (TownFamily_Line, TownFamily_Stage) at 0x1590 (lines 4 and 5 run on into the holders at
 * 0x2df0). */
ModelObject *TownItemModels_DrawFamily(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    int line = TownFamily_Line(code);
    int stage = TownFamily_Stage(code);
    ModelObject *model = town_item_model(process->models_1590, line * TOWN_ITEM_MODELS_PER_LINE + stage);
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225598, TownItemModels_DrawFamily)

/* func_ov003_02225608: the short lines: of the twelve pointers at 0x4978, 0-3 for 0x2b-0x2e and
 * for 0xff-0x102, 4-7 for 0x62-0x65, 8-11 for 0xd0-0xd3 (any other code: the code less 0xc8). */
ModelObject *TownItemModels_DrawShortLine(TileEventProcess *process, const u16 *code, Mtx43 matrix)
{
    u16 id = *code;
    int index;
    if (id >= 0x2b && id <= 0x2e) {
        index = id - 0x2b;
    } else if (id >= 0xff && id <= 0x102) {
        index = id - 0xff;
    } else if (id >= 0x62 && id <= 0x65) {
        index = id - 0x5e;
    } else {
        index = id - 0xc8;
    }
    ModelObject *model = town_item_pointer(process, TOWN_ITEM_MODELS_SHORT, index);
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225608, TownItemModels_DrawShortLine)

/* func_ov003_02225694: codes 0x25 (holder 5 of the set at 0x174 for the tile's parity), 0xc7
 * (holder 5 at 0x11e8) and 0x5c (any other: holder 5 at 0xc6c). */
ModelObject *TownItemModels_DrawCode25(TileEventProcess *process, const u16 *code, int x, int z, Mtx43 matrix)
{
    u16 id = *code;
    ModelObject *model;
    if (id == 0x25) {
        model = &process->models_0174[((x ^ z) & 1) * 6 + 5];
    } else if (id == 0xc7) {
        model = &process->models_11e8[5];
    } else {
        model = &process->models_0c6c[5];
    }
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225694, TownItemModels_DrawCode25)

/* func_ov003_02225714: a growth code drawn at `point` (TownItemModels_DrawGrowth, on a copy),
 * then a tree's shadow at `point` sized by its stage. */
void TownItemModels_DrawGrowthWithShadow(TileEventProcess *process, const u16 *code, int x, int z, Vec3 *point, Mtx43 matrix)
{
    Vec3 at = *point;
    TownItemModels_DrawGrowth(process, code, x, z, &at, matrix);
    ObjShadow_DrawTree(point, (u8) MapItem_GrowthStage(code));
}
CLEAN_AS(func_ov003_02225714, TownItemModels_DrawGrowthWithShadow)

/* `count` items `item` drawn whole at `point` plus each offset, at scale 1.0. */
static void town_item_draw_items(TileEventProcess *process, int item, const Vec3 *point, const Vec3 *offsets, int count)
{
    for (int i = 0; i < count; i++) {
        Vec3 at = {point->x + offsets[i].x, point->y + offsets[i].y, point->z + offsets[i].z};
        Vec3 scale = {TOWN_ITEM_MODELS_ONE, TOWN_ITEM_MODELS_ONE, TOWN_ITEM_MODELS_ONE};
        TownItemModels_DrawItem(process, item, &at, TOWN_ITEM_MODELS_OPAQUE, &scale, 0, 0, 0);
    }
}

/* func_ov003_02225768: a growth code at tile (x, z) drawn by the holder of its stage
 * (MapItem_GrowthStage): the eight-code lines 0x2f-0x56 and code 0x69 from holder 12 of the set
 * at 0x174, line 0x57-0x5b and the other codes from the set's half for the tile's parity, the
 * codes 0x5d-0x61 and 0x6a-0x6d at 0xc6c, 0xc8-0xcf at 0x11e8. Grown codes of the lines 0x2f-0x5b
 * carry their fruit (TownItemModels_DrawFruit), code 0x69 three of item 0x1542 always, grown
 * codes of 0xc8-0xcf two of item 0x1548; code 0x6d also draws its frame
 * (TownItemModels_DrawCode6dFrame). */
ModelObject *TownItemModels_DrawGrowth(TileEventProcess *process, const u16 *code, int x, int z, const Vec3 *point,
                                       Mtx43 matrix)
{
    int stage = MapItem_GrowthStage(code);
    u16 id = *code;
    int parity_set = ((x ^ z) & 1) * 6;
    ModelObject *model;
    if (id >= 0x2f && id <= 0x56) {
        if (MapItem_IsGrown(code)) {
            Vec3 at = *point;
            TownItemModels_DrawFruit(process, code, &at);
        }
        model = town_item_model(process->models_0174, 12 + stage);
    } else if (id >= 0x57 && id <= 0x5b) {
        if (MapItem_IsGrown(code)) {
            Vec3 at = *point;
            TownItemModels_DrawFruit(process, code, &at);
        }
        model = town_item_model(process->models_0174, parity_set + stage);
    } else if (id == 0x69) {
        town_item_draw_items(process, TOWN_ITEM_MODELS_FRUIT_69, point, data_ov003_02236b64, 3);
        model = town_item_model(process->models_0174, 12 + stage);
    } else if (id >= 0x6a && id <= 0x6c) {
        model = town_item_model(process->models_0c6c, stage);
    } else if (id == 0x6d) {
        Vec3 at = *point;
        TownItemModels_DrawCode6dFrame(process, &at, x, z);
        model = town_item_model(process->models_0c6c, stage);
    } else if (id >= 0x5d && id <= 0x61) {
        model = town_item_model(process->models_0c6c, stage);
    } else if (id >= 0xc8 && id <= 0xcf) {
        if (MapItem_IsGrown(code)) {
            town_item_draw_items(process, TOWN_ITEM_MODELS_FRUIT_C8, point, data_ov003_02236b4c, 2);
        }
        model = town_item_model(process->models_11e8, stage);
    } else {
        model = town_item_model(process->models_0174, parity_set + stage);
    }
    TownItemModels_Draw(process, model, matrix);
    return model;
}
CLEAN_AS(func_ov003_02225768, TownItemModels_DrawGrowth)

/* func_ov003_022259e8: the frame of code 0x6d at tile (x, z) drawn at `point`: for the day's
 * code 0x6d spot k there (TownDay_FindCode6d), holder (k + (clock + 15 k) / 20) % 3 at 0x1014,
 * each frame shown 20 frames of the clock; none where there is no spot. */
void TownItemModels_DrawCode6dFrame(TileEventProcess *process, const Vec3 *point, int x, int z)
{
    ModelObject *model = NULL;
    int spot = TownDay_FindCode6d(x, z);
    if (spot != -1) {
        int frame = (spot + (*town_item_clock(process) + spot * 15) / 20) % 3;
        model = town_item_model(process->models_1014, frame);
    }
    town_item_place(point);
    TownItemModels_Draw(process, model, data_021fbe48);
}
CLEAN_AS(func_ov003_022259e8, TownItemModels_DrawCode6dFrame)

/* func_ov003_02225a90: the three fruit of a grown code of the lines 0x2f-0x5b: item 0x14b8 for
 * line 0x57-0x5b, else the fruit of its line (data_ov003_0223667c). */
void TownItemModels_DrawFruit(TileEventProcess *process, const u16 *code, const Vec3 *point)
{
    u16 id = *code;
    int item = id >= 0x57 && id <= 0x5b ? TOWN_ITEM_MODELS_FRUIT_57 : data_ov003_0223667c[MapItem_EightLine(code)];
    town_item_draw_items(process, item, point, data_ov003_02236b64, 3);
}
CLEAN_AS(func_ov003_02225a90, TownItemModels_DrawFruit)

/* Codes TownItemModels_DrawCode hands TownItemModels_DrawFamily (the families A and C with the
 * codes after them). */
static int town_item_family_code(u16 code)
{
    return code <= 0x1a || code == 0x1c || code == 0x1d || (code >= 0x8a && code <= 0xa5);
}

/* func_ov003_02225b24: `code` drawn at `point` bent over the globe, turned by the bend about X
 * and by the three angles, scaled by `scale`: codes 0xd4-0xda as items 0x153b-0x1541, 0xdb-0xe1
 * as item 0x153b, 0x20 as item 0x156a; items (kinds 1, 3 and 4) by their holder; codes of kind
 * 0 by TownItemModels_DrawCode1a (0x1a, 0x1b, 0x1d, 0x1e, 0x88, 0x89), TownItemModels_DrawFamily
 * (families A and C, 0x1a, 0x1c, 0x1d and 0xa4) or TownItemModels_DrawCodeA7 (0xa7-0xc6);
 * others are not drawn. */
void TownItemModels_DrawCode(TileEventProcess *process, u16 code, const Vec3 *point, const Vec3 *scale, short angle_x,
                             short angle_y, short angle_z)
{
    town_item_place(point);
    Mtx43_RotateZYX(&data_021fbe48, angle_x, angle_y, angle_z);
    Mtx43_Scale(&data_021fbe48, scale->x, scale->y, scale->z);

    u16 drawn = code;
    if (code >= 0xd4 && code <= 0xe1) {
        u16 index = (u16) (code - 0xd4);
        drawn = index < 7 ? (u16) (index + 0x153b) : 0x153b;
    } else if (code == 0x20) {
        drawn = 0x156a;
    }

    switch ((drawn & 0xf000) >> 12) {
        case 0:
            if (town_item_code_1a(drawn)) {
                TownItemModels_DrawCode1a(process, &drawn, data_021fbe48);
            } else if (town_item_family_code(drawn)) {
                TownItemModels_DrawFamily(process, &drawn, data_021fbe48);
            } else if (drawn >= 0xa7 && drawn <= 0xc6) {
                TownItemModels_DrawCodeA7(process, &drawn, data_021fbe48);
            }
            break;
        case 1:
        case 3:
        case 4: {
            ModelObject *holder = town_item_pointer(process, TOWN_ITEM_MODELS_ITEM_HOLDERS, ItemTraits_Unk07(&drawn));
            TownItemModels_Draw(process, holder, data_021fbe48);
            break;
        }
    }
}
CLEAN_AS(func_ov003_02225b24, TownItemModels_DrawCode)

/* func_ov003_02225da0: `item` drawn by its holder (ItemTraits_Unk07, TownItemModels_DrawHolder);
 * the holder's address. */
int TownItemModels_DrawItem(TileEventProcess *process, int item, const Vec3 *point, int alpha, const Vec3 *scale,
                            short angle_x, short angle_y, short angle_z)
{
    u16 code = (u16) item;
    Vec3 at = *point;
    Vec3 size = *scale;
    ModelObject *model =
        TownItemModels_DrawHolder(process, ItemTraits_Unk07(&code), &at, alpha, &size, angle_x, angle_y, angle_z);
    return (int) (intptr_t) model;
}
CLEAN_AS(func_ov003_02225da0, TownItemModels_DrawItem)

/* func_ov003_02225e00: item holder `holder` drawn at `point` bent over the globe, turned by the
 * bend about X and by the three angles, scaled by `scale`, its materials' alpha `alpha`;
 * returns it.
 * REQUIRES: the holder exists (its model is read before the draw checks it). */
ModelObject *TownItemModels_DrawHolder(TileEventProcess *process, int holder, const Vec3 *point, int alpha, const Vec3 *scale,
                                       short angle_x, short angle_y, short angle_z)
{
    ModelObject *model = town_item_pointer(process, TOWN_ITEM_MODELS_ITEM_HOLDERS, holder);
    town_item_place(point);
    Mtx43_RotateZYX(&data_021fbe48, angle_x, angle_y, angle_z);
    Mtx43_Scale(&data_021fbe48, scale->x, scale->y, scale->z);
    func_0210744c(model->model, alpha);
    TownItemModels_Draw(process, model, data_021fbe48);
    return model;
}
CLEAN_AS(func_ov003_02225e00, TownItemModels_DrawHolder)
