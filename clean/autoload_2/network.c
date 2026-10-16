/* The game's layer over the wireless libraries (network.h). */
#include "network.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(sizeof(FriendStatus) == 0x23, "a friend's status");
static_assert(offsetof(FriendList, status) == 0x180, "the statuses follow the friend data");
static_assert(offsetof(FriendList, status[0].status) == 0x1a0, "the status byte the game clears");

/* The library in use: */
enum NetworkMode {
    MODE_NONE = 0,         /* nothing started yet (Net_Init) */
    MODE_LOCAL_PARENT = 1, /* the local wireless library, as the parent (its AID is 0) */
    MODE_LOCAL_CHILD = 2,  /* the local wireless library, as a child looking for parents */
    MODE_HOSTING = 3,      /* hosting a game friends join (Wfc_HostGame) */
    MODE_JOINING = 4,      /* joining a friend's game (Wfc_JoinFriendGame) */
    MODE_EXCHANGE = 5,     /* the wireless exchange (Exchange_Init) */
    MODE_ENDED = 6,        /* shut down (Net_End) */
};
extern u8 data_021fbef8;

/* The Wi-Fi Connection's stage (func_020ec980): from STAGE_LOGGED_IN the server requests and the
 * friend list can be used, and from STAGE_READY the list can be changed. */
enum WfcStage {
    STAGE_START = 0,
    STAGE_CONNECTING = 1, /* connecting to the Internet */
    STAGE_CONNECTED = 2,  /* connected; the login comes next */
    STAGE_LOGGING_IN = 3, /* logging in and updating the friend list */
    STAGE_LOGGED_IN = 4,
    STAGE_READY = 5,
};
extern u16 data_021fbefc;

/* The number of players a hosted game takes. */
extern u8 data_021fbef4;
/* The game's id, given to the exchange (func_020ece54 sets it). */
extern u32 data_021fbf20;
/* The time in milliseconds a client last joined the game being hosted (func_020ed5f8); 0 when
 * none did since the clients were last let in again (Wfc_UpdateConnectBlock). */
extern u32 data_021fbf34;

/* The exchange: its work memory, whether the library ended (func_020ed17c) and whether the data
 * was exchanged (func_020ed168). */
extern void *data_021fbf28;
extern int data_021fbf48;
extern u32 data_021fbf50;

/* The friend list, and the user's data (NitroDWC's DWCUserData; the user's key is at +0x20). */
extern FriendList *data_021fbf3c;
extern u8 *data_021fbf40;
/* TRUE while NitroDWC updates the friend list (cleared by func_020ed540). */
extern int data_0213e6c4;

/* A GET request: TRUE while none is under way (cleared by the request, set by its callback),
 * the size of the reply to copy, and for Wfc_GetSigned its URL, the hash text, the URL it was
 * given and the region it sends. */
extern int data_0213e6c0;
extern int data_021fbf14;
extern char *data_021fbf44;
extern char *data_021fbf0c;
extern const char *data_021fbf4c;
extern const char *data_021fbf10;
/* A POST request: TRUE while none is under way, its body (the key, then the data in Base64)
 * and the hash text. */
extern int data_0213e6bc;
extern char *data_021fbf1c;
extern char *data_021fbf2c;

/* The key the requests are signed with, and the formats and names they use. */
extern const char data_0213e708[]; /* the key, 20 characters */
extern const char data_0213e6f0[]; /* "%s?pid=%llu&region=%s" */
extern const char data_0213e720[]; /* "%llu" */
extern const char data_0213e728[]; /* "pid" */
extern const char data_0213e72c[]; /* "hash" */
extern const char data_0213e734[]; /* "data" */
extern const char data_0213e73c[]; /* "region" */
#define SIGNING_KEY_LENGTH 0x14
/* The hash text: 40 hexadecimal digits and a NUL, the SHA-1 digest first computed into its
 * second half. */
#define HASH_TEXT_SIZE 0x29
#define SHA1_DIGEST_SIZE 0x14
#define URL_SIZE 0x100

/* The local wireless library's entries (Local_ListEntries) and the copy Local_SelectEntry
 * hands it. */
#define LOCAL_ENTRY_COUNT 8
#define LOCAL_ENTRY_SIZE 0xe0
#define LOCAL_STATE_READY 7
extern void *data_021fbf78[LOCAL_ENTRY_COUNT];
extern u8 data_021fc040[LOCAL_ENTRY_SIZE];

/* Net_Alloc and Net_Free by the game's symbols, handed to the local library. UTi_PutString's
 * name is NitroSDK's but does not fit: it calls the free function. */
extern void *func_020edaf0(int size, int align);
extern void UTi_PutString(void *block);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern int STD_GetStringLength(const char *s);
extern char *STD_CopyString(char *dst, const char *src);
extern void MATH_CalcSHA1(void *digest, const void *data, u32 length);
extern int OS_SNPrintf(char *buffer, u32 size, const char *format, ...);

/* NitroSDK's WXC. */
extern int WXC_GetStateCode(void);
extern void WXC_Start(void);
extern int WXC_SetParentParameter(int a, int b, int c);
/* By their arguments WXC_Init (work memory, callback, priority) and WXC_RegisterCommonData
 * (game id, callback, data sent and its size, buffer received into and its size). */
extern void func_ov067_02268990(void *work, void (*callback)(int state, void *argument), int priority);
extern int func_ov067_02268688(u32 game_id, void (*callback)(void), u8 *send, int send_size, u8 *receive, int receive_size);
extern void func_ov067_0226883c(void);
extern void func_020ed17c(int state, void *argument);
extern void func_020ed168(void);

/* NitroDWC. */
extern int DWC_CanChangeFriendList(void);
extern int DWC_IsBuddyFriendData(const void *friend_data);
extern int DWC_GetFriendDataType(const void *friend_data);
extern int DWC_CheckFriendKey(const void *user_data, int key_low, int key_high);
extern int DWC_GetGsProfileId(const void *user_data, const void *friend_data);
extern int DWCi_Acc_IsAuthentic(const void *user_data);
extern int DWCi_Acc_IsDirty(void *user_data);
extern int DWCi_GetProfileIDFromList(int index);
extern int DWCi_GetFriendListIndex(int profile_id);
/* A GET's callback: the reply and its length, the result (0: success) and the argument. */
typedef void GetCallback(const void *reply, int length, int result, void *argument);
extern int DWC_GetGHTTPData(const char *url, GetCallback *callback, void *argument);
extern int DWC_PostGHTTPData(const char *url, void *post, void (*callback)(void), void *argument);
extern int func_0210101c(const void *a, const void *b);
extern int func_021012c4(void *data);
extern s64 func_02101210(const void *friend_data);
/* The friend data for a friend key (it is checked first). */
extern void func_02101164(void *friend_data, int key_low, int key_high);
extern u64 func_0210118c(const void *user_data);
extern void func_0210111c(void *user_data, void *value);
/* Called after the user data is made, and when it was found changed (Wfc_TakeDirty). */
extern void func_02101234(void *user_data);
extern void func_0210131c(void *user_data, u32 game_code);
/* By its use DWC_DeleteBuddyFriendData. */
extern void func_ov065_022797a4(void *friend_data);
/* By its arguments DWC_UpdateServersAsync (player name, then three callbacks with their
 * arguments: the update finished, a friend's status changed, a friend was deleted). */
extern int func_ov065_02277edc(const char *name, void (*updated)(void *, int, void *), void *updated_argument,
                               void (*status)(int, int, void *, void *), void *status_argument,
                               void (*deleted)(int, int, void *), void *deleted_argument);
extern void func_020ed540(void *result, int changed, void *argument);
extern void func_020ed4cc(int index, int status, void *profile, void *argument);
extern void func_020ed440(int index, int reason, void *argument);
/* By its arguments, Base64: `length` bytes of `src` into at most `capacity` characters of
 * `dst`; the characters written. */
extern int func_ov065_02277148(const void *src, u32 length, char *dst, int capacity);
/* A POST's form: made empty, then each field added. */
extern int func_ov065_0227f6b0(void *post);
extern int func_ov065_0227f6a4(void *post, const char *name, const char *value);
extern GetCallback func_020ed194;
extern GetCallback func_020ed320;
extern void func_020ed3c0(void);
/* Joining and hosting: by their arguments DWC_ConnectToGameServerAsync (the friend's index)
 * and DWC_SetupGameServer (the number of players), each with a callback for the connection
 * and one for a new client; then the callbacks for data sent and received, and for a
 * connection closed. */
extern void func_ov065_02277d50(int index, void (*connected)(u32, int, int, int, int, void *), void *connected_argument,
                                void (*new_client)(void), void *new_client_argument);
extern void func_ov065_02277e7c(u8 max_entry, void (*connected)(int, int), void *connected_argument, void (*new_client)(void),
                                void *new_client_argument);
extern void *func_ov065_0227ed18(void (*sent)(int, int));
extern void *func_ov065_0227ed04(void (*received)(int, int, int));
extern void func_ov065_02277d38(void (*closed)(int, int, int, int, int, void *), void *argument);
extern void func_020ed6ac(u32 result, int local, int is_server, int cancelled, int peer, void *argument);
extern void func_020ed5f8(int result, int argument);
extern void func_020ed5f4(void);
extern void func_020ed68c(int size, int peer);
extern void func_020ed658(int peer, int buffer, int size);
extern void func_020ed6a8(int status, int local, int cancelled, int peer, int connection, void *argument);
extern void func_ov065_0227e67c(void);
extern void func_ov065_022784a0(void);

/* The local wireless library. */
extern int func_ov066_0226760c(void);
extern int func_ov066_022682ec(void *entry, int a, int b);
extern void *func_ov066_02267784(int a, u8 index);
extern int func_ov066_02266c7c(void *entry);
extern int func_ov066_02266cc8(void *entry);
extern void *func_ov066_02266c8c(void *entry);
extern int func_ov066_02269638(const void *data, u32 length);

