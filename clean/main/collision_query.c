/* Questions to the field's collision (collision_query.h). */
#include "collision_query.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "collision_map.h"
#include "itcm/field_units.h"
#include "itcm/vector.h"
#include "unit_type_info.h"

static_assert(sizeof(CollisionSegmentTest) == 0x40, "segment test");
static_assert(offsetof(CollisionSegmentTest, tag) == 0x1c && offsetof(CollisionSegmentTest, attr) == 0x30,
              "segment test fields");
static_assert(sizeof(CollisionTraceHit) == 0x14, "segment test result");
static_assert(sizeof(CollisionPushOut) == 0x28, "push-out visitor");

/* The world of the collision code and its current map. */
extern CollisionWorld data_021c31e8;
extern FieldBlockMap *data_020da1a8;
/* The rows of the unit type table. */
extern const CollisionTypeInfo data_020c907c[];
/* A margin added to the box of a gathering on every side; its X also widens the reach a move
 * may cover in one go. */
extern Vec3 data_021c31a0;
/* The vtables of the segment test and of the push-out visitor. */
extern const u8 data_020da1d4[];
extern const u8 data_020da1e8[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *difference);

/* The visitors' base class: constructor and destructor (they set its vtable, 0x020da1c0). */
extern void func_02031e74(void *visitor);
extern void func_02031e68(void *visitor);
/* `*bound` becomes the smaller (func_02031e08) or the larger (func_02031e28) of itself and
 * `point`, axis by axis. */
extern void func_02031e08(Vec3 *bound, const Vec3 *point);
extern void func_02031e28(Vec3 *bound, const Vec3 *point);
/* The post source of the current map, or a default one. */
extern CollisionPostSource *func_02031c50(void);
/* The walls and floors of the objects listed by the world's byte at 0x1a90, in the box of
 * `centre` and half size `half`: those above height 0 in pass 0, the others in pass 1. */
extern void func_02031ecc(u8 *list, const Vec3 *centre, const Vec3 *half, CollisionWallList *walls, CollisionFloorList *floors,
                          int flags, int pass);
/* Whether the ground under `position` is above 0 or a post stands on its unit. */
extern int func_02031bb8(const Vec3 *position);
/* Tells the objects listed by the world's byte at 0x1a91 that `owner` of `radius` is at
 * `position`, each one within its reach. */
extern void func_02032610(const Vec3 *position, fx32 radius, void *owner);

/* A gathering's box covers at most this far around a move (6.0) with the margins. */
#define COLLISION_QUERY_MOVE_REACH 0xc000
/* How far above the ground a moved position is put (1/8). */
#define COLLISION_QUERY_CLEARANCE 0x200
/* The height of the floor CollisionQuery_FloorHeight gives (1/8). */
#define COLLISION_QUERY_FLOOR 0x200
/* The heights a ground probe goes from and to (100.0 and -100.0). */
#define COLLISION_QUERY_PROBE_TOP 0x64000
#define COLLISION_QUERY_PROBE_BOTTOM (-0x64000)
/* The flags of the probes of CollisionQuery_CanStep. */
#define COLLISION_QUERY_STEP_FLAGS (COLLISION_QUERY_GROUND | COLLISION_QUERY_STORE | COLLISION_QUERY_NO_FENCES)
/* The side attribute CollisionQuery_FindSpotInBlock looks for, and its answers. */
#define COLLISION_SIDE_14 0x14
#define COLLISION_SPOT_FREE_ROW 1
#define COLLISION_SPOT_BLOCKED_ROW 0
#define COLLISION_SPOT_EDGE 2
#define COLLISION_SPOT_EDGE_14 3
#define COLLISION_SPOT_NONE 4
/* The distance CollisionQuery_IsWaterAroundPoint looks around (0.625) and its ground mode. */
#define COLLISION_QUERY_WATER_RADIUS 0xa00
#define COLLISION_QUERY_WATER_MODE 2

static fx32 collision_query_abs(fx32 value)
{
    return value < 0 ? -value : value;
}

/* The centre of unit `unit` on its axis. */
static fx32 collision_query_unit_centre(int unit)
{
    return (fx32) (((u32) unit << COLLISION_UNIT_SHIFT) + COLLISION_HALF_UNIT);
}

