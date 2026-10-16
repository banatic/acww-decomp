/* The save on the game card as the activity process and the boot screen read and write it
 * (activity_card.h). */
#include "activity_card.h"

#include "backup_card.h"
#include "card_save.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "player_record.h"
#include "player_records.h"
#include "state_block.h"
#include "wifi_friends.h"

static_assert(offsetof(ActivityCard, run_start) == 0xa4 - 0xa0 && offsetof(ActivityCard, image) == 0xb0 - 0xa0,
              "activity card");
static_assert(offsetof(Activity, unk_a0) == 0xa0 && offsetof(Activity, block_copy) == 0xb8, "activity");
static_assert(offsetof(Activity, unk_10b) == 0x10b && offsetof(Activity, card_parts) == 0x10e, "activity");

extern BackupCard data_021c8188;
extern StateBlock data_021dc7a8;
extern SaveStamp data_021f3ba0; /* the state block's part_173f8 */
/* The current activity, or NULL. */
extern Activity *data_021f3c3c;

/* For each CardSavePart: where it starts in the save memory, its length, and the length its
 * sum covers. */
extern const u32 data_020d1c20[3];
extern const u32 data_020d1bf0[3];
extern const u32 data_020d1c08[3];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The exchange block (part_11c70, 0x950 bytes): the checksum kept at its 0x94a. */
extern u16 func_0209015c(u8 *block);
extern void func_02090168(u8 *block, u16 checksum);
/* The part at 0x1704c of the state block (0x104 bytes): the checksum byte kept at its 0x100. */
extern u8 func_0208ffe8(u8 *part);
extern void func_0208fff4(u8 *part, u8 checksum);

/* The steps' tables (function-local statics of the game, filled once) and their constants. */
extern u32 data_021f3c2c;
extern MemberPointer data_021f3c84[7];
extern const MemberPointer data_020e38a8, data_020e3918, data_020e3930, data_020e3968, data_020e39d8, data_020e3a60;
extern u32 data_021f3c28;
extern MemberPointer data_021f3c64[4];
extern const MemberPointer data_020e3828, data_020e3838, data_020e38f0, data_020e3868;
extern const MemberPointer __ptmf_null;

#define STATE_BLOCK_SIZE 0x173fc
#define LETTERS_SIZE 0xc804
#define LETTERS_CHECKSUM 0xc802 /* the letters block's halfword that makes its sum 0 */
#define EXCHANGE_BLOCK_SIZE 0x950
#define PART_1704C_SIZE 0x104
#define ACCOUNT_SIZE 0x50
#define FRIEND_ROSTER_SIZE 0x484
#define STAMP_SIZE 4
#define ERASED 0xff /* what an erased part is filled with */
#define NIBBLE 0xf
#define NO_PART 3 /* Activity.card_parts before the check chose */

/* The activity's fields for the card. */
static ActivityCard *card_of(Activity *activity)
{
    return (ActivityCard *) (void *) &activity->unk_a0;
}

/* The results of checking copy 0 (bits 4-7) and copy 1 (bits 0-3), at 0x10d. */
static u8 *copy_results(Activity *activity)
{
    return &activity->unk_10b[2];
}

static void set_low_nibble(u8 *byte, int value)
{
    *byte = (u8) ((*byte & ~NIBBLE) | (value & NIBBLE));
}

static void set_high_nibble(u8 *byte, int value)
{
    *byte = (u8) ((*byte & ~(NIBBLE << 4)) | ((value & NIBBLE) << 4));
}

/* Where a part is kept in memory: the state block for either copy, else the current activity's
 * block of letters (asked for in any case). */
static u8 *part_place(int part, u8 *letters)
{
    return part == CARD_SAVE_LETTERS ? letters : (u8 *) &data_021dc7a8;
}

/* The 16-bit sum of the halfwords of `length` bytes at `data`. */
static u16 sum(u8 *data, int length)
{
    return BackupCard_Sum((unsigned short *) (void *) data, length);
}

/* func_020a1738: copy `copy`'s stamp (the last 4 bytes of a state block) read from the card
 * into `stamp`, synchronously; BackupCard_Read's result. */
