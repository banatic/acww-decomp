/* func_ov003_02218f18 @ 0x02218f18, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02218f54(unsigned int *p);
extern int func_02073908(unsigned int a, unsigned int b);
extern void func_0200c2c8(unsigned int *p);
extern void func_0200f554(unsigned int *p);
extern void func_02010d64(unsigned int *p);
extern unsigned int data_020ccf94;

void func_ov003_02218f18(unsigned int *arg0)
{
    func_ov003_02218f54(arg0);
    if (func_02073908(data_020ccf94, arg0[0x200])) {
        func_0200c2c8(arg0);
    } else {
        func_0200f554(arg0);
    }
    func_02010d64(arg0);
}
