/* The fish display and the players' fish (fish_disp.h). */
#include "fish_disp.h"

#include "autoload_2/heap.h"                /* Heap_AllocAuxZeroed, Heap_FreeAux */
#include "autoload_2/sound_emitter_class.h" /* SoundEmitterClass_ConstructBaseB, ..._DestructBaseB */
#include "clean.h"
#include "main/packed_bytes.h"  /* PackedBytes_UnpackPoint */
#include "main/sound_emitter.h" /* SoundEmitter_Vfunc10B, _StopB, _UpdateAtB, _PlayB */
#include "animated_model.h"
#include "c_library.h"
#include "frame_ctrl.h"
#include "globe.h"
#include "model_object.h"
#include "model_pool.h"
#include "rom_file.h"

static_assert(sizeof(FishModelObject) == 0xb8, "FishModelObject size");
static_assert(offsetof(FishModel, kind) == 0x40, "FishModel kind");
static_assert(offsetof(FishModel, state) == 0x44, "FishModel state");
static_assert(offsetof(FishModel, slot) == 0x48, "FishModel slot");
static_assert(offsetof(FishModel, files) == 0x4c, "FishModel files");
static_assert(offsetof(FishModel, position) == 0x8c, "FishModel position");
static_assert(offsetof(FishModel, object) == 0x98, "FishModel object");
static_assert(offsetof(FishModel, object.matrix) == 0xfc, "FishModel matrix");
static_assert(offsetof(FishModel, object.frames) == 0x134, "FishModel frames");
static_assert(offsetof(FishModel, scale) == 0x150, "FishModel scale");
static_assert(offsetof(FishModel, rotation) == 0x15c, "FishModel rotation");
static_assert(offsetof(FishModel, alpha) == 0x164, "FishModel alpha");
static_assert(offsetof(FishModel, animate) == 0x168, "FishModel animate");
static_assert(offsetof(FishModel, play_sound) == 0x169, "FishModel play_sound");
static_assert(sizeof(FishModel) == 0x16c, "FishModel size");
static_assert(offsetof(FishDisp, models) == 0x50, "FishDisp models");
static_assert(offsetof(FishDisp, pool) == 0x600, "FishDisp pool");
static_assert(sizeof(FishDisp) == 0x618, "FishDisp size");
static_assert(sizeof(FishDispPlayer) == 12, "FishDispPlayer size");

/* The display while it exists (FishDisp_Create), else NULL. */
extern FishDisp *data_021c8184;
/* The number of models in use: 4, or 1 for a display of parameter 1 (FishDisp_Create). */
extern int data_020dcd78;
/* The players' fish. */
extern FishDispPlayer data_020dce10[FISH_DISP_PLAYERS];
/* 0 in the town (not in a room). */
extern u8 data_020e54a8;
/* The handlers of player message 42 by its first byte: FishDisp_OnMessage0 to 2. */
extern void (*data_020dcefc[3])(u8 *payload, int player);

/* Vtables: the display's, and its base class's. */
extern const u32 data_020dce48[];
extern const u32 data_020da13c[];

/* Paths: the shadow's model and animation, and fish56-fish58's models. */
extern const char *data_020dcd74;
extern const char *data_020dcd70;
extern const char *data_020dcd84[3];
/* Formats of a fish's model and animation, for kinds below 10 ("fish0%d") and the others. */
extern const char data_020dce90[];
extern const char data_020dcea8[];
extern const char data_020dcec0[];
extern const char data_020dced8[];
/* "fish_disp", the pool's name. */
extern char data_020dcef0[];

/* The scratch matrix of main's models. */
extern Mtx43 data_021fbe48;

