/* func_ov066_02268ed4 @ 0x02268ed4, 0x48 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02268ed4 {
    char pad_00[0x98];
    unsigned short flags;
};

extern struct UnkStruct_02268ed4 *data_ov066_0226bdf4;
extern void MI_CpuCopy8(void *src, void *dst, unsigned int size);
extern void func_ov066_0226943c(void);

void func_ov066_02268ed4(int bit, void *ptr)
{
    unsigned char local[8];
    MI_CpuCopy8(ptr, local, 8);
    data_ov066_0226bdf4->flags |= (1 << bit);
    func_ov066_0226943c();
}
