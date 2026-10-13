/* func_ov145_02299da4 @ 0x02299da4, 0x2c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov145_02299da4(void *self)
{
    int i;
    char *p;

    p = (char *) self + 0xc4;
    *p = 0;
    for (i = 0; i < 0x12; i++) {
        func_02070b84((char *) self + 0x340 + i * 0x6c);
    }
}
