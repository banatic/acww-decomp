/* The shared records of the multiplayer session (session_record.h). */
#include "session_record.h"

#include "clean.h"
#include "main/packed_bytes.h"
#include "main/session.h"
#include "main/session_net.h"
#include "c_library.h"
#include "ov003/town_insect_tables.h"
#include "quick_message.h"
#include "scene_share_table.h"
#include "session_players.h"

#define RECORD_TABLE_SIZE 0x6a0
#define RECORD_TABLE_ALIGN 4

extern NetSession *data_020ccf94;                  /* the session */
extern SessionRecordWriter *const data_020cd2f4[]; /* the writers, by record id */

extern SessionRecordFiller *const data_020cd1dc[]; /* the fillers, by record id */
extern const u16 data_020cd050[];                  /* each record's offset in the table */
extern const u8 data_020ccfa8[];                   /* each record's size */

/* The packers of records 0-7 (the actors' saved states use them too). */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_0207718c: makes the record table, zeroed, and fills each record.
 * QUIRK: the table is handed to the session before it is checked for NULL; the records are
 * filled even when there is none. */
void SessionRecord_Init(void)
{
    u8 *table = SessionNet_Alloc(RECORD_TABLE_SIZE, RECORD_TABLE_ALIGN);
    Session_SetRecordTable(data_020ccf94, table);
    if (table != NULL) {
        MI_CpuFill8(table, 0, RECORD_TABLE_SIZE);
    }
    for (int id = 0; id < SESSION_RECORDS; id++) {
        SessionRecord_Fill(id);
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
    u32 size = SessionRecord_GetSize((u32) id);
    u8 *record = Session_GetRecord(session, id);

    if (!flagged && !force) {
        MI_CpuCopy8(record, session->record_scratch, size);
    }
    data_020cd2f4[id](record, object, mode);

    if (force) {
        Session_SetRecordFlag(session, id, 1);
    } else if (!flagged) {
        session = data_020ccf94;
        Session_SetRecordFlag(session, id, CLib_BytesDiffer(record, session->record_scratch, size));
    }
}
CLEAN_AS(func_020771cc, SessionRecord_Update)

/* func_02077254: the writer of record 69. */
void SessionRecord_Write69(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 69);
}
CLEAN_AS(func_02077254, SessionRecord_Write69)

/* func_02077260: the writer of record 68. */
void SessionRecord_Write68(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 68);
}
CLEAN_AS(func_02077260, SessionRecord_Write68)

/* func_0207726c: the writer of record 67. */
void SessionRecord_Write67(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 67);
}
CLEAN_AS(func_0207726c, SessionRecord_Write67)

/* func_02077278: the writer of record 66. */
void SessionRecord_Write66(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 66);
}
CLEAN_AS(func_02077278, SessionRecord_Write66)

/* func_02077284: the writer of record 65. */
void SessionRecord_Write65(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 65);
}
CLEAN_AS(func_02077284, SessionRecord_Write65)

/* func_02077290: the writer of record 64. */
void SessionRecord_Write64(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 64);
}
CLEAN_AS(func_02077290, SessionRecord_Write64)

/* func_0207729c: the writer of record 63. */
void SessionRecord_Write63(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 63);
}
CLEAN_AS(func_0207729c, SessionRecord_Write63)

/* func_020772a8: the writer of record 62. */
void SessionRecord_Write62(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 62);
}
CLEAN_AS(func_020772a8, SessionRecord_Write62)

/* func_020772b4: the writer of record 61. */
void SessionRecord_Write61(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 61);
}
CLEAN_AS(func_020772b4, SessionRecord_Write61)

/* func_020772c0: the writer of record 60. */
void SessionRecord_Write60(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 60);
}
CLEAN_AS(func_020772c0, SessionRecord_Write60)

/* func_020772cc: the writer of record 59. */
void SessionRecord_Write59(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 59);
}
CLEAN_AS(func_020772cc, SessionRecord_Write59)

/* func_020772d8: the writer of record 58. */
void SessionRecord_Write58(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 58);
}
CLEAN_AS(func_020772d8, SessionRecord_Write58)

/* func_020772e4: the writer of record 57. */
void SessionRecord_Write57(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 57);
}
CLEAN_AS(func_020772e4, SessionRecord_Write57)

/* func_020772f0: the writer of record 56. */
void SessionRecord_Write56(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 56);
}
CLEAN_AS(func_020772f0, SessionRecord_Write56)

/* func_020772fc: the writer of record 55. */
void SessionRecord_Write55(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 55);
}
CLEAN_AS(func_020772fc, SessionRecord_Write55)

/* func_02077308: the writer of record 54. */
void SessionRecord_Write54(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 54);
}
CLEAN_AS(func_02077308, SessionRecord_Write54)

