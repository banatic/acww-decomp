/* The state block's save stamp (save_stamp.h). */
#include "save_stamp.h"

#include "clean.h"
#include "main_random.h"

static_assert(sizeof(SaveStamp) == 4 && offsetof(SaveStamp, serial) == 3, "a save stamp");

/* Set by SaveStamp_SetLostFlag; nothing in the game reads it. */
extern char data_021f3c10;

#define SERIAL_RANGE 0xff

/* func_0209faec */
int SaveStamp_Checksum(SaveStamp *stamp)
{
    return stamp->checksum;
}
CLEAN_AS(func_0209faec, SaveStamp_Checksum)

/* func_0209faf0 */
void SaveStamp_SetChecksum(SaveStamp *stamp, int checksum)
{
    stamp->checksum = (u16) checksum;
}
CLEAN_AS(func_0209faf0, SaveStamp_SetChecksum)

/* func_0209faf4 */
int SaveStamp_Serial(SaveStamp *stamp)
{
    return stamp->serial;
}
CLEAN_AS(func_0209faf4, SaveStamp_Serial)

/* func_0209faf8 */
void SaveStamp_SetSerial(SaveStamp *stamp, int serial)
{
    stamp->serial = (u8) serial;
}
CLEAN_AS(func_0209faf8, SaveStamp_SetSerial)

/* func_0209fafc: a new random serial, never the one it had. When the draw gives the old one
 * it is stepped up by one (down from 0xff, which the draw below 0xff never gives). */
void SaveStamp_NewSerial(SaveStamp *stamp)
{
    u8 old = stamp->serial;
    stamp->serial = (u8) MainRandom_Below(SERIAL_RANGE);
    if (stamp->serial == old) {
        if (stamp->serial < 0xff) {
            stamp->serial++;
        } else {
            stamp->serial--;
        }
    }
}
CLEAN_AS(func_0209fafc, SaveStamp_NewSerial)

/* func_0209fb28: whether the stamp says neither written nor being written. */
int SaveStamp_HasNoWrite(const SaveStamp *stamp)
{
    return stamp->status != SAVE_STAMP_WRITTEN && stamp->status != SAVE_STAMP_WRITING;
}
CLEAN_AS(func_0209fb28, SaveStamp_HasNoWrite)

/* func_0209fb3c */
int SaveStamp_IsWritten(SaveStamp *stamp)
{
    return stamp->status == SAVE_STAMP_WRITTEN;
}
CLEAN_AS(func_0209fb3c, SaveStamp_IsWritten)

/* func_0209fb4c: by the activity process once the copies are written. */
void SaveStamp_MarkWritten(SaveStamp *stamp)
{
    stamp->status = SAVE_STAMP_WRITTEN;
}
CLEAN_AS(func_0209fb4c, SaveStamp_MarkWritten)

/* func_0209fb54: by the activity process before it writes the copies. */
void SaveStamp_MarkWriting(SaveStamp *stamp)
{
    stamp->status = SAVE_STAMP_WRITING;
}
CLEAN_AS(func_0209fb54, SaveStamp_MarkWriting)

/* func_0209fb5c */
void SaveStamp_Clear(SaveStamp *stamp)
{
    stamp->status = SAVE_STAMP_NONE;
}
CLEAN_AS(func_0209fb5c, SaveStamp_Clear)

/* func_0209fb64: by StateBlock_SetUpTown; the same as SaveStamp_MarkWritten. */
void SaveStamp_MarkTownWritten(SaveStamp *stamp)
{
    stamp->status = SAVE_STAMP_WRITTEN;
}
CLEAN_AS(func_0209fb64, SaveStamp_MarkTownWritten)

/* func_0209fb6c: the destructor; nothing to do. */
void SaveStamp_Destruct(SaveStamp *stamp)
{
    (void) stamp;
}
CLEAN_AS(func_0209fb6c, SaveStamp_Destruct)

/* func_0209fb70: the constructor; nothing to do (a stamp made on the stack to read a card
 * copy's into is left as it was). */
void SaveStamp_Construct(SaveStamp *stamp)
{
    (void) stamp;
}
CLEAN_AS(func_0209fb70, SaveStamp_Construct)

/* func_020a01d4: the boot screen sets 1 when both copies on the card are bad although the
 * state block's stamp says a write began or finished (BootScreen_ApplySave).
 * QUIRK: nothing reads the flag. */
void SaveStamp_SetLostFlag(char value)
{
    data_021f3c10 = value;
}
CLEAN_AS(func_020a01d4, SaveStamp_SetLostFlag)
