/* Objects that play sounds through a handle of NNS's sound player (sound_emitter.h). */
#include "sound_emitter.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"

static_assert(offsetof(SoundSourceVtable, update) == 0x10, "SoundSourceVtable layout");
static_assert(offsetof(SoundSource, flags) == 0x0a, "SoundSource layout");
static_assert(offsetof(SoundEmitterVtable, vfunc_10) == 0x10, "SoundEmitterVtable layout");
static_assert(sizeof(SoundEmitter) == 0x44, "SoundEmitter size");

/* Positions handed to the sound layer are taken relative to this point, and only while the
 * camera (data_021c67a4) exists. */
extern void *data_021c67a4;
extern Vec3 data_021c67b8;

/* The vtable of class 0x020d8414 and the base class's destructor (0x0213f074). */
extern const SoundEmitterVtable data_020d8414;
extern void func_020f5914(SoundEmitter *emitter);

extern int func_020f5748(SoundEmitter *emitter, int number, int volume, int arg);
extern int func_020f545c(SoundEmitter *emitter, u32 number, u32 flag);
extern int func_020f56a4(SoundEmitter *emitter, int number, int arg2, int arg3);

extern void func_020f503c(void *sound, s16 value);
extern void func_020f4f80(void *sound);
/* The first argument is not read. */
extern void func_020f4fb8(void *sound, const Vec3 *pos);
extern void func_020f5054(void *sound, int number, const Vec3 *pos);
extern void func_020f52a0(void *sound, int number, const Vec3 *pos);
extern void func_020f5360(void *sound, int owner);
extern void func_020f4d4c(void *list);
extern void func_020f4f44(char *list);

/* `pos` relative to data_021c67b8. */
static Vec3 relative(const Vec3 *pos)
{
    Vec3 rel = {pos->x - data_021c67b8.x, pos->y - data_021c67b8.y, pos->z - data_021c67b8.z};
    return rel;
}

/* func_02004280: slot 1, stop what the handle plays and release it. */
void SoundSource_Release(SoundSource *source)
{
    source->vtable->release(source);
}
CLEAN_AS(func_02004280, SoundSource_Release)

/* func_02004290: slot 3, ask for sound `number` for this frame only. */
void SoundSource_Play(SoundSource *source, int number)
{
    source->vtable->play(source, number);
}
CLEAN_AS(func_02004290, SoundSource_Play)

/* func_020042a0: slot 2, ask for sound `number` and keep it playing while it is not asked
 * for again. */
void SoundSource_PlayHeld(SoundSource *source, int number)
{
    source->vtable->play_held(source, number);
}
CLEAN_AS(func_020042a0, SoundSource_PlayHeld)

/* func_020042b0: slot 4, the frame's update: start, stop or follow the sound at `pos` as it
 * was asked for. */
void SoundSource_Update(SoundSource *source, const Vec3 *pos)
{
    source->vtable->update(source, pos);
}
CLEAN_AS(func_020042b0, SoundSource_Update)

/* func_020042c0: slot 4 with the position relative to data_021c67b8, or with none. With a
 * position but no camera, nothing is updated. */
void SoundSource_UpdateAt(SoundSource *source, const Vec3 *pos)
{
    if (pos == NULL) {
        source->vtable->update(source, NULL);
        return;
    }
    if (data_021c67a4 == NULL) {
        return;
    }
    Vec3 rel = relative(pos);
    source->vtable->update(source, &rel);
}
CLEAN_AS(func_020042c0, SoundSource_UpdateAt)

/* func_0200430c: slot 0, set up the handle and clear the number and flags. QUIRK: the slot
 * returns nothing; the result is whatever it leaves behind, and no caller uses it. */
int SoundSource_Init(SoundSource *source)
{
    return source->vtable->init(source);
}
CLEAN_AS(func_0200430c, SoundSource_Init)

/* func_0200431c: always yes (overlay 4 asks before starting a list of point sounds). */
int PointSound_CanStartList(void)
{
    return 1;
}
CLEAN_AS(func_0200431c, PointSound_CanStartList)

/* func_02004320: write `value` to variable 0 of the sound's player. */
void PointSound_SetVariable(void *sound, s16 value)
{
    func_020f503c(sound, value);
}
CLEAN_AS(func_02004320, PointSound_SetVariable)

/* func_02004328: take the sound out of the list, stop it and release its handle. */
void PointSound_Release(char *sound)
{
    func_020f4f80(sound);
}
CLEAN_AS(func_02004328, PointSound_Release)

/* func_02004330: set the volume of the sound layer's handle at data_021fd1f8 from `pos` (the
 * sound itself is passed on but not read). Without a position or a camera nothing happens. */
void PointSound_UpdateVolumeAt(void *sound, const Vec3 *pos)
{
    if (pos == NULL || data_021c67a4 == NULL) {
        return;
    }
    Vec3 rel = relative(pos);
    func_020f4fb8(sound, &rel);
}
CLEAN_AS(func_02004330, PointSound_UpdateVolumeAt)

/* func_02004384: play sound `number` at `pos`. Without a position or a camera nothing
 * happens. */
void PointSound_PlayAt(void *sound, int number, const Vec3 *pos)
{
    if (pos == NULL || data_021c67a4 == NULL) {
        return;
    }
    Vec3 rel = relative(pos);
    func_020f5054(sound, number, &rel);
}
CLEAN_AS(func_02004384, PointSound_PlayAt)

