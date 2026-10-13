/* func_ov004_02230438 @ 0x02230438, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222c3f4(void *, void *);
extern void func_ov004_0222c348(void *, void *);
extern void *func_ov004_0222c3a0(void *);
extern void *func_ov004_0222c33c(void *);
extern void func_02055f2c(void *, void *, int);
extern void NNS_G3dBindMdlTex(void *, void *);
extern void NNS_G3dBindMdlPltt(void *, void *);

void func_ov004_02230438(char *self, int i, void *p2, void *p3)
{
    char *a = self + 0x4b8 + i * 0xa4;
    char *b;
    func_ov004_0222c3f4(a, p2);
    b = self + 0x6a4 + i * 4;
    func_ov004_0222c348(b, p3);
    func_02055f2c(self + 0x290 + i * 0xb8, func_ov004_0222c3a0(a), 0);
    NNS_G3dBindMdlTex(func_ov004_0222c3a0(a), func_ov004_0222c33c(b));
    NNS_G3dBindMdlPltt(func_ov004_0222c3a0(a), func_ov004_0222c33c(b));
}
