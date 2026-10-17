/* The gatekeeper's talk scene (class vtable 0x02264208, at 0x658 of the gatekeeper,
 * gatekeeper.h): a scene base (scene_base.h) that shows the lines of the archive
 * "sp_npc_gatekeeper" and runs the connections the gatekeeper opens for the player.
 *
 * The player's answer to a line (its vtable slot 0x18, GatekeeperTalk_OnAnswer) goes to the
 * handlers of a table keyed by the number of the line shown (the receiver's message, byte 0x1e).
 *
 * The connection is a machine of 23 states (GATEKEEPER_TALK_*), a table of C++ pointers to
 * member functions with a flag each (data_ov048_02264344, filled at start-up by
 * __sinit_ov048_022639b0). The flagged states are run before each step of the scene (slot 0x80,
 * GatekeeperTalk_RunNetworkState); the others, when a command of the scene ends (slot 0x84,
 * GatekeeperTalk_RunTalkState). Each state shows the next line itself and moves on through
 * GatekeeperTalk_SetState; state 0 has no function.
 *
 * Over the local wireless library of overlay 66 (modes 1 and 2 of autoload_2/network.h), as a
 * child: the parents found are looked through for one that takes visitors (state 1) and the
 * player's chosen one is joined (states 4-9), the local status exchanged with it
 * (session_link.h) and this system's block sent (SystemPacket_SendSenderBlock). Over the
 * Nintendo Wi-Fi Connection (overlay 65, modes 3 and 4): the friend list is awaited (state 10),
 * the downloads and the upload of wfc_session.h made one after the other (states 11-18), a
 * friend's game joined or the session's result told (state 19), and the connection ended and
 * its downloads applied (state 20). States 21 and 22 wait for the missing character
 * (missing_npc1.h) and the activity's job 0x13 (activity_job.h).
 *
 * A wait counts down the gatekeeper's halfword at 0xe6e (Countdown_Tick16): at 0 the talk shows
 * a line and the state ends. Errors of the network layer (Net_GetError) end it the same way. */
#ifndef CLEAN_OV048_GATEKEEPER_TALK_H
#define CLEAN_OV048_GATEKEEPER_TALK_H

#include "main/scene_base.h"
#include "ov066/local_search.h"
#include "types.h"

struct Gatekeeper;

/* The states (GatekeeperTalk.state). */
#define GATEKEEPER_TALK_IDLE 0
#define GATEKEEPER_TALK_FIND_PARENT 1
#define GATEKEEPER_TALK_TAKE_FRIEND 2
#define GATEKEEPER_TALK_GROUP_CHECK 3
#define GATEKEEPER_TALK_JOIN_PARENT 4
#define GATEKEEPER_TALK_WAIT_CONNECTED 5
#define GATEKEEPER_TALK_SEND_STATUS_0 6
#define GATEKEEPER_TALK_WAIT_STATUS_0 7
#define GATEKEEPER_TALK_SEND_STATUS_1 8
#define GATEKEEPER_TALK_WAIT_STATUS_1 9
#define GATEKEEPER_TALK_WAIT_FRIENDS 10
#define GATEKEEPER_TALK_START_STATS_UPLOAD 11
#define GATEKEEPER_TALK_FINISH_STATS_UPLOAD 12
#define GATEKEEPER_TALK_START_STATS_GET 13
#define GATEKEEPER_TALK_FINISH_STATS_GET 14
#define GATEKEEPER_TALK_START_LETTER_GET 15
#define GATEKEEPER_TALK_FINISH_LETTER_GET 16
#define GATEKEEPER_TALK_START_NOTICE_GET 17
#define GATEKEEPER_TALK_FINISH_NOTICE_GET 18
#define GATEKEEPER_TALK_AFTER_DOWNLOADS 19
#define GATEKEEPER_TALK_END_WFC 20
#define GATEKEEPER_TALK_WAIT_MISSING_NPC 21
#define GATEKEEPER_TALK_WAIT_JOB_13 22
#define GATEKEEPER_TALK_STATES 23

/* The size of the data a parent of this game carries (Local_EntryData). */
#define GATEKEEPER_PARENT_DATA_SIZE 0x1a

