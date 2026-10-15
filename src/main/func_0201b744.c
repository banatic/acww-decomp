/* func_0201b744 @ 0x0201b744, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c450(void *p);
extern void func_02019ff0(void *p);
extern void func_0201637c(void *p);
extern int func_0200441c(void *p);
extern void func_0201bf24(void *p, int n);

int func_0201b744(unsigned char *base)
{
    func_0201c450(base);
    func_02019ff0(base + 0x2ac);
    func_0201637c(base + 0x334);
    func_0200441c(base + 0x514);
    if (base[0x563] == 0) {
        func_0201bf24(base, 1);
    }
    return 1;
}
