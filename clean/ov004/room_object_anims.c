/* The animations and sounds of the room objects (room_object_anims.h). */
#include "room_object_anims.h"

#include <stdint.h>

#include "clean.h"
#include "furniture_model.h"
#include "main/lookups.h"
#include "room_object_methods.h"
#include "room_object_parts.h"

#define NO_SOUND 0xffff /* from RoomObject_MoveSound: none */
#define DEFAULT_MOVE_SOUND 0x4c1
#define FLOOR_SOUND_FIRST 0x1144 /* the item codes func_02031914 gives a move a sound for */
#define FLOOR_SOUND_LAST 0x1187
#define KEEP_FRAME 0xffff /* RoomObject_PlayAnimsFrom: each animation keeps its frame */

extern u8 data_020e54a8;
/* The pool the objects' slots are in (RoomObject.slot). */
extern u8 data_ov004_02259698[];
/* The value func_ov004_0223a730 and its kin give for no sound. */
extern u16 data_ov004_0224fd38;

extern ItemCode *func_ov004_022320d8(void);
extern u8 func_02062300(ItemCode *item);
extern u16 func_02031914(int index);
extern int func_0209d238(u8 *pool, u16 *slot);
extern u32 func_02054ec4(void *model);
extern void func_02054cdc(void *model);
extern int func_02056f94(void *anim);
extern void func_02056ffc(void *anim);
extern void *func_02055e00(void *model);
extern void func_02056440(FurnitureAnim *anim, void *model, const AnimFile *file, int mode, int speed, int frame);
extern void func_020563ec(FurnitureAnim *anim, void *model, const AnimFile *file, u8 *texture, int mode, int speed, int frame);
extern void func_02055060(void *model, const AnimFile *file, int mode, int speed, int frame, int a5);
extern int func_0209d324(void *entry);
extern int func_020564d0(FurnitureAnim *anim, G3dModel *resource, int a2);
extern int func_0205650c(FurnitureAnim *anim, G3dModel *resource, int a2);
extern int func_02055140(void *model, int a1);
extern void func_02056478(FurnitureAnim *anim, const AnimFile *file, u8 mode, int speed, u16 frame);
extern void func_02056424(FurnitureAnim *anim, const AnimFile *file, u8 *texture, u8 mode, int speed, u16 frame);
extern void func_02055050(void *model);
extern void func_020563dc(FurnitureAnim *anim, void *model);
extern int func_ov004_0223a730(int number);
extern int func_ov004_0223a740(int number);
extern int func_ov004_0223a750(int number);
extern u16 func_ov004_0223a760(int number);
extern void func_ov004_0223cf54(RoomSound *sound, int id, Vec3 *position);
extern void func_ov004_0223cf40(RoomSound *sound, int id, Vec3 *position);

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
 * func_02031914 gives the floor item of func_ov004_022320d8 when it is one of
 * FLOOR_SOUND_FIRST to FLOOR_SOUND_LAST, else DEFAULT_MOVE_SOUND. */
int RoomObject_MoveSound(RoomObject *object)
{
    (void) object;
    if (data_020e54a8 != 1) {
        return NO_SOUND;
    }
    ItemCode *item = func_ov004_022320d8();
    if (*item >= FLOOR_SOUND_FIRST && *item <= FLOOR_SOUND_LAST) {
        int sound = func_02031914(func_02062300(item));
        if (sound != NO_SOUND) {
            return sound;
        }
    }
    return DEFAULT_MOVE_SOUND;
}
CLEAN_AS(func_ov004_0220ec8c, RoomObject_MoveSound)

/* func_ov004_0220ffa4: the object's entry in the pool (func_0209d238), taken if it has none. */
int RoomObject_PoolEntry(RoomObject *object)
{
    return func_0209d238(data_ov004_02259698, &object->slot);
}
CLEAN_AS(func_ov004_0220ffa4, RoomObject_PoolEntry)

/* func_ov004_0220ffbc: advances the model's joint animation (when the model has one,
 * func_02054ec4) and the bound ones of RoomObject.anims, each of those giving its frame to its
 * target; whether all of them are at their end (func_02056f94). */
