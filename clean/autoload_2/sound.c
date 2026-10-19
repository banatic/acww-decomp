/* The sound heap and players, the sound groups, the lists, the faders and the sound system's
 * effects (sound.h). Each failure the game does not expect stops it (OS_Terminate). */
#include "sound.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"
#include "main/game_halt.h"
#include "sound_system.h"

static_assert(sizeof(SoundList) == 0xc, "NNSFndList");
static_assert(sizeof(SoundGroup) == 0x28, "the group before the next global");
static_assert(offsetof(SoundGroup, key) == 0x15, "the key at 0x15");
static_assert(offsetof(SoundGroup, heap_level) == 0x1c, "the level at 0x1c");
static_assert(sizeof(SoundFader) == 0xc, "a fader");
static_assert(offsetof(SoundSystem, voice_type) == 0x44, "the voice's kind");
static_assert(offsetof(SoundSystem, voice) == 0x48, "the voice's handle");

/* The sound heap (NNSSndHeapHandle). */
extern void *data_021fd048;
/* The handle Sound_StartSeqArcDefault plays on. */
extern SoundHandle data_021fd04c;
/* The output effect's buffer in the sound heap (Sound_AllocEffectBuffer). */
extern void *data_021fd050;
/* The sound archive when it is read from a file, and when it is in memory (NNSSndArc). */
extern u8 data_021fd10c[];
extern u8 data_021fd07c[];

extern int NNS_SndHeapGetCurrentLevel(void *heap);
extern void NNS_SndHeapLoadState(void *heap, int level);
extern int NNS_SndHeapSaveState(void *heap);
extern int NNS_SndArcLoadGroup(int group, void *heap);
extern int NNS_SndPlayerStopSeq(void *handle, int fade_frames);
extern int NNS_SndArcPlayerStartSeqArcEx(SoundHandle *handle, int player_no, int bank_no, int player_priority, int seq_arc,
                                         int index);
extern int NNS_SndArcPlayerStartSeqArc(SoundHandle *handle, int seq_arc, int index);
extern void NNS_SndMain(void);
extern void *NNS_SndHeapAlloc(void *heap, unsigned int size,
                              void (*dispose)(void *memory, unsigned int size, unsigned int data1, unsigned int data2),
                              unsigned int data1, unsigned int data2);
extern void NNS_SndCaptureStartOutputEffect(void *buffer, int size, int type);
extern void NNS_SndInit(void);
extern void *NNS_SndHeapCreate(void *memory, unsigned int size);
extern void NNS_SndArcInit(void *arc, const void *path, void *heap, int load_string_block);
extern void NNS_SndArcInitOnMemory(void *arc, const void *data);
extern int NNS_SndArcPlayerSetup(void *heap);
extern void NNS_FndInitList(SoundList *list, u16 offset);
extern void *NNS_FndGetPrevListObject(SoundList *list, void *object);
extern void *NNS_FndGetNextListObject(SoundList *list, void *object);
extern void NNS_FndRemoveListObject(SoundList *list, void *object);
extern void NNS_FndAppendListObject(SoundList *list, void *object);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
/* NNS_SndHandleInit: the handle made empty. */
extern void func_0210b7e0(SoundHandle *handle);
/* The pan of the tracks in `track_mask` (it passes the player's number to the SDK). */
extern void func_0210b634(SoundHandle *handle, u16 track_mask, int pan);
/* The output effect buffer's dispose callback, handed to the sound heap (Sound_DisposeNothing). */
extern void func_020eeea0(void *memory, unsigned int size, unsigned int data1, unsigned int data2);

/* The tracks the game's sound effects change: 0-3 (0x000f). */
extern const u16 data_0213e858;

/* The output effect's buffer: 0x1000 bytes at a 32-byte boundary, room allocated for it. */
#define EFFECT_BUFFER_SIZE 0x1000
#define EFFECT_BUFFER_ALIGN 32

/* The sound system's effect started and stopped by SoundSystem_PlayEffect45 and
 * SoundSystem_StopEffect45: sequence 45 of sequence archive 0. */
#define EFFECT_45 45

/* func_020eec48: the sound heap's level (the number of states saved). */
int Sound_GetHeapLevel(void)
{
    return NNS_SndHeapGetCurrentLevel(data_021fd048);
}
CLEAN_AS(func_020eec48, Sound_GetHeapLevel)

/* func_020eec60: the sound heap taken back to `level` (Sound_LoadGroup's result), freeing what
 * was loaded since; the game stops on no level, level 0 or a level not reached.
 * QUIRK: the level is read once more at the end and not used. */
