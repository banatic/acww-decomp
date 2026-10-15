/* func_ov124_0229f320 @ 0x0229f320, 0x58 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov124_0229f27c(int a);
extern void func_02070adc(int, int, int, int, int, int, int);

void func_ov124_0229f320(int a0)
{
    int s;
    unsigned int v;

    v = func_ov124_0229f27c(a0);

    switch (v) {
        case 0:
            s = 0xd;
            break;
        case 1:
            s = 8;
            break;
        case 2:
            s = 0x14;
            break;
        case 3:
            s = 5;
            break;
        case 4:
            s = 0xa;
            break;
    }

    func_02070adc(a0, 3, 0x11, s, 4, 1, 0);
}
