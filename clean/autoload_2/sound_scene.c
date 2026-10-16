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
extern const SoundSceneVtable data_0213eb70; /* kind 30 */
extern const SoundSceneVtable data_0213eb3c; /* kind 24 */
extern const SoundSceneVtable data_0213eb08; /* kind 23 */
extern const SoundSceneVtable data_0213ead4; /* kind 22 */
extern const SoundSceneVtable data_0213eaa0; /* kind 21 */
extern const SoundSceneVtable data_0213ea6c; /* kind 20 */
extern const SoundSceneVtable data_0213ea38; /* kind 19 */
extern const SoundSceneVtable data_0213ea04; /* kind 10 */
extern const SoundSceneVtable data_0213ec40; /* kind 3 */
extern const SoundSceneVtable data_0213e99c; /* kind 2 */
extern const SoundSceneVtable data_0213ef80; /* kind 1 */

/* The sound system. */
extern SoundSystem data_021fd1bc;

extern int NNS_SndHeapSaveState(void *heap);
extern int NNS_SndHeapGetCurrentLevel(void *heap);
extern int NNS_SndPlayerCreateHeap(int player_no, void *heap, int size);
extern void NNS_SndPlayerSetPlayerVolume(int player_no, int volume);
/* Loads item 9 of the sound archive into the heap (one of the SDK's archive loads). */
extern int func_0210e160(int item, void *heap);
/* The base class's slots 7 (the keyboard's sounds for a mode loaded: sequence archive 0x85,
 * 0x86 or 0x87; returns 1) and 8 (the sound heap back to its saved state). */
extern int func_020f4338(SoundScene *scene, unsigned int mode);
extern void func_020f4318(SoundScene *scene);
/* The base class's constructor: the object made the system's scene, the volumes put back to
 * full; kind -1. */
extern SoundScene *func_020f45c4(SoundScene *scene);
/* The base class's destructor: no scene in the system, the scenes' heap emptied. */
extern SoundScene *func_020f4514(SoundScene *scene);
/* The base class's loading: player 0's heap of `player_heap` bytes (unless the system's byte
 * 0x62 is set) and group `group` of the archive. */
extern void func_020f4220(SoundScene *scene, int player_heap, unsigned char group);
/* `count` heaps for player 11. */
extern void func_020f41a4(SoundScene *scene, int count);
/* Every player that plays a scene's sounds stopped over `fade_frames`. */
extern void func_020f43f8(SoundScene *scene, int fade_frames);
/* A sound set's sequence stopped. */
extern void func_020f6700(void *set);

/* Player 4's heap (0x206c bytes) and player 5's (0x31ac). */
extern void func_020f41f4(SoundScene *scene);
extern void func_020f4178(SoundScene *scene);
/* The base class's frame update (slot 4): the sound system's frame (func_020f0fb0). */
extern void func_020f44f8(SoundScene *scene, int value);
/* Sets the byte at data_021fd238. */
extern void func_020f5a3c(char value);
/* Class 41's part (SoundScenePart): its constructor, destructor, set-up and switch. */
extern SoundScenePart *func_020f9624(SoundScenePart *part);
extern SoundScenePart *func_020f95f8(SoundScenePart *part);
/* The set-up of class 41's part and of class 10's (SoundScene10Part, its base class). */
extern void func_020f97dc(void *part, unsigned char stopped);
extern void func_020f95f0(SoundScenePart *part, unsigned char on);
/* Class 10's part (SoundScene10Part): its constructor and destructor. */
extern SoundScene10Part *func_020f9888(SoundScene10Part *part);
extern SoundScene10Part *func_020f9868(SoundScene10Part *part);

/* The kinds of these classes. */
enum {
    KIND_1 = 1,
    KIND_2 = 2,
    KIND_3 = 3,
    KIND_10 = 10,
    KIND_19 = 19,
    KIND_20 = 20,
    KIND_21 = 21,
    KIND_22 = 22,
    KIND_23 = 23,
    KIND_24 = 24,
    KIND_30 = 30,
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

/* The sequence archive class 60 loads (also class 1 and the classes derived from it). */
#define SEQ_ARC_60 0x8f
/* The sequence archive class 1's slot 9 loads for its value 1. */
#define SEQ_ARC_1_ALT 0xb2
/* The sequence archive class 10 loads. */
#define SEQ_ARC_10 0x90

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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
    NNS_SndHeapSaveState((void *) (uintptr_t) Sound_GetHeap());
    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_60);
    data_021fd1bc.unk_62 = 0;
}
CLEAN_AS(func_020f25bc, SoundScene60_Start)

