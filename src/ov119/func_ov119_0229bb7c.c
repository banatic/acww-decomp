/* func_ov119_0229bb7c @ 0x0229bb7c, 0x2c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov119_0229bb7c(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0x9e;
    *p = 0;
    base = (char *) arg0 + 0x4d0;
    for (i = 0; i < 0x13; i++) {
        func_02070b84(base + i * 0x6c);
    }
}
