/* The gatekeeper's talk scene: its start line, the ends of its lines, the answers to the menus
 * of the connections, and its constructor and destructors (gatekeeper_talk_lines.h). */
#include "gatekeeper_talk_lines.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/network.h"
#include "clean.h"
#include "gatekeeper.h"
#include "main/calendar.h"
#include "main/design_info.h"
#include "main/library_overlay.h"
#include "main/message_receiver.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/start_kind.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "main/wfc_delivery.h"
#include "main/wfc_stats.h"
#include "main/wifi_friends.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(GatekeeperTalkStart) == 8, "GatekeeperTalkStart");

/* The network modes (autoload_2/network.c): a child of the local wireless library, and the
 * Wi-Fi Connection's hosting and joining. */
#define GATEKEEPER_LINES_MODE_LOCAL_CHILD 2
#define GATEKEEPER_LINES_MODE_HOSTING 3
#define GATEKEEPER_LINES_MODE_JOINING 4

/* The players a session is started for (Session_Start). */
#define GATEKEEPER_LINES_PLAYERS 4

/* The waits, in frames (Gatekeeper.countdown). */
#define GATEKEEPER_LINES_WAIT_LOCAL 200
#define GATEKEEPER_LINES_WAIT_WFC 2400

/* The talk's members after its scene base (offsets in GatekeeperTalk), built and destroyed
 * with it. */
#define GATEKEEPER_LINES_DESIGN 0x0bc
#define GATEKEEPER_LINES_SCREEN_B 0x2f0 /* the second buffer screen 4 is given */
#define GATEKEEPER_LINES_LETTER 0x3f0
#define GATEKEEPER_LINES_NOTICE 0x504
#define GATEKEEPER_LINES_STATS 0x5d8

/* The talk's vtable slot that resets it (SceneBase_Reset). */
#define GATEKEEPER_LINES_SLOT_RESET 2

/* The screens of the scene's command 0 (scene_command.h) it opens: screen 2 in mode 0x3c (the
 * friend roster, whose pick GatekeeperTalk_TakeFriend reads), and screen 4. */
#define GATEKEEPER_LINES_SCREEN_MODE 2
#define GATEKEEPER_LINES_FRIEND_SCREEN 0x3c
#define GATEKEEPER_LINES_SCREEN_ARGS 4

/* The friend code's parts in the talk: three groups of four digits. */
#define GATEKEEPER_LINES_CODE_HIGH 5
#define GATEKEEPER_LINES_CODE_MIDDLE 8
#define GATEKEEPER_LINES_CODE_LOW 9
#define GATEKEEPER_LINES_CODE_DIGITS 4
#define GATEKEEPER_LINES_CODE_FORMAT 6

/* The current player's flag set once it has met the gatekeeper, and the one that keeps it from
 * the Wi-Fi Connection's menus. */
#define GATEKEEPER_LINES_FLAG_MET 5
#define GATEKEEPER_LINES_FLAG_1 1

/* The line ends GatekeeperTalk_OnMessageEnded looks through. */
#define GATEKEEPER_LINE_ENDS 28

/* The session. */
extern NetSession *data_020ccf94;
/* "sp_npc_gatekeeper", the archive of its lines (the first word of data_ov048_02263d20). */
extern const char *const data_ov048_02263d20;
/* The class's vtable. */
extern const u8 data_ov048_02264208[];
/* The line shown for each choice once the player's user data is ready: 0x24, 0x41, 0x7f. */
extern const u8 data_ov048_02263964[];

/* The start lines by topic; the names of all but topic 8 ("sp_etc_sequence4") are filled from
 * data_ov048_02263d20 on the first call (bit 0 of data_ov048_0226472c). */
extern GatekeeperTalkStart data_ov048_022641a8[GATEKEEPER_TOPICS];
extern u32 data_ov048_0226472c;

/* A line end: the line and its handler, filled from the constants below on the first call (bit
 * 0 of data_ov048_02264724). */
typedef struct GatekeeperLineEnd {
    s32 line;
    MemberPointer handler;
} GatekeeperLineEnd;
static_assert(sizeof(GatekeeperLineEnd) == 12, "GatekeeperLineEnd");
extern GatekeeperLineEnd data_ov048_02264458[GATEKEEPER_LINE_ENDS];
extern u32 data_ov048_02264724;
extern const MemberPointer data_ov048_02263fbc, data_ov048_022640cc, data_ov048_02263ebc, data_ov048_02263eb4,
    data_ov048_02263eac, data_ov048_02263ea4, data_ov048_02263e9c, data_ov048_02263e94, data_ov048_02263e8c,
    data_ov048_02263e84, data_ov048_02263e7c, data_ov048_02263e74, data_ov048_02263e6c, data_ov048_02263e64,
    data_ov048_02263e5c, data_ov048_02263e54, data_ov048_02263fdc, data_ov048_02263fc4, data_ov048_02263fb4,
    data_ov048_02263fa4, data_ov048_02263e2c, data_ov048_02263e24, data_ov048_02263e1c, data_ov048_02263f6c,
    data_ov048_02263f5c, data_ov048_02263dcc, data_ov048_02263f34, data_ov048_02263ddc;

