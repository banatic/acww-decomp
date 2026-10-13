/* func_ov100_0229cf30 @ 0x0229cf30, 0xa0 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d42c(void *, unsigned char);
extern int func_ov100_0229d3d8(void *, unsigned char);
extern int func_0206fe54(void);
extern void func_0208aa80(void *);
extern void func_0208aa78(void *);
extern void func_0208aa60(void *, int, int);
extern int func_ov100_0229d630(void *, unsigned char);
extern int func_ov100_0229d620(void *, unsigned char);
extern int func_ov100_0229d5d4(void *, unsigned char);
extern void func_ov094_0229abb8(void *, void *, int);

void func_ov100_0229cf30(unsigned char *self)
{
    int r6, r4;

    r6 = func_ov100_0229d42c(self, *(unsigned char *) (self + 0x291f)) - 0x6d;
    r4 = func_ov100_0229d3d8(self, *(unsigned char *) (self + 0x291f)) - 0x78;

    if (func_0206fe54() != 0) {
        r4 -= 8;
    }

    if (r4 < -92) {
        func_0208aa80(self + 0x218c);
        r4 = func_ov100_0229d3d8(self, *(unsigned char *) (self + 0x291f)) - 0x50;
    } else {
        func_0208aa78(self + 0x218c);
    }

    func_0208aa60(self + 0x218c, r6, r4);

    if (func_ov100_0229d630(self, *(unsigned char *) (self + 0x291f)) != 0 ||
        func_ov100_0229d620(self, *(unsigned char *) (self + 0x291f)) != 0) {
        int tmp = func_ov100_0229d5d4(self, *(unsigned char *) (self + 0x291f));
        func_ov094_0229abb8(self + 0xcc, self + 0x218c, tmp);
    }
}
