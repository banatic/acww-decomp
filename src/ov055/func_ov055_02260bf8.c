/* func_ov055_02260bf8 @ 0x02260bf8, 0x40 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *p);
extern void func_ov055_022604f4(void *p);
extern void func_ov055_02260b24(void *p, int x);
extern void func_ov004_02246ecc(void *p);
extern void func_0203e334(void);
extern void func_ov055_02260544(void *p);
extern void *data_ov055_02261080;

int func_ov055_02260bf8(void *arg)
{
    if (!func_0202ec58(arg)) {
        return 0;
    }

    data_ov055_02261080 = arg;
    func_ov055_022604f4(arg);
    func_ov055_02260b24(arg, 0);
    func_ov004_02246ecc((char *) arg + 0x5c);
    func_0203e334();
    func_ov055_02260544(arg);

    return 1;
}
