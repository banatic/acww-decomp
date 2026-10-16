/* Scene sound classes (sound_scene.h). */
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
extern const SoundSceneVtable data_0213ee7c; /* kind 50 */
extern const SoundSceneVtable data_0213ee48; /* kind 48 */
extern const SoundSceneVtable data_0213ee14; /* kind 47 */
extern const SoundSceneVtable data_0213ede0; /* kind 46 */
extern const SoundSceneVtable data_0213edac; /* kind 45 */
extern const SoundSceneVtable data_0213ed78; /* kind 44 */
extern const SoundSceneVtable data_0213ed44; /* kind 43 */
extern const SoundSceneVtable data_0213ed10; /* kind 42 */
extern const SoundSceneVtable data_0213ecdc; /* kind 41 */
extern const SoundSceneVtable data_0213eca8; /* kind 40 */
extern const SoundSceneVtable data_0213ec74; /* kind 35 */
extern const SoundSceneVtable data_0213e9d0; /* kind 34 */
extern const SoundSceneVtable data_0213ec0c; /* kind 33 */
extern const SoundSceneVtable data_0213ebd8; /* kind 32 */
extern const SoundSceneVtable data_0213eba4; /* kind 31 */

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

/* Player 4's heap (0x206c bytes), player 5's (0x31ac) and player 6's two (0x7a4c each). */
extern void func_020f41f4(SoundScene *scene);
extern void func_020f4178(SoundScene *scene);
extern void func_020f4130(SoundScene *scene);
/* The base class's frame update (slot 4): the sound system's frame (func_020f0fb0). */
extern void func_020f44f8(SoundScene *scene, int value);
/* Sets the byte at data_021fd238. */
extern void func_020f5a3c(char value);
/* Class 41's part (SoundScenePart): its constructor, destructor, set-up and switch. */
extern SoundScenePart *func_020f9624(SoundScenePart *part);
extern SoundScenePart *func_020f95f8(SoundScenePart *part);
extern void func_020f97dc(SoundScenePart *part, unsigned char stopped);
extern void func_020f95f0(SoundScenePart *part, unsigned char on);

/* The kinds of these classes. */
enum {
    KIND_31 = 31,
    KIND_32 = 32,
    KIND_33 = 33,
    KIND_34 = 34,
    KIND_35 = 35,
    KIND_40 = 40,
    KIND_41 = 41,
    KIND_42 = 42,
    KIND_43 = 43,
    KIND_44 = 44,
    KIND_45 = 45,
    KIND_46 = 46,
    KIND_47 = 47,
    KIND_48 = 48,
    KIND_50 = 50,
    KIND_51 = 51,
    KIND_52 = 52,
    KIND_60 = 60,
    KIND_99 = 99,
};

/* The sequence archive class 60 loads. */
#define SEQ_ARC_60 0x8f

/* The music class 41's part follows. */
#define SCENE41_MUSIC_FIRST 99
#define SCENE41_MUSIC_LAST 171

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

/* func_020f2840: slot 3: group 27 of the archive loaded, with no heap for player 0 and three
 * heaps for player 11. */
void SoundScene50_Start(SoundScene *scene)
{
    func_020f4220(scene, 0, 27);
    func_020f41a4(scene, 3);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2840, SoundScene50_Start)

/* func_020f2888: slot 1. */
SoundScene *SoundScene50_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ee7c;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2888, SoundScene50_DestructDelete)

/* func_020f28b4: slot 0. */
SoundScene *SoundScene50_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ee7c;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f28b4, SoundScene50_Destruct)

/* func_020f28d8 */
SoundScene *SoundScene50_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ee7c;
    scene->kind = KIND_50;
    func_020f5a3c(1);
    return scene;
}
CLEAN_AS(func_020f28d8, SoundScene50_Construct)

/* func_020f290c: slot 3: group 26 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene48_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 26);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f290c, SoundScene48_Start)

/* func_020f2954: slot 1. */
SoundScene *SoundScene48_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ee48;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2954, SoundScene48_DestructDelete)

/* func_020f2980: slot 0. */
SoundScene *SoundScene48_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ee48;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f2980, SoundScene48_Destruct)

/* func_020f29a4 */
SoundScene *SoundScene48_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ee48;
    scene->kind = KIND_48;
    return scene;
}
CLEAN_AS(func_020f29a4, SoundScene48_Construct)

/* func_020f29d0: slot 3: group 25 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene47_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 25);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f29d0, SoundScene47_Start)

/* func_020f2a18: slot 1. */
SoundScene *SoundScene47_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ee14;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2a18, SoundScene47_DestructDelete)

/* func_020f2a44: slot 0. */
SoundScene *SoundScene47_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ee14;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f2a44, SoundScene47_Destruct)

/* func_020f2a68 */
SoundScene *SoundScene47_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ee14;
    scene->kind = KIND_47;
    return scene;
}
CLEAN_AS(func_020f2a68, SoundScene47_Construct)

