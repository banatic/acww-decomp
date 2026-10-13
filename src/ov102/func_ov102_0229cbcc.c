/* func_ov102_0229cbcc @ 0x0229cbcc, 0x58 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229cb84(void *);
extern int func_ov102_0229cb74(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern int func_ov102_0229d438(void *, unsigned char);
extern void func_ov002_0220a374(void *, int);
extern void func_ov102_0229ca98(void *);

void func_ov102_0229cbcc(unsigned char *self)
{
    int a;
    int b;

    a = func_ov102_0229cb84(self);
    b = func_ov102_0229cb74(self);
    func_ov002_0220a0b4(self + 0x2274, a, b);
    if (func_ov102_0229d438(self, self[0x25a5]) != 0) {
        func_ov002_0220a374(self + 0x2274, 7);
    } else {
        func_ov002_0220a374(self + 0x2274, 1);
    }
    func_ov102_0229ca98(self);
}
