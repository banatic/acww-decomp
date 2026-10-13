/* func_ov120_0229b97c @ 0x0229b97c, 0x60 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern const char data_ov120_0229c6b0[];
extern const char data_ov120_0229c6c8[];
extern const char data_ov120_0229c6e4[];
extern void func_02002d14(const char *data, void *obj, int a, int b, int c, int d);
extern void func_02002c6c(const char *data, void *obj, int a, int b, int c, int d);

void func_ov120_0229b97c(void)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov120_0229c6b0, p, 8, 6, 6, 14);
    func_02002c6c(data_ov120_0229c6c8, p, 8, 0xc0, 0xc0, 0xff);
    func_02002c6c(data_ov120_0229c6e4, p, 8, 0x180, 0x180, 0x1ff);
}
