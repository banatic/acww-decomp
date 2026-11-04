/* The town's mystery cat record, Blanca's face (mystery_cat_record.h). */
#include "mystery_cat_record.h"

#include "clean.h"
#include "state_block.h"

static_assert(offsetof(MysteryCatRecord, checksum) == 0x234 && offsetof(MysteryCatRecord, status) == 0x236, "record");
static_assert(sizeof(MysteryCatRecord) == MYSTERY_CAT_RECORD_SIZE, "record");

/* The state block flag that keeps the record from being used. */
#define MYSTERY_CAT_RECORD_STATE_FLAG_13 0x13

extern u32 data_021dc7a8[]; /* the state block (state_block.h) */

/* func_020881ac */
u16 MysteryCatRecord_Checksum(const MysteryCatRecord *record)
{
    return record->checksum;
}
CLEAN_AS(func_020881ac, MysteryCatRecord_Checksum)

/* func_020881b8 */
void MysteryCatRecord_SetChecksum(MysteryCatRecord *record, u16 checksum)
{
    record->checksum = checksum;
}
CLEAN_AS(func_020881b8, MysteryCatRecord_SetChecksum)

/* func_020881c4: whether the record is in use (status 2) while the state block's flag 0x13 is
 * clear; the flag is asked first. */
int MysteryCatRecord_IsInUse(const MysteryCatRecord *record)
{
    return StateBlock_TestFlag(data_021dc7a8, MYSTERY_CAT_RECORD_STATE_FLAG_13) == 0 &&
           record->status == MYSTERY_CAT_RECORD_IN_USE;
}
CLEAN_AS(func_020881c4, MysteryCatRecord_IsInUse)

/* func_020881f0 */
u8 MysteryCatRecord_Impression(const MysteryCatRecord *record)
{
    return record->impression;
}
CLEAN_AS(func_020881f0, MysteryCatRecord_Impression)

/* The record's design, blanked when the record is reset. */
#include "design.h"
#include "design_info.h"

static_assert(sizeof(Design) == offsetof(MysteryCatRecord, checksum), "record design");

#define MYSTERY_CAT_RECORD_BLANK_COLOUR 0xf
#define MYSTERY_CAT_RECORD_BLANK_PALETTE 0

/* func_020881fc */
void MysteryCatRecord_SetImpression(MysteryCatRecord *record, u8 value)
{
    record->impression = value;
}
CLEAN_AS(func_020881fc, MysteryCatRecord_SetImpression)

/* func_02088208 */
u8 MysteryCatRecord_Status(const MysteryCatRecord *record)
{
    return record->status;
}
CLEAN_AS(func_02088208, MysteryCatRecord_Status)

/* func_02088214 */
void MysteryCatRecord_SetStatus(MysteryCatRecord *record, u8 status)
{
    record->status = status;
}
CLEAN_AS(func_02088214, MysteryCatRecord_SetStatus)

/* func_02088220: the design the record starts with (the record itself). */
Design *MysteryCatRecord_Design(MysteryCatRecord *record)
{
    return (Design *) (void *) record;
}
CLEAN_AS(func_02088220, MysteryCatRecord_Design)

/* func_02088224: the design blanked: every pixel colour 15, then palette 0. The design is
 * asked for once for each. */
void MysteryCatRecord_ClearDesign(MysteryCatRecord *record)
{
    Design_Fill((unsigned int *) (void *) MysteryCatRecord_Design(record)->pixels, MYSTERY_CAT_RECORD_BLANK_COLOUR);
    Design *design = MysteryCatRecord_Design(record);
    DesignInfo_SetPalette((DesignInfo *) (uintptr_t) Design_Info((unsigned int) (uintptr_t) design),
                          MYSTERY_CAT_RECORD_BLANK_PALETTE);
}
CLEAN_AS(func_02088224, MysteryCatRecord_ClearDesign)

/* func_02088248: the record set up: reset. */
void MysteryCatRecord_Init(MysteryCatRecord *record)
{
    MysteryCatRecord_Reset(record);
}
CLEAN_AS(func_02088248, MysteryCatRecord_Init)

/* func_02088250: back to MYSTERY_CAT_RECORD_NONE with a blank design. */
void MysteryCatRecord_Reset(MysteryCatRecord *record)
{
    record->status = MYSTERY_CAT_RECORD_NONE;
    MysteryCatRecord_ClearDesign(record);
}
CLEAN_AS(func_02088250, MysteryCatRecord_Reset)

/* func_02088264: destructs the record's design. */
MysteryCatRecord *MysteryCatRecord_Destruct(MysteryCatRecord *record)
{
    Design_Destruct((Design *) (void *) record);
    return record;
}
CLEAN_AS(func_02088264, MysteryCatRecord_Destruct)

/* func_02088274: constructs the record's design. */
MysteryCatRecord *MysteryCatRecord_Construct(MysteryCatRecord *record)
{
    Design_Construct((char *) record);
    return record;
}
CLEAN_AS(func_02088274, MysteryCatRecord_Construct)