/* func_02077314: the writer of record 53. */
void SessionRecord_Write53(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 53);
}
CLEAN_AS(func_02077314, SessionRecord_Write53)

/* func_02077320: the writer of record 52. */
void SessionRecord_Write52(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 52);
}
CLEAN_AS(func_02077320, SessionRecord_Write52)

/* func_0207732c: the writer of record 51. */
void SessionRecord_Write51(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 51);
}
CLEAN_AS(func_0207732c, SessionRecord_Write51)

/* func_02077338: the writer of record 50. */
void SessionRecord_Write50(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 50);
}
CLEAN_AS(func_02077338, SessionRecord_Write50)

/* func_02077344: the writer of record 49. */
void SessionRecord_Write49(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 49);
}
CLEAN_AS(func_02077344, SessionRecord_Write49)

/* func_02077350: the writer of record 48. */
void SessionRecord_Write48(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 48);
}
CLEAN_AS(func_02077350, SessionRecord_Write48)

/* func_0207735c: the writer of record 47. */
void SessionRecord_Write47(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 47);
}
CLEAN_AS(func_0207735c, SessionRecord_Write47)

/* func_02077368: the writer of record 46. */
void SessionRecord_Write46(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 46);
}
CLEAN_AS(func_02077368, SessionRecord_Write46)

/* func_02077374: the writer of record 45. */
void SessionRecord_Write45(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 45);
}
CLEAN_AS(func_02077374, SessionRecord_Write45)

/* func_02077380: the writer of record 44. */
void SessionRecord_Write44(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 44);
}
CLEAN_AS(func_02077380, SessionRecord_Write44)

/* func_0207738c: the writer of record 43. */
void SessionRecord_Write43(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 43);
}
CLEAN_AS(func_0207738c, SessionRecord_Write43)

/* func_02077398: the writer of record 42. */
void SessionRecord_Write42(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 42);
}
CLEAN_AS(func_02077398, SessionRecord_Write42)

/* func_020773a4: the writer of record 41. */
void SessionRecord_Write41(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 41);
}
CLEAN_AS(func_020773a4, SessionRecord_Write41)

/* func_020773b0: the writer of record 40. */
void SessionRecord_Write40(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 40);
}
CLEAN_AS(func_020773b0, SessionRecord_Write40)

/* func_020773bc: the writer of record 39. */
void SessionRecord_Write39(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 39);
}
CLEAN_AS(func_020773bc, SessionRecord_Write39)

/* func_020773c8: the writer of record 38. */
void SessionRecord_Write38(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 38);
}
CLEAN_AS(func_020773c8, SessionRecord_Write38)

/* func_020773d4: the writer of record 37. */
void SessionRecord_Write37(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 37);
}
CLEAN_AS(func_020773d4, SessionRecord_Write37)

/* func_020773e0: the writer of record 36. */
void SessionRecord_Write36(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 36);
}
CLEAN_AS(func_020773e0, SessionRecord_Write36)

/* func_020773ec: the writer of record 35. */
void SessionRecord_Write35(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 35);
}
CLEAN_AS(func_020773ec, SessionRecord_Write35)

/* func_020773f8: the writer of record 34. */
void SessionRecord_Write34(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 34);
}
CLEAN_AS(func_020773f8, SessionRecord_Write34)

/* func_02077404: the writer of record 33. */
void SessionRecord_Write33(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 33);
}
CLEAN_AS(func_02077404, SessionRecord_Write33)

/* func_02077410: the writer of record 32. */
void SessionRecord_Write32(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordD(record, 32);
}
CLEAN_AS(func_02077410, SessionRecord_Write32)

/* func_0207741c: the writer of record 31. */
void SessionRecord_Write31(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 31, object);
}
CLEAN_AS(func_0207741c, SessionRecord_Write31)

/* func_02077428: the writer of record 30. */
void SessionRecord_Write30(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 30, object);
}
CLEAN_AS(func_02077428, SessionRecord_Write30)

/* func_02077434: the writer of record 29. */
void SessionRecord_Write29(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 29, object);
}
CLEAN_AS(func_02077434, SessionRecord_Write29)

/* func_02077440: the writer of record 28. */
void SessionRecord_Write28(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 28, object);
}
CLEAN_AS(func_02077440, SessionRecord_Write28)

/* func_0207744c: the writer of record 27. */
void SessionRecord_Write27(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 27, object);
}
CLEAN_AS(func_0207744c, SessionRecord_Write27)

/* func_02077458: the writer of record 26. */
void SessionRecord_Write26(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 26, object);
}
CLEAN_AS(func_02077458, SessionRecord_Write26)

/* func_02077464: the writer of record 25. */
void SessionRecord_Write25(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 25, object);
}
CLEAN_AS(func_02077464, SessionRecord_Write25)

