/* Overlay 50: Tom Nook in his store and the twins who keep it with him. Three special
 * characters share one class: the twins of the message file "sp_npc_twins" (profiles 0x74 and
 * 0x75, model npc_sp/model/lrc) and Tom Nook of "sp_npc_raccoon" (profile 0x76, a model for
 * each of the store's four sizes: rcn, rcc, rcs and rcd). Their records are
 * data_ov050_02265918 (0x74, NookClerk_CreateTwinA), data_ov050_02265900 (0x75,
 * NookClerk_CreateTwinB) and data_ov050_022658e8 (0x76, NookClerk_CreateNook), which main's
 * profile table data_020e3134 points to. Each is a scene object of class 0x020da088 (main's
 * special_scene_object.h) with vtable data_ov050_02265a60, 0x744 bytes.
 *
 * A clerk stands behind the counter and turns to the player, walking along the counter's path
 * (ScenePathStep_Choose toward the player's start point) when the player is farther than 3.0
 * (running past 4.0). When the player faces an item on display (NookClerk_FindShown: the tile
 * 2.0 ahead of the player, at the press of A or a tap on it) the clerk asks for an event of
 * kind 6 and tells its price (talk modes 8 to 0x19 by the item's class, data_ov050_022650e4).
 * The twins share the counter: only the nearer of the two answers the player
 * (NookClerk_IsNearerThanTwin). Tom Nook also greets the player on the first visit of the day,
 * tells the store's news and its upgrades (the talk's line, nook_clerk_talk.h), sells and buys
 * items, takes orders from the catalog and paint for the house's roof, takes the house loan's
 * payments, and runs the part-time job a new player works for him (the player's record flag 1:
 * the errands of the villager part's block 0, main's villager_part.h).
 *
 * Their states (NookClerk.state, NOOK_CLERK_STATE_*) are C++ pointers to member functions, an
 * entry and an update each, in data_ov050_02265f08 (filled at start-up by
 * __sinit_ov050_0226520c), set by NookClerk_SetState and run each frame by NookClerk_Update:
 *   0  greet:        each frame the clerk asks for an event of kind 6 (to greet the player);
 *   1  stand:        the clerk stands; a turn or a walk when the player moves; Tom Nook with a
 *                    dated event of kind 3 today acts (state 7) after 100 to 180 frames;
 *   2  turn:         the clerk turns to the player, then stands;
 *   3  walk:         the clerk walks along the counter toward the player, then stands;
 *   4  talk:         turns to the one talked with and talks; then the event ends;
 *   5  talk, leave:  the same, then the player is put out of the store (exit 0, or exit 1 for
 *                    a twin once the date of main's block part 0x18 has passed);
 *   6  talked:       nothing;
 *   7  act:          the motion of kind 10, then the clerk stands;
 *   8  await:        while the session decides who runs the clerk (linked);
 *   9  other:        another system's player talks to the clerk;
 *   10 await twin:   twin 0x75 waits until twin 0x74 has greeted, then stands;
 *   11 face:         a turn, then the clerk keeps facing the player;
 *   12 still:        the clerk stands, nothing more (twin 0x75 while twin 0x74 talks);
 *   13 linked stand: the clerk stands and turns to the player (state 14);
 *   14 linked turn:  the clerk turns to the player, then state 13;
 *   15 paused:       an event starts: nothing;
 *   16 approach:     the clerk walks toward the player for up to 50 frames, then talks;
 *   17 lead:         the player is walked to (16.0, 9.0) of the store, then the clerk turns;
 *   18 turn, ask:    the clerk turns, then asks for an event of kind 6 each frame. */
#ifndef CLEAN_OV050_NOOK_CLERK_H
#define CLEAN_OV050_NOOK_CLERK_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

enum NookClerkState {
    NOOK_CLERK_STATE_GREET = 0,
    NOOK_CLERK_STATE_STAND = 1,
    NOOK_CLERK_STATE_TURN = 2,
    NOOK_CLERK_STATE_WALK = 3,
    NOOK_CLERK_STATE_TALK = 4,
    NOOK_CLERK_STATE_TALK_LEAVE = 5,
    NOOK_CLERK_STATE_TALKED = 6,
    NOOK_CLERK_STATE_ACT = 7,
    NOOK_CLERK_STATE_AWAIT = 8,
    NOOK_CLERK_STATE_OTHER = 9,
    NOOK_CLERK_STATE_AWAIT_TWIN = 10,
    NOOK_CLERK_STATE_FACE = 11,
    NOOK_CLERK_STATE_STILL = 12,
    NOOK_CLERK_STATE_LINKED_STAND = 13,
    NOOK_CLERK_STATE_LINKED_TURN = 14,
    NOOK_CLERK_STATE_PAUSED = 15,
    NOOK_CLERK_STATE_APPROACH = 16,
    NOOK_CLERK_STATE_LEAD = 17,
    NOOK_CLERK_STATE_TURN_ASK = 18,
    NOOK_CLERK_STATES = 19
};

