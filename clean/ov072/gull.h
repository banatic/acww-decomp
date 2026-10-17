/* Overlay 72: the special character of the message archive "sp_npc_gull" with the model
 * npc_sp/model/seg, object profile 0x60 (its record at data_ov072_02279a3c, which the main
 * module's profile table data_020e3134 points to). Main's spawner (main/spawner.h) makes it
 * from its spawn table's entry of code 0xd015, loading this overlay with it; overlay 3's spot
 * object of profile 0x27 (ov003/spawn_spot.h) asks for it where that object stands. A scene
 * object of class 0x020da088 (special_scene_object.h) with vtable 0x02279b08, 0x724 bytes.
 *
 * It wants item 0x1568: its talk (GullTalk, gull_talk.h, at 0x658) takes each one the player
 * carries and counts them in the state block (item_1568_count.h) up to five, places up to five
 * of them in the town's inner acres (gull_spots.h), and once five were counted gives an item of
 * kind 0, group 0x13 (item_lists.h). The count's mark is set at the end of the first talk.
 *
 * Its own states (GULL_*), a table of C++ pointers to member functions (an entry and a run for
 * each state, data_ov072_02279bd8, filled by __sinit_ov072_022798b4):
 * - GULL_UNMET (before the mark): animation 0xef, its look turned away;
 * - GULL_IDLE (after the mark): it stands; once five were counted it plays one of the acts
 *   0xc-0xe every 400-999 frames;
 * - GULL_TALK: talks (turning to the player when no act plays) and, once its action ends,
 *   finishes its event and takes GULL_TALKED;
 * - GULL_TALKED: nothing.
 * Told of event 0 (its vtable slot 0x4c) it talks; told the act ended (8) it takes GULL_IDLE or
 * GULL_UNMET by the mark. */
#ifndef CLEAN_OV072_GULL_H
#define CLEAN_OV072_GULL_H

#include "gull_talk.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The states. */
#define GULL_UNMET 0
#define GULL_IDLE 1
#define GULL_TALK 2
#define GULL_TALKED 3
#define GULL_STATES 4

typedef struct Gull {
    u8 unk_000[0x8e];  /* the scene object (special_scene_object.h, scene_object.h) */
    s16 angle;         /* 0x08e: where it faces */
    u8 unk_090[0x458]; /* 0x090 */
    u32 flags;         /* 0x4e8: the scene object's flags (2: held, scene_action.h) */
    u8 unk_4ec[0x168]; /* 0x4ec: the members to 0x654 (gull.c names them) */
    s32 state;         /* 0x654: GULL_* (Gull_SetState) */
    GullTalk talk;     /* 0x658 */
    u8 all_counted;    /* 0x718: five were counted when it started (cleared when it talks) */
    u8 unk_719[3];     /* 0x719 */
    s32 act_wait;      /* 0x71c: GULL_IDLE's frames to its next act */
    s32 act_frames;    /* 0x720: the frames its act has left; when it talks, an act to stop first */
} Gull;

/* A state's row: its entry and its run (the null member pointer when it has none); the table,
 * filled by __sinit_ov072_022798b4 (GullInit_Tables). */
typedef struct GullStateRow {
    MemberPointer enter;
    MemberPointer run;
} GullStateRow;
extern GullStateRow data_ov072_02279bd8[GULL_STATES];

/* The object's life and vtable slots. */
Gull *Gull_Destruct(Gull *self);
Gull *Gull_DestructDelete(Gull *self);
void Gull_OnEvent(Gull *self, int code);
int Gull_MayAct(Gull *self);
int Gull_ModelName(void);
int Gull_TextureName(void);
int Gull_Start(Gull *self);
int Gull_Init(Gull *self);
Gull *Gull_Create(void);

/* Its states. */
int Gull_UpdateTalked(void);
int Gull_UpdateTalk(Gull *self);
int Gull_EnterTalk(Gull *self);
int Gull_UpdateIdle(Gull *self);
int Gull_EnterIdle(Gull *self);
int Gull_UpdateUnmet(void);
int Gull_EnterUnmet(Gull *self);
int Gull_CountDown(Gull *self, s32 *counter);
void Gull_SetState(Gull *self, int state);
int Gull_Update(Gull *self);

/* The overlay's static initialiser (ov072_static_init.c). */
void GullInit_Tables(void);

#endif