/* func_020043c4: the same through the sound layer's other entry (numbers 0x3ea to 0x42f are
 * queued, the others started at once). */
void PointSound_PlayAtB(void *sound, int number, const Vec3 *pos)
{
    if (pos == NULL || data_021c67a4 == NULL) {
        return;
    }
    Vec3 rel = relative(pos);
    func_020f52a0(sound, number, &rel);
}
CLEAN_AS(func_020043c4, PointSound_PlayAtB)

/* func_02004404: set the sound up; `owner` becomes the sound layer's current list
 * (data_021fd234). */
void PointSound_Init(void *sound, int owner)
{
    func_020f5360(sound, owner);
}
CLEAN_AS(func_02004404, PointSound_Init)

/* func_0200440c: empty the list, stopping its sounds. */
void PointSound_FlushList(void *list)
{
    func_020f4d4c(list);
}
CLEAN_AS(func_0200440c, PointSound_FlushList)

/* func_02004414: start an empty list. */
void PointSound_StartList(char *list)
{
    func_020f4f44(list);
}
CLEAN_AS(func_02004414, PointSound_StartList)

/* func_0200441c: slot 4 (vtable offset 0x10). */
int SoundEmitter_Vfunc10(SoundEmitter *emitter)
{
    return emitter->vtable->vfunc_10(emitter);
}
CLEAN_AS(func_0200441c, SoundEmitter_Vfunc10)

/* func_0200442c: play sound `number`; the result is the sound layer's. */
int SoundEmitter_Play(SoundEmitter *emitter, int number, int volume, int arg)
{
    return func_020f5748(emitter, number, volume, arg);
}
CLEAN_AS(func_0200442c, SoundEmitter_Play)

/* func_0200443c: play `number` raised by 2 or 3 in turn (the emitter's flags at 0x3f keep
 * which came last), at volume 0x7f. */
void SoundEmitter_PlayAlternating(SoundEmitter *emitter, u32 number, u32 flag)
{
    func_020f545c(emitter, number, flag);
}
CLEAN_AS(func_0200443c, SoundEmitter_PlayAlternating)

/* Slot 3 with the position relative to data_021c67b8, or with none. With a position but no
 * camera, nothing is updated. */
static void update_at(SoundEmitter *emitter, const Vec3 *pos)
{
    if (pos == NULL) {
        emitter->vtable->update(emitter, NULL);
        return;
    }
    if (data_021c67a4 == NULL) {
        return;
    }
    Vec3 rel = relative(pos);
    emitter->vtable->update(emitter, &rel);
}

/* func_02004444: slot 3 at `pos` (update_at). */
void SoundEmitter_UpdateAt(SoundEmitter *emitter, const Vec3 *pos)
{
    update_at(emitter, pos);
}
CLEAN_AS(func_02004444, SoundEmitter_UpdateAt)

/* func_02004490: slot 2, stop. */
void SoundEmitter_Stop(SoundEmitter *emitter)
{
    emitter->vtable->stop(emitter);
}
CLEAN_AS(func_02004490, SoundEmitter_Stop)

/* func_020044a0: a second copy of SoundEmitter_Vfunc10. */
int SoundEmitter_Vfunc10B(SoundEmitter *emitter)
{
    return emitter->vtable->vfunc_10(emitter);
}
CLEAN_AS(func_020044a0, SoundEmitter_Vfunc10B)

/* func_020044b0: play sound `number` through the sound layer's other entry; 0 while the sound
 * state's byte 0x4d is 1. */
int SoundEmitter_PlayEx(SoundEmitter *emitter, int number, int arg2, int arg3)
{
    return func_020f56a4(emitter, number, arg2, arg3);
}
CLEAN_AS(func_020044b0, SoundEmitter_PlayEx)

/* func_020044c0: a second copy of SoundEmitter_Play. */
int SoundEmitter_PlayB(SoundEmitter *emitter, int number, int volume, int arg)
{
    return func_020f5748(emitter, number, volume, arg);
}
CLEAN_AS(func_020044c0, SoundEmitter_PlayB)

/* func_020044d0: a second copy of SoundEmitter_UpdateAt. */
void SoundEmitter_UpdateAtB(SoundEmitter *emitter, const Vec3 *pos)
{
    update_at(emitter, pos);
}
CLEAN_AS(func_020044d0, SoundEmitter_UpdateAtB)

/* func_0200451c: a second copy of SoundEmitter_Stop. */
void SoundEmitter_StopB(SoundEmitter *emitter)
{
    emitter->vtable->stop(emitter);
}
CLEAN_AS(func_0200451c, SoundEmitter_StopB)

/* func_02005198: the destructor of class 0x020d8414 (the field actor's emitter at 0x880): its
 * vtable, then the base's destructor. Returns the emitter. */
void *SoundEmitter_Destruct(SoundEmitter *emitter)
{
    emitter->vtable = &data_020d8414;
    func_020f5914(emitter);
    return emitter;
}
CLEAN_AS(func_02005198, SoundEmitter_Destruct)

/* func_020115ec: the deleting destructor of class 0x020d8414 (its vtable slot 1): its vtable,
 * the base's destructor, then the memory freed. Returns the emitter. */
void *SoundEmitter_DestructDelete(SoundEmitter *emitter)
{
    emitter->vtable = &data_020d8414;
    SoundEmitterClass_DestructBase((SoundEmitterObject *) emitter);
    Heap_OperatorDeleteB(emitter);
    return emitter;
}
CLEAN_AS(func_020115ec, SoundEmitter_DestructDelete)
