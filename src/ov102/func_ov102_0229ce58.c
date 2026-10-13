/* func_ov102_0229ce58 @ 0x0229ce58, 0xa0 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d1e8(void *, unsigned char);
extern int func_ov102_0229d178(void *, unsigned char);
extern int func_0206fe54(void);
extern void func_0208aa80(void *);
extern void func_0208aa78(void *);
extern void func_0208aa60(void *, int, int);
extern int func_ov102_0229d464(void *, unsigned char);
extern int func_ov102_0229d454(void *, unsigned char);
extern int func_ov102_0229d400(void *, unsigned char);
extern void func_ov094_0229abb8(void *, void *, int);

void func_ov102_0229ce58(unsigned char *self)
{
    int r6, r4;

    r6 = func_ov102_0229d1e8(self, *(unsigned char *) (self + 0x25a1)) - 0x6d;
    r4 = func_ov102_0229d178(self, *(unsigned char *) (self + 0x25a1)) - 0x78;

    if (func_0206fe54() != 0) {
        r4 -= 8;
    }

    if (r4 < -92) {
        func_0208aa80(self + 0x218c);
        r4 = func_ov102_0229d178(self, *(unsigned char *) (self + 0x25a1)) - 0x50;
    } else {
        func_0208aa78(self + 0x218c);
    }

    func_0208aa60(self + 0x218c, r6, r4);

    if (func_ov102_0229d464(self, *(unsigned char *) (self + 0x25a1)) != 0 ||
        func_ov102_0229d454(self, *(unsigned char *) (self + 0x25a1)) != 0) {
        int tmp = func_ov102_0229d400(self, *(unsigned char *) (self + 0x25a1));
        func_ov094_0229abb8(self + 0xcc, self + 0x218c, tmp);
    }
}