/* Overlay 4's scene that leaves for the next line. */
extern int func_ov004_0222d4d4(void);
extern int func_ov004_0222d518(void);

/* ---- Helpers */

static TalkObject *gatekeeper_lines_object(const GatekeeperTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

static u8 gatekeeper_lines_shown(const GatekeeperTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* Line `line` of "sp_npc_gatekeeper" given to the talk to show. */
static void gatekeeper_lines_say(GatekeeperTalk *talk, int line)
{
    u8 message = (u8) line;
    TalkObject_SetMessage(gatekeeper_lines_object(talk), &message, data_ov048_02263d20);
}

static u8 *gatekeeper_lines_member(GatekeeperTalk *talk, int offset)
{
    return (u8 *) talk + offset;
}

static SceneCommandScene *gatekeeper_lines_commands(GatekeeperTalk *talk)
{
    return (SceneCommandScene *) (void *) talk;
}

/* The talk's user data of the Wi-Fi Connection: the current player's account's. */
static u8 *gatekeeper_lines_user_data(void)
{
    return WifiAccount_GetUserData(PlayerRecord_WifiAccount(PlayerRecords_Current()));
}

/* A wait of `frames` (the gatekeeper's countdown), then the state `state`. */
static void gatekeeper_lines_wait(GatekeeperTalk *talk, u16 frames, u32 state)
{
    talk->owner->countdown = frames;
    GatekeeperTalk_SetState(talk, state);
}

/* ---- Answers to lines */

/* func_ov048_02261be8 (lines 0x0f and 0x22): answer 0: line 8 with the current player's flag 1,
 * else 0x50 when the session is linked and this system has slot 0, else 0x51 when this system's
 * slot is taken, else 0x52. Answer 1: line 0xe with the flag, else the line of the session
 * (GatekeeperTalk_LineOfSession). Answer 2, when this system has not slot 0 of the session
 * (else nothing): line 8 with the flag; else, with overlay 65 switched in, line 0x2f when the
 * library refuses the player's user data (Wfc_Call021012c4), else 0x29 with the player's friend
 * code in the talk when the data is authentic, else 0x23; then overlay 68. Any other answer
 * shows nothing. */
void GatekeeperTalk_OnAnswerSessionOrCode(GatekeeperTalk *talk, int answer)
{
    u8 *record = PlayerRecords_Current();
    int line = 0xff;

    switch (answer) {
        case 0: {
            NetSession *session;
            if (PlayerRecord_TestFlag(record, GATEKEEPER_LINES_FLAG_1)) {
                line = 8;
                break;
            }
            session = data_020ccf94;
            if (Session_IsLinked(session) && Session_IsLocalSlot(session, 0)) {
                line = 0x50;
                break;
            }
            line = Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot) ? 0x51 : 0x52;
            break;
        }
        case 1:
            if (PlayerRecord_TestFlag(record, GATEKEEPER_LINES_FLAG_1)) {
                line = 0xe;
            } else {
                line = GatekeeperTalk_LineOfSession(talk);
            }
            break;
        case 2: {
            u8 *user_data;
            if (Session_IsLocalSlot(data_020ccf94, 0)) {
                break;
            }
            if (PlayerRecord_TestFlag(record, GATEKEEPER_LINES_FLAG_1)) {
                line = 8;
                break;
            }
            LibraryOverlay_Switch65();
            user_data = WifiAccount_GetUserData(PlayerRecord_WifiAccount(record));
            if (!Wfc_Call021012c4(user_data)) {
                line = 0x2f;
            } else if (Wfc_IsAuthentic(user_data)) {
                line = 0x29;
                GatekeeperTalk_PutFriendCode(talk, Wfc_GetUserKey(user_data));
            } else {
                line = 0x23;
            }
            LibraryOverlay_Switch68();
            break;
        }
        default:
            break;
    }
    if (line != 0xff) {
        gatekeeper_lines_say(talk, line);
    }
}
CLEAN_AS(func_ov048_02261be8, GatekeeperTalk_OnAnswerSessionOrCode)

/* func_ov048_02261ce4 (line 0x0a): answer 0, line 0x19. */
void GatekeeperTalk_OnAnswer0a(GatekeeperTalk *talk, int answer)
{
    if (answer == 0) {
        gatekeeper_lines_say(talk, 0x19);
    }
}
CLEAN_AS(func_ov048_02261ce4, GatekeeperTalk_OnAnswer0a)

/* func_ov048_02261d08: the line for the player's choice. For choice 1 or 2 without a friend in
 * the current player's roster, line 0x70, or 0x6f for choice 2. Else, with overlay 65 switched
 * in: when the player's user data is authentic and the library takes it (Wfc_Call021012c4),
 * the choice's line (0x24, 0x41, 0x7f); authentic but not taken, byte 0x810 set and line 0x72;
 * not authentic, line 0x71. Then overlay 68.
 * QUIRK: the user data is found before overlay 65 is switched in. */
void GatekeeperTalk_SayChoiceLine(GatekeeperTalk *talk)
{
    u8 *user_data;

    if (talk->choice != 0 && !GatekeeperTalk_HasFriends(talk)) {
        gatekeeper_lines_say(talk, talk->choice == 2 ? 0x6f : 0x70);
        return;
    }
    user_data = gatekeeper_lines_user_data();
    LibraryOverlay_Switch65();
    if (Wfc_IsAuthentic(user_data)) {
        if (Wfc_Call021012c4(user_data)) {
            gatekeeper_lines_say(talk, data_ov048_02263964[talk->choice]);
        } else {
            talk->unk_810 = 1;
            gatekeeper_lines_say(talk, 0x72);
        }
    } else {
        gatekeeper_lines_say(talk, 0x71);
    }
    LibraryOverlay_Switch68();
}
CLEAN_AS(func_ov048_02261d08, GatekeeperTalk_SayChoiceLine)

/* func_ov048_02261ddc (line 0x3d): answer 1, choice 1 and its line; answer 2, line 0x21 or
 * 0x22. */
void GatekeeperTalk_OnAnswer3d(GatekeeperTalk *talk, int answer)
{
    if (answer == 1) {
        talk->choice = 1;
        GatekeeperTalk_SayChoiceLine(talk);
    } else if (answer == 2) {
        gatekeeper_lines_say(talk, GatekeeperTalk_Line21Or22(talk));
    }
}
CLEAN_AS(func_ov048_02261ddc, GatekeeperTalk_OnAnswer3d)

/* func_ov048_02261e1c (line 0x52): answer 1, choice 2 and its line; answer 2, line 0x21 or
 * 0x22. */
void GatekeeperTalk_OnAnswer52(GatekeeperTalk *talk, int answer)
{
    if (answer == 1) {
        talk->choice = 2;
        GatekeeperTalk_SayChoiceLine(talk);
    } else if (answer == 2) {
        gatekeeper_lines_say(talk, GatekeeperTalk_Line21Or22(talk));
    }
}
CLEAN_AS(func_ov048_02261e1c, GatekeeperTalk_OnAnswer52)

/* func_ov048_02261e5c (lines 0x23, 0x28, 0x2f): answer 0, choice 0 and its line. */
void GatekeeperTalk_OnAnswerChoice0(GatekeeperTalk *talk, int answer)
{
    if (answer == 0) {
        talk->choice = 0;
        GatekeeperTalk_SayChoiceLine(talk);
    }
}
CLEAN_AS(func_ov048_02261e5c, GatekeeperTalk_OnAnswerChoice0)

/* func_ov048_02261e78 (line 0x71): answer 0, by the choice: 2, line 0x5b kept and line 0x6a;
 * 1, line 0x3e kept and line 0x6a; 0, line 0x25; any other, nothing. */
void GatekeeperTalk_OnAnswer71(GatekeeperTalk *talk, int answer)
{
    int line = 0xff;

    if (answer != 0) {
        return;
    }
    switch (talk->choice) {
        case 2:
            talk->saved_message = 0x5b;
            line = 0x6a;
            break;
        case 1:
            talk->saved_message = 0x3e;
            line = 0x6a;
            break;
        case 0:
            line = 0x25;
            break;
        default:
            break;
    }
    if (line != 0xff) {
        gatekeeper_lines_say(talk, line);
    }
}
CLEAN_AS(func_ov048_02261e78, GatekeeperTalk_OnAnswer71)

/* func_ov048_02261ed0 (line 0x57): answer 2, the session ended. */
void GatekeeperTalk_OnAnswer57(GatekeeperTalk *talk, int answer)
{
    if (answer == 2) {
        GatekeeperTalk_EndSession(talk);
    }
}
CLEAN_AS(func_ov048_02261ed0, GatekeeperTalk_OnAnswer57)

/* func_ov048_02261ee4 (line 0x74): answer 0, the current player's account made anew with
 * overlay 65 switched in (then overlay 68); then as line 0x71 (GatekeeperTalk_OnAnswer71). */
void GatekeeperTalk_OnAnswer74(GatekeeperTalk *talk, int answer)
{
    if (answer == 0) {
        LibraryOverlay_Switch65();
        WifiAccount_Init(PlayerRecord_WifiAccount(PlayerRecords_Current()));
        LibraryOverlay_Switch68();
    }
    GatekeeperTalk_OnAnswer71(talk, answer);
}
CLEAN_AS(func_ov048_02261ee4, GatekeeperTalk_OnAnswer74)

/* ---- The end of a line */

/* Obj_ov048_02264208::func_ov048_02261f14 (vtable slot 0x14, a line ended): each handler of the
 * line shown is called. The line is read again for each entry, so a handler that shows a line
 * with handlers further down the table has them run too. */
void GatekeeperTalk_OnMessageEnded(GatekeeperTalk *talk)
{
    static const MemberPointer *const handlers[GATEKEEPER_LINE_ENDS] = {
        &data_ov048_02263fbc, /* 0x00: GatekeeperTalk_SayLine10OrF */
        &data_ov048_022640cc, /* 0x04: GatekeeperTalk_SayLine10OrF */
        &data_ov048_02263ebc, /* 0x05: GatekeeperTalk_SayLine10OrF */
        &data_ov048_02263eb4, /* 0x06: GatekeeperTalk_SayLine10OrF */
        &data_ov048_02263eac, /* 0x07: GatekeeperTalk_SayLine10OrF */
        &data_ov048_02263ea4, /* 0x38: GatekeeperTalk_EndConnection */
        &data_ov048_02263e9c, /* 0x46: GatekeeperTalk_SetOwnerState6 */
        &data_ov048_02263e94, /* 0x54: GatekeeperTalk_StartFindParent */
        &data_ov048_02263e8c, /* 0x3e: GatekeeperTalk_StartWfc */
        &data_ov048_02263e84, /* 0x5b: GatekeeperTalk_StartWfc */
        &data_ov048_02263e7c, /* 0x6c: GatekeeperTalk_SetOwnerState6 */
        &data_ov048_02263e74, /* 0x47: GatekeeperTalk_SetOwnerState5 */
        &data_ov048_02263e6c, /* 0x48: GatekeeperTalk_SetOwnerState5 */
        &data_ov048_02263e64, /* 0x49: GatekeeperTalk_SetOwnerState5 */
        &data_ov048_02263e5c, /* 0x25: GatekeeperTalk_StartWfc */
        &data_ov048_02263e54, /* 0x55: GatekeeperTalk_OpenScreen4 */
        &data_ov048_02263fdc, /* 0x5d: GatekeeperTalk_OpenFriendScreen */
        &data_ov048_02263fc4, /* 0x6d: GatekeeperTalk_OpenFriendScreen */
        &data_ov048_02263fb4, /* 0x62: GatekeeperTalk_JoinFriend */
        &data_ov048_02263fa4, /* 0x59: GatekeeperTalk_StartJoinParent */
        &data_ov048_02263e2c, /* 0x68: GatekeeperTalk_SetOwnerState8 */
        &data_ov048_02263e24, /* 0x0d: GatekeeperTalk_SetOwnerStateA */
        &data_ov048_02263e1c, /* 0x11: GatekeeperTalk_SayLine21Or22 */
        &data_ov048_02263f6c, /* 0x58: GatekeeperTalk_SayLine21Or22 */
        &data_ov048_02263f5c, /* 0x61: GatekeeperTalk_SayLine21Or22 */
        &data_ov048_02263dcc, /* 0x75: GatekeeperTalk_SayCodeOrChoice */
        &data_ov048_02263f34, /* 0x12: GatekeeperTalk_StartSendStatus1 */
        &data_ov048_02263ddc, /* 0x6a: GatekeeperTalk_StartWaitMissingNpc */
    };
    u32 flags = data_ov048_02264724;

    if ((flags & 1) == 0) {
        for (int i = 0; i < GATEKEEPER_LINE_ENDS; i++) {
            data_ov048_02264458[i].handler = *handlers[i];
        }
        data_ov048_02264724 = flags | 1;
    }
    for (u32 i = 0; i < GATEKEEPER_LINE_ENDS; i++) {
        const GatekeeperLineEnd *entry = &data_ov048_02264458[i];
        if (entry->line == gatekeeper_lines_shown(talk)) {
            MemberPointer_CallVoid(&entry->handler, talk);
        }
    }
}
CLEAN_AS(_ZN18Obj_ov048_0226420819func_ov048_02261f14Ev, GatekeeperTalk_OnMessageEnded)

/* func_ov048_02262114 (line 0x12): the talk held with the spinner's sound, a wait of 200 frames
 * and GATEKEEPER_TALK_SEND_STATUS_1. */
void GatekeeperTalk_StartSendStatus1(GatekeeperTalk *talk)
{
    GatekeeperTalk_HoldWithSpinner(talk, 1);
    gatekeeper_lines_wait(talk, GATEKEEPER_LINES_WAIT_LOCAL, GATEKEEPER_TALK_SEND_STATUS_1);
}
CLEAN_AS(func_ov048_02262114, GatekeeperTalk_StartSendStatus1)

/* func_ov048_0226213c (line 0x75): with byte 0x810 set, the current player's friend code put in
 * the talk and line 0x76; else the line of the player's choice (GatekeeperTalk_LineOfChoice). */
void GatekeeperTalk_SayCodeOrChoice(GatekeeperTalk *talk)
{
    if (talk->unk_810 != 0) {
        GatekeeperTalk_PutFriendCode(talk, Wfc_GetUserKey(gatekeeper_lines_user_data()));
        gatekeeper_lines_say(talk, 0x76);
    } else {
        gatekeeper_lines_say(talk, GatekeeperTalk_LineOfChoice(talk));
    }
}
CLEAN_AS(func_ov048_0226213c, GatekeeperTalk_SayCodeOrChoice)

/* func_ov048_022621a0 (lines 0x11, 0x58, 0x61): line 0x21 or 0x22. */
void GatekeeperTalk_SayLine21Or22(GatekeeperTalk *talk)
{
    gatekeeper_lines_say(talk, GatekeeperTalk_Line21Or22(talk));
}
CLEAN_AS(func_ov048_022621a0, GatekeeperTalk_SayLine21Or22)

/* func_ov048_022621c8 (line 0x0d): the gatekeeper's state 0xa. */
void GatekeeperTalk_SetOwnerStateA(GatekeeperTalk *talk)
{
    Gatekeeper_SetState(talk->owner, GATEKEEPER_STATE_A);
}
CLEAN_AS(func_ov048_022621c8, GatekeeperTalk_SetOwnerStateA)

/* func_ov048_022621d8 (line 0x68): the gatekeeper's state 8. */
void GatekeeperTalk_SetOwnerState8(GatekeeperTalk *talk)
{
    Gatekeeper_SetState(talk->owner, GATEKEEPER_STATE_8);
}
CLEAN_AS(func_ov048_022621d8, GatekeeperTalk_SetOwnerState8)

/* func_ov048_022621e8 (line 0x62): the session's connect mode 1; unless the network joins over
 * the Wi-Fi Connection (mode 4), the Wi-Fi Connection is started (GatekeeperTalk_StartWfc);
 * else the talk held with the spinner's sound, the friend taken is joined (overlay 65 in), a
 * wait of 2400 frames and GATEKEEPER_TALK_WAIT_CONNECTED. */
void GatekeeperTalk_JoinFriend(GatekeeperTalk *talk)
{
    Session_SetConnectMode(data_020ccf94, 1);
    if (Net_GetMode() != GATEKEEPER_LINES_MODE_JOINING) {
        GatekeeperTalk_StartWfc(talk);
    } else {
        int profile_id;
        GatekeeperTalk_HoldWithSpinner(talk, 1);
        profile_id = talk->profile_id;
        LibraryOverlay_Require65();
        Wfc_JoinFriendGame(profile_id);
        gatekeeper_lines_wait(talk, GATEKEEPER_LINES_WAIT_WFC, GATEKEEPER_TALK_WAIT_CONNECTED);
    }
}
CLEAN_AS(func_ov048_022621e8, GatekeeperTalk_JoinFriend)

/* func_ov048_0226224c (line 0x59): the talk held with the spinner's sound; when the network is
 * already a local child (mode 2) the session's connect mode 1, else a session of mode 2 with
 * connect mode 1 started; a wait of 200 frames and GATEKEEPER_TALK_JOIN_PARENT. */
void GatekeeperTalk_StartJoinParent(GatekeeperTalk *talk)
{
    GatekeeperTalk_HoldWithSpinner(talk, 1);
    if (Net_GetMode() == GATEKEEPER_LINES_MODE_LOCAL_CHILD) {
        Session_SetConnectMode(data_020ccf94, 1);
    } else {
        GatekeeperTalk_StartSession(talk, GATEKEEPER_LINES_MODE_LOCAL_CHILD, 1);
    }
    gatekeeper_lines_wait(talk, GATEKEEPER_LINES_WAIT_LOCAL, GATEKEEPER_TALK_JOIN_PARENT);
}
CLEAN_AS(func_ov048_0226224c, GatekeeperTalk_StartJoinParent)

/* func_ov048_02262298 (lines 0x5d, 0x6d): screen 2 asked for in mode 0x3c (the friend roster),
 * then GATEKEEPER_TALK_TAKE_FRIEND. */
void GatekeeperTalk_OpenFriendScreen(GatekeeperTalk *talk)
{
    SceneCommand_SetScreenMode(gatekeeper_lines_commands(talk), GATEKEEPER_LINES_FRIEND_SCREEN, 0);
    SceneCommand_RequestScreen(gatekeeper_lines_commands(talk), GATEKEEPER_LINES_SCREEN_MODE);
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_TAKE_FRIEND);
}
CLEAN_AS(func_ov048_02262298, GatekeeperTalk_OpenFriendScreen)

