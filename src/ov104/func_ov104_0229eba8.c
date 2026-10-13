/* func_ov104_0229eba8 @ 0x0229eba8, 0x36 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov104_0229c344(void *, int);
extern void func_ov104_0229eec8(void *);
extern void func_ov104_0229eb88(void *);

void func_ov104_0229eba8(void *param)
{
    if (func_ov002_02207f3c(param, 0)) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov104_0229c344(param, 0x80);
        func_ov104_0229eec8(param);
    } else {
        func_ov104_0229eb88(param);
    }
}
