/* func_ov003_0221f424 @ 0x0221f424, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221f5ac(int unused0);
extern void func_02055e7c(int, int);

int func_ov003_0221f424(int param)
{
    int result;
    if (func_ov003_0221f5ac(param) != 0) {
        func_02055e7c(param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