/* func_020f2614: slot 1. */
SoundScene *SoundScene60_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ef18;
    SoundScene1_DestructBase(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f2614, SoundScene60_DestructDelete)

/* func_020f2640: slot 0. */
SoundScene *SoundScene60_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ef18;
    SoundScene1_DestructBase(scene);
    return scene;
}
CLEAN_AS(func_020f2640, SoundScene60_Destruct)

/* func_020f2664 */
SoundScene *SoundScene60_Construct(SoundScene *scene)
{
    SoundScene1_ConstructBase(scene);
    scene->vtable = &data_0213ef18;
    scene->kind = KIND_60;
    return scene;
}
CLEAN_AS(func_020f2664, SoundScene60_Construct)

/* func_020f2690: slot 3: as class 99's. */
void SoundScene52_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 29);
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(&scene->base);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer6Heaps(scene);
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer6Heaps(scene);
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer6Heaps(scene);
    SoundScene_CreatePlayer12Heaps(scene);
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
    SoundScene_CreatePlayer6Heaps(scene);
    SoundScene_CreatePlayer12Heaps(scene);
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

/* func_020f3440: slot 0. */
SoundScene *SoundScene31_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eba4;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f3440, SoundScene31_Destruct)

/* func_020f3464 */
SoundScene *SoundScene31_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eba4;
    scene->kind = KIND_31;
    return scene;
}
CLEAN_AS(func_020f3464, SoundScene31_Construct)

/* func_020f3490: slot 3: group 12 of the archive loaded, with 0x232f4 bytes for player 0 and the
 * heaps of players 4, 5 and 6. */
void SoundScene30_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x232f4, 12);
    func_020f41f4(scene);
    func_020f4178(scene);
    SoundScene_CreatePlayer6Heaps(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    finish_start();
}
CLEAN_AS(func_020f3490, SoundScene30_Start)

/* func_020f34e8: slot 1. */
SoundScene *SoundScene30_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eb70;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f34e8, SoundScene30_DestructDelete)

/* func_020f3514: slot 0. */
SoundScene *SoundScene30_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eb70;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f3514, SoundScene30_Destruct)

/* func_020f3538 */
SoundScene *SoundScene30_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eb70;
    scene->kind = KIND_30;
    return scene;
}
CLEAN_AS(func_020f3538, SoundScene30_Construct)

/* func_020f3564: slot 3: group 11 of the archive loaded, with 0x2a824 bytes for player 0 and the
 * heap of player 4. */
void SoundScene24_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 11);
    func_020f41f4(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    finish_start();
}
CLEAN_AS(func_020f3564, SoundScene24_Start)

/* func_020f35ac: slot 1. */
SoundScene *SoundScene24_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eb3c;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f35ac, SoundScene24_DestructDelete)

/* func_020f35d8: slot 0. */
SoundScene *SoundScene24_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eb3c;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f35d8, SoundScene24_Destruct)

/* func_020f35fc */
SoundScene *SoundScene24_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eb3c;
    scene->kind = KIND_24;
    return scene;
}
CLEAN_AS(func_020f35fc, SoundScene24_Construct)

/* func_020f3628: slot 3: group 10 of the archive loaded, with 0x2a824 bytes for player 0 and the
 * heaps of players 4, 5 and 6. */
void SoundScene23_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 10);
    func_020f41f4(scene);
    func_020f4178(scene);
    SoundScene_CreatePlayer6Heaps(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    finish_start();
}
CLEAN_AS(func_020f3628, SoundScene23_Start)

/* func_020f3680: slot 1. */
SoundScene *SoundScene23_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eb08;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3680, SoundScene23_DestructDelete)

/* func_020f36ac: slot 0. */
SoundScene *SoundScene23_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eb08;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f36ac, SoundScene23_Destruct)

/* func_020f36d0 */
SoundScene *SoundScene23_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eb08;
    scene->kind = KIND_23;
    return scene;
}
CLEAN_AS(func_020f36d0, SoundScene23_Construct)

/* func_020f36fc: slot 3: group 9 of the archive loaded, with 0x2a824 bytes for player 0 and the
 * heap of player 4. */
