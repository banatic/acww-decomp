/* What the field's sound object asks of the sound system at the end of the frame
 * (music_commands.h). */
#include "music_commands.h"

#include "clean.h"
#include "sound.h"

static_assert(sizeof(MusicCommands) == 0x1c, "commands size");
static_assert(offsetof(MusicCommands, music) == 0x06, "commands music");
static_assert(offsetof(MusicCommands, value) == 0x0c, "commands value");
static_assert(offsetof(MusicCommands, volume) == 0x14, "commands volume");

/* The object of the running process 0x020da334. */
extern Obj021c526c *data_021c526c;

/* func_02035f6c: each thing set handed on and unset: the word, then the music (the member at
 * 0x2f0 of the object at data_021c526c is told of it), then the volume. */
void MusicCommands_Apply(MusicCommands *self)
{
    if (self->value_set != 0) {
        self->value_set = 0;
        SoundSys_Call020f1c00(self->value);
    }
    if (self->music_set != 0) {
        self->music_set = 0;
        SoundSys_ChangeMusic(self->music);
        Music2f0_OnMusic((Music2f0 *) (void *) data_021c526c->unk_2f0, self->music);
    }
    if (self->volume_set != 0) {
        self->volume_set = 0;
        SoundSys_MoveVolume(self->volume, self->frames);
    }
}
CLEAN_AS(func_02035f6c, MusicCommands_Apply)

/* func_02035fc0: nothing set (the owner is kept). */
void MusicCommands_Clear(MusicCommands *self)
{
    self->music_set = 0;
    self->music = MUSIC_NONE;
    self->value_set = 0;
    self->value = 0;
    self->volume_set = 0;
    self->volume = 0;
    self->frames = 0;
}
CLEAN_AS(func_02035fc0, MusicCommands_Clear)

/* func_02035fd8: the volume to move to over `frames` frames. */
void MusicCommands_SetVolume(MusicCommands *self, int volume, int frames)
{
    self->volume_set = 1;
    self->volume = volume;
    self->frames = frames;
}
CLEAN_AS(func_02035fd8, MusicCommands_SetVolume)

/* func_02035fe4: the word for SoundSys_Call020f1c00. */
void MusicCommands_SetValue(MusicCommands *self, int value)
{
    self->value_set = 1;
    self->value = value;
}
CLEAN_AS(func_02035fe4, MusicCommands_SetValue)

/* func_02035fec: the music to change to (its low 16 bits). */
void MusicCommands_SetMusic(MusicCommands *self, int music)
{
    self->music_set = 1;
    self->music = (u16) music;
}
CLEAN_AS(func_02035fec, MusicCommands_SetMusic)

/* func_02035ff4: the destructor: nothing. */
void MusicCommands_Destruct(MusicCommands *self)
{
    (void) self;
}
CLEAN_AS(func_02035ff4, MusicCommands_Destruct)

/* func_02035ff8: the constructor: the owner kept and nothing set. */
MusicCommands *MusicCommands_Construct(MusicCommands *self, Obj021c526c *owner)
{
    self->owner = owner;
    MusicCommands_Clear(self);
    return self;
}
CLEAN_AS(func_02035ff8, MusicCommands_Construct)
