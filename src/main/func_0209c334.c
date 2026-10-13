/* func_0209c334 @ 0x0209c334, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209c51c(unsigned char *p, int a, int b);
extern int func_0209c4a8(unsigned char *p);
extern void func_0209c470(unsigned char *p, int n);
extern void func_0209e474(unsigned char *p);

void func_0209c334(unsigned char *p, int a, int b)
{
    func_0209c51c(p + 0x11, a, b);
    p[0x10] = (unsigned char) func_0209c4a8(p + 0x11);
    if (b) {
        func_0209c470(p + 0x11, p[0x10]);
    }
    func_0209e474(p);
    p += 8;
    func_0209e474(p);
}
