/* The gatekeeper's talk scene and the connections it runs (gatekeeper_talk.h). */
#include "gatekeeper_talk.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Countdown_Tick16, Math_IsBetween */
#include "autoload_2/network.h"
#include "clean.h"
#include "gatekeeper.h"
#include "gatekeeper_talk_lines.h"
#include "main/activity_job.h"
#include "main/activity_vars.h"
#include "main/block_021d27ac.h"
#include "main/card_save.h"
#include "main/group_params.h"
#include "main/library_overlay.h"
#include "main/link_global.h"
#include "main/message_receiver.h"
#include "main/message_texts.h"
#include "main/middle_spot.h"
#include "main/missing_npc1.h"
#include "main/number_text.h"
#include "main/paired_town.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/start_kind.h"
#include "main/system_packet.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/town_name.h"
#include "main/wfc_session.h"
#include "main/wifi_friends.h"
#include "ov004/member_pointer.h"

static_assert(offsetof(GatekeeperTalk, saved_message) == 0xae && offsetof(GatekeeperTalk, topic) == 0xb0, "GatekeeperTalk");
static_assert(offsetof(GatekeeperTalk, state) == 0xb4 && offsetof(GatekeeperTalk, owner) == 0xb8, "GatekeeperTalk");
static_assert(offsetof(GatekeeperTalk, parent) == 0x30c && offsetof(GatekeeperTalk, profile_id) == 0x3ec, "GatekeeperTalk");
static_assert(offsetof(GatekeeperTalk, unk_810) == 0x810 && offsetof(GatekeeperTalk, choice) == 0x813, "GatekeeperTalk");
static_assert(sizeof(GatekeeperTalk) == 0x814, "GatekeeperTalk");
static_assert(sizeof(MessageReceiver) == 0x20 && offsetof(MessageReceiver, message) == 0x1e, "the line shown");
static_assert(offsetof(LocalParent, mac) == 2, "a parent's address");

/* The network modes (autoload_2/network.c): the Wi-Fi Connection's, hosting or joining. */
#define GATEKEEPER_MODE_HOSTING 3
#define GATEKEEPER_MODE_JOINING 4

/* The local statuses the peers answer with (Session_GetLocalStatus). */
#define GATEKEEPER_STATUS_ACCEPTED 5
#define GATEKEEPER_STATUS_REFUSED 6

/* Errors of the network layer (Net_GetError) with a line of their own. */
#define GATEKEEPER_ERROR_400A 0x400a
#define GATEKEEPER_ERROR_400B 0x400b
#define GATEKEEPER_ERROR_800C 0x800c
/* The error detail (a Wi-Fi Connection error code) with a line of its own. */
#define GATEKEEPER_DETAIL_80410 80410

/* NitroDWC's friend status of a friend hosting a game of its own (DWC_STATUS_MATCH_SC_SV). */
#define GATEKEEPER_FRIEND_HOSTING 6

/* The waits, in frames (GatekeeperTalk.owner->countdown). */
#define GATEKEEPER_WAIT_LOCAL 200
#define GATEKEEPER_WAIT_JOIN_FRIEND 2400

/* The talk's mode that keeps it for more messages (TalkObject.mode), cleared here. */
#define GATEKEEPER_TALK_MODE_DONE 0

/* The number of the error code's parts in the talk: its thousands and the rest. */
#define GATEKEEPER_PART_THOUSANDS 6
#define GATEKEEPER_PART_UNITS 7
/* The parts the parent's town and player names go in. */
#define GATEKEEPER_PART_TOWN 3
#define GATEKEEPER_PART_PLAYER 4

/* The place of the names in a parent's data, and their length in characters. */
#define GATEKEEPER_PARENT_TOWN 0x00
#define GATEKEEPER_PARENT_PLAYER 0x0c
#define GATEKEEPER_PARENT_NAME_LENGTH 6
/* The parent's byte that is 0 while it takes visitors. */
#define GATEKEEPER_PARENT_CLOSED 0x18

/* The lines of the answers' handlers that GatekeeperTalk_OnAnswer runs. */
#define GATEKEEPER_ANSWERS 29

/* The session. */
extern NetSession *data_020ccf94;
/* "sp_npc_gatekeeper", the archive of its lines (the first word of data_ov048_02263d20). */
extern const char *const data_ov048_02263d20;
/* "sp_etc_sequence2", the archive of the line shown when job 0x13 has reached its step 3. */
extern const char data_ov048_02264704[];

/* A state: its function and whether it runs before the scene's steps. */
typedef struct GatekeeperTalkState {
    MemberPointer run;
    u8 network; /* run by slot 0x80 when set, by slot 0x84 when not */
    u8 unk_09[3];
} GatekeeperTalkState;
extern GatekeeperTalkState data_ov048_02264344[GATEKEEPER_TALK_STATES];

/* An answer's handler, for the line shown; GatekeeperTalk_OnAnswer fills the handlers from
 * the constants below on its first call (a function-local static, data_ov048_02264734 bit 0). */
typedef struct GatekeeperAnswer {
    s32 line;
    MemberPointer handler;
} GatekeeperAnswer;
extern GatekeeperAnswer data_ov048_022645a8[GATEKEEPER_ANSWERS];
extern u32 data_ov048_02264734;
extern const MemberPointer data_ov048_02263edc, data_ov048_02263f44, data_ov048_022640d4, data_ov048_02263dbc,
    data_ov048_02263db4, data_ov048_02263dac, data_ov048_02263da4, data_ov048_02263d9c, data_ov048_02263d94,
    data_ov048_02263d8c, data_ov048_02263fd4, data_ov048_02263fac, data_ov048_02263d64, data_ov048_02263e14,
    data_ov048_02263dd4, data_ov048_02263dfc, data_ov048_02263f1c, data_ov048_02263ee4, data_ov048_02263f54,
    data_ov048_02263d3c, data_ov048_02263d2c, data_ov048_02263d44, data_ov048_02263e4c, data_ov048_02263e34,
    data_ov048_02263d74, data_ov048_02263dec, data_ov048_02263ecc, data_ov048_02263d34, data_ov048_02263e44;

