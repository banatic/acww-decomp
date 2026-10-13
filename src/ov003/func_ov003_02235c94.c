/* func_ov003_02235c94 @ 0x02235c94, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
} UnkStruct_02235c94;

extern UnkStruct_02235c94 data_ov003_02262aa8[];
extern void func_020779b8(void *buf, int a, int b);
extern int func_0207762c(int id);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);

void func_ov003_02235c94(void *dst, int id)
{
    u8 buf[8];
    int i;

    i = id - 0x18;
    func_020779b8(buf, data_ov003_02262aa8[i].unk_00, data_ov003_02262aa8[i].unk_08);
    buf[5] = data_ov003_02262aa8[i].unk_0C;
    buf[6] = data_ov003_02262aa8[i].unk_0D;
    MI_CpuCopy8(buf, dst, func_0207762c(id));
}