/* func_020ead48: TRUE once the data was exchanged. */
u32 Exchange_IsDone(void)
{
    return data_021fbf50;
}
CLEAN_AS(func_020ead48, Exchange_IsDone)

/* func_020ead58: TRUE while the exchange library is running (its state 2). */
int Exchange_IsActive(void)
{
    return WXC_GetStateCode() == 2;
}
CLEAN_AS(func_020ead58, Exchange_IsActive)

/* func_020ead7c: overlay 67's func_ov067_0226883c; its callers use it when the exchange is not
 * done and not running. */
void Exchange_Call0226883c(void)
{
    func_ov067_0226883c();
}
CLEAN_AS(func_020ead7c, Exchange_Call0226883c)

/* func_020ead88 */
void Exchange_Start(void)
{
    WXC_Start();
}
CLEAN_AS(func_020ead88, Exchange_Start)

/* func_020ead94: the exchange set up to send `size` bytes of `send` and receive as many into
 * `receive`. Its work memory (0xa000 bytes) comes from the game's allocator. */
void Exchange_Init(u8 *send, u8 *receive, int size)
{
    data_021fbef8 = MODE_EXCHANGE;
    data_021fbf48 = 0;
    data_021fbf50 = 0;
    data_021fbf28 = Net_Alloc(0xa000, 0x20);
    func_ov067_02268990(data_021fbf28, func_020ed17c, 2);
    WXC_SetParentParameter(0x3c, 0x3c, 1);
    func_ov067_02268688(data_021fbf20, func_020ed168, send, size, receive, size);
}
CLEAN_AS(func_020ead94, Exchange_Init)

/* func_020eae40: when hosting, the host's set-up time cleared and func_ov065_0227e67c called.
 * Always TRUE. The ROM's code leaves &data_021fbf34 in the first argument register; the
 * callee does not read it. */
int Wfc_ClearHostTime(void)
{
    if (data_021fbef8 == MODE_HOSTING) {
        data_021fbf34 = 0;
        func_ov065_0227e67c();
    }
    return TRUE;
}
CLEAN_AS(func_020eae40, Wfc_ClearHostTime)

/* Whether the friend list can be changed now: NitroDWC allows it, the connection is ready and
 * no update is under way. */
static BOOL can_change_friends(void)
{
    return DWC_CanChangeFriendList() && data_021fbefc >= STAGE_READY && !data_0213e6c4;
}

/* The status of friend `index` cleared.
 * QUIRK: the status byte is cleared again after the whole entry. */
static void clear_friend_status(int index)
{
    MI_CpuFill8(&data_021fbf3c->status[index], 0, sizeof(FriendStatus));
    data_021fbf3c->status[index].status = 0;
}

/* func_020eae80: friend `index` deleted from NitroDWC's list and from the game's; FALSE when the
 * list cannot be changed now. */
int Wfc_DeleteFriend(int index)
{
    if (!can_change_friends()) {
        return FALSE;
    }
    func_ov065_022797a4(data_021fbf3c->friend_data[index]);
    MI_CpuFill8(data_021fbf3c->friend_data[index], 0, FRIEND_DATA_SIZE);
    clear_friend_status(index);
    return TRUE;
}
CLEAN_AS(func_020eae80, Wfc_DeleteFriend)

/* func_020eaf48: friend `index` set to `friend_data`, its status cleared, and NitroDWC asked
 * to update its list; what that request returns (FALSE also when the list cannot be changed
 * now). The update is under way until its callback (func_020ed540) or a failed request. */
int Wfc_SetFriend(int index, const void *friend_data)
{
    if (!can_change_friends()) {
        return FALSE;
    }
    MI_CpuCopy8(friend_data, data_021fbf3c->friend_data[index], FRIEND_DATA_SIZE);
    clear_friend_status(index);
    data_0213e6c4 = TRUE;
    int started = func_ov065_02277edc(NULL, func_020ed540, NULL, func_020ed4cc, NULL, func_020ed440, NULL);
    if (!started) {
        data_0213e6c4 = FALSE;
    }
    return started;
}
CLEAN_AS(func_020eaf48, Wfc_SetFriend)

/* func_020eb040 */
int Wfc_IsBuddyFriendData(const void *friend_data)
{
    return DWC_IsBuddyFriendData(friend_data);
}
CLEAN_AS(func_020eb040, Wfc_IsBuddyFriendData)

/* func_020eb04c: 2 for a friend key (Wfc_GetFriendKey). */
int Wfc_GetFriendDataType(const void *friend_data)
{
    return DWC_GetFriendDataType(friend_data);
}
CLEAN_AS(func_020eb04c, Wfc_GetFriendDataType)

/* func_020eb058 */
int Wfc_Call0210101c(const void *a, const void *b)
{
    return func_0210101c(a, b);
}
CLEAN_AS(func_020eb058, Wfc_Call0210101c)

/* func_020eb064 */
int Wfc_Call021012c4(void *data)
{
    return func_021012c4(data);
}
CLEAN_AS(func_020eb064, Wfc_Call021012c4)

/* func_020eb070: the buffers of the last signed GET freed; FALSE while the connection is not
 * logged in or a GET is under way. */
int Wfc_FinishGet(void)
{
    if (data_021fbefc < STAGE_LOGGED_IN || !data_0213e6c0) {
        return FALSE;
    }
    if (data_021fbf44 != NULL) {
        Net_Free(data_021fbf44);
        Net_Free(data_021fbf0c);
        data_021fbf44 = NULL;
        data_021fbf0c = NULL;
    }
    return TRUE;
}
CLEAN_AS(func_020eb070, Wfc_FinishGet)

/* func_020eb108: a GET of `url` started, its reply's first `size` bytes to be copied to
 * `buffer` (func_020ed320); FALSE while the connection is not logged in or a GET is under way. */
int Wfc_Get(const char *url, void *buffer, int size)
{
    if (data_021fbefc < STAGE_LOGGED_IN || !data_0213e6c0) {
        return FALSE;
    }
    data_021fbf14 = size;
    data_0213e6c0 = FALSE;
    DWC_GetGHTTPData(url, func_020ed320, buffer);
    return TRUE;
}
CLEAN_AS(func_020eb108, Wfc_Get)

/* func_020eb188: a signed GET of `url` started: first "url?pid=key&region=region"; its reply
 * is hashed with the signing key and asked for again with the hash (func_020ed194), and that
 * reply goes to `buffer` (`size` bytes). The URL and the hash text are allocated here and freed
 * by Wfc_FinishGet. FALSE when the connection is not logged in, a GET is under way or the
 * memory is short. */
int Wfc_GetSigned(const char *url, void *buffer, int size, const char *region)
{
    if (data_021fbefc < STAGE_LOGGED_IN || !data_0213e6c0) {
        return FALSE;
    }
    data_021fbf44 = Net_Alloc(URL_SIZE, 4);
    if (data_021fbf44 == NULL) {
        return FALSE;
    }
    data_021fbf0c = Net_Alloc(HASH_TEXT_SIZE, 4);
    if (data_021fbf0c == NULL) {
        Net_Free(data_021fbf44);
        data_021fbf44 = NULL;
        return FALSE;
    }
    data_0213e6c0 = FALSE;
    data_021fbf4c = url;
    data_021fbf14 = size;
    data_021fbf10 = region;
    u64 key = Wfc_GetUserKey(data_021fbf40 + 0x20);
    OS_SNPrintf(data_021fbf44, URL_SIZE, data_0213e6f0, data_021fbf4c, key, region);
    DWC_GetGHTTPData(data_021fbf44, func_020ed194, buffer);
    return TRUE;
}
CLEAN_AS(func_020eb188, Wfc_GetSigned)

/* func_020eb2ec: the buffers of the last signed POST freed; FALSE while the connection is not
 * logged in or a POST is under way. */
int Wfc_FinishPost(void)
{
    if (data_021fbefc < STAGE_LOGGED_IN || !data_0213e6bc) {
        return FALSE;
    }
    if (data_021fbf1c != NULL) {
        Net_Free(data_021fbf1c);
        Net_Free(data_021fbf2c);
        data_021fbf1c = NULL;
        data_021fbf2c = NULL;
    }
    return TRUE;
}
CLEAN_AS(func_020eb2ec, Wfc_FinishPost)

/* The SHA-1 digest at `text` + SHA1_DIGEST_SIZE written over `text` as 40 lower-case
 * hexadecimal digits and a NUL. Each byte is read before the digits that overwrite it. */
static void digest_to_hex(char *text)
{
    static const char digits[] = "0123456789abcdef";
    const u8 *digest = (const u8 *) text + SHA1_DIGEST_SIZE;
    for (int i = 0; i < SHA1_DIGEST_SIZE; i++) {
        u8 byte = digest[i];
        text[2 * i] = digits[byte >> 4];
        text[2 * i + 1] = digits[byte & 0xf];
    }
    text[2 * SHA1_DIGEST_SIZE] = '\0';
}

/* func_020eb384: a signed POST of `length` bytes of `data` to `url` started. The data is sent
 * in Base64, with the user's key, the region and the SHA-1 of the signing key followed by the
 * Base64 text. The body and the hash text are allocated here and freed by Wfc_FinishPost.
 * FALSE when the connection is not logged in, a POST is under way or the memory is short.
 * QUIRK: the Base64 text is sent from a fixed 20 characters into the body, the signing key's
 * length. */