/* func_020f2a94: slot 3: group 24 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene46_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 24);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2a94, SoundScene46_Start)

/* func_020f2adc: slot 1. */
SoundScene *SoundScene46_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ede0;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2adc, SoundScene46_DestructDelete)

/* func_020f2b08: slot 0. */
SoundScene *SoundScene46_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ede0;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f2b08, SoundScene46_Destruct)

/* func_020f2b2c */
SoundScene *SoundScene46_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ede0;
    scene->kind = KIND_46;
    return scene;
}
CLEAN_AS(func_020f2b2c, SoundScene46_Construct)

/* func_020f2b58: slot 3: group 23 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene45_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 23);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2b58, SoundScene45_Start)

/* func_020f2ba0: slot 1. */
SoundScene *SoundScene45_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213edac;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2ba0, SoundScene45_DestructDelete)

/* func_020f2bcc: slot 0. */
SoundScene *SoundScene45_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213edac;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f2bcc, SoundScene45_Destruct)

/* func_020f2bf0 */
SoundScene *SoundScene45_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213edac;
    scene->kind = KIND_45;
    return scene;
}
CLEAN_AS(func_020f2bf0, SoundScene45_Construct)

/* func_020f2c1c: slot 3: group 22 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene44_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 22);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2c1c, SoundScene44_Start)

/* func_020f2c64: slot 1. */
SoundScene *SoundScene44_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ed78;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2c64, SoundScene44_DestructDelete)

/* func_020f2c90: slot 0. */
SoundScene *SoundScene44_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ed78;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f2c90, SoundScene44_Destruct)

/* func_020f2cb4 */
SoundScene *SoundScene44_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ed78;
    scene->kind = KIND_44;
    return scene;
}
CLEAN_AS(func_020f2cb4, SoundScene44_Construct)

/* func_020f2ce0: slot 3: group 21 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene43_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 21);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2ce0, SoundScene43_Start)

/* func_020f2d28: slot 1. */
SoundScene *SoundScene43_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ed44;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2d28, SoundScene43_DestructDelete)

/* func_020f2d54: slot 0. */
SoundScene *SoundScene43_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ed44;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f2d54, SoundScene43_Destruct)

/* func_020f2d78 */
SoundScene *SoundScene43_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ed44;
    scene->kind = KIND_43;
    return scene;
}
CLEAN_AS(func_020f2d78, SoundScene43_Construct)

/* func_020f2da4: slot 3: group 20 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene42_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 20);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2da4, SoundScene42_Start)

/* func_020f2dec: slot 1. */
SoundScene *SoundScene42_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ed10;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2dec, SoundScene42_DestructDelete)

/* func_020f2e18: slot 0. */
SoundScene *SoundScene42_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ed10;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f2e18, SoundScene42_Destruct)

/* func_020f2e3c */
SoundScene *SoundScene42_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ed10;
    scene->kind = KIND_42;
    return scene;
}
CLEAN_AS(func_020f2e3c, SoundScene42_Construct)

/* func_020f2ed4: slot 3: group 19 of the archive loaded, with 0x2a824 bytes for player 0 and the
 * heap of player 4. */
void SoundScene41_Start(SoundScene41 *scene)
{
    func_020f4220(&scene->base, 0x2a824, 19);
    func_020f41f4(&scene->base);
    func_020f4038(&scene->base);
    finish_start();
}
CLEAN_AS(func_020f2ed4, SoundScene41_Start)

/* func_020f2eb0: slot 4: the base class's frame update, then the part's. */
void SoundScene41_Update(SoundScene41 *scene, int value)
{
    func_020f44f8(&scene->base, value);
    scene->part.vtable->update(&scene->part);
}
CLEAN_AS(func_020f2eb0, SoundScene41_Update)

/* func_020f2e68: slot 10, told of the music (`stopped`, `music` as SoundSceneVtable's
 * on_music): the part is turned on for music 99 to 171 and set up with `stopped`, and turned
 * off for any other. */
void SoundScene41_OnMusic(SoundScene41 *scene, int stopped, unsigned int music)
{
    if (music >= SCENE41_MUSIC_FIRST && music <= SCENE41_MUSIC_LAST) {
        /* QUIRK: the part keeps `stopped` as a byte. */
        func_020f97dc(&scene->part, (unsigned char) stopped);
        func_020f95f0(&scene->part, 1);
    } else {
        func_020f95f0(&scene->part, 0);
    }
}
CLEAN_AS(func_020f2e68, SoundScene41_OnMusic)

/* func_020f2f1c: slot 1. */
SoundScene41 *SoundScene41_DestructDelete(SoundScene41 *scene)
{
    scene->base.vtable = &data_0213ecdc;
    func_020f95f8(&scene->part);
    func_020f4514(&scene->base);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2f1c, SoundScene41_DestructDelete)

