/* The effects and the sound of an act (act_effects.h). */
#include "act_effects.h"

#include "clean.h"
#include "sound.h"

static_assert(sizeof(ActEffectCue) == 4, "ActEffectCue layout");
static_assert(offsetof(ActEffects, cues) == 0x10, "ActEffects layout");
static_assert(offsetof(ActEffects, emitter) == 0x18, "ActEffects layout");
static_assert(offsetof(ActEffects, part) == 0x20, "ActEffects layout");
static_assert(offsetof(ActEffects, effect_arg) == 0x27, "ActEffects layout");
static_assert(sizeof(SceneMotionActPart) == 0xc, "SceneMotionActPart layout");

/* The effect kinds a cue may start (0 to 0x65). */
#define ACT_EFFECTS_KINDS 0x66
/* The act's sound number is this plus the act's. */
#define ACT_EFFECTS_SOUND_BASE 0x84
#define ACT_EFFECTS_VOLUME 0x7f
/* A part's sound frame: its half-word 0x0a. */
#define ACT_EFFECTS_PART_SOUND_FRAME 0x0a

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The effects: one started (its handle), moved, stopped. */
extern int func_020912ac(int kind, int arg, Vec3 *point, s16 *angle);
extern void func_02091278(int effect, Vec3 *point, s16 *angle, int a);
extern void func_0209129c(int effect);

/* The act's sound number. */
static int act_effects_sound(const ActEffects *self)
{
    return self->act + ACT_EFFECTS_SOUND_BASE;
}

/* func_0201a484: the group ends: its effects and its sound stop (ActEffects_StopAll). */
void ActEffects_End(ActEffects *self)
{
    ActEffects_StopAll(self);
}
CLEAN_AS(func_0201a484, ActEffects_End)

/* func_0201a48c: the group's frame, with the body playing `animation` at whole frame `frame`:
 * a kept sound is kept up (ActEffects_KeepSound), each effect is moved to `point` and `yaw`
 * (func_02091278), and both cues are stepped (ActEffects_StepCue). */
void ActEffects_Update(ActEffects *self, Vec3 *point, short yaw, int animation, u16 frame)
{
    s16 angle = yaw;
    ActEffects_KeepSound(self);
    for (int i = 0; i < ACT_EFFECTS_SLOTS; i++) {
        if (self->slots[i] != ACT_EFFECTS_NO_EFFECT) {
            func_02091278(self->slots[i], point, &angle, 0);
        }
    }
    for (int i = 0; i < ACT_EFFECTS_CUES; i++) {
        ActEffects_StepCue(self, point, angle, animation, frame, i);
    }
}
CLEAN_AS(func_0201a48c, ActEffects_Update)

/* func_0201a4e4: every effect started stops (func_0209129c) and its slot is freed, then the
 * sound stops (ActEffects_StopSound). */
void ActEffects_StopAll(ActEffects *self)
{
    for (int i = 0; i < ACT_EFFECTS_SLOTS; i++) {
        if (self->slots[i] == ACT_EFFECTS_NO_EFFECT) {
            continue;
        }
        func_0209129c(self->slots[i]);
        self->slots[i] = ACT_EFFECTS_NO_EFFECT;
    }
    ActEffects_StopSound(self);
}
CLEAN_AS(func_0201a4e4, ActEffects_StopAll)

/* func_0201a518: cue `index`, with an effect kind below 0x66 and while the body plays the
 * part's animation (not none): at the cue's frame its effect starts at `point` and `yaw` in a
 * free slot (func_020912ac), when there is one, and a cue that does not repeat is cleared;
 * then, at the part's sound frame, the sound may start (ActEffects_StartSound).
 * REQUIRES: the act is below 60 (the ROM reads the part's sound frame through the null record
 * of SceneMotion_Act otherwise); the group sets its act with the part's animation. */
void ActEffects_StepCue(ActEffects *self, Vec3 *point, int yaw, int animation, u16 frame, int index)
{
    ActEffectCue *cue = &self->cues[index];
    if (cue->effect < 0 || cue->effect >= ACT_EFFECTS_KINDS) {
        return;
    }
    if (self->animation != animation || self->animation == ACT_EFFECTS_NO_ANIMATION) {
        return;
    }

    s16 angle = (s16) yaw;
    if (cue->frame == frame) {
        int slot = ActEffects_FreeSlot(self);
        if (slot != -1) {
            self->slots[slot] = func_020912ac((u16) cue->effect, self->effect_arg, point, &angle);
            if (cue->repeat == 0) {
                ActEffects_ClearCues(self, cue, 1);
            }
        }
    }

    const u8 *record = (const u8 *) SceneMotion_Act(self->act);
    const u8 *part = record + (u32) self->part * sizeof(SceneMotionActPart);
    if (*(const s16 *) (part + ACT_EFFECTS_PART_SOUND_FRAME) == frame) {
        ActEffects_StartSound(self, cue);
    }
}
CLEAN_AS(func_0201a518, ActEffects_StepCue)

/* func_0201a5b0: the sound stops: a kept sound on the handle at 0x40 is stopped
 * (SoundSys_StopHandle40; one through the emitter just is not kept up any more); no sound. */
void ActEffects_StopSound(ActEffects *self)
{
    if (self->sound == ACT_EFFECTS_SOUND_KEPT && self->on_handle != 0) {
        SoundSys_StopHandle40();
    }
    self->sound = ACT_EFFECTS_SOUND_NONE;
}
CLEAN_AS(func_0201a5b0, ActEffects_StopSound)

