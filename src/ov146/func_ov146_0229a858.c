/* func_ov146_0229a858 @ 0x0229a858, 0x44 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov146_02299b80(const void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov146_0229a464(void *p);
extern int func_ov146_0229a5e8(const void *p);
extern int func_ov146_0229a59c(const void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);

void func_ov146_0229a858(void *p)
{
    int a;
    int b;

    if (func_ov146_02299b80(p) != 0) {
        func_ov002_02208098(p, 3);
        func_ov146_0229a464(p);
    }

    a = func_ov146_0229a5e8(p);
    b = func_ov146_0229a59c(p);
    func_ov002_0220a0b4((char *) p + 0x15cc, a, b);
}
