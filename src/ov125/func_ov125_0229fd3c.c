/* func_ov125_0229fd3c @ 0x0229fd3c, 0x88 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov125_0229fe40(const void *self, unsigned char c);
extern int func_0206fe54(int x);
extern int func_ov125_0229fe4c(const void *self, unsigned char c);
extern void func_0208aa60(void *dst, int a, int b);
extern int func_02062e50(void *p);
extern int func_020984e8(int x);
extern int func_020996b8(int x);
extern int func_02072bb0(int x, unsigned char c);
extern int func_02072d4c(int x);
extern int func_02072ea4(int x, void *p);
extern void func_0208aecc(void *p);
extern void func_02051984(void *dst, void *src);
extern void func_0208aa48(void *dst, void *src);
extern void func_0208aeb8(void *p);
extern void func_02062e00(void *p);

void func_ov125_0229fd3c(void *self)
{
    unsigned char a[0x24];
    unsigned char b[0x30];
    int v, r4;

    v = func_ov125_0229fe40(self, *((unsigned char *) self + 0x87a));
    r4 = v - 0x84;
    if (func_0206fe54(v)) {
        r4 -= 0xa;
    }

    func_0208aa60((char *) self + 0x574, func_ov125_0229fe4c(self, *((unsigned char *) self + 0x87a)) - 0x78, r4);

    func_02072ea4(
        func_02072d4c(func_02072bb0(func_020996b8(func_020984e8(func_02062e50(a))), *((unsigned char *) self + 0x87a))), a);

    func_0208aecc(b);
    func_02051984(b, a);
    func_0208aa48((char *) self + 0x574, b);
    func_0208aeb8(b);
    func_02062e00(a);
}
