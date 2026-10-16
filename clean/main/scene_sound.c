/* The sound of the current scene and the sound layer's start-up and frame (scene_sound.h). */
#include "scene_sound.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/heap.h"
#include "calendar.h"
#include "clean.h"

static_assert(offsetof(SceneSoundVtable, vfunc_24) == 0x24, "SceneSoundVtable layout");

/* The current scene's sound object, or NULL. */
extern SceneSound *data_0213fff0;

/* The game's sound state (sound.h), its byte 0x60 seen as its own symbol, and the memory its
 * sound heap is made in. */
extern u8 data_021fd1bc[];
extern u8 data_021fd21c[];
extern u8 data_0213fff4[];
#define SOUND_HEAP_SIZE 0x80000

/* "/sound_data.sdat" */
extern const char data_020d72e0[];

/* 0 or 1; with any other value every scene gets the base class. */
extern u8 data_020e54a8;
/* While the camera exists the scene's sound is updated each frame, with this value. */
extern void *data_021c67a4;
extern int data_021c679c;
extern u8 *data_021c526c;

extern void func_0206e8d8(void);
extern void func_0206e904(void);
extern void func_020f2388(void *sys);
/* The original also passes 1 as a fifth argument, which the callee does not read. */
extern void func_020f23b4(void *sys, u8 *heap, u32 heap_size, const char *archive);
extern int func_02035bec(u8 *flags);

extern void func_0209def4(Time *now);
extern void func_0209e474(DateTime *now);
extern u8 func_020b65c4(void);
extern u8 func_020b22b8(void);
extern u8 func_020b22dc(void);
extern int func_020b6640(void);
extern int func_0203fc78(int event, const DateTime *when, int arg);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The constructors of the scene sound classes. */
extern void *func_020f2590(void *sound); /* the base class */
extern void *func_020f2664(void *sound);
extern void *func_020f2720(void *sound);
extern void *func_020f2814(void *sound);
extern void *func_020f28d8(void *sound);
extern void *func_020f29a4(void *sound);
extern void *func_020f2a68(void *sound);
extern void *func_020f2b2c(void *sound);
extern void *func_020f2bf0(void *sound);
extern void *func_020f2cb4(void *sound);
extern void *func_020f2d78(void *sound);
extern void *func_020f2e3c(void *sound);
extern void *func_020f2f84(void *sound); /* 0x38 bytes */
extern void *func_020f3050(void *sound);
extern void *func_020f3114(void *sound);
extern void *func_020f31e8(void *sound);
extern void *func_020f32bc(void *sound);
extern void *func_020f3390(void *sound);
extern void *func_020f3464(void *sound);
extern void *func_020f3538(void *sound);
extern void *func_020f35fc(void *sound);
extern void *func_020f36d0(void *sound);
extern void *func_020f3794(void *sound);
extern void *func_020f3858(void *sound);
extern void *func_020f391c(void *sound);
extern void *func_020f39e0(void *sound);
extern void *func_020f3be8(void *sound); /* 0x20 bytes */
extern void *func_020f3cd4(void *sound);
extern void *func_020f3dc4(void *sound);
extern void *func_020f3f88(void *sound);

typedef void *(*SceneSoundConstructor)(void *sound);

/* func_020045ac: slot 9 (vtable offset 0x24). */
void SceneSound_Vfunc24(int value)
{
    data_0213fff0->vtable->vfunc_24(data_0213fff0, value);
}
CLEAN_AS(func_020045ac, SceneSound_Vfunc24)

/* func_020045c8: the base class's slot 9, which does nothing. */
void SceneSound_BaseVfunc24(void) {}
CLEAN_AS(func_020045c8, SceneSound_BaseVfunc24)

/* func_020045dc: slot 8 (vtable offset 0x20). */
void SceneSound_Vfunc20(void)
{
    data_0213fff0->vtable->vfunc_20(data_0213fff0);
}
CLEAN_AS(func_020045dc, SceneSound_Vfunc20)

/* func_02004618: slot 7: set the keyboard's mode in the sound state (SoundSys_SetKeyboardMode)
 * and play its sound. */
int SceneSound_SetKeyboardMode(int mode)
{
    return data_0213fff0->vtable->set_keyboard_mode(data_0213fff0, mode);
}
CLEAN_AS(func_02004618, SceneSound_SetKeyboardMode)

/* func_0200468c: slot 5: stop; the sound state's byte 0x4d is set, which keeps further sounds
 * from playing. */
void SceneSound_Stop(void)
{
    data_0213fff0->vtable->stop(data_0213fff0);
}
CLEAN_AS(func_0200468c, SceneSound_Stop)

/* func_020046c4: unload the scene's sounds and delete the object. When any of the three
 * bytes func_02035bec looks at in data_021c526c's block (at 0x2d8) is set, the sound state's
 * byte 0x62 is set first, which keeps the unloading from going back to the saved heap
 * level. */
