/* Towns paired with the players' (paired_town.h). */
#include "paired_town.h"

#include "autoload_2/network.h"
#include "clean.h"
#include "game_variables.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"
#include "wifi_friends.h"

extern NetSession *data_020ccf94;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The 8-bit text of a town's name (0x20 bytes): made, set from a town and destroyed. The texts
 * made here are not read afterwards. */
typedef struct PairedTownText {
    u32 words[8];
} PairedTownText;
extern void *func_020641c8(PairedTownText *text);
extern void *func_020641b0(PairedTownText *text);
extern void func_02064210(const u8 *town, PairedTownText *text);

/* A design creator's town (a player's, from PlayerRecord_Player). */
extern u16 *func_02095040(DesignCreator *creator);

/* A slot's exchange block (0x950 bytes; 4 for this system's, data_021ee418) and the paired town
 * in it. */
extern u8 *func_02090040(int slot);
extern u8 *func_02090124(u8 *block);

/* A paired town's parts: its town (the object itself), its days, its bit 4, and setting them;
 * all cleared. */
extern u8 *func_020882ec(u8 *pairing);
extern int func_020882dc(u8 *pairing);
extern int func_020882c4(u8 *pairing);
extern void func_020882b0(u8 *pairing, u32 flag);
extern void func_020882e4(u8 *pairing, const void *town);
extern void func_020882cc(u8 *pairing, u8 days);
extern void func_020882f0(u8 *pairing);

extern u32 func_020644cc(int bound); /* a random number below `bound` */

/* The slot whose exchange block a slot is given (Activity.block_source). */
extern u8 func_020a2450(const Activity *activity, int slot);
/* The word at 0x94 of the link state (data_021f4320): a slot. */
extern u32 func_020a6ed0(void);

#define NO_PLAYER 4
#define OWN_BLOCK 4
/* Network modes of the Wi-Fi Connection (Net_GetMode). */
#define NET_MODE_WFC_3 3
#define NET_MODE_WFC_4 4
/* Game variable 0x49 of bank 0: while it is 0, a pairing is made only one time in 16. */
#define VARIABLE_BANK 0
#define VARIABLE_PAIRING 0x49
#define PAIRING_ODDS 16

/* The town of a player record's player. */
static const u8 *record_town(u8 *record)
{
    return (const u8 *) func_02095040(PlayerRecord_Player(record));
}

/* func_020a0c18: whether `record`'s player (its own friend data) is among the friends of
 * `owner`'s player. `activity` is not read. */
int PairedTown_AreFriends(Activity *activity, u8 *record, u8 *owner)
{
    (void) activity;
    WifiFriendData *own = WifiFriendData_GetData(WifiAccount_GetFriendData(PlayerRecord_WifiAccount(record)));
    WifiFriend *friends = WifiFriendList_GetEntries(PlayerRecord_WifiFriends(owner));
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        WifiFriendData *data = WifiFriendData_GetData(WifiFriend_GetFriendData(&friends[i]));
        if (data != NULL && Wfc_Call0210101c(own, data) != 0) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020a0c18, PairedTown_AreFriends)

/* func_020a0c74: session player `player` paired, unless it has no record or already has a
 * paired town (which is then noted). The partner is the first other player of the session in
 * slot order without a paired town (over the Wi-Fi Connection, a friend both ways). While game
 * variable 0x49 is 0 the pairing is made one time in 16. Each record gets the other's town and
 * PAIRED_TOWN_DAYS days, the partner's the flag when a draw of 0 or 1 gives 0 and the player's
 * when it gives 1; both pairings are noted and each goes into the exchange block its player is
 * given. */
