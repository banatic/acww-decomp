/* Scenes that one player at a time may enter, decided by the session's host (scene_claim.h). */
#include "scene_claim.h"

#include "clean.h"
#include "main/acre_tile.h" /* AcreTile_SnapToTileCentre */
#include "session.h"
#include "scene_exit.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session_players.h"

static_assert(offsetof(SceneClaimExit, next_tile) == 0x10, "SceneClaimExit.next_tile is at 0x10");
static_assert(offsetof(SceneClaimExit, angle) == 0x1c, "SceneClaimExit.angle is at 0x1c");
static_assert(offsetof(SceneClaimExit, placed) == 0x20, "SceneClaimExit.placed is at 0x20");
static_assert(sizeof(SceneClaimExit) == 0x24, "SceneClaimExit is 0x24 bytes");
static_assert(sizeof(SceneClaimRoom) == 2, "SceneClaimRoom is 2 bytes");

/* The session messages. */
#define SCENE_CLAIM_MSG_REQUEST 0x33 /* to the host: the scene */
#define SCENE_CLAIM_MSG_ANSWER 0x34  /* to the asking slot: nonzero when given */
#define SCENE_CLAIM_MSG_RELEASE 0x35 /* to the host: the scene */

#define HOST_SLOT 0
#define NO_SLOT 4 /* NetSession.local_slot without a slot */
#define MASK_SLOTS 4

#define NO_EXIT (-1)
#define THIS_PLAYER 4    /* what func_020961a8 takes for this console's player */
#define TILE_SIZE 0x2000 /* fx32: one tile */

extern NetSession *data_020ccf94; /* the session */
extern u8 data_020e54a8;
extern const SceneClaimRoom data_020d1ad8[SCENE_CLAIM_ROOMS];
extern SceneClaimExit data_021dc6e8;
extern SceneClaimMask data_021dc70c[SCENE_CLAIM_SCENES];
extern const Vec3 data_021fbee8; /* (0, 0, 0) */

/* The part of a player's actor read here (what func_020961a8 gives). */
typedef struct SceneClaimPlayer {
    u8 unk_00[0x5c];
    Vec3 position; /* 0x5c */
    u8 unk_68[0x26];
    s16 angle; /* 0x8e */
} SceneClaimPlayer;
static_assert(offsetof(SceneClaimPlayer, angle) == 0x8e, "SceneClaimPlayer.angle is at 0x8e");

/* The element destructor handed to __cxa_vec_cleanup (SceneClaimMask_Destruct's). */
extern void func_0209d934(void *mask);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* Whether claims are decided here: the session is not linked or this system is the host. */
static int decides_here(NetSession *session)
{
    return !Session_IsLinked(session) || Session_IsLocalSlot(session, HOST_SLOT);
}

/* A one-byte message to `slot`. */
static void send_byte(u8 value, u32 handler, u32 slot)
{
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, &value, 1);
    Session_EndMessage(session, handler, slot);
}

/* ---- The claims */

/* func_0209d484 (message 0x35, on the host): `slot` leaves `*scene`. */
void SceneClaim_ReceiveRelease(const unsigned char *scene, int slot)
{
    SceneClaimMasks_Remove(data_021dc70c, *scene, slot);
}
CLEAN_AS(func_0209d484, SceneClaim_ReceiveRelease)

/* func_0209d498 (message 0x34): the host's answer. */
void SceneClaim_ReceiveAnswer(unsigned char *given)
{
    SceneClaimExit_SetAnswer(&data_021dc6e8, *given != 0 ? SCENE_CLAIM_GIVEN : SCENE_CLAIM_REFUSED);
}
CLEAN_AS(func_0209d498, SceneClaim_ReceiveAnswer)

/* func_0209d4c0 (message 0x33, on the host): `*scene` given to `slot` unless another slot is
 * in it, and the answer sent to `slot`.
 * QUIRK: a scene of 0x33 or more is answered as given (and nothing is noted). */