/* func_ov048_022622bc (line 0x55): screen 4 asked for with the talk's buffers at 0x30c and
 * 0x2f0, then GATEKEEPER_TALK_GROUP_CHECK. */
void GatekeeperTalk_OpenScreen4(GatekeeperTalk *talk)
{
    SceneCommand_SetScreenArgs(gatekeeper_lines_commands(talk), (s32) (intptr_t) &talk->parent,
                               (s32) (intptr_t) gatekeeper_lines_member(talk, GATEKEEPER_LINES_SCREEN_B), 0);
    SceneCommand_RequestScreen(gatekeeper_lines_commands(talk), GATEKEEPER_LINES_SCREEN_ARGS);
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_GROUP_CHECK);
}
CLEAN_AS(func_ov048_022622bc, GatekeeperTalk_OpenScreen4)

/* func_ov048_022622ec (line 0x54): the talk held with the spinner's sound, a session of mode 2
 * with connect mode 2 started, a wait of 200 frames and GATEKEEPER_TALK_FIND_PARENT. */
void GatekeeperTalk_StartFindParent(GatekeeperTalk *talk)
{
    GatekeeperTalk_HoldWithSpinner(talk, 1);
    GatekeeperTalk_StartSession(talk, GATEKEEPER_LINES_MODE_LOCAL_CHILD, 2);
    gatekeeper_lines_wait(talk, GATEKEEPER_LINES_WAIT_LOCAL, GATEKEEPER_TALK_FIND_PARENT);
}
CLEAN_AS(func_ov048_022622ec, GatekeeperTalk_StartFindParent)

