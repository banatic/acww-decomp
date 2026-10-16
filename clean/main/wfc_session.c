/* What the game fetches from and sends to Nintendo's servers (wfc_session.h). */
#include "wfc_session.h"

#include <string.h>

#include "autoload_2/network.h"
#include "backup_card.h"
#include "clean.h"
#include "library_overlay.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"
#include "session_link.h"
#include "state_block.h"
#include "wifi_friends.h"

#define NOTICE_SIZE 0xd2
#define LETTER_SIZE 0x114
#define STATS_SIZE 0x238
#define HMAC_SIZE 0x10 /* the digest, and the key's length */
#define URL_SIZE 0x80

/* The statistics record's status (byte 0x236). */
enum WfcStatsStatus {
    WFC_STATS_NONE = 0,     /* to be fetched */
    WFC_STATS_RECEIVED = 1, /* fetched and checked */
    WFC_STATS_TO_SEND = 3,  /* to be sent */
};

/* The state block flag that keeps the notice and the letter from being fetched. */
#define STATE_BLOCK_FLAG_NO_DOWNLOADS 20

/* The network modes of the Wi-Fi Connection (Net_GetMode): hosting and joining. */
#define NET_MODE_WFC_HOSTING 3
#define NET_MODE_WFC_JOINING 4

#define GATEKEEPER_TALK 0
#define GATEKEEPER_SAVE_FAILED 2 /* the message shown when the friend roster was not written */

extern StateBlock data_021dc7a8;
extern NetSession *data_020ccf94;

/* What was fetched, and whether each fetch has finished since it was last applied. */
extern u8 data_021f3cbc[NOTICE_SIZE];
extern u8 data_021f3d90[LETTER_SIZE];
extern u8 data_021f40a4[STATS_SIZE];
extern u8 data_021f3c18; /* the notice */
extern u8 data_021f3c04; /* the letter */
extern u8 data_021f3c14; /* the statistics */

/* The statistics record in the state block (its part at 0x16ad0). */
extern u8 data_021f3278[STATS_SIZE];

extern const char *const data_020e3800; /* "kr": the region the signed requests name */
extern const char *const data_020e3804; /* "forest_bbs_KOR.bin" */
extern const char *const data_020e3808; /* "http://www.nintendo.co.jp/ds/admj/oidydm/" */
extern const char *const data_020e380c; /* "forest_mail_KOR.bin" */
extern const char data_020e3bb0[];      /* ".../acrossingds/download.asp" */
extern const char data_020e3bf0[];      /* ".../acrossingds/upload.asp" */
extern const char data_020e3c2c[];      /* "sp_npc_gatekeeper" */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void DGT_Hash1CalcHmac(void *digest, const void *data, int length, const void *key, int key_length);
extern char *func_0212d914(char *dst, const char *src);           /* appends `src` to `dst` */
extern int func_02064344(const void *a, const void *b, u32 size); /* whether the bytes differ */
extern const void *func_02000b7c(void);                           /* the HMAC key */

/* A notice: its constructor and destructor (they do nothing), where its HMAC is, and posting
 * it on the board when its serial is new. */
extern void func_0203f5e0(u8 *notice);
extern void func_0203f5dc(u8 *notice);
extern u8 *func_0203f5d8(u8 *notice);
extern int func_0203f5a4(u8 *notice);
/* A letter: its constructor and destructor, where its HMAC is, and delivering it to the
 * current player when its number is new. */
extern u8 *func_0203f674(u8 *letter);
extern u8 *func_0203f664(u8 *letter);
extern u8 *func_0203f658(u8 *letter);
extern int func_0203f5e4(u8 *letter);
/* The statistics record: its status (get, set), its checksum (get, set) and resetting it. */
extern u8 func_02088208(u8 *record);
extern void func_02088214(u8 *record, u8 status);
extern u16 func_020881ac(u8 *record);
extern void func_020881b8(u8 *record, u16 checksum);
extern void func_02088250(u8 *record);

/* The current player's friend roster written to both copies on the card: 1 when a write
 * failed. */
extern int func_020a1518(void);
/* Talk `index`, its two flags reset, and a message of a file given to it. */
extern void *func_020682e0(int index);
extern void func_02068358(void *talk);
extern void func_02068434(void *talk);
extern void func_0206844c(void *talk, const u8 *message, const char *name);

/* func_0209fc60: a notice that was received checked against its HMAC and, when it matches,
 * posted on the board; the received notice is then cleared. */
