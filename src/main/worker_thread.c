/* worker_thread: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020422d0 @ 0x020422d0, 0x28 bytes, Thumb
 * func_020422a0 @ 0x020422a0, 0x30 bytes, Thumb
 */

struct UnkStruct_020422d0 {
    char pad_00[0x10ea];
    unsigned char unk_10EA;
};

extern int OS_IsThreadTerminated(void *param0);
extern void OS_KillThread(void *param0, int param1);
extern struct UnkStruct_020422a0 {
    char pad_00[0x20];
    unsigned int unk_20;
} data_021c779c;
extern unsigned int data_021fbe94;
extern void func_020e993c(unsigned int a, unsigned int b);

void func_020422d0(struct UnkStruct_020422d0 *param0)
{
    if (param0->unk_10EA != 0) {
        if (OS_IsThreadTerminated(param0) == 0) {
            OS_KillThread(param0, 0);
        }
    }
}

void func_020422a0(void)
{
    unsigned int value = data_021c779c.unk_20;
    if (value == 0) {
        return;
    }
    func_020422d0((struct UnkStruct_020422d0 *) value);
    func_020e993c(data_021fbe94, value);
    data_021c779c.unk_20 = 0;
}