/* func_0201a5d8: a kept sound through the emitter is played again (SoundEmitter_PlayEx). */
void ActEffects_KeepSound(ActEffects *self)
{
    if (self->sound == ACT_EFFECTS_SOUND_KEPT && self->on_handle == 0) {
        SoundEmitter_PlayEx(self->emitter, act_effects_sound(self), ACT_EFFECTS_VOLUME, 0);
    }
}
CLEAN_AS(func_0201a5d8, ActEffects_KeepSound)

/* func_0201a608: when `cue` repeats or no sound is on, the act's sound starts the way its
 * record's byte 0x19 says, which becomes the group's sound state: 1 through the emitter's
 * SoundEmitter_PlayEx (or SoundSys_StartOnHandle40), another through SoundEmitter_PlayB (or
 * SoundSys_StartOnHandle40B).
 * REQUIRES: the act is below 60 (SceneMotion_Act gives null for others, which the ROM reads
 * through). */
void ActEffects_StartSound(ActEffects *self, ActEffectCue *cue)
{
    const SceneMotionAct *record = SceneMotion_Act(self->act);
    if (cue->repeat != 1 && self->sound != ACT_EFFECTS_SOUND_NONE) {
        return;
    }
    self->sound = record->unk_19[0];
    if (self->sound == ACT_EFFECTS_SOUND_KEPT) {
        if (self->on_handle == 0) {
            SoundEmitter_PlayEx(self->emitter, act_effects_sound(self), ACT_EFFECTS_VOLUME, 0);
        } else {
            SoundSys_StartOnHandle40((u16) act_effects_sound(self));
        }
    } else {
        if (self->on_handle == 0) {
            SoundEmitter_PlayB(self->emitter, act_effects_sound(self), ACT_EFFECTS_VOLUME, 0);
        } else {
            SoundSys_StartOnHandle40B((u16) act_effects_sound(self));
        }
    }
}
CLEAN_AS(func_0201a608, ActEffects_StartSound)

/* func_0201a698: part `index` of an act begins: a part that restarts stops what runs first
 * (ActEffects_StopAll); a part with cues sets them and its animation (ActEffects_SetCues) and
 * becomes the group's part. */
void ActEffects_StartPart(ActEffects *self, SceneMotionActPart *parts, int index)
{
    SceneMotionActPart *part = &parts[index];
    if (part->restart != 0) {
        ActEffects_StopAll(self);
    }
    if (part->effect != 0) {
        ActEffects_SetCues(self, part->effect, part->unk_08, part->animation);
        self->part = index;
    }
}
CLEAN_AS(func_0201a698, ActEffects_StartPart)

/* func_0201a6c8: both cues are cleared, the first `count` are copied from `cues` (an address)
 * and the part's animation is `animation`. */
void ActEffects_SetCues(ActEffects *self, u32 cues, u32 count, u32 animation)
{
    ActEffects_ClearCues(self, self->cues, ACT_EFFECTS_CUES);
    ActEffects_CopyCues(self, self->cues, (const ActEffectCue *) (uintptr_t) cues, (int) count);
    self->animation = (s32) animation;
}
CLEAN_AS(func_0201a6c8, ActEffects_SetCues)

/* func_0201a6f8: the first free slot, or -1. */
int ActEffects_FreeSlot(ActEffects *self)
{
    for (int i = 0; i < ACT_EFFECTS_SLOTS; i++) {
        if (self->slots[i] == ACT_EFFECTS_NO_EFFECT) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_0201a6f8, ActEffects_FreeSlot)

/* func_0201a714: `count` cues copied from `src` to `dst` (MI_CpuCopy8). */
void ActEffects_CopyCues(ActEffects *self, ActEffectCue *dst, const ActEffectCue *src, int count)
{
    (void) self;
    MI_CpuCopy8(src, dst, (u32) count << 2);
}
CLEAN_AS(func_0201a714, ActEffects_CopyCues)

/* func_0201a720: `count` cues cleared (MI_CpuFill8 each), with no effect. */
void ActEffects_ClearCues(ActEffects *self, ActEffectCue *cues, int count)
{
    (void) self;
    for (int i = 0; i < count; i++) {
        MI_CpuFill8(&cues[i], 0, sizeof(ActEffectCue));
        cues[i].effect = -1;
    }
}
CLEAN_AS(func_0201a720, ActEffects_ClearCues)

/* func_0201a74c: no effect started (MI_CpuFill8 with 0xff), no cue, no animation, no sound, no
 * act; the sound through the emitter and an effect argument of 0. */
void ActEffects_Init(ActEffects *self)
{
    MI_CpuFill8(self->slots, 0xff, sizeof(self->slots));
    ActEffects_ClearCues(self, self->cues, ACT_EFFECTS_CUES);
    self->animation = ACT_EFFECTS_NO_ANIMATION;
    self->sound = ACT_EFFECTS_SOUND_NONE;
    self->act = ACT_EFFECTS_NO_ACT;
    self->effect_arg = 0;
    self->on_handle = 0;
}
CLEAN_AS(func_0201a74c, ActEffects_Init)

/* func_0201a790: the group's destructor, which does nothing. */
void ActEffects_Destruct(ActEffects *self)
{
    (void) self;
}
CLEAN_AS(func_0201a790, ActEffects_Destruct)

/* func_0201a794: the group's constructor, which does nothing (ActEffects_Init sets it up). */
void ActEffects_Construct(ActEffects *self)
{
    (void) self;
}
CLEAN_AS(func_0201a794, ActEffects_Construct)
