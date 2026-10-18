/* The main program's calls into the game's sound layer (sound.h). */
#include "sound.h"

#include <stddef.h>

#include "clean.h"
#include "autoload_2/music_cue.h"
#include "autoload_2/sound.h"
#include "autoload_2/sound_melody.h"
#include "autoload_2/sound_system.h"
#include "autoload_2/voice.h"

/* Positions handed to the sound layer are taken relative to this point, and only while the
 * camera (data_021c67a4) exists. */
extern void *data_021c67a4;
extern Vec3 data_021c67b8;

/* The game's sound state. */
extern u8 data_021fd1bc[];

/* `pos` relative to data_021c67b8. */
static Vec3 relative(const Vec3 *pos)
{
    Vec3 rel = {pos->x - data_021c67b8.x, pos->y - data_021c67b8.y, pos->z - data_021c67b8.z};
    return rel;
}

/* func_0200403c: stop the sequence (if one plays) and release its handle. */
void SoundSeq_Stop(void *seq)
{
    MelodySeq_Stop(seq);
}
CLEAN_AS(func_0200403c, SoundSeq_Stop)

/* func_02004044: follow `pos`, or no position for NULL. With a position but no camera,
 * nothing is called. */
void SoundSeq_UpdateAt(void *seq, const Vec3 *pos)
{
    if (pos == NULL) {
        MelodySeq_Update(seq, NULL);
        return;
    }
    if (data_021c67a4 != NULL) {
        Vec3 rel = relative(pos);
        MelodySeq_Update(seq, &rel);
    }
}
CLEAN_AS(func_02004044, SoundSeq_UpdateAt)

/* func_0200408c */
void SoundSeq_Start(void *seq, u16 number)
{
    MelodySeq_Start(seq, number);
}
CLEAN_AS(func_0200408c, SoundSeq_Start)

/* func_02004094 */
void SoundSeq_Init(void *seq)
{
    MelodySeq_Init(seq);
}
CLEAN_AS(func_02004094, SoundSeq_Init)

/* func_0200409c: 3 the first time it is asked while playing, else -1. */
int SoundCue_TakeStart(void *cue)
{
    return MusicCue_TakeStart(cue);
}
CLEAN_AS(func_0200409c, SoundCue_TakeStart)

/* func_020040a4: the sound library's global variable 2 (the cue itself is not used). */
u8 SoundCue_ReadVariable(char *cue)
{
    (void) cue;
    return MusicCue_ReadBeat();
}
CLEAN_AS(func_020040a4, SoundCue_ReadVariable)

/* func_020040ac: the cue waits for variable 2 to equal value - 1 (15 for 0). */
void SoundCue_SetTarget(void *cue, int value)
{
    MusicCue_SetTarget(cue, value);
}
CLEAN_AS(func_020040ac, SoundCue_SetTarget)

/* func_020040b4 */
void SoundCue_Stop(void *cue)
{
    MusicCue_Release(cue);
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
    return MusicCue_Update(cue, &rel);
}
CLEAN_AS(func_020040bc, SoundCue_UpdateAt)

/* func_02004108: 0 off, 1 start playing, 2 wait for the variable. */
void SoundCue_SetMode(void *cue, int mode)
{
    MusicCue_SetMode(cue, mode);
}
CLEAN_AS(func_02004108, SoundCue_SetMode)

/* func_02004110 */
void SoundCue_Init(void *cue, u16 number)
{
    MusicCue_Init(cue, number);
}
CLEAN_AS(func_02004110, SoundCue_Init)

/* func_02004118: the sound layer's fixed object at data_02138fe4 (`set` is not used). */
void *SoundSet_Default(void *set)
{
    (void) set;
    return (void *) (void *) MelodySet_DefaultMelody();
}
CLEAN_AS(func_02004118, SoundSet_Default)

