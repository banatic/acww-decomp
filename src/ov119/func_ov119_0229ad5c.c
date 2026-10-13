/* func_ov119_0229ad5c @ 0x0229ad5c, 0x26 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229ae68(void);
extern void func_ov119_0229adc4(int);
extern void func_020984e8(void);
extern void func_02099658(void);
extern void func_02077cb4(void);

void func_ov119_0229ad5c(int r0)
{
    int r4 = r0;
    if (func_ov119_0229ae68() != 0) {
        func_ov119_0229adc4(r4);
    } else {
        func_020984e8();
        func_02099658();
        func_02077cb4();
    }
}
