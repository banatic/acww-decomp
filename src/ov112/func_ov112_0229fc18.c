/* func_ov112_0229fc18 @ 0x0229fc18, 0x30 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070a04(void *ptr, int a, int b);

void func_ov112_0229fc18(void *p)
{
    int i = 0;
    char *base = (char *) p + 0x3fac;
    int zero = i;

    for (; i < 6; i++) {
        func_02070a04(base + i * 108, zero, zero);
    }
}
