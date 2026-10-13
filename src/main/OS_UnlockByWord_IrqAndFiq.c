/* OS_UnlockByWord_IrqAndFiq @ 0x0203cd1c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct OSLockWord OSLockWord;

extern s32 OSi_DoUnlockByWord__main_0203cd2c(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp)(void), BOOL disableFIQ);

s32 OS_UnlockByWord_IrqAndFiq(u16 lockID, OSLockWord *lockp, void (*ctrlFuncp)(void))
{
    return OSi_DoUnlockByWord__main_0203cd2c(lockID, lockp, ctrlFuncp, TRUE);
}
