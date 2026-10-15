/* func_ov095_0229bfd8 @ 0x0229bfd8, 0x28 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002b40(void *ptr, int a, int b, int c);
extern void func_ov095_022999a0(void *ptr, int a);

void func_ov095_0229bfd8(void *base, int arg)
{
    func_02002b40((char *) base + 0x2428, arg, 0x800, 0);
    func_ov095_022999a0(base, 1);
}