void Sound_RestoreHeapLevel(int level)
{
    if (level == SOUND_NONE) {
        GameHalt_Terminate();
    }
    if (level == 0) {
        GameHalt_Terminate();
    }
    NNS_SndHeapLoadState(data_021fd048, level);
    if (level != Sound_GetHeapLevel()) {
        GameHalt_Terminate();
    }
    Sound_GetHeapLevel();
}
CLEAN_AS(func_020eec60, Sound_RestoreHeapLevel)

/* func_020eecb0: a group of the sound archive loaded into the sound heap and the heap's state
 * saved after it; the level before (to unload it with Sound_RestoreHeapLevel), or -1 when the
 * group could not be loaded. The game stops when the state cannot be saved. */
int Sound_LoadGroup(int group)
{
    int level = Sound_GetHeapLevel();
    if (!NNS_SndArcLoadGroup(group, data_021fd048)) {
        return -1;
    }
    if (NNS_SndHeapSaveState(data_021fd048) == -1) {
        GameHalt_Terminate();
    }
    return level;
}
CLEAN_AS(func_020eecb0, Sound_LoadGroup)

/* func_020eed18: the sequence of a player handle stopped, fading out over `fade_frames`; the
 * game stops without a handle. */
int Sound_StopSequence(void *handle, int fade_frames)
{
    if (handle == NULL) {
        GameHalt_Terminate();
    }
    return NNS_SndPlayerStopSeq(handle, fade_frames);
}
CLEAN_AS(func_020eed18, Sound_StopSequence)

/* func_020eed48: a handle made empty; the game
 * stops without one. */
void Sound_InitHandle(SoundHandle *handle)
{
    if (handle == NULL) {
        GameHalt_Terminate();
    }
    func_0210b7e0(handle);
}
CLEAN_AS(func_020eed48, Sound_InitHandle)

/* func_020eed68: a sequence of a sequence archive started on `handle` with a player, bank and
 * player priority of its own (-1: the archive's); the game stops without a handle. */
void Sound_StartSeqArcEx(SoundHandle *handle, int player_no, int bank_no, int player_priority, int seq_arc, int index)
{
    if (handle == NULL) {
        GameHalt_Terminate();
    }
    NNS_SndArcPlayerStartSeqArcEx(handle, player_no, bank_no, player_priority, seq_arc, index);
}
CLEAN_AS(func_020eed68, Sound_StartSeqArcEx)

/* func_020eedb8: sequence `index` of sequence archive `seq_arc` started on `handle`; whether it
 * started. The game stops without a handle. */
int Sound_StartSeqArc(int index, int seq_arc, SoundHandle *handle)
{
    if (handle == NULL) {
        GameHalt_Terminate();
    }
    return NNS_SndArcPlayerStartSeqArc(handle, seq_arc, index);
}
CLEAN_AS(func_020eedb8, Sound_StartSeqArc)

/* func_020eede8: Sound_StartSeqArc on the default handle. */
int Sound_StartSeqArcDefault(int index, int seq_arc)
{
    return Sound_StartSeqArc(index, seq_arc, &data_021fd04c);
}
CLEAN_AS(func_020eede8, Sound_StartSeqArcDefault)

/* func_020eedfc: the sound library's work of a frame. */
void Sound_Main(void)
{
    NNS_SndMain();
}
CLEAN_AS(func_020eedfc, Sound_Main)

/* func_020eee08: the output effect's buffer allocated from the sound heap, with room to align
 * it; the game stops when it cannot be. */
void Sound_AllocEffectBuffer(void)
{
    data_021fd050 = NNS_SndHeapAlloc((void *) Sound_GetHeap(), EFFECT_BUFFER_SIZE + EFFECT_BUFFER_ALIGN, func_020eeea0, 0, 0);
    if (data_021fd050 == NULL) {
        GameHalt_Terminate();
    }
}
CLEAN_AS(func_020eee08, Sound_AllocEffectBuffer)

/* func_020eee5c: the output effect of `type` started on the buffer; the game stops without one. */
void Sound_StartOutputEffect(int type)
{
    u32 buffer = (u32) data_021fd050;

    if (data_021fd050 == NULL) {
        GameHalt_Terminate();
    }
    buffer = (buffer + (EFFECT_BUFFER_ALIGN - 1)) & ~(u32) (EFFECT_BUFFER_ALIGN - 1);
    NNS_SndCaptureStartOutputEffect((void *) buffer, EFFECT_BUFFER_SIZE, type);
}
CLEAN_AS(func_020eee5c, Sound_StartOutputEffect)