int Wfc_PostSigned(const char *url, const void *data, u32 length, const char *region)
{
    if (data_021fbefc < STAGE_LOGGED_IN || !data_0213e6bc) {
        return FALSE;
    }
    u32 capacity = (length + 2) / 3 * 4 + 1;
    int key_length = STD_GetStringLength(data_0213e708);
    data_021fbf1c = Net_Alloc((int) (key_length + capacity), 4);
    if (data_021fbf1c == NULL) {
        return FALSE;
    }
    data_021fbf2c = Net_Alloc(HASH_TEXT_SIZE, 4);
    if (data_021fbf2c == NULL) {
        Net_Free(data_021fbf1c);
        data_021fbf1c = NULL;
        return FALSE;
    }
    STD_CopyString(data_021fbf1c, data_0213e708);
    int encoded = func_ov065_02277148(data, length, data_021fbf1c + key_length, (int) capacity);
    MATH_CalcSHA1(data_021fbf2c + SHA1_DIGEST_SIZE, data_021fbf1c, (u32) (key_length + encoded));
    digest_to_hex(data_021fbf2c);
    data_0213e6bc = FALSE;

    char key_text[16];
    void *post;
    MI_CpuFill8(key_text, 0, sizeof(key_text));
    OS_SNPrintf(key_text, sizeof(key_text), data_0213e720, Wfc_GetUserKey(data_021fbf40 + 0x20));
    func_ov065_0227f6b0(&post);
    func_ov065_0227f6a4(&post, data_0213e728, key_text);
    func_ov065_0227f6a4(&post, data_0213e72c, data_021fbf2c);
    func_ov065_0227f6a4(&post, data_0213e734, data_021fbf1c + SIGNING_KEY_LENGTH);
    func_ov065_0227f6a4(&post, data_0213e73c, region);
    DWC_PostGHTTPData(url, &post, func_020ed3c0, NULL);
    return TRUE;
}
CLEAN_AS(func_020eb384, Wfc_PostSigned)

/* func_020eb61c: the friend key a friend data holds (one of type 2); the game shows it as 12
 * decimal digits (func_02077d84). */
s64 Wfc_GetFriendKey(const void *friend_data)
{
    return func_02101210(friend_data);
}
CLEAN_AS(func_020eb61c, Wfc_GetFriendKey)

/* func_020eb628: `friend_data` made from the friend key `key_high`:`key_low` the user typed;
 * TRUE when the key is valid for `user_data` and gives a profile. */
int Wfc_FriendDataFromKey(const void *user_data, void *friend_data, int key_low, int key_high)
{
    if (!DWC_CheckFriendKey(user_data, key_low, key_high)) {
        return FALSE;
    }
    func_02101164(friend_data, key_low, key_high);
    return DWC_GetGsProfileId(user_data, friend_data) > 0;
}
CLEAN_AS(func_020eb628, Wfc_FriendDataFromKey)

/* func_020eb694: the 64-bit number made from the user's data that the requests send as their
 * pid. */
u64 Wfc_GetUserKey(const void *user_data)
{
    return func_0210118c(user_data);
}
CLEAN_AS(func_020eb694, Wfc_GetUserKey)

/* func_020eb6a0 */
void Wfc_Call0210111c(void *user_data, void *value)
{
    func_0210111c(user_data, value);
}
CLEAN_AS(func_020eb6a0, Wfc_Call0210111c)

/* func_020eb6ac */
int Wfc_IsAuthentic(const void *user_data)
{
    return DWCi_Acc_IsAuthentic(user_data);
}
CLEAN_AS(func_020eb6ac, Wfc_IsAuthentic)

/* func_020eb6b8: TRUE when the user's data changed; func_02101234 is then called on it. */
int Wfc_TakeDirty(void *user_data)
{
    if (!DWCi_Acc_IsDirty(user_data)) {
        return FALSE;
    }
    func_02101234(user_data);
    return TRUE;
}
CLEAN_AS(func_020eb6b8, Wfc_TakeDirty)

/* func_020eb6e8: the user's data made for the game `game_code` (the game passes 'ADMK'). */
void Wfc_InitUserData(void *user_data, u32 game_code)
{
    func_0210131c(user_data, game_code);
    func_02101234(user_data);
}
CLEAN_AS(func_020eb6e8, Wfc_InitUserData)

/* The callbacks for the data of a game being hosted or joined. */
static void set_game_callbacks(void)
{
    func_ov065_0227ed18(func_020ed68c);
    func_ov065_0227ed04(func_020ed658);
    func_ov065_02277d38(func_020ed6a8, NULL);
}

/* func_020eb704: joining the game of the friend with `profile_id` started. FALSE when the
 * connection is not exactly at STAGE_LOGGED_IN or the friend is not in the list.
 * QUIRK: the mode is set to joining before the friend is looked up, and stays when it is not
 * found. */
int Wfc_JoinFriendGame(int profile_id)
{
    if (data_021fbefc != STAGE_LOGGED_IN) {
        return FALSE;
    }
    data_021fbef8 = MODE_JOINING;
    int index = Wfc_FriendIndexOf(profile_id);
    if (index == -1) {
        return FALSE;
    }
    func_ov065_02277d50(index, func_020ed6ac, NULL, func_020ed5f4, NULL);
    set_game_callbacks();
    return TRUE;
}
CLEAN_AS(func_020eb704, Wfc_JoinFriendGame)

/* func_020eb7ac: hosting a game for data_021fbef4 players started; FALSE while the connection
 * is not logged in. */
int Wfc_HostGame(void)
{
    if (data_021fbefc < STAGE_LOGGED_IN) {
        return FALSE;
    }
    data_021fbef8 = MODE_HOSTING;
    func_ov065_02277e7c(data_021fbef4, func_020ed5f8, NULL, func_020ed5f4, NULL);
    set_game_callbacks();
    return TRUE;
}
CLEAN_AS(func_020eb7ac, Wfc_HostGame)

/* func_020eb844: the friend list; NULL while the connection is not logged in. */
FriendList *Wfc_GetFriendList(void)
{
    if (data_021fbefc < STAGE_LOGGED_IN) {
        return NULL;
    }
    return data_021fbf3c;
}
CLEAN_AS(func_020eb844, Wfc_GetFriendList)

/* func_020eb868: the profile id of friend `index`; -1 while the connection is not logged in. */
int Wfc_ProfileIdAt(int index)
{
    if (data_021fbefc < STAGE_LOGGED_IN) {
        return -1;
    }
    return DWCi_GetProfileIDFromList(index);
}
CLEAN_AS(func_020eb868, Wfc_ProfileIdAt)

/* func_020eb8a0: the index in the friend list of `profile_id`; -1 when it is not there or the
 * connection is not logged in. */
int Wfc_FriendIndexOf(int profile_id)
{
    if (data_021fbefc < STAGE_LOGGED_IN) {
        return -1;
    }
    return DWCi_GetFriendListIndex(profile_id);
}
CLEAN_AS(func_020eb8a0, Wfc_FriendIndexOf)

/* func_020eb8d8: `entry` (one of Local_ListEntries') copied and handed to the local wireless
 * library; its result, or FALSE when the library is not ready or there is no entry. */
int Local_SelectEntry(const void *entry)
{
    if (func_ov066_0226760c() != LOCAL_STATE_READY || entry == NULL) {
        return FALSE;
    }
    MI_CpuCopy8(entry, data_021fc040, LOCAL_ENTRY_SIZE);
    return func_ov066_022682ec(data_021fc040, 0, 0);
}
CLEAN_AS(func_020eb8d8, Local_SelectEntry)

/* func_020eb92c: the local wireless library's valid entries, up to 8, in the order of its
 * slots and the rest NULL (all NULL when it is not ready). The callers find each entry's
 * address at its bytes 2 to 7. */
void **Local_ListEntries(void)
{
    MI_CpuFill8(data_021fbf78, 0, sizeof(data_021fbf78));
    if (func_ov066_0226760c() == LOCAL_STATE_READY) {
        int count = 0;
        for (u32 slot = 0; slot < LOCAL_ENTRY_COUNT; slot++) {
            void *entry = func_ov066_02267784(0, (u8) slot);
            if (func_ov066_02266c7c(entry)) {
                data_021fbf78[count++] = entry;
            }
        }
    }
    return data_021fbf78;
}
CLEAN_AS(func_020eb92c, Local_ListEntries)

/* func_020eb998: the size of the data an entry carries; 0 for no entry. */
int Local_EntryDataSize(void *entry)
{
    if (entry == NULL) {
        return 0;
    }
    return func_ov066_02266cc8(entry);
}
CLEAN_AS(func_020eb998, Local_EntryDataSize)

/* func_020eb9c4: the data an entry carries; NULL for no entry. */
void *Local_EntryData(void *entry)
{
    if (entry == NULL) {
        return NULL;
    }
    return func_ov066_02266c8c(entry);
}
CLEAN_AS(func_020eb9c4, Local_EntryData)

/* func_020eb9f0: `length` bytes of `data` handed to the local wireless library. */
int Local_Call02269638(const void *data, u32 length)
{
    return func_ov066_02269638(data, length);
}
CLEAN_AS(func_020eb9f0, Local_Call02269638)

/* func_020eb9fc */
void Wfc_Call022784a0(void)
{
    func_ov065_022784a0();
}
CLEAN_AS(func_020eb9fc, Wfc_Call022784a0)

/* ---- Shared state of the connection ---- */

/* Each peer's ping (data_021fbff8, by AID): the latency NitroDWC last measured (0xffff for an
 * AID with nobody) and the pings sent since anything was last heard from it. Past
 * MAX_UNANSWERED the connection counts as lost (Wfc_GetError). */
typedef struct PeerPing {
    u16 latency;
    u8 unanswered;
    u8 pad;
} PeerPing;
static_assert(sizeof(PeerPing) == 4, "a peer's ping");
#define PEER_COUNT 16
#define MAX_UNANSWERED 30
#define PING_INTERVAL_MS 250
extern PeerPing data_021fbff8[PEER_COUNT];
/* The AID pinged last (Wfc_PingNext). */
extern u8 data_0213e6b0;

