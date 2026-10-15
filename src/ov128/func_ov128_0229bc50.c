/* func_ov128_0229bc50 @ 0x0229bc50, 0x38 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a05c(unsigned char *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov128_0229bc50(unsigned char *base, int a, int b)
{
    func_ov002_0220a05c(base + 0x110, a, b, 3, 1);
    base[0x2d6a] = base[0x8d];
    func_ov002_02208098((void *) (base), 7);
}
