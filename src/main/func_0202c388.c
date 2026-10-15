/* func_0202c388 @ 0x0202c388, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_0207ef48(int);
extern int func_02099870(int);
extern int func_02094ffc(void *);
extern int func_020800fc(int);
extern int func_02015e70(int, int, int);
extern int func_0209dcac(void);
extern unsigned char data_020c8f64[];

int func_0202c388(int a, int *b, int c)
{
    int r4;
    int r5 = 0;
    int r6 = 0;
    int r7 = 0;
    int sp0;

    r7 = a;
    r5 = (int) b;
    r6 = c;
    sp0 = func_020984e8();
    r4 = func_0207ef48(r6);
    if (r4 == 1) {
        if (func_02094ffc((void *) func_02099870(sp0)) != 0) {
            r4 = 0;
        }
    }
    if (r4 == 2) {
        func_02015e70(r7, func_020800fc(r6), 1);
    } else {
        *b = func_0209dcac();
    }
    return (int) &data_020c8f64[r4 * 8];
}
