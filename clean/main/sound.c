/* The main program's calls into the game's sound layer (sound.h). */
#include "sound.h"

#include <stddef.h>

#include "clean.h"

/* Positions handed to the sound layer are taken relative to this point, and only while the
 * camera (data_021c67a4) exists. */
extern void *data_021c67a4;
extern Vec3 data_021c67b8;

/* The game's sound state. */
extern u8 data_021fd1bc[];

extern void func_020f64c8(void *seq);
extern void func_020f61e4(void *seq, const Vec3 *pos);
extern void func_020f6350(void *seq, u16 number);
extern void func_020f6508(void *seq);

extern int func_020f9f48(void *cue);
extern u8 func_020f9f98(void);
extern void func_020f9f74(void *cue, int value);
extern void func_020fa034(void *cue);
extern int func_020f9ea4(void *cue, const Vec3 *pos);
extern void func_020f9fcc(void *cue, int mode);
extern void func_020fa054(void *cue, u16 number);

extern void *func_020f6970(void);
extern void *func_020f6720(u8 *set);
extern int func_020f6754(void *set, u32 number);
extern u8 func_020f65c8(void *set);
extern int func_020f65d0(void *set);
extern void func_020f65fc(void *set, int value);
extern void func_020f66f0(void *set);
extern void func_020f67e4(void *set, u32 number);
extern void func_020f660c(void *set, const Vec3 *pos, u32 index);
extern void func_020f688c(void *set, u32 number, void *block);
extern void func_020f6950(u8 *set, const u8 *block);
extern void func_020f697c(void *set);

extern void func_020f0f68(void *sys, int value);
extern void func_020f0f7c(void *sys, int value);
extern void func_020f1030(void *sys);
extern void func_020f1074(void *sys);
extern void func_020f10b8(void *sys);
extern void func_020f1108(void *sys);
extern int *func_020f0ff0(void *sys);
extern void func_020f165c(void *sys, int mode);
extern void func_020f19c0(void *sys, u32 set);
extern void func_020f1a54(void *sys, int set);
extern void func_020f1ba4(void *sys, int volume, int frames);
extern void func_020f1c00(void *sys, int value);

/* `pos` relative to data_021c67b8. */
static Vec3 relative(const Vec3 *pos)
{
    Vec3 rel = {pos->x - data_021c67b8.x, pos->y - data_021c67b8.y, pos->z - data_021c67b8.z};
    return rel;
}

/* func_0200403c: stop the sequence (if one plays) and release its handle. */
void SoundSeq_Stop(void *seq)
{
    func_020f64c8(seq);
}
CLEAN_AS(func_0200403c, SoundSeq_Stop)

/* func_02004044: follow `pos`, or no position for NULL. With a position but no camera,
 * nothing is called. */
void SoundSeq_UpdateAt(void *seq, const Vec3 *pos)
{
    if (pos == NULL) {
        func_020f61e4(seq, NULL);
        return;
    }
    if (data_021c67a4 != NULL) {
        Vec3 rel = relative(pos);
        func_020f61e4(seq, &rel);
    }
}
CLEAN_AS(func_02004044, SoundSeq_UpdateAt)

/* func_0200408c */
void SoundSeq_Start(void *seq, u16 number)
{
    func_020f6350(seq, number);
}
CLEAN_AS(func_0200408c, SoundSeq_Start)

/* func_02004094 */
void SoundSeq_Init(void *seq)
{
    func_020f6508(seq);
}
CLEAN_AS(func_02004094, SoundSeq_Init)

/* func_0200409c: 3 the first time it is asked while playing, else -1. */
int SoundCue_TakeStart(void *cue)
{
    return func_020f9f48(cue);
}
CLEAN_AS(func_0200409c, SoundCue_TakeStart)

/* func_020040a4: the sound library's global variable 2 (the cue itself is not used). */
u8 SoundCue_ReadVariable(char *cue)
{
    (void) cue;
    return func_020f9f98();
}
CLEAN_AS(func_020040a4, SoundCue_ReadVariable)

/* func_020040ac: the cue waits for variable 2 to equal value - 1 (15 for 0). */
void SoundCue_SetTarget(void *cue, int value)
{
    func_020f9f74(cue, value);
}
CLEAN_AS(func_020040ac, SoundCue_SetTarget)

/* func_020040b4 */
void SoundCue_Stop(void *cue)
{
    func_020fa034(cue);
}
CLEAN_AS(func_020040b4, SoundCue_Stop)

/* func_020040bc: update at `pos`. QUIRK: without a position or without a camera nothing is
 * called and the result is -1, not the -0x1000 the cue's own update gives when off. */
int SoundCue_UpdateAt(void *cue, const Vec3 *pos)
{
    if (pos == NULL || data_021c67a4 == NULL) {
        return -1;
    }
    Vec3 rel = relative(pos);
    return func_020f9ea4(cue, &rel);
}
CLEAN_AS(func_020040bc, SoundCue_UpdateAt)

/* func_02004108: 0 off, 1 start playing, 2 wait for the variable. */
void SoundCue_SetMode(void *cue, int mode)
{
    func_020f9fcc(cue, mode);
}
CLEAN_AS(func_02004108, SoundCue_SetMode)

/* func_02004110 */
void SoundCue_Init(void *cue, u16 number)
{
    func_020fa054(cue, number);
}
CLEAN_AS(func_02004110, SoundCue_Init)

/* func_02004118: the sound layer's fixed object at data_02138fe4 (`set` is not used). */
void *SoundSet_Default(void *set)
{
    (void) set;
    return func_020f6970();
}
CLEAN_AS(func_02004118, SoundSet_Default)

