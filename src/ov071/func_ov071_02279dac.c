/* func_ov071_02279dac @ 0x02279dac, 0x2c bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern int func_02041620(void);
extern void func_0208602c(void);
extern void func_020860b8(void);
extern void func_0208786c(void);

int func_ov071_02279dac(void)
{
    if (func_0202ec14() == 0) {
        return 0;
    }
    if (func_02041620() == 0) {
        func_0208602c();
        func_020860b8();
        func_0208786c();
    }
    return 1;
}
