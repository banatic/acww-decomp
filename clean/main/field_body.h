/* The field's bodies (data_021d3120): upright cylinders that objects enter each frame
 * (FieldBody_Enter) and that FieldBody_PushApart then sorts out, telling each body what it
 * touched and pushing overlapping ones apart in the ground plane. The pushes are left in the
 * bodies for their owners to apply; the walk empties the list.
 *
 * A body is a C++ object whose vtable gives its position (slot 0), an identity (slot 1: bodies
 * of the same nonzero identity never touch) and what to do when it touches another (slot 2).
 * Three classes are here: a body of an actor (at the actor's position, its identity the actor's
 * serial number), the same with a point of its own, and a body at a point of its own. */
#ifndef CLEAN_MAIN_FIELD_BODY_H
#define CLEAN_MAIN_FIELD_BODY_H

#include "autoload_2/vector.h"
#include "main/actor.h"
#include "types.h"

/* FieldBody.flags */
#define FIELD_BODY_PASSIVE 1 /* keeps only the deepest touch; neither pushes nor is pushed */
#define FIELD_BODY_FIXED 2   /* pushes others and is not pushed */

/* The base class (0x40 bytes, vtable data_020e201c, constructed by func_0208a088). */
typedef struct FieldBody {
    const u32 *vtable;
    fx32 radius;    /* 0x04 */
    fx32 height;    /* 0x08 */
    u8 kind;        /* 0x0c */
    u8 index;       /* 0x0d */
    u8 touch_kind;  /* 0x0e: the kind of the body touched, 0 for none */
    u8 touch_index; /* 0x0f: its index, 0xff for none */
    Vec3 push;      /* 0x10: how far to move in the ground plane (y is cleared by a push) */
    u32 flags;      /* 0x1c: FIELD_BODY_... and what it is to others */
    u32 touches;    /* 0x20: the flags of the bodies it can touch */
    u8 unk_24[4];
    u32 touch_flags;        /* 0x28: the flags of the body touched */
    int touch_id;           /* 0x2c: the identity of the body touched (an actor's serial number) */
    fx32 deepest;           /* 0x30: a passive body's deepest overlap this frame */
    fx32 weight;            /* 0x34: shares a push between two bodies */
    struct FieldBody *next; /* 0x38 */
    u8 touched;             /* 0x3c: it touched something this frame */
    u8 unk_3d[3];
} FieldBody;

/* A body of an actor (0x44 bytes, vtable data_020e2008): at the actor's position. */
typedef struct FieldOwnedBody {
    FieldBody body;
    Actor *owner; /* 0x40 */
} FieldOwnedBody;

/* A body of an actor with a point of its own (0x50 bytes, vtable data_020e2044). */
typedef struct FieldOwnedPointBody {
    FieldOwnedBody base;
    Vec3 point; /* 0x44 */
} FieldOwnedPointBody;

/* A body at a point of its own (0x4c bytes, vtable data_020e2030). */
typedef struct FieldPointBody {
    FieldBody body;
    Vec3 point; /* 0x40 */
} FieldPointBody;

FieldPointBody *FieldPointBody_Destruct(FieldPointBody *body);
FieldPointBody *FieldPointBody_Destruct2(FieldPointBody *body);
FieldPointBody *FieldPointBody_Construct(FieldPointBody *body);
FieldPointBody *FieldPointBody_Construct2(FieldPointBody *body);
void FieldOwnedPointBody_Set(FieldOwnedPointBody *body, Actor *owner, const Vec3 *point, fx32 radius, fx32 height, int flags,
                             int touches, int kind, u8 index, fx32 weight);
FieldOwnedPointBody *FieldOwnedPointBody_Destruct(FieldOwnedPointBody *body);
FieldOwnedPointBody *FieldOwnedPointBody_Construct(FieldOwnedPointBody *body);
void FieldPointBody_Set(FieldPointBody *body, const Vec3 *point, fx32 radius, fx32 height, int flags, int touches, int kind,
                        u8 index, fx32 weight);
void FieldOwnedBody_Set(FieldOwnedBody *body, Actor *owner, fx32 radius, fx32 height, int flags, int touches, int kind,
                        u8 index, fx32 weight);
int FieldOwnedBody_Identity(FieldOwnedBody *body);
const Vec3 *FieldOwnedBody_Position(FieldOwnedBody *body);
FieldOwnedBody *FieldOwnedBody_Destruct(FieldOwnedBody *body);
FieldOwnedBody *FieldOwnedBody_Destruct2(FieldOwnedBody *body);
FieldOwnedBody *FieldOwnedBody_Construct2(FieldOwnedBody *body);
FieldOwnedBody *FieldOwnedBody_Construct(FieldOwnedBody *body);
int FieldBody_TouchedWith(FieldBody *body, u32 flags);
void FieldBody_PushApart(void);
int FieldBody_CanTouch(FieldBody *a, FieldBody *b);
void FieldBody_Enter(FieldBody *body);
void FieldBody_Clear(FieldBody *body);
void FieldBody_Set(FieldBody *body, fx32 radius, fx32 height, int flags, int touches, int kind, u8 index, fx32 weight);
int FieldBody_TouchedActor(FieldBody *body);

int FieldBody_TouchedAhead(FieldBody *body, int yaw);
void FieldBody_IgnoreTouch(void);
void FieldBody_Destruct(FieldBody *body);
FieldBody *FieldBody_Construct(FieldBody *body);
void FieldBody_EmptyList(void);
void FieldBody_Reset(void);
const Vec3 *FieldOwnedPointBody_Position(FieldOwnedPointBody *body);
void FieldOwnedPointBody_Identity(FieldOwnedPointBody *body);
const Vec3 *FieldPointBody_Position(FieldPointBody *body);
int FieldPointBody_Identity(void);

#endif