void SoundScene22_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 9);
    func_020f41f4(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    finish_start();
}
CLEAN_AS(func_020f36fc, SoundScene22_Start)

/* func_020f3744: slot 1. */
SoundScene *SoundScene22_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ead4;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3744, SoundScene22_DestructDelete)

/* func_020f3770: slot 0. */
SoundScene *SoundScene22_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ead4;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f3770, SoundScene22_Destruct)

/* func_020f3794 */
SoundScene *SoundScene22_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ead4;
    scene->kind = KIND_22;
    return scene;
}
CLEAN_AS(func_020f3794, SoundScene22_Construct)

/* func_020f37c0: slot 3: group 8 of the archive loaded, with 0x2a824 bytes for player 0 and the
 * heap of player 4. */
void SoundScene21_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 8);
    func_020f41f4(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    finish_start();
}
CLEAN_AS(func_020f37c0, SoundScene21_Start)

/* func_020f3808: slot 1. */
SoundScene *SoundScene21_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213eaa0;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3808, SoundScene21_DestructDelete)

/* func_020f3834: slot 0. */
SoundScene *SoundScene21_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213eaa0;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f3834, SoundScene21_Destruct)

/* func_020f3858 */
SoundScene *SoundScene21_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213eaa0;
    scene->kind = KIND_21;
    return scene;
}
CLEAN_AS(func_020f3858, SoundScene21_Construct)

/* func_020f3884: slot 3: group 7 of the archive loaded, with 0x2a824 bytes for player 0 and the
 * heap of player 4. */
void SoundScene20_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 7);
    func_020f41f4(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    finish_start();
}
CLEAN_AS(func_020f3884, SoundScene20_Start)

/* func_020f38cc: slot 1. */
SoundScene *SoundScene20_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ea6c;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f38cc, SoundScene20_DestructDelete)

/* func_020f38f8: slot 0. */
SoundScene *SoundScene20_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ea6c;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f38f8, SoundScene20_Destruct)

/* func_020f391c */
SoundScene *SoundScene20_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ea6c;
    scene->kind = KIND_20;
    return scene;
}
CLEAN_AS(func_020f391c, SoundScene20_Construct)

/* func_020f3948: slot 3: group 6 of the archive loaded, with 0x2a824 bytes for player 0 and the
 * heap of player 4. */
void SoundScene19_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x2a824, 6);
    func_020f41f4(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    finish_start();
}
CLEAN_AS(func_020f3948, SoundScene19_Start)

/* func_020f3990: slot 1. */
SoundScene *SoundScene19_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ea38;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3990, SoundScene19_DestructDelete)

/* func_020f39bc: slot 0. */
SoundScene *SoundScene19_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ea38;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f39bc, SoundScene19_Destruct)

/* func_020f39e0 */
SoundScene *SoundScene19_Construct(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ea38;
    scene->kind = KIND_19;
    return scene;
}
CLEAN_AS(func_020f39e0, SoundScene19_Construct)

/* func_020f3a0c: slot 8: the base class's (the sound heap back to its saved state, which drops
 * the keyboard's sounds), then sequence archive 0x90 and player 12's heaps loaded again. */
void SoundScene10_ReloadSounds(SoundScene10 *scene)
{
    func_020f4318(&scene->base);
    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_10);
    SoundScene_CreatePlayer12Heaps(&scene->base);
    NNS_SndHeapSaveState((void *) (uintptr_t) Sound_GetHeap());
    scene->stage = 1;
}
CLEAN_AS(func_020f3a0c, SoundScene10_ReloadSounds)

/* func_020f3a48: slot 7: the sound heap back to its level before sequence archive 0x90, then
 * the base class's (the keyboard's sounds for `mode` loaded).
 * QUIRK: the base class's result is not returned. */
void SoundScene10_SetKeyboardMode(SoundScene10 *scene, int mode)
{
    Sound_RestoreHeapLevel(scene->heap_level);
    func_020f4338(&scene->base, (unsigned int) mode);
    scene->stage = 2;
}
CLEAN_AS(func_020f3a48, SoundScene10_SetKeyboardMode)

/* func_020f3a80: slot 10, told of the music: the part set up with `stopped`, whatever the music
 * is. */
void SoundScene10_OnMusic(SoundScene10 *scene, unsigned char stopped)
{
    func_020f97dc(&scene->part, stopped);
}
CLEAN_AS(func_020f3a80, SoundScene10_OnMusic)