/* func_02004120: the 16-byte block its index at 0x3b picks, copied to 0x28; returns the copy. */
void *SoundSet_LoadBlock(u8 *set)
{
    return func_020f6720(set);
}
CLEAN_AS(func_02004120, SoundSet_LoadBlock)

/* func_02004128 */
int SoundSet_Load(void *set, u32 number)
{
    return func_020f6754(set, number);
}
CLEAN_AS(func_02004128, SoundSet_Load)

/* func_02004130: the byte at 0x38 that SoundSet_Poll sets. */
u8 SoundSet_WasActive(void *set)
{
    return func_020f65c8(set);
}
CLEAN_AS(func_02004130, SoundSet_WasActive)

/* func_02004138 */
int SoundSet_Poll(void *set)
{
    return func_020f65d0(set);
}
CLEAN_AS(func_02004138, SoundSet_Poll)

/* func_02004140 */
void SoundSet_Call020f65fc(void *set, int value)
{
    func_020f65fc(set, value);
}
CLEAN_AS(func_02004140, SoundSet_Call020f65fc)

/* func_02004148 */
void SoundSet_Call020f66f0(void *set)
{
    func_020f66f0(set);
}
CLEAN_AS(func_02004148, SoundSet_Call020f66f0)

/* func_02004150: load by number with the set's own block at 0x28. */
void SoundSet_LoadOwn(void *set, u32 number)
{
    func_020f67e4(set, number);
}
CLEAN_AS(func_02004150, SoundSet_LoadOwn)

/* func_02004158: load one of a few fixed entries (by `index`) at `pos`. Without a camera
 * nothing is called. REQUIRES: `pos` is not NULL. */
void SoundSet_LoadAt(void *set, const Vec3 *pos, int index)
{
    if (data_021c67a4 == NULL) {
        return;
    }
    Vec3 rel = relative(pos);
    func_020f660c(set, &rel, (u32) index);
}
CLEAN_AS(func_02004158, SoundSet_LoadAt)

/* func_02004194: load by number with the 16-byte `block`. */
void SoundSet_LoadWith(void *set, u32 number, void *block)
{
    func_020f688c(set, number, block);
}
CLEAN_AS(func_02004194, SoundSet_LoadWith)

/* func_0200419c: copy a 16-byte block to 0x28. */
void SoundSet_SetBlock(u8 *set, const u8 *block)
{
    func_020f6950(set, block);
}
CLEAN_AS(func_0200419c, SoundSet_SetBlock)

/* func_020041a4: make the set the sound state's current one and clear it. */
void SoundSet_MakeCurrent(void *set)
{
    func_020f697c(set);
}
CLEAN_AS(func_020041a4, SoundSet_MakeCurrent)

/* func_020041ac: set the byte at 0x70 and hand it on to the players. */
void SoundSys_SetPlayerByte(int value)
{
    func_020f0f68(data_021fd1bc, value);
}
CLEAN_AS(func_020041ac, SoundSys_SetPlayerByte)

/* func_020041bc: the same when the byte changes. */
void SoundSys_ChangePlayerByte(int value)
{
    func_020f0f7c(data_021fd1bc, value);
}
CLEAN_AS(func_020041bc, SoundSys_ChangePlayerByte)

/* func_020041cc: the second fader back to full volume, unless the music is lowered. */
void SoundSys_RestoreSecond(void)
{
    func_020f1030(data_021fd1bc);
}
CLEAN_AS(func_020041cc, SoundSys_RestoreSecond)

/* func_020041dc: the second fader down to 0x28, unless the music is lowered. */
void SoundSys_LowerSecond(void)
{
    func_020f1074(data_021fd1bc);
}
CLEAN_AS(func_020041dc, SoundSys_LowerSecond)

/* func_020041ec: both faders back to full volume over 5 frames. */
void SoundSys_RestoreMusic(void)
{
    func_020f10b8(data_021fd1bc);
}
CLEAN_AS(func_020041ec, SoundSys_RestoreMusic)

/* func_020041fc: both faders down (to 0x46 and 0x28) over 15 frames. */
void SoundSys_LowerMusic(void)
{
    func_020f1108(data_021fd1bc);
}
CLEAN_AS(func_020041fc, SoundSys_LowerMusic)

/* func_0200420c: 0x14 bytes into the entry the state's first word points to, or NULL. */
int *SoundSys_FirstEntryData(void)
{
    return func_020f0ff0(data_021fd1bc);
}
CLEAN_AS(func_0200420c, SoundSys_FirstEntryData)

/* func_0200421c */
void SoundSys_SetMode(int mode)
{
    func_020f165c(data_021fd1bc, mode);
}
CLEAN_AS(func_0200421c, SoundSys_SetMode)

/* func_0200422c: the fader at 0x04 from silence to full volume, with one of five track
 * masks. */
void SoundSys_FadeInTracks(int set)
{
    func_020f19c0(data_021fd1bc, (u32) set);
}
CLEAN_AS(func_0200422c, SoundSys_FadeInTracks)

/* func_0200423c: a track mask chosen by `set`, faded out or applied at once. */
void SoundSys_SetTracks(int set)
{
    func_020f1a54(data_021fd1bc, set);
}
CLEAN_AS(func_0200423c, SoundSys_SetTracks)

/* func_0200424c: move the music's volume (clamped to 0..0x7f) over `frames`. */
void SoundSys_MoveVolume(int volume, int frames)
{
    func_020f1ba4(data_021fd1bc, volume, frames);
}
CLEAN_AS(func_0200424c, SoundSys_MoveVolume)

/* func_02004260 */
void SoundSys_Call020f1c00(int value)
{
    func_020f1c00(data_021fd1bc, value);
}
CLEAN_AS(func_02004260, SoundSys_Call020f1c00)
