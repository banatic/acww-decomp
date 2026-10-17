/* The fish shadows' states and the process's frame, destruction and drawing (fish_shadow.h):
 * where a shadow is placed, how it comes into view, fades and flees, and the helpers of the
 * other shadow files (random numbers, boxes, the current).
 *
 * A shadow's states (the member functions of data_ov003_0225f1d0, entry and update):
 *   0 FISH_SHADOW_NONE     waits to be placed in its group, one shadow a frame
 *                          (FishShadow_UpdateNone, FishShadow_Place);
 *   1 FISH_SHADOW_PLACED   placed out of the camera's view; once its point comes into view it
 *                          goes to state 2 and the fin is loaded for a kind with one
 *                          (FishShadow_UpdatePlaced);
 *   2                      appears: shown once the fin is loaded, or once it has moved
 *                          (FishShadow_UpdateAppearing);
 *   3 FISH_SHADOW_SHOWN    swims (FishShadow_UpdateShown), flees the player at this console
 *                          when that player runs near it, fades out once fleeing, and goes
 *                          away when out of view (FishShadow_CheckInView);
 *   4 FISH_SHADOW_AWAY     out of view: back to 3 when in view again, else taken away when its
 *                          timer ends (FishShadow_UpdateAway).
 * Each shadow also counts down its respawn (FishShadow_TickRespawn). */
#include "fish_shadow.h"

#include "autoload_2/heap.h" /* Heap_FreeCurrent */
#include "autoload_2/matrix.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/acre_tile.h"
#include "main/collision_query.h"
#include "main/actor.h" /* Actor, Vec_YawTo */
#include "main/creature_table.h"
#include "main/effect_system.h"
#include "main/globe.h"
#include "main/main_random.h"
#include "main/player_actor_ops.h"
#include "main/rom_file.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/sky.h"
#include "main/unit_type_info.h"
#include "autoload_2/approach.h" /* Countdown_Tick16 */
#include "field_actor.h"         /* FieldActor_PlayerFlag9 */
#include "thrown_bottle.h"

#include <string.h>

/* A size class's numbers (data_ov003_0223c014, eight rows of 0x14 bytes); those read here. */
typedef struct FishStateSize {
    u8 unk_00[8]; /* 0x00 */
    u8 radius;    /* 0x08: its radius against walls, in tenths of a unit */
    u8 unk_09[5]; /* 0x09 */
    u8 scale_x;   /* 0x0e: the shadow's scale, in percent */
    u8 scale_z;   /* 0x0f */
    u8 unk_10[4]; /* 0x10 */
} FishStateSize;
static_assert(sizeof(FishStateSize) == 0x14, "FishStateSize");

/* Where the fin is (the 0x10 bytes at 0x48 of FishFin). */
typedef struct FishStateFinPlace {
    Vec3 position; /* 0x00 */
    s16 yaw;       /* 0x0c */
    u8 pad_0e[2];  /* 0x0e */
} FishStateFinPlace;

/* An acre a shadow may be placed in (FishShadow_ListAcres). */
typedef struct FishShadowAcre {
    u8 x;
    u8 z;
} FishShadowAcre;

/* A unit of an acre a shadow may be placed on (FishShadow_FindSpot). */
typedef struct FishShadowUnit {
    s8 x;
    s8 z;
} FishShadowUnit;

#define FISH_STATE_THIS_CONSOLE 4 /* main's player number for the player at this console */
#define FISH_STATE_FIN_FIRST 0x34 /* the kinds that show the fin */
#define FISH_STATE_FIN_LAST 0x36
#define FISH_STATE_RAIN_KIND 0x37      /* the kind placed only while it rains or snows */
#define FISH_STATE_SENSE_KIND 0xb      /* the only kind that hears the player (FishShadowSense) */
#define FISH_STATE_SURFACE_Y (-0x1333) /* the height a shadow is drawn at */
#define FISH_STATE_ALPHA_FULL 0x1f
#define FISH_STATE_ALPHA_FLEE 0x1e
#define FISH_STATE_RESPAWN 0x960 /* 2400 frames */
/* FishShadow.group_state when no kind could be picked for group 0 or 1. */
#define FISH_STATE_NO_KIND0 5
#define FISH_STATE_NO_KIND1 6
#define FISH_STATE_RUN_SPEED 0x548
#define FISH_STATE_SCARE_DISTANCE 0x135c3 /* the square of the player's distance that scares it */
#define FISH_STATE_SCARE_FRAMES 6
#define FISH_STATE_AWAY_SHORT 300 /* the timer out of view with water behind it */
#define FISH_STATE_AWAY_LONG 1200
/* The box around the camera's point a shadow is seen in: 10.0 across, 16.0 ahead, 10.0 behind. */
#define FISH_STATE_VIEW_X 0xa000
#define FISH_STATE_VIEW_AHEAD 0x10000
#define FISH_STATE_VIEW_BEHIND 0xa000
/* The model's name it is shared by ('fsdw'). */
#define FISH_STATE_MODEL_NAME 0x66736477

extern FishShadow data_ov003_0225f76c[FISH_SHADOW_COUNT];
extern FishFin data_ov003_0225f220;
extern PlayerFish data_ov003_0225f4dc[PLAYER_FISH_COUNT];
extern ThrownBottle data_ov003_0225f35c[THROWN_BOTTLE_COUNT];
/* The object ThrownBottle_Step is handed (fish_shadow.h, FishShadowGlobal0225f0b4_*). */
extern u8 data_ov003_0225f0b4[];
extern const FishStateSize data_ov003_0223c014[];
extern const CreatureTableInfo data_020cb784[];
extern NetSession *data_020ccf94;
/* The camera (itcm/camera.h, 0 while there is none) and the point it follows. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;
/* The town's map. */
extern AcreMap *data_021c80bc;
/* The water's surface height. */
extern s32 data_020c904c;
/* The matrix the model's place is built in. */
extern Mtx43 data_021fbe48;
extern Heap *data_021fbe94;
/* The files: the shadow's model ("/fish/03/fish_shadow.nsbmd") and the fin's model,
 * animation and texture animation ("/fish/03/fish_hire.*"). */
extern const char *data_ov003_0223bdb8;
extern const char *data_ov003_0223bdb0;
extern const char *data_ov003_0223bdb4;
extern const char *data_ov003_0223bdbc;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* NitroSystem: an animation file's set of joint and texture SRT animations, and animation
 * `index` of a set. */
