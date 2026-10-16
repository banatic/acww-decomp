/* How a scene object walks and turns (class 0x020d8c64, obj_020d8c64.h: its member at 0x350),
 * driven by its motion's kinds (scene_motion_kinds.h).
 *
 * A mode (SceneMover_SetMode, from the five records at data_020c822c) picks a pace, a turning
 * rate, a reach and the body animation: 0 stands, 1 walks, 2 walks at the second pace, 3 turns
 * in place, 4 turns first (the walking angle is set at once and no animation starts). A pace is
 * a speed with the steps it is reached by (speeding up, slowing down); paces 1 and 2 are the
 * object's (SceneMover_SetPace), pace 0 stands.
 *
 * Each frame the object's walking angle (0x94) turns towards the mover's angle by the turning
 * rate, the way `turn_way` says, and the object faces it (SceneMover_Steer); its speed (0x98)
 * goes to the pace's, without passing the end point when it heads straight for it, and the
 * object moves (SceneMover_Drive). The mover's angle is kept on the end point by the motions
 * (SceneMover_AimAtEnd). */
#ifndef CLEAN_MAIN_SCENE_MOVER_H
#define CLEAN_MAIN_SCENE_MOVER_H

#include "autoload_2/vector.h"
#include "types.h"

/* The modes. */
#define SCENE_MOVER_STAND 0
#define SCENE_MOVER_WALK 1
#define SCENE_MOVER_WALK_2 2
#define SCENE_MOVER_TURN 3
#define SCENE_MOVER_TURN_FIRST 4
#define SCENE_MOVER_MODES 5

/* The ways of turning (`turn_way`): by the shorter side, or always up or always down until
 * within a step. */
#define SCENE_MOVER_TURN_SHORTER 0
#define SCENE_MOVER_TURN_UP 1
#define SCENE_MOVER_TURN_DOWN 2

#define SCENE_MOVER_PACES 3

typedef struct ScenePace {
    fx32 speed;
    fx32 speed_up;  /* the step to the speed when this is below the speed (SceneMover_Drive) */
    fx32 slow_down; /* the step to it otherwise */
} ScenePace;

typedef struct SceneMover {
    ScenePace pace;                     /* 0x00: the mode's */
    ScenePace paces[SCENE_MOVER_PACES]; /* 0x0c */
    s32 mode;                           /* 0x30 */
    s16 angle;                          /* 0x34: where the object is to walk */
    s16 turn_rate;                      /* 0x36 */
    Vec3 start;                         /* 0x38 */
    Vec3 end;                           /* 0x44 */
    fx32 reach;                         /* 0x50: a point is reached nearer than this */
    u8 continues;                       /* 0x54: the mode's animation goes on from another's */
    u8 turn_way;                        /* 0x55 */
    u8 unk_56[2];
} SceneMover;

void SceneMover_SetTurnWay(SceneMover *self, u8 way);
ScenePace *SceneMover_Pace(SceneMover *self);
void SceneMover_SetPace(SceneMover *self, int index, fx32 speed, fx32 speed_up, fx32 slow_down);
void SceneMover_EndAtStart(SceneMover *self);
int SceneMover_PointsDiffer(SceneMover *self);
Vec3 *SceneMover_End(SceneMover *self);
void SceneMover_SetEnd(SceneMover *self, const Vec3 *point);
s16 SceneMover_TurnRate(SceneMover *self);
s16 SceneMover_Angle(SceneMover *self);
void SceneMover_SetAngle(SceneMover *self, int angle);
int SceneMover_Reached(SceneMover *self, u8 *object, int at_start);
Vec3 *SceneMover_EndPoint(SceneMover *self);
void SceneMover_SetStart(SceneMover *self, const Vec3 *point);
void SceneMover_Steer(SceneMover *self, u8 *object);
int SceneMover_Turn(SceneMover *self, s16 *angle, s16 target, s16 step, u8 way);
void SceneMover_AimAtEnd(SceneMover *self, u8 *object);
int SceneMover_Mode(SceneMover *self);
void SceneMover_SetMode(SceneMover *self, u8 *object, int mode, int turn_rate, u16 word);
void SceneMover_Drive(SceneMover *self, u8 *object);

#endif
