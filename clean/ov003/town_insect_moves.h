/* What the town's insects do each frame (town_insect.h): the update function of each group of
 * kinds (the table of town_insect_kinds.h passes the insect on to them) and the moves they share.
 *
 * Each update picks a move by the insect's action (TownInsect.action, the byte 0x251). What an
 * action means depends on the group; actions 9 (fleeing) and 0xb (let go from a player's hand)
 * mean the same for all, and 0x13 is the action TownInsectKind_Begin starts each kind with.
 *
 * Most kinds notice the players (TownInsectMove_SensePlayers): the byte 0x254 is an alarm level
 * that rises while a player is near and moving (the faster, the more) and falls by one a frame
 * otherwise; when it reaches the kind's byte 0x255, the insect flies off or hides. Kinds that
 * fly keep to a point (TownInsect.target) they approach, turning from what stands ahead
 * (TownInsectMove_TurnFromObstacle). When an insect has faded out (TownInsectMove_FadeStep) it
 * leaves (TownInsectMove_Leave).
 *
 *   kinds                     update
 *   9, 0x10-0x14, 0x1f, ...   TownInsectMove_UpdateLeaning  (rests on something, sways, flies off)
 *   0xa, 0x33                 TownInsectMove_Update0A
 *   0xb, 0x3a                 TownInsectMove_Update0B
 *   0xc, 0xd, 0x1b-0x1d       TownInsectMove_UpdateWaiting  (waits, turns, flies to a new point)
 *   0xe, 0xf, 0x1a, 0x20      TownInsectMove_UpdateInArea   (wanders in a box around its place)
 *   0x15-0x17                 TownInsectMove_UpdateTurned   (hovers, turns, flies to a new point)
 *   0x18, 0x3b                TownInsectMove_Update18
 *   0x19                      TownInsectMove_Update19
 *   0x1e                      TownInsectMove_Update1E
 *   0x23                      TownInsectMove_Update23
 *   0x25, 0x39                TownInsectMove_Update25
 *   0x30                      TownInsectMove_Update30       (hops)
 *   0x31                      TownInsectMove_Update31       (comes out when a player stands by)
 *   0x32                      TownInsectMove_Update32
 *   0x35                      TownInsectMove_Update35
 *   0x36, 0x37                TownInsectMove_Update36
 *   8                         TownInsectMove_Update08 */
#ifndef CLEAN_OV003_TOWN_INSECT_MOVES_H
#define CLEAN_OV003_TOWN_INSECT_MOVES_H

#include "autoload_2/vector.h"
#include "main/actor.h"
#include "ov003/town_insect.h"
#include "types.h"

