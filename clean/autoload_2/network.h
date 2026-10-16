/* The game's layer over the wireless libraries: the wireless exchange of data with nearby
 * systems (NitroSDK's WXC, in overlay 67), the Nintendo Wi-Fi Connection (NitroDWC, overlay 65:
 * the friend list, hosting or joining a friend's game, and HTTP requests to the game's server)
 * and the local wireless library of overlay 66. One mode says which is in use (data_021fbef8),
 * and the Wi-Fi Connection advances through stages (data_021fbefc, func_020ec980). Over the
 * local library and NitroDWC alike the game sends blocks through one queue of 16 and reads
 * one error code (Net_GetError). */
#ifndef CLEAN_AUTOLOAD_2_NETWORK_H
#define CLEAN_AUTOLOAD_2_NETWORK_H

#include "types.h"

/* What NitroDWC reports of a friend (DWC_GetFriendStatusSCData): the status data the friend
 * set, its status and the entries of the game it hosts. */
typedef struct FriendStatus {
    char data[0x20];
    u8 status;
    u8 max_entry;
    u8 num_entry;
} FriendStatus;

#define FRIEND_COUNT 32
#define FRIEND_DATA_SIZE 12 /* NitroDWC's DWCFriendData */

/* The friend list the game hands NitroDWC (data_021fbf3c), and what is known of each. */
typedef struct FriendList {
    u8 friend_data[FRIEND_COUNT][FRIEND_DATA_SIZE];
    FriendStatus status[FRIEND_COUNT];
} FriendList;

u32 Exchange_IsDone(void);
int Exchange_IsActive(void);
void Exchange_Call0226883c(void);
void Exchange_Start(void);
void Exchange_Init(u8 *send, u8 *receive, int size);
int Wfc_ClearHostTime(void);
int Wfc_DeleteFriend(int index);
int Wfc_SetFriend(int index, const void *friend_data);
int Wfc_IsBuddyFriendData(const void *friend_data);
int Wfc_GetFriendDataType(const void *friend_data);
int Wfc_Call0210101c(const void *a, const void *b);
int Wfc_Call021012c4(void *data);
int Wfc_FinishGet(void);
int Wfc_Get(const char *url, void *buffer, int size);
int Wfc_GetSigned(const char *url, void *buffer, int size, const char *region);
int Wfc_FinishPost(void);
int Wfc_PostSigned(const char *url, const void *data, u32 length, const char *region);
s64 Wfc_GetFriendKey(const void *friend_data);
int Wfc_FriendDataFromKey(const void *user_data, void *friend_data, int key_low, int key_high);
u64 Wfc_GetUserKey(const void *user_data);
void Wfc_Call0210111c(void *user_data, void *value);
int Wfc_IsAuthentic(const void *user_data);
int Wfc_TakeDirty(void *user_data);
void Wfc_InitUserData(void *user_data, u32 game_code);
int Wfc_JoinFriendGame(int profile_id);
int Wfc_HostGame(void);
FriendList *Wfc_GetFriendList(void);
int Wfc_ProfileIdAt(int index);
int Wfc_FriendIndexOf(int profile_id);
int Local_SelectEntry(const void *entry);
void **Local_ListEntries(void);
int Local_EntryDataSize(void *entry);
void *Local_EntryData(void *entry);
int Local_Call02269638(const void *data, u32 length);
void Wfc_Call022784a0(void);

/* What the game is handed data received from a peer with: the peer's AID, the data, its size. */
typedef void ReceiveHandler(int aid, char *buffer, unsigned int size);
/* Called once a block of the send queue was sent. */
typedef void SentCallback(void *argument);

int Net_GetErrorDetail(void);
int Net_GetError(void);
int Wfc_GetError(void);
int Local_GetError(void);
u8 Net_GetMode(void);
int Net_CountJoinable(void);
int Wfc_CountFriends(void);
int Local_CountParents(void);
int Net_GetConnectedMask(void);
int Net_GetMyAid(void);
int Net_CountPlayers(void);
int Net_SetReceiveBuffer(int aid, void *buffer, int size);
int Net_GetLinkLevel(void);
int Wfc_GetLinkLevel(void);
int Local_GetLinkLevel(void);
void Net_Init(int game_code, int game_id, int local_argument, u64 timeout_ticks, u8 players, void *(*alloc)(int, int),
              void (*free)(void *));
void Wfc_Setup(int mode, ReceiveHandler *on_received, void (*on_deleted)(int index), u8 *user_block, FriendList *friends);
void Local_Setup(int mode, ReceiveHandler *on_received);
int Net_UpdateConnection(void);
int Local_IsConnected(void);
int Wfc_UpdateConnection(void);
void Wfc_BlockNewClients(void);
void Wfc_Process(void);
void Wfc_UpdateConnectBlock(void);
void Wfc_PingNext(void);
int Net_SendBlocks(const void *buffer1, int size1, int to1, SentCallback *sent1, const void *buffer2, int size2, u16 to2,
                   SentCallback *sent2, const void *buffer3, int size3, u16 to3, SentCallback *sent3);
int Net_CanSend(void);
int Wfc_CanSendToAll(void);
int Net_IsSendQueueIdle(u32 ready);
int Net_QueueSend(const void *buffer, int size, int to, SentCallback *sent);
int Wfc_QueueSend(const void *buffer, int size, u32 to, SentCallback *sent);
int Local_QueueSend(const void *buffer, int size, int to, SentCallback *sent);
int Net_Enqueue(const void *buffer, u32 size, u16 to, SentCallback *sent);
void Net_ClearSendQueue(void);
int Wfc_UpdateEnd(void);
int Net_End(void);
int Exchange_End(void);
int Wfc_EndStep(void);
int Local_End(void);
void Wfc_OnPing(u16 latency, int aid);
void Exchange_OnExchanged(void);
void Exchange_OnState(int state, void *argument);
void Wfc_OnSignedGetChallenge(const char *reply, int length, int result, char *buffer);
void Wfc_OnGetReply(const void *reply, int length, int result, void *buffer);
void Wfc_OnSignedGetReply(const char *reply, int length, int result, void *buffer);
void Wfc_OnPosted(void);
void Wfc_OnLoggedIn(int result, int profile_id, int argument);
void Wfc_OnFriendDeleted(int index, int reason, void *argument);
void Wfc_OnFriendStatus(int index, int status, void *profile, void *argument);
void Wfc_OnFriendsUpdated(void *result, int changed, void *argument);
void Wfc_OnNewClient(void);
void Wfc_OnClientJoined(int error, int cancelled);
void Wfc_OnReceived(int aid, char *buffer, int size);
void Wfc_OnSent(int size, int aid);
void Wfc_OnClosed(int error, int local, int cancelled, int aid, int index, void *argument);
void Wfc_OnJoined(u32 result, int local, int is_server, int cancelled, int aid, void *argument);
void Net_DispatchReceived(int aid, char *buffer, unsigned int size);
void Local_OnEvent(u8 *event);
void Net_Empty020ecf1c(void);
void Net_Empty020ecf20(void);

#endif
