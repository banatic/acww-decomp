/* screen_object: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221b808 @ 0x0221b808, 0x4 bytes, Thumb
 * func_ov003_0221b7f0 @ 0x0221b7f0, 0x18 bytes, Thumb
 */

extern int func_0206fbc0(void);
extern int func_0203e020(int);

int func_ov003_0221b808(void *object)
{
    return 1;
}

void func_ov003_0221b7f0(int param)
{
    if (func_0206fbc0() == 0) {
        return;
    }
    func_0203e020(param);
}
