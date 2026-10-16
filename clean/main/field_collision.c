/* Collision on the field (field_collision.h): the shapes gathered around a move, pushing a
 * position out of them, the contacts recorded, and the ground at a point. */
#include "field_collision.h"

#include "autoload_2/fx_math.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "itcm/field_units.h"

static_assert(sizeof(CollisionTag) == 8, "tag");
static_assert(sizeof(CollisionSegment) == 0x20, "segment");
static_assert(offsetof(CollisionWall, kind) == 0x28, "wall kind");
static_assert(sizeof(CollisionWall) == 0x30, "wall");
static_assert(offsetof(CollisionWallList, count) == 0x480, "wall count");
static_assert(offsetof(CollisionTriangle, offset) == 0x34, "triangle offset");
static_assert(sizeof(CollisionFloor) == 0x40, "floor");
static_assert(offsetof(CollisionFloorList, count) == 0xa00, "floor count");
static_assert(offsetof(CollisionPost, tag) == 0x14, "post tag");
static_assert(sizeof(CollisionPost) == 0x24, "post");
static_assert(sizeof(CollisionPostList) == 0x244, "post list");
static_assert(sizeof(CollisionCell) == 0x18, "cell");
static_assert(offsetof(CollisionCellGrid, min_x) == 0x498, "grid bounds");
static_assert(offsetof(CollisionContactList, kind) == 0x10, "contact kinds");
static_assert(offsetof(CollisionContacts, walls) == 0x0c, "contacts list");
static_assert(sizeof(CollisionContacts) == 0x30, "contacts");
static_assert(offsetof(CollisionPushOut, facing) == 0x18, "push-out facing");
static_assert(offsetof(CollisionPushOut, flags) == 0x24, "push-out flags");
static_assert(offsetof(CollisionGround, unit_x) == 0x1c, "ground unit");
static_assert(offsetof(CollisionGround, limit) == 0x3c, "ground limit");
static_assert(offsetof(CollisionTypeInfo, height) == 0x1c, "type height");
static_assert(sizeof(CollisionTypeInfo) == 0x1e, "type row");

/* The attributes the corner slopes give the ground. */
#define COLLISION_ATTR_13 0x13
#define COLLISION_ATTR_16 0x16

/* The unit types with a corner slope (CollisionGround_Query). */
#define UNIT_TYPE_51 0x51
#define UNIT_TYPE_52 0x52
#define UNIT_TYPE_53 0x53
#define UNIT_TYPE_54 0x54
#define UNIT_TYPE_55 0x55

/* Back faces of cliffs and the posts of the extra list are this high. */
#define COLLISION_BACK_TOP 0x8000
/* A wall stops only what is below its top by more than this. */
#define COLLISION_WALL_CLEARANCE 0x700

/* The class vtables: segment, wall, floor. */
extern const u8 data_020da1a4[];
extern const u8 data_020da210[];
extern const u8 data_020da21c[];

/* The type and attribute table (0x7c rows). */
extern const CollisionTypeInfo data_020c907c[];
/* The radius of an extra post by its kind (0 to 2). */
extern const fx32 data_020c9050[];
/* (0, 0): the origin of CollisionPoint distances. */
extern CollisionPoint data_021c30b8;
/* (0, 1.0, 0): the floors' normal. */
extern Vec3 data_021c317c;
/* Up to four extra posts of kind 2 (func_02034600 answers for a unit); its first byte, the
 * mask of those in use, is tested before asking. */
extern u8 data_021c5124;
/* The current map. */
extern FieldBlockMap *data_020da1a8;

/* The eight function-local static normals of CollisionWalls_AddCliffs, each with its guard
 * word and the record __register_global_object keeps it in. */
