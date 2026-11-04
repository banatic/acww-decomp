/* What the game fetches from and sends to Nintendo's servers over the Nintendo Wi-Fi
 * Connection (overlay 48 drives the steps), and what is done with it when the session ends:
 *
 *   a notice for the town's board: "forest_bbs_KOR.bin" from the game's page at
 *   www.nintendo.co.jp, 0xd2 bytes (data_021f3cbc) ending in an HMAC of the rest;
 *   a letter: "forest_mail_KOR.bin", 0x114 bytes (data_021f3d90), with its HMAC at 0x102;
 *   the town's mystery cat record, Blanca's face (mystery_cat_record.h; 0x238 bytes at 0x16ad0
 *   of the state block, data_021f3278): fetched signed from gamestats.gs.nintendowifi.net's download.asp into
 *   data_021f40a4 while its status (byte 0x236) is 0, sent to upload.asp when it is 3.
 *
 * A FinishGet step marks its download as received; WfcSession_End then checks each one (the
 * HMAC with the game's key, or the record's checksum) and hands it on. */
#ifndef CLEAN_MAIN_WFC_SESSION_H
#define CLEAN_MAIN_WFC_SESSION_H

#include "types.h"

void WfcSession_ApplyNotice(void);
void WfcSession_ApplyLetter(void);
void WfcSession_ApplyCatRecord(void);
int WfcSession_FinishCatRecordUpload(void);
int WfcSession_FinishNoticeGet(void);
int WfcSession_FinishLetterGet(void);
int WfcSession_FinishCatRecordGet(void);
int WfcSession_StartNoticeGet(void);
int WfcSession_StartLetterGet(void);
int WfcSession_StartCatRecordGet(void);
int WfcSession_StartCatRecordUpload(void);
int WfcSession_End(void *unused);
void WfcSession_KeepFriendData(void);

#endif
