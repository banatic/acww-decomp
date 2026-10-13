/* func_020e9a3c @ 0x020e9a3c, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020e9a3c {
    char pad_00[0x10];
    int unk_10;
};
extern int OS_DisableInterrupts(struct UnkStruct_020e9a3c *self, int value);
extern void OS_RestoreInterrupts(int ret, int flag);

int func_020e9a3c(struct UnkStruct_020e9a3c *self, int value)
{
    int ret = OS_DisableInterrupts(self, value);
    int old = self->unk_10;
    int flag = value & 0x8000;
    if (flag == 0) {
        self->unk_10 = value;
    }
    OS_RestoreInterrupts(ret, flag);
    return old;
}
