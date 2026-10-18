/* The field's bodies (field_body.h). */
#include "field_body.h"

#include "clean.h"

static_assert(offsetof(FieldBody, push) == 0x10 && offsetof(FieldBody, touch_flags) == 0x28, "FieldBody");
static_assert(offsetof(FieldBody, next) == 0x38 && sizeof(FieldBody) == 0x40, "FieldBody");
static_assert(sizeof(FieldOwnedBody) == 0x44 && sizeof(FieldOwnedPointBody) == 0x50, "FieldOwnedBody");
static_assert(sizeof(FieldPointBody) == 0x4c, "FieldPointBody");

#define FX32_ONE 0x1000
#define NO_TOUCH_INDEX 0xff

extern FieldBody *data_021d3120; /* the bodies entered this frame */

extern const u32 data_020e2008[]; /* FieldOwnedBody's vtable */
extern const u32 data_020e2030[]; /* FieldPointBody's vtable */
extern const u32 data_020e2044[]; /* FieldOwnedPointBody's vtable */

/* FieldOwnedBody_Identity, called by its symbol (FieldOwnedPointBody_Identity). */
extern int func_02089c48(FieldOwnedBody *body);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The vtable's slots. */
typedef const Vec3 *(*FieldBodyPositionMethod)(FieldBody *body);
typedef int (*FieldBodyIdentityMethod)(FieldBody *body);
typedef void (*FieldBodyTouchMethod)(FieldBody *body, u8 kind, u8 index, u32 flags);

static const Vec3 *position_of(FieldBody *body)
{
    return ((FieldBodyPositionMethod) (uintptr_t) body->vtable[0])(body);
}

static int identity_of(FieldBody *body)
{
    return ((FieldBodyIdentityMethod) (uintptr_t) body->vtable[1])(body);
}

static void touch(FieldBody *body, u8 kind, u8 index, u32 flags)
{
    ((FieldBodyTouchMethod) (uintptr_t) body->vtable[2])(body, kind, index, flags);
}

/* `body` notes that it touched `other`. */
static void note_touch(FieldBody *body, FieldBody *other)
{
    body->touch_flags = other->flags;
    body->touch_id = identity_of(other);
    body->touch_kind = other->kind;
    body->touch_index = other->index;
}

/* func_02089b20: the destructor. */
FieldPointBody *FieldPointBody_Destruct(FieldPointBody *body)
{
    body->body.vtable = data_020e2030;
    FieldBody_Destruct(&body->body);
    return body;
}
CLEAN_AS(func_02089b20, FieldPointBody_Destruct)

/* func_02089b38: the same as func_02089b20. */
FieldPointBody *FieldPointBody_Destruct2(FieldPointBody *body)
{
    body->body.vtable = data_020e2030;
    FieldBody_Destruct(&body->body);
    return body;
}
CLEAN_AS(func_02089b38, FieldPointBody_Destruct2)

/* func_02089b50: the constructor. */
FieldPointBody *FieldPointBody_Construct(FieldPointBody *body)
{
    FieldBody_Construct(&body->body);
    body->body.vtable = data_020e2030;
    return body;
}
CLEAN_AS(func_02089b50, FieldPointBody_Construct)

/* func_02089b68: the same as func_02089b50. */
FieldPointBody *FieldPointBody_Construct2(FieldPointBody *body)
{
    FieldBody_Construct(&body->body);
    body->body.vtable = data_020e2030;
    return body;
}
CLEAN_AS(func_02089b68, FieldPointBody_Construct2)

/* func_02089b80: the body set for `owner` at `point` (FieldOwnedBody_Set). */
void FieldOwnedPointBody_Set(FieldOwnedPointBody *body, Actor *owner, const Vec3 *point, fx32 radius, fx32 height, int flags,
                             int touches, int kind, u8 index, fx32 weight)
{
    FieldOwnedBody_Set(&body->base, owner, radius, height, flags, touches, kind, index, weight);
    body->point.x = point->x;
    body->point.y = point->y;
    body->point.z = point->z;
}
CLEAN_AS(func_02089b80, FieldOwnedPointBody_Set)

/* func_02089bbc: the destructor. */
FieldOwnedPointBody *FieldOwnedPointBody_Destruct(FieldOwnedPointBody *body)
{
    body->base.body.vtable = data_020e2044;
    FieldOwnedBody_Destruct(&body->base);
    return body;
}
CLEAN_AS(func_02089bbc, FieldOwnedPointBody_Destruct)

