/* town_spot_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02087a74 @ 0x02087a74, 0x2 bytes, Thumb
 * func_02087a70 @ 0x02087a70, 0x2 bytes, Thumb
 * func_02087a64 @ 0x02087a64, 0xc bytes, Thumb
 */

extern void MI_CpuFill8(int a, int b, int c);

void func_02087a74(void *object) {}

void func_02087a70(void *object) {}

void func_02087a64(int a)
{
    MI_CpuFill8(a, 0, 8);
}
