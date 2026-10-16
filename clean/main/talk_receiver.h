/* The receiver a talk is for (class data_020df008, 0x48 bytes; Base_02066994 of
 * include/cpp/main/Base_02066994.h): a message receiver (message_receiver.h: the name of a
 * message file and the number of a message in it) with the speaker's name, the talk showing it
 * and whether the speaker is unnamed. The scene base (scene_base.h), the field actors and the
 * objects that talk derive from it, and override its slots.
 *
 * Its vtable: slots 0 and 1 the destructors, slot 2 (0x08) the reset, slot 3 (0x0c) the folder
 * of the message files ("/script/KOR/message"), then the slots the talk calls, which do nothing
 * here (0x10 to 0x64, 0x70, 0x74), say there is no villager (0x68) and no speaker's kind
 * (0x6c). What the talk asks of them (talk_tags.h, talk_flow.h):
 * - 0x10, 0x14, 0x18: as the field actors and the activity use them, the talk ignored, what
 *   follows a message, the player's answer;
 * - 0x1c to 0x34: the tags of groups 1, 3 and 6;
 * - 0x38 to 0x60: the scene's moves (scene_base.h);
 * - 0x70: the talk closes (TalkFlow_EnterClosing); 0x74: the talk goes on after a stop of its
 *   walk (func_02067be0).
 *
 * The speaker's name is an 8-bit text of 14 bytes (class data_020def4c) on the text base of
 * text_base.h; the word of its attributes at 0x0c is a style the speaker gives with its name,
 * which the talk's name plate reads (func_02067e84). */
#ifndef CLEAN_MAIN_TALK_RECEIVER_H
#define CLEAN_MAIN_TALK_RECEIVER_H

#include "main/message_receiver.h"
#include "main/text_base.h"
#include "types.h"

#define TALK_RECEIVER_NAME_CAPACITY 14
/* What slot 0x6c answers without a speaker (as SceneBase_SpeakingKind does). */
#define TALK_RECEIVER_NO_KIND 5

struct TalkFlowTalk;

/* The speaker's name (0x20 bytes). */
typedef struct TalkReceiverName {
    const TextVtable *vtable;                /* 0x00: data_020def4c */
    u32 length;                              /* 0x04: the text base's */
    const void *attributes;                  /* 0x08: the attributes' vtable */
    s32 style;                               /* 0x0c: the attributes' word */
    u8 attributes_10[2];                     /* 0x10 */
    char chars[TALK_RECEIVER_NAME_CAPACITY]; /* 0x12 */
} TalkReceiverName;

typedef struct TalkReceiver {
    MessageReceiver base;      /* 0x00: its vtable data_020df008, or a derived class's */
    TalkReceiverName speaker;  /* 0x20 */
    struct TalkFlowTalk *talk; /* 0x40: the talk showing the receiver's message, or NULL */
    u8 nameless;               /* 0x44: set when the speaker's name was cleared */
    u8 unk_45[3];
} TalkReceiver;

int TalkReceiverName_Chars(int name);
int TalkReceiverName_Capacity(void);
TalkReceiverName *TalkReceiverName_DestructDelete(TalkReceiverName *name);
void *TalkReceiverName_Destruct(void *name);
void *TalkReceiverName_Construct(void *name);

void TalkReceiver_DropTalk(TalkReceiver *receiver);
void TalkReceiver_SetTalk(TalkReceiver *receiver, struct TalkFlowTalk *talk);
void TalkReceiver_Nothing74(void);
void TalkReceiver_Nothing70(void);
int TalkReceiver_SpeakingKind(void);
int TalkReceiver_Villager(void);
void TalkReceiver_Nothing64(void);
void TalkReceiver_Nothing60(void);
void TalkReceiver_Nothing5c(void);
void TalkReceiver_Nothing58(void);
void TalkReceiver_Nothing54(void);
void TalkReceiver_Nothing50(void);
void TalkReceiver_Nothing4c(void);
void TalkReceiver_Nothing48(void);
void TalkReceiver_Nothing44(void);
void TalkReceiver_Nothing40(void);
void TalkReceiver_Nothing3c(void);
void TalkReceiver_Nothing38(void);
void TalkReceiver_Nothing34(void);
void TalkReceiver_Nothing30(void);
void TalkReceiver_Nothing2c(void);
void TalkReceiver_Nothing28(void);
void TalkReceiver_Nothing24(void);
void TalkReceiver_Nothing20(void);
void TalkReceiver_Nothing1c(void);
void TalkReceiver_Nothing18(void);
void TalkReceiver_Nothing14(void);
void TalkReceiver_Nothing10(void);
int TalkReceiver_Folder(void);
int TalkReceiver_SpeakerStyle(const TalkReceiver *receiver);
u8 TalkReceiver_IsNameless(const TalkReceiver *receiver);
TalkReceiverName *TalkReceiver_SpeakerName(TalkReceiver *receiver);
void TalkReceiver_NextSpeaker(TalkReceiver *receiver, TextBase *name, int style);
void TalkReceiver_ClearSpeaker(TalkReceiver *receiver, int style);
void TalkReceiver_SetSpeakerText(TalkReceiver *receiver, TextBase *name, int style);
void TalkReceiver_SetSpeaker(TalkReceiver *receiver, const char *name, int style);
void TalkReceiver_Reset(TalkReceiver *receiver);
void *TalkReceiver_Destruct(TalkReceiver *receiver);
void *TalkReceiver_DestructDelete(TalkReceiver *receiver);
void *TalkReceiver_DestructSlot(TalkReceiver *receiver);
TalkReceiver *TalkReceiver_Construct(TalkReceiver *receiver);
TalkReceiver *TalkReceiver_ConstructBase(TalkReceiver *receiver);

#endif
