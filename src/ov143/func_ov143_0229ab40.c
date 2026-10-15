/* func_ov143_0229ab40 @ 0x0229ab40, 0x28 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov143_0229a2e0(void *p);
extern void func_ov143_0229aaac(void *p);

void func_ov143_0229ab40(void *p)
{
    if (func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0(p, 2);
        func_ov143_0229a2e0(p);
    }
    func_ov143_0229aaac(p);
}
