/* func_0200d0b0 @ 0x0200d0b0, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02010718(void *a);
extern int func_020113b0(int a, int b);
extern int func_02011398(int a, int b);
extern int func_0200dc48(void *a);
extern int func_020113e0(short *p, int b);
extern void func_020110a0(void *a, short *p);
extern int FX_MulFunc(int a, int b);
extern void func_0201107c(void *a, int *p);
extern short FX_SinCosTable_[];

void func_0200d0b0(char *a)
{
    int *p = (int *) (a + 0x7d4);
    int cur = func_02010718(a);

    if (*p < cur) {
        *p = func_020113b0(*p, cur);
    } else if (*p > cur) {
        *p = func_02011398(*p, cur);
    }

    {
        int r7 = func_0200dc48(a);
        short local = *(short *) (a + 0x8e);

        if (cur > 0) {
            func_020113e0(&local, r7);
            func_020110a0(a, &local);
        }

        {
            short diff = (short) (local - r7);
            unsigned short udiff = (unsigned short) diff;
            int idx = (udiff >> 4) * 2 + 1;
            int t = FX_MulFunc(*p, FX_SinCosTable_[idx]);
            int val;
            if (t < 0) {
                t = -t;
            }
            val = t;
            func_0201107c(a, &val);
        }
    }
}