extern void *NNS_G3dGetJntAnmSet(void *file);
extern void *NNS_G3dGetTexSRTAnmSet(void *file);
extern u8 *func_02107b44(void *set, int index);
extern u8 *func_02107bbc(void *set, int index);

/* The frames the player at this console must keep running near it before it flees (the byte
 * at 0x214). */
static u8 *fish_state_scare_wait(FishShadow *fish)
{
    return &fish->pad_214[0];
}

static AnimatedModel *fish_state_model(FishShadowModel *model)
{
    return (AnimatedModel *) (void *) model;
}

static FishStateFinPlace *fish_state_fin_place(FishFin *fin)
{
    return (FishStateFinPlace *) (void *) fin->unk_48;
}

static int fish_state_abs(int value)
{
    return value < 0 ? -value : value;
}

/* func_ov003_02227654: shadow `index` (0-5) when it is shown or away (states 3 and 4), else
 * NULL. */
FishShadow *FishShadow_Shown(int index)
{
    if (index < 0 || index >= FISH_SHADOW_COUNT) {
        return NULL;
    }
    FishShadow *fish = &data_ov003_0225f76c[index];
    if (fish->state != FISH_SHADOW_SHOWN && fish->state != FISH_SHADOW_AWAY) {
        return NULL;
    }
    return fish;
}
CLEAN_AS(func_ov003_02227654, FishShadow_Shown)

/* func_ov003_02227608: the position of shadow `index` when it is shown (FishShadow_Shown), in
 * `out`; whether it is. */
int FishShadow_ShownPosition(Vec3 *out, int index)
{
    FishShadow *fish = FishShadow_Shown(index);
    if (fish == NULL) {
        return 0;
    }
    *out = fish->position;
    return 1;
}
CLEAN_AS(func_ov003_02227608, FishShadow_ShownPosition)

/* func_ov003_02227638: the kind of shadow `index` when it is shown (FishShadow_Shown), else -1. */
int FishShadow_ShownKind(int index)
{
    FishShadow *fish = FishShadow_Shown(index);
    if (fish == NULL) {
        return -1;
    }
    return fish->kind;
}
CLEAN_AS(func_ov003_02227638, FishShadow_ShownKind)

/* func_ov003_02227680: the fin loaded in an entry of the "fish_fin" pool: its model from the
 * model file, its joint animation (from the animation file read into the entry's heap) started
 * looping at speed 1.0, and its texture animation the same; 0 when the model file could not be
 * read or an animation could not be set up. */
int FishFin_Load(FishFin *fin, ModelPool *pool)
{
    ModelPoolEntry *entry = ModelPool_Take(pool, &fin->slot);
    if (!ModelPoolFiles_Load(&fin->files, entry, data_ov003_0223bdb0)) {
        return 0;
    }
    AnimatedModel *model = fish_state_model(&fin->model);
    ModelObject_SetModel(&model->object, (u8 *) (uintptr_t) ModelPoolFiles_Model(&fin->files), NULL);
    Heap *heap = (Heap *) (uintptr_t) ModelPoolEntry_Heap(entry);
    u8 *joints = func_02107b44(NNS_G3dGetJntAnmSet(RomFile_Load(data_ov003_0223bdb4, heap, 4, NULL)), 0);
    if (!AnimatedModel_LoadAnim(model, heap)) {
        return 0;
    }
    AnimatedModel_Start(model, joints, 0, 0x1000, 1, 0);
    AnimatedModel_Attach(model);
    u8 *textures = func_02107bbc(NNS_G3dGetTexSRTAnmSet(RomFile_Load(data_ov003_0223bdbc, heap, 4, NULL)), 0);
    if (!ModelAnim_AllocMaterialAnim(&fin->anim, model->object.model, heap)) {
        return 0;
    }
    ModelAnim_Start(&fin->anim, textures, 0, 0x1000, 1);
    ModelAnim_Attach(&fin->anim, ModelObject_RenderObject(&model->object));
    return 1;
}
CLEAN_AS(func_ov003_02227680, FishFin_Load)

/* func_ov003_02227778: the shadow's model taken from the shared one ('fsdw', the shadow's model
 * file) and, given the animation file `file`, its animation set up in an entry of the
 * "fish_sdw" pool and started looping at speed 1.0; whether it was. */
int FishShadow_LoadModel(FishShadow *fish, void *file, ModelPool *pool)
{
    AnimatedModel *model = fish_state_model(&fish->model);
    ModelObject_LoadShared(&model->object, FISH_STATE_MODEL_NAME, data_ov003_0223bdb8);
    if (file == NULL) {
        return 0;
    }
    Heap *heap = (Heap *) (uintptr_t) ModelPoolEntry_Heap(ModelPool_Take(pool, &fish->slot));
    u8 *joints = func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
    if (!AnimatedModel_LoadAnim(model, heap)) {
        return 0;
    }
    AnimatedModel_Start(model, joints, 0, 0x1000, 1, 0);
    AnimatedModel_Attach(model);
    return 1;
}
CLEAN_AS(func_ov003_02227778, FishShadow_LoadModel)

/* func_ov003_022277fc: the shadow's animation speed set to `speed` sixteenths of a frame.
 * QUIRK: the speed is kept in 20 bits (shifted up 12, then down 4 with its sign). */
void FishShadow_SetAnimSpeed(FishShadow *fish, int speed)
{
    fish->model.frames.speed = (int) ((u32) speed << 12) >> 4;
}
CLEAN_AS(func_ov003_022277fc, FishShadow_SetAnimSpeed)

/* func_ov003_0222780c: a fish from the pockets (items 0x12e8-0x131f, the item's halfword) let
 * go by player `player` (0-3) towards `point`: it starts from the player's actor (PLAYER_FISH_ARC,
 * PLAYER_FISH_TAKE), turned for its kind towards the point. 0 for another item or player, a
 * player whose fish is busy or one without an actor. */
int PlayerFish_PlaceFromPockets(int player, int item, Vec3 *point)
{
    u16 code = (u16) item;
    if (code < 0x12e8 || code > 0x131f) {
        return 0;
    }
    if (player < 0 || player >= PLAYER_FISH_COUNT) {
        return 0;
    }
    PlayerFish *fish = &data_ov003_0225f4dc[player];
    if (fish->state != PLAYER_FISH_IDLE) {
        return 0;
    }
    Actor *actor = SessionPlayers_ActorOf(player);
    if (actor == NULL) {
        return 0;
    }
    Vec3 from = actor->position;
    int kind = code - 0x12e8;
    fish->kind = kind;
    PlayerFish_TurnForThrow(fish, Vec_YawTo(&from, point), kind);
    fish->point_a = from;
    fish->point_b = *point;
    fish->position = from;
    fish->frames = 0;
    fish->mode = PLAYER_FISH_ARC;
    fish->state = PLAYER_FISH_TAKE;
    return 1;
}
CLEAN_AS(func_ov003_0222780c, PlayerFish_PlaceFromPockets)

