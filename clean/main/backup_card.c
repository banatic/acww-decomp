/* The game card's save memory (backup_card.h). */
#include "backup_card.h"

#include "clean.h"

static_assert(sizeof(BackupCard) == 12, "BackupCard size");

/* The game's record of its save memory. */
extern BackupCard data_021c8188;
/* "forest", handed to BackupCard_Init, which does not use it. */
extern const char data_020cb8e8[];

/* NitroSDK's OS and CARD functions. The ones known by address only are, by their use,
 * func_0211ec44 CARD_LockBackup, func_0211ec34 CARD_UnlockBackup, func_0211f23c
 * CARD_IdentifyBackup and func_0211f230 CARD_TryWaitBackupAsync. */
extern int CARD_IsAvailable(void);
extern void CARD_Init(void);
extern int OS_GetLockID(void);
extern void OS_ReleaseLockID(unsigned short lock);
extern void func_0211ec44(unsigned short lock);
extern void func_0211ec34(unsigned short lock);
extern int func_0211f23c(int type);
extern int func_0211f230(void);
extern int CARD_GetBackupTotalSize(void);
extern int CARD_GetResultCode(void);
extern void CARD_CancelBackupAsync(void);
extern u64 OS_GetTick(void);
extern int CARDi_RequestStreamCommand(u32 src, u32 dst, u32 length, void *callback, void *arg, int is_async, int request,
                                      int retries, int mode);

/* CARDi_RequestStreamCommand's requests and modes (NitroSDK's CARDRequest, CARDRequestMode). */
#define CARD_REQ_READ_BACKUP 6
#define CARD_REQ_WRITE_BACKUP 7
#define CARD_REQUEST_MODE_RECV 0
#define CARD_REQUEST_MODE_SEND_VERIFY 2
#define CARD_RETRY_COUNT_MAX 10

/* About 0.1 s in OS ticks (33.514 MHz / 64). */
#define CANCEL_WAIT_TICKS 0xcc8d

/* func_02050b78: the game's record, for save memory of type 0x1202. */
void BackupCard_InitGame(void)
{
    BackupCard_Init(&data_021c8188, BACKUP_CARD_TYPE, data_020cb8e8);
}
CLEAN_AS(func_02050b78, BackupCard_InitGame)

/* func_02050b94: initialises the card library when it is not yet, identifies the save memory
 * as `type` under a lock of its own and keeps its size. `name` is not used.
 * QUIRK: the lock id is used without checking that one was given (BACKUP_CARD_NO_LOCK). */
void BackupCard_Init(BackupCard *card, int type, const void *name)
{
    (void) name;
    if (CARD_IsAvailable() == 0) {
        CARD_Init();
    }
    int lock = OS_GetLockID();
    func_0211ec44((u16) lock);
    func_0211f23c(type);
    card->size = (u32) CARD_GetBackupTotalSize();
    func_0211ec34((u16) lock);
    OS_ReleaseLockID((u16) lock);
    card->unk_08 = 4;
}
CLEAN_AS(func_02050b94, BackupCard_Init)

/* func_02050974: the state of the request under way: BACKUP_CARD_IDLE when no lock is held,
 * BACKUP_CARD_BUSY while it runs, else its result, BACKUP_CARD_OK or BACKUP_CARD_FAILED. */
int BackupCard_Status(BackupCard *card)
{
    if (card->lock == BACKUP_CARD_NO_LOCK) {
        return BACKUP_CARD_IDLE;
    }
    if (func_0211f230() == 0) {
        return BACKUP_CARD_BUSY;
    }
    return CARD_GetResultCode() != 0 ? BACKUP_CARD_FAILED : BACKUP_CARD_OK;
}
CLEAN_AS(func_02050974, BackupCard_Status)

/* func_02050948: ends a request: its lock is given back, when one is held. */
void BackupCard_Finish(BackupCard *card)
{
    if (card->lock == BACKUP_CARD_NO_LOCK) {
        return;
    }
    func_0211ec34((u16) card->lock);
    OS_ReleaseLockID((u16) card->lock);
    card->lock = BACKUP_CARD_NO_LOCK;
}
CLEAN_AS(func_02050948, BackupCard_Finish)

/* func_020508a0: on the way out, a request of the game's record still under way is cancelled
 * and waited for, at most about 0.1 s; then its lock is given back.
 * HW: the wait reads the tick counter.
 * QUIRK: the record keeps the lock id it gave back. */
void BackupCard_Shutdown(void)
{
    if (BackupCard_Status(&data_021c8188) != BACKUP_CARD_BUSY) {
        return;
    }
    u32 start = (u32) OS_GetTick();
    CARD_CancelBackupAsync();
    while (func_0211f230() == 0 && (u32) OS_GetTick() - start < CANCEL_WAIT_TICKS) {
    }
    if (data_021c8188.lock != BACKUP_CARD_NO_LOCK) {
        func_0211ec34((u16) data_021c8188.lock);
        OS_ReleaseLockID((u16) data_021c8188.lock);
    }
}
CLEAN_AS(func_020508a0, BackupCard_Shutdown)

