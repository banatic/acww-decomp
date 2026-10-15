/* func_ov145_0229a6c8 @ 0x0229a6c8, 0xb0 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021fbe94;

extern const unsigned char data_ov145_0229af10[];
extern const unsigned char data_ov145_0229af28[];
extern const unsigned char data_ov145_0229af40[];
extern const unsigned char data_ov145_0229af58[];
extern const unsigned char data_ov145_0229af70[];
extern const unsigned char data_ov145_0229af88[];

extern int func_02002c6c(const unsigned char *src, unsigned char *dst, int a, int b, int c, int d);
extern int func_02002d14(const unsigned char *src, unsigned char *dst, int a, int b, int c, int d);
extern int func_02064af4(const unsigned char *src, unsigned char *dst, int size);
extern int func_02002b40(unsigned char *dst, int val, int size, int flag);

void func_ov145_0229a6c8(unsigned char *self)
{
    unsigned char *p = data_021fbe94;

    func_02002c6c(data_ov145_0229af10, p, 6, 0x11, 0x11, 0x63);
    func_02002c6c(data_ov145_0229af28, p, 6, 0x26e, 0x26e, 0x27d);
    func_02002d14(data_ov145_0229af40, p, 6, 1, 1, 7);

    func_02064af4(data_ov145_0229af58, self + 0x24c6, 0x20);
    func_02064af4(data_ov145_0229af70, self + 0xcc6, 0x800);
    func_02064af4(data_ov145_0229af88, self + 0x1cc6, 0x800);

    func_02002b40(self + 0x1cc6, 6, 0x800, 0);
}
