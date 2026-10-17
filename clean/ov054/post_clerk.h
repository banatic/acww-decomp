/* Overlay 54: the post office's clerks, the pelicans: the special characters of the message
 * files "sp_npc_ypelican" (person 0xd006, the model npc_sp/model/pga) and "sp_npc_opelican"
 * (person 0xd007, the model npc_sp/model/pgb). Scene 9, the post office, names overlay 54 in
 * its SceneInfo (data_020e55bc, scene_process.h); a clerk is the object of profile 0x7a (the
 * record data_ov054_02262f94, which main's profile table data_020e3134 points to).
 *
 * A clerk is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * data_ov054_02263094, 0x818 bytes, made by PostClerk_Create. Unlinked, one clerk serves: the
 * one with the person 0xd006 (PostClerk.clerk 0), except from 10 p.m. to 7 a.m., when the
 * other (0xd007, clerk 1) does, unless a game is being started anew. In a linked game the
 * object made with the person 0xd006 makes the other one (profile 0x7a, person 0xd007, at the
 * first place behind the counter) and stands at the second; each clerk serves the player at
 * the counter place before her (PostClerk.spot).
 *
 * The counter has two places for the player (data_ov054_022629c8) with a place behind each
 * for a clerk (data_ov054_022629e0). The clerk that serves walks behind the place the player
 * stands at (PostClerk_FindSpot) and turns back to her home angle.
 *
 * Her states (PostClerk.state), each an entry and an update function (C++ members taking her)
 * from the table data_ov054_022632dc (filled at start-up by __sinit_ov054_02262a70), set by
 * PostClerk_SetState:
 *   0  greet:     she asks for an event of kind 6 each frame (a game being started anew);
 *   1  call over: this console's player walks to the first counter place; then she talks;
 *   2  stand:     she stands; unlinked she walks when the player moves to the other place,
 *                 and with a dated event today not told yet she acts after 100 to 180 frames;
 *   3  walk:      she walks behind the player's counter place, then turns;
 *   4  talk:      she talks; once her action is idle her event ends: state 5;
 *   5  talked:    nothing;
 *   6  turn:      she turns to her home angle, then stands;
 *   7  act:       her motion of kind 10, then she stands;
 *   8  leave:     once talk 0 is gone, main's entry record takes the player out to the town,
 *                 before building 0x5000;
 *   9  await:     linked, while the session decides who runs her;
 *  10  other:     another system's player talks to her;
 *  11  paused:    an event starts: nothing.
 *
 * Her talk scene (PostClerkTalk, post_clerk_talk.h) handles the letters, the savings, the
 * house's loan and the errands of the villagers, and starts linked games. */
#ifndef CLEAN_OV054_POST_CLERK_H
#define CLEAN_OV054_POST_CLERK_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct PostClerk;

/* Her talk scene (0x1ac bytes as far as the clerk's layout goes): a scene of class 0x020d9ff8
 * (main's obj_020d9ff8.h) with vtable data_ov054_02263004. */
typedef struct PostClerkTalk {
    SceneBase base;          /* 0x00: the receiver's file name (0x04) and message (0x1e) */
    u8 unk_80[0x30];         /* 0x80: the scene's commands (scene_command.h) */
    struct PostClerk *owner; /* 0xb0 */
    u32 menu;                /* 0xb4: the menu of answers offered (POST_CLERK_TALK_MENU_*) */
    u32 step;                /* 0xb8: POST_CLERK_TALK_STEP_* (post_clerk_talk.h) */
    u8 letters_shown;        /* 0xbc: the letters (item 0x1565) were shown in this talk */
    u8 unk_bd[3];            /* 0xbd */
    s32 balance;             /* 0xc0: the account's balance before its screen */
    s32 town_amount;         /* 0xc4: the town-wide amount before something was added to it */
    u16 search_frames;       /* 0xc8: the frames left to find a linked game */
    u8 unk_ca[0x1ac - 0xca]; /* 0xca */
} PostClerkTalk;

/* The size of the special character's scene object she derives from, as far as it is used. */
#define POST_CLERK_BASE_SIZE 0x654

