/* The shared records of the multiplayer session (session.h): SESSION_RECORDS records in one
 * table of 0x6a0 bytes (sizes data_020ccfa8, offsets data_020cd050). A record is written by its
 * writer in data_020cd2f4, which SessionRecord_Update calls and then flags the record to be
 * sent when its bytes changed; data_020cd1dc holds what fills each record when the table is
 * made (func_02077598).
 *
 * The records and what their writers do:
 *   0-3    5 bytes   pack the x and z of a point (SessionRecord_PackPoint);
 *   4-7    2 bytes   pack a 16-bit value (SessionRecord_PackValue);
 *   8-11   12 bytes  built by func_0209649c;
 *   12-19  30 bytes  copied from the id's entry at data_021d213c (func_02085310), which also
 *                    sets data_021d2128; the only records with a filler;
 *   20-23  46 bytes  built by func_02039128 from `object`;
 *   24-31  7 bytes   built by overlay 3 (func_ov003_02235c94) from its own table;
 *   32-69  30 bytes  handed with their id to func_0208520c, which sets the first byte of that
 *                    id's 30-byte entry at data_021d232c and copies the entry into the record. */
#ifndef CLEAN_MAIN_SESSION_RECORD_H
#define CLEAN_MAIN_SESSION_RECORD_H

#include "types.h"

/* A record's writer: fills `record` from `object`, as `mode` says. */
typedef void SessionRecordWriter(u8 *record, void *object, int mode);

/* A record's filler, called when the table is made. */
typedef void SessionRecordFiller(u8 *record);

/* The point records 0-3 are written from. */
typedef struct SessionRecordPoint {
    fx32 x;
    fx32 y;
    fx32 z;
} SessionRecordPoint;

void SessionRecord_Init(void);
void SessionRecord_Update(int id, void *object, int mode, int force);

void SessionRecord_Write69(u8 *record, void *object, int mode);
void SessionRecord_Write68(u8 *record, void *object, int mode);
void SessionRecord_Write67(u8 *record, void *object, int mode);
void SessionRecord_Write66(u8 *record, void *object, int mode);
void SessionRecord_Write65(u8 *record, void *object, int mode);
void SessionRecord_Write64(u8 *record, void *object, int mode);
void SessionRecord_Write63(u8 *record, void *object, int mode);
void SessionRecord_Write62(u8 *record, void *object, int mode);
void SessionRecord_Write61(u8 *record, void *object, int mode);
void SessionRecord_Write60(u8 *record, void *object, int mode);
void SessionRecord_Write59(u8 *record, void *object, int mode);
void SessionRecord_Write58(u8 *record, void *object, int mode);
void SessionRecord_Write57(u8 *record, void *object, int mode);
void SessionRecord_Write56(u8 *record, void *object, int mode);
void SessionRecord_Write55(u8 *record, void *object, int mode);
void SessionRecord_Write54(u8 *record, void *object, int mode);
void SessionRecord_Write53(u8 *record, void *object, int mode);
void SessionRecord_Write52(u8 *record, void *object, int mode);
void SessionRecord_Write51(u8 *record, void *object, int mode);
void SessionRecord_Write50(u8 *record, void *object, int mode);
void SessionRecord_Write49(u8 *record, void *object, int mode);
void SessionRecord_Write48(u8 *record, void *object, int mode);
void SessionRecord_Write47(u8 *record, void *object, int mode);
void SessionRecord_Write46(u8 *record, void *object, int mode);
void SessionRecord_Write45(u8 *record, void *object, int mode);
void SessionRecord_Write44(u8 *record, void *object, int mode);
void SessionRecord_Write43(u8 *record, void *object, int mode);
void SessionRecord_Write42(u8 *record, void *object, int mode);
void SessionRecord_Write41(u8 *record, void *object, int mode);
void SessionRecord_Write40(u8 *record, void *object, int mode);
void SessionRecord_Write39(u8 *record, void *object, int mode);
void SessionRecord_Write38(u8 *record, void *object, int mode);
void SessionRecord_Write37(u8 *record, void *object, int mode);
void SessionRecord_Write36(u8 *record, void *object, int mode);
void SessionRecord_Write35(u8 *record, void *object, int mode);
void SessionRecord_Write34(u8 *record, void *object, int mode);
void SessionRecord_Write33(u8 *record, void *object, int mode);
void SessionRecord_Write32(u8 *record, void *object, int mode);
void SessionRecord_Write31(u8 *record, void *object);
void SessionRecord_Write30(u8 *record, void *object);
void SessionRecord_Write29(u8 *record, void *object);
void SessionRecord_Write28(u8 *record, void *object);
void SessionRecord_Write27(u8 *record, void *object);
void SessionRecord_Write26(u8 *record, void *object);
void SessionRecord_Write25(u8 *record, void *object);
void SessionRecord_Write24(u8 *record, void *object);
void SessionRecord_Write23(u8 *record, void *object, int mode);
void SessionRecord_Write22(u8 *record, void *object, int mode);
void SessionRecord_Write21(u8 *record, void *object, int mode);
void SessionRecord_Write20(u8 *record, void *object, int mode);
void SessionRecord_Write19(u8 *record, void *object, int mode);
void SessionRecord_Write18(u8 *record, void *object, int mode);
void SessionRecord_Write17(u8 *record, void *object, int mode);
void SessionRecord_Write16(u8 *record, void *object, int mode);
void SessionRecord_Write15(u8 *record, void *object, int mode);
void SessionRecord_Write14(u8 *record, void *object, int mode);
void SessionRecord_Write13(u8 *record, void *object, int mode);
void SessionRecord_Write12(u8 *record, void *object, int mode);
void SessionRecord_Write11(u8 *record, void *object, int mode);
void SessionRecord_Write10(u8 *record, void *object, int mode);
void SessionRecord_Write9(u8 *record, void *object, int mode);
void SessionRecord_Write8(u8 *record, void *object, int mode);
void SessionRecord_Write7(u8 *record, const s16 *value, int mode);
void SessionRecord_Write6(u8 *record, const s16 *value, int mode);
void SessionRecord_Write5(u8 *record, const s16 *value, int mode);
void SessionRecord_Write4(u8 *record, const s16 *value, int mode);
void SessionRecord_PackValue(u8 *record, const s16 *value);
void SessionRecord_Write3(u8 *record, const SessionRecordPoint *point, int mode);
void SessionRecord_Write2(u8 *record, const SessionRecordPoint *point, int mode);
void SessionRecord_Write1(u8 *record, const SessionRecordPoint *point, int mode);
void SessionRecord_Write0(u8 *record, const SessionRecordPoint *point, int mode);
void SessionRecord_PackPoint(u8 *record, const SessionRecordPoint *point);

void SessionRecord_Fill(int id);
void SessionRecord_Fill19(u8 *record);
void SessionRecord_Fill18(u8 *record);
void SessionRecord_Fill17(u8 *record);
void SessionRecord_Fill16(u8 *record);
void SessionRecord_Fill15(u8 *record);
void SessionRecord_Fill14(u8 *record);
void SessionRecord_Fill13(u8 *record);
void SessionRecord_Fill12(u8 *record);
u16 SessionRecord_GetOffset(u16 id);
u8 SessionRecord_GetSize(u32 id);

#endif