/* func_ov003_022278e0: where the hooked fish of player `player` (0-3) started in the water, in
 * `out`; whether it is hooked (PLAYER_FISH_HOOKED). */
int PlayerFish_HookedStart(Vec3 *out, int player)
{
    if (player < 0 || player >= PLAYER_FISH_COUNT) {
        return 0;
    }
    PlayerFish *fish = &data_ov003_0225f4dc[player];
    if (fish->mode != PLAYER_FISH_HOOKED) {
        return 0;
    }
    *out = fish->point_a;
    return 1;
}
CLEAN_AS(func_ov003_022278e0, PlayerFish_HookedStart)

/* func_ov003_0222791c: a random number in [lo, hi) (FishShadow_Random), negated half the time. */
int FishShadow_RandomSigned(int lo, int hi)
{
    int value = FishShadow_Random(lo, hi);
    if (MainRandom_Below(2) == 0) {
        value = -value;
    }
    return value;
}
CLEAN_AS(func_ov003_0222791c, FishShadow_RandomSigned)

/* func_ov003_0222793c: a random number in [lo, hi). */
int FishShadow_Random(int lo, int hi)
{
    return lo + (int) MainRandom_Below(hi - lo);
}
CLEAN_AS(func_ov003_0222793c, FishShadow_Random)

/* func_ov003_02227950: whether `value` is at least as far from `from` as `to` is. */
int FishShadow_ReachedOnAxis(int value, int from, int to)
{
    return fish_state_abs(value - from) >= fish_state_abs(to - from);
}
CLEAN_AS(func_ov003_02227950, FishShadow_ReachedOnAxis)

/* func_ov003_0222796c: whether `position` is at least as far from `from` as `to` is, along x and
 * along z (it has reached the end of the line from `from` to `to`). */
int FishShadow_ReachedXZ(const Vec3 *position, const Vec3 *from, const Vec3 *to)
{
    return FishShadow_ReachedOnAxis(position->x, from->x, to->x) && FishShadow_ReachedOnAxis(position->z, from->z, to->z);
}
CLEAN_AS(func_ov003_0222796c, FishShadow_ReachedXZ)

/* func_ov003_0222799c: whether `b` is in the box around `a`: at most `dx` off along x, and at
 * most `dz_ahead` beyond along z or `dz_behind` before. */
int FishShadow_InBox(const Vec3 *a, const Vec3 *b, int dx, int dz_ahead, int dz_behind)
{
    if (fish_state_abs(b->x - a->x) > dx) {
        return 0;
    }
    int dz = b->z - a->z;
    if (dz >= 0) {
        return dz <= dz_ahead;
    }
    return a->z - b->z <= dz_behind;
}
CLEAN_AS(func_ov003_0222799c, FishShadow_InBox)

/* func_ov003_022279d8: the respawn counted down; when it ends, a shadow not yet shown (states 0
 * and 1) goes back to waiting to be placed in its group (by its number) and the count starts
 * again at 2400. */
void FishShadow_TickRespawn(FishShadow *fish)
{
    if (Countdown_Tick16((u16 *) &fish->respawn) != 0) {
        return;
    }
    if ((u32) fish->state <= FISH_SHADOW_PLACED) {
        fish->state = FISH_SHADOW_NONE;
        if (fish->index < FISH_SHADOW_GROUP_SIZE) {
            fish->group_state = FISH_SHADOW_WAIT_GROUP0;
        } else if (fish->index < FISH_SHADOW_COUNT) {
            fish->group_state = FISH_SHADOW_WAIT_GROUP1;
        }
    }
    fish->respawn = FISH_STATE_RESPAWN;
}
CLEAN_AS(func_ov003_022279d8, FishShadow_TickRespawn)

/* func_ov003_02227a30: whether rain or snow falls (Sky_Falling). */
int FishShadow_SkyFalling(FishShadowProcess *self)
{
    (void) self;
    int falling = Sky_Falling();
    return falling == SKY_FALLING_RAIN || falling == SKY_FALLING_SNOW;
}
CLEAN_AS(func_ov003_02227a30, FishShadow_SkyFalling)

/* func_ov003_02227a48: whether a fish of kind `kind` may be placed as shadow `fish`: a kind with
 * the fin needs the player at this console to have an actor and no other shadow of group 1 with
 * the fin; kind 0x37 needs rain or snow. */