/* The gatekeeper's state; the scene that leaves for the next line (overlay 4). */
extern void func_ov048_022635f4(Gatekeeper *self, int state);
extern int func_ov004_0222d4f4(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* ---- Helpers */

static TalkObject *talk_object(const GatekeeperTalk *talk)
{
    return (TalkObject *) (void *) talk->scene.talk;
}

/* The number of the line shown (the receiver's message). */
static u8 shown_line(const GatekeeperTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* Line `line` of "sp_npc_gatekeeper" given to `object` to show. */
static void say_on(TalkObject *object, int line)
{
    u8 message = (u8) line;
    TalkObject_SetMessage(object, &message, data_ov048_02263d20);
}

static void say(GatekeeperTalk *talk, int line)
{
    say_on(talk_object(talk), line);
}

/* The magnitude of `value`, as the ROM's negation gives it (the most negative int stays). */
static int magnitude(int value)
{
    return value < 0 ? (int) (0u - (u32) value) : value;
}

static int is_wfc_mode(void)
{
    return Net_GetMode() == GATEKEEPER_MODE_HOSTING || Net_GetMode() == GATEKEEPER_MODE_JOINING;
}

static void set_next_state(GatekeeperTalk *talk, int step)
{
    GatekeeperTalk_SetState(talk, (u32) (talk->state + step));
}

/* The gatekeeper's countdown, one frame less; whether it ran out. */
static int countdown_ran_out(GatekeeperTalk *talk)
{
    return Countdown_Tick16(&talk->owner->countdown) == 0;
}

/* `code` put in the talk as an error code: its thousands in part 6 (two digits), the rest in
 * part 7 (three digits). */
static void put_error_parts(GatekeeperTalk *talk, int code)
{
    MessageText46 thousands;
    MessageText46 units;
    int high = code / 1000;

    MessageText46_Construct(&thousands);
    MessageText46_Construct(&units);
    NumberText_Format(&thousands, high, 2, 6, 0, 0);
    NumberText_Format(&units, code - high * 1000, 3, 6, 0, 0);
    TalkObject_SetPart(talk_object(talk), GATEKEEPER_PART_THOUSANDS, (TextBase *) (void *) &thousands);
    TalkObject_SetPart(talk_object(talk), GATEKEEPER_PART_UNITS, (TextBase *) (void *) &units);
    MessageText46_Destruct(&units);
    MessageText46_Destruct(&thousands);
}

/* The number of the friends of the session's start table that host a game. */
static int count_hosting_friends(void)
{
    const FriendList *friends = (const FriendList *) (const void *) Session_GetStartTable(data_020ccf94);
    int count = 0;
    for (int i = 0; i < FRIEND_COUNT; i++) {
        if (friends->status[i].status == GATEKEEPER_FRIEND_HOSTING) {
            count++;
        }
    }
    return count;
}

/* The parent `entry` takes visitors: it carries data of this game's size, copied into `data`,
 * whose byte 0x18 is 0. */
static int parent_is_open(void *entry, u8 *data)
{
    int size;

    LibraryOverlay_Require66();
    size = Local_EntryDataSize(entry);
    if (size != GATEKEEPER_PARENT_DATA_SIZE) {
        return 0;
    }
    LibraryOverlay_Require66();
    MI_CpuCopy8(Local_EntryData(entry), data, (u32) size);
    return data[GATEKEEPER_PARENT_CLOSED] == 0;
}

/* ---- Lines chosen by the network mode or the session */

/* func_ov048_022609a4: line 0x80 over the Wi-Fi Connection, else 0x63. */
unsigned char GatekeeperTalk_Line80Or63(GatekeeperTalk *talk)
{
    (void) talk;
    return is_wfc_mode() ? 0x80 : 0x63;
}
CLEAN_AS(func_ov048_022609a4, GatekeeperTalk_Line80Or63)

/* func_ov048_022609d0: line 0x82 over the Wi-Fi Connection, else 0x65. */
unsigned char GatekeeperTalk_Line82Or65(GatekeeperTalk *talk)
{
    (void) talk;
    return is_wfc_mode() ? 0x82 : 0x65;
}
CLEAN_AS(func_ov048_022609d0, GatekeeperTalk_Line82Or65)

/* func_ov048_022609fc: line 0x21 when this system has slot 0 of the session, else 0x22. */
unsigned char GatekeeperTalk_Line21Or22(GatekeeperTalk *talk)
{
    (void) talk;
    return Session_IsLocalSlot(data_020ccf94, 0) ? 0x21 : 0x22;
}
CLEAN_AS(func_ov048_022609fc, GatekeeperTalk_Line21Or22)

/* func_ov048_02260a24: when this system has slot 0 of the session: line 0x17 while it is
 * linked, else 0x3a when hosting and 0x38 otherwise; without slot 0, line 0x3d. */
int GatekeeperTalk_LineOfSession(GatekeeperTalk *talk)
{
    NetSession *session = data_020ccf94;
    (void) talk;
    if (!Session_IsLocalSlot(session, 0)) {
        return 0x3d;
    }
    if (Session_IsLinked(session)) {
        return 0x17;
    }
    return Net_GetMode() == GATEKEEPER_MODE_HOSTING ? 0x3a : 0x38;
}
CLEAN_AS(func_ov048_02260a24, GatekeeperTalk_LineOfSession)

/* func_ov048_02260a60: the line for the player's choice: 0, line 0x26, with this player's
 * friend code in the talk (overlay 65 switched in for it, then overlay 68); 1, line 0x6b when
 * a friend of the session's start table hosts a game, else 0x46; 2, line 0x5d; any other, 0. */
int GatekeeperTalk_LineOfChoice(GatekeeperTalk *talk)
{
    int hosting = count_hosting_friends();
    int line = 0;

    switch (talk->choice) {
        case 0: {
            u64 key;
            LibraryOverlay_Switch65();
            line = 0x26;
            key = Wfc_GetUserKey(WifiAccount_GetUserData(PlayerRecord_WifiAccount(PlayerRecords_Current())));
            GatekeeperTalk_PutFriendCode(talk, key);
            LibraryOverlay_Switch68();
            break;
        }
        case 1:
            line = hosting != 0 ? 0x6b : 0x46;
            break;
        case 2:
            line = 0x5d;
            break;
        default:
            break;
    }
    return line;
}
CLEAN_AS(func_ov048_02260a60, GatekeeperTalk_LineOfChoice)

/* func_ov048_0226077c: the line for the Wi-Fi Connection error `code`, which is put in the
 * talk (parts 6 and 7):
 *   0x83  20101, 23503 and 23000-23999;
 *   0x85  20108;  0x86  20110;  0x87  50099;
 *   0x88  51099-51102, 51104-51198 and 51300-51398;  0x89  51103;  0x8a  51200-51299;
 *   0x8b  52000-52003, 52100-52103 and 52200-52203;
 *   0x84  any other (20102-20107, 20109, 20111-20999, 52004-52098, 52300-52399 and
 *         53000-53299 named first among them). */
int GatekeeperTalk_PutErrorCode(GatekeeperTalk *talk, int code)
{
    int line = 0x84;

    if (code == 20101 || code == 23503 || Math_IsBetween(code, 23000, 23999)) {
        line = 0x83;
    } else if (Math_IsBetween(code, 20102, 20107) || code == 20109 || Math_IsBetween(code, 20111, 20999) ||
               Math_IsBetween(code, 52004, 52098) || Math_IsBetween(code, 52300, 52399) ||
               Math_IsBetween(code, 53000, 53099) || Math_IsBetween(code, 53100, 53199) ||
               Math_IsBetween(code, 53200, 53299)) {
        line = 0x84;
    } else if (code == 20108) {
        line = 0x85;
    } else if (code == 20110) {
        line = 0x86;
    } else if (code == 50099) {
        line = 0x87;
    } else if (Math_IsBetween(code, 51099, 51102) || Math_IsBetween(code, 51104, 51198) ||
               Math_IsBetween(code, 51300, 51398)) {
        line = 0x88;
    } else if (code == 51103) {
        line = 0x89;
    } else if (Math_IsBetween(code, 51200, 51299)) {
        line = 0x8a;
    } else if (Math_IsBetween(code, 52000, 52003) || Math_IsBetween(code, 52100, 52103) ||
               Math_IsBetween(code, 52200, 52203)) {
        line = 0x8b;
    }
    put_error_parts(talk, code);
    return line;
}
CLEAN_AS(func_ov048_0226077c, GatekeeperTalk_PutErrorCode)

/* ---- Ending a state with a line */

/* func_ov048_02260e28: line `line` shown; over the Wi-Fi Connection the talk goes to
 * GATEKEEPER_TALK_END_WFC, else it is released, the session ended and the state 0. */
void GatekeeperTalk_EndWithLine(GatekeeperTalk *talk, int line, int unused)
{
    (void) unused;
    say(talk, line);
    if (is_wfc_mode()) {
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_END_WFC);
    } else {
        GatekeeperTalk_Release(talk);
        GatekeeperTalk_EndSession(talk);
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
    }
}
CLEAN_AS(func_ov048_02260e28, GatekeeperTalk_EndWithLine)

/* func_ov048_02260e78: a frame of the wait; when it runs out, line 0x56 ends the state.
 * Whether it did. */
int GatekeeperTalk_TimeOut56(GatekeeperTalk *talk)
{
    if (countdown_ran_out(talk)) {
        GatekeeperTalk_EndWithLine(talk, 0x56, 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov048_02260e78, GatekeeperTalk_TimeOut56)

/* func_ov048_02260ea8: a frame of the wait; when it runs out, line 0x7a ends the state; else
 * an error of the network layer ends it with the line of its error code
 * (GatekeeperTalk_PutErrorCode). Whether it ended. */
int GatekeeperTalk_TimeOutOrError(GatekeeperTalk *talk)
{
    if (countdown_ran_out(talk)) {
        GatekeeperTalk_EndWithLine(talk, 0x7a, 1);
        return 1;
    }
    if (Net_GetError() != 0) {
        int line = GatekeeperTalk_PutErrorCode(talk, magnitude(Net_GetErrorDetail()));
        GatekeeperTalk_EndWithLine(talk, line, 1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov048_02260ea8, GatekeeperTalk_TimeOutOrError)

/* func_ov048_02260f00: a frame of the wait; when it runs out, line 0x65 ends the state.
 * Whether it did. */
int GatekeeperTalk_TimeOut65(GatekeeperTalk *talk)
{
    if (countdown_ran_out(talk)) {
        GatekeeperTalk_EndWithLine(talk, 0x65, 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov048_02260f00, GatekeeperTalk_TimeOut65)

/* func_ov048_02260f30: a frame of the wait; when it runs out, line 0x82 or 0x65
 * (GatekeeperTalk_Line82Or65) ends the state. Whether it did. */
int GatekeeperTalk_TimeOutByMode(GatekeeperTalk *talk)
{
    if (countdown_ran_out(talk)) {
        GatekeeperTalk_EndWithLine(talk, GatekeeperTalk_Line82Or65(talk), 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov048_02260f30, GatekeeperTalk_TimeOutByMode)

/* func_ov048_02260f64: the state ended by an error of the network layer, or because the
 * connection is `lost`. Lost: line 0x82 or 0x65. An error over the Wi-Fi Connection: the error
 * detail put in the talk as its code (parts 6 and 7) and line 0x7d for error 0x400b, 0x78 for
 * 0x400a, 0x7a for detail 80410, else 0x7e. Another error: line 0x82 or 0x65. Whether it
 * ended. */
int GatekeeperTalk_CheckError(GatekeeperTalk *talk, int lost)
{
    int error = Net_GetError();

    if (error == 0 && lost == 0) {
        return 0;
    }
    if (lost != 0 || !is_wfc_mode()) {
        GatekeeperTalk_EndWithLine(talk, GatekeeperTalk_Line82Or65(talk), 0);
        return 1;
    }
    {
        int code = magnitude(Net_GetErrorDetail());
        int high = code / 1000;
        MessageText46 thousands;
        MessageText46 units;

        MessageText46_Construct(&thousands);
        MessageText46_Construct(&units);
        NumberText_Format(&thousands, high, 2, 6, 0, 0);
        NumberText_Format(&units, code - high * 1000, 3, 6, 0, 0);
        TalkObject_SetPart(talk_object(talk), GATEKEEPER_PART_THOUSANDS, (TextBase *) (void *) &thousands);
        TalkObject_SetPart(talk_object(talk), GATEKEEPER_PART_UNITS, (TextBase *) (void *) &units);
        if (error == GATEKEEPER_ERROR_400B) {
            GatekeeperTalk_EndWithLine(talk, 0x7d, 0);
        } else if (error == GATEKEEPER_ERROR_400A) {
            GatekeeperTalk_EndWithLine(talk, 0x78, 0);
        } else if (code == GATEKEEPER_DETAIL_80410) {
            GatekeeperTalk_EndWithLine(talk, 0x7a, 0);
        } else {
            GatekeeperTalk_EndWithLine(talk, 0x7e, 0);
        }
        MessageText46_Destruct(&units);
        MessageText46_Destruct(&thousands);
    }
    return 1;
}
CLEAN_AS(func_ov048_02260f64, GatekeeperTalk_CheckError)

/* func_ov048_022614ac: whether the error detail is a server's, 98000-98999. */
int GatekeeperTalk_IsServerError(void)
{
    return Math_IsBetween(magnitude(Net_GetErrorDetail()), 98000, 98999) != 0;
}
CLEAN_AS(func_ov048_022614ac, GatekeeperTalk_IsServerError)

/* ---- The states: the local wireless library */

/* func_ov048_0226125c (GATEKEEPER_TALK_FIND_PARENT): unless the wait runs out (line 0x56),
 * the first of the parents found that takes visitors is kept (copied to `parent`), its town's
 * and its player's names put in the talk's parts 3 and 4, line 0x57 shown, the talk released
 * and the state 0. */
void GatekeeperTalk_FindParent(GatekeeperTalk *talk)
{
    TownNameText town;
    TownNameWideText town_wide;
    PlayerIdText player;
    PlayerIdWideText player_wide;
    TalkObject *object;
    void **entries;
    int count;

    if (GatekeeperTalk_TimeOut56(talk)) {
        return;
    }
    Session_SendNothing();
    count = Net_CountJoinable();
    if (count <= 0) {
        return;
    }
    LibraryOverlay_Require66();
    entries = Local_ListEntries();
    TownNameText_Construct(&town);
    TownNameWideText_Construct(&town_wide);
    PlayerIdText_Construct(&player);
    PlayerIdWideText_Construct(&player_wide);
    object = talk_object(talk);

    for (u8 i = 0; i < count; i++) {
        u8 data[GATEKEEPER_PARENT_DATA_SIZE];
        void *entry = entries[i];

        if (entry == NULL || !parent_is_open(entry, data)) {
            continue;
        }
        MI_CpuCopy8(entry, &talk->parent, sizeof(LocalParent));
        TextBase_SetWide(&town_wide, &data[GATEKEEPER_PARENT_TOWN], GATEKEEPER_PARENT_NAME_LENGTH);
        TextBase_WideToBytes((TextBase *) (void *) &town, (WideTextBase *) (void *) &town_wide, 0, 0);
        TextBase_SetWide(&player_wide, &data[GATEKEEPER_PARENT_PLAYER], GATEKEEPER_PARENT_NAME_LENGTH);
        TextBase_WideToBytes((TextBase *) (void *) &player, (WideTextBase *) (void *) &player_wide, 0, 0);
        TalkObject_SetPart(object, GATEKEEPER_PART_TOWN, (TextBase *) (void *) &town);
        TalkObject_SetPart(object, GATEKEEPER_PART_PLAYER, (TextBase *) (void *) &player);
        say_on(object, 0x57);
        GatekeeperTalk_Release(talk);
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
        break;
    }

    PlayerIdWideText_Destruct(&player_wide);
    PlayerIdText_Destruct(&player);
    TownNameWideText_Destruct(&town_wide);
    TownNameText_Destruct(&town);
}
CLEAN_AS(func_ov048_0226125c, GatekeeperTalk_FindParent)

/* func_ov048_022611f0 (GATEKEEPER_TALK_TAKE_FRIEND, a talk state): when the group's parameter
 * C4C is 1, the friend its argument numbers is kept (its profile id), line 0x62 and the state
 * 0; else GATEKEEPER_TALK_END_WFC and line 0x61. */
void GatekeeperTalk_TakeFriend(GatekeeperTalk *talk)
{
    if (GroupParams_C4CIs1()) {
        int index = GroupParams_Arg();
        LibraryOverlay_Require65();
        talk->profile_id = Wfc_ProfileIdAt(index);
        say(talk, 0x62);
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
    } else {
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_END_WFC);
        say(talk, 0x61);
    }
}
CLEAN_AS(func_ov048_022611f0, GatekeeperTalk_TakeFriend)

/* func_ov048_022611a0 (GATEKEEPER_TALK_GROUP_CHECK, a talk state): line 0x59 when the group's
 * parameter C4C is 1, else line 0x58 and the session ended; then the state 0. */
void GatekeeperTalk_GroupCheck(GatekeeperTalk *talk)
{
    if (GroupParams_C4CIs1()) {
        say(talk, 0x59);
    } else {
        say(talk, 0x58);
        GatekeeperTalk_EndSession(talk);
    }
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
}
CLEAN_AS(func_ov048_022611a0, GatekeeperTalk_GroupCheck)

/* func_ov048_02260d28 (GATEKEEPER_TALK_JOIN_PARENT): unless an error or the wait (line 0x65)
 * ends it, the parent kept is looked for among those found that take visitors (by its
 * address); found, it is selected, the wait set to 200 frames and the state
 * GATEKEEPER_TALK_WAIT_CONNECTED.
 * QUIRK: the search goes on after a parent is selected, so a second entry of the same address
 * would be selected again. */
void GatekeeperTalk_JoinParent(GatekeeperTalk *talk)
{
    void **entries;
    int count;

    if (GatekeeperTalk_CheckError(talk, 0)) {
        return;
    }
    if (GatekeeperTalk_TimeOut65(talk)) {
        return;
    }
    Session_SendNothing();
    count = Net_CountJoinable();
    if (count <= 0) {
        return;
    }
    LibraryOverlay_Require66();
    entries = Local_ListEntries();

    for (u8 i = 0; i < count; i++) {
        u8 data[GATEKEEPER_PARENT_DATA_SIZE];
        u8 *entry = entries[i];
        int same = 1;

        if (entry == NULL || !parent_is_open(entry, data)) {
            continue;
        }
        for (int k = 0; k < (int) sizeof(talk->parent.mac); k++) {
            if (entry[offsetof(LocalParent, mac) + k] != talk->parent.mac[k]) {
                same = 0;
                break;
            }
        }
        if (!same) {
            continue;
        }
        LibraryOverlay_Require66();
        Local_SelectEntry(entry);
        talk->owner->countdown = GATEKEEPER_WAIT_LOCAL;
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_WAIT_CONNECTED);
    }
}
CLEAN_AS(func_ov048_02260d28, GatekeeperTalk_JoinParent)

/* func_ov048_02260cd0 (GATEKEEPER_TALK_WAIT_CONNECTED): unless an error or the wait (line 0x82
 * or 0x65) ends it, once connected: the wait set to 200 frames, the state
 * GATEKEEPER_TALK_SEND_STATUS_0, and the transfer to this system's AID stopped.
 * QUIRK: the network mode is asked for a second time when it is not 3, and not used. */
void GatekeeperTalk_WaitConnected(GatekeeperTalk *talk)
{
    if (GatekeeperTalk_CheckError(talk, 0)) {
        return;
    }
    if (GatekeeperTalk_TimeOutByMode(talk)) {
        return;
    }
    LibraryOverlay_RequireAny();
    if (!Net_UpdateConnection()) {
        return;
    }
    if (Net_GetMode() != GATEKEEPER_MODE_HOSTING) {
        Net_GetMode();
    }
    talk->owner->countdown = GATEKEEPER_WAIT_LOCAL;
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_SEND_STATUS_0);
    Session_StopTransfer((u32) Net_GetMyAid());
}
CLEAN_AS(func_ov048_02260cd0, GatekeeperTalk_WaitConnected)

/* func_ov048_02260c88 (GATEKEEPER_TALK_SEND_STATUS_0): the connection updated; an error (or
 * its loss) ends the state and the local status; else once local status 0 is sent, no chunk
 * sent yet and GATEKEEPER_TALK_WAIT_STATUS_0. */
void GatekeeperTalk_SendStatus0(GatekeeperTalk *talk)
{
    int lost;

    LibraryOverlay_RequireAny();
    lost = Net_UpdateConnection() == 0;
    if (GatekeeperTalk_CheckError(talk, lost)) {
        Session_FinishLocalStatus();
    } else if (Session_SendLocalStatus(0)) {
        talk->chunks_sent = 0;
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_WAIT_STATUS_0);
    }
}
CLEAN_AS(func_ov048_02260c88, GatekeeperTalk_SendStatus0)

/* func_ov048_02260b64 (GATEKEEPER_TALK_WAIT_STATUS_0): the connection updated.
 * - An error (or its loss) ends the state and the local status; and when the middle spot is
 *   marked, the current player's paired town loses its flag 5.
 * - Accepted (local status 5): when the middle spot is marked, the paired town gets flag 5;
 *   then this system's block is sent to the link's members, chunk by chunk; once it all is,
 *   the session's connect mode 0, the link's kinds 0, the activity's slot this system's AID,
 *   the local status finished, the talk's mode cleared, the talk released, the state 0 and
 *   the gatekeeper's state 0xc.
 * - Refused (local status 6), or error 0x800c: the local status finished, and line 0x79 for
 *   the error, else line 0x80 or 0x63, end the state. */
void GatekeeperTalk_WaitStatus0(GatekeeperTalk *talk)
{
    int lost;
    int status;

    LibraryOverlay_RequireAny();
    lost = !Net_UpdateConnection();
    if (GatekeeperTalk_CheckError(talk, lost)) {
        Session_FinishLocalStatus();
        if (MiddleSpot_HasMark((const MiddleSpot *) (const void *) Block021d27ac_Part0C(Block021d27ac_Get()))) {
            if (PairedTown_Flag5(PlayerRecord_Field242C(PlayerRecords_Current()))) {
                PairedTown_ClearFlag5(PlayerRecord_Field242C(PlayerRecords_Current()));
            }
        }
        return;
    }

    status = Session_GetLocalStatus();
    if (status == GATEKEEPER_STATUS_ACCEPTED) {
        u16 members;
        if (MiddleSpot_HasMark((const MiddleSpot *) (const void *) Block021d27ac_Part0C(Block021d27ac_Get()))) {
            if (!PairedTown_Flag5(PlayerRecord_Field242C(PlayerRecords_Current()))) {
                PairedTown_SetFlag5(PlayerRecord_Field242C(PlayerRecords_Current()));
            }
        }
        members = LinkGlobal_MemberMask();
        if (SystemPacket_SendSenderBlock(&talk->chunks_sent, members)) {
            Session_SetConnectMode(data_020ccf94, 0);
            LinkGlobal_SetKind(0);
            LinkGlobal_SetDoneKind(0);
            ActivityVars_SetSlot3C1C((u32) Net_GetMyAid());
            Session_FinishLocalStatus();
            talk_object(talk)->mode = GATEKEEPER_TALK_MODE_DONE;
            GatekeeperTalk_Release(talk);
            GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
            func_ov048_022635f4(talk->owner, GATEKEEPER_STATE_C);
        }
        return;
    }

    if (status != GATEKEEPER_STATUS_REFUSED && Net_GetError() != GATEKEEPER_ERROR_800C) {
        return;
    }
    Session_FinishLocalStatus();
    if (Net_GetError() == GATEKEEPER_ERROR_800C) {
        GatekeeperTalk_EndWithLine(talk, 0x79, 1);
    } else {
        GatekeeperTalk_EndWithLine(talk, GatekeeperTalk_Line80Or63(talk), 0);
    }
}
CLEAN_AS(func_ov048_02260b64, GatekeeperTalk_WaitStatus0)

/* func_ov048_02260b4c (GATEKEEPER_TALK_SEND_STATUS_1): local status 1 sent, then
 * GATEKEEPER_TALK_WAIT_STATUS_1. */
void GatekeeperTalk_SendStatus1(GatekeeperTalk *talk)
{
    Session_SendLocalStatus(1);
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_WAIT_STATUS_1);
}
CLEAN_AS(func_ov048_02260b4c, GatekeeperTalk_SendStatus1)

/* func_ov048_02260ae8 (GATEKEEPER_TALK_WAIT_STATUS_1): once the peer answers (local status 5
 * or 6), the talk released and the state 0; accepted, the talk's mode cleared, the
 * gatekeeper's state 0xd and the link's kinds 1; refused, line 0x0c. Then the local status
 * finished. */
void GatekeeperTalk_WaitStatus1(GatekeeperTalk *talk)
{
    TalkObject *object = talk_object(talk);
    int status = Session_GetLocalStatus();

    if (status != GATEKEEPER_STATUS_ACCEPTED && status != GATEKEEPER_STATUS_REFUSED) {
        return;
    }
    GatekeeperTalk_Release(talk);
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
    if (status == GATEKEEPER_STATUS_ACCEPTED) {
        object->mode = GATEKEEPER_TALK_MODE_DONE;
        func_ov048_022635f4(talk->owner, GATEKEEPER_STATE_D);
        LinkGlobal_SetKind(1);
        LinkGlobal_SetDoneKind(1);
    } else {
        say_on(object, 0x0c);
    }
    Session_FinishLocalStatus();
}
CLEAN_AS(func_ov048_02260ae8, GatekeeperTalk_WaitStatus1)

/* ---- The states: the Nintendo Wi-Fi Connection */

/* func_ov048_0226166c (GATEKEEPER_TALK_WAIT_FRIENDS): the connection updated; unless the wait
 * or an error ends it, once the friend list is there: for choice 0 straight to
 * GATEKEEPER_TALK_AFTER_DOWNLOADS, else the next state. */
void GatekeeperTalk_WaitFriends(GatekeeperTalk *talk)
{
    LibraryOverlay_RequireAny();
    Net_UpdateConnection();
    if (GatekeeperTalk_TimeOutOrError(talk)) {
        return;
    }
    LibraryOverlay_Require65();
    if (Wfc_GetFriendList() == NULL) {
        return;
    }
    if (talk->choice == 0) {
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_AFTER_DOWNLOADS);
    } else {
        set_next_state(talk, 1);
    }
}
CLEAN_AS(func_ov048_0226166c, GatekeeperTalk_WaitFriends)

/* func_ov048_02261578 (GATEKEEPER_TALK_START_STATS_UPLOAD): the next state once the upload has
 * started, else the one after it. */
void GatekeeperTalk_StartStatsUpload(GatekeeperTalk *talk)
{
    set_next_state(talk, WfcSession_StartStatsUpload() ? 1 : 2);
}
CLEAN_AS(func_ov048_02261578, GatekeeperTalk_StartStatsUpload)

/* func_ov048_02261540 (GATEKEEPER_TALK_FINISH_STATS_UPLOAD): on a server's error the request
 * is dropped (Wfc_Call022784a0) and the next state; else the next state once it finished. */
void GatekeeperTalk_FinishStatsUpload(GatekeeperTalk *talk)
{
    if (GatekeeperTalk_IsServerError()) {
        Wfc_Call022784a0();
        set_next_state(talk, 1);
    } else if (WfcSession_FinishStatsUpload()) {
        set_next_state(talk, 1);
    }
}
CLEAN_AS(func_ov048_02261540, GatekeeperTalk_FinishStatsUpload)

/* func_ov048_02261514 (GATEKEEPER_TALK_START_STATS_GET): the next state once the download has
 * started, else the one after it. */
void GatekeeperTalk_StartStatsGet(GatekeeperTalk *talk)
{
    set_next_state(talk, WfcSession_StartStatsGet() ? 1 : 2);
}
CLEAN_AS(func_ov048_02261514, GatekeeperTalk_StartStatsGet)

/* func_ov048_022614dc (GATEKEEPER_TALK_FINISH_STATS_GET): as GatekeeperTalk_FinishStatsUpload
 * for the statistics' download. */
void GatekeeperTalk_FinishStatsGet(GatekeeperTalk *talk)
{
    if (GatekeeperTalk_IsServerError()) {
        Wfc_Call022784a0();
        set_next_state(talk, 1);
    } else if (WfcSession_FinishStatsGet()) {
        set_next_state(talk, 1);
    }
}
CLEAN_AS(func_ov048_022614dc, GatekeeperTalk_FinishStatsGet)

/* func_ov048_02261640 (GATEKEEPER_TALK_START_LETTER_GET): the next state once the download has
 * started, else the one after it. */
void GatekeeperTalk_StartLetterGet(GatekeeperTalk *talk)
{
    set_next_state(talk, WfcSession_StartLetterGet() ? 1 : 2);
}
CLEAN_AS(func_ov048_02261640, GatekeeperTalk_StartLetterGet)

/* func_ov048_02261608 (GATEKEEPER_TALK_FINISH_LETTER_GET): as
 * GatekeeperTalk_FinishStatsUpload for the letter's download. */
void GatekeeperTalk_FinishLetterGet(GatekeeperTalk *talk)
{
    if (GatekeeperTalk_IsServerError()) {
        Wfc_Call022784a0();
        set_next_state(talk, 1);
    } else if (WfcSession_FinishLetterGet()) {
        set_next_state(talk, 1);
    }
}
CLEAN_AS(func_ov048_02261608, GatekeeperTalk_FinishLetterGet)

/* func_ov048_022615dc (GATEKEEPER_TALK_START_NOTICE_GET): the next state once the download has
 * started, else the one after it. */
void GatekeeperTalk_StartNoticeGet(GatekeeperTalk *talk)
{
    set_next_state(talk, WfcSession_StartNoticeGet() ? 1 : 2);
}
CLEAN_AS(func_ov048_022615dc, GatekeeperTalk_StartNoticeGet)

/* func_ov048_022615a4 (GATEKEEPER_TALK_FINISH_NOTICE_GET): as
 * GatekeeperTalk_FinishStatsUpload for the notice's download. */
void GatekeeperTalk_FinishNoticeGet(GatekeeperTalk *talk)
{
    if (GatekeeperTalk_IsServerError()) {
        Wfc_Call022784a0();
        set_next_state(talk, 1);
    } else if (WfcSession_FinishNoticeGet()) {
        set_next_state(talk, 1);
    }
}
CLEAN_AS(func_ov048_022615a4, GatekeeperTalk_FinishNoticeGet)

/* func_ov048_02261380 (GATEKEEPER_TALK_AFTER_DOWNLOADS):
 * - after line 0x62 (a friend was taken): when that friend hosts a game, it is joined, the
 *   wait set to 2400 frames and the state GATEKEEPER_TALK_WAIT_CONNECTED; else line 0x78 ends
 *   the state;
 * - else: when the user data of the session's start header changed, the current player's
 *   account is updated from it (its friend data handed to the library, the user data copied
 *   to the account) and saved: line 2, or 0x75 when the save failed; unchanged, the line of
 *   the player's choice (GatekeeperTalk_LineOfChoice). Then for choice 0, or with byte 0x810
 *   set, GATEKEEPER_TALK_END_WFC; else the talk released and the state 0.
 * QUIRK: a friend not in the list (index -1) has the byte before the statuses read as its
 * status before the index is tested. */
void GatekeeperTalk_AfterDownloads(GatekeeperTalk *talk)
{
    NetSession *session = data_020ccf94;
    u8 *header = Session_GetStartHeader(session);
    u8 *record = PlayerRecords_Current();
    u8 *user_data = header + 0x20;
    int line;

    if (shown_line(talk) == 0x62) {
        const u8 *friends = Session_GetStartTable(session);
        int index;
        u8 status;

        LibraryOverlay_Require65();
        index = Wfc_FriendIndexOf(talk->profile_id);
        status = *(friends + (int) (offsetof(FriendList, status) + offsetof(FriendStatus, status)) +
                   index * (int) sizeof(FriendStatus));
        if (status != GATEKEEPER_FRIEND_HOSTING || index == -1) {
            GatekeeperTalk_EndWithLine(talk, 0x78, 1);
        } else {
            int profile_id = talk->profile_id;
            LibraryOverlay_Require65();
            Wfc_JoinFriendGame(profile_id);
            talk->owner->countdown = GATEKEEPER_WAIT_JOIN_FRIEND;
            GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_WAIT_CONNECTED);
        }
        return;
    }

    if (Wfc_TakeDirty(user_data)) {
        WifiFriendData *friend_data = WifiFriendData_GetData(WifiAccount_GetFriendData(PlayerRecord_WifiAccount(record)));
        u8 *account_data;
        Wfc_Call0210111c(user_data, friend_data);
        account_data = WifiAccount_GetUserData(PlayerRecord_WifiAccount(record));
        MI_CpuCopy8(user_data, account_data, 0x40);
        line = CardSave_WriteAccount() ? 2 : 0x75;
    } else {
        line = GatekeeperTalk_LineOfChoice(talk);
    }
    say(talk, line);

    if (talk->choice == 0 || talk->unk_810 != 0) {
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_END_WFC);
    } else {
        GatekeeperTalk_Release(talk);
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
    }
}
CLEAN_AS(func_ov048_02261380, GatekeeperTalk_AfterDownloads)

/* func_ov048_02261120 (GATEKEEPER_TALK_END_WFC): the talk held while the Wi-Fi Connection
 * ends; once it has, the talk released and, for a current player of number 0-3, the downloads
 * applied (statistics, letter, notice), the session ended, the friend data kept and, once the
 * friend roster is saved, line 2. Then the state 0. */
void GatekeeperTalk_EndWfc(GatekeeperTalk *talk)
{
    TalkObject *object = talk_object(talk);
    u8 *record;
    int number;

    if (object != NULL) {
        TalkObject_Hold(object);
    }
    LibraryOverlay_Require65();
    if (!Wfc_UpdateEnd()) {
        return;
    }
    if (object != NULL) {
        GatekeeperTalk_Release(talk);
    }
    record = PlayerRecords_Current();
    if (record != NULL) {
        number = PlayerRecord_Number(record);
        if (number >= 0 && number < 4) {
            WfcSession_ApplyStats();
            WfcSession_ApplyLetter();
            WfcSession_ApplyNotice();
            GatekeeperTalk_EndSession(talk);
            WfcSession_KeepFriendData();
            if (CardSave_WriteFriendRoster()) {
                say(talk, 2);
            }
        }
    }
    GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
}
CLEAN_AS(func_ov048_02261120, GatekeeperTalk_EndWfc)

/* ---- The states: after a connection */

/* func_ov048_022610f8 (GATEKEEPER_TALK_WAIT_MISSING_NPC): once the gatekeeper waits with the
 * missing character, the activity is asked for job 0x13 and GATEKEEPER_TALK_WAIT_JOB_13; until
 * then the missing character is kept facing the player. */
void GatekeeperTalk_WaitMissingNpc(GatekeeperTalk *talk)
{
    if (Gatekeeper_IsWaitingInPoseBA(talk->owner)) {
        ActivityJob_Ask13();
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_WAIT_JOB_13);
    } else {
        MissingNpc1_StopToFacePlayer();
    }
}
CLEAN_AS(func_ov048_022610f8, GatekeeperTalk_WaitMissingNpc)

