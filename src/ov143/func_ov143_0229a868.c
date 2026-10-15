/* func_ov143_0229a868 @ 0x0229a868, 0x74 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern const unsigned char data_ov143_0229b260[];
extern const unsigned char data_ov143_0229b274[];
extern const unsigned char data_ov143_0229b288[];
extern const unsigned char data_ov143_0229b2a0[];
extern int func_02002c6c(const unsigned char *, int, int, int, int, int);
extern int func_02002d14(const unsigned char *, int, int, int, int, int);
extern int func_02002ca4(const unsigned char *, int, int);
extern int func_02064af4(const unsigned char *, const unsigned char *, int);
extern int func_02002b40(const unsigned char *, int, int, int);

void func_ov143_0229a868(unsigned char *arg0)
{
    int g = data_021fbe94;
    func_02002c6c(data_ov143_0229b260, g, 6, 0x11, 0x11, 0x9c);
    func_02002d14(data_ov143_0229b274, g, 6, 1, 1, 6);
    func_02002ca4(data_ov143_0229b288, g, 6);
    func_02064af4(data_ov143_0229b2a0, arg0 + 0x99c, 0x800);
    func_02002b40(arg0 + 0x99c, 4, 0x800, 0);
}
