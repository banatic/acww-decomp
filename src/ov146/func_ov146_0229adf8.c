/* func_ov146_0229adf8 @ 0x0229adf8, 0x30 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern int func_ov002_022080a0(void *, int);
extern int func_ov146_0229adb8(void *);

int func_ov146_0229adf8(void *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        return func_ov002_022080a0(p, 5);
    } else {
        return func_ov146_0229adb8(p);
    }
}
