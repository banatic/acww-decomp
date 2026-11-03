/* xct_exchange_4: 5 functions, module ov055
 * mwccarm 1.2/base -O4,s
 * func_ov055_02260c38 @ 0x02260c38, 0x30 bytes, Thumb
 * func_ov055_02260bf8 @ 0x02260bf8, 0x40 bytes, Thumb
 * func_ov055_02260bc4 @ 0x02260bc4, 0x34 bytes, Thumb
 * func_ov055_02260bbc @ 0x02260bbc, 0x8 bytes, Thumb
 * func_ov055_02260bb4 @ 0x02260bb4, 0x8 bytes, Thumb
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov055_02260a04(void *, void *);
extern int func_0202ec58(void *p);
extern void func_ov055_022604f4(void *receiver);
extern void func_ov055_02260b24(void *p, int x);
extern int func_ov004_02246ecc(void *p);
extern void func_0203e334(void);
extern void func_ov055_02260544(void *p);
extern void *data_ov055_02261080;
extern int func_0202ec14(void *argument0);
extern void func_ov055_022604d4(void *receiver);
extern void func_0203e328(void);
extern void func_ov055_02260514(int);
extern int data_ov055_02260ef0;
extern int data_ov055_02260ec0;

int func_ov055_02260c38(void *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov055_02260a04((char *) self + 0x658, self);
    return 1;
}

int func_ov055_02260bf8(void *arg)
{
    if (!func_0202ec58(arg)) {
        return 0;
    }

    data_ov055_02261080 = arg;
    func_ov055_022604f4((void *) arg);
    func_ov055_02260b24(arg, 0);
    func_ov004_02246ecc((char *) arg + 0x5c);
    func_0203e334();
    func_ov055_02260544(arg);

    return 1;
}

int func_ov055_02260bc4(int param)
{
    if (!func_0202ec14((void *) param)) {
        return 0;
    }
    (*(int *) &data_ov055_02261080) = 0;
    func_ov055_022604d4((void *) param);
    func_0203e328();
    func_ov055_02260514(param);
    return 1;
}

int func_ov055_02260bbc(void)
{
    return (int) &data_ov055_02260ef0;
}

int func_ov055_02260bb4(void)
{
    return (int) &data_ov055_02260ec0;
}
