/* func_ov138_0229c7fc @ 0x0229c7fc, 0x5c bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov138_0229c7a8(void *p);
extern int func_ov138_0229c754(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern int func_ov138_0229c574(void *p, int);
extern void func_ov002_0220a374(void *p, int);
extern void func_ov138_0229c66c(void *p);

void func_ov138_0229c7fc(unsigned char *self)
{
    int a, b;

    a = func_ov138_0229c7a8(self);
    b = func_ov138_0229c754(self);
    func_ov002_0220a0b4(self + 0x98, a, b);

    if (func_ov138_0229c574(self, 2) != 0 || (self[0x95] != 3 && self[0x95] != 4)) {
        func_ov002_0220a374(self + 0x98, 1);
    } else {
        func_ov002_0220a374(self + 0x98, 7);
    }

    func_ov138_0229c66c(self);
}
