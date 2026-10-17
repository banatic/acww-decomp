/* Overlay 74: the faceless cat of the message file "sp_npc_mysterycat" with the model
 * npc_sp/model/mkab (person code 0xd020; Blanca is the game's cat without a face, but nothing
 * here names her). The spawner's table (main's spawner.h, data_020e1d8c) makes her as object
 * profile 0x67 with code 0xd020 and loads overlay 74 with her, when Spawner_CheckD020 allows it
 * (no event 0x3b to 0x44 on, and the town's record data_021f3278 accepted); her record at
 * 0x02279bb8 is what main's profile table data_020e3134 points to for profile 0x67.
 *
 * She is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x02279c68, 0x740 bytes, made by MysteryCat_Create, with no texture file of her own: her face
 * (MysteryCatFace, at 0x714) is the design kept in the town's record (WfcStats_Design of
 * data_021f3278), copied over her model's material "f". Her talk scene (MysteryCatTalk,
 * mystery_cat_talk.h, at 0x658) has the player draw her a face and pick a villager she will
 * imitate.
 *
 * Her states (MysteryCat.state), each an entry and an update function (C++ members taking
 * her) from the table data_ov074_02279d9c (filled at start-up by __sinit_ov074_022799d8), set
 * by MysteryCat_SetState and run each frame by MysteryCat_Update:
 *   0  talk end: once her action is idle the event ends: state 1;
 *   1  talked:   nothing;
 *   2  wander:   while she is in the camera's view she stands or, one frame in eight, walks or
 *                turns toward a free tile 12.0 away; out of view while moving, state 3;
 *   3  wait:     she stands without footsteps until she is in the camera's view: state 2;
 *   4  talk:     she turns to the talk's partner and talks.
 * The events she is told of (MysteryCat_OnEvent): code 0, state 0; code 3, the talk begins
 * (state 4); code 8, the event ended (state 2). */
#ifndef CLEAN_OV074_MYSTERY_CAT_H
#define CLEAN_OV074_MYSTERY_CAT_H

#include "autoload_2/vector.h"
#include "main/scene_base.h"
#include "main/vram_copy_task.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct MysteryCat;

/* Her talk scene (0xbc bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * data_ov074_02279bd8. Its receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct MysteryCatTalk {
    SceneBase base;           /* 0x00 */
    u8 unk_80[0x30];          /* 0x80: the scene's commands (scene_command.h) */
    struct MysteryCat *owner; /* 0xb0 */
    MemberPointer after;      /* 0xb4: void (talk), run once when the scene's command ends */
} MysteryCatTalk;

/* Her face: the design's texture file (a block of ClothTexture_Size bytes of the current heap,
 * main's item_texture.h) and the copy of it over her model's material "f". */
typedef struct MysteryCatFace {
    u8 *file;              /* 0x00: DesignModel, or null */
    VramCopyMaterial copy; /* 0x04 */
} MysteryCatFace;

/* The size of the special character's scene object she derives from, as far as it is used. */
#define MYSTERY_CAT_BASE_SIZE 0x654

typedef struct MysteryCat {
    u8 base[MYSTERY_CAT_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                      /* 0x654: enum MysteryCatState */
    MysteryCatTalk talk;            /* 0x658 */
    MysteryCatFace face;            /* 0x714 */
} MysteryCat;

enum MysteryCatState {
    MYSTERY_CAT_TALK_END = 0,
    MYSTERY_CAT_TALKED = 1,
    MYSTERY_CAT_WANDER = 2,
    MYSTERY_CAT_WAIT = 3,
    MYSTERY_CAT_TALK = 4,
    MYSTERY_CAT_STATES = 5
};

/* A state's functions in data_ov074_02279d9c. */
typedef struct MysteryCatStep {
    MemberPointer enter;  /* 0x00: int (cat); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (cat) */
} MysteryCatStep;

MysteryCat *MysteryCat_Destroy(MysteryCat *cat);
void *MysteryCat_Delete(void *cat);
void MysteryCatFace_End(MysteryCatFace *face, const void *heap);
void MysteryCatFace_Show(MysteryCatFace *face, u8 *model);
int MysteryCatFace_Textures(MysteryCatFace *face);
void MysteryCatFace_Start(MysteryCatFace *face, int heap, int model);
void MysteryCatFace_Destruct(MysteryCatFace *face);
MysteryCatFace *MysteryCatFace_Construct(MysteryCatFace *face);
void MysteryCat_OnEvent(MysteryCat *cat, int code);
int MysteryCat_MayAct(MysteryCat *cat);
int MysteryCat_UpdateTalk(void);
int MysteryCat_EnterTalk(MysteryCat *cat);
int MysteryCat_UpdateTalked(void);
int MysteryCat_UpdateTalkEnd(MysteryCat *cat);
int MysteryCat_EnterTalkEnd(void);
int MysteryCat_UpdateWait(MysteryCat *cat);
int MysteryCat_EnterWait(MysteryCat *cat);
int MysteryCat_UpdateWander(MysteryCat *cat);
int MysteryCat_IsSteeringAside(MysteryCat *cat);
int MysteryCat_SteerAside(MysteryCat *cat);
int MysteryCat_SidePoint(MysteryCat *cat, Vec3 *out, const Vec3 *offset);
int MysteryCat_PickWalkPoint(MysteryCat *cat, fx32 *x, fx32 *z);
int MysteryCat_InView(MysteryCat *cat);
int MysteryCat_IsInViewOf(int unused, const Vec3 *focus, const Vec3 *at);
int MysteryCat_EnterWander(MysteryCat *cat);
void MysteryCat_SetState(MysteryCat *cat, int state);
int MysteryCat_Update(MysteryCat *cat);
int MysteryCat_ModelName(void);
int MysteryCat_TextureName(void);
int MysteryCat_Leave(MysteryCat *cat);
int MysteryCat_Start(MysteryCat *cat);
int MysteryCat_Init(MysteryCat *cat);
int MysteryCat_AnimSpeed(void);
void *MysteryCat_Create(void);

#endif
