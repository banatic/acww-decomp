/* design_editor_8: 6 functions, module ov123
 * mwccarm 1.2/base -O4,s
 * func_ov123_0229bf88 @ 0x0229bf88, 0x8 bytes, Thumb
 * func_ov123_0229bf64 @ 0x0229bf64, 0x24 bytes, Thumb
 * func_ov123_0229bf50 @ 0x0229bf50, 0x14 bytes, Thumb
 * func_ov123_0229bf04 @ 0x0229bf04, 0x4c bytes, Thumb
 * func_ov123_0229be60 @ 0x0229be60, 0xa4 bytes, Thumb
 * func_ov123_0229bdfc @ 0x0229bdfc, 0x64 bytes, Thumb
 */

extern void func_ov002_0220af74(void *);
extern void func_ov123_0229a1e8(void *);
extern void func_ov123_0229a1f4(void *);
extern void func_ov123_0229b1a0(int);
extern void func_ov123_0229a2b4(int);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void *data_021fbe94;
extern const char data_ov123_0229d258[];
extern const char data_ov123_0229d26c[];
extern const char data_ov123_0229d27c[];
extern const char data_ov123_0229d28c[];
extern const char data_ov123_0229d29c[];
extern const char data_ov123_0229d2b0[];
extern int func_02002d14(const char *, const void *, int, int, int, int);
extern int func_02064af4(const char *, char *, int);
extern int func_02002b40(char *, int, int, int);
extern int func_02002ca4(const char *, const void *, int);
extern int func_02002c6c(const char *, const void *, int, int, int, int);
extern const char data_ov123_0229d21c[];
extern const char data_ov123_0229d230[];
extern const char data_ov123_0229d244[];

void func_ov123_0229bf50(int arg);

void func_ov123_0229bf88(int arg0)
{
    func_ov123_0229bf50(arg0);
}

void func_ov123_0229bf64(void *arg0)
{
    func_ov002_0220af74((char *) arg0 + 0x5030);
    func_ov123_0229a1e8(arg0);
    func_ov123_0229a1f4(arg0);
}

void func_ov123_0229bf50(int arg)
{
    func_ov123_0229b1a0(arg);
    func_ov123_0229a2b4(arg);
}

void func_ov123_0229bf04(void)
{
    func_02001c08(0);
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 2);
    func_020028bc(4, 0, 0, 0);
    func_020029e8(3, 2);
    func_020028bc(3, 0, 0, 0);
}

void func_ov123_0229be60(char *self)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov123_0229d258, p, 6, 4, 4, 0xe);
    func_02064af4(data_ov123_0229d26c, self + 0x230, 0x800);
    func_02002b40(self + 0x230, 6, 0x800, 0);
    func_02002ca4(data_ov123_0229d27c, p, 4);
    func_02002ca4(data_ov123_0229d28c, p, 3);
    func_02002c6c(data_ov123_0229d29c, p, 6, 0x120, 0x120, 0x1ff);
    func_02002c6c(data_ov123_0229d2b0, p, 6, 0x10, 0x10, 0x1f);
}

void func_ov123_0229bdfc(void *receiver)
{
    void *p = data_021fbe94;
    func_02002d14((const char *) data_ov123_0229d21c, p, 8, 4, 4, 0xc);
    func_02002c6c((const char *) data_ov123_0229d230, p, 8, 0xc0, 0xc0, 0x12f);
    func_02002c6c((const char *) data_ov123_0229d244, p, 8, 0x130, 0x130, 0x19f);
}
