/* func_020ba3bc @ 0x020ba3bc, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_020bb1d4(void *, void *);
extern void func_0209e100(void *, int);
extern int func_020bb214(void *, void *);
extern void MI_CpuCopy8(void *, const void *, int);
extern void func_0209e29c(void *, int);
extern void func_0209e234(void *, int);
extern int func_0209e3ac(void *, const void *, int);
extern unsigned char data_021f75b0;

void func_020ba3bc(unsigned char *dst, int num, int idx)
{
    int local[2];
    int ret;

    local[0] = 0;
    local[1] = 0;

    func_0209e474(local);
    func_020bb1d4(&data_021f75b0, local);
    func_0209e100(local, 6);
    ret = func_020bb214(&data_021f75b0, local);
    MI_CpuCopy8(local, dst, 8);

    if (num < 0) {
        num += 0x200;
    }
    if (num < ret) {
        num += 0x200;
    }

    func_0209e29c(dst, (num - ret) / 8);

    if (idx < 0) {
        idx = 0;
    } else if (idx > 0x68) {
        idx = 0x68;
    }

    dst[2] = 0x12;
    dst[1] = 0;
    dst[0] = 0;

    func_0209e234(dst, idx * 0x2d0 / 0x68);

    if (dst[2] == 6) {
        func_0209e100(dst, 1);
    }

    func_0209e474(local);
    func_0209e234(local, 0x1e);

    if (func_0209e3ac(local, dst, 0x3c) == 1) {
        func_0209e29c(dst, 0x40);
    }
}
