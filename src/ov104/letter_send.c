/* letter_send: 6 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229c378 @ 0x0229c378, 0x64 bytes, Thumb
 * func_ov104_0229c364 @ 0x0229c364, 0x12 bytes, Thumb
 * func_ov104_0229c354 @ 0x0229c354, 0xe bytes, Thumb
 * func_ov104_0229c344 @ 0x0229c344, 0xe bytes, Thumb
 * func_ov104_0229c260 @ 0x0229c260, 0xe4 bytes, Thumb
 * func_ov104_0229c180 @ 0x0229c180, 0xe0 bytes, Thumb
 */

extern void *data_021c9b28; // at 0x021c9b28
extern void *data_020ccf94; // at 0x020ccf94
extern void *func_020e9958(void *, int);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern void func_020e993c(void *, void *);
extern void func_02070590(int);
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

int func_ov104_0229c378(int arg1, void *arg2)
{
    void *g1_l;
    void *g2_l;
    unsigned char *buf;

    g1_l = data_021c9b28;
    buf = func_020e9958(g1_l, 0x101);
    buf[0] = 8;
    MI_CpuCopy8(arg2, buf + 1, 0x100);
    g2_l = data_020ccf94;
    func_02073820(g2_l);
    func_020737f0(g2_l, buf, 0x101);
    func_02073770(g2_l, 0x16, 0);
    func_020e993c(g1_l, buf);
    func_02070590(8);
    return 1;
}

int func_ov104_0229c364(int r0, int r1)
{
    if (*(int *) (r0 + 0x94) & r1) {
        return 1;
    }
    return 0;
}

void func_ov104_0229c354(void *param1, unsigned int param2)
{
    unsigned int *ptr;
    ptr = (unsigned int *) ((char *) param1 + 0x94);
    *ptr |= param2;
}

void func_ov104_0229c344(void *param0, unsigned int param1)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) param0 + 0x94);
    val = *ptr;
    val &= ~param1;
    *((unsigned int *) ((char *) param0 + 0x94)) = val;
}

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

void *func_ov104_0229c180(void *self)
{
    *(void **) self = (void *) ((unsigned char *) &data_ov104_0229f6d0);
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
    func_ov094_0229a2d0((char *) self + 0x0d80);
    func_ov094_0229bc30((char *) self + 0x0d58);
    func_ov094_0229afe0((char *) self + 0x02f8);
    func_02066688((char *) self + 0x01c0);
    func_02066688((char *) self + 0xc0);
    func_ov002_0220826c(self);
    return self;
}
