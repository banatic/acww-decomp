/* A cockroach of the player's house (scene object 0xc0; the C++ class with vtable
 * data_ov004_0225622c on the actor, 0x268 bytes; house_roaches.h lets them out). Its model is shared under the name "GOKI" and loaded from
 * /insect/51/bug52.nsbmd with the visibility animation /insect/51/bug52.nsbva.
 *
 * As a process: slot 0 loads it in a room of the house (HouseRoach_Create), slot 3 releases it
 * (HouseRoach_Remove), slot 6 is its frame (HouseRoach_Execute) and slot 9 its draw
 * (HouseRoach_DrawPhase).
 *
 * It fades in (its process's param is its alpha, 0 to 0x1f), then stands still or runs for a
 * random time (HOUSE_ROACH_STAND, HOUSE_ROACH_RUN), runs away from the player or a villager
 * that comes near while it stands, and jumps when one is near in front of it while it runs. It
 * turns from walls, steps and the room's keep-out boxes, which two feelers ahead of it to the
 * left and right find (HouseRoach_SetFeelers, HouseRoach_FeelersBlocked). Stepped on by the
 * player or a villager that moves, or found up on something, it vanishes with an effect
 * (HOUSE_ROACH_VANISH) and fades out; at alpha 0 it is released and its param becomes 0xffff,
 * which house_roaches.h counts as made away with.
 *
 * Its sound: while it runs it asks to rustle (sound state 1); the one house_roaches.h chooses
 * (state 2) plays it. */
#ifndef CLEAN_OV004_HOUSE_ROACH_H
#define CLEAN_OV004_HOUSE_ROACH_H

#include "autoload_2/vector.h"
#include "main/actor.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/sound_emitter.h"
#include "types.h"

/* HouseRoach.sound_state */
enum {
    HOUSE_ROACH_QUIET = 0,
    HOUSE_ROACH_ASKING = 1,   /* it would make its sound */
    HOUSE_ROACH_SOUNDING = 2, /* it was chosen to make it (house_roaches.h) */
};

/* HouseRoach.state */
enum {
    HOUSE_ROACH_STAND = 0,
    HOUSE_ROACH_RUN = 1,
    HOUSE_ROACH_VANISH = 2, /* stepped on or up on something */
    HOUSE_ROACH_DECIDE = 3, /* just made: stands or runs, at random */
};

/* HouseRoach.life */
enum {
    HOUSE_ROACH_OUT = 1,
    HOUSE_ROACH_LEAVING = 2, /* vanished, fading out */
    HOUSE_ROACH_RELEASED = 4,
};

/* HouseRoach_PlaySound's sounds. */
enum {
    HOUSE_ROACH_SOUND_RUSTLE = 0, /* asks for its rustle */
    HOUSE_ROACH_SOUND_JUMP = 1,
    HOUSE_ROACH_SOUND_VANISH = 2,
};

/* The feelers ahead of it (HouseRoach.feelers). */
#define HOUSE_ROACH_FEELERS 2
/* The bytes of its model: an animated model without the blended model's ramp. */
#define HOUSE_ROACH_MODEL_SIZE 0xb8

typedef struct HouseRoach {
    /* 0x000: the process's param is its alpha; it becomes 0xffff once the cockroach is made
     * away with (house_roaches.h) */
    Actor actor;
    fx32 walk_speed;                        /* 0x0d4 */
    fx32 run_speed;                         /* 0x0d8: while it jumps */
    CollisionContacts contacts;             /* 0x0dc */
    int state;                              /* 0x10c: HOUSE_ROACH_STAND... */
    int life;                               /* 0x110: HOUSE_ROACH_OUT... */
    SoundSource sound;                      /* 0x114 */
    u8 model[HOUSE_ROACH_MODEL_SIZE];       /* 0x120: an AnimatedModel */
    FieldOwnedPointBody body;               /* 0x1d8 */
    s16 start_angle;                        /* 0x228: its heading when loaded */
    u8 jumping;                             /* 0x22a */
    u8 pad_22b;                             /* 0x22b */
    s16 timer;                              /* 0x22c: frames left standing or running */
    s16 jump_frame;                         /* 0x22e: 0 when not jumping */
    Vec3 feelers[HOUSE_ROACH_FEELERS];      /* 0x230: left and right ahead */
    Vec3 feelers_last[HOUSE_ROACH_FEELERS]; /* 0x248: where they were before */
    s8 blocked;                             /* 0x260: bit 0 the first feeler is, bit 1 the second */
    u8 pad_261;                             /* 0x261 */
    u8 turn;                                /* 0x262: the way it turned last (1, 2; times 10 once free) */
    u8 sound_asked;                         /* 0x263: it asked for its rustle this frame */
    int sound_state;                        /* 0x264: HOUSE_ROACH_QUIET... */
} HouseRoach;

void HouseRoach_Remove(HouseRoach *roach);
void HouseRoach_Execute(HouseRoach *roach);
int HouseRoach_Create(HouseRoach *roach);
void HouseRoach_DrawPhase(HouseRoach *roach);
int HouseRoach_Run(HouseRoach *roach);
void HouseRoach_SetBody(HouseRoach *roach);
void HouseRoach_Stand(HouseRoach *roach);
Actor *HouseRoach_NearestOther(HouseRoach *roach);
void HouseRoach_SetFeelers(HouseRoach *roach, int distance, int spread);
unsigned char HouseRoach_FeelersBlocked(HouseRoach *roach);
void HouseRoach_PlaySound(HouseRoach *roach, int sound);
int HouseRoach_Release(HouseRoach *roach);
int HouseRoach_Draw(HouseRoach *roach);
int HouseRoach_CheckStepped(HouseRoach *roach);
int HouseRoach_CheckRaised(HouseRoach *roach);
int HouseRoach_Update(HouseRoach *roach);
void HouseRoach_StepAppearing(HouseRoach *roach);
void HouseRoach_Move(HouseRoach *roach);
void HouseRoach_Act(HouseRoach *roach);
int HouseRoach_Load(HouseRoach *roach);
void HouseRoach_SetSoundState(HouseRoach *roach, int state);
int HouseRoach_SoundState(HouseRoach *roach);
void HouseRoach_FindVillager(HouseRoach *roach);
HouseRoach *HouseRoach_Delete(HouseRoach *roach);
HouseRoach *HouseRoach_Destruct(HouseRoach *roach);
HouseRoach *HouseRoach_Construct(HouseRoach *roach);

#endif
