/* func_ov146_0229a400 @ 0x0229a400, 0x2c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov146_0229a400(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0xb4;
    *p = 0;
    base = (char *) arg0 + 0x1630;
    for (i = 0; i < 20; i++) {
        func_02070b84(base + i * 0x6c);
    }
}
