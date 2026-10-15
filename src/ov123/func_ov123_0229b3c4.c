/* func_ov123_0229b3c4 @ 0x0229b3c4, 0x58 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02088220(void *);
extern void *func_02072da0(void *);
extern unsigned int func_02072d4c(void *);
extern int func_02072f74(void *);
extern void func_ov123_0229b0dc(void *, int);
extern void MIi_CpuCopy32(void *, const void *, unsigned int);

extern unsigned char data_021f3278[];

void func_ov123_0229b3c4(char *arg)
{
    void *p = func_02088220((void *) data_021f3278);
    MIi_CpuCopy32(func_02072da0(p), arg + 0xa30, 0x200);
    MIi_CpuCopy32(func_02072da0(p), arg + 0xc30, 0x200);
    func_ov123_0229b0dc(arg, func_02072f74((void *) func_02072d4c(p)));
}
