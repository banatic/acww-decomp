/* A message's INF1 entry as the talks keep it (12 bytes, the layout of bmg_file.h's BmgEntry:
 * the text's offset, then the message's attributes). TalkObject keeps the entry of the message
 * it shows at 0x14ac (TalkObject_LoadMessage copies BmgFile_Entry into it, TalkObject_BeginMessage
 * and its neighbors read it), TalkAnswers one per answer and the picked answer's at 0x354
 * (TalkAnswers_PickByLevel copies one of the candidates into it). The first attribute is the
 * message's kind, 0 to 24, which picks per kind whether the text is centered, the writing speed
 * and the window (data_020d1d0c, data_020d1ca8, data_020d1c44); the others are the change to the
 * villager's fondness, the values the receiver is told as the message begins and ends (or the
 * answer picked), the message that follows and the message's sound. */
#ifndef CLEAN_MAIN_MESSAGE_ENTRY_H
#define CLEAN_MAIN_MESSAGE_ENTRY_H

#include "types.h"

typedef struct MessageEntry {
    u32 text_offset; /* 0x00: from the start of DAT1's data */
    u8 kind;         /* 0x04: 0 to 24, indexes data_020d1c44, data_020d1ca8 and data_020d1d0c */
    u8 fondness;     /* 0x05: the change to the villager's fondness at the message's end */
    u8 begin_value;  /* 0x06: told the receiver as the message begins */
    u8 end_value;    /* 0x07: told it as the message ends, or as the answer picked */
    u8 next;         /* 0x08: the message that follows */
    u8 sound;        /* 0x09: the message's sound (data_020cce84) */
    u8 unk_0a;
    u8 unk_0b;
} MessageEntry;

int MessageEntry_CenteredOfKind(MessageEntry *record);
void *MessageEntry_SpeedOfKind(MessageEntry *record);
int MessageEntry_WindowOfKind(MessageEntry *record);
void MessageEntry_GetNext(u8 *out, MessageEntry *record);
int MessageEntry_Sound(MessageEntry *record);
int MessageEntry_EndValue(MessageEntry *record);
int MessageEntry_BeginValue(MessageEntry *record);
int MessageEntry_Fondness(MessageEntry *record);
int MessageEntry_Kind(MessageEntry *record);
void *MessageEntry_Self(void *record);
void MessageEntry_Clear(MessageEntry *record);
void MessageEntry_Copy(void *dst, const void *src);
void MessageEntry_Destruct(void *record);
MessageEntry *MessageEntry_Construct(MessageEntry *record);

#endif
