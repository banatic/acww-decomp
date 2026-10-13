/* func_ov137_0229c7d8 @ 0x0229c7d8, 0x5c bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov137_0229c794(void *self);
extern int func_ov137_0229c750(void *self);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern int func_ov137_0229c574(void *self, int x);
extern void func_ov002_0220a374(void *p, int v);
extern void func_ov137_0229c668(void *self);

void func_ov137_0229c7d8(void *self)
{
    int a;
    int b;

    a = func_ov137_0229c794(self);
    b = func_ov137_0229c750(self);
    func_ov002_0220a0b4((char *) self + 0x94, a, b);

    if (func_ov137_0229c574(self, 2) != 0 || *(unsigned char *) ((char *) self + 0x2b77) != 2) {
        func_ov002_0220a374((char *) self + 0x94, 1);
    } else {
        func_ov002_0220a374((char *) self + 0x94, 7);
    }

    func_ov137_0229c668(self);
}