/* The send queue: up to 16 blocks waiting to be sent, each a slot of data_021fc120 whose index
 * is a message of the queue data_021fbf98 (data_021fbfb8 holds its messages). A slot is free
 * while its buffer is NULL. `to` is a mask of AIDs for the local library and one AID for
 * NitroDWC; `sent` is called once the block was sent (func_020ed950). */
typedef struct SendSlot {
    const void *buffer;
    u32 size;
    u16 to;
    u16 pad;
    SentCallback *sent;
} SendSlot;
static_assert(sizeof(SendSlot) == 0x10, "a send slot");
#define SEND_SLOT_COUNT 16
extern SendSlot data_021fc120[SEND_SLOT_COUNT];
struct OSMessageQueue;
extern struct OSMessageQueue data_021fbf98;
extern u32 data_021fbfb8[SEND_SLOT_COUNT];
/* When a block was first found still waiting in the queue (milliseconds), 0 when none is. */
extern u32 data_021fbf18;

/* What the game is handed data received from a peer with (Net_DispatchReceived). The name is
 * NitroSDK's but does not fit the use. */
extern ReceiveHandler *CTRDGi_WriteAgbFlashSectorAsync;
/* What the game is told a friend was deleted with (func_020ed440), or NULL. */
extern void (*data_021fbf30)(int index);

/* Set up by Net_Init: the game code ('ADMK'), the value handed first to the local library,
 * how long a wait may take before it is given up (milliseconds), and the allocator and the
 * free function the libraries use (func_020edaf0, UTi_PutString). OS_PutString's name is
 * NitroSDK's but does not fit: it holds the free function. */
extern int data_021fbf04;
extern u8 data_0213e6b4;
extern u32 data_0213e6b8;
extern void *(*data_021fbf08)(int size, int align);
extern void (*OS_PutString)(void *block);

/* The local library's peers (Local_OnEvent): TRUE for each AID connected. The first byte is
 * also set to LOCAL_ENDED when the library reports its end. */
#define LOCAL_ENDED 0xff
extern u8 data_021fbf68[PEER_COUNT];

/* The detail of the last error (Net_GetErrorDetail): NitroDWC's error code, or
 * LOST_PEER_DETAIL when a peer stopped answering. */
#define LOST_PEER_DETAIL 1000000
extern int data_021fbf24;

/* The shutdown of the Wi-Fi Connection: its step (Wfc_EndStep) and when the step began. */
enum WfcEndStep {
    END_START,
    END_WAIT_IDLE,     /* until no request is under way, then close the connections */
    END_WAIT_CLOSED,   /* until the peers are gone */
    END_STEP_3,        /* func_ov065_0227f710 */
    END_STEP_4,        /* func_ov065_022781e4 */
    END_WAIT_LIBRARY,  /* until func_ov065_0227f22c says it is done */
    END_FREE_REQUESTS, /* the buffers of the requests freed */
    END_DONE,
};
extern u16 data_021fbf00;
extern u32 data_021fbf54;

/* NitroDWC's work memory and control (opaque here), the game name ("acrossingds") and the
 * secret key it logs in with. */
extern u8 data_021fbf5c[];
extern u8 data_021fc220[];
extern const char data_0213e744[];
extern const char data_0213e750[];
/* The format of the signed GET's second URL: "%s?pid=%llu&hash=%s&region=%s". */
extern const char data_0213e758[];

extern u64 OS_GetTick(void);
extern void OS_InitMessageQueue(struct OSMessageQueue *queue, u32 *messages, int count);
extern int OS_SendMessage(struct OSMessageQueue *queue, u32 message, int flags);
extern int OS_ReceiveMessage(struct OSMessageQueue *queue, u32 *message, int flags);
extern int OS_ReadMessage(struct OSMessageQueue *queue, u32 *message, int flags);
extern char *STD_ConcatenateString(char *dst, const char *src);
extern void WXC_End(void);

/* NitroDWC, by name. */
extern int DWC_GetLastError(int *error_code);
extern u32 DWC_GetAIDList(u8 **list);
extern int DWC_GetMyAID(void);
extern int DWC_IsValidAID(int aid);
extern void DWC_Ping(int aid);
extern int DWC_SetRecvBuffer(u8 aid, void *buffer, int size);
extern void DWC_SetAuthServer(int server);
extern void DWC_ConnectInetAsync(void);
extern int DWC_GetInetStatus(void);
extern void DWC_ProcessInet(void);
extern void DWC_SetSendSplitMax(int size);
extern int DWC_SetMatchingOption(int option, const void *value, int size);
extern int DWC_GetMOSCConnectBlockState(void);
extern int DWC_Auth_Base64Decode(const char *src, int length, void *dst, int capacity);
#define DWC_INET_CONNECTED 4
#define DWC_MATCH_OPTION_SC_CONNECT_BLOCK 1

/* NitroDWC, by their use or arguments where a name is given. */
extern int func_ov065_0227eef4(u8 aid);                /* TRUE when data can be sent to `aid` */
extern int func_ov065_02279894(void *list, int count); /* on the friend list */
extern int func_ov065_02277b98(void);                  /* the mask of the AIDs connected */
extern int func_ov065_02277c28(void);                  /* the number of players connected */
extern int func_ov065_0227f208(void);                  /* the link level, 0 to 3 */
extern int func_ov065_02277cbc(void);                  /* the connections closed; < 0 on failure */
extern int func_ov065_0227f710(void);
extern void func_ov065_022781e4(void);
extern int func_ov065_0227f22c(void);
extern int func_ov065_0227f46c(void *work); /* before DWC_SetAuthServer and DWC_ConnectInetAsync */
extern int func_ov065_0227f380(void);       /* before DWC_GetInetStatus */
extern int func_ov065_0227f720(const char *game_name);
/* By its arguments DWC_InitFriendsMatch (control, user data, product id, game name, secret key,
 * two buffer sizes, friend list and its length) and DWC_LoginAsync (callback last but one). */
extern void func_ov065_022782d4(void *control, void *user_data, int product_id, const char *game_name, const char *secret_key,
                                int send_size, int receive_size, void *friends, int friend_count);
extern void func_ov065_02277f98(int a, int b, void (*logged_in)(int, int, int), int argument);
extern void *func_ov065_0227ecf0(void (*pinged)(u16, int)); /* the ping callback set */
extern void func_ov065_02278000(void);
extern int func_ov065_0227f700(void);
extern void func_ov065_0227f1f4(u32 alloc, u32 free); /* the allocator and free function */
extern int func_ov065_0227982c(void *a, int b);
/* By its use DWC_GetFriendStatusSCData: a friend's status, filling its entries and data. */
extern u8 func_ov065_022798d0(const void *friend_data, u8 *max_entry, u8 *num_entry, char *data, int *size);
/* By its use: TRUE for a friend data that holds a friend. */
extern int func_0210132c(const void *friend_data);
extern void func_020ed3d4(int result, int profile_id, int argument);
extern void func_020ed144(u16 latency, int aid);
extern int func_020edab8(int unused, int size, int align);
extern void func_020edaa8(int unused, int block);
extern GetCallback func_020ed370;

/* The local wireless library. */
extern int func_ov066_02269934(void);  /* TRUE when data can be sent */
extern int func_ov066_022677e0(int a); /* the number of parents found */
extern int func_ov066_0226997c(void);  /* the mask of the AIDs connected */
extern int func_ov066_022699cc(void);  /* the child's AID */
extern int func_ov066_0226807c(void);  /* the number of players connected */
extern int func_ov066_0226a8c4(int aid, void *buffer, int size);
extern int func_ov066_02266ce8(void);                    /* the link level */
extern int func_ov066_022672b8(int state, int b, int c); /* a state asked for */
extern void func_ov066_0226b90c(void);
extern int func_ov066_02267404(void);
/* The library's set-up: what it is given first, the allocator, the free function. */
extern int func_ov066_0226748c(int a, void *(*alloc)(int, int), void (*free)(void *), int d);
extern int func_ov066_022667e0(void (*on_event)(u8 *event));
extern void func_ov066_02267fe8(ReceiveHandler *on_received);
extern void func_020ed6e8(u8 *event);
extern void CTRDG_WriteAgbFlashSectorAsync(int aid, char *buffer, unsigned int size);
#define LOCAL_STATE_IDLE 2
#define LOCAL_STATE_CONNECTED_A 10
#define LOCAL_STATE_CONNECTED_B 11
#define LOCAL_STATE_ERROR 0x80

/* The local library's parameters (func_ov066_0226b9b8). */
typedef struct LocalParameters {
    u32 game_id;
    u8 players;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
} LocalParameters;
extern int func_ov066_0226b9b8(LocalParameters *parameters);

/* Net_OnBlockSent by the game's symbol, the callback the local library is given. */
extern void func_020ed950(void *argument);
extern int func_ov066_022698ec(const void *buffer, u32 size, u16 to, void (*sent)(void *argument));
extern int func_ov065_0227ee74(u8 aid, const void *buffer, u32 size);
/* Waits for the next frame (OS_SleepThread on the frame's thread queue). */
extern void func_0206e6b0(void);

static BOOL is_local(u8 mode)
{
    return mode == MODE_LOCAL_PARENT || mode == MODE_LOCAL_CHILD;
}

static BOOL is_wfc(u8 mode)
{
    return mode == MODE_HOSTING || mode == MODE_JOINING;
}

/* OS_TicksToMilliSeconds. QUIRK: the shift wraps for ticks past 2^58. */
static u64 ticks_to_ms(u64 ticks)
{
    return (ticks << 6) / 0x82ea;
}

static u32 now_ms(void)
{
    return (u32) ticks_to_ms(OS_GetTick());
}

