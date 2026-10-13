/* func_ov004_0220c1f4 @ 0x0220c1f4, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea990(void *a, void *b);

int func_ov004_0220c1f4(void *a, void *b)
{
    unsigned short d;

    if (b != 0 && func_020ea990((char *) b + 0x5c, (char *) a + 0x5c) < 0x2333) {
        d = (unsigned short) (*(short *) ((char *) b + 0x8e) - (*(short *) ((char *) a + 0x8e) + 0x8000));
        if (d < 0x1000) {
            goto ret1;
        }
        if (d < 0xf000) {
            goto ret0;
        }
    ret1:
        return 1;
    ret0:
        return 0;
    }
    return 0;
}
