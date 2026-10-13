/* func_ov104_0229dd00 @ 0x0229dd00, 0x20 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov104_0229dd54(int);
extern void func_ov104_0229dd20(int);

void func_ov104_0229dd00(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov104_0229dd54(r4);
    } else {
        func_ov104_0229dd20(r4);
    }
}
