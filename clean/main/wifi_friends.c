/* The Wi-Fi Connection account and friend roster of a player record (wifi_friends.h). */
#include "wifi_friends.h"

#include "autoload_2/network.h"
#include "clean.h"

static_assert(offsetof(WifiFriend, text_0c) == 0x0c, "text 0c");
static_assert(offsetof(WifiFriend, text_18) == 0x18, "text 18");
static_assert(sizeof(WifiFriend) == 0x24, "friend size");
static_assert(offsetof(WifiFriendList, checksum) == 0x480, "list checksum");
static_assert(sizeof(WifiFriendList) == 0x484, "list size");
static_assert(offsetof(WifiAccount, friend_data) == 0x40, "own friend data");
static_assert(offsetof(WifiAccount, checksum) == 0x4c, "account checksum");
static_assert(sizeof(WifiAccount) == 0x50, "account size");

#define GAME_CODE 0x41444d4b /* "ADMK", the game's code */
#define FRIEND_DATA_KEY 2    /* Wfc_GetFriendDataType: a friend key */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_02051bf8(u16 *dst, int units); /* clears `units` 16-bit units */

/* The friend data's own functions, after this code in the ROM. */
extern int func_02077e38(WifiFriendData *friend_data);  /* whether its type is a friend key */
extern int func_02077e50(WifiFriendData *friend_data);  /* whether it holds a friend (type not 0) */
extern void func_02077e68(WifiFriendData *friend_data); /* clears its 12 bytes */
extern void func_02077ebc(WifiFriendData *friend_data); /* its destructor: does nothing */
extern void func_02077ec0(WifiFriendData *friend_data); /* its constructor: does nothing */

/* WifiFriend_Construct and WifiFriend_Destruct at the game's addresses, declared as the vector
 * helpers take them (their results are not used). */
extern void func_02077c8c(void *entry);
extern void func_02077c7c(void *entry);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* ---- The account ---- */

/* func_02077bb8 */
u16 WifiAccount_GetChecksum(const WifiAccount *account)
{
    return account->checksum;
}
CLEAN_AS(func_02077bb8, WifiAccount_GetChecksum)

/* func_02077bc0 */
void WifiAccount_SetChecksum(WifiAccount *account, u16 checksum)
{
    account->checksum = checksum;
}
CLEAN_AS(func_02077bc0, WifiAccount_SetChecksum)

/* func_02077bc8: this user's own friend data. */
WifiFriendData *WifiAccount_GetFriendData(WifiAccount *account)
{
    return &account->friend_data;
}
CLEAN_AS(func_02077bc8, WifiAccount_GetFriendData)

/* func_02077bcc: the user's data, at the account's start. */
u8 *WifiAccount_GetUserData(WifiAccount *account)
{
    return account->user_data;
}
CLEAN_AS(func_02077bcc, WifiAccount_GetUserData)

/* func_02077bd0 */
int WifiAccount_Call021012c4(void *user_data)
{
    return Wfc_Call021012c4(user_data);
}
CLEAN_AS(func_02077bd0, WifiAccount_Call021012c4)

/* func_02077bd8: whether the user's data has been authenticated. */
int WifiAccount_IsAuthentic(const void *user_data)
{
    return Wfc_IsAuthentic(user_data);
}
CLEAN_AS(func_02077bd8, WifiAccount_IsAuthentic)

/* func_02077be0: the number made from the user's data (Wfc_GetUserKey). */
u64 WifiAccount_GetUserKey(const void *user_data)
{
    return Wfc_GetUserKey(user_data);
}
CLEAN_AS(func_02077be0, WifiAccount_GetUserKey)

/* func_02077be8: a new user's data for the game, and the friend data made from it. */
void WifiAccount_Init(WifiAccount *account)
{
    Wfc_InitUserData(account->user_data, GAME_CODE);
    Wfc_Call0210111c(account->user_data, WifiFriendData_GetData(&account->friend_data));
}
CLEAN_AS(func_02077be8, WifiAccount_Init)

/* func_02077c0c: the destructor. */
WifiAccount *WifiAccount_Destruct(WifiAccount *account)
{
    func_02077ebc(&account->friend_data);
    return account;
}
CLEAN_AS(func_02077c0c, WifiAccount_Destruct)

/* func_02077c20: the constructor. */
WifiAccount *WifiAccount_Construct(WifiAccount *account)
{
    func_02077ec0(&account->friend_data);
    return account;
}
CLEAN_AS(func_02077c20, WifiAccount_Construct)

/* ---- A friend ---- */

/* func_02077c34 */
u16 *WifiFriend_GetText18(WifiFriend *entry)
{
    return entry->text_18;
}
CLEAN_AS(func_02077c34, WifiFriend_GetText18)

/* func_02077c38 */
u16 *WifiFriend_GetText0C(WifiFriend *entry)
{
    return entry->text_0c;
}
CLEAN_AS(func_02077c38, WifiFriend_GetText0C)

/* func_02077c3c: the friend data, at the entry's start. */
WifiFriendData *WifiFriend_GetFriendData(WifiFriend *entry)
{
    return &entry->friend_data;
}
CLEAN_AS(func_02077c3c, WifiFriend_GetFriendData)

