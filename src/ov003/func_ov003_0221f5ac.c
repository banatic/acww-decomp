/* func_ov003_0221f5ac @ 0x0221f5ac, 0x2a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221f5e0(int arg);
extern int func_ov003_0221f5d8(int arg);

int func_ov003_0221f5ac(int arg)
{
    if (func_ov003_0221f5e0(arg) != -1 && func_ov003_0221f5d8(arg) != -1) {
        return 1;
    } else {
        return 0;
    }
}
