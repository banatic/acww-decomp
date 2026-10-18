/* The motions the museum's insects share (museum_insects.h): the kinds' initialisers start one
 * (InsectMotion_Start) and their frame functions run one each frame (InsectMotion_Update*).
 *
 * A motion is a state machine on MuseumInsect.mode: MUSEUM_INSECT_MODE_REST (25) waits out
 * MuseumInsect.timer, 4 moves, 3 turns towards MuseumInsect.unk_ac, and each motion adds its
 * own modes. The player is watched through InsectMotion_WatchPlayer (InsectSighting): each frame it
 * moves the insect's alarm (unk_9c, 0-255) up while the player is near or moving and down
 * otherwise, and says how the alarm stands against the insect's threshold (unk_9e). An alarmed
 * insect runs, hops, flies off or hides, by its motion.
 *
 * The fields a motion uses, as far as the code shows:
 *   unk_98   frames left (a hop, a hidden spell, a walk)
 *   unk_9a   set while startled
 *   unk_9c   the alarm (InsectMotion_FollowPlayer counts frames in it)
 *   unk_9e   the alarm's threshold
 *   unk_a0   how far it sees the player
 *   unk_a8   the height it moves at, unk_54 a copy
 *   unk_ac   the yaw it turns to
 *   unk_ae   the way it turns (or, hovering, the way it drifts in x)
 *   unk_168  the frames of the current mode, or a phase
 *   unk_16c  its speed
 *   unk_170  a direction flag (up or down, left or right)
 *   kept     a point it goes to or comes back to; anchor, a point it hovers about
 *   low/high the x and z it keeps within */
#ifndef CLEAN_OV004_MUSEUM_INSECT_MOTIONS_H
#define CLEAN_OV004_MUSEUM_INSECT_MOTIONS_H

#include "autoload_2/vector.h"
#include "museum_insects.h"
#include "types.h"

/* What InsectMotion_WatchPlayer sees of the player (0x1c bytes). */
typedef struct InsectSighting {
    Vec3 player;       /* 0x00: the player's position */
    fx32 player_speed; /* 0x0c */
    fx32 distance;     /* 0x10: from the insect, in x and z */
    u8 seen;           /* 0x14: there is a player */
    u8 pad_15[7];
} InsectSighting;

/* func_ov004_02244658's result: how the alarm stands against the threshold. */
#define INSECT_MOTION_ALARM_NO_PLAYER (-1)
#define INSECT_MOTION_ALARM_BELOW 0
#define INSECT_MOTION_ALARM_ROSE 1 /* it has just reached the threshold */
#define INSECT_MOTION_ALARM_FELL 2 /* it has just dropped below it */
#define INSECT_MOTION_ALARM_ABOVE 3

/* MuseumInsect.mode, as the motions use it. */
#define INSECT_MOTION_SINK 1       /* hovering: down */
#define INSECT_MOTION_RISE 2       /* hovering: up */
#define INSECT_MOTION_TURN 3       /* to unk_ac (hovering: a sway) */
#define INSECT_MOTION_MOVE 4       /* walking, flying, hopping */
#define INSECT_MOTION_TURN_AWAY 15 /* from a wall, to unk_ac */

/* More of MuseumInsect.mode: the flappers' (kinds 0-7) and the darters' (kinds 21-23). */
#define INSECT_MOTION_FLY 0              /* flapping */
#define INSECT_MOTION_SETTLE 5           /* to the rest point */
#define INSECT_MOTION_PERCH 6            /* on the anchor */
#define INSECT_MOTION_STARTLED 7         /* alarmed: off along unk_ac */
#define INSECT_MOTION_HOVER 11           /* before a dart */
#define INSECT_MOTION_HOVER_BLOCKED 12   /* after a wall */
#define INSECT_MOTION_HOVER_BLOCKED_2 13 /* the same */
#define INSECT_MOTION_HOVER_TO_REST 14   /* before the rest point */
#define INSECT_MOTION_TURN_TO_REST 19    /* to the rest point */

