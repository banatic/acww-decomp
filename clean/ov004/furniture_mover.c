/* The room's furniture mover (furniture_mover.h). */
#include "furniture_mover.h"

#include <string.h>

#include "clean.h"
#include "main/c_library.h"
#include "main/frame_ctrl.h"
#include "main/item_code.h"
#include "main/model_object.h"
#include "main/rom_file.h"

static_assert(offsetof(FurnitureMover, position) == 0x04, "position");
static_assert(offsetof(FurnitureMover, heap) == 0x10, "heap");
static_assert(offsetof(FurnitureMover, idle_anim) == 0x20, "idle animation");
static_assert(offsetof(FurnitureMover, model_resource) == 0x28, "model resource");
static_assert(offsetof(FurnitureMover, model) == 0x2c, "model");
static_assert(offsetof(FurnitureMover, model.frames) == 0xc8, "the model's frames");

#define HEAP_SIZE 0x2800
#define FILE_ALIGN 4
#define MOVER_ITEM 0x3984 /* the furniture whose model the mover animates */
#define ANIM_MODE_ONCE 1  /* stop at the end */
#define ONE 0x1000        /* normal speed, 20.12 fixed point */
#define ROOT_NODE 0
#define NODE_COMMAND 6     /* NitroSystem's NNS_G3D_SBC_NODEDESC */
#define NODE_HOOK_TIMING 2 /* the hook's timing for that command */

/* NitroSystem's archive (NNSFndArchive), mounted on the stack while the files are taken out. */
typedef struct FurnitureMoverArchive {
    u32 words[26];
} FurnitureMoverArchive;

static_assert(offsetof(FurnitureMoverRenderState, hooks) == 0x0c, "hooks");
static_assert(offsetof(FurnitureMoverRenderState, hook_timings) == 0x8c, "hook timings");
static_assert(offsetof(FurnitureMoverRenderState, joint) == 0xb4, "joint");

/* The heap files are loaded on. */
extern Heap *data_021fbe94;
/* The matrix being built. */
extern Mtx43 data_021fbe48;
/* "/ftr/%d/%d/%04x.arc", "FTT" (the furniture archive's name) and a pointer to its model,
 * "FTT:a/bmd/bmd0". */
extern const char data_ov004_022560fc[];
extern const char data_ov004_02256110[];
extern const char *data_ov004_02255f70;
/* "/ftr/anm/anm.arc", "ANM", and its animations "ANM:a/bca/ft_push1.nsbca",
 * "ANM:a/bca/ft_pull1.nsbca" and "ANM:a/bca/ft_kb_hw_def_anim.nsbca". */
extern const char data_ov004_02256114[];
extern const char data_ov004_02256128[];
extern const char data_ov004_0225612c[];
extern const char data_ov004_02256148[];
extern const char data_ov004_02256164[];

/* The model's hooks, as the game's functions (the render object keeps their addresses). */
extern void func_ov004_0223b1b8(void *state);
extern void func_ov004_0223b1c8(void *state);

extern int NNS_FndMountArchive(FurnitureMoverArchive *archive, const char *name, void *data);
extern u8 *NNS_FndGetArchiveFileByName(const char *path);
extern int func_0210285c(FurnitureMoverArchive *archive);
/* NitroSystem: a model file's model set, a file's set of joint animations and animation
 * `index` of a set. */
extern u8 *func_02107828(u8 *file);
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern const u8 *func_02107b44(void *set, int index);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);

static u16 read16(const u8 *p)
{
    u16 value;
    memcpy(&value, p, sizeof value);
    return value;
}

static u32 read32(const u8 *p)
{
    u32 value;
    memcpy(&value, p, sizeof value);
    return value;
}

/* An arithmetic shift right, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* The model's transform: the 4x3 matrix at 0x64 of its holder, which places the model. */
static Mtx43 *transform(FurnitureMover *mover)
{
    return (Mtx43 *) (void *) mover->model.object.unk_64;
}

/* func_ov004_0223adf4 */
u32 FurnitureMover_IdleAnim(FurnitureMover *mover)
{
    return (u32) (uintptr_t) mover->idle_anim;
}
CLEAN_AS(func_ov004_0223adf4, FurnitureMover_IdleAnim)

