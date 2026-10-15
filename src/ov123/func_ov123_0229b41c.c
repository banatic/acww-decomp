/* func_ov123_0229b41c @ 0x0229b41c, 0xec bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void *func_020996b8(void *object);
extern int func_0206fc8c(void);
extern int func_02072bb0(int, int);
extern int func_ov123_02299d9c(unsigned char *);
extern int func_02072d84(int, int);
extern int func_02072d4c(int);
extern void func_02072f38(int);
extern void func_02072f54(int, int);
extern int func_02072ba4(int);
extern int func_02072b64(int, int);
extern unsigned short *func_02099710(int);
extern unsigned short *func_020996f8(int);
extern void func_ov123_02299640(unsigned char *, int);

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

    p7 = func_020984e8();
    p6 = (int) func_020996b8((void *) p7);
    a = func_0206fc8c();

    r4 = func_02072bb0(p6, a);
    func_02072d84(r4, func_ov123_02299d9c(self));
    func_02072f38(func_02072d4c(r4));
    func_02072f54(func_02072d4c(r4), self[0xa1]);
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
