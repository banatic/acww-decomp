/* Overlay 3's animated models of the growth-line codes (growth_model.h). */
#include "growth_model.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "itcm/vector.h" /* Vec_Add */
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor.h"       /* Actor */
#include "main/actor_table.h" /* Position, Position_Tile */
#include "main/animated_model.h"
#include "main/globe.h"
#include "main/map_item.h"
#include "main/model_object.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/scene_lights.h"
#include "main/session.h"
#include "main/session_players.h"
#include "main/tile_requests.h"
#include "tile_event.h"

static_assert(sizeof(GrowthModel) == 0x14c, "a model");
static_assert(offsetof(GrowthModel, position) == 0xc0, "position");
static_assert(offsetof(GrowthModel, mode) == 0xd4, "mode");
static_assert(offsetof(GrowthModel, sound) == 0xe0, "sound");
static_assert(offsetof(GrowthModel, unk_138) == 0x138, "unk_138");
static_assert(offsetof(GrowthModel, part_a) == 0x144, "part_a");
static_assert(sizeof(GrowthModelRequest) == 0x18, "a request");
static_assert(offsetof(GrowthModels, line_5d) == 0xf90, "line_5d");
static_assert(offsetof(GrowthModels, line_c8) == 0x18a4, "line_c8");
static_assert(offsetof(GrowthModels, requests) == 0x1dd4, "requests");
static_assert(offsetof(GrowthModels, files) == 0x1e4c, "files");
static_assert(offsetof(GrowthModelFiles, anims) == 0x80, "anims");
static_assert(offsetof(GrowthModelRenderState, unk_b8) == 0xb8, "unk_b8");
static_assert(offsetof(AnimatedModel, frames) == 0x9c, "frames");

/* The tile events' process, which holds the models at 0x4b20. */
extern TileEventProcess *data_ov003_0223cf70;
/* The heap the files are loaded into. */
extern Heap *data_ov003_0223cf78;
/* The session. */
extern NetSession *data_020ccf94;
/* The parts' table (func_ov003_02223c7c, func_ov003_02223d14). */
extern u8 data_ov003_0223cfa0[];
/* The joint animation files' paths, by mode and stage (NULL for none). */
extern const char *const data_ov003_0223bcc4[GROWTH_MODEL_MODES][GROWTH_MODEL_STAGES];
/* The offsets from a tile's centre where drops start: [0] and [1] for the one-drop codes by
 * side (GrowthModel_PlayerSide), [0] (three) and [2] (two) for the three-drop ones. */
extern const Vec3 *const data_ov003_02239f5c[3];
/* The item the three-drop codes drop, by line (MapItem_EightLine). */
extern const u16 data_ov003_02236688[];
/* The matrix the model is drawn with (built here in place). */
extern Mtx43 data_021fbe48;

/* The first joint animation of a file, as NitroSystem finds it. */
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern u8 *func_02107b44(void *set, u32 index);
/* NitroSystem: the emission colour of material `material` of a model. */
extern void NNS_G3dMdlSetMdlEmi(u8 *model, int material, unsigned short colour);
/* Two settings of all a model's materials: a value 0-31 (the fade's whole part), and a
 * polygon ID. */
extern void func_0210744c(u8 *model, int value);
extern void func_02107494(u8 *model, int id);
/* Starts a part of the table for the model's mode, `stage` and `parts`, at `tile`. */
extern GrowthModelPart *func_ov003_02223c7c(void *parts, int mode, int stage, int item, TileChangesTile *tile, int count);
extern GrowthModelPart *func_ov003_02223d14(void *parts, int mode, int stage, int item, TileChangesTile *tile, int count);

/* The sounds. */
#define GROWTH_MODEL_VOLUME 0x7f
/* What a released model's mode is. */
#define GROWTH_MODEL_RELEASED 8
/* The model's node the hook hides in modes 0-3. */
#define GROWTH_MODEL_HIDDEN_NODE 2

static AnimatedModel *growth_model_animated(GrowthModel *model)
{
    return (AnimatedModel *) (void *) model->model;
}

