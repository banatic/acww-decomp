/* func_0204c7f0 @ 0x0204c7f0, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int FX_Div(int numerator, int denominator);
extern int func_0204c878(void *p);
extern int func_0204c7c8(void *p);
extern int func_020984e8(void);
extern unsigned int func_020996a0(unsigned int object);
extern unsigned short *func_020adf50(void *record);
extern int func_0204c86c(unsigned short *counter);

int func_0204c7f0(void *p)
{
    int forwarded_value;

    int v;
    int pct;
    int mode;

    v = func_0204c878(p);
    if (func_0204c7c8(p) != 0) {
        return v;
    }
    if ((forwarded_value = (int) func_020984e8()) == 0) {
        goto ret_v;
    }
    mode = func_0204c86c(func_020adf50((void *) func_020996a0((unsigned int) forwarded_value)));
    pct = 0;
    switch (mode) {
        case 2:
            pct = 5;
            break;
        case 3:
            pct = 10;
            break;
        case 4:
            pct = 20;
            break;
    }
    if (pct == 0) {
        return v;
    }
    v = (100 - pct) * v;
    if (v >= 100) {
        return v / 100;
    }
    return FX_Div(v << 12, 100 << 12) >> 12;
ret_v:
    return v;
}
