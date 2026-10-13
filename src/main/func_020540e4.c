/* func_020540e4 @ 0x020540e4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e95f8(void);
extern void func_020540c0(void);
extern void func_02041dc4(void);
extern void GX_SetBankForLCDC(unsigned int);
extern void MIi_CpuClearFast(unsigned int, unsigned int, unsigned int);
extern void func_02110aa0(void);
extern void func_02002ee8(void);
extern void func_020024cc(void);
extern void func_020b98dc(void);
extern void func_020b9990(void);

void func_020540e4(void)
{
    volatile unsigned int v1;
    volatile unsigned int v0;
    volatile unsigned int v2;

    func_020e95f8();
    func_020540c0();
    func_02041dc4();

    *(volatile unsigned short *) 0x04000304 = (*(volatile unsigned short *) 0x04000304 & 0xfffffdf1) | 0x20e;

    GX_SetBankForLCDC(0x1f7);

    v0 = 0;
    MIi_CpuClearFast(v0, 0x06800000, 0x00084000);

    func_02110aa0();

    v1 = 0xc0;
    MIi_CpuClearFast(v1, 0x07000000, 0x00000400);

    v2 = 0;
    MIi_CpuClearFast(v2, 0x05000000, 0x00000400);

    func_02002ee8();
    func_020024cc();
    func_020b98dc();
    func_020b9990();
}
