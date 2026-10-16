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

typedef struct Obj020dd33c {
    Process base; /* 0x00 */
    u16 item;     /* 0x50 */
    u8 pad_52[2];
    int unk_54; /* 0x54 */
    u8 stage;   /* 0x58 */
    u8 pad_59[3];
    int unk_5c; /* 0x5c */
    Vec3 point; /* 0x60 */
    u8 unk_6c[0x50];
    fx32 reach; /* 0xbc: the distance from the point an actor is near within */
    u8 unk_c0[4];
    int fish_model; /* 0xc4: the fish display's model of the item, -1 for none */
    u8 mode;        /* 0xc8: 0 while idle */
    u8 pad_c9[3];
    void *actors[2]; /* 0xcc: the first is the one that started it */
    u8 unk_d4;
    u8 unk_d5; /* 0xd5 */
    u16 unk_d6;
    u8 unk_d8;
    u8 unk_d9;     /* 0xd9 */
    u8 actor_mode; /* 0xda: the mode the first actor last set */
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

#endif
