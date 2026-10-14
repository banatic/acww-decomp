/* func_ov106_0229c180 @ 0x0229c180, 0xe0 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void *p);
extern void func_ov002_0220afdc(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void *));
extern void func_ov002_0220b464(void *p);
extern void func_0206e35c(void *p);
extern void func_ov002_0220ba0c(void *p);
extern void func_ov002_02209ac8(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_02209e38(void *p);
extern void func_ov002_02207e28(void *p);
extern void func_ov094_0229a2d0(void *p);
extern void func_ov094_0229bc30(void *p);
extern void func_ov094_0229afe0(void *p);
extern void func_ov002_0220826c(void *p);
extern char data_ov106_0229f6e0[];

void *func_ov106_0229c180(char *self)
{
    *(void **) self = data_ov106_0229f6e0;

    func_02066688(self + 0x4280);
    func_02066688(self + 0x4180);
    func_ov002_0220afdc(self + 0x3fb4);
    __cxa_vec_cleanup(self + 0x35b4, 0xa, 0x100, func_02066688);
    __cxa_vec_cleanup(self + 0x2bb4, 0xa, 0x100, func_02066688);
    func_ov002_0220b464(self + 0x2b3c);
    func_0206e35c(self + 0x2814);
    func_ov002_0220ba0c(self + 0x26f8);
    func_ov002_02209ac8(self + 0x2304);
    func_ov002_02209cb4(self + 0x22a0);
    func_ov002_02209e38(self + 0x2288);
    func_ov002_02207e28(self + 0x21b8);
    func_ov094_0229a2d0(self + 0xb80);
    func_ov094_0229bc30(self + 0xb58);
    func_ov094_0229afe0(self + 0xf8);
    func_ov002_0220826c(self);
    return self;
}
