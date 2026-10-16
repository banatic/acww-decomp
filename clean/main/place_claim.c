/* Places claimed in a room, decided by the session's host (place_claim.h). */
#include "place_claim.h"

#include "clean.h"
#include "session.h"

static_assert(sizeof(PlaceClaim) == 20, "PlaceClaim size");
static_assert(offsetof(PlaceClaim, scene) == 0x10, "PlaceClaim scene");
static_assert(sizeof(PlaceClaimRequest) == 3, "PlaceClaimRequest size");

extern NetSession *data_020ccf94; /* the session */
extern u32 data_021c8750;         /* PlaceClaimAnswer */
extern PlaceClaim data_021c87fc[PLACE_CLAIM_SLOTS];

#define HOST_SLOT 0
#define NO_SLOT 4 /* NetSession.local_slot without a slot */

/* The point's x and z in a request are in units of 0x200. */
#define REQUEST_SHIFT 9

extern u8 func_020b65c4(void); /* the scene */
/* Gives `slot` the claim of `point` in `scene` unless another slot holds one too near; whether
 * it did. */
extern int func_02053380(PlaceClaim *claims, int slot, int scene, const Vec3 *point);
/* Lets `slot`'s claim go (nothing for slot 4 or above); whether it did. */
extern int func_0205340c(PlaceClaim *claims, int slot);

/* Whether claims are decided here: the session is not linked or this system is the host. */
static int decides_here(NetSession *session)
{
    return !Session_IsLinked(session) || Session_IsLocalSlot(session, HOST_SLOT);
}

/* func_02051dfc (for func_ov004_0222b540) */
unsigned int PlaceClaim_Answer1(void)
{
    return PlaceClaim_Answer();
}
CLEAN_AS(func_02051dfc, PlaceClaim_Answer1)

/* func_02051e04 (for func_ov004_0222b5e0) */
void PlaceClaim_Request1(const Vec3 *point)
{
    PlaceClaim_Request(point);
}
CLEAN_AS(func_02051e04, PlaceClaim_Request1)

/* func_02051e0c (for func_ov004_0222b814): lets slot 0's claim go. */
void PlaceClaim_ReleaseSlot0(void)
{
    PlaceClaim_Release(HOST_SLOT);
}
CLEAN_AS(func_02051e0c, PlaceClaim_ReleaseSlot0)

/* func_02051e18 (for func_ov004_0222ba44) */
unsigned int PlaceClaim_Answer2(void)
{
    return PlaceClaim_Answer();
}
CLEAN_AS(func_02051e18, PlaceClaim_Answer2)

/* func_02051e20 (for func_ov004_0222bb0c) */
void PlaceClaim_Request2(const Vec3 *point)
{
    PlaceClaim_Request(point);
}
CLEAN_AS(func_02051e20, PlaceClaim_Request2)

/* func_02051e28 (for func_ov004_0222aff0) */
unsigned int PlaceClaim_Answer3(void)
{
    return PlaceClaim_Answer();
}
CLEAN_AS(func_02051e28, PlaceClaim_Answer3)

/* func_02051e30 (for func_ov004_0222b0fc) */
void PlaceClaim_Request3(const Vec3 *point)
{
    PlaceClaim_Request(point);
}
CLEAN_AS(func_02051e30, PlaceClaim_Request3)

/* func_02051e38: forgets the answer and lets `slot`'s claim go: on a linked system that is not
 * the host but has a slot, by asking the host (message 33, for this system's slot; `slot` is
 * not sent), else at once. */
void PlaceClaim_Release(int slot)
{
    NetSession *session = data_020ccf94;
    data_021c8750 = PLACE_CLAIM_WAITING;
    if (decides_here(session) || Session_IsLocalSlot(session, NO_SLOT)) {
        func_0205340c(data_021c87fc, slot);
        return;
    }
    session = data_020ccf94;
    Session_BeginMessage(session);
    Session_EndMessage(session, PLACE_CLAIM_MSG_RELEASE, HOST_SLOT);
}
CLEAN_AS(func_02051e38, PlaceClaim_Release)

