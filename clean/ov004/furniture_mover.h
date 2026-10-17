/* The room's furniture mover (the member at 0x1c4 of the room, data_ov004_022595c0;
 * RoomManager_Mover): when the player pushes or pulls a piece of furniture, a hidden animated
 * model (the model of furniture 0x3984 in its archive) plays "ft_push1" or "ft_pull1" from
 * "/ftr/anm/anm.arc", and the furniture follows the model's root node, placed by the mover's
 * transform (the furniture's start and its angle). One move at a time: a room object asks with
 * the flag it keeps (FurnitureMoveFlag, RoomObject.unk_250), and steps the move each frame until
 * the animation ends (room_object.c). "ft_kb_hw_def_anim", the third animation, is not played
 * here; room objects take it for their joints (room_object_02252ba8.c).
 *
 * Its files are loaded on a frame heap of its own (0x2800 bytes). */
#ifndef CLEAN_OV004_FURNITURE_MOVER_H
#define CLEAN_OV004_FURNITURE_MOVER_H

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "main/animated_model.h"
#include "types.h"

typedef struct FurnitureMover {
    u8 moving; /* 0x00 */
    u8 pad_01[3];
    Vec3 position;       /* 0x04: where the root node is, from the last draw */
    Heap *heap;          /* 0x10 */
    u8 *anim_archive;    /* 0x14: "/ftr/anm/anm.arc" */
    const u8 *push_anim; /* 0x18: "ft_push1" */
    const u8 *pull_anim; /* 0x1c: "ft_pull1" */
    const u8 *idle_anim; /* 0x20: "ft_kb_hw_def_anim" */
    u8 *model_archive;   /* 0x24: the archive of furniture 0x3984 */
    u8 *model_resource;  /* 0x28: its model */
    AnimatedModel model; /* 0x2c: as far as its anim, 0xb8 bytes (no ramp) */
} FurnitureMover;

/* The flag a room object keeps for its move: set while the mover moves it. */
typedef struct FurnitureMoveFlag {
    u8 moving;
} FurnitureMoveFlag;

/* The parts of NitroSystem's NNSG3dRenderObj and NNSG3dRS the model's hooks use. */
typedef struct FurnitureMoverRender {
    u8 unk_00[0x2c];
    FurnitureMover *user; /* 0x2c: what ModelObject_SetInitHook was given */
} FurnitureMoverRender;

typedef struct FurnitureMoverRenderState {
    const u8 *command;               /* 0x00: the command being run: byte 1 is its node */
    FurnitureMoverRender *object;    /* 0x04 */
    u32 flags;                       /* 0x08 */
    u32 hooks[0x20];                 /* 0x0c: each command's hook, 0 for none */
    u8 hook_timings[0x20];           /* 0x8c */
    u8 unk_ac[8];                    /* 0xac */
    const AnimatedModelJoint *joint; /* 0xb4: the node's transform */
} FurnitureMoverRenderState;

u32 FurnitureMover_IdleAnim(FurnitureMover *mover);
u32 FurnitureMover_PullAnim(FurnitureMover *mover);
u32 FurnitureMover_PushAnim(FurnitureMover *mover);
int FurnitureMover_ForgetModel(FurnitureMover *mover);
int FurnitureMover_LoadModel(FurnitureMover *mover);
int FurnitureMover_ForgetAnims(FurnitureMover *mover);
int FurnitureMover_LoadAnims(FurnitureMover *mover);
int FurnitureMover_DeleteHeap(FurnitureMover *mover);
int FurnitureMover_CreateHeap(FurnitureMover *mover);
int FurnitureMover_Step(FurnitureMover *mover, FurnitureMoveFlag *flag, Vec3 *position);
int FurnitureMover_StartPull(FurnitureMover *mover, FurnitureMoveFlag *flag, Vec3 *position, int angle);
int FurnitureMover_StartPush(FurnitureMover *mover, FurnitureMoveFlag *flag, Vec3 *position, int angle);
int FurnitureMover_Start(FurnitureMover *mover, const u8 *anim, FurnitureMoveFlag *flag, Vec3 *position, s16 angle);
FurnitureMover *FurnitureMover_SetPosition(FurnitureMover *mover, const Vec3 *position);
Mtx43 *FurnitureMover_Transform(FurnitureMover *mover);
void FurnitureMover_Release(FurnitureMover *mover);
void FurnitureMover_Load(FurnitureMover *mover);
FurnitureMover *FurnitureMover_Destruct(FurnitureMover *mover);
FurnitureMover *FurnitureMover_Construct(FurnitureMover *mover);
void FurnitureMover_SetModelHooks(FurnitureMoverRenderState *state);
void FurnitureMover_RootNodeHook(FurnitureMoverRenderState *state);
void FurnitureMoveFlag_Destruct(FurnitureMoveFlag *flag);
void FurnitureMoveFlag_Construct(FurnitureMoveFlag *flag);

#endif