/* func_02077470: the writer of record 24. */
void SessionRecord_Write24(u8 *record, void *object)
{
    TownInsectTables_WriteRecord(record, 24, object);
}
CLEAN_AS(func_02077470, SessionRecord_Write24)

/* func_0207747c: the writer of record 23. */
void SessionRecord_Write23(u8 *record, void *object, int mode)
{
    (void) mode;
    QuickMessage_WriteRecordOf(record, 23, object);
}
CLEAN_AS(func_0207747c, SessionRecord_Write23)

/* func_02077488: the writer of record 22. */
void SessionRecord_Write22(u8 *record, void *object, int mode)
{
    (void) mode;
    QuickMessage_WriteRecordOf(record, 22, object);
}
CLEAN_AS(func_02077488, SessionRecord_Write22)

/* func_02077494: the writer of record 21. */
void SessionRecord_Write21(u8 *record, void *object, int mode)
{
    (void) mode;
    QuickMessage_WriteRecordOf(record, 21, object);
}
CLEAN_AS(func_02077494, SessionRecord_Write21)

/* func_020774a0: the writer of record 20. */
void SessionRecord_Write20(u8 *record, void *object, int mode)
{
    (void) mode;
    QuickMessage_WriteRecordOf(record, 20, object);
}
CLEAN_AS(func_020774a0, SessionRecord_Write20)

/* func_020774ac: the writer of record 19. */
void SessionRecord_Write19(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 19);
}
CLEAN_AS(func_020774ac, SessionRecord_Write19)

/* func_020774b8: the writer of record 18. */
void SessionRecord_Write18(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 18);
}
CLEAN_AS(func_020774b8, SessionRecord_Write18)

/* func_020774c4: the writer of record 17. */
void SessionRecord_Write17(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 17);
}
CLEAN_AS(func_020774c4, SessionRecord_Write17)

/* func_020774d0: the writer of record 16. */
void SessionRecord_Write16(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 16);
}
CLEAN_AS(func_020774d0, SessionRecord_Write16)

/* func_020774dc: the writer of record 15. */
void SessionRecord_Write15(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 15);
}
CLEAN_AS(func_020774dc, SessionRecord_Write15)

/* func_020774e8: the writer of record 14. */
void SessionRecord_Write14(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 14);
}
CLEAN_AS(func_020774e8, SessionRecord_Write14)

/* func_020774f4: the writer of record 13. */
void SessionRecord_Write13(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 13);
}
CLEAN_AS(func_020774f4, SessionRecord_Write13)

/* func_02077500: the writer of record 12. */
void SessionRecord_Write12(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SceneShareTable_WriteRecordE(record, 12);
}
CLEAN_AS(func_02077500, SessionRecord_Write12)

/* func_0207750c: the writer of record 11. */
void SessionRecord_Write11(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SessionPlayers_WriteStateRecord(record, 11);
}
CLEAN_AS(func_0207750c, SessionRecord_Write11)

/* func_02077518: the writer of record 10. */
void SessionRecord_Write10(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SessionPlayers_WriteStateRecord(record, 10);
}
CLEAN_AS(func_02077518, SessionRecord_Write10)

/* func_02077524: the writer of record 9. */
void SessionRecord_Write9(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SessionPlayers_WriteStateRecord(record, 9);
}
CLEAN_AS(func_02077524, SessionRecord_Write9)

/* func_02077530: the writer of record 8. */
void SessionRecord_Write8(u8 *record, void *object, int mode)
{
    (void) object;
    (void) mode;
    SessionPlayers_WriteStateRecord(record, 8);
}
CLEAN_AS(func_02077530, SessionRecord_Write8)

/* func_0207753c: the writer of record 7: `*value` packed. */
void SessionRecord_Write7(u8 *record, const s16 *value, int mode)
{
    (void) mode;
    SessionRecord_PackValue(record, value);
}
CLEAN_AS(func_0207753c, SessionRecord_Write7)

/* func_02077544: the writer of record 6: `*value` packed. */
void SessionRecord_Write6(u8 *record, const s16 *value, int mode)
{
    (void) mode;
    SessionRecord_PackValue(record, value);
}
CLEAN_AS(func_02077544, SessionRecord_Write6)

/* func_0207754c: the writer of record 5: `*value` packed. */
void SessionRecord_Write5(u8 *record, const s16 *value, int mode)
{
    (void) mode;
    SessionRecord_PackValue(record, value);
}
CLEAN_AS(func_0207754c, SessionRecord_Write5)

/* func_02077554: the writer of record 4: `*value` packed. */
void SessionRecord_Write4(u8 *record, const s16 *value, int mode)
{
    (void) mode;
    SessionRecord_PackValue(record, value);
}
CLEAN_AS(func_02077554, SessionRecord_Write4)

