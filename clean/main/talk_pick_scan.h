/* A walk through the text of the answer the player picked (class data_020defc0, 0x40 bytes,
 * made on the stack by func_020673e0): a walker of the message texts (message_cursor.h) that
 * hands the first parameter byte of each 10/0 tag it meets to the talk's receiver (vtable slot
 * 0x64, which does nothing in the receiver's own class, talk_receiver.h).
 *
 * Its vtable after the base class's: the destructor, the deleting destructor and slot 5 (a
 * tag: TalkPickScan_OnTag); the other slots are the base class's. */
#ifndef CLEAN_MAIN_TALK_PICK_SCAN_H
#define CLEAN_MAIN_TALK_PICK_SCAN_H

#include "message_decoder.h"
#include "message_walker.h"
#include "types.h"

struct TalkObject;

typedef struct TalkPickScan {
    MessageWalker base;      /* 0x00 */
    struct TalkObject *talk; /* 0x24: the talk whose receiver is told */
    s32 stopped;             /* 0x28: no tag is handed on while set; only ever cleared */
    MessageTag tag;          /* 0x2c: the tag met */
} TalkPickScan;

void TalkPickScan_TellReceiver(TalkPickScan *scan);
void TalkPickScan_Reset(TalkPickScan *scan);
void TalkPickScan_OnTag(TalkPickScan *scan, int position);
void TalkPickScan_Run(TalkPickScan *scan, const void *text);
TalkPickScan *TalkPickScan_Delete(TalkPickScan *scan);
TalkPickScan *TalkPickScan_Destruct(TalkPickScan *scan);
TalkPickScan *TalkPickScan_Construct(TalkPickScan *scan, struct TalkObject *talk);

#endif
