/* func_ov101_0229d8a8 @ 0x0229d8a8, 0x38 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229caac(void *p);
extern int func_ov002_02207d5c(void *p);
extern void func_ov002_022091cc(void *p);
extern void func_ov094_0229a05c(void *p);

void func_ov101_0229d8a8(void *p)
{
    func_ov002_022091cc((char *) p + 0x2300);
    func_ov094_0229a05c((char *) p + 0xb7c);
    if (func_ov002_02207d5c((char *) p + 0x21b4)) {
        func_ov101_0229caac(p);
    }
}