/* func_020f3a90: slot 4: the base class's frame update, then the part's. */
void SoundScene10_Update(SoundScene10 *scene, int value)
{
    func_020f44f8(&scene->base, value);
    scene->part.vtable->update((SoundScenePart *) &scene->part);
}
CLEAN_AS(func_020f3a90, SoundScene10_Update)

/* func_020f3ab4: slot 3: group 5 of the archive loaded, with 0x10ea0 bytes for player 0 and the
 * heaps of players 4, 5, 6, 17, 18 and 19; then item 9 of the archive loaded (func_0210e160)
 * and the heap's level kept, sequence archive 0x90 and player 12's heaps loaded on top, the
 * part set up as when the music stops and players 18 and 19 at volume 63. */
void SoundScene10_Start(SoundScene10 *scene)
{
    void *heap;

    func_020f4220(&scene->base, 0x10ea0, 5);
    func_020f41f4(&scene->base);
    func_020f4178(&scene->base);
    SoundScene_CreatePlayer6Heaps(&scene->base);
    SoundScene_CreatePlayer17Heaps(&scene->base);
    SoundScene_CreatePlayer18And19Heaps(&scene->base);

    heap = (void *) (uintptr_t) Sound_GetHeap();
    func_0210e160(9, heap);
    NNS_SndHeapSaveState(heap);
    /* QUIRK: the level is kept as a byte. */
    scene->heap_level = (u8) NNS_SndHeapGetCurrentLevel(heap);

    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_10);
    SoundScene_CreatePlayer12Heaps(&scene->base);
    NNS_SndHeapSaveState(heap);
    scene->stage = 1;
    data_021fd1bc.unk_62 = 0;

    func_020f97dc(&scene->part, 1);
    NNS_SndPlayerSetPlayerVolume(18, 63);
    NNS_SndPlayerSetPlayerVolume(19, 63);
}
CLEAN_AS(func_020f3ab4, SoundScene10_Start)

/* func_020f3b80: slot 1. */
SoundScene10 *SoundScene10_DestructDelete(SoundScene10 *scene)
{
    scene->base.vtable = &data_0213ea04;
    func_020f9868(&scene->part);
    func_020f4514(&scene->base);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3b80, SoundScene10_DestructDelete)

/* func_020f3bb8: slot 0. */
SoundScene10 *SoundScene10_Destruct(SoundScene10 *scene)
{
    scene->base.vtable = &data_0213ea04;
    func_020f9868(&scene->part);
    func_020f4514(&scene->base);
    return scene;
}
CLEAN_AS(func_020f3bb8, SoundScene10_Destruct)

/* func_020f3be8 */
SoundScene10 *SoundScene10_Construct(SoundScene10 *scene)
{
    func_020f45c4(&scene->base);
    scene->base.vtable = &data_0213ea04;
    func_020f9888(&scene->part);
    scene->base.kind = KIND_10;
    scene->stage = 0;
    return scene;
}
CLEAN_AS(func_020f3be8, SoundScene10_Construct)

/* func_020f3c24: slot 3: group 3 of the archive loaded, with 0x21ef8 bytes for player 0, two
 * heaps for player 11 and player 13's, then sequence archive 0x8f. */
void SoundScene3_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x21ef8, 3);
    func_020f41a4(scene, 2);
    SoundScene_CreatePlayer13Heap(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    NNS_SndHeapSaveState((void *) (uintptr_t) Sound_GetHeap());
    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_60);
    data_021fd1bc.unk_62 = 0;
}
CLEAN_AS(func_020f3c24, SoundScene3_Start)

/* func_020f3c84: slot 1. */
SoundScene *SoundScene3_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ec40;
    SoundScene1_DestructBase(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3c84, SoundScene3_DestructDelete)

/* func_020f3cb0: slot 0. */
SoundScene *SoundScene3_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ec40;
    SoundScene1_DestructBase(scene);
    return scene;
}
CLEAN_AS(func_020f3cb0, SoundScene3_Destruct)

/* Sets the sound set's halfword at 0x08 (func_020f6f80). */
extern void func_020f65bc(void *set, unsigned short value);

/* The value class 1's constructors (and those of classes 3 and 2) give the current sound set. */
#define SOUND_SET_VALUE_1 0xd1