/* Whether more than the wait limit has passed since `since`.
 * QUIRK: compared in 64 bits, so when `since` is past the present time the difference wraps
 * and counts as elapsed. */
static BOOL timed_out(u32 since)
{
    return ticks_to_ms(OS_GetTick()) - since > (u64) data_0213e6b8;
}

/* ---- Errors ---- */

/* func_020eba08: the detail of the last error Net_GetError found. */
int Net_GetErrorDetail(void)
{
    return data_021fbf24;
}
CLEAN_AS(func_020eba08, Net_GetErrorDetail)

/* func_020eba18: the error of the library in use, 0 for none: 0x80xx from the local library,
 * 0x40xx from NitroDWC, 0xffff when no library is in use. The detail is cleared first. */
int Net_GetError(void)
{
    u8 mode = data_021fbef8;
    data_021fbf24 = 0;
    if (is_local(mode)) {
        return Local_GetError();
    }
    if (is_wfc(mode)) {
        return Wfc_GetError();
    }
    return mode == MODE_EXCHANGE ? 0 : 0xffff;
}
CLEAN_AS(func_020eba18, Net_GetError)

/* func_020eba94: NitroDWC's last error 1 to 11 as 0x4001 to 0x400b (its code the detail), any
 * other as 0xffff; without one, 0x4007 when a peer has not answered more than 30 pings. */
int Wfc_GetError(void)
{
    int error = DWC_GetLastError(&data_021fbf24);
    if (error != 0) {
        return error >= 1 && error <= 11 ? 0x4000 + error : 0xffff;
    }
    for (u32 aid = 0; aid < PEER_COUNT; aid++) {
        if (data_021fbff8[aid].unanswered > MAX_UNANSWERED) {
            data_021fbf24 = LOST_PEER_DETAIL;
            return 0x4007;
        }
    }
    return 0;
}
CLEAN_AS(func_020eba94, Wfc_GetError)

/* func_020ebc30: the local library's error: its state with LOCAL_STATE_ERROR set carries a code
 * 1 to 16 or 65 to 68, returned as 0x8000 + code (code 0 is no error, any other 0xffff);
 * without one, 0x80ff once the library reported its end. */
int Local_GetError(void)
{
    int state = func_ov066_0226760c();
    if (state & LOCAL_STATE_ERROR) {
        int code = state & ~LOCAL_STATE_ERROR;
        if (code == 0) {
            return 0;
        }
        if ((code >= 1 && code <= 16) || (code >= 65 && code <= 68)) {
            return 0x8000 + code;
        }
        return 0xffff;
    }
    if (data_021fbf68[0] == LOCAL_ENDED) {
        return 0x80ff;
    }
    return 0;
}
CLEAN_AS(func_020ebc30, Local_GetError)

/* ---- What the library in use reports ---- */

/* func_020ec1e8: the mode (NetworkMode). */
u8 Net_GetMode(void)
{
    return data_021fbef8;
}
CLEAN_AS(func_020ec1e8, Net_GetMode)

/* func_020ec148: the number of games a child can join: the parents the local library found,
 * or for joining what func_ov065_02279894 counts in the friend list; -1 in the other modes. */
int Net_CountJoinable(void)
{
    if (data_021fbef8 == MODE_LOCAL_CHILD) {
        return Local_CountParents();
    }
    if (data_021fbef8 == MODE_JOINING) {
        return Wfc_CountFriends();
    }
    return -1;
}
CLEAN_AS(func_020ec148, Net_CountJoinable)

/* func_020ec198 */
int Wfc_CountFriends(void)
{
    return func_ov065_02279894(data_021fbf3c, FRIEND_COUNT);
}
CLEAN_AS(func_020ec198, Wfc_CountFriends)

/* func_020ec1b4: the parents found; -1 while the library is not ready. */
int Local_CountParents(void)
{
    if (func_ov066_0226760c() != LOCAL_STATE_READY) {
        return -1;
    }
    return func_ov066_022677e0(0);
}
CLEAN_AS(func_020ec1b4, Local_CountParents)

/* func_020ec1f8: the mask of the AIDs connected (the player's alone, 1, with no library). */
int Net_GetConnectedMask(void)
{
    u8 mode = data_021fbef8;
    if (is_local(mode)) {
        return func_ov066_0226997c();
    }
    if (is_wfc(mode)) {
        return (u16) func_ov065_02277b98();
    }
    return 1;
}
CLEAN_AS(func_020ec1f8, Net_GetConnectedMask)

/* func_020ec260: the player's AID: 0 for the local parent and with no library. */
int Net_GetMyAid(void)
{
    u8 mode = data_021fbef8;
    if (is_local(mode)) {
        if (mode == MODE_LOCAL_PARENT) {
            return 0;
        }
        return func_ov066_022699cc();
    }
    if (is_wfc(mode)) {
        return DWC_GetMyAID();
    }
    return 0;
}
CLEAN_AS(func_020ec260, Net_GetMyAid)

/* func_020ec2d4: the number of players connected (1, the player, with no library). */
int Net_CountPlayers(void)
{
    u8 mode = data_021fbef8;
    if (is_local(mode)) {
        return func_ov066_0226807c();
    }
    if (!is_wfc(mode)) {
        return 1;
    }
    return func_ov065_02277c28() & 0xff;
}
CLEAN_AS(func_020ec2d4, Net_CountPlayers)

/* func_020ec338: the buffer data from peer `aid` is received into; 0 with no library. */
int Net_SetReceiveBuffer(int aid, void *buffer, int size)
{
    u8 mode = data_021fbef8;
    if (is_local(mode)) {
        return func_ov066_0226a8c4(aid, buffer, size);
    }
    if (is_wfc(mode)) {
        return DWC_SetRecvBuffer((u8) aid, buffer, size);
    }
    return 0;
}
CLEAN_AS(func_020ec338, Net_SetReceiveBuffer)

/* func_020ec39c: by its range and use (the game shows 3 less it as an icon), the link level,
 * 0 to 3; 0 with no library. */
int Net_GetLinkLevel(void)
{
    if (is_local(data_021fbef8)) {
        return Local_GetLinkLevel();
    }
    if (is_wfc(data_021fbef8)) {
        return Wfc_GetLinkLevel();
    }
    return 0;
}
CLEAN_AS(func_020ec39c, Net_GetLinkLevel)

/* func_020ec3fc: 0 until the Internet is connected. */
int Wfc_GetLinkLevel(void)
{
    if (data_021fbefc <= STAGE_CONNECTING) {
        return 0;
    }
    return func_ov065_0227f208();
}
CLEAN_AS(func_020ec3fc, Wfc_GetLinkLevel)

/* func_020ec434: what the library says, other values than 1 to 3 as 0. */
int Local_GetLinkLevel(void)
{
    int level = func_ov066_02266ce8();
    return level >= 1 && level <= 3 ? level : 0;
}
CLEAN_AS(func_020ec434, Local_GetLinkLevel)

/* ---- Starting ---- */

/* func_020ece54: the state set up before any library starts: the game code, the game's id,
 * the value handed first to the local library, the wait limit (given in ticks), the number of
 * players, and the allocator and free function. The send queue is emptied. */
void Net_Init(int game_code, int game_id, int local_argument, u64 timeout_ticks, u8 players, void *(*alloc)(int, int),
              void (*free)(void *))
{
    data_021fbef8 = MODE_NONE;
    data_021fbf04 = game_code;
    data_021fbf20 = (u32) game_id;
    data_0213e6b4 = (u8) local_argument;
    data_0213e6b8 = (u32) ticks_to_ms(timeout_ticks);
    data_021fbef4 = players;
    data_021fbf08 = alloc;
    OS_PutString = free;
    OS_InitMessageQueue(&data_021fbf98, data_021fbfb8, SEND_SLOT_COUNT);
    MI_CpuFill8(data_021fc120, 0, sizeof(data_021fc120));
}
CLEAN_AS(func_020ece54, Net_Init)

/* func_020ecba8: the Wi-Fi Connection set up in `mode` (hosting or joining) with the game's
 * handlers for data received and for a deleted friend, the user's block (NitroDWC's user data
 * at +0x20) and the friend list. The stages at their start, GETs allowed and POSTs held back
 * until the login (data_0213e6bc), no request buffers, the pings and the friends' statuses
 * cleared. */
void Wfc_Setup(int mode, ReceiveHandler *on_received, void (*on_deleted)(int index), u8 *user_block, FriendList *friends)
{
    data_021fbef8 = (u8) mode;
    CTRDGi_WriteAgbFlashSectorAsync = on_received;
    data_021fbf40 = user_block;
    data_021fbf3c = friends;
    data_021fbf30 = on_deleted;
    data_021fbefc = STAGE_START;
    data_021fbf00 = END_START;
    data_0213e6bc = FALSE;
    data_0213e6c0 = TRUE;
    data_021fbf1c = NULL;
    data_021fbf2c = NULL;
    data_021fbf44 = NULL;
    data_021fbf4c = NULL;
    data_021fbf14 = 0;
    data_021fbf10 = NULL;
    data_021fbf0c = NULL;
    data_021fbf34 = 0;
    MI_CpuFill8(data_021fbff8, 0, sizeof(data_021fbff8));
    for (u32 i = 0; i < FRIEND_COUNT; i++) {
        data_021fbf3c->status[i].status = 0;
    }
    func_ov065_0227f1f4((u32) (uintptr_t) func_020edab8, (u32) (uintptr_t) func_020edaa8);
}
CLEAN_AS(func_020ecba8, Wfc_Setup)

/* func_020ecce4: the local library started in `mode` (parent or child) with the game's handler
 * for data received. */
