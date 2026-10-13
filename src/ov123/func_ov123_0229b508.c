/* func_ov123_0229b508 @ 0x0229b508, 0x64 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *);
extern void *func_020996b8(void *);
extern void *func_0206fc8c(void);
extern void *func_02072bb0(void *, void *);
extern void *func_02072da0(void *);
extern void MIi_CpuCopy32(void *, void *, unsigned int);
extern void func_02072d4c(void *);
extern void *func_02072f74(void);
extern void func_ov123_0229b0dc(void *, void *);

void func_ov123_0229b508(char *arg0)
{
    void *r4;

    r4 = func_020996b8(func_020984e8(arg0));
    r4 = func_02072bb0(r4, func_0206fc8c());
    MIi_CpuCopy32(func_02072da0(r4), arg0 + 0xa30, 0x200);
    MIi_CpuCopy32(func_02072da0(r4), arg0 + 0xc30, 0x200);
    func_02072d4c(r4);
    func_ov123_0229b0dc(arg0, func_02072f74());
}
