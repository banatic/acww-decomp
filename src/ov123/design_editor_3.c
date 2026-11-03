/* design_editor_3: 4 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_02299e84 @ 0x02299e84, 0x24 bytes, Thumb
 * func_ov123_02299e28 @ 0x02299e28, 0x5c bytes, Thumb
 * func_ov123_02299dc4 @ 0x02299dc4, 0x64 bytes, Thumb
 * func_ov123_02299d9c @ 0x02299d9c, 0x28 bytes, Thumb
 */

extern void func_020b9ccc(void *p);
extern void func_ov123_02299630(void *self, int a);
extern int func_ov123_02299650(void *self, int a);
extern void func_ov123_02299640(void *self, int a);
extern void MIi_CpuCopy32(void *dst, void *src, int size);
extern void func_0200467c(int cmd);

void func_ov123_02299e84(void *p)
{
    int i = 0;
    char *base = (char *) p + 0x124;
    for (; i < 3; i++) {
        func_020b9ccc(base + i * 0x38);
    }
}

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

void func_ov123_02299dc4(void *arg)
{
    if (func_ov123_02299650(arg, 0x80)) {
        func_ov123_02299630(arg, 0x80);
    } else {
        func_ov123_02299640(arg, 0x80);
    }

    if (func_ov123_02299650(arg, 0x4000)) {
        func_0200467c(0x86c);
        func_ov123_02299630(arg, 0x4000);
    } else {
        func_0200467c(0x86b);
        func_ov123_02299640(arg, 0x4000);
    }

    func_ov123_02299640(arg, 0x40);
}

char *func_ov123_02299d9c(char *p)
{
    if (func_ov123_02299650(p, 0x80)) {
        return p + 0xa30;
    }
    return p + 0xc30;
}