/* The model's constructor and destructor, handed to the vector helpers (the game's own). */
extern void *func_0205072c(void *model);
extern void *func_02050704(void *model);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The pool of heaps: constructor, destructor, set-up (with the allocator and the releaser it is
 * handed, the game's own) and release. */
extern int func_0205c8f8(int size, int heapword);
extern void func_0205c8dc(void);
extern void *NNS_G3dGetJntAnmSet(void *file);
extern void *func_02107b44(void *set, int index);
extern void NNS_G3dMdlSetMdlAlpha(void *resource, int material, int alpha);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* ---- The players' fish */

/* func_0204feac: a player's point, x and z; 0 for a number that is no player. */
int FishDisp_PlayerPoint(int *x, int *z, unsigned int player)
{
    if (player >= FISH_DISP_PLAYERS) {
        return 0;
    }
    *x = data_020dce10[player].x;
    *z = data_020dce10[player].z;
    return 1;
}
CLEAN_AS(func_0204feac, FishDisp_PlayerPoint)

/* func_0204fed0: a player's fish's kind; 0xff for a number that is no player. */
unsigned char FishDisp_PlayerKind(unsigned int player)
{
    if (player >= FISH_DISP_PLAYERS) {
        return 0xff;
    }
    return data_020dce10[player].kind;
}
CLEAN_AS(func_0204fed0, FishDisp_PlayerKind)

/* func_0204fee8: a player's state; FISH_DISP_PLAYER_INVALID for a number that is no player. */
int FishDisp_PlayerState(unsigned int player)
{
    if (player >= FISH_DISP_PLAYERS) {
        return FISH_DISP_PLAYER_INVALID;
    }
    return data_020dce10[player].state;
}
CLEAN_AS(func_0204fee8, FishDisp_PlayerState)

static void set_player(FishDispPlayer *p, u8 state, int kind, int x, int z)
{
    p->state = state;
    p->kind = (u8) kind;
    p->x = x;
    p->z = z;
}

/* func_0204ff00: sets a player's state (nothing for a number that is no player or a kind of
 * 0x38 and above; -1 passes).
 *   0, 8: the state with the kind and the point.
 *   1: taken in the town when the player is in state 3, else the state becomes 8; with the kind
 *      and the point.
 *   2: taken in the town when the player is in state 3, 8 or 1, else 8; with the kind and the
 *      point.
 *   others: the state alone.
 * QUIRK: for 2 the player's state is asked again for each value it is compared with. */
void FishDisp_SetPlayerState(unsigned int player, unsigned int state, int kind, int x, int z)
{
    if (player >= FISH_DISP_PLAYERS || kind >= FISH_DISP_FISH_KINDS) {
        return;
    }
    FishDispPlayer *p = &data_020dce10[player];
    u8 next;
    switch (state) {
        case 0:
            set_player(p, 0, kind, x, z);
            break;
        case 1:
            next = FISH_DISP_PLAYER_NONE;
            if (data_020e54a8 == 0 && FishDisp_PlayerState(player) == 3) {
                next = 1;
            }
            set_player(p, next, kind, x, z);
            break;
        case 2:
            next = FISH_DISP_PLAYER_NONE;
            if (data_020e54a8 == 0 &&
                (FishDisp_PlayerState(player) == 3 || FishDisp_PlayerState(player) == FISH_DISP_PLAYER_NONE ||
                 FishDisp_PlayerState(player) == 1)) {
                next = 2;
            }
            set_player(p, next, kind, x, z);
            break;
        case FISH_DISP_PLAYER_NONE:
            set_player(p, FISH_DISP_PLAYER_NONE, kind, x, z);
            break;
        default:
            p->state = (u8) state;
            break;
    }
}
CLEAN_AS(func_0204ff00, FishDisp_SetPlayerState)

/* func_02050814: message 2: state 2. */
void FishDisp_OnMessage2(const u8 *payload, int player)
{
    (void) payload;
    FishDisp_SetPlayerState((u8) player, 2, -1, 0, 0);
}
CLEAN_AS(func_02050814, FishDisp_OnMessage2)

/* func_02050830: message 1: state 1. */
void FishDisp_OnMessage1(const u8 *payload, int player)
{
    (void) payload;
    FishDisp_SetPlayerState((u8) player, 1, -1, 0, 0);
}
CLEAN_AS(func_02050830, FishDisp_OnMessage1)

/* func_0205084c: message 0: state 0 with the fish's kind (byte 1, signed) and the point packed
 * in bytes 2-6. */
void FishDisp_OnMessage0(const s8 *payload, int player)
{
    s8 kind = payload[1];
    u8 packed[5];
    u32 x;
    u32 z;
    MI_CpuCopy8(payload + 2, packed, sizeof(packed));
    PackedBytes_UnpackPoint(packed, &x, &z);
    FishDisp_SetPlayerState((u8) player, 0, kind, (int) x, (int) z);
}
CLEAN_AS(func_0205084c, FishDisp_OnMessage0)

/* func_02050884: player message 42, by its first byte (0-2; others are ignored), through the
 * game's table of handlers. */
void FishDisp_HandleMessage(u8 *payload, int player)
{
    u8 kind = payload[0];
    if (kind >= 3) {
        return;
    }
    data_020dcefc[kind](payload, player);
}
CLEAN_AS(func_02050884, FishDisp_HandleMessage)

/* ---- The process */

/* func_020507b8: a new display from the processes' heap (Heap_AllocAuxZeroed), constructed:
 * the base process, the four models and the pool. NULL when there is no room. */
FishDisp *FishDisp_New(void)
{
    FishDisp *disp = Heap_AllocAuxZeroed(sizeof(FishDisp));
    if (disp != NULL) {
        Process_Construct(&disp->base);
        disp->base.vtable = data_020da13c;
        disp->base.vtable = data_020dce48;
        __cxa_vec_ctor(disp->models, FISH_DISP_MODELS, sizeof(FishModel), (void (*)(void *))(uintptr_t) func_0205072c,
                       (void (*)(void *))(uintptr_t) func_02050704);
        ModelPool_Init((ModelPool *) (void *) disp->pool);
    }
    return disp;
}
CLEAN_AS(func_020507b8, FishDisp_New)

/* func_0204fcac (vtable slot 16): the destructor: the pool's, the models', then the base
 * classes'. */
FishDisp *FishDisp_Destruct(FishDisp *disp)
{
    disp->base.vtable = data_020dce48;
    ModelPool_Destruct(disp->pool);
    __cxa_vec_cleanup(disp->models, FISH_DISP_MODELS, sizeof(FishModel), (void (*)(void *))(uintptr_t) func_02050704);
    disp->base.vtable = data_020da13c;
    Process_Destruct(&disp->base);
    return disp;
}
CLEAN_AS(func_0204fcac, FishDisp_Destruct)

/* func_0204fcf0 (vtable slot 17): the destructor, and the display freed. */
FishDisp *FishDisp_DestructFree(FishDisp *disp)
{
    disp->base.vtable = data_020dce48;
    ModelPool_Destruct(disp->pool);
    __cxa_vec_cleanup(disp->models, FISH_DISP_MODELS, sizeof(FishModel), (void (*)(void *))(uintptr_t) func_02050704);
    disp->base.vtable = data_020da13c;
    Process_Destruct(&disp->base);
    Heap_FreeAux(disp);
    return disp;
}
CLEAN_AS(func_0204fcf0, FishDisp_DestructFree)

/* func_0205072c: a model's constructor: free, no kind, position and scale (1.0, 1.0, 1.0), no
 * rotation and alpha 31. */
FishModel *FishDisp_ConstructModel(FishModel *model)
{
    SoundEmitterClass_ConstructBaseB((SoundEmitterObject *) model);
    ModelPoolSlot_Construct(&model->slot);
    ModelPoolFiles_Construct((ModelPoolFiles *) (void *) model->files);
    AnimatedModel_Construct((AnimatedModel *) &model->object);
    model->kind = FISH_DISP_KIND_NONE;
    model->state = FISH_MODEL_FREE;
    ModelPoolFiles_Reset((ModelPoolFiles *) (void *) model->files);
    model->position = (Vec3){0x1000, 0x1000, 0x1000};
    model->scale = (Vec3){0x1000, 0x1000, 0x1000};
    model->rotation[0] = 0;
    model->rotation[1] = 0;
    model->rotation[2] = 0;
    model->alpha = 0x1f;
    return model;
}
CLEAN_AS(func_0205072c, FishDisp_ConstructModel)

/* func_02050704: a model's destructor. */
FishModel *FishDisp_DestructModel(FishModel *model)
{
    AnimatedModel_DestructComplete((AnimatedModel *) &model->object);
    ModelPoolFiles_Destruct((ModelPoolFiles *) (void *) model->files);
    ModelPoolSlot_Destruct(&model->slot);
    SoundEmitterClass_DestructBaseB((SoundEmitterObject *) model);
    return model;
}
CLEAN_AS(func_02050704, FishDisp_DestructModel)

/* func_02050588 (vtable slot 0): creation: four models for parameter 0, one for 1 (another
 * keeps the number there was), the pool set up with an entry of 0x134c bytes for each, and the
 * display made the current one.
 * QUIRK: the number of models is a global, not the display's. */
int FishDisp_Create(FishDisp *disp)
{
    if (disp->base.param == 0) {
        data_020dcd78 = 4;
    } else if (disp->base.param == 1) {
        data_020dcd78 = 1;
    }
    ModelPool_Create((ModelPool *) (void *) disp->pool, (unsigned int) data_020dcd78, 0x800, 0x80, 0x134c, func_0205c8f8,
                     func_0205c8dc, data_020dcef0);
    data_021c8184 = disp;
    return 1;
}
CLEAN_AS(func_02050588, FishDisp_Create)

/* func_0205009c (vtable slot 3): deletion: every model freed, the pool released and no display
 * current. */
int FishDisp_Delete(FishDisp *disp)
{
    for (int i = 0; i < data_020dcd78; i++) {
        FishDisp_FreeModel(disp, i);
    }
    ModelPool_Destroy((ModelPool *) (void *) disp->pool);
    data_021c8184 = NULL;
    return 1;
}
CLEAN_AS(func_0205009c, FishDisp_Delete)

static int is_extra(int kind)
{
    return kind >= FISH_DISP_KIND_EXTRA && kind < FISH_DISP_KIND_EXTRA + 3;
}

/* func_02050444 (vtable slot 6, the execute phase): each model in use by its state (see the
 * top of fish_disp.h). A shown fish moves on its animation and, with play_sound, takes its
 * emitter along and plays sound 0x84d at volume 127 when its animation passes frame 1; the
 * shadow moves on and gets its alpha; fish56-fish58 only are placed. 0 when there is no
 * display. The current display's models are run, with this one's pool. */
int FishDisp_Execute(FishDisp *disp)
{
    if (data_021c8184 == NULL) {
        return 0;
    }
    FishModel *model = data_021c8184->models;
    for (int i = 0; i < data_020dcd78; i++, model++) {
        switch (model->state) {
            case FISH_MODEL_TAKEN:
                if (model->kind != FISH_DISP_KIND_NONE) {
                    FishDisp_StartLoad(disp, i);
                }
                break;
            case FISH_MODEL_LOADING:
                if (is_extra(model->kind)) {
                    FishDisp_LoadExtra(disp, disp->pool, model);
                } else if (model->kind == FISH_DISP_KIND_SHADOW) {
                    FishDisp_LoadShadow(disp, disp->pool, model);
                } else {
                    FishDisp_LoadFish(disp, disp->pool, model);
                }
                break;
            case FISH_MODEL_SHOWN:
                if (model->kind == FISH_DISP_KIND_SHADOW) {
                    AnimatedModel_StepFrames((AnimatedModel *) &model->object);
                    NNS_G3dMdlSetMdlAlpha((void *) (uintptr_t) ModelPoolFiles_Model((ModelPoolFiles *) (void *) model->files),
                                          0, model->alpha);
                } else if (!is_extra(model->kind)) {
                    AnimatedModel_StepFrames((AnimatedModel *) &model->object);
                    if (model->play_sound) {
                        Vec3 at = model->position;
                        SoundEmitter_UpdateAtB((SoundEmitter *) model, &at);
                        if (FrameCtrl_Passed((const FrameCtrl *) (void *) model->object.frames, 1) != 0) {
                            SoundEmitter_PlayB((SoundEmitter *) model, 0x84d, 0x7f, 0);
                        }
                    }
                }
                FishDisp_PlaceModel(disp, model);
                break;
            case FISH_MODEL_RELEASED:
                FishDisp_FreeModel(disp, i);
                break;
            default:
                break;
        }
    }
    return 1;
}
CLEAN_AS(func_02050444, FishDisp_Execute)

/* func_020500d8 (vtable slot 9, the draw phase): the shown models, each at its scale. 0 when
 * there is no display. */
int FishDisp_Draw(void)
{
    if (data_021c8184 == NULL) {
        return 0;
    }
    FishModel *model = data_021c8184->models;
    for (int i = 0; i < data_020dcd78; i++, model++) {
        if (model->state == FISH_MODEL_SHOWN) {
            Vec3 scale = model->scale;
            AnimatedModel_Draw((AnimatedModel *) &model->object, &scale);
        }
    }
    return 1;
}
CLEAN_AS(func_020500d8, FishDisp_Draw)

/* ---- The models */

/* func_020506c0: takes the first free model and gives its number, or -1 when there is none or
 * no display. */
int FishDisp_FindFreeModel(void)
{
    if (data_021c8184 == NULL) {
        return -1;
    }
    FishModel *model = data_021c8184->models;
    for (int i = 0; i < data_020dcd78; i++, model++) {
        if (model->state == FISH_MODEL_FREE) {
            model->state = FISH_MODEL_TAKEN;
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_020506c0, FishDisp_FindFreeModel)

/* func_0204fea4: takes a model (FishDisp_FindFreeModel). */
int FishDisp_TakeModel(void)
{
    return FishDisp_FindFreeModel();
}
CLEAN_AS(func_0204fea4, FishDisp_TakeModel)

/* func_0205007c */
void FishDisp_SetModelScale(FishModel *model, const Vec3 *scale)
{
    model->scale.x = scale->x;
    model->scale.y = scale->y;
    model->scale.z = scale->z;
}
CLEAN_AS(func_0205007c, FishDisp_SetModelScale)

/* func_0204fdec: sets a model: its kind (below FISH_DISP_KINDS), position, scale, rotation,
 * whether the fish is animated and plays its sound, and the shadow's alpha. 0 (and nothing set)
 * when there is no display or the model or the kind is out of range. */
int FishDisp_ShowModel(int index, int kind, const Vec3 *position, const Vec3 *scale, s16 rotation_x, s16 rotation_y,
                       s16 rotation_z, u8 animate, u8 play_sound, u32 alpha)
{
    if (data_021c8184 == NULL || index < 0 || index >= data_020dcd78 || kind < 0 || kind >= FISH_DISP_KINDS) {
        return 0;
    }
    FishModel *model = &data_021c8184->models[index];
    model->kind = kind;
    model->position.x = position->x;
    model->position.y = position->y;
    model->position.z = position->z;
    Vec3 size = *scale;
    FishDisp_SetModelScale(model, &size);
    model->rotation[0] = rotation_x;
    model->rotation[1] = rotation_y;
    model->rotation[2] = rotation_z;
    model->animate = animate;
    model->play_sound = play_sound;
    model->alpha = (s32) alpha;
    return 1;
}
CLEAN_AS(func_0204fdec, FishDisp_ShowModel)

/* func_0204fdbc: gives a model back (FISH_MODEL_RELEASED); nothing when there is no display or
 * the number is out of range. */
void FishDisp_ReleaseModel(int index)
{
    if (data_021c8184 == NULL || index < 0 || index >= data_020dcd78) {
        return;
    }
    data_021c8184->models[index].state = FISH_MODEL_RELEASED;
}
CLEAN_AS(func_0204fdbc, FishDisp_ReleaseModel)

/* func_0204fd6c: whether a fish model's animation passed `frame` (func_02056f28); 0 for a
 * number out of range or a model that is not a fish.
 * REQUIRES: a display exists (the ROM reads the models of a NULL display at address 0x50). */
int FishDisp_ModelPassedFrame(int index, int frame)
{
    if (index < 0 || index >= data_020dcd78) {
        return 0;
    }
    FishModel *model =
        (FishModel *) ((uintptr_t) data_021c8184 + offsetof(FishDisp, models) + (u32) index * sizeof(FishModel));
    if (model->kind < 0 || model->kind >= FISH_DISP_FISH_KINDS) {
        return 0;
    }
    return FrameCtrl_Passed((const FrameCtrl *) (void *) model->object.frames, frame) != 0;
}
CLEAN_AS(func_0204fd6c, FishDisp_ModelPassedFrame)

/* func_0205066c: a taken model starts loading: it takes its entry of the pool, its files are
 * reset and its sound stops. 0 when there is no display or for model -1. */
int FishDisp_StartLoad(FishDisp *disp, int index)
{
    if (data_021c8184 == NULL || index == -1) {
        return 0;
    }
    FishModel *model = &data_021c8184->models[index];
    model->state = FISH_MODEL_LOADING;
    ModelPool_Take((ModelPool *) (void *) disp->pool, &model->slot);
    ModelPoolFiles_Reset((ModelPoolFiles *) (void *) model->files);
    SoundEmitter_StopB((SoundEmitter *) model);
    return 1;
}
CLEAN_AS(func_0205066c, FishDisp_StartLoad)

/* func_020505f4: frees a model: its emitter is told (vtable slot 4) when it was loading or
 * shown, it becomes free with no kind, its model object and files are emptied and its entry
 * goes back to this display's pool. Nothing when there is no display or the number is out of
 * range. */
void FishDisp_FreeModel(FishDisp *disp, int index)
{
    if (index < 0 || index >= data_020dcd78 || data_021c8184 == NULL) {
        return;
    }
    FishModel *model = &data_021c8184->models[index];
    if (model->state != FISH_MODEL_FREE && model->state != FISH_MODEL_TAKEN) {
        SoundEmitter_Vfunc10B((SoundEmitter *) model);
    }
    model->kind = FISH_DISP_KIND_NONE;
    model->state = FISH_MODEL_FREE;
    AnimatedModel_DetachJoints((AnimatedModel *) &model->object);
    ModelPoolFiles_Release((ModelPoolFiles *) (void *) model->files);
    ModelObject_Release((ModelObject *) &model->object);
    ModelPool_Release((ModelPool *) (void *) disp->pool, &model->slot);
}
CLEAN_AS(func_020505f4, FishDisp_FreeModel)

/* func_02050140: loads the shadow (kind 0x3b) and its animation, played from frame 1 at speed
 * 1.0; shown and placed, with its alpha, when that works. 0 (still loading) when it does not, or for no pool or model. */
int FishDisp_LoadShadow(FishDisp *disp, u8 *pool, FishModel *model)
{
    if (pool == NULL || model == NULL) {
        return 0;
    }
    int kind = model->kind;
    void *entry = ModelPool_Take((ModelPool *) (void *) pool, &model->slot);
    if (ModelPoolFiles_Load((ModelPoolFiles *) (void *) model->files, entry, data_020dcd74) == 0) {
        return 0;
    }
    ModelObject_SetModel((ModelObject *) &model->object,
                         (u8 *) (uintptr_t) ModelPoolFiles_Model((ModelPoolFiles *) (void *) model->files), NULL);
    void *heap = (void *) (uintptr_t) ModelPoolEntry_Heap(entry);
    void *animation = func_02107b44(NNS_G3dGetJntAnmSet(RomFile_Load(data_020dcd70, heap, 4, NULL)), 0);
    if (AnimatedModel_LoadAnim((AnimatedModel *) &model->object, heap) == 0) {
        return 0;
    }
    AnimatedModel_Start((AnimatedModel *) &model->object, animation, 0, 0x1000, 1, 0);
    AnimatedModel_Attach((AnimatedModel *) &model->object);
    model->state = FISH_MODEL_SHOWN;
    FishDisp_PlaceModel(disp, model);
    if (kind == FISH_DISP_KIND_SHADOW) {
        NNS_G3dMdlSetMdlAlpha((void *) (uintptr_t) ModelPoolFiles_Model((ModelPoolFiles *) (void *) model->files), 0,
                              model->alpha);
    }
    return 1;
}
CLEAN_AS(func_02050140, FishDisp_LoadShadow)

/* func_02050210: loads one of fish56-fish58 (kinds 0x38-0x3a), shown and placed when that
 * works; 0 when it does not, or for no pool or model. */
int FishDisp_LoadExtra(FishDisp *disp, u8 *pool, FishModel *model)
{
    if (pool == NULL || model == NULL) {
        return 0;
    }
    int kind = model->kind;
    void *entry = ModelPool_Take((ModelPool *) (void *) pool, &model->slot);
    if (ModelPoolFiles_Load((ModelPoolFiles *) (void *) model->files, entry, data_020dcd84[kind - FISH_DISP_KIND_EXTRA]) ==
        0) {
        return 0;
    }
    ModelObject_SetModel((ModelObject *) &model->object,
                         (u8 *) (uintptr_t) ModelPoolFiles_Model((ModelPoolFiles *) (void *) model->files), NULL);
    model->state = FISH_MODEL_SHOWN;
    FishDisp_PlaceModel(disp, model);
    return 1;
}
CLEAN_AS(func_02050210, FishDisp_LoadExtra)

/* func_0205027c: loads a fish: "/fish/0<kind / 16>/fish<kind>.nsbmd" (kind written with two
 * digits below 10 as well) and its .nsbca, played from frame 1 at speed 1.0 or, without
 * `animate`, held;
 * shown and placed when that works. 0 when it does not, or for no pool or model. */
int FishDisp_LoadFish(FishDisp *disp, u8 *pool, FishModel *model)
{
    if (pool == NULL || model == NULL) {
        return 0;
    }
    int kind = model->kind;
    void *entry = ModelPool_Take((ModelPool *) (void *) pool, &model->slot);
    int folder = kind / 16;
    char path[0x18];
    CLib_SPrintf(path, kind < 10 ? data_020dce90 : data_020dcea8, folder, kind);
    if (ModelPoolFiles_Load((ModelPoolFiles *) (void *) model->files, entry, path) == 0) {
        return 0;
    }
    ModelObject_SetModel((ModelObject *) &model->object,
                         (u8 *) (uintptr_t) ModelPoolFiles_Model((ModelPoolFiles *) (void *) model->files), NULL);
    void *heap = (void *) (uintptr_t) ModelPoolEntry_Heap(entry);
    CLib_SPrintf(path, kind < 10 ? data_020dcec0 : data_020dced8, folder, kind);
    void *animation = func_02107b44(NNS_G3dGetJntAnmSet(RomFile_Load(path, heap, 4, NULL)), 0);
    int speed = model->animate ? 0x1000 : 0;
    if (AnimatedModel_LoadAnim((AnimatedModel *) &model->object, heap) == 0) {
        return 0;
    }
    AnimatedModel_Start((AnimatedModel *) &model->object, animation, 0, speed, 1, 0);
    AnimatedModel_Attach((AnimatedModel *) &model->object);
    model->state = FISH_MODEL_SHOWN;
    FishDisp_PlaceModel(disp, model);
    return 1;
}
CLEAN_AS(func_0205027c, FishDisp_LoadFish)

/* func_02050394: places a model: for display parameter 0 at its position as the camera shows
 * it, tilted about x by the angle that gives (func_0203f8d0); for parameter 1 at its position
 * untilted. Then rotated by its rotation, about z, y and x (Mtx43_RotateZYX) or, for kind 15,
 * about y, then z, then x. The matrix is built in data_021fbe48 and copied to the model.
 * REQUIRES: the display's parameter is 0 or 1 (another leaves the point and the angle
 * unset in the ROM; here they are 0). */
void FishDisp_PlaceModel(FishDisp *disp, FishModel *model)
{
    int kind = model->kind;
    Vec3 at = model->position;
    Vec3 shown = {0, 0, 0};
    int tilt = 0;
    if (disp->base.param == 0) {
        tilt = Globe_BendFar(&shown, &at);
    } else if (disp->base.param == 1) {
        tilt = 0;
        shown = at;
    }
    Mtx43 *mtx = &data_021fbe48;
    Mtx43_Translation(mtx, shown.x, shown.y, shown.z);
    Mtx43_RotateX(mtx, tilt);
    if (kind != FISH_DISP_KIND_ROTATE_YZX) {
        Mtx43_RotateZYX(mtx, model->rotation[0], model->rotation[1], model->rotation[2]);
    } else {
        Mtx43_RotateY(mtx, model->rotation[1]);
        Mtx43_RotateZ(mtx, model->rotation[2]);
        Mtx43_RotateX(mtx, model->rotation[0]);
    }
    model->object.matrix = *mtx;
}
CLEAN_AS(func_02050394, FishDisp_PlaceModel)
