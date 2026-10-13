/* func_ov094_0229a098 @ 0x0229a098, 0x78 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002d14(const void *a, const void *b, int c, int d, int e, int f);
extern void func_02002c6c(const void *a, const void *b, int c, int d, int e, int f);
extern void *data_021fbe94;
extern char data_ov094_0229be58[];
extern char data_ov094_0229be78[];
extern char data_ov094_0229be90[];
extern char data_ov094_0229bea8[];

void func_ov094_0229a098(void)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov094_0229be58, p, 8, 4, 4, 6);
    func_02002d14(data_ov094_0229be78, p, 8, 7, 7, 0xe);
    func_02002c6c(data_ov094_0229be90, p, 8, 0xc0, 0xc0, 0x15f);
    func_02002c6c(data_ov094_0229bea8, p, 8, 0x160, 0x160, 0x1ff);
}
