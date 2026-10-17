/* Moves of the town's insects (ov003/town_insect.h) that overlay 68 holds, called from the
 * behaviours of their kinds in overlay 3 (ov003/town_insect_kinds.h):
 *
 * - wandering and fleeing (InsectPath_Wander, InsectPath_FleeFrom) and going to a spot
 *   to settle on (InsectPath_FindSpot, InsectPath_GoToSpot): a flower of the town's
 *   map near it whose line suits the kind (kinds 2 and 3 ask more of it), or for kind 0x33 a
 *   point of its own;
 * - kinds 0x36 and 0x37 (both run by func_ov003_02232640), which go for the player once
 *   alarmed (InsectPath_WatchPlayer): they turn to the player and, close enough while the
 *   player is in a state that allows it, make the player react (FieldActor_PlayerRequestState6D,
 *   with 1 for kind 0x37); kind 0x36 hops, and kind 0x37 plays frames 0xb to 0xe of its
 *   animation; out of reach they flee, stop, and calm down (InsectPath_CalmDown);
 * - kinds 0xb and 0x3a (run by func_ov003_02233674), which chase the player
 *   (InsectPath_Chase), circle the player once within 1.0 (action 3) while the player is
 *   asked for state 0x78 (FieldActor_PlayerRequestState78), then fly off and fade away
 *   (InsectPath_CircleOrLeave). */
#ifndef CLEAN_OV068_INSECT_PATHS_H
#define CLEAN_OV068_INSECT_PATHS_H

#include "autoload_2/vector.h"
#include "ov003/town_insect.h"
#include "types.h"

/* TownInsect.action values set here (besides those of town_insect.h). */
#define INSECT_PATH_CIRCLE 3   /* kinds 0xb and 0x3a: circling the player */
#define INSECT_PATH_STOPPED 4  /* kinds 0x36 and 0x37: stopped fleeing */
#define INSECT_PATH_MISSED 5   /* kinds 0x36 and 0x37: the player was out of reach */
#define INSECT_PATH_SETTLED 6  /* on its spot */
#define INSECT_PATH_FLEE 7     /* fleeing; kinds 0xb and 0x3a: flying off */
#define INSECT_PATH_SHOWN 0x12 /* an event insect shown */

void InsectPath_Show(TownInsect *insect);
void InsectPath_FleeFrom(TownInsect *insect, const Vec3 *point);
void InsectPath_Wander(TownInsect *insect, s16 *heading, int step, int period, u8 limit, int scale);
void InsectPath_SpotOffset(int line, Vec3 *spot);
int InsectPath_FindSpot(TownInsect *insect, s16 *turn, int *distance, Vec3 *spot);
int InsectPath_GoToSpot(TownInsect *insect, s16 *heading);
int InsectPath_GoForPlayer(TownInsect *insect, int mode, const Vec3 *player, s16 *counter);
int InsectPath_TurnToPlayer(TownInsect *insect, int mode, const Vec3 *player);
int InsectPath_WatchPlayer(TownInsect *insect, s16 *counter);
void InsectPath_CalmDown(TownInsect *insect, s16 *hop, int result);
void InsectPath_CircleOrLeave(TownInsect *insect);
void InsectPath_Flap(Vec3 *scale, TownInsectModel *model, int turned);
void InsectPath_Chase(TownInsect *insect);

#endif
