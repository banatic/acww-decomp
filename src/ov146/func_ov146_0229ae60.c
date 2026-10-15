/* func_ov146_0229ae60 @ 0x0229ae60, 0x30 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov146_0229a724(void *p);
extern void func_ov146_0229a17c(void *p);
extern void func_ov146_0229adb8(void *p);

void func_ov146_0229ae60(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov146_0229a724(p);
    } else {
        func_ov146_0229a17c(p);
    }
    func_ov146_0229adb8(p);
}
