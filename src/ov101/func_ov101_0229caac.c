/* func_ov101_0229caac @ 0x0229caac, 0x6c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229cd08(unsigned char *, unsigned char);
extern int func_ov101_0229ccd0(unsigned char *, unsigned char);
extern int func_0206fe54(int);
extern void func_0208aa60(unsigned char *, int, int);
extern int func_ov101_0229ce38(unsigned char *, unsigned char);
extern int func_ov101_0229ce1c(unsigned char *, unsigned char);
extern void func_ov094_0229abb8(unsigned char *, unsigned char *, int);

void func_ov101_0229caac(unsigned char *p)
{
    int ret1;
    int v1;
    int ret2;
    int v2;
    int ret3;

    ret1 = func_ov101_0229cd08(p, p[0xb1]);
    v1 = ret1 - 0x6d;
    ret2 = func_ov101_0229ccd0(p, p[0xb1]);
    v2 = ret2 - 0x78;
    if (func_0206fe54(ret2) != 0) {
        v2 -= 8;
    }
    func_0208aa60(p + 0x21b4, v1, v2);
    if (func_ov101_0229ce38(p, p[0xb1]) != 0) {
        ret3 = func_ov101_0229ce1c(p, p[0xb1]);
        func_ov094_0229abb8(p + 0xf4, p + 0x21b4, ret3);
    }
}
