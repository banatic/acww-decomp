/* func_ov142_0229ae60 @ 0x0229ae60, 0x2c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov142_0229ae60(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0xbb;
    *p = 0;
    base = (char *) arg0 + 0x360;
    for (i = 0; i < 14; i++) {
        func_02070b84(base + i * 0x6c);
    }
}