/* func_ov048_0226107c (GATEKEEPER_TALK_WAIT_JOB_13): once job 0x13 is at its step 3, the talk
 * released, line 10 of "sp_etc_sequence2" and the state 0; else once the activity has no job,
 * that is noted, the talk released, the kept line shown, the missing character set to follow
 * the player and the state 0. */
void GatekeeperTalk_WaitJob13(GatekeeperTalk *talk)
{
    TalkObject *object = talk_object(talk);

    if (ActivityJob_Is13AtStep3()) {
        u8 message = 10;
        GatekeeperTalk_Release(talk);
        TalkObject_SetMessage(object, &message, data_ov048_02264704);
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
    } else if (ActivityJob_IsIdleForOv048()) {
        talk->job_idle_seen = 1;
        GatekeeperTalk_Release(talk);
        say_on(object, talk->saved_message);
        MissingNpc1_StartFollowing();
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_IDLE);
    }
}
CLEAN_AS(func_ov048_0226107c, GatekeeperTalk_WaitJob13)

/* func_ov048_022616b8 */
void GatekeeperTalk_SetState(GatekeeperTalk *talk, u32 state)
{
    talk->state = (s32) state;
}
CLEAN_AS(func_ov048_022616b8, GatekeeperTalk_SetState)

/* ---- Its vtable slots */