void SceneClaim_ReceiveRequest(unsigned char *scene, int slot)
{
    u8 wanted = *scene;
    u8 given;
    if ((unsigned int) SceneClaimMasks_CountWith(data_021dc70c, wanted, slot) <= 1) {
        SceneClaimMasks_Add(data_021dc70c, wanted, slot);
        given = 1;
    } else {
        given = 0;
    }
    send_byte(given, SCENE_CLAIM_MSG_ANSWER, (u32) slot);
}
CLEAN_AS(func_0209d4c0, SceneClaim_ReceiveRequest)

/* func_0209d51c (at each change of scene): the exit being taken cleared; with data_020e54a8 at
 * 1, coming from a claimed scene into the scene its exit leads to lets slot 0's claim on it go
 * (slot 0: this system's where claims are decided here; elsewhere the host is asked, and lets
 * the sender's go). */
void SceneClaim_Leave(void)
{
    SceneClaimExit_Clear(&data_021dc6e8);
    if (data_020e54a8 != 1) {
        return;
    }
    u8 scene = SceneQuery_Current();
    u8 before = SceneQuery_Previous();
    for (unsigned int i = 0; i < SCENE_CLAIM_ROOMS; i++) {
        if (scene == data_020d1ad8[i].exit_to && before == data_020d1ad8[i].scene) {
            SceneClaim_Release(before, HOST_SLOT);
        }
    }
}
CLEAN_AS(func_0209d51c, SceneClaim_Leave)

/* func_0209d57c: `slot` leaves `scene`: at once where claims are decided here or this system
 * has no slot, else by asking the host (message 0x35; the host takes the sender's slot). */
void SceneClaim_Release(unsigned char scene, int slot)
{
    NetSession *session = data_020ccf94;
    if (decides_here(session) || Session_IsLocalSlot(session, NO_SLOT)) {
        SceneClaimMasks_Remove(data_021dc70c, scene, slot);
        return;
    }
    send_byte(scene, SCENE_CLAIM_MSG_RELEASE, HOST_SLOT);
}
CLEAN_AS(func_0209d57c, SceneClaim_Release)

/* func_0209d5e8: the exit being taken. */
int SceneClaim_Exit(void)
{
    return (int) (uintptr_t) &data_021dc6e8;
}
CLEAN_AS(func_0209d5e8, SceneClaim_Exit)

/* func_0209d5f0: starts taking exit `exit` of the scene for this console's player: its answer
 * set to waiting, then, when the exit and the player are there, the exit noted (with the
 * exit's own position and angle when its byte 0x18 is set, else the player's) and its scene
 * claimed for slot 0 or asked of the host (message 0x33). 0 when the exit or the player is
 * missing, else 1. */
