/* func_ov055_02260bc4 @ 0x02260bc4, 0x34 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern void func_ov055_022604d4(int);
extern void func_0203e328(void);
extern void func_ov055_02260514(int);
extern int data_ov055_02261080;

int func_ov055_02260bc4(int param)
{
    if (!func_0202ec14()) {
        return 0;
    }
    data_ov055_02261080 = 0;
    func_ov055_022604d4(param);
    func_0203e328();
    func_ov055_02260514(param);
    return 1;
}
