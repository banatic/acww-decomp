/* heap_3: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e9a3c @ 0x020e9a3c, 0x2c bytes, ARM
 * func_020e9a08 @ 0x020e9a08, 0x34 bytes, ARM
 */

struct UnkStruct_020e9a3c {
    char pad_00[0x10];
    int unk_10;
};

extern unsigned int OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(unsigned int ret);
extern int data_021fbe94;

int func_020e9a3c(struct UnkStruct_020e9a3c *self, int value)
{
    int ret = OS_DisableInterrupts();
    int old = self->unk_10;
    int flag = value & 0x8000;
    if (flag == 0) {
        self->unk_10 = value;
    }
    OS_RestoreInterrupts(ret);
    return old;
}

int func_020e9a08(int param)
{
    int result = OS_DisableInterrupts();
    int old = data_021fbe94;
    data_021fbe94 = param;
    OS_RestoreInterrupts(result);
    return old;
}
