/* What the main program's field actor files share: the actor's layout (ov003/field_actor.h, as
 * far as it is named there), the words past it, and calls through the state tables.
 *
 * The state machine (field_actor_states.c) keeps a table per state number (0 to 146) of four
 * C++ pointers to member functions: the update run each frame, a message handler run when the
 * session reports that another console's actor went to the state, the entry function and the
 * exit function. Each table is a function-local static filled from constants the first time its
 * function runs (ov004/member_pointer.h).
 *
 * The word at 0x7fc (FieldActor.next_state in the overlay's header) is the priority a queued
 * request must exceed to be taken: func_02008264's value for the state on entering it, and
 * func_02008258's once the state's work is done. */
#ifndef CLEAN_MAIN_FIELD_ACTOR_PARTS_H
#define CLEAN_MAIN_FIELD_ACTOR_PARTS_H

#include <stdint.h>

#include "main/actor.h"
#include "ov003/field_actor.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The states, and the size of each state table. */
#define FIELD_ACTOR_STATES 147

/* The field actor is an actor (main/actor.h): position, angles, velocity, pivot and pitch. */
static inline Actor *FieldActor_Base(FieldActor *actor)
{
    return (Actor *) actor;
}

/* A field of the actor the overlay's header leaves unnamed. */
#define FIELD_ACTOR_FIELD(actor, type, offset) (*(type *) ((u8 *) (actor) + (offset)))

/* The models and parts at their offsets: the body's model (func_02054860 updates it, its
 * animation is FieldActor.anim at 0x2d0), the three models drawn with it, each with its matrix
 * at 0x64 into it, and the parts that decide whether the second and third are drawn. */
#define FIELD_ACTOR_BODY 0x234
#define FIELD_ACTOR_MODEL_A 0x38c
#define FIELD_ACTOR_PART_B 0x428
#define FIELD_ACTOR_MODEL_B 0x464
#define FIELD_ACTOR_PART_C 0x59c
#define FIELD_ACTOR_MODEL_C 0x500
#define FIELD_ACTOR_MODEL_MATRIX 0x64

/* Matrices kept by the body's update (Mtx43): the actor's model matrix (FieldActor.unk_298),
 * the joints 0xf, 0xe and 0xb, and the held item's two placements (FieldActor.unk_62C and
 * unk_68C are the translations of the second and third). */
#define FIELD_ACTOR_MATRIX_MODEL 0x298
#define FIELD_ACTOR_MATRIX_JOINT_F 0x42c
#define FIELD_ACTOR_MATRIX_JOINT_E 0x668
#define FIELD_ACTOR_MATRIX_JOINT_B 0x698
#define FIELD_ACTOR_MATRIX_HELD 0x608
#define FIELD_ACTOR_MATRIX_HELD_ALT 0x638

/* Points on the curved ground (func_0203f7d0) of joints 7, 4 and 0x10 (the last is
 * FieldActor.effect_point). */
#define FIELD_ACTOR_POINT_JOINT_7 0x6c8
#define FIELD_ACTOR_POINT_JOINT_4 0x6d4
#define FIELD_ACTOR_POINT_JOINT_10 0x6e0

/* The sound emitters: 0x83c (class 0x0213f058) plays with flag 0x19, else 0x880 (class
 * 0x020d8414). */
#define FIELD_ACTOR_EMITTER_B 0x83c
#define FIELD_ACTOR_EMITTER 0x880

/* The looks (field_actor_looks.c), named by the texture and palette names they are copied
 * under: the body's look at 0x389 (its texture "cloth" comes from the clothes), the palettes
 * "skin_pl" and "hair_pl" at 0x7a0, the face at 0x70d (the textures "e.0" and "m.0"), the part
 * at 0x70e that gives the face's two animations and the one at 0x70f whose heap holds them, the
 * clothes at 0x774 (bound to the body's material "w" through 0x778), and the head (part B). */