typedef struct PostClerk {
    u8 base[POST_CLERK_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                     /* 0x654: enum PostClerkState */
    PostClerkTalk talk;            /* 0x658 */
    s16 home_angle;                /* 0x804: the angle she faces at her start */
    u8 unk_806[2];                 /* 0x806 */
    u32 clerk;                     /* 0x808: POST_CLERK_DAY or POST_CLERK_NIGHT */
    u32 spot;                      /* 0x80c: the counter place she serves, 0 or 1 */
    u16 act_countdown;             /* 0x810: the frames before she acts, 0xff for none */
    u16 stand_word;                /* 0x812: the word of her next stand (scene_motion_request.h) */
    u8 event_told;                 /* 0x814: today's dated event was told in this visit */
    u8 unk_815[3];                 /* 0x815 */
} PostClerk;

/* PostClerk.clerk: which of the two she is (the message files, models and persons by it). */
#define POST_CLERK_DAY 0   /* person 0xd006, "sp_npc_ypelican" */
#define POST_CLERK_NIGHT 1 /* person 0xd007, "sp_npc_opelican" */

enum PostClerkState {
    POST_CLERK_GREET = 0,
    POST_CLERK_CALL_OVER = 1,
    POST_CLERK_STAND = 2,
    POST_CLERK_WALK = 3,
    POST_CLERK_TALK = 4,
    POST_CLERK_TALKED = 5,
    POST_CLERK_TURN = 6,
    POST_CLERK_ACT = 7,
    POST_CLERK_LEAVE = 8,
    POST_CLERK_AWAIT = 9,
    POST_CLERK_OTHER = 10,
    POST_CLERK_PAUSED = 11,
    POST_CLERK_STATES = 12
};

/* A state's functions in data_ov054_022632dc. */
typedef struct PostClerkStep {
    MemberPointer enter;  /* 0x00: int (clerk); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (clerk) */
} PostClerkStep;

/* Her vtable slots and questions (post_clerk.c). */
PostClerk *PostClerk_Destruct(PostClerk *clerk);
PostClerk *PostClerk_DestructDelete(PostClerk *clerk);
int PostClerk_IsLinked(PostClerk *clerk);
u8 PostClerk_HasSessionSlot(PostClerk *clerk);
int PostClerk_ReadyForJob(PostClerk *clerk);
void PostClerk_OnEvent(PostClerk *clerk, int code, int participant);
int PostClerk_MayTalk(PostClerk *clerk, u8 *actor);
int PostClerk_FindSpot(PostClerk *clerk);
void PostClerk_SetState(PostClerk *clerk, int state);
int PostClerk_Update(PostClerk *clerk);
unsigned int PostClerk_ModelName(PostClerk *clerk);
int PostClerk_TextureName(PostClerk *clerk);
int PostClerk_Leave(PostClerk *clerk);
int PostClerk_Start(PostClerk *clerk);
int PostClerk_Init(PostClerk *clerk);
PostClerk *PostClerk_Create(void);

/* Her states (post_clerk.c). */
int PostClerk_UpdatePaused(void);
int PostClerk_EnterPaused(void);
int PostClerk_UpdateOther(PostClerk *clerk);
int PostClerk_EnterOther(void);
int PostClerk_UpdateAwait(PostClerk *clerk);
int PostClerk_EnterAwait(void);
int PostClerk_UpdateLeave(PostClerk *clerk);
int PostClerk_EnterLeave(void);
int PostClerk_UpdateAct(PostClerk *clerk);
int PostClerk_EnterAct(PostClerk *clerk);
int PostClerk_UpdateTurn(PostClerk *clerk);
int PostClerk_EnterTurn(PostClerk *clerk);
int PostClerk_UpdateTalked(void);
int PostClerk_EnterTalked(void);
int PostClerk_UpdateTalk(PostClerk *clerk);
int PostClerk_EnterTalk(PostClerk *clerk);
int PostClerk_UpdateWalk(PostClerk *clerk);
int PostClerk_EnterWalk(PostClerk *clerk);
int PostClerk_UpdateStand(PostClerk *clerk);
int PostClerk_EnterStand(PostClerk *clerk);
int PostClerk_UpdateCallOver(PostClerk *clerk);
int PostClerk_EnterCallOver(void);
int PostClerk_UpdateGreet(PostClerk *clerk);
int PostClerk_EnterGreet(void);

#endif
