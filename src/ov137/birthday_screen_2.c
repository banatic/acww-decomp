/* birthday_screen_2: 2 functions, module ov137
 * mwccarm 1.2/base -O4,s
 * func_ov137_0229c6e4 @ 0x0229c6e4, 0x50 bytes, Thumb
 * func_ov137_0229c684 @ 0x0229c684, 0x60 bytes, Thumb
 */

extern int func_ov137_0229c574(void *arg, int n);
extern void func_ov002_0220a2b4(void *p);
extern void func_ov002_0220a314(void *p);
extern int func_ov137_0229c794(void *arg);
extern int func_ov137_0229c750(void *arg);
extern void func_ov002_0220a05c(unsigned char *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(unsigned char *self, unsigned char value);
extern void func_ov137_0229c554(unsigned char *self, int n);

void func_ov137_0229c684(unsigned char *self, int arg2, int arg3);

void func_ov137_0229c6e4(void *arg)
{
    if (!(func_ov137_0229c574(arg, 2) == 0 && ((unsigned char *) arg)[0x2b77] == 2)) {
        func_ov002_0220a2b4((char *) arg + 0x94);
    } else {
        func_ov002_0220a314((char *) arg + 0x94);
    }
    {
        int a = func_ov137_0229c794(arg);
        int b = func_ov137_0229c750(arg);
        func_ov137_0229c684((unsigned char *) arg, a, b);
    }
}

void func_ov137_0229c684(unsigned char *self, int arg2, int arg3)
{
    if (func_ov137_0229c574((void *) self, 4) != 0) {
        func_ov002_0220a05c(self + 0x94, arg2, arg3, 2, 1);
    } else {
        func_ov002_0220a05c(self + 0x94, arg2, arg3, 3, 1);
    }
    self[0x2b76] = self[0x8d];
    func_ov002_02208098(self, 8);
    func_ov137_0229c554(self, 4);
}
