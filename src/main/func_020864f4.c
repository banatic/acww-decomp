/* func_020864f4 @ 0x020864f4, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020864f4(int *out, unsigned short *in)
{
    int r6 = 1;
    int r5 = r6;
    int r4 = r6;
    int r3 = 0;
    unsigned short v = *in;

    if (v <= 5) {
        r3 = 1;
    }
    if (!r3) {
        if (v < 6 || v > 11) {
            r4 = 0;
        }
    }
    if (!r4) {
        if (v < 12 || v > 17) {
            r5 = 0;
        }
    }
    if (!r5) {
        if ((v < 18 || v > 25) && v != 28) {
            r6 = 0;
        }
    }

    if (r6 || v == 26 || (unsigned short) (v + 0xFFE3) <= 1) {
        if (v > 27) {
            *out = v - 1;
        } else {
            *out = v;
        }
        return 1;
    } else {
        return 0;
    }
}
