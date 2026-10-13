/* func_0201bfbc @ 0x0201bfbc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(int, int, int);

void func_0201bfbc(int a, int b, int c)
{
    if (c > 4) {
        c = 4;
    }
    MI_CpuCopy8(b, a + 0x62d, c);
}
