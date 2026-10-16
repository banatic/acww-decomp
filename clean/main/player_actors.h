/* Small helpers on the players' field actors (field_actor.h): making a session player's actor,
 * the size and alignment of one in its heap, this console's player's actor (func_02096718(4))
 * giving its player number or playing a sound, and the item cleared where another player's
 * reported state 0x75 starts or ends. */
#ifndef CLEAN_MAIN_PLAYER_ACTORS_H
#define CLEAN_MAIN_PLAYER_ACTORS_H

#include "autoload_2/vector.h"
#include "types.h"

void PlayerActors_Spawn(unsigned int player, const Vec3 *position, const s16 *angle, unsigned int param);
int PlayerActors_FieldActorAlignment(void);
int PlayerActors_FieldActorSize(void);
int PlayerActors_OwnPlayer(void);
void PlayerActors_ClearItemOnState75(int *player, u8 *scene, int *state, int *new_state, int *x, int *z);
int PlayerActors_OwnPlaySound(int number);
void PlayerActors_Nothing(void);

#endif
