/* The animations and sounds of the room objects (room_object_anims.h). */
#include "room_object_anims.h"

#include <stdint.h>

#include "clean.h"
#include "furniture_model.h"
#include "main/lookups.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "furniture_sounds.h"
#include "main/animated_model.h"
#include "main/frame_ctrl.h"
#include "main/item_info.h"
#include "main/model_anim.h"
#include "main/model_object.h"
#include "main/model_pool.h"
#include "main/unit_type_info.h"
#include "room_shell.h"
#include "room_sound.h"

#define NO_SOUND 0xffff /* from RoomObject_MoveSound: none */
#define DEFAULT_MOVE_SOUND 0x4c1
#define FLOOR_SOUND_FIRST 0x1144 /* the item codes UnitTypeInfo_Word02 gives a move a sound for */
#define FLOOR_SOUND_LAST 0x1187
#define KEEP_FRAME 0xffff /* RoomObject_PlayAnimsFrom: each animation keeps its frame */

extern u8 data_020e54a8;
/* The pool the objects' slots are in (RoomObject.slot). */
extern ModelPool data_ov004_02259698;
/* The value FurnitureSounds_Sound3 and its kin give for no sound. */
extern u16 data_ov004_0224fd38;

/* An animation file, from the address AnimSet keeps. */
static const AnimFile *anim_file(int address)
{
    return (const AnimFile *) (uintptr_t) (u32) address;
}

/* The animations of the object's archive: each call reads the set again, as the game does. */
static AnimSet *anims_of(RoomObject *object)
{
    return FurnitureModel_Anims(&object->model_files);
}

/* The frame an animation keeps (bits 12-27 of its 20.12 fixed point frame). */
static u16 kept_frame(u32 frame)
{
    return (u16) (frame >> 12);
}

/* The frame to start `file` from: KEEP_FRAME keeps `current`, else `frame` held to the last.
 * QUIRK: a file without frames starts from 0xffff. */
static u16 start_frame(const AnimFile *file, u16 frame, u32 current)
{
    if (frame == KEEP_FRAME) {
        return kept_frame(current);
    }
    return (u16) (frame >= file->frames ? file->frames - 1 : frame);
}

/* func_ov004_0220ec8c: the sound of a move (NO_SOUND outside data_020e54a8 1): the one
 * UnitTypeInfo_Word02 gives the floor item of RoomShell_CarpetCode2 when it is one of
 * FLOOR_SOUND_FIRST to FLOOR_SOUND_LAST, else DEFAULT_MOVE_SOUND. */
int RoomObject_MoveSound(RoomObject *object)
{
    (void) object;
    if (data_020e54a8 != 1) {
        return NO_SOUND;
    }
    ItemCode *item = RoomShell_CarpetCode2();
    if (*item >= FLOOR_SOUND_FIRST && *item <= FLOOR_SOUND_LAST) {
        int sound = UnitTypeInfo_Word02(ItemInfo_IndoorUnk01(item));
        if (sound != NO_SOUND) {
            return sound;
        }
    }
    return DEFAULT_MOVE_SOUND;
}
CLEAN_AS(func_ov004_0220ec8c, RoomObject_MoveSound)

/* func_ov004_0220ffa4: the object's entry in the pool (ModelPool_Take), taken if it has none. */
int RoomObject_PoolEntry(RoomObject *object)
{
    return (int) (uintptr_t) ModelPool_Take(&data_ov004_02259698, &object->slot);
}
CLEAN_AS(func_ov004_0220ffa4, RoomObject_PoolEntry)

/* func_ov004_0220ffbc: advances the model's joint animation (when the model has one,
 * AnimatedModel_Anim) and the bound ones of RoomObject.anims, each of those giving its frame to its
 * target; whether all of them are at their end (FrameCtrl_IsDone). */