static GrowthModels *growth_models(void)
{
    return (GrowthModels *) (void *) data_ov003_0223cf70->member_4b20;
}

/* The item at tile (x, z) of `map`, layer 0. */
static u16 *growth_model_item(AcreMap *map, int x, int z)
{
    int acre_x = x >> 4;
    int acre_z = z >> 4;
    return AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x & 0xf, z & 0xf, 0);
}

/* func_ov003_02222af0: a request whose model cannot play: unless its mode is 1, when the tile
 * change of the request's slot is at the tile, what the code there drops falls
 * (GrowthModel_Drop, on the town's map); then that tile change is finished and the request is
 * no longer pending. Always 0. */
int GrowthModel_SkipRequest(GrowthModelRequest *request)
{
    if (request->mode != 1) {
        TileChangesTile at = request->tile;
        if (TileChanges_FindOwnAt((u32) request->player, &at, 0) >= 0) {
            AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
            if (map != NULL) {
                u16 *item = growth_model_item(map, request->tile.x, request->tile.z);
                if (item != NULL) {
                    TileChangesTile on = request->tile;
                    GrowthModel_Drop(item, request->player, &on);
                }
            }
        }
    }
    TileChangesTile tile = request->tile;
    TileChanges_FinishOwnAt(&tile, request->player, 0);
    request->pending = 0;
    return 0;
}
CLEAN_AS(func_ov003_02222af0, GrowthModel_SkipRequest)

/* func_ov003_02222b68: the path of the joint animation file of `mode` and `stage` (the
 * address, as the game keeps it), or 0. */
int GrowthModel_FilePath(GrowthModelFiles *files, int mode, int stage)
{
    (void) files;
    return (int) (intptr_t) data_ov003_0223bcc4[mode][stage];
}
CLEAN_AS(func_ov003_02222b68, GrowthModel_FilePath)

/* func_ov003_02222b78: every file loaded freed from the heap. */
void GrowthModel_FreeFiles(GrowthModelFiles *files)
{
    Heap *heap = data_ov003_0223cf78;
    for (int mode = 0; mode < GROWTH_MODEL_MODES; mode++) {
        for (int stage = 0; stage < GROWTH_MODEL_STAGES; stage++) {
            if (files->files[mode][stage] != NULL) {
                Heap_Free(heap, files->files[mode][stage]);
                files->files[mode][stage] = NULL;
            }
        }
    }
}
CLEAN_AS(func_ov003_02222b78, GrowthModel_FreeFiles)

/* func_ov003_02222bc0: each file with a path loaded into the heap (aligned to 4) with its first
 * joint animation; NULL for the others. */
void GrowthModel_LoadFiles(GrowthModelFiles *files)
{
    for (int mode = 0; mode < GROWTH_MODEL_MODES; mode++) {
        for (int stage = 0; stage < GROWTH_MODEL_STAGES; stage++) {
            const char *path = (const char *) (intptr_t) GrowthModel_FilePath(files, mode, stage);
            if (path != NULL) {
                files->files[mode][stage] = RomFile_Load(path, data_ov003_0223cf78, 4, NULL);
                files->anims[mode][stage] = func_02107b44(NNS_G3dGetJntAnmSet(files->files[mode][stage]), 0);
            } else {
                files->files[mode][stage] = NULL;
                files->anims[mode][stage] = NULL;
            }
        }
    }
}
CLEAN_AS(func_ov003_02222bc0, GrowthModel_LoadFiles)

/* func_ov003_02222c34 (the hook func_ov003_02223580 sets on each model): at node 2, in modes
 * 0-3, the render state's word at 0xb8 is cleared. */
void GrowthModel_NodeHook(GrowthModelRenderState *state)
{
    GrowthModel *model = state->render_object->user;
    if (state->command[1] == GROWTH_MODEL_HIDDEN_NODE && (u32) model->mode <= 3) {
        *state->unk_b8 = 0;
    }
}
CLEAN_AS(func_ov003_02222c34, GrowthModel_NodeHook)