void TownInsectMove_FlyUpAway(TownInsect *insect, short *frames);
void TownInsectMove_Leave(TownInsect *insect);
void TownInsectMove_SetBox(TownInsect *insect);
void TownInsectMove_ShiftAside(TownInsect *insect);
void TownInsectMove_WanderInBox(TownInsect *insect);
void TownInsectMove_WatchPlayer(TownInsect *insect, u16 *frames);
int TownInsectMove_OnSetBTile(const Vec3 *point);
void TownInsectMove_UpdateInArea(TownInsect *insect);
void TownInsectMove_CheckStartle(TownInsect *insect, short *frames);
void TownInsectMove_FadeByAlarm(TownInsect *insect, short *frames);
void TownInsectMove_TakeOff(TownInsect *insect, short *frames);
void TownInsectMove_FlyOff(TownInsect *insect, short *frames);
void TownInsectMove_Sway(TownInsect *insect, short *frames);
void TownInsectMove_Descend(TownInsect *insect, short *frames);
void TownInsectMove_Ascend(TownInsect *insect, short *frames);
void TownInsectMove_Rest(TownInsect *insect, short *frames);
void TownInsectMove_UpdateLeaning(TownInsect *insect);
void TownInsectMove_Update35(TownInsect *insect);
void TownInsectMove_ClampXZ(Vec3 *dst, const Vec3 *src, int limit);
int TownInsectMove_WalkLinked(TownInsect *insect);
int TownInsectMove_Walk(TownInsect *insect);
int TownInsectMove_FadeStep(TownInsect *insect, int amount);
void TownInsectMove_Update23(TownInsect *insect);
void TownInsectMove_Update36(TownInsect *insect);
void TownInsectMove_Update30(TownInsect *insect);
void TownInsectMove_Update08(TownInsect *insect);
int TownInsectMove_AppearFromTile(TownInsect *insect, short *frames);
void TownInsectMove_Walk31(TownInsect *insect);
void TownInsectMove_Wait31(TownInsect *insect);
void TownInsectMove_Update31(TownInsect *insect);
int TownInsectMove_TurnFromObstacle(TownInsect *insect);
void TownInsectMove_Walk1E(TownInsect *insect, short *frames);
void TownInsectMove_Flee(TownInsect *insect, short *frames);
void TownInsectMove_Hop(TownInsect *insect, short *frames);
void TownInsectMove_Wait1E(TownInsect *insect, short *frames);
void TownInsectMove_Update1E(TownInsect *insect);
void TownInsectMove_Update18(TownInsect *insect);
void TownInsectMove_Update0A(TownInsect *insect);
void TownInsectMove_Update0B(TownInsect *insect);
void TownInsectMove_Crawl25(TownInsect *insect);
void TownInsectMove_Update25(TownInsect *insect);
void TownInsectMove_Update32(TownInsect *insect);
void TownInsectMove_Update19(TownInsect *insect);
void TownInsectMove_Sound1BTo1D(TownInsect *insect);
void TownInsectMove_SoundCD(TownInsect *insect);
int TownInsectMove_TurnAtObstacle(TownInsect *insect, short *frames);
void TownInsectMove_FlyWaiting(TownInsect *insect);
short TownInsectMove_RandomTurn(int steps, int either_way);
void TownInsectMove_Wait(TownInsect *insect, short *frames);
void TownInsectMove_UpdateWaiting(TownInsect *insect);
int TownInsectMove_SensePlayers(TownInsect *insect, Vec3 *nearest);
void TownInsectMove_SensePlayer(TownInsect *insect, Vec3 *point, fx32 *distance, u8 *away, u8 player, u8 counting);
int TownInsectMove_TurnToHeading(TownInsect *insect, int byte24c);
short TownInsectMove_HeadingOff(short angle, int side);
void TownInsectMove_CheckObstacle(TownInsect *insect);
void TownInsectMove_RiseAway(TownInsect *insect, short *frames);
void TownInsectMove_FlyToTarget(TownInsect *insect);
void TownInsectMove_Hover(TownInsect *insect, short *frames);
void TownInsectMove_UpdateTurned(TownInsect *insect);
int TownInsectMove_TestFlags(int value);
void TownInsectMove_FlapCycle(TownInsect *insect, short *frames);
void TownInsectMove_Escape(TownInsect *insect, fx32 speed);
int TownInsectMove_WaitOver(TownInsect *insect);
void TownInsectMove_FlyBobbing(TownInsect *insect);
void TownInsectMove_Update00To07(TownInsect *insect);
void TownInsectMove_ToggleFrame(TownInsect *insect);
void TownInsectMove_AlarmTurn(TownInsect *insect, const Vec3 *nearest);
int TownInsectMove_Sense(TownInsect *insect);
void TownInsectMove_Bob(TownInsect *insect, int frame, int limit, fx32 divisor);
void TownInsectMove_Meander(TownInsect *insect, short *heading, int step, int divisor, u8 threshold, fx32 scale);
int TownInsectMove_KindSpeed(TownInsect *insect);
int TownInsectMove_KindReach(TownInsect *insect);
int TownInsectMove_KindLeash(TownInsect *insect);
void TownInsectMove_SetTurnDelay(TownInsect *insect);
void TownInsectMove_TurnBack(TownInsect *insect, const Vec3 *point, int step);
int TownInsectMove_SoundNumber(int kind, int which);
void TownInsectMove_PlaySound(TownInsect *insect, int which, int play);
int TownInsectMove_CountStand(TownInsect *insect, const Vec3 *point);
int TownInsectMove_Splash(TownInsect *insect);
int TownInsectMove_SuitsCode(int kind, const u16 *code);
void TownInsectMove_OnSpot(TownInsect *insect);
Actor *TownInsectMove_NearestPlayer(const Vec3 *point);
int TownInsectMove_TargetAhead(TownInsect *insect, int angle, int steps);
int TownInsectMove_SetTarget(TownInsect *insect, int angle, fx32 distance);
void TownInsectMove_FleeIfFlagged(TownInsect *insect, int most);
int TownInsectMove_OnGroupTile(const Vec3 *point);
void TownInsectMove_StepAlong(Vec3 *step, int angle);
int TownInsectMove_PlaceFeelers(TownInsect *insect, int percent, int spread);
int TownInsectMove_FeelersOffGround(TownInsect *insect);
int TownInsectMove_FeelersBlocked(TownInsect *insect);
int TownInsectMove_FeelObstacles(TownInsect *insect, int reach, int spread);

#endif