/* func_020eeea0: the effect buffer's dispose callback: nothing to do. */
void Sound_DisposeNothing(void *memory, unsigned int size, unsigned int data1, unsigned int data2)
{
    (void) memory;
    (void) size;
    (void) data1;
    (void) data2;
}
CLEAN_AS(func_020eeea0, Sound_DisposeNothing)

/* func_020eeea4: the sound library started: the sound heap made in `heap_memory`, the effect
 * buffer allocated, the sound archive opened (from the file `arc_path`, else from memory),
 * the players set up and the default handle emptied. The game stops if a sound heap exists
 * already, on any failure and without an archive. */
void Sound_Init(void *heap_memory, unsigned int heap_size, const void *arc_path, const void *arc_in_memory)
{
    NNS_SndInit();
    if (data_021fd048 != NULL) {
        GameHalt_Terminate();
    }
    data_021fd048 = NNS_SndHeapCreate(heap_memory, heap_size);
    if (data_021fd048 == NULL) {
        GameHalt_Terminate();
    }
    Sound_AllocEffectBuffer();
    if (arc_path != NULL) {
        NNS_SndArcInit(data_021fd10c, arc_path, data_021fd048, 0);
    } else {
        if (arc_in_memory == NULL) {
            GameHalt_Terminate();
        }
        NNS_SndArcInitOnMemory(data_021fd07c, arc_in_memory);
    }
    if (!NNS_SndArcPlayerSetup(data_021fd048)) {
        GameHalt_Terminate();
    }
    func_0210b7e0(&data_021fd04c);
}
CLEAN_AS(func_020eeea4, Sound_Init)

/* func_020eef70: the sound heap. */
unsigned int Sound_GetHeap(void)
{
    return (unsigned int) data_021fd048;
}
CLEAN_AS(func_020eef70, Sound_GetHeap)

/* func_020eef80: every SoundSlots in the group's list stopped and released; the game stops
 * without a group. */
void SoundGroup_StopAll(SoundGroup *group)
{
    void *slots;

    if (group == NULL) {
        GameHalt_Terminate();
    }
    for (slots = (void *) SoundList_First(&group->playing); slots != NULL; slots = SoundList_Next(&group->playing, slots)) {
        SoundSlots_Shutdown(slots);
    }
}
CLEAN_AS(func_020eef80, SoundGroup_StopAll)

/* func_020eefd4: the group's sound data unloaded (the heap taken back to its level), when it
 * was loaded; the game stops for a group of none. */
void SoundGroup_Unload(SoundGroup *group)
{
    if (group->key.group == SOUND_NONE) {
        GameHalt_Terminate();
    }
    if (group->heap_level != SOUND_NONE) {
        Sound_RestoreHeapLevel(group->heap_level);
    }
}
CLEAN_AS(func_020eefd4, SoundGroup_Unload)

/* func_020ef008: the group closed: what plays from it stopped, its data unloaded when
 * `unload`; 0. */
int SoundGroup_Close(SoundGroup *group, int unload)
{
    SoundGroup_StopAll(group);
    if (unload) {
        SoundGroup_Unload(group);
    }
    group->state = 0;
    return 0;
}
CLEAN_AS(func_020ef008, SoundGroup_Close)

/* func_020ef040: the group opened for `key`: its group loaded unless the key keeps the heap,
 * its handles emptied and its list started; 0 when the group could not be loaded (the group
 * then stays closed), else 1. The game stops if it is open already or for a key of no group. */
int SoundGroup_Open(SoundGroup *group, void *unk_10, u8 unk_14, SoundGroupKey key)
{
    if (group->state != 0) {
        GameHalt_Terminate();
    }
    if (key.group == SOUND_NONE) {
        GameHalt_Terminate();
    }
    group->key = key;
    if (key.keep_heap == 0) {
        if (!SoundGroup_Load(group)) {
            return 0;
        }
    } else {
        group->heap_level = SOUND_NONE;
    }
    group->unk_10 = unk_10;
    group->unk_14 = unk_14;
    func_0210b7e0(&group->handle_a);
    func_0210b7e0(&group->handle_b);
    NNS_FndInitList(&group->playing, 0);
    group->state = 1;
    return 1;
}
CLEAN_AS(func_020ef040, SoundGroup_Open)

/* func_020ef100: the group's group loaded and the heap's level before kept (SOUND_NONE for a
 * group of none, which loads nothing); 0 when it could not be loaded, else 1. */
