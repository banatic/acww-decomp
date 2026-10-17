/* The gatekeeper's talk scene (gatekeeper_talk.h), the rest of its class 0x02264208: the line
 * it starts with (vtable slot 0x78, by its topic), what follows the end of a line (slot 0x14, a
 * table keyed by the line shown), the handlers of the answers to the menus of the connections,
 * and its constructor and destructors.
 *
 * The connections it opens are started here and run by the states of gatekeeper_talk.h: over
 * the local wireless library as a child (session mode 2) or over the Nintendo Wi-Fi Connection
 * as a joining system (mode 4); the session is started with overlay 66 or 65 switched in and
 * ended with overlay 68 switched back.
 *
 * The talk's `choice` (byte 0x813) is what the player asked of the Wi-Fi Connection: 0 to get
 * the friend code (lines 0x23, 0x28, 0x2f), 1 or 2 from lines 0x3d and 0x52. */
#ifndef CLEAN_OV048_GATEKEEPER_TALK_LINES_H
#define CLEAN_OV048_GATEKEEPER_TALK_LINES_H

#include "gatekeeper_talk.h"
#include "types.h"

/* The topics of the talk (GatekeeperTalk.topic): each picks the line it starts with
 * (GatekeeperTalk_StartLine). */
#define GATEKEEPER_TOPIC_FIRST_MEETING 0 /* the current player's first talk with it */
#define GATEKEEPER_TOPIC_PART_OF_DAY 1   /* 1 to 4: Calendar_PartOfDay plus 1 */
#define GATEKEEPER_TOPIC_NOT_HOST 5      /* TalkChecks_IsHostOrAlone refused */
#define GATEKEEPER_TOPIC_6 6
#define GATEKEEPER_TOPIC_7 7
#define GATEKEEPER_TOPIC_SPECIAL_START 8 /* the game started in a special way (StartKind_IsSet) */
#define GATEKEEPER_TOPIC_CALL_LINKED 9
#define GATEKEEPER_TOPIC_CALL_ALONE 10
#define GATEKEEPER_TOPIC_NONE 11 /* past the table: the start line is left as it is */
#define GATEKEEPER_TOPICS 11

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct GatekeeperTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} GatekeeperTalkStart;

/* Answers to lines. */
void GatekeeperTalk_OnAnswerSessionOrCode(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer0a(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_SayChoiceLine(GatekeeperTalk *talk);
void GatekeeperTalk_OnAnswer3d(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer52(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswerChoice0(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer71(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer57(GatekeeperTalk *talk, int answer);
void GatekeeperTalk_OnAnswer74(GatekeeperTalk *talk, int answer);

/* The end of a line (slot 0x14) and its handlers. */
void GatekeeperTalk_OnMessageEnded(GatekeeperTalk *talk);
void GatekeeperTalk_StartSendStatus1(GatekeeperTalk *talk);
void GatekeeperTalk_SayCodeOrChoice(GatekeeperTalk *talk);
void GatekeeperTalk_SayLine21Or22(GatekeeperTalk *talk);
void GatekeeperTalk_SetOwnerStateA(GatekeeperTalk *talk);
void GatekeeperTalk_SetOwnerState8(GatekeeperTalk *talk);
void GatekeeperTalk_JoinFriend(GatekeeperTalk *talk);
void GatekeeperTalk_StartJoinParent(GatekeeperTalk *talk);
void GatekeeperTalk_OpenFriendScreen(GatekeeperTalk *talk);
void GatekeeperTalk_OpenScreen4(GatekeeperTalk *talk);
void GatekeeperTalk_StartFindParent(GatekeeperTalk *talk);
void GatekeeperTalk_StartWfc(GatekeeperTalk *talk);
void GatekeeperTalk_SetOwnerState6(GatekeeperTalk *talk);
void GatekeeperTalk_SetOwnerState5(GatekeeperTalk *talk);
void GatekeeperTalk_EndConnection(GatekeeperTalk *talk);
void GatekeeperTalk_SayLine10OrF(GatekeeperTalk *talk);
void GatekeeperTalk_StartWaitMissingNpc(GatekeeperTalk *talk);

/* The talk held and released, its topic and start, the session. */
void GatekeeperTalk_Release(GatekeeperTalk *talk);
void GatekeeperTalk_HoldWithSpinner(GatekeeperTalk *talk, int sound);
void GatekeeperTalk_StartLine(GatekeeperTalk *talk, GatekeeperTalkStart *out);
int GatekeeperTalk_HasFriends(GatekeeperTalk *talk);
void GatekeeperTalk_PutFriendCode(GatekeeperTalk *talk, unsigned long long key);
void GatekeeperTalk_StartSession(GatekeeperTalk *talk, unsigned int mode, int connect_mode);
int GatekeeperTalk_EndSession(GatekeeperTalk *talk);
u32 GatekeeperTalk_Topic(GatekeeperTalk *talk);
void GatekeeperTalk_SetTopic(GatekeeperTalk *talk, u32 topic);
void GatekeeperTalk_Start(GatekeeperTalk *talk, struct Gatekeeper *owner);

/* Constructor and destructors. */
GatekeeperTalk *GatekeeperTalk_DestructDelete(GatekeeperTalk *talk);
GatekeeperTalk *GatekeeperTalk_Destruct(GatekeeperTalk *talk);
GatekeeperTalk *GatekeeperTalk_Construct(GatekeeperTalk *talk);

#endif
