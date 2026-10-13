/* func_ov113_0229a2c4 @ 0x0229a2c4, 0x68 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021fbe94;
extern char data_ov113_0229ad18;
extern char data_ov113_0229ad2c;
extern char data_ov113_0229ad40;

extern void func_02002d14(const char *a, unsigned int b, int c, int d, int e, int f);
extern void func_02064af4(const char *a, void *b, int c);
extern void func_02002b40(void *a, int b, int c, int d);
extern void func_02002c6c(const char *a, unsigned int b, int c, int d, int e, int f);

void func_ov113_0229a2c4(void *arg0)
{
    unsigned int temp;
    char *p;

    temp = data_021fbe94;
    p = (char *) arg0;

    func_02002d14(&data_ov113_0229ad18, temp, 2, 8, 8, 14);
    func_02064af4(&data_ov113_0229ad2c, p + 0xa0, 0x800);
    p += 0xa0;
    func_02002b40(p, 2, 0x800, 0);
    func_02002c6c(&data_ov113_0229ad40, temp, 2, 16, 16, 319);
}