/* func_ov048_02262320 (lines 0x25, 0x3e, 0x5b): the talk held with the spinner's sound, a
 * session of mode 4 (joining over the Wi-Fi Connection) with connect mode 2 started, a wait of
 * 2400 frames and GATEKEEPER_TALK_WAIT_FRIENDS. */
void GatekeeperTalk_StartWfc(GatekeeperTalk *talk)
{
    GatekeeperTalk_HoldWithSpinner(talk, 1);
    GatekeeperTalk_StartSession(talk, GATEKEEPER_LINES_MODE_JOINING, 2);
    gatekeeper_lines_wait(talk, GATEKEEPER_LINES_WAIT_WFC, GATEKEEPER_TALK_WAIT_FRIENDS);
}
CLEAN_AS(func_ov048_02262320, GatekeeperTalk_StartWfc)

/* func_ov048_02262358 (lines 0x46, 0x6c): the gatekeeper's state 6. */
void GatekeeperTalk_SetOwnerState6(GatekeeperTalk *talk)
{
    Gatekeeper_SetState(talk->owner, GATEKEEPER_STATE_6);
}
CLEAN_AS(func_ov048_02262358, GatekeeperTalk_SetOwnerState6)

/* func_ov048_02262368 (lines 0x47, 0x48, 0x49): the gatekeeper's state 5. */
void GatekeeperTalk_SetOwnerState5(GatekeeperTalk *talk)
{
    Gatekeeper_SetState(talk->owner, GATEKEEPER_STATE_5);
}
CLEAN_AS(func_ov048_02262368, GatekeeperTalk_SetOwnerState5)

