/* The handlers of the players' messages (player_messages.h). */
#include "player_messages.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/packed_bytes.h"
#include "bbs.h"
#include "bottle_mail.h"
#include "catch_panel.h"
#include "exchange_block.h"
#include "letter.h"
#include "mail.h"
#include "main/sound.h"
#include "ov003/fish_shadow.h"
#include "ov003/thrown_bottle.h"
#include "ov003/town_insect.h"
#include "screen_panels.h"
#include "session.h"
#include "session_players.h"
#include "tile_changes.h"
#include "town_tune.h"
#include "villager_town.h"

#define RECORD_SIZE 0x100
#define BYTES_SIZE 30
#define NIBBLES_SIZE 16
#define PACKED_POSITION_SIZE 5
#define LOG_ENTRY_SIZE 0xc0

/* One degree in the game's 16-bit angles (65536 / 360, rounded). */
#define ANGLE_DEGREE 0xb6
/* Type 1's angle byte is in degrees plus this. */
#define TURN_BIAS 30

/* Type 2's ids: 0x12e8 and the 0x38 after it; a larger byte gives 0x12e8. */
#define PLACE_ID_FIRST 0x12e8
#define PLACE_IDS 0x38

/* What func_020961a8 gives for a player; only the angle is read here. */
typedef struct PlayerObject {
    u8 unk_00[0x8e];
    s16 angle;
} PlayerObject;

extern Heap *data_021fbe94;                           /* the current heap (heap.h) */
extern void *data_020ccf94;                           /* the message being built to send */
extern u8 data_020df6a4;                              /* the last reply to a type 8 (PLAYER_MESSAGE_NONE: none) */
extern const int data_020df6a8[PLAYER_MESSAGE_MODES]; /* the word for each mode: 0-4 */
extern u8 data_021cfbbc[NIBBLES_SIZE];                /* type 12's values */
extern u64 data_021f3b68;                             /* and packed, one in each 4 bits */
extern u16 data_021e5a2c;
extern u8 data_021f36ec[RECORD_SIZE];
extern u8 data_021ee418[RECORD_SIZE];
extern u8 data_021f3a68[BYTES_SIZE];
extern u8 data_021f3a86[BYTES_SIZE];
extern u8 data_020e54a8;  /* types 1, 2 and 5 are ignored unless 0 */
extern s32 data_020c904c; /* the height types 2 and 5 are placed at */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The handlers by type (PLAYER_MESSAGE_TYPES of them), as DS addresses. */
extern const u32 data_020df6bc[];

typedef void (*PlayerMessageHandler)(const u8 *message, int player);

static void *mode_object(void)
{
    return (void *) (uintptr_t) ScreenPanels_SecondPanel();
}

/* func_0207042c: type 23. */
void PlayerMessages_Key(const u8 *message, int player)
{
    (void) player;
    TileChanges_FreeHeld(message[1]);
}
CLEAN_AS(func_0207042c, PlayerMessages_Key)

/* func_02070438: types 18-22, the answer to 13-17: take the mode too. */
void PlayerMessages_ModeSet(const u8 *message, int player)
{
    (void) player;
    PlayerMessages_ApplyMode(message[0] - PLAYER_MESSAGE_MODE_SET);
}
CLEAN_AS(func_02070438, PlayerMessages_ModeSet)

/* func_02070444: types 13-17, set the mode (0-4) and answer with types 18-22. Mode 0 is taken
 * only when the mode is not 0 already, the others only when it is 0; otherwise nothing is done
 * or answered. QUIRK: the answer goes to player 4, not to the sender. */
void PlayerMessages_SetMode(const u8 *message, int player)
{
    (void) player;
    int mode = message[0] - PLAYER_MESSAGE_SET_MODE;
    BOOL mode_is_0 = CatchPanel_IsStopped(mode_object()) != 0;
    if (mode == 0 ? mode_is_0 : !mode_is_0) {
        return;
    }
    PlayerMessages_ApplyMode(mode);
    PlayerMessages_Send((u8) (PLAYER_MESSAGE_MODE_SET + mode), 4);
}
CLEAN_AS(func_02070444, PlayerMessages_SetMode)

