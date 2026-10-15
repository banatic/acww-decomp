/* func_ov108_0229d34c @ 0x0229d34c, 0x50 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov002_02209114(void *ptr, int b, int c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov108_0229d34c(unsigned char *base)
{
    if (func_0208e484(base + 0x2498) != 0) {
        unsigned char *p;
        func_ov002_02209114(base + 0x24fc, base[0x2b5], 1);
        p = base + base[0x2b5];
        base[0x2b4] = p[0x28e9];
        func_ov002_02208098((void *) (base), 0x14);
    }
}
