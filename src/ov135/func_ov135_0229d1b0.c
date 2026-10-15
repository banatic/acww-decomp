/* func_ov135_0229d1b0 @ 0x0229d1b0, 0x28 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov135_0229ca1c(int a);
extern void func_ov135_0229d128(int a);

void func_ov135_0229d1b0(int a)
{
    if (func_ov002_02207f48(a, 0)) {
        func_ov002_022080a0((void *) (a), 2);
        func_ov135_0229ca1c(a);
    }
    func_ov135_0229d128(a);
}
