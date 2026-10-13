/* func_ov113_0229990c @ 0x0229990c, 0x74 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov113_02299da4(unsigned char *self, int n);
extern int func_ov113_022999c4(unsigned char *self);
extern int func_ov113_022999a4(unsigned char *self);
extern void func_ov113_02299d84(unsigned char *self, int n);
extern void func_ov002_0220a0b4(unsigned char *base, int a, int b);
extern void func_ov002_0220a05c(unsigned char *base, int a, int b, int c, int d);
extern void func_ov002_02208098(unsigned char *self, int n);

void func_ov113_0229990c(unsigned char *self)
{
    int v1, v2;

    if (func_ov113_02299da4(self, 0x80) != 0) {
        v1 = func_ov113_022999c4(self);
        v2 = func_ov113_022999a4(self);
        func_ov002_0220a0b4(self + 0x2b20, v1, v2);
        func_ov113_02299d84(self, 0x80);
    } else {
        v1 = func_ov113_022999c4(self);
        v2 = func_ov113_022999a4(self);
        func_ov002_0220a05c(self + 0x2b20, v1, v2, 4, 1);
        self[0x9c] = self[0x8d];
        func_ov002_02208098(self, 2);
    }
}
