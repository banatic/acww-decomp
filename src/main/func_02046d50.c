/* func_02046d50 @ 0x02046d50, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020988a4(void *base, int n);
extern int func_02098844(void *base, int n);
extern int func_02099734(int a);
extern unsigned short *func_02098f48(void *base, int n);
extern int func_02098f0c(unsigned short *p0, unsigned short *p1, int p2, int p3);

extern unsigned char data_021dc7bc[];

void func_02046d50(void)
{
    int outer;
    int inner;
    int neg;
    int h;
    int q;
    int start;
    int flag;
    int ctr;
    unsigned short idx;
    unsigned short *p;
    unsigned short v;
    int y;
    unsigned short t;

    for (outer = 0; outer < 4; outer++) {
        neg = -1;
        ctr = 0;
        start = 0;
        if (func_020988a4((void *) data_021dc7bc, outer) == 0) {
            continue;
        }
        h = func_02098844((void *) data_021dc7bc, outer);
        for (inner = start; inner < 15; inner++) {
            q = func_02099734(h);
            p = func_02098f48((void *) q, inner);
            if (p != 0) {
                flag = 0;
                v = *p;
                if (v >= 0x1531u && v <= 0x153au) {
                    flag = 1;
                }
                if (flag != 0) {
                    if (v >= 0x1531u && v <= 0x153au) {
                        y = v - 0x1531;
                    } else {
                        y = neg;
                    }
                    if ((unsigned int) y < 10) {
                        t = (unsigned short) (0x154a + y);
                    } else {
                        t = 0x154a;
                    }
                    idx = t;
                    func_02098f0c((unsigned short *) q, &idx, inner, ctr);
                }
            }
        }
    }
}
