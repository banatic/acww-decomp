/* func_ov109_0229ca7c @ 0x0229ca7c, 0x34 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ccb4(void);
extern int func_ov109_0229cc98(int, int);
extern int func_ov094_0229aaac(int, int);

int func_ov109_0229ca7c(int a, int b)
{
    int result;
    if (func_ov109_0229ccb4() != 0) {
        result = func_ov094_0229aaac(a + 0xcc, func_ov109_0229cc98(a, b));
    } else {
        result = 0x0000fff1;
    }
    return result;
}
