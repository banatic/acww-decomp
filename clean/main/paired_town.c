/* Towns paired with the players' (paired_town.h). */
#include "paired_town.h"

#include "autoload_2/network.h"
#include "clean.h"
#include "game_variables.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"
#include "wifi_friends.h"
#include "activity.h"
#include "exchange_block.h"
#include "link_global.h"
#include "main_random.h"
#include "player_id.h"
#include "town_name.h"

extern NetSession *data_020ccf94;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The 8-bit text of a town's name (0x20 bytes): made, set from a town and destroyed. The texts
 * made here are not read afterwards. */
typedef struct PairedTownText {
    u32 words[8];
} PairedTownText;

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
    return (const u8 *) PlayerId_Town(PlayerRecord_Player(record));
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
    TownNameText_Construct((TownNameText *) &player_text);
    TownName_ToText((TownName *) (void *) record_town(record), (TextBase *) &player_text);
    u8 *pairing = PlayerRecord_Field242C(record);
    if (PairedTown_Days(pairing) != 0) {
        PairedTown_Note(activity, pairing);
        TownNameText_Destruct((TownNameText *) &player_text);
        return;
    }

    int partner = NO_PLAYER;
    u8 *partner_record = NULL;
    u8 *partner_pairing = NULL;
    PairedTownText partner_text;
    TownNameText_Construct((TownNameText *) &partner_text);
    NetSession *session = data_020ccf94;
    for (int i = 0; i < SESSION_SLOTS; i++) {
        if (i == player || Session_IsSlotTaken(session, i) == 0) {
            continue;
        }
        partner_record = PlayerRecords_OfPlayer(i);
        if (partner_record == NULL) {
            continue;
        }
        TownName_ToText((TownName *) (void *) record_town(partner_record), (TextBase *) &partner_text);
        partner_pairing = PlayerRecord_Field242C(partner_record);
        if (PairedTown_Days(partner_pairing) != 0) {
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
        (*GameVariables_Slot(VARIABLE_BANK, VARIABLE_PAIRING) == 0 && MainRandom_Below(PAIRING_ODDS) != 0)) {
        TownNameText_Destruct((TownNameText *) &partner_text);
        TownNameText_Destruct((TownNameText *) &player_text);
        return;
    }

    u32 draw = MainRandom_Below(2);
    PairedTown_SetFlag4(partner_pairing, draw == 0);
    PairedTown_SetTown(partner_pairing, record_town(record));
    PairedTown_SetDays(partner_pairing, PAIRED_TOWN_DAYS);
    PairedTown_SetFlag4(pairing, draw == 1);
    PairedTown_SetTown(pairing, record_town(partner_record));
    PairedTown_SetDays(pairing, PAIRED_TOWN_DAYS);
    PairedTown_Note(activity, pairing);
    PairedTown_Note(activity, partner_pairing);

    int player_block = Activity_BlockSource(activity, player);
    int partner_block = Activity_BlockSource(activity, partner);

    u8 *block_record = PlayerRecords_OfPlayer(player_block);
    u8 *block = (u8 *) (uintptr_t) ExchangeBlock_OfSlot(player_block);
    PairedTownText player_block_text;
    TownNameText_Construct((TownNameText *) &player_block_text);
    if (block_record != NULL) {
        TownName_ToText((TownName *) (void *) record_town(block_record), (TextBase *) &player_block_text);
    }
    MI_CpuCopy8(pairing, (void *) (uintptr_t) ExchangeBlock_PairedTown((ExchangeBlock *) (void *) block), PAIRED_TOWN_SIZE);

    block_record = PlayerRecords_OfPlayer(partner_block);
    block = (u8 *) (uintptr_t) ExchangeBlock_OfSlot(partner_block);
    PairedTownText partner_block_text;
    TownNameText_Construct((TownNameText *) &partner_block_text);
    if (block_record != NULL) {
        TownName_ToText((TownName *) (void *) record_town(block_record), (TextBase *) &partner_block_text);
    }
    MI_CpuCopy8(partner_pairing, (void *) (uintptr_t) ExchangeBlock_PairedTown((ExchangeBlock *) (void *) block),
                PAIRED_TOWN_SIZE);

    TownNameText_Destruct((TownNameText *) &partner_block_text);
    TownNameText_Destruct((TownNameText *) &player_block_text);
    TownNameText_Destruct((TownNameText *) &partner_text);
    TownNameText_Destruct((TownNameText *) &player_text);
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
            PairedTown_Reset(
                (u8 *) (uintptr_t) ExchangeBlock_PairedTown((ExchangeBlock *) (uintptr_t) ExchangeBlock_OfSlot(slot)));
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
            PairedTown_Reset(
                (u8 *) (uintptr_t) ExchangeBlock_PairedTown((ExchangeBlock *) (uintptr_t) ExchangeBlock_OfSlot(slot)));
        }
    }
    PairedTown_Pair(activity, (int) LinkGlobal_ServedSlot());
}
CLEAN_AS(func_020a0efc, PairedTown_PairOwn)

