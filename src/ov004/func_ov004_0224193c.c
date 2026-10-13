/* func_ov004_0224193c @ 0x0224193c, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int n);

int func_ov004_0224193c(void *self, short *state)
{
    short ang = *(short *) ((char *) self + 0x192);

    if (state[0] == 0) {
        if (func_020644cc(0x64) > 0x32) {
            *(unsigned char *) ((char *) self + 0x170) = 0;
        } else {
            *(unsigned char *) ((char *) self + 0x170) = 1;
        }
    }

    if (*(unsigned char *) ((char *) self + 0x170) != 0) {
        if (ang > 0xaaa) {
            *(unsigned char *) ((char *) self + 0x170) = 0;
        }
    } else {
        if (ang < (short) 0xf556) {
            *(unsigned char *) ((char *) self + 0x170) = 1;
        }
    }

    if (*(unsigned char *) ((char *) self + 0x170) != 0) {
        *(short *) ((char *) self + 0x192) = ang + 0x222;
    } else {
        *(short *) ((char *) self + 0x192) = ang - 0x222;
    }

    state[0] = state[0] + 1;
    return 1;
}
