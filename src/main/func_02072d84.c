/* func_02072d84 @ 0x02072d84, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072da0(int, int);
extern int MI_CpuCopy8(int, int, int);

int func_02072d84(int a, int b)
{
    return MI_CpuCopy8(b, func_02072da0(a, b), 0x200);
}
