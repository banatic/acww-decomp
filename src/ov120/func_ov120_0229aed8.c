/* func_ov120_0229aed8 @ 0x0229aed8, 0x38 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229ae78(int a, unsigned char b, unsigned char c);
extern void func_ov120_0229adc4(int a, unsigned char b);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

int func_ov120_0229aed8(int arg)
{
    int result;

    result = func_ov120_0229ae78(arg, data_021f6c58, data_021f6c54);
    if (result == 14) {
        return 0;
    } else {
        func_ov120_0229adc4(arg, (unsigned char) (result + 1));
        return 1;
    }
}
