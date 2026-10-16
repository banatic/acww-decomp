/* Scene sound classes 99, 60, 52 and 51 (sound_scene.h). */
#include "sound_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "heap.h"

/* The classes' vtables. */
extern const SoundSceneVtable data_0213ef4c; /* kind 99 */
extern const SoundSceneVtable data_0213ef18; /* kind 60 */
extern const SoundSceneVtable data_0213eee4; /* kind 52 */
extern const SoundSceneVtable data_0213eeb0; /* kind 51 */

/* The sound system. */
extern SoundSystem data_021fd1bc;

extern int NNS_SndHeapSaveState(void *heap);
/* The base class's constructor: the object made the system's scene, the volumes put back to
 * full; kind -1. */
extern SoundScene *func_020f45c4(SoundScene *scene);
/* The base class's destructor: no scene in the system, the scenes' heap emptied. */
extern SoundScene *func_020f4514(SoundScene *scene);
/* The constructor and destructor of the class (kind 1, vtable 0x0213ef80) class 60 derives
 * from. */
extern SoundScene *func_020f3fe0(SoundScene *scene);
extern SoundScene *func_020f3f14(SoundScene *scene);
/* The base class's loading: player 0's heap of `player_heap` bytes (unless the system's byte
 * 0x62 is set) and group `group` of the archive. */
extern void func_020f4220(SoundScene *scene, int player_heap, unsigned char group);
/* Player 12's two heaps, and `count` heaps for player 11. */
extern int func_020f4038(SoundScene *scene);
extern void func_020f41a4(SoundScene *scene, int count);
/* Every player that plays a scene's sounds stopped over `fade_frames`. */
extern void func_020f43f8(SoundScene *scene, int fade_frames);
/* A sound set's sequence stopped. */
extern void func_020f6700(void *set);

/* The kinds of these classes. */
enum {
    KIND_51 = 51,
    KIND_52 = 52,
    KIND_60 = 60,
    KIND_99 = 99,
};

/* The sequence archive class 60 loads. */
#define SEQ_ARC_60 0x8f

/* The end of each start: the sound heap's state saved, the players' heaps no longer kept. */
static void finish_start(void)
{
    NNS_SndHeapSaveState((void *) (uintptr_t) Sound_GetHeap());
    data_021fd1bc.unk_62 = 0;
}

/* func_020f2500: slot 3: group 29 of the archive loaded, with 0x2a824 bytes for player 0. */
void SoundScene99_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 29);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2500, SoundScene99_Start)

/* func_020f2540: slot 1. */
SoundScene *SoundScene99_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ef4c;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2540, SoundScene99_DestructDelete)

/* func_020f256c: slot 0. */
SoundScene *SoundScene99_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ef4c;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f256c, SoundScene99_Destruct)

/* func_020f2590 */
SoundScene *SoundScene99_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ef4c;
    scene->kind = KIND_99;
    return scene;
}
CLEAN_AS(func_020f2590, SoundScene99_Construct)

/* func_020f25bc: slot 3: group 4 of the archive loaded, with 0x21ef8 bytes for player 0 and
 * two heaps for player 11, then sequence archive 0x8f. */
void SoundScene60_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x21ef8, 4);
    func_020f41a4(scene, 2);
    func_020f4038(scene);
    NNS_SndHeapSaveState((void *) (uintptr_t) Sound_GetHeap());
    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_60);
    data_021fd1bc.unk_62 = 0;
}
CLEAN_AS(func_020f25bc, SoundScene60_Start)

/* func_020f2614: slot 1. */
SoundScene *SoundScene60_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ef18;
    func_020f3f14(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2614, SoundScene60_DestructDelete)

/* func_020f2640: slot 0. */
SoundScene *SoundScene60_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ef18;
    func_020f3f14(scene);
    return scene;
}
CLEAN_AS(func_020f2640, SoundScene60_Destruct)

/* func_020f2664 */
SoundScene *SoundScene60_Construct(SoundScene *scene)
{
    func_020f3fe0(scene);
    scene->vtable = &data_0213ef18;
    scene->kind = KIND_60;
    return scene;
}
CLEAN_AS(func_020f2664, SoundScene60_Construct)

/* func_020f2690: slot 3: as class 99's. */
void SoundScene52_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 29);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2690, SoundScene52_Start)

/* func_020f26d0: slot 1. */
SoundScene *SoundScene52_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eee4;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f26d0, SoundScene52_DestructDelete)

/* func_020f26fc: slot 0. */
SoundScene *SoundScene52_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eee4;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f26fc, SoundScene52_Destruct)

/* func_020f2720 */
SoundScene *SoundScene52_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eee4;
    scene->kind = KIND_52;
    return scene;
}
CLEAN_AS(func_020f2720, SoundScene52_Construct)

/* func_020f274c: slot 5: the sound set stopped, effects muted and the scene's players
 * stopped over 17 frames.
 * QUIRK: unlike the base class's stop, the object is not marked stopped and nothing is
 * returned. */
void SoundScene51_Stop(SoundScene *scene)
{
    func_020f6700(data_021fd1bc.sound_set);
    data_021fd1bc.muted = 1;
    func_020f43f8(scene, 0x11);
}
CLEAN_AS(func_020f274c, SoundScene51_Stop)

/* func_020f2784: slot 3: group 28 of the archive loaded, with no heap for player 0, then the
 * music faded in. */
void SoundScene51_Start(SoundScene *scene)
{
    func_020f4220(scene, 0, 28);
    func_020f4038(scene);
    finish_start();
    SoundSystem_FadeInMusic(&data_021fd1bc);
}
CLEAN_AS(func_020f2784, SoundScene51_Start)

/* func_020f27c4: slot 1. */
SoundScene *SoundScene51_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eeb0;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f27c4, SoundScene51_DestructDelete)

/* func_020f27f0: slot 0. */
SoundScene *SoundScene51_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eeb0;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f27f0, SoundScene51_Destruct)

/* func_020f2814 */
SoundScene *SoundScene51_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eeb0;
    scene->kind = KIND_51;
    return scene;
}
CLEAN_AS(func_020f2814, SoundScene51_Construct)