/* func_02070490: request 0x67 for mode 0 and 0x66 for the others (SoundSys_PlaySe), then set
 * the mode's word. REQUIRES: 0 <= mode < 5. */
void PlayerMessages_ApplyMode(int mode)
{
    SoundSys_PlaySe(mode == 0 ? 0x67 : 0x66);
    CatchPanel_Start(mode_object(), data_020df6a8[mode], 0);
}
CLEAN_AS(func_02070490, PlayerMessages_ApplyMode)

/* func_020704c0: type 12, 16 values of four bits: kept, and packed into a 64-bit word. */
void PlayerMessages_Nibbles(const void *message, int player)
{
    (void) player;
    MI_CpuCopy8((const u8 *) message + 1, data_021cfbbc, NIBBLES_SIZE);
    TownTune_Pack((TownTunePacked *) &data_021f3b68, data_021cfbbc);
    TownTune_UseTune();
    VillagerTown_ClearMark((VillagerTown *) &data_021e5a2c);
}
CLEAN_AS(func_020704c0, PlayerMessages_Nibbles)

/* func_020704f4: types 9-11, the answer to a type 8. */
void PlayerMessages_StoreReply(const u8 *message, int player)
{
    (void) player;
    data_020df6a4 = message[0];
}
CLEAN_AS(func_020704f4, PlayerMessages_StoreReply)

/* func_02070500: type 8, a record to store in the first free of 10 slots; the sender is told
 * whether it was stored and whether there is room for another. REQUIRES: the current heap has
 * room for the record's copy (the allocation is not checked). */
void PlayerMessages_StoreRecord(const u8 *message, int player)
{
    Heap *heap = data_021fbe94;
    void *record = Heap_AllocBack(heap, RECORD_SIZE);
    int reply = PLAYER_MESSAGE_NOT_STORED;
    MI_CpuCopy8(message + 1, record, RECORD_SIZE);
    if (Mail_HoldAtPostOffice(record, 1) != 0) {
        reply = Mail_PostOfficeHasRoom() != 0 ? PLAYER_MESSAGE_STORED : PLAYER_MESSAGE_STORED_FULL;
    }
    Heap_Free(heap, record);
    PlayerMessages_Send(reply, player);
}
CLEAN_AS(func_02070500, PlayerMessages_StoreRecord)

/* func_0207055c: send a message of one byte, `type`, to `player`. */
void PlayerMessages_Send(int type, int player)
{
    void *outgoing = data_020ccf94;
    u8 byte = (u8) type;
    Session_BeginMessage(outgoing);
    Session_AppendMessage(outgoing, &byte, 1);
    Session_EndMessage(outgoing, PLAYER_MESSAGE_CATEGORY, (u32) player);
}
CLEAN_AS(func_0207055c, PlayerMessages_Send)

/* func_02070590 */
void PlayerMessages_SetReply(char reply)
{
    data_020df6a4 = (u8) reply;
}
CLEAN_AS(func_02070590, PlayerMessages_SetReply)

/* func_0207059c */
u8 PlayerMessages_Reply(void)
{
    return data_020df6a4;
}
CLEAN_AS(func_0207059c, PlayerMessages_Reply)

/* func_020705a8: type 7. */
void PlayerMessages_ClearRecord(const u8 *message, int player)
{
    (void) message;
    (void) player;
    Letter_Clear((Letter *) BottleMail_Letter((BottleState *) (void *) data_021f36ec));
}
CLEAN_AS(func_020705a8, PlayerMessages_ClearRecord)

/* func_020705c0: type 6, a record for data_021ee418. REQUIRES: the current heap has room for
 * the record's copy (the allocation is not checked). */
void PlayerMessages_Record(const char *message, int player)
{
    (void) player;
    Heap *heap = data_021fbe94;
    void *copy = Heap_AllocBack(heap, RECORD_SIZE);
    MI_CpuCopy8(message + 1, copy, RECORD_SIZE);
    Letter_Assign((Letter *) ExchangeBlock_BottleLetter((ExchangeBlock *) (void *) data_021ee418), copy);
    ExchangeBlock_ClearDrifts((ExchangeBlock *) (void *) data_021ee418);
    ExchangeBlock_SetArrivesAtOnce((ExchangeBlock *) (void *) data_021ee418, 0);
    Heap_Free(heap, copy);
}
CLEAN_AS(func_020705c0, PlayerMessages_Record)

