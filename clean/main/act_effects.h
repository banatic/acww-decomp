/* The effects and the sound of an act (the 60 records at data_020c8290, SceneMotionAct,
 * scene_motion_kinds.h): a group kept by the field actors (at 0x90c, state 0x14) and the scene
 * objects (at 0x420, motion kind 8).
 *
 * A part of an act names an animation of the body and up to two cues: an effect (a kind below
 * 0x66) started at a frame of that animation, once or each time the frame comes round. Each
 * frame the group (ActEffects_Update) moves the effects it started to the given point and
 * angle, and while the body plays the part's animation starts each cue at its frame. At the
 * part's sound frame (the part's half-word 0x0a) the act's sound starts (number 0x84 plus the
 * act's), through the group's emitter or, with `on_handle`, the sound system's handle at 0x40;
 * the record's byte 0x19 picks how (1: a sound the group keeps up each frame). */
#ifndef CLEAN_MAIN_ACT_EFFECTS_H
#define CLEAN_MAIN_ACT_EFFECTS_H

#include "autoload_2/vector.h"
#include "scene_motion_kinds.h"
#include "sound_emitter.h"
#include "types.h"

/* A slot without an effect, an animation of none, and the act of none. */
#define ACT_EFFECTS_NO_EFFECT (-1)
#define ACT_EFFECTS_NO_ANIMATION 0x137
#define ACT_EFFECTS_NO_ACT 60

/* The sound's states: kept up each frame, and none. */
#define ACT_EFFECTS_SOUND_KEPT 1
#define ACT_EFFECTS_SOUND_NONE 2

#define ACT_EFFECTS_SLOTS 4
#define ACT_EFFECTS_CUES 2

/* An effect started at a frame of the part's animation. */
typedef struct ActEffectCue {
    s16 effect; /* the effect's kind; -1 for none */
    u8 frame;
    u8 repeat; /* 0: started once, then the cue is cleared; 1: also starts the sound again */
} ActEffectCue;

typedef struct ActEffects {
    s32 slots[ACT_EFFECTS_SLOTS];        /* 0x00: the effects started, ACT_EFFECTS_NO_EFFECT for none */
    ActEffectCue cues[ACT_EFFECTS_CUES]; /* 0x10 */
    SoundEmitter *emitter;               /* 0x18 */
    s32 animation;                       /* 0x1c: the part's animation of the body */
    s32 part;                            /* 0x20: the part (0 or 1) of the act */
    u8 sound;                            /* 0x24: ACT_EFFECTS_SOUND_KEPT, _NONE or another */
    u8 act;                              /* 0x25: the act's number */
    u8 on_handle;                        /* 0x26: nonzero: the sound plays on the handle at 0x40 */
    u8 effect_arg;                       /* 0x27: handed to func_020912ac with each effect */
} ActEffects;

void ActEffects_End(ActEffects *self);
void ActEffects_Update(ActEffects *self, Vec3 *point, short yaw, int animation, u16 frame);
void ActEffects_StopAll(ActEffects *self);
void ActEffects_StepCue(ActEffects *self, Vec3 *point, int yaw, int animation, u16 frame, int index);
void ActEffects_StopSound(ActEffects *self);
void ActEffects_KeepSound(ActEffects *self);
void ActEffects_StartSound(ActEffects *self, ActEffectCue *cue);
void ActEffects_StartPart(ActEffects *self, SceneMotionActPart *parts, int index);
void ActEffects_SetCues(ActEffects *self, u32 cues, u32 count, u32 animation);
int ActEffects_FreeSlot(ActEffects *self);
void ActEffects_CopyCues(ActEffects *self, ActEffectCue *dst, const ActEffectCue *src, int count);
void ActEffects_ClearCues(ActEffects *self, ActEffectCue *cues, int count);
void ActEffects_Init(ActEffects *self);
void ActEffects_Destruct(ActEffects *self);
void ActEffects_Construct(ActEffects *self);

#endif
