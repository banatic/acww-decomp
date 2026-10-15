/* func_ov110_0229cea8 @ 0x0229cea8, 0xac bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d3d8(char *self, unsigned char c);
extern int func_ov110_0229d388(char *self, unsigned char c);
extern int func_0206fe54(void);
extern void func_0208aa80(char *addr);
extern void func_0208aa78(char *addr);
extern void func_0208aa60(char *addr, int a, int b);
extern int func_ov110_0229d5e4(char *self, unsigned char c);
extern int func_ov110_0229d5d4(char *self, unsigned char c);
extern int func_ov110_0229d590(char *self, unsigned char c);
extern void func_ov094_0229abb8(char *a, char *b, int c);

void func_ov110_0229cea8(char *self)
{
    int v6, v4, t;

    v6 = func_ov110_0229d3d8(self, ((unsigned char *) self)[0xf3]) - 0x6d;

    t = func_ov110_0229d388(self, ((unsigned char *) self)[0xf3]);
    v4 = t - 0x78;
    if (func_0206fe54() != 0) {
        v4 -= 8;
    }

    if (v4 < -92) {
        func_0208aa80(self + 0x21f8);
        v4 = func_ov110_0229d388(self, ((unsigned char *) self)[0xf3]) - 0x50;
    } else {
        func_0208aa78(self + 0x21f8);
    }

    func_0208aa60(self + 0x21f8, v6, v4);

    if (func_ov110_0229d5e4(self, ((unsigned char *) self)[0xf3]) != 0 ||
        func_ov110_0229d5d4(self, ((unsigned char *) self)[0xf3]) != 0) {
        t = func_ov110_0229d590(self, ((unsigned char *) self)[0xf3]);
        func_ov094_0229abb8(self + 0x138, self + 0x21f8, t);
    }
}