/* func_02030ebc: gathers the shapes of the box from `min` to `max` (widened by the margin on
 * every side) into the world's lists and hands them to `visitor`: its posts, then its walls,
 * then its floors. The lists are emptied first; the grid is loaded over the box's units (from
 * the other table set with `alternate`); then, by `flags`, the posts of the map's source, the
 * walls and floors of the listed objects, fences between the posts and cliffs from the grid,
 * and with `with_floors` the floors of the grid's units. */
void CollisionQuery_Gather(const Vec3 *min, const Vec3 *max, CollisionVisitor *visitor, int flags, u8 with_floors,
                           u8 alternate)
{
    CollisionWorld *world = &data_021c31e8;
    int all = (flags & COLLISION_QUERY_ALL) ? 1 : 0;
    Vec3 low;
    Vec3 high;
    Vec3 centre;
    Vec3 half;

    Vec_Subtract(&low, min, &data_021c31a0);
    Vec_Add(&high, max, &data_021c31a0);
    int x0 = low.x >> COLLISION_UNIT_SHIFT;
    int z0 = low.z >> COLLISION_UNIT_SHIFT;
    int x1 = high.x >> COLLISION_UNIT_SHIFT;
    int z1 = high.z >> COLLISION_UNIT_SHIFT;

    Vec_Add(&centre, &low, &high);
    centre.x >>= 1;
    centre.y >>= 1;
    centre.z >>= 1;
    Vec_Subtract(&half, &high, &low);
    half.x >>= 1;
    half.y >>= 1;
    half.z >>= 1;

    world->posts.count = 0;
    world->walls.count = 0;
    world->floors.count = 0;
    CollisionCellGrid_Load(&world->grid, x0, x1, z0, z1, alternate);

    if ((flags & (COLLISION_QUERY_GROUND | COLLISION_QUERY_WALLS | COLLISION_QUERY_ALL)) != 0 &&
        (flags & COLLISION_QUERY_NO_POSTS) == 0) {
        CollisionPosts_Gather(&world->posts, func_02031c50(), x0, x1, z0, z1, all);
    }
    if ((flags & COLLISION_QUERY_NO_LISTED) == 0) {
        func_02031ecc(&world->unk_1a90, &centre, &half, &world->walls, &world->floors, flags, 0);
        func_02031ecc(&world->unk_1a90, &centre, &half, &world->walls, &world->floors, flags, 1);
    }
    if ((flags & (COLLISION_QUERY_WALLS | COLLISION_QUERY_ALL)) != 0) {
        if ((flags & COLLISION_QUERY_NO_FENCES) == 0) {
            CollisionPosts_AddFences(&world->posts, &world->walls);
        }
        CollisionWalls_AddCliffs(&world->walls, &world->grid, x0, x1, z0, z1, all);
    }
    if (with_floors != 0 && flags != 0) {
        CollisionFloors_AddCells(&world->floors, &world->grid, x0, x1, z0, z1);
    }

    visitor->vtable->posts(visitor, &world->posts);
    visitor->vtable->walls(visitor, &world->walls);
    visitor->vtable->floors(visitor, &world->floors);
}
CLEAN_AS(func_02030ebc, CollisionQuery_Gather)

/* func_0203104c: whether a post stands on the unit under `point`. */
int CollisionQuery_HasPostAtPoint(const Vec3 *point)
{
    return CollisionQuery_HasPostAt(point->x >> COLLISION_UNIT_SHIFT, point->z >> COLLISION_UNIT_SHIFT);
}
CLEAN_AS(func_0203104c, CollisionQuery_HasPostAtPoint)

/* func_02031060: whether a post stands on unit (x, z). */
int CollisionQuery_HasPostAt(int x, int z)
{
    fx32 radius;
    fx32 height;
    int kind;
    return CollisionQuery_PostAt(x, z, &radius, &height, &kind);
}
CLEAN_AS(func_02031060, CollisionQuery_HasPostAt)

/* func_02031078: the post on unit (x, z) as the current map's own post source tells it (none
 * without one): its radius, height and kind, and the result 1; else 0 and nothing written. */