/* func_020a0b94: when this system's exchange block holds a paired town (days left), it goes
 * into this system's player's record; then the block's is cleared. `unused` is not read.
 * QUIRK: the block's bit 4 is read and not used. */
void PairedTown_TakeOwn(void *unused)
{
    (void) unused;
    u8 *block = (u8 *) (uintptr_t) ExchangeBlock_OfSlot(OWN_BLOCK);
    u8 *record = PlayerRecords_Current();
    PairedTownText player_text;
    TownNameText_Construct((TownNameText *) &player_text);
    TownName_ToText((TownName *) (void *) record_town(record), (TextBase *) &player_text);
    u8 *own_pairing = PlayerRecord_Field242C(record);
    u8 *arrived = (u8 *) (uintptr_t) ExchangeBlock_PairedTown((ExchangeBlock *) (void *) block);
    PairedTownText arrived_text;
    TownNameText_Construct((TownNameText *) &arrived_text);
    TownName_ToText((TownName *) (void *) PairedTown_Town(arrived), (TextBase *) &arrived_text);
    if (PairedTown_Days(arrived) != 0) {
        MI_CpuCopy8(arrived, own_pairing, PAIRED_TOWN_SIZE);
        PairedTown_Flag4(arrived);
    }
    PairedTown_Reset((u8 *) (uintptr_t) ExchangeBlock_PairedTown((ExchangeBlock *) (void *) block));
    TownNameText_Destruct((TownNameText *) &arrived_text);
    TownNameText_Destruct((TownNameText *) &player_text);
}
CLEAN_AS(func_020a0b94, PairedTown_TakeOwn)

/* The paired town's own parts. */
#include "autoload_2/approach.h"

/* The days in which the pairing counts as in its last week (of PAIRED_TOWN_DAYS). */
#define PAIRED_TOWN_WEEK_FIRST 1
#define PAIRED_TOWN_WEEK_LAST 7
/* The player record's flag cleared once the pairing is outside its last week. */
#define PAIRED_TOWN_PLAYER_FLAG 0x33

extern u32 data_021dc7a8[]; /* the state block (state_block.h) */

static u8 *paired_town_of_state_block(void)
{
    return (u8 *) data_021dc7a8 + PAIRED_TOWN_STATE_BLOCK_OFFSET;
}

/* func_02088284 */
void PairedTown_ClearFlag5(u8 *pairing)
{
    pairing[PAIRED_TOWN_STATE] &= (u8) ~PAIRED_TOWN_FLAG_5;
}
CLEAN_AS(func_02088284, PairedTown_ClearFlag5)

/* func_02088290 */
void PairedTown_SetFlag5(u8 *pairing)
{
    pairing[PAIRED_TOWN_STATE] |= PAIRED_TOWN_FLAG_5;
}
CLEAN_AS(func_02088290, PairedTown_SetFlag5)

/* func_0208829c */
int PairedTown_Flag5(u8 *pairing)
{
    return (pairing[PAIRED_TOWN_STATE] & PAIRED_TOWN_FLAG_5) != 0;
}
CLEAN_AS(func_0208829c, PairedTown_Flag5)

/* func_020882b0: the flag set from bit 0 of `flag`. */
void PairedTown_SetFlag4(u8 *pairing, u32 flag)
{
    u8 state = pairing[PAIRED_TOWN_STATE] & (u8) ~PAIRED_TOWN_FLAG_4;
    pairing[PAIRED_TOWN_STATE] = (u8) (state | ((flag & 1) << 4));
}
CLEAN_AS(func_020882b0, PairedTown_SetFlag4)

/* func_020882c4 */
int PairedTown_Flag4(u8 *pairing)
{
    return (pairing[PAIRED_TOWN_STATE] & PAIRED_TOWN_FLAG_4) != 0;
}
CLEAN_AS(func_020882c4, PairedTown_Flag4)

/* func_020882cc: the days set to the low four bits of `days`. */
void PairedTown_SetDays(u8 *pairing, u8 days)
{
    u8 state = pairing[PAIRED_TOWN_STATE] & (u8) ~PAIRED_TOWN_DAYS_MASK;
    pairing[PAIRED_TOWN_STATE] = (u8) (state | (days & PAIRED_TOWN_DAYS_MASK));
}
CLEAN_AS(func_020882cc, PairedTown_SetDays)