void WfcSession_ApplyNotice(void)
{
    if (data_021f3c18 == 0) {
        return;
    }
    data_021f3c18 = 0;
    u8 copy[NOTICE_SIZE];
    u8 digest[HMAC_SIZE];
    func_0203f5e0(copy);
    MI_CpuCopy8(data_021f3cbc, copy, NOTICE_SIZE);
    MI_CpuFill8(func_0203f5d8(copy), 0, HMAC_SIZE);
    DGT_Hash1CalcHmac(digest, copy, NOTICE_SIZE, func_02000b7c(), HMAC_SIZE);
    if (func_02064344(func_0203f5d8(data_021f3cbc), digest, HMAC_SIZE) == 0) {
        func_0203f5a4(data_021f3cbc);
    }
    MI_CpuFill8(data_021f3cbc, 0, NOTICE_SIZE);
    func_0203f5dc(copy);
}
CLEAN_AS(func_0209fc60, WfcSession_ApplyNotice)

/* func_0209fcd8: a letter that was received checked against its HMAC and, when it matches,
 * delivered; the received letter is then cleared. */
void WfcSession_ApplyLetter(void)
{
    if (data_021f3c04 == 0) {
        return;
    }
    data_021f3c04 = 0;
    u8 copy[LETTER_SIZE];
    u8 digest[HMAC_SIZE];
    func_0203f674(copy);
    MI_CpuCopy8(data_021f3d90, copy, LETTER_SIZE);
    MI_CpuFill8(func_0203f658(copy), 0, HMAC_SIZE);
    DGT_Hash1CalcHmac(digest, copy, LETTER_SIZE, func_02000b7c(), HMAC_SIZE);
    if (func_02064344(func_0203f658(data_021f3d90), digest, HMAC_SIZE) == 0) {
        func_0203f5e4(data_021f3d90);
    }
    MI_CpuFill8(data_021f3d90, 0, LETTER_SIZE);
    func_0203f664(copy);
}
CLEAN_AS(func_0209fcd8, WfcSession_ApplyLetter)

/* func_0209fd54: a statistics record that was received and whose halfwords sum to 0 marked
 * received and copied into the state block; the received one is then cleared, with a checksum
 * of 1 so that it no longer sums to 0. */
void WfcSession_ApplyStats(void)
{
    if (data_021f3c14 == 0) {
        return;
    }
    data_021f3c14 = 0;
    if (BackupCard_Sum((unsigned short *) (void *) data_021f40a4, STATS_SIZE) == 0) {
        func_02088214(data_021f40a4, WFC_STATS_RECEIVED);
        MI_CpuCopy8(data_021f40a4, data_021f3278, STATS_SIZE);
    }
    MI_CpuFill8(data_021f40a4, 0, STATS_SIZE);
    func_020881b8(data_021f40a4, 1);
}
CLEAN_AS(func_0209fd54, WfcSession_ApplyStats)

/* func_0209fdac: once the upload finished, the record in the state block reset; whether it
 * finished. */
