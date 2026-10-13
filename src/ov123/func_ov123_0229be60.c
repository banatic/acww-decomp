/* func_ov123_0229be60 @ 0x0229be60, 0xa4 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern const char data_ov123_0229d258[];
extern const char data_ov123_0229d26c[];
extern const char data_ov123_0229d27c[];
extern const char data_ov123_0229d28c[];
extern const char data_ov123_0229d29c[];
extern const char data_ov123_0229d2b0[];

extern void func_02002d14(const char *, const void *, int, int, int, int);
extern void func_02064af4(const char *, char *, int);
extern void func_02002b40(char *, int, int, int);
extern void func_02002ca4(const char *, const void *, int);
extern void func_02002c6c(const char *, const void *, int, int, int, int);

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