extern CollisionPoint data_021c3128, data_021c3138, data_021c3100, data_021c3110;
extern CollisionPoint data_021c3120, data_021c3118, data_021c3130, data_021c3108;
extern u32 data_021c30e8, data_021c30d8, data_021c30d4, data_021c30cc;
extern u32 data_021c30f0, data_021c30ec, data_021c30fc, data_021c30f4;
extern u8 data_021c31c4[], data_021c31dc[], data_021c3140[], data_021c3164[];
extern u8 data_021c3188[], data_021c31ac[], data_021c31d0[], data_021c314c[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __register_global_object(void *object, void *destruct, void *record);

/* Points seen from above: set, difference a - b, normalize (whether it had a length), the unit
 * normal of the line from a to b, the squared distance, and the destructor (nothing). */
extern void func_0202f8fc(CollisionPoint *point, fx32 x, fx32 z);
extern void func_0202f898(CollisionPoint *difference, const CollisionPoint *a, const CollisionPoint *b);
extern int func_0202f7f4(CollisionPoint *v);
extern void func_0202f7a0(CollisionPoint *normal, const CollisionPoint *a, const CollisionPoint *b);
extern s64 func_0202f838(const CollisionPoint *a, const CollisionPoint *b);
extern void func_0202f2f0(void *point);
/* Segments: set the three points (and the offset), the base destructor; the three tests that
 * push `moved` out of a wall coming from `from`, and whether they did. */
extern void func_0202f6ac(CollisionSegment *segment, const CollisionPoint *start, const CollisionPoint *end,
                          const CollisionPoint *normal);
extern void func_0202f6dc(CollisionSegment *segment);
extern int func_0202f288(CollisionWall *wall, CollisionPoint *moved, const CollisionPoint *from, fx32 radius);
extern int func_0202f3e4(CollisionWall *wall, CollisionPoint *moved, const CollisionPoint *from, fx32 radius);
extern int func_0202f2f4(CollisionWall *wall, CollisionPoint *moved, const CollisionPoint *from, fx32 radius);
/* Triangles: base constructor, set the corners and normal, construct and set, whether a point
 * is inside seen from above, base destructor and destructor. */
extern void func_0202ff00(CollisionTriangle *triangle);
extern int func_0202fc18(CollisionTriangle *triangle, const Vec3 *a, const Vec3 *b, const Vec3 *c, const Vec3 *normal);
extern CollisionTriangle *func_0202feb4(CollisionTriangle *triangle, const Vec3 *a, const Vec3 *b, const Vec3 *c,
                                        const Vec3 *normal);
extern int func_0202fb8c(CollisionTriangle *triangle, const Vec3 *point);
extern void func_0202fed4(CollisionTriangle *triangle);
extern void func_0202fee0(CollisionTriangle *triangle);
/* Cylinders: set position, radius and height; construct; destruct; land on the top coming
 * from above; push a point of `radius` out of the side. */
extern void func_02030640(CollisionPost *post, const Vec3 *position, fx32 radius, fx32 height);
extern void *func_02030690(CollisionPost *post);
extern int func_02030658(CollisionPost *post);
extern int func_02030580(CollisionPost *post, Vec3 *position, const Vec3 *previous);
extern int func_020305b0(CollisionPost *post, Vec3 *position, fx32 radius);
/* What main's tables say of a unit: a post's radius and added height, and its kind. */
extern int func_02031078(int x, int z, int *radius, int *height, int *kind);
/* The quarter of its unit a point is in, and the attribute of a unit in that quarter (from
 * one table set or the other); whether an attribute is ground in a mode. */
extern int func_02031da8(const Vec3 *position);
extern int func_02031ca8(int x, int z, int quarter);
extern int func_02031d28(int x, int z, int quarter);
extern int func_02031c14(int attr, int mode);
extern int func_02034600(void *extra_posts, int x, int z);
extern void func_02034448(CollisionCell *cell, int x, int z, int alternate);

/* The members' constructors and destructors handed to __cxa_vec_ctor: the game's own. */
extern void *func_020339dc(void *wall);
extern void *func_020339b8(void *wall);
extern void *func_02033ccc(void *floor);
extern void *func_02033ca8(void *floor);
extern void *func_02033100(void *post);
extern void *func_020330e8(void *post);

/* The centre of unit `unit` on its axis. */
static fx32 collision_unit_centre(int unit)
{
    return (fx32) (((u32) unit << COLLISION_UNIT_SHIFT) + COLLISION_HALF_UNIT);
}

/* Row `index` of the type table, read where the game reads it for any index below 0x7c. */
static const CollisionTypeInfo *collision_type_info(int index)
{
    return (const CollisionTypeInfo *) (uintptr_t) ((uintptr_t) data_020c907c + (u32) index * sizeof(CollisionTypeInfo));
}

/* The lists of posts and walls are walked as the game walks them: up to the address of the
 * first entry plus count entries, computed in 32 bits after every entry. */
static u32 collision_first(const void *entries)
{
    return (u32) (uintptr_t) entries;
}

static u32 collision_end(const void *entries, u32 count, u32 size)
{
    return (u32) (uintptr_t) entries + count * size;
}

/* ---- Tags */

/* func_02034280 */
void CollisionTag_Copy(CollisionTag *tag, const CollisionTag *from)
{
    tag->attr = from->attr;
    tag->handler = from->handler;
}
CLEAN_AS(func_02034280, CollisionTag_Copy)

/* func_0203428c */
void CollisionTag_Set(CollisionTag *tag, int attr, CollisionHandler *handler)
{
    tag->attr = (u8) attr;
    tag->handler = handler;
}
CLEAN_AS(func_0203428c, CollisionTag_Set)

/* func_02034294: nothing to do. */
void CollisionTag_Destroy(CollisionTag *tag)
{
    (void) tag;
}
CLEAN_AS(func_02034294, CollisionTag_Destroy)

/* func_020342a4: no attribute, no handler. */
void CollisionTag_Clear(CollisionTag *tag)
{
    tag->attr = 0;
    tag->handler = NULL;
}
CLEAN_AS(func_020342a4, CollisionTag_Clear)

/* func_0203429c: the same as CollisionTag_Clear, for the tag at the start of a segment test's
 * own result (func_020311bc). */
void CollisionHitTag_Clear(CollisionTag *tag)
{
    tag->attr = 0;
    tag->handler = NULL;
}
CLEAN_AS(func_0203429c, CollisionHitTag_Clear)

/* func_02034298: its destructor; nothing to do. */
void CollisionHitTag_Destroy(CollisionTag *tag)
{
    (void) tag;
}
CLEAN_AS(func_02034298, CollisionHitTag_Destroy)

/* func_02032adc: a segment test's result, made before func_020311bc fills it. */
CollisionSegmentHit *CollisionSegmentHit_Construct(CollisionSegmentHit *hit)
{
    CollisionTag_Clear(&hit->tag);
    return hit;
}
CLEAN_AS(func_02032adc, CollisionSegmentHit_Construct)

/* func_02032acc */
int CollisionSegmentHit_Destroy(CollisionSegmentHit *hit)
{
    CollisionTag_Destroy(&hit->tag);
    return (int) (uintptr_t) hit;
}
CLEAN_AS(func_02032acc, CollisionSegmentHit_Destroy)

/* ---- Contacts */

/* The angle and kind of touch `i`, read where the game reads them for any count (the list
 * holds two; the classification reads as many as the count says). */
static s16 collision_contact_angle(const CollisionContactList *list, u32 i)
{
    return *(const s16 *) (uintptr_t) ((uintptr_t) list + offsetof(CollisionContactList, angle) + 2 * i);
}

static int collision_contact_kind(const CollisionContactList *list, u32 i)
{
    return *(const int *) (uintptr_t) ((uintptr_t) list + offsetof(CollisionContactList, kind) + 4 * i);
}

/* func_02032aec: sets the flags of the walls and posts touched, by their kind and where their
 * normal points from the actor `facing` that way; with two touches, also whether the actor
 * faces into the corner between them and whether their angles cancel.
 * QUIRK: the corner test turns the mean normal by 0x7fff, not half a turn, and compares it
 * with `facing` without wrapping the difference to a turn. */
void CollisionContacts_ClassifyWalls(CollisionContacts *contacts, int facing)
{
    u32 opposite = (u32) facing + 0x8000;
    u32 i;

    for (i = 0; i < contacts->walls.count; i++) {
        u16 offset = (u16) ((u32) collision_contact_angle(&contacts->walls, i) - opposite);
        int kind2 = collision_contact_kind(&contacts->walls, i) == COLLISION_KIND_2;
        u32 where;

        if (offset < 0x2000 || offset >= 0xe000) {
            where = kind2 ? COLLISION_TOUCH_2_AHEAD : COLLISION_TOUCH_1_AHEAD;
        } else if (offset < 0x6000) {
            where = kind2 ? COLLISION_TOUCH_2_SIDE_PLUS : COLLISION_TOUCH_1_SIDE_PLUS;
        } else if (offset < 0xa000) {
            where = kind2 ? COLLISION_TOUCH_2_BEHIND : COLLISION_TOUCH_1_BEHIND;
        } else {
            where = kind2 ? COLLISION_TOUCH_2_SIDE_MINUS : COLLISION_TOUCH_1_SIDE_MINUS;
        }
        contacts->flags |= (kind2 ? COLLISION_TOUCH_2 : COLLISION_TOUCH_1) | where;
    }

    if (contacts->walls.count == 2) {
        int sum = contacts->walls.angle[0] + contacts->walls.angle[1];
        int mean = (s16) (sum >> 1);
        int against = (s16) (mean + 0x7fff);
        int difference = (int) ((u32) facing - (u32) against);
        if (difference < 0) {
            difference = (int) (0u - (u32) difference);
        }
        if (difference < 0x2000) {
            contacts->flags |= COLLISION_IN_CORNER;
        }
        if ((s16) sum == 0) {
            contacts->flags |= COLLISION_OPPOSITE;
        }
    }
}
CLEAN_AS(func_02032aec, CollisionContacts_ClassifyWalls)

/* func_02032c50 */
CollisionContacts *CollisionContacts_Destroy(CollisionContacts *contacts)
{
    CollisionContactList_Destroy(&contacts->walls);
    return contacts;
}
CLEAN_AS(func_02032c50, CollisionContacts_Destroy)

/* func_02032c64 */
CollisionContacts *CollisionContacts_Construct(CollisionContacts *contacts)
{
    CollisionContactList_Construct(&contacts->walls);
    CollisionContacts_Clear(contacts);
    return contacts;
}
CLEAN_AS(func_02032c64, CollisionContacts_Construct)

/* func_02032c7c: everything but the list of touches. */
void CollisionContacts_Clear(CollisionContacts *contacts)
{
    contacts->flags = 0;
    contacts->previous_flags = 0;
    contacts->ground_attr = 0;
    contacts->moved.x = 0;
    contacts->moved.y = 0;
    contacts->moved.z = 0;
}
CLEAN_AS(func_02032c7c, CollisionContacts_Clear)

/* func_02032c8c: before a move's checks; the flags of the last move become the previous ones,
 * which are also the result. */
int CollisionContacts_StartFrame(CollisionContacts *contacts)
{
    u32 flags;

    CollisionContactList_Clear(&contacts->walls);
    contacts->ground_attr = 0;
    flags = contacts->flags;
    contacts->previous_flags = flags;
    contacts->flags = 0;
    contacts->moved.x = 0;
    contacts->moved.y = 0;
    contacts->moved.z = 0;
    return (int) flags;
}
CLEAN_AS(func_02032c8c, CollisionContacts_StartFrame)

/* func_02032cac: records a touch unless one of the same angle and kind is there; whether it
 * did (not when two are there already). */
int CollisionContactList_Add(CollisionContactList *list, s16 angle, int kind, int attr)
{
    u32 i;

    for (i = 0; i < list->count; i++) {
        if (collision_contact_angle(list, i) == angle && collision_contact_kind(list, i) == kind) {
            return 0;
        }
    }
    if (list->count < COLLISION_MAX_CONTACTS) {
        list->angle[list->count] = angle;
        list->kind[list->count] = kind;
        list->attr[list->count] = attr;
        list->count++;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02032cac, CollisionContactList_Add)

/* func_02032d10 */
void CollisionContactList_Clear(CollisionContactList *list)
{
    int i;

    list->count = 0;
    for (i = 0; i < COLLISION_MAX_CONTACTS; i++) {
        list->angle[i] = 0;
        list->attr[i] = 0;
        list->kind[i] = 0;
    }
}
CLEAN_AS(func_02032d10, CollisionContactList_Clear)

/* func_02032d34: nothing to do. */
void CollisionContactList_Destroy(CollisionContactList *list)
{
    (void) list;
}
CLEAN_AS(func_02032d34, CollisionContactList_Destroy)

/* func_02032d38 */
int CollisionContactList_Construct(CollisionContactList *list)
{
    CollisionContactList_Clear(list);
    return (int) (uintptr_t) list;
}
CLEAN_AS(func_02032d38, CollisionContactList_Construct)

/* ---- The push-out visitor */

/* func_02032aa8: the visitor's method for the walls (slot 0 of vtable 0x020da1e8). */
int CollisionPushOut_Walls(CollisionPushOut *visitor, CollisionWallList *walls)
{
    return CollisionWalls_PushOut(walls, visitor->position, &visitor->previous, visitor->radius, visitor->contacts,
                                  visitor->owner);
}
CLEAN_AS(func_02032aa8, CollisionPushOut_Walls)

/* ---- Posts */

/* func_02032d48: fences between every post and the neighbouring posts (CollisionPost_AddFence
 * for every ordered pair, a post with itself included). */
void CollisionPosts_AddFences(CollisionPostList *posts, CollisionWallList *walls)
{
    u32 count = posts->count;
    u32 i;
    u32 j;

    for (i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            CollisionPost_AddFence(&posts->posts[i], walls, &posts->posts[j]);
        }
    }
}
CLEAN_AS(func_02032d48, CollisionPosts_AddFences)

/* func_02032d8c: the posts of the units x0..x1 by z0..z1 (rows of Z, X increasing). Where the
 * source names a post, it is added at the unit's centre with its radius, height and attribute,
 * as kind 2 when the source says 2 and kind 1 otherwise; a kind 2 post is skipped unless `all`.
 * With `all`, a unit without one may hold one of the extra posts (radius by its kind, height
 * 1.0, kind 2, attribute 2). */
void CollisionPosts_Gather(CollisionPostList *posts, CollisionPostSource *source, int x0, int x1, int z0, int z1, int all)
{
    int x;
    int z;

    for (z = z0; z <= z1; z++) {
        fx32 centre_z = collision_unit_centre(z);
        for (x = x0; x <= x1; x++) {
            fx32 radius;
            fx32 height;
            int kind;
            Vec3 at;

            if (source->vtable->post_at(source, &radius, &height, &kind, x, z) != 0) {
                if (kind == COLLISION_KIND_2 && !all) {
                    continue;
                }
                at.x = collision_unit_centre(x);
                at.y = 0;
                at.z = centre_z;
                CollisionPosts_Add(posts, &at, radius, height, kind == COLLISION_KIND_2 ? COLLISION_KIND_2 : COLLISION_KIND_1,
                                   kind);
            } else {
                fx32 extra;
                if (!all || data_021c5124 == 0) {
                    continue;
                }
                extra = func_02034600(&data_021c5124, x, z);
                if (extra == 0) {
                    continue;
                }
                at.x = collision_unit_centre(x);
                at.y = 0;
                at.z = centre_z;
                CollisionPosts_Add(posts, &at, extra, 0x1000, COLLISION_KIND_2, 2);
            }
        }
    }
}
CLEAN_AS(func_02032d8c, CollisionPosts_Gather)

/* func_02032e80: whether there was room for the post. */
int CollisionPosts_Add(CollisionPostList *posts, const Vec3 *position, fx32 radius, fx32 height, int kind, int attr)
{
    if (posts->count >= COLLISION_MAX_POSTS) {
        return 0;
    }
    CollisionPost_Init(&posts->posts[posts->count], position, radius, height, kind, attr);
    posts->count++;
    return 1;
}
CLEAN_AS(func_02032e80, CollisionPosts_Add)

/* func_02032eb8: lands `position`, coming down from `previous`, on the top of the first kind 1
 * post under it; whether it did, with that post's attribute in `attr`. */
int CollisionPosts_Land(CollisionPostList *posts, Vec3 *position, const Vec3 *previous, int *attr, u32 unused_mode, int unused)
{
    u32 at;

    (void) unused_mode;
    (void) unused;
    for (at = collision_first(posts->posts); at < collision_end(posts->posts, posts->count, sizeof(CollisionPost));
         at += sizeof(CollisionPost)) {
        CollisionPost *post = (CollisionPost *) (uintptr_t) at;
        if (post->kind == COLLISION_KIND_1 && func_02030580(post, position, previous) != 0) {
            *attr = post->tag.attr;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02032eb8, CollisionPosts_Land)

/* func_02032f0c: pushes a point of `radius` out of every post it touches, recording each touch
 * with the angle from the post to the point; whether any was touched. */
int CollisionPosts_PushOut(CollisionPostList *posts, Vec3 *position, fx32 radius, CollisionContacts *contacts, u32 unused_mode,
                           int unused)
{
    int touched = 0;
    u32 at;

    (void) unused_mode;
    (void) unused;
    for (at = collision_first(posts->posts); at < collision_end(posts->posts, posts->count, sizeof(CollisionPost));
         at += sizeof(CollisionPost)) {
        CollisionPost *post = (CollisionPost *) (uintptr_t) at;
        if (func_020305b0(post, position, radius) != 0) {
            Vec3 away;
            Vec_Subtract(&away, position, &post->position);
            CollisionContactList_Add(&contacts->walls, Math_Atan2(away.x, away.z), post->kind, post->tag.attr);
            touched = 1;
        }
    }
    return touched;
}
CLEAN_AS(func_02032f0c, CollisionPosts_PushOut)

/* func_02032f78 */
void *CollisionPosts_Destroy(CollisionPostList *posts)
{
    __cxa_vec_cleanup(posts->posts, COLLISION_MAX_POSTS, sizeof(CollisionPost), (void (*)(void *))(uintptr_t) func_020330e8);
    return posts;
}
CLEAN_AS(func_02032f78, CollisionPosts_Destroy)

/* func_02032f94 */
CollisionPostList *CollisionPosts_Construct(CollisionPostList *posts)
{
    __cxa_vec_ctor(posts->posts, COLLISION_MAX_POSTS, sizeof(CollisionPost), (void (*)(void *))(uintptr_t) func_02033100,
                   (void (*)(void *))(uintptr_t) func_020330e8);
    posts->count = 0;
    return posts;
}
CLEAN_AS(func_02032f94, CollisionPosts_Construct)

/* func_02032fc0: when `other` stands on the next unit south, east, south-east or north-east of
 * `post`, a fence from the far side of `post` to the far side of `other`, facing both ways, as
 * high as the lower post (kind 3: it records no touch); whether it made one. */
int CollisionPost_AddFence(CollisionPost *post, CollisionWallList *walls, CollisionPost *other)
{
    int dx = other->unit_x - post->unit_x;
    int dz = other->unit_z - post->unit_z;
    CollisionPoint from, to, direction, start, end, normal, back;
    fx32 x;
    fx32 z;
    fx32 top;

    if (!((dx == 0 && dz == 1) || (dx == 1 && dz >= -1 && dz <= 1))) {
        return 0;
    }
    func_0202f8fc(&from, post->position.x, post->position.z);
    func_0202f8fc(&to, other->position.x, other->position.z);
    func_0202f898(&direction, &to, &from);
    func_0202f7f4(&direction);

    z = from.z - FX_MulFunc(direction.z, post->radius);
    x = from.x - FX_MulFunc(direction.x, post->radius);
    func_0202f8fc(&start, x, z);
    z = to.z + FX_MulFunc(direction.z, other->radius);
    x = to.x + FX_MulFunc(direction.x, other->radius);
    func_0202f8fc(&end, x, z);

    func_0202f8fc(&normal, 0, 0);
    func_0202f7a0(&normal, &from, &to);
    func_0202f8fc(&back, -normal.x, -normal.z);

    top = other->height > post->height ? post->height : other->height;
    CollisionWalls_AddWall(walls, &start, &end, &normal, top, COLLISION_KIND_SILENT, 0, NULL);
    CollisionWalls_AddWall(walls, &start, &end, &back, top, COLLISION_KIND_SILENT, 0, NULL);
    return 1;
}
CLEAN_AS(func_02032fc0, CollisionPost_AddFence)

/* func_020330bc: a post at `position`, on the unit it is in. */
void CollisionPost_Init(CollisionPost *post, const Vec3 *position, fx32 radius, fx32 height, int kind, int attr)
{
    post->unit_x = (s16) (position->x >> COLLISION_UNIT_SHIFT);
    post->unit_z = (s16) (position->z >> COLLISION_UNIT_SHIFT);
    func_02030640(post, position, radius, height);
    post->kind = kind;
    CollisionTag_Set(&post->tag, attr, NULL);
}
CLEAN_AS(func_020330bc, CollisionPost_Init)

/* func_020330e8 */
void *CollisionPost_Destroy(CollisionPost *post)
{
    CollisionTag_Destroy(&post->tag);
    func_02030658(post);
    return post;
}
CLEAN_AS(func_020330e8, CollisionPost_Destroy)

/* func_02033100 */
void *CollisionPost_Construct(CollisionPost *post)
{
    func_02030690(post);
    CollisionTag_Clear(&post->tag);
    return post;
}
CLEAN_AS(func_02033100, CollisionPost_Construct)

/* ---- Walls */

/* A wall at the origin with no attribute: the segment's constructor, then the wall's. */
static void collision_wall_construct(CollisionWall *wall)
{
    wall->segment.vtable = data_020da1a4;
    func_0202f8fc(&wall->segment.start, 0, 0);
    func_0202f8fc(&wall->segment.end, 0, 0);
    func_0202f8fc(&wall->segment.normal, 0, 0);
    CollisionTag_Clear(&wall->tag);
    wall->segment.vtable = data_020da210;
}

/* One of the static normals, set and registered for destruction the first time. */
static const CollisionPoint *collision_static_normal(CollisionPoint *normal, u32 *guard, fx32 x, fx32 z, u8 *record)
{
    if ((*guard & 1) == 0) {
        func_0202f8fc(normal, x, z);
        __register_global_object(normal, (void *) (uintptr_t) func_0202f2f0, record);
        *guard |= 1;
    }
    return normal;
}

/* A step between two levels along `start`-`end`: a kind 1 wall facing `face` up to `top`, and
 * with `back` a kind 2 wall facing `back_face`, 8.0 high, attribute 2. */
static void collision_add_step(CollisionWallList *walls, const CollisionPoint *start, const CollisionPoint *end,
                               const CollisionPoint *face, const CollisionPoint *back_face, fx32 top, int attr, int back)
{
    CollisionWalls_AddWall(walls, start, end, face, top, COLLISION_KIND_1, attr, NULL);
    if (back) {
        CollisionWalls_AddWall(walls, start, end, back_face, COLLISION_BACK_TOP, COLLISION_KIND_2, 2, NULL);
    }
}

/* func_02033118: the walls where the grid's units change level, for the units x0..x1 by
 * z0..z1 taken from the last row and column back: on the east edge of a unit where its east
 * side and the next unit's west side differ, on the south edge where its south side and the
 * next unit's north side differ, and across a unit whose north side differs from its west
 * side (the diagonal from north-west to south-east) or else from its east side (north-east to
 * south-west). The wall faces away from the higher side and is as high as it.
 * QUIRK: on the east edge, a higher next unit gives the wall its north side's height and
 * attribute, not its west side's that the edge compared. */
void CollisionWalls_AddCliffs(CollisionWallList *walls, CollisionCellGrid *grid, int x0, int x1, int z0, int z1, int back)
{
    int x;
    int z;

    for (z = z1; z >= z0; z--) {
        for (x = x1; x >= x0; x--) {
            CollisionCell *cell = CollisionCellGrid_Get(grid, x, z);
            CollisionCell *east;
            CollisionCell *south;
            fx32 cx;
            fx32 cz;
            CollisionPoint start;
            CollisionPoint end;

            if (cell == NULL) {
                continue;
            }
            east = CollisionCellGrid_Get(grid, x + 1, z);
            south = CollisionCellGrid_Get(grid, x, z + 1);
            cx = collision_unit_centre(x);
            cz = collision_unit_centre(z);

            if (east != NULL && cell->side_height[COLLISION_EAST] != east->side_height[COLLISION_WEST]) {
                const CollisionPoint *plus_x =
                    collision_static_normal(&data_021c3128, &data_021c30e8, 0x1000, 0, data_021c31c4);
                const CollisionPoint *minus_x =
                    collision_static_normal(&data_021c3138, &data_021c30d8, -0x1000, 0, data_021c31dc);
                func_0202f8fc(&start, cx + 0x1000, cz - 0x1000);
                func_0202f8fc(&end, start.x, cz + 0x1000);
                if (cell->side_height[COLLISION_EAST] > east->side_height[COLLISION_WEST]) {
                    collision_add_step(walls, &start, &end, plus_x, minus_x, cell->side_height[COLLISION_EAST],
                                       cell->side_attr[COLLISION_EAST], back);
                } else {
                    collision_add_step(walls, &start, &end, minus_x, plus_x, east->side_height[COLLISION_NORTH],
                                       east->side_attr[COLLISION_NORTH], back);
                }
            }

            if (south != NULL && cell->side_height[COLLISION_SOUTH] != south->side_height[COLLISION_NORTH]) {
                const CollisionPoint *plus_z =
                    collision_static_normal(&data_021c3100, &data_021c30d4, 0, 0x1000, data_021c3140);
                const CollisionPoint *minus_z =
                    collision_static_normal(&data_021c3110, &data_021c30cc, 0, -0x1000, data_021c3164);
                func_0202f8fc(&start, cx - 0x1000, cz + 0x1000);
                func_0202f8fc(&end, cx + 0x1000, start.z);
                if (cell->side_height[COLLISION_SOUTH] > south->side_height[COLLISION_NORTH]) {
                    collision_add_step(walls, &start, &end, plus_z, minus_z, cell->side_height[COLLISION_SOUTH],
                                       cell->side_attr[COLLISION_SOUTH], back);
                } else {
                    collision_add_step(walls, &start, &end, minus_z, plus_z, south->side_height[COLLISION_NORTH],
                                       south->side_attr[COLLISION_NORTH], back);
                }
            }

            if (cell->side_height[COLLISION_NORTH] != cell->side_height[COLLISION_WEST]) {
                /* (-0.707, 0.707) and its opposite */
                const CollisionPoint *south_west =
                    collision_static_normal(&data_021c3120, &data_021c30f0, -0xb50, 0xb50, data_021c3188);
                const CollisionPoint *north_east =
                    collision_static_normal(&data_021c3118, &data_021c30ec, -data_021c3120.x, -data_021c3120.z, data_021c31ac);
                func_0202f8fc(&start, cx - 0x1000, cz - 0x1000);
                func_0202f8fc(&end, cx + 0x1000, cz + 0x1000);
                if (cell->side_height[COLLISION_NORTH] > cell->side_height[COLLISION_WEST]) {
                    collision_add_step(walls, &start, &end, south_west, north_east, cell->side_height[COLLISION_NORTH],
                                       cell->side_attr[COLLISION_NORTH], back);
                } else {
                    collision_add_step(walls, &start, &end, north_east, south_west, cell->side_height[COLLISION_WEST],
                                       cell->side_attr[COLLISION_WEST], back);
                }
            } else if (cell->side_height[COLLISION_NORTH] != cell->side_height[COLLISION_EAST]) {
                /* (0.707, 0.707) and its opposite */
                const CollisionPoint *south_east =
                    collision_static_normal(&data_021c3130, &data_021c30fc, 0xb50, 0xb50, data_021c31d0);
                const CollisionPoint *north_west =
                    collision_static_normal(&data_021c3108, &data_021c30f4, -data_021c3130.x, -data_021c3130.z, data_021c314c);
                func_0202f8fc(&start, cx - 0x1000, cz + 0x1000);
                func_0202f8fc(&end, cx + 0x1000, cz - 0x1000);
                if (cell->side_height[COLLISION_NORTH] > cell->side_height[COLLISION_EAST]) {
                    collision_add_step(walls, &start, &end, south_east, north_west, cell->side_height[COLLISION_NORTH],
                                       cell->side_attr[COLLISION_NORTH], back);
                } else {
                    collision_add_step(walls, &start, &end, north_west, south_east, cell->side_height[COLLISION_EAST],
                                       cell->side_attr[COLLISION_EAST], back);
                }
            }
        }
    }
}
CLEAN_AS(func_02033118, CollisionWalls_AddCliffs)

/* func_02033614: adds a wall made from its parts; whether there was room. */
void *CollisionWalls_AddWall(CollisionWallList *walls, const CollisionPoint *start, const CollisionPoint *end,
                             const CollisionPoint *normal, fx32 top, int kind, int attr, CollisionHandler *handler)
{
    CollisionWall wall;
    int added;

    CollisionWall_ConstructInit(&wall, start, end, normal, top, kind, attr, handler);
    added = CollisionWalls_Add(walls, &wall);
    CollisionWall_Destroy(&wall);
    return (void *) (uintptr_t) added;
}
CLEAN_AS(func_02033614, CollisionWalls_AddWall)

/* func_0203364c: whether there was room for a copy of `wall`. */
int CollisionWalls_Add(CollisionWallList *walls, const CollisionWall *wall)
{
    u32 index;

    if (walls->count >= COLLISION_MAX_WALLS) {
        return 0;
    }
    index = walls->count;
    walls->count = index + 1;
    CollisionWall_Copy(&walls->walls[index], wall);
    return 1;
}
CLEAN_AS(func_0203364c, CollisionWalls_Add)

/* One pass of CollisionWalls_PushOut with one of the wall tests. */
static int collision_walls_pass(CollisionWallList *walls,
                                int (*test)(CollisionWall *, CollisionPoint *, const CollisionPoint *, fx32),
                                const Vec3 *position, CollisionPoint *moved, const CollisionPoint *from, fx32 radius,
                                CollisionContacts *contacts, void *owner)
{
    int pushed = 0;
    u32 at;

    for (at = collision_first(walls->walls); at < collision_end(walls->walls, walls->count, sizeof(CollisionWall));
         at += sizeof(CollisionWall)) {
        CollisionWall *wall = (CollisionWall *) (uintptr_t) at;
        if (wall->top - COLLISION_WALL_CLEARANCE > position->y && test(wall, moved, from, radius) != 0) {
            int kind = wall->kind;
            if (kind != COLLISION_KIND_SILENT) {
                CollisionContactList_Add(&contacts->walls, Math_Atan2(wall->segment.normal.x, wall->segment.normal.z), kind,
                                         wall->tag.attr);
                if (wall->tag.handler != NULL) {
                    wall->tag.handler->vtable->touch(wall->tag.handler, wall, owner, radius);
                }
            }
            pushed = 1;
        }
    }
    return pushed;
}

/* func_02033678: pushes `position`, a circle of `radius` moving from `previous`, out of the
 * walls whose top is more than 0.4375 above it; a wall of kind other than 3 records the touch
 * with its normal's angle and tells its handler (with `owner`). Three passes: one testing the
 * path when the move is at least `radius` long, then two at the end point. Whether any pushed. */
int CollisionWalls_PushOut(CollisionWallList *walls, Vec3 *position, const Vec3 *previous, fx32 radius,
                           CollisionContacts *contacts, void *owner)
{
    CollisionPoint moved;
    CollisionPoint from;
    CollisionPoint step;
    int pushed = 0;

    func_0202f8fc(&moved, position->x, position->z);
    func_0202f8fc(&from, previous->x, previous->z);
    func_0202f8fc(&step, position->x - previous->x, position->z - previous->z);
    if (func_0202f838(&step, &data_021c30b8) >= (s64) FX_MulFunc(radius, radius)) {
        pushed |= collision_walls_pass(walls, func_0202f288, position, &moved, &from, radius, contacts, owner);
    }
    pushed |= collision_walls_pass(walls, func_0202f3e4, position, &moved, &from, radius, contacts, owner);
    pushed |= collision_walls_pass(walls, func_0202f2f4, position, &moved, &from, radius, contacts, owner);
    position->x = moved.x;
    position->z = moved.z;
    return pushed;
}
CLEAN_AS(func_02033678, CollisionWalls_PushOut)

/* func_02033878: the list's destructor destroys its walls. */
void *CollisionWalls_Destroy(CollisionWallList *walls)
{
    __cxa_vec_cleanup(walls->walls, COLLISION_MAX_WALLS, sizeof(CollisionWall), (void (*)(void *))(uintptr_t) func_020339b8);
    return walls;
}
CLEAN_AS(func_02033878, CollisionWalls_Destroy)

/* func_02033894 */
void *CollisionWalls_Construct(CollisionWallList *walls)
{
    __cxa_vec_ctor(walls->walls, COLLISION_MAX_WALLS, sizeof(CollisionWall), (void (*)(void *))(uintptr_t) func_020339dc,
                   (void (*)(void *))(uintptr_t) func_020339b8);
    walls->count = 0;
    return walls;
}
CLEAN_AS(func_02033894, CollisionWalls_Construct)

/* func_020338c4: always 1. */
int CollisionWall_Init(CollisionWall *wall, const CollisionPoint *start, const CollisionPoint *end,
                       const CollisionPoint *normal, fx32 top, int kind, int attr, CollisionHandler *handler)
{
    CollisionTag_Set(&wall->tag, attr, handler);
    func_0202f6ac(&wall->segment, start, end, normal);
    wall->kind = kind;
    wall->top = top;
    return 1;
}
CLEAN_AS(func_020338c4, CollisionWall_Init)

/* func_020338f8: always 1. */
int CollisionWall_Copy(CollisionWall *wall, const CollisionWall *from)
{
    CollisionTag_Copy(&wall->tag, &from->tag);
    func_0202f6ac(&wall->segment, &from->segment.start, &from->segment.end, &from->segment.normal);
    wall->kind = from->kind;
    wall->top = from->top;
    return 1;
}
CLEAN_AS(func_020338f8, CollisionWall_Copy)

/* func_0203392c */
void CollisionWall_GetMiddle(CollisionPoint *middle, const CollisionWall *wall)
{
    func_0202f8fc(middle, (wall->segment.start.x + wall->segment.end.x) >> 1,
                  (wall->segment.start.z + wall->segment.end.z) >> 1);
}
CLEAN_AS(func_0203392c, CollisionWall_GetMiddle)

/* func_0203394c */
CollisionWall *CollisionWall_ConstructInit(CollisionWall *wall, const CollisionPoint *start, const CollisionPoint *end,
                                           const CollisionPoint *normal, fx32 top, int kind, int attr,
                                           CollisionHandler *handler)
{
    collision_wall_construct(wall);
    CollisionWall_Init(wall, start, end, normal, top, kind, attr, handler);
    return wall;
}
CLEAN_AS(func_0203394c, CollisionWall_ConstructInit)

/* func_020339b8 */
CollisionWall *CollisionWall_Destroy(CollisionWall *wall)
{
    wall->segment.vtable = data_020da210;
    CollisionTag_Destroy(&wall->tag);
    func_0202f6dc(&wall->segment);
    return wall;
}
CLEAN_AS(func_020339b8, CollisionWall_Destroy)

/* func_020339dc: a wall at the origin, with no attribute. */
void *CollisionWall_Construct(CollisionWall *wall)
{
    collision_wall_construct(wall);
    return wall;
}
CLEAN_AS(func_020339dc, CollisionWall_Construct)

/* ---- Floors */

/* func_02033a24: whether there was room for the triangle. */
int CollisionFloors_Add(CollisionFloorList *floors, const Vec3 *a, const Vec3 *b, const Vec3 *c, const Vec3 *normal, int attr,
                        CollisionHandler *handler)
{
    u32 index;

    if (floors->count >= COLLISION_MAX_FLOORS) {
        return 0;
    }
    index = floors->count;
    floors->count = index + 1;
    return CollisionFloor_Init(&floors->floors[index], a, b, c, normal, attr, handler);
}
CLEAN_AS(func_02033a24, CollisionFloors_Add)

static void collision_set(Vec3 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* func_02033a5c: the floor triangles of the grid's units x0..x1 by z0..z1 (rows of Z, X
 * increasing): a flat unit is two triangles at its north side's height; another is four
 * meeting at its centre, each at the height of its side (north, west, south, east), with that
 * side's attribute. */
void CollisionFloors_AddCells(CollisionFloorList *floors, CollisionCellGrid *grid, int x0, int x1, int z0, int z1)
{
    int x;
    int z;

    for (z = z0; z <= z1; z++) {
        fx32 cz = collision_unit_centre(z);
        for (x = x0; x <= x1; x++) {
            CollisionCell *cell = CollisionCellGrid_Get(grid, x, z);
            fx32 cx;
            fx32 east;
            fx32 west;
            fx32 south;
            fx32 north;
            int flat;
            Vec3 a;
            Vec3 b;
            Vec3 c;
            fx32 h;

            if (cell == NULL) {
                continue;
            }
            cx = collision_unit_centre(x);
            east = cx + 0x1000;
            west = cx - 0x1000;
            south = cz + 0x1000;
            north = cz - 0x1000;
            flat = cell->type < COLLISION_TYPE_COUNT ? data_020c907c[cell->type].flat : 0;
            if (flat != 0) {
                Vec3 d;
                h = cell->side_height[COLLISION_NORTH];
                collision_set(&a, west, h, north);
                collision_set(&b, west, h, south);
                collision_set(&c, east, h, south);
                collision_set(&d, east, h, north);
                CollisionFloors_Add(floors, &a, &b, &c, &data_021c317c, cell->side_attr[COLLISION_NORTH], NULL);
                CollisionFloors_Add(floors, &a, &c, &d, &data_021c317c, cell->side_attr[COLLISION_NORTH], NULL);
            } else {
                h = cell->side_height[COLLISION_NORTH];
                collision_set(&a, cx, h, cz);
                collision_set(&b, east, h, north);
                collision_set(&c, west, h, north);
                CollisionFloors_Add(floors, &a, &b, &c, &data_021c317c, cell->side_attr[COLLISION_NORTH], NULL);
                h = cell->side_height[COLLISION_WEST];
                collision_set(&a, cx, h, cz);
                collision_set(&b, west, h, north);
                collision_set(&c, west, h, south);
                CollisionFloors_Add(floors, &a, &b, &c, &data_021c317c, cell->side_attr[COLLISION_WEST], NULL);
                h = cell->side_height[COLLISION_SOUTH];
                collision_set(&a, cx, h, cz);
                collision_set(&b, west, h, south);
                collision_set(&c, east, h, south);
                CollisionFloors_Add(floors, &a, &b, &c, &data_021c317c, cell->side_attr[COLLISION_SOUTH], NULL);
                h = cell->side_height[COLLISION_EAST];
                collision_set(&a, cx, h, cz);
                collision_set(&b, east, h, south);
                collision_set(&c, east, h, north);
                CollisionFloors_Add(floors, &a, &b, &c, &data_021c317c, cell->side_attr[COLLISION_EAST], NULL);
            }
        }
    }
}
CLEAN_AS(func_02033a5c, CollisionFloors_AddCells)

/* func_02033c2c */
int CollisionFloors_Destroy(CollisionFloorList *floors)
{
    __cxa_vec_cleanup(floors->floors, COLLISION_MAX_FLOORS, sizeof(CollisionFloor),
                      (void (*)(void *))(uintptr_t) func_02033ca8);
    return (int) (uintptr_t) floors;
}
CLEAN_AS(func_02033c2c, CollisionFloors_Destroy)

/* func_02033c48 */
CollisionFloorList *CollisionFloors_Construct(CollisionFloorList *floors)
{
    __cxa_vec_ctor(floors->floors, COLLISION_MAX_FLOORS, sizeof(CollisionFloor), (void (*)(void *))(uintptr_t) func_02033ccc,
                   (void (*)(void *))(uintptr_t) func_02033ca8);
    floors->count = 0;
    return floors;
}
CLEAN_AS(func_02033c48, CollisionFloors_Construct)

/* func_02033c78: always 1. */
int CollisionFloor_Init(CollisionFloor *floor, const Vec3 *a, const Vec3 *b, const Vec3 *c, const Vec3 *normal, int attr,
                        CollisionHandler *handler)
{
    CollisionTag_Set(&floor->tag, attr, handler);
    func_0202fc18(&floor->triangle, a, b, c, normal);
    return 1;
}
CLEAN_AS(func_02033c78, CollisionFloor_Init)

/* func_02033ca8 */
void *CollisionFloor_Destroy(CollisionFloor *floor)
{
    floor->triangle.vtable = data_020da21c;
    CollisionTag_Destroy(&floor->tag);
    func_0202fed4(&floor->triangle);
    return floor;
}
CLEAN_AS(func_02033ca8, CollisionFloor_Destroy)

/* func_02033ccc */
void *CollisionFloor_Construct(CollisionFloor *floor)
{
    func_0202ff00(&floor->triangle);
    CollisionTag_Clear(&floor->tag);
    floor->triangle.vtable = data_020da21c;
    return floor;
}
CLEAN_AS(func_02033ccc, CollisionFloor_Construct)

/* ---- The ground at a point */

/* The current map's halfwords at 0x132 and 0x134; 0x134 is how far up the corner slopes the
 * level is (in 1.0), and which of them is larger turns the slopes' normal around. */
static s16 collision_map_s16(u32 offset)
{
    return *(const s16 *) (uintptr_t) ((uintptr_t) data_020da1a8 + offset);
}

/* The end of a corner slope (types 0x51, 0x52, 0x54, 0x55): `p`, `q`, `r` make the triangle
 * of the unit that is the slope's part; a point in it (or out of it, when `slope_inside` is 0)
 * is on the slope, attribute 0x16 with the normal turned by `angle`; elsewhere attribute 0x13
 * and unk_30 0. `point` becomes the middle of `b`-`c`. */
static void collision_corner_slope(CollisionGround *ground, const Vec3 *position, const Vec3 *p, const Vec3 *q, const Vec3 *r,
                                   const Vec3 *b, const Vec3 *c, int slope_inside, int from, int level, int angle)
{
    CollisionTriangle triangle;

    func_0202feb4(&triangle, p, q, r, &data_021c317c);
    if ((func_0202fb8c(&triangle, position) != 0) == slope_inside) {
        ground->attr = COLLISION_ATTR_16;
        CollisionGround_SetSlopeNormal(ground, from, level, angle);
    } else {
        ground->unk_30 = 0;
        ground->attr = COLLISION_ATTR_13;
    }
    ground->has_point = 1;
    ground->point.x = (b->x + c->x) >> 1;
    ground->point.y = (b->y + c->y) >> 1;
    ground->point.z = (b->z + c->z) >> 1;
    func_0202fee0(&triangle);
}

/* func_02033cec: the ground at `position`: its attribute from the unit's type and the quarter
 * of the unit (one table set, or the other with `alternate`), its height, normal and limit.
 * When the attribute is ground in `mode` (func_02031c14), the corner-slope unit types (0x51
 * to 0x55) put the point on the slope or beside it, and other types may turn the normal by
 * the first eighth of a turn their row names; else unk_30 is 0. */
void CollisionGround_Query(CollisionGround *ground, const Vec3 *position, int alternate, int mode)
{
    int from = collision_map_s16(0x132);
    int level = collision_map_s16(0x134);
    int type;
    int quarter;
    const CollisionTypeInfo *info;

    ground->has_point = 0;
    ground->position.x = position->x;
    ground->position.y = position->y;
    ground->position.z = position->z;
    ground->unit_x = position->x >> COLLISION_UNIT_SHIFT;
    ground->unit_z = position->z >> COLLISION_UNIT_SHIFT;
    type = FieldUnits_GetType(ground->unit_x, ground->unit_z);
    quarter = func_02031da8(position);
    if (alternate != 0) {
        ground->attr = func_02031ca8(ground->unit_x, ground->unit_z, quarter);
    } else {
        ground->attr = func_02031d28(ground->unit_x, ground->unit_z, quarter);
    }
    info = collision_type_info(ground->attr);
    ground->height = ground->attr < COLLISION_TYPE_COUNT ? info->height * 256 : 0;
    ground->limit = -0x12000;
    ground->unk_30 = ground->attr < COLLISION_TYPE_COUNT ? info->unk_14 : 0;
    ground->normal.x = 0;
    ground->normal.y = 0;
    ground->normal.z = 0x1000;

    if (func_02031c14(ground->attr, mode) == 0) {
        ground->unk_30 = 0;
        return;
    }

    if (type == UNIT_TYPE_52 || type == UNIT_TYPE_55 || type == UNIT_TYPE_51 || type == UNIT_TYPE_54) {
        fx32 cx = (position->x & ~0x1fff) + 0x1000;
        fx32 cz = (position->z & ~0x1fff) + 0x1000;
        Vec3 a;
        Vec3 b;
        Vec3 c;

        a.y = 0;
        b.y = 0;
        c.y = 0;
        if (type == UNIT_TYPE_52) {
            a.x = cx - 0x1000;
            a.z = cz + 0x1000;
            b.x = a.x;
            b.z = a.z - FX_MulFunc(level, 0x1666);
            c.x = a.x + FX_MulFunc(level, 0x1666);
            c.z = a.z;
            collision_corner_slope(ground, position, &b, &a, &c, &b, &c, 1, from, level, 0x6000);
        } else if (type == UNIT_TYPE_55) {
            a.x = cx + 0xb33;
            a.z = cz - 0xb33;
            b.x = a.x;
            b.z = a.z + FX_MulFunc(0x1000 - level, 0x1666);
            c.x = a.x - FX_MulFunc(0x1000 - level, 0x1666);
            c.z = a.z;
            collision_corner_slope(ground, position, &a, &c, &b, &b, &c, 0, from, level, 0x6000);
        } else if (type == UNIT_TYPE_51) {
            a.x = cx + 0x1000;
            a.z = cz + 0x1000;
            b.x = a.x;
            b.z = a.z - FX_MulFunc(level, 0x1666);
            c.x = a.x - FX_MulFunc(level, 0x1666);
            c.z = a.z;
            collision_corner_slope(ground, position, &b, &c, &a, &b, &c, 1, from, level, -0x6000);
        } else {
            a.x = cx - 0xb33;
            a.z = cz - 0xb33;
            b.x = a.x;
            b.z = a.z + FX_MulFunc(0x1000 - level, 0x1666);
            c.x = a.x + FX_MulFunc(0x1000 - level, 0x1666);
            c.z = a.z;
            collision_corner_slope(ground, position, &a, &b, &c, &b, &c, 0, from, level, -0x6000);
        }
    } else if (type == UNIT_TYPE_53) {
        fx32 cx = (position->x & ~0x1fff) + 0x1000;
        fx32 cz = (position->z & ~0x1fff) + 0x1000;
        fx32 edge = cz + 0x1000 - FX_MulFunc(level, 0x1666);

        if (edge > position->z) {
            ground->unk_30 = 0;
            ground->attr = COLLISION_ATTR_13;
        } else {
            ground->attr = COLLISION_ATTR_16;
            CollisionGround_SetSlopeNormal(ground, from, level, -0x8000);
        }
        ground->has_point = 1;
        ground->point.x = cx;
        ground->point.y = 0;
        ground->point.z = edge;
    } else {
        int turns = ground->attr < COLLISION_TYPE_COUNT ? collision_type_info(ground->attr)->normal_turns : 0;
        if (turns != 0) {
            int angle = 0;
            int i;
            for (i = 0; i < 8; i++) {
                if ((turns & (1 << i)) != 0) {
                    angle = (s16) (i << 13);
                    break;
                }
            }
            Vec_RotateY(&ground->normal, angle);
        }
    }

    if (ground->unk_30 != 0) {
        ground->limit = -0x1000;
    }
}
CLEAN_AS(func_02033cec, CollisionGround_Query)

/* func_02034150: the normal (0, 0, 1.0) turned by `angle`, or by `angle` plus half a turn
 * when `level` is not above `from`. */
void CollisionGround_SetSlopeNormal(CollisionGround *ground, int from, int level, int angle)
{
    int half = level - from <= 0 ? -0x8000 : 0;

    ground->normal.x = 0;
    ground->normal.y = 0;
    ground->normal.z = 0x1000;
    Vec_RotateY(&ground->normal, (s16) ((u32) angle + (u32) half));
}
CLEAN_AS(func_02034150, CollisionGround_SetSlopeNormal)

/* func_02034184: whether the ground has unk_30 and `y` is not above its limit. */
int CollisionGround_IsBelowLimit(const CollisionGround *ground, fx32 y)
{
    return ground->unk_30 != 0 && y <= ground->limit;
}
CLEAN_AS(func_02034184, CollisionGround_IsBelowLimit)

/* func_0203419c: the limit, times 0.3 (30 / 100) on attribute 0x16. */
fx32 CollisionGround_GetLimit(const CollisionGround *ground)
{
    if (ground->attr == COLLISION_ATTR_16) {
        return FX_MulFunc(ground->limit, FX_Div(0x1e000, 0x64000));
    }
    return ground->limit;
}
CLEAN_AS(func_0203419c, CollisionGround_GetLimit)

/* func_020341c8: the ground's height; `with_post` adds the height main's tables give the
 * unit's post (kind other than 2) when the point is within its radius of the unit's centre. */
fx32 CollisionGround_GetHeight(const CollisionGround *ground, int with_post)
{
    int radius;
    int height;
    int kind;

    if (with_post == 0) {
        return ground->height;
    }
    if (func_02031078(ground->unit_x, ground->unit_z, &radius, &height, &kind) != 0 && kind != COLLISION_KIND_2) {
        Vec3 centre;
        s64 distance;
        centre.x = collision_unit_centre(ground->unit_x);
        centre.y = 0;
        centre.z = collision_unit_centre(ground->unit_z);
        distance = Vec_DistanceSquaredXZ(&centre, &ground->position);
        if ((s64) FX_MulFunc(radius, radius) >= distance) {
            return ground->height + height;
        }
    }
    return ground->height;
}
CLEAN_AS(func_020341c8, CollisionGround_GetHeight)

/* func_0203423c: nothing to do. */
void CollisionGround_Destroy(CollisionGround *ground)
{
    (void) ground;
}
CLEAN_AS(func_0203423c, CollisionGround_Destroy)

/* func_02034240: the ground at the centre of unit (x, z). */
int CollisionGround_InitAtUnit(CollisionGround *ground, int x, int z, int alternate, int mode)
{
    Vec3 at;

    at.x = collision_unit_centre(x);
    at.y = 0;
    at.z = collision_unit_centre(z);
    CollisionGround_Query(ground, &at, alternate, mode);
    return (int) (uintptr_t) ground;
}
CLEAN_AS(func_02034240, CollisionGround_InitAtUnit)

/* func_02034270 */
int CollisionGround_Init(CollisionGround *ground, const Vec3 *position, int alternate, int mode)
{
    CollisionGround_Query(ground, position, alternate, mode);
    return (int) (uintptr_t) ground;
}
CLEAN_AS(func_02034270, CollisionGround_Init)

/* ---- The grid of units */

/* func_020342ac: sets the current map's index (data_021c31e8) when `value` is 0 to 7; whether
 * it did. */
int CollisionMaps_SetIndex(int *index, int value)
{
    if (value >= 0 && value < 8) {
        *index = value;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020342ac, CollisionMaps_SetIndex)

/* func_020342c0: the grid's unit (x, z), NULL outside the units loaded. */
CollisionCell *CollisionCellGrid_Get(CollisionCellGrid *grid, int x, int z)
{
    if (x >= grid->min_x && x <= grid->max_x && z >= grid->min_z && z <= grid->max_z) {
        u32 row = ((u32) z - (u32) grid->min_z) * (u32) sizeof(grid->cells[0]);
        u32 column = ((u32) x - (u32) grid->min_x) * (u32) sizeof(CollisionCell);
        return (CollisionCell *) (uintptr_t) ((uintptr_t) grid + row + column);
    }
    return NULL;
}
CLEAN_AS(func_020342c0, CollisionCellGrid_Get)

/* func_02034310: loads the units x0..x1 by z0..z1 (func_02034448, from one table set or the
 * other with `alternate`).
 * QUIRK: when either side is longer than 7, the 7 by 7 units from (x0, z0) are loaded, so the
 * other side may grow to 7 too. */
void CollisionCellGrid_Load(CollisionCellGrid *grid, int x0, int x1, int z0, int z1, int alternate)
{
    int width = (int) ((u32) x1 - (u32) x0 + 1);
    int depth = (int) ((u32) z1 - (u32) z0 + 1);
    int x;
    int z;

    grid->min_x = x0;
    grid->min_z = z0;
    if (width <= COLLISION_GRID_SIZE && depth <= COLLISION_GRID_SIZE) {
        grid->max_x = x1;
        grid->max_z = z1;
    } else {
        grid->max_x = x0 + COLLISION_GRID_SIZE - 1;
        grid->max_z = z0 + COLLISION_GRID_SIZE - 1;
    }
    for (z = grid->min_z; z <= grid->max_z; z++) {
        for (x = grid->min_x; x <= grid->max_x; x++) {
            CollisionCell *cell = (CollisionCell *) (uintptr_t) ((uintptr_t) grid +
                                                                 ((u32) z - (u32) grid->min_z) * (u32) sizeof(grid->cells[0]) +
                                                                 ((u32) x - (u32) grid->min_x) * (u32) sizeof(CollisionCell));
            func_02034448(cell, x, z, alternate);
        }
    }
}
CLEAN_AS(func_02034310, CollisionCellGrid_Load)

/* func_020343f0: a unit's constructor; nothing to do. */
void CollisionCell_Construct(CollisionCell *cell)
{
    (void) cell;
}
CLEAN_AS(func_020343f0, CollisionCell_Construct)