/* func_ov048_022616c0 (slot 0x84, a command of the scene ended): the state's function, when the
 * state is not a network state and has one.
 * REQUIRES: the state is below GATEKEEPER_TALK_STATES (the game's are). */
void GatekeeperTalk_RunTalkState(GatekeeperTalk *talk)
{
    const GatekeeperTalkState *state = &data_ov048_02264344[talk->state];
    if (state->network != 0 || state->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&state->run, talk);
}
CLEAN_AS(func_ov048_022616c0, GatekeeperTalk_RunTalkState)

/* func_ov048_02261704 (slot 0x80, before each step of the scene): the state's function, when
 * the state is a network state and has one.
 * REQUIRES: the state is below GATEKEEPER_TALK_STATES (the game's are). */
void GatekeeperTalk_RunNetworkState(GatekeeperTalk *talk)
{
    const GatekeeperTalkState *state = &data_ov048_02264344[talk->state];
    if (state->network == 0 || state->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&state->run, talk);
}
CLEAN_AS(func_ov048_02261704, GatekeeperTalk_RunNetworkState)

/* func_ov048_02261748 (slot 0x18, the player's answer): unless the game started in a special
 * way (StartKind_IsSet), each handler of the line shown is called with the answer picked. The
 * line is read again for each entry, so a handler that shows a line with handlers of its own
 * further down the table has them run too. */
