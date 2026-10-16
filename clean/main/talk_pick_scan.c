/* A walk through the picked answer's text for its 10/0 tags (talk_pick_scan.h). */
#include "talk_pick_scan.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "message_tag.h"
#include "talk_object.h"
#include "text_walker.h"

static_assert(offsetof(TalkPickScan, talk) == 0x24, "TalkPickScan talk");
static_assert(offsetof(TalkPickScan, stopped) == 0x28, "TalkPickScan stopped");
static_assert(offsetof(TalkPickScan, tag) == 0x2c, "TalkPickScan tag");
static_assert(sizeof(TalkPickScan) == 0x40, "TalkPickScan");

/* The class's vtable, and the walkers' base class's. */
extern const u8 data_020defc0[];
extern const u8 data_020e3e68[];

/* The tag handed on: group 10, kind 0. */
#define TALK_PICK_SCAN_GROUP 10
#define TALK_PICK_SCAN_KIND 0

/* The receiver's vtable slot told the tag's byte. */
#define TALK_PICK_SCAN_SLOT_RECEIVER 0x64

typedef void TalkPickScanSlot(void *receiver, u8 value);

/* func_02069168: the first parameter byte of the tag met handed to the talk's receiver (its
 * vtable slot 0x64).
 * REQUIRES: the talk has a receiver. */
void TalkPickScan_TellReceiver(TalkPickScan *scan)
{
    u8 value;
    MessageTag_GetFirstByte(&scan->tag, &value);
    void *receiver = scan->talk->receiver;
    const u8 *vtable = *(const u8 *const *) receiver;
    u32 function = *(const u32 *) (const void *) (vtable + TALK_PICK_SCAN_SLOT_RECEIVER);
    ((TalkPickScanSlot *) (uintptr_t) function)(receiver, value);
}
CLEAN_AS(func_02069168, TalkPickScan_TellReceiver)

/* func_02069194: not stopped, and the tag made empty. */
void TalkPickScan_Reset(TalkPickScan *scan)
{
    scan->stopped = 0;
    MessageTag_Construct(&scan->tag);
}
CLEAN_AS(func_02069194, TalkPickScan_Reset)

/* func_020691a4 (slot 5): the tag at `position` read; a 10/0 tag handed to the receiver
 * unless the scan is stopped. */
void TalkPickScan_OnTag(TalkPickScan *scan, int position)
{
    MessageTag_Read(&scan->tag, position);
    if (scan->stopped == 0) {
        if (scan->tag.group == TALK_PICK_SCAN_GROUP && scan->tag.kind == TALK_PICK_SCAN_KIND) {
            TalkPickScan_TellReceiver(scan);
        }
    }
}
CLEAN_AS(func_020691a4, TalkPickScan_OnTag)

/* func_020691cc: `text` walked from its start to its end. */
void TalkPickScan_Run(TalkPickScan *scan, const void *text)
{
    TalkPickScan_Reset(scan);
    scan->stopped = 0;
    MessageWalker_Start(&scan->base, (int) (uintptr_t) text);
    TextWalker_Run(&scan->base, 0);
}
CLEAN_AS(func_020691cc, TalkPickScan_Run)

/* func_020691f4 (slot 1): the destructor, and the walk freed. */
TalkPickScan *TalkPickScan_Delete(TalkPickScan *scan)
{
    scan->base.vtable = data_020defc0;
    scan->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(scan);
    Heap_OperatorDeleteB(scan);
    return scan;
}
CLEAN_AS(func_020691f4, TalkPickScan_Delete)

/* func_0206921c (slot 0): the destructor: its vtable, the base class's, then the walkers' base
 * destructor. */
TalkPickScan *TalkPickScan_Destruct(TalkPickScan *scan)
{
    scan->base.vtable = data_020defc0;
    scan->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(scan);
    return scan;
}
CLEAN_AS(func_0206921c, TalkPickScan_Destruct)

/* func_0206923c: the constructor, for `talk`: not stopped, no tag. */
TalkPickScan *TalkPickScan_Construct(TalkPickScan *scan, struct TalkObject *talk)
{
    MessageWalker_Construct(&scan->base);
    scan->base.vtable = data_020e3e68;
    scan->base.vtable = data_020defc0;
    scan->talk = talk;
    scan->stopped = 0;
    MessageTag_Construct(&scan->tag);
    return scan;
}
CLEAN_AS(func_0206923c, TalkPickScan_Construct)