/* func_02004120: the 16-byte block its index at 0x3b picks, copied to 0x28; returns the copy. */
void *SoundSet_LoadBlock(u8 *set)
{
    return MelodySet_LoadPreset((MelodySet *) (void *) set);
}
CLEAN_AS(func_02004120, SoundSet_LoadBlock)

/* func_02004128 */
int SoundSet_Load(void *set, u32 number)
{
    return MelodySet_PlayRandomPreset(set, number);
}
CLEAN_AS(func_02004128, SoundSet_Load)

/* func_02004130: the byte at 0x38 that SoundSet_Poll sets. */
u8 SoundSet_WasActive(void *set)
{
    return MelodySet_APlaying(set);
}
CLEAN_AS(func_02004130, SoundSet_WasActive)

/* func_02004138 */
int SoundSet_Poll(void *set)
{
    return MelodySet_Update(set);
}
CLEAN_AS(func_02004138, SoundSet_Poll)

/* func_02004140 */
void SoundSet_Call020f65fc(void *set, int value)
{
    MelodySet_PlaySeqD3B(set, value);
}
CLEAN_AS(func_02004140, SoundSet_Call020f65fc)

/* func_02004148 */
void SoundSet_Call020f66f0(void *set)
{
    MelodySet_StartA(set);
}
CLEAN_AS(func_02004148, SoundSet_Call020f66f0)

/* func_02004150: load by number with the set's own block at 0x28. */
void SoundSet_LoadOwn(void *set, u32 number)
{
    MelodySet_PlayOwn(set, number);
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
    MelodySet_PlayAt(set, &rel, (u32) index);
}
CLEAN_AS(func_02004158, SoundSet_LoadAt)

/* func_02004194: load by number with the 16-byte `block`. */
void SoundSet_LoadWith(void *set, u32 number, void *block)
{
    MelodySet_PlayWith(set, number, block);
}
CLEAN_AS(func_02004194, SoundSet_LoadWith)

/* func_0200419c: copy a 16-byte block to 0x28. */
void SoundSet_SetBlock(u8 *set, const u8 *block)
{
    MelodySet_SetMelody((MelodySet *) (void *) set, block);
}
CLEAN_AS(func_0200419c, SoundSet_SetBlock)

/* func_020041a4: make the set the sound state's current one and clear it. */
void SoundSet_MakeCurrent(void *set)
{
    MelodySet_MakeCurrent(set);
}
CLEAN_AS(func_020041a4, SoundSet_MakeCurrent)

/* func_020041ac: set the byte at 0x70 and hand it on to the players. */
void SoundSys_SetPlayerByte(int value)
{
    SoundSystem_SetPan((SoundSystem *) (void *) data_021fd1bc, value);
}
CLEAN_AS(func_020041ac, SoundSys_SetPlayerByte)

/* func_020041bc: the same when the byte changes. */
void SoundSys_ChangePlayerByte(int value)
{
    SoundSystem_ChangePan((SoundSystem *) (void *) data_021fd1bc, value);
}
CLEAN_AS(func_020041bc, SoundSys_ChangePlayerByte)

