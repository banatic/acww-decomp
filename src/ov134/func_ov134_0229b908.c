/* func_ov134_0229b908 @ 0x0229b908, 0x4c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209de88(unsigned char a, unsigned char b, unsigned char c);
extern void func_ov134_0229b63c(unsigned char *a, unsigned char b, int c, int d, int e, int f, int g, int h);
extern unsigned char data_ov134_0229bf6c[];

void func_ov134_0229b908(unsigned char *X)
{
    int local0;
    local0 = data_ov134_0229bf6c[func_0209de88(X[0xBD], X[0xBC], X[0xBB])];
    func_ov134_0229b63c(X, X[0xA3], 424, 7, local0, 1, 15, 0);
}
