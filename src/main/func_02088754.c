/* func_02088754 @ 0x02088754, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(int a, int b, int c);

int func_02088754(int a)
{
    MI_CpuFill8(a, 0xff, 1);
    {
        register int result;
        asm { mov result, r0 }
        return result;
    }
}
