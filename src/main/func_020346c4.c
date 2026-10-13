/* func_020346c4 @ 0x020346c4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020346a4(unsigned char *base, int a, int b);

int func_020346c4(unsigned char *base, int a, int b)
{
    int idx;
    unsigned char *p;

    idx = func_020346a4(base, a, b);
    if (idx != -1) {
        *base |= (1 << idx);
        p = base + idx;
        p[5] = a;
        p[9] = b;
        p[1] = 0;
        return 1;
    } else {
        return 0;
    }
}