#define FIELD_ACTOR_BODY_LOOK 0x389
#define FIELD_ACTOR_PALETTES 0x7a0
#define FIELD_ACTOR_FACE 0x70d
#define FIELD_ACTOR_FACE_ANIM_SET 0x70e
#define FIELD_ACTOR_FACE_ANIM_HEAP 0x70f
#define FIELD_ACTOR_CLOTH 0x774
#define FIELD_ACTOR_CLOTH_BINDING 0x778

/* The animations (field_actor_anim.c): the parts that give the body's animations (0x700) and
 * those of the held item (0x701), the held item's animation (0x708), the flags the body's
 * animation was started with (0x70c, FrameCtrlFlags), and the face's two animations at 0x710
 * and 0x73c (each an object with a FrameCtrl at its start) with the number each plays (0x76c,
 * 0x770; FACE_ANIM_NONE for none) and the timer at 0x768 that lets the first one run on. */
#define FIELD_ACTOR_BODY_ANIM_SET 0x700
#define FIELD_ACTOR_HELD_ANIM_SET 0x701
#define FIELD_ACTOR_HELD_ANIM(actor) FIELD_ACTOR_FIELD(actor, int, 0x708)
#define FIELD_ACTOR_ANIM_FLAGS(actor) FIELD_ACTOR_FIELD(actor, u8, 0x70c)
#define FIELD_ACTOR_FACE_ANIM_A 0x710
#define FIELD_ACTOR_FACE_ANIM_B 0x73c
#define FIELD_ACTOR_FACE_ANIM_A_FRAME(actor) FIELD_ACTOR_FIELD(actor, fx32, 0x718)
#define FIELD_ACTOR_FACE_ANIM_B_FRAME(actor) FIELD_ACTOR_FIELD(actor, fx32, 0x744)
#define FIELD_ACTOR_FACE_ANIM_TIMER 0x768
#define FIELD_ACTOR_FACE_ANIM_A_NUMBER(actor) FIELD_ACTOR_FIELD(actor, int, 0x76c)
#define FIELD_ACTOR_FACE_ANIM_B_NUMBER(actor) FIELD_ACTOR_FIELD(actor, int, 0x770)
#define FACE_ANIM_NONE 0x16f

/* The contact bodies other objects touch (as SnowmanBody, ov003/snowman.h): the actor's at
 * 0x174 and a second one at 0x1c4; and the actor's collider at 0x7a4 (its flags at 0x7a8). */
#define FIELD_ACTOR_CONTACT 0x174
#define FIELD_ACTOR_CONTACT_B 0x1c4
#define FIELD_ACTOR_COLLIDER 0x7a4
#define FIELD_ACTOR_COLLIDER_FLAGS(actor) FIELD_ACTOR_FIELD(actor, u32, 0x7a8)

/* A change of the head or of part C is asked for (status LOOKS_READY to LOOKS_PENDING with the
 * request's values), applied (LOOKS_LOADING) and polled until its models are loaded
 * (LOOKS_READY). */
#define LOOKS_PENDING 0
#define LOOKS_LOADING 1
#define LOOKS_READY 2
#define FIELD_ACTOR_PART_C_STATUS(actor) FIELD_ACTOR_FIELD(actor, int, 0xc8c)
#define FIELD_ACTOR_PART_C_ITEM(actor) FIELD_ACTOR_FIELD(actor, u16, 0xc90)
#define FIELD_ACTOR_HEAD_STATUS(actor) FIELD_ACTOR_FIELD(actor, int, 0xc94)
#define FIELD_ACTOR_HEAD_ITEM(actor) FIELD_ACTOR_FIELD(actor, u16, 0xc98)
#define FIELD_ACTOR_HEAD_KIND(actor) FIELD_ACTOR_FIELD(actor, u8, 0xc9a)
#define FIELD_ACTOR_HEAD_HAIR_COLOR(actor) FIELD_ACTOR_FIELD(actor, u8, 0xc9b)
#define FIELD_ACTOR_HEAD_WITH_FACE(actor) FIELD_ACTOR_FIELD(actor, u8, 0xc9c)

/* 1.0 in 20.12 fixed point. */
#define FX32_ONE 0x1000

