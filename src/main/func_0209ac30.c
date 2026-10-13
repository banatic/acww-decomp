/* func_0209ac30 @ 0x0209ac30, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003738(void *ptr);

void func_0209ac30(void *base)
{
    int i = 0;
    char *p = (char *) base + 0x60;
    for (; i < 3; i++) {
        func_02003738(p + i * 16);
    }
}