/* func_ov004_0223adf8 */
u32 FurnitureMover_PullAnim(FurnitureMover *mover)
{
    return (u32) (uintptr_t) mover->pull_anim;
}
CLEAN_AS(func_ov004_0223adf8, FurnitureMover_PullAnim)

/* func_ov004_0223adfc */
u32 FurnitureMover_PushAnim(FurnitureMover *mover)
{
    return (u32) (uintptr_t) mover->push_anim;
}
CLEAN_AS(func_ov004_0223adfc, FurnitureMover_PushAnim)

/* func_ov004_0223ae00: the model's files forgotten (they are on the mover's heap). Always 1. */
int FurnitureMover_ForgetModel(FurnitureMover *mover)
{
    mover->model_archive = NULL;
    mover->model_resource = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0223ae00, FurnitureMover_ForgetModel)

/* func_ov004_0223ae0c: with the heap and nothing loaded yet, the archive of furniture 0x3984
 * loaded and its model set up with its joints' animation, the push animation started (and
 * attached), and the hook that sets the node hooks (func_ov004_0223b1b8) given the mover.
 * Whether the model was set up. */
int FurnitureMover_LoadModel(FurnitureMover *mover)
{
    if (mover->heap == NULL || mover->model_archive != NULL || mover->model_resource != NULL) {
        return 0;
    }
    char path[0x2a];
    ItemCode item = MOVER_ITEM;
    int number = ItemCode_VariantItem(&item);
    CLib_SPrintf(path, data_ov004_022560fc, shift_right(number, 8), (number & 0xff) >> 4, number);
    mover->model_archive = RomFile_Load(path, mover->heap, FILE_ALIGN, NULL);
    FurnitureMoverArchive archive;
    if (mover->model_archive == NULL || NNS_FndMountArchive(&archive, data_ov004_02256110, mover->model_archive) == 0) {
        return 0;
    }
    int loaded = 0;
    /* the model set's dictionary: its entries' offset at 0xe, the first model's offset 4 bytes
     * into the entries (8 from the dictionary at 8) */
    u8 *set = func_02107828(NNS_FndGetArchiveFileByName(data_ov004_02255f70));
    mover->model_resource = set + read32(set + read16(set + 0xe) + 0xc);
    if (ModelObject_SetModelTexture(&mover->model.object, mover->model_resource, NULL) != 0 &&
        AnimatedModel_LoadAnim(&mover->model, mover->heap) != 0) {
        const u8 *anim = (const u8 *) (uintptr_t) FurnitureMover_PushAnim(mover);
        AnimatedModel_Start(&mover->model, anim, ANIM_MODE_ONCE, ONE, 0, 0);
        AnimatedModel_Attach(&mover->model);
        ModelObject_SetInitHook(&mover->model.object, (void *) func_ov004_0223b1b8, mover);
        loaded = 1;
    }
    func_0210285c(&archive);
    return loaded;
}
CLEAN_AS(func_ov004_0223ae0c, FurnitureMover_LoadModel)

/* func_ov004_0223af08: the animations forgotten (they are on the mover's heap). Always 1. */
int FurnitureMover_ForgetAnims(FurnitureMover *mover)
{
    mover->anim_archive = NULL;
    mover->push_anim = NULL;
    mover->pull_anim = NULL;
    mover->idle_anim = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0223af08, FurnitureMover_ForgetAnims)

/* The first joint animation of the archive's file `path`, kept in `*anim` when the file is
 * there. */
static void take_joint_anim(const char *path, const u8 **anim)
{
    u8 *file = NNS_FndGetArchiveFileByName(path);
    if (file != NULL) {
        *anim = func_02107b44(NNS_G3dGetJntAnmSet(file), 0);
    }
}

/* func_ov004_0223af18: when not loaded yet, "/ftr/anm/anm.arc" loaded on the mover's heap and
 * its three animations taken (each one missing left as it was). Whether the archive was
 * mounted.
 * QUIRK: once the archive is loaded, later calls give 0. */
