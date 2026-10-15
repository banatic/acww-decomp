/* func_ov124_0229f398 @ 0x0229f398, 0xa4 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov124_0229f0ec(void *r0, void *r1, int r2);
extern int func_02002ca4(void *r0, void *r1, int r2);
extern int func_0206fca4(void);
extern int func_0207094c(void *r0, int r1);
extern void func_02070adc(void *r0, void *r1, int r2, int r3, int r4, int r5, int r6);
extern void func_02070a04(void *r0, int r1, int r2);

extern char data_ov124_0229f674;
extern void *data_021fbe94;

void func_ov124_0229f398(void *r0, void *r1, int r2)
{
    func_ov124_0229f0ec(r0, r1, 5);
    func_02002ca4(&data_ov124_0229f674, data_021fbe94, r2);

    switch (func_0206fca4() - 4) {
        case 0:
        case 3:
        case 6:
            func_0207094c(r0, 0x3a);
            break;
        case 1:
            func_0207094c(r0, 0x90);
            break;
        case 4:
        case 5:
            func_0207094c(r0, 0x92);
            break;
        case 2:
            func_0207094c(r0, 0x49);
            break;
        default:
            func_0207094c(r0, 0x3a);
            break;
    }

    func_02070adc(r0, r1, 0x11, 0xd, 4, 1, 0);
    func_02070a04(r0, 1, 0);
}