/* func_02089bd4: the constructor. */
FieldOwnedPointBody *FieldOwnedPointBody_Construct(FieldOwnedPointBody *body)
{
    FieldOwnedBody_Construct(&body->base);
    body->base.body.vtable = data_020e2044;
    return body;
}
CLEAN_AS(func_02089bd4, FieldOwnedPointBody_Construct)

/* func_02089bec: the body set at `point` (FieldBody_Set). */
void FieldPointBody_Set(FieldPointBody *body, const Vec3 *point, fx32 radius, fx32 height, int flags, int touches, int kind,
                        u8 index, fx32 weight)
{
    body->point.x = point->x;
    body->point.y = point->y;
    body->point.z = point->z;
    FieldBody_Set(&body->body, radius, height, flags, touches, kind, index, weight);
}
CLEAN_AS(func_02089bec, FieldPointBody_Set)

/* func_02089c20: the body set for `owner` (FieldBody_Set). */
void FieldOwnedBody_Set(FieldOwnedBody *body, Actor *owner, fx32 radius, fx32 height, int flags, int touches, int kind,
                        u8 index, fx32 weight)
{
    body->owner = owner;
    FieldBody_Set(&body->body, radius, height, flags, touches, kind, index, weight);
}
CLEAN_AS(func_02089c20, FieldOwnedBody_Set)

/* func_02089c48: vtable slot 1, the identity: the owner's serial number. */
int FieldOwnedBody_Identity(FieldOwnedBody *body)
{
    return body->owner->serial;
}
CLEAN_AS(func_02089c48, FieldOwnedBody_Identity)

/* func_02089c50: vtable slot 0, the position: the owner's. */
const Vec3 *FieldOwnedBody_Position(FieldOwnedBody *body)
{
    return &body->owner->position;
}
CLEAN_AS(func_02089c50, FieldOwnedBody_Position)

/* func_02089c58: the destructor. */
FieldOwnedBody *FieldOwnedBody_Destruct(FieldOwnedBody *body)
{
    body->body.vtable = data_020e2008;
    FieldBody_Destruct(&body->body);
    return body;
}
CLEAN_AS(func_02089c58, FieldOwnedBody_Destruct)

/* func_02089c70: the same as func_02089c58. */
FieldOwnedBody *FieldOwnedBody_Destruct2(FieldOwnedBody *body)
{
    body->body.vtable = data_020e2008;
    FieldBody_Destruct(&body->body);
    return body;
}
CLEAN_AS(func_02089c70, FieldOwnedBody_Destruct2)

/* func_02089c88: the constructor, with no owner. */
FieldOwnedBody *FieldOwnedBody_Construct2(FieldOwnedBody *body)
{
    FieldBody_Construct(&body->body);
    body->body.vtable = data_020e2008;
    body->owner = NULL;
    return body;
}
CLEAN_AS(func_02089c88, FieldOwnedBody_Construct2)

/* func_02089ca4: the same as func_02089c88. */
FieldOwnedBody *FieldOwnedBody_Construct(FieldOwnedBody *body)
{
    FieldBody_Construct(&body->body);
    body->body.vtable = data_020e2008;
    body->owner = NULL;
    return body;
}
CLEAN_AS(func_02089ca4, FieldOwnedBody_Construct)

/* func_02089cc0: whether the body touched one with any of `flags`. */
int FieldBody_TouchedWith(FieldBody *body, u32 flags)
{
    return body->touched != 0 && (body->touch_flags & flags) != 0;
}
CLEAN_AS(func_02089cc0, FieldBody_TouchedWith)

/* func_02089ce0: every pair of the bodies entered this frame that can touch (FieldBody_CanTouch)
 * and overlap, both upright and in the ground plane, is told of it: each is marked touched and
 * notes the other (a passive body only when this overlap is at least its deepest so far), and
 * each one's slot 2 is called with the other's kind, index and flags. Unless either is passive
 * or both are fixed, they are then pushed apart along the line between their centres by the
 * overlap: all of it onto the one that is not fixed, else shared, each moving by the other's
 * weight's part of half of it. The list is walked by its head, which ends empty.
 *
 * QUIRK: two bodies at the same place in the ground plane are pushed apart along X.
 * BUG: the second body of a pair, when passive, compares the overlap with its deepest but never
 *      records it, so a later shallower touch can replace a deeper one.
 *      BUGFIX: record it as for the first.
 * REQUIRES: the bodies' methods leave the list's head alone (the original reads it again after
 *           each call). */
