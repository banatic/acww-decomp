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

/* The behaviours of more kinds, run from their groups' updates in overlay 3:
 *
 * - kinds 0xb and 0x3a once more: action 4 (InsectPath_StartGrow) leaves it a speck facing the
 *   player, and action 2 (InsectPath_Grow) grows it and lowers it to 2.5 before the chase
 *   starts (action 0) with music 0x3f;
 * - kind 0x32, action 0: it follows the player (InsectPath_FollowPlayer);
 * - kind 0x35: it sways in place (action 0x12, InsectPath_Sway) and is knocked aside by the
 *   player striking its tile (action 0x13, InsectPath_KnockedAside);
 * - kind 0x23: it circles a loose snowball (action 4, InsectPath_CircleSnowball) and rests on
 *   the ground (action 5, InsectPath_Rest);
 * - kinds 0xa and 0x33, action 0: it roams and goes to its spot (InsectPath_Roam);
 * - kind 8: it hovers about (action 0, InsectPath_Hover) and makes for a building's tile
 *   (action 7, InsectPath_ToBuilding, by InsectPath_NearestBuildingTile);
 * - kinds 0x15-0x17: a perch on a tile of item 0x500a or 0xe3-0xe7 next to it
 *   (InsectPath_FindPerch, action 0xe) and the way down to it (action 4,
 *   InsectPath_GoToPerch);
 * - kind 0x19: it picks a heading (actions 3 and 0xf, InsectPath_PickHeading), glides along it
 *   within its box (action 4, InsectPath_Glide) and turns from what stands ahead
 *   (InsectPath_TurnFromObstacle);
 * - outside a session, the alarm counted from this console's player and the other actors
 *   (InsectPath_SensePlayers, InsectPath_Alarm). */
#define INSECT_PATH_GROWING 2    /* kinds 0xb and 0x3a: growing before the chase */
#define INSECT_PATH_EMERGING 4   /* kinds 0xb and 0x3a: about to grow */
#define INSECT_PATH_LEAVE 9      /* off and away (overlay 3's flight, func_ov003_02230e18) */
#define INSECT_PATH_PERCHING 0xe /* kinds 0x15-0x17: a perch found */
#define INSECT_PATH_TURNING 0xf  /* kind 0x19: turning to unk_240 */

void InsectPath_StretchScale(Vec3 *scale, int stretch);
void InsectPath_Grow(TownInsect *insect);
void InsectPath_StartGrow(TownInsect *insect);
void InsectPath_FollowPlayer(TownInsect *insect, s16 *phase);
int InsectPath_Sway(TownInsect *insect);
int InsectPath_KnockedAside(TownInsect *insect);
void InsectPath_CircleSnowball(TownInsect *insect);
void InsectPath_Rest(TownInsect *insect);
void InsectPath_Roam(TownInsect *insect);
int InsectPath_NearestBuildingTile(TownInsect *insect, Vec3 *tile);
int InsectPath_ToBuilding(TownInsect *insect, s16 *frames, Vec3 *step);
void InsectPath_Hover(TownInsect *insect);
void InsectPath_GoToPerch(TownInsect *insect);
void InsectPath_TurnFromObstacle(TownInsect *insect, u16 *frames);
void InsectPath_PickHeading(TownInsect *insect, s16 *frames);
void InsectPath_Glide(TownInsect *insect, s16 *frames);
int InsectPath_FindPerch(TownInsect *insect);
void InsectPath_Alarm(TownInsect *insect, u8 *calm, int speed, int distance);
void InsectPath_SensePlayers(TownInsect *insect, u8 *calm, Vec3 *nearest);

#endif