/* func_ov003_02222c68: the model free: not playing, no tile, no parts. */
void GrowthModel_Reset(GrowthModel *model)
{
    model->state = 0;
    model->fade = 0;
    model->tile.x = -1;
    model->tile.z = -1;
    for (int i = 0; i < 3; i++) {
        model->unk_138[i] = -1;
    }
    model->part_a = NULL;
    model->part_b = NULL;
}
CLEAN_AS(func_ov003_02222c68, GrowthModel_Reset)

/* func_ov003_02222cac: the model starts at `tile` for `player`: the joint animation of `mode`
 * and `stage` from the start at speed 1.0, once unless the mode is 2 (attached again when the
 * model had been released); at the tile's centre, faded in fully, no parts yet; then
 * GrowthModel_Hit.
 * QUIRK: the town's map is asked for first and not used. */
void GrowthModel_Start(GrowthModel *model, int player, const TileChangesTile *tile, int mode, int stage, int quiet)
{
    AcreMap_Town();
    AnimatedModel *animated = growth_model_animated(model);
    AnimatedModel_Start(animated, (const u8 *) growth_models()->files.anims[mode][stage], mode != 2, 0x1000, 0, 0);
    if (model->mode == GROWTH_MODEL_RELEASED) {
        AnimatedModel_Attach(animated);
    }
    model->mode = mode;
    model->player = player;
    model->tile = *tile;
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    model->position = centre;
    model->fade = 0x1f000;
    model->parts = 0;
    GrowthModel_Hit(model, quiet);
}
CLEAN_AS(func_ov003_02222cac, GrowthModel_Start)

/* func_ov003_02222d68: what `item` drops at the model's tile falls, for its player. */
void GrowthModel_DropAt(GrowthModel *model, u16 *item)
{
    TileChangesTile tile = model->tile;
    GrowthModel_Drop(item, model->player, &tile);
}
CLEAN_AS(func_ov003_02222d68, GrowthModel_DropAt)

/* func_ov003_02222d8c: what the code at `tile` drops falls, for the session slot `slot`: lines
 * 0x2f-0x5b and 0xc8-0xcf at their last stage (MapItem_IsGrown) drop three
 * (GrowthModel_DropThree); 0x67 and 0x6b, when main lets items drop, a kind 7 event
 * (GrowthModel_DropKind7); the other codes of 0x66-0x68 and 0x6a-0x6c one
 * (GrowthModel_DropOne); other codes nothing. (Also main's TileChanges_Replace.) */
void GrowthModel_Drop(u16 *code, int slot, const TileChangesTile *tile)
{
    u16 id = *code;
    if ((id >= 0x2f && id <= 0x56) || (id >= 0xc8 && id <= 0xcf) || (id >= 0x57 && id <= 0x5b)) {
        if (!MapItem_IsGrown(code)) {
            return;
        }
        TileChangesTile at = *tile;
        GrowthModel_DropThree(code, slot, &at);
        return;
    }
    if (id == 0x67 || id == 0x6b) {
        if (TileRequests_ItemDropAllowed() == 0) {
            return;
        }
        TileChangesTile at = *tile;
        GrowthModel_DropKind7(slot, &at);
        return;
    }
    if ((id >= 0x66 && id <= 0x68) || (id >= 0x6a && id <= 0x6c)) {
        TileChangesTile at = *tile;
        GrowthModel_DropOne(code, slot, &at);
    }
}
CLEAN_AS(func_ov003_02222d8c, GrowthModel_Drop)

/* func_ov003_02222e24: with a tile change of `slot` tagged 0 (TileChanges_FindByTag), its item
 * falls from the tile's centre plus the offset of the player's side (GrowthModel_PlayerSide)
 * of table [0] for codes 0x66-0x68, [1] for 0x6a-0x6c, to that change's tile: as kind 6 for
 * codes 0x66 and 0x6a, else kind 5.
 * REQUIRES: `code` is one of 0x66-0x68 and 0x6a-0x6c (as GrowthModel_Drop hands it); for other
 * codes the original reads an offset table it never set. */
