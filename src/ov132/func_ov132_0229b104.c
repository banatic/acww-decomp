/* func_ov132_0229b104 @ 0x0229b104, 0x20 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov132_0229b140(int);
extern void func_ov132_0229b124(int);

void func_ov132_0229b104(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov132_0229b140(r4);
    } else {
        func_ov132_0229b124(r4);
    }
}