int FishShadow_KindAllowed(FishShadowProcess *self, FishShadow *fish, int kind)
{
    if (kind >= FISH_STATE_FIN_FIRST && kind <= FISH_STATE_FIN_LAST) {
        if (SessionPlayers_ActorOf(FISH_STATE_THIS_CONSOLE) == NULL) {
            return 0;
        }
        for (int i = FISH_SHADOW_GROUP_SIZE; i < FISH_SHADOW_COUNT; i++) {
            FishShadow *other = &data_ov003_0225f76c[i];
            if (fish != other && other->has_fin) {
                return 0;
            }
        }
    } else if (kind == FISH_STATE_RAIN_KIND) {
        if (!FishShadow_SkyFalling(self)) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_02227a48, FishShadow_KindAllowed)

/* Whether unit (x, z) is ground `ground` may be placed on (see FishShadow_FindSpot); `first_z`
 * is the acre's first row. */
static int fish_state_unit_fits(unsigned int ground, int x, int z, int first_z)
{
    switch (ground) {
        case 5:
        case 6:
            return UnitTypeInfo_GroupAt(x, z) == 1;
        case 0:
        case 1:
            return UnitTypeInfo_GroupAt(x, z) == 2;
        case 2:
            return z < first_z + 3 && UnitTypeInfo_GroupAt(x, z) == 2;
        case 3:
            return UnitTypeInfo_IsType07At(x, z) != 0;
        case 4:
            return UnitTypeInfo_GroupAt(x, z) == 2 || UnitTypeInfo_GroupAt(x, z) == 1;
        default:
            return 0;
    }
}

/* func_ov003_02227ab0: a place for a shadow of ground `ground` in group `group`: an acre picked
 * at random of those listed for the ground (FishShadow_ListAcres), in `acre_x` and `acre_z`; no
 * place when another shadow of the group (but `skip`) is in that acre (0, the unit left alone).
 * Then a unit of the acre picked at random of those of the ground's kind (units of group 2 for
 * the grounds 0 and 1, the same in the acre's first three rows for 2, type 7 for 3, group 1 or
 * 2 for 4, group 1 for 5 and 6), in `unit_x` and `unit_z`: none when there is none, or when the
 * unit's centre is in view of the camera (both -1, and 0). 0 also while there is no camera.
 * QUIRK: the picked acre and unit are read as signed bytes. */
int FishShadow_FindSpot(FishShadowProcess *self, int *unit_x, int *unit_z, int *acre_x, int *acre_z, unsigned int ground,
                        int group, FishShadow *skip)
{
    FishShadowAcre acres[16];
    FishShadowUnit units[258];
    int acre_count = 0;
    if (data_021c67a4 == 0) {
        return 0;
    }
    Vec3 camera = data_021c67d0;
    Vec3 camera_tile;
    AcreTile_SnapToTileCentre(&camera_tile, &camera);
    if (!FishShadow_ListAcres(self, acres, &acre_count, ground)) {
        return 0;
    }
    int pick = FishShadow_Random(0, (u16) acre_count);
    *acre_x = (s8) acres[pick].x;
    *acre_z = (s8) acres[pick].z;
    int x = *acre_x;
    int z = *acre_z;
    if (group == FISH_SHADOW_IN_GROUP0 || group == FISH_SHADOW_IN_GROUP1) {
        int first = group == FISH_SHADOW_IN_GROUP0 ? 0 : FISH_SHADOW_GROUP_SIZE;
        for (int i = first; i < first + FISH_SHADOW_GROUP_SIZE; i++) {
            FishShadow *other = &data_ov003_0225f76c[i];
            if (skip != other && x == other->tile_x && z == other->tile_z) {
                return 0;
            }
        }
    }
    int first_x;
    int first_z;
    AcreTile_TileOfAcre(&first_x, &first_z, x, z, 0, 0);
    int count = 0;
    int end_x = first_x + ACRE_RECORD_SIDE;
    int end_z = first_z + ACRE_RECORD_SIDE;
    for (int i = first_x; i < end_x; i++) {
        for (int j = first_z; j < end_z; j++) {
            if (fish_state_unit_fits(ground, i, j, first_z)) {
                units[count].x = (s8) i;
                units[count].z = (s8) j;
                count++;
            }
        }
    }
    if (count == 0) {
        *unit_x = -1;
        *unit_z = -1;
        return 0;
    }
    pick = (s16) FishShadow_Random(0, (u16) count);
    int spot_z = units[pick].z;
    int spot_x = units[pick].x;
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) spot_x, (u32) spot_z);
    if (FishShadow_InBox(&centre, &camera_tile, FISH_STATE_VIEW_X, FISH_STATE_VIEW_AHEAD, FISH_STATE_VIEW_BEHIND)) {
        *unit_x = -1;
        *unit_z = -1;
        return 0;
    }
    *unit_x = spot_x;
    *unit_z = spot_z;
    return 1;
}
CLEAN_AS(func_ov003_02227ab0, FishShadow_FindSpot)

/* Whether acre `acre` suits ground `ground` (see FishShadow_ListAcres). */
static int fish_state_acre_fits(unsigned int ground, AcreRecord *acre)
{
    switch (ground) {
        case 6:
        case 5:
            return (AcreRecord_Flags(acre) & 8) != 0;
        case 0:
            return (AcreRecord_Flags(acre) & 0x7f000) != 0;
        case 1:
            return (AcreRecord_Flags(acre) & 0x100) != 0;
        case 2:
            return (AcreRecord_Flags(acre) & 0x80000) != 0;
        case 3:
            return AcreRecord_ModelIsListed(acre) != 0;
        case 4: {
            int flags = AcreRecord_Flags(acre);
            return (flags & 0x7f000) != 0 && (flags & 8) != 0;
        }
        default:
            return 0;
    }
}

/* func_ov003_02227cec: the acres of the town's map, but its border, that suit ground `ground`
 * (by their flags: 8 for the grounds 5 and 6, 0x7f000 for 0, 0x100 for 1, 0x80000 for 2, both
 * 0x7f000 and 8 for 4; a listed model for 3) appended to `out`, `count` counting them; whether
 * any is listed (counting those `count` held before).
 * QUIRK: x runs to the map's height less one and z to its width less one, while the acre is
 * looked up with x as the column and z as the row (an acre out of the map is skipped). */
int FishShadow_ListAcres(FishShadowProcess *self, FishShadowAcre *out, int *count, unsigned int ground)
{
    (void) self;
    AcreMap *map = data_021c80bc;
    if (map != NULL) {
        for (int x = 1; x < map->acres_high - 1; x++) {
            for (int z = 1; z < map->acres_wide - 1; z++) {
                if ((u32) x >= (u32) map->acres_wide || (u32) z >= (u32) map->acres_high || map->acres == NULL) {
                    continue;
                }
                AcreRecord *acre = (AcreRecord *) (void *) (map->acres + (z * map->acres_wide + x) * ACRE_MAP_ACRE_SIZE);
                if (fish_state_acre_fits(ground, acre)) {
                    out[*count].x = (u8) x;
                    out[*count].z = (u8) z;
                    *count = *count + 1;
                }
            }
        }
    }
    return *count > 0;
}
CLEAN_AS(func_ov003_02227cec, FishShadow_ListAcres)

/* func_ov003_02227e94: shadow `fish` placed in group `group` (0, else 1): a kind and its ground
 * picked for the group's place now (CreatureTable_PickNow; none: the shadow found no place,
 * group state 5 or 6), a place for it (FishShadow_FindSpot; none: it waits again, 3 or 4) and
 * the kind allowed (FishShadow_KindAllowed; else nothing changes). Placed, it is at the unit's
 * centre at the surface, facing -z, of that kind and ground, in the group, in state
 * FISH_SHADOW_PLACED, swimming state 0, its acre kept, no timer. Whether it was placed. */
