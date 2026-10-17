/* Overlay 3's animated models of the growth-line codes of the town's map (main/map_item.h),
 * kept in the tile events' process (tile_event.h) at 0x4b20 (made by func_ov003_02223b8c,
 * destroyed by func_ov003_02223b34):
 *
 *   - twenty models (0x14c bytes each): two sets of four for the codes of line 0x57-0x5b and
 *     most others (by the tile's parity), four for the eight-code lines 0x2f-0x56 and 0x69,
 *     four for 0x5d-0x61 and 0x6a-0x6d, four for 0xc8-0xcf, one per growth stage
 *     (func_ov003_02223870 picks one), and three more the loops here leave alone;
 *   - five requests (0x18 bytes) that main's tile changes of the hitting kinds leave: when the
 *     model for the code can play (func_ov003_0222378c), it starts at the tile in one of eight
 *     modes and what the code drops falls (as tile events of kinds 5, 6 and 7); otherwise the
 *     drop happens without it (GrowthModel_SkipRequest);
 *   - their files: for each mode and growth stage a joint animation file, from the paths of
 *     data_ov003_0223bcc4.
 *
 * While it plays, modes 4-7 fade the model out and start two parts each (the table at
 * data_ov003_0223cfa0, by func_ov003_02223c7c and func_ov003_02223d14); modes 0, 1, 2 and the
 * others start them once. Which object each mode shows is not read from this code. */
#ifndef CLEAN_OV003_GROWTH_MODEL_H
#define CLEAN_OV003_GROWTH_MODEL_H

#include "autoload_2/vector.h"
#include "main/sound_emitter.h"
#include "main/tile_changes.h" /* TileChangesTile */
#include "types.h"

#define GROWTH_MODEL_MODES 8
#define GROWTH_MODEL_STAGES 4

/* A part func_ov003_02223c7c or func_ov003_02223d14 started, as far as it is read here. */
typedef struct GrowthModelPart {
    u8 unk_00[0x0d];
    u8 unk_0d; /* 0x0d: set to 0x1a by mode 2 */
} GrowthModelPart;

typedef struct GrowthModel {
    int state;               /* 0x000: 1 while it plays, 0 when free */
    int player;              /* 0x004: the session slot whose request started it */
    u8 model[0xb4];          /* 0x008: an animated model (animated_model.h, without the blend) */
    u8 unk_0bc[4];           /* 0x0bc */
    Vec3 position;           /* 0x0c0: the tile's centre */
    TileChangesTile tile;    /* 0x0cc: -1, -1 when free */
    int mode;                /* 0x0d4: 0-7; 8 once its files were released */
    fx32 fade;               /* 0x0d8: 31.0 at the start; modes 4-7 lower it */
    int parts;               /* 0x0dc: how many times parts were started */
    SoundEmitter sound;      /* 0x0e0 */
    u8 unk_124[0x14];        /* 0x124 */
    int unk_138[3];          /* 0x138: -1 when reset */
    GrowthModelPart *part_a; /* 0x144 */
    GrowthModelPart *part_b; /* 0x148 */
} GrowthModel;

/* A request a tile change leaves (func_ov003_02223a04 runs the pending ones). */
typedef struct GrowthModelRequest {
    int pending;          /* 0x00 */
    int player;           /* 0x04: the session slot */
    TileChangesTile tile; /* 0x08 */
    int mode;             /* 0x10 */
    int quiet;            /* 0x14: another set of sounds */
} GrowthModelRequest;

typedef struct GrowthModelFiles {
    u8 *files[GROWTH_MODEL_MODES][GROWTH_MODEL_STAGES];   /* 0x00: loaded from main's heap */
    void *anims[GROWTH_MODEL_MODES][GROWTH_MODEL_STAGES]; /* 0x80: the first joint animation of each */
} GrowthModelFiles;

typedef struct GrowthModels {
    GrowthModel sets[3][4];         /* 0x0000 */
    GrowthModel line_5d[4];         /* 0x0f90 */
    GrowthModel unk_14c0[3];        /* 0x14c0 */
    GrowthModel line_c8[4];         /* 0x18a4 */
    GrowthModelRequest requests[5]; /* 0x1dd4 */
    GrowthModelFiles files;         /* 0x1e4c */
} GrowthModels;

/* The node hook's view of NitroSystem's render state (NNSG3dRS). */
typedef struct GrowthModelRenderObject {
    u8 unk_00[0x2c];
    struct GrowthModel *user; /* 0x2c: the model the hook was set up with */
} GrowthModelRenderObject;

typedef struct GrowthModelRenderState {
    const u8 *command;                      /* 0x00: the command being run: byte 1 is its node */
    GrowthModelRenderObject *render_object; /* 0x04 */
    u8 unk_08[0xb0];                        /* 0x08 */
    int *unk_b8;                            /* 0xb8: a word the hook clears */
} GrowthModelRenderState;

int GrowthModel_SkipRequest(GrowthModelRequest *request);
int GrowthModel_FilePath(GrowthModelFiles *files, int mode, int stage);
void GrowthModel_FreeFiles(GrowthModelFiles *files);
void GrowthModel_LoadFiles(GrowthModelFiles *files);
void GrowthModel_NodeHook(GrowthModelRenderState *state);
void GrowthModel_Reset(GrowthModel *model);
void GrowthModel_Start(GrowthModel *model, int player, const TileChangesTile *tile, int mode, int stage, int quiet);
void GrowthModel_DropAt(GrowthModel *model, u16 *item);
void GrowthModel_Drop(u16 *code, int slot, const TileChangesTile *tile);
void GrowthModel_DropOne(u16 *code, int slot, const TileChangesTile *tile);
void GrowthModel_DropKind7(int slot, const TileChangesTile *tile);
void GrowthModel_DropThree(u16 *code, int slot, const TileChangesTile *tile);
int GrowthModel_PlayerSide(int slot, const Vec3 *point);
void GrowthModel_Hit(GrowthModel *model, int quiet);
void GrowthModel_Release(GrowthModel *model);
void GrowthModel_Draw(GrowthModel *model);
void GrowthModel_Update(GrowthModel *model);

#endif