void Local_Setup(int mode, ReceiveHandler *on_received)
{
    LocalParameters parameters;
    CTRDGi_WriteAgbFlashSectorAsync = on_received;
    data_021fbef8 = (u8) mode;
    MI_CpuFill8(data_021fbf68, 0, sizeof(data_021fbf68));
    parameters.game_id = data_021fbf20;
    parameters.players = data_021fbef4;
    parameters.unk_05 = 8;
    parameters.unk_06 = 60;
    parameters.unk_07 = 2;
    func_ov066_0226748c(data_0213e6b4, func_020edaf0, UTi_PutString, 0);
    func_ov066_022667e0(func_020ed6e8);
    func_ov066_0226b9b8(&parameters);
    func_ov066_02267fe8(CTRDG_WriteAgbFlashSectorAsync);
    if (mode == MODE_LOCAL_PARENT) {
        func_ov066_022672b8(3, 0, 0);
    } else if (mode == MODE_LOCAL_CHILD) {
        func_ov066_022672b8(4, 0, 0);
    }
}
CLEAN_AS(func_020ecce4, Local_Setup)

/* ---- Connecting ---- */

/* func_020ec920: the connection advanced; TRUE once it is up. */
int Net_UpdateConnection(void)
{
    if (is_local(data_021fbef8)) {
        return Local_IsConnected();
    }
    if (is_wfc(data_021fbef8)) {
        return Wfc_UpdateConnection();
    }
    return FALSE;
}
CLEAN_AS(func_020ec920, Net_UpdateConnection)

/* func_020ecb80 */
int Local_IsConnected(void)
{
    int state = func_ov066_0226760c();
    return state == LOCAL_STATE_CONNECTED_A || state == LOCAL_STATE_CONNECTED_B;
}
CLEAN_AS(func_020ecb80, Local_IsConnected)

/* func_020ec980: one step of the Wi-Fi Connection: connect to the Internet, log in and update
 * the friend list, wait for the game hosted or joined (data_0213e6c4 cleared by the callbacks),
 * then set the ping callback. TRUE once ready: when joining, while the host (AID 0) is connected
 * and answers pings. */
int Wfc_UpdateConnection(void)
{
    switch (data_021fbefc) {
        case STAGE_START:
            func_ov065_0227f46c(data_021fbf5c);
            DWC_SetAuthServer(2);
            DWC_ConnectInetAsync();
            data_021fbefc = STAGE_CONNECTING;
            break;
        case STAGE_CONNECTING:
            if (func_ov065_0227f380() && DWC_GetInetStatus() == DWC_INET_CONNECTED) {
                data_021fbefc = STAGE_CONNECTED;
            }
            break;
        case STAGE_CONNECTED:
            func_ov065_0227f720(data_0213e744);
            data_0213e6bc = TRUE;
            data_0213e6c4 = TRUE;
            func_ov065_022782d4(data_021fc220, data_021fbf40 + 0x20, 0x299e, data_0213e744, data_0213e750, 0, 0, data_021fbf3c,
                                FRIEND_COUNT);
            func_ov065_02277f98(0, 0, func_020ed3d4, 0);
            data_021fbefc = STAGE_LOGGING_IN;
            break;
        case STAGE_LOGGING_IN:
            if (!data_0213e6c4) {
                data_0213e6c4 = TRUE;
                data_021fbefc = STAGE_LOGGED_IN;
            }
            break;
        case STAGE_LOGGED_IN:
            if (data_021fbef8 == MODE_HOSTING) {
                data_0213e6c4 = FALSE;
            }
            if (!data_0213e6c4) {
                DWC_SetSendSplitMax(0x100);
                func_ov065_0227ecf0(func_020ed144);
                Wfc_BlockNewClients();
                data_021fbefc = STAGE_READY;
            }
            break;
        case STAGE_READY:
            if (data_021fbef8 != MODE_JOINING) {
                return TRUE;
            }
            return (Net_GetConnectedMask() & 1) && data_021fbff8[0].unanswered <= MAX_UNANSWERED;
    }
    return FALSE;
}
CLEAN_AS(func_020ec980, Wfc_UpdateConnection)

/* func_020ecfec: when hosting, NitroDWC set to let no client in after one joins
 * (DWC_MATCH_OPTION_SC_CONNECT_BLOCK); the time a client joined cleared in every mode. */
void Wfc_BlockNewClients(void)
{
    u8 mode = data_021fbef8;
    data_021fbf34 = 0;
    if (mode == MODE_HOSTING) {
        int on = TRUE;
        DWC_SetMatchingOption(DWC_MATCH_OPTION_SC_CONNECT_BLOCK, &on, 0);
    }
}
CLEAN_AS(func_020ecfec, Wfc_BlockNewClients)

/* func_020ecde8: the Wi-Fi Connection processed, once a frame: only the Internet connection
 * while connecting, else NitroDWC, a ping and the block of new clients. */
void Wfc_Process(void)
{
    if (!is_wfc(data_021fbef8)) {
        return;
    }
    if (data_021fbefc == STAGE_CONNECTING) {
        DWC_ProcessInet();
        return;
    }
    func_ov065_02278000();
    func_ov065_0227f700();
    Wfc_PingNext();
    Wfc_UpdateConnectBlock();
}
CLEAN_AS(func_020ecde8, Wfc_Process)

/* func_020ecf24: when hosting, new clients let in again (func_ov065_0227e67c) 2 minutes after
 * one joined while NitroDWC blocks them. */
void Wfc_UpdateConnectBlock(void)
{
    if (data_021fbef8 != MODE_HOSTING || !DWC_GetMOSCConnectBlockState() || data_021fbf34 == 0) {
        return;
    }
    if (ticks_to_ms(OS_GetTick()) - data_021fbf34 > 2 * 60 * 1000) {
        data_021fbf34 = 0;
        func_ov065_0227e67c();
    }
}
CLEAN_AS(func_020ecf24, Wfc_UpdateConnectBlock)

/* func_020ed03c: once ready, each 250 ms one AID in turn (the time's quarter seconds modulo the
 * number of players) pinged and counted as unanswered until it answers; the player's own AID
 * and an AID with nobody get their ping reset instead.
 * REQUIRES: data_021fbef4 (the number of players) != 0. */
void Wfc_PingNext(void)
{
    if (data_021fbefc < STAGE_READY) {
        return;
    }
    u8 aid = (u8) (ticks_to_ms(OS_GetTick()) / PING_INTERVAL_MS % data_021fbef4);
    if (aid == data_0213e6b0) {
        return;
    }
    data_0213e6b0 = aid;
    if (aid == DWC_GetMyAID()) {
        data_021fbff8[aid].latency = 0;
        data_021fbff8[aid].unanswered = 0;
    } else if (DWC_IsValidAID(aid)) {
        data_021fbff8[aid].unanswered++;
        DWC_Ping(aid);
    } else {
        data_021fbff8[aid].latency = 0xffff;
        data_021fbff8[aid].unanswered = 0;
    }
}
CLEAN_AS(func_020ed03c, Wfc_PingNext)

/* ---- Sending ---- */

/* func_020ebeb8: up to three blocks sent (each a buffer, its size, the AIDs it goes to and a
 * callback for when it was sent; a block without a buffer, size or AID is skipped), when the
 * connection is up and nothing is waiting to be sent. TRUE when one was queued and the first
 * started; when it could not start the queue is emptied. */
int Net_SendBlocks(const void *buffer1, int size1, int to1, SentCallback *sent1, const void *buffer2, int size2, u16 to2,
                   SentCallback *sent2, const void *buffer3, int size3, u16 to3, SentCallback *sent3)
{
    if (!Net_UpdateConnection() || !Net_CanSend()) {
        return FALSE;
    }
    int queued1 = Net_QueueSend(buffer1, size1, to1, sent1);
    int queued2 = Net_QueueSend(buffer2, size2, to2, sent2);
    int queued3 = Net_QueueSend(buffer3, size3, to3, sent3);
    if (queued1 || queued2 || queued3) {
        if (Net_SendNext()) {
            return TRUE;
        }
        Net_ClearSendQueue();
    }
    return FALSE;
}
CLEAN_AS(func_020ebeb8, Net_SendBlocks)

/* func_020ebf70: TRUE when the library can send and the queue is empty (Net_IsSendQueueIdle). */
int Net_CanSend(void)
{
    u8 mode = data_021fbef8;
    if (is_local(mode)) {
        return Net_IsSendQueueIdle((u32) func_ov066_02269934());
    }
    if (!is_wfc(mode)) {
        return FALSE;
    }
    return Net_IsSendQueueIdle((u32) Wfc_CanSendToAll());
}
CLEAN_AS(func_020ebf70, Net_CanSend)

/* func_020ebfd8: TRUE when data can be sent to every AID connected but the player's. */
int Wfc_CanSendToAll(void)
{
    u8 *list;
    u32 count = DWC_GetAIDList(&list);
    for (u32 i = 0; i < count; i++) {
        u8 aid = list[i];
        if (aid != DWC_GetMyAID() && !func_ov065_0227eef4(aid)) {
            return FALSE;
        }
    }
    return TRUE;
}
CLEAN_AS(func_020ebfd8, Wfc_CanSendToAll)

/* func_020ec040: TRUE when the library is `ready` and the send queue is empty. A block found
 * waiting has its time noted, and once it waited past the limit it is sent again
 * (Net_SendNext). */
int Net_IsSendQueueIdle(u32 ready)
{
    u32 message;
    if (!ready) {
        data_021fbf18 = 0;
        return FALSE;
    }
    if (!OS_ReadMessage(&data_021fbf98, &message, 0)) {
        data_021fbf18 = 0;
        return TRUE;
    }
    if (data_021fbf18 == 0) {
        data_021fbf18 = now_ms();
    } else if (timed_out(data_021fbf18)) {
        data_021fbf18 = 0;
        Net_SendNext();
    }
    return FALSE;
}
CLEAN_AS(func_020ec040, Net_IsSendQueueIdle)