/* A state's functions in data_ov050_02265f08. */
typedef struct NookClerkStep {
    MemberPointer enter;  /* 0x00: int (clerk); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (clerk) */
} NookClerkStep;

/* The profiles of the three clerks (Actor.profile, at 0x0c of the object). */
#define NOOK_CLERK_TWIN_A 0x74
#define NOOK_CLERK_TWIN_B 0x75
#define NOOK_CLERK_NOOK 0x76

/* NookClerkTalk.mode: what the talk is about, which picks the line it starts with
 * (data_ov050_02265114, NookClerkTalk_Line). The ones named in the code: */
#define NOOK_CLERK_MODE_NOOK_GREET 0x00  /* Tom Nook's greeting (state 0) */
#define NOOK_CLERK_MODE_SPOT_TAKEN 0x01  /* the player's start point is claimed (Tom Nook) */
#define NOOK_CLERK_MODE_NOOK_TALKED 0x05 /* the player talked to Tom Nook */
#define NOOK_CLERK_MODE_NOOK_DATE 0x06   /* the date of main's block part 0x18 passed (Tom Nook) */
#define NOOK_CLERK_MODE_DRAMA 0x0f       /* a dated event of kind 3: its own line */
#define NOOK_CLERK_MODE_TWIN_GREET 0x11  /* a twin's greeting (state 0) */
#define NOOK_CLERK_MODE_TWIN_SPOT 0x12   /* the player's start point is claimed (a twin) */
#define NOOK_CLERK_MODE_TWIN_TALKED 0x13 /* the player talked to a twin */
#define NOOK_CLERK_MODE_TWIN_A_DATE 0x1d /* the date of main's block part 0x18 passed (twin 0x74) */
#define NOOK_CLERK_MODE_JOB_DOOR 0x1e    /* the player at work went toward the door */
#define NOOK_CLERK_MODES 0x1f

struct NookClerk;

/* The clerk's talk scene (0xd4 bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h)
 * with vtable data_ov050_02265b14. */
typedef struct NookClerkTalk {
    SceneBase base;          /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];         /* 0x80: the scene's commands (scene_command.h) */
    u32 mode;                /* 0xb0: NOOK_CLERK_MODE_* */
    struct NookClerk *owner; /* 0xb4 */
    MemberPointer sequence;  /* 0xb8: void (talk), run once when a command of the scene ends */
    s32 extra_bags;          /* 0xc0: what SceneBells_Fit is asked with */
    s32 price;               /* 0xc4: the bells of the deal talked about */
    u8 unk_c8[4];            /* 0xc8 */
    s32 package_slot;        /* 0xcc: the pocket of the item 0x36fc; -1 not looked for, -2 done */
    s32 line;                /* 0xd0: the line an answer or a line's end asks for, 0xff none */
} NookClerkTalk;

/* What the talk's line function gives: the message file's name and the line. */
typedef struct NookClerkLine {
    const char *text;
    u8 message;
    u8 unk_05[3];
} NookClerkLine;

/* The size of the special character's scene object the clerk derives from, as far as it is
 * used; its byte 0x651 is the step of state 17. */
#define NOOK_CLERK_BASE_SIZE 0x654

