/* func_ov114_0229d688 @ 0x0229d688, 0x78 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002d14(const void *data, void *p, int a, int b, int c, int d);
extern void func_02002c6c(const void *data, void *p, int a, int b, int c, int d);
extern void *data_021fbe94;
extern const char data_ov114_0229dbcc[];
extern const char data_ov114_0229dbe4[];
extern const char data_ov114_0229dbf8[];
extern const char data_ov114_0229dc0c[];

void func_ov114_0229d688(void)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov114_0229dbcc, p, 8, 7, 7, 14);
    func_02002d14(data_ov114_0229dbe4, p, 8, 4, 4, 6);
    func_02002c6c(data_ov114_0229dbf8, p, 8, 0xc0, 0xc0, 0x140);
    func_02002c6c(data_ov114_0229dc0c, p, 8, 0x141, 0x141, 0x1bf);
}
