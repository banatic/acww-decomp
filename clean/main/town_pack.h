/* The state block (state_block.h) packed for sending to another system, and unpacked when
 * received, on a thread of its own. The activity process (activity.h) allocates the buffer
 * (its word 0xc8, func_020a1350) and the thread object (word 0xcc, func_020a1338):
 *
 *   the buffer: the packed size, then the block compressed with the SDK's LZ77 (MI_CompressLZ),
 *   or the size 0 and the block as it is when it does not compress;
 *   the thread object: an OSThread, its 0x1000-byte stack between two marks of 12345 and a
 *   flag set when the work is done. The thread packs the state block into the buffer, or
 *   unpacks the buffer into the received block (func_020a13b8, data_021f3c24). */
#ifndef CLEAN_MAIN_TOWN_PACK_H
#define CLEAN_MAIN_TOWN_PACK_H

#include "state_block.h"
#include "types.h"

#define TOWN_PACK_STACK_SIZE 0x1000

typedef struct TownPackBuffer {
    u32 packed_size; /* the compressed size (its 4-byte header included), or 0 */
    u8 data[sizeof(StateBlock)];
} TownPackBuffer;

typedef struct TownPackThread {
    u8 thread[0x64];                /* NitroSDK's OSThread, 0xc0 bytes ... */
    u32 thread_state;               /* 0x64: ... its state (2: terminated) ... */
    u8 thread_rest[0xc0 - 0x68];    /* ... and the rest of it */
    u32 mark_low;                   /* 0xc0: 12345 */
    u8 stack[TOWN_PACK_STACK_SIZE]; /* 0xc4 */
    u32 mark_high;                  /* 0x10c4: 12345, at the stack's top */
    u8 done;                        /* 0x10c8 */
    u8 unk_10c9[3];
} TownPackThread;

u8 TownPack_IsDone(TownPackThread *thread);
void TownPack_StartThread(TownPackThread *thread, void *pack);
void TownPack_KillThread(TownPackThread *thread);
int TownPack_InitThread(TownPackThread *thread);
void TownPack_ThreadMain(int pack);
int TownPack_PackedSize(TownPackBuffer *buffer);
void TownPack_Unpack(TownPackBuffer *buffer);
void TownPack_Pack(TownPackBuffer *buffer);

#endif
