/* func_0206f0d4 @ 0x0206f0d4, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern unsigned char data_021cfc10;
extern const char data_020df2d8[];
extern const char data_020df2f8[];
extern const char data_020df310[];

extern int func_02002ca4(const char *a, int b, int c);
extern int func_02064328(char *buf, const char *fmt, unsigned char c);
extern int func_02002d14(char *buf, int a, int b, int c, int d, int e);
extern int func_02002c6c(char *buf, int a, int b, int c, int d, int e);

int func_0206f0d4(int p)
{
    int g;
    char local[36];
    g = data_021fbe94;
    if (!func_02002ca4(data_020df2d8, g, p)) {
        return 0;
    }
    func_02064328(local, data_020df2f8, data_021cfc10);
    if (!func_02002d14(local, g, p, 0, 0, 0)) {
        return 0;
    }
    func_02064328(local, data_020df310, data_021cfc10);
    func_02002c6c(local, g, p, 0, 0, 0xf);
    return 1;
}