void PairedTown_Pair(Activity *activity, int player)
{
    u8 *record = PlayerRecords_OfPlayer(player);
    if (record == NULL) {
        return;
    }
    PairedTownText player_text;
    func_020641c8(&player_text);
    func_02064210(record_town(record), &player_text);
    u8 *pairing = PlayerRecord_Field242C(record);
    if (func_020882dc(pairing) != 0) {
        PairedTown_Note(activity, pairing);
        func_020641b0(&player_text);
        return;
    }

    int partner = NO_PLAYER;
    u8 *partner_record = NULL;
    u8 *partner_pairing = NULL;
    PairedTownText partner_text;
    func_020641c8(&partner_text);
    NetSession *session = data_020ccf94;
    for (int i = 0; i < SESSION_SLOTS; i++) {
        if (i == player || Session_IsSlotTaken(session, i) == 0) {
            continue;
        }
        partner_record = PlayerRecords_OfPlayer(i);
        if (partner_record == NULL) {
            continue;
        }
        func_02064210(record_town(partner_record), &partner_text);
        partner_pairing = PlayerRecord_Field242C(partner_record);
        if (func_020882dc(partner_pairing) != 0) {
            continue;
        }
        if (Net_GetMode() == NET_MODE_WFC_3 || Net_GetMode() == NET_MODE_WFC_4) {
            if (PairedTown_AreFriends(activity, partner_record, record) == 0 ||
                PairedTown_AreFriends(activity, record, partner_record) == 0) {
                continue;
            }
        }
        partner = i;
        break;
    }
    if (partner == NO_PLAYER ||
        (*GameVariables_Slot(VARIABLE_BANK, VARIABLE_PAIRING) == 0 && func_020644cc(PAIRING_ODDS) != 0)) {
        func_020641b0(&partner_text);
        func_020641b0(&player_text);
        return;
    }

    u32 draw = func_020644cc(2);
    func_020882b0(partner_pairing, draw == 0);
    func_020882e4(partner_pairing, record_town(record));
    func_020882cc(partner_pairing, PAIRED_TOWN_DAYS);
    func_020882b0(pairing, draw == 1);
    func_020882e4(pairing, record_town(partner_record));
    func_020882cc(pairing, PAIRED_TOWN_DAYS);
    PairedTown_Note(activity, pairing);
    PairedTown_Note(activity, partner_pairing);

    int player_block = func_020a2450(activity, player);
    int partner_block = func_020a2450(activity, partner);

    u8 *block_record = PlayerRecords_OfPlayer(player_block);
    u8 *block = func_02090040(player_block);
    PairedTownText player_block_text;
    func_020641c8(&player_block_text);
    if (block_record != NULL) {
        func_02064210(record_town(block_record), &player_block_text);
    }
    MI_CpuCopy8(pairing, func_02090124(block), PAIRED_TOWN_SIZE);

    block_record = PlayerRecords_OfPlayer(partner_block);
    block = func_02090040(partner_block);
    PairedTownText partner_block_text;
    func_020641c8(&partner_block_text);
    if (block_record != NULL) {
        func_02064210(record_town(block_record), &partner_block_text);
    }
    MI_CpuCopy8(partner_pairing, func_02090124(block), PAIRED_TOWN_SIZE);

    func_020641b0(&partner_block_text);
    func_020641b0(&player_block_text);
    func_020641b0(&partner_text);
    func_020641b0(&player_text);
}
CLEAN_AS(func_020a0c74, PairedTown_Pair)

/* func_020a0ea8: does nothing. */
void PairedTown_Note(Activity *activity, u8 *pairing)
{
    (void) activity;
    (void) pairing;
}
CLEAN_AS(func_020a0ea8, PairedTown_Note)

/* func_020a0eac: the paired town of every taken slot's exchange block cleared, then the player
 * of every taken slot paired (PairedTown_Pair), from slot 3 down. */
void PairedTown_PairAll(Activity *activity)
{
    NetSession *session = data_020ccf94;
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            func_020882f0(func_02090124(func_02090040(slot)));
        }
    }
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            PairedTown_Pair(activity, slot);
        }
    }
}
CLEAN_AS(func_020a0eac, PairedTown_PairAll)

/* func_020a0efc: the paired town of every taken slot's exchange block cleared, then the player
 * of the link state's slot (func_020a6ed0) paired. */
void PairedTown_PairOwn(Activity *activity)
{
    NetSession *session = data_020ccf94;
    for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
        if (Session_IsSlotTaken(session, slot) != 0) {
            func_020882f0(func_02090124(func_02090040(slot)));
        }
    }
    PairedTown_Pair(activity, (int) func_020a6ed0());
}
CLEAN_AS(func_020a0efc, PairedTown_PairOwn)

/* func_020a0b94: when this system's exchange block holds a paired town (days left), it goes
 * into this system's player's record; then the block's is cleared. `unused` is not read.
 * QUIRK: the block's bit 4 is read and not used. */
void PairedTown_TakeOwn(void *unused)
{
    (void) unused;
    u8 *block = func_02090040(OWN_BLOCK);
    u8 *record = PlayerRecords_Current();
    PairedTownText player_text;
    func_020641c8(&player_text);
    func_02064210(record_town(record), &player_text);
    u8 *own_pairing = PlayerRecord_Field242C(record);
    u8 *arrived = func_02090124(block);
    PairedTownText arrived_text;
    func_020641c8(&arrived_text);
    func_02064210(func_020882ec(arrived), &arrived_text);
    if (func_020882dc(arrived) != 0) {
        MI_CpuCopy8(arrived, own_pairing, PAIRED_TOWN_SIZE);
        func_020882c4(arrived);
    }
    func_020882f0(func_02090124(block));
    func_020641b0(&arrived_text);
    func_020641b0(&player_text);
}
CLEAN_AS(func_020a0b94, PairedTown_TakeOwn)