int ActivityCard_ReadStamp(int copy, SaveStamp *stamp)
{
    u32 offset = data_020d1c20[copy] + ((u32) (uintptr_t) &data_021f3ba0 - (u32) (uintptr_t) &data_021dc7a8);
    return BackupCard_Read(&data_021c8188, (u32) (uintptr_t) stamp, STAMP_SIZE, offset);
}
CLEAN_AS(func_020a1738, ActivityCard_ReadStamp)

/* func_020a1768: whether reading copy 0's stamp fails (the title's menu, overlay 147, asks). */
int ActivityCard_Copy0StampUnreadable(void)
{
    return ActivityCard_StampUnreadable(CARD_SAVE_COPY_0);
}
CLEAN_AS(func_020a1768, ActivityCard_Copy0StampUnreadable)

/* func_020a1774: whether reading copy `copy`'s stamp fails. */
int ActivityCard_StampUnreadable(int copy)
{
    SaveStamp stamp;
    SaveStamp_Construct(&stamp);
    int failed = ActivityCard_ReadStamp(copy, &stamp) != 0;
    SaveStamp_Destruct(&stamp);
    return failed;
}
CLEAN_AS(func_020a1774, ActivityCard_StampUnreadable)

/* func_020a199c: whether the `length` bytes at `a` and `b` are the same.
 * QUIRK: a negative length counts down until it wraps around to 0, comparing on the way. */