/* Unnamed words. */
#define FIELD_ACTOR_MARK(actor) FIELD_ACTOR_FIELD(actor, int, 0x6f0) /* handed with joint 1's point to func_020acbc8 */
#define FIELD_ACTOR_SOUND_POINT(actor)                                                                                        \
    FIELD_ACTOR_FIELD(actor, Vec3, 0x8c4)                               /* where the sound emitters play; 0 for none yet */
#define FIELD_ACTOR_BODY_ARG(actor) FIELD_ACTOR_FIELD(actor, u8, 0x8e9) /* handed to func_02055d38 with each model */
#define FIELD_ACTOR_UNK_8EA(actor) FIELD_ACTOR_FIELD(actor, u8, 0x8ea)
#define FIELD_ACTOR_UNK_8EB(actor) FIELD_ACTOR_FIELD(actor, s8, 0x8eb)   /* 0 on entering state 0x76; 3, 2, 1 by state 0x35 */
#define FIELD_ACTOR_COUNTDOWN(actor) FIELD_ACTOR_FIELD(actor, u8, 0x8ec) /* counted down each frame */
#define FIELD_ACTOR_REMOTE_STATE(actor) FIELD_ACTOR_FIELD(actor, int, 0x8f8) /* 147 for none */
#define FIELD_ACTOR_PENDING_X(actor) FIELD_ACTOR_FIELD(actor, int, 0x8fc)
#define FIELD_ACTOR_PENDING_Z(actor) FIELD_ACTOR_FIELD(actor, int, 0x900)
#define FIELD_ACTOR_PENDING_BITS(actor) FIELD_ACTOR_FIELD(actor, u8, 0x904)   /* PENDING_ACTION_... */
#define FIELD_ACTOR_ENTERED_STATE(actor) FIELD_ACTOR_FIELD(actor, int, 0xc88) /* with FieldActor.unk_C84 */

/* The control of this console's actor (FieldActor_ReadControl, field_actor_control.c): how far it
 * is pushed (0 to 1.0) and towards which angle, whether it runs, the act of this frame (A
 * pressed or an object picked with the pen, with func_020b7524's value), whether A is held (or
 * the pen is on the actor), and the extra byte of what the pen picked (0xff for none). */
#define FIELD_ACTOR_PUSH(actor) FIELD_ACTOR_FIELD(actor, fx32, 0x134)
#define FIELD_ACTOR_PUSH_ANGLE(actor) FIELD_ACTOR_FIELD(actor, s16, 0x138)
#define FIELD_ACTOR_RUN(actor) FIELD_ACTOR_FIELD(actor, u8, 0x13a)
#define FIELD_ACTOR_ACT(actor) FIELD_ACTOR_FIELD(actor, u8, 0x13b)
#define FIELD_ACTOR_ACT_VALUE(actor) FIELD_ACTOR_FIELD(actor, int, 0x13c)
#define FIELD_ACTOR_HOLD(actor) FIELD_ACTOR_FIELD(actor, u8, 0x141)
#define FIELD_ACTOR_PICK_EXTRA(actor) FIELD_ACTOR_FIELD(actor, u8, 0x16d)

/* The bits at 0x904: a remote action (FieldActor_TakeRemoteAction) put off to a later frame. */
#define PENDING_ACTION_TYPE 0x1f
#define PENDING_ACTION_SUB_SHIFT 5
#define PENDING_ACTION_SUB 0x60
#define PENDING_ACTION_SET 0x80

/* Calls through a member pointer with the arguments of the tables' functions. */
static inline void FieldActor_CallUpdate(const MemberPointer *member, FieldActor *actor)
{
    MemberPointer_CallVoid(member, actor);
}

static inline void FieldActor_CallWithInt(const MemberPointer *member, FieldActor *actor, int arg)
{
    void *self = MemberPointer_Object(member, actor);
    ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(member, self))(self, arg);
}

static inline void FieldActor_CallEntry(const MemberPointer *member, FieldActor *actor, const StateRequest *request,
                                        int previous)
{
    void *self = MemberPointer_Object(member, actor);
    ((void (*)(void *, const StateRequest *, int))(uintptr_t) MemberPointer_Code(member, self))(self, request, previous);
}

#endif