/* func_020041cc: the second fader back to full volume, unless the music is lowered. */
void SoundSys_RestoreSecond(void)
{
    SoundSystem_RaiseB((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_020041cc, SoundSys_RestoreSecond)

/* func_020041dc: the second fader down to 0x28, unless the music is lowered. */
void SoundSys_LowerSecond(void)
{
    SoundSystem_LowerB((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_020041dc, SoundSys_LowerSecond)

/* func_020041ec: both faders back to full volume over 5 frames. */
void SoundSys_RestoreMusic(void)
{
    SoundSystem_RaiseBoth((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_020041ec, SoundSys_RestoreMusic)

/* func_020041fc: both faders down (to 0x46 and 0x28) over 15 frames. */
void SoundSys_LowerMusic(void)
{
    SoundSystem_LowerBoth((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_020041fc, SoundSys_LowerMusic)

/* func_0200420c: 0x14 bytes into the entry the state's first word points to, or NULL. */
int *SoundSys_FirstEntryData(void)
{
    return SoundSystem_OwnerData((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_0200420c, SoundSys_FirstEntryData)

/* func_0200421c */
void SoundSys_SetMode(int mode)
{
    SoundSystem_SetArrangement((SoundSystem *) (void *) data_021fd1bc, mode);
}
CLEAN_AS(func_0200421c, SoundSys_SetMode)

/* func_0200422c: the fader at 0x04 from silence to full volume, with one of five track
 * masks. */
void SoundSys_FadeInTracks(int set)
{
    SoundSystem_FadeInTracks((SoundSystem *) (void *) data_021fd1bc, (u32) set);
}
CLEAN_AS(func_0200422c, SoundSys_FadeInTracks)

/* func_0200423c: a track mask chosen by `set`, faded out or applied at once. */
void SoundSys_SetTracks(int set)
{
    SoundSystem_SetTracks((SoundSystem *) (void *) data_021fd1bc, set);
}
CLEAN_AS(func_0200423c, SoundSys_SetTracks)

/* func_0200424c: move the music's volume (clamped to 0..0x7f) over `frames`. */
void SoundSys_MoveVolume(int volume, int frames)
{
    SoundSystem_MoveMusicVolume((SoundSystem *) (void *) data_021fd1bc, volume, frames);
}
CLEAN_AS(func_0200424c, SoundSys_MoveVolume)

/* func_02004260 */
void SoundSys_Call020f1c00(int value)
{
    SoundSystem_EndMusic((SoundSystem *) (void *) data_021fd1bc, value);
}
CLEAN_AS(func_02004260, SoundSys_Call020f1c00)

extern void func_020f1c6c(void *sys, u32 music);

/* func_02004270: switch the music to `music`. 0 and 1 work the stream player instead, and some
 * numbers (0xb0 to 0xf5) start silent. */
void SoundSys_ChangeMusic(u32 music)
{
    SoundSystem_ChangeMusic((SoundSystem *) (void *) data_021fd1bc, music);
}
CLEAN_AS(func_02004270, SoundSys_ChangeMusic)

/* func_0200452c: stop sound 0x2d, fading over one frame. */
void SoundSys_StopSound2d(void)
{
    SoundSystem_StopEffect45((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_0200452c, SoundSys_StopSound2d)

/* func_0200453c: start sound 0x2d on the handle at 0x38. */
void SoundSys_StartSound2d(void)
{
    SoundSystem_PlayEffect45((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_0200453c, SoundSys_StartSound2d)

/* func_0200454c: stop what the handle at 0x40 plays, at once. */
void SoundSys_StopHandle40(void)
{
    SoundSystem_StopEffectB((SoundSystem *) (void *) data_021fd1bc);
}
CLEAN_AS(func_0200454c, SoundSys_StopHandle40)

/* func_0200455c: start entry `index` of sequence archive 0 on the handle at 0x40 (player 10). */
void SoundSys_StartOnHandle40(int index)
{
    SoundSystem_PlayEffectB((SoundSystem *) (void *) data_021fd1bc, index);
}
CLEAN_AS(func_0200455c, SoundSys_StartOnHandle40)

/* func_0200456c: the same through a second copy of the callee. */
void SoundSys_StartOnHandle40B(int index)
{
    SoundSystem_PlayEffectBAgain((SoundSystem *) (void *) data_021fd1bc, index);
}
CLEAN_AS(func_0200456c, SoundSys_StartOnHandle40B)

/* func_0200457c: play sound 0x2c on the shared handle; the result of starting it. */
int SoundSys_PlaySound2c(void *unused)
{
    return SoundSystem_PlayEffect2c((SoundSystem *) (void *) data_021fd1bc, unused);
}
CLEAN_AS(func_0200457c, SoundSys_PlaySound2c)

/* func_0200458c: the byte at 0x71 becomes 1 for 1, else 0. */
void SoundSys_SetByte71(int value)
{
    SoundSystem_SetUnk71((SoundSystem *) (void *) data_021fd1bc, value);
}
CLEAN_AS(func_0200458c, SoundSys_SetByte71)

/* func_0200459c: the volumes of the handles at 0x38 (2 * level + 16) and 0x40 (level + 80),
 * each at most 0x7f; a negative level counts as 0. */
void SoundSys_SetHandleLevel(int level)
{
    SoundSystem_SetEffectLevel((SoundSystem *) (void *) data_021fd1bc, level);
}
CLEAN_AS(func_0200459c, SoundSys_SetHandleLevel)

/* func_020045cc: the keyboard's mode at 0x44, which SoundSys_PlayKeyboardSound reads. */
void SoundSys_SetKeyboardMode(int mode)
{
    SoundSystem_SetVoiceType((SoundSystem *) (void *) data_021fd1bc, mode);
}
CLEAN_AS(func_020045cc, SoundSys_SetKeyboardMode)

/* func_020045f4: the click of a key of the on-screen keyboard. */
void SoundSys_PlayKeyboardSound(int action, int layout, int key, int previous_key)
{
    Voice_Speak((SoundSystem *) (void *) data_021fd1bc, action, layout, key, previous_key);
}
CLEAN_AS(func_020045f4, SoundSys_PlayKeyboardSound)

/* func_02004634: keep `effect` at 0x50 and hand it to the sound capture. */
void SoundSys_SetCaptureEffect(int effect)
{
    SoundSystem_ChangeOutputEffect((SoundSystem *) (void *) data_021fd1bc, effect);
}
CLEAN_AS(func_02004634, SoundSys_SetCaptureEffect)

/* func_02004644: stop every player of sound `number`, fading over `fade_frames`. */
void SoundSys_StopSound(int number, int fade_frames)
{
    SoundSystem_StopSequence(data_021fd1bc, number, fade_frames);
}
CLEAN_AS(func_02004644, SoundSys_StopSound)

/* func_02004658: start sound `number` on the handle at 0x38 (0x862 silenced). */
void SoundSys_StartOnHandle38(int number)
{
    SoundSystem_PlayOnEffect((SoundSystem *) (void *) data_021fd1bc, number);
}
CLEAN_AS(func_02004658, SoundSys_StartOnHandle38)

/* func_02004668: start entry `index` of sequence archive 0 on the handle at 0x38, then hand
 * `value` to the handle's player with the parameter at data_0213e858. */
void SoundSys_StartIndexOnHandle38(int index, int value)
{
    SoundSystem_PlayEffectWithPan((SoundSystem *) (void *) data_021fd1bc, index, value);
}
CLEAN_AS(func_02004668, SoundSys_StartIndexOnHandle38)

/* RtcSendPxiCommand: play sound effect `number` (some on the handles at 0x38 and 0x40, the
 * others on the shared handle). Nothing plays while the byte at 0x4d is set. The symbol's
 * name is not what the function does. */
void SoundSys_PlaySe(int number)
{
    SoundSystem_PlayEffect((SoundSystem *) (void *) data_021fd1bc, number);
}
CLEAN_AS(RtcSendPxiCommand, SoundSys_PlaySe)

/* func_020046a4: the master volume to 0x7f. The callee takes no argument (the original still
 * hands it the sound state). */
void SoundSys_MasterVolumeFull(void)
{
    SoundSystem_MasterVolumeFull();
}
CLEAN_AS(func_020046a4, SoundSys_MasterVolumeFull)

/* func_020046b4: the master volume to 0. */
void SoundSys_MasterVolumeOff(void)
{
    SoundSystem_MasterVolumeOff(data_021fd1bc);
}
CLEAN_AS(func_020046b4, SoundSys_MasterVolumeOff)