typedef struct NookClerk {
    u8 base[NOOK_CLERK_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                     /* 0x654: enum NookClerkState */
    NookClerkTalk talk;            /* 0x658 */
    u8 has_event;                  /* 0x72c: Tom Nook has a dated event of kind 3 today */
    u8 unk_72d;                    /* 0x72d */
    u16 act_countdown;             /* 0x72e: the frames before he acts (state 7) */
    u16 stand_word;                /* 0x730: the word of the next stand (scene_motion_request.h) */
    u16 item;                      /* 0x732: the item on display talked about, 0xfff1 for none */
    s32 tile_x;                    /* 0x734: its tile */
    s32 tile_z;                    /* 0x738 */
    u8 bought;                     /* 0x73c: the item on display was bought in this talk */
    u8 approach_frames;            /* 0x73d: the frames left to walk toward the player (state 16) */
    u8 job_step;                   /* 0x73e: where the part-time job's talk stands (0 to 2) */
    u8 sound_played;               /* 0x73f: the action's start sound played (vtable slot 0x80) */
    u8 greeting;                   /* 0x740: twin 0x74 greets (twin 0x75 waits, state 10) */
    u8 unk_741[3];                 /* 0x741 */
} NookClerk;

/* The vtable slots and questions (nook_clerk.c). */
void *NookClerk_Destruct(NookClerk *clerk);
void *NookClerk_DestructDelete(NookClerk *clerk);
int NookClerk_HurryDistance(NookClerk *clerk);
int NookClerk_WalkDistance(NookClerk *clerk);
int NookClerk_IsTwin(NookClerk *clerk);
int NookClerk_IsTwinA(NookClerk *clerk);
int NookClerk_IsTwinB(NookClerk *clerk);
int NookClerk_IsNook(NookClerk *clerk);
int NookClerk_CheckDatePassed(NookClerk *clerk);
int NookClerk_CheckSpotTaken(NookClerk *clerk);
int NookClerk_CheckJobDoor(NookClerk *clerk);
int NookClerk_OfferShown(NookClerk *clerk);
int NookClerk_FindShown(NookClerk *clerk);
int NookClerk_OtherTwin(NookClerk *clerk);
int NookClerk_IsNearerThanTwin(NookClerk *clerk);
void NookClerk_OnEvent(NookClerk *clerk, int code, int participant);
int NookClerk_MayActKind6(NookClerk *clerk);
int NookClerk_MayAct(NookClerk *clerk);
void NookClerk_SoundPlayed(NookClerk *clerk);
int NookClerk_HasActionSound(NookClerk *clerk);
void NookClerk_SetState(NookClerk *clerk, int state);
int NookClerk_ModelName(NookClerk *clerk);
int NookClerk_TextureName(NookClerk *clerk);
int NookClerk_Start(NookClerk *clerk);
int NookClerk_Init(NookClerk *clerk);
void *NookClerk_CreateTwinA(void);
void *NookClerk_CreateTwinB(void);
void *NookClerk_CreateNook(void);
int NookClerk_Update(NookClerk *clerk);

/* The states (nook_clerk.c). */
int NookClerk_UpdateApproach(NookClerk *clerk);
int NookClerk_EnterApproach(NookClerk *clerk);
int NookClerk_UpdatePaused(void);
int NookClerk_EnterPaused(void);
int NookClerk_UpdateLinkedTurn(NookClerk *clerk);
int NookClerk_EnterLinkedTurn(NookClerk *clerk);
int NookClerk_UpdateLinkedStand(NookClerk *clerk);
int NookClerk_EnterLinkedStand(NookClerk *clerk);
int NookClerk_UpdateOther(NookClerk *clerk);
int NookClerk_EnterOther(void);
int NookClerk_UpdateAwait(NookClerk *clerk);
int NookClerk_EnterAwait(void);
int NookClerk_UpdateTurnAsk(NookClerk *clerk);
int NookClerk_EnterTurnAsk(NookClerk *clerk);
int NookClerk_UpdateLead(NookClerk *clerk);
int NookClerk_EnterLead(NookClerk *clerk);
int NookClerk_UpdateAct(NookClerk *clerk);
int NookClerk_EnterAct(NookClerk *clerk);
int NookClerk_UpdateFace(NookClerk *clerk);
int NookClerk_EnterFace(NookClerk *clerk);
int NookClerk_UpdateStill(void);
int NookClerk_EnterStill(NookClerk *clerk);
int NookClerk_UpdateAwaitTwin(NookClerk *clerk);
int NookClerk_EnterAwaitTwin(void);
int NookClerk_UpdateTalked(void);
int NookClerk_EnterTalked(void);
int NookClerk_UpdateTalkLeave(NookClerk *clerk);
int NookClerk_EnterTalkLeave(NookClerk *clerk);
int NookClerk_UpdateTalk(NookClerk *clerk);
int NookClerk_EnterTalk(NookClerk *clerk);
int NookClerk_UpdateWalk(NookClerk *clerk);
int NookClerk_EnterWalk(NookClerk *clerk);
int NookClerk_UpdateTurn(NookClerk *clerk);
int NookClerk_EnterTurn(NookClerk *clerk);
int NookClerk_UpdateStand(NookClerk *clerk);
int NookClerk_EnterStand(NookClerk *clerk);
int NookClerk_UpdateGreet(NookClerk *clerk);
int NookClerk_EnterGreet(NookClerk *clerk);

#endif
