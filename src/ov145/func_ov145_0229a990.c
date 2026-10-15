/* func_ov145_0229a990 @ 0x0229a990, 0x28 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int x);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov145_0229a310(void *p);
extern void func_ov145_0229a8e8(void *p);

void func_ov145_0229a990(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0((void *) (p), 2);
        func_ov145_0229a310(p);
    }
    func_ov145_0229a8e8(p);
}