int ActivityCard_SameBytes(const Activity *unused, const u8 *a, const u8 *b, int length)
{
    (void) unused;
    for (; length != 0; length--) {
        if (*a++ != *b++) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020a199c, ActivityCard_SameBytes)

/* func_020a19c0: a step reading part `part` from the card into its place in memory: DONE when
 * its sum is right, else BAD.
 * REQUIRES: `part` is a CardSavePart. */
int ActivityCard_StepReadPart(int unused, int part)
{
    (void) unused;
    u8 *place = part_place(part, Activity_CurrentLetters());
    int status = BackupCard_Status(&data_021c8188);
    u32 offset = data_020d1c20[part];
    u32 length = data_020d1bf0[part];
    if (status == BACKUP_CARD_IDLE) {
        BackupCard_ReadAsync(&data_021c8188, (u32) (uintptr_t) place, length, offset);
    } else if (status == BACKUP_CARD_FAILED) {
        BackupCard_Finish(&data_021c8188);
        return ACTIVITY_CARD_FAILED;
    } else if (status != BACKUP_CARD_BUSY) {
        BackupCard_Finish(&data_021c8188);
        return sum(place, (int) data_020d1c08[part]) == 0 ? ACTIVITY_CARD_DONE : ACTIVITY_CARD_BAD;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a19c0, ActivityCard_StepReadPart)

/* func_020a1a40: a step reading copy `copy` of the state block into `buffer` (cleared first;
 * the boot screen's): DONE when its sum is right and it holds a set-up town
 * (StateBlock_IsSetUp), else BAD.
 * QUIRK: a failed read is checked like one that worked (the request is finished and the buffer
 * checked): ACTIVITY_CARD_FAILED is never given.
 * REQUIRES: `copy` is a CardSavePart. */
int ActivityCard_StepReadCopy(int copy, void *buffer)
{
    int status = BackupCard_Status(&data_021c8188);
    u32 offset = data_020d1c20[copy];
    u32 length = data_020d1bf0[copy];
    if (status == BACKUP_CARD_IDLE) {
        MI_CpuFill8(buffer, 0, length);
        BackupCard_ReadAsync(&data_021c8188, (u32) (uintptr_t) buffer, length, offset);
        return ACTIVITY_CARD_BUSY;
    }
    if (status == BACKUP_CARD_BUSY) {
        return ACTIVITY_CARD_BUSY;
    }
    BackupCard_Finish(&data_021c8188);
    u16 total = sum(buffer, (int) data_020d1c08[copy]);
    if (StateBlock_IsSetUp(buffer) == 0) {
        return ACTIVITY_CARD_BAD;
    }
    return total == 0 ? ACTIVITY_CARD_DONE : ACTIVITY_CARD_BAD;
}
CLEAN_AS(func_020a1a40, ActivityCard_StepReadCopy)

/* func_020a1acc: a step reading copy `copy` into the activity's card buffer (cleared first):
 * DONE when it holds a set-up town and its sum is right, else BAD.
 * QUIRK: a failed read is checked like one that worked: ACTIVITY_CARD_FAILED is never given.
 * QUIRK: the set-up marker is looked at in the current activity's card buffer, the sum in
 * `activity`'s (the same buffer when `activity` is the current one).
 * REQUIRES: `copy` is a CardSavePart; once the read ended, there is a current activity. */
int ActivityCard_StepReadCopyToCard(Activity *activity, int copy)
{
    ActivityCard *card = card_of(activity);
    int status = BackupCard_Status(&data_021c8188);
    u32 offset = data_020d1c20[copy];
    u32 length = data_020d1bf0[copy];
    if (status == BACKUP_CARD_IDLE) {
        MI_CpuFill8(card->card, 0, length);
        BackupCard_ReadAsync(&data_021c8188, (u32) (uintptr_t) card->card, length, offset);
        return ACTIVITY_CARD_BUSY;
    }
    if (status == BACKUP_CARD_BUSY) {
        return ACTIVITY_CARD_BUSY;
    }
    BackupCard_Finish(&data_021c8188);
    if (StateBlock_IsSetUp((StateBlock *) (void *) card_of(data_021f3c3c)->card) == 0) {
        return ACTIVITY_CARD_BAD;
    }
    return sum(card->card, (int) data_020d1c08[copy]) == 0 ? ACTIVITY_CARD_DONE : ACTIVITY_CARD_BAD;
}
CLEAN_AS(func_020a1acc, ActivityCard_StepReadCopyToCard)

/* func_020a1b68: part `part` read from the card synchronously into its place in memory, or with
 * `into_image` (for a copy) into the current activity's image; whether that failed (also when
 * there is no current activity then).
 * REQUIRES: `part` is a CardSavePart. */
int ActivityCard_ReadPart(unsigned int part, int into_image)
{
    u8 *place = part_place((int) part, Activity_CurrentLetters());
    u32 offset = data_020d1c20[part];
    u32 length = data_020d1bf0[part];
    if (into_image != 0 && part <= CARD_SAVE_COPY_1) {
        if (data_021f3c3c == NULL) {
            return 1;
        }
        place = card_of(data_021f3c3c)->image;
    }
    return BackupCard_Read(&data_021c8188, (u32) (uintptr_t) place, length, offset) != BACKUP_CARD_OK;
}
CLEAN_AS(func_020a1b68, ActivityCard_ReadPart)

/* func_020a1bd0: part `part` read into its place in memory (the activity loads the letters
 * this way when it is made). */
void ActivityCard_LoadPart(int part)
{
    ActivityCard_ReadPart((unsigned int) part, 0);
}
CLEAN_AS(func_020a1bd0, ActivityCard_LoadPart)

/* func_020a1bdc: copy `copy` of the state block read synchronously into the state block, or with
 * `into_image` into the current activity's image, and checked: FAILED when the read failed (or
 * there is no current activity for `into_image`), BAD when the block's sum is wrong or it holds
 * no set-up town, else DONE.
 * QUIRK: the sums of the exchange block and of each town player's Wi-Fi account and friend
 * roster are worked out after that and not looked at. */
int ActivityCard_ReadAndCheckCopy(int copy, int into_image)
{
    if (into_image != 0 && data_021f3c3c == NULL) {
        return ACTIVITY_CARD_FAILED;
    }
    int result = ActivityCard_ReadPart((unsigned int) copy, into_image);
    if (result != 0) {
        return result;
    }
    u8 *block = into_image != 0 ? card_of(data_021f3c3c)->image : (u8 *) &data_021dc7a8;
    u16 total = sum(block, STATE_BLOCK_SIZE);
    if (StateBlock_IsSetUp((StateBlock *) (void *) block) == 0) {
        return ACTIVITY_CARD_BAD;
    }
    if (total != 0) {
        return ACTIVITY_CARD_BAD;
    }
    sum(block + offsetof(StateBlock, part_11c70), EXCHANGE_BLOCK_SIZE);
    u8 *players = block + offsetof(StateBlock, players);
    for (int player = 0; player < PLAYER_RECORDS_TOWN; player++) {
        sum((u8 *) PlayerRecord_WifiAccount(PlayerRecords_TownRecord(players, player)), ACCOUNT_SIZE);
        sum((u8 *) PlayerRecord_WifiFriends(PlayerRecords_TownRecord(players, player)), FRIEND_ROSTER_SIZE);
    }
    return result;
}
CLEAN_AS(func_020a1bdc, ActivityCard_ReadAndCheckCopy)

/* func_020a1c90: copy `copy` read into the state block and checked. */
int ActivityCard_LoadAndCheckCopy(int copy)
{
    return ActivityCard_ReadAndCheckCopy(copy, 0);
}
CLEAN_AS(func_020a1c90, ActivityCard_LoadAndCheckCopy)

/* func_020a1c9c: the save loaded into the state block: both copies read and checked, then the
 * one to use read again: the good one, or with both good copy 1 when their serials are the
 * same (CardSave_SameSerial), else copy 0. FAILED when a read failed, BAD when both copies are
 * bad (the state block then holds copy 1 as read), else DONE. */
int ActivityCard_LoadSave(void)
{
    int first = ActivityCard_LoadAndCheckCopy(CARD_SAVE_COPY_0);
    int second = ActivityCard_LoadAndCheckCopy(CARD_SAVE_COPY_1);
    if (first == ACTIVITY_CARD_FAILED || second == ACTIVITY_CARD_FAILED) {
        return ACTIVITY_CARD_FAILED;
    }
    if (first != ACTIVITY_CARD_DONE && second != ACTIVITY_CARD_DONE) {
        return ACTIVITY_CARD_BAD;
    }
    if (first != ACTIVITY_CARD_DONE) {
        ActivityCard_LoadPart(CARD_SAVE_COPY_1);
    } else if (second != ACTIVITY_CARD_DONE) {
        ActivityCard_LoadPart(CARD_SAVE_COPY_0);
    } else {
        ActivityCard_LoadPart(CardSave_SameSerial());
    }
    return ACTIVITY_CARD_DONE;
}
CLEAN_AS(func_020a1c9c, ActivityCard_LoadSave)

/* func_020a1cec: a step erasing part `part` on the card: the activity's image filled with 0xff
 * for the part's length and written there. */
int ActivityCard_StepErasePart(Activity *activity, int part)
{
    ActivityCard *card = card_of(activity);
    int status = BackupCard_Status(&data_021c8188);
    u32 offset = data_020d1c20[part];
    u32 length = data_020d1bf0[part];
    if (status == BACKUP_CARD_FAILED) {
        BackupCard_Finish(&data_021c8188);
        return ACTIVITY_CARD_FAILED;
    }
    if (status == BACKUP_CARD_IDLE) {
        MI_CpuFill8(card->image, ERASED, length);
        BackupCard_WriteAsync(&data_021c8188, (int) offset, card->image, (int) length);
    } else if (status != BACKUP_CARD_BUSY) {
        BackupCard_Finish(&data_021c8188);
        return ACTIVITY_CARD_DONE;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a1cec, ActivityCard_StepErasePart)

/* func_020a1d54: the last step of a write: the image, with its new sums, copied back to the
 * part's place in memory. */
int ActivityCard_WriteStepCopyOut(Activity *activity, int part)
{
    ActivityCard *card = card_of(activity);
    u8 *place = part_place(part, Activity_CurrentLetters());
    MI_CpuCopy8(card->image, place, data_020d1c08[part]);
    card->write_step = ACTIVITY_CARD_WRITE_END;
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a1d54, ActivityCard_WriteStepCopyOut)

/* func_020a1d94: a step of a write: the run of differing blocks written from the image; once
 * done the run is reset and the comparison goes on. A failed write gives FAILED. */
int ActivityCard_WriteStepRun(Activity *activity, int part)
{
    ActivityCard *card = card_of(activity);
    int status = BackupCard_Status(&data_021c8188);
    u32 offset = data_020d1c20[part];
    if (status == BACKUP_CARD_FAILED) {
        BackupCard_Finish(&data_021c8188);
        return ACTIVITY_CARD_FAILED;
    }
    if (status == BACKUP_CARD_IDLE) {
        int start = card->run_start * ACTIVITY_CARD_BLOCK;
        const void *from = (const void *) (uintptr_t) ((u32) (uintptr_t) card->image + (u32) start);
        BackupCard_WriteAsync(&data_021c8188, start + (int) offset, from, (int) card->run_length);
    } else if (status != BACKUP_CARD_BUSY) {
        BackupCard_Finish(&data_021c8188);
        card->run_start = -1;
        card->run_length = 0;
        card->write_step = ACTIVITY_CARD_WRITE_COMPARE;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a1d94, ActivityCard_WriteStepRun)

/* func_020a1e08: a step of a write: the image compared with what the card holds, a block at a
 * time from ActivityCard.block. Differing blocks make a run; it is written (to
 * ACTIVITY_CARD_WRITE_RUN) when a block that is the same follows it, or with the last block.
 * Once every block is compared, ACTIVITY_CARD_WRITE_COPY_OUT. The last block is the length's
 * remainder (it is compared, with 0 bytes, also when there is none). */
int ActivityCard_WriteStepCompare(Activity *activity, int part)
{
    ActivityCard *card = card_of(activity);
    s32 length = (s32) data_020d1bf0[part];
    s32 last = length / ACTIVITY_CARD_BLOCK;
    s32 rest = length % ACTIVITY_CARD_BLOCK;
    while (card->block <= last) {
        s32 size = card->block == last ? rest : ACTIVITY_CARD_BLOCK;
        s32 at = card->block * ACTIVITY_CARD_BLOCK;
        if (ActivityCard_SameBytes(activity, card->image + at, card->card + at, size) == 0) {
            if (card->run_start == -1) {
                card->run_start = card->block;
            }
            card->run_length += (u32) size;
            if (card->block == last) {
                card->write_step = ACTIVITY_CARD_WRITE_RUN;
                card->block++;
                return ACTIVITY_CARD_BUSY;
            }
        } else if (card->run_length != 0) {
            card->write_step = ACTIVITY_CARD_WRITE_RUN;
            return ACTIVITY_CARD_BUSY;
        }
        card->block++;
    }
    if (card->block > last) {
        card->write_step = ACTIVITY_CARD_WRITE_COPY_OUT;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a1e08, ActivityCard_WriteStepCompare)

/* func_020a1ee0: a step of a write: the part as the card holds it read into the card buffer
 * (cleared first); then ACTIVITY_CARD_WRITE_COMPARE. A failed read gives FAILED. */
int ActivityCard_WriteStepReadBack(Activity *activity, int part)
{
    ActivityCard *card = card_of(activity);
    int status = BackupCard_Status(&data_021c8188);
    u32 offset = data_020d1c20[part];
    u32 length = data_020d1bf0[part];
    if (status == BACKUP_CARD_FAILED) {
        BackupCard_Finish(&data_021c8188);
        return ACTIVITY_CARD_FAILED;
    }
    if (status == BACKUP_CARD_IDLE) {
        MI_CpuFill8(card->card, 0, length);
        BackupCard_ReadAsync(&data_021c8188, (u32) (uintptr_t) card->card, length, offset);
    } else if (status != BACKUP_CARD_BUSY) {
        BackupCard_Finish(&data_021c8188);
        card->write_step = ACTIVITY_CARD_WRITE_COMPARE;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a1ee0, ActivityCard_WriteStepReadBack)

/* The value that brings the halfword sum of `length` bytes at `data` to `total`. */
static u16 checksum(u8 *data, int length, u16 total)
{
    return BackupCard_Checksum((const u16 *) (void *) data, length, total);
}

/* func_020a1f4c: a step of a write: the image's sums set. For the letters, the halfword at
 * 0xc802. For a copy of the state block: first a new serial for copy 0; for copy 1, copy 0 is
 * read and checked into the card buffer (staying in this step while that is under way) and,
 * when it is good, its stamp read from the card and its serial taken. Then the checksums of
 * the exchange block, the part at 0x1704c, each town player's Wi-Fi account and friend roster,
 * and last the stamp's, for the whole block.
 * QUIRK: the block's sum is worked out twice more at the end and not looked at; the result of
 * reading copy 0's stamp is not looked at either. */
int ActivityCard_WriteStepSums(Activity *activity, int part)
{
    ActivityCard *card = card_of(activity);
    if (part == CARD_SAVE_LETTERS) {
        u8 *letters = card->image;
        u16 *total = (u16 *) (void *) (letters + LETTERS_CHECKSUM);
        *total = checksum(letters, LETTERS_SIZE, *total);
    } else {
        int copy_0 = ACTIVITY_CARD_DONE;
        if (part == CARD_SAVE_COPY_1) {
            copy_0 = ActivityCard_StepReadCopyToCard(activity, CARD_SAVE_COPY_0);
        }
        if (copy_0 == ACTIVITY_CARD_BUSY) {
            return ACTIVITY_CARD_BUSY;
        }
        if (copy_0 == ACTIVITY_CARD_FAILED) {
            return ACTIVITY_CARD_FAILED;
        }
        u8 *block = card->image;
        SaveStamp *stamp = (SaveStamp *) (void *) (block + offsetof(StateBlock, part_173f8));
        if (part == CARD_SAVE_COPY_0) {
            SaveStamp_NewSerial(stamp);
        } else if (copy_0 == ACTIVITY_CARD_DONE) {
            SaveStamp read;
            SaveStamp_Construct(&read);
            ActivityCard_ReadStamp(CARD_SAVE_COPY_0, &read);
            SaveStamp_SetSerial(stamp, SaveStamp_Serial(&read));
            SaveStamp_Destruct(&read);
        }
        u8 *exchange = block + offsetof(StateBlock, part_11c70);
        func_02090168(exchange, checksum(exchange, EXCHANGE_BLOCK_SIZE, func_0209015c(exchange)));
        u8 *part_1704c = block + offsetof(StateBlock, part_1704c);
        func_0208fff4(part_1704c, (u8) checksum(part_1704c, PART_1704C_SIZE, func_0208ffe8(part_1704c)));
        u8 *players = block + offsetof(StateBlock, players);
        for (int player = 0; player < PLAYER_RECORDS_TOWN; player++) {
            WifiAccount *account = PlayerRecord_WifiAccount(PlayerRecords_TownRecord(players, player));
            WifiAccount_SetChecksum(account, checksum((u8 *) account, ACCOUNT_SIZE, WifiAccount_GetChecksum(account)));
            WifiFriendList *roster = PlayerRecord_WifiFriends(PlayerRecords_TownRecord(players, player));
            WifiFriendList_SetChecksum(roster,
                                       checksum((u8 *) roster, FRIEND_ROSTER_SIZE, WifiFriendList_GetChecksum(roster)));
        }
        SaveStamp_SetChecksum(stamp, checksum(block, STATE_BLOCK_SIZE, (u16) SaveStamp_Checksum(stamp)));
        sum(block, STATE_BLOCK_SIZE);
        sum(block, STATE_BLOCK_SIZE);
    }
    card->write_step = ACTIVITY_CARD_WRITE_READ_BACK;
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a1f4c, ActivityCard_WriteStepSums)

/* func_020a20b4: the first step of a write: the image cleared for the part's length, the part
 * copied into it, the comparison reset to block 0 with no run. */
int ActivityCard_WriteStepCopyIn(Activity *activity, int part)
{
    ActivityCard *card = card_of(activity);
    u8 *place = part_place(part, Activity_CurrentLetters());
    MI_CpuFill8(card->image, 0, data_020d1bf0[part]);
    MI_CpuCopy8(place, card->image, data_020d1c08[part]);
    card->block = 0;
    card->run_start = -1;
    card->run_length = 0;
    card->write_step = ACTIVITY_CARD_WRITE_SUMS;
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a20b4, ActivityCard_WriteStepCopyIn)

/* Calls a step through its member pointer, with `part` when it takes one. */
static int call_step(const MemberPointer *step, Activity *activity, int part)
{
    void *self = MemberPointer_Object(step, activity);
    return ((int (*)(void *, int))(uintptr_t) MemberPointer_Code(step, self))(self, part);
}

/* func_020a2120: part `part` written to the card (activity_card.h), one step a call through the
 * table of steps (ActivityCard_WriteStep*): BUSY while under way, FAILED when a card request
 * failed (the step is kept), DONE at the end, when the step is reset. */
int ActivityCard_StepWritePart(Activity *activity, int part)
{
    static const MemberPointer *const constants[7] = {
        &data_020e38a8, &data_020e3918, &data_020e3930, &data_020e3968, &data_020e39d8, &data_020e3a60, &__ptmf_null,
    };
    MemberTable_InitOnce(&data_021f3c2c, data_021f3c84, constants, 7);
    ActivityCard *card = card_of(activity);
    int result = ACTIVITY_CARD_BUSY;
    const MemberPointer *step = &data_021f3c84[card->write_step];
    if (step->function != 0) {
        result = call_step(step, activity, part);
    }
    if (card->write_step == ACTIVITY_CARD_WRITE_END) {
        card->write_step = ACTIVITY_CARD_WRITE_COPY_IN;
        return ACTIVITY_CARD_DONE;
    }
    return result;
}
CLEAN_AS(func_020a2120, ActivityCard_StepWritePart)

/* func_020a21ec: the last step of the check: the part to read and the part to write chosen
 * from the copies' results (Activity.card_parts: read in bits 0-3, write in bits 4-7). With
 * copy 0 bad, copy 1 is read and copy 0 written, and the other way round with copy 1 bad.
 * With both bad the same, and the check gives BAD; with both good copy 1 is read when their
 * serials are the same (CardSave_SameSerial), else copy 0, and the other one written.
 * FAILED when a read failed (which ActivityCard_StepReadCopyToCard never reports). */
int ActivityCard_CheckStepChoose(Activity *activity)
{
    u8 results = *copy_results(activity);
    int copy_1 = results & NIBBLE;
    int copy_0 = results >> 4;
    u8 *parts = &activity->card_parts;
    int result = ACTIVITY_CARD_DONE;
    if (copy_1 == ACTIVITY_CARD_FAILED || copy_0 == ACTIVITY_CARD_FAILED) {
        result = ACTIVITY_CARD_FAILED;
    } else if (copy_0 != ACTIVITY_CARD_DONE && copy_1 != ACTIVITY_CARD_DONE) {
        set_low_nibble(parts, CARD_SAVE_COPY_1);
        set_high_nibble(parts, CARD_SAVE_COPY_0);
        result = ACTIVITY_CARD_BAD;
    } else if (copy_0 != ACTIVITY_CARD_DONE) {
        set_low_nibble(parts, CARD_SAVE_COPY_1);
        set_high_nibble(parts, CARD_SAVE_COPY_0);
    } else if (copy_1 != ACTIVITY_CARD_DONE) {
        set_low_nibble(parts, CARD_SAVE_COPY_0);
        set_high_nibble(parts, CARD_SAVE_COPY_1);
    } else {
        set_low_nibble(parts, CardSave_SameSerial());
        if ((*parts & NIBBLE) == CARD_SAVE_COPY_1) {
            set_high_nibble(parts, CARD_SAVE_COPY_0);
        } else {
            set_high_nibble(parts, CARD_SAVE_COPY_1);
        }
    }
    card_of(activity)->write_step = ACTIVITY_CARD_CHECK_END;
    return result;
}
CLEAN_AS(func_020a21ec, ActivityCard_CheckStepChoose)

/* func_020a22b8: a step of the check: copy 1 read and checked; its result kept (bits 0-3 at
 * 0x10d), and once it is not BUSY the next step. */
int ActivityCard_CheckStepCopy1(Activity *activity)
{
    set_low_nibble(copy_results(activity), ActivityCard_StepReadCopyToCard(activity, CARD_SAVE_COPY_1));
    if ((*copy_results(activity) & NIBBLE) != ACTIVITY_CARD_BUSY) {
        card_of(activity)->write_step++;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a22b8, ActivityCard_CheckStepCopy1)

/* func_020a22f8: a step of the check: copy 0 read and checked; its result kept (bits 4-7 at
 * 0x10d), and once it is not BUSY the next step. */
int ActivityCard_CheckStepCopy0(Activity *activity)
{
    set_high_nibble(copy_results(activity), ActivityCard_StepReadCopyToCard(activity, CARD_SAVE_COPY_0));
    if ((*copy_results(activity) >> 4) != ACTIVITY_CARD_BUSY) {
        card_of(activity)->write_step++;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a22f8, ActivityCard_CheckStepCopy0)

/* func_020a233c: the first step of the check: both copies' results set to BUSY and both parts
 * of Activity.card_parts to NO_PART. */
int ActivityCard_CheckStepStart(Activity *activity)
{
    u8 *results = copy_results(activity);
    set_high_nibble(results, ACTIVITY_CARD_BUSY);
    set_low_nibble(results, ACTIVITY_CARD_BUSY);
    set_low_nibble(&activity->card_parts, NO_PART);
    set_high_nibble(&activity->card_parts, NO_PART);
    card_of(activity)->write_step++;
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a233c, ActivityCard_CheckStepStart)

/* func_020a238c: the card checked (activity_card.h), one step a call through the table of
 * steps (ActivityCard_CheckStep*): BUSY while under way, else the last step's result, when the
 * step is reset. */
int ActivityCard_StepCheck(Activity *activity)
{
    static const MemberPointer *const constants[4] = {
        &data_020e3828,
        &data_020e3838,
        &data_020e38f0,
        &data_020e3868,
    };
    MemberTable_InitOnce(&data_021f3c28, data_021f3c64, constants, 4);
    ActivityCard *card = card_of(activity);
    int result = 0;
    const MemberPointer *step = &data_021f3c64[card->write_step];
    if (step->function != 0) {
        result = MemberPointer_CallInt(step, activity);
    }
    if (result != ACTIVITY_CARD_BUSY) {
        card->write_step = ACTIVITY_CARD_CHECK_START;
        return result;
    }
    return ACTIVITY_CARD_BUSY;
}
CLEAN_AS(func_020a238c, ActivityCard_StepCheck)

/* This system's exchange block. */
extern u8 data_021ee418[EXCHANGE_BLOCK_SIZE];
/* The exchange block's count (at its 0x938) raised by 1, to 5 at most. */
extern void func_0209010c(u8 *block);
/* The record number used for a guest's (7, which no record has). */
extern const u8 data_020e37f8;

#define PLAYER_RECORD_SIZE 0x249c

/* func_020a2468: the activity's exchange block copied to this system's. */
void Activity_ExchangeBlockToSystem(Activity *activity)
{
    MI_CpuCopy8(activity->exchange_block, data_021ee418, EXCHANGE_BLOCK_SIZE);
}
CLEAN_AS(func_020a2468, Activity_ExchangeBlockToSystem)

/* func_020a2480: this system's exchange block counted once more and copied to the activity's. */
void Activity_SystemExchangeBlockToActivity(Activity *activity)
{
    u8 *block = data_021ee418;
    func_0209010c(block);
    MI_CpuCopy8(block, activity->exchange_block, EXCHANGE_BLOCK_SIZE);
}
CLEAN_AS(func_020a2480, Activity_SystemExchangeBlockToActivity)

/* func_020a24ac: this system's player record copied to record data_020e37f8 (7); the activity
 * is not read. */
void Activity_CurrentRecordToGuest(Activity *activity)
{
    (void) activity;
    u8 *record = PlayerRecords_Current();
    MI_CpuCopy8(record, PlayerRecords_Get(data_020e37f8), PLAYER_RECORD_SIZE);
}
CLEAN_AS(func_020a24ac, Activity_CurrentRecordToGuest)
