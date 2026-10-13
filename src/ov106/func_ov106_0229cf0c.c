/* func_ov106_0229cf0c @ 0x0229cf0c, 0x80 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d170(unsigned char *, unsigned char);
extern int func_ov106_0229d128(unsigned char *, unsigned char);
extern int func_0206fe54(void);
extern void func_0208aa60(unsigned char *, int, int);
extern int func_ov106_0229d3a0(unsigned char *, unsigned char);
extern int func_ov106_0229d390(unsigned char *, unsigned char);
extern int func_ov106_0229d360(unsigned char *, unsigned char);
extern void func_ov094_0229b9b4(unsigned char *, unsigned char *, int);

void func_ov106_0229cf0c(unsigned char *self)
{
    int v6;
    int v4;
    int v2;

    v6 = func_ov106_0229d170(self, self[0xb6]) - 0x6d;
    v4 = func_ov106_0229d128(self, self[0xb6]) - 0x78;
    if (func_0206fe54()) {
        v4 -= 8;
    }
    func_0208aa60(self + 0x21b8, v6, v4);

    if (func_ov106_0229d3a0(self, self[0xb6]) == 0) {
        if (func_ov106_0229d390(self, self[0xb6]) == 0) {
            return;
        }
    }

    v2 = func_ov106_0229d360(self, self[0xb6]);
    func_ov094_0229b9b4(self + 0x0b58, self + 0x21b8, v2);
}
