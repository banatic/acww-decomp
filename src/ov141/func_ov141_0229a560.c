/* func_ov141_0229a560 @ 0x0229a560, 0x20 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov141_0229a59c(int);
extern void func_ov141_0229a580(int);

void func_ov141_0229a560(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov141_0229a59c(r4);
    } else {
        func_ov141_0229a580(r4);
    }
}
