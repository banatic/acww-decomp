/* func_ov143_02299a38 @ 0x02299a38, 0x2c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov143_02299a38(void *arg0)
{
    int i;
    char *p = (char *) arg0 + 0x9f;
    *p = 0;
    for (i = 0; i < 16; i++) {
        func_02070b84((char *) arg0 + 0x2dc + i * 0x6c);
    }
}
