/* func_ov123_02299e28 @ 0x02299e28, 0x5c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_02299630(void *self, int a);
extern int func_ov123_02299650(void *self, int a);
extern void func_ov123_02299640(void *self, int a);
extern void MIi_CpuCopy32(void *dst, void *src, int size);

void func_ov123_02299e28(void *self)
{
    func_ov123_02299630(self, 0x4000);
    if (func_ov123_02299650(self, 0x80)) {
        MIi_CpuCopy32((char *) self + 0xa30, (char *) self + 0xc30, 0x200);
        func_ov123_02299630(self, 0x80);
    } else {
        MIi_CpuCopy32((char *) self + 0xc30, (char *) self + 0xa30, 0x200);
        func_ov123_02299640(self, 0x80);
    }
}
