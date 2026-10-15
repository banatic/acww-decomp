/* func_ov102_0229c4c0 @ 0x0229c4c0, 0x44 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229c504(unsigned char *arg0);
extern void func_02070adc(int, int, int, int, int, int, int);
extern int func_0207094c(int, int);
extern void func_02070a04(int, int, int);

void func_ov102_0229c4c0(int param1, int param2)
{
    int r5;
    int r4;
    int sp[3];

    r5 = 1;
    if (param2 != 0) {
        r5 = 15;
    }
    r4 = func_ov102_0229c504((unsigned char *) param1);
    sp[0] = r5;
    sp[1] = 9;
    sp[2] = 0;
    func_02070adc(r4, 4, 0x1d6, 6, sp[0], sp[1], sp[2]);
    func_0207094c(r4, 0x88);
    func_02070a04(r4, 1, 1);
}
