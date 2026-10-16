/* The state block packed and unpacked on a thread (town_pack.h). */
#include "town_pack.h"

#include "clean.h"

static_assert(sizeof(TownPackBuffer) == 0x17400, "the activity's buffer");
static_assert(sizeof(TownPackThread) == 0x10cc && offsetof(TownPackThread, done) == 0x10c8, "the thread object");
static_assert(offsetof(TownPackThread, stack) == 0xc4 && offsetof(TownPackThread, mark_high) == 0x10c4, "the stack");

#define TOWN_PACK_MARK 12345
#define TOWN_PACK_PRIORITY 30
#define OS_THREAD_SIZE 0xc0
#define OS_THREAD_STATE_TERMINATED 2

extern StateBlock data_021dc7a8;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern u32 MI_CompressLZ(const void *src, u32 size, void *dst);
extern void MI_InitUncompContextLZ(void *context, void *dst, const void *header);
extern int MI_ReadUncompLZ8(void *context, const void *data, u32 length);
extern void OS_CreateThread(void *thread, void (*function)(void *), void *argument, void *stack_top, u32 stack_size,
                            u32 priority);
extern void OS_WakeupThreadDirect(void *thread);
extern int OS_IsThreadTerminated(void *thread);
extern void OS_KillThread(void *thread, void *argument);
extern void OS_ExitThread(void);

/* The thread's function (TownPack_ThreadMain), handed to the SDK by its game symbol, as the
 * SDK calls it: its argument is TownPack_StartThread's `pack`. */
extern void func_020a00c0(void *pack);
/* The activity's buffer and thread object, and the received state block. */
extern TownPackBuffer *func_020a1350(void);
extern TownPackThread *func_020a1338(void);
extern StateBlock *func_020a13b8(void);

/* func_020a0030 */
u8 TownPack_IsDone(TownPackThread *thread)
{
    return thread->done;
}
CLEAN_AS(func_020a0030, TownPack_IsDone)

/* func_020a003c: the thread started on its own stack: `pack` non-zero packs the state block,
 * zero unpacks the buffer (TownPack_ThreadMain). */
void TownPack_StartThread(TownPackThread *thread, void *pack)
{
    OS_CreateThread(thread, func_020a00c0, pack, thread->stack + TOWN_PACK_STACK_SIZE, TOWN_PACK_STACK_SIZE,
                    TOWN_PACK_PRIORITY);
    OS_WakeupThreadDirect(thread);
}
CLEAN_AS(func_020a003c, TownPack_StartThread)

/* func_020a0070: the thread killed unless it has ended. */
void TownPack_KillThread(TownPackThread *thread)
{
    if (OS_IsThreadTerminated(thread) == 0) {
        OS_KillThread(thread, NULL);
    }
}
CLEAN_AS(func_020a0070, TownPack_KillThread)

/* func_020a008c: the marks written, the flag cleared and the OSThread cleared and marked as
 * terminated, so that it can be killed or checked before it ever ran; gives that state. */
int TownPack_InitThread(TownPackThread *thread)
{
    thread->mark_low = TOWN_PACK_MARK;
    thread->mark_high = TOWN_PACK_MARK;
    thread->done = 0;
    MI_CpuFill8(thread, 0, OS_THREAD_SIZE);
    thread->thread_state = OS_THREAD_STATE_TERMINATED;
    return OS_THREAD_STATE_TERMINATED;
}
CLEAN_AS(func_020a008c, TownPack_InitThread)

/* func_020a00c0: the thread's work: the activity's buffer packed or unpacked, the activity's
 * thread object marked done, and the thread ended. */
void TownPack_ThreadMain(int pack)
{
    if (pack != 0) {
        TownPack_Pack(func_020a1350());
    } else {
        TownPack_Unpack(func_020a1350());
    }
    func_020a1338()->done = 1;
    OS_ExitThread();
}
CLEAN_AS(func_020a00c0, TownPack_ThreadMain)

/* func_020a00fc */
int TownPack_PackedSize(TownPackBuffer *buffer)
{
    return (int) buffer->packed_size;
}
CLEAN_AS(func_020a00fc, TownPack_PackedSize)

/* func_020a0100: the buffer unpacked into the received state block. */
void TownPack_Unpack(TownPackBuffer *buffer)
{
    StateBlock *to = func_020a13b8();
    if (buffer->packed_size != 0) {
        u32 context[4]; /* MIUncompContextLZ */
        MI_InitUncompContextLZ(context, to, buffer->data);
        MI_ReadUncompLZ8(context, buffer->data + 4, buffer->packed_size - 4);
    } else {
        MI_CpuCopy8(buffer->data, to, sizeof(StateBlock));
    }
}
CLEAN_AS(func_020a0100, TownPack_Unpack)

/* func_020a0140: the state block packed into the buffer. */
void TownPack_Pack(TownPackBuffer *buffer)
{
    u32 size = MI_CompressLZ(&data_021dc7a8, sizeof(StateBlock), buffer->data);
    if (size == 0) {
        buffer->packed_size = 0;
        MI_CpuCopy8(&data_021dc7a8, buffer->data, sizeof(StateBlock));
    } else {
        buffer->packed_size = size;
    }
}
CLEAN_AS(func_020a0140, TownPack_Pack)
