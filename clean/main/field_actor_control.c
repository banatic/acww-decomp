/* How the field actor of this console is steered (field_actor.h): FieldActor_ReadControl turns
 * the buttons, the d-pad and the touch screen into a push (how far, 0 to 1.0, and towards which
 * angle), a run flag, an act and an aim point each frame, and the functions after it read
 * them back.
 *
 * The push angle is relative to the camera for the buttons (aim_mode 1) and already in the
 * world for the pen (aim_mode 2). */
#include "field_actor.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/fx_math.h"
#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "field_actor_parts.h"
#include "main/session.h"
#include "acre_tile.h"
#include "actor_table.h"
#include "angle_sector.h"
#include "camera_control.h"
#include "camera_view.h"
#include "empty_0203de64.h"
#include "event_queue.h"
#include "field_label.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "touch_pick_shapes.h"

/* The buttons (autoload_2/input.h). */
#define BUTTON_A 0x0001
#define BUTTON_B 0x0002
#define BUTTON_RIGHT 0x0010
#define BUTTON_LEFT 0x0020
#define BUTTON_UP 0x0040
#define BUTTON_DOWN 0x0080
#define BUTTON_R 0x0100
#define BUTTON_L 0x0200
#define BUTTON_DPAD (BUTTON_RIGHT | BUTTON_LEFT | BUTTON_UP | BUTTON_DOWN)
/* Every button but Select and Start; with them. */
#define BUTTONS_STEER 0x2ff3
#define BUTTONS_ALL 0x2fff

/* The push of the d-pad: a walk, or a run with B, R or L held. */
#define PUSH_WALK 0xc32
#define PUSH_FULL FX32_ONE

/* 2 while the player may steer. */
extern u8 data_021c75b8;
/* Both set: the pen came down on the touch screen in this frame (as the touch code keeps
 * them). */
extern u8 data_021f6c34;
extern u8 data_021f6c38;
/* Nonzero: the touch screen is not read for the field. */
extern int data_021c8c9c;
/* The map of the field's tiles. */
extern void *data_021c80bc;
extern NetSession *data_020ccf94;
/* The camera. */
extern int data_021c67a4;
extern PadState data_021fbe40;
/* Where the pen is on the touch screen, in pixels (0xff when up). */
extern u16 data_021fbde0;
extern u16 data_021fbde4;
extern const s16 FX_SinCosTable_[];
/* Distances ahead of the actor for the aim point: with the pen on the actor, after B, and
 * otherwise. */
extern const fx32 data_020d72f4[];
extern const fx32 data_020d7308[];
extern const fx32 data_020d7310[];

extern int FX_MulFunc(int a, int b);
extern int FX_Div(int numerator, int denominator);
extern int FX_Sqrt(int value);

static_assert(offsetof(FieldActor, unk_140) == 0x140, "0x140");
static_assert(offsetof(FieldActor, unk_14C) == 0x14c, "0x14c");
static_assert(offsetof(FieldActor, aim_point) == 0x158, "aim point");
static_assert(offsetof(FieldActor, aim_mode) == 0x170, "aim mode");
static_assert(offsetof(FieldActor, start_position) == 0x6f4, "start position");

static const Vec3 *position_of(const FieldActor *actor)
{
    return &actor->position;
}

static const u16 *yaw_of(const FieldActor *actor)
{
    return (const u16 *) &actor->yaw;
}

/* The angle's sine and cosine (FX_SinCosTable_). */
static int sine(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2];
}

static int cosine(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2 + 1];
}

static BOOL pen_came_down(void)
{
    return data_021f6c38 != 0 && data_021f6c34 != 0;
}

/* The push from the pen's distance `length` (on the ground or on the screen): none up to 0x19a
 * (after scaling by 0x4f4), full from 1.0, and between, the cube of the square root of
 * (length + 0x39a) / 0x139a, all in 20.12 fixed point. QUIRK: the square root is taken of the
 * quotient's whole part only. */
static fx32 push_of_length(fx32 length)
{
    fx32 push = FX_MulFunc(length, 0x4f4);
    if (push >= FX32_ONE) {
        return FX32_ONE;
    }
    if (push <= 0x19a) {
        return 0;
    }
    fx32 root = FX_Sqrt(FX_Div((push + 0x39a) << 12, 0x139a) >> 12);
    push = root;
    for (int i = 0; i < 3; i++) {
        push = FX_MulFunc(push, root << 12) >> 12;
    }
    if (push > FX32_ONE) {
        return FX32_ONE;
    }
    if (push < 0) {
        return 0;
    }
    return push;
}

