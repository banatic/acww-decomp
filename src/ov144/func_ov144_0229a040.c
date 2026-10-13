/* func_ov144_0229a040 @ 0x0229a040, 0x2c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov144_0229a040(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0xbf;
    *p = 0;
    base = (char *) arg0 + 0x33c;
    for (i = 0; i < 9; i++) {
        func_02070b84(base + i * 0x6c);
    }
}