/* func_ov048_02262378: the talk released: its spinner stopped and its hold let go. */
void GatekeeperTalk_Release(GatekeeperTalk *talk)
{
    TalkObject *object = gatekeeper_lines_object(talk);
    TalkObject_StopSpinner(object);
    TalkObject_Release(object);
}
CLEAN_AS(func_ov048_02262378, GatekeeperTalk_Release)

/* func_ov048_02262390: the talk's spinner started (with its sound when `sound` is set) and the
 * talk held. */
void GatekeeperTalk_HoldWithSpinner(GatekeeperTalk *talk, int sound)
{
    TalkObject *object = gatekeeper_lines_object(talk);
    TalkObject_StartSpinner(object, sound != 0 ? 1 : 0);
    TalkObject_Hold(object);
}
CLEAN_AS(func_ov048_02262390, GatekeeperTalk_HoldWithSpinner)

/* func_ov048_022623b8 (line 0x38): the gatekeeper's state 7 and the link's status reset; then
 * over the Wi-Fi Connection GATEKEEPER_TALK_END_WFC, else the session ended. */
void GatekeeperTalk_EndConnection(GatekeeperTalk *talk)
{
    Gatekeeper_SetState(talk->owner, GATEKEEPER_STATE_7);
    Session_ResetLinkStatus();
    if (Net_GetMode() == GATEKEEPER_LINES_MODE_HOSTING || Net_GetMode() == GATEKEEPER_LINES_MODE_JOINING) {
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_END_WFC);
    } else {
        GatekeeperTalk_EndSession(talk);
    }
}
CLEAN_AS(func_ov048_022623b8, GatekeeperTalk_EndConnection)

