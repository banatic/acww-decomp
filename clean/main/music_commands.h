/* The member at 0x2b4 of the field's sound object (music_queue.h): what the sound system is
 * asked at the end of the frame. The queue and the volume member set a music to change to, a
 * word for SoundSys_Call020f1c00 and a volume to move to; MusicCommands_Apply hands each one set
 * to the sound system once. */
#ifndef CLEAN_MAIN_MUSIC_COMMANDS_H
#define CLEAN_MAIN_MUSIC_COMMANDS_H

#include "music_queue.h"
#include "types.h"

typedef struct MusicCommands {
    Obj021c526c *owner;
    u8 music_set; /* 0x04 */
    u8 unk_05;
    u16 music;    /* 0x06: for SoundSys_ChangeMusic */
    u8 value_set; /* 0x08 */
    u8 unk_09[3];
    s32 value;     /* 0x0c: for SoundSys_Call020f1c00 */
    u8 volume_set; /* 0x10 */
    u8 unk_11[3];
    s32 volume; /* 0x14: for SoundSys_MoveVolume */
    s32 frames; /* 0x18: over how many frames */
} MusicCommands;

void MusicCommands_Apply(MusicCommands *self);
void MusicCommands_Clear(MusicCommands *self);
void MusicCommands_SetVolume(MusicCommands *self, int volume, int frames);
void MusicCommands_SetValue(MusicCommands *self, int value);
void MusicCommands_SetMusic(MusicCommands *self, int music);
void MusicCommands_Destruct(MusicCommands *self);
MusicCommands *MusicCommands_Construct(MusicCommands *self, Obj021c526c *owner);

#endif
