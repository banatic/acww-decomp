/* func_ov101_0229cf80 @ 0x0229cf80, 0x20 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern void func_ov101_0229cfa0(int arg);
extern void func_ov101_0229cfd4(int arg);

void func_ov101_0229cf80(int arg)
{
    if (func_0206fe60() != 0) {
        func_ov101_0229cfd4(arg);
    } else {
        func_ov101_0229cfa0(arg);
    }
}