/* func_ov048_022623f0 (lines 0, 4, 5, 6, 7, the greetings): line 0x10 when this system has slot
 * 0 of the session, else 0xf. */
void GatekeeperTalk_SayLine10OrF(GatekeeperTalk *talk)
{
    gatekeeper_lines_say(talk, Session_IsLocalSlot(data_020ccf94, 0) ? 0x10 : 0xf);
}
CLEAN_AS(func_ov048_022623f0, GatekeeperTalk_SayLine10OrF)

/* func_ov048_0226242c (line 0x6a): the talk held with a silent spinner, then
 * GATEKEEPER_TALK_WAIT_MISSING_NPC. */
void GatekeeperTalk_StartWaitMissingNpc(GatekeeperTalk *talk)
{
    GatekeeperTalk_HoldWithSpinner(talk, 0);
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_WAIT_MISSING_NPC);
}
CLEAN_AS(func_ov048_0226242c, GatekeeperTalk_StartWaitMissingNpc)

/* ---- Its start, topic and session */

/* func_ov048_02262444 (vtable slot 0x78, the talk starting): bytes 0x810 and 0x811 cleared and
 * the topic chosen: GATEKEEPER_TOPIC_SPECIAL_START when the game started in a special way; topic
 * 6 kept (overlay 4's func_ov004_0222d518 called unless func_ov004_0222d4d4 agrees); topics 7,
 * 9 and 10 kept; else GATEKEEPER_TOPIC_NOT_HOST when the system may not host, the first meeting
 * (the current player's flag 5 then set) when the flag is clear, else the part of the day plus
 * 1. A topic of the table (0-10) gives `out` its line and message file:
 *   0: 0, 1-4: 4, 5, 6, 7, 5: 0xa, 6: 0x68, 7: 0xd, 8: 9 of "sp_etc_sequence4", 9: 0x47,
 *   10: 0x48 (all others of "sp_npc_gatekeeper"). */
