/* func_ov004_0221ef70 @ 0x0221ef70, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221ef90(void);
extern void func_0203e0a8(int, int);

int func_ov004_0221ef70(int param)
{
    int result;
    if (func_ov004_0221ef90() != 0) {
        func_0203e0a8(param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
