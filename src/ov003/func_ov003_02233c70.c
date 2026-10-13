/* func_ov003_02233c70 @ 0x02233c70, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int a);

short func_ov003_02233c70(int a, int b)
{
    unsigned char v = func_020644cc(a);
    if (v != 0) {
        if (b != 0) {
            if (func_020644cc(0x64) > 0x32) {
                return v * -0x38e;
            }
        }
        return v * 0x38e;
    }
    return 0;
}