/* func_02051e9c (for func_ov004_022288c8) */
unsigned int PlaceClaim_Answer4(void)
{
    return PlaceClaim_Answer();
}
CLEAN_AS(func_02051e9c, PlaceClaim_Answer4)

/* func_02051ea4 (for func_ov004_022289b8) */
void PlaceClaim_Request4(const Vec3 *point)
{
    PlaceClaim_Request(point);
}
CLEAN_AS(func_02051ea4, PlaceClaim_Request4)

/* func_02051eac: PlaceClaimAnswer. */
unsigned int PlaceClaim_Answer(void)
{
    return data_021c8750;
}
CLEAN_AS(func_02051eac, PlaceClaim_Answer)

/* func_02051eb8: asks for `point` in the current scene. Where claims are decided here it is
 * claimed for slot 0 at once and answered; otherwise the host is asked (message 30) and the
 * answer waits for its reply.
 * QUIRK: the host gets x and z divided by 0x200 and cut to 8 bits, and y as 0. */
void PlaceClaim_Request(const Vec3 *point)
{
    NetSession *session = data_020ccf94;
    data_021c8750 = PLACE_CLAIM_WAITING;
    if (decides_here(session)) {
        if (func_02053380(data_021c87fc, HOST_SLOT, func_020b65c4(), point)) {
            data_021c8750 = PLACE_CLAIM_GIVEN;
        } else {
            data_021c8750 = PLACE_CLAIM_REFUSED;
        }
        return;
    }
    PlaceClaimRequest request;
    request.x = (u8) (point->x >> REQUEST_SHIFT);
    request.z = (u8) (point->z >> REQUEST_SHIFT);
    request.scene = func_020b65c4();
    session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &request, sizeof(request));
    Session_EndMessage(session, PLACE_CLAIM_MSG_REQUEST, HOST_SLOT);
}
CLEAN_AS(func_02051eb8, PlaceClaim_Request)

/* func_020528d4 (message 33, on the host): lets the sender's claim go; whether it did. */
void *PlaceClaim_ReceiveRelease(int slot)
{
    return (void *) (intptr_t) func_0205340c(data_021c87fc, slot);
}
CLEAN_AS(func_020528d4, PlaceClaim_ReceiveRelease)

/* func_020528e4 (messages 31 and 32): the host's answer. */
void PlaceClaim_ReceiveAnswer(int given)
{
    data_021c8750 = given ? PLACE_CLAIM_GIVEN : PLACE_CLAIM_REFUSED;
}
CLEAN_AS(func_020528e4, PlaceClaim_ReceiveAnswer)

/* func_020528fc (message 30, on the host): claims the requested point for the sender's slot and
 * answers that slot with message 31 or 32. */
void PlaceClaim_ReceiveRequest(const PlaceClaimRequest *request, int slot)
{
    Vec3 point = {
        .x = request->x << REQUEST_SHIFT,
        .y = 0,
        .z = request->z << REQUEST_SHIFT,
    };
    int given = func_02053380(data_021c87fc, slot, request->scene, &point);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_EndMessage(session, given ? PLACE_CLAIM_MSG_GIVEN : PLACE_CLAIM_MSG_REFUSED, (u32) slot);
}
CLEAN_AS(func_020528fc, PlaceClaim_ReceiveRequest)

#include "itcm/vector.h"

/* A claim keeps the others away within this squared distance (Vec_DistanceSquared). */
#define PLACE_CLAIM_MIN_DISTANCE_SQUARED 0x2400

extern void func_02053498(void *claim); /* a claim's destructor, handed to __cxa_vec_cleanup */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_02053380: gives `slot` the claim of `point` in `scene` unless another slot holds one too
 * near (PlaceClaim_IsFree); whether it did. */
int PlaceClaim_Claim(PlaceClaim *claims, int slot, int scene, const Vec3 *point)
{
    if (!PlaceClaim_IsFree(claims, slot, (u8) scene, point)) {
        return 0;
    }
    return PlaceClaim_Set(claims, slot, scene, point);
}
CLEAN_AS(func_02053380, PlaceClaim_Claim)