/* func_0200dc98: reads the control for the actor of this console. With the field not
 * steerable (the byte 0x021c75b8 not 2) only the act at 0x140, the word at 0x144 and the byte
 * at 0x16d are reset. Under flag 0xb or 0x1b the control is reset to nothing (the aim point
 * 1.0 ahead at data_020d7310) and, under flag 0x1b, when func_020b5d5c says 1 and FieldActor_AnyPlayerUnreported
 * says 0, the flag is cleared (func_020b8db4; func_020eae40 when this console has slot 0 in
 * network modes 3 and 4; func_0203e110 in states 2, 0x83, 0x28 and 8).
 *
 * Otherwise the pen is read first (unless data_021c8c9c is set): what it picked, when the pen
 * came down this frame, gives by its kind: 1 an act on the actor itself; 2, 3, 6, 7, 9 and 0xb
 * to 0x11 an act (func_020b7524's value at 0x13c) at the pen's ground point; 4 and 5 the word
 * at 0x144 (2 or 1) with the picked point (5 may take the ground point: on items 0xfc and 0xfd
 * of the map with the pen's tile not the actor's) kept at 0x14c; 8 and 0xa the aim at the
 * picked point (func_0204f7e0), and the extra byte at 0x16d whether or not the pen came down.
 *
 * An act on the actor, or func_0203de78 without a ground point, stops it: no push, A held, act
 * at 0x140, the aim 1.0 ahead at data_020d72f4, aim mode 2. Else in aim mode 2 the pen's ground
 * point keeps it (else mode 1); in mode 1 a button switches to it, and a ground point back to
 * mode 2. In mode 2 the push comes from how far the pen is from the actor (push_of_length; on
 * the ground, or for states 0x1d to 0x23 from a point behind the actor by the camera's pitch
 * and yaw; else on the screen) with the angle towards the ground point; a push above 0xc32 is
 * a run; and the aim is the ground point when the pen came down without picking. In mode 1
 * the d-pad pushes (0xc32, or 1.0 to run with B, R or L) along its own angle, A held is kept at
 * 0x141, a press of A is the act, and a press of B (when A is not held) aims at the point at
 * data_020d7308 ahead. Mode 1 is taken while a button but Select and Start (with
 * func_0203e31c or flag 0x13, any button) is held. */