int FurnitureMover_LoadAnims(FurnitureMover *mover)
{
    if (mover->anim_archive != NULL) {
        return 0;
    }
    mover->anim_archive = RomFile_Load(data_ov004_02256114, mover->heap, FILE_ALIGN, NULL);
    if (mover->anim_archive == NULL) {
        return 0;
    }
    FurnitureMoverArchive archive;
    if (NNS_FndMountArchive(&archive, data_ov004_02256128, mover->anim_archive) == 0) {
        return 0;
    }
    take_joint_anim(data_ov004_0225612c, &mover->push_anim);
    take_joint_anim(data_ov004_02256148, &mover->pull_anim);
    take_joint_anim(data_ov004_02256164, &mover->idle_anim);
    func_0210285c(&archive);
    return 1;
}
CLEAN_AS(func_ov004_0223af18, FurnitureMover_LoadAnims)

/* func_ov004_0223afb4: whether there was a heap to delete. */
int FurnitureMover_DeleteHeap(FurnitureMover *mover)
{
    if (mover->heap != NULL) {
        Heap_Delete(mover->heap);
        mover->heap = NULL;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223afb4, FurnitureMover_DeleteHeap)

/* func_ov004_0223afd4: whether a heap was made now (0 when there was one already). */
int FurnitureMover_CreateHeap(FurnitureMover *mover)
{
    if (mover->heap == NULL) {
        mover->heap = FrameHeap_Create(HEAP_SIZE, data_021fbe94);
        if (mover->heap != NULL) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223afd4, FurnitureMover_CreateHeap)

/* func_ov004_0223b004 (each frame of a move): while the mover and the object's flag are set,
 * the animation steps and the model is drawn without commands (its root node's hook places the
 * mover); `position` gets the mover's position. When the animation is done, both flags are
 * cleared and 1 is given. */
int FurnitureMover_Step(FurnitureMover *mover, FurnitureMoveFlag *flag, Vec3 *position)
{
    if (mover->moving == 0 || flag->moving == 0) {
        return 0;
    }
    AnimatedModel_StepFrames(&mover->model);
    ModelObject_DrawWithoutCommands(&mover->model.object);
    position->x = mover->position.x;
    position->y = mover->position.y;
    position->z = mover->position.z;
    if (FrameCtrl_IsDone(&mover->model.frames)) {
        flag->moving = 0;
        mover->moving = flag->moving;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223b004, FurnitureMover_Step)

/* func_ov004_0223b058: a pull (the room object's move back).
 * QUIRK: the angle is taken to 16 bits. */
int FurnitureMover_StartPull(FurnitureMover *mover, FurnitureMoveFlag *flag, Vec3 *position, int angle)
{
    const u8 *anim = (const u8 *) (uintptr_t) FurnitureMover_PullAnim(mover);
    return FurnitureMover_Start(mover, anim, flag, position, (s16) angle);
}
CLEAN_AS(func_ov004_0223b058, FurnitureMover_StartPull)

/* func_ov004_0223b080: a push (the room object's move ahead).
 * QUIRK: the angle is taken to 16 bits. */
int FurnitureMover_StartPush(FurnitureMover *mover, FurnitureMoveFlag *flag, Vec3 *position, int angle)
{
    const u8 *anim = (const u8 *) (uintptr_t) FurnitureMover_PushAnim(mover);
    return FurnitureMover_Start(mover, anim, flag, position, (s16) angle);
}
CLEAN_AS(func_ov004_0223b080, FurnitureMover_StartPush)

/* func_ov004_0223b0a8: when neither the object nor the mover is moving and there is an
 * animation, it is started once at normal speed, both flags set, the mover placed at
 * `position`, and its transform the translation to `position` turned by `angle` about y (built
 * in data_021fbe48). Whether the move started. */
int FurnitureMover_Start(FurnitureMover *mover, const u8 *anim, FurnitureMoveFlag *flag, Vec3 *position, s16 angle)
{
    if (flag->moving != 0 || mover->moving != 0 || anim == NULL) {
        return 0;
    }
    AnimatedModel_Start(&mover->model, anim, ANIM_MODE_ONCE, ONE, 0, 0);
    mover->moving = 1;
    flag->moving = mover->moving;
    mover->position.x = position->x;
    mover->position.y = position->y;
    mover->position.z = position->z;
    Mtx43_Translation(&data_021fbe48, position->x, position->y, position->z);
    Mtx43_RotateY(&data_021fbe48, angle);
    *transform(mover) = data_021fbe48;
    return 1;
}
CLEAN_AS(func_ov004_0223b0a8, FurnitureMover_Start)

/* func_ov004_0223b128 */
FurnitureMover *FurnitureMover_SetPosition(FurnitureMover *mover, const Vec3 *position)
{
    mover->position.x = position->x;
    mover->position.y = position->y;
    mover->position.z = position->z;
    return mover;
}
CLEAN_AS(func_ov004_0223b128, FurnitureMover_SetPosition)

/* func_ov004_0223b138: the model's transform. */
Mtx43 *FurnitureMover_Transform(FurnitureMover *mover)
{
    return transform(mover);
}
CLEAN_AS(func_ov004_0223b138, FurnitureMover_Transform)

/* func_ov004_0223b13c (at the room's end): the files forgotten and the heap deleted. */
void FurnitureMover_Release(FurnitureMover *mover)
{
    FurnitureMover_ForgetModel(mover);
    FurnitureMover_ForgetAnims(mover);
    FurnitureMover_DeleteHeap(mover);
}
CLEAN_AS(func_ov004_0223b13c, FurnitureMover_Release)

/* func_ov004_0223b158 (at the room's start): the heap, the animations, then the model. */
void FurnitureMover_Load(FurnitureMover *mover)
{
    FurnitureMover_CreateHeap(mover);
    FurnitureMover_LoadAnims(mover);
    FurnitureMover_LoadModel(mover);
}
CLEAN_AS(func_ov004_0223b158, FurnitureMover_Load)

/* func_ov004_0223b174 */
FurnitureMover *FurnitureMover_Destruct(FurnitureMover *mover)
{
    mover->moving = 0;
    AnimatedModel_DestructComplete(&mover->model);
    return mover;
}
CLEAN_AS(func_ov004_0223b174, FurnitureMover_Destruct)

/* func_ov004_0223b18c */
FurnitureMover *FurnitureMover_Construct(FurnitureMover *mover)
{
    AnimatedModel_Construct(&mover->model);
    mover->heap = NULL;
    mover->model_archive = NULL;
    mover->model_resource = NULL;
    mover->push_anim = NULL;
    mover->pull_anim = NULL;
    mover->idle_anim = NULL;
    mover->anim_archive = NULL;
    mover->moving = 0;
    mover->position.x = 0;
    mover->position.y = 0;
    mover->position.z = 0;
    return mover;
}
CLEAN_AS(func_ov004_0223b18c, FurnitureMover_Construct)

/* func_ov004_0223b1b8 (the model's hook before it is drawn): the node commands' hook set to
 * FurnitureMover_RootNodeHook (func_ov004_0223b1c8). */
void FurnitureMover_SetModelHooks(FurnitureMoverRenderState *state)
{
    state->hooks[NODE_COMMAND] = (u32) (uintptr_t) func_ov004_0223b1c8;
    state->hook_timings[NODE_COMMAND] = NODE_HOOK_TIMING;
}
CLEAN_AS(func_ov004_0223b1b8, FurnitureMover_SetModelHooks)

/* func_ov004_0223b1c8 (a node's hook): at the root node, the mover's position is the node's
 * translation through the mover's transform (copied into data_021fbe48). */
void FurnitureMover_RootNodeHook(FurnitureMoverRenderState *state)
{
    if (state == NULL || state->command[1] != ROOT_NODE) {
        return;
    }
    Vec3 translation = state->joint->translation;
    FurnitureMover *mover = state->object->user;
    if (mover == NULL) {
        return;
    }
    data_021fbe48 = *FurnitureMover_Transform(mover);
    Vec3 placed;
    MTX_MultVec43(&translation, &data_021fbe48, &placed);
    FurnitureMover_SetPosition(mover, &placed);
}
CLEAN_AS(func_ov004_0223b1c8, FurnitureMover_RootNodeHook)

/* func_ov004_0223b248 */
void FurnitureMoveFlag_Destruct(FurnitureMoveFlag *flag)
{
    flag->moving = 0;
}
CLEAN_AS(func_ov004_0223b248, FurnitureMoveFlag_Destruct)

/* func_ov004_0223b250 */
void FurnitureMoveFlag_Construct(FurnitureMoveFlag *flag)
{
    flag->moving = 0;
}
CLEAN_AS(func_ov004_0223b250, FurnitureMoveFlag_Construct)
