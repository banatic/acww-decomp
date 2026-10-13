/* func_020a6ff0 @ 0x020a6ff0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f4320[12];
extern void func_020a7738(const unsigned char *src, unsigned char *b0, unsigned char *b1, unsigned char *b2);

int func_020a6ff0(int key)
{
    int idx_zero = 4;
    int idx_nonzero = 4;
    unsigned int i;
    unsigned char *p = data_021f4320;
    unsigned char b[3];

    for (i = 0; i < 4; i++) {
        func_020a7738(p, &b[0], &b[1], &b[2]);
        if (b[0] == key && b[1] != 0) {
            if (b[2] != 0) {
                idx_zero = (int) i;
            } else {
                idx_nonzero = (int) i;
            }
        }
        p += 3;
    }

    if (idx_zero == 4 && idx_nonzero == 4) {
        return 4;
    }
    if (idx_zero != 4 && idx_nonzero != 4) {
        return idx_nonzero;
    }
    if (idx_zero != 4) {
        return idx_zero;
    }
    return idx_nonzero;
}