int WfcSession_FinishStatsUpload(void)
{
    LibraryOverlay_Require65();
    if (Wfc_FinishPost() != 0) {
        func_02088250(data_021f3278);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0209fdac, WfcSession_FinishStatsUpload)

/* func_0209fdd4: once the notice's download finished, it is marked received; whether it
 * finished. */
int WfcSession_FinishNoticeGet(void)
{
    LibraryOverlay_Require65();
    if (Wfc_FinishGet() != 0) {
        data_021f3c18 = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0209fdd4, WfcSession_FinishNoticeGet)

/* func_0209fdf8: the same for the letter. */
int WfcSession_FinishLetterGet(void)
{
    LibraryOverlay_Require65();
    if (Wfc_FinishGet() != 0) {
        data_021f3c04 = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0209fdf8, WfcSession_FinishLetterGet)

/* func_0209fe1c: the same for the statistics. */
int WfcSession_FinishStatsGet(void)
{
    LibraryOverlay_Require65();
    if (Wfc_FinishGet() != 0) {
        data_021f3c14 = 1;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0209fe1c, WfcSession_FinishStatsGet)

/* The download of `file` from the game's page into `buffer` started; whether it was. None is
 * started while the state block's flag STATE_BLOCK_FLAG_NO_DOWNLOADS is set.
 * QUIRK: the game also passes the region (data_020e3800) as a fourth argument, which Wfc_Get
 * does not take. */
static int start_page_get(const char *file, u8 *buffer, int size)
{
    if (StateBlock_TestFlag((u32 *) (void *) &data_021dc7a8, STATE_BLOCK_FLAG_NO_DOWNLOADS) != 0) {
        return 0;
    }
    char url[URL_SIZE];
    strcpy(url, data_020e3808);
    func_0212d914(url, file);
    LibraryOverlay_Require65();
    return Wfc_Get(url, buffer, size) != 0;
}

/* func_0209fe40 */
int WfcSession_StartNoticeGet(void)
{
    return start_page_get(data_020e3804, data_021f3cbc, NOTICE_SIZE);
}
CLEAN_AS(func_0209fe40, WfcSession_StartNoticeGet)

/* func_0209fea4 */
int WfcSession_StartLetterGet(void)
{
    return start_page_get(data_020e380c, data_021f3d90, LETTER_SIZE);
}
CLEAN_AS(func_0209fea4, WfcSession_StartLetterGet)

/* func_0209ff0c: while the state block's record has status WFC_STATS_NONE, the signed download
 * of a new one started; whether it was. */
int WfcSession_StartStatsGet(void)
{
    if (func_02088208(data_021f3278) != WFC_STATS_NONE) {
        return 0;
    }
    LibraryOverlay_Require65();
    return Wfc_GetSigned(data_020e3bb0, data_021f40a4, STATS_SIZE, data_020e3800) != 0;
}
CLEAN_AS(func_0209ff0c, WfcSession_StartStatsGet)

/* func_0209ff54: when the state block's record has status WFC_STATS_TO_SEND, its checksum is
 * set so that its halfwords sum to 0 and its signed upload started; whether it had that
 * status.
 * QUIRK: 1 even when the upload could not be started. */
int WfcSession_StartStatsUpload(void)
{
    u8 *record = data_021f3278;
    if (func_02088208(record) != WFC_STATS_TO_SEND) {
        return 0;
    }
    u16 checksum = BackupCard_Checksum((const u16 *) (const void *) record, STATS_SIZE, func_020881ac(record));
    func_020881b8(record, checksum);
    LibraryOverlay_Require65();
    Wfc_PostSigned(data_020e3bf0, record, STATS_SIZE, data_020e3800);
    return 1;
}
CLEAN_AS(func_0209ff54, WfcSession_StartStatsUpload)

/* func_0209ffb0: the session ended (Session_End's result is given back). After a Wi-Fi
 * Connection session, with a current player of the town, what was downloaded is applied, the
 * friends' data kept, and when the friend roster could not be written to the card the
 * gatekeeper says so (message 2 of "sp_npc_gatekeeper", in talk 0). */
int WfcSession_End(void *unused)
{
    (void) unused;
    int wifi = Net_GetMode() == NET_MODE_WFC_HOSTING || Net_GetMode() == NET_MODE_WFC_JOINING;
    int result = Session_End();
    if (!wifi) {
        return result;
    }
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return result;
    }
    int number = PlayerRecord_Number(record);
    if (number < 0 || number >= PLAYER_RECORDS_TOWN) {
        return result;
    }
    WfcSession_ApplyStats();
    WfcSession_ApplyLetter();
    WfcSession_ApplyNotice();
    WfcSession_KeepFriendData();
    if (func_020a1518() != 0) {
        void *talk = func_020682e0(GATEKEEPER_TALK);
        func_02068358(talk);
        func_02068434(talk);
        u8 message = GATEKEEPER_SAVE_FAILED;
        func_0206844c(talk, &message, data_020e3c2c);
    }
    return result;
}
CLEAN_AS(func_0209ffb0, WfcSession_End)

/* func_020a01f8: the first 32 friend data of the session's start table (the table handed to
 * the network library when the session started) copied into the current player's friend
 * roster. */
void WfcSession_KeepFriendData(void)
{
    const u8 *table = Session_GetStartTable(data_020ccf94);
    WifiFriend *entry = WifiFriendList_GetEntries(PlayerRecord_WifiFriends(PlayerRecords_Current()));
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        WifiFriendData *data = WifiFriendData_GetData(WifiFriend_GetFriendData(entry));
        MI_CpuCopy8(table + i * sizeof(WifiFriendData), data, sizeof(WifiFriendData));
        entry++;
    }
}
CLEAN_AS(func_020a01f8, WfcSession_KeepFriendData)
