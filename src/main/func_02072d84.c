/* func_02072d84 @ 0x02072d84, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072da0(void *);
extern void MI_CpuCopy8(int, int, int);

void func_02072d84(int a, int b)
{
    MI_CpuCopy8(b, func_02072da0((void *) a), 0x200);
}
