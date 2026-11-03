/* design_editor_7: 4 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229b508 @ 0x0229b508, 0x64 bytes, Thumb
 * func_ov123_0229b41c @ 0x0229b41c, 0xec bytes, Thumb
 * func_ov123_0229b3c4 @ 0x0229b3c4, 0x58 bytes, Thumb
 * func_ov123_0229b384 @ 0x0229b384, 0x40 bytes, Thumb
 */

extern void *func_020984e8(void);
extern void *func_020996b8(void *);
extern void *func_0206fc8c(void);
extern void *func_02072bb0(void *, void *);
extern void *func_02072da0(void *);
extern void MIi_CpuCopy32(void *, void *, unsigned int);
extern unsigned int func_02072d4c(void *);
extern void *func_02072f74(void *);
extern void func_ov123_0229b0dc(void *, void *);
extern int func_ov123_02299d9c(unsigned char *);
extern void func_02072d84(int, int);
extern void func_02072f38(int);
extern void func_02072f54(int, int);
extern int func_02072ba4(int);
extern int func_02072b64(int, int);
extern unsigned short *func_02099710(int);
extern unsigned short *func_020996f8(int);
extern void func_ov123_02299640(unsigned char *, int);
extern void *func_02088220(void *);
extern unsigned char data_021f3278[];

void func_ov123_0229b508(char *arg0)
{
    void *r4;

    r4 = func_020996b8(func_020984e8());
    r4 = func_02072bb0(r4, func_0206fc8c());
    MIi_CpuCopy32(func_02072da0(r4), arg0 + 0xa30, 0x200);
    MIi_CpuCopy32(func_02072da0(r4), arg0 + 0xc30, 0x200);
    func_ov123_0229b0dc(arg0, func_02072f74((void *) func_02072d4c(r4)));
}

void func_ov123_0229b41c(unsigned char *self)
{
    int p7;
    int p6;
    unsigned int a;
    int r4;
    unsigned short *p1;
    unsigned short *p2;
    unsigned int flag1;
    unsigned int flag2;
    unsigned short val1;
    unsigned short val2;
    int idx1;
    int idx2;

    p7 = (int) func_020984e8();
    p6 = (int) func_020996b8((void *) p7);
    a = (int) func_0206fc8c();

    r4 = (int) func_02072bb0((void *) p6, (void *) a);
    func_02072d84(r4, func_ov123_02299d9c(self));
    func_02072f38((int) func_02072d4c((void *) r4));
    func_02072f54((int) func_02072d4c((void *) r4), self[0xa1]);
    r4 = func_02072b64(func_02072ba4(p6), a);

    p1 = func_02099710(p7);
    flag1 = 0;
    val1 = *p1;
    if (val1 >= 0x12a8 && val1 <= 0x12af) {
        flag1 = 1;
    }
    if (flag1 != 0) {
        idx1 = val1 - 0x12a8;
    } else {
        idx1 = -1;
    }
    if (idx1 != -1 && idx1 == r4) {
        func_ov123_02299640(self, 0x8000);
    }

    p2 = func_020996f8(p7);
    flag2 = 0;
    val2 = *p2;
    if (val2 >= 0x1429 && val2 <= 0x1430) {
        flag2 = 1;
    }
    if (flag2 != 0) {
        idx2 = val2 - 0x1429;
    } else {
        idx2 = -1;
    }
    if (idx2 != -1 && idx2 == r4) {
        func_ov123_02299640(self, 0x10000);
    }
}

void func_ov123_0229b3c4(char *arg)
{
    void *p = func_02088220((void *) data_021f3278);
    MIi_CpuCopy32(func_02072da0(p), (void *) (arg + 0xa30), 0x200);
    MIi_CpuCopy32(func_02072da0(p), (void *) (arg + 0xc30), 0x200);
    func_ov123_0229b0dc(arg, (void *) ((int) func_02072f74((void *) func_02072d4c(p))));
}

void func_ov123_0229b384(void *param)
{
    void *r4;
    r4 = func_02088220(data_021f3278);
    func_02072d84((int) r4, (int) ((void *) func_ov123_02299d9c((unsigned char *) param)));
    func_02072f38((int) ((void *) func_02072d4c(r4)));
    func_02072f54((int) ((void *) func_02072d4c(r4)), (unsigned char) (((unsigned char *) param)[0xa1]));
}
