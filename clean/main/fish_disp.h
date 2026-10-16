/* The fish display ("fish_disp", the name its pool of heaps is given): a process (the C++ class
 * with vtable data_020dce48, derived from data_020da13c's) that shows up to four fish models,
 * and the state of the fish each of the four players of a session has out (data_020dce10).
 *
 * Models. Overlay 3 takes a model (FishDisp_TakeModel) when a player holds up a fish, sets it
 * each frame (FishDisp_ShowModel: kind, position, scale, rotation) and gives it back
 * (FishDisp_ReleaseModel). A model's kind is:
 *   0-0x37  a fish (items 0x12e8-0x131f): "/fish/0<kind / 16>/fish<kind>.nsbmd", animated by the
 *           .nsbca of the same name;
 *   0x38-0x3a  the models "/fish/03/fish56.nsbmd" to "fish58.nsbmd", not animated;
 *   0x3b    the shadow "/fish/03/fish_shadow.nsbmd" with its .nsbca, drawn with the model's
 *           alpha.
 * Each frame (FishDisp_Execute) a taken model with a kind starts loading into its entry of the
 * pool, a loading one tries to load its files (and stays loading until that works), a shown one
 * moves on its animation and is placed, and a released one is freed. The draw phase
 * (FishDisp_Draw) draws the shown ones at their scale.
 *
 * Players. Main's player message 42 (func_02050884) sets a player's state:
 *   0     with a fish's kind and a point (x, z): overlay 3 then shows it and sets 3;
 *   1, 2  asked by messages 1 and 2; overlay 3 handles them and sets 8;
 *   3     set by overlay 3 while it shows the fish; 6 when it starts with a player in state 3;
 *   8     none (the start);
 *   9     what FishDisp_PlayerState gives for a number that is no player. */
#ifndef CLEAN_MAIN_FISH_DISP_H
#define CLEAN_MAIN_FISH_DISP_H

#include "autoload_2/matrix.h"
#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "types.h"

#define FISH_DISP_MODELS 4
#define FISH_DISP_PLAYERS 4

/* Model kinds (FishModel.kind). */
#define FISH_DISP_KIND_NONE (-1)
#define FISH_DISP_FISH_KINDS 0x38    /* 0-0x37: the fish */
#define FISH_DISP_KIND_EXTRA 0x38    /* 0x38-0x3a: fish56-fish58 */
#define FISH_DISP_KIND_SHADOW 0x3b   /* the shadow */
#define FISH_DISP_KINDS 0x3c         /* what FishDisp_ShowModel accepts */
#define FISH_DISP_KIND_ROTATE_YZX 15 /* the one fish rotated about y, z, then x */

/* A model's state (FishModel.state). */
enum FishModelState {
    FISH_MODEL_FREE = 0,
    FISH_MODEL_TAKEN = 1,    /* FishDisp_TakeModel */
    FISH_MODEL_LOADING = 2,  /* FishDisp_StartLoad, until its files are loaded */
    FISH_MODEL_SHOWN = 3,    /* placed and drawn */
    FISH_MODEL_RELEASED = 4, /* FishDisp_ReleaseModel: freed by the next frame's work */
};

/* Players' states (FishDispPlayer.state). */
#define FISH_DISP_PLAYER_NONE 8
#define FISH_DISP_PLAYER_INVALID 9

/* The model object of main a model draws through (0xb8 bytes; constructor func_02055210,
 * destructor func_020551e0). */
typedef struct FishModelObject {
    u8 unk_00[0x64];
    Mtx43 matrix; /* 0x64: where it is drawn (FishDisp_PlaceModel) */
    u8 unk_94[8];
    u8 frames[0x1c]; /* 0x9c: its animation's frame control (func_02056f28) */
} FishModelObject;

/* One model (0x16c bytes). It starts with a sound emitter of the base class
 * (SoundEmitterClass_ConstructBaseB), which plays the fish's sound. */
typedef struct FishModel {
    u8 sound[0x40];
    s32 kind;  /* 0x40: FISH_DISP_KIND_*, or a fish's kind */
    s32 state; /* 0x44: FishModelState */
    u16 slot;  /* 0x48: its entry in the pool (func_0209d238) */
    u8 pad_4a[2];
    u8 files[0x40];         /* 0x4c: the files loaded for it (func_0209d0ac) */
    Vec3 position;          /* 0x8c */
    FishModelObject object; /* 0x98 */
    Vec3 scale;             /* 0x150 */
    s16 rotation[3];        /* 0x15c: about x, y and z */
    u8 pad_162[2];
    s32 alpha;     /* 0x164: the shadow's alpha, 0-31 */
    u8 animate;    /* 0x168: the fish's animation runs (else it is held at speed 0) */
    u8 play_sound; /* 0x169: the emitter follows the fish and plays its sound */
    u8 pad_16a[2];
} FishModel;

typedef struct FishDisp {
    Process base;                       /* param: 0 for four models, 1 for one (FishDisp_Create) */
    FishModel models[FISH_DISP_MODELS]; /* 0x50 */
    u8 pool[0x18];                      /* 0x600: the heaps the models load into (func_0209d180) */
} FishDisp;

/* A player's fish (data_020dce10). */
typedef struct FishDispPlayer {
    u8 state; /* see the top of this file */
    u8 kind;  /* the fish's kind, 0xff for none */
    u8 pad_02[2];
    s32 x;
    s32 z;
} FishDispPlayer;

FishDisp *FishDisp_New(void);
FishDisp *FishDisp_Destruct(FishDisp *disp);
FishDisp *FishDisp_DestructFree(FishDisp *disp);
FishModel *FishDisp_ConstructModel(FishModel *model);
FishModel *FishDisp_DestructModel(FishModel *model);
int FishDisp_Create(FishDisp *disp);
int FishDisp_Delete(FishDisp *disp);
int FishDisp_Execute(FishDisp *disp);
int FishDisp_Draw(void);

int FishDisp_TakeModel(void);
int FishDisp_FindFreeModel(void);
int FishDisp_ShowModel(int index, int kind, const Vec3 *position, const Vec3 *scale, s16 rotation_x, s16 rotation_y,
                       s16 rotation_z, u8 animate, u8 play_sound, u32 alpha);
void FishDisp_SetModelScale(FishModel *model, const Vec3 *scale);
void FishDisp_ReleaseModel(int index);
int FishDisp_ModelPassedFrame(int index, int frame);
int FishDisp_StartLoad(FishDisp *disp, int index);
void FishDisp_FreeModel(FishDisp *disp, int index);
int FishDisp_LoadShadow(FishDisp *disp, u8 *pool, FishModel *model);
int FishDisp_LoadExtra(FishDisp *disp, u8 *pool, FishModel *model);
int FishDisp_LoadFish(FishDisp *disp, u8 *pool, FishModel *model);
void FishDisp_PlaceModel(FishDisp *disp, FishModel *model);

int FishDisp_PlayerPoint(int *x, int *z, unsigned int player);
unsigned char FishDisp_PlayerKind(unsigned int player);
int FishDisp_PlayerState(unsigned int player);
void FishDisp_SetPlayerState(unsigned int player, unsigned int state, int kind, int x, int z);
void FishDisp_HandleMessage(u8 *payload, int player);
void FishDisp_OnMessage0(const s8 *payload, int player);
void FishDisp_OnMessage1(const u8 *payload, int player);
void FishDisp_OnMessage2(const u8 *payload, int player);

#endif
