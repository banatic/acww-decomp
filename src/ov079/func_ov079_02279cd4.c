/* func_ov079_02279cd4 @ 0x02279cd4, 0x2c bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern int func_02041620(void);
extern void func_0208602c(void);
extern void func_020860b8(void);
extern void func_0208786c(void);

int func_ov079_02279cd4(void)
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
