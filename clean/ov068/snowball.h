/* The snowballs' states that overlay 68 holds: the entries and updates of overlay 3's first
 * machine of a snowball (ov003/snowman.h, Snowman_SetState and Snowman_UpdateState), and the
 * helpers they share.
 *
 *   state  entry                    update                    what happens
 *   0      Snowball_EnterLoose      Snowball_UpdateLoose      a loose ball at rest or rolling; one pushed
 *                                                             into another becomes a snowman
 *   1      Snowball_EnterFall       Snowball_UpdateFall       over ground below height 0, it falls
 *   2      Snowball_EnterFloat      Snowball_UpdateFloat      it floats on the water, drifts and melts away
 *   3      Snowball_EnterBroken     Snowball_UpdateBroken     it bursts and is deleted
 *   4      Snowball_EnterSink       Snowball_UpdateSink       it rolls into the middle of a tile holding item
 *                                                             0xfc or 0xfd, sinking, and bursts there
 *   5      Snowball_EnterSlide      Snowball_UpdateSlide      on ground of attribute 0x16 or 0x17 it is
 *                                                             carried south and down
 *   6      Snowball_EnterDrift      Snowball_UpdateDrift      then drifts on the water below and melts away
 *   7      Snowball_EnterSettleBody Snowball_UpdateSettleBody a new snowman's body moves to the middle of
 *                                                             its tile and stands there as a map object
 *   8      Snowball_EnterJumpOn     Snowball_UpdateJumpOn     the new snowman's head jumps onto the body
 *   10     Snowball_EnterSettleHead Snowball_UpdateSettleHead then rises to its place on it
 *   12     Snowball_EnterShakeBody  Snowball_UpdateShakeBody  a body (its map object taken away) shakes and
 *                                                             bursts
 *   13     Snowball_EnterShakeHead  Snowball_UpdateShakeHead  a head shakes and bursts
 *
 * (States 9 and 11, a snowman's standing body and head, are overlay 3's.)
 *
 * A ball leaving the loose states forgets what main keeps of it between visits (its entry of
 * Snowmen_LooseBalls is set back to the origin and size 0x800). */
#ifndef CLEAN_OV068_SNOWBALL_H
#define CLEAN_OV068_SNOWBALL_H

#include "ov003/snowman.h"
#include "types.h"

/* The states of the first machine named here (see above; enum SnowmanState has the others). */
#define SNOWBALL_STATE_FALL 1
#define SNOWBALL_STATE_FLOAT 2
#define SNOWBALL_STATE_SINK 4
#define SNOWBALL_STATE_SLIDE 5
#define SNOWBALL_STATE_DRIFT 6
#define SNOWBALL_STATE_SETTLE_BODY 7
#define SNOWBALL_STATE_JUMP_ON 8
#define SNOWBALL_STATE_SETTLE_HEAD 10

void Snowball_UpdateShakeHead(Snowman *ball);
int Snowball_EnterShakeHead(Snowman *ball);
void Snowball_UpdateShakeBody(Snowman *ball);
int Snowball_EnterShakeBody(Snowman *ball);
void Snowball_UpdateSettleHead(Snowman *ball);
int Snowball_EnterSettleHead(Snowman *ball);
void Snowball_UpdateJumpOn(Snowman *ball);
int Snowball_EnterJumpOn(Snowman *ball);
void Snowball_UpdateSettleBody(Snowman *ball);
int Snowball_EnterSettleBody(Snowman *ball);
void Snowball_UpdateDrift(Snowman *ball);
int Snowball_EnterDrift(Snowman *ball);
void Snowball_UpdateSlide(Snowman *ball);
int Snowball_EnterSlide(Snowman *ball);
void Snowball_UpdateSink(Snowman *ball);
int Snowball_EnterSink(Snowman *ball);
void Snowball_UpdateBroken(Snowman *ball);
int Snowball_EnterBroken(Snowman *ball);
void Snowball_UpdateFloat(Snowman *ball);
int Snowball_EnterFloat(Snowman *ball);
void Snowball_UpdateFall(Snowman *ball);
int Snowball_EnterFall(Snowman *ball);
void Snowball_UpdateLoose(Snowman *ball);
int Snowball_EnterLoose(Snowman *ball);
void Snowball_Splash(Snowman *ball);
void Snowball_Burst(Snowman *ball);
int Snowball_Face(fx32 ratio);
void Snowball_Fall(Snowman *ball);

#endif
