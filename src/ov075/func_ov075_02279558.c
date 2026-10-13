/* func_ov075_02279558 @ 0x02279558, 0x2c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern int func_02041620(void);
extern void func_0208602c(void);
extern void func_020860c0(void);
extern void func_02087e64(void);

int func_ov075_02279558(void)
{
    if (func_0202ec14() == 0) {
        return 0;
    } else {
        if (func_02041620() == 0) {
            func_0208602c();
            func_020860c0();
            func_02087e64();
        }
        return 1;
    }
}