/* func_020ed73c: a block queued for the library in use; TRUE when it was. */
int Net_QueueSend(const void *buffer, int size, int to, SentCallback *sent)
{
    if (is_local(data_021fbef8)) {
        return Local_QueueSend(buffer, size, to, sent);
    }
    if (is_wfc(data_021fbef8)) {
        return Wfc_QueueSend(buffer, size, (u32) to, sent);
    }
    return FALSE;
}
CLEAN_AS(func_020ed73c, Net_QueueSend)

/* func_020ed79c: the block queued once for each AID of the mask `to` (AIDs 0 to 15); FALSE
 * without a buffer, size or AID, or when the queue is full.
 * QUIRK: the blocks queued before the queue was found full stay queued. */
int Wfc_QueueSend(const void *buffer, int size, u32 to, SentCallback *sent)
{
    if (buffer == NULL || size == 0 || to == 0) {
        return FALSE;
    }
    for (u32 aid = 0; aid < PEER_COUNT; aid++) {
        if ((to & (1u << aid)) && !Net_Enqueue(buffer, (u32) size, (u16) aid, sent)) {
            return FALSE;
        }
    }
    return TRUE;
}
CLEAN_AS(func_020ed79c, Wfc_QueueSend)

/* func_020ed834: the block queued once, for all the AIDs of `to`. */
int Local_QueueSend(const void *buffer, int size, int to, SentCallback *sent)
{
    if (buffer == NULL || size == 0 || to == 0) {
        return FALSE;
    }
    return Net_Enqueue(buffer, (u32) size, (u16) to, sent);
}
CLEAN_AS(func_020ed834, Local_QueueSend)

/* func_020ed874: the block put in the first free slot and the slot's index sent to the queue;
 * FALSE when every slot is taken. */
int Net_Enqueue(const void *buffer, u32 size, u16 to, SentCallback *sent)
{
    for (u32 i = 0; i < SEND_SLOT_COUNT; i++) {
        SendSlot *slot = &data_021fc120[i];
        if (slot->buffer == NULL) {
            slot->buffer = buffer;
            slot->size = size;
            slot->to = to;
            slot->sent = sent;
            OS_SendMessage(&data_021fbf98, i, 0);
            return TRUE;
        }
    }
    return FALSE;
}
CLEAN_AS(func_020ed874, Net_Enqueue)

/* func_020ed8f4: the queue emptied and every slot freed. */
void Net_ClearSendQueue(void)
{
    u32 message;
    while (OS_ReceiveMessage(&data_021fbf98, &message, 0)) {
    }
    for (u32 i = 0; i < SEND_SLOT_COUNT; i++) {
        data_021fc120[i].buffer = NULL;
    }
}
CLEAN_AS(func_020ed8f4, Net_ClearSendQueue)

/* func_020ed950: the block first in the queue was sent: it leaves the queue, its callback is
 * called (with what the library passed) and its slot freed. The next block, if any, is then
 * started, waiting frame after frame until the library takes it. */
void Net_OnBlockSent(void *argument)
{
    u32 index;
    if (!OS_ReceiveMessage(&data_021fbf98, &index, 0)) {
        return;
    }
    SendSlot *slot = &data_021fc120[index];
    if (slot->sent != NULL) {
        slot->sent(argument);
    }
    slot->buffer = NULL;
    while (OS_ReadMessage(&data_021fbf98, &index, 0) && !Net_SendNext()) {
        Net_WaitFrame();
    }
}
CLEAN_AS(func_020ed950, Net_OnBlockSent)

/* func_020ed9f4: the block first in the queue handed to the library in use (the local library
 * calls Net_OnBlockSent when it was sent; NitroDWC's own callback does); what the library
 * answers, FALSE with nothing queued or no library. */
int Net_SendNext(void)
{
    u32 index;
    if (!OS_ReadMessage(&data_021fbf98, &index, 0)) {
        return FALSE;
    }
    const SendSlot *slot = &data_021fc120[index];
    u8 mode = data_021fbef8;
    if (is_local(mode)) {
        return func_ov066_022698ec(slot->buffer, slot->size, slot->to, func_020ed950);
    }
    if (is_wfc(mode)) {
        return func_ov065_0227ee74((u8) slot->to, slot->buffer, slot->size);
    }
    return FALSE;
}
CLEAN_AS(func_020ed9f4, Net_SendNext)

/* func_020edb14: the Wi-Fi Connection processed and the next frame waited for. */
void Net_WaitFrame(void)
{
    Wfc_Process();
    func_0206e6b0();
}
CLEAN_AS(func_020edb14, Net_WaitFrame)

/* ---- Memory ---- */

/* func_020edaa8: NitroDWC's free function (func_ov065_0227f1f4), `name` being the kind of
 * block. QUIRK: it jumps to Net_Free, whose result stays in the result register, but it is
 * declared without a result. */
void Wfc_Free(int name, void *block)
{
    (void) name;
    Net_Free(block);
}
CLEAN_AS(func_020edaa8, Wfc_Free)

/* func_020edab8: NitroDWC's allocator. */
void *Wfc_Alloc(int name, int size, int align)
{
    (void) name;
    return Net_Alloc(size, align);
}
CLEAN_AS(func_020edab8, Wfc_Alloc)

/* UTi_PutString: a block freed through the free function the game installed (Net_Init).
 * QUIRK: what the free function leaves in the result register is returned. */
int Net_Free(void *block)
{
    return ((int (*)(void *)) OS_PutString)(block);
}
CLEAN_AS(UTi_PutString, Net_Free)

/* func_020edaf0: a block from the allocator the game installed (Net_Init). */
void *Net_Alloc(int size, int align)
{
    return data_021fbf08(size, align);
}
CLEAN_AS(func_020edaf0, Net_Alloc)

/* ---- Ending ---- */

/* func_020ec49c */
int Wfc_UpdateEnd(void)
{
    return Wfc_EndStep();
}
CLEAN_AS(func_020ec49c, Wfc_UpdateEnd)

/* func_020ec4a8: the library in use shut down, waiting for it; TRUE when it ended (the mode is
 * then MODE_ENDED), FALSE when the local library did not, or no library is in use. */
int Net_End(void)
{
    u8 mode = data_021fbef8;
    if (is_local(mode)) {
        return Local_End();
    }
    if (is_wfc(mode)) {
        while (!Wfc_EndStep()) {
            Net_WaitFrame();
        }
        data_021fbef8 = MODE_ENDED;
        return TRUE;
    }
    if (mode == MODE_EXCHANGE) {
        return Exchange_End();
    }
    return FALSE;
}
CLEAN_AS(func_020ec4a8, Net_End)

/* func_020ec548: the exchange ended, waiting frame by frame for the library to say so, and its
 * work memory freed. */
int Exchange_End(void)
{
    WXC_End();
    while (!data_021fbf48) {
        Net_WaitFrame();
    }
    Net_Free(data_021fbf28);
    data_021fbf28 = NULL;
    data_021fbef8 = MODE_ENDED;
    return TRUE;
}
CLEAN_AS(func_020ec548, Exchange_End)

/* func_020ec5ac: one step of the shutdown of the Wi-Fi Connection; TRUE once it is done. The
 * error is read (and its detail cleared) before the connections are closed, its value unused.
 * QUIRK: when closing the connections fails, the wait for the peers counts from time 0, so it
 * ends at once (timed_out). */
int Wfc_EndStep(void)
{
    switch (data_021fbf00) {
        case END_START:
            data_021fbf54 = now_ms();
            data_021fbf00 = END_WAIT_IDLE;
            break;
        case END_WAIT_IDLE:
            if (!data_0213e6c4 || data_021fbefc == STAGE_LOGGED_IN || timed_out(data_021fbf54)) {
                Net_GetError();
                if (func_ov065_02277cbc() < 0) {
                    data_021fbf54 = 0;
                } else {
                    data_021fbf54 = now_ms();
                }
                data_021fbf00 = END_WAIT_CLOSED;
            }
            break;
        case END_WAIT_CLOSED:
            if (func_ov065_02277c28() < 2 || timed_out(data_021fbf54)) {
                data_021fbf00 = END_STEP_3;
            }
            break;
        case END_STEP_3:
            func_ov065_0227f710();
            data_021fbf00 = END_STEP_4;
            break;
        case END_STEP_4:
            func_ov065_022781e4();
            data_021fbf00 = END_WAIT_LIBRARY;
            break;
        case END_WAIT_LIBRARY:
            if (func_ov065_0227f22c()) {
                data_021fbf00 = END_FREE_REQUESTS;
            }
            break;
        case END_FREE_REQUESTS:
            if (data_021fbf1c != NULL) {
                Net_Free(data_021fbf1c);
                Net_Free(data_021fbf2c);
                data_021fbf1c = NULL;
                data_021fbf2c = NULL;
            }
            if (data_021fbf44 != NULL) {
                Net_Free(data_021fbf44);
                Net_Free(data_021fbf0c);
                data_021fbf44 = NULL;
                data_021fbf0c = NULL;
            }
            data_021fbf00 = END_DONE;
            break;
        case END_DONE:
            return TRUE;
    }
    return FALSE;
}
CLEAN_AS(func_020ec5ac, Wfc_EndStep)

/* func_020ec848: the local library asked to stop, waited for until idle, then shut down; FALSE
 * when it did not get idle within the wait limit or did not shut down.
 * HW: a busy wait: the library's state is changed by its callbacks, run from interrupts. */
int Local_End(void)
{
    func_ov066_022672b8(0, 0, 0);
    u32 start = now_ms();
    while (func_ov066_0226760c() != LOCAL_STATE_IDLE) {
        if (timed_out(start)) {
            return FALSE;
        }
    }
    func_ov066_0226b90c();
    if (!func_ov066_02267404()) {
        return FALSE;
    }
    data_021fbef8 = MODE_ENDED;
    return TRUE;
}
CLEAN_AS(func_020ec848, Local_End)

