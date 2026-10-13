/* func_02093990 @ 0x02093990, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209418c(int a, int b, int c, int d, void *e, void *f, void (*g)(void));
extern void func_020939b8(void);
extern char data_020e28fc;
extern char data_020e279c;

int func_02093990(int a, int b, int c, int d)
{
    return func_0209418c(a, b, c, d, &data_020e28fc, &data_020e279c, func_020939b8);
}
