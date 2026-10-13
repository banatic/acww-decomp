/* func_ov130_0229a00c @ 0x0229a00c, 0x64 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088df8(int a, const void *b, int c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);
extern const char data_ov130_0229aae0[];
extern const char data_ov130_0229ab70[];

void func_ov130_0229a00c(void *param)
{
    void *p = (char *) param + 0x60;
    func_02088df8(1, data_ov130_0229aae0, 0x80, p, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, data_ov130_0229ab70, 0x80, p, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