int RoomObject_AdvanceAnims(RoomObject *object)
{
    int anims_ended = 1;
    int joints_ended = 1;
    if (func_02054ec4(object->unk_538) != 0) {
        func_02054cdc(object->unk_538);
        if (func_02056f94(object->joint_anim) == 0) {
            joints_ended = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        FurnitureAnim *anim = &object->anims[i];
        if (FurnitureAnim_Target(anim) != NULL) {
            func_02056ffc(anim);
            *anim->target = anim->frame;
            if (func_02056f94(anim) == 0) {
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
        func_02056440(&object->anims[ROOM_ANIM_VISIBILITY], func_02055e00(object->unk_538), file, mode, speed,
                      (u16) (file->frames - 1));
    }
    if (AnimSet_Anim08(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim08(anims_of(object), v));
        func_02056440(&object->anims[ROOM_ANIM_MATERIAL], func_02055e00(object->unk_538), file, mode, speed,
                      (u16) (file->frames - 1));
    }
    if (AnimSet_Anim18(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim18(anims_of(object), v));
        func_02056440(&object->anims[ROOM_ANIM_TEXCOORD], func_02055e00(object->unk_538), file, mode, speed,
                      (u16) (file->frames - 1));
    }
    if (AnimSet_Anim20(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim20(anims_of(object), v));
        void *model = func_02055e00(object->unk_538);
        func_020563ec(&object->anims[ROOM_ANIM_PATTERN], model, file, FurnitureModel_Texture(&object->model_files), mode,
                      speed, (u16) (file->frames - 1));
    }
    if (AnimSet_Anim00(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim00(anims_of(object), v));
        func_02055060(object->unk_538, file, mode, speed, (u16) (file->frames - 1), 0);
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
        u16 start = start_frame(file, frame, anim->frame);
        func_02056440(anim, func_02055e00(object->unk_538), file, mode, speed, start);
    }
    if (AnimSet_Anim08(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim08(anims_of(object), v));
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_MATERIAL];
        u16 start = start_frame(file, frame, anim->frame);
        func_02056440(anim, func_02055e00(object->unk_538), file, mode, speed, start);
    }
    if (AnimSet_Anim18(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim18(anims_of(object), v));
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_TEXCOORD];
        u16 start = start_frame(file, frame, anim->frame);
        func_02056440(anim, func_02055e00(object->unk_538), file, mode, speed, start);
    }
    if (AnimSet_Anim20(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim20(anims_of(object), v));
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_PATTERN];
        u16 start = start_frame(file, frame, anim->frame);
        void *model = func_02055e00(object->unk_538);
        func_020563ec(anim, model, file, FurnitureModel_Texture(&object->model_files), mode, speed, start);
    }
    if (AnimSet_Anim00(anims_of(object), v)) {
        const AnimFile *file = anim_file(AnimSet_Anim00(anims_of(object), v));
        u16 start = start_frame(file, frame, object->joint_frame);
        func_02055060(object->unk_538, file, mode, speed, start, 0);
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
        if (func_020564d0(anim, resource, func_0209d324(entry))) {
            func_02056478(anim, anim_file(AnimSet_Anim10(anims_of(object), v)), mode, speed, frame);
            func_020563dc(anim, func_02055e00(object->unk_538));
        }
    }
    if (AnimSet_Anim08(anims_of(object), v)) {
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_MATERIAL];
        G3dModel *resource = object->model_resource;
        if (func_0205650c(anim, resource, func_0209d324(entry))) {
            func_02056478(anim, anim_file(AnimSet_Anim08(anims_of(object), v)), mode, speed, frame);
            func_020563dc(anim, func_02055e00(object->unk_538));
        }
    }
    if (AnimSet_Anim18(anims_of(object), v)) {
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_TEXCOORD];
        G3dModel *resource = object->model_resource;
        if (func_0205650c(anim, resource, func_0209d324(entry))) {
            func_02056478(anim, anim_file(AnimSet_Anim18(anims_of(object), v)), mode, speed, frame);
            func_020563dc(anim, func_02055e00(object->unk_538));
        }
    }
    if (AnimSet_Anim20(anims_of(object), v)) {
        FurnitureAnim *anim = &object->anims[ROOM_ANIM_PATTERN];
        G3dModel *resource = object->model_resource;
        if (func_0205650c(anim, resource, func_0209d324(entry))) {
            const AnimFile *file = anim_file(AnimSet_Anim20(anims_of(object), v));
            func_02056424(anim, file, FurnitureModel_Texture(&object->model_files), mode, speed, frame);
            func_020563dc(anim, func_02055e00(object->unk_538));
        }
    }
    if (AnimSet_Anim00(anims_of(object), v)) {
        if (func_02055140(object->unk_538, func_0209d324(entry))) {
            func_02055060(object->unk_538, anim_file(AnimSet_Anim00(anims_of(object), v)), mode, speed, frame, 0);
            func_02055050(object->unk_538);
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

/* Plays `sound` at the object's centre (func_ov004_0223cf54) unless it is no sound. */
static int play_sound(RoomObject *object, int sound)
{
    if (sound != data_ov004_0224fd38) {
        func_ov004_0223cf54(&object->sound, sound, &object->sound.position);
        return 1;
    }
    return 0;
}

/* func_ov004_022106fc: plays the sound at 6 in the furniture's row (func_ov004_0223a730);
 * whether there was one. Not for a preview. */
int RoomObject_PlaySound3(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    return play_sound(object, func_ov004_0223a730(object->unk_284));
}
CLEAN_AS(func_ov004_022106fc, RoomObject_PlaySound3)

/* func_ov004_02210744: the same with the sound at 4 (func_ov004_0223a740). */
int RoomObject_PlaySound2(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    return play_sound(object, func_ov004_0223a740(object->unk_284));
}
CLEAN_AS(func_ov004_02210744, RoomObject_PlaySound2)

/* func_ov004_0221078c: the same with the sound at 2 (func_ov004_0223a750). */
int RoomObject_PlaySound1(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    return play_sound(object, func_ov004_0223a750(object->unk_284));
}
CLEAN_AS(func_ov004_0221078c, RoomObject_PlaySound1)

/* func_ov004_022107d4: the sound at 0 (func_ov004_0223a760), played the other way
 * (func_ov004_0223cf40). */
int RoomObject_PlaySound0(RoomObject *object)
{
    if (RoomObject_Unk76CIs2(object)) {
        return 0;
    }
    int sound = func_ov004_0223a760(object->unk_284);
    if (sound != data_ov004_0224fd38) {
        func_ov004_0223cf40(&object->sound, sound, &object->sound.position);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022107d4, RoomObject_PlaySound0)
