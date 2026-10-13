/* func_0209dae8 @ 0x0209dae8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a53c4(void);
extern int func_0202f12c(int, int, int);
extern int func_0202f134(int, int, int, int);
extern unsigned short data_020d1adc[8];

void func_0209dae8(void)
{
    int r5;
    int r4;
    int r7;
    int r0;
    int r1;
    int r2;
    int r3;

    func_020a53c4();
    r5 = func_0202f12c(0, 0, 1);
    r4 = 0;
    r7 = 0;
    while (r4 < 7) {
        r0 = data_020d1adc[r4];
        r1 = r5;
        r2 = r7;
        r3 = r7;
        func_0202f134(r0, r1, r2, r3);
        r4++;
    }
}