void SceneSound_Delete(void)
{
    if (data_0213fff0 == NULL) {
        return;
    }
    if (func_02035bec(data_021c526c + 0x2d0)) {
        data_021fd21c[2] = 1;
    }
    data_0213fff0->vtable->unload(data_0213fff0);
    if (data_0213fff0 != NULL) {
        data_0213fff0->vtable->destruct_delete(data_0213fff0);
    }
    data_0213fff0 = NULL;
}
CLEAN_AS(func_020046c4, SceneSound_Delete)

/* A new object of `size` bytes made by `construct`, or NULL when there is no memory. */
static SceneSound *make(u32 size, SceneSoundConstructor construct)
{
    void *memory = Heap_OperatorNewB(size);
    if (memory != NULL) {
        memory = construct(memory);
    }
    return memory;
}

/* The class of the scenes without one of their own. */
static SceneSound *make_default(void)
{
    if (data_020e54a8 != 0) {
        return make(0x20, func_020f3be8);
    }
    if (func_020b22b8() != 0 || func_020b22dc() != 0) {
        return make(8, func_020f3dc4);
    }
    if (func_020b6640() != 0) {
        return make(8, func_020f2664);
    }

    /* The clock's date checked for three events (func_0203fc78), each with its own copy. */
    DateTime now = {0};
    DateTime copy;
    func_0209e474(&now);
    MI_CpuCopy8(&now, &copy, sizeof(copy));
    if (func_0203fc78(0xf, &copy, 0) != 0) {
        return make(8, func_020f3cd4);
    }
    MI_CpuCopy8(&now, &copy, sizeof(copy));
    if (func_0203fc78(0x12, &copy, 0) != 0) {
        return make(8, func_020f3cd4);
    }
    MI_CpuCopy8(&now, &copy, sizeof(copy));
    if (func_0203fc78(0x13, &copy, 0) != 0 && now.hour < 2) {
        return make(8, func_020f3cd4);
    }
    return make(8, func_020f3f88);
}

/* The class of scene `scene`, `now` being the time of day. */
static SceneSound *make_for_scene(int scene, const Time *now)
{
    switch (scene) {
        case 6:
        case 7:
        case 8:
            return make(8, func_020f39e0);
        case 9:
            return make(8, func_020f391c);
        case 0xa:
            return make(8, func_020f3858);
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0x2f:
            return make(8, func_020f3794);
        case 0xf:
            return make(8, func_020f36d0);
        case 0x10:
            return make(8, func_020f35fc);
        case 0x1a:
            return make(8, func_020f3538);
        case 0x1b:
            return make(8, func_020f3464);
        case 0x1c:
            return make(8, func_020f3390);
        case 0x1d:
            return make(8, func_020f32bc);
        case 0x1e:
            return make(8, func_020f31e8);
        case 0x1f:
            return make(8, func_020f3114);
        case 0x20:
            return make(8, func_020f3050);
        case 0x21:
            return make(0x38, func_020f2f84);
        case 0x22:
            return make(8, func_020f2e3c);
        case 0x23:
        case 0x24:
            return make(8, func_020f2d78);
        case 0x25:
        case 0x26:
            return make(8, func_020f2cb4);
        case 0x27:
            return make(8, func_020f2bf0);
        case 0x28:
            /* One class from 8:00 to 16:59, another for the rest of the day. */
            if (now->hour >= 8 && now->hour <= 16) {
                return make(8, func_020f2a68);
            }
            return make(8, func_020f2b2c);
        case 0x29:
            return make(8, func_020f29a4);
        case 0x2c:
            return make(8, func_020f28d8);
        case 0x2d:
            return make(8, func_020f2814);
        case 0x2e:
        case 0x30:
            return make(8, func_020f2720);
        case 0x32:
            return make(8, func_020f2590);
        default:
            return make_default();
    }
}

/* func_0200471c: make the scene's sound object and start it. REQUIRES: there is memory for
 * it (the original starts it without checking). */
void SceneSound_Create(void)
{
    if (data_020e54a8 != 0 && data_020e54a8 != 1) {
        data_0213fff0 = make(8, func_020f2590);
    } else {
        Time now;
        func_0209def4(&now);
        data_0213fff0 = make_for_scene(func_020b65c4(), &now);
    }
    data_0213fff0->vtable->start(data_0213fff0);
}
CLEAN_AS(func_0200471c, SceneSound_Create)

/* func_02004b30: the sound layer's part of a frame: the sound set's poll, the sound state's
 * frame, then the scene's sound while the camera exists. */
void SoundLayer_Frame(void)
{
    func_0206e8d8();
    func_020f2388(data_021fd1bc);
    if (data_0213fff0 != NULL && data_021c67a4 != NULL) {
        data_0213fff0->vtable->update(data_0213fff0, data_021c679c);
    }
}
CLEAN_AS(func_02004b30, SoundLayer_Frame)

/* func_02004b70: the start-up: no scene sound yet, the sound state with its heap of
 * SOUND_HEAP_SIZE bytes at data_0213fff4 and the sound archive, then the sound set. */
void SoundLayer_Init(void)
{
    data_0213fff0 = NULL;
    func_020f23b4(data_021fd1bc, data_0213fff4, SOUND_HEAP_SIZE, data_020d72e0);
    func_0206e904();
}
CLEAN_AS(func_02004b70, SoundLayer_Init)
