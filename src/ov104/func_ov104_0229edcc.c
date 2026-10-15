/* func_ov104_0229edcc @ 0x0229edcc, 0x28 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *arg, int param);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov104_0229dd00(void *arg);
extern void func_ov104_0229eb48(void *arg);

void func_ov104_0229edcc(void *arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0((void *) (arg), 2);
        func_ov104_0229dd00(arg);
    }
    func_ov104_0229eb48(arg);
}