void GatekeeperTalk_StartLine(GatekeeperTalk *talk, GatekeeperTalkStart *out)
{
    u8 *record;
    s32 topic;

    if ((data_ov048_0226472c & 1) == 0) {
        const char *name = data_ov048_02263d20;
        for (int i = 0; i < GATEKEEPER_TOPICS; i++) {
            if (i != GATEKEEPER_TOPIC_SPECIAL_START) {
                data_ov048_022641a8[i].name = name;
            }
        }
        data_ov048_0226472c |= 1;
    }

    talk->job_idle_seen = 0;
    talk->unk_810 = 0;
    record = PlayerRecords_Current();

    if (StartKind_IsSet()) {
        GatekeeperTalk_SetTopic(talk, GATEKEEPER_TOPIC_SPECIAL_START);
    } else if (GatekeeperTalk_Topic(talk) == GATEKEEPER_TOPIC_6) {
        if (func_ov004_0222d4d4() == 0) {
            func_ov004_0222d518();
        }
    } else if (GatekeeperTalk_Topic(talk) == GATEKEEPER_TOPIC_7 ||
               GatekeeperTalk_Topic(talk) == GATEKEEPER_TOPIC_CALL_LINKED ||
               GatekeeperTalk_Topic(talk) == GATEKEEPER_TOPIC_CALL_ALONE) {
        /* kept */
    } else if (!TalkChecks_IsHostOrAlone()) {
        GatekeeperTalk_SetTopic(talk, GATEKEEPER_TOPIC_NOT_HOST);
    } else if (!PlayerRecord_TestFlag(record, GATEKEEPER_LINES_FLAG_MET)) {
        GatekeeperTalk_SetTopic(talk, GATEKEEPER_TOPIC_FIRST_MEETING);
        PlayerRecord_SetFlag(record, GATEKEEPER_LINES_FLAG_MET);
    } else {
        GatekeeperTalk_SetTopic(talk, (u32) (Calendar_PartOfDay() + GATEKEEPER_TOPIC_PART_OF_DAY));
    }

    topic = (s32) talk->topic;
    if (topic >= 0 && topic < GATEKEEPER_TOPICS) {
        out->message = data_ov048_022641a8[topic].message;
        out->name = data_ov048_022641a8[topic].name;
    }
}
CLEAN_AS(func_ov048_02262444, GatekeeperTalk_StartLine)

/* func_ov048_0226254c: whether the current player's friend roster has a friend. */
int GatekeeperTalk_HasFriends(GatekeeperTalk *talk)
{
    WifiFriend *friends = WifiFriendList_GetEntries(PlayerRecord_WifiFriends(PlayerRecords_Current()));
    (void) talk;
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        if (WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i]))) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov048_0226254c, GatekeeperTalk_HasFriends)

/* func_ov048_02262588: the friend code `key` (12 decimal digits) put in the talk's parts 5, 8
 * and 9, four digits each, highest first. */
void GatekeeperTalk_PutFriendCode(GatekeeperTalk *talk, unsigned long long key)
{
    unsigned long long high = key / 100000000ULL;
    unsigned long long rest = key - high * 100000000ULL;
    unsigned long long middle = rest / 10000ULL;
    u32 low = (u32) (key - middle * 10000ULL - high * 100000000ULL);

    SceneBase_PutValue(&talk->scene, (int) (u32) high, GATEKEEPER_LINES_CODE_HIGH, GATEKEEPER_LINES_CODE_DIGITS,
                       GATEKEEPER_LINES_CODE_FORMAT, 0);
    SceneBase_PutValue(&talk->scene, (int) (u32) middle, GATEKEEPER_LINES_CODE_MIDDLE, GATEKEEPER_LINES_CODE_DIGITS,
                       GATEKEEPER_LINES_CODE_FORMAT, 0);
    SceneBase_PutValue(&talk->scene, (int) low, GATEKEEPER_LINES_CODE_LOW, GATEKEEPER_LINES_CODE_DIGITS,
                       GATEKEEPER_LINES_CODE_FORMAT, 0);
}
CLEAN_AS(func_ov048_02262588, GatekeeperTalk_PutFriendCode)