int InsectMotion_Start(MuseumInsect *insect, short threshold, int sight, short pitch, short yaw, int height, int speed);
void InsectMotion_BoundAroundPosition(MuseumInsect *insect);
void InsectMotion_SetBounds(MuseumInsect *insect, const int *low, const int *high);
short InsectMotion_RandomTurn(int steps);
void InsectMotion_Drift(MuseumInsect *insect);
void InsectMotion_ReactToPlayer(MuseumInsect *insect, short *frames);
void InsectMotion_UpdateDrifter(MuseumInsect *insect);
void InsectMotion_UpdateWatcher(MuseumInsect *insect);
void InsectMotion_Sway(MuseumInsect *insect, short *step);
void InsectMotion_Sink(MuseumInsect *insect, short *step);
void InsectMotion_Rise(MuseumInsect *insect, short *step);
void InsectMotion_IdleKind9(MuseumInsect *insect);
void InsectMotion_UpdateHoverer(MuseumInsect *insect);
int InsectMotion_Swing(MuseumInsect *insect, short *step);
int InsectMotion_PlayerWithin(MuseumInsect *insect);
void InsectMotion_UpdateKind53(MuseumInsect *insect);
void InsectMotion_ClampXZ(Vec3 *dst, const Vec3 *src, int whole);
int InsectMotion_Walk(MuseumInsect *insect);
void InsectMotion_Hop(MuseumInsect *insect, InsectSighting *sighting);
void InsectMotion_UpdateHopper(MuseumInsect *insect);
void InsectMotion_UpdatePartners(MuseumInsect *insect);
int InsectMotion_FacePlayer(MuseumInsect *insect);
void InsectMotion_PairWalk(MuseumInsect *insect);
void InsectMotion_PairBackOff(MuseumInsect *insect);
void InsectMotion_PairPause(MuseumInsect *insect);
void InsectMotion_PairCircleOther(MuseumInsect *insect);
void InsectMotion_PairCircledBy(MuseumInsect *insect);
void InsectMotion_PairJostle(MuseumInsect *insect);
int InsectMotion_PairChoose(MuseumInsect *insect);
int InsectMotion_PairFaceEachOther(MuseumInsect *a, MuseumInsect *b);
void InsectMotion_Waggle(MuseumInsect *insect, int yaw, int frame);
void InsectMotion_UpdatePair(MuseumInsect *insect);
void InsectMotion_Hover(MuseumInsect *insect);
void InsectMotion_UpdateHovering(MuseumInsect *insect);
void InsectMotion_PlaceOf(Vec3 *out, unsigned int place);
void InsectMotion_NextPlace(MuseumInsect *insect);
void InsectMotion_FlyToPlace(MuseumInsect *insect);
int InsectMotion_Calm(MuseumInsect *insect);
void InsectMotion_UpdateVisitor(MuseumInsect *insect);
int InsectMotion_AvoidWalls(MuseumInsect *insect);
void InsectMotion_WalkOut(MuseumInsect *insect, short *frames);
void InsectMotion_Leap(MuseumInsect *insect, short *frames);
void InsectMotion_WaitHidden(MuseumInsect *insect);
void InsectMotion_UpdateBurrower(MuseumInsect *insect);
void InsectMotion_HopToKept(MuseumInsect *insect);
void InsectMotion_UpdateJumper(MuseumInsect *insect);
void InsectMotion_Fly(MuseumInsect *insect);
void InsectMotion_UpdateFlier(MuseumInsect *insect);
void InsectMotion_Flutter(MuseumInsect *insect);
void InsectMotion_UpdateFlutterer(MuseumInsect *insect);
void InsectMotion_FollowPlayer(MuseumInsect *insect, short *phase);
void InsectMotion_UpdateFollower(MuseumInsect *insect);
int InsectMotion_RandomSideTurn(int bound);
void InsectMotion_Dash(MuseumInsect *insect, short *frames);
void InsectMotion_StartDash(MuseumInsect *insect, short *frames);
void InsectMotion_UpdateDasher(MuseumInsect *insect);
void InsectMotion_SingWhenCalm(MuseumInsect *insect);
void *InsectMotion_TurnFromWall(MuseumInsect *insect, short *frames);
void InsectMotion_Glide(MuseumInsect *insect);
void InsectMotion_UpdateGlider(MuseumInsect *insect);

int InsectMotion_NearestRestPoint(MuseumInsect *insect);
void InsectMotion_DartFromWall(MuseumInsect *insect);
void InsectMotion_Dart(MuseumInsect *insect);
void InsectMotion_HoverInPlace(MuseumInsect *insect);
void InsectMotion_SettleOnRestPoint(MuseumInsect *insect);
void InsectMotion_UpdateDarter(MuseumInsect *insect);
void InsectMotion_FlapBounds(MuseumInsect *insect, short *phase);
void InsectMotion_FlapFly(MuseumInsect *insect);
void InsectMotion_UpdateFlapper(MuseumInsect *insect);
int InsectMotion_WatchPlayer(MuseumInsect *insect, InsectSighting *sighting);
int InsectMotion_UpdateAlarm(MuseumInsect *insect);
void InsectMotion_TurnToHeading(MuseumInsect *insect, int flag, int mode);
short InsectMotion_YawFromWall(short yaw, int blocked);
void InsectMotion_TowardAnchor(MuseumInsect *insect, short *turn, int *distance, Vec3 *anchor);
int InsectMotion_FleeIfAlarmed(MuseumInsect *insect);
void InsectMotion_BobHeight(MuseumInsect *insect, int phase, int range, int divisor);
void InsectMotion_Wander(MuseumInsect *insect, int step, int period, unsigned int threshold);
int InsectMotion_SoundNumber(int kind, int variant);
int InsectMotion_PlaySound(MuseumInsect *insect, int mode);
int InsectMotion_TimerDone(MuseumInsect *insect);
void InsectMotion_Perched(MuseumInsect *insect);
void InsectMotion_SeekAnchor(MuseumInsect *insect);
int InsectMotion_ClampToBounds(MuseumInsect *insect, Vec3 *point);
int InsectMotion_StayOnFloor(Vec3 *position, const Vec3 *previous);
void InsectMotion_FlipFrame(MuseumInsect *insect);
void InsectMotion_PointAlong(Vec3 *out, const Vec3 *base, int yaw, fx32 distance);
short InsectMotion_RandomYaw(void);
void InsectMotion_Facing(Vec3 *out, int yaw);
void InsectMotion_PlaceFeelers(MuseumInsect *insect);
int InsectMotion_FeelersPushed(MuseumInsect *insect);
int InsectMotion_FeelersOffGround(MuseumInsect *insect);
int InsectMotion_FeelWalls(MuseumInsect *insect);
int InsectMotion_FeelGround(MuseumInsect *insect);

#endif