int SceneClaim_TakeExit(int exit)
{
    SceneClaimPlayer *player = SessionPlayers_ActorOf(THIS_PLAYER);
    u8 scene;
    u8 unk_14;
    u8 unk_15;
    s16 unused_angle;
    Vec3 unused_position;
    int unk_10;
    int found = SceneExit_Resolve((const SceneExit *) (uintptr_t) SceneTables_EntryRecord(), exit, &scene, &unused_position,
                                  &unk_10, &unused_angle, &unk_14, &unk_15, NULL, NULL);
    SceneClaimExit_SetAnswer(&data_021dc6e8, SCENE_CLAIM_WAITING);
    if (found == 0 || player == NULL) {
        return 0;
    }

    Vec3 from = player->position;
    s16 player_angle = player->angle;
    int placed;
    s16 exit_angle;
    Vec3 exit_position;
    SceneExit_DoorInfo((const SceneExit *) (uintptr_t) SceneTables_EntryRecord(), exit, &placed, &exit_angle);
    SceneExit_DoorPoint((const SceneExit *) (uintptr_t) SceneTables_EntryRecord(), exit, &exit_position, &from);

    SceneClaimExit_SetExit(&data_021dc6e8, exit);
    SceneClaimExit_SetPlaced(&data_021dc6e8, (unsigned char) placed);
    SceneClaimExit_SetScene(&data_021dc6e8, scene);
    if (placed != 0) {
        SceneClaimExit_SetPosition(&data_021dc6e8, &exit_position);
        SceneClaimExit_SetAngle(&data_021dc6e8, exit_angle);
    } else {
        SceneClaimExit_SetPosition(&data_021dc6e8, &from);
        SceneClaimExit_SetAngle(&data_021dc6e8, player_angle);
    }
    /* The tile after the player's along z; AcreTile_SnapToTileCentre leaves the height 0. */
    Vec3 next_tile = from;
    next_tile.z = from.z + TILE_SIZE;
    AcreTile_SnapToTileCentre(&next_tile, &next_tile);
    next_tile.x = from.x;
    SceneClaimExit_SetNextTile(&data_021dc6e8, &next_tile);

    if (!SceneClaim_IsClaimed(scene)) {
        SceneClaimExit_SetAnswer(&data_021dc6e8, SCENE_CLAIM_GIVEN);
        return 1;
    }
    if (decides_here(data_020ccf94)) {
        if ((unsigned int) SceneClaimMasks_CountWith(data_021dc70c, scene, HOST_SLOT) <= 1) {
            SceneClaimMasks_Add(data_021dc70c, scene, HOST_SLOT);
            SceneClaimExit_SetAnswer(&data_021dc6e8, SCENE_CLAIM_GIVEN);
        } else {
            SceneClaimExit_SetAnswer(&data_021dc6e8, SCENE_CLAIM_REFUSED);
        }
        return 1;
    }
    send_byte(scene, SCENE_CLAIM_MSG_REQUEST, HOST_SLOT);
    return 1;
}
CLEAN_AS(func_0209d5f0, SceneClaim_TakeExit)

/* func_0209d780: whether exit `exit` of the scene leads to a scene that needs a claim. */
int SceneClaim_IsClaimedExit(int exit)
{
    u8 scene;
    u8 unk_14;
    u8 unk_15;
    s16 angle;
    Vec3 position;
    int unk_10;
    if (SceneExit_Resolve((const SceneExit *) (uintptr_t) SceneTables_EntryRecord(), exit, &scene, &position, &unk_10, &angle,
                          &unk_14, &unk_15, NULL, NULL) == 0) {
        return 0;
    }
    return SceneClaim_IsClaimed(scene);
}
CLEAN_AS(func_0209d780, SceneClaim_IsClaimedExit)