void GrowthModel_DropOne(u16 *code, int slot, const TileChangesTile *tile)
{
    int index = TileChanges_FindByTag((u8) slot, 0);
    if (index < 0) {
        return;
    }
    u16 id = *code;
    const Vec3 *offsets;
    int sideways;
    if (id >= 0x66 && id <= 0x68) {
        offsets = data_ov003_02239f5c[0];
        sideways = id == 0x66;
    } else {
        offsets = data_ov003_02239f5c[1];
        sideways = id == 0x6a;
    }
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    const Vec3 *offset = offsets + GrowthModel_PlayerSide(slot, &centre);
    const TileChange *change = (const TileChange *) (uintptr_t) TileChanges_At(index);
    Vec3 from = {centre.x + offset->x, centre.y + offset->y, centre.z + offset->z};
    u16 packed = change->tile;
    TileChangesTile to = {packed >> 8, packed & 0xff};
    if (!sideways) {
        TileEvent_StartKind5(slot, change->item, &to, &from, 0, 0);
    } else {
        TileEvent_StartKind6(slot, change->item, &to, &from, 0);
    }
}
CLEAN_AS(func_ov003_02222e24, GrowthModel_DropOne)

/* func_ov003_02222f0c: unless the session is linked or flag 1 of the current player record is
 * set, item 0x1569 falls as a kind 7 event from the tile's centre plus the offset of the
 * player's side of table [0]. */
void GrowthModel_DropKind7(int slot, const TileChangesTile *tile)
{
    if (Session_IsLinked(data_020ccf94)) {
        return;
    }
    if (PlayerRecord_TestFlag(PlayerRecords_Current(), 1) != 0) {
        return;
    }
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);
    const Vec3 *offset = &data_ov003_02239f5c[0][GrowthModel_PlayerSide(slot, &centre)];
    Vec3 from;
    Vec_Add(&from, &centre, offset);
    TileChangesTile at = *tile;
    TileEvent_StartKind7(slot, 0x1569, &at, &from);
}
CLEAN_AS(func_ov003_02222f0c, GrowthModel_DropKind7)

/* func_ov003_02222f8c: drops fall as kind 5 events from the tile's centre plus each offset of a
 * table: code 0xcc two of item 0x1548 (table [2]), 0x5b three of 0x14b8, other codes three of
 * the item of their line (data_ov003_02236688). Drop i goes to the tile of the tile change of
 * `slot` tagged i, with angle 0; without one, to the tile under its start, with angle 1; its
 * extra is i. */
void GrowthModel_DropThree(u16 *code, int slot, const TileChangesTile *tile)
{
    Vec3 centre;
    AcreTile_TileCentre(&centre, (u32) tile->x, (u32) tile->z);

    const Vec3 *offset;
    int count;
    u16 item;
    switch (*code) {
        case 0xcc:
            offset = data_ov003_02239f5c[2];
            count = 2;
            item = 0x1548;
            break;
        case 0x5b:
            offset = data_ov003_02239f5c[0];
            count = 3;
            item = 0x14b8;
            break;
        default:
            offset = data_ov003_02239f5c[0];
            count = 3;
            item = data_ov003_02236688[MapItem_EightLine(code)];
            break;
    }

    int to[2] = {0, 0};
    for (int i = 0; i < count; i++, offset++) {
        int index = TileChanges_FindByTag((u8) slot, (u8) i);
        Vec3 from = {centre.x + offset->x, centre.y + offset->y, centre.z + offset->z};
        int unplaced;
        if (index >= 0) {
            const TileChange *change = (const TileChange *) (uintptr_t) TileChanges_At(index);
            to[0] = change->tile >> 8;
            to[1] = change->tile & 0xff;
            unplaced = 0;
        } else {
            Position_Tile(&to[0], &to[1], (const Position *) (const void *) &from);
            unplaced = 1;
        }
        TileChangesTile at = {to[0], to[1]};
        TileEvent_StartKind5(slot, item, &at, &from, (short) unplaced, i);
    }
}
CLEAN_AS(func_ov003_02222f8c, GrowthModel_DropThree)

