/* func_0209c270 @ 0x0209c270, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209c330(void *);
extern void func_0209c32c(void *, int);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, int);

void func_0209c270(unsigned char *arg0)
{
    if (func_0209c330(arg0) == 2) {
        arg0[0x21] = (arg0[0x21] & ~1) | 1;
    } else {
        arg0[0x21] = arg0[0x21] & ~1;
    }
    func_0209c32c(arg0, 8);
    func_0209e474(arg0);
    MI_CpuCopy8(arg0, arg0 + 8, 8);
}
