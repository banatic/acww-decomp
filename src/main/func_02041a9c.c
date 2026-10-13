/* func_02041a9c @ 0x02041a9c, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 G2_GetBG2ScrPtr(void);
extern u32 G2_GetBG2CharPtr(void);
extern u32 G2S_GetBG2ScrPtr(void);
extern u32 G2S_GetBG2CharPtr(void);
extern void MIi_CpuClear16(u16, u32, u32);
extern void func_02001b44(int);
extern void func_02001b0c(int);

void func_02041a9c(void)
{
    volatile u16 arr[6];
    u32 v;

    *(volatile u16 *) 0x0400000c &= ~3;
    *(volatile u16 *) 0x0400000c = (*(volatile u16 *) 0x0400000c & 0x43) | 0x600;

    v = G2_GetBG2ScrPtr();
    arr[0] = 0;
    MIi_CpuClear16(arr[0], v, 0x800);

    v = G2_GetBG2CharPtr();
    arr[1] = 0x1111;
    MIi_CpuClear16(arr[1], v, 0x20);

    arr[2] = 0x8000;
    MIi_CpuClear16(arr[2], 0x05000000, 4);

    func_02001b44(4);

    *(volatile u16 *) 0x0400100c &= ~3;
    *(volatile u16 *) 0x0400100c = (*(volatile u16 *) 0x0400100c & 0x43) | 0xe04;

    v = G2S_GetBG2ScrPtr();
    arr[3] = 0;
    MIi_CpuClear16(arr[3], v, 0x800);

    v = G2S_GetBG2CharPtr();
    arr[4] = 0x1111;
    MIi_CpuClear16(arr[4], v, 0x20);

    arr[5] = 0x8000;
    MIi_CpuClear16(arr[5], 0x05000400, 4);

    func_02001b0c(4);
}
