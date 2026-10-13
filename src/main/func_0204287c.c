/* func_0204287c @ 0x0204287c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02042a08(void *a, void *b, void *c, int d);
extern int func_020644cc(int a);
extern void *MI_CpuFill8(void *s, int c, int n);
extern void func_02042954(void *a, int b, void *c, void *d, int e, void *f);
extern void func_020429a0(void *a, void *b, void *c, int d);
extern unsigned char data_020db870;
extern void MI_CpuCopy8(void *src, void *dst, int n);

void func_0204287c(char *a, char *b, char *c)
{
    unsigned char buf[0x4c];
    unsigned char arr[8];
    int ret;

    ret = func_02042a08(a, buf, b + 0x17260, 0x4c);
    if (ret == 0) {
        ret = 0x4c;
        MI_CpuFill8(buf, 0, ret);
    }
    ret = func_020644cc(ret);
    MI_CpuCopy8(c, arr, 8);
    func_02042954(a, ret, &data_020db870, buf, 0x4c, arr);
    func_020429a0(a, b + 0x17260, buf, 0xa);
}