/* func_0209d7c8: whether `scene` needs a claim. */
int SceneClaim_IsClaimed(int scene)
{
    for (unsigned int i = 0; i < SCENE_CLAIM_ROOMS; i++) {
        if (scene == data_020d1ad8[i].scene) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0209d7c8, SceneClaim_IsClaimed)

/* func_0209d7e8: the exit being taken cleared and every scene emptied. */
void SceneClaim_Reset(void)
{
    SceneClaimExit_Clear(&data_021dc6e8);
    SceneClaimMasks_Clear((char *) data_021dc70c);
}
CLEAN_AS(func_0209d7e8, SceneClaim_Reset)

/* ---- The exit being taken */

/* func_0209d808: copied a word at a time, x first (so an overlapping `next_tile` is read as
 * it is overwritten). */
void SceneClaimExit_SetNextTile(SceneClaimExit *target, const Vec3 *next_tile)
{
    target->next_tile.x = next_tile->x;
    target->next_tile.y = next_tile->y;
    target->next_tile.z = next_tile->z;
}
CLEAN_AS(func_0209d808, SceneClaimExit_SetNextTile)

/* func_0209d818 */
void SceneClaimExit_SetAngle(SceneClaimExit *target, int angle)
{
    target->angle = (u16) angle;
}
CLEAN_AS(func_0209d818, SceneClaimExit_SetAngle)

/* func_0209d81c: copied a word at a time, x first. */
void SceneClaimExit_SetPosition(SceneClaimExit *target, const Vec3 *position)
{
    target->position.x = position->x;
    target->position.y = position->y;
    target->position.z = position->z;
}
CLEAN_AS(func_0209d81c, SceneClaimExit_SetPosition)

/* func_0209d82c */
void SceneClaimExit_SetScene(SceneClaimExit *target, int scene)
{
    target->scene = (u8) scene;
}
CLEAN_AS(func_0209d82c, SceneClaimExit_SetScene)

/* func_0209d830 */
void SceneClaimExit_SetPlaced(SceneClaimExit *target, unsigned char placed)
{
    target->placed = placed;
}
CLEAN_AS(func_0209d830, SceneClaimExit_SetPlaced)

/* func_0209d838 */
void SceneClaimExit_SetExit(SceneClaimExit *target, int exit)
{
    target->exit = (u8) exit;
}
CLEAN_AS(func_0209d838, SceneClaimExit_SetExit)

/* func_0209d83c */
void SceneClaimExit_SetAnswer(SceneClaimExit *target, int answer)
{
    target->answer = (u8) answer;
}
CLEAN_AS(func_0209d83c, SceneClaimExit_SetAnswer)

/* func_0209d840: the address of next_tile. */
int SceneClaimExit_NextTile(SceneClaimExit *target)
{
    return (int) (uintptr_t) &target->next_tile;
}
CLEAN_AS(func_0209d840, SceneClaimExit_NextTile)

/* func_0209d844: the address of position. */
int SceneClaimExit_Position(SceneClaimExit *target)
{
    return (int) (uintptr_t) &target->position;
}
CLEAN_AS(func_0209d844, SceneClaimExit_Position)

/* func_0209d848 */
unsigned char SceneClaimExit_Placed(SceneClaimExit *target)
{
    return target->placed;
}
CLEAN_AS(func_0209d848, SceneClaimExit_Placed)

/* func_0209d850 */
int SceneClaimExit_Answer(SceneClaimExit *target)
{
    return target->answer;
}
CLEAN_AS(func_0209d850, SceneClaimExit_Answer)

/* func_0209d854: no exit: answered as given, number 0xff, at (0, 0, 0). */
void SceneClaimExit_Clear(SceneClaimExit *target)
{
    SceneClaimExit_SetAnswer(target, SCENE_CLAIM_GIVEN);
    SceneClaimExit_SetExit(target, NO_EXIT);
    SceneClaimExit_SetPlaced(target, 0);
    SceneClaimExit_SetScene(target, 0);
    SceneClaimExit_SetPosition(target, &data_021fbee8);
    SceneClaimExit_SetAngle(target, 0);
    SceneClaimExit_SetNextTile(target, &data_021fbee8);
}
CLEAN_AS(func_0209d854, SceneClaimExit_Clear)

/* func_0209d89c: the exit's destructor: nothing. */
void SceneClaimExit_Destruct(void *target)
{
    (void) target;
}
CLEAN_AS(func_0209d89c, SceneClaimExit_Destruct)

/* func_0209d8a0: the exit's constructor: cleared. */
int SceneClaimExit_Construct(SceneClaimExit *target)
{
    SceneClaimExit_Clear(target);
    return (int) (uintptr_t) target;
}
CLEAN_AS(func_0209d8a0, SceneClaimExit_Construct)

/* ---- The masks of the slots in each scene */

/* func_0209d8b0: how many slots would be in `scene` with `slot` added; 0 for a scene of 0x33
 * or more. */
int SceneClaimMasks_CountWith(SceneClaimMask *masks, unsigned int scene, int slot)
{
    if (scene >= SCENE_CLAIM_SCENES) {
        return 0;
    }
    return SceneClaimMask_CountWith(&masks[scene].slots, slot);
}
CLEAN_AS(func_0209d8b0, SceneClaimMasks_CountWith)

/* func_0209d8cc: `slot` leaves `scene`; nothing for a scene of 0x33 or more. */
void SceneClaimMasks_Remove(SceneClaimMask *masks, unsigned int scene, int slot)
{
    if (scene >= SCENE_CLAIM_SCENES) {
        return;
    }
    SceneClaimMask_Remove(&masks[scene].slots, slot);
}
CLEAN_AS(func_0209d8cc, SceneClaimMasks_Remove)

/* func_0209d8e4: `slot` enters `scene`; nothing for a scene of 0x33 or more. */
void SceneClaimMasks_Add(SceneClaimMask *masks, unsigned int scene, int slot)
{
    if (scene >= SCENE_CLAIM_SCENES) {
        return;
    }
    SceneClaimMask_Add(&masks[scene].slots, slot);
}
CLEAN_AS(func_0209d8e4, SceneClaimMasks_Add)

/* func_0209d8fc: every scene empty. */
void SceneClaimMasks_Clear(char *masks)
{
    for (unsigned int i = 0; i < SCENE_CLAIM_SCENES; i++) {
        SceneClaimMask_Clear((SceneClaimMask *) (void *) &masks[i]);
    }
}
CLEAN_AS(func_0209d8fc, SceneClaimMasks_Clear)

/* func_0209d918: how many slots the mask would hold with `slot` added. */
int SceneClaimMask_CountWith(unsigned char *mask, int slot)
{
    unsigned char with = *mask;
    SceneClaimMask_Add(&with, slot);
    return SceneClaimMask_Count(&with);
}
CLEAN_AS(func_0209d918, SceneClaimMask_CountWith)

/* func_0209d934: a mask's destructor: nothing. */
void SceneClaimMask_Destruct(void *mask)
{
    (void) mask;
}
CLEAN_AS(func_0209d934, SceneClaimMask_Destruct)

/* func_0209d938: how many slots the mask holds. */
int SceneClaimMask_Count(void *mask)
{
    int count = 0;
    for (unsigned int slot = 0; slot < MASK_SLOTS; slot++) {
        if (SceneClaimMask_Has(mask, (int) slot)) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0209d938, SceneClaimMask_Count)

/* func_0209d95c: whether the mask holds `slot`.
 * QUIRK: the slot is taken modulo 4, here and when a slot is added or removed. */
int SceneClaimMask_Has(const unsigned char *mask, int slot)
{
    return (*mask >> (slot & 3)) & 1;
}
CLEAN_AS(func_0209d95c, SceneClaimMask_Has)

/* func_0209d970 */
void SceneClaimMask_Remove(unsigned char *mask, int slot)
{
    *mask = (unsigned char) (*mask & ~(1u << (slot & 3)));
}
CLEAN_AS(func_0209d970, SceneClaimMask_Remove)

/* func_0209d988 */
void SceneClaimMask_Add(unsigned char *mask, int slot)
{
    *mask = (unsigned char) (*mask | (1u << (slot & 3)));
}
CLEAN_AS(func_0209d988, SceneClaimMask_Add)

/* func_0209d9a0 */
void SceneClaimMask_Clear(SceneClaimMask *mask)
{
    mask->slots = 0;
}
CLEAN_AS(func_0209d9a0, SceneClaimMask_Clear)

/* func_0209d9a8: the masks' array destructor. */
void *SceneClaimMasks_Destruct(void *masks)
{
    __cxa_vec_cleanup(masks, SCENE_CLAIM_SCENES, sizeof(SceneClaimMask), func_0209d934);
    return masks;
}
CLEAN_AS(func_0209d9a8, SceneClaimMasks_Destruct)

/* func_0209d9c4: a mask's constructor: empty. */
void *SceneClaimMask_Construct(void *mask)
{
    SceneClaimMask_Clear(mask);
    return mask;
}
CLEAN_AS(func_0209d9c4, SceneClaimMask_Construct)
