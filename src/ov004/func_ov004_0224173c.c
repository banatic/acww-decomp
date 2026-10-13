/* func_ov004_0224173c @ 0x0224173c, 0xbc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

void func_ov004_0224173c(char *self, short *pc)
{
    int lim = *(int *) (self + 0xa8) + 0x400;
    int *v = (int *) (self + 0x2c8);
    short s = *pc;
    if ((s >= 0 && s < 2) || (s >= 6 && s < 8)) {
        *pc += 1;
        *(short *) (self + 0x192) = (short) (*(short *) (self + 0x192) + 0x2aa);
        *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) + 0xaa);
        v[1] += 0x20;
    } else if (s >= 2 && s < 6) {
        *pc += 1;
        *(short *) (self + 0x192) = (short) (*(short *) (self + 0x192) - 0x2aa);
        *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) - 0xaa);
        v[1] += 0x20;
    } else if (func_020644cc(0x64) > 0x46) {
        *(short *) (self + 0x172) = 1;
        *pc = 0;
    } else if (*pc >= 8) {
        *pc = 0;
    }
    if (v[1] > lim) {
        v[1] = lim;
    }
}
