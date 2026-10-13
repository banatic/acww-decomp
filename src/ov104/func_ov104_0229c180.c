/* func_ov104_0229c180 @ 0x0229c180, 0xe0 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov104_0229f6d0;
extern void func_02066688(void *);
extern void func_0206e35c(void *);
extern void func_ov002_0220afdc(void *);
extern void func_ov002_0220b464(void *);
extern void func_ov002_0220ba0c(void *);
extern void func_ov002_02209ac8(void *);
extern void func_ov002_02209cb4(void *);
extern void func_ov002_02209e38(void *);
extern void func_ov002_02207e28(void *);
extern void func_ov094_0229a2d0(void *);
extern void func_ov094_0229bc30(void *);
extern void func_ov094_0229afe0(void *);
extern void func_ov002_0220826c(void *);
extern void func_02138c48(void *, int, int, void (*)(void *));

void *func_ov104_0229c180(void *self)
{
    *(void **) self = (void *) &data_ov104_0229f6d0;
    func_ov002_0220afdc((char *) self + 0x41b4);
    func_02138c48((char *) self + 0x37b4, 0xa, 0x100, func_02066688);
    func_02138c48((char *) self + 0x2db4, 0xa, 0x100, func_02066688);
    func_ov002_0220b464((char *) self + 0x2d3c);
    func_0206e35c((char *) self + 0x2a14);
    func_ov002_0220ba0c((char *) self + 0x28f8);
    func_ov002_02209ac8((char *) self + 0x2504);
    func_ov002_02209cb4((char *) self + 0x24a0);
    func_ov002_02209e38((char *) self + 0x2488);
    func_ov002_02207e28((char *) self + 0x23b8);
    func_ov094_0229a2d0((char *) self + 0x0d80);
    func_ov094_0229bc30((char *) self + 0x0d58);
    func_ov094_0229afe0((char *) self + 0x02f8);
    func_02066688((char *) self + 0x01c0);
    func_02066688((char *) self + 0xc0);
    func_ov002_0220826c(self);
    return self;
}