/* func_020533ac: whether no slot but `slot` holds a point in `scene` at a squared distance below
 * PLACE_CLAIM_MIN_DISTANCE_SQUARED from `point`; 0 for a slot of 4 or more. */
int PlaceClaim_IsFree(PlaceClaim *claims, int slot, u8 scene, const Vec3 *point)
{
    if (slot >= PLACE_CLAIM_SLOTS) {
        return 0;
    }
    for (int i = 0; i < PLACE_CLAIM_SLOTS; i++) {
        const PlaceClaim *claim = &claims[i];
        if (i == slot || !claim->held || claim->scene != scene) {
            continue;
        }
        if (Vec_DistanceSquared(&claim->point, point) < PLACE_CLAIM_MIN_DISTANCE_SQUARED) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020533ac, PlaceClaim_IsFree)

/* func_0205340c: lets `slot`'s claim go; 0 (and nothing done) for a slot of 4 or more.
 * REQUIRES: slot is not negative (the ROM would clear a byte before the claims). */
int PlaceClaim_Free(PlaceClaim *claims, int slot)
{
    if (slot >= PLACE_CLAIM_SLOTS) {
        return 0;
    }
    return PlaceClaim_Drop(&claims[slot]);
}
CLEAN_AS(func_0205340c, PlaceClaim_Free)

/* func_02053428: `slot` holds `point` in `scene`.
 * QUIRK: a slot of 4 or more is not stored but still answers 1.
 * REQUIRES: slot is not negative (the ROM would write before the claims). */
int PlaceClaim_Set(PlaceClaim *claims, int slot, int scene, const Vec3 *point)
{
    if (slot >= PLACE_CLAIM_SLOTS) {
        return 1;
    }
    return PlaceClaim_Hold(&claims[slot], (u8) scene, point);
}
CLEAN_AS(func_02053428, PlaceClaim_Set)

/* func_02053448: the claim is no longer held (the point and scene stay); 1. */
int PlaceClaim_Drop(PlaceClaim *claim)
{
    claim->held = 0;
    return 1;
}
CLEAN_AS(func_02053448, PlaceClaim_Drop)

/* func_02053450: the claim is held, of `point` in `scene`; 1. The point is copied one
 * coordinate at a time after `held` is set, as the original does. */
int PlaceClaim_Hold(PlaceClaim *claim, u8 scene, const Vec3 *point)
{
    claim->held = 1;
    claim->point.x = point->x;
    claim->point.y = point->y;
    claim->point.z = point->z;
    claim->scene = scene;
    return 1;
}
CLEAN_AS(func_02053450, PlaceClaim_Hold)

/* func_0205346c: not held, at (0, 0, 0) in scene 0 (the padding is left alone). */
void PlaceClaim_Clear(PlaceClaim *claim)
{
    claim->held = 0;
    claim->point.x = 0;
    claim->point.y = 0;
    claim->point.z = 0;
    claim->scene = 0;
}
CLEAN_AS(func_0205346c, PlaceClaim_Clear)

/* func_0205347c: the destructor of the slots' claims: each claim's (func_02053498, handed to
 * __cxa_vec_cleanup). */
PlaceClaim *PlaceClaim_DestructAll(PlaceClaim *claims)
{
    __cxa_vec_cleanup(claims, PLACE_CLAIM_SLOTS, sizeof(PlaceClaim), func_02053498);
    return claims;
}
CLEAN_AS(func_0205347c, PlaceClaim_DestructAll)

/* func_02053498: nothing to take down. */
void PlaceClaim_Destruct(PlaceClaim *claim)
{
    (void) claim;
}
CLEAN_AS(func_02053498, PlaceClaim_Destruct)

/* func_0205349c: a claim starts cleared. */
PlaceClaim *PlaceClaim_Construct(PlaceClaim *claim)
{
    PlaceClaim_Clear(claim);
    return claim;
}
CLEAN_AS(func_0205349c, PlaceClaim_Construct)