int RoomObject_AdvanceAnims(RoomObject *object)
{
    int anims_ended = 1;
    int joints_ended = 1;
    if (AnimatedModel_Anim(&object->model) != 0) {
        AnimatedModel_Update(&object->model);
        if (FrameCtrl_IsDone(&object->model.frames) == 0) {
            joints_ended = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        FurnitureAnim *anim = &object->anims[i];
        if (FurnitureAnim_Target(anim) != NULL) {
            FrameCtrl_Step(&anim->base.ctrl);
            anim->base.anim->frame = anim->base.ctrl.frame;
            if (FrameCtrl_IsDone(&anim->base.ctrl) == 0) {
                anims_ended = 0;
            }
        }
    }
    return anims_ended && joints_ended;
}
CLEAN_AS(func_ov004_0220ffbc, RoomObject_AdvanceAnims)

/* func_ov004_02210054: plays the animations of `variant` the archive has, by `mode` and
 * `speed`, from their last frame. */
void RoomObject_PlayAnimsFromEnd(RoomObject *object, int variant, int mode, int speed)
{
    int v = variant & 1;
    if (AnimSet_Anim10(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim10(anims_of(object), v));
        ModelAnim_Restart(&object->anims[ROOM_ANIM_VISIBILITY].base, ModelObject_RenderObject(&object->model.object),
                          (const u8 *) file, mode, speed, (u16) (file->frames - 1));
    }
    if (AnimSet_Anim08(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim08(anims_of(object), v));
        ModelAnim_Restart(&object->anims[ROOM_ANIM_MATERIAL].base, ModelObject_RenderObject(&object->model.object),
                          (const u8 *) file, mode, speed, (u16) (file->frames - 1));
    }
    if (AnimSet_Anim18(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim18(anims_of(object), v));
        ModelAnim_Restart(&object->anims[ROOM_ANIM_TEXCOORD].base, ModelObject_RenderObject(&object->model.object),
                          (const u8 *) file, mode, speed, (u16) (file->frames - 1));
    }
    if (AnimSet_Anim20(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim20(anims_of(object), v));
        void *model = ModelObject_RenderObject(&object->model.object);
        ModelAnim_RestartTextured(&object->anims[ROOM_ANIM_PATTERN].base, model, (const u8 *) file,
                                  FurnitureModel_Texture(&object->model_files), mode, speed, (u16) (file->frames - 1));
    }
    if (AnimSet_Anim00(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim00(anims_of(object), v));
        AnimatedModel_Start(&object->model, (const u8 *) file, mode, speed, (u16) (file->frames - 1), 0);
    }
}
CLEAN_AS(func_ov004_02210054, RoomObject_PlayAnimsFromEnd)

/* func_ov004_022101e4: plays the animations of `variant` the archive has, by `mode` and
 * `speed`, from `frame` (held to each one's last), or each from the frame it is at for
 * KEEP_FRAME. */
void RoomObject_PlayAnimsFrom(RoomObject *object, int variant, u8 mode, int speed, u16 frame)
{
    int v = variant & 1;
    if (AnimSet_Anim10(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim10(anims_of(object), v));
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_VISIBILITY];
        u16 start = start_frame(file, frame, anim->base.ctrl.frame);
        ModelAnim_Restart(&anim->base, ModelObject_RenderObject(&object->model.object), (const u8 *) file, mode, speed, start);
    }
    if (AnimSet_Anim08(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim08(anims_of(object), v));
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_MATERIAL];
        u16 start = start_frame(file, frame, anim->base.ctrl.frame);
        ModelAnim_Restart(&anim->base, ModelObject_RenderObject(&object->model.object), (const u8 *) file, mode, speed, start);
    }
    if (AnimSet_Anim18(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim18(anims_of(object), v));
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_TEXCOORD];
        u16 start = start_frame(file, frame, anim->base.ctrl.frame);
        ModelAnim_Restart(&anim->base, ModelObject_RenderObject(&object->model.object), (const u8 *) file, mode, speed, start);
    }
    if (AnimSet_Anim20(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim20(anims_of(object), v));
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_PATTERN];
        u16 start = start_frame(file, frame, anim->base.ctrl.frame);
        void *model = ModelObject_RenderObject(&object->model.object);
        ModelAnim_RestartTextured(&anim->base, model, (const u8 *) file, FurnitureModel_Texture(&object->model_files), mode,
                                  speed, start);
    }
    if (AnimSet_Anim00(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim00(anims_of(object), v));
        u16 start = start_frame(file, frame, object->joint_frame);
        AnimatedModel_Start(&object->model, (const u8 *) file, mode, speed, start, 0);
    }
}
CLEAN_AS(func_ov004_022101e4, RoomObject_PlayAnimsFrom)

/* func_ov004_0221041c: binds the animations of `variant` the archive has to the model (each
 * only when its binding, given the object's pool entry, succeeds) and plays them by `mode` and
 * `speed` from `frame`. */
