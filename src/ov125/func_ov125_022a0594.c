/* func_ov125_022a0594 @ 0x022a0594, 0x38 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int arg);
extern void func_020027f0(int arg);
extern void func_ov125_0229f74c(void *p, int arg);
extern void func_ov002_022080a0(void *p, int arg);
extern void func_ov125_022a0564(void *p);

void func_ov125_022a0594(void *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_020027f0(4);
        func_ov125_0229f74c(p, 1);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov125_022a0564(p);
    }
}
