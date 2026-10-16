/* The scene object class with vtable 0x020dd33c (0x11c bytes, a process of its own: the root
 * of the scene objects at 0x020da13c, with a sound emitter base at 0xdc). Its one instance is
 * kept at data_021c9350 while it exists, and the functions here ask it or hand it an actor,
 * each doing nothing (0) without it.
 *
 * It keeps an item (0xfff1 for none; a fish display model for the fish items 0x12e8-0x131f),
 * the two actors that take part, a point and a reach around it, a mode (0 while idle) and a
 * stage (0xc after a reset). The player's field states 0x30 to 0x35 (field_actor_states.c) and
 * scene motions of kinds 14 and 17 (scene_motion.c) use it. */
#ifndef CLEAN_MAIN_OBJ_020DD33C_H
#define CLEAN_MAIN_OBJ_020DD33C_H

#include "autoload_2/process.h"
#include "autoload_2/vector.h"
#include "main/actor.h"
#include "types.h"

/* Obj020dd33c.item without an item, and Obj020dd33c_Stage without the object. */
#define OBJ_020DD33C_NO_ITEM 0xfff1
#define OBJ_020DD33C_NO_STAGE 0xc

/* Obj020dd33c.look: the item drawn as model 0x27 instead (except items 0x155f-0x1564); mode 8
 * puts it back to 0. */
#define OBJ_020DD33C_LOOK_MODEL_27 2

/* The modes (Obj020dd33c.mode, actor_mode): 1 to 11 run the handlers of the table at
 * data_021c9460 (by mode and kind); OBJ_020DD33C_NO_MODE in actor_mode asks for none. */
#define OBJ_020DD33C_MODE_COUNT 12
#define OBJ_020DD33C_NO_MODE 0xc

typedef struct Obj020dd33c {
    Process base; /* 0x00 */
    u16 item;     /* 0x50 */
    u8 pad_52[2];
    int look; /* 0x54: OBJ_020DD33C_LOOK_MODEL_27 or 0 */
    u8 stage; /* 0x58 */
    u8 pad_59[3];
    int kind;        /* 0x5c: which column (0 or 1) of the mode table runs */
    Vec3 point;      /* 0x60: where the item is drawn */
    Vec3 target;     /* 0x6c: where the point is going */
    Vec3 offset;     /* 0x78: added to the point, turned to the first actor's heading */
    Vec3 velocity;   /* 0x84: the offset before turning, or the point less the held point */
    Vec3 speed;      /* 0x90: the step on each axis towards the target */
    Vec3 goal;       /* 0x9c: the point beside the first actor the item settles at */
    Vec3 scale;      /* 0xa8: the item's drawn size (x, y and z kept equal) */
    s16 rotation[3]; /* 0xb4: the item's drawn angles */
    u8 pad_ba[2];
    fx32 reach;      /* 0xbc: the distance from the point an actor is near within */
    fx32 scale_step; /* 0xc0: the step the scale shrinks by */
    int fish_model;  /* 0xc4: the fish display's model of the item, -1 for none */
    u8 mode;         /* 0xc8: 0 while idle */
    u8 pad_c9[3];
    Actor *actors[2]; /* 0xcc: the first is the one that started it */
    u8 phase;         /* 0xd4: the step within a mode's handler */
    u8 unk_d5;        /* 0xd5: a countdown set when actor_mode becomes 1 or 7 */
    u16 frames;       /* 0xd6: frames counted in the mode */
    u8 shown;         /* 0xd8: 1 when the item is drawn */
    u8 unk_d9;        /* 0xd9: 1 while the mode's movement runs, 0 once it is over */
    u8 actor_mode;    /* 0xda: the mode the first actor last set */
    u8 pad_db;
    u8 emitter[0x40]; /* 0xdc: the sound emitter base */
} Obj020dd33c;

void *Obj020dd33c_Destruct(Obj020dd33c *obj);
void *Obj020dd33c_Delete(Obj020dd33c *obj);
int Obj020dd33c_SetStage(int stage, void *actor);
void Obj020dd33c_Item(u16 *item);
int Obj020dd33c_IsBusy(void);
int Obj020dd33c_InMode(int mode);
int Obj020dd33c_Lead(void *actor);
int Obj020dd33c_Point(Vec3 *point);
int Obj020dd33c_IsNear(const Actor *actor);
void Obj020dd33c_Finish(void *actor);
u8 Obj020dd33c_Stage(void);
int Obj020dd33c_SetActorMode(int mode, void *actor);
int Obj020dd33c_IsLead(void *actor);
int Obj020dd33c_Start(u16 *item, int look, int stage, int kind, Actor *first, Actor *second);

/* The mode handlers (obj_020dd33c_modes.c), named by mode and kind; Enter runs when the mode
 * starts, Update each frame. */
