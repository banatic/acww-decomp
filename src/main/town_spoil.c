/* town_spoil: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02046d50 @ 0x02046d50, 0xa4 bytes, Thumb
 * func_02046d38 @ 0x02046d38, 0x16 bytes, Thumb
 * func_02046d14 @ 0x02046d14, 0x24 bytes, Thumb
 * func_02046cac @ 0x02046cac, 0x68 bytes, Thumb
 */

extern int func_020988a4(void *base, int n);
extern int func_02098844(void *base, int n);
extern int func_02099734(int a);
extern unsigned short *func_02098f48(void *base, int n);
extern int func_02098f0c(unsigned short *p0, unsigned short *p1, int p2, int p3);
extern unsigned char data_021dc7bc[];
extern int func_0204e414(void);
extern void func_02046df4(int a, int b);
extern int func_0204df30(int i);
extern unsigned short data_021f3a86[15];
extern char data_021dc7a8[];

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

void func_02046d38(int r0)
{
    int r4 = r0;
    int r1 = func_0204e414();
    func_02046df4(r4, r1);
}

void func_02046d14(int param)
{
    int i;
    for (i = 0; i < 5; i++) {
        func_02046df4(param, func_0204df30(i));
    }
}

void func_02046cac(void)
{
    unsigned short *in = data_021f3a86;
    int j;

    for (j = 0; j < 15; in++, j++) {
        unsigned short val = *in;
        if (val < 0x1531 || val > 0x153a) {
            continue;
        }
        {
            int r;
            if (val >= 0x1531 && val <= 0x153a) {
                r = val - 0x1531;
            } else {
                r = -1;
            }
            {
                unsigned short out;
                if ((unsigned int) r < 10) {
                    out = (unsigned short) (0x154a + r);
                } else {
                    out = 0x154a;
                }
                *(unsigned short *) (data_021dc7a8 + j * 2 + 0x172de) = out;
            }
        }
    }
}