/* func_020f2f54: slot 0. */
SoundScene41 *SoundScene41_Destruct(SoundScene41 *scene)
{
    scene->base.vtable = &data_0213ecdc;
    func_020f95f8(&scene->part);
    func_020f4514(&scene->base);
    return scene;
}
CLEAN_AS(func_020f2f54, SoundScene41_Destruct)

/* func_020f2f84 */
SoundScene41 *SoundScene41_Construct(SoundScene41 *scene)
{
    func_020f45c4(&scene->base);
    scene->base.vtable = &data_0213ecdc;
    func_020f9624(&scene->part);
    scene->base.kind = KIND_41;
    return scene;
}
CLEAN_AS(func_020f2f84, SoundScene41_Construct)

/* func_020f2fb8: slot 3: group 18 of the archive loaded, with 0x245c0 bytes for player 0 and the
 * heap of player 4. */
void SoundScene40_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x245c0, 18);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f2fb8, SoundScene40_Start)

/* func_020f3000: slot 1. */
SoundScene *SoundScene40_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eca8;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3000, SoundScene40_DestructDelete)

/* func_020f302c: slot 0. */
SoundScene *SoundScene40_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eca8;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f302c, SoundScene40_Destruct)

/* func_020f3050 */
SoundScene *SoundScene40_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eca8;
    scene->kind = KIND_40;
    return scene;
}
CLEAN_AS(func_020f3050, SoundScene40_Construct)

/* func_020f307c: slot 3: group 17 of the archive loaded, with 0x232f4 bytes for player 0 and the
 * heap of player 4. */
void SoundScene35_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x232f4, 17);
    func_020f41f4(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f307c, SoundScene35_Start)

/* func_020f30c4: slot 1. */
SoundScene *SoundScene35_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ec74;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f30c4, SoundScene35_DestructDelete)

/* func_020f30f0: slot 0. */
SoundScene *SoundScene35_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ec74;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f30f0, SoundScene35_Destruct)

/* func_020f3114 */
SoundScene *SoundScene35_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ec74;
    scene->kind = KIND_35;
    return scene;
}
CLEAN_AS(func_020f3114, SoundScene35_Construct)

/* func_020f3140: slot 3: group 16 of the archive loaded, with 0x232f4 bytes for player 0 and the
 * heaps of players 4, 5 and 6. */
void SoundScene34_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x232f4, 16);
    func_020f41f4(scene);
    func_020f4178(scene);
    func_020f4130(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f3140, SoundScene34_Start)

/* func_020f3198: slot 1. */
SoundScene *SoundScene34_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213e9d0;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3198, SoundScene34_DestructDelete)

/* func_020f31c4: slot 0. */
SoundScene *SoundScene34_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213e9d0;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f31c4, SoundScene34_Destruct)

/* func_020f31e8 */
SoundScene *SoundScene34_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213e9d0;
    scene->kind = KIND_34;
    return scene;
}
CLEAN_AS(func_020f31e8, SoundScene34_Construct)

/* func_020f3214: slot 3: group 15 of the archive loaded, with 0x232f4 bytes for player 0 and the
 * heaps of players 4, 5 and 6. */
void SoundScene33_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x232f4, 15);
    func_020f41f4(scene);
    func_020f4178(scene);
    func_020f4130(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f3214, SoundScene33_Start)

/* func_020f326c: slot 1. */
SoundScene *SoundScene33_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ec0c;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f326c, SoundScene33_DestructDelete)

/* func_020f3298: slot 0. */
SoundScene *SoundScene33_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ec0c;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f3298, SoundScene33_Destruct)

/* func_020f32bc */
SoundScene *SoundScene33_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ec0c;
    scene->kind = KIND_33;
    return scene;
}
CLEAN_AS(func_020f32bc, SoundScene33_Construct)

/* func_020f32e8: slot 3: group 14 of the archive loaded, with 0x232f4 bytes for player 0 and the
 * heaps of players 4, 5 and 6. */
void SoundScene32_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x232f4, 14);
    func_020f41f4(scene);
    func_020f4178(scene);
    func_020f4130(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f32e8, SoundScene32_Start)

/* func_020f3340: slot 1. */
SoundScene *SoundScene32_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ebd8;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3340, SoundScene32_DestructDelete)

/* func_020f336c: slot 0. */
SoundScene *SoundScene32_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ebd8;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f336c, SoundScene32_Destruct)

/* func_020f3390 */
SoundScene *SoundScene32_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ebd8;
    scene->kind = KIND_32;
    return scene;
}
CLEAN_AS(func_020f3390, SoundScene32_Construct)

/* func_020f33bc: slot 3: group 13 of the archive loaded, with 0x232f4 bytes for player 0 and the
 * heaps of players 4, 5 and 6. */
void SoundScene31_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x232f4, 13);
    func_020f41f4(scene);
    func_020f4178(scene);
    func_020f4130(scene);
    func_020f4038(scene);
    finish_start();
}
CLEAN_AS(func_020f33bc, SoundScene31_Start)

/* func_020f3414: slot 1. */
SoundScene *SoundScene31_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eba4;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3414, SoundScene31_DestructDelete)
