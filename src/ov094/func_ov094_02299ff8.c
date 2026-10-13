/* func_ov094_02299ff8 @ 0x02299ff8, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *p);

void func_ov094_02299ff8(void *p)
{
    int i;
    for (i = 0; i < 2; i++) {
        func_02070b84((char *) p + 0xe0 + i * 0x6c);
    }
}
