/* func_ov066_02267e00 @ 0x02267e00, 0x28 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern int OS_DisableInterrupts(unsigned int param);
extern void OS_RestoreInterrupts(int value);

struct UnkStruct_02267e00 {
    unsigned char pad_00[0x6C];
    unsigned int unk_6C;
};

extern struct UnkStruct_02267e00 *data_ov066_0226bdf0;

void func_ov066_02267e00(unsigned int param)
{
    int ret = OS_DisableInterrupts(param);
    data_ov066_0226bdf0->unk_6C = param;
    OS_RestoreInterrupts(ret);
}