void GatekeeperTalk_OnAnswer(GatekeeperTalk *talk)
{
    static const MemberPointer *const handlers[GATEKEEPER_ANSWERS] = {
        &data_ov048_02263edc, /* 0x15: GatekeeperTalk_OnAnswer15 */
        &data_ov048_02263f44, /* 0x41: GatekeeperTalk_OnAnswer41 */
        &data_ov048_022640d4, /* 0x14: GatekeeperTalk_OnAnswer14 */
        &data_ov048_02263dbc, /* 0x7f: GatekeeperTalk_OnAnswer7f */
        &data_ov048_02263db4, /* 0x24: GatekeeperTalk_OnAnswerTo21Or22 */
        &data_ov048_02263dac, /* 0x56: GatekeeperTalk_OnAnswerTo21Or22 */
        &data_ov048_02263da4, /* 0x0a: GatekeeperTalk_OnAnswer0a */
        &data_ov048_02263d9c, /* 0x10: GatekeeperTalk_OnAnswerSession */
        &data_ov048_02263d94, /* 0x21: GatekeeperTalk_OnAnswerSession */
        &data_ov048_02263d8c, /* 0x0f: GatekeeperTalk_OnAnswerSessionOrCode */
        &data_ov048_02263fd4, /* 0x22: GatekeeperTalk_OnAnswerSessionOrCode */
        &data_ov048_02263fac, /* 0x51: GatekeeperTalk_OnAnswer51 */
        &data_ov048_02263d64, /* 0x63: GatekeeperTalk_OnAnswerTo59 */
        &data_ov048_02263e14, /* 0x65: GatekeeperTalk_OnAnswerTo59 */
        &data_ov048_02263dd4, /* 0x7d: GatekeeperTalk_OnAnswerTo62 */
        &data_ov048_02263dfc, /* 0x7e: GatekeeperTalk_OnAnswerTo62 */
        &data_ov048_02263f1c, /* 0x80: GatekeeperTalk_OnAnswerTo62 */
        &data_ov048_02263ee4, /* 0x82: GatekeeperTalk_OnAnswerTo62 */
        &data_ov048_02263f54, /* 0x2c: GatekeeperTalk_OnAnswer2c */
        &data_ov048_02263d3c, /* 0x6b: GatekeeperTalk_OnAnswer6b */
        &data_ov048_02263d2c, /* 0x5f: GatekeeperTalk_OnAnswer5f */
        &data_ov048_02263d44, /* 0x23: GatekeeperTalk_OnAnswerChoice0 */
        &data_ov048_02263e4c, /* 0x28: GatekeeperTalk_OnAnswerChoice0 */
        &data_ov048_02263e34, /* 0x2f: GatekeeperTalk_OnAnswerChoice0 */
        &data_ov048_02263d74, /* 0x52: GatekeeperTalk_OnAnswer52 */
        &data_ov048_02263dec, /* 0x3d: GatekeeperTalk_OnAnswer3d */
        &data_ov048_02263ecc, /* 0x71: GatekeeperTalk_OnAnswer71 */
        &data_ov048_02263d34, /* 0x74: GatekeeperTalk_OnAnswer74 */
        &data_ov048_02263e44, /* 0x57: GatekeeperTalk_OnAnswer57 */
    };

    if (StartKind_IsSet()) {
        return;
    }
    {
        u32 flags = data_ov048_02264734;
        if ((flags & 1) == 0) {
            for (int i = 0; i < GATEKEEPER_ANSWERS; i++) {
                data_ov048_022645a8[i].handler = *handlers[i];
            }
            data_ov048_02264734 = flags | 1;
        }
    }
    for (u32 i = 0; i < GATEKEEPER_ANSWERS; i++) {
        const GatekeeperAnswer *entry = &data_ov048_022645a8[i];
        if (entry->line == shown_line(talk)) {
            int answer = (int) TalkAnswers_Picked(TalkObject_Answers(talk_object(talk)));
            void *self = MemberPointer_Object(&entry->handler, talk);
            ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(&entry->handler, self))(self, answer);
        }
    }
}
CLEAN_AS(_ZN18Obj_ov048_0226420819func_ov048_02261748Ev, GatekeeperTalk_OnAnswer)