int SoundGroup_Load(SoundGroup *group)
{
    int level = SOUND_NONE;

    if (group->key.group != SOUND_NONE) {
        level = Sound_LoadGroup(group->key.group);
        if (level == -1) {
            return 0;
        }
    }
    group->heap_level = level;
    return 1;
}
CLEAN_AS(func_020ef100, SoundGroup_Load)

/* func_020efc10: the list's last object. */
int SoundList_Last(SoundList *list)
{
    return (int) list->last;
}
CLEAN_AS(func_020efc10, SoundList_Last)

/* func_020efc18: the list's first
 * object. */
unsigned long SoundList_First(const SoundList *list)
{
    return (unsigned long) list->first;
}
CLEAN_AS(func_020efc18, SoundList_First)

/* func_020efc20 */
void *SoundList_Prev(SoundList *list, void *object)
{
    return NNS_FndGetPrevListObject(list, object);
}
CLEAN_AS(func_020efc20, SoundList_Prev)

/* func_020efc2c */
void *SoundList_Next(SoundList *list, void *object)
{
    return NNS_FndGetNextListObject(list, object);
}
CLEAN_AS(func_020efc2c, SoundList_Next)

/* func_020efc38 */
void SoundList_Remove(SoundList *list, void *object)
{
    NNS_FndRemoveListObject(list, object);
}
CLEAN_AS(func_020efc38, SoundList_Remove)

/* func_020efc44 */
void SoundList_Append(SoundList *list, void *object)
{
    NNS_FndAppendListObject(list, object);
}
CLEAN_AS(func_020efc44, SoundList_Append)

/* func_020efc50: a link out of any list; the game stops without one. */
void SoundLink_Clear(ListNode *link)
{
    if (link == NULL) {
        GameHalt_Terminate();
    }
    link->prev = NULL;
    link->next = NULL;
}
CLEAN_AS(func_020efc50, SoundLink_Clear)

/* func_020f0d3c: called every frame between the sound library's work and the system's
 * streams; does nothing. */
void SoundSystem_UpdateNothing(SoundSystem *system)
{
    (void) system;
}
CLEAN_AS(func_020f0d3c, SoundSystem_UpdateNothing)

/* func_020f0d50: a frame of the fader: one step nearer, the target itself at the last frame;
 * the level's whole part.
 * QUIRK: the whole part is cut to 16 bits, sign included. */
int SoundFader_Step(SoundFader *fader)
{
    if (fader->frames != 0) {
        fader->frames--;
        if (fader->frames != 0) {
            fader->level += fader->step;
        } else {
            fader->level = fader->target * 4096;
        }
    }
    return (s16) (fader->level >> 12);
}
CLEAN_AS(func_020f0d50, SoundFader_Step)

/* func_020f0d98: the fader sent to `target` over `frames` frames; at once with 0 frames. */
void SoundFader_Start(SoundFader *fader, short target, short frames)
{
    fx32 goal = target * 4096;

    fader->target = target;
    fader->frames = (u16) frames;
    if (frames == 0) {
        fader->level = goal;
        return;
    }
    fader->step = FX_Div(goal - fader->level, frames * 4096);
}
CLEAN_AS(func_020f0d98, SoundFader_Start)

/* func_020f0ddc: the fader put at `level`, still.
 * QUIRK: the target is left as it was. */
void SoundFader_Set(SoundFader *fader, int level)
{
    fader->level = level * 4096;
    fader->frames = 0;
}
CLEAN_AS(func_020f0ddc, SoundFader_Set)

/* func_020f0df0: sound effect `index` (of sequence archive 0) started on the effects' handle,
 * its tracks panned to `pan`. */
void SoundSystem_PlayEffectWithPan(SoundSystem *system, int index, int pan)
{
    Sound_StartSeqArc(index, 0, &system->effect);
    func_0210b634(&system->effect, data_0213e858, pan);
}
CLEAN_AS(func_020f0df0, SoundSystem_PlayEffectWithPan)

/* func_020f0e34: sound effect 45 stopped wherever it plays, over 1 frame. */
void SoundSystem_StopEffect45(SoundSystem *system)
{
    SoundSystem_StopSequence(system, EFFECT_45, 1);
}
CLEAN_AS(func_020f0e34, SoundSystem_StopEffect45)

/* func_020f0e48: sound effect 45 started on the effects' handle. */
void SoundSystem_PlayEffect45(SoundSystem *system)
{
    Sound_StartSeqArc(EFFECT_45, 0, &system->effect);
}
CLEAN_AS(func_020f0e48, SoundSystem_PlayEffect45)
