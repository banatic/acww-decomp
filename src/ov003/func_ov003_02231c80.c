/* func_ov003_02231c80 @ 0x02231c80, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int a);

void func_ov003_02231c80(char *self, short *ph)
{
    short a = *(short *) (self + 0x23a);
    int lim = *(int *) (self + 0x228) + 0x400;
    int *v = (int *) (self + 0x204);
    short t = *ph;
    if (t >= 8) {
        if (func_020644cc(0x64) > 0x46) {
            *(char *) (self + 0x251) = 1;
        }
        *ph = 0;
    } else {
        if (t >= 2 && t < 6) {
            a = (short) (a - 0x16b);
            *(short *) (self + 0x238) = (short) (*(short *) (self + 0x238) - 0xb6);
        } else {
            a = (short) (a + 0x16b);
            *(short *) (self + 0x238) = (short) (*(short *) (self + 0x238) + 0xb6);
        }
        v[1] += 0x20;
        *ph = (short) (*ph + 1);
        if (v[1] > lim) {
            v[1] = lim;
        }
    }
    *(short *) (self + 0x23a) = a;
}
