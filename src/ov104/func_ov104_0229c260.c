/* func_ov104_0229c260 @ 0x0229c260, 0xe4 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov104_0229f6d0;
extern void __cxa_vec_cleanup(void *dest, int a, int b, void *cb);
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_0220b464(void *p);
extern void *func_0206e35c(void *p);
extern void *func_ov002_0220ba0c(void *p);
extern void *func_ov002_02209ac8(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void func_ov002_02209e38(void *p);
extern void *func_ov002_02207e28(void *p);
extern void *func_ov094_0229a2d0(void *p);
extern void func_ov094_0229bc30(void *p);
extern void *func_ov094_0229afe0(void *p);
extern void func_02066688(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);

void *func_ov104_0229c260(void *self)
{
    *(void **) self = (void *) &data_ov104_0229f6d0;
    func_ov002_0220afdc((char *) self + 0x41b4);
    __cxa_vec_cleanup((char *) self + 0x37b4, 0xa, 0x100, (void *) func_02066688);
    __cxa_vec_cleanup((char *) self + 0x2db4, 0xa, 0x100, (void *) func_02066688);
    func_ov002_0220b464((char *) self + 0x2d3c);
    func_0206e35c((char *) self + 0x2a14);
    func_ov002_0220ba0c((char *) self + 0x28f8);
    func_ov002_02209ac8((char *) self + 0x2504);
    func_ov002_02209cb4((char *) self + 0x24a0);
    func_ov002_02209e38((char *) self + 0x2488);
    func_ov002_02207e28((char *) self + 0x23b8);
    func_ov094_0229a2d0((char *) self + 0xd80);
    func_ov094_0229bc30((char *) self + 0xd58);
    func_ov094_0229afe0((char *) self + 0x2f8);
    func_02066688((char *) self + 0x1c0);
    func_02066688((char *) self + 0xc0);
    func_ov002_0220826c((char *) self + 0x0);
    func_ov002_02207f6c((char *) self + 0x0);
    return self;
}