/* func_020f3cd4: class 1's constructor, then the sound set given the same value again. */
SoundScene *SoundScene3_Construct(SoundScene *scene)
{
    SoundScene1_ConstructBase(scene);
    scene->vtable = &data_0213ec40;
    if (data_021fd1bc.sound_set != NULL) {
        func_020f65bc(data_021fd1bc.sound_set, SOUND_SET_VALUE_1);
    }
    scene->kind = KIND_3;
    return scene;
}
CLEAN_AS(func_020f3cd4, SoundScene3_Construct)

/* func_020f3d1c: slot 3: group 2 of the archive loaded, with 0x1f340 bytes for player 0 and two
 * heaps for player 11, then sequence archive 0x8f. */
void SoundScene2_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x1f340, 2);
    func_020f41a4(scene, 2);
    SoundScene_CreatePlayer12Heaps(scene);
    NNS_SndHeapSaveState((void *) (uintptr_t) Sound_GetHeap());
    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_60);
    data_021fd1bc.unk_62 = 0;
}
CLEAN_AS(func_020f3d1c, SoundScene2_Start)

/* func_020f3d74: slot 1. */
SoundScene *SoundScene2_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213e99c;
    SoundScene1_DestructBase(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3d74, SoundScene2_DestructDelete)

/* func_020f3da0: slot 0. */
SoundScene *SoundScene2_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213e99c;
    SoundScene1_DestructBase(scene);
    return scene;
}
CLEAN_AS(func_020f3da0, SoundScene2_Destruct)

/* func_020f3dc4: class 1's constructor, then the sound set given the same value again. */
SoundScene *SoundScene2_Construct(SoundScene *scene)
{
    SoundScene1_ConstructBase(scene);
    scene->vtable = &data_0213e99c;
    if (data_021fd1bc.sound_set != NULL) {
        func_020f65bc(data_021fd1bc.sound_set, SOUND_SET_VALUE_1);
    }
    scene->kind = KIND_2;
    return scene;
}
CLEAN_AS(func_020f3dc4, SoundScene2_Construct)

/* func_020f3e0c: slot 9: the sound heap back to its saved state, then sequence archive 0x8f
 * loaded for `value` 0, or 0xb2 for 1; any other value loads nothing. */
void SoundScene1_Vfunc24(SoundScene *scene, int value)
{
    (void) scene;
    Sound_RestoreHeapLevel(Sound_GetHeapLevel());
    if (value == 0) {
        SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_60);
    } else if (value == 1) {
        SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_1_ALT);
    }
}
CLEAN_AS(func_020f3e0c, SoundScene1_Vfunc24)

/* func_020f3e5c: slot 8: the base class's (the keyboard's sounds dropped), then sequence
 * archive 0x8f loaded again. */
void SoundScene1_Vfunc20(SoundScene *scene)
{
    func_020f4318(scene);
    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_60);
}
CLEAN_AS(func_020f3e5c, SoundScene1_Vfunc20)

/* func_020f3e84: slot 7: the sound heap back to its saved state (dropping sequence archive
 * 0x8f), then the base class's. */
int SoundScene1_SetKeyboardMode(SoundScene *scene, int mode)
{
    Sound_RestoreHeapLevel(Sound_GetHeapLevel());
    return func_020f4338(scene, (unsigned int) mode);
}
CLEAN_AS(func_020f3e84, SoundScene1_SetKeyboardMode)

/* func_020f3eb4: slot 3: group 1 of the archive loaded, with 0x21ef8 bytes for player 0, three
 * heaps for player 11 and player 13's, then sequence archive 0x8f. */
void SoundScene1_Start(SoundScene *scene)
{
    func_020f4220(scene, 0x21ef8, 1);
    func_020f41a4(scene, 3);
    SoundScene_CreatePlayer13Heap(scene);
    SoundScene_CreatePlayer12Heaps(scene);
    NNS_SndHeapSaveState((void *) (uintptr_t) Sound_GetHeap());
    SoundSystem_LoadSeqArc(&data_021fd1bc, SEQ_ARC_60);
    data_021fd1bc.unk_62 = 0;
}
CLEAN_AS(func_020f3eb4, SoundScene1_Start)

/* func_020f3f14: the destructor the derived classes (60, 3 and 2) call. */
SoundScene *SoundScene1_DestructBase(SoundScene *scene)
{
    scene->vtable = &data_0213ef80;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f3f14, SoundScene1_DestructBase)

