/* The shared records of the multiplayer session (session_record.h). */
#include "session_record.h"

#include "clean.h"
#include "main/session.h"

#define RECORD_TABLE_SIZE 0x6a0
#define RECORD_TABLE_ALIGN 4

extern NetSession *data_020ccf94;                  /* the session */
extern SessionRecordWriter *const data_020cd2f4[]; /* the writers, by record id */

extern void *func_02077afc(int size, int align);                  /* from the network heap (data_021c9b30) */
extern u8 func_0207762c(u32 id);                                  /* a record's size */
extern void func_02077598(int id);                                /* fills a record from data_020cd1dc */
extern int func_02064344(const void *a, const void *b, u32 size); /* whether the bytes differ */
extern void func_0208520c(u8 *record, int id);                    /* the record from its entry at data_021d232c */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_0207718c: makes the record table, zeroed, and fills each record.
 * QUIRK: the table is handed to the session before it is checked for NULL; the records are
 * filled even when there is none. */
void SessionRecord_Init(void)
{
    u8 *table = func_02077afc(RECORD_TABLE_SIZE, RECORD_TABLE_ALIGN);
    Session_SetRecordTable(data_020ccf94, table);
    if (table != NULL) {
        MI_CpuFill8(table, 0, RECORD_TABLE_SIZE);
    }
    for (int id = 0; id < SESSION_RECORDS; id++) {
        func_02077598(id);
    }
}
CLEAN_AS(func_0207718c, SessionRecord_Init)

/* func_020771cc: record `id` written by its writer from `object` and `mode`. With `force` the
 * record is flagged to be sent; else, when it was not flagged yet, it is flagged when its bytes
 * changed (compared with a copy in the session's scratch block made before the write).
 * REQUIRES: 0 <= id < SESSION_RECORDS. */
void SessionRecord_Update(int id, void *object, int mode, int force)
{
    NetSession *session = data_020ccf94;
    int flagged = Session_GetRecordFlag(session, id);
    u32 size = func_0207762c((u32) id);
    u8 *record = Session_GetRecord(session, id);

    if (!flagged && !force) {
        MI_CpuCopy8(record, session->record_scratch, size);
    }
    data_020cd2f4[id](record, object, mode);

    if (force) {
        Session_SetRecordFlag(session, id, 1);
    } else if (!flagged) {
        session = data_020ccf94;
        Session_SetRecordFlag(session, id, func_02064344(record, session->record_scratch, size));
    }
}
CLEAN_AS(func_020771cc, SessionRecord_Update)

/* func_02077254: the writer of record 69. */
void SessionRecord_Write69(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 69);
}
CLEAN_AS(func_02077254, SessionRecord_Write69)

/* func_02077260: the writer of record 68. */
void SessionRecord_Write68(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 68);
}
CLEAN_AS(func_02077260, SessionRecord_Write68)

/* func_0207726c: the writer of record 67. */
void SessionRecord_Write67(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 67);
}
CLEAN_AS(func_0207726c, SessionRecord_Write67)

/* func_02077278: the writer of record 66. */
void SessionRecord_Write66(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 66);
}
CLEAN_AS(func_02077278, SessionRecord_Write66)

/* func_02077284: the writer of record 65. */
void SessionRecord_Write65(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 65);
}
CLEAN_AS(func_02077284, SessionRecord_Write65)

/* func_02077290: the writer of record 64. */
void SessionRecord_Write64(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 64);
}
CLEAN_AS(func_02077290, SessionRecord_Write64)

/* func_0207729c: the writer of record 63. */
void SessionRecord_Write63(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 63);
}
CLEAN_AS(func_0207729c, SessionRecord_Write63)

/* func_020772a8: the writer of record 62. */
void SessionRecord_Write62(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 62);
}
CLEAN_AS(func_020772a8, SessionRecord_Write62)

/* func_020772b4: the writer of record 61. */
void SessionRecord_Write61(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 61);
}
CLEAN_AS(func_020772b4, SessionRecord_Write61)

/* func_020772c0: the writer of record 60. */
void SessionRecord_Write60(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 60);
}
CLEAN_AS(func_020772c0, SessionRecord_Write60)

/* func_020772cc: the writer of record 59. */
void SessionRecord_Write59(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 59);
}
CLEAN_AS(func_020772cc, SessionRecord_Write59)

/* func_020772d8: the writer of record 58. */
void SessionRecord_Write58(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 58);
}
CLEAN_AS(func_020772d8, SessionRecord_Write58)

/* func_020772e4: the writer of record 57. */
void SessionRecord_Write57(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 57);
}
CLEAN_AS(func_020772e4, SessionRecord_Write57)

/* func_020772f0: the writer of record 56. */
void SessionRecord_Write56(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 56);
}
CLEAN_AS(func_020772f0, SessionRecord_Write56)

/* func_020772fc: the writer of record 55. */
void SessionRecord_Write55(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 55);
}
CLEAN_AS(func_020772fc, SessionRecord_Write55)

/* func_02077308: the writer of record 54. */
void SessionRecord_Write54(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 54);
}
CLEAN_AS(func_02077308, SessionRecord_Write54)

/* func_02077314: the writer of record 53. */
void SessionRecord_Write53(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 53);
}
CLEAN_AS(func_02077314, SessionRecord_Write53)

/* func_02077320: the writer of record 52. */
void SessionRecord_Write52(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 52);
}
CLEAN_AS(func_02077320, SessionRecord_Write52)

/* func_0207732c: the writer of record 51. */
void SessionRecord_Write51(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 51);
}
CLEAN_AS(func_0207732c, SessionRecord_Write51)

/* func_02077338: the writer of record 50. */
void SessionRecord_Write50(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 50);
}
CLEAN_AS(func_02077338, SessionRecord_Write50)

/* func_02077344: the writer of record 49. */
void SessionRecord_Write49(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 49);
}
CLEAN_AS(func_02077344, SessionRecord_Write49)

/* func_02077350: the writer of record 48. */
void SessionRecord_Write48(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 48);
}
CLEAN_AS(func_02077350, SessionRecord_Write48)

/* func_0207735c: the writer of record 47. */
void SessionRecord_Write47(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 47);
}
CLEAN_AS(func_0207735c, SessionRecord_Write47)

/* func_02077368: the writer of record 46. */
void SessionRecord_Write46(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 46);
}
CLEAN_AS(func_02077368, SessionRecord_Write46)

/* func_02077374: the writer of record 45. */
void SessionRecord_Write45(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 45);
}
CLEAN_AS(func_02077374, SessionRecord_Write45)

/* func_02077380: the writer of record 44. */
void SessionRecord_Write44(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    func_0208520c(record, 44);
}
CLEAN_AS(func_02077380, SessionRecord_Write44)
