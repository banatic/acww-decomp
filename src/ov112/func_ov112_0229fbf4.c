/* func_ov112_0229fbf4 @ 0x0229fbf4, 0x24 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *ptr);

void func_ov112_0229fbf4(void *arg)
{
    int i = 0;
    char *base = (char *) arg + 0x3fac;
    do {
        func_02070b84(base + i * 0x6c);
        i++;
    } while (i < 6);
}
