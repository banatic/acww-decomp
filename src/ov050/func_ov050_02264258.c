/* func_ov050_02264258 @ 0x02264258, 0x5c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern void func_0208602c(void);
extern int func_020860d0(void);
extern int func_ov050_022604bc(void *self);
extern int func_02087ec0(int x);
extern int func_020b5e10(void);
extern void func_020b6098(int first, int flag);
extern void func_ov050_02264834(void *self, int x);

int func_ov050_02264258(void *self)
{
    int r5;
    if (func_02014868((char *) self + 0x618) != 0) {
        goto done;
    }
    func_0208602c();
    r5 = func_020860d0();
    if (func_ov050_022604bc(self) != 0 && func_02087ec0(r5) != 0) {
        func_020b6098(func_020b5e10(), 1);
    } else {
        func_020b6098(func_020b5e10(), 0);
    }
    func_ov050_02264834(self, 6);
done:
    return 1;
}
