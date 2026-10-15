/* func_ov115_0229e454 @ 0x0229e454, 0x28 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *, int kind);
extern unsigned char *func_ov002_022080a0(void *, unsigned char v);
extern void func_ov115_0229df6c(int arg);
extern void func_ov115_0229e3a8(void *);

void func_ov115_0229e454(void *r0)
{
    if (func_ov002_02207f48(r0, 0) != 0) {
        func_ov002_022080a0(r0, 2);
        func_ov115_0229df6c((int) r0);
    }
    func_ov115_0229e3a8(r0);
}