/* ---- Callbacks the libraries call ---- */

/* func_020ed144: NitroDWC's ping answer from `aid`. */
void Wfc_OnPing(u16 latency, int aid)
{
    data_021fbff8[aid].latency = latency;
    data_021fbff8[aid].unanswered = 0;
}
CLEAN_AS(func_020ed144, Wfc_OnPing)

/* func_020ed168: the exchange's data was exchanged. */
void Exchange_OnExchanged(void)
{
    data_021fbf50 = TRUE;
}
CLEAN_AS(func_020ed168, Exchange_OnExchanged)

/* func_020ed17c: the exchange library's state; 0 when it ended. */
void Exchange_OnState(int state, void *argument)
{
    (void) argument;
    if (state == 0) {
        data_021fbf48 = TRUE;
    }
}
CLEAN_AS(func_020ed17c, Exchange_OnState)

/* func_020ed194: the first reply of a signed GET (Wfc_GetSigned), `buffer` its argument: the
 * signing key and the reply hashed (SHA-1, as hexadecimal into data_021fbf0c) and the URL asked
 * for again with the user's key, the hash and the region; that reply goes to func_020ed370. A
 * failed or empty reply ends the GET. */
void Wfc_OnSignedGetChallenge(const char *reply, int length, int result, char *buffer)
{
    if (reply == NULL || length == 0 || result != 0) {
        data_0213e6c0 = TRUE;
        return;
    }
    STD_CopyString(buffer, data_0213e708);
    STD_ConcatenateString(buffer, reply);
    MATH_CalcSHA1(data_021fbf0c + SHA1_DIGEST_SIZE, buffer, (u32) (length + STD_GetStringLength(data_0213e708)));
    digest_to_hex(data_021fbf0c);
    u64 key = Wfc_GetUserKey(data_021fbf40 + 0x20);
    OS_SNPrintf(data_021fbf44, URL_SIZE, data_0213e758, data_021fbf4c, key, data_021fbf0c, data_021fbf10);
    DWC_GetGHTTPData(data_021fbf44, func_020ed370, buffer);
}
CLEAN_AS(func_020ed194, Wfc_OnSignedGetChallenge)

/* func_020ed320: a GET's reply (Wfc_Get) copied to `buffer`; the GET is over either way.
 * BUG: the size asked for is copied whatever the reply's length. */
void Wfc_OnGetReply(const void *reply, int length, int result, void *buffer)
{
    if (reply != NULL && length != 0 && result == 0) {
#ifdef BUGFIX
        u32 size = (u32) length < (u32) data_021fbf14 ? (u32) length : (u32) data_021fbf14;
#else
        u32 size = (u32) data_021fbf14;
#endif
        MI_CpuCopy8(reply, buffer, size);
    }
    data_0213e6c0 = TRUE;
}
CLEAN_AS(func_020ed320, Wfc_OnGetReply)

/* func_020ed370: the signed GET's second reply, Base64, decoded into `buffer` (at most the size
 * asked for); the GET is over either way. */
void Wfc_OnSignedGetReply(const char *reply, int length, int result, void *buffer)
{
    if (reply != NULL && length != 0 && result == 0) {
        DWC_Auth_Base64Decode(reply, length, buffer, data_021fbf14);
    }
    data_0213e6c0 = TRUE;
}
CLEAN_AS(func_020ed370, Wfc_OnSignedGetReply)

/* func_020ed3c0: a POST is over. */
void Wfc_OnPosted(void)
{
    data_0213e6bc = TRUE;
}
CLEAN_AS(func_020ed3c0, Wfc_OnPosted)

/* func_020ed3d4: logged in (result 0): func_ov065_0227982c on the user's block, then the
 * friend list updated with the callbacks below, `argument` handed to each. */
void Wfc_OnLoggedIn(int result, int profile_id, int argument)
{
    (void) profile_id;
    if (result != 0) {
        return;
    }
    func_ov065_0227982c(data_021fbf40, 0x20);
    void *pass = (void *) (uintptr_t) (u32) argument;
    func_ov065_02277edc(NULL, func_020ed540, pass, func_020ed4cc, pass, func_020ed440, pass);
}
CLEAN_AS(func_020ed3d4, Wfc_OnLoggedIn)

/* func_020ed440: friend `index` was deleted by NitroDWC: cleared in the game's list, and the
 * game told. */
void Wfc_OnFriendDeleted(int index, int reason, void *argument)
{
    (void) reason;
    (void) argument;
    MI_CpuFill8(data_021fbf3c->friend_data[index], 0, FRIEND_DATA_SIZE);
    clear_friend_status(index);
    if (data_021fbf30 != NULL) {
        data_021fbf30(index);
    }
}
CLEAN_AS(func_020ed440, Wfc_OnFriendDeleted)

/* The status of friend `index` read from NitroDWC into the list. */
static void read_friend_status(int index)
{
    FriendStatus *status = &data_021fbf3c->status[index];
    int size;
    u8 value =
        func_ov065_022798d0(data_021fbf3c->friend_data[index], &status->max_entry, &status->num_entry, status->data, &size);
    data_021fbf3c->status[index].status = value;
}

/* func_020ed4cc: friend `index`'s status changed. */
void Wfc_OnFriendStatus(int index, int status, void *profile, void *argument)
{
    (void) status;
    (void) profile;
    (void) argument;
    read_friend_status(index);
}
CLEAN_AS(func_020ed4cc, Wfc_OnFriendStatus)

/* func_020ed540: the friend list's update finished (result NULL: success): no update is under
 * way, and the status of each friend read. */
void Wfc_OnFriendsUpdated(void *result, int changed, void *argument)
{
    (void) changed;
    (void) argument;
    if (result != NULL) {
        return;
    }
    data_0213e6c4 = FALSE;
    for (u32 i = 0; i < FRIEND_COUNT; i++) {
        if (func_0210132c(data_021fbf3c->friend_data[i])) {
            read_friend_status((int) i);
        }
    }
}
CLEAN_AS(func_020ed540, Wfc_OnFriendsUpdated)

/* func_020ed5f4: NitroDWC's callback for a new client; nothing to do. */
void Wfc_OnNewClient(void) {}
CLEAN_AS(func_020ed5f4, Wfc_OnNewClient)

/* func_020ed5f8: a client joined the game hosted (no error, not cancelled): the time noted. */
void Wfc_OnClientJoined(int error, int cancelled)
{
    if (error != 0 || cancelled != 0) {
        return;
    }
    data_021fbf34 = now_ms();
}
CLEAN_AS(func_020ed5f8, Wfc_OnClientJoined)

/* func_020ed658: data from `aid` received: the peer answered, and the game is given it. */
void Wfc_OnReceived(int aid, char *buffer, int size)
{
    data_021fbff8[aid].unanswered = 0;
    CTRDGi_WriteAgbFlashSectorAsync(aid, buffer, (unsigned int) size);
}
CLEAN_AS(func_020ed658, Wfc_OnReceived)

/* func_020ed68c: data to `aid` sent: the peer answered, and the send queue moves on
 * (Net_OnBlockSent, given the size). */
void Wfc_OnSent(int size, int aid)
{
    data_021fbff8[aid].unanswered = 0;
    Net_OnBlockSent((void *) (uintptr_t) (u32) size);
}
CLEAN_AS(func_020ed68c, Wfc_OnSent)

/* func_020ed6a8: a connection closed; nothing to do. */
void Wfc_OnClosed(int error, int local, int cancelled, int aid, int index, void *argument)
{
    (void) error;
    (void) local;
    (void) cancelled;
    (void) aid;
    (void) index;
    (void) argument;
}
CLEAN_AS(func_020ed6a8, Wfc_OnClosed)

/* func_020ed6ac: the friend's game was joined (result 0): the wait in Wfc_UpdateConnection
 * ends. */
void Wfc_OnJoined(u32 result, int local, int is_server, int cancelled, int aid, void *argument)
{
    (void) local;
    (void) is_server;
    (void) cancelled;
    (void) aid;
    (void) argument;
    if (result == 0) {
        data_0213e6c4 = FALSE;
    }
}
CLEAN_AS(func_020ed6ac, Wfc_OnJoined)

/* CTRDG_WriteAgbFlashSectorAsync (the name is NitroSDK's but does not fit): data received by
 * the local library handed to the game's handler. */
void Net_DispatchReceived(int aid, char *buffer, unsigned int size)
{
    CTRDGi_WriteAgbFlashSectorAsync(aid, buffer, size);
}
CLEAN_AS(CTRDG_WriteAgbFlashSectorAsync, Net_DispatchReceived)

/* func_020ed6e8: the local library's events: event[0] 0 and 1 for the peer event[1] connected
 * and disconnected, 2 for the library's end.
 * QUIRK: the end is noted in the flag of AID 0. */
void Local_OnEvent(u8 *event)
{
    switch (event[0]) {
        case 0:
            data_021fbf68[event[1]] = TRUE;
            break;
        case 1:
            data_021fbf68[event[1]] = FALSE;
            break;
        case 2:
            data_021fbf68[0] = LOCAL_ENDED;
            break;
    }
}
CLEAN_AS(func_020ed6e8, Local_OnEvent)

/* ---- Empty ---- */

/* func_020ecf1c: empty; called before func_0205cb4c. */
void Net_Empty020ecf1c(void) {}
CLEAN_AS(func_020ecf1c, Net_Empty020ecf1c)

/* func_020ecf20: empty; called after func_0205cb68. */
void Net_Empty020ecf20(void) {}
CLEAN_AS(func_020ecf20, Net_Empty020ecf20)
