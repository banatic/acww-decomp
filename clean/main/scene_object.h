/* The scene object class with vtable 0x020d8c64 (obj_020d8c64.h): its own vtable slots (the
 * class with vtable 0x020da088 shares most of them) and the questions others ask of it.
 *
 * Its members, by place: the model (0xec, layered_model.h), the standard animations (0x2a0,
 * scene_standard_anims.h), the face (0x2ac, scene_face.h), the animation player (0x334,
 * speaker_anim.h), the mover (0x350, scene_mover.h), the probe ahead (0x3a8, scene_probe.h),
 * the pair at 0x3aa (scene_value_3aa.h), the look (0x3b0, scene_look.h), the talking state
 * (0x418, scene_talk_state.h), the act effects (0x420, act_effects.h), joint 11's matrix
 * (0x448) and the points of joints 16, 7 and 4 (0x478, 0x484, 0x490) read when it is drawn,
 * the sound emitter (0x514, sound_emitter.h), the footsteps (0x558, footsteps.h), the motion
 * (0x564, scene_motion.h), the action (0x618, scene_action.h), the held item's link (0x628,
 * held_item_link.h) and the scene it talks in (0x634, scene_base.h). Its state shared with a
 * session is in scene_share.h.
 *
 * Each frame (SceneObject_Update) it moves, and unless disabled (byte 0x561) it follows the
 * shared record when another system runs it, runs its action and motion, steers, collides,
 * looks, probes ahead, plays its animations and sounds, and publishes its state. */
#ifndef CLEAN_MAIN_SCENE_OBJECT_H
#define CLEAN_MAIN_SCENE_OBJECT_H

#include "autoload_2/vector.h"
#include "types.h"

struct SceneBase;

/* What SceneObject_SideStep answers. */
#define SCENE_OBJECT_CLEAR 0      /* nothing ahead blocks the way */
#define SCENE_OBJECT_BLOCKED 1    /* no free point to the side */
#define SCENE_OBJECT_SIDE_POINT 2 /* the free point to the side is given */

int SceneObject_VillagerRecord(void *object);
int SceneObject_Vfunc60(void *object);
void SceneObject_Vfunc4c(void *object, int event, int participant);
int SceneObject_Joint11Point(u8 *object, Vec3 *out);
int SceneObject_Leave(u8 *object);
void SceneObject_Vfunc30(void);
int SceneObject_Draw(u8 *object);
int SceneObject_Update(u8 *object);
int SceneObject_Vfunc68(void *object);
void SceneObject_ChangeState(u8 *object, int mode);
int SceneObject_Start(u8 *object);
int SceneObject_Init(u8 *object);
u8 SceneObject_IsEnabled(const u8 *object);
void SceneObject_VfuncA4(void);
u16 SceneObject_Act0Word(void *object);
int SceneObject_Kind11SecondAnimation(u8 *object);
int SceneObject_Kind11FirstAnimation(u8 *object);
int SceneObject_SideStep(u8 *object, Vec3 *out);
int SceneObject_TrySidePoint(u8 *object, Vec3 *out, const Vec3 *offset);
void SceneObject_OnTalkEnd(void *object);
void SceneObject_Vfunc8c(void *object);
void SceneObject_OnFrame8(void);
int SceneObject_Sort(u8 *object);
u32 SceneObject_Scene(u8 *object);
void SceneObject_SetScene(u8 *object, struct SceneBase *scene);
int SceneObject_ActorObject(u8 *object, int actor);
int SceneObject_AngleTo(u8 *object, u8 *target);
void *SceneObject_YawToActor(u8 *object, int actor);
int SceneObject_YawTo(u8 *object, u8 *target);
int SceneObject_IsNearActor(u8 *object, int distance, int actor);

int SceneObject_IsNear(u8 *object, u8 *other, int distance);
int SceneObject_DistanceToActor(u8 *object, int actor);
int SceneObject_DistanceTo(u8 *object, u8 *other);
int SceneObject_FacesPoint(u8 *object, s16 *yaw, const Vec3 *point);
int SceneObject_IsWithinQuarterTurn(int angle);
void SceneObject_SetColliderSize(u8 *object, int size);
void SceneObject_SetPerson(u8 *object, u16 *code);
void SceneObject_SetPersonIndex(u8 *object, u16 index);
u16 SceneObject_PersonIndex(u8 *object);
int SceneObject_ReleaseModel(u8 *object);
int SceneObject_LoadModel(u8 *object);

#endif
