/* func_ov055_02260668 @ 0x02260668, 0x24 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02090040(int);
extern void *MI_CpuCopy8(void *, const void *, int);

struct UnkStruct_02260668 {
    char pad_00[0x714];
    char unk_714[0x950];
};

void *func_ov055_02260668(struct UnkStruct_02260668 *p)
{
    return MI_CpuCopy8(p->unk_714, func_02090040(4), 0x950);
}