int FishShadow_Place(FishShadowProcess *self, FishShadow *fish, int group)
{
    int unit_x = -1;
    int unit_z = -1;
    int acre_x = -1;
    int acre_z = -1;
    int kind;
    int ground;
    if (!CreatureTable_PickNow(&kind, &ground, group == 0 ? 0 : 1)) {
        if (group == FISH_SHADOW_IN_GROUP0) {
            fish->group_state = FISH_STATE_NO_KIND0;
        } else if (group == FISH_SHADOW_IN_GROUP1) {
            fish->group_state = FISH_STATE_NO_KIND1;
        }
        return 0;
    }
    if (!FishShadow_FindSpot(self, &unit_x, &unit_z, &acre_x, &acre_z, (unsigned int) ground, group, fish)) {
        if (group == FISH_SHADOW_IN_GROUP0) {
            fish->group_state = FISH_SHADOW_WAIT_GROUP0;
        } else if (group == FISH_SHADOW_IN_GROUP1) {
            fish->group_state = FISH_SHADOW_WAIT_GROUP1;
        }
        return 0;
    }
    if (!FishShadow_KindAllowed(self, fish, kind)) {
        return 0;
    }
    Vec3 at;
    AcreTile_TileCentre(&at, (u32) unit_x, (u32) unit_z);
    at.y = FISH_STATE_SURFACE_Y;
    fish->kind = (s8) kind;
    fish->has_fin = kind >= FISH_STATE_FIN_FIRST && kind <= FISH_STATE_FIN_LAST;
    fish->ground = (u8) ground;
    fish->size = data_020cb784[kind].offset_class;
    fish->yaw = -0x8000;
    fish->unk_12c = at;
    fish->group_state = (u8) group;
    fish->state = FISH_SHADOW_PLACED;
    fish->behaviour = 0;
    fish->last_position = at;
    fish->tile_x = acre_x;
    fish->tile_z = acre_z;
    fish->timer = -1;
    return 1;
}
CLEAN_AS(func_ov003_02227e94, FishShadow_Place)

/* func_ov003_02227fe4: whether player `player`'s actor is within sqrt(0x135c3) (about 19.3) of
 * `point` along the ground; 0 without an actor. */
int FishShadow_PlayerNear(FishShadowProcess *self, const Vec3 *point, int player)
{
    (void) self;
    Actor *actor = SessionPlayers_ActorOf(player);
    if (actor == NULL) {
        return 0;
    }
    return Vec_DistanceSquaredXZ(&actor->position, point) <= FISH_STATE_SCARE_DISTANCE;
}
CLEAN_AS(func_ov003_02227fe4, FishShadow_PlayerNear)

/* func_ov003_02228018: whether player `player`'s actor runs (its speed above 0x548). */
int FishShadow_PlayerRunning(int player)
{
    Actor *actor = SessionPlayers_ActorOf(player);
    return actor != NULL && actor->speed > FISH_STATE_RUN_SPEED;
}
CLEAN_AS(func_ov003_02228018, FishShadow_PlayerRunning)

/* func_ov003_0222803c: `position` drifted by `amount` along the ground's normal there (the
 * water's current), in x and z. */
void FishShadow_Drift(Vec3 *position, int amount)
{
    CollisionGround ground;
    CollisionGround_Init(&ground, position, 0, 0);
    position->x += FX_MulFunc(amount, ground.normal.x);
    position->z += FX_MulFunc(amount, ground.normal.z);
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov003_0222803c, FishShadow_Drift)

/* func_ov003_0222807c: a shown shadow not hooked (or fleeing from the hook) that is out of the
 * camera's view: one fleeing is taken away (the fin put away with it), another goes away
 * (FISH_SHADOW_AWAY, set without its entry function) with a timer of 1200 frames, or 300 on the
 * grounds 4-6 with water behind it. */
void FishShadow_CheckInView(FishShadowProcess *self, FishShadow *fish, int index)
{
    if (fish->hooked != 0 && fish->hook_state != FISH_SHADOW_HOOK_FLEEING) {
        return;
    }
    if (data_021c67a4 == 0) {
        return;
    }
    Vec3 camera = data_021c67d0;
    if (FishShadow_InBox(&fish->position, &camera, FISH_STATE_VIEW_X, FISH_STATE_VIEW_AHEAD, FISH_STATE_VIEW_BEHIND)) {
        return;
    }
    if (fish->behaviour == FISH_SHADOW_FLEEING || fish->hook_state == FISH_SHADOW_HOOK_FLEEING) {
        if (fish->has_fin) {
            FishShadow_ReleaseFin(self);
        }
        FishShadow_Reset(self, index);
        return;
    }
    if (fish->ground >= 4 && fish->ground <= 6 && FishShadow_IsWaterBehind(fish)) {
        fish->timer = FISH_STATE_AWAY_SHORT;
    } else {
        fish->timer = FISH_STATE_AWAY_LONG;
    }
    fish->state = FISH_SHADOW_AWAY;
}
CLEAN_AS(func_ov003_0222807c, FishShadow_CheckInView)

/* The effect of a fleeing shadow's splash, by its size class (none for 8 or more). */
static int fish_state_flee_effect(int size)
{
    static const u8 kinds[8] = {0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x21, 0x20};
    return size < 8 ? kinds[size] : -1;
}

/* func_ov003_02228150: the shown shadow (none: 0) flees from `from`, unless it already flees
 * (free or from the hook): free, its swimming state becomes FISH_SHADOW_FLEEING, hooked, its
 * hook state FISH_SHADOW_HOOK_FLEEING. It starts fading (alpha 0x1e), its frames start again,
 * it turns away from `from` (a shadow with the fin to yaw 0), and its splash at the water's
 * surface is its effect (kept for the size classes 0-7). Whether it flees now. */