/* func_ov048_02262618: a session of network mode `mode` for four players with `connect_mode`
 * started, with the library's overlay switched in first: 65 for the Wi-Fi Connection's modes 3
 * and 4, 66 for the local wireless modes 1 and 2. */
void GatekeeperTalk_StartSession(GatekeeperTalk *talk, unsigned int mode, int connect_mode)
{
    (void) talk;
    switch (mode) {
        case 3:
        case 4:
            LibraryOverlay_Switch65();
            break;
        case 1:
        case 2:
            LibraryOverlay_Switch66();
            break;
        default:
            break;
    }
    Session_Start((int) mode, GATEKEEPER_LINES_PLAYERS, connect_mode);
}
CLEAN_AS(func_ov048_02262618, GatekeeperTalk_StartSession)

/* func_ov048_02262658: the session ended; once it has, overlay 68 switched back in. What
 * LibraryOverlay_Switch68 answers, or 0 while the session has not ended. */
int GatekeeperTalk_EndSession(GatekeeperTalk *talk)
{
    int result = Session_End();
    (void) talk;
    if (result != 0) {
        result = LibraryOverlay_Switch68();
    }
    return result;
}
CLEAN_AS(func_ov048_02262658, GatekeeperTalk_EndSession)

/* func_ov048_02262670 */
u32 GatekeeperTalk_Topic(GatekeeperTalk *talk)
{
    return talk->topic;
}
CLEAN_AS(func_ov048_02262670, GatekeeperTalk_Topic)

/* func_ov048_02262678 */
void GatekeeperTalk_SetTopic(GatekeeperTalk *talk, u32 topic)
{
    talk->topic = topic;
}
CLEAN_AS(func_ov048_02262678, GatekeeperTalk_SetTopic)

/* func_ov048_02262680: the talk reset (its vtable slot 2), given its gatekeeper and no topic. */
void GatekeeperTalk_Start(GatekeeperTalk *talk, struct Gatekeeper *owner)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(GatekeeperTalk *))(uintptr_t) vtable[GATEKEEPER_LINES_SLOT_RESET])(talk);
    talk->owner = owner;
    talk->topic = GATEKEEPER_TOPIC_NONE;
}
CLEAN_AS(func_ov048_02262680, GatekeeperTalk_Start)

/* The members destroyed, last built first. */
static void gatekeeper_lines_destruct_members(GatekeeperTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov048_02264208;
    WfcStats_Destruct((WfcStats *) (void *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_STATS));
    WfcDelivery_DestructNotice((WfcNotice *) (void *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_NOTICE));
    WfcDelivery_DestructLetter((WfcLetter *) (void *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_LETTER));
    Design_Destruct((Design *) (void *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_DESIGN));
    SceneBase_DestructBody(talk);
}

/* func_ov048_022626a4 (vtable slot 1): destructed, then freed. */
GatekeeperTalk *GatekeeperTalk_DestructDelete(GatekeeperTalk *talk)
{
    gatekeeper_lines_destruct_members(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov048_022626a4, GatekeeperTalk_DestructDelete)

/* func_ov048_022626f0 (vtable slot 0): the destructor: its statistics, notice, letter and
 * design, then the scene base's. */
GatekeeperTalk *GatekeeperTalk_Destruct(GatekeeperTalk *talk)
{
    gatekeeper_lines_destruct_members(talk);
    return talk;
}
CLEAN_AS(func_ov048_022626f0, GatekeeperTalk_Destruct)

/* func_ov048_02262738: the constructor: the scene base, its vtable, then its design (0xbc),
 * letter (0x3f0), notice (0x504) and statistics (0x5d8). */
GatekeeperTalk *GatekeeperTalk_Construct(GatekeeperTalk *talk)
{
    SceneBase_Construct(&talk->scene);
    *(const u8 **) (void *) talk = data_ov048_02264208;
    Design_Construct((char *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_DESIGN));
    WfcDelivery_ConstructLetter((WfcLetter *) (void *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_LETTER));
    WfcDelivery_ConstructNotice((WfcNotice *) (void *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_NOTICE));
    WfcStats_Construct((WfcStats *) (void *) gatekeeper_lines_member(talk, GATEKEEPER_LINES_STATS));
    return talk;
}
CLEAN_AS(func_ov048_02262738, GatekeeperTalk_Construct)