/* func_020f3f38: slot 1. */
SoundScene *SoundScene1_DestructDelete(SoundScene *scene)
{
    scene->vtable = &data_0213ef80;
    func_020f4514(scene);
    Heap_OperatorDeleteB(scene);
    return scene;
}
CLEAN_AS(func_020f3f38, SoundScene1_DestructDelete)

/* func_020f3f64: slot 0; the same as func_020f3f14. */
SoundScene *SoundScene1_Destruct(SoundScene *scene)
{
    scene->vtable = &data_0213ef80;
    func_020f4514(scene);
    return scene;
}
CLEAN_AS(func_020f3f64, SoundScene1_Destruct)

/* Class 1's construction: the current sound set (if any) given value 0xd1, the byte at
 * data_021fd238 set and the music's arrangement back to 0. */
static void construct_kind_1(SoundScene *scene)
{
    func_020f45c4(scene);
    scene->vtable = &data_0213ef80;
    if (data_021fd1bc.sound_set != NULL) {
        func_020f65bc(data_021fd1bc.sound_set, SOUND_SET_VALUE_1);
    }
    scene->kind = KIND_1;
    func_020f5a3c(1);
    data_021fd1bc.arrangement = 0;
}

/* func_020f3f88: the constructor clean/main/scene_sound.c calls. */
SoundScene *SoundScene1_Construct(SoundScene *scene)
{
    construct_kind_1(scene);
    return scene;
}
CLEAN_AS(func_020f3f88, SoundScene1_Construct)

/* func_020f3fe0: the constructor the derived classes (60, 3 and 2) call; the same as
 * func_020f3f88. */
SoundScene *SoundScene1_ConstructBase(SoundScene *scene)
{
    construct_kind_1(scene);
    return scene;
}
CLEAN_AS(func_020f3fe0, SoundScene1_ConstructBase)

/* func_020f4038: player 12's two heaps of 0x8cc bytes; the result is the second one's. */
int SoundScene_CreatePlayer12Heaps(SoundScene *scene)
{
    void *heap = (void *) (uintptr_t) Sound_GetHeap();

    (void) scene;
    NNS_SndPlayerCreateHeap(12, heap, 0x8cc);
    return NNS_SndPlayerCreateHeap(12, heap, 0x8cc);
}
CLEAN_AS(func_020f4038, SoundScene_CreatePlayer12Heaps)

/* func_020f4080: player 13's heap of 0x1f4c bytes. */
void SoundScene_CreatePlayer13Heap(SoundScene *scene)
{
    (void) scene;
    NNS_SndPlayerCreateHeap(13, (void *) (uintptr_t) Sound_GetHeap(), 0x1f4c);
}
CLEAN_AS(func_020f4080, SoundScene_CreatePlayer13Heap)

/* func_020f40ac: player 18's heap of 0x5ecc bytes and player 19's of 0x46bc. */
void SoundScene_CreatePlayer18And19Heaps(SoundScene *scene)
{
    void *heap = (void *) (uintptr_t) Sound_GetHeap();

    (void) scene;
    NNS_SndPlayerCreateHeap(18, heap, 0x5ecc);
    NNS_SndPlayerCreateHeap(19, heap, 0x46bc);
}
CLEAN_AS(func_020f40ac, SoundScene_CreatePlayer18And19Heaps)

/* func_020f40e8: player 17's four heaps of 0x356c bytes. */
void SoundScene_CreatePlayer17Heaps(SoundScene *scene)
{
    void *heap = (void *) (uintptr_t) Sound_GetHeap();

    (void) scene;
    for (int i = 0; i < 4; i++) {
        NNS_SndPlayerCreateHeap(17, heap, 0x356c);
    }
}
CLEAN_AS(func_020f40e8, SoundScene_CreatePlayer17Heaps)

/* func_020f4130: player 6's two heaps of 0x7a4c bytes. */
void SoundScene_CreatePlayer6Heaps(SoundScene *scene)
{
    void *heap = (void *) (uintptr_t) Sound_GetHeap();

    (void) scene;
    NNS_SndPlayerCreateHeap(6, heap, 0x7a4c);
    NNS_SndPlayerCreateHeap(6, heap, 0x7a4c);
}
CLEAN_AS(func_020f4130, SoundScene_CreatePlayer6Heaps)
