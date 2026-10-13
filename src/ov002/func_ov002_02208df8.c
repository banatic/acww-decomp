/* func_ov002_02208df8 @ 0x02208df8, 0x20 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *ptr);

void func_ov002_02208df8(void *p)
{
    int i;
    char *base;
    int stride;

    i = 0;
    base = (char *) p;
    base += 0x28;
    stride = 116;

    do {
        func_02070b84(base + i * stride);
        i++;
    } while (i < 5);
}