void RoomObject_LoadAnims(RoomObject *object, int variant, u8 mode, int speed, u16 frame)
{
    void *entry = (void *) (uintptr_t) (u32) RoomObject_PoolEntry(object);
    int v = variant & 1;
    if (AnimSet_Anim10(anims_of(object), v)) {
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_VISIBILITY];
        G3dModel *resource = object->model_resource;
        if (ModelAnim_AllocJointAnim(&anim->base, (u8 *) resource, (Heap *) (uintptr_t) ModelPoolEntry_Heap(entry))) {
            ModelAnim_Start(&anim->base, (const u8 *) anim_file(AnimSet_Anim10(anims_of(object), v)), mode, speed, frame);
            ModelAnim_Attach(&anim->base, ModelObject_RenderObject(&object->model.object));
        }
    }
    if (AnimSet_Anim08(anims_of(object), v)) {
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_MATERIAL];
        G3dModel *resource = object->model_resource;
        if (ModelAnim_AllocMaterialAnim(&anim->base, (u8 *) resource, (Heap *) (uintptr_t) ModelPoolEntry_Heap(entry))) {
            ModelAnim_Start(&anim->base, (const u8 *) anim_file(AnimSet_Anim08(anims_of(object), v)), mode, speed, frame);
            ModelAnim_Attach(&anim->base, ModelObject_RenderObject(&object->model.object));
        }
    }
    if (AnimSet_Anim18(anims_of(object), v)) {
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_TEXCOORD];
        G3dModel *resource = object->model_resource;
        if (ModelAnim_AllocMaterialAnim(&anim->base, (u8 *) resource, (Heap *) (uintptr_t) ModelPoolEntry_Heap(entry))) {
            ModelAnim_Start(&anim->base, (const u8 *) anim_file(AnimSet_Anim18(anims_of(object), v)), mode, speed, frame);
            ModelAnim_Attach(&anim->base, ModelObject_RenderObject(&object->model.object));
        }
    }
    if (AnimSet_Anim20(anims_of(object), v)) {
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_PATTERN];
        G3dModel *resource = object->model_resource;
        if (ModelAnim_AllocMaterialAnim(&anim->base, (u8 *) resource, (Heap *) (uintptr_t) ModelPoolEntry_Heap(entry))) {
            const AnimFile *file = anim_file(AnimSet_Anim20(anims_of(object), v));
            ModelAnim_StartTextured(&anim->base, (const u8 *) file, FurnitureModel_Texture(&object->model_files), mode, speed,
                                    frame);
            ModelAnim_Attach(&anim->base, ModelObject_RenderObject(&object->model.object));
        }
    }
    if (AnimSet_Anim00(anims_of(object), v)) {
        if (AnimatedModel_LoadAnim(&object->model, (Heap *) (uintptr_t) ModelPoolEntry_Heap(entry))) {
            AnimatedModel_Start(&object->model, (const u8 *) anim_file(AnimSet_Anim00(anims_of(object), v)), mode, speed,
                                frame, 0);
            AnimatedModel_Attach(&object->model);
        }
    }
}
CLEAN_AS(func_ov004_0221041c, RoomObject_LoadAnims)

/* func_ov004_0221062c: the frame count of the first animation of `variant` the archive has, in
 * the order joints, material colours, texture coordinates, texture patterns, visibility; 0
 * without any. */
u16 RoomObject_AnimFrames(RoomObject *object, int variant)
{
    int v = variant & 1;
    if (AnimSet_Anim00(anims_of(object), v)) {
        return anim_file(AnimSet_Anim00(anims_of(object), v))->frames;
    }
    if (AnimSet_Anim08(anims_of(object), v)) {
        return anim_file(AnimSet_Anim08(anims_of(object), v))->frames;
    }
    if (AnimSet_Anim18(anims_of(object), v)) {
        return anim_file(AnimSet_Anim18(anims_of(object), v))->frames;
    }
    if (AnimSet_Anim20(anims_of(object), v)) {
        return anim_file(AnimSet_Anim20(anims_of(object), v))->frames;
    }
    if (AnimSet_Anim10(anims_of(object), v)) {
        return anim_file(AnimSet_Anim10(anims_of(object), v))->frames;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221062c, RoomObject_AnimFrames)

/* Plays `sound` at the object's centre (RoomSound_PlayAtB) unless it is no sound. */
static int play_sound(RoomObject *object, int sound)
{
    if (sound != data_ov004_0224fd38) {
        RoomSound_PlayAtB(&object->sound, sound, &object->sound.position);
        return 1;
    }
    return 0;
}

/* func_ov004_022106fc: plays the sound at 6 in the furniture's row (FurnitureSounds_Sound3);
 * whether there was one. Not for a preview. */
int RoomObject_PlaySound3(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    return play_sound(object, FurnitureSounds_Sound3(object->unk_284));
}
CLEAN_AS(func_ov004_022106fc, RoomObject_PlaySound3)

/* func_ov004_02210744: the same with the sound at 4 (FurnitureSounds_Sound2). */
int RoomObject_PlaySound2(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    return play_sound(object, FurnitureSounds_Sound2(object->unk_284));
}
CLEAN_AS(func_ov004_02210744, RoomObject_PlaySound2)

/* func_ov004_0221078c: the same with the sound at 2 (FurnitureSounds_Sound1). */
int RoomObject_PlaySound1(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    return play_sound(object, FurnitureSounds_Sound1(object->unk_284));
}
CLEAN_AS(func_ov004_0221078c, RoomObject_PlaySound1)

/* func_ov004_022107d4: the sound at 0 (FurnitureSounds_Sound0), played the other way
 * (RoomSound_PlayAt). */
int RoomObject_PlaySound0(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    int sound = FurnitureSounds_Sound0(object->unk_284);
    if (sound != data_ov004_0224fd38) {
        RoomSound_PlayAt(&object->sound, sound, &object->sound.position);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022107d4, RoomObject_PlaySound0)
