/* func_ov004_02241588 @ 0x02241588, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

void func_ov004_02241588(char *self, short *pc)
{
    short a = *(short *) (self + 0x192);
    short d = *pc;
    if (d == 0) {
        if (func_020644cc(0x64) < 0x32) {
            *pc += 1;
        } else {
            *pc -= 1;
        }
    } else if ((d > 0 && d <= 6) || (d > 0x12 && d <= 0x18) || (d < ~5 && d >= ~0x11)) {
        if (d > 0) {
            *pc += 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) + 0xb6);
        } else {
            *pc -= 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) - 0xb6);
        }
        a = (short) (a + 0x16b);
    } else if ((d > 6 && d <= 0x12) || (d < 0 && d >= ~5) || (d < ~0x11 && d >= ~0x17)) {
        if (d > 0) {
            *pc += 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) - 0xb6);
        } else {
            *pc -= 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) + 0xb6);
        }
        a = (short) (a - 0x16b);
    } else {
        *pc = 0;
        *(short *) (self + 0x172) = 0x19;
    }
    *(short *) (self + 0x192) = a;
}
