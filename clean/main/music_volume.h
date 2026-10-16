/* The member at 0x1c4 of the field's sound object (music_queue.h): eight slots, each of which
 * may want the music's volume moved while the head of the music queue is playing.
 *
 * Every frame each slot's handler runs (slot i gets handler i); a handler that wants a change
 * asks for a volume over a number of frames and marks it pending. Then, when the head request
 * is current and has a music, the pending slot of lowest index gives the frames and the active slot
 * (state not 0) of lowest index gives the volume, and that is asked of the sound system through
 * the object's commands (music_commands.h). Slot 7 follows the head request's own volume and is
 * active while the queue is not empty, so it is the volume the others fall back to.
 *
 * The slots' states are set from outside: slot 1 by overlays 90 to 92, slot 2 by
 * func_02066c54 and func_02066f8c, slots 3 and 4 by the field actor (overlay 3). */
#ifndef CLEAN_MAIN_MUSIC_VOLUME_H
#define CLEAN_MAIN_MUSIC_VOLUME_H

#include "music_queue.h"
#include "types.h"

#define MUSIC_VOLUME_SLOTS 8
#define MUSIC_VOLUME_FULL 0x7f

typedef struct MusicVolumeSlot {
    u8 pending; /* a change of volume was asked this frame */
    u8 held;    /* this frame its asks are ignored */
    u8 unk_02[2];
    s32 volume; /* 0x04 */
    s32 frames; /* 0x08 */
    s32 state;  /* 0x0c: 0 when it does not want the volume changed */
} MusicVolumeSlot;

typedef struct MusicVolume {
    Obj021c526c *owner;
    MusicVolumeSlot slots[MUSIC_VOLUME_SLOTS]; /* 0x04 */
    s32 countdown;                             /* 0x84: slot 2's frames left in state 9 */
} MusicVolume;

void MusicVolume_ClearHeld(MusicVolume *self);
void MusicVolume_ClearPending(MusicVolume *self);
void MusicVolume_Apply(MusicVolume *self);
void MusicVolume_HoldForHead(MusicVolume *self);
void MusicVolume_UpdateHeadSlot(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_ClearStarted(MusicRequest *request);
void MusicVolume_UpdateSceneSlot(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_UpdateGroundSlot(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_UpdateSlot4(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_UpdateSlot3(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_UpdateSlot2(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_UpdateSlot1(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_UpdateSlot0(MusicVolume *self, MusicVolumeSlot *slot);
void MusicVolume_UpdateSlots(MusicVolume *self);
void MusicVolume_EndSlot4(MusicVolume *self);
void MusicVolume_BeginSlot4(MusicVolume *self);
void MusicVolume_EndSlot3(MusicVolume *self);
void MusicVolume_BeginSlot3(MusicVolume *self);
void MusicVolume_EndSlot1(MusicVolume *self);
void MusicVolume_SetSlot1(MusicVolume *self, int index);
void MusicVolume_EndSlot2(MusicVolume *self);
void MusicVolume_BeginSlot2(MusicVolume *self);
void MusicVolume_Reset(MusicVolume *self);
void MusicVolume_Execute(MusicVolume *self);
void MusicVolume_Delete(MusicVolume *self);
void MusicVolume_Create(MusicVolume *self);
MusicVolume *MusicVolume_Destruct(MusicVolume *self);
MusicVolume *MusicVolume_Construct(MusicVolume *self, Obj021c526c *owner);
void MusicVolume_Request(MusicVolumeSlot *slot, int volume, int frames, int pending);
void MusicVolume_ClearSlot(MusicVolumeSlot *slot);
void MusicVolume_DestructSlot(MusicVolumeSlot *slot);
MusicVolumeSlot *MusicVolume_ConstructSlot(MusicVolumeSlot *slot);

#endif
