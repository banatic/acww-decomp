/* func_020b6d20 @ 0x020b6d20, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b69c8(void);
extern void func_02091300(void);
extern void func_0208a0ac(void);
extern void func_020b5e88(void *);
extern void func_0203ecac(void);
extern int func_020b65c4(void);
extern void func_020398b0(void);
extern void func_02035240(void);
extern int data_021d3124;
extern int data_021f69d0;
extern int data_020dd828;

int func_020b6d20(void)
{
    volatile unsigned short *reg = (volatile unsigned short *) 0x04000008;

    func_020b69c8();
    func_02091300();
    *reg = (*reg & ~3) | 2;
    func_0208a0ac();
    data_021d3124 = 0;
    func_020b5e88(&data_021f69d0);
    data_020dd828 = 3;
    func_0203ecac();
    if (func_020b65c4() == 0x2e || func_020b65c4() == 0xd || func_020b65c4() == 0x2f) {
        func_020398b0();
    }
    func_02035240();
    return 1;
}
