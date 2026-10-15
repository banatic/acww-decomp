/* func_ov127_02299f90 @ 0x02299f90, 0x44 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002d14(const void *a, void *b, int c, int d, int e, int f);
extern int func_02002c6c(const void *a, void *b, int c, int d, int e, int f);
extern void *data_021fbe94;
extern const char data_ov127_0229b634[];
extern const char data_ov127_0229b64c[];

void func_ov127_02299f90(void)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov127_0229b634, p, 8, 5, 5, 9);
    func_02002c6c(data_ov127_0229b64c, p, 8, 0xc0, 0xc0, 0x13f);
}
