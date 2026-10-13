/* func_02098b44 @ 0x02098b44, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c878(unsigned short *p);
extern int func_02098be8(void *self);
extern unsigned short *func_02098f48(void *self, int index);
extern void func_02098f0c(void *self, unsigned short *p, int index, int zero);

unsigned int func_02098b44(void *self, unsigned int r5)
{
    unsigned short pair[2];
    int r7;
    int r4;
    unsigned int cond;
    unsigned short vv;

    pair[0] = 0x14fdu;
    r7 = func_0204c878(pair);
    pair[1] = 0xfff1u;

    while (r5 > 99999u) {
        r4 = func_02098be8(self);
        if (r4 == -1) {
            break;
        }

        pair[1] = *func_02098f48(self, r4);

        cond = 0;
        vv = *(volatile unsigned short *) &pair[1];
        if (pair[1] >= 0x1492u && vv <= 0x14fdu) {
            cond = 1;
        }

        if (cond) {
            func_02098f0c(self, pair, r4, 0);
            r5 -= (r7 - func_0204c878(&pair[1]));
        } else {
            if (vv != 0xfff1u) {
                break;
            }
            func_02098f0c(self, pair, r4, 0);
            r5 -= r7;
        }
    }
    return r5;
}
