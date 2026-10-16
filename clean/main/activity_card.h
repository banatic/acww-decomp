/* The save on the game card as the activity process (activity.h) and the boot screen read and
 * write it: the parts of card_save.h (CardSavePart: copy 0 and copy 1 of the state block, the
 * block of letters), at the offsets of data_020d1c20, data_020d1bf0 bytes long, of which the
 * first data_020d1c08 bytes are covered by the part's 16-bit halfword sum (0 when good).
 *
 * Most functions here are steps, called once a frame through the game's one record of the save
 * memory (backup_card.h): one that finds no request under way starts its asynchronous read or
 * write and gives ACTIVITY_CARD_BUSY, as it does while the request runs; once it ended the
 * request is finished and the step gives its result.
 *
 * The activity keeps two buffers for the card, each the size of the state block:
 * ActivityCard.image (Activity at 0xb0) for the part as it is to be on the card, and
 * ActivityCard.card (0xb4) for the part as it was read from the card.
 *
 * A part is written in the steps of ActivityCard_StepWritePart (ActivityCard.write_step):
 * the part copied into the image, its sums set (for a copy of the state block: a new serial
 * for copy 0, copy 0's serial for copy 1 when copy 0 is good), the part read back from the
 * card, then the image compared with what was read in 0x200-byte blocks, each run of differing
 * blocks written, and at last the image copied back to the part (with its new sums).
 *
 * The card is checked in the steps of ActivityCard_StepCheck: both copies read and checked into
 * the card buffer, their results kept in ActivityCard.copy_results, and the part to read and the
 * part to write chosen into Activity.card_parts (activity_save.h). */
#ifndef CLEAN_MAIN_ACTIVITY_CARD_H
#define CLEAN_MAIN_ACTIVITY_CARD_H

#include "activity.h"
#include "save_stamp.h"
#include "types.h"

/* What the steps give. */
enum ActivityCardResult {
    ACTIVITY_CARD_DONE = 0,
    ACTIVITY_CARD_FAILED = 1, /* the card request failed */
    ACTIVITY_CARD_BUSY = 3,   /* under way: call again */
    ACTIVITY_CARD_BAD = 4,    /* read, but its sum or its set-up marker is wrong */
};

/* ActivityCard.write_step. */
enum ActivityCardWriteStep {
    ACTIVITY_CARD_WRITE_COPY_IN = 0,
    ACTIVITY_CARD_WRITE_SUMS = 1,
    ACTIVITY_CARD_WRITE_READ_BACK = 2,
    ACTIVITY_CARD_WRITE_COMPARE = 3,
    ACTIVITY_CARD_WRITE_RUN = 4,
    ACTIVITY_CARD_WRITE_COPY_OUT = 5,
    ACTIVITY_CARD_WRITE_END = 6,
};

/* ActivityCard.write_step while the card is checked. */
enum ActivityCardCheckStep {
    ACTIVITY_CARD_CHECK_START = 0,
    ACTIVITY_CARD_CHECK_COPY_0 = 1,
    ACTIVITY_CARD_CHECK_COPY_1 = 2,
    ACTIVITY_CARD_CHECK_CHOOSE = 3,
    ACTIVITY_CARD_CHECK_END = 6,
};

#define ACTIVITY_CARD_BLOCK 0x200 /* the size of the blocks compared and written */

/* The activity's fields for the card, from Activity.unk_a0 (the step) on. */
typedef struct ActivityCard {
    u8 write_step; /* 0xa0: ActivityCardWriteStep or ActivityCardCheckStep */
    u8 unk_a1;     /* 0xa1: Activity.state */
    u8 block;      /* 0xa2: the next block to compare */
    u8 unk_a3;
    s16 run_start; /* 0xa4: the first block of the run of differing blocks, -1 for none */
    u8 unk_a6[2];
    u32 run_length; /* 0xa8: the bytes in that run */
    u8 unk_ac[4];
    u8 *image; /* 0xb0 */
    u8 *card;  /* 0xb4 */
} ActivityCard;

int ActivityCard_ReadStamp(int copy, SaveStamp *stamp);
int ActivityCard_Copy0StampUnreadable(void);
int ActivityCard_StampUnreadable(int copy);
int ActivityCard_SameBytes(const Activity *unused, const u8 *a, const u8 *b, int length);
int ActivityCard_StepReadPart(int unused, int part);
int ActivityCard_StepReadCopy(int copy, void *buffer);
int ActivityCard_StepReadCopyToCard(Activity *activity, int copy);
int ActivityCard_ReadPart(unsigned int part, int into_image);
void ActivityCard_LoadPart(int part);
int ActivityCard_ReadAndCheckCopy(int copy, int into_image);
int ActivityCard_LoadAndCheckCopy(int copy);
int ActivityCard_LoadSave(void);
int ActivityCard_StepErasePart(Activity *activity, int part);
int ActivityCard_WriteStepCopyOut(Activity *activity, int part);
int ActivityCard_WriteStepRun(Activity *activity, int part);
int ActivityCard_WriteStepCompare(Activity *activity, int part);
int ActivityCard_WriteStepReadBack(Activity *activity, int part);
int ActivityCard_WriteStepSums(Activity *activity, int part);
int ActivityCard_WriteStepCopyIn(Activity *activity, int part);
int ActivityCard_StepWritePart(Activity *activity, int part);
int ActivityCard_CheckStepChoose(Activity *activity);
int ActivityCard_CheckStepCopy1(Activity *activity);
int ActivityCard_CheckStepCopy0(Activity *activity);
int ActivityCard_CheckStepStart(Activity *activity);
int ActivityCard_StepCheck(Activity *activity);

#endif