/* func_02077c40: empties the entry. */
void WifiFriend_Clear(WifiFriend *entry)
{
    func_02077e68(&entry->friend_data);
    func_02051bf8(entry->text_0c, WIFI_FRIEND_TEXT_LENGTH);
    func_02051bf8(entry->text_18, WIFI_FRIEND_TEXT_LENGTH);
}
CLEAN_AS(func_02077c40, WifiFriend_Clear)

/* func_02077c64: `src` copied into `dst`; returns `dst`. */
WifiFriend *WifiFriend_Copy(WifiFriend *dst, WifiFriend *src)
{
    MI_CpuCopy8(src, dst, sizeof(WifiFriend));
    return dst;
}
CLEAN_AS(func_02077c64, WifiFriend_Copy)

/* func_02077c7c: the destructor. */
WifiFriend *WifiFriend_Destruct(WifiFriend *entry)
{
    func_02077ebc(&entry->friend_data);
    return entry;
}
CLEAN_AS(func_02077c7c, WifiFriend_Destruct)

/* func_02077c8c: the constructor. */
WifiFriend *WifiFriend_Construct(WifiFriend *entry)
{
    func_02077ec0(&entry->friend_data);
    return entry;
}
CLEAN_AS(func_02077c8c, WifiFriend_Construct)

/* ---- The roster ---- */

/* func_02077c9c */
u16 WifiFriendList_GetChecksum(const WifiFriendList *list)
{
    return list->checksum;
}
CLEAN_AS(func_02077c9c, WifiFriendList_GetChecksum)

/* func_02077ca8 */
void WifiFriendList_SetChecksum(WifiFriendList *list, u16 checksum)
{
    list->checksum = checksum;
}
CLEAN_AS(func_02077ca8, WifiFriendList_SetChecksum)

/* func_02077cb4: moves the friends to the front of the roster, in their order, emptying the
 * entries they leave. */
void WifiFriendList_Compact(WifiFriendList *list)
{
    WifiFriend *entries = WifiFriendList_GetEntries(list);
    int kept = 0;

    for (int i = 0; i < WIFI_FRIENDS; i++) {
        WifiFriend *entry = &entries[i];
        if (func_02077e50(WifiFriend_GetFriendData(entry)) == 0) {
            continue;
        }
        if (i != kept) {
            WifiFriend_Copy(&entries[kept], entry);
            WifiFriend_Clear(entry);
        }
        kept++;
    }
}
CLEAN_AS(func_02077cb4, WifiFriendList_Compact)

/* func_02077d00: the entries, at the roster's start. */
WifiFriend *WifiFriendList_GetEntries(WifiFriendList *list)
{
    return list->friends;
}
CLEAN_AS(func_02077d00, WifiFriendList_GetEntries)

/* func_02077d04: empties every entry. */
void WifiFriendList_ClearAll(WifiFriendList *list)
{
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        WifiFriend_Clear(&list->friends[i]);
    }
}
CLEAN_AS(func_02077d04, WifiFriendList_ClearAll)

/* func_02077d24: the destructor: each entry's, through the vector helper. */
WifiFriendList *WifiFriendList_Destruct(WifiFriendList *list)
{
    __cxa_vec_cleanup(list, WIFI_FRIENDS, sizeof(WifiFriend), func_02077c7c);
    return list;
}
CLEAN_AS(func_02077d24, WifiFriendList_Destruct)

/* func_02077d40: the constructor: each entry's, through the vector helper. */
WifiFriendList *WifiFriendList_Construct(WifiFriendList *list)
{
    __cxa_vec_ctor(list, WIFI_FRIENDS, sizeof(WifiFriend), func_02077c8c, func_02077c7c);
    return list;
}
CLEAN_AS(func_02077d40, WifiFriendList_Construct)

/* ---- A friend data ---- */

/* func_02077d68: the data NitroDWC reads: the object itself. */
WifiFriendData *WifiFriendData_GetData(WifiFriendData *friend_data)
{
    return friend_data;
}
CLEAN_AS(func_02077d68, WifiFriendData_GetData)

/* func_02077d6c: 1 unless the friend data is a friend key not yet exchanged. */
int WifiFriendData_IsNotFriendKey(WifiFriendData *friend_data)
{
    return func_02077e38(friend_data) == 0;
}
CLEAN_AS(func_02077d6c, WifiFriendData_IsNotFriendKey)

/* func_02077d84: the friend key of a friend data that is one, as its 12 decimal digits (the
 * values 0-9, most significant first) in `digits`; 1, or 0 with nothing written when the
 * friend data is no friend key. */
int WifiFriendData_GetKeyDigits(WifiFriendData *friend_data, char *digits)
{
    if (Wfc_GetFriendDataType(friend_data) != FRIEND_DATA_KEY) {
        return 0;
    }
    u64 key = (u64) Wfc_GetFriendKey(friend_data);
    for (int i = WIFI_FRIEND_KEY_DIGITS - 1; i >= 0; i--) {
        digits[i] = (char) (key % 10);
        key /= 10;
    }
    return 1;
}
CLEAN_AS(func_02077d84, WifiFriendData_GetKeyDigits)
