/* func_ov123_0229bdfc @ 0x0229bdfc, 0x64 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern const char data_ov123_0229d21c[];
extern const char data_ov123_0229d230[];
extern const char data_ov123_0229d244[];

extern void func_02002d14(const void *data, const void *ptr, int arg3, int arg4, int arg5, int arg6);
extern void func_02002c6c(const void *data, const void *ptr, int arg3, int arg4, int arg5, int arg6);

void func_ov123_0229bdfc(void)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov123_0229d21c, p, 8, 4, 4, 0xc);
    func_02002c6c(data_ov123_0229d230, p, 8, 0xc0, 0xc0, 0x12f);
    func_02002c6c(data_ov123_0229d244, p, 8, 0x130, 0x130, 0x19f);
}