/* func_ov003_02223078: 1 when the actor of the player of session slot `slot` stands at a
 * smaller x than `point`, else 0 (also without the actor). */
int GrowthModel_PlayerSide(int slot, const Vec3 *point)
{
    const Actor *actor = SessionPlayers_ActorOf(TileRequests_PlayerOf(slot));
    return actor != NULL && actor->position.x < point->x;
}
CLEAN_AS(func_ov003_02223078, GrowthModel_PlayerSide)

/* func_ov003_022230a0: the hit the model shows: in mode 1 nothing drops; in modes 2 and 3 only
 * while a tile change is at the tile in layer 0; otherwise what the code at the tile drops
 * falls (GrowthModel_DropAt) and the player's tile change there is finished. Then a sound:
 * 0x7dc for modes 0, 2 and 3, 0x7d9 for mode 1, none for the others; with `quiet` set 0x855
 * for modes 4-7, else 0x7dd. The model plays from now on. */
void GrowthModel_Hit(GrowthModel *model, int quiet)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    u16 *item = growth_model_item(map, model->tile.x, model->tile.z);
    int drops;
    switch (model->mode) {
        case 1:
            drops = 0;
            break;
        case 2:
        case 3: {
            TileChangesTile at = model->tile;
            drops = TileChanges_FindAt(&at, 0) >= 0;
            break;
        }
        default:
            drops = 1;
            break;
    }
    if (drops) {
        GrowthModel_DropAt(model, item);
        TileChangesTile at = model->tile;
        TileChanges_FinishOwnAt(&at, model->player, 0);
    }

    if (quiet == 0) {
        switch (model->mode) {
            case 0:
            case 2:
            case 3:
                SoundEmitter_PlayB(&model->sound, 0x7dc, GROWTH_MODEL_VOLUME, 0);
                break;
            case 1:
                SoundEmitter_PlayB(&model->sound, 0x7d9, GROWTH_MODEL_VOLUME, 0);
                break;
        }
    } else {
        switch (model->mode) {
            case 4:
            case 5:
            case 6:
            case 7:
                SoundEmitter_PlayB(&model->sound, 0x855, GROWTH_MODEL_VOLUME, 0);
                break;
            default:
                SoundEmitter_PlayB(&model->sound, 0x7dd, GROWTH_MODEL_VOLUME, 0);
                break;
        }
    }
    model->state = 1;
}
CLEAN_AS(func_ov003_022230a0, GrowthModel_Hit)

/* func_ov003_022231e8: the model reset, its model object let go, its sound let go (vtable slot
 * 0x10 of its emitter). */
void GrowthModel_Release(GrowthModel *model)
{
    GrowthModel_Reset(model);
    ModelObject_Release(&growth_model_animated(model)->object);
    SoundEmitter_Vfunc10B(&model->sound);
}
CLEAN_AS(func_ov003_022231e8, GrowthModel_Release)

/* func_ov003_02223208: a playing model drawn at its position bent over the globe, turned by the
 * bend about X; lit by the scene's emission colour. */
void GrowthModel_Draw(GrowthModel *model)
{
    if (model->state != 1) {
        return;
    }
    AnimatedModel *animated = growth_model_animated(model);
    Vec3 bent;
    int tilt = Globe_BendFar(&bent, &model->position);
    Mtx43_Translation(&data_021fbe48, bent.x, bent.y, bent.z);
    Mtx43_RotateX(&data_021fbe48, tilt);
    memcpy(animated->object.unk_64, &data_021fbe48, sizeof(Mtx43));
    AnimatedModel_Draw(animated, NULL);
    NNS_G3dMdlSetMdlEmi(animated->object.model, 0, (unsigned short) SceneLights_EmissionColour());
}
CLEAN_AS(func_ov003_02223208, GrowthModel_Draw)

/* Codes of the four short lines (main/map_item.h), whose stage MapItem_ShortStage gives. */
static int growth_model_short_line(u16 code)
{
    return (code >= 0x2b && code <= 0x2e) || (code >= 0xff && code <= 0x102) || (code >= 0x62 && code <= 0x65) ||
           (code >= 0xd0 && code <= 0xd3);
}

