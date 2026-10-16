/* The animations of a scene object's talking (the member at 0x334 of an object of class
 * 0x020d8c64, obj_020d8c64.h; func_0201b910 runs SpeakerAnim_Update each frame).
 *
 * The member holds an object at 0 whose vtable slot 0x08 gives a set of animations and whose
 * byte 0x04 is its entry there (func_02082fec gives animation 0, 1 or 2 of the entry,
 * func_0205cb80 its number, 0x144 for none). While the object's animation 2 is number 0x143
 * (func_02016618), the object talks (its talking state at 0x418: byte 0 is 1, word 4 a style
 * below 2) and the talking animation plays on the object's model (its member at 0xec,
 * func_02054240) over frames 0 to 7 or 6 to 12, picked anew each time a cycle ends; when the
 * talk stops or its style is 2 or more, the animation stops (func_020541e8).
 *
 * Each frame, unless `keep_speed`, the speed of the object's body animation (at 0x188, as in
 * footsteps.h; its frame count at 0x18c, frame at 0x190 and speed at 0x198) follows the
 * object's speed at 0x98 scaled by `speed_scale`. */
#ifndef CLEAN_MAIN_SPEAKER_ANIM_H
#define CLEAN_MAIN_SPEAKER_ANIM_H

#include "types.h"

typedef struct SpeakerAnim {
    const u8 *set_vtable; /* 0x00: the holder of the animations (slot 0x08: the set) */
    s8 entry;             /* 0x04: its entry in the set, -1 once released */
    u8 unk_05[3];
    s32 speed;   /* 0x08: the body animation's speed (fx32), 0x1000 when still */
    s32 variant; /* 0x0c: the frames of the talking animation: 1 for 6-12, else 0-7 */
    u8 playing;  /* 0x10: 1 while the talking animation plays */
    u8 unk_11[3];
    s32 speed_scale; /* 0x14 (fx32) */
    u8 keep_speed;   /* 0x18: 1 to leave the body animation's speed alone */
} SpeakerAnim;

void SpeakerAnim_SetTalkStyle(SpeakerAnim *anim, u8 *object);
void SpeakerAnim_Release(SpeakerAnim *anim);
void SpeakerAnim_Update(SpeakerAnim *anim, u8 *object);
int SpeakerAnim_LastFrame(SpeakerAnim *anim, int variant);
int SpeakerAnim_FirstFrame(SpeakerAnim *anim, int variant);
void SpeakerAnim_UpdateSpeed(SpeakerAnim *anim, u8 *object);
int SpeakerAnim_Number(SpeakerAnim *anim, int which);
int SpeakerAnim_BodyAtEnd(SpeakerAnim *anim, u8 *object);
void SpeakerAnim_PlayFromBodyFrame(SpeakerAnim *anim, u8 *object, int animation, int arg, int slot);
void SpeakerAnim_SetKeepSpeed(SpeakerAnim *anim, int keep);
void SpeakerAnim_StopTalk(SpeakerAnim *anim, u8 *object);
void SpeakerAnim_StartTalk(SpeakerAnim *anim, u8 *object, int first, int last);

/* Loading and playing the animations of the member's entry (slot 0 the body, 1 the pose of a
 * held item, 2 the talking animation) on the object's model (its member at 0xec). */
int SpeakerAnim_TalkResource(SpeakerAnim *anim);
void SpeakerAnim_LoadTalk(SpeakerAnim *anim);
int SpeakerAnim_HasTalk(SpeakerAnim *anim);
void SpeakerAnim_PlayItemPose(SpeakerAnim *anim, u8 *object, u16 *item, int pose, u16 arg);
void SpeakerAnim_Play(SpeakerAnim *anim, u8 *object, int number, int arg, int mode, int speed, u16 frame, int slot);
int SpeakerAnim_IsBody(SpeakerAnim *anim, int number, void *standard);
int SpeakerAnim_Resolve(SpeakerAnim *anim, int number, void *standard);
int SpeakerAnim_Load(SpeakerAnim *anim, int number, int slot);
int SpeakerAnim_Init(SpeakerAnim *anim, u8 *object, s32 speed_scale);
SpeakerAnim *SpeakerAnim_Construct(SpeakerAnim *anim);
SpeakerAnim *SpeakerAnim_Destruct(SpeakerAnim *anim);

#endif