/* func_0207755c: `*value` packed into 2 bytes (PackedBytes_WriteS16). */
void SessionRecord_PackValue(u8 *record, const s16 *value)
{
    PackedBytes_WriteS16(record, *value);
}
CLEAN_AS(func_0207755c, SessionRecord_PackValue)

/* func_02077568: the writer of record 3: `point` packed. */
void SessionRecord_Write3(u8 *record, const SessionRecordPoint *point, int mode)
{
    (void) mode;
    SessionRecord_PackPoint(record, point);
}
CLEAN_AS(func_02077568, SessionRecord_Write3)

/* func_02077570: the writer of record 2: `point` packed. */
void SessionRecord_Write2(u8 *record, const SessionRecordPoint *point, int mode)
{
    (void) mode;
    SessionRecord_PackPoint(record, point);
}
CLEAN_AS(func_02077570, SessionRecord_Write2)

/* func_02077578: the writer of record 1: `point` packed. */
void SessionRecord_Write1(u8 *record, const SessionRecordPoint *point, int mode)
{
    (void) mode;
    SessionRecord_PackPoint(record, point);
}
CLEAN_AS(func_02077578, SessionRecord_Write1)

/* func_02077580: the writer of record 0: `point` packed. */
void SessionRecord_Write0(u8 *record, const SessionRecordPoint *point, int mode)
{
    (void) mode;
    SessionRecord_PackPoint(record, point);
}
CLEAN_AS(func_02077580, SessionRecord_Write0)

/* func_02077588: the x and z of `point` packed into 5 bytes (PackedBytes_PackPoint); y is left out. */
void SessionRecord_PackPoint(u8 *record, const SessionRecordPoint *point)
{
    PackedBytes_PackPoint(record, point->x, point->z);
}
CLEAN_AS(func_02077588, SessionRecord_PackPoint)

/* func_02077598: record `id` filled by its filler in data_020cd1dc, when it has one (records
 * 12-19).
 * QUIRK: the filler is handed NULL while the session has no record table (SessionRecord_Init
 * fills the records even then).
 * REQUIRES: 0 <= id < SESSION_RECORDS. */
void SessionRecord_Fill(int id)
{
    SessionRecordFiller *fill = data_020cd1dc[id];
    if (fill != NULL) {
        fill(Session_GetRecord(data_020ccf94, id));
    }
}
CLEAN_AS(func_02077598, SessionRecord_Fill)

/* func_020775c0: the filler of record 19. */
void SessionRecord_Fill19(u8 *record)
{
    SceneShareTable_FillRecordE(record, 19);
}
CLEAN_AS(func_020775c0, SessionRecord_Fill19)

/* func_020775cc: the filler of record 18. */
void SessionRecord_Fill18(u8 *record)
{
    SceneShareTable_FillRecordE(record, 18);
}
CLEAN_AS(func_020775cc, SessionRecord_Fill18)

/* func_020775d8: the filler of record 17. */
void SessionRecord_Fill17(u8 *record)
{
    SceneShareTable_FillRecordE(record, 17);
}
CLEAN_AS(func_020775d8, SessionRecord_Fill17)

/* func_020775e4: the filler of record 16. */
void SessionRecord_Fill16(u8 *record)
{
    SceneShareTable_FillRecordE(record, 16);
}
CLEAN_AS(func_020775e4, SessionRecord_Fill16)

/* func_020775f0: the filler of record 15. */
void SessionRecord_Fill15(u8 *record)
{
    SceneShareTable_FillRecordE(record, 15);
}
CLEAN_AS(func_020775f0, SessionRecord_Fill15)

/* func_020775fc: the filler of record 14. */
void SessionRecord_Fill14(u8 *record)
{
    SceneShareTable_FillRecordE(record, 14);
}
CLEAN_AS(func_020775fc, SessionRecord_Fill14)

/* func_02077608: the filler of record 13. */
void SessionRecord_Fill13(u8 *record)
{
    SceneShareTable_FillRecordE(record, 13);
}
CLEAN_AS(func_02077608, SessionRecord_Fill13)

/* func_02077614: the filler of record 12. */
void SessionRecord_Fill12(u8 *record)
{
    SceneShareTable_FillRecordE(record, 12);
}
CLEAN_AS(func_02077614, SessionRecord_Fill12)

/* func_02077620: a record's offset in the record table.
 * REQUIRES: id < SESSION_RECORDS. */
u16 SessionRecord_GetOffset(u16 id)
{
    return data_020cd050[id];
}
CLEAN_AS(func_02077620, SessionRecord_GetOffset)

/* func_0207762c: a record's size in bytes.
 * REQUIRES: id < SESSION_RECORDS. */
u8 SessionRecord_GetSize(u32 id)
{
    return data_020ccfa8[id];
}
CLEAN_AS(func_0207762c, SessionRecord_GetSize)
