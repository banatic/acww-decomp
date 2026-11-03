/* bbs_board: 3 functions, module ov113
 * mwccarm 1.2/base -O4,s
 * func_ov113_0229990c @ 0x0229990c, 0x74 bytes, Thumb
 * func_ov113_022998ec @ 0x022998ec, 0x20 bytes, Thumb
 * func_ov113_022998cc @ 0x022998cc, 0x20 bytes, Thumb
 */

extern int func_ov113_02299da4(unsigned char *self, int n);
extern int func_ov113_022999c4(unsigned char *self);
extern int func_ov113_022999a4(unsigned char *self);
extern void func_ov113_02299d84(unsigned char *self, int n);
extern void func_ov002_0220a0b4(unsigned char *base, int a, int b);
extern void func_ov002_0220a05c(unsigned char *base, int a, int b, int c, int d);
extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *);

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
        func_ov002_02208098((void *) self, 2);
    }
}

void func_ov113_022998ec(void *arg)
{
    func_ov002_0220a1dc((char *) arg + 0x2b20);
    func_ov002_02208098(arg, 3);
}

void func_ov113_022998cc(void *p)
{
    func_ov002_0220a164((char *) p + 0x2b20);
    func_ov002_02208098(p, 4);
}
