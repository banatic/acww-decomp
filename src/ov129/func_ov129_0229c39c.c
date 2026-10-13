/* func_ov129_0229c39c @ 0x0229c39c, 0x58 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229c548(void *self);
extern int func_ov129_0229c520(void *self);
extern int func_ov129_0229c468(void *self);
extern int func_ov129_0229c418(void *self);
extern void func_ov129_0229c368(void *self, int a, int b);
extern void func_ov002_0220a2b4(void *p);
extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a254(void *p);

void func_ov129_0229c39c(void *self)
{
    if (func_ov129_0229c548(self)) {
        func_ov002_0220a2b4((char *) self + 0x3a0);
    } else if (func_ov129_0229c520(self)) {
        func_ov002_0220a314((char *) self + 0x3a0);
    } else {
        func_ov002_0220a254((char *) self + 0x3a0);
    }
    {
        int p = func_ov129_0229c468(self);
        int q = func_ov129_0229c418(self);
        func_ov129_0229c368(self, p, q);
    }
}
