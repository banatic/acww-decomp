/* func_ov120_0229a9b4 @ 0x0229a9b4, 0x7c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern int func_ov120_0229a448(void *, int);
extern void func_ov120_0229adc4(void *, int);
extern void func_ov120_0229b22c(void *);
extern void func_ov120_0229b214(void *);
extern void func_ov120_0229abec(void *, int);

int func_ov120_0229a9b4(unsigned char *a)
{
    unsigned char b0 = data_021f6c58;
    unsigned char b1 = data_021f6c54;
    if ((int) b1 < 0x38 || (int) b1 > 0x4c) {
        return 0;
    }
    if (func_ov120_0229a448(a, 1)) {
        if ((int) b0 < 0xcc || (int) b0 > 0xe4) {
            return 0;
        }
        func_ov120_0229adc4(a, 0);
        func_ov120_0229b22c(a);
    } else {
        if ((int) b0 < 0xb0 || (int) b0 > 0xc8) {
            return 0;
        }
        func_ov120_0229adc4(a, 0);
        func_ov120_0229b214(a);
    }
    func_ov120_0229abec(a, 0);
    a[0xa3] = 0xff;
    return 1;
}
