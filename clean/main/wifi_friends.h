/* The Nintendo Wi-Fi Connection data a player record keeps (autoload_2/network.h):
 *
 *   the account (WifiAccount, 0x50 bytes at 0x1f0c of the player record, func_02099664): the
 *   user's data (NitroDWC's DWCUserData, 0x40 bytes) made for the game 'ADMK', the friend data
 *   others register this user with, and a checksum of the block (func_020508fc);
 *   the friend roster (WifiFriendList, 0x484 bytes at 0x1f5c, func_02099658): 32 friends
 *   (WifiFriend, 0x24 bytes: a friend data and two 6-character texts) and a checksum.
 *
 * A friend data (WifiFriendData, 12 bytes) is NitroDWC's DWCFriendData: its type (2 for a
 * friend key not yet exchanged, 0 for none, Wfc_GetFriendDataType) and its key or profile.
 * The roster is a C++ array of WifiFriend objects; its constructor and destructor hand the
 * game's own WifiFriend_Construct and WifiFriend_Destruct to the vector helpers. */
#ifndef CLEAN_MAIN_WIFI_FRIENDS_H
#define CLEAN_MAIN_WIFI_FRIENDS_H

#include "types.h"

#define WIFI_FRIENDS 32
#define WIFI_FRIEND_TEXT_LENGTH 6 /* the 16-bit characters of a friend's texts */
#define WIFI_FRIEND_KEY_DIGITS 12 /* the decimal digits a friend key is shown with */

typedef struct WifiFriendData {
    u8 data[12];
} WifiFriendData;

typedef struct WifiFriend {
    WifiFriendData friend_data;           /* 0x00 */
    u16 text_0c[WIFI_FRIEND_TEXT_LENGTH]; /* 0x0c */
    u16 text_18[WIFI_FRIEND_TEXT_LENGTH]; /* 0x18 */
} WifiFriend;

typedef struct WifiFriendList {
    WifiFriend friends[WIFI_FRIENDS]; /* 0x000 */
    u16 checksum;                     /* 0x480 */
    u8 unk_482[2];
} WifiFriendList;

typedef struct WifiAccount {
    u8 user_data[0x40];         /* 0x00: DWCUserData */
    WifiFriendData friend_data; /* 0x40: this user's own friend data */
    u16 checksum;               /* 0x4c */
    u8 unk_4e[2];
} WifiAccount;

u16 WifiAccount_GetChecksum(const WifiAccount *account);
void WifiAccount_SetChecksum(WifiAccount *account, u16 checksum);
WifiFriendData *WifiAccount_GetFriendData(WifiAccount *account);
u8 *WifiAccount_GetUserData(WifiAccount *account);
int WifiAccount_Call021012c4(void *user_data);
int WifiAccount_IsAuthentic(const void *user_data);
u64 WifiAccount_GetUserKey(const void *user_data);
void WifiAccount_Init(WifiAccount *account);
WifiAccount *WifiAccount_Destruct(WifiAccount *account);
WifiAccount *WifiAccount_Construct(WifiAccount *account);

u16 *WifiFriend_GetText18(WifiFriend *entry);
u16 *WifiFriend_GetText0C(WifiFriend *entry);
WifiFriendData *WifiFriend_GetFriendData(WifiFriend *entry);
void WifiFriend_Clear(WifiFriend *entry);
WifiFriend *WifiFriend_Copy(WifiFriend *dst, WifiFriend *src);
WifiFriend *WifiFriend_Destruct(WifiFriend *entry);
WifiFriend *WifiFriend_Construct(WifiFriend *entry);

u16 WifiFriendList_GetChecksum(const WifiFriendList *list);
void WifiFriendList_SetChecksum(WifiFriendList *list, u16 checksum);
void WifiFriendList_Compact(WifiFriendList *list);
WifiFriend *WifiFriendList_GetEntries(WifiFriendList *list);
void WifiFriendList_ClearAll(WifiFriendList *list);
WifiFriendList *WifiFriendList_Destruct(WifiFriendList *list);
WifiFriendList *WifiFriendList_Construct(WifiFriendList *list);

WifiFriendData *WifiFriendData_GetData(WifiFriendData *friend_data);
int WifiFriendData_IsNotFriendKey(WifiFriendData *friend_data);
int WifiFriendData_GetKeyDigits(WifiFriendData *friend_data, char *digits);
int WifiFriendData_SetFromKeyDigits(WifiFriendData *friend_data, const u8 *digits, const void *user_data);
int WifiFriendData_IsFriendKey(WifiFriendData *friend_data);
int WifiFriendData_IsSet(WifiFriendData *friend_data);
void WifiFriendData_Clear(WifiFriendData *friend_data);
u32 WifiFriendData_Matches(const void *friend_data, WifiFriendData *other);
WifiFriendData *WifiFriendData_Copy(WifiFriendData *dst, const WifiFriendData *src);
void WifiFriendData_Destruct(WifiFriendData *friend_data);
void WifiFriendData_Construct(WifiFriendData *friend_data);

#endif