/* The talk scene (0x814 bytes). */
typedef struct GatekeeperTalk {
    SceneBase scene;          /* 0x000: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_080[0x2e];         /* 0x080 */
    u8 saved_message;         /* 0x0ae: a line kept to show once the activity has no job */
    u8 unk_0af;               /* 0x0af */
    u32 topic;                /* 0x0b0: GatekeeperTalk_SetTopic sets it */
    s32 state;                /* 0x0b4: GATEKEEPER_TALK_* */
    struct Gatekeeper *owner; /* 0x0b8 */
    u8 unk_0bc[0x250];        /* 0x0bc */
    LocalParent parent;       /* 0x30c: the parent found by GATEKEEPER_TALK_FIND_PARENT */
    s32 profile_id;           /* 0x3ec: the friend whose game is joined (Wfc_ProfileIdAt) */
    u8 unk_3f0[0x420];        /* 0x3f0 */
    u8 unk_810;               /* 0x810: cleared by GatekeeperTalk_StartLine */
    u8 job_idle_seen;         /* 0x811: set once the activity was seen with no job */
    u8 chunks_sent;           /* 0x812: SystemPacket_SendSenderBlock's count */
    u8 choice;                /* 0x813: 0, 1 or 2, from the answers to lines 0x23, 0x28, 0x2f, 0x52 */
} GatekeeperTalk;

/* Lines chosen by the network mode or the session. */
unsigned char GatekeeperTalk_Line80Or63(GatekeeperTalk *talk);
unsigned char GatekeeperTalk_Line82Or65(GatekeeperTalk *talk);
unsigned char GatekeeperTalk_Line21Or22(GatekeeperTalk *talk);
int GatekeeperTalk_LineOfSession(GatekeeperTalk *talk);
int GatekeeperTalk_LineOfChoice(GatekeeperTalk *talk);
int GatekeeperTalk_PutErrorCode(GatekeeperTalk *talk, int code);

/* Ending a state with a line, and the checks that do. */
void GatekeeperTalk_EndWithLine(GatekeeperTalk *talk, int line, int unused);
int GatekeeperTalk_TimeOut56(GatekeeperTalk *talk);
int GatekeeperTalk_TimeOutOrError(GatekeeperTalk *talk);
int GatekeeperTalk_TimeOut65(GatekeeperTalk *talk);
int GatekeeperTalk_TimeOutByMode(GatekeeperTalk *talk);
int GatekeeperTalk_CheckError(GatekeeperTalk *talk, int lost);
int GatekeeperTalk_IsServerError(void);

/* The states. */
void GatekeeperTalk_FindParent(GatekeeperTalk *talk);
void GatekeeperTalk_TakeFriend(GatekeeperTalk *talk);
void GatekeeperTalk_GroupCheck(GatekeeperTalk *talk);
void GatekeeperTalk_JoinParent(GatekeeperTalk *talk);
void GatekeeperTalk_WaitConnected(GatekeeperTalk *talk);
void GatekeeperTalk_SendStatus0(GatekeeperTalk *talk);
void GatekeeperTalk_WaitStatus0(GatekeeperTalk *talk);
void GatekeeperTalk_SendStatus1(GatekeeperTalk *talk);
void GatekeeperTalk_WaitStatus1(GatekeeperTalk *talk);
void GatekeeperTalk_WaitFriends(GatekeeperTalk *talk);
void GatekeeperTalk_StartStatsUpload(GatekeeperTalk *talk);
void GatekeeperTalk_FinishStatsUpload(GatekeeperTalk *talk);
void GatekeeperTalk_StartStatsGet(GatekeeperTalk *talk);
void GatekeeperTalk_FinishStatsGet(GatekeeperTalk *talk);
void GatekeeperTalk_StartLetterGet(GatekeeperTalk *talk);
void GatekeeperTalk_FinishLetterGet(GatekeeperTalk *talk);
void GatekeeperTalk_StartNoticeGet(GatekeeperTalk *talk);
void GatekeeperTalk_FinishNoticeGet(GatekeeperTalk *talk);
void GatekeeperTalk_AfterDownloads(GatekeeperTalk *talk);
void GatekeeperTalk_EndWfc(GatekeeperTalk *talk);
void GatekeeperTalk_WaitMissingNpc(GatekeeperTalk *talk);
void GatekeeperTalk_WaitJob13(GatekeeperTalk *talk);
void GatekeeperTalk_SetState(GatekeeperTalk *talk, u32 state);

/* Its vtable slots. */
void GatekeeperTalk_RunTalkState(GatekeeperTalk *talk);
void GatekeeperTalk_RunNetworkState(GatekeeperTalk *talk);
void GatekeeperTalk_OnAnswer(GatekeeperTalk *talk);

/* The handlers of the answers, by line. */
void GatekeeperTalk_OnAnswer5f(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer6b(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer2c(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswerTo62(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswerTo59(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer51(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswerKeep(GatekeeperTalk *talk, int answer, int line);
void GatekeeperTalk_OnAnswer7f(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer14(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer41(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer15(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswerTo21Or22(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswerSession(GatekeeperTalk *talk, int answer);

#endif