void FieldActor_ReadControl(FieldActor *actor)
{
    BOOL on_actor = 0;
    BOOL run = 0;
    int mode = actor->aim_mode;
    BOOL act = 0;
    int act_value = 0;
    BOOL on_ground = 0;
    u8 hold = FIELD_ACTOR_HOLD(actor);
    BOOL aimed = 0;
    BOOL picked = 0;
    Vec3 aim;
    Vec3 ground;
    Vec3 pick;
    int pick_kind;
    u8 pick_extra;

    FieldActor_PointAhead(&aim, actor, position_of(actor), yaw_of(actor), data_020d7310);
    actor->unk_140 = 0;
    actor->unk_144 = 0;
    FIELD_ACTOR_PICK_EXTRA(actor) = 0xff;
    if (data_021c75b8 != 2) {
        return;
    }

    if (FieldActor_TestFlag(actor, 0xb) || FieldActor_TestFlag(actor, 0x1b)) {
        FIELD_ACTOR_PUSH(actor) = 0;
        FIELD_ACTOR_RUN(actor) = 0;
        FIELD_ACTOR_ACT(actor) = 0;
        FIELD_ACTOR_ACT_VALUE(actor) = 0;
        FIELD_ACTOR_HOLD(actor) = 0;
        actor->unk_148 = 0;
        actor->aim_point = aim;
        if (!FieldActor_TestFlag(actor, 0x1b) || SceneTables_NoPlayerInClosedScene() != 1 ||
            FieldActor_AnyPlayerUnreported(actor) != 0) {
            return;
        }
        FieldActor_ClearFlag(actor, 0x1b);
        FieldLabel_ClearMessage();
        /* Network modes 3 and 4 (Net_GetMode's result less 3, as a byte, at most 1). */
        if (data_020ccf94->local_slot == 0 && (u8) (Net_GetMode() - 3) <= 1) {
            Wfc_ClearHostTime();
        }
        int state = actor->state;
        if (state == 2 || state == 0x83 || state == 0x28 || state == 8) {
            EventQueue_FinishKind4Or12();
        }
        return;
    }

    if (data_021c8c9c == 0) {
        on_ground = TouchPick_GetGround((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &ground) != 0;
        if (TouchPick_GetPick((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &pick, (u32 *) &pick_kind, &pick_extra)) {
            picked = 1;
            switch (pick_kind) {
                case 1:
                    if (pen_came_down()) {
                        on_actor = 1;
                        aim = ground;
                    }
                    break;
                case 2:
                case 3:
                case 6:
                case 7:
                case 9:
                case 0xb:
                case 0xc:
                case 0xd:
                case 0xe:
                case 0xf:
                case 0x10:
                case 0x11:
                    if (pen_came_down()) {
                        act = 1;
                        act_value = TouchPick_PickedObject((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), NULL, NULL);
                        aim = ground;
                    }
                    break;
                case 5:
                    if (pen_came_down()) {
                        actor->unk_144 = 1;
                        Vec3 target = pick;
                        if (FieldActor_HeldTool(actor) == 1) {
                            u16 *tile_item = AcreTile_ItemAt(data_021c80bc, &pick, 0);
                            if (*tile_item >= 0xfc && *tile_item <= 0xfd) {
                                int actor_x = 0, actor_z = 0, ground_x = 0, ground_z = 0;
                                Position_Tile(&actor_x, &actor_z, (const Position *) position_of(actor));
                                Position_Tile(&ground_x, &ground_z, (const Position *) &ground);
                                if (actor_x != ground_x || actor_z != ground_z) {
                                    target = ground;
                                }
                            }
                        }
                        actor->unk_14C = target;
                        aim = actor->unk_14C;
                    }
                    break;
                case 4:
                    if (pen_came_down()) {
                        actor->unk_144 = 2;
                        actor->unk_14C = pick;
                        aim = actor->unk_14C;
                    }
                    break;
                case 8:
                case 0xa:
                    if (pen_came_down()) {
                        aimed = 1;
                        AcreTile_SnapToTileCentre(&pick, &pick);
                        aim = pick;
                    }
                    FIELD_ACTOR_PICK_EXTRA(actor) = pick_extra;
                    break;
            }
        }
    }

    if (on_actor || (Empty0203de64_No78() && !on_ground)) {
        Vec3 ahead;
        FIELD_ACTOR_PUSH(actor) = 0;
        FIELD_ACTOR_RUN(actor) = 0;
        hold = 1;
        actor->unk_140 = 1;
        FieldActor_PointAhead(&ahead, actor, position_of(actor), yaw_of(actor), data_020d72f4);
        aim = ahead;
        mode = 2;
    } else {
        actor->unk_140 = 0;
        if (actor->aim_mode == 2) {
            mode = on_ground ? 2 : 1;
        } else if (data_021fbe40.held & BUTTONS_STEER) {
            mode = 1;
        } else if (on_ground) {
            mode = 2;
        }

        if (mode == 2) {
            Vec3 toward;
            fx32 length;
            if (actor->state >= 0x1d && actor->state <= 0x23) {
                /* From the point the camera's pitch puts 0x1266 x tan(0x4000 - pitch) behind the
                 * start position, along the camera's yaw. */
                int camera = data_021c67a4;
                Vec3 from = actor->start_position;
                u16 slope = (u16) (0x4000 - CameraControl_Pitch((CameraControl *) (uintptr_t) camera));
                fx32 back = FX_Div(FX_MulFunc(0x1266, sine(slope)), cosine(slope));
                u16 yaw = (u16) CameraControl_Yaw((CameraControl *) (uintptr_t) camera);
                Vec3 behind;
                behind.x = from.x - FX_MulFunc(back, sine(yaw));
                behind.z = from.z - FX_MulFunc(back, cosine(yaw));
                toward.x = ground.x - behind.x;
                toward.y = 0; /* not read */
                toward.z = ground.z - behind.z;
                length = Vec_LengthXZ(&toward);
            } else {
                /* On the screen: the pen against the start position's place, 0x80 x 0x60 being
                 * the screen's middle. */
                int screen_x, screen_y;
                Vec3 offset;
                toward.x = ground.x - actor->start_position.x;
                toward.y = 0; /* not read */
                toward.z = ground.z - actor->start_position.z;
                CameraControl_ScreenPosition(&screen_x, &screen_y, &actor->start_position);
                screen_x += 0x80;
                screen_y += 0x60;
                offset.x = ((u8) data_021fbde0 - screen_x) * 0x100;
                offset.y = 0;
                offset.z = ((u8) data_021fbde4 - screen_y) * 0x100;
                length = Vec_LengthXZ(&offset);
            }
            fx32 push = push_of_length(length);
            FIELD_ACTOR_PUSH(actor) = push;
            if (push > PUSH_WALK) {
                run = 1;
            }
            if (push > 0) {
                FIELD_ACTOR_PUSH_ANGLE(actor) = Math_Atan2(toward.x, toward.z);
            }
            if (!picked && pen_came_down()) {
                aimed = 1;
                aim = ground;
            }
        } else {
            u16 steer = (EventQueue_TestFlag8() || FieldActor_TestFlag(actor, 0x13)) ? BUTTONS_ALL : BUTTONS_STEER;
            u16 held = data_021fbe40.held;
            mode = (held & steer) ? 1 : actor->aim_mode;
            run = (held & (BUTTON_B | BUTTON_R | BUTTON_L)) != 0;
            act = (data_021fbe40.pressed & BUTTON_A) != 0;
            actor->unk_140 = (u8) act;
            if (data_021fbe40.held & BUTTON_A) {
                hold = 1;
            } else {
                hold = 0;
                if (data_021fbe40.pressed & BUTTON_B) {
                    Vec3 ahead;
                    aimed = 1;
                    FieldActor_PointAhead(&ahead, actor, position_of(actor), yaw_of(actor), data_020d7308);
                    aim = ahead;
                }
            }
            if (data_021fbe40.held & BUTTON_DPAD) {
                FIELD_ACTOR_PUSH(actor) = run ? PUSH_FULL : PUSH_WALK;
                FIELD_ACTOR_PUSH_ANGLE(actor) = data_021fbe40.dpad_angle;
            } else {
                FIELD_ACTOR_PUSH(actor) = 0;
            }
        }
        FIELD_ACTOR_RUN(actor) = (u8) run;
    }
    FIELD_ACTOR_ACT(actor) = (u8) act;
    FIELD_ACTOR_ACT_VALUE(actor) = act_value;
    FIELD_ACTOR_HOLD(actor) = hold;
    actor->unk_148 = (u8) aimed;
    actor->aim_point = aim;
    actor->aim_mode = mode;
}
CLEAN_AS(func_0200dc98, FieldActor_ReadControl)

/* func_0200dc8c: the push (0 to 1.0). */
u32 FieldActor_Push(FieldActor *actor)
{
    return (u32) FIELD_ACTOR_PUSH(actor);
}
CLEAN_AS(func_0200dc8c, FieldActor_Push)

/* func_0200dc80: the push's angle as the control gives it. */
s16 FieldActor_PushAngle(FieldActor *actor)
{
    return FIELD_ACTOR_PUSH_ANGLE(actor);
}
CLEAN_AS(func_0200dc80, FieldActor_PushAngle)

/* func_0200dc48: the push's angle in the world: the camera's yaw (func_0203c568) is added
 * unless the pen steers (aim mode 2) or there is no camera. */
s16 FieldActor_PushYaw(FieldActor *actor)
{
    s16 yaw = FieldActor_PushAngle(actor);
    if (actor->aim_mode != 2 && data_021c67a4 != 0) {
        yaw = (s16) (yaw + CameraControl_Yaw((CameraControl *) (uintptr_t) data_021c67a4));
    }
    return yaw;
}
CLEAN_AS(func_0200dc48, FieldActor_PushYaw)

/* func_0200dc10: where the push points from the body's yaw, by func_02064558: 0 ahead, 1 to
 * the positive side, 2 behind, 3 to the negative side (quarter turns centred on each). */
int FieldActor_PushQuadrant(FieldActor *actor)
{
    s16 relative = (s16) (FieldActor_PushYaw(actor) - actor->yaw);
    return AngleSector_Four(relative);
}
CLEAN_AS(func_0200dc10, FieldActor_PushQuadrant)

/* func_0200dc2c: the side of the body the push points to, by func_02064594: 0 positive, 1
 * negative, 2 straight ahead or behind. */
int FieldActor_PushSide(FieldActor *actor)
{
    s16 relative = (s16) (FieldActor_PushYaw(actor) - actor->yaw);
    return AngleSector_Side(relative);
}
CLEAN_AS(func_0200dc2c, FieldActor_PushSide)

/* func_0200dc04: the act of this frame (the byte at 0x13b). */
u8 FieldActor_Act(FieldActor *actor)
{
    return FIELD_ACTOR_ACT(actor);
}
CLEAN_AS(func_0200dc04, FieldActor_Act)