/* func_02070614: types 3 and 4, 30 bytes for one of two places. */
void PlayerMessages_Bytes(const u8 *message, int player)
{
    (void) player;
    u8 bytes[BYTES_SIZE];
    MI_CpuCopy8(message + 1, bytes, BYTES_SIZE);
    switch (message[0]) {
        case PLAYER_MESSAGE_BYTES_A:
            MI_CpuCopy8(bytes, data_021f3a68, BYTES_SIZE);
            break;
        case PLAYER_MESSAGE_BYTES_B:
            MI_CpuCopy8(bytes, data_021f3a86, BYTES_SIZE);
            break;
    }
}
CLEAN_AS(func_02070614, PlayerMessages_Bytes)

/* func_02070658: types 2 and 5, a position packed in five bytes (from the payload's second
 * byte), at the height data_020c904c. Type 2 also carries an id in its first payload byte. */
void PlayerMessages_Place(const u8 *message, int player)
{
    if (data_020e54a8 != 0) {
        return;
    }
    int sender = (u8) player;
    u8 packed[PACKED_POSITION_SIZE];
    Vec3 position;
    MI_CpuCopy8(message + 2, packed, PACKED_POSITION_SIZE);
    PackedBytes_UnpackPoint(packed, (u32 *) &position.x, (u32 *) &position.z);
    position.y = data_020c904c;
    if (message[0] == PLAYER_MESSAGE_PLACE_ID) {
        int id = message[1] < PLACE_IDS ? PLACE_ID_FIRST + message[1] : PLACE_ID_FIRST;
        PlayerFish_PlaceFromPockets(sender, id, &position);
    } else {
        ThrownBottle_SetTarget(&position, sender);
    }
}
CLEAN_AS(func_02070658, PlayerMessages_Place)

/* func_020706cc: type 1, an angle in degrees (less TURN_BIAS) from the sender's object's own,
 * and a byte for func_ov003_0222e898; nothing while func_ov003_0222ea84 is not 0 for the
 * sender. QUIRK: the angle is kept in 16 bits, wrapping. */
void PlayerMessages_Turn(const u8 *message, int player)
{
    if (data_020e54a8 != 0) {
        return;
    }
    int sender = (u8) player;
    s16 angle = (s16) ((message[2] - TURN_BIAS) * ANGLE_DEGREE);
    PlayerObject *object = SessionPlayers_ActorOf(sender);
    if (object == NULL) {
        return;
    }
    angle = (s16) (angle + object->angle);
    if (TownInsect_HeldState(sender) == 0) {
        TownInsect_TakeHeld(message[1], sender);
        TownInsect_LetGo(sender, angle);
    }
}
CLEAN_AS(func_020706cc, PlayerMessages_Turn)

/* func_0207072c: type 0, an entry for the log at data_021eed68, copied out of the message
 * first (into a block of the current heap). */
void PlayerMessages_LogEntry(const u8 *message, int player)
{
    (void) player;
    Heap *heap = data_021fbe94;
    void *entry = Heap_AllocBack(heap, LOG_ENTRY_SIZE);
    MI_CpuCopy8(message + 1, entry, LOG_ENTRY_SIZE);
    Bbs_PostText(entry);
    Heap_Free(heap, entry);
}
CLEAN_AS(func_0207072c, PlayerMessages_LogEntry)

/* func_02070760: hand a received message to the handler of its type. QUIRK: the type is not
 * checked; one of PLAYER_MESSAGE_TYPES or more calls whatever word follows the table. */
void PlayerMessages_Dispatch(const u8 *message, int player)
{
    ((PlayerMessageHandler) (uintptr_t) data_020df6bc[message[0]])(message, player);
}
CLEAN_AS(func_02070760, PlayerMessages_Dispatch)

/* func_02070778 */
void PlayerMessages_ClearReply(void)
{
    data_020df6a4 = PLAYER_MESSAGE_NONE;
}
CLEAN_AS(func_02070778, PlayerMessages_ClearReply)