/* func_020882dc */
int PairedTown_Days(u8 *pairing)
{
    return pairing[PAIRED_TOWN_STATE] & PAIRED_TOWN_DAYS_MASK;
}
CLEAN_AS(func_020882dc, PairedTown_Days)

/* func_020882e4: the town copied in. */
void PairedTown_SetTown(u8 *pairing, const void *town)
{
    TownName_Copy((TownName *) (void *) pairing, town);
}
CLEAN_AS(func_020882e4, PairedTown_SetTown)

/* func_020882ec: the town (the object itself). */
u8 *PairedTown_Town(u8 *pairing)
{
    return pairing;
}
CLEAN_AS(func_020882ec, PairedTown_Town)

/* func_020882f0: no town, no days and both flags clear. */
void PairedTown_Reset(u8 *pairing)
{
    TownName_Clear((TownName *) (void *) pairing);
    pairing[PAIRED_TOWN_STATE] &= (u8) ~(PAIRED_TOWN_DAYS_MASK | PAIRED_TOWN_FLAG_4 | PAIRED_TOWN_FLAG_5);
}
CLEAN_AS(func_020882f0, PairedTown_Reset)

/* func_02088318: the state block's pairing copied back into the current player's record;
 * outside its last week the record's flag 0x33 is cleared. Nothing without a current player. */
void PairedTown_RestoreCurrent(void)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return;
    }
    u8 *pairing = paired_town_of_state_block();
    MI_CpuCopy8(pairing, PlayerRecord_Field242C(record), PAIRED_TOWN_SIZE);
    if (Math_IsBetween(PairedTown_Days(pairing), PAIRED_TOWN_WEEK_FIRST, PAIRED_TOWN_WEEK_LAST) == 0) {
        PlayerRecord_ClearFlag(record, PAIRED_TOWN_PLAYER_FLAG);
    }
}
CLEAN_AS(func_02088318, PairedTown_RestoreCurrent)

/* func_02088368: the current player's pairing copied into the state block. */
void PairedTown_SaveCurrent(void)
{
    u8 *record = PlayerRecords_Current();
    if (record != NULL) {
        MI_CpuCopy8(PlayerRecord_Field242C(record), paired_town_of_state_block(), PAIRED_TOWN_SIZE);
    }
}
CLEAN_AS(func_02088368, PairedTown_SaveCurrent)

/* func_02088394: whether the current player's pairing has the flag and 1-7 days left. */
int PairedTown_CurrentFlaggedInLastWeek(void)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return 0;
    }
    u8 *pairing = PlayerRecord_Field242C(record);
    return PairedTown_Flag4(pairing) == 1 &&
           Math_IsBetween(PairedTown_Days(pairing), PAIRED_TOWN_WEEK_FIRST, PAIRED_TOWN_WEEK_LAST) != 0;
}
CLEAN_AS(func_02088394, PairedTown_CurrentFlaggedInLastWeek)

/* func_020883cc: whether the current player's pairing lacks the flag and has 1-7 days left. */
int PairedTown_CurrentUnflaggedInLastWeek(void)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return 0;
    }
    u8 *pairing = PlayerRecord_Field242C(record);
    return PairedTown_Flag4(pairing) == 0 &&
           Math_IsBetween(PairedTown_Days(pairing), PAIRED_TOWN_WEEK_FIRST, PAIRED_TOWN_WEEK_LAST) != 0;
}
CLEAN_AS(func_020883cc, PairedTown_CurrentUnflaggedInLastWeek)

/* func_02088404: `days` days (1 or more) taken off the state block's pairing, which is reset
 * when none are left; then it goes back into the current player's record. */
void PairedTown_PassDays(int days)
{
    if (days < 1) {
        return;
    }
    u8 *pairing = paired_town_of_state_block();
    int left = PairedTown_Days(pairing) - days;
    if (left <= 0) {
        PairedTown_Reset(pairing);
    } else {
        PairedTown_SetDays(pairing, (u8) left);
    }
    PairedTown_RestoreCurrent();
}
CLEAN_AS(func_02088404, PairedTown_PassDays)

/* func_02088450: destructs the town. */
u8 *PairedTown_Destruct(u8 *pairing)
{
    TownName_Destruct(pairing);
    return pairing;
}
CLEAN_AS(func_02088450, PairedTown_Destruct)

/* func_02088460: constructs the town. */
u8 *PairedTown_Construct(u8 *pairing)
{
    TownName_Construct(pairing);
    return pairing;
}
CLEAN_AS(func_02088460, PairedTown_Construct)
