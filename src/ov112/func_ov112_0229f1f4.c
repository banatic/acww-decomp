/* func_ov112_0229f1f4 @ 0x0229f1f4, 0x5c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8874(void *dst, void *src, int size);
extern void func_020a8a70(void *dst, void *src, int a, int b);
extern int func_020b4424(void *p);
extern void func_020a87e0(void *dst, void *src);
extern void func_0205182c(void *dst, void *src, int size);

void func_ov112_0229f1f4(void *self)
{
    char *base = (char *) self;
    char *p = base + 0xc4;
    func_020a8874(base + 0x4580, p, 0x60);
    func_020a8a70(base + 0x44ac, base + 0x4580, 0, 0);
    if (func_020b4424(base + 0x44ac) != 0) {
        func_020a87e0(base + 0x4580, base + 0x44ac);
        func_0205182c(base + 0x4580, p, 0x60);
    }
}
