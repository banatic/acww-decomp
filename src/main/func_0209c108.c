/* func_0209c108 @ 0x0209c108, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c4a8(unsigned char *);
extern int func_0209c38c(int);
extern void func_0209c32c(unsigned char *, int);
extern void func_0209c470(unsigned char *, int);
extern void func_0209e474(unsigned char *);
extern void MI_CpuCopy8(void *, void *, int);

int func_0209c108(unsigned char *p)
{
    int r4;

    if (p[0x10] != 8) {
        goto fail;
    }
    r4 = func_0209c4a8(p + 0x11);
    if (func_0209c38c(r4) == 0) {
        goto fail;
    }
    func_0209c32c(p, r4);
    func_0209c470(p + 0x11, r4);
    p[0x21] &= ~1;
    func_0209e474(p);
    MI_CpuCopy8(p, p + 8, 8);
    return r4;
fail:
    return 0xc;
}