/* ---- The answers' handlers */

/* func_ov048_0226196c (line 0x5f): answers 0 and 2, GATEKEEPER_TALK_END_WFC; answer 1, line
 * 0x6c. */
void GatekeeperTalk_OnAnswer5f(GatekeeperTalk *talk, int answer)
{
    switch (answer) {
        case 0:
        case 2:
            GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_END_WFC);
            break;
        case 1:
            say(talk, 0x6c);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov048_0226196c, GatekeeperTalk_OnAnswer5f)

/* func_ov048_022619ac (line 0x6b): nothing. */
void GatekeeperTalk_OnAnswer6b(GatekeeperTalk *talk, int answer)
{
    (void) talk;
    (void) answer;
}
CLEAN_AS(func_ov048_022619ac, GatekeeperTalk_OnAnswer6b)

/* func_ov048_022619b0 (line 0x2c): answer 0, the talk's mode cleared and the gatekeeper's
 * state 0xe; answer 1, line 0x21 or 0x22. */
void GatekeeperTalk_OnAnswer2c(GatekeeperTalk *talk, int answer)
{
    TalkObject *object = talk_object(talk);
    if (answer == 0) {
        object->mode = GATEKEEPER_TALK_MODE_DONE;
        func_ov048_022635f4(talk->owner, GATEKEEPER_STATE_E);
    } else if (answer == 1) {
        say_on(object, GatekeeperTalk_Line21Or22(talk));
    }
}
CLEAN_AS(func_ov048_022619b0, GatekeeperTalk_OnAnswer2c)