void Obj020dd33c_UpdateMode9Kind1(Obj020dd33c *obj);
void Obj020dd33c_Mode9Kind1Shrink(Obj020dd33c *obj);
void Obj020dd33c_Mode9Kind1Follow(Obj020dd33c *obj);
void Obj020dd33c_Mode9Kind1Wait(Obj020dd33c *obj);
void Obj020dd33c_EnterMode9Kind1(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode7Kind1(Obj020dd33c *obj);
void Obj020dd33c_EnterMode7Kind1(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode5Kind1(Obj020dd33c *obj);
void Obj020dd33c_EnterMode5Kind1(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode4Kind1(Obj020dd33c *obj);
void Obj020dd33c_EnterMode4Kind1(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode3Kind1(Obj020dd33c *obj);
void Obj020dd33c_EnterMode3Kind1(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode2Kind1(Obj020dd33c *obj);
void Obj020dd33c_EnterMode2Kind1(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode1Kind1(Obj020dd33c *obj);
void Obj020dd33c_Mode1Kind1Grow(Obj020dd33c *obj);
void Obj020dd33c_Mode1Kind1Drop(Obj020dd33c *obj);
void Obj020dd33c_Mode1Kind1Wait(Obj020dd33c *obj);
void Obj020dd33c_EnterMode1Kind1(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode11Kind0(Obj020dd33c *obj);
void Obj020dd33c_Mode11Kind0Shrink(Obj020dd33c *obj);
void Obj020dd33c_Mode11Kind0Follow(Obj020dd33c *obj);
void Obj020dd33c_EnterMode11Kind0(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode8Kind0(Obj020dd33c *obj);
void Obj020dd33c_EnterMode8Kind0(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode7Kind0(Obj020dd33c *obj);
void Obj020dd33c_EnterMode7Kind0(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode6Kind0(void);
void Obj020dd33c_EnterMode6Kind0(void);
void Obj020dd33c_UpdateMode5Kind0(Obj020dd33c *obj);
void Obj020dd33c_EnterMode5Kind0(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode10Kind0(Obj020dd33c *obj);
void Obj020dd33c_EnterMode10Kind0(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode4Kind0(Obj020dd33c *obj);
void Obj020dd33c_EnterMode4Kind0(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode3Kind0(Obj020dd33c *obj);
void Obj020dd33c_EnterMode3Kind0(Obj020dd33c *obj);
void Obj020dd33c_EnterMode2Kind0(Obj020dd33c *obj);
void Obj020dd33c_UpdateMode1Kind0(Obj020dd33c *obj);
void Obj020dd33c_Mode1Kind0Rise(Obj020dd33c *obj);
void Obj020dd33c_Mode1Kind0Hold(Obj020dd33c *obj);
void Obj020dd33c_EnterMode1Kind0(Obj020dd33c *obj);

/* The instance's own methods. */
void Obj020dd33c_HoldOffset(Vec3 *out, Obj020dd33c *obj, int index);
void Obj020dd33c_PlaceByActor(Obj020dd33c *obj, Vec3 *out, const Vec3 *offset, unsigned int index);
int Obj020dd33c_SetStageIfLead(Obj020dd33c *obj, u8 stage, void *actor);
void Obj020dd33c_SetMoving(Obj020dd33c *obj, u8 moving);
void Obj020dd33c_HoldPoint(Obj020dd33c *obj, Vec3 *out);
void Obj020dd33c_Draw(Obj020dd33c *obj);
void Obj020dd33c_DrawModel(Obj020dd33c *obj, int model, const Vec3 *position, const Vec3 *scale, const s16 *rotation);
void Obj020dd33c_DrawItem(Obj020dd33c *obj, const u16 *item, const Vec3 *position, const Vec3 *scale, const s16 *rotation);
int Obj020dd33c_ModeAllowsAway(Obj020dd33c *obj);
int Obj020dd33c_SetActorModeIfLead(Obj020dd33c *obj, int mode, void *actor);
void Obj020dd33c_SetActorModeOf(Obj020dd33c *obj, u8 mode);
void Obj020dd33c_ClearActorMode(Obj020dd33c *obj);
int Obj020dd33c_MakeLead(Obj020dd33c *obj, void *actor);
int Obj020dd33c_IsActor(Obj020dd33c *obj, void *actor, unsigned int index);
int Obj020dd33c_Begin(Obj020dd33c *obj, u16 *item, int look, u8 stage, int kind, Actor *first, Actor *second);

/* The offsets a held fish is placed by (the table of data_020dd31c): for each holder shape
 * (Obj020dd33c_HolderShape) and each offset class (CreatureTable_OffsetClass), two of them. */
typedef struct Obj020dd33cFishOffsets {
    Vec3 first;  /* 0x00: Obj020dd33c_FishFirstOffset */
    Vec3 second; /* 0x0c: Obj020dd33c_FishSecondOffset */
} Obj020dd33cFishOffsets;

/* Obj020dd33c_HolderShape: those of three special characters, the default one (also of any
 * holder of class 9) and the two the villagers' species fall into. */
#define OBJ_020DD33C_SHAPE_D00C 0
#define OBJ_020DD33C_SHAPE_D013 1
#define OBJ_020DD33C_SHAPE_D012 2
#define OBJ_020DD33C_SHAPE_DEFAULT 3
#define OBJ_020DD33C_SHAPE_SPECIES_A 4
#define OBJ_020DD33C_SHAPE_SPECIES_B 5

/* The process's own steps (its class's vtable) and its making. */
void Obj020dd33c_Reset(Obj020dd33c *obj);
int Obj020dd33c_DrawStep(Obj020dd33c *obj);
int Obj020dd33c_ExecuteStep(Obj020dd33c *obj);
int Obj020dd33c_DeleteStep(void);
int Obj020dd33c_CreateStep(Obj020dd33c *obj);
Obj020dd33c *Obj020dd33c_New(void);

/* Where a held fish goes, by its holder. */
Vec3 *Obj020dd33c_FishSecondOffset(Actor *holder, int offset_class);
Vec3 *Obj020dd33c_FishFirstOffset(Actor *holder, int offset_class);
int Obj020dd33c_HolderShape(Actor *holder);
u32 Obj020dd33c_FishScale(u32 offset_class);

#endif