void FieldBody_PushApart(void)
{
    for (FieldBody *body = data_021d3120; body != NULL; body = body->next) {
        if (body->flags & FIELD_BODY_PASSIVE) {
            body->deepest = -FX32_ONE;
        }
    }

    while (data_021d3120 != NULL) {
        FieldBody *a = data_021d3120;
        const Vec3 *a_position = position_of(a);

        for (FieldBody *b = a->next; b != NULL; b = b->next) {
            if (!FieldBody_CanTouch(a, b)) {
                continue;
            }
            Vec3 d;
            Vec_Subtract(&d, position_of(b), a_position);
            int upright = d.y < 0 ? b->height + d.y : a->height - d.y;
            if (upright <= 0) {
                continue;
            }
            fx32 distance = Vec_LengthXZ(&d);
            if (distance == 0) {
                d.x = FX32_ONE;
                distance = FX32_ONE;
            }
            fx32 overlap = a->radius + b->radius - distance;
            if (overlap <= 0) {
                continue;
            }

            b->touched = 1;
            a->touched = 1;
            if (!(a->flags & FIELD_BODY_PASSIVE)) {
                note_touch(a, b);
            } else if (overlap >= a->deepest) {
                a->deepest = overlap;
                note_touch(a, b);
            }
            if (!(b->flags & FIELD_BODY_PASSIVE)) {
                note_touch(b, a);
            } else if (overlap >= b->deepest) {
#ifdef BUGFIX
                b->deepest = overlap;
#endif
                note_touch(b, a);
            }
            touch(a, b->kind, b->index, b->flags);
            touch(b, a->kind, a->index, a->flags);

            if ((a->flags & FIELD_BODY_PASSIVE) || (b->flags & FIELD_BODY_PASSIVE)) {
                continue;
            }
            if ((a->flags & FIELD_BODY_FIXED) && (b->flags & FIELD_BODY_FIXED)) {
                continue;
            }
            if (a->flags & FIELD_BODY_FIXED) {
                b->push.y = 0;
                fx32 share = FX_Div(overlap, distance);
                b->push.x += FX_MulFunc(d.x, share);
                b->push.z += FX_MulFunc(d.z, share);
            } else if (b->flags & FIELD_BODY_FIXED) {
                a->push.y = 0;
                fx32 share = FX_Div(overlap, distance);
                a->push.x -= FX_MulFunc(d.x, share);
                a->push.z -= FX_MulFunc(d.z, share);
            } else {
                fx32 a_weight = a->weight;
                fx32 b_weight = b->weight;
                fx32 half = FX_Div(overlap, distance) >> 1;
                fx32 total = a_weight + b_weight;
                fx32 a_share = FX_MulFunc(half, FX_Div(b_weight, total));
                fx32 b_share = FX_MulFunc(half, FX_Div(a_weight, total));
                b->push.y = 0;
                a->push.y = 0;
                a->push.x -= FX_MulFunc(d.x, a_share);
                a->push.z -= FX_MulFunc(d.z, a_share);
                b->push.x += FX_MulFunc(d.x, b_share);
                b->push.z += FX_MulFunc(d.z, b_share);
            }
        }
        data_021d3120 = a->next;
    }
}
CLEAN_AS(func_02089ce0, FieldBody_PushApart)

/* func_02089f70: whether `a` and `b` can touch: each has a flag the other touches, they are
 * not the same body and not of the same nonzero identity. */
int FieldBody_CanTouch(FieldBody *a, FieldBody *b)
{
    if ((a->flags & b->touches) == 0 || (a->touches & b->flags) == 0) {
        return 0;
    }
    int identity = identity_of(a);
    if (identity != 0 && identity == identity_of(b)) {
        return 0;
    }
    return a != b;
}
CLEAN_AS(func_02089f70, FieldBody_CanTouch)

/* func_02089fc8: the body cleared and put at the head of this frame's list. */
void FieldBody_Enter(FieldBody *body)
{
    FieldBody_Clear(body);
    body->next = data_021d3120;
    data_021d3120 = body;
}
CLEAN_AS(func_02089fc8, FieldBody_Enter)

