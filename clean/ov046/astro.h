/* Overlay 46: the special character of the message archive "sp_npc_astro" with the model
 * npc_sp/model/ows, object profile 0x6d (its record at data_ov046_02262010, which the main
 * module's profile table data_020e3134 points to). The overlay is the first of the two extra
 * overlays of scene 0x22 (its SceneInfo, data_ov019_022600e4, data_020e55bc), a room whose
 * setup makes this character at (14.0, 0, 21.75). A scene object of class 0x020da088
 * (special_scene_object.h) with vtable 0x022620e0, 0x744 bytes.
 *
 * It keeps the players' constellations (constellations.h): through its talk scene (AstroTalk,
 * astro_talk.h, at 0x658) the player makes a constellation in a free slot, renames, redraws or
 * removes one, or asks when one is in view.
 *
 * Its own states (ASTRO_*), a table of C++ pointers to member functions (an entry and a run for
 * each state, data_ov046_0226248c, filled by __sinit_ov046_02261cac):
 * - ASTRO_IDLE: stands for 120 frames, then plays animation 0xf0 (ASTRO_ANIMATE), unless the
 *   session is linked, game variable 0x4a is set or it is evening or night;
 * - ASTRO_TURN_BACK: turns back to the angle it started at, then ASTRO_IDLE;
 * - ASTRO_ANIMATE: animation 0xf0 with effect 0x3c at its joint 16;
 * - ASTRO_TALK: turns to the one it talks with and talks; once its action ends its event is
 *   finished and it takes ASTRO_TALKED;
 * - ASTRO_TALKED: nothing.
 * While it stands or plays its animation, a player who stands near (16.5, -, 23.0) facing it
 * and presses A or touches it calls it over (Astro_IsCalled, Astro_TakeCall). Told of event 0 or 1 (its
 * vtable slot 0x4c) it talks; told the act ended (code 8) it turns back. */
#ifndef CLEAN_OV046_ASTRO_H
#define CLEAN_OV046_ASTRO_H

#include "astro_talk.h"
#include "autoload_2/vector.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The states. */
#define ASTRO_IDLE 0
#define ASTRO_TURN_BACK 1
#define ASTRO_ANIMATE 2
#define ASTRO_TALK 3
#define ASTRO_TALKED 4
#define ASTRO_STATES 5

typedef struct Astro {
    u8 unk_000[0x8e];  /* the scene object (special_scene_object.h, scene_object.h) */
    s16 angle;         /* 0x08e: where it faces */
    u8 unk_090[0x3e8]; /* 0x090 */
    Vec3 joint16;      /* 0x478: the point of joint 16 (scene_object.h) */
    u8 unk_484[0x64];  /* 0x484 */
    u32 flags;         /* 0x4e8: the scene object's flags (2: held, scene_action.h) */
    u8 unk_4ec[0x168]; /* 0x4ec: the members to 0x654 (astro.c names them) */
    s32 state;         /* 0x654: ASTRO_* (Astro_SetState) */
    AstroTalk talk;    /* 0x658 */
    u16 countdown;     /* 0x738: ASTRO_IDLE's frames left */
    s16 home_angle;    /* 0x73a: the angle it faced when it started */
    u16 anim_word;     /* 0x73c: the word ASTRO_ANIMATE's animation is asked with */
    u8 was_animating;  /* 0x73e: set by ASTRO_ANIMATE, cleared when its talk ends */
    u8 unk_73f;        /* 0x73f */
    s32 effect;        /* 0x740: effect 0x3c's handle, -1 for none */
} Astro;

/* A state's row: its entry and its run (the null member pointer when it has none); the table,
 * filled by __sinit_ov046_02261cac (AstroInit_Tables). */
typedef struct AstroStateRow {
    MemberPointer enter;
    MemberPointer run;
} AstroStateRow;
extern AstroStateRow data_ov046_0226248c[ASTRO_STATES];

/* The object's life and vtable slots. */
Astro *Astro_Destruct(Astro *self);
Astro *Astro_DestructDelete(Astro *self);
int Astro_TakeCall(Astro *self);
int Astro_IsCalled(Astro *self);
void Astro_OnEvent(Astro *self, int code);
int Astro_MayTalk(Astro *self);
int Astro_MayAct(Astro *self);
int Astro_ModelName(void);
int Astro_TextureName(void);
int Astro_Leave(Astro *self);
int Astro_Start(Astro *self);
int Astro_Init(Astro *self);
Astro *Astro_Create(void);

/* Its states. */
int Astro_UpdateTalked(void);
int Astro_UpdateTalk(Astro *self);
int Astro_EnterTalk(Astro *self);
int Astro_UpdateAnimate(Astro *self);
int Astro_EnterAnimate(Astro *self);
int Astro_UpdateTurnBack(Astro *self);
int Astro_EnterTurnBack(Astro *self);
int Astro_UpdateIdle(Astro *self);
int Astro_EnterIdle(Astro *self);
void Astro_SetState(Astro *self, unsigned int state);
int Astro_Update(Astro *self);

/* The overlay's static initialiser (astro_static_init.c). */
void AstroInit_Tables(void);

#endif