int CollisionQuery_PostAt(int x, int z, fx32 *radius, fx32 *height, int *kind)
{
    CollisionPostSource *source = (CollisionPostSource *) (uintptr_t) data_020da1a8->unk_120;
    fx32 r;
    fx32 h;
    int k;

    if (source != NULL && source->vtable->post_at(source, &r, &h, &k, x, z) != 0) {
        *radius = r;
        *height = h;
        *kind = k;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02031078, CollisionQuery_PostAt)

/* func_020310c8: the height of a floor, always 0x200 (the height CollisionQuery_Move keeps a
 * position above the ground). */
int CollisionQuery_FloorHeight(int unused)
{
    (void) unused;
    return COLLISION_QUERY_FLOOR;
}
CLEAN_AS(func_020310c8, CollisionQuery_FloorHeight)

/* func_020310d0: the height of what is under `point`: a segment test from 100.0 above to 100.0
 * below it (with `flags` less 0x02 and 0x04) gives the height met and its tag's attribute;
 * failing that, the ground (CollisionGround, table set 0, mode 0) gives its height and its
 * attribute. The attribute goes to `attr` unless it is NULL. */
int CollisionQuery_GroundY(const Vec3 *point, int *attr, int flags)
{
    CollisionTraceHit hit;
    Vec3 top;
    Vec3 bottom;
    int y;

    CollisionSegmentHit_Construct(&hit.hit);
    flags &= ~(COLLISION_QUERY_WALLS | COLLISION_QUERY_ALL);
    top = *point;
    bottom = *point;
    top.y = COLLISION_QUERY_PROBE_TOP;
    bottom.y = COLLISION_QUERY_PROBE_BOTTOM;
    if (CollisionQuery_Trace(&hit, &bottom, &top, flags) != 0) {
        if (attr != NULL) {
            *attr = hit.hit.tag.attr;
        }
        y = bottom.y;
        CollisionSegmentHit_Destroy(&hit.hit);
        return y;
    }

    CollisionGround ground;
    CollisionGround_Init(&ground, point, 0, 0);
    if (attr != NULL) {
        *attr = ground.attr;
    }
    y = CollisionGround_GetHeight(&ground, 0);
    CollisionGround_Destroy(&ground);
    CollisionSegmentHit_Destroy(&hit.hit);
    return y;
}
CLEAN_AS(func_020310d0, CollisionQuery_GroundY)

/* func_02031168: keeps `point` (X and Z) `inset` inside the rectangle of `width` by `depth`
 * centred on `centre`; whether it moved. */
int CollisionQuery_ClampToRect(Vec3 *point, fx32 inset, const Vec3 *centre, fx32 width, fx32 depth)
{
    fx32 half_width = width >> 1;
    fx32 half_depth = depth >> 1;
    fx32 low_x = inset + (centre->x - half_width);
    fx32 high_x = (centre->x + half_width) - inset;
    fx32 low_z = inset + (centre->z - half_depth);
    fx32 high_z = (centre->z + half_depth) - inset;
    int moved = 0;

    if (point->x < low_x) {
        point->x = low_x;
        moved = 1;
    } else if (point->x > high_x) {
        point->x = high_x;
        moved = 1;
    }
    if (point->z < low_z) {
        point->z = low_z;
        moved = 1;
    } else if (point->z > high_z) {
        point->z = high_z;
        moved = 1;
    }
    return moved;
}
CLEAN_AS(func_02031168, CollisionQuery_ClampToRect)

/* func_020311bc: the segment test from `start` to `*end` over the shapes gathered in their box
 * (with `flags`, and floors): whether it met one. `result` gets the tag and the normal of the
 * last one met; with COLLISION_QUERY_STORE `*end` becomes the meeting point.
 * BUG: when nothing is met, the normal copied to `result` is whatever the test's stack held. */
int CollisionQuery_Trace(CollisionTraceHit *result, Vec3 *end, const Vec3 *start, int flags)
{
    Vec3 to = *end;
    Vec3 low = *start;
    Vec3 high = *start;
    CollisionSegmentTest test;

    func_02031e08(&low, &to);
    func_02031e28(&high, &to);
    func_02031e74(&test);
    test.vtable = data_020da1d4;
    CollisionHitTag_Clear(&test.tag);
    test.attr = 0;
    test.end = &to;
    test.start = *start;
    test.flags = (u32) flags;
    test.hit = 0;
    test.wall_count = 0;
    test.floor_count = 0;
    test.post_count = 0;

    CollisionQuery_Gather(&low, &high, (CollisionVisitor *) &test, flags, 1, 0);

    if ((flags & COLLISION_QUERY_STORE) != 0) {
        *end = to;
    }
    result->normal = test.normal;
    CollisionTag_Copy(&result->hit.tag, &test.tag);
    int hit = test.hit;
    test.vtable = data_020da1d4;
    CollisionHitTag_Destroy(&test.tag);
    func_02031e68(&test);
    return hit;
}
CLEAN_AS(func_020311bc, CollisionQuery_Trace)

/* func_02031288: moves an actor of `radius` from `previous` to `*position`, facing `facing`:
 * the shapes around the move (the box of both points widened by the radius) push it out of
 * walls and posts (the push-out visitor), the touches go to `contacts`, and by `flags`:
 * - COLLISION_QUERY_ALL: back to `*previous` where the ground is raised or a post stands;
 * - COLLISION_QUERY_GROUND: up to COLLISION_QUERY_CLEARANCE over the ground when below it
 *   (COLLISION_ON_GROUND and the ground's attribute), COLLISION_BELOW_LIMIT where the ground
 *   says so;
 * - COLLISION_QUERY_STORE: the result is written to `*position`.
 * How far the checks moved it goes to the contacts either way, and with an `owner` the objects
 * of the list at 0x1a91 are told where it is. The table set of the gathering and of the ground
 * is the other one while the last move was below the limit.
 * A move longer than the reach (with the margins) is taken as starting at `*position`. */
void CollisionQuery_Move(CollisionContacts *contacts, Vec3 *position, const Vec3 *previous, int facing, fx32 radius,
                         void *owner, int flags)
{
    Vec3 at = *position;
    Vec3 from = *previous;
    fx32 reach = (fx32) ((u32) (data_021c31a0.x + radius) << 1);

    if (reach + collision_query_abs(at.x - previous->x) > COLLISION_QUERY_MOVE_REACH ||
        reach + collision_query_abs(at.z - previous->z) > COLLISION_QUERY_MOVE_REACH) {
        from = at;
    }

    Vec3 size = {radius, radius, radius};
    Vec3 high = from;
    Vec3 low = from;
    func_02031e28(&high, &at);
    func_02031e08(&low, &at);
    VEC_Add(&high, &size, &high);
    VEC_Subtract(&low, &size, &low);

    CollisionPushOut push;
    func_02031e74(&push);
    push.vtable = data_020da1e8;
    push.contacts = contacts;
    push.position = &at;
    push.previous = from;
    push.facing = (u16) facing;
    push.radius = radius;
    push.owner = owner;
    push.flags = (u32) flags;

    CollisionContacts_StartFrame(contacts);
    CollisionQuery_Gather(&low, &high, (CollisionVisitor *) &push, flags, 0,
                          (contacts->previous_flags & COLLISION_BELOW_LIMIT) ? 1 : 0);

    if ((flags & COLLISION_QUERY_ALL) != 0 && func_02031bb8(&at) != 0) {
        at = *previous;
    }
    if ((flags & COLLISION_QUERY_GROUND) != 0) {
        CollisionGround ground;
        CollisionGround_Init(&ground, &at, (contacts->previous_flags & COLLISION_BELOW_LIMIT) ? 1 : 0,
                             (flags & COLLISION_QUERY_MODE_1) ? 1 : 0);
        if (at.y < CollisionGround_GetHeight(&ground, 0) + COLLISION_QUERY_CLEARANCE) {
            contacts->flags |= COLLISION_ON_GROUND;
            contacts->ground_attr = ground.attr;
            at.y = CollisionGround_GetHeight(&ground, 0) + COLLISION_QUERY_CLEARANCE;
        }
        if (CollisionGround_IsBelowLimit(&ground, at.y) != 0) {
            contacts->flags |= COLLISION_BELOW_LIMIT;
        }
        CollisionGround_Destroy(&ground);
    }

    CollisionContacts_ClassifyWalls(contacts, facing);
    Vec3 moved;
    Vec_Subtract(&moved, &at, position);
    contacts->moved = moved;
    if ((flags & COLLISION_QUERY_STORE) != 0) {
        *position = at;
    }
    if (owner != NULL) {
        func_02032610(&at, radius, owner);
    }
    push.vtable = data_020da1e8;
    func_02031e68(&push);
}
CLEAN_AS(func_02031288, CollisionQuery_Move)

/* Whether all four sides of `cell` have attribute COLLISION_SIDE_14. */
static int collision_query_all_sides_14(const CollisionCell *cell)
{
    return cell->side_attr[COLLISION_NORTH] == COLLISION_SIDE_14 && cell->side_attr[COLLISION_WEST] == COLLISION_SIDE_14 &&
           cell->side_attr[COLLISION_SOUTH] == COLLISION_SIDE_14 && cell->side_attr[COLLISION_EAST] == COLLISION_SIDE_14;
}

/* func_02031498: walks the units of block (block_x, block_z) of the current map row by row
 * (X increasing), each unit (*x, *z) written before it is looked at, until:
 * - the unit and the next on X have all four sides of attribute 0x14: then 1 when the unit
 *   after those has them too, else 0;
 * - the unit has 0x14 on its south and east sides only and the next one on its west and south
 *   but neither its north nor its east side: then 3 when byte 0x14 of the row of that east
 *   side's attribute is set, else 2.
 * The result is 4 when no unit matches or the block is outside the map. */
int CollisionQuery_FindSpotInBlock(int *x, int *z, int block_x, int block_z)
{
    if (FieldUnits_GetBlock(block_x, block_z) == NULL) {
        return COLLISION_SPOT_NONE;
    }
    int base_x = (int) ((u32) block_x << 4);
    int base_z = (int) ((u32) block_z << 4);

    for (int dz = 0; dz < 16; dz++) {
        int row_z = base_z + dz;
        for (int dx = 0; dx < 16; dx++) {
            CollisionCell unit;
            CollisionCell next;

            *x = base_x + dx;
            *z = row_z;
            CollisionCell_Load(&unit, *x, *z, 0);
            CollisionCell_Load(&next, *x + 1, *z, 0);
            if (collision_query_all_sides_14(&unit)) {
                if (collision_query_all_sides_14(&next)) {
                    CollisionCell after;
                    CollisionCell_Load(&after, *x + 2, *z, 0);
                    return collision_query_all_sides_14(&after) ? COLLISION_SPOT_FREE_ROW : COLLISION_SPOT_BLOCKED_ROW;
                }
                continue;
            }
            if (unit.side_attr[COLLISION_NORTH] != COLLISION_SIDE_14 && unit.side_attr[COLLISION_WEST] != COLLISION_SIDE_14 &&
                unit.side_attr[COLLISION_SOUTH] == COLLISION_SIDE_14 && unit.side_attr[COLLISION_EAST] == COLLISION_SIDE_14 &&
                next.side_attr[COLLISION_NORTH] != COLLISION_SIDE_14 && next.side_attr[COLLISION_WEST] == COLLISION_SIDE_14 &&
                next.side_attr[COLLISION_SOUTH] == COLLISION_SIDE_14 && next.side_attr[COLLISION_EAST] != COLLISION_SIDE_14) {
                int east = next.side_attr[COLLISION_EAST];
                int flag = east < COLLISION_TYPE_COUNT ? data_020c907c[east].unk_14 : 0;
                return flag == 0 ? COLLISION_SPOT_EDGE : COLLISION_SPOT_EDGE_14;
            }
        }
    }
    return COLLISION_SPOT_NONE;
}
CLEAN_AS(func_02031498, CollisionQuery_FindSpotInBlock)

/* func_02031608: a grid unit's destructor; nothing to do. */
void CollisionQuery_DestructCell(void *cell)
{
    (void) cell;
}
CLEAN_AS(func_02031608, CollisionQuery_DestructCell)

/* func_02031614: CollisionQuery_IsWaterAround within 0.625 in ground mode 2. */
int CollisionQuery_IsWaterAroundPoint(const Vec3 *point)
{
    return CollisionQuery_IsWaterAround(point, COLLISION_QUERY_WATER_RADIUS, NULL, COLLISION_QUERY_WATER_MODE);
}
CLEAN_AS(func_02031614, CollisionQuery_IsWaterAroundPoint)

/* func_0203162c: CollisionQuery_FindWaterAlong in ground mode 2. */
int CollisionQuery_FindWaterAhead(Vec3 *out, const Vec3 *from, int angle, int distance, fx32 radius, int steps)
{
    return CollisionQuery_FindWaterAlong(out, from, (u32) distance, angle, (u32) steps, radius, COLLISION_QUERY_WATER_MODE);
}
CLEAN_AS(func_0203162c, CollisionQuery_FindWaterAhead)

/* func_02031650: the first of `steps` + 1 points from `from` to `distance` away in the direction
 * `angle` (about Y from +Z), evenly spaced, where CollisionQuery_IsWaterAround holds: it goes to
 * `out` at the height of the water's limit, and the result is 1; else 0 (also for no steps).
 * QUIRK: the spacing is `distance` / `steps` rounded down, so the last point may fall short. */
int CollisionQuery_FindWaterAlong(Vec3 *out, const Vec3 *from, u32 distance, int angle, u32 steps, fx32 radius, int mode)
{
    if (steps < 1) {
        return 0;
    }
    u32 spacing = distance / steps;
    Vec3 direction = {0, 0, 0x1000};
    Vec_RotateY(&direction, angle);
    for (u32 i = 0; i <= steps; i++) {
        fx32 along = (fx32) (i * spacing);
        Vec3 point;
        fx32 surface;
        point.z = from->z + FX_MulFunc(direction.z, along);
        point.y = from->y + FX_MulFunc(direction.y, along);
        point.x = from->x + FX_MulFunc(direction.x, along);
        if (CollisionQuery_IsWaterAround(&point, radius, &surface, mode) != 0) {
            out->x = point.x;
            out->y = surface;
            out->z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02031650, CollisionQuery_FindWaterAlong)

/* func_020316fc: whether the ground (table set 0, `mode`) is water (its unk_30, what the
 * fishing float ripples on) at `point` and at the eight points `radius` away on X, Z or both;
 * then the limit of the ground at `point` goes to `surface` unless it is NULL. */
int CollisionQuery_IsWaterAround(const Vec3 *point, fx32 radius, fx32 *surface, int mode)
{
    CollisionGround centre;

    CollisionGround_Init(&centre, point, 0, mode);
    if (centre.unk_30 == 0) {
        CollisionGround_Destroy(&centre);
        return 0;
    }
    const Vec3 offsets[8] = {
        {-radius, 0, -radius}, {-radius, 0, radius}, {radius, 0, radius}, {radius, 0, -radius},
        {-radius, 0, 0},       {radius, 0, 0},       {0, 0, radius},      {0, 0, -radius},
    };
    fx32 limit = 0;
    for (int i = 0; i < 8; i++) {
        Vec3 near;
        CollisionGround around;
        Vec_Add(&near, point, &offsets[i]);
        CollisionGround_Init(&around, &near, 0, mode);
        if (around.unk_30 == 0) {
            CollisionGround_Destroy(&around);
            CollisionGround_Destroy(&centre);
            return 0;
        }
        limit = centre.limit;
        CollisionGround_Destroy(&around);
    }
    if (surface != NULL) {
        *surface = limit;
    }
    CollisionGround_Destroy(&centre);
    return 1;
}
CLEAN_AS(func_020316fc, CollisionQuery_IsWaterAround)

/* Whether the four sides of the grid unit at `point` (table set 0) are at one height. */
static int collision_query_is_level(const Vec3 *point)
{
    CollisionCell cell;
    CollisionCell_LoadAt(&cell, point, 0);
    return cell.side_height[0] == cell.side_height[1] && cell.side_height[0] == cell.side_height[2] &&
           cell.side_height[0] == cell.side_height[3];
}

/* func_020317c4: whether a step from unit (from_x, from_z) to the neighbouring or same unit
 * (x, z) is open: the target's byte 4 must be set (and with `strict` its byte 0x17 clear); a
 * straight step needs ground at height 0 there; a diagonal one needs that and one of the two
 * units beside the diagonal (the one on the target's X first) at height 0 and level. Units
 * further apart than one on either axis are not neighbours (0). */
int CollisionQuery_CanStep(int from_x, int from_z, int x, int z, u8 strict)
{
    int dx = from_x - x;
    if (dx < 0) {
        dx = -dx;
    }
    if (dx > 1) {
        return 0;
    }
    int dz = from_z - z;
    if (dz < 0) {
        dz = -dz;
    }
    if (dz > 1) {
        return 0;
    }
    if (strict != 0) {
        if (UnitTypeInfo_Byte04At(x, z) == 0 || UnitTypeInfo_HasByte17At(x, z) != 0) {
            return 0;
        }
    } else if (UnitTypeInfo_Byte04At(x, z) == 0) {
        return 0;
    }

    Vec3 from_point = {collision_query_unit_centre(from_x), 0, collision_query_unit_centre(from_z)};
    Vec3 to_point = {collision_query_unit_centre(x), 0, collision_query_unit_centre(z)};
    int steps = dx + dz;
    int target_y = CollisionQuery_GroundY(&to_point, NULL, COLLISION_QUERY_STEP_FLAGS);
    if (steps == 1) {
        return target_y == 0;
    }
    if (steps != 2) {
        return 1;
    }

    Vec3 side_x = {to_point.x, 0, from_point.z};
    if (CollisionQuery_GroundY(&side_x, NULL, COLLISION_QUERY_STEP_FLAGS) == 0 && target_y == 0 &&
        collision_query_is_level(&side_x)) {
        return 1;
    }
    Vec3 side_z = {from_point.x, 0, to_point.z};
    if (CollisionQuery_GroundY(&side_z, NULL, COLLISION_QUERY_STEP_FLAGS) == 0 && target_y == 0 &&
        collision_query_is_level(&side_z)) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020317c4, CollisionQuery_CanStep)

/* func_020319ac: byte 8 of the row of unit (x, z), or 0 when a post stands there (asked of
 * the map's post source, or the default one). */
int CollisionQuery_Byte08IfNoPost(int x, int z)
{
    CollisionPostSource *source = func_02031c50();
    if (source != NULL) {
        fx32 radius;
        fx32 height;
        int kind;
        if (source->vtable->post_at(source, &radius, &height, &kind, x, z) != 0) {
            return 0;
        }
    }
    return UnitTypeInfo_Byte08At(x, z);
}
CLEAN_AS(func_020319ac, CollisionQuery_Byte08IfNoPost)

/* func_020319e4: CollisionQuery_Byte08IfNoPost, or 0 on a unit with path directions. */
int CollisionQuery_Byte08IfFree(int x, int z)
{
    if (CollisionMap_PathDirections(x, z) != 0) {
        return 0;
    }
    return CollisionQuery_Byte08IfNoPost(x, z);
}
CLEAN_AS(func_020319e4, CollisionQuery_Byte08IfFree)

/* func_02031bb8: whether the ground under `position` has a height other than 0 (the ground in
 * mode 0 of the first table set, CollisionGround_GetHeight without posts) or a post stands on
 * its unit (CollisionQuery_PostAt). */
int CollisionQuery_IsRaisedOrPost(const Vec3 *position)
{
    CollisionGround ground;
    fx32 radius;
    fx32 height;
    int kind;
    int result;

    CollisionGround_Init(&ground, position, 0, 0);
    if (CollisionGround_GetHeight(&ground, 0) != 0) {
        result = 1;
    } else {
        result = CollisionQuery_PostAt(position->x >> COLLISION_UNIT_SHIFT, position->z >> COLLISION_UNIT_SHIFT, &radius,
                                       &height, &kind) != 0;
    }
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_02031bb8, CollisionQuery_IsRaisedOrPost)
