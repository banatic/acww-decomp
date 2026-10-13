/* func_ov130_0229a678 @ 0x0229a678, 0x60 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002c6c(const void *, void *, void *, int, int, int);
extern void func_02002d14(const void *, void *, void *, int, int, int);
extern void *data_021fbe94;
extern const unsigned char data_ov130_0229ac80[];
extern const unsigned char data_ov130_0229ac94[];
extern const unsigned char data_ov130_0229aca8[];

void func_ov130_0229a678(void *arg)
{
    void *v;

    v = data_021fbe94;
    func_02002c6c(data_ov130_0229ac80, v, arg, 0x10, 0x10, 0xff);
    func_02002c6c(data_ov130_0229ac94, v, arg, 0x100, 0x100, 0x1a9);
    func_02002d14(data_ov130_0229aca8, v, arg, 1, 1, 0xd);
}
