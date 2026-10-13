/* func_020422d0 @ 0x020422d0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int OS_IsThreadTerminated(void *param0);
extern void OS_KillThread(void *param0, int param1);

struct UnkStruct_020422d0 {
    char pad_00[0x10ea];
    unsigned char unk_10EA;
};

void func_020422d0(struct UnkStruct_020422d0 *param0)
{
    if (param0->unk_10EA != 0) {
        if (OS_IsThreadTerminated(param0) == 0) {
            OS_KillThread(param0, 0);
        }
    }
}
