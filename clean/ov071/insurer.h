/* Overlay 71: the insurance seller, the special character of the message file
 * "sp_npc_insurance" with the model npc_sp/model/ott (person code 0xd00d). Main's spawner
 * (spawner.h) makes him in the town while event 0x3c is on (Spawner_CheckD00DIn): its spawn
 * table (data_020e1d8c) gives his object profile 0x69 the code 0xd00d and overlay 71, loaded
 * with him; the profile's record is at 0x0227a1ac, which main's profile table data_020e3134
 * points to.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x0227a278, 0x744 bytes, made by Insurer_Create, with his talk scene (InsurerTalk,
 * insurer_talk.h) at 0x658. He sells the player insurance (3000 bells, player record flag
 * 0x17) and a dearer cover (6000 bells, flag 0x18), and takes the items of codes 0x3934-0x3983
 * as claims, which raise the player record's count of claims (PlayerField2416; main's
 * insurance letter pays for them).
 *
 * His states (Insurer.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov071_0227a3a4 (filled at start-up by __sinit_ov071_02279fd4), set by
 * Insurer_SetState:
 *   0  talk ends: once his action is idle the event ends: state 2;
 *   1  chase:  he calls to the player and runs after the player while the player stays in view
 *              (Insurer_UpdateChase: its three steps), then waits in front of the player;
 *   2  talked: nothing;
 *   3  wander: he stands, walks to random clear spots near him or turns, stepping aside of
 *              what blocks him; once his rest is over, a player in view who has not been
 *              pitched to today (daily bit 0x28), close ahead of him, is chased (state 1);
 *   4  wait:   his footsteps off; he wanders (state 3) once the player is in view, or chases
 *              a player who was not pitched to today and is close ahead of him;
 *   5  talk:   he turns to the talk's partner and talks. */
#ifndef CLEAN_OV071_INSURER_H
#define CLEAN_OV071_INSURER_H

#include "autoload_2/vector.h"
#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Insurer;

/* The lines of explanation his talk picks from (Insurer.explained). */
#define INSURER_EXPLANATIONS 5

/* His talk scene (0xcc bytes, a scene of main's class 0x020d9ff8, vtable 0x0227a1e8). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct InsurerTalk {
    SceneBase base;              /* 0x00 */
    u8 unk_80[0x30];             /* 0x80 */
    s32 first;                   /* 0xb0: INSURER_TALK_FIRST_*, what the talk started with */
    struct Insurer *owner;       /* 0xb4 */
    u8 explained_count;          /* 0xb8: lines of explanation said in a row */
    u8 unk_b9[3];                /* 0xb9 */
    MemberPointer sequence;      /* 0xbc: void (talk), run when a command of the scene ends */
    MemberPointer next_sequence; /* 0xc4: the one that follows it */
} InsurerTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define INSURER_BASE_SIZE 0x654

typedef struct Insurer {
    u8 base[INSURER_BASE_SIZE];         /* 0x000: the special character's scene object */
    s32 state;                          /* 0x654: INSURER_* */
    InsurerTalk talk;                   /* 0x658 */
    u8 explained[INSURER_EXPLANATIONS]; /* 0x724: 1 for each line of explanation said */
    u8 chase_step;                      /* 0x729: INSURER_CHASE_* */
    u8 unk_72a[2];                      /* 0x72a */
    int timer;                          /* 0x72c: frames left of a move or a wait */
    int rest;                           /* 0x730: frames before he chases again */
    u32 player;                         /* 0x734: the object of this console's player, or 0 */
    Vec3 start;                         /* 0x738: where the chase started */
} Insurer;

enum InsurerState {
    INSURER_TALK_ENDS = 0,
    INSURER_CHASE = 1,
    INSURER_TALKED = 2,
    INSURER_WANDER = 3,
    INSURER_WAIT = 4,
    INSURER_TALKING = 5,
    INSURER_STATES = 6
};

/* The steps of the chase (Insurer.chase_step). */
enum InsurerChaseStep { INSURER_CHASE_CALL = 0, INSURER_CHASE_RUN = 1, INSURER_CHASE_WAIT = 2, INSURER_CHASE_STEPS = 3 };

/* A state's functions in data_ov071_0227a3a4. */
typedef struct InsurerStep {
    MemberPointer enter;  /* 0x00: int (insurer); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (insurer) */
} InsurerStep;

void *Insurer_Destroy(void *insurer);
void *Insurer_Delete(void *insurer);
void Insurer_OnEvent(Insurer *insurer, int code);
int Insurer_MayAct(Insurer *insurer);
int Insurer_UpdateTalked(void);
int Insurer_UpdateWait(Insurer *insurer);
int Insurer_EnterWait(Insurer *insurer);
int Insurer_UpdateWander(Insurer *insurer);
int Insurer_StepAsideIfMoving(Insurer *insurer);
int Insurer_StepAside(Insurer *insurer);
int Insurer_ProbePoint(Insurer *insurer, Vec3 *out, int offset);
int Insurer_RandomSpot(Insurer *insurer, int *x, int *z);
int Insurer_EnterWander(Insurer *insurer);
int Insurer_UpdateChase(Insurer *insurer);
int Insurer_EnterChase(Insurer *insurer);
void Insurer_ChaseWait(Insurer *insurer);
void Insurer_ChaseRun(Insurer *insurer);
void Insurer_ChaseCall(Insurer *insurer);
int Insurer_PlayerAhead(Insurer *insurer, int range);
int Insurer_NearStart(Insurer *insurer);
int Insurer_UpdateTalking(void);
int Insurer_EnterTalking(char *insurer);
int Insurer_UpdateTalkEnds(Insurer *insurer);
int Insurer_EnterTalkEnds(void);
int Insurer_CountDown(int unused, int *counter);
int Insurer_InView(Insurer *insurer, int wide);
int Insurer_InBox(int unused, const Vec3 *centre, const Vec3 *point, int wide);
void Insurer_SetState(Insurer *insurer, int state);
int Insurer_Update(Insurer *insurer);
int Insurer_SecondAnimation(void);
int Insurer_FirstAnimation(void);
int Insurer_ModelName(void);
int Insurer_TextureName(void);
int Insurer_Leave(void *insurer);
int Insurer_Start(Insurer *insurer);
int Insurer_Init(Insurer *insurer);
int Insurer_AnimSpeed(void);
void *Insurer_Create(void);

#endif
