/* The game card's save memory (NitroSDK's CARD backup functions): the game's one record of it
 * (data_021c8188) with its size and the lock held while a request is under way, reads and
 * verified writes, synchronous or not, and the 16-bit sums its blocks are checked with.
 *
 * The game identifies its save memory as type 0x1202 (NitroSDK's CARD_BACKUP_TYPE_FLASH_2MBITS:
 * flash, 2^18 bytes). */
#ifndef CLEAN_MAIN_BACKUP_CARD_H
#define CLEAN_MAIN_BACKUP_CARD_H

#include "types.h"

#define BACKUP_CARD_NO_LOCK (-3) /* OS_GetLockID's answer when there is none */
#define BACKUP_CARD_TYPE 0x1202

/* What BackupCard_Status gives, and the requests' results. */
enum BackupCardStatus {
    BACKUP_CARD_OK = 0,
    BACKUP_CARD_FAILED = 1,
    BACKUP_CARD_BUSY = 3, /* an asynchronous request is under way */
    BACKUP_CARD_IDLE = 4, /* no request holds the lock */
};

typedef struct BackupCard {
    u32 size;  /* the save memory's size in bytes (BackupCard_Init) */
    s32 lock;  /* the lock id held during a request, or BACKUP_CARD_NO_LOCK */
    u8 unk_08; /* 4 after BackupCard_Init */
    u8 pad_09[3];
} BackupCard;

void BackupCard_InitGame(void);
void BackupCard_Init(BackupCard *card, int type, const void *name);
int BackupCard_Status(BackupCard *card);
void BackupCard_Finish(BackupCard *card);
void BackupCard_Shutdown(void);
int BackupCard_ReadAsync(BackupCard *card, u32 dst, u32 length, u32 offset);
int BackupCard_Read(BackupCard *card, u32 dst, u32 length, u32 offset);
int BackupCard_WriteAsync(BackupCard *card, int offset, const void *src, int length);
int BackupCard_Write(BackupCard *card, int offset, const void *src, int length);
unsigned short BackupCard_Sum(unsigned short *data, int length);
unsigned short BackupCard_Checksum(const u16 *data, int length, unsigned short total);

#endif
