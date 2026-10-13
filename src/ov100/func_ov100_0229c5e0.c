/* func_ov100_0229c5e0 @ 0x0229c5e0, 0x2c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *p);

void func_ov100_0229c5e0(void *p)
{
    int i = 0;
    ((char *) p)[0x2927] = i;
    {
        char *base = (char *) p + 0x27e8;
        for (; i < 2; i++) {
            func_02070b84(base + i * 0x6c);
        }
    }
}