/* func_ov048_022619f0 (lines 0x7d, 0x7e, 0x80, 0x82): answer 0, line 0x62. */
void GatekeeperTalk_OnAnswerTo62(GatekeeperTalk *talk, int answer)
{
    if (answer == 0) {
        say(talk, 0x62);
    }
}
CLEAN_AS(func_ov048_022619f0, GatekeeperTalk_OnAnswerTo62)

/* func_ov048_02261a14 (lines 0x63, 0x65): answer 0, line 0x59. */
void GatekeeperTalk_OnAnswerTo59(GatekeeperTalk *talk, int answer)
{
    if (answer == 0) {
        say(talk, 0x59);
    }
}
CLEAN_AS(func_ov048_02261a14, GatekeeperTalk_OnAnswerTo59)

/* func_ov048_02261a38 (line 0x51): answer 0, line 0x52, overlay 4's func_ov004_0222d4f4 and
 * the link's status reset; then over the Wi-Fi Connection GATEKEEPER_TALK_END_WFC, else the
 * session ended. */
void GatekeeperTalk_OnAnswer51(GatekeeperTalk *talk, int answer)
{
    if (answer != 0) {
        return;
    }
    say(talk, 0x52);
    func_ov004_0222d4f4();
    Session_ResetLinkStatus();
    if (is_wfc_mode()) {
        GatekeeperTalk_SetState(talk, GATEKEEPER_TALK_END_WFC);
    } else {
        GatekeeperTalk_EndSession(talk);
    }
}
CLEAN_AS(func_ov048_02261a38, GatekeeperTalk_OnAnswer51)

