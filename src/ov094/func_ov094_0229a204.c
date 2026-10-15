/* func_ov094_0229a204 @ 0x0229a204, 0x98 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov094_0229bedc[];
extern unsigned char data_ov094_0229bef8[];
extern unsigned char data_ov094_0229bf18[];
extern unsigned char data_ov094_0229bf38[];
extern unsigned char data_ov094_0229bf54[];
extern void *data_021fbe94;

extern int func_02002d14(const void *, void *, int, int, int, int);
extern int func_02064af4(const void *, void *, int);
extern int func_02002b40(void *, int, int, int);
extern int func_02002c6c(const void *, void *, int, int, int, int);

void func_ov094_0229a204(void *param1, int param2)
{
    void *g_ptr;
    const unsigned char *data;

    g_ptr = data_021fbe94;
    func_02002d14(data_ov094_0229bedc, g_ptr, ((unsigned char *) param1)[0xe], 0, 1, 13);

    data = param2 ? data_ov094_0229bef8 : data_ov094_0229bf18;
    func_02064af4(data, (char *) param1 + 0x1b8, 0x800);

    func_02002b40((char *) param1 + 0x1b8, ((unsigned char *) param1)[0xe], 0x800, 0);

    func_02002c6c(data_ov094_0229bf38, g_ptr, ((unsigned char *) param1)[0xe], 0, 0x10, 0xff);
    func_02002c6c(data_ov094_0229bf54, g_ptr, ((unsigned char *) param1)[0xe], 0x100, 0x100, 0x1ff);
}
