/* A town villager's mood as its scene object shows it (the villager scene object, class
 * 0x020d9e88, villager_scene_object.h: this member is at 0x83c and the villager's town record
 * at 0x830). The mood is kept in the villager's running state (villager_state.h): byte 0x18
 * is the mood and the counter at 0x1a the frames it lasts. 0 is no mood; 1 to 4 are the moods
 * shown; 5, or more, is none asked for.
 *
 * A mood is asked for (VillagerMood_Ask) with a length in units of 1200 frames, and taken on
 * at the next update once it is told to (VillagerMood_Apply); asking again for the mood
 * waiting lengthens it, and taking the mood the villager has lengthens that. Each update while
 * the member is on (VillagerMood_Start):
 * - the counter runs down, and the mood ends (back to 0) when it is out, or while the
 *   villager's action is busy;
 * - the villager's two standard animations (scene_standard_anims.h) are the mood's, from the
 *   tables data_020c8ed4 and data_020c8ee8 (mood 0: animations 0 and 1; mood 1: 0xe5 and
 *   0xe6; moods 2 and 4: 0xe7 and 0xe8; mood 3: 0xe9 and 0xea); mood 4 shows mood 3's for
 *   the personalities 0 and 3 ("bo_", "fu_") and mood 2's for the others;
 * - while the villager plays one of the mood's animations, a repeating effect (a member
 *   function pointer at 0x4c) spawns an effect at the villager's joint 16 and plays a sound
 *   on the member (the member is a sound emitter, sound_emitter.h): mood 1 effects 0x5a and
 *   0x5b in turn every 20 frames with sound 0x7b, moods 2 and 4 effect 0x5c every 20 frames
 *   with sound 0x83, moods 3 and 4 effect 0x62 every 14 frames with sound 0x7f;
 * - the emitter follows the villager's position.
 * While another system shares the session (Session_IsSlotTaken of this system's slot), no
 * mood is asked for, taken on or updated. */
#ifndef CLEAN_MAIN_VILLAGER_MOOD_H
#define CLEAN_MAIN_VILLAGER_MOOD_H

#include "ov004/member_pointer.h"
#include "types.h"

#define VILLAGER_MOOD_NONE 0
#define VILLAGER_MOOD_COUNT 5
#define VILLAGER_MOOD_UNSET 5 /* no mood asked for, shown or with its effect */

typedef struct VillagerMood {
    /* 0x00: a sound emitter of the base class (vtable 0x0213f074, sound_emitter_class.h).
     * QUIRK: `shown` below is its byte 0x40, which the emitters of kind 99 use as a volume;
     * this one is of kind 0, which does not. */
    u8 emitter[0x40];
    u8 shown; /* 0x40: the mood shown at the last update */
    u8 unk_41[3];
    s32 effect_mood;      /* 0x44: the mood whose effect runs, VILLAGER_MOOD_UNSET for none */
    u8 frame;             /* 0x48: the effect's frame in its cycle */
    u8 unk_49[3];         /* 0x49 */
    MemberPointer effect; /* 0x4c: the effect run each update, called with the villager */
    u8 asked;             /* 0x54: the mood asked for, VILLAGER_MOOD_UNSET for none */
    u8 unk_55;            /* 0x55 */
    u16 asked_frames;     /* 0x56: how long it lasts */
    u8 apply;             /* 0x58: take on the mood asked for at the next update */
    u8 on;                /* 0x59 */
    u8 sounds_on;         /* 0x5a: the effects play their sounds and spawn */
} VillagerMood;

void VillagerMood_Update(VillagerMood *mood, u8 *villager);
void VillagerMood_UpdateEffect(VillagerMood *mood, u8 *villager, int shown);
int VillagerMood_StartEffect(VillagerMood *mood, u8 *villager, unsigned int which);
int VillagerMood_IsFirstAnimation(VillagerMood *mood, u8 *villager);
void VillagerMood_RunEffect3(VillagerMood *mood, u8 *villager);
int VillagerMood_StartEffect3(VillagerMood *mood, u8 *villager);
void VillagerMood_PlayEffect3(VillagerMood *mood, u8 *villager);
void VillagerMood_RunEffect2(VillagerMood *mood, u8 *villager);
int VillagerMood_StartEffect2(VillagerMood *mood, u8 *villager);
void VillagerMood_PlayEffect2(VillagerMood *mood, u8 *villager);
void VillagerMood_RunEffect1(VillagerMood *mood, u8 *villager);
int VillagerMood_StartEffect1(VillagerMood *mood, u8 *villager);
int VillagerMood_PlayEffect1B(VillagerMood *mood, u8 *villager);
void VillagerMood_PlayEffect1A(VillagerMood *mood, u8 *villager);
int VillagerMood_IsMoodAnimation(VillagerMood *mood, u8 *villager);
int VillagerMood_SoundsOn(const VillagerMood *mood);
void VillagerMood_SoundsOff(VillagerMood *mood);
void VillagerMood_SetSoundsOn(VillagerMood *mood);
void VillagerMood_FollowVillager(VillagerMood *mood, u8 *villager);
int VillagerMood_PlayEffect(VillagerMood *mood, u8 *villager, int effect, int sound);
void VillagerMood_Apply(VillagerMood *mood);
void VillagerMood_Ask(VillagerMood *mood, unsigned int which, unsigned int units);
void VillagerMood_ClearAsked(VillagerMood *mood);
void VillagerMood_ShowAnimations(VillagerMood *mood, u8 *villager, int shown);
int VillagerMood_IsOn(const VillagerMood *mood);
int VillagerMood_Stop(VillagerMood *mood);
void VillagerMood_Start(VillagerMood *mood);
void VillagerMood_Reset(VillagerMood *mood);
void *VillagerMood_Destruct(VillagerMood *mood);
int VillagerMood_Construct(VillagerMood *mood);

#endif