int FishShadow_Flee(FishShadow *fish, const Vec3 *from)
{
    if (fish == NULL) {
        return 0;
    }
    if (fish->behaviour == FISH_SHADOW_FLEEING || fish->hook_state == FISH_SHADOW_HOOK_FLEEING ||
        fish->state != FISH_SHADOW_SHOWN) {
        return 0;
    }
    if (fish->hooked == 0) {
        fish->behaviour = FISH_SHADOW_FLEEING;
    } else {
        fish->hook_state = FISH_SHADOW_HOOK_FLEEING;
    }
    fish->alpha = FISH_STATE_ALPHA_FLEE;
    fish->unk_13c = 0;
    Vec3 at = fish->position;
    if (fish->has_fin) {
        fish->yaw = 0;
    } else {
        fish->yaw = Vec_YawTo(from, &at);
    }
    int effect = fish_state_flee_effect(fish->size);
    Vec3 splash = at;
    splash.y = data_020c904c;
    if (effect >= 0) {
        fish->effect = EffectSystem_StartKind(effect, &splash, NULL, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov003_02228150, FishShadow_Flee)

/* func_ov003_022282b8: the shadow (none: 0) flees from `from` (FishShadow_Flee) unless it is
 * hooked; whether it did. */
int FishShadow_TryFlee(FishShadow *fish, const Vec3 *from)
{
    if (fish == NULL) {
        return 0;
    }
    if (fish->hooked == 1) {
        return 0;
    }
    return FishShadow_Flee(fish, from) != 0;
}
CLEAN_AS(func_ov003_022282b8, FishShadow_TryFlee)

/* func_ov003_022282e8: whether player `player` near the shadow (FishShadow_PlayerNear) startles
 * it: at once with the player's flag 9 set, else after running near it for six more frames; the
 * frames start again whenever the player is not near or not running. */
int FishShadow_Startled(FishShadowProcess *self, int player, FishShadow *fish)
{
    u8 *wait = fish_state_scare_wait(fish);
    if (!FishShadow_PlayerNear(self, &fish->position, player)) {
        *wait = FISH_STATE_SCARE_FRAMES;
        return 0;
    }
    if (FieldActor_PlayerFlag9(player)) {
        return 1;
    }
    if (!FishShadow_PlayerRunning(player)) {
        *wait = FISH_STATE_SCARE_FRAMES;
        return 0;
    }
    if (*wait != 0) {
        *wait -= 1;
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov003_022282e8, FishShadow_Startled)

/* func_ov003_02228348: a shadow startled by the player at this console (FishShadow_Startled)
 * flees from where that player's frame began (FishShadow_TryFlee); whether it was startled and
 * the player has an actor. */
int FishShadow_CheckPlayerScare(FishShadowProcess *self, FishShadow *fish)
{
    if (!FishShadow_Startled(self, FISH_STATE_THIS_CONSOLE, fish)) {
        return 0;
    }
    const Vec3 *from = PlayerActorOps_StartPosition(FISH_STATE_THIS_CONSOLE);
    if (from == NULL) {
        return 0;
    }
    FishShadow_TryFlee(fish, from);
    return 1;
}
CLEAN_AS(func_ov003_02228348, FishShadow_CheckPlayerScare)

/* func_ov003_02228380: a fully shown shadow (alpha 0x1f) checks the player at this console
 * (FishShadow_CheckPlayerScare); a fading one without the fin fades one step. Once faded (alpha
 * 1 or less) it is fully shown again and taken away (the fin put away when the hook's landing
 * gave 2 and it has one). */
void FishShadow_StepFade(FishShadowProcess *self, FishShadow *fish, int index)
{
    u8 alpha = fish->alpha;
    if (alpha == FISH_STATE_ALPHA_FULL) {
        FishShadow_CheckPlayerScare(self, fish);
    } else if (!fish->has_fin) {
        fish->alpha = (u8) (alpha - 1);
    }
    if (fish->alpha > 1) {
        return;
    }
    fish->alpha = FISH_STATE_ALPHA_FULL;
    if (FishShadowHook_TryLand(fish) == 2 && fish->has_fin) {
        FishShadow_ReleaseFin(self);
    }
    FishShadow_Reset(self, index);
}
CLEAN_AS(func_ov003_02228380, FishShadow_StepFade)

/* func_ov003_022283e4: the shown shadow's fading (FishShadow_StepFade), then its view check
 * (FishShadow_CheckInView). */
void FishShadow_StepShownChecks(FishShadowProcess *self, FishShadow *fish, int index)
{
    FishShadow_StepFade(self, fish, index);
    FishShadow_CheckInView(self, fish, index);
}
CLEAN_AS(func_ov003_022283e4, FishShadow_StepShownChecks)

/* func_ov003_02228400: the shadows within `reach` of `point` along the ground flee from it
 * (FishShadow_TryFlee); whether one did. */
int FishShadow_ScareNear(const Vec3 *point, int reach)
{
    int found = 0;
    for (int i = 0; i < FISH_SHADOW_COUNT; i++) {
        FishShadow *fish = &data_ov003_0225f76c[i];
        Vec3 at = fish->position;
        if (Vec_DistanceXZ(&at, point) <= reach && FishShadow_TryFlee(fish, point)) {
            found = 1;
        }
    }
    return found;
}
CLEAN_AS(func_ov003_02228400, FishShadow_ScareNear)

/* func_ov003_02228460: the four thrown bottles stopped. */
void FishShadow_StopBottles(FishShadowProcess *self)
{
    (void) self;
    for (int i = 0; i < THROWN_BOTTLE_COUNT; i++) {
        data_ov003_0225f35c[i].state = THROWN_BOTTLE_NONE;
        data_ov003_0225f35c[i].frames = 0;
    }
}
CLEAN_AS(func_ov003_02228460, FishShadow_StopBottles)

/* func_ov003_0222847c: the four players' fish ended (PlayerFish_StepEnd) and their sounds
 * stopped. */
void FishShadow_EndPlayerFish(FishShadowProcess *self)
{
    (void) self;
    for (int i = 0; i < PLAYER_FISH_COUNT; i++) {
        PlayerFish *fish = &data_ov003_0225f4dc[i];
        PlayerFish_StepEnd(fish, (u8) i);
        SoundEmitter_Vfunc10B((SoundEmitter *) (void *) fish->emitter);
    }
}
CLEAN_AS(func_ov003_0222847c, FishShadow_EndPlayerFish)

/* func_ov003_022284a8: every shadow taken away, its pool entry given back and its sounds
 * stopped; the shadow's animation file freed and the "fish_sdw" pool destroyed; the fin put
 * away when a shadow had it, and the "fish_fin" pool destroyed. */
void FishShadow_ReleaseShadows(FishShadowProcess *self)
{
    int had_fin = 0;
    for (int i = 0; i < FISH_SHADOW_COUNT; i++) {
        FishShadow *fish = &data_ov003_0225f76c[i];
        if (fish->has_fin) {
            had_fin = 1;
        }
        FishShadow_Reset(self, i);
        ModelPool_Release(&self->shadows, &fish->slot);
        SoundEmitter_Vfunc10B((SoundEmitter *) (void *) fish->emitter);
        SoundSource_Release(&fish->source);
    }
    Heap_FreeCurrent(self->shadow_file);
    ModelPool_Destroy(&self->shadows);
    if (had_fin) {
        FishShadow_ReleaseFin(self);
    }
    ModelPool_Destroy(&self->fin);
}
CLEAN_AS(func_ov003_022284a8, FishShadow_ReleaseShadows)

/* func_ov003_02228520 (vtable slot 3): the shadows, the players' fish and the bottles
 * released. Done (1). */
int FishShadow_Destroy(FishShadowProcess *self)
{
    FishShadow_ReleaseShadows(self);
    FishShadow_EndPlayerFish(self);
    FishShadow_StopBottles(self);
    return 1;
}
CLEAN_AS(func_ov003_02228520, FishShadow_Destroy)

/* The scale a size class draws a shadow at. */
static Vec3 fish_state_scale(const FishStateSize *size)
{
    Vec3 scale;
    scale.x = (size->scale_x << 12) / 100;
    scale.y = 0x1000;
    scale.z = (size->scale_z << 12) / 100;
    return scale;
}

/* The first material of model resource `model` (NNSG3dResMdl: its materials' block at the
 * offset in word 2, whose dictionary's first entry gives the material's offset). */
static u8 *fish_state_first_material(u8 *model)
{
    u8 *materials = model + *(u32 *) (void *) (model + 0x08);
    u8 *entries = materials + *(u16 *) (void *) (materials + 0x0a);
    return materials + *(u32 *) (void *) (entries + 0x08);
}

/* A material's polygon attributes (GX's POLYGON_ATTR) and their alpha. */
#define FISH_STATE_MATERIAL_ATTRIBUTES 0x0c
#define FISH_STATE_ALPHA_SHIFT 16
#define FISH_STATE_ALPHA_KEEP 0xffe0ffffu

/* func_ov003_0222853c (vtable slot 9): each shown shadow drawn at its size class's scale, the
 * first material taking its alpha (when above 0), and the fin drawn with it at the same scale.
 * Done (1). */
int FishShadow_Draw(void)
{
    for (int i = 0; i < FISH_SHADOW_COUNT; i++) {
        FishShadow *fish = &data_ov003_0225f76c[i];
        if (fish->state != FISH_SHADOW_SHOWN) {
            continue;
        }
        const FishStateSize *size = &data_ov003_0223c014[fish->size];
        Vec3 scale = fish_state_scale(size);
        u8 *material = fish_state_first_material(fish->model.object.model);
        int alpha = fish->alpha;
        if (material != NULL && alpha > 0) {
            u32 *attributes = (u32 *) (void *) (material + FISH_STATE_MATERIAL_ATTRIBUTES);
            *attributes &= FISH_STATE_ALPHA_KEEP;
            *attributes |= (u32) (alpha & 0x1f) << FISH_STATE_ALPHA_SHIFT;
        }
        AnimatedModel_Draw(fish_state_model(&fish->model), &scale);
        if (fish->has_fin) {
            Vec3 fin_scale = fish_state_scale(size);
            AnimatedModel_Draw(fish_state_model(&data_ov003_0225f220.model), &fin_scale);
        }
    }
    return 1;
}
CLEAN_AS(func_ov003_0222853c, FishShadow_Draw)

/* func_ov003_02228618: the players' fish kept with the other consoles' in a session
 * (PlayerFish_Sync), then each player's fish and thrown bottle stepped. */
void FishShadow_StepPlayers(FishShadowProcess *self)
{
    if (Session_IsLinked(data_020ccf94)) {
        PlayerFish_Sync(self);
    }
    for (int i = 0; i < PLAYER_FISH_COUNT; i++) {
        PlayerFish_Update(&data_ov003_0225f4dc[i], (u8) i);
        ThrownBottle_Step(data_ov003_0225f0b4, &data_ov003_0225f35c[i]);
    }
}
CLEAN_AS(func_ov003_02228618, FishShadow_StepPlayers)

/* func_ov003_0222866c (vtable slot 6): each shadow's frame (FishShadow_Update), the placing of
 * this frame allowed again, and the players' fish and bottles stepped. Done (1). */
int FishShadow_Step(FishShadowProcess *self)
{
    for (int i = 0; i < FISH_SHADOW_COUNT; i++) {
        FishShadow_Update(self, &data_ov003_0225f76c[i], i);
    }
    self->unk_84 = 0;
    FishShadow_StepPlayers(self);
    return 1;
}
CLEAN_AS(func_ov003_0222866c, FishShadow_Step)

/* func_ov003_022286ac: model holder `object` placed at `at` bent over the globe, tilted about x
 * by the bend and turned about y by `yaw` (built in data_021fbe48). */
void FishShadow_PlaceModel(FishShadowProcess *self, const Vec3 *at, ModelObject *object, int yaw)
{
    (void) self;
    Vec3 bent;
    int tilt = Globe_Bend(&bent, at);
    Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
    Mtx43_RotateX(&data_021fbe48, tilt);
    Mtx43_RotateY(&data_021fbe48, yaw);
    memcpy(object->unk_64, &data_021fbe48, sizeof(Mtx43));
}
CLEAN_AS(func_ov003_022286ac, FishShadow_PlaceModel)

/* func_ov003_022286f4: the fin follows shadow `fish`: its position and yaw, its animation's
 * speed and a frame one past the whole frame of the shadow's; both models placed, both
 * animations stepped, and the fin's texture animation stepped.
 * QUIRK: the fin's frame is the shadow's whole frame plus one, kept in 16 bits. */
void FishShadow_MoveFin(FishShadowProcess *self, FishShadow *fish)
{
    FishFin *fin = &data_ov003_0225f220;
    FishStateFinPlace *place = fish_state_fin_place(fin);
    place->position = fish->position;
    int yaw = fish->yaw;
    place->yaw = (s16) yaw;
    fin->model.frames.speed = fish->model.frames.speed;
    u16 whole = (u16) ((u32) fish->model.frames.frame >> 12);
    fin->model.frames.frame = (fx32) ((u32) (u16) (whole + 1) << 12);
    FishShadow_PlaceModel(self, &fish->position, &fin->model.object, yaw);
    AnimatedModel_StepFrames(fish_state_model(&fish->model));
    AnimatedModel_StepFrames(fish_state_model(&fin->model));
    FrameCtrl_Step(&fin->anim.ctrl);
    fin->anim.anim->frame = fin->anim.ctrl.frame;
}
CLEAN_AS(func_ov003_022286f4, FishShadow_MoveFin)

/* func_ov003_02228784: state 3's update: the shadow swims (FishShadow_StepShown) and is moved
 * against walls from where it was (its size class's radius), its model placed at the surface
 * and stepped (with the fin, when it has one), then its fading and view check
 * (FishShadow_StepShownChecks). */
void FishShadow_UpdateShown(FishShadowProcess *self, FishShadow *fish, int index)
{
    FishShadow_StepShown(fish);
    CollisionQuery_Move(&fish->contacts, &fish->position, &fish->last_position, fish->yaw,
                        (data_ov003_0223c014[fish->size].radius << 12) / 10, NULL, 0xb);
    fish->last_position = fish->position;
    Vec3 at = fish->position;
    at.y = FISH_STATE_SURFACE_Y;
    FishShadow_PlaceModel(self, &at, &fish->model.object, fish->yaw);
    if (fish->has_fin) {
        FishShadow_MoveFin(self, fish);
    } else {
        AnimatedModel_StepFrames(fish_state_model(&fish->model));
    }
    FishShadow_StepShownChecks(self, fish, index);
}
CLEAN_AS(func_ov003_02228784, FishShadow_UpdateShown)

/* func_ov003_02228848: state 3's entry: nothing. */
void FishShadow_EnterShown(void) {}
CLEAN_AS(func_ov003_02228848, FishShadow_EnterShown)

/* func_ov003_0222884c: state 4's update: in the camera's view again, the shadow is shown again
 * (FISH_SHADOW_SHOWN, set without its entry function) without a timer; otherwise its timer
 * counts down and, at 0, it is taken away (the fin put away with it). Nothing while there is no
 * camera or no timer. */
void FishShadow_UpdateAway(FishShadowProcess *self, FishShadow *fish, int index)
{
    if (data_021c67a4 == 0) {
        return;
    }
    Vec3 camera = data_021c67d0;
    if (FishShadow_InBox(&fish->position, &camera, FISH_STATE_VIEW_X, FISH_STATE_VIEW_AHEAD, FISH_STATE_VIEW_BEHIND)) {
        fish->state = FISH_SHADOW_SHOWN;
        fish->timer = -1;
        return;
    }
    int timer = fish->timer;
    if (timer == -1) {
        return;
    }
    if (timer == 0) {
        if (fish->has_fin) {
            FishShadow_ReleaseFin(self);
        }
        FishShadow_Reset(self, index);
    } else {
        fish->timer = timer - 1;
    }
}
CLEAN_AS(func_ov003_0222884c, FishShadow_UpdateAway)

/* func_ov003_022288e0: state 4's entry: nothing. */
void FishShadow_EnterAway(void) {}
CLEAN_AS(func_ov003_022288e0, FishShadow_EnterAway)

/* func_ov003_022288e4: state 2's update. A shadow with the fin waits for the fin to load
 * (FishFin_Load, in the "fish_fin" pool); then it moves (FishShadow_StepPlacing) and is shown
 * (FISH_SHADOW_SHOWN, set without its entry function) fully, its model and the fin's placed at
 * its position. Another moves and is shown once it has moved more than 3 frames, or when its
 * swimming state is 3; kind 0xb's sense starts cleared. */
void FishShadow_UpdateAppearing(FishShadowProcess *self, FishShadow *fish)
{
    if (fish->has_fin) {
        FishFin *fin = &data_ov003_0225f220;
        if (FishFin_Load(fin, &self->fin)) {
            FishShadow_StepPlacing(fish);
            fish->state = FISH_SHADOW_SHOWN;
            fish->alpha = FISH_STATE_ALPHA_FULL;
            int yaw = fish->yaw;
            FishShadow_PlaceModel(self, &fish->position, &fish->model.object, yaw);
            FishShadow_PlaceModel(self, &fish->position, &fin->model.object, yaw);
        }
        return;
    }
    FishShadow_StepPlacing(fish);
    if (fish->unk_201 > 3 || fish->behaviour == 3) {
        fish->state = FISH_SHADOW_SHOWN;
        fish->alpha = FISH_STATE_ALPHA_FULL;
        fish->unk_201 = 0;
        FishShadow_PlaceModel(self, &fish->position, &fish->model.object, fish->yaw);
        if (fish->kind == FISH_STATE_SENSE_KIND) {
            FishShadow_ResetSense(fish);
        }
    }
}
CLEAN_AS(func_ov003_022288e4, FishShadow_UpdateAppearing)

/* func_ov003_022289b0: state 2's entry: nothing. */
void FishShadow_EnterAppearing(void) {}
CLEAN_AS(func_ov003_022289b0, FishShadow_EnterAppearing)

/* func_ov003_022289b4: state 1's update: once the place it was put at is in the camera's view,
 * the shadow goes to state 2 (FishShadow_SetState2) and, with the fin, the fin starts loading
 * (FishShadow_TakeFin). */
void FishShadow_UpdatePlaced(FishShadowProcess *self, FishShadow *fish, int index)
{
    if (data_021c67a4 == 0) {
        return;
    }
    Vec3 camera = data_021c67d0;
    if (FishShadow_InBox(&fish->unk_12c, &camera, FISH_STATE_VIEW_X, FISH_STATE_VIEW_AHEAD, FISH_STATE_VIEW_BEHIND)) {
        FishShadow_SetState2(self, index);
        if (fish->has_fin) {
            FishShadow_TakeFin(self);
        }
    }
}
CLEAN_AS(func_ov003_022289b4, FishShadow_UpdatePlaced)

/* func_ov003_02228a1c: state 1's entry: nothing. */
void FishShadow_EnterPlaced(void) {}
CLEAN_AS(func_ov003_02228a1c, FishShadow_EnterPlaced)

/* func_ov003_02228a20: state 0's update: one shadow a frame (the process's unk_84) waiting to be
 * placed in its group, and not hooked, is placed (FishShadow_Place) and, when it was, set to
 * state 1 (FishShadow_SetState). */
void FishShadow_UpdateNone(FishShadowProcess *self, FishShadow *fish, int index)
{
    if (self->unk_84 != 0) {
        return;
    }
    int group;
    if (fish->group_state == FISH_SHADOW_WAIT_GROUP0) {
        group = FISH_SHADOW_IN_GROUP0;
    } else if (fish->group_state == FISH_SHADOW_WAIT_GROUP1) {
        group = FISH_SHADOW_IN_GROUP1;
    } else {
        return;
    }
    if (fish->hooked != 0) {
        return;
    }
    if (FishShadow_Place(self, fish, group)) {
        FishShadow_SetState(self, FISH_SHADOW_PLACED, fish, index);
    }
    self->unk_84 = 1;
}
CLEAN_AS(func_ov003_02228a20, FishShadow_UpdateNone)
