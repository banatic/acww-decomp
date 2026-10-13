/* func_ov104_0229c378 @ 0x0229c378, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
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
