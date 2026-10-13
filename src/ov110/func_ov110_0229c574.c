/* func_ov110_0229c574 @ 0x0229c574, 0x2c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov110_0229c574(void *param)
{
    int i;
    char *p;
    char *base;

    p = (char *) param + 0xfb;
    *p = 0;
    base = (char *) param + 0x2854;
    for (i = 0; i < 2; i++) {
        func_02070b84(base + i * 0x6c);
    }
}