/* func_ov048_02261a88: answer 0, `line` kept, and shown when the activity was seen with no
 * job, else line 0x6a; answer 1, line 0x21 or 0x22. */
void GatekeeperTalk_OnAnswerKeep(GatekeeperTalk *talk, int answer, int line)
{
    if (answer == 0) {
        talk->saved_message = (u8) line;
        if (talk->job_idle_seen != 0) {
            say(talk, talk->saved_message);
        } else {
            say(talk, 0x6a);
        }
    }
    if (answer == 1) {
        say(talk, GatekeeperTalk_Line21Or22(talk));
    }
}
CLEAN_AS(func_ov048_02261a88, GatekeeperTalk_OnAnswerKeep)

/* func_ov048_02261af8 (line 0x7f): GatekeeperTalk_OnAnswerKeep with line 0x5b. */
void GatekeeperTalk_OnAnswer7f(GatekeeperTalk *talk, int answer)
{
    GatekeeperTalk_OnAnswerKeep(talk, answer, 0x5b);
}
CLEAN_AS(func_ov048_02261af8, GatekeeperTalk_OnAnswer7f)

/* func_ov048_02261b04 (line 0x14): GatekeeperTalk_OnAnswerKeep with line 0x54. */
void GatekeeperTalk_OnAnswer14(GatekeeperTalk *talk, int answer)
{
    GatekeeperTalk_OnAnswerKeep(talk, answer, 0x54);
}
CLEAN_AS(func_ov048_02261b04, GatekeeperTalk_OnAnswer14)

/* func_ov048_02261b10 (line 0x41): GatekeeperTalk_OnAnswerKeep with line 0x3e. */
void GatekeeperTalk_OnAnswer41(GatekeeperTalk *talk, int answer)
{
    GatekeeperTalk_OnAnswerKeep(talk, answer, 0x3e);
}
CLEAN_AS(func_ov048_02261b10, GatekeeperTalk_OnAnswer41)

/* func_ov048_02261b1c (line 0x15): GatekeeperTalk_OnAnswerKeep with line 0x46. */
void GatekeeperTalk_OnAnswer15(GatekeeperTalk *talk, int answer)
{
    GatekeeperTalk_OnAnswerKeep(talk, answer, 0x46);
}
CLEAN_AS(func_ov048_02261b1c, GatekeeperTalk_OnAnswer15)

/* func_ov048_02261b28 (lines 0x24, 0x56): answer 1, line 0x21 or 0x22. */
void GatekeeperTalk_OnAnswerTo21Or22(GatekeeperTalk *talk, int answer)
{
    if (answer == 1) {
        say(talk, GatekeeperTalk_Line21Or22(talk));
    }
}
CLEAN_AS(func_ov048_02261b28, GatekeeperTalk_OnAnswerTo21Or22)

/* func_ov048_02261b54 (lines 0x10, 0x21): with the current player's flag 1, line 8 (answer 0)
 * or 0xe (answer 1). Else answer 0: line 0x50 when the session is linked and this system has
 * slot 0, else 0x51 when this system's slot is taken, else 0x52; answer 1: the line of the
 * session (GatekeeperTalk_LineOfSession). Any other answer shows nothing. */
void GatekeeperTalk_OnAnswerSession(GatekeeperTalk *talk, int answer)
{
    u8 *record = PlayerRecords_Current();
    int line = 0xff;

    switch (answer) {
        case 0: {
            NetSession *session;
            if (PlayerRecord_TestFlag(record, 1)) {
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
            if (PlayerRecord_TestFlag(record, 1)) {
                line = 0xe;
            } else {
                line = GatekeeperTalk_LineOfSession(talk);
            }
            break;
        default:
            break;
    }
    if (line != 0xff) {
        say(talk, line);
    }
}
CLEAN_AS(func_ov048_02261b54, GatekeeperTalk_OnAnswerSession)