/* Takes a lock for a request and locks the save memory with it; 0 when there is no lock. */
static int take_lock(BackupCard *card)
{
    card->lock = OS_GetLockID();
    if (card->lock == BACKUP_CARD_NO_LOCK) {
        return 0;
    }
    func_0211ec44((u16) card->lock);
    return 1;
}

/* func_020509a8: starts reading `length` bytes at `offset` into `dst`. BACKUP_CARD_BUSY while
 * it runs (BackupCard_Status follows it; BackupCard_Finish ends it); BACKUP_CARD_FAILED when
 * it is out of the save memory, there is no lock, or it ended at once.
 * QUIRK: a read that ended at once is reported as failed, whatever its result. */
int BackupCard_ReadAsync(BackupCard *card, u32 dst, u32 length, u32 offset)
{
    if (offset + length > card->size || !take_lock(card)) {
        return BACKUP_CARD_FAILED;
    }
    CARDi_RequestStreamCommand(offset, dst, length, NULL, NULL, 1, CARD_REQ_READ_BACKUP, 1, CARD_REQUEST_MODE_RECV);
    if (BackupCard_Status(card) == BACKUP_CARD_BUSY) {
        return BACKUP_CARD_BUSY;
    }
    BackupCard_Finish(card);
    return BACKUP_CARD_FAILED;
}
CLEAN_AS(func_020509a8, BackupCard_ReadAsync)

/* func_02050a10: reads `length` bytes at `offset` into `dst` and waits: BACKUP_CARD_OK when
 * that worked, else BACKUP_CARD_FAILED (also when it is out of the save memory or there is no
 * lock). */
int BackupCard_Read(BackupCard *card, u32 dst, u32 length, u32 offset)
{
    if (offset + length > card->size || !take_lock(card)) {
        return BACKUP_CARD_FAILED;
    }
    int result = BACKUP_CARD_FAILED;
    if (CARDi_RequestStreamCommand(offset, dst, length, NULL, NULL, 0, CARD_REQ_READ_BACKUP, 1, CARD_REQUEST_MODE_RECV) != 0) {
        result = BACKUP_CARD_OK;
    }
    func_0211ec34((u16) card->lock);
    OS_ReleaseLockID((u16) card->lock);
    card->lock = BACKUP_CARD_NO_LOCK;
    return result;
}
CLEAN_AS(func_02050a10, BackupCard_Read)

/* func_02050a84: starts writing and verifying `length` bytes of `src` at `offset`, retried up
 * to 10 times; the results are BackupCard_ReadAsync's.
 * QUIRK: a write that ended at once is reported as failed, whatever its result. */
int BackupCard_WriteAsync(BackupCard *card, int offset, const void *src, int length)
{
    if ((u32) offset + (u32) length > card->size || !take_lock(card)) {
        return BACKUP_CARD_FAILED;
    }
    CARDi_RequestStreamCommand((u32) (uintptr_t) src, (u32) offset, (u32) length, NULL, NULL, 1, CARD_REQ_WRITE_BACKUP,
                               CARD_RETRY_COUNT_MAX, CARD_REQUEST_MODE_SEND_VERIFY);
    if (BackupCard_Status(card) == BACKUP_CARD_BUSY) {
        return BACKUP_CARD_BUSY;
    }
    BackupCard_Finish(card);
    return BACKUP_CARD_FAILED;
}
CLEAN_AS(func_02050a84, BackupCard_WriteAsync)

/* func_02050af8: writes and verifies `length` bytes of `src` at `offset` and waits; the
 * results are BackupCard_Read's. */
int BackupCard_Write(BackupCard *card, int offset, const void *src, int length)
{
    if ((u32) offset + (u32) length > card->size || !take_lock(card)) {
        return BACKUP_CARD_FAILED;
    }
    int result = BACKUP_CARD_FAILED;
    if (CARDi_RequestStreamCommand((u32) (uintptr_t) src, (u32) offset, (u32) length, NULL, NULL, 0, CARD_REQ_WRITE_BACKUP,
                                   CARD_RETRY_COUNT_MAX, CARD_REQUEST_MODE_SEND_VERIFY) != 0) {
        result = BACKUP_CARD_OK;
    }
    func_0211ec34((u16) card->lock);
    OS_ReleaseLockID((u16) card->lock);
    card->lock = BACKUP_CARD_NO_LOCK;
    return result;
}
CLEAN_AS(func_02050af8, BackupCard_Write)

/* func_02050920: the 16-bit sum of the halfwords of `length` bytes; 0 for an odd length.
 * QUIRK: a negative even length is stepped down by 2 until it wraps around to 0. */
unsigned short BackupCard_Sum(unsigned short *data, int length)
{
    u16 sum = 0;
    if (length & 1) {
        return 0;
    }
    for (; length != 0; length -= 2) {
        sum = (u16) (sum + *data++);
    }
    return sum;
}
CLEAN_AS(func_02050920, BackupCard_Sum)

/* func_020508fc: the value that brings the 16-bit sum of the block to `total`. */
unsigned short BackupCard_Checksum(const u16 *data, int length, unsigned short total)
{
    return (u16) (total - BackupCard_Sum((unsigned short *) (uintptr_t) data, length));
}
CLEAN_AS(func_020508fc, BackupCard_Checksum)