/* Modes 4-7: from frame 17 on the fade drops by `fade_step` a frame (to 0); the parts start at
 * frame 4 the first time and at frame `second` the second time, with sound 0x7ea. */
static int growth_model_fading(GrowthModel *model, u16 frame, fx32 fade_step, u16 second)
{
    if (frame >= 0x11) {
        model->fade -= fade_step;
        if (model->fade < 0) {
            model->fade = 0;
        }
    }
    switch (model->parts) {
        case 0:
            return frame >= 4;
        case 1:
            if (frame >= second) {
                SoundEmitter_PlayB(&model->sound, 0x7ea, GROWTH_MODEL_VOLUME, 0);
                return 1;
            }
            return 0;
        default:
            return 0;
    }
}

/* func_ov003_02223274: a playing model steps its animation; at its end the model is reset.
 * Before that, by mode: modes 4 and 5 fade by 0x2955 and start parts the second time at frame
 * 20, modes 6 and 7 by 0x2627 and at frame 13 (growth_model_fading); mode 3 none; mode 2 at
 * frame 4 the first time, and at other times sets byte 0x0d of its parts to 0x1a; the others at
 * frame 4 the first time. The fade's whole part and the polygon ID 0x33 + this system's player
 * go to the model. Parts start, on the town's map with an item at the tile, at the item's
 * stage (MapItem_ShortStage or MapItem_GrowthStage) when it is above 0. The sound follows the
 * model's position. The animation is made to stop at its end each frame, playing or not
 * (func_ov003_022235d8 makes a model loop while its player keeps at the tile). */
void GrowthModel_Update(GrowthModel *model)
{
    AnimatedModel *animated = growth_model_animated(model);
    if (model->state == 1) {
        AnimatedModel_StepFrames(animated);
        if (FrameCtrl_IsDone(&animated->frames)) {
            GrowthModel_Reset(model);
        } else {
            int start_parts = 0;
            int player = data_020ccf94->local_player;
            u16 frame = (u16) ((u32) animated->frames.frame >> 12);
            switch ((u32) model->mode) {
                case 4:
                case 5:
                    start_parts = growth_model_fading(model, frame, 0x2955, 0x14);
                    break;
                case 6:
                case 7:
                    start_parts = growth_model_fading(model, frame, 0x2627, 0xd);
                    break;
                case 2:
                    if (model->parts == 0 && frame >= 4) {
                        start_parts = 1;
                    } else {
                        if (model->part_a != NULL) {
                            model->part_a->unk_0d = 0x1a;
                        }
                        if (model->part_b != NULL) {
                            model->part_b->unk_0d = 0x1a;
                        }
                    }
                    break;
                case 3:
                    break;
                default:
                    if (model->parts == 0 && frame >= 4) {
                        start_parts = 1;
                    }
                    break;
            }

            func_0210744c(animated->object.model, model->fade >> 12);
            func_02107494(animated->object.model, player + 0x33);

            if (start_parts) {
                AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
                if (map != NULL) {
                    u16 *item = growth_model_item(map, model->tile.x, model->tile.z);
                    if (item != NULL) {
                        int stage = growth_model_short_line(*item) ? MapItem_ShortStage(item) : MapItem_GrowthStage(item);
                        if (stage > 0) {
                            TileChangesTile at = model->tile;
                            model->part_a = func_ov003_02223c7c(data_ov003_0223cfa0, model->mode, stage - 1,
                                                                (int) (intptr_t) item, &at, model->parts);
                            TileChangesTile at2 = model->tile;
                            model->part_b = func_ov003_02223d14(data_ov003_0223cfa0, model->mode, stage - 1,
                                                                (int) (intptr_t) item, &at2, model->parts);
                            model->parts++;
                        }
                    }
                }
            }
        }
        Vec3 at = model->position;
        SoundEmitter_UpdateAtB(&model->sound, &at);
    }
    animated->frames.flags = FRAME_CTRL_ONCE;
}
CLEAN_AS(func_ov003_02223274, GrowthModel_Update)