/* func_02089fe4: the frame's results cleared: no list, no push, nothing touched. */
void FieldBody_Clear(FieldBody *body)
{
    body->next = NULL;
    body->push.x = 0;
    body->push.y = 0;
    body->push.z = 0;
    body->touched = 0;
    body->touch_id = 0;
    body->touch_flags = 0;
    body->touch_kind = 0;
    body->touch_index = NO_TOUCH_INDEX;
}
CLEAN_AS(func_02089fe4, FieldBody_Clear)

/* func_0208a000 */
void FieldBody_Set(FieldBody *body, fx32 radius, fx32 height, int flags, int touches, int kind, u8 index, fx32 weight)
{
    body->radius = radius;
    body->height = height;
    body->flags = (u32) flags;
    body->touches = (u32) touches;
    body->kind = (u8) kind;
    body->index = index;
    body->weight = weight;
}
CLEAN_AS(func_0208a000, FieldBody_Set)

/* func_0208a020: the actor the body touched (by its serial number), 0 for none. */
int FieldBody_TouchedActor(FieldBody *body)
{
    if (body->touch_id == 0) {
        return 0;
    }
    return Actor_FindBySerial(body->touch_id);
}
CLEAN_AS(func_0208a020, FieldBody_TouchedActor)

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/fx_math.h"  /* Math_Atan2 */

extern const u32 data_020e201c[]; /* FieldBody's vtable */

/* func_0208a038: whether the body touched something this frame that lies ahead of `yaw`: the
 * push it was given points within 45 degrees (0x2000) of straight behind. */
int FieldBody_TouchedAhead(FieldBody *body, int yaw)
{
    if (body->touched == 0) {
        return 0;
    }
    s16 push_angle = Math_Atan2(body->push.x, body->push.z);
    return Math_AbsDiff16(push_angle, (s16) (yaw + 0x8000)) <= 0x2000;
}
CLEAN_AS(func_0208a038, FieldBody_TouchedAhead)

/* func_0208a078: vtable slot 2 of the classes here: a touch does nothing. */
void FieldBody_IgnoreTouch(void) {}
CLEAN_AS(func_0208a078, FieldBody_IgnoreTouch)

/* func_0208a07c: the base class's destructor. */
void FieldBody_Destruct(FieldBody *body)
{
    body->vtable = data_020e201c;
}
CLEAN_AS(func_0208a07c, FieldBody_Destruct)

/* func_0208a088: the base class's constructor: nothing entered, nothing touched. */
FieldBody *FieldBody_Construct(FieldBody *body)
{
    body->vtable = data_020e201c;
    FieldBody_Clear(body);
    return body;
}
CLEAN_AS(func_0208a088, FieldBody_Construct)

/* func_0208a0a0: the list of the bodies entered this frame emptied. */
void FieldBody_EmptyList(void)
{
    data_021d3120 = NULL;
}
CLEAN_AS(func_0208a0a0, FieldBody_EmptyList)

/* func_0208a0ac: the same, as the scene processes call it. */
void FieldBody_Reset(void)
{
    FieldBody_EmptyList();
}
CLEAN_AS(func_0208a0ac, FieldBody_Reset)

/* func_0208a0b4: vtable slot 0, the position: the body's own point. */
const Vec3 *FieldOwnedPointBody_Position(FieldOwnedPointBody *body)
{
    return &body->point;
}
CLEAN_AS(func_0208a0b4, FieldOwnedPointBody_Position)

/* func_0208a0b8: vtable slot 1, the identity: the owner's serial number (FieldOwnedBody_Identity).
 * QUIRK: declared without a result; in the ROM the serial number is still in r0 when it
 * returns, which is what the caller of the slot reads. The call names the game's symbol, not
 * FieldOwnedBody_Identity: a compiler that sees that function only reads memory drops a call
 * whose result is unused, and the value with it. */
void FieldOwnedPointBody_Identity(FieldOwnedPointBody *body)
{
    (void) func_02089c48(&body->base);
}
CLEAN_AS(func_0208a0b8, FieldOwnedPointBody_Identity)

/* func_0208a0c0: vtable slot 0, the position: the body's own point. */
const Vec3 *FieldPointBody_Position(FieldPointBody *body)
{
    return &body->point;
}
CLEAN_AS(func_0208a0c0, FieldPointBody_Position)

/* func_0208a0c4: vtable slot 1, the identity: none, so it touches every body. */
int FieldPointBody_Identity(void)
{
    return 0;
}
CLEAN_AS(func_0208a0c4, FieldPointBody_Identity)
