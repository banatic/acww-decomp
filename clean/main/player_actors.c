/* Small helpers on the players' field actors (player_actors.h). */
#include "player_actors.h"

#include "actor.h"
#include "actor_table.h"
#include "clean.h"
#include "field_actor.h"
#include "scene_query.h"
#include "town_tile_put.h"

/* The field actor's class, and how its argument carries the player. */
#define PLAYER_ACTORS_PROFILE 9
#define PLAYER_ACTORS_PLAYER_SHIFT 30
#define PLAYER_ACTORS_PLAYER_MASK 0xc0000000u
#define PLAYER_ACTORS_PARAM_MASK 0x3fffffffu

/* Where the field actors live: their heap's blocks are aligned to 4, and one is 0xca0 bytes. */
#define PLAYER_ACTORS_ALIGNMENT 4
#define PLAYER_ACTORS_SIZE 0xca0

/* func_02096718's player for this console's player. */
#define PLAYER_ACTORS_OWN 4

/* The reported state whose start or end clears an item (state 0x75 ends state 0x74 with a
 * splash, ov003/field_actor.c), the item put in its place and the scene it is put in. */
#define PLAYER_ACTORS_STATE_75 0x75
#define PLAYER_ACTORS_NO_ITEM 0xfff1
#define PLAYER_ACTORS_TOWN_SCENE 0

/* The field actor of session player `player` (4: this console's), or NULL; its player number is
 * the word at 0x800. */
typedef struct PlayerActorsFieldActor {
    u8 unk_000[0x800];
    int player; /* 0x800 */
} PlayerActorsFieldActor;

extern PlayerActorsFieldActor *func_02096718(int player);
/* Whether session player `player` has a field actor's process. */
extern void *func_020961a8(int player);
/* Whether session player `player`'s field actor is in state `state` (word 0x7f0). */
extern int func_020960f8(int state, int player);

/* func_020952ac: session player `player`'s field actor made at `position` and `angle`, its
 * argument the player in the top two bits and `param` in the others. */
void PlayerActors_Spawn(unsigned int player, const Vec3 *position, const s16 *angle, unsigned int param)
{
    unsigned int group =
        ((player << PLAYER_ACTORS_PLAYER_SHIFT) & PLAYER_ACTORS_PLAYER_MASK) | (param & PLAYER_ACTORS_PARAM_MASK);
    Actor_Spawn(PLAYER_ACTORS_PROFILE, (int) group, position, angle, NULL);
}
CLEAN_AS(func_020952ac, PlayerActors_Spawn)

/* func_020952e0: the alignment of a field actor in its heap. */
int PlayerActors_FieldActorAlignment(void)
{
    return PLAYER_ACTORS_ALIGNMENT;
}
CLEAN_AS(func_020952e0, PlayerActors_FieldActorAlignment)

/* func_020952e4: the size of a field actor. */
int PlayerActors_FieldActorSize(void)
{
    return PLAYER_ACTORS_SIZE;
}
CLEAN_AS(func_020952e4, PlayerActors_FieldActorSize)

/* func_020952ec: the player number of this console's player's field actor.
 * REQUIRES: the actor exists (it is not checked for NULL). */
int PlayerActors_OwnPlayer(void)
{
    return func_02096718(PLAYER_ACTORS_OWN)->player;
}
CLEAN_AS(func_020952ec, PlayerActors_OwnPlayer)

/* func_02095304: from what session player `*player` reported (its scene, its new state and its
 * point) against the state recorded for it before: in the current scene, when the player left
 * state 0x75 and this console's actor of it is not still in that state, and elsewhere, when the
 * player entered state 0x75, the item on the town's tile at the point is taken away. */
void PlayerActors_ClearItemOnState75(int *player, u8 *scene, int *state, int *new_state, int *x, int *z)
{
    if (*scene == SceneQuery_Current()) {
        if (*state != PLAYER_ACTORS_STATE_75 || *new_state == PLAYER_ACTORS_STATE_75) {
            return;
        }
        if (func_020961a8(*player) != NULL && func_020960f8(PLAYER_ACTORS_STATE_75, *player) != 0) {
            return;
        }
    } else {
        if (*new_state != PLAYER_ACTORS_STATE_75 || *state == PLAYER_ACTORS_STATE_75) {
            return;
        }
    }

    Position at = {.x = *x, .y = 0, .z = *z};
    int tile_x;
    int tile_z;
    Position_Tile(&tile_x, &tile_z, &at);
    TownTilePut_OnScene(PLAYER_ACTORS_TOWN_SCENE, tile_x, tile_z, PLAYER_ACTORS_NO_ITEM, 0);
}
CLEAN_AS(func_02095304, PlayerActors_ClearItemOnState75)

/* func_02095380: sound `number` played by this console's player's field actor; 0 without it,
 * else the sound's answer. */
int PlayerActors_OwnPlaySound(int number)
{
    PlayerActorsFieldActor *actor = func_02096718(PLAYER_ACTORS_OWN);
    if (actor == NULL) {
        return 0;
    }
    return FieldActor_PlaySound((struct FieldActor *) (void *) actor, number);
}
CLEAN_AS(func_02095380, PlayerActors_OwnPlaySound)

/* func_0209539c: does nothing. */
void PlayerActors_Nothing(void) {}
CLEAN_AS(func_0209539c, PlayerActors_Nothing)
