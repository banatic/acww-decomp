/* The shared records of the multiplayer session (session.h): SESSION_RECORDS records in one
 * table of 0x6a0 bytes (sizes data_020ccfa8, offsets data_020cd050). A record is written by its
 * writer in data_020cd2f4, which SessionRecord_Update calls and then flags the record to be
 * sent when its bytes changed; data_020cd1dc holds what fills each record when the table is
 * made (func_02077598).
 *
 * The writers of records 44-69 here each hand their record and its id to func_0208520c, which
 * sets the first byte of that id's 30-byte entry at data_021d232c (ids 32-69) and copies the
 * entry into the record. */
#ifndef CLEAN_MAIN_SESSION_RECORD_H
#define CLEAN_MAIN_SESSION_RECORD_H

#include "types.h"

/* A record's writer: fills `record` from `object`, as `mode` says. */
typedef void SessionRecordWriter(u8 *record, void *object, int mode);

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

#endif